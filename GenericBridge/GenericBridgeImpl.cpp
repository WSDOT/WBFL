///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// GenericBridgeImpl.cpp : Implementation of CGenericBridge
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "GenericBridgeImpl.h"
#include "StageCollection.h"
#include "PierCollection.h"
#include "Pier.h"
#include "SpanCollection.h"
#include "Span.h"
#include "SuperstructureMemberCollection.h"
#include "CogoInfo.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenericBridge
HRESULT CGenericBridge::FinalConstruct()
{
   CComObject<CStageCollection>* pStages;
   CComObject<CStageCollection>::CreateInstance(&pStages);
   m_Stages = pStages;
   AdviseChild(m_Stages,IID_IStageCollectionEvents,&m_dwStagesCookie);
   pStages->SetBridge(this);

   CComObject<CPierCollection>* pPiers;
   CComObject<CPierCollection>::CreateInstance(&pPiers);
   m_Piers = pPiers;
   AdviseChild(m_Piers,IID_IPierCollectionEvents,&m_dwPiersCookie);
   pPiers->SetBridge(this);

   CComObject<CSpanCollection>* pSpans;
   CComObject<CSpanCollection>::CreateInstance(&pSpans);
   m_Spans = pSpans;
   AdviseChild(m_Spans,IID_ISpanCollectionEvents,&m_dwSpansCookie);
   pSpans->SetBridge(this);

   HRESULT hr;
   hr = m_CogoModel.CoCreateInstance(CLSID_CogoModel);
   ATLASSERT(SUCCEEDED(hr));

   hr = m_CogoEngine.CoCreateInstance(CLSID_CogoEngine);
   ATLASSERT(SUCCEEDED(hr));

   hr = m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<IPathCollection> alignments;
   m_CogoModel->get_Alignments(&alignments);

   CComPtr<IPath> path;
   alignments->Add(g_AlignmentKey,&path);
   path.QueryInterface(&m_Alignment);
   AdviseChild(m_Alignment,IID_IPathEvents,&m_dwAlignmentCookie);

   CComObject<CCogoInfo>* pCogoInfo;
   CComObject<CCogoInfo>::CreateInstance(&pCogoInfo);
   pCogoInfo->SetBridge(this);
   m_CogoInfo = pCogoInfo;

   return S_OK;
}

void CGenericBridge::FinalRelease()
{
   UnadviseChild(m_Stages,IID_IStageCollectionEvents,m_dwStagesCookie);
   UnadviseChild(m_Piers,IID_IPierCollectionEvents,m_dwPiersCookie);
   UnadviseChild(m_Spans,IID_ISpanCollectionEvents,m_dwSpansCookie);
   UnadviseChild(m_Alignment,IID_IPathEvents,m_dwAlignmentCookie);

   m_Stages.Release();
   m_Piers.Release();
   m_Spans.Release();
   m_Alignment.Release();
   m_CogoModel.Release();

   if ( m_Deck )
   {
      InternalAddRef();
      AtlUnadvise(m_Deck,IID_IBridgeDeckEvents,m_dwDeckCookie);
   }
}

STDMETHODIMP CGenericBridge::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGenericBridge,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CGenericBridge::SetCollections(IStageCollection* stages,ISpanCollection* spans,IPierCollection* piers)
{
   // Unadvice all current connection points
   UnadviseChild(m_Stages,IID_IStageCollectionEvents,m_dwStagesCookie);
   UnadviseChild(m_Piers,IID_IPierCollectionEvents,m_dwPiersCookie);
   UnadviseChild(m_Spans,IID_ISpanCollectionEvents,m_dwSpansCookie);

   // Remove the parent pointer down
   dynamic_cast<CPierCollection*>(m_Piers.p)->SetBridge(NULL);
   dynamic_cast<CSpanCollection*>(m_Spans.p)->SetBridge(NULL);

   // Update the interface pointers
   m_Stages = stages;
   m_Piers = piers;
   m_Spans = spans;

   // Pass the parent pointer down
   dynamic_cast<CPierCollection*>(m_Piers.p)->SetBridge(this);
   dynamic_cast<CSpanCollection*>(m_Spans.p)->SetBridge(this);

   // Advise all the new connection points
   AdviseChild(m_Stages,IID_IStageCollectionEvents,&m_dwStagesCookie);
   AdviseChild(m_Piers,IID_IPierCollectionEvents,&m_dwPiersCookie);
   AdviseChild(m_Spans,IID_ISpanCollectionEvents,&m_dwSpansCookie);

   LinkSpansAndPiers();

   DoUpdateBridgeModel();
}

void CGenericBridge::LinkSpansAndPiers()
{
   // Hook the piers to the spans
   PierIndexType nPiers;
   m_Piers->get_Count(&nPiers);
   for ( PierIndexType pierIdx = 0; pierIdx < nPiers; pierIdx++ )
   {
      CComPtr<IPier> pier;
      m_Piers->get_Item(pierIdx,&pier);

      CPier* pPier = dynamic_cast<CPier*>(pier.p);

      pPier->SetIndex(pierIdx);

      CSpan* pPrevSpan = NULL;
      CSpan* pNextSpan = NULL;

      CComPtr<ISpan> prevSpan;
      CComPtr<ISpan> nextSpan;

      if ( pierIdx != 0 )
      {
         m_Spans->get_Item(pierIdx-1,&prevSpan);
         pPrevSpan = dynamic_cast<CSpan*>(prevSpan.p);
      }

      if ( pierIdx < nPiers-1 )
      {
         m_Spans->get_Item(pierIdx,&nextSpan);
         pNextSpan = dynamic_cast<CSpan*>(nextSpan.p);
      }

      pPier->SetSpans(pPrevSpan,pNextSpan);
   }

   // Hook up the spans to the piers
   SpanIndexType nSpans;
   m_Spans->get_Count(&nSpans);
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      CComPtr<ISpan> span;
      m_Spans->get_Item(spanIdx,&span);

      CSpan* pSpan = dynamic_cast<CSpan*>(span.p);

      pSpan->SetIndex(spanIdx);

      CComPtr<IPier> prevPier;
      CComPtr<IPier> nextPier;

      m_Piers->get_Item(spanIdx,  &prevPier);
      m_Piers->get_Item(spanIdx+1,&nextPier);

      CPier* pPrevPier = dynamic_cast<CPier*>(prevPier.p);
      CPier* pNextPier = dynamic_cast<CPier*>(nextPier.p);

      pSpan->SetPiers(pPrevPier,pNextPier);
   }
}

CPierCollection* CGenericBridge::GetPierCollection()
{
   return dynamic_cast<CPierCollection*>(m_Piers.p);
}

CSpanCollection* CGenericBridge::GetSpanCollection()
{
   return dynamic_cast<CSpanCollection*>(m_Spans.p);
}

void CGenericBridge::DoUpdateBridgeModel()
{
   if ( m_bHoldUpdate )
      return;

   //////////////////////////////////
   // Update COGO model

   // clear the previously computed points
   CComPtr<IPointCollection> points;
   m_CogoModel->get_Points(&points);
   points->Clear();

   // clear the previously created line segments
   // that represent the girder lines
   CComPtr<ILineSegmentCollection> lineSegments;
   m_CogoModel->get_LineSegments(&lineSegments);
   lineSegments->Clear();

   // get the alignment
   CComPtr<IPathCollection> alignments;
   m_CogoModel->get_Alignments(&alignments);

   CComPtr<IPathCollection> paths;
   m_CogoModel->get_Paths(&paths);

   CComPtr<IPath> path;
   alignments->get_Item(g_AlignmentKey,&path);
   CComQIPtr<IAlignment> alignment(path);
   ATLASSERT(alignment != NULL);

   CComPtr<IPath> clBridge;
   paths->Remove(g_CLBridgeKey);
   path->CreateParallelPath(m_AlignmentOffset,&clBridge);
   paths->AddEx(g_CLBridgeKey,clBridge);

   // locate each pier on the alignment
   PierIndexType nPiers;
   m_Piers->get_Count(&nPiers);
   for ( PierIndexType pierIdx = 0; pierIdx < nPiers; pierIdx++ )
   {
      CComPtr<IPier> pier;
      m_Piers->get_Item(pierIdx,&pier);

      CComPtr<IStation> objStation;
      pier->get_Station(&objStation);

      // Locate the Alignment-Pier intersection point
      CComPtr<IPoint2d> point;
      alignment->LocatePoint(CComVariant(objStation),omtAlongDirection, 0.00,CComVariant(0.00),&point);

      CogoElementKey pointID;
      ::GB_GetPierAlignmentPointId(pierIdx,&pointID);
      points->AddEx(pointID,point);
   }

   // for each span, locate the intersection of each girder line
   // with the CL pier and CL bearing. Create a line segment that represents the girder
   SpanIndexType nSpans;
   m_Spans->get_Count(&nSpans);
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      CComPtr<ISpan> span;
      m_Spans->get_Item(spanIdx,&span);

      UpdatePierGirderIntersectionPoints(spanIdx,span);

      GirderIndexType nGirders;
      span->get_GirderCount(&nGirders);
      for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirders; gdrIdx++ )
      {
         CComPtr<ILineSegment2d> objLS;
         CComPtr<IPoint2d> objA, objB;
         CogoElementKey ptA, ptB;
         ::GB_GetPierGirderPointId(spanIdx,  gdrIdx, qcbAfter,  &ptA);
         ::GB_GetPierGirderPointId(spanIdx+1,gdrIdx, qcbBefore, &ptB);
         points->get_Item(ptA,&objA);
         points->get_Item(ptB,&objB);
         
         CogoElementKey lineID;
         ::GB_GetGirderLineId(spanIdx,gdrIdx,&lineID);
         lineSegments->Add(lineID,objA,objB,&objLS);

         UpdateGirderEndPoints(spanIdx,gdrIdx);
      }
   }
}

void CGenericBridge::UpdatePierGirderIntersectionPoints(SpanIndexType spanIdx,ISpan* pSpan)
{
   PierIndexType prevPierIdx = spanIdx;
   PierIndexType nextPierIdx = prevPierIdx+1;

   // get the piers on either end of span
   CComPtr<IPier> prevPier, nextPier;
   pSpan->get_PrevPier(&prevPier);
   pSpan->get_NextPier(&nextPier);

   // get the station and direction of the piers
   CComPtr<IDirection> objPrevPierDirection, objNextPierDirection;
   CComPtr<IStation> objPrevPierStation, objNextPierStation;
   prevPier->get_Direction(&objPrevPierDirection);
   prevPier->get_Station(&objPrevPierStation);
   nextPier->get_Direction(&objNextPierDirection);
   nextPier->get_Station(&objNextPierStation);

   Float64 prevPierStation, nextPierStation;
   objPrevPierStation->get_Value(&prevPierStation);
   objNextPierStation->get_Value(&nextPierStation);

   Float64 prevPierDirection, nextPierDirection;
   objPrevPierDirection->get_Value(&prevPierDirection);
   objNextPierDirection->get_Value(&nextPierDirection);

   // get the connections
   CComPtr<IConnection> startConnection, endConnection;
   prevPier->get_Connection(qcbAfter,&startConnection);
   nextPier->get_Connection(qcbBefore,&endConnection);

   // get the bearing offsets
   Float64 start_brg_offset, end_brg_offset;
   MeasurementType start_brg_offset_measure, end_brg_offset_measure;

   startConnection->get_BearingOffset(&start_brg_offset);
   startConnection->get_BearingOffsetMeasurementType(&start_brg_offset_measure);

   endConnection->get_BearingOffset(&end_brg_offset);
   endConnection->get_BearingOffsetMeasurementType(&end_brg_offset_measure);

   // get the girder spacing
   CComPtr<IGirderSpacing> startSpacing;
   prevPier->get_GirderSpacing(qcbAfter,&startSpacing);

   CComPtr<IGirderSpacing> endSpacing;
   nextPier->get_GirderSpacing(qcbBefore,&endSpacing);

   MeasurementType mtStart, mtEnd;
   MeasurementLocation mlStart, mlEnd;
   startSpacing->get_MeasurementType(&mtStart);
   startSpacing->get_MeasurementLocation(&mlStart);
   endSpacing->get_MeasurementType(&mtEnd);
   endSpacing->get_MeasurementLocation(&mlEnd);

   GirderIndexType startRefGirderIdx, endRefGirderIdx;
   Float64 startRefGirderOffset, endRefGirderOffset;
   OffsetType startRefGirderOffsetType, endRefGirderOffsetType;
   startSpacing->get_RefGirder(&startRefGirderIdx);
   startSpacing->get_RefGirderOffset(&startRefGirderOffset);
   startSpacing->get_RefGirderOffsetType(&startRefGirderOffsetType);

   endSpacing->get_RefGirder(&endRefGirderIdx);
   endSpacing->get_RefGirderOffset(&endRefGirderOffset);
   endSpacing->get_RefGirderOffsetType(&endRefGirderOffsetType);

   // get alignment offsets
   Float64 prev_pier_alignment_offset = m_AlignmentOffset;
   if ( mtStart == mtAlongItem )
   {
      CComPtr<IAngle> objPrevPierSkewAngle;
      prevPier->get_SkewAngle(&objPrevPierSkewAngle);
      Float64 prev_pier_skew_angle;
      objPrevPierSkewAngle->get_Value(&prev_pier_skew_angle);

      // alignment_offset is measured normal to alignment.. skew adjust it so it is measured in
      // the along the pier
      prev_pier_alignment_offset /= cos(fabs(prev_pier_skew_angle));
   }


   Float64 next_pier_alignment_offset = m_AlignmentOffset;
   if ( mtEnd == mtAlongItem )
   {
      CComPtr<IAngle> objNextPierSkewAngle;
      nextPier->get_SkewAngle(&objNextPierSkewAngle);
      Float64 next_pier_skew_angle;
      objNextPierSkewAngle->get_Value(&next_pier_skew_angle);

      // alignment_offset is measured normal to alignment.. skew adjust it so it is measured in
      // the along the pier
      next_pier_alignment_offset /= cos(fabs(next_pier_skew_angle));
   }

   // sum all of the individual spacing to get the total spacing width
   // at the start and end of the span (we'll need this to lay out the girder points)
   GirderIndexType nGirders;
   pSpan->get_GirderCount(&nGirders);
   SpacingIndexType nSpaces = (nGirders == 0 ? 0 : nGirders-1);

   Float64 start_spacing_width = 0;
   Float64 end_spacing_width   = 0;
   for ( SpacingIndexType spaceIdx = 0; spaceIdx < nSpaces; spaceIdx++ )
   {
      Float64 spacing;
      startSpacing->get_Spacing(spaceIdx,&spacing);
      start_spacing_width += spacing;

      endSpacing->get_Spacing(spaceIdx,&spacing);
      end_spacing_width += spacing;
   }

   // get the alignment
   CComPtr<IPathCollection> alignments;
   m_CogoModel->get_Alignments(&alignments);

   CComPtr<IPathCollection> paths;
   m_CogoModel->get_Paths(&paths);

   CComPtr<IPath> path;
   alignments->get_Item(g_AlignmentKey,&path);
   CComQIPtr<IAlignment> alignment(path);
   ATLASSERT(alignment != NULL);

   // get the CL bridge path
   CComPtr<IPath> clBridge;
   paths->get_Item(g_CLBridgeKey,&clBridge);

   // get the cogo point collection
   CComPtr<IPointCollection> points;
   m_CogoModel->get_Points(&points);

   // get the interfaces we need to do the COGO computations
   CComQIPtr<ILocate> locate(m_CogoModel);
   CComQIPtr<ILocate2> locate2(m_CogoEngine);
   CComQIPtr<IIntersect2> intersect(m_CogoEngine);
   CComQIPtr<IMeasure2> measure(m_CogoEngine);


   // get intersection point of pier and alignment
   CComPtr<IPoint2d> pntStartPier, pntEndPier;
   CogoElementKey startPierPointID;
   ::GB_GetPierAlignmentPointId(prevPierIdx,&startPierPointID);
   points->get_Item(startPierPointID,&pntStartPier);

   CogoElementKey endPierPointID;
   ::GB_GetPierAlignmentPointId(nextPierIdx,&endPierPointID);
   points->get_Item(endPierPointID,&pntEndPier);

   // create a line to represent the CL of start pier
   CComPtr<ILine2d> objStartPierLine;
   objStartPierLine.CoCreateInstance(CLSID_Line2d);

   CComPtr<IVector2d> v;
   CComPtr<IPoint2d> p;
   objStartPierLine->GetExplicit(&p,&v);
   v->put_Direction(prevPierDirection);
   objStartPierLine->SetExplicit(pntStartPier,v);

   // create a line to represent the line normal to the alignment at the start pier
   CComPtr<ILine2d> objStartPierNormalLine;
   objStartPierNormalLine.CoCreateInstance(CLSID_Line2d);
   CComPtr<IDirection> objStartPierNormal;
   alignment->Normal(CComVariant(objPrevPierStation),&objStartPierNormal);
   Float64 dir;
   objStartPierNormal->get_Value(&dir);
   p.Release();
   v.Release();
   objStartPierNormalLine->GetExplicit(&p,&v);
   v->put_Direction(dir);
   objStartPierNormalLine->SetExplicit(pntStartPier,v);


   //
   // locate the CL Bridge - CL Pier intersection point at start of bridge
   //
   CComPtr<IPoint2d> pntStartPierBridge;
   clBridge->Intersect(objStartPierLine,pntStartPier,&pntStartPierBridge);
   CogoElementKey pointID;
   ::GB_GetPierCLBridgePointId(prevPierIdx,&pointID);
   points->AddEx(pointID,pntStartPierBridge);

   //
   // locate CL brg stations
   //
   CComPtr<IStation> objStartBrgStation;
   CComPtr<ILine2d> objStartBrgLine;
   CComPtr<ILine2d> objStartBrgNormalLine;
   if ( start_brg_offset_measure == mtNormal )
   {
      // bearing offset is measured normal to the cl pier.
      // since the alignent could be curved a simple triangle wont work
      //

      // create parallel line to represent the CL bearing
      CComPtr<ILine2d> brgLine;
      m_GeomUtil->CreateParallelLine(objStartPierLine,start_brg_offset,&objStartBrgLine);

      // intersect the alignment and the bearing line
      CComPtr<IPoint2d> pntStartBrg;
      alignment->Intersect(objStartBrgLine,pntStartPier,&pntStartBrg);

      // get station of the intersection point
      Float64 offset;
      alignment->Offset(pntStartBrg,&objStartBrgStation,&offset);
      ATLASSERT( IsZero(offset) );

      // create a line normal to the alignment at the CL Brg
      CComPtr<IDirection> dirStartBrgNormal;
      alignment->Normal(CComVariant(objStartBrgStation),&dirStartBrgNormal);

      Float64 startBrgNormalDirection;
      dirStartBrgNormal->get_Value(&startBrgNormalDirection);
   
      objStartBrgNormalLine.CoCreateInstance(CLSID_Line2d);
      CComPtr<IPoint2d> p;
      CComPtr<IVector2d> v;
      objStartBrgNormalLine->GetExplicit(&p,&v);
      v->put_Direction(startBrgNormalDirection);
      objStartBrgNormalLine->SetExplicit(pntStartBrg,v);
   }
   else
   {
      // bearing offset is measured along the girder. With the general geometry
      // there are multiple bearing lines. We cannot have a single bearing station
      ATLASSERT( mlStart == mlPierLine ); // spacing must be measured relative to pier datum line
   }

   // create a line to represent the CL of end pier
   CComPtr<ILine2d> objEndPierLine;
   objEndPierLine.CoCreateInstance(CLSID_Line2d);
   p.Release();
   v.Release();
   objEndPierLine->GetExplicit(&p,&v);
   v->put_Direction(nextPierDirection);
   objEndPierLine->SetExplicit(pntEndPier,v);

   // create a line to represent the line normal to the alignment at the end pier
   CComPtr<ILine2d> objEndPierNormalLine;
   objEndPierNormalLine.CoCreateInstance(CLSID_Line2d);
   CComPtr<IDirection> objEndPierNormal;
   alignment->Normal(CComVariant(objNextPierStation),&objEndPierNormal);
   objEndPierNormal->get_Value(&dir);
   p.Release();
   v.Release();
   objEndPierNormalLine->GetExplicit(&p,&v);
   v->put_Direction(dir);
   objEndPierNormalLine->SetExplicit(pntEndPier,v);

   //
   // locate the CL Bridge - CL Pier intersection point at end of bridge
   //
   CComPtr<IPoint2d> pntEndPierBridge;
   clBridge->Intersect(objEndPierLine,pntEndPier,&pntEndPierBridge);
   ::GB_GetPierCLBridgePointId(nextPierIdx,&pointID);
   points->AddEx(pointID,pntEndPierBridge);

   CComPtr<IStation> objEndBrgStation;
   CComPtr<ILine2d> objEndBrgLine;
   CComPtr<ILine2d> objEndBrgNormalLine;
   if ( end_brg_offset_measure == mtNormal )
   {
      // bearing offset is measured normal to the cl pier.
      // since the alignent could be curved a simple triangle wont work
      //

      // create parallel line to represent the CL bearing
      m_GeomUtil->CreateParallelLine(objEndPierLine,-end_brg_offset,&objEndBrgLine);

      // intersect the alignment and the bearing line
      CComPtr<IPoint2d> pntEndBrg;
      alignment->Intersect(objEndBrgLine,pntEndPier,&pntEndBrg);

      // get station of the intersection point
      Float64 offset;
      alignment->Offset(pntEndBrg,&objEndBrgStation,&offset);
      ATLASSERT( IsZero(offset) );

      // create a line normal to the alignment at the CL Brg
      CComPtr<IDirection> dirEndBrgNormal;
      alignment->Normal(CComVariant(objEndBrgStation),&dirEndBrgNormal);

      Float64 endBrgNormalDirection;
      dirEndBrgNormal->get_Value(&endBrgNormalDirection);
   
      objEndBrgNormalLine.CoCreateInstance(CLSID_Line2d);
      CComPtr<IPoint2d> p;
      CComPtr<IVector2d> v;
      objEndBrgNormalLine->GetExplicit(&p,&v);
      v->put_Direction(endBrgNormalDirection);
      objEndBrgNormalLine->SetExplicit(pntEndBrg,v);
   }
   else
   {
      // bearing offset is measured along the girder. With the general geometry
      // there are multiple bearing lines. We cannot have a single bearing station
      ATLASSERT( mlEnd == mlPierLine ); // spacing must be measured relative to pier datum line
   }

   // get intersection point of bearing and alignment (if bearing is uniquely located)
   CComPtr<IPoint2d> pntStartBrg, pntEndBrg;
   if ( start_brg_offset_measure == mtNormal )
      alignment->LocatePoint(CComVariant(objStartBrgStation),omtAlongDirection, 0.00,CComVariant(objPrevPierDirection),&pntStartBrg);

   if ( end_brg_offset_measure == mtNormal )
      alignment->LocatePoint(CComVariant(objEndBrgStation),  omtAlongDirection, 0.00,CComVariant(objNextPierDirection),&pntEndBrg);

   //
   // get station and direction of the lines along which the
   // girder spacing is measured
   //

   // start of span
   Float64 startStation, startDir;
   if ( mlStart == mlPierLine )
   {
      startStation = prevPierStation;
   }
   else
   {
      ATLASSERT( start_brg_offset_measure == mtNormal );
      objStartBrgStation->get_Value(&startStation);
   }

   // get direction of line
   if ( mtStart == mtNormal )
   {
      CComPtr<IDirection> dir;
      alignment->Normal(CComVariant(startStation),&dir); // alignment normals are to the right
      dir->IncrementBy(CComVariant(M_PI)); // rotate by 180 deg so line points left of alignment
      dir->get_Value(&startDir);
   }
   else
   {
      startDir = prevPierDirection;
   }

   // end of line
   Float64 endStation, endDir;
   if ( mlEnd == mlPierLine )
   {
      endStation = nextPierStation;
   }
   else
   {
      ATLASSERT( end_brg_offset_measure == mtNormal );
      objEndBrgStation->get_Value(&endStation);
   }


   // get direction of line
   if ( mtEnd == mtNormal )
   {
      CComPtr<IDirection> dir;
      alignment->Normal(CComVariant(endStation),&dir);
      dir->IncrementBy(CComVariant(M_PI)); // rotate by 180 deg so line points left of alignment
      dir->get_Value(&endDir);
   }
   else
   {
      endDir = nextPierDirection;
   }


   //
   // locate work points at the intersection of the line girder spacing is measured along and the girder lines
   //

   Float64 start_left_girder; // distance from alignment to left most girder
   if ( startRefGirderIdx == ALL_GIRDERS )
   {
      // the transverse placement of the girders at the start ofthe span is based on the
      // mid-point of the spacing width
      start_left_girder = -(start_spacing_width/2) + startRefGirderOffset;
   }
   else
   {
      // the transverse placement of the girders at the start ofthe span is based on 
      // the location of a specific girder measured from the CL bridge or alignment
      start_left_girder = startRefGirderOffset; 
      for ( GirderIndexType i = 0; i < startRefGirderIdx; i++ )
      {
         Float64 spacing;
         startSpacing->get_Spacing(i,&spacing);
         start_left_girder -= spacing;
      }
   }
   
   if ( startRefGirderOffsetType == otBridge )
   {
      // the offset is relative to the CL bridge, shift the girders
      // so that they are relative to the alignment
      start_left_girder += prev_pier_alignment_offset;
   }

   Float64 start_offset = start_left_girder; // distance from alignment

   ///////////////////////

   Float64 end_left_girder; // distance from alignment to left most girder
   if ( endRefGirderIdx == ALL_GIRDERS )
   {
      // the transverse placement of the girders at the end ofthe span is based on the
      // mid-point of the spacing width
      end_left_girder = -(end_spacing_width/2) + endRefGirderOffset;
   }
   else
   {
      // the transverse placement of the girders at the end ofthe span is based on 
      // the location of a specific girder measured from the CL bridge or alignment
      end_left_girder = endRefGirderOffset; 
      for ( GirderIndexType i = 0; i < endRefGirderIdx; i++ )
      {
         Float64 spacing;
         endSpacing->get_Spacing(i,&spacing);
         end_left_girder -= spacing;
      }
   }
   
   if ( endRefGirderOffsetType == otBridge )
   {
      // the offset is relative to the CL bridge, shift the girders
      // so that they are relative to the alignment
      end_left_girder += next_pier_alignment_offset;
   }

   Float64 end_offset = end_left_girder; // distance from alignment

   PierIndexType prev_pier_idx = spanIdx;
   PierIndexType next_pier_idx = prev_pier_idx+1;

   // locate work points
   // connect these points into lines to represent the centerline of the girders
   // intersect the girder lines with the measurement line
   // locate the CL brg/girder and CL pier/girder intersections
   for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirders; gdrIdx++ )
   {
      if ( gdrIdx != 0 )
      {
         Float64 space;
         startSpacing->get_Spacing(gdrIdx-1,&space);
         start_offset += space;

         endSpacing->get_Spacing(gdrIdx-1,&space);
         end_offset += space;
      }

      // locate work point near start of girder
      CComPtr<IPoint2d> pntStartGirder;
      if ( mtStart == mtAlongItem )
      {
         alignment->LocatePoint(CComVariant(startStation),omtAlongDirection, -start_offset,CComVariant(startDir),&pntStartGirder);
      }
      else
      {
         // work point is on the CL pier/brg at the intersection of the CL pier/brg and
         // a path that is parallel to the alignment passing through the normal line
         // at the "start_offset" from the alignment
         ATLASSERT( mtStart == mtNormal );

         // create parallel path
         CComPtr<IPath> parallel_path;
         HRESULT hr = path->CreateParallelPath(start_offset,&parallel_path);
         ATLASSERT(SUCCEEDED(hr));

         // intersection with CL pier/brg line
         if ( mlStart == mlPierLine )
         {
#if defined _DEBUG
            VARIANT_BOOL bContainsPoint;
            m_GeomUtil->DoesLineContainPoint(objStartPierNormalLine,pntStartPier,1e-6,&bContainsPoint);
            ATLASSERT( bContainsPoint == VARIANT_TRUE);
#endif
            hr = parallel_path->Intersect(objStartPierNormalLine,pntStartPier,&pntStartGirder);
         }
         else
         {
#if defined _DEBUG
            VARIANT_BOOL bContainsPoint;
            m_GeomUtil->DoesLineContainPoint(objStartBrgNormalLine,pntStartBrg,1e-6,&bContainsPoint);
            ATLASSERT( bContainsPoint == VARIANT_TRUE);
#endif
            hr = parallel_path->Intersect(objStartBrgNormalLine,pntStartBrg,&pntStartGirder);
         }

         ATLASSERT(SUCCEEDED(hr));
      }
#if defined _DEBUG
      Float64 xs,ys;
      pntStartGirder->get_X(&xs);
      pntStartGirder->get_Y(&ys);
      WATCH("Start Point: Span " << spanIdx << " GdrIdx " << gdrIdx << " X = " << xs << ", Y = " << ys);
#endif // _DEBUG

      // locate work point near end of girder
      CComPtr<IPoint2d> pntEndGirder;
      if ( mtEnd == mtAlongItem )
      {
         alignment->LocatePoint(CComVariant(endStation),omtAlongDirection, -end_offset,CComVariant(endDir),&pntEndGirder);
      }
      else
      {
         // work point is on the CL pier/brg at the intersection of the CL pier/brg and
         // a path that is parallel to the alignment passing through the normal line
         // at the "end_offset" from the alignment
         ATLASSERT( mtEnd == mtNormal );

         // create parallel path
         CComPtr<IPath> parallel_path;
         HRESULT hr = path->CreateParallelPath(end_offset,&parallel_path);
         ATLASSERT(SUCCEEDED(hr));

         // intersection with item line
         if ( mlEnd == mlPierLine )
            hr = parallel_path->Intersect(objEndPierNormalLine,pntEndPier,&pntEndGirder);
         else
            hr = parallel_path->Intersect(objEndBrgNormalLine,pntEndBrg,&pntEndGirder);

         ATLASSERT(SUCCEEDED(hr));
      }
#if defined _DEBUG
      Float64 xe,ye;
      pntEndGirder->get_X(&xe);
      pntEndGirder->get_Y(&ye);
      WATCH("End Point: Span " << spanIdx << " GdrIdx " << gdrIdx << " X = " << xe << ", Y = " << ye);
#endif // _DEBUG

      // get direction of girder line
      CComPtr<IDirection> objGirderDir;
      measure->Direction(pntStartGirder,pntEndGirder,&objGirderDir);
      Float64 dirGirder;
      objGirderDir->get_Value(&dirGirder);

      CComPtr<ILine2d> objGirderLine;
      objGirderLine.CoCreateInstance(CLSID_Line2d);

      CComPtr<IVector2d> gdrVector;
      gdrVector.CoCreateInstance(CLSID_Vector2d);
      gdrVector->put_Direction(dirGirder);
      objGirderLine->SetExplicit(pntStartGirder,gdrVector);

      ///////////////////////////////////////////////////////////////////
      // NOTE: The CL Pier and CL Bearing are parallel so you'll see the objPrev[Next]PierDirection
      // objects used when intersecting the CL bearing and CL girder
      ///////////////////////////////////////////////////////////////////

      //
      // intersect girder line with CL of start pier
      //
      CComPtr<IPoint2d> pntStartPierGirder;
      m_GeomUtil->LineLineIntersect(objStartPierLine,objGirderLine,&pntStartPierGirder);

      // save the point
      CogoElementKey startPointID;
      ::GB_GetPierGirderPointId(prev_pier_idx,gdrIdx,qcbAfter,&startPointID);
      points->AddEx(startPointID,pntStartPierGirder);

      //
      // intersect girder line with CL of end pier
      //
      CComPtr<IPoint2d> pntEndPierGirder;
      m_GeomUtil->LineLineIntersect(objEndPierLine,objGirderLine,&pntEndPierGirder);

      // save the point
      CogoElementKey endPointID;
      ::GB_GetPierGirderPointId(next_pier_idx,gdrIdx,qcbBefore,&endPointID);
      points->AddEx(endPointID,pntEndPierGirder);

      //
      // intersect girder line with CL of start pier bearing
      //
      CComPtr<IPoint2d> pntStartBrgGirder;
      if ( pntStartBrg )
      {
         // a unique bearing line was located
         // locate the intersection of the CL girder and the bearing at the start pier
         // by intersecting the CL girder and CL bearing lines
         m_GeomUtil->LineLineIntersect(objStartBrgLine,objGirderLine,&pntStartBrgGirder);
      }
      else
      {
         // there is not a unique bearing line. CL bearing is located by a measurement along
         // the CL girder.
         ATLASSERT(start_brg_offset_measure == mtAlongItem);
         locate2->PointOnLine(pntStartPierGirder,pntEndPierGirder,start_brg_offset,0.00,&pntStartBrgGirder);
      }

      // store the point
      ::GB_GetBearingGirderPointId(prev_pier_idx,gdrIdx,qcbAfter,&startPointID);
      points->AddEx(startPointID,pntStartBrgGirder);

      //
      // intersect girder line with CL of end pier bearing
      //
      CComPtr<IPoint2d> pntEndBrgGirder;
      if ( pntEndBrg )
      {
         // a unique bearing line was located
         // locate the intersection of the CL girder and the bearing at the end pier
         // by intersecting the CL girder and CL bearing lines
         m_GeomUtil->LineLineIntersect(objEndBrgLine,objGirderLine,&pntEndBrgGirder);
      }
      else
      {
         // there is not a unique bearing line. CL bearing is located by a measurement along
         // the CL girder.
         ATLASSERT(end_brg_offset_measure == mtAlongItem);
         locate2->PointOnLine(pntEndPierGirder,pntStartPierGirder,end_brg_offset,0.00,&pntEndBrgGirder);
      }

      // store the point
      ::GB_GetBearingGirderPointId(next_pier_idx,gdrIdx,qcbBefore,&endPointID);
      points->AddEx(endPointID,pntEndBrgGirder);
   } // next girder
}

void CGenericBridge::UpdateGirderEndPoints(SpanIndexType spanIdx,GirderIndexType gdrIdx)
{
   // locate points at the ends of the girder

   // get the girder line ID
   CogoElementKey girderlineID;
   ::GB_GetGirderLineId(spanIdx,gdrIdx,&girderlineID);

   // get the connections at each end of the girder
   CComPtr<ISpan> span;
   GetSpanCollection()->get_Item(spanIdx,&span);

   CComPtr<IPier> prevPier, nextPier;
   span->get_PrevPier(&prevPier);
   span->get_NextPier(&nextPier);
   PierIndexType prevPierIdx, nextPierIdx;
   prevPier->get_Index(&prevPierIdx);
   nextPier->get_Index(&nextPierIdx);

   CComPtr<IConnection> startConnection, endConnection;
   prevPier->get_Connection(qcbAfter, &startConnection);
   nextPier->get_Connection(qcbBefore,&endConnection);

   // get the COGO point IDs for the intersection of CL Girder/CL Brg, CL Girder/CL Pier
   // and the girder end points
   CogoElementKey startBrgPointID, startPierPointID, startEndPointID;
   CogoElementKey endBrgPointID,   endPierPointID,   endEndPointID;
   ::GB_GetBearingGirderPointId(prevPierIdx,gdrIdx,qcbAfter,&startBrgPointID);
   ::GB_GetPierGirderPointId(prevPierIdx,gdrIdx,qcbAfter,&startPierPointID);
   ::GB_GetGirderEndPointId(spanIdx,gdrIdx,etStart,&startEndPointID);
   
   ::GB_GetBearingGirderPointId(nextPierIdx,gdrIdx,qcbBefore,&endBrgPointID);
   ::GB_GetPierGirderPointId(nextPierIdx,gdrIdx,qcbBefore,&endPierPointID);
   ::GB_GetGirderEndPointId(spanIdx,gdrIdx,etEnd,&endEndPointID);

   // get the distance from the CL bearing to the end of the girder
   Float64 start_end_distance, end_end_distance;
   GetEndDistance(etStart,startBrgPointID,startPierPointID,girderlineID,startConnection,prevPier,&start_end_distance);
   GetEndDistance(etEnd,  endBrgPointID,  endPierPointID,  girderlineID,endConnection,  nextPier,&end_end_distance);

   // locate the girder end points in the cogo model (points are saved into the cogo model)

   // the CL Brg and CL Pier points can be coincident. ILocate::PointOnLine requires that
   // they are unique points. To ensure that we have unique points locate the start end of the
   // girder from the CL Bearing point at the end of the girder with the line passing
   // through the CL Pier point at the start of the girder. The distance along the line,
   // from the start point, is the distance between the CL Brg points at each end of the
   // girder and the start end distance. The end of the girder is located using a similar
   // procedure, measuring from the CL Brg point at the start of the girder.

   //   + CL Pier                                     CL Pier +
   //   |    + End of girder               End of girder +    |
   //   |    |  + CL Brg                       CL Brg +  |    |
   //   |    |  |                                     |  |    |
   //        +-------------------------------------------+
   //   *    |  *                                     *  |    *
   //        +-------------------------------------------+
   //           |<---          Distance           --->|
   //        |--| Start end distance End end distance |--|
   //
   //  Locate start end of girder meeasuring from here, in the direction indicated
   //           start_end_dist + distance
   //        |<<<-------------------------------------|
   //
   //  Locate end end of girder meeasuring from here, in the direction indicated
   //                 end_end_distance + distance
   //           |------------------------------------->>>|
   CComQIPtr<ILocate> locate(m_CogoModel);
   CComPtr<IPointCollection> points;
   m_CogoModel->get_Points(&points);
   CComPtr<IPoint2d> pntStartBrg, pntEndBrg;
   points->get_Item(startBrgPointID,&pntStartBrg);
   points->get_Item(endBrgPointID,&pntEndBrg);

   Float64 distance;
   pntStartBrg->DistanceEx(pntEndBrg,&distance);

   locate->PointOnLine(startEndPointID,endBrgPointID,    startPierPointID,distance+start_end_distance,0.0);
   locate->PointOnLine(endEndPointID,  startBrgPointID,  endPierPointID,  distance+end_end_distance,  0.0);
}

void CGenericBridge::GetEndDistance(EndType end,CogoElementKey brgPntID,CogoElementKey pierPntID,CogoElementKey girderLineID,IConnection* connection,IPier* pier,Float64* endDist)
{
   Float64 end_dist;
   connection->get_EndDistance(&end_dist);

   MeasurementType measure_type;
   connection->get_EndDistanceMeasurementType(&measure_type);

   MeasurementLocation measure_loc;
   connection->get_EndDistanceMeasurementLocation(&measure_loc);

   if ( measure_type == mtAlongItem )
   {
      // Measured along girder
      if ( measure_loc == mlCenterlineBearing )
      {
         ;// do nothing - input is same as internal
      }
      else if ( measure_loc == mlPierLine )
      {
         // subtract end dist from bearing offset
         Float64 bearing_offset;
         CComQIPtr<IMeasure> measure(m_CogoModel);
         measure->Distance(brgPntID,pierPntID,&bearing_offset); // want offset measured along girder
         end_dist = bearing_offset - end_dist;
      }
      else
      {
         ATLASSERT(0);
      }
   }
   else if ( measure_type == mtNormal )
   {
      // Measured normal to pier
      // First create a line along the pier centerline
      CComPtr<IPointCollection> points;
      m_CogoModel->get_Points(&points);
      CComPtr<IPoint2d> pier_pnt;
      points->get_Item(pierPntID, &pier_pnt);

      CComPtr<IDirection> pier_dir;
      pier->get_Direction(&pier_dir);

      CComQIPtr<ILocate2> locate(m_CogoEngine);

      Float64 dist = end==etEnd ? 10.0 : -10.0; // distance is abitrary, we just want a line that's left side faces inward to span
      CComPtr<IPoint2d> pier_pnt2;
      locate->ByDistDir(pier_pnt, dist, CComVariant(pier_dir), 0.0, &pier_pnt2);

      CComPtr<ILine2d> pier_line;
      pier_line.CoCreateInstance(CLSID_Line2d);
      pier_line->ThroughPoints(pier_pnt, pier_pnt2);

      // compute distance from bearing point to CL pier along CL pier
      CComPtr<IPoint2d> brg_pnt;
      points->get_Item(brgPntID, &brg_pnt);

      Float64 bearing_to_pier_dist;
      m_GeomUtil->ShortestDistanceToPoint(pier_line, brg_pnt, &bearing_to_pier_dist);
      bearing_to_pier_dist *= -1.0; // left side is negative 

      // get girder line to intersect with
      CComPtr<ILineSegmentCollection> lineSegments;
      m_CogoModel->get_LineSegments(&lineSegments);
      CComPtr<ILineSegment2d> gdr_lineseg;
      lineSegments->get_Item(girderLineID,&gdr_lineseg);
      // make segment into a line so we know we'll intersect
      CComPtr<IPoint2d> gdr_pnt1, gdr_pnt2;
      gdr_lineseg->get_StartPoint(&gdr_pnt1);
      gdr_lineseg->get_EndPoint(&gdr_pnt2);

      CComPtr<ILine2d> gdr_line;
      gdr_line.CoCreateInstance(CLSID_Line2d);
      gdr_line->ThroughPoints(gdr_pnt1, gdr_pnt2);

      // Now we have our construction lines. Basic idea is to offset the pier line and find
      // its intersection with the girder line. That will give us the end of the girder
      Float64 offset_dist=0.0;
      Float64 sign = 1;
      if ( measure_loc == mlCenterlineBearing )
      {
         // measured from centerline bearing
         offset_dist = bearing_to_pier_dist - end_dist;
      }
      else if ( measure_loc == mlPierLine )
      {
         offset_dist = end_dist;

         if (end_dist > bearing_to_pier_dist)
         {
            // end of girder is before bearing, negative end dist
            sign = -1;
         }
      }
      else
      {
         ATLASSERT(0);
      }

      pier_line->Offset(offset_dist);

      CComPtr<IPoint2d> end_of_girder;
      m_GeomUtil->LineLineIntersect(pier_line,gdr_line,&end_of_girder);

      // finally, our end distance
      m_GeomUtil->Distance(brg_pnt, end_of_girder, &end_dist);
      end_dist *= sign;
   }
   else
   {
      ATLASSERT(0);
   }

   *endDist   = end_dist;
}

HRESULT CGenericBridge::AdviseChild(IUnknown* punk,REFIID riid,DWORD* pdwCookie)
{
   HRESULT hr;
   CComQIPtr<IConnectionPointContainer> pCPC(punk);
   CComPtr<IConnectionPoint> pCP;
   hr = pCPC->FindConnectionPoint(riid,&pCP);
   ATLASSERT(SUCCEEDED(hr));

   hr = pCP->Advise(GetUnknown(),pdwCookie);
   ATLASSERT(SUCCEEDED(hr));

   InternalRelease(); // Break circual reference
   return S_OK;
}

HRESULT CGenericBridge::UnadviseChild(IUnknown* punk,REFIID riid,DWORD dwCookie)
{
   InternalAddRef(); // Counter act call to InternalRelease in AdviseChild
   CComQIPtr<IConnectionPointContainer> pCPC(punk);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint(riid,&pCP);

   pCP->Unadvise(dwCookie);

   return S_OK;
}

/////////////////////////////////////////////////////
// IGenericBridge implementation
STDMETHODIMP CGenericBridge::UpdateBridgeModel()
{
   m_bHoldUpdate = false;
   DoUpdateBridgeModel();
   m_bHoldUpdate = true;
   return S_OK;
}

STDMETHODIMP CGenericBridge::get_CogoModel(ICogoModel* *cogoModel)
{
   CHECK_RETOBJ(cogoModel);

   (*cogoModel) = m_CogoModel;
   (*cogoModel)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::get_CogoInfo(ICogoInfo* *cogoInfo)
{
   CHECK_RETOBJ(cogoInfo);
   (*cogoInfo) = m_CogoInfo;
   (*cogoInfo)->AddRef();
   return S_OK;
}

STDMETHODIMP CGenericBridge::get_Alignment(IAlignment* *alignment)
{
   CHECK_RETOBJ(alignment);

   (*alignment) = m_Alignment;
   (*alignment)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::put_AlignmentOffset(Float64 alignmentOffset)
{
   if ( !IsEqual(alignmentOffset,m_AlignmentOffset) )
   {
      m_AlignmentOffset = alignmentOffset;
      Fire_OnBridgeChanged(this);
   }
   return S_OK;
}

STDMETHODIMP CGenericBridge::get_AlignmentOffset(Float64* alignmentOffset)
{
   CHECK_RETVAL(alignmentOffset);
   *alignmentOffset = m_AlignmentOffset;
   return S_OK;
}

STDMETHODIMP CGenericBridge::putref_Alignment(IAlignment *alignment)
{
   CHECK_IN(alignment);

   UnadviseChild(m_Alignment,IID_IPathEvents,m_dwAlignmentCookie);
   m_Alignment = alignment;
   AdviseChild(m_Alignment,IID_IPathEvents,&m_dwAlignmentCookie);

   CComPtr<IPathCollection> alignments;
   m_CogoModel->get_Alignments(&alignments);

   alignments->Remove(g_AlignmentKey);
   alignments->AddEx(g_AlignmentKey,alignment);

   DoUpdateBridgeModel();
   Fire_OnBridgeChanged(this);

   return S_OK;
}

STDMETHODIMP CGenericBridge::get_Deck(IBridgeDeck** deck)
{
   CHECK_RETOBJ(deck);
   (*deck) = m_Deck;

   if ( *deck ) 
      (*deck)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::putref_Deck(IBridgeDeck* deck)
{
   if ( (m_Deck == NULL && deck == NULL) || m_Deck.IsEqualObject(deck) )
      return S_OK;

   CComPtr<IUnknown> punk;
   QueryInterface(IID_IUnknown,(void**)&punk);

   // Make sure we can sink events on the new deck;
   HRESULT hr;
   DWORD dwCookie;
   if ( deck )
   {
      hr = AtlAdvise(deck,punk,IID_IBridgeDeckEvents,&dwCookie);
      if ( FAILED(hr) )
         return hr; // can't sink on new strategy... get outta here before anything gets changed

      InternalRelease();
   }

   // unsink on the old deck (if there was one)
   if ( m_Deck )
   {
      InternalAddRef();

      hr = AtlUnadvise(m_Deck,IID_IBridgeDeckEvents,m_dwDeckCookie);
      ATLASSERT( SUCCEEDED(hr) );
   }

   m_Deck = deck;
   m_Deck->putref_Bridge(this);

   if ( m_Deck )
   {
      m_dwDeckCookie = dwCookie;
   }
   
   Fire_OnBridgeChanged(this);
   return S_OK;
}

STDMETHODIMP CGenericBridge::get_Piers(IPierCollection* *piers)
{
   CHECK_RETOBJ(piers);

   (*piers) = m_Piers;
   (*piers)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::get_Spans(ISpanCollection* *spans)
{
   CHECK_RETOBJ(spans);

   (*spans) = m_Spans;
   (*spans)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::SpanFromStation(Float64 station,ISpan** ppSpan)
{
   CHECK_RETOBJ(ppSpan);

   SpanIndexType nSpans;
   m_Spans->get_Count(&nSpans);
   (*ppSpan) = NULL;
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      CComPtr<ISpan> span;
      m_Spans->get_Item(spanIdx,&span);

      CComPtr<IPier> prevPier, nextPier;
      span->get_PrevPier(&prevPier);
      span->get_NextPier(&nextPier);

      CComPtr<IStation> objStation;
      Float64 prevStation, nextStation;

      prevPier->get_Station(&objStation);
      objStation->get_Value(&prevStation);

      objStation.Release();
      nextPier->get_Station(&objStation);
      objStation->get_Value(&nextStation);

      if ( ( spanIdx == 0 && IsEqual(station,prevStation) ) ||
           (prevStation <= station && station < nextStation) ||
           ( spanIdx == nSpans-1 && IsEqual(station,nextStation) )
         )
      {
         (*ppSpan) = span;
         (*ppSpan)->AddRef();
         return S_OK;
      }
   }

   return S_OK;
}

STDMETHODIMP CGenericBridge::SpanFromOffset(Float64 offsetFromStartOfBridge,ISpan** ppSpan)
{
   CComPtr<IPier> pier;
   m_Piers->get_Item(0,&pier);

   CComPtr<IStation> objStation;
   pier->get_Station(&objStation);

   Float64 station;
   objStation->get_Value(&station);

   station += offsetFromStartOfBridge;
   return SpanFromStation(station,ppSpan);
}

STDMETHODIMP CGenericBridge::get_Stages(IStageCollection* *stages)
{
   CHECK_RETOBJ(stages);

   (*stages) = m_Stages;
   (*stages)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::Move(Float64 offset)
{
   if ( IsZero(offset) )
      return S_OK;

   PierIndexType nPiers;
   m_Piers->get_Count(&nPiers);

   for ( PierIndexType i = 0; i < nPiers; i++ )
   {
      CComPtr<IPier> pier;
      m_Piers->get_Item(i,&pier);

      // get the current station value
      CComPtr<IStation> station;
      pier->get_Station(&station);

      Float64 value;
      station->get_Value(&value);

      // compute the new station value
      value += offset;

      // set the pier station WITHOUT CREATING ADDITIONAL TRANSACTION OR EVENTS
      CPier* pPier = dynamic_cast<CPier*>(pier.p);
      pPier->SetStationValue(value);
   }

   Fire_OnBridgeChanged(this);
   return S_OK;
}

STDMETHODIMP CGenericBridge::MoveToStation(PierIndexType pierIdx, Float64 newStation)
{
   CComPtr<IPier> pier;
   HRESULT hr = m_Piers->get_Item(pierIdx,&pier);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IStation> station;
   pier->get_Station(&station);

   Float64 value;
   station->get_Value(&value);

   Float64 offset = newStation - value;
   return Move(offset);
}

HRESULT CGenericBridge::InsertSpanAndPier(SpanIndexType spanIdx, Float64 spanLength,PositionType pos,DirectionType side)
{
   // Verify that the index is valid
   SpanIndexType spanCount;
   m_Spans->get_Count(&spanCount);

   if ( spanCount == 0 )
   {
      // this is the first span, so we have to add a pier at the start of the bridge
      CComObject<CPier>* pPier1;
      CComObject<CPier>::CreateInstance(&pPier1);
      GetPierCollection()->Add(pPier1);
      pPier1->SetStationValue(0.0);
   }


   if ( spanIdx == ALL_SPANS )
   {
      spanIdx = (spanCount == 0 ? 0 : spanCount-1);
   }

   if ( spanCount != 0 && spanCount <= spanIdx )
      return E_INVALIDARG;

   // Verify span length (note, if span length is less than zero, the length of the previous span is used)
   if ( IsZero(spanLength) )
      return E_INVALIDARG;

   // Get the positions of the new span and pier
   SpanIndexType newSpanIdx = (spanCount == 0 ? 0 : 
                               spanIdx    + (pos  == qcbBefore ? 0 : 1));
   PierIndexType newPierIdx = newSpanIdx + (side == qcbLeft   ? 0 : 1);

   // Get the index of the first pier that is going to be moved and the original station of that pier
   // (for a later undo)
   PierIndexType movedPierIdx = spanIdx + (pos == qcbBefore ? 0 : 1) + (side == qcbLeft ? 0 : 1);

   PierIndexType nPiers;
   m_Piers->get_Count(&nPiers);
   Float64 originalStation;

   if ( nPiers <= movedPierIdx )
   {
      movedPierIdx = ALL_PIERS; // no pier to be moved
      originalStation = -999.999; // an obviously bogus value that should never be used
   }
   else
   {
      CComPtr<IPier> originalPier;
      m_Piers->get_Item(movedPierIdx,&originalPier);
      CComPtr<IStation> station;
      originalPier->get_Station(&station);
      station->get_Value(&originalStation);
   }

   // Create/get a new span object
   CComObject<CSpan>* pSpan;
   CComObject<CSpan>::CreateInstance(&pSpan);
   CComPtr<ISpan> newSpan = pSpan;

   // Create/get new pier object
   CComObject<CPier>* pPier;
   CComObject<CPier>::CreateInstance(&pPier);
   CComPtr<IPier> newPier = pPier;

   if ( side == qcbLeft )
   {
      // if the new pier goes to the left of the new span, we have to
      // set its station to that of the pier that is being moved
      CComPtr<IStation> newPierStation;
      newPier->get_Station(&newPierStation);
      newPierStation->put_Value(originalStation);
   }
   else if ( 1 < movedPierIdx && movedPierIdx != ALL_PIERS )
   {
      // otherwise, set it to the station for the start of the new span
      CComPtr<IPier> refPier;
      m_Piers->get_Item(movedPierIdx-1,&refPier);
      CComPtr<IStation> station;
      refPier->get_Station(&station);
      Float64 value;
      station->get_Value(&value);

      CComPtr<IStation> newPierStation;
      newPier->get_Station(&newPierStation);
      newPierStation->put_Value(value);
   }

   // Add the span and pier the collections
   CSpanCollection* pSpans = GetSpanCollection();
   pSpans->Insert(newSpanIdx,newSpan);

   CPierCollection* pPiers = GetPierCollection();
   pPiers->InsertQuietly(newPierIdx,newPier); // don't fire an event

   // Hook the piers and spans together
   LinkSpansAndPiers();

   // Now that everything is wired up and the new span and pier are in the containers... Set the span length
   // (Setting the span length actually moves the piers)
   // (Note if span length < 0, use the length of the previous span. If this is the first span, use the next span)
   if ( spanLength < 0 )
   {
      SpanIndexType refSpanIdx = (spanIdx == 0 ? 0 : spanIdx-1);
      CComPtr<ISpan> refSpan;
      m_Spans->get_Item(refSpanIdx,&refSpan);
      refSpan->get_Length(&spanLength);
   }
   dynamic_cast<CSpan*>(newSpan.p)->SetLength(spanLength); // use backdoor so extra events and txn don't happen

   DoUpdateBridgeModel();

   Fire_OnBridgeChanged(this);

   return S_OK;
}

HRESULT CGenericBridge::RemoveSpanAndPier(SpanIndexType spanIdx, DirectionType side)
{
   // Verify that the index is valid
   SpanIndexType spanCount;
   m_Spans->get_Count(&spanCount);
   if ( spanIdx < 0 || spanCount <= spanIdx )
      return E_INVALIDARG;

   // get the length of the next span (need to maintain this length)
   Float64 nextSpanLength = 0.0;
   if ( spanIdx+1 < spanCount )
   {
      CComPtr<ISpan> span;
      m_Spans->get_Item(spanIdx+1,&span);
      span->get_Length(&nextSpanLength);
   }

   PierIndexType pierIdx = spanIdx + (side == qcbLeft ? 0 : 1);
   CComPtr<IPier> removedPier;
   m_Piers->get_Item(pierIdx,&removedPier);
   CComPtr<IStation> station;
   removedPier->get_Station(&station);
   Float64 removedPierStation;
   station->get_Value(&removedPierStation);

   // Remove the span and pier
   GetSpanCollection()->Remove(spanIdx);
   GetPierCollection()->Remove(pierIdx);

   // Make sure the spans and piers are linked up properly
   LinkSpansAndPiers();

   // Ensure the span lengths and pier locations are correct
   if ( spanIdx+1 < spanCount && side == qcbRight )
   {
      CComPtr<ISpan> span;

      // Now use txnData.spanIdx because a span has been removed
      m_Spans->get_Item(spanIdx,&span);
      dynamic_cast<CSpan*>(span.p)->SetLength(nextSpanLength);
   }
   else
   {
      PierIndexType nPiers;
      m_Piers->get_Count(&nPiers);
      if ( 0 < pierIdx && pierIdx < nPiers )
      {
         CComPtr<IPier> pier;
         m_Piers->get_Item(pierIdx,&pier);
         dynamic_cast<CPier*>(pier.p)->SetStationValueEx(removedPierStation);
      }
   }

   DoUpdateBridgeModel();

   Fire_OnBridgeChanged(this);

   return S_OK;
}

STDMETHODIMP CGenericBridge::get_Length(Float64* length)
{
   CHECK_RETVAL(length);
   PierIndexType nPiers;
   m_Piers->get_Count(&nPiers);
   CComPtr<IPier> objFirstPier, objLastPier;

   m_Piers->get_Item(0,&objFirstPier);
   m_Piers->get_Item(nPiers-1,&objLastPier);

   CComPtr<IStation> objFirstPierStation, objLastPierStation;
   objFirstPier->get_Station(&objFirstPierStation);
   objLastPier->get_Station(&objLastPierStation);

   Float64 first_pier_station, last_pier_station;
   objFirstPierStation->get_Value(&first_pier_station);
   objLastPierStation->get_Value(&last_pier_station);

   (*length) = last_pier_station - first_pier_station;

   ATLASSERT( 0 <= *length );

   return S_OK;
}

STDMETHODIMP CGenericBridge::ResizeSpans(VARIANT varArray)
{
   if ( varArray.vt != (VT_BYREF | VT_VARIANT) &&  // VB Script
        varArray.vt != (VT_ARRAY | VT_R8) )        // VB/C++
   {
      return E_INVALIDARG;
   }

   
   // Extract the SAFEARRAY
   SAFEARRAY* pSpanLengths;
   if ( varArray.vt & VT_BYREF )
   {
      if ( !(varArray.pvarVal->vt & (VT_BYREF | VT_ARRAY)) )
         return E_INVALIDARG;

      pSpanLengths = *(varArray.pvarVal->pparray); // VBScript
   }
   else
   {
      pSpanLengths = varArray.parray; // VB or C++
   }

   // Check out the safe array. Make sure it is the right size
   // and contains the right stuff
   HRESULT hr;
   VARTYPE vt;
   hr = SafeArrayGetVartype(pSpanLengths,&vt);
   if ( FAILED(hr) )
      return hr;

   if ( varArray.vt & VT_BYREF && vt != VT_VARIANT )
      return E_INVALIDARG;

   if ( varArray.vt & VT_ARRAY && vt != VT_R8 )
      return E_INVALIDARG;

   // Make sure this is a 1 dimensional array
   if ( SafeArrayGetDim(pSpanLengths) != 1 )
      return E_INVALIDARG;

   // Get the array bounds, loop over the array, and collect the span lengths
   long lb,ub;
   SafeArrayGetLBound(pSpanLengths,1,&lb);
   SafeArrayGetUBound(pSpanLengths,1,&ub);

   std::vector<Float64> spanLengths;

   for ( long i = lb; i <= ub; i++ )
   {
      Float64 length;
      VARIANT varKey;
      if ( pSpanLengths->fFeatures & FADF_VARIANT )
      {
         // VBScript
         hr = SafeArrayGetElement(pSpanLengths,&i,&varKey);
         ATLASSERT(SUCCEEDED(hr));
         ATLASSERT(varKey.vt == VT_R8);
         length = varKey.dblVal;
      }
      else
      {
         // VB
         hr = SafeArrayGetElement(pSpanLengths,&i,&length);
         ATLASSERT(SUCCEEDED(hr));
      }

      spanLengths.push_back(length);
   }

   CComPtr<ISpanCollection> spans;
   get_Spans(&spans);

   CComPtr<IPierCollection> piers;
   get_Piers(&piers);

   SpanIndexType nSpans;
   spans->get_Count(&nSpans);
   ATLASSERT(nSpans == spanLengths.size());

   // Set the span lengths by moving the piers
   // Get the station of the first pier
   CComPtr<IPier> firstPier;
   piers->get_Item(0,&firstPier);

   CComPtr<IStation> objStation;
   firstPier->get_Station(&objStation);
   Float64 lastStation;
   objStation->get_Value(&lastStation);

   // Walk the remaining piers and adjust their stations
   PierIndexType nPiers;
   piers->get_Count(&nPiers);

   for ( PierIndexType i = 1; i < nPiers; i++ )
   {
      CComPtr<IPier> pier;
      piers->get_Item(i,&pier);
      Float64 currStation = lastStation + spanLengths[i-1];

      // set the pier station WITHOUT CREATING ADDITIONAL TRANSACTION OR EVENTS
      CPier* pPier = dynamic_cast<CPier*>(pier.p);
      pPier->SetStationValue(currStation);

      lastStation = currStation;
   }

   Fire_OnBridgeChanged(this);
   return S_OK;
}

STDMETHODIMP CGenericBridge::Clone(IGenericBridge* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CGenericBridge>* pClone;
   CComObject<CGenericBridge>::CreateInstance(&pClone);
   (*clone) = pClone;
   (*clone)->AddRef();

   // Clone Cogo Model/Alignment
   CComPtr<ICogoModel> cloneCOGO;
   m_CogoModel->Clone(&cloneCOGO);
   pClone->m_CogoModel = cloneCOGO;

   CComPtr<IPathCollection> alignments;
   cloneCOGO->get_Alignments(&alignments);

   CComPtr<IPath> path;
   alignments->get_Item(g_AlignmentKey,&path);
   CComQIPtr<IAlignment> alignment(path);
   ATLASSERT(alignment != NULL);
   pClone->putref_Alignment(alignment);

   // Create new collections
   CStageCollection* pStages = dynamic_cast<CStageCollection*>(m_Stages.p);
   CComPtr<IStageCollection> stages;
   pStages->Clone(&stages);

   // Clone Spans
   CSpanCollection* pSpans = dynamic_cast<CSpanCollection*>(m_Spans.p);
   CComPtr<ISpanCollection> spans;
   pSpans->Clone(&spans);

   // Clone Piers
   CPierCollection* pPiers = dynamic_cast<CPierCollection*>(m_Piers.p);
   CComPtr<IPierCollection> piers;
   pPiers->Clone(&piers);

   // Clone wearing surface information
   pClone->put_WearingSurfaceDepth(m_WearingSurfaceDepth);
   pClone->put_WearingSurfaceDensity(m_WearingSurfaceDensity);
   pClone->put_SacrificialDepth(m_SacrificialDepth);

   // Wire up all the collections
   pClone->SetCollections(stages,spans,piers);

   CComPtr<IBridgeDeck> deck_clone;
   if ( m_Deck )
   {
      m_Deck->Clone(&deck_clone);
      pClone->putref_Deck(deck_clone);
   }

   pClone->put_AlignmentOffset(m_AlignmentOffset);

   return S_OK;
}


//STDMETHODIMP CGenericBridge::GetSuperstructureMemberSegment(long spanIdx,long gdrLineIdx,Float64 location, ISegment** segment)
//{
//   CHECK_RETOBJ(segment);
//
//   long nSpans;
//   m_Spans->get_Count(&nSpans);
//
//   if ( spanIdx < 0 || nSpans <= spanIdx )
//      return E_INVALIDARG;
//
//   long nGdrLines;
//   get_GirderLineCount(&nGdrLines);
//   if ( gdrLineIdx < 0 || nGdrLines <= gdrLineIdx )
//      return E_INVALIDARG;
//
//   CComPtr<ISpan> span;
//   m_Spans->get_Item(spanIdx,&span);
//   Float64 l;
//   span->get_GirderLineLength(gdrLineIdx,&l);
//   if ( (spanIdx == 0 && l <= location) || 
//        (spanIdx == nSpans-1 && location < 0) || 
//        ((0<spanIdx && spanIdx <nSpans-1) && !InRange(0.0,location,l)) )
//   {
//      return E_INVALIDARG; // location is not on span
//   }
//
//   Float64 cumm_location = 0;
//   for ( long s = 0; s < spanIdx; s++ )
//   {
//      CComPtr<ISpan> span;
//      m_Spans->get_Item(s,&span);
//      Float64 l;
//      span->get_GirderLineLength(gdrLineIdx,&l);
//      cumm_location += l;
//   }
//
//   CComPtr<ISuperstructureMemberCollection> ssmbrs;
//   get_SuperstructureMembers(gdrLineIdx,&ssmbrs);
//
//   Float64 offset;
//   ssmbrs->get_Offset(etStart,&offset);
//
//   cumm_location += offset;
//   cumm_location += location;
//
//   Float64 dist;
//   return ssmbrs->GetSegmentForLocation(cumm_location,&dist,segment);
//}
//
//STDMETHODIMP CGenericBridge::SpanGirderToSegment(long spanIdx,long gdrLineIdx,Float64 location,long* ssmbrIdx,long* segmentIdx,Float64* dist)
//{
//   CHECK_RETVAL(ssmbrIdx);
//   CHECK_RETVAL(segmentIdx);
//   CHECK_RETVAL(dist);
//
//   // location can only be negative if this is the first span
//   if ( spanIdx != 0 && location < 0 )
//      return E_INVALIDARG;
//
//   Float64 dist_from_start; // distance from start of superstructure member for this girder line
//   HRESULT hr = SpanGirderLocationToAbsolute(spanIdx,gdrLineIdx,location,&dist_from_start);
//   if ( FAILED(hr) )
//      return hr;
//
//   if ( dist_from_start < 0 )
//      return E_INVALIDARG; // location is before the superstructure members
//
//   Float64 max_dist;
//   get_GirderLineLength(gdrLineIdx,&max_dist);
//   if ( max_dist < dist_from_start )
//      return E_INVALIDARG; // location is beyond end of girder line
//
//   CComPtr<ISuperstructureMemberCollection> ssmbrs;
//   get_SuperstructureMembers(gdrLineIdx,&ssmbrs);
//
//   return ssmbrs->GetSegmentPoint(dist_from_start,ssmbrIdx,segmentIdx,dist);
//}

STDMETHODIMP CGenericBridge::get_LeftBarrier(ISidewalkBarrier** barrier)
{
   CHECK_RETOBJ(barrier);
   (*barrier) = m_LeftBarrier;

   if ( *barrier ) 
      (*barrier)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::putref_LeftBarrier(ISidewalkBarrier* barrier)
{
   CHECK_IN(barrier);
   if ( (m_LeftBarrier == NULL && barrier == NULL) || m_LeftBarrier.IsEqualObject(barrier) )
      return S_OK;

   m_LeftBarrier = barrier;
   Fire_OnBridgeChanged(this);
   return S_OK;
}

STDMETHODIMP CGenericBridge::get_RightBarrier(ISidewalkBarrier** barrier)
{
   CHECK_RETOBJ(barrier);
   (*barrier) = m_RightBarrier;

   if ( *barrier ) 
      (*barrier)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::putref_RightBarrier(ISidewalkBarrier* barrier)
{
   CHECK_IN(barrier);
   if ( (m_RightBarrier == NULL && barrier == NULL) || m_RightBarrier.IsEqualObject(barrier) )
      return S_OK;

   m_RightBarrier = barrier;
   Fire_OnBridgeChanged(this);
   return S_OK;
}


STDMETHODIMP CGenericBridge::get_WearingSurfaceDepth(/*[out,retval]*/Float64* d)
{
   CHECK_RETVAL(d);
   *d = m_WearingSurfaceDepth;
   return S_OK;
}

STDMETHODIMP CGenericBridge::put_WearingSurfaceDepth(/*[in]*/Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_WearingSurfaceDepth,depth) )
      return S_OK;

   m_WearingSurfaceDepth = depth;
   Fire_OnBridgeChanged(this);

   return S_OK;
}

STDMETHODIMP CGenericBridge::get_WearingSurfaceDensity(/*[out,retval]*/Float64* d)
{
   CHECK_RETVAL(d);
   *d = m_WearingSurfaceDensity;
   return S_OK;
}

STDMETHODIMP CGenericBridge::put_WearingSurfaceDensity(/*[in]*/Float64 density)
{
   if ( density < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_WearingSurfaceDensity,density) )
      return S_OK;

   m_WearingSurfaceDensity = density;
   Fire_OnBridgeChanged(this);

   return S_OK;
}

STDMETHODIMP CGenericBridge::get_SacrificialDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_SacrificialDepth;
   return S_OK;
}

STDMETHODIMP CGenericBridge::put_SacrificialDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_SacrificialDepth,depth) )
      return S_OK;

   m_SacrificialDepth = depth;
   Fire_OnBridgeChanged(this);
   return S_OK;
}

//STDMETHODIMP CGenericBridge::SegmentToSpanGirder(long gdrLineIdx,long ssmbrIdx,long segmentIdx,Float64 dist,long* spanIdx,Float64* location)
//{
//   CHECK_RETVAL(spanIdx);
//   CHECK_RETVAL(location);
//
//   Float64 dist_from_start; // distance from start of superstructure member for this girder line
//   HRESULT hr = SegmentLocationToAbsolute(gdrLineIdx,ssmbrIdx,segmentIdx,dist,&dist_from_start);
//   if ( FAILED(hr) )
//      return hr;
//
//   // Deduct offset at start of girder line
//   CComPtr<ISuperstructureMemberCollection> ssmbrs;
//   get_SuperstructureMembers(gdrLineIdx,&ssmbrs);
//
//   Float64 offset;
//   ssmbrs->get_Offset(etStart,&offset);
//
//   dist_from_start -= offset;
//
//   if ( dist_from_start < 0 )
//   {
//      *spanIdx = 0;
//      *location = dist_from_start;
//      return S_OK;
//   }
//
//   // determine which span
//   long nSpans;
//   m_Spans->get_Count(&nSpans);
//   Float64 sum_span_length = 0;
//   for ( long s = 0; s < nSpans; s++ )
//   {
//      CComPtr<ISpan> span;
//      m_Spans->get_Item(s,&span);
//      Float64 l;
//      span->get_GirderLineLength(gdrLineIdx,&l);
//
//      Float64 end_of_span = sum_span_length + l;
//      if ( InRange(sum_span_length,dist_from_start,end_of_span) )
//      {
//         *spanIdx = s;
//         *location = dist_from_start - sum_span_length;
//         return S_OK;
//      }
//
//      sum_span_length = end_of_span;
//   }
//
//   // if we get this far, the point is beyond the last pier
//   // if it is within the cantilever, we are good, otherwise not
//   ssmbrs->get_Offset(etEnd,&offset);
//   if ( offset < dist_from_start-sum_span_length )
//   {
//      // error
//   ATLASSERT(false);
//   }
//   else
//   {
//      CComPtr<ISpan> span;
//      m_Spans->get_Item(nSpans-1,&span);
//      Float64 length;
//      span->get_GirderLineLength(gdrLineIdx,&length);
//
//      *spanIdx = nSpans-1;
//      *location = dist_from_start - length;
//      return S_OK;
//   }
//
//
//   // Should never get here
//   ATLASSERT(false);
//   return E_FAIL;
//}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CGenericBridge::Load(IStructuredLoad2* load)
{
//   // Turn off connection points
//   UnadviseSuperstructureMembers();
//   UnadviseChild(m_Stages,IID_IStageCollectionEvents,m_dwStagesCookie);
//   UnadviseChild(m_Piers,IID_IPierCollectionEvents,m_dwPiersCookie);
//   UnadviseChild(m_Spans,IID_ISpanCollectionEvents,m_dwSpansCookie);
//
//   // Empty containers...
//   dynamic_cast<CPierCollection*>(m_Piers.p)->Clear();
//   dynamic_cast<CSpanCollection*>(m_Spans.p)->Clear();
//   dynamic_cast<CStageCollection*>(m_Stages.p)->Clear();
//
//   // Load the model
//   CComVariant var;
//   
//   CHECK_IN(load);
//   load->BeginUnit(CComBSTR("GenericBridge"));
//
//   load->get_Property(CComBSTR("GirderLineType"),&var);
//   m_GirderLineType = (GirderLineType)(var.lVal);
//
//   CComPtr<IStructuredStorage2> ss;
//
//   ss.Release();
//   m_Stages->QueryInterface(&ss);
//   ss->Load(load);
//
//   ss.Release();
//   m_Piers->QueryInterface(&ss);
//   ss->Load(load);
//
//   ss.Release();
//   m_Spans->QueryInterface(&ss);
//   ss->Load(load);
//
//   LinkSpansAndPiers();
//
//   ss.Release();
//   m_GirderSpacing->QueryInterface(&ss);
//   ss->Load(load);
//
//   VARIANT_BOOL bEnd;
//   load->EndUnit(&bEnd);
//
//   DoUpdateBridgeModel(); // Generate the COGO model
//
//   // Turn on connection points
//   AdviseSuperstructureMembers();
//   AdviseChild(m_Stages,IID_IStageCollectionEvents,&m_dwStagesCookie);
//   AdviseChild(m_Piers,IID_IPierCollectionEvents,&m_dwPiersCookie);
//   AdviseChild(m_Spans,IID_ISpanCollectionEvents,&m_dwSpansCookie);
//
   return S_OK;
}

STDMETHODIMP CGenericBridge::Save(IStructuredSave2* save)
{
   CHECK_IN(save);
//
//   save->BeginUnit(CComBSTR("GenericBridge"),1.0);
//
//   save->put_Property(CComBSTR("GirderLineType"),CComVariant(m_GirderLineType));
//
//   CComPtr<IStructuredStorage2> ss;
//
//   ss.Release();
//   m_Stages->QueryInterface(&ss);
//   ss->Save(save);
//
//   ss.Release();
//   m_Piers->QueryInterface(&ss);
//   ss->Save(save);
//
//   ss.Release();
//   m_Spans->QueryInterface(&ss);
//   ss->Save(save);
//
//   ss.Release();
//   m_GirderSpacing->QueryInterface(&ss);
//   ss->Save(save);
//
//   save->EndUnit();
//
   return S_OK;
}

/////////////////////////////////////////////////////
// IStageCollectionEvents implementation
STDMETHODIMP CGenericBridge::OnStageRenamed(BSTR bstrOldName,IStage* stage)
{
   CComBSTR bstrNewName;
   stage->get_Name(&bstrNewName);

//   std::vector<std::pair<DWORD,CComPtr<ISuperstructureMemberCollection> > >::iterator iter;
//   for ( iter = m_SuperstructureMembers.begin(); iter != m_SuperstructureMembers.end(); iter++ )
//   {
//      CComPtr<ISuperstructureMemberCollection> mbrs = (*iter).second;
//
//      CSuperstructureMemberCollection* pMbrs = dynamic_cast<CSuperstructureMemberCollection*>(mbrs.p);
//
//      pMbrs->RenameStageReferences(bstrOldName,bstrNewName);
//   }
   // rename into spans????

   CPierCollection* pPiers = GetPierCollection();
   pPiers->RenameStageReferences(bstrOldName,bstrNewName);

   Fire_OnBridgeChanged(this);

   return S_OK;
}

STDMETHODIMP CGenericBridge::OnStageAdded(CollectionIndexType idx)
{
   CComPtr<IStage> stage;
   m_Stages->get_Item(idx,&stage);

   CComBSTR bstrName;
   stage->get_Name(&bstrName);

//   std::vector<std::pair<DWORD,CComPtr<ISuperstructureMemberCollection> > >::iterator iter;
//   for ( iter = m_SuperstructureMembers.begin(); iter != m_SuperstructureMembers.end(); iter++ )
//   {
//      CComPtr<ISuperstructureMemberCollection> mbrs = (*iter).second;
//
//      CSuperstructureMemberCollection* pMbrs = dynamic_cast<CSuperstructureMemberCollection*>(mbrs.p);
//
//      pMbrs->AddDataForStage(bstrName);
//   }
   // add to span???

   CPierCollection* pPiers = GetPierCollection();
   pPiers->AddDataForStage(bstrName);

   Fire_OnBridgeChanged(this);

   return S_OK;
}

STDMETHODIMP CGenericBridge::OnStageRemoved(CollectionIndexType idx,BSTR name)
{
//   std::vector<std::pair<DWORD,CComPtr<ISuperstructureMemberCollection> > >::iterator iter;
//   for ( iter = m_SuperstructureMembers.begin(); iter != m_SuperstructureMembers.end(); iter++ )
//   {
//      CComPtr<ISuperstructureMemberCollection> mbrs = (*iter).second;
//
//      CSuperstructureMemberCollection* pMbrs = dynamic_cast<CSuperstructureMemberCollection*>(mbrs.p);
//
//      pMbrs->RemoveDataForStage(name);
//   }
   // remove for Span???

   CPierCollection* pPiers = GetPierCollection();
   pPiers->RemoveDataForStage(name);

   Fire_OnBridgeChanged(this);

   return S_OK;
}

STDMETHODIMP CGenericBridge::OnStageMoved(BSTR name,CollectionIndexType from,CollectionIndexType to)
{
#pragma Reminder("Review")
   // What are the ramifications of a stage being moved in the temporal order?

   Fire_OnBridgeChanged(this);

   return S_OK;
}

//#if defined _DEBUG
//void CGenericBridge::Dump(CDumpContext& dc)
//{
//   dc << "Dump Bridge Data\n";
//   dc << "================\n";
//
//   dc << "Dump by span\n";
//   long nSpans;
//   m_Spans->get_Count(&nSpans);
//   for ( long i = 0; i < nSpans; i++ )
//   {
//      CComPtr<ISpan> span;
//      m_Spans->get_Item(i,&span);
//
//      CSpan* pSpan = dynamic_cast<CSpan*>(span.p);
//
//
//      CPier* pPrevPier = pSpan->GetPrevPier();
//      CPier* pNextPier = pSpan->GetNextPier();
//
//      CSpan* pPrevSpan = pNextPier->GetPrevSpan();
//      CSpan* pNextSpan = pPrevPier->GetNextSpan();
//
//      dc << "Prev Pier " << (void*)pPrevPier << " (Next Span " << (void*)pNextSpan << ")\n";
//      dc << "Span " << (i+1) << "                        " << (void*)pSpan << "\n";
//      dc << "Next Pier " << (void*)pNextPier << " (Prev Span " << (void*)pPrevSpan << ")\n";
//   }
//
//   dc << "Dump by pier\n";
//   long nPiers;
//   m_Piers->get_Count(&nPiers);
//   for ( i = 0; i < nPiers; i++ )
//   {
//      CComPtr<IPier> pier;
//      m_Piers->get_Item(i,&pier);
//      CPier* pPier = dynamic_cast<CPier*>(pier.p);
//
//      CSpan* pPrevSpan = pPier->GetPrevSpan();
//      CSpan* pNextSpan = pPier->GetNextSpan();
//
//      CPier* pPrevPier = (pNextSpan ? pNextSpan->GetPrevPier() : NULL);
//      CPier* pNextPier = (pPrevSpan ? pPrevSpan->GetNextPier() : NULL);
//
//      dc << "Prev Span " << (void*)pPrevSpan << " (Next Pier " << (void*)pNextPier << ")\n";
//      dc << "Pier " << (i+1) << "                        " << (void*)pPier << "\n";
//      dc << "Next Span " << (void*)pNextSpan << " (Prev Pier " << (void*)pPrevPier << ")\n";
//   }
//
//   dc << "\n";
//   dc << "Dump of Girder Spacing Data\n";
//   dc << "===========================\n";
//   GetGirderSpacing()->Dump(dc);
//}
//#endif // _DEBUG

//HRESULT CGenericBridge::SpanGirderLocationToAbsolute(long spanIdx,long gdrLineIdx,Float64 location,Float64* dist)
//{
//   long nSpans;
//   m_Spans->get_Count(&nSpans);
//
//   if ( spanIdx < 0 || nSpans <= spanIdx )
//      return E_INVALIDARG;
//
//   long nGdrLines;
//   get_GirderLineCount(&nGdrLines);
//   if ( gdrLineIdx < 0 || nGdrLines <= gdrLineIdx )
//      return E_INVALIDARG;
//
//   // convert location from start of span to location from start of superstructure member collection
//   Float64 loc = 0;
//   for ( long s = 0; s < spanIdx; s++ )
//   {
//      CComPtr<ISpan> span;
//      m_Spans->get_Item(s,&span);
//      Float64 l;
//      span->get_GirderLineLength(gdrLineIdx,&l);
//      loc += l;
//   }
//
//   CComPtr<ISuperstructureMemberCollection> ssmbrs;
//   get_SuperstructureMembers(gdrLineIdx,&ssmbrs);
//
//   Float64 offset;
//   ssmbrs->get_Offset(etStart,&offset);
//
////   if ( location < 0 )
////   {
////      // location along span is fractional, make sbsolute
////      CComPtr<ISpan> span;
////      m_Spans->get_Item(spanIdx,&span);
////      Float64 span_length;
////      span->get_Length(&span_length);
////      location *= -span_length;
////   }
//
//   loc += offset;
//   loc += location;
//
//   *dist = loc;
//   return S_OK;
//}
//
//HRESULT CGenericBridge::SegmentLocationToAbsolute(long gdrLineIdx,long ssmbrIdx,long segIdx,Float64 loc,Float64* dist)
//{
//   CComPtr<ISuperstructureMemberCollection> ssmbrs;
//   HRESULT hr = get_SuperstructureMembers(gdrLineIdx,&ssmbrs);
//   if ( FAILED(hr) )
//      return hr;
//
//   long nSSMbrs;
//   ssmbrs->get_Count(&nSSMbrs);
//   if ( ssmbrIdx < 0 || nSSMbrs <= ssmbrIdx )
//      return E_INVALIDARG;
//
//   // deal with the location - error check and make absolute if fractional
//   CComPtr<ISuperstructureMember> ssmbr;
//   ssmbrs->get_Item(ssmbrIdx,&ssmbr);
//
//   // is segment index out of bounds?
//   long nSegments;
//   ssmbr->get_SegmentCount(&nSegments);
//   if ( segIdx < 0 || nSegments <= segIdx )
//      return E_INVALIDARG;
//
//   if ( loc < 0 && !InRange(-1.0,loc,0.0) )
//      return E_INVALIDARG; // fractional distance and out of range
//
//   CComPtr<ISegment> segment;
//   ssmbr->get_Segment(segIdx,&segment);
//   Float64 seg_length;
//   segment->get_Length(&seg_length);
//
//   VARIANT_BOOL bFractional;
//   ssmbr->get_Fractional(&bFractional);
//
//   Float64 ssmbr_length;
//   ssmbr->get_Length(&ssmbr_length);
//
//   if ( bFractional == VARIANT_TRUE )
//      seg_length *= -ssmbr_length;
//
//   if ( 0 <= loc && seg_length < loc )
//      return E_INVALIDARG; // absolute distance, but past end of segment
//
//   // make location absolute measure
//   if ( loc < 0 )
//   {
//      loc *= -seg_length;
//   }
//   
//   Float64 dist_from_start = 0;
//   for ( long i = 0; i <= ssmbrIdx; i++ )
//   {
//      CComPtr<ISuperstructureMember> ssmbr;
//      ssmbrs->get_Item(i,&ssmbr);
//
//      VARIANT_BOOL bFractional;
//      ssmbr->get_Fractional(&bFractional);
//
//      Float64 ssmbr_length;
//      ssmbr->get_Length(&ssmbr_length);
//
//      CComPtr<IFilteredSegmentCollection> segments;
//      ssmbr->GetMemberSegments(&segments);
//
//      long nSegments;
//      segments->get_Count(&nSegments);
//
//      if ( i == ssmbrIdx && (segIdx < 0 || nSegments <= segIdx) )
//         return E_INVALIDARG;
//
//      long maxSeg = ( i != ssmbrIdx ) ? nSegments : segIdx;
//      for ( long seg = 0; seg < maxSeg; seg++ )
//      {
//         CComPtr<ISegment> segment;
//         segments->get_Item(seg,&segment);
//
//         Float64 segment_length;
//         segment->get_Length(&segment_length);
//
//         if ( bFractional == VARIANT_TRUE )
//         {
//            segment_length *= -ssmbr_length;
//         }
//
//         dist_from_start += segment_length;
//      }
//   }
//
//
//   dist_from_start += loc;
//
//   *dist = dist_from_start;
//
//   return S_OK;
//}

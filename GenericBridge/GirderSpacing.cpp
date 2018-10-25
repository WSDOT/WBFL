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

// GirderSpacing.cpp : Implementation of CGirderSpacing
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "GirderSpacing.h"
#include "Pier.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGirderSpacing
HRESULT CGirderSpacing::FinalConstruct()
{
   m_pPier = 0;
   return S_OK;
}

void CGirderSpacing::FinalRelease()
{
}

STDMETHODIMP CGirderSpacing::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGirderSpacing,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CGirderSpacing::SetBridge(IGenericBridge* pBridge)
{
   m_pBridge = pBridge;
}

void CGirderSpacing::SetPier(CPier* pPier,EndType end)
{
   m_pPier   = pPier;
   m_SpanEnd = end;
}

void CGirderSpacing::SetGirderCount(GirderIndexType nGirders)
{
   if ( (GirderIndexType)m_Spacing.size() < nGirders )
      RemoveGirders( nGirders - m_Spacing.size() );
   else
      AddGirders( m_Spacing.size() - nGirders );
}

GirderIndexType CGirderSpacing::GetGirderCount()
{
   return m_Spacing.size();
}

void CGirderSpacing::AddGirders(GirderIndexType nGirders)
{
   Float64 space;
   Float64 haunch;
   if ( m_Spacing.size() == 0 )
   {
      space = 1.0; // this is the first girder/space added... use a default value
      haunch = 1.0;
   }
   else
   {
      space = m_Spacing.back(); // use the last spacing
      haunch = m_Haunch.back();
   }

   // if this is the first girders to be added, there will be nGirders-1 spaces, otherwise
   // add a space for each new girder
   SpacingIndexType nSpacesToAdd = (m_Spacing.size() == 0 ? nGirders-1 : nGirders);
   m_Spacing.insert(m_Spacing.end(),nSpacesToAdd,space);

   // add default haunches for the new girders
   m_Haunch.insert(m_Haunch.end(),nGirders,haunch);
}

void CGirderSpacing::RemoveGirders(GirderIndexType nGirders)
{
   std::vector<Float64>::iterator last  = m_Spacing.end();
   std::vector<Float64>::iterator first = last - nGirders;
   m_Spacing.erase(first,last);

   last  = m_Haunch.end();
   first = last - nGirders;
   m_Haunch.erase(first,last);
}

void CGirderSpacing::GetSpan(ISpan** ppSpan)
{
   CComPtr<ISpan> span;
   if ( m_SpanEnd == etStart )
   {
      m_pPier->get_NextSpan(ppSpan);
   }
   else
   {
      m_pPier->get_PrevSpan(ppSpan);
   }
}

STDMETHODIMP CGirderSpacing::SetRefGirder(GirderIndexType refGirderIdx,Float64 refGirderOffset,OffsetType refGirderOffsetType)
{
   bool bEvent = false;
   if ( refGirderIdx != m_RefGirderIdx )
   {
      m_RefGirderIdx = refGirderIdx;
      bEvent = true;
   }

   if ( refGirderOffset != m_RefGirderOffset )
   {
      m_RefGirderOffset = refGirderOffset;
      bEvent = true;
   }

   if ( refGirderOffsetType != m_RefGirderOffsetType )
   {
      m_RefGirderOffsetType = refGirderOffsetType;
      bEvent = true;
   }

   if ( bEvent )
      Fire_OnGirderSpacingChanged();

   return S_OK;
}

STDMETHODIMP CGirderSpacing::put_RefGirder(GirderIndexType refGirderIdx)
{
   if ( refGirderIdx != m_RefGirderIdx )
   {
      m_RefGirderIdx = refGirderIdx;
      Fire_OnGirderSpacingChanged();
   }
   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_RefGirder(GirderIndexType* refGirderIdx)
{
   CHECK_RETVAL(refGirderIdx);
   *refGirderIdx = m_RefGirderIdx;
   return S_OK;
}

STDMETHODIMP CGirderSpacing::put_RefGirderOffset(Float64 refGirderOffset)
{
   if ( refGirderOffset != m_RefGirderOffset )
   {
      m_RefGirderOffset = refGirderOffset;
      Fire_OnGirderSpacingChanged();
   }
   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_RefGirderOffset(Float64* refGirderOffset)
{
   CHECK_RETVAL(refGirderOffset);
   *refGirderOffset = m_RefGirderOffset;
   return S_OK;
}

STDMETHODIMP CGirderSpacing::put_RefGirderOffsetType(OffsetType refGirderOffsetType)
{
   if ( refGirderOffsetType != m_RefGirderOffsetType )
   {
      m_RefGirderOffsetType = refGirderOffsetType;
      Fire_OnGirderSpacingChanged();
   }
   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_RefGirderOffsetType(OffsetType* refGirderOffsetType)
{
   CHECK_RETVAL(refGirderOffsetType);
   *refGirderOffsetType = m_RefGirderOffsetType;
   return S_OK;
}

STDMETHODIMP CGirderSpacing::SetMeasurement(MeasurementLocation ml,MeasurementType mt)
{
   bool bEvent = false;
   if ( ml != m_MeasureLocation )
   {
      m_MeasureLocation = ml;
      bEvent = true;
   }

   if ( mt != m_MeasureType )
   {
      m_MeasureType = mt;
      bEvent = true;
   }

   if ( bEvent )
      Fire_OnGirderSpacingChanged();

   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_MeasurementLocation(/*[out,retval]*/MeasurementLocation* ml)
{
   CHECK_RETVAL(ml);
   *ml = m_MeasureLocation;
   return S_OK;
}

STDMETHODIMP CGirderSpacing::put_MeasurementLocation(/*[in]*/MeasurementLocation ml)
{
   if ( m_MeasureLocation != ml )
   {
      m_MeasureLocation = ml;
      Fire_OnGirderSpacingChanged();
   }

   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_MeasurementType(/*[out,retval]*/MeasurementType* mt)
{
   CHECK_RETVAL(mt);
   *mt = m_MeasureType;
   return S_OK;
}

STDMETHODIMP CGirderSpacing::put_MeasurementType(/*[in]*/MeasurementType mt)
{
   if ( m_MeasureType != mt )
   {
      m_MeasureType = mt;
      Fire_OnGirderSpacingChanged();
   }

   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_Spacing(SpacingIndexType spaceIdx,Float64* spacing)
{
   CHECK_RETVAL(spacing);
   if ( spaceIdx < 0 || (SpacingIndexType)m_Spacing.size() <= spaceIdx )
      return E_INVALIDARG;

   *spacing = m_Spacing[spaceIdx];
   return S_OK;
}

STDMETHODIMP CGirderSpacing::put_Spacing(SpacingIndexType spaceIdx,Float64 spacing)
{
   if ( spaceIdx < 0 || (SpacingIndexType)m_Spacing.size() <= spaceIdx )
      return E_INVALIDARG;

   if ( spacing <= 0 )
      return E_INVALIDARG;

   if ( !IsEqual(m_Spacing[spaceIdx],spacing) )
   {
      m_Spacing[spaceIdx] = spacing;
      Fire_OnGirderSpacingChanged();
   }

   return S_OK;
}

STDMETHODIMP CGirderSpacing::put_Spacings(IDblArray* spaces)
{
   CHECK_IN(spaces);
   SpacingIndexType nSpaces = m_Spacing.size();
   CollectionIndexType cSpaces;
   spaces->get_Count(&cSpaces);
   nSpaces = _cpp_min(nSpaces,(SpacingIndexType)cSpaces);
   bool bChanged = false;
   for ( SpacingIndexType spaceIdx = 0; spaceIdx < nSpaces; spaceIdx++ )
   {
      Float64 space;
      spaces->get_Item(spaceIdx,&space);
      if ( !IsEqual(space,m_Spacing[spaceIdx]) )
      {
         m_Spacing[spaceIdx] = space;
         bChanged = true;
      }
   }

   if ( bChanged )
      Fire_OnGirderSpacingChanged();

   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_GirderSpacing(SpacingIndexType spaceIdx,MeasurementLocation ml,MeasurementType mt,Float64* spacing)
{
   CHECK_RETVAL(spacing);

   CogoElementKey leftPointID[2], rightPointID[2]; // girder/line intersection point on left and right side of this space

   PierIndexType pierIdx;
   m_pPier->get_Index(&pierIdx);

   PierIndexType startPierIdx = ( m_SpanEnd == etStart ? pierIdx     : pierIdx-1 );
   PierIndexType endPierIdx   = ( m_SpanEnd == etStart ? pierIdx + 1 : pierIdx   );
   if ( ml == mlPierLine )
   {
      ::GB_GetPierGirderPointId(startPierIdx, spaceIdx,   qcbAfter,  &leftPointID[etStart]);
      ::GB_GetPierGirderPointId(endPierIdx,   spaceIdx,   qcbBefore, &leftPointID[etEnd]);
      ::GB_GetPierGirderPointId(startPierIdx, spaceIdx+1, qcbAfter,  &rightPointID[etStart]);
      ::GB_GetPierGirderPointId(endPierIdx,   spaceIdx+1, qcbBefore, &rightPointID[etEnd]);
   }
   else
   {
      ::GB_GetBearingGirderPointId(startPierIdx, spaceIdx,   qcbAfter,  &leftPointID[etStart]);
      ::GB_GetBearingGirderPointId(endPierIdx,   spaceIdx,   qcbBefore, &leftPointID[etEnd]);
      ::GB_GetBearingGirderPointId(startPierIdx, spaceIdx+1, qcbAfter,  &rightPointID[etStart]);
      ::GB_GetBearingGirderPointId(endPierIdx,   spaceIdx+1, qcbBefore, &rightPointID[etEnd]);
   }

   CComPtr<ICogoModel> cogoModel;
   m_pBridge->get_CogoModel(&cogoModel);

   CComPtr<IAlignment> alignment;
   m_pBridge->get_Alignment(&alignment);

   if ( mt == mtAlongItem )
   {
      // requesting spacing measured along CL Pier or CL Bearing
      // simply measure the distance between the points

      CComQIPtr<IMeasure> measure(cogoModel);
      measure->Distance(leftPointID[m_SpanEnd],rightPointID[m_SpanEnd],spacing);
   }
   else
   {
      // requesting spacing measured along a normal to the alignment
      // intersect the girder lines with the normal line and measure between the intersection points

      // Get the normal to the alignment at the pier
      CComPtr<IStation> objStation;
      if ( ml == mlPierLine )
      {
         // want the normal where the CL Pier intersects the alignment
         m_pPier->get_Station(&objStation);
      }
      else
      {
         // want the normal where the CL Bearing intersects the alignment

         // get the bearing offset from the connection object
         CComPtr<IConnection> connection;
         m_pPier->get_Connection(m_SpanEnd == etStart ? qcbAfter : qcbBefore,&connection);
         Float64 brgOffset;
         connection->get_BearingOffset(&brgOffset);

         // determine how the bearing offset is measured
         MeasurementType measureType;
         connection->get_BearingOffsetMeasurementType(&measureType);

         if ( measureType == mtNormal )
         {
            // bearing offset is measured normal to the CL Pier

            // create a line that is parallel to the CL Pier.
            // This will be the CL Bearing line

            // Get ends points of the pier
            CComPtr<IPoint2d> pntPierLeft, pntPierRight;
            ::GB_GetPierEndPoints(m_pBridge,pierIdx,&pntPierLeft,&pntPierRight);

            // create a line for the CL Pier
            CComPtr<ILine2d> line;
            line.CoCreateInstance(CLSID_Line2d);
            line->ThroughPoints(pntPierLeft,pntPierRight);

            // offset the line to make it the CL Bearing line
            line->Offset(m_SpanEnd == etStart ? brgOffset : -brgOffset);

            // get the point where the CL Bearing intersects the alignment
            CComPtr<IPoint2d> pntBrg;
            alignment->Intersect(line,pntPierLeft,&pntBrg);

            // get the station where the CL Bearing intersects the alignment
            Float64 offset;
            alignment->Offset(pntBrg,&objStation,&offset);
            ATLASSERT(IsZero(offset));
         }
         else
         {
            ATLASSERT(false);
            // bearing offset is measured along the CL girder so there isn't a single
            // unique bearing line (unless all girders are parallel)

            // do something here so we don't have a total mess up in release builds
            m_pPier->get_Station(&objStation);

            CComPtr<IStation> clone;
            objStation->Clone(&clone);

            clone->Increment(m_SpanEnd == etStart ? brgOffset : -brgOffset);
            objStation.Release();
            objStation = clone;
         }
      }

      // get the normal to the alignment at the station where the measurement line
      // intersects the alignment
      CComPtr<IDirection> normal;
      alignment->Normal(CComVariant(objStation),&normal);

      Float64 direction;
      normal->get_Value(&direction);

      // get the point where the measurement line intersects the alignment
      CComPtr<IPoint2d> pntAlignment;
      alignment->LocatePoint(CComVariant(objStation),omtNormal,0.0,CComVariant(normal),&pntAlignment);

      // get the end points of the girder
      CComPtr<IPointCollection> points;
      cogoModel->get_Points(&points);
      CComPtr<IPoint2d> pntLeftGdr[2], pntRightGdr[2];
      points->get_Item(leftPointID[etStart], &pntLeftGdr[etStart]);
      points->get_Item(leftPointID[etEnd],   &pntLeftGdr[etEnd]);
      points->get_Item(rightPointID[etStart],&pntRightGdr[etStart]);
      points->get_Item(rightPointID[etEnd],  &pntRightGdr[etEnd]);

      // get the bearing (direction) of the girders
      CComQIPtr<IMeasure> measure(cogoModel);
      CComPtr<IDirection> dirLeftGdr, dirRightGdr;
      measure->Direction(leftPointID[etStart],leftPointID[etEnd],&dirLeftGdr);
      measure->Direction(rightPointID[etStart],rightPointID[etEnd],&dirRightGdr);

      // get some COGO interfaces
      CComPtr<ICogoEngine> cogoEngine;
      cogoModel->get_Engine(&cogoEngine);

      CComPtr<IIntersect2> intersect;
      cogoEngine->get_Intersect(&intersect);

      // intersect the measurement line with the girder lines
      CComPtr<IPoint2d> pntLeft, pntRight;
      intersect->Bearings(pntAlignment,CComVariant(normal),0.0,pntLeftGdr[etStart], CComVariant(dirLeftGdr), 0.0,&pntLeft);
      intersect->Bearings(pntAlignment,CComVariant(normal),0.0,pntRightGdr[etStart],CComVariant(dirRightGdr),0.0,&pntRight);

      // spacing is the distance between the intersection points
      pntLeft->DistanceEx(pntRight,spacing);
   }

   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_Width(Float64 distFromStartOfSpan,MeasurementType measureType,Float64* width)
{
   // Compute the outside girder to girder width, normal to the alignment at 'distFromStartOfSpan'
   CComPtr<ISpan> span;
   GetSpan(&span);
   SpanIndexType spanIdx;
   span->get_Index(&spanIdx);

   // Determine station that corrosponds to distFromStartOfSpan
   CComPtr<IPier> pier;
   span->get_PrevPier(&pier);

   CComPtr<IStation> objStartStation;
   pier->get_Station(&objStartStation);
   Float64 start_station;
   objStartStation->get_Value(&start_station);

   Float64 cut_station = start_station + distFromStartOfSpan;


   CComPtr<IAlignment> alignment;
   m_pBridge->get_Alignment(&alignment);


   CComPtr<IPoint2d> alignment_point;
   alignment->LocatePoint(CComVariant(cut_station),omtAlongDirection, 0.00,CComVariant(0.00),&alignment_point);

   // project point onto first and last girder line
   CComPtr<ICogoInfo> cogoinfo;
   m_pBridge->get_CogoInfo(&cogoinfo);

   CComPtr<ICogoModel> cogomodel;
   m_pBridge->get_CogoModel(&cogomodel);

   CComPtr<ICogoEngine> cogoengine;
   cogoengine.CoCreateInstance(CLSID_CogoEngine);
   CComQIPtr<IProject2> project(cogoengine);
   CComQIPtr<IMeasure2> measure(cogoengine);

   CComPtr<IPointCollection> points;
   cogomodel->get_Points(&points);

   CComPtr<IPoint2d> pntLeft, pntRight;

   // left girder line
   CogoElementKey startPointID, endPointID;
   cogoinfo->get_PierGirderIntersectionPointID(spanIdx,  0, qcbAfter,  &startPointID);
   cogoinfo->get_PierGirderIntersectionPointID(spanIdx+1,0, qcbBefore, &endPointID);

   CComPtr<IPoint2d> startPoint,endPoint;
   points->get_Item(startPointID, &startPoint);
   points->get_Item(endPointID,   &endPoint  );

   project->PointOnLineByPoints(alignment_point,startPoint,endPoint,0.00,&pntLeft);


   // right girder line
   GirderIndexType nGirders;
   span->get_GirderCount(&nGirders);
   cogoinfo->get_PierGirderIntersectionPointID(spanIdx,  nGirders-1, qcbAfter,  &startPointID);
   cogoinfo->get_PierGirderIntersectionPointID(spanIdx+1,nGirders-1, qcbBefore, &endPointID);

   startPoint.Release();
   endPoint.Release();
   points->get_Item(startPointID, &startPoint);
   points->get_Item(endPointID,   &endPoint  );

   project->PointOnLineByPoints(alignment_point,startPoint,endPoint,0.00,&pntRight);

   // measure distance between girder line points
   Float64 w = 0;
   measure->Distance(pntLeft,pntRight,&w);
   *width = w;

   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_WidthAtPier(MeasurementType measureType,Float64* width)
{
   return GetPierWidth(mlPierLine,measureType,width);
}

STDMETHODIMP CGirderSpacing::get_WidthAtBearing(MeasurementType measureType,Float64* width)
{
   return GetPierWidth(mlCenterlineBearing,measureType,width);
}

STDMETHODIMP CGirderSpacing::get_SpacingAlongGirder(GirderIndexType gdrIdx, Float64 dist, DirectionType side, Float64* space)
{
   // computes the distance from this girder line to the girder line on "side". Dist is the distance along
   // this girder line. the space is measured normal to this girder
   CHECK_RETVAL(space);

   // get the other girder spacing for the span this girder spacing object is associted with
   CComPtr<ISpan> span;
   CComPtr<IGirderSpacing> otherSpacing;
   if ( m_SpanEnd == etStart )
   {
      // this spacing object is for the start of the span. the associated span
      // is the next span
      m_pPier->get_NextSpan(&span);
      span->get_GirderSpacing(etEnd,&otherSpacing);
   }
   else
   {
      // this spacing object is for the end of the span. the associated span
      // is the prev span
      m_pPier->get_PrevSpan(&span);
      span->get_GirderSpacing(etStart,&otherSpacing);
   }

   GirderIndexType nGirders;
   span->get_GirderCount(&nGirders);
   if ( (gdrIdx == 0          && side == qcbLeft) ||  // left side of first girder -OR-
        (gdrIdx == nGirders-1 && side == qcbRight) )  // right side of last girder
   {
      // Requesting space on exterior side of exterior girder
      *space = -1;
      return S_OK;
   }

   // We are going to need the underlying COGO model to deal with this
   
   // ASSUMPTIONS: Spacing is equal to the distance to the next (or previous) girder line
   //              measured normal to this girder line.
   CComPtr<ICogoModel> cogoModel;
   CComPtr<ICogoInfo> cogoInfo;
   m_pBridge->get_CogoModel(&cogoModel);
   m_pBridge->get_CogoInfo(&cogoInfo);

   SpanIndexType spanIdx;
   span->get_Index(&spanIdx);

   CogoElementKey girder_line_id;
   cogoInfo->get_GirderLineID(spanIdx,gdrIdx,&girder_line_id);

   CComPtr<ICogoEngine> cogoEngine;
   cogoEngine.CoCreateInstance(CLSID_CogoEngine);

   CComPtr<IPointCollection> points;
   cogoModel->get_Points(&points);

   // Get start and end points of girder line
   CogoElementKey girder_line_start_point_id;
   CogoElementKey girder_line_end_point_id;
   cogoInfo->get_PierGirderIntersectionPointID(PierIndexType(spanIdx),   gdrIdx, qcbAfter,  &girder_line_start_point_id);
   cogoInfo->get_PierGirderIntersectionPointID(PierIndexType(spanIdx+1), gdrIdx, qcbBefore, &girder_line_end_point_id);

   CComPtr<IPoint2d> gdrStartPoint, gdrEndPoint;
   points->get_Item(girder_line_start_point_id,&gdrStartPoint);
   points->get_Item(girder_line_end_point_id,  &gdrEndPoint);

   // Get point on girder line at which spacing will be measured
   CComPtr<IPoint2d> p1;
   CComQIPtr<ILocate2> locate(cogoEngine);
   locate->PointOnLine(gdrStartPoint,gdrEndPoint,dist,0.00,&p1);

   // Get direction of girder line
   CComQIPtr<IMeasure2> measure(cogoEngine);
   CComPtr<IDirection> direction1;
   measure->Direction(gdrStartPoint,gdrEndPoint,&direction1);

   // Rotate direction normal to girder line
   direction1->IncrementBy(CComVariant(PI_OVER_2));

   // index of adjacent girder line
   GirderIndexType adjGdrIdx = gdrIdx + (side == qcbLeft ? -1 : +1);

   // Get start and end points of the adjacent girder line
   CogoElementKey adj_girder_line_start_point_id;
   CogoElementKey adj_girder_line_end_point_id;
   cogoInfo->get_PierGirderIntersectionPointID(PierIndexType(spanIdx),   adjGdrIdx, qcbAfter,  &adj_girder_line_start_point_id);
   cogoInfo->get_PierGirderIntersectionPointID(PierIndexType(spanIdx+1), adjGdrIdx, qcbBefore, &adj_girder_line_end_point_id);

   CComPtr<IPoint2d> adjGdrStartPoint, adjGdrEndPoint;
   points->get_Item(adj_girder_line_start_point_id, &adjGdrStartPoint);
   points->get_Item(adj_girder_line_end_point_id,   &adjGdrEndPoint);

   // Get direction of adjacent girder line
   CComPtr<IDirection> direction2;
   measure->Direction(adjGdrStartPoint,adjGdrEndPoint,&direction2);

   // Intersection a line normal to the girder line, passing through the point on
   // the girder line, with the adjacent girder line
   CComQIPtr<IIntersect2> intersect(cogoEngine);
   CComPtr<IPoint2d> p2;
   intersect->Bearings(p1,CComVariant(direction1),0.00,adjGdrStartPoint,CComVariant(direction2),0.00,&p2);

   // Spacing is the distance between p1 and p2;
   Float64 spacing;
   measure->Distance(p1,p2,&spacing);

   (*space) = spacing;

   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_GirderOffset(GirderIndexType gdrIdx,MeasurementLocation measureLocation,MeasurementType measureType,Float64* pOffset)
{
   // returns the distance from the geometric center of the spacing to the girder
   // negative values indicate the girder is left of center
   CHECK_RETVAL(pOffset);

   Float64 width;
   if ( measureLocation == mlPierLine )
      get_WidthAtPier(measureType,&width);
   else
      get_WidthAtBearing(measureType,&width);

   Float64 offset = -width/2; // offset to the left most girder
   // add spaces until we get to the girder we're after
   for ( GirderIndexType girderIdx = 1; girderIdx <= gdrIdx; girderIdx++ )
   {
      SpacingIndexType spaceIdx = SpacingIndexType(girderIdx-1);

      Float64 space;
      get_GirderSpacing(spaceIdx,measureLocation,measureType,&space);
      offset += space;
   }

   (*pOffset) = offset;
   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_SpaceWidth(SpacingIndexType spaceIdx,Float64 distFromStartOfSpan,Float64* space)
{
   // returns the width of a girder space, measured normal to the alignment at "distFromStartOfSpan".
   CHECK_RETVAL(space);

   // indices of girders on either side of the space
   GirderIndexType gdrIdx1 = spaceIdx;
   GirderIndexType gdrIdx2 = gdrIdx1 + 1;

   // get station where space is measured
   CComPtr<IStation> objStation;
   Float64 station;
   SpanIndexType spanIdx;
   if ( m_SpanEnd == etStart )
   {
      m_pPier->get_Station(&objStation);
      CComPtr<ISpan> nextSpan;
      m_pPier->get_NextSpan(&nextSpan);
      nextSpan->get_Index(&spanIdx);
   }
   else
   {
      CComPtr<ISpan> prevSpan;
      m_pPier->get_PrevSpan(&prevSpan);

      CComPtr<IPier> prevPier;
      prevSpan->get_PrevPier(&prevPier);

      prevPier->get_Station(&objStation);
      prevSpan->get_Index(&spanIdx);
   }

   objStation->get_Value(&station);
   station += distFromStartOfSpan;

   // get the cogo model information
   CComPtr<ICogoInfo> cogoinfo;
   m_pBridge->get_CogoInfo(&cogoinfo);

   CComPtr<ICogoModel> cogomodel;
   m_pBridge->get_CogoModel(&cogomodel);

   // get the line ID for each girder line
   CogoElementKey gdrID1, gdrID2;
   ::GB_GetGirderLineId(spanIdx,gdrIdx1,&gdrID1);
   ::GB_GetGirderLineId(spanIdx,gdrIdx2,&gdrID2);

   // get the line segment for each girder line
   CComPtr<ILineSegment2d> lsGirder1, lsGirder2;
   CComPtr<ILineSegmentCollection> lineSegments;
   cogomodel->get_LineSegments(&lineSegments);
   lineSegments->get_Item(gdrID1,&lsGirder1);
   lineSegments->get_Item(gdrID2,&lsGirder2);

   // get the direction of the normal to the alignment at the station
   CogoElementKey alignmentKey;
   cogoinfo->get_AlignmentKey(&alignmentKey);

   CComPtr<IPathCollection> paths;
   cogomodel->get_Alignments(&paths);
   CComPtr<IPath> path;
   paths->get_Item(alignmentKey,&path);
   CComQIPtr<IAlignment> alignment(path);
   CComPtr<IDirection> normal;
   alignment->Normal(CComVariant(station),&normal);

   // get a point on the alignment at station
   CComPtr<IPoint2d> pntAlignment;
   alignment->LocatePoint(CComVariant(station),omtAlongDirection, 0.00,CComVariant(normal),&pntAlignment);


   // compute the intersection point of the normal with each girder line segment
   CComPtr<ICogoEngine> cogoengine;
   cogoengine.CoCreateInstance(CLSID_CogoEngine);
   CComQIPtr<IMeasure2> measure(cogoengine);

   // get direction of girder line 1;
   CComPtr<IPoint2d> pntG11,pntG12;
   lsGirder1->get_StartPoint(&pntG11);
   lsGirder1->get_EndPoint(&pntG12);
   CComPtr<IDirection> dirGirder1;
   measure->Direction(pntG11,pntG12,&dirGirder1);

   // get direction of girder line 2;
   CComPtr<IPoint2d> pntG21,pntG22;
   lsGirder2->get_StartPoint(&pntG21);
   lsGirder2->get_EndPoint(&pntG22);
   CComPtr<IDirection> dirGirder2;
   measure->Direction(pntG21,pntG22,&dirGirder2);

   // intersect the line segment/normal
   CComQIPtr<IIntersect2> intersect(cogoengine);
   CComPtr<IPoint2d> pntIntersect1;
   intersect->Bearings(pntAlignment,CComVariant(normal),0.00,pntG11,CComVariant(dirGirder1),0.00,&pntIntersect1);

   CComPtr<IPoint2d> pntIntersect2;
   intersect->Bearings(pntAlignment,CComVariant(normal),0.00,pntG21,CComVariant(dirGirder2),0.00,&pntIntersect2);

   measure->Distance(pntIntersect1,pntIntersect2,space);

   return S_OK;
}

STDMETHODIMP CGirderSpacing::get_GirderHaunch(GirderIndexType gdrIdx,Float64* pHaunch)
{
   ATLASSERT( 0 <= gdrIdx && gdrIdx < (GirderIndexType)m_Haunch.size() );
   (*pHaunch) = m_Haunch[gdrIdx];
   return S_OK;
}

STDMETHODIMP CGirderSpacing::put_GirderHaunch(GirderIndexType gdrIdx,Float64 haunch)
{
   ATLASSERT( 0 <= gdrIdx && gdrIdx < (GirderIndexType)m_Haunch.size() );
   m_Haunch[gdrIdx] = haunch;
   return S_OK;
}

//////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CGirderSpacing::Save(IStructuredSave2* pSave)
{
//   pSave->BeginUnit(CComBSTR("GirderSpacing"),1.0);
//
//   pSave->put_Property(CComBSTR("Uniform"),CComVariant(m_bUniform));
//   pSave->put_Property(CComBSTR("UniformSpacing"),CComVariant(m_UniformSpacing));
//
//   pSave->BeginUnit(CComBSTR("SpacingData"),1.0);
//   long nPiers = m_SpacingData.size();
//   pSave->put_Property(CComBSTR("NumPiers"),CComVariant(nPiers));
//   std::vector<SpacingData>::iterator iter2;
//   for ( iter2 = m_SpacingData.begin(); iter2 != m_SpacingData.end(); iter2++ )
//   {
//      pSave->BeginUnit(CComBSTR("SpacingDataAtPier"),1.0);
//      SpacingData& spacing = *iter2;
//      pSave->put_Property(CComBSTR("Measure"),CComVariant(spacing.m_Measure));
//
//      long nSpaces = spacing.m_Spacing.size();
//      pSave->put_Property(CComBSTR("NumSpaces"),CComVariant(nSpaces));
//      std::vector<Float64>::iterator it;
//      for ( it = spacing.m_Spacing.begin(); it != spacing.m_Spacing.end(); it++ )
//      {
//         Float64 space = *it;
//         pSave->put_Property(CComBSTR("Space"),CComVariant(space));
//      }
//      pSave->EndUnit();
//   }
//   pSave->EndUnit();
//
//   pSave->BeginUnit(CComBSTR("SuperstructureMembersAlongGirderLines"),1.0);
//   long nMembers = m_SuperstructureMembers.size();
//   pSave->put_Property(CComBSTR("NumGirderLines"),CComVariant(nMembers));
//   std::vector<CComPtr<ISuperstructureMemberCollection> >::iterator iter;
//   for ( iter = m_SuperstructureMembers.begin(); iter != m_SuperstructureMembers.end(); iter++ )
//   {
//      CComPtr<ISuperstructureMemberCollection> members = *iter;
//
//      // Don't want to save link source data, so unlink now and relink after save.
//      CComPtr<ISuperstructureMemberCollection> linkSource;
//      members->get_LinkSource(&linkSource);
//      long linkPosition;
//      if ( linkSource )
//      {
//         dynamic_cast<CSuperstructureMemberCollection*>(members.p)->UnlinkQuietly(&linkPosition);
//
//         long sourceIndex = GetGirderLineIndex(linkSource);
//
//         pSave->put_Property(CComBSTR("Linked"),CComVariant(VARIANT_TRUE));
//         pSave->put_Property(CComBSTR("LinkSourceIndex"),CComVariant(sourceIndex));
//      }
//      else
//      {
//         pSave->put_Property(CComBSTR("Linked"),CComVariant(VARIANT_FALSE));
//      }
//
//      CComQIPtr<IStructuredStorage2> ss(members);
//      ss->Save(pSave);
//
//      if ( linkSource )
//      {
//         dynamic_cast<CSuperstructureMemberCollection*>(linkSource.p)->LinkQuietly(members,linkPosition);
//      }
//   }
//   pSave->EndUnit();
//
//   
//   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CGirderSpacing::Load(IStructuredLoad2* pLoad)
{
//   // make sure we start with empty containers
//   m_SpacingData.clear();
//   m_SuperstructureMembers.clear();
//
//   CComVariant var;
//   VARIANT_BOOL bEnd;
//
//   pLoad->BeginUnit(CComBSTR("GirderSpacing"));
//
//   pLoad->get_Property(CComBSTR("Uniform"),&var);
//   m_bUniform = var.boolVal;
//
//   pLoad->get_Property(CComBSTR("UniformSpacing"),&var);
//   m_UniformSpacing = var.dblVal;
//
//   
//   
//   pLoad->BeginUnit(CComBSTR("SpacingData"));
//   long nPiers;
//   pLoad->get_Property(CComBSTR("NumPiers"),&var);
//   nPiers = var.lVal;
//   for ( long i = 0; i < nPiers; i++ )
//   {
//      pLoad->BeginUnit(CComBSTR("SpacingDataAtPier"));
//
//      SpacingData sd;
//
//      pLoad->get_Property(CComBSTR("Measure"),&var);
//      sd.m_Measure = (MeasurementType)var.lVal;
//
//      long nSpaces;
//      pLoad->get_Property(CComBSTR("NumSpaces"),&var);
//      nSpaces = var.lVal;
//
//      for ( long j = 0; j < nSpaces; j++ )
//      {
//         pLoad->get_Property(CComBSTR("Space"),&var);
//         sd.m_Spacing.push_back(var.dblVal);
//      }
//      
//      m_SpacingData.push_back(sd);
//
//      pLoad->EndUnit(&bEnd);
//   }
//   pLoad->EndUnit(&bEnd);
//
//   
//   std::vector<std::pair<long,long> > linkData; // first = link target, second = link source
//
//   pLoad->BeginUnit(CComBSTR("SuperstructureMembersAlongGirderLines"));
//   pLoad->get_Property(CComBSTR("NumGirderLines"),&var);
//   long nGirderLines = var.lVal;
//   for ( i = 0; i < nGirderLines; i++ )
//   {
//      CComObject<CSuperstructureMemberCollection>* pMembers;
//      CComObject<CSuperstructureMemberCollection>::CreateInstance(&pMembers);
//      CComPtr<ISuperstructureMemberCollection> members = pMembers;
//      pMembers->SetBridge(m_pBridge);
//
//      pLoad->get_Property(CComBSTR("Linked"),&var);
//      if ( var.boolVal == VARIANT_TRUE )
//      {
//         long sourceIndex;
//         pLoad->get_Property(CComBSTR("LinkSourceIndex"),&var);
//         sourceIndex = var.lVal;
//
//         linkData.push_back( std::make_pair(i,sourceIndex) );
//      }
//
//      CComQIPtr<IStructuredStorage2> ss(members);
//      ss->Load(pLoad);
//
//      PutSuperstructureMembers(i,members);
//   }
//   pLoad->EndUnit(&bEnd);
//
//
//
//   pLoad->EndUnit(&bEnd);
//
//
//   // Make all the links
//   std::vector<std::pair<long,long> >::iterator iter;
//   for ( iter = linkData.begin(); iter != linkData.end(); iter++ )
//   {
//      long targetIndex = (*iter).first;
//      long sourceIndex = (*iter).second;
//
//      CComPtr<ISuperstructureMemberCollection> target;
//      get_SuperstructureMembers(targetIndex,&target);
//
//      CComPtr<ISuperstructureMemberCollection> source;
//      get_SuperstructureMembers(sourceIndex,&source);
//
//      source->Link(target);
//   }

   return S_OK;
}

HRESULT CGirderSpacing::GetPierWidth(MeasurementLocation measureLocation,MeasurementType measureType,Float64* width)
{
   // Compute the outside girder to girder width at the CL pier
   CHECK_RETVAL(width);
   
   PierIndexType pierIdx;
   m_pPier->get_Index(&pierIdx);

   CComPtr<ISpan> span;
   GetSpan(&span);

   CComPtr<ICogoModel> cogomodel;
   m_pBridge->get_CogoModel(&cogomodel);
   
   CComQIPtr<IMeasure> measure(cogomodel);

   CComPtr<IPointCollection> points;
   cogomodel->get_Points(&points);

   // Get intersection of CL pier and Left and Right girder line
   CComPtr<IPoint2d> pntLeft, pntRight;

   GirderIndexType nGirders;
   span->get_GirderCount(&nGirders);

   CogoElementKey startPointID, endPointID;
   if ( measureLocation == mlPierLine )
   {
      ::GB_GetPierGirderPointId(pierIdx,          0, m_SpanEnd == etStart ? qcbAfter : qcbBefore,  &startPointID);
      ::GB_GetPierGirderPointId(pierIdx, nGirders-1, m_SpanEnd == etStart ? qcbAfter : qcbBefore, &endPointID);
   }
   else
   {
      ::GB_GetBearingGirderPointId(pierIdx,          0, m_SpanEnd == etStart ? qcbAfter : qcbBefore,  &startPointID);
      ::GB_GetBearingGirderPointId(pierIdx, nGirders-1, m_SpanEnd == etStart ? qcbAfter : qcbBefore, &endPointID);
   }

   Float64 dist;
   measure->Distance(startPointID,endPointID,&dist);

   if ( measureType == mtNormal )
   {
      CComPtr<IAngle> objSkewAngle;
      m_pPier->get_SkewAngle(&objSkewAngle);
      Float64 skewAngle;
      objSkewAngle->get_Value(&skewAngle);

      dist *= cos(skewAngle);
   }

   *width = dist;

   return S_OK;
}

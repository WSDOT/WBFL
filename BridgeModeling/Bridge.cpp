///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfBridge        
****************************************************************************/
#include <BridgeModeling\Bridge.h>                // class implementation
#include <BridgeModeling\SpanFactory.h>
#include <BridgeModeling\PierFactory.h>
#include <BridgeModeling\TrafficBarrierTemplate.h>
#include <BridgeModeling\TrafficBarrier.h>
#include <BridgeModeling\DrawSettings.h>
#include <BridgeModeling\Girder.h>
#include <BridgeModeling\IGirderSection.h>
#include <BridgeModeling\GirderProfile.h>
#include <GraphicsLib\GraphTool.h>

#include <GeomModel\rectangle.h>

#include <GraphicsLib\Dimension.h>
#include <mathex.h>
#include "AlignmentObserver.h"

#include <boost\shared_ptr.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined _DEBUG
#include <iostream>
#include <fstream>
#include <iomanip>
#include <CrtDbg.h>
#endif // _DEBUG

DIAG_DEFINE_GROUP( bmf, DIAG_GROUP_ENABLE, BMF_LEVEL_DRAW );

// set up drawing colors
static COLORREF girder_border_color = RGB(0,0,0);
static COLORREF girder_fill_color = RGB(120,120,120);
static COLORREF slab_border_color = RGB(0,0,0);
static COLORREF slab_fill_color = RGB(150,150,150);
static COLORREF barrier_border_color = RGB(0,0,0);
static COLORREF barrier_fill_color = RGB(200,200,200);
static COLORREF overlay_border_color = RGB(0,0,0);
static COLORREF overlay_fill_color = RGB(80,80,80);

CComModule _Module;

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bmfBridge::bmfBridge(ICogoModel* pCogoModel,IDType alignmentID):
m_HasShapeBeenBuilt(false),
m_CogoModel(pCogoModel)
{
   CComPtr<IPathCollection> alignments;
   m_CogoModel->get_Alignments(&alignments);

   CComPtr<IPath> path;
   alignments->get_Item(alignmentID,&path);
   CComQIPtr<IAlignment> alignment(path);
   ATLASSERT(alignment != NULL);
   m_Alignment = alignment;

   CComObject<bmfAlignmentObserver>* pAlignmentObserver;
   CComObject<bmfAlignmentObserver>::CreateInstance(&pAlignmentObserver);
   pAlignmentObserver->SetBridge(this);
   m_AlignmentObserver = pAlignmentObserver;

   m_pSpanFactory = std::auto_ptr<bmfSpanFactory>(new bmfSpanFactory);
   m_pPierFactory = std::auto_ptr<bmfPierFactory>(new bmfPierFactory);
} // bmfBridge

bmfBridge::bmfBridge(const bmfBridge& rOther)
{
   ATLASSERT(false); // is this ever called???

   m_pSpanFactory = std::auto_ptr<bmfSpanFactory>(new bmfSpanFactory);
   m_pPierFactory = std::auto_ptr<bmfPierFactory>(new bmfPierFactory);

   MakeCopy( rOther );
}

bmfBridge::~bmfBridge()
{
   bmfAlignmentObserver* pObserver = (bmfAlignmentObserver*)(&(*m_AlignmentObserver));
   pObserver->ReleaseBridge();
   m_AlignmentObserver.Release();
} // ~bmfBridge

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bmfSpan* bmfBridge::CreateSpan(SpanIDType id,PierIDType startPierId, PierIDType endPierId)
{
   bmfSpan* pSpan = m_pSpanFactory->CreateSpan();
   if ( !AddSpan( pSpan, id, startPierId, endPierId ) )
      return 0;
   
   return pSpan;
}

bool bmfBridge::AddSpan(bmfSpan* pSpan,SpanIDType id,PierIDType startPierId,PierIDType endPierId)
{
   bmfPier* pstart_pier;
   bmfPier* pend_pier;

   pSpan->SetID( id );
   pSpan->SetBridge(this);

   // Setup associations between the span and the start pier
   pstart_pier = GetPier(startPierId);
   if ( pstart_pier == 0 )
      return false;

   pSpan->SetStartPier(pstart_pier);
   pstart_pier->SetRightSpan(pSpan);

   // Setup associations between the span and the end pier
   pend_pier = GetPier(endPierId);
   if ( pend_pier == 0 )
      return false;

   pSpan->SetEndPier(pend_pier);
   pend_pier->SetLeftSpan(pSpan);

   // Finish setting up the span
   SetupSpan(pSpan);
   StoreSpan( id, pSpan );

   // Now that the span is completely added to the bridge,
   // Give the span a chance to do any addition setup
   pSpan->OnSetup();

   return true;
}

const bmfSpan* bmfBridge::GetSpan(SpanIDType spanId) const
{
   SpanContainer::const_iterator iter = m_Spans.find( spanId );

   CHECKX( iter != m_Spans.end(), _T("Span not found") );

   return (*iter).second.get();
} // GetSpan

bmfSpan* bmfBridge::GetSpan(SpanIDType spanId)
{
   SpanContainer::const_iterator iter = m_Spans.find( spanId );

   CHECKX( iter != m_Spans.end(), _T("Span not found") );

   return (*iter).second.get();
} // GetSpan

const bmfSpan* bmfBridge::GetSpanAtStation(Float64 station) const
{
   SpanContainer::const_iterator start = m_Spans.begin();
   SpanContainer::const_iterator finish = m_Spans.end();
   const bmfSpan* pspan;
   while ( start != finish )
   {
      pspan = (*start++).second.get();
      Float64 start, end;
      start = pspan->StartStation();
      end = pspan->EndStation();
      if ( start > end )
      {
         Float64 temp = start;
         start = end;
         end = temp;
      }

      if (start <= station && station <= end)
      {
         return pspan;
      }
   }

   return 0;
}

void bmfBridge::GetSpans(std::vector<bmfSpan*>& vSpans)
{
   SpanContainer::const_iterator iter;
   for( iter = m_Spans.begin(); iter != m_Spans.end(); iter++ )
   {
      vSpans.push_back( (*iter).second.get() );
   }
}

void bmfBridge::GetSpans(std::vector<const bmfSpan*>& vSpans) const
{
   SpanContainer::const_iterator iter;
   for( iter = m_Spans.begin(); iter != m_Spans.end(); iter++ )
   {
      vSpans.push_back( (*iter).second.get() );
   }
}

void bmfBridge::RemoveSpan(SpanIDType spanId)
{
   bmfSpan* pSpan = GetSpan(spanId);

   // Eliminate associations between the span and its piers.
   bmfPier* pPier;
   pPier = pSpan->GetStartPier();
   pSpan->SetStartPier( 0 );

   pPier = pSpan->GetEndPier();
   pSpan->SetEndPier( 0 );

   delete pSpan;
   m_Spans.erase( spanId );

//   Notify();
}

SpanIndexType bmfBridge::GetSpanCount() const
{
   return m_Spans.size();
}

bmfPier* bmfBridge::CreatePier(PierIDType id,Float64 station,const bmfPierLayout& pl,const bmfConnection* pConnection)
{
   bmfPier* pPier = m_pPierFactory->CreatePier();
   pPier->Layout( pl );
   pPier->SetConnection( pConnection );
   AddPier( pPier, id, station );
   return pPier;
}

void bmfBridge::AddPier(bmfPier* pPier,PierIDType id,Float64 station)
{
   pPier->SetBridge(this);
   pPier->SetID( id );

   SetupPier(pPier);
   StorePier( id ,pPier);

   pPier->OnSetup();
   pPier->Move(station);

//   Notify();
}

void bmfBridge::AddPier(PierIDType id, bmfPier* pPier)
{
   pPier->SetBridge(this);
   pPier->SetID( id );

   SetupPier(pPier);
   StorePier( id ,pPier);

   pPier->OnSetup();
//   Notify();
}


bmfPier* bmfBridge::GetPier(PierIDType pierId) const
{
   PierContainer::const_iterator iter = m_Piers.find( pierId );

   CHECKX( iter != m_Piers.end(), _T("Pier not found") );

   return (*iter).second.get();
} // GetPier

void bmfBridge::GetPiers(std::vector<bmfPier*>& vPiers)
{
   PierContainer::iterator iter;
   for ( iter = m_Piers.begin(); iter != m_Piers.end(); iter++ )
      vPiers.push_back( (*iter).second.get() );
}

void bmfBridge::GetPiers(std::vector<const bmfPier*>& vPiers) const
{
   PierContainer::const_iterator iter;
   for ( iter = m_Piers.begin(); iter != m_Piers.end(); iter++ )
      vPiers.push_back( (*iter).second.get() );
}

void bmfBridge::RemovePier(PierIDType pierId)
{
   bmfPier* pPier = GetPier(pierId);

   // Eliminate associations between the span and its piers.
   bmfSpan* pSpan;
   pSpan = pPier->GetLeftSpan();
   if ( pSpan )
   {
      pSpan->SetEndPier( 0 );
   }
   pPier->SetLeftSpan( 0 );

   pSpan = pPier->GetRightSpan();
   if ( pSpan )
   {
      pSpan->SetStartPier( 0 );
   }
   pPier->SetRightSpan( 0 );

   delete pPier;
   m_Piers.erase( pierId );
} // RemovePier

PierIndexType bmfBridge::GetPierCount() const
{
   return m_Piers.size();
}

void bmfBridge::SetSlab(const bmfSlab& rSlab)
{
   m_pSlab = std::auto_ptr<bmfSlab>(new bmfSlab(rSlab) );

   // This is the opportunity to associated other components in the
   // bridge with the slab.  The association can be either via
   // chain of responsibility or subject/observer.
   //
   // In the current implementation, a slab is a component of a bridge.
   // Nothing else needs to be associated with a slab.
   m_pSlab->SetBridge(this);
}

const bmfSlab* bmfBridge::GetSlab() const
{
   return m_pSlab.get();
}

bmfSlab* bmfBridge::GetSlab()
{
   return m_pSlab.get();
}

void bmfBridge::CreateLeftTrafficBarrier(const bmfTrafficBarrierTemplate* pTpl)
{
   m_pLeftBarrier = std::auto_ptr<bmfTrafficBarrier>( pTpl->CreateTrafficBarrier() );
}

void bmfBridge::RemoveLeftTrafficBarrier()
{
   m_pLeftBarrier = std::auto_ptr<bmfTrafficBarrier>();
}

const bmfTrafficBarrier* bmfBridge::GetLeftTrafficBarrier() const
{
   return m_pLeftBarrier.get();
}

bmfTrafficBarrier* bmfBridge::GetLeftTrafficBarrier()
{
   return m_pLeftBarrier.get();
}

void bmfBridge::CreateRightTrafficBarrier(const bmfTrafficBarrierTemplate* pTpl)
{
   m_pRightBarrier = std::auto_ptr<bmfTrafficBarrier>( pTpl->CreateTrafficBarrier() );
}

void bmfBridge::RemoveRightTrafficBarrier()
{
   m_pRightBarrier = std::auto_ptr<bmfTrafficBarrier>();
}

const bmfTrafficBarrier* bmfBridge::GetRightTrafficBarrier() const
{
   return m_pRightBarrier.get();
}

bmfTrafficBarrier* bmfBridge::GetRightTrafficBarrier()
{
   return m_pRightBarrier.get();
}

Float64 bmfBridge::GetRoadwayWidth(Float64 station) const
{
   Float64 slab = m_pSlab->GetWidth();
   Float64 tb_left =  (m_pLeftBarrier.get()  != 0 ? m_pLeftBarrier->GetTrafficBarrierShape()->GetX2()  : 0);
   Float64 tb_right = (m_pRightBarrier.get() != 0 ? m_pRightBarrier->GetTrafficBarrierShape()->GetX2() : 0);

   return slab - tb_left - tb_right;
}

void bmfBridge::PlanView(HDC hDC,RECT& rect,UINT settings) const
{
   grlibPointMapper mapper;
   LONG center_x,center_y;

   // state settings
   bool bIsotropic      = (settings & BMF_PV_DRAW_ISOTROPIC)!=0;
   bool bScale          = (settings & BMF_PV_DRAW_TO_SCALE)!=0;
   bool bLabelGirders   = (settings & BMF_PV_LABEL_GIRDERS)!=0;
   bool bLabelAlignment = (settings & BMF_PV_LABEL_ALIGNMENT)!=0;
   bool bLabelPiers     = (settings & BMF_PV_LABEL_PIERS)!=0;

   CHECKX(!bScale,_T("Scales not set up"));
   bScale=false;

   grlibPointMapper::MapMode mapmode;
   mapmode = ( bIsotropic ? grlibPointMapper::Isotropic : grlibPointMapper::Anisotropic );

   grlibPointMapper::MapModeModifier modifier;
   modifier = (bScale ? grlibPointMapper::BestFitXY : grlibPointMapper::NoFit);

   mapper.SetMappingMode(mapmode);
   mapper.SetMappingModeModifier(modifier);

   mapper.SetDeviceExt(rect.right - rect.left, rect.bottom - rect.top);

   center_x = (rect.left + rect.right)/2;
   center_y = (rect.top + rect.bottom)/2;
   mapper.SetDeviceOrg(center_x,center_y);
   
   gpRect2d box = GetBoundingBox();

   mapper.SetWorldExt( box.Size() );
   mapper.SetWorldOrg( box.Center() );

   DoDrawPlanView(hDC,mapper, bLabelGirders, bLabelAlignment, bLabelPiers);
} // Draw

bool bmfBridge::DrawSection(HDC hDC, RECT& rect, Float64 station, UINT settings,
                            const unitmgtLengthData& rlen_units) const
{
   // build the section shape if it has not been built, or if the station is different
   if(!m_HasShapeBeenBuilt || station!=m_Station)
   {
      if(BuildSectionShape(station))
         m_Station = station;
      else
      {
         CHECKX(0,_T("Failed to build Section Shape"));
         return false;
      }
   }

   // state settings
   bool bIsotropic      = (settings & BMF_CS_DRAW_ISOTROPIC)!=0;
   bool bScale          = (settings & BMF_CS_DRAW_TO_SCALE)!=0;
   bool bDrawLabels     = (settings & BMF_CS_LABEL_GIRDERS)!=0;
   bool bShowDimensions = (settings & BMF_CS_SHOW_DIMENSIONS)!=0;

   CHECKX(!bScale,_T("Scales not set up"));
   bScale=false;

   // Set up point mapper for device.
   grlibPointMapper mapper;
   LONG center_x,center_y;
   grlibPointMapper::MapMode mapmode;
   mapmode = ( bIsotropic ? grlibPointMapper::Isotropic : grlibPointMapper::Anisotropic );
   grlibPointMapper::MapModeModifier modifier;
   modifier = (bScale ? grlibPointMapper::BestFitXY : grlibPointMapper::NoFit);
   mapper.SetMappingMode(mapmode);
   mapper.SetMappingModeModifier(modifier);
   mapper.SetDeviceExt(rect.right - rect.left, rect.bottom - rect.top);

   center_x = (rect.left + rect.right)/2;
   center_y = (rect.top + rect.bottom)/2;
   mapper.SetDeviceOrg(center_x,center_y);

   // draw dimensions
   grDimension girder_dimension;
   grDimension left_overhang_dimension;
   grDimension right_overhang_dimension;
   grDimension roadway_dimension;

   girder_dimension.SetPointSize(8);
   left_overhang_dimension.SetPointSize(8);
   right_overhang_dimension.SetPointSize(8);
   roadway_dimension.SetPointSize(8);

   CollectionIndexType siz = m_GirderBottoms.size();
   if (bShowDimensions)
   {
      if (siz>1)
      {
         // place dimension for girder spacing
         std::_tostringstream osmsg;
         girder_dimension.SetHookPoints(m_GirderBottoms[0], m_GirderBottoms[siz-1]);
         girder_dimension.SetVerticalDimensionPos(grDimension::Below);
         girder_dimension.SetSpaceFactor(0.5);
         // set up label
         Float64 dist = (m_GirderBottoms[siz-1].X() - m_GirderBottoms[0].X())/(siz-1);
         dist = ::ConvertFromSysUnits(dist, rlen_units.UnitOfMeasure);

         // NOTE:
         // dist is already skew adjusted.  The coordinates of the bottoms of the
         // girder where determined with the skew angle in mind.  Don't adjust this
         // dimension for skew again!!!
//         // adjust dimension for skew angle.  Assume all girders are equally
//         // spaced.
//         const bmfSpan* pspan = GetSpan(0);
//         const bmfGirder* pgird          = pspan->GetGirder(0);
//         const bmfGirderPath* ppath = pgird->GetGirderPath();
//         cogoAngle skew = ppath->GetSectionSkew(station);
//         dist /= fabs(cos(skew.AsFloat64()));

         sysNumericFormatTool nf(rlen_units.Format, rlen_units.Width, rlen_units.Precision);
         osmsg << (siz-1) << (siz==2?" space":" spaces") << " @ "<<nf.AsString(dist)<<" "<<rlen_units.UnitOfMeasure.UnitTag()<< std::endl
               << "Measured Normal to Alignment";
         girder_dimension.SetLabel(osmsg.str());

         // overhang dimension (left overhang)
         std::_tostringstream osdlmsg;
         left_overhang_dimension.SetHookPoints(m_SlabLeftTop, gpPoint2d(m_GirderBottoms[0].X(),m_SlabLeftTop.Y()));
         left_overhang_dimension.SetHorizontalDimensionPos(grDimension::Right);
         dist = m_GirderBottoms[0].X()-m_SlabLeftTop.X();
         dist = ::ConvertFromSysUnits(dist, rlen_units.UnitOfMeasure);
         osdlmsg << nf.AsString(dist)<<" "<<rlen_units.UnitOfMeasure.UnitTag();
         left_overhang_dimension.SetLabel(osdlmsg.str());

         // overhang dimension (right overhang)
         std::_tostringstream osdrmsg;
         right_overhang_dimension.SetHookPoints(gpPoint2d(m_GirderBottoms[m_GirderBottoms.size()-1].X(),m_SlabRightTop.Y()),m_SlabRightTop);
         right_overhang_dimension.SetHorizontalDimensionPos(grDimension::Left);
         dist = m_SlabRightTop.X() - m_GirderBottoms[m_GirderBottoms.size()-1].X();
         dist = ::ConvertFromSysUnits(dist, rlen_units.UnitOfMeasure);
         osdrmsg << nf.AsString(dist)<<" "<<rlen_units.UnitOfMeasure.UnitTag();
         right_overhang_dimension.SetLabel(osdrmsg.str());

         // roadway dimension
         std::_tostringstream strRoadwayDim;
         Float64 width = GetRoadwayWidth(station);
         width = ::ConvertFromSysUnits(width,rlen_units.UnitOfMeasure);
         strRoadwayDim << width << " " << rlen_units.UnitOfMeasure.UnitTag();
         Float64 tb_left =  m_pLeftBarrier->GetTrafficBarrierShape()->GetX2();
         Float64 tb_right = m_pRightBarrier->GetTrafficBarrierShape()->GetX2();

         gpPoint2d left = m_SlabLeftTop;
         gpPoint2d right = m_SlabRightTop;

         left.X()  += tb_left;
         right.X() -= tb_right;
         roadway_dimension.SetHookPoints(left,right);
         roadway_dimension.SetHorizontalDimensionPos(grDimension::Center);
         roadway_dimension.SetVerticalDimensionPos(grDimension::Above);
         roadway_dimension.SetSpaceFactor(1.0);
         roadway_dimension.SetLabel(strRoadwayDim.str());
      }
   }

   // set up world bounding box. This is a "chicken and egg" situation because
   // dimensions are scaled by both world and device coords.
   // bounding box of model
   gpRect2d box = m_DrawSectionShape.GetBoundingBox();

   // first need to set up a temporary mapper which is as close as we can get to the
   // final size. Then we can fine-tune.
   // don't try to draw dimensions if they take up too much screen space
   if (bShowDimensions)
   {
      gpRect2d tbox = box;
      LONG dim_hgt = girder_dimension.GetApproxVerticalHeight(hDC);
      Float64 factor = Float64(dim_hgt) / Float64(abs(rect.top-rect.bottom));
      if (factor>0.0 && factor<0.3)
      {
         Float64 tborder = tbox.Height();
         tborder *= .9/(1-factor);
         tbox.Bottom()-= tborder;

         mapper.SetWorldExt( tbox.Size() );
         mapper.SetWorldOrg( tbox.Center() );

         // get bounding box of dimensions only
         gpRect2d dim_box = girder_dimension.GetBoundingBox(hDC,mapper);
         dim_box.Union(left_overhang_dimension.GetBoundingBox(hDC,mapper));
         dim_box.Union(right_overhang_dimension.GetBoundingBox(hDC,mapper));
         dim_box.Union(roadway_dimension.GetBoundingBox(hDC,mapper));

         box.Union(dim_box);
      }
      else
      {
         bShowDimensions = false;
      }
   }

   // labels need extra room if no dimensions
   if (!bShowDimensions && bDrawLabels)
   {
      Float64 border = box.Height();
      border *= .25;
      box.Bottom() -= border;
   }

   // fine tune extents now that dimensions are accounted for
   mapper.SetWorldOrg( box.Center() );
   mapper.SetWorldExt( box.Size() );

// debugging code for rect bounds
//   grGraphTool::DrawRect(hDC,mapper,box,RGB(255,120,255));

   m_DrawSectionShape.Draw(hDC,mapper);

   // draw dimensions and labels after shape so they cover shape
   // dimensions
   if (bShowDimensions)
   {
      girder_dimension.Draw(hDC,mapper);
      left_overhang_dimension.Draw(hDC,mapper);
      right_overhang_dimension.Draw(hDC,mapper);
      roadway_dimension.Draw(hDC,mapper);
   }

   // girder labels
   UINT old_align = ::SetTextAlign( hDC, TA_TOP | TA_CENTER );
   HFONT font = grGraphTool::CreateRotatedFont(hDC, 0, 8);
   HGDIOBJ old_font = ::SelectObject(hDC, font);
   int old_bk = ::SetBkMode(hDC,TRANSPARENT);
   LONG dvx, dvy;
   if (bDrawLabels)
   {
      for(CollectionIndexType i=0; i<siz; i++)
      {
         CHECK(_CrtCheckMemory());

         std::_tstring message;
         message.erase();
         message = (TCHAR)(i) + _T('A');
         mapper.WPtoDP(m_GirderBottoms[i].X(),m_GirderBottoms[i].Y(), &dvx, &dvy);
         dvy+=1;
         ::TextOut( hDC, dvx, dvy, message.c_str(), (int)message.size() );
      }
   }

   ::SelectObject(hDC, old_font);
   ::SetTextAlign( hDC, old_align );
   ::DeleteObject(font);
   ::SetBkMode(hDC,old_bk);

   return true;
}

Float64 bmfBridge::GetPierStation(IDType pierId) const
{
   bmfPier* pPier = GetPier(pierId);
   return pPier->GetStation();
} // GetPierStation


void bmfBridge::GetPierBearing(PierIDType pierId,IDirection** ppBearing) const
{
   bmfPier* pPier = GetPier(pierId);
   pPier->GetBearing(ppBearing);
}

void bmfBridge::MovePier(PierIDType pier,Float64 station)
{
   bmfPier* pPier = GetPier(pier);
   pPier->Move(station);
} // MovePier

void bmfBridge::LayoutGirderPaths(SpanIDType spanId,
                               GirderIndexType nGirders,
                               Float64 spacing,
                               bmfMeasuredWhere where,
                               bmfMeasuredHow how)
{
   bmfSpan* pSpan = GetSpan(spanId);
   pSpan->LayoutGirderPaths(nGirders, spacing, where, how);
} // LayoutGirderLines

void bmfBridge::CreateGirder(SpanIDType spanId, bmfGirderTemplate* pTpl,GirderIndexType gdrPathIdx)
{
   bmfSpan* pSpan = GetSpan(spanId);
   pSpan->CreateGirder( pTpl, gdrPathIdx );
}

bmfGirder* bmfBridge::GetGirder(SpanIDType spanId,GirderIndexType gdrPathIdx)
{
   bmfSpan* pSpan = GetSpan( spanId );
   return pSpan->GetGirder( gdrPathIdx );
}

const bmfGirder* bmfBridge::GetGirder(SpanIDType spanId,GirderIndexType gdrPathIdx) const
{
   const bmfSpan* pSpan = GetSpan( spanId );
   return pSpan->GetGirder( gdrPathIdx );
}

void bmfBridge::Clear()
{
   // :TODO: 01.09.97 : Implement
   // :METHOD: bmfBridge::Clear()
   //
   // Implement this method.  Clear the entire bridge model back to c'tor status
#pragma Reminder("Implement")
} // Clear

//======================== ACCESS     =======================================
void bmfBridge::GetCogoModel(ICogoModel** ppModel)
{
   (*ppModel) = m_CogoModel;
   (*ppModel)->AddRef();
}

void bmfBridge::GetAlignment(IAlignment** ppAlignment)
{
   (*ppAlignment) = m_Alignment;
   (*ppAlignment)->AddRef();
}

Float64 bmfBridge::GetLength()
{
   Float64 length = 0;
   
   for (SpanIndexType span = 0; span < GetSpanCount(); span++)
   {
      bmfSpan* pSpan = GetSpan(span);
      length += pSpan->GetLength();
   }

   return length;
} // GetLength

Float64 bmfBridge::GetSpanLength(SpanIDType spanId)
{
   PRECONDITION(spanId == 0); // only single span bridges currently supported

   bmfSpan* pSpan = GetSpan(spanId);
   return pSpan->GetLength();
} // GetSpanLength

bmfPierLayout bmfBridge::GetPierLayout(PierIDType pier) const
{
   bmfPier* pPier = GetPier(pier);
   return pPier->GetLayout();
} // GetPierLocation

void bmfBridge::LayoutPier(PierIDType pierId,const bmfPierLayout& pl)
{
   bmfPier* pPier = GetPier(pierId);
   pPier->Layout(pl);
} // SetPierLayout

void bmfBridge::SetPierConnection(PierIDType pierId,const bmfConnection* pConnection)
{
   bmfPier* pPier = GetPier(pierId);
   pPier->SetConnection(pConnection);
} // SetPierConnection

GirderIndexType bmfBridge::GetGirderPathCount(SpanIDType spanId) const
{
   const bmfSpan* pSpan = GetSpan(spanId);
   return pSpan->GetGirderPathCount();
} // GetGirderLineCount

void bmfBridge::GetGirderPathLayout(SpanIDType spanId,
                                    GirderIndexType& nGirders,
                                    Float64& spacing,
                                    bmfMeasuredWhere& where,
                                    bmfMeasuredHow& how) const
{
   const bmfSpan* pSpan = GetSpan(spanId);
   pSpan->GetGirderPathLayout(nGirders,spacing,where,how);
} // GetGirderLineLayout

bmfSpanFactory* bmfBridge::SetSpanFactory(bmfSpanFactory* pFactory)
{
   bmfSpanFactory* pOldFactory = m_pSpanFactory.release();
   m_pSpanFactory = std::auto_ptr<bmfSpanFactory>( pFactory );
   return pOldFactory;
}

bmfPierFactory* bmfBridge::SetPierFactory(bmfPierFactory* pFactory)
{
   bmfPierFactory* pOldFactory = m_pPierFactory.release();
   m_pPierFactory = std::auto_ptr<bmfPierFactory>( pFactory );
   return pOldFactory;
}

//======================== INQUIRY    =======================================

#if defined _DEBUG
void bmfBridge::DumpGirder(SpanIDType spanId,GirderIndexType gdrPathIdx,LPCTSTR fname)
{
   std::_tofstream ofile( fname );

   if ( !fname )
      return;

   bmfSpan* pSpan = GetSpan( spanId );
   bmfGirder* pGirder = pSpan->GetGirder( gdrPathIdx );
   pGirder->Dump( ofile );

   ofile.close();
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void bmfBridge::MakeCopy(const bmfBridge& rOther)
{
   // :TODO: Implement
   CHECKX(false,_T("Copying of bmfBridge objects is not implemented"));
#pragma Reminder("Sink alignment events")
}

void bmfBridge::MakeAssignment(const bmfBridge& rOther)
{
   MakeCopy( rOther );
}

bmfBridge* bmfBridge::CreateClone() const
{
   return new bmfBridge( *this );
}

void bmfBridge::DoDrawPlanView(HDC hDC,const grlibPointMapper& mapper,
                               bool bLabelGirders, bool bLabelAlignment, 
                               bool bLabelPiers) const
{
   WATCHX( bmf, BMF_LEVEL_DRAW, _T("Drawing plan view of bridge") );

   WATCHX( bmf, BMF_LEVEL_DRAW, _T("Drawing piers") );
   PierContainer::const_iterator begin = m_Piers.begin();
   PierContainer::const_iterator end   = m_Piers.end();
   while ( begin != end )
   {
      const bmfPier* pier = (*begin++).second.get();
      pier->Draw( hDC, mapper, bLabelPiers );
   }

   WATCHX( bmf, BMF_LEVEL_DRAW, _T("Drawing spans") );
   SpanContainer::const_iterator start = m_Spans.begin();
   SpanContainer::const_iterator finish = m_Spans.end();
   while ( start != finish )
   {
      const bmfSpan* span = (*start++).second.get();
      span->PlanView( hDC, mapper, bLabelAlignment, bLabelGirders );
   }

   WATCHX( bmf, BMF_LEVEL_DRAW, _T("Drawing slab") );
   if ( m_pSlab.get() != 0 )
      m_pSlab->PlanView( hDC, mapper );

} // DoDraw

void bmfBridge::SetupSpan(bmfSpan* /*pSpan*/)
{
   // Allows the bridge to do any initialization of the span
   // Does nothing by default
} // SetupSpan

void bmfBridge::SetupPier(bmfPier* /*pPier*/)
{
   // Allows the bridge to do any initialization of the pier
   // Does nothing by default
} // SetupSpan

gpRect2d bmfBridge::GetBoundingBox() const
{
   bool first = true;;
   gpRect2d box;

   SpanContainer::const_iterator i;
   for ( i = m_Spans.begin(); i != m_Spans.end(); i++ )
   {
      const bmfSpan* p_span = (*i).second.get();
      if ( first )
      {
         box = p_span->GetBoundingBox();
         first = false;
      }
      else
      {
         box.Union( p_span->GetBoundingBox() );
      }
   }

   PierContainer::const_iterator begin = m_Piers.begin();
   PierContainer::const_iterator end   = m_Piers.end();
   while ( begin != end )
   {
      const bmfPier* p_pier = (*begin++).second.get();
      box.Union( p_pier->GetBoundingBox() );
   }

   if ( m_pSlab.get()!=0 )
      box.Union( m_pSlab->GetExtents() );

   return box;
} // GetExtents

void bmfBridge::OnAlignmentChanged()
{
   PierContainer::iterator current_pier = m_Piers.begin();
   while ( current_pier != m_Piers.end() )
   {
      bmfPier* pPier = (*current_pier++).second.get();
      pPier->OnAlignmentChanged();
   }

   SpanContainer::iterator current_span = m_Spans.begin();
   while ( current_span != m_Spans.end() )
   {
      bmfSpan* pSpan = (*current_span++).second.get();
      pSpan->OnAlignmentChanged();
   }

   if ( m_pSlab.get() != 0 )
      m_pSlab->OnAlignmentChanged();

   // update drawing model, but only after a station has been defined and the model
   // has been drawn at least once.
   if (m_HasShapeBeenBuilt)
   {
      BuildSectionShape(m_Station);
   }

   // Notify all bridge observers that the bridge has changed
   Notify( 0 );
}

//======================== ACCESS     =======================================

//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfBridge::StoreSpan(SpanIDType spanId,bmfSpan* pSpan)
{
   m_Spans.insert( SpanEntry(spanId,boost::shared_ptr<bmfSpan>(pSpan)) );
} // StoreSpan

void bmfBridge::StorePier(PierIDType pierId,bmfPier* pPier)
{
	m_Piers.insert( PierEntry(pierId,boost::shared_ptr<bmfPier>(pPier)) );
} // StoreSpan

// Data structure used in implement of BuildSectionShape
typedef struct WidthLoc
{
   Float64 TopWidth;
   gpPoint2d TopCenter;
} WidthLoc;

bool bmfBridge::BuildSectionShape(Float64 station) const
{
   // Builds a model of the cross section
   // Cross section is taken normal to the alignment at the
   // specified station.


   // empty out the shape
   m_DrawSectionShape.Clear();
   m_GirderBottoms.clear();

   // figure out which span we're in
   WATCHX( bmf, BMF_LEVEL_DRAW, _T("determining span at section") );
   const bmfSpan* pspan = GetSpanAtStation(station);
   CHECK(pspan);
   if (!pspan)
      return false;

   // get slab thickness and other values
   WATCHX( bmf, BMF_LEVEL_DRAW, _T("determining slab geometry") );
   // this check  will probably go away for non-slab bridges
   CHECK(m_pSlab.get());
   bool is_slab = m_pSlab.get()!=0;

   Float64 slab_thickness = (is_slab ? m_pSlab->GetGrossDepth() : 0.0);
   Float64 slab_overhang  = (is_slab ? m_pSlab->GetOverhang() : 0.0);
   Float64 slab_offset    = (is_slab ? m_pSlab->GetOffset() : 0.0);
   Float64 slab_overlay   = (is_slab ? m_pSlab->GetOverlayDepth() : 0.0);

   // point where top of slab and roadway centerline meet is origin
   CComPtr<IProfile> profile;
   m_Alignment->get_Profile(&profile);

   Float64 elev;
   profile->Elevation(CComVariant(station),0.00,&elev);
   gpPoint2d origin;
   origin.X() = 0;
   origin.Y() = elev;

   // cycle through girder paths to determine structure width and also
   // place girder shapes into composite.
   Float64 max_girder_loc = -Float64_Max;
   Float64 min_girder_loc = Float64_Max;
   GirderIndexType num_girds = pspan->GetGirderPathCount();

   // store girder top flange widths, girder location, in pairs
   // (top flange widths are adjusted for skew. On curved bridges
   //  the girder lines are not parallel to the alignment.  In section,
   //  the girders are skewed).
   typedef std::vector<WidthLoc>    WidthLocVector;
   WidthLocVector  gird_locs;

   // ==== build and add girder shapes
   for (GirderIndexType i = 0; i<num_girds; i++)
   {
      // offsets from alignment.
      Float64 girder_offset = pspan->GetGirderPathOffset(i, station); // this is normal to alignment
      max_girder_loc = max(max_girder_loc, girder_offset);
      min_girder_loc = min(min_girder_loc, girder_offset);

      // Get top of slab elevation directly above this girder
      profile->Elevation(CComVariant(station),girder_offset,&elev);
      Float64 top_girder_y = elev - slab_offset;

      // Get some girder template imformation
      const bmfGirder* pgird          = pspan->GetGirder(i);
      const bmfGirderTemplate* ptempl = pgird->GetTemplate();

      // Get the girder section and the top flange width. store to use
      // in slab creation later.
      // First need to determine location of station in girder coords
      const bmfGirderPath* ppath = pgird->GetGirderPath();
      Float64 girder_length = ppath->Length();
      Float64 end_dist = ppath->EndDistanceFromStation(station);

      // create a girder shape and add it's shape to the composite.
      const bmfGirderProfile* pprofile = ptempl->GetProfile();
      std::auto_ptr<gmIShape> pshape( pprofile->CreateShape(end_dist,girder_length) );

      // Skew of girders with respect to the normal to the alignment
      CComPtr<IAngle> skew;
      ppath->GetSectionSkew(station,&skew);

      bool fill_girder=true;
      // make sure a section is here. If the skew is large, it may not be.
      if (end_dist>=0 && end_dist<=girder_length)
      {
         std::auto_ptr<bmfIGirderSection> apsect(pgird->CreateGirderSection(end_dist));
         Float64 top_width = apsect->GetTopWidth();

         // Adjust for skew angle
         Float64 valSkew;
         skew->get_Value(&valSkew);
         top_width /= fabs( cos(valSkew) );

         WidthLoc wl;
         wl.TopWidth = top_width;
         wl.TopCenter = gpPoint2d(girder_offset, top_girder_y);
         gird_locs.push_back(wl);
      }
      else
      {
         fill_girder = false;
      }

//      // clone the shape, color it, and move it to the correct location
//      std::auto_ptr<gmIShape> apshape(pshape->CreateClone());
//
//      // Create a skew adjusted cross section
//
//      // NOTE:
//      // I'm probably killing the generallity of this method
//      // but I've got to get some work done!
//      gmIPrecastBeam* pBeam = dynamic_cast<gmIPrecastBeam*>(apshape.get());
//      std::auto_ptr<gmIPrecastBeam> pClone( dynamic_cast<gmIPrecastBeam*>(pBeam->CreateClone()) );
//      pClone->SetFillColor(girder_fill_color);
//      pClone->SetBorderColor(girder_border_color);
//      pClone->EnableFillMode(fill_girder);
      pshape->SetFillColor(girder_fill_color);
      pshape->SetBorderColor(girder_border_color);
      pshape->EnableFillMode(fill_girder);

#pragma Reminder("Need to adjust horizontal dimensions for skew")

      gpPoint2d gird_loc(girder_offset, top_girder_y);
//      pClone->Move(gmIShape::TopCenter, gird_loc);
      pshape->Move(gmIShape::TopCenter, gird_loc);
      //beam.Move(gmIShape::TopCenter, gird_loc);

      // save bottom location of girder
      m_GirderBottoms.push_back( pshape->GetBoundingBox().BottomCenter());
      m_DrawSectionShape.AddShape(*pshape);
   }

   if (is_slab)
   {
      // ==== build slab - start at left top and go CCW
      Float64 y_slab_top      = origin.Y();
      Float64 y_slab_bottom   = y_slab_top - slab_thickness;
      Float64 x_slab_left     = -m_pSlab->GetWidth()/2;
      Float64 y_slab_left;
      profile->Elevation(CComVariant(station),x_slab_left,&y_slab_left);
      Float64 x_slab_right    = m_pSlab->GetWidth()/2;
      Float64 y_slab_right;
      profile->Elevation(CComVariant(station),x_slab_right,&y_slab_right);
      Float64 y_haunch_bottom = y_slab_top - slab_offset;

      // The basic slab has 6 points
      // A = Top of slab at crown point
      // B = Top of slab at left edge
      // C = Bottom of slab at left edge
      // D = Bottom of slab at crown point
      // E = Bottom of slab at right edge
      // F = Top of slab at right edge


      // store point for dimensioning later
      m_SlabLeftTop.Move(x_slab_left, y_slab_left);
      m_SlabRightTop.Move(x_slab_right, y_slab_right);

      gmPolygon slab_shape;

      // Point A
      slab_shape.AddPoint(origin);

      // Point B
      slab_shape.AddPoint( gpPoint2d(x_slab_left,y_slab_left) );

      // Point C
      slab_shape.AddPoint( gpPoint2d(x_slab_left,y_slab_left - slab_thickness) );

      // bottom of slab - draw haunches if an offset exists
      if (!IsZero(slab_offset))
      {
         Int32 gdrIdx = 0;
         for (WidthLocVector::iterator ig=gird_locs.begin(); ig!=gird_locs.end(); ig++)
         {
            // four points for each girder location ____1  4____
            // per mating surface                       |__|
            //                                          2  3
            //
            gpPoint2d top_center = ig->TopCenter;

            // NOTE: This is a bit of a "hack". The bridge model should probably have a
            //       generic bridge beam shape (not gmIShape). Casting to gmIPrecastBeam
            //       assumes that all beams are going to be precast which is not the case.
            //       However, there are two factors that need to be considered here.
            //       First, a new bridge modeling framework is going to be built. This
            //       framework will be more general and flexible. Second, this "draw me"
            //       method is also a "hack" so a hack in a hack is still just a hack.
            const bmfGirder* pgird = pspan->GetGirder(gdrIdx++);
            const bmfGirderTemplate* ptempl = pgird->GetTemplate();
            const bmfGirderProfile* pprofile = ptempl->GetProfile();

            const bmfGirderPath* ppath = pgird->GetGirderPath();
            Float64 girder_length = ppath->Length();
            Float64 end_dist = ppath->EndDistanceFromStation(station);
            
            std::auto_ptr<gmIShape> pshape( pprofile->CreateShape(end_dist,girder_length) );
            const gmIPrecastBeam* pBeam = dynamic_cast<const gmIPrecastBeam*>(pshape.get());

            CollectionIndexType nMatingSurfaces = pBeam->GetNumberOfMatingSurfaces();
            for ( CollectionIndexType j = 0; j < nMatingSurfaces; j++ )
            {
               Float64 loc = pBeam->GetMatingSurfaceLocation(j); // location relative to center of beam
               Float64 width = pBeam->GetMatingSurfaceWidth(j);

               Float64 x12 = top_center.X() + loc - width/2;
               Float64 x34 = top_center.X() + loc + width/2;
               Float64 el12;
               profile->Elevation(CComVariant(station),x12,&el12);
               Float64 el34;
               profile->Elevation(CComVariant(station),x34,&el34);

               gpPoint2d tmpnt;

               if ( ig != gird_locs.begin() || j != 0 )
               {
                  tmpnt.X() = x12;
                  tmpnt.Y() = el12-slab_thickness;
                  slab_shape.AddPoint(tmpnt); // 1
               }

               tmpnt.X() = x12;
               tmpnt.Y() = top_center.Y();
               slab_shape.AddPoint(tmpnt); // 2

               tmpnt.X() = x34;
               tmpnt.Y() = top_center.Y();
               slab_shape.AddPoint(tmpnt); // 3

               if ( ig != gird_locs.end()-1 || j != nMatingSurfaces-1)
               {
                  tmpnt.X() = x34;
                  tmpnt.Y() = el34-slab_thickness;
                  slab_shape.AddPoint(tmpnt); // 4
               }
            }
         }
      }


      // Point D
      // slab_shape.AddPoint( gpPoint2d( origin.X(), origin.Y() - slab_thickness) );

      // Point E
      slab_shape.AddPoint( gpPoint2d(x_slab_right, y_slab_right - slab_thickness) );

      // Point F
      slab_shape.AddPoint( gpPoint2d(x_slab_right, y_slab_right) );

      // Close the shape
      slab_shape.AddPoint(origin);

      // color the shape and add it to the composite
      slab_shape.SetFillColor(slab_fill_color);
      slab_shape.SetBorderColor(slab_border_color);
      slab_shape.EnableFillMode(true);

      m_DrawSectionShape.AddShape(slab_shape);

      // ==== build slab overlay shape and add to composite
      if (slab_overlay>0)
      {
         // Overlays are created using the same basic 6 points as the
         // main slab

         gmPolygon overlay_shape;

         // Point A
         overlay_shape.AddPoint(gpPoint2d(origin.X(),origin.Y()+slab_overlay));

         // Point B
         overlay_shape.AddPoint(gpPoint2d(x_slab_left,y_slab_left+slab_overlay));

         // Point C
         overlay_shape.AddPoint(gpPoint2d(x_slab_left,y_slab_left));

         // Point D
         overlay_shape.AddPoint(gpPoint2d(origin.X(),origin.Y()));

         // Point E
         overlay_shape.AddPoint(gpPoint2d(x_slab_right,y_slab_right));

         // Point F
         overlay_shape.AddPoint(gpPoint2d(x_slab_right,y_slab_right+slab_overlay));

         // Close the shape
         overlay_shape.AddPoint(gpPoint2d(origin.X(),origin.Y()+slab_overlay));

         overlay_shape.SetFillColor(overlay_fill_color);
         overlay_shape.SetBorderColor(overlay_border_color);
         overlay_shape.EnableFillMode(true);

         m_DrawSectionShape.AddShape(overlay_shape);
      }

      // ==== build barrier shapes and add to composite
      // left
      const bmfTrafficBarrier* pbar_left = GetLeftTrafficBarrier();
      if (pbar_left !=0)
      {
         gmTrafficBarrier bar_shape = *(pbar_left->GetTrafficBarrierShape());
         bar_shape.SetFillColor(barrier_fill_color);
         bar_shape.SetBorderColor(barrier_border_color);
         bar_shape.EnableFillMode(true);
         gpPoint2d hp = bar_shape.GetHookPoint();
         bar_shape.Move(hp, gpPoint2d(x_slab_left, y_slab_left));
         m_DrawSectionShape.AddShape(bar_shape);
      }

      // right
      const bmfTrafficBarrier* pbar_right = GetRightTrafficBarrier();
      if (pbar_left !=0)
      {
         gmTrafficBarrier bar_shape = *(pbar_right->GetTrafficBarrierShape());
         bar_shape.SetFillColor(barrier_fill_color);
         bar_shape.SetBorderColor(barrier_border_color);
         bar_shape.EnableFillMode(true);
         gpPoint2d hp = bar_shape.GetHookPoint();
         bar_shape.Move(hp, gpPoint2d(x_slab_right, y_slab_right));
         m_DrawSectionShape.AddShape(bar_shape);
      }
   }

   m_HasShapeBeenBuilt = true;
   return true;
}


//======================== ACCESS     =======================================
//======================== INQUERY ==========================================

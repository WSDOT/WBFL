///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2013  Washington State Department of Transportation
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

// SectionCutTool.cpp : Implementation of CSectionCutTool
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "SectionCutTool.h"
#include "BridgeGeometryTool.h"
#include "EffectiveFlangeWidthTool.h"
#include "Helpers.h"
#include <WBFLGeometry.h>
#include <MathEx.h>
#include <float.h> // for DBL_MAX

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSectionCutTool
HRESULT CSectionCutTool::FinalConstruct()
{
   CComObject<CEffectiveFlangeWidthTool>* pTool;
   HRESULT hr = CComObject<CEffectiveFlangeWidthTool>::CreateInstance(&pTool);
   if ( FAILED(hr) || pTool == NULL )
      return E_FAIL;

   m_EffFlangeTool = pTool;


   CComObject<CBridgeGeometryTool>* pBGTool;
   hr = CComObject<CBridgeGeometryTool>::CreateInstance(&pBGTool);
   if ( FAILED(hr) || pBGTool == NULL )
      return E_FAIL;

   m_BridgeGeometryTool = pBGTool;

   return S_OK;
}

void CSectionCutTool::FinalRelease()
{
   m_EffFlangeTool.Release();
   m_BridgeGeometryTool.Release();
}

STDMETHODIMP CSectionCutTool::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISectionCutTool
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSectionCutTool::CreateLeftBarrierShape(IGenericBridge* bridge,Float64 station,IShape** shape)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(shape);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   CComPtr<IProfile> profile;
   alignment->get_Profile(&profile);

   // Get Left top point of deck
   Float64 Left_deck_offset; // distance from alignment to Left edge of deck
   m_BridgeGeometryTool->DeckOffset(bridge,station,NULL,qcbLeft,&Left_deck_offset);

   Float64 elev;
   profile->Elevation(CComVariant(station),Left_deck_offset,&elev);

   CComPtr<ISidewalkBarrier> barrier;
   bridge->get_LeftBarrier(&barrier);

   CComPtr<IShape> barrier_shape;
   barrier->get_Shape(&barrier_shape);

   barrier_shape->Clone(shape);

   CComQIPtr<IXYPosition> position(*shape);
   position->Offset(Left_deck_offset, elev);

   return S_OK;
}

STDMETHODIMP CSectionCutTool::CreateRightBarrierShape(IGenericBridge* bridge,Float64 station,IShape** shape)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(shape);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   CComPtr<IProfile> profile;
   alignment->get_Profile(&profile);

   // Get right top point of deck
   Float64 right_deck_offset; // distance from alignment to right edge of deck
   m_BridgeGeometryTool->DeckOffset(bridge,station,NULL,qcbRight,&right_deck_offset);

   Float64 elev;
   profile->Elevation(CComVariant(station),right_deck_offset,&elev);

   CComPtr<ISidewalkBarrier> barrier;
   bridge->get_RightBarrier(&barrier);

   CComPtr<IShape> barrier_shape;
   barrier->get_Shape(&barrier_shape);

   barrier_shape->Clone(shape);

   CComQIPtr<IXYPosition> position(*shape);
   position->Offset(right_deck_offset,elev);

   return S_OK;
}

STDMETHODIMP CSectionCutTool::CreateLeftBarrierSection(IGenericBridge* bridge,Float64 station,VARIANT_BOOL bStructuralOnly,ISection** section)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(section);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   CComPtr<IProfile> profile;
   alignment->get_Profile(&profile);

   // Get left top point
   Float64 left_deck_offset; // distance from alignment to left edge of deck
   m_BridgeGeometryTool->DeckOffset(bridge,station,NULL,qcbLeft,&left_deck_offset);

   Float64 elev;
   profile->Elevation(CComVariant(station),left_deck_offset,&elev);

   CComPtr<ISidewalkBarrier> left_barrier;
   bridge->get_LeftBarrier(&left_barrier);

   if ( left_barrier == NULL )
   {
      *section = NULL;
      return S_FALSE;
   }

   CComPtr<ISidewalkBarrier> barrier;
   left_barrier->Clone(&barrier);

   // returns the whole railing system shape including sidewalk and interior railing
   CComPtr<IShape> shape;
   if ( bStructuralOnly == VARIANT_TRUE )
      barrier->get_StructuralShape(&shape);
   else
      barrier->get_Shape(&shape);


   if ( !shape )
   {
      *section = NULL;
      return S_FALSE;
   }

   CComQIPtr<IXYPosition> position(shape);
   position->Offset(left_deck_offset,elev);

   // use material for exterior barrier as materior for entire section
   CComPtr<IBarrier> ext_barrier;
   barrier->get_ExteriorBarrier(&ext_barrier);

   CComPtr<IMaterial> material;
   ext_barrier->get_Material(&material);

   Float64 E,density;
   material->get_E(0,&E);
   material->get_Density(0,&density);

   CComPtr<ICompositeSectionItemEx> sectionItem;
   sectionItem.CoCreateInstance(CLSID_CompositeSectionItemEx);
   sectionItem->putref_Shape(shape);
   sectionItem->put_Efg(E);
   sectionItem->put_Ebg(0.0);
   sectionItem->put_Dfg(density);
   sectionItem->put_Dbg(0.0);
   sectionItem->put_Structural(VARIANT_TRUE);


   CComPtr<ICompositeSectionEx> compSection;
   compSection.CoCreateInstance(CLSID_CompositeSectionEx);
   compSection->AddSectionEx(sectionItem);

   compSection.QueryInterface(section);

   return S_OK;
}

STDMETHODIMP CSectionCutTool::CreateRightBarrierSection(IGenericBridge* bridge,Float64 station,VARIANT_BOOL bStructuralOnly,ISection** section)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(section);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   CComPtr<IProfile> profile;
   alignment->get_Profile(&profile);

   // Get right top point
   Float64 right_deck_offset; // distance from alignment to right edge of deck
   m_BridgeGeometryTool->DeckOffset(bridge,station,NULL,qcbRight,&right_deck_offset);

   Float64 elev;
   profile->Elevation(CComVariant(station),right_deck_offset,&elev);

   CComPtr<ISidewalkBarrier> right_barrier;
   bridge->get_RightBarrier(&right_barrier);

   if ( right_barrier == NULL )
   {
      *section = NULL;
      return S_FALSE;
   }

   CComPtr<ISidewalkBarrier> barrier;
   right_barrier->Clone(&barrier);

   // returns the whole railing system shape including sidewalk and interior railing
   CComPtr<IShape> shape;
   if ( bStructuralOnly == VARIANT_TRUE )
      barrier->get_StructuralShape(&shape);
   else
      barrier->get_Shape(&shape);

   if ( !shape )
   {
      *section = NULL;
      return S_FALSE;
   }

   CComQIPtr<IXYPosition> position(shape);
   position->Offset(right_deck_offset,elev);

   // use material for exterior barrier as materior for entire section
   CComPtr<IBarrier> ext_barrier;
   barrier->get_ExteriorBarrier(&ext_barrier);

   CComPtr<IMaterial> material;
   ext_barrier->get_Material(&material);

   Float64 E,density;
   material->get_E(0,&E);
   material->get_Density(0,&density);

   CComPtr<ICompositeSectionItemEx> sectionItem;
   sectionItem.CoCreateInstance(CLSID_CompositeSectionItemEx);
   sectionItem->putref_Shape(shape);
   sectionItem->put_Efg(E);
   sectionItem->put_Ebg(0);
   sectionItem->put_Dfg(density);
   sectionItem->put_Dbg(0);
   sectionItem->put_Structural(VARIANT_TRUE);

   CComPtr<ICompositeSectionEx> compSection;
   compSection.CoCreateInstance(CLSID_CompositeSectionEx);
   compSection->AddSectionEx(sectionItem);

   compSection.QueryInterface(section);

   return S_OK;
}

STDMETHODIMP CSectionCutTool::CreateSlabShape(IGenericBridge* bridge,Float64 station,IShape** shape)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(shape);

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);
   CComPtr<IPier> pier;
   piers->get_Item(0,&pier);

   CComPtr<IStation> pier_station;
   pier->get_Station(&pier_station);

   Float64 start_station;
   pier_station->get_Value(&start_station);

   PierIndexType nPiers;
   piers->get_Count(&nPiers);
   SpanIndexType nSpans = SpanIndexType(nPiers-1);

   Float64 distFromStart = station - start_station;
   distFromStart = (IsZero(distFromStart) ? 0.0 : distFromStart);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   CComPtr<IProfile> profile;
   alignment->get_Profile(&profile);

   CComPtr<IPier> prev_pier;
   for ( PierIndexType pierIdx = 0; pierIdx < nPiers-1; pierIdx++ )
   {
      prev_pier.Release();
      piers->get_Item(pierIdx,&prev_pier);

      CComPtr<IStation> objPrevPierStation;
      prev_pier->get_Station(&objPrevPierStation);

      Float64 prev_pier_station;
      objPrevPierStation->get_Value(&prev_pier_station);

      if ( prev_pier_station < station )
      {
         break; // previous pier found
      }
   }
   pier_station.Release();
   prev_pier->get_Station(&pier_station);
   Float64 prev_pier_station;
   pier_station->get_Value(&prev_pier_station);
   Float64 distFromStartOfSpan = station - prev_pier_station;
   distFromStartOfSpan = (IsZero(distFromStartOfSpan) ? 0.0 : distFromStartOfSpan);

   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   CComQIPtr<ICastSlab> cip(deck);
   CComQIPtr<IPrecastSlab> sip(deck);
   CComQIPtr<IOverlaySlab> overlay(deck);
   ATLASSERT(cip != NULL || sip != NULL || overlay != NULL);

   // The basic slab has 5 points
   // A = Top of slab at crown point
   // B = Top of slab at left edge
   // C = Bottom of slab at left edge
   // ... haunches along bottom of slab ...
   // E = Bottom of slab at right edge
   // F = Top of slab at right edge
   CComPtr<IPolyShape> slab_shape;
   slab_shape.CoCreateInstance(CLSID_PolyShape);

   Float64 left_deck_offset; // distance from alignment to left edge of deck
   m_BridgeGeometryTool->DeckOffset(bridge,station,NULL,qcbLeft,&left_deck_offset);

   Float64 right_deck_offset; // distance from alignment to right edge of deck
   m_BridgeGeometryTool->DeckOffset(bridge,station,NULL,qcbRight,&right_deck_offset);

   // Point A - Crown Point
   CComPtr<IPoint2d> A;
   A.CoCreateInstance(CLSID_Point2d);
   
   Float64 elev;
   Float64 cpo;
   profile->CrownPointOffset(CComVariant(station),&cpo);

   // if crown point isn't between left and right edge of deck,
   // force it onto the deck
   Float64 crown_point = ForceIntoRange(left_deck_offset,cpo,right_deck_offset);

   profile->Elevation(CComVariant(station),crown_point,&elev);

   A->Move(crown_point,elev);
   slab_shape->AddPointEx(A);

   // Point B - Left Edge, Top
   Float64 gross_depth;
   deck->get_GrossDepth(&gross_depth);

   profile->Elevation(CComVariant(station),left_deck_offset,&elev);
   CComPtr<IPoint2d> B;
   B.CoCreateInstance(CLSID_Point2d);
   B->Move(left_deck_offset,elev);
   slab_shape->AddPointEx(B);

   // Point C - Left Edge, Bottom
   Float64 fillet;
   Float64 overhang_depth;
   DeckOverhangTaper overhang_taper;
   if ( cip )
   {
      cip->get_OverhangDepth(&overhang_depth);
      cip->get_OverhangTaper(&overhang_taper);
      cip->get_Fillet(&fillet);
   }
   else if ( sip )
   {
      sip->get_OverhangDepth(&overhang_depth);
      sip->get_OverhangTaper(&overhang_taper);
      sip->get_Fillet(&fillet);
   }
   else
   {
      overhang_depth = gross_depth;
      overhang_taper = dotNone;
      fillet = 0.0;
   }

   Float64 left_slope;
   profile->CrownSlope(CComVariant(station),left_deck_offset,&left_slope);
   left_slope *= ::BinarySign(cpo - left_deck_offset);

   CComPtr<IPoint2d> C;
   C.CoCreateInstance(CLSID_Point2d);
   C->Move(left_deck_offset - left_slope*overhang_depth,elev - overhang_depth);
   slab_shape->AddPointEx(C);

   // get right crown slope now because we are going to need it when creating the
   // haunches
   Float64 right_slope;
   profile->CrownSlope(CComVariant(station),right_deck_offset,&right_slope);
   right_slope *= ::BinarySign(right_deck_offset - cpo);

#pragma Reminder("UPDATE: Need to fix the implementation so the slab haunch is drawn correctly")
   // there is still problems when the bridge is skewed and the cut location has girders in different spans

   // Haunches along bottom of slab
   // haunch is defined by 6 points per mating surface
   //
   //    --------1\      /6------
   //             2      5
   //             |      |
   //             3------4
   //
   CComPtr<IFilteredSuperstructureMemberCollection> members;
   bridge->get_SuperstructureMembersAtStation(station,&members);

   GirderIndexType nGirders;
   members->get_Count(&nGirders);
   for ( GirderIndexType girderIdx = 0; girderIdx < nGirders; girderIdx++ )
   {
      CComPtr<ISuperstructureMember> ssmbr;
      members->get_Item(girderIdx,&ssmbr);

      GirderIDType ssmbrID;
      ssmbr->get_ID(&ssmbrID);

      CComPtr<ISegment> firstSegment;
      ssmbr->get_Segment(0,&firstSegment);

      CComPtr<IGirderLine> firstGirderLine;
      firstSegment->get_GirderLine(&firstGirderLine);

      CComPtr<IPierLine> firstPierLine;
      firstGirderLine->get_StartPier(&firstPierLine);

      CComPtr<IStation> firstStation;
      firstPierLine->get_Station(&firstStation);

      Float64 firstStationValue;
      firstStation->get_Value(&firstStationValue);

      Float64 distFromStartOfSSMbr = station - firstStationValue;

      SegmentIndexType segIdx;
      CComPtr<ISegment> segment;
      Float64 dist_along_segment;
      ssmbr->GetDistanceFromStartOfSegment(distFromStartOfSSMbr,&dist_along_segment,&segIdx,&segment);

      if ( segIdx == INVALID_INDEX || segment == NULL )
         continue;

      // orientation of girder in radians... 0 = plumb, rotated CW is +
      Float64 orientation;
      segment->get_Orientation(&orientation);

      CComPtr<IShape> girder_shape;
      segment->get_PrimaryShape(dist_along_segment,&girder_shape);

      CComQIPtr<IGirderSection> girder_section(girder_shape);

      Float64 min_top_flange_thickness = 0;
      FlangeIndexType nTopFlanges;
      girder_section->get_TopFlangeCount(&nTopFlanges);
      if ( nTopFlanges != 0 )
         girder_section->get_MinTopFlangeThickness(&min_top_flange_thickness);

      //SpanIndexType spanIdx;
      //Float64 spanDist;

      //// get the span index for this girder point
      //m_BridgeGeometryTool->GirderLinePoint(bridge,distFromStart,girderIdx,&spanIdx,&spanDist);

      //// if this points is off the bridge, use the index of the first/last span
      //if ( spanIdx == INVALID_INDEX )
      //{
      //   spanIdx = 0;
      //}
      //else if ( spanIdx == -2 )
      //{
      //   ATLASSERT(false); // how can span index == -2?
      //   spanIdx = nSpans-1;
      //}

      //// girder is in a different span then where the section cut is taken
      //// (probably because of skews)
      //SpanIndexType idx;
      //span->get_Index(&idx);
      //if ( idx != spanIdx )
      //{
      //   // make sure that span has enough girders... if not, continue
      //   CComPtr<ISpanCollection> spans;
      //   CComPtr<ISpan> span_with_girderline_point;
      //   bridge->get_Spans(&spans);
      //   spans->get_Item(spanIdx,&span_with_girderline_point);
      //   GirderIndexType nGirdersThisSpan;
      //   span_with_girderline_point->get_GirderCount(&nGirdersThisSpan);
      //   if ( nGirdersThisSpan <= girderIdx )
      //      continue; // not enough girders
      //}

      // get offset of CL girder from CL alignment ( < 0 means left of CL alignment )
      Float64 girder_offset;
      m_BridgeGeometryTool->GirderPathOffset(bridge,ssmbrID,segIdx,CComVariant(station),&girder_offset);

      //Float64 location;
      //SpanIndexType span_index;
      //m_BridgeGeometryTool->GirderLinePoint(bridge,distFromStart,girderIdx,&span_index,&location);

      //if (span_index == INVALID_INDEX) // this girder point is before/after the limits of the bridge (typically happens with skews)
      //   continue; // go to the next girder

      Float64 haunch = 0;
      segment->GetHaunchDepth(dist_along_segment,&haunch);

      Float64 elclg; // elevation at CL of girder
      profile->Elevation(CComVariant(station),girder_offset,&elclg);

      MatingSurfaceIndexType nMatingSurfaces;
      girder_section->get_MatingSurfaceCount(&nMatingSurfaces);
      for ( CollectionIndexType msIdx = 0; msIdx < nMatingSurfaces; msIdx++ )
      {
         Float64 ms_width;
         girder_section->get_MatingSurfaceWidth(msIdx,&ms_width);

         Float64 ms_location; // relative to center of beam
         girder_section->get_MatingSurfaceLocation(msIdx,&ms_location);

         Float64 x23; // x location of points 2 & 3
         Float64 x45; // x location of points 4 & 5
         Float64 xcl; // x location of centerline of flange
         xcl = girder_offset + ms_location;
         x23 = xcl - ms_width/2;
         x45 = xcl + ms_width/2;

         if ( InRange(left_deck_offset,x23,right_deck_offset) && InRange(left_deck_offset,x45,right_deck_offset))
         {
            Float64 el23; // deck elevation above points 2 & 3
            Float64 el45; // deck elevation above points 4 & 5
            Float64 elcl; // deck elevation above centerline of flange
            profile->Elevation(CComVariant(station),x23,&el23);
            profile->Elevation(CComVariant(station),x45,&el45);
            profile->Elevation(CComVariant(station),xcl,&elcl);

            Float64 el3; // top of girder elevation on left side of flange (point 3)
            el3 = elclg - gross_depth - haunch - (ms_location - ms_width/2)*sin(orientation);

            Float64 el4; // top of girder elevation on right side of flange (point 4)
            el4 = elclg - gross_depth - haunch - (ms_location + ms_width/2)*sin(orientation);

            if ( girderIdx != 0 || msIdx != 0 || overhang_taper == dotNone || overhang_taper == dotBottomTopFlange )
            {
               // only use this point if this is an interior girder or an interior web
               // on the first girder, or the deck overhang is not tapered
               Float64 dy;
               Float64 dx;
               if (girderIdx != 0 || msIdx != 0)
               {
                  // not exterior girder, or exterior web of exterior girder
                  dy = gross_depth;
                  dx = 0;
               }
               else
               {
                  if ( overhang_taper == dotNone )
                  {
                     dy = overhang_depth;
                     dx = 0;
                  }
                  else
                  {
                     dy = gross_depth + haunch - (elcl-el23) + min_top_flange_thickness; // slab overhang to bottom of girder top flange
                     dx = left_slope*min_top_flange_thickness;
                  }
               }
               slab_shape->AddPoint(x23-dx-fillet,el23-dy); // 1
               slab_shape->AddPoint(x23-dx,el23-dy-fillet); // 2
            }

            slab_shape->AddPoint(x23,el3); // 3
            slab_shape->AddPoint(x45,el4); // 4

            if ( girderIdx != nGirders-1 || msIdx != nMatingSurfaces-1 || overhang_taper == dotNone || overhang_taper == dotBottomTopFlange)
            {
               // only use this point if this is an interior girder or an interior web
               // on the last girder, or the deck overhang is not tapered
               Float64 dy;
               Float64 dx;
               if ( girderIdx != nGirders-1 || msIdx != nMatingSurfaces-1)
               {
                  // not exterior girder, or exterior web of exterior girder
                  dy = gross_depth;
                  dx = 0;
               }
               else
               {
                  if ( overhang_taper == dotNone )
                  {
                     dy = overhang_depth;
                     dx = 0;
                  }
                  else
                  {
                     dy = gross_depth + haunch - (elcl-el45) + min_top_flange_thickness; // slab overhang to bottom of girder top flange
                     dx = right_slope*min_top_flange_thickness;
                  }
               }
               slab_shape->AddPoint(x45+dx,el45-dy-fillet); // 5
               slab_shape->AddPoint(x45+dx+fillet,el45-dy); // 6
            }
         }
      }
   }

   // Point E - Right Edge, Bottom
   profile->Elevation(CComVariant(station),right_deck_offset,&elev);
   CComPtr<IPoint2d> E;
   E.CoCreateInstance(CLSID_Point2d);
   E->Move(right_deck_offset + right_slope*overhang_depth,elev-overhang_depth);
   slab_shape->AddPointEx(E);

   // Point F - Right Edge, Top
   CComPtr<IPoint2d> F;
   F.CoCreateInstance(CLSID_Point2d);
   F->Move(right_deck_offset,elev);
   slab_shape->AddPointEx(F);

   slab_shape.QueryInterface(shape);

   return S_OK;
}


STDMETHODIMP CSectionCutTool::putref_EffectiveFlangeWidthTool(IEffectiveFlangeWidthTool* pTool)
{
   CHECK_IN(pTool);
   m_EffFlangeTool = pTool;
   return S_OK;
}

STDMETHODIMP CSectionCutTool::get_EffectiveFlangeWidthTool(IEffectiveFlangeWidthTool* *pTool)
{
   CHECK_RETOBJ(pTool);
   (*pTool) = m_EffFlangeTool;
   (*pTool)->AddRef();
   return S_OK;
}

STDMETHODIMP CSectionCutTool::CreateGirderSectionBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 distFromStartOfSSMbr,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section)
{
   CComPtr<ISuperstructureMember> ssMbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssMbr);

   Float64 distFromStartOfSegment;
   SegmentIndexType segIdx;
   CComPtr<ISegment> segment;
   ssMbr->GetDistanceFromStartOfSegment(distFromStartOfSSMbr,&distFromStartOfSegment,&segIdx,&segment);

   return CreateGirderSectionBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,stageIdx,sectionPropMethod,section);
}

STDMETHODIMP CSectionCutTool::CreateGirderSectionBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section)
{
   // Validate input
   CHECK_RETOBJ(section);
   CHECK_IN(bridge);

   return CreateCompositeSection(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,stageIdx,sectionPropMethod,section);
}

STDMETHODIMP CSectionCutTool::CreateNetDeckSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,ISection** section)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(section);

   return CreateDeckSection(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,stageIdx,spmNet,section);
}

STDMETHODIMP CSectionCutTool::CreateBridgeSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,StageIndexType stageIdx,BarrierSectionCut bsc,ISection** section)
{
   // location is measured along the alignment, from the station of the first pier. The section cut is made
   // normal to the alignment.
   HRESULT hr = S_OK;
   
   Float64 bottom_deck_elevation = -DBL_MAX;

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IPier> first_pier;
   piers->get_Item(0,&first_pier);

   CComPtr<IStation> station;
   first_pier->get_Station(&station);

   Float64 first_pier_station;
   station->get_Value(&first_pier_station);

   Float64 target_station = first_pier_station + distFromStartOfBridge;

   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   // Need to determine span,girder,location along each girder line so we can call CreateNoncompositeSection correctly
   CComPtr<ICompositeSectionEx> bridge_section;
   bridge_section.CoCreateInstance(CLSID_CompositeSectionEx);

   CComPtr<IEnumSuperstructureMembers> enumSSMbrs;
   bridge->get__EnumSuperstructureMembers(&enumSSMbrs);
   CComPtr<ISuperstructureMember> ssMbr;
   while ( enumSSMbrs->Next(1,&ssMbr,NULL) != S_FALSE )
   {
      GirderIDType ssMbrID;
      ssMbr->get_ID(&ssMbrID);

      SegmentIndexType nSegments;
      ssMbr->get_SegmentCount(&nSegments);
      for ( SegmentIndexType segIdx = 0; segIdx < nSegments; segIdx++ )
      {
         CComPtr<ISegment> segment;
         ssMbr->get_Segment(segIdx,&segment);

         CComPtr<IGirderLine> girderLine;
         segment->get_GirderLine(&girderLine);

         // get station range for segment
         // can't use pier stations because they don't account for skew and offset from alignment
         
         // get the end points of the line
         CComPtr<IPoint2d> pntStart, pntEnd;
         girderLine->get_PierPoint(etStart,&pntStart);
         girderLine->get_PierPoint(etEnd,  &pntEnd);
   
         // get the station and offsets
         Float64 startStation, endStation;
         Float64 offset;
         station.Release();
         alignment->Offset(pntStart,&station,&offset);
         station->get_Value(&startStation);
         station.Release();
         alignment->Offset(pntEnd,&station,&offset);
         station->get_Value(&endStation);

         if ( ::InRange(startStation,target_station,endStation) )
         {
            Float64 dist_from_start_of_segment = target_station - startStation;

            // Create a noncomposite section for the segment that is being cut
            CComPtr<ISection> girder_section;
            CreateNoncompositeSection(bridge,ssMbrID,segIdx,dist_from_start_of_segment,stageIdx,spmGross,&girder_section);

            if ( girder_section == NULL )
               continue; // this girder does not cross the section cut... must be a short, highly skewed bridge

            CComPtr<IRect2d> boundbox;
            girder_section->get_BoundingBox(&boundbox);
            Float64 top;
            boundbox->get_Top(&top);

            bottom_deck_elevation = _cpp_max(bottom_deck_elevation,top);
            
            // Store into a composite container
            CComQIPtr<ICompositeSectionEx> cmpsection(girder_section);
            ATLASSERT(cmpsection);
            CollectionIndexType item_count;
            cmpsection->get_Count(&item_count);
            for ( CollectionIndexType i = 0; i < item_count; i++ )
            {
               CComPtr<ICompositeSectionItemEx> item;
               cmpsection->get_Item(i,&item);

               bridge_section->AddSectionEx(item);
            }
         }
      }
      ssMbr.Release();
   }

   // The deck shape is a flat rectangle, so move the tops of the girders up so
   // that they touch to bottom of the slab.
   // If the deck model improves, improve this.
   CollectionIndexType nSections;
   bridge_section->get_Count(&nSections);
   for ( CollectionIndexType sectionIdx = 0; sectionIdx < nSections; sectionIdx++ )
   {
      CComPtr<ICompositeSectionItemEx> item;
      bridge_section->get_Item(sectionIdx,&item);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComQIPtr<IXYPosition> position(shape);

      CComPtr<IPoint2d> pntTC;
      position->get_LocatorPoint(lpTopCenter,&pntTC);
      pntTC->put_Y(bottom_deck_elevation);
      position->put_LocatorPoint(lpTopCenter,pntTC);
   }

   // If appropriate for the bridge and stage, add the bridge deck
   CComPtr<ICompositeSectionItemEx> deckitem;
   hr = CreateBridgeDeckSection(bridge,distFromStartOfBridge,stageIdx,bottom_deck_elevation,&deckitem);
   if ( FAILED(hr) )
      return hr;

   if ( deckitem )
   {
      bridge_section->AddSectionEx(deckitem);
   }


   // include the traffic barrier
   VARIANT_BOOL bStructuralOnly = (bsc == bscStructurallyContinuousOnly ? VARIANT_TRUE : VARIANT_FALSE);
   if ( bsc != bscNone )
   {
      Float64 station = DistanceToStation(bridge,distFromStartOfBridge);

      CComPtr<ISection> leftBarrier, rightBarrier;
      CreateLeftBarrierSection( bridge,station,bStructuralOnly,&leftBarrier);
      CreateRightBarrierSection(bridge,station,bStructuralOnly,&rightBarrier);

      if ( leftBarrier )
      {
         CComQIPtr<ICompositeSectionEx> compSection(leftBarrier);
         CComQIPtr<ICompositeSectionItemEx> item;
         compSection->get_Item(0,&item);
         bridge_section->AddSectionEx(item);
      }

      if ( rightBarrier )
      {
         CComQIPtr<ICompositeSectionEx> compSection(rightBarrier);
         CComQIPtr<ICompositeSectionItemEx> item;
         compSection->get_Item(0,&item);
         bridge_section->AddSectionEx(item);
      }
   }

   bridge_section.QueryInterface(section);
   return S_OK;
}

STDMETHODIMP CSectionCutTool::CreateGirderShapeBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 distFromStartOfSSMbr,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,IShape** ppShape)
{
   CComPtr<ISuperstructureMember> ssMbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssMbr);

   Float64 distFromStartOfSegment;
   SegmentIndexType segIdx;
   CComPtr<ISegment> segment;
   ssMbr->GetDistanceFromStartOfSegment(distFromStartOfSSMbr,&distFromStartOfSegment,&segIdx,&segment);

   return CreateGirderShapeBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,stageIdx,ppShape);
}

STDMETHODIMP CSectionCutTool::CreateGirderShapeBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx, IShape** ppShape)
{
   // Validate input
   CHECK_RETOBJ(ppShape);
   CHECK_IN(bridge);

   return CreateGirderShape(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,stageIdx,ppShape);
}

HRESULT CSectionCutTool::CreateCompositeSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section)
{
   CComPtr<ISection> ncsection;
   HRESULT hr = CreateNoncompositeSection(bridge,ssMbrID,segIdx,distFromStartOfSegment,stageIdx,sectionPropMethod,&ncsection);
   if ( FAILED(hr) )
      return hr;

   (*section) = ncsection;
   (*section)->AddRef();

   // for net properties, we only want the girder
   if ( sectionPropMethod == spmNet )
      return S_OK;

   CComPtr<ISection> deckSection;
   hr = CreateDeckSection(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,stageIdx,sectionPropMethod,&deckSection);
   if ( FAILED(hr) )
      return hr;

   if ( hr == S_OK )
   {
      // put slab on top of beam
      CComQIPtr<ICompositeSectionEx> cmpSection(ncsection);
      CComPtr<ICompositeSectionItemEx> si;
      cmpSection->get_Item(0,&si);
      CComPtr<IShape> beam_shape;
      si->get_Shape(&beam_shape);
      CComQIPtr<IXYPosition> beam_position(beam_shape);
      CComPtr<IPoint2d> beam_top_center;
      beam_position->get_LocatorPoint(lpTopCenter,&beam_top_center);

      // move the composite so all the rebar inside the deck moves too
      CComQIPtr<IXYPosition> deck_position(deckSection);
      deck_position->put_LocatorPoint(lpBottomCenter,beam_top_center);

      // can't put a composite section inside of another composite section so
      // take each section item from the deck and put it into the main composite 
      // section object
      CComQIPtr<ICompositeSectionEx> cmpDeckSection(deckSection);
      CollectionIndexType nItems;
      cmpDeckSection->get_Count(&nItems);
      for ( CollectionIndexType idx = 0; idx < nItems; idx++ )
      {
         CComPtr<ICompositeSectionItemEx> sectionItem;
         cmpDeckSection->get_Item(idx,&sectionItem);
         cmpSection->AddSectionEx(sectionItem);
      }
   }

   return S_OK;
}

HRESULT CSectionCutTool::CreateDeckSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section)
{
   CComPtr<ICompositeSectionEx> cmpSection;
   cmpSection.CoCreateInstance(CLSID_CompositeSectionEx);
   cmpSection.QueryInterface(section);

   // Get bridge deck and determine type
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   // this model doesn't have a deck... get the heck outta here
   if ( deck == NULL )
   {
      return S_FALSE;
   }

   VARIANT_BOOL bComposite;
   deck->get_Composite(&bComposite);
   if ( bComposite == VARIANT_FALSE )
   {
      // if deck is not composite, we are done
      return S_FALSE;
   }


   CComQIPtr<ICastSlab> cip(deck);
   CComQIPtr<IPrecastSlab> sip(deck);
   CComQIPtr<IOverlaySlab> overlay(deck);

   if ( cip == NULL && sip == NULL && overlay == NULL )
   {
      return Error(IDS_E_UNKNOWNDECKTYPE,IID_ISectionCutTool,GBMT_E_UNKNOWNDECKTYPE);
   }

   Float64 Econc;
   Float64 Dconc;
   CComPtr<IMaterial> material;
   deck->get_Material(&material);
   material->get_E(stageIdx,&Econc);
   material->get_Density(stageIdx,&Dconc);

   if ( IsZero(Econc) )
   {
      // Deck isn't cast yet
      return S_OK;
   }

   // Need to get effective flange width of the slab
   Float64 eff_flange_width;
   HRESULT hr = m_EffFlangeTool->EffectiveFlangeWidthBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,&eff_flange_width);
   if ( FAILED(hr) )
      return hr;

   // get structural thickness of deck
   Float64 structural_depth = 0;
   if ( cip != NULL )
   {
      Float64 gross,wearing;
      cip->get_GrossDepth(&gross);
      cip->get_SacrificialDepth(&wearing);
      structural_depth = gross - wearing;
   }
   else if ( sip != NULL )
   {
      Float64 panel, cast, wearing;
      sip->get_PanelDepth(&panel);
      sip->get_CastDepth(&cast);
      sip->get_SacrificialDepth(&wearing);

      structural_depth = panel + cast - wearing;
   }
   else if ( overlay != NULL )
   {
      Float64 gross,wearing;
      overlay->get_GrossDepth(&gross);
      overlay->get_SacrificialDepth(&wearing);
      structural_depth = gross - wearing;
   }
   else
   {
      ATLASSERT(false); // should never get here
   }

   // Build a slab shape and add it to the section
   CComPtr<IRectangle> slab;
   slab.CoCreateInstance(CLSID_Rect);
   slab->put_Height(structural_depth);
   slab->put_Width(eff_flange_width);

   CComQIPtr<IShape> shape(slab);
   cmpSection->AddSection(shape,Econc,0.0,Dconc,0.0,IsZero(Econc) ? VARIANT_FALSE : VARIANT_TRUE );

   if ( sectionPropMethod == spmTransformed || sectionPropMethod == spmNet )
   {
      // Add Longitudinal Reinforcement Bars

      // get the location of the bottom of the slab... the rebar are located from the bottom
      CComQIPtr<IXYPosition> position(slab);
      CComPtr<IPoint2d> pntBottomCenter;
      position->get_LocatorPoint(lpBottomCenter,&pntBottomCenter);
      Float64 yBottom;
      pntBottomCenter->get_Y(&yBottom);

      CComPtr<IBridgeDeckRebarLayout> rebarLayout;
      deck->get_RebarLayout(&rebarLayout);

      CComPtr<IRebarSection> rebarSection;
      rebarLayout->CreateRebarSection(ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,&rebarSection);

      CComPtr<IEnumRebarSectionItem> enumRebarSectionItem;
      rebarSection->get__EnumRebarSectionItem(&enumRebarSectionItem);

      CComPtr<IRebarSectionItem> rebarSectionItem;
      while ( enumRebarSectionItem->Next(1,&rebarSectionItem,NULL) != S_FALSE )
      {
         CComPtr<IPoint2d> pntRebar;
         rebarSectionItem->get_Location(&pntRebar);

         // x measured from CL girder
         // y measured from bottom of deck
         Float64 x,y;
         pntRebar->Location(&x,&y);

         CComPtr<IRebar> rebar;
         rebarSectionItem->get_Rebar(&rebar);

         Float64 Abar;
         rebar->get_NominalArea(&Abar);

         // models bar as an object with area. Moment of inertia is taken to be zero
         CComPtr<IGenericShape> rebarShape;
         rebarShape.CoCreateInstance(CLSID_GenericShape);
         rebarShape->put_Area(Abar);
         rebarShape->put_Ixx(0);
         rebarShape->put_Iyy(0);
         rebarShape->put_Ixy(0);
         rebarShape->put_Perimeter(0);

         CComPtr<IPoint2d> centroid;
         rebarShape->get_Centroid(&centroid);

         centroid->Move(x,yBottom + y);

         CComQIPtr<IMaterial> material(rebar);
         ATLASSERT(material);

         Float64 Ebar, Dbar;
         material->get_E(stageIdx,&Ebar);
         material->get_Density(stageIdx,&Dbar);

         // If the bar doesn't have strength or density, then it isn't in the girder yet.
         // Make the foreground material properties the same as the background
         // material properties. This will eliminate the bar from the section
         // (e.g EA = Ab(Ebar - Econc) = Ab(Econc - Econc) = 0)
         if ( sectionPropMethod == spmTransformed )
         {
            if ( IsZero(Ebar) )
               Ebar = Econc;

            if ( IsZero(Dbar) )
               Dbar = Dconc;
         }
         else if ( sectionPropMethod == spmNet )
         {
            // If we are computing net properties, we want to
            // model the hole and not the bar
            // (e.g. EA = EconcAg + Abar(0 - Econc) = EconcAg - Abar(Econc) = (Ag-Abar)Econc
            Ebar = 0;
            Dbar = 0;
         }

         // EA = EgAg + Abar(Ebar-Eg) = Eg(Ag-Abar) + EbarAbar
         // models the bar and makes a hole in the concrete for the bar
         CComQIPtr<IShape> rebar_shape(rebarShape);
         cmpSection->AddSection(rebar_shape,Ebar,Econc,Dbar,Dconc,VARIANT_TRUE);
         rebarSectionItem.Release();
      }
   } // if not gross properties

   return S_OK;
}

HRESULT CSectionCutTool::CreateNoncompositeSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** ppSection)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   // this is the primary section (the girder)
   CComPtr<ISection> section;
   HRESULT hr = segment->get_Section(stageIdx,distFromStartOfSegment,&section);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
      return hr;

   section.CopyTo(ppSection);

   // get the girder shape
   // the girder is the primary shape so it is the first item in the section model
   CComQIPtr<ICompositeSectionEx> compositeSection(section);
   ATLASSERT(compositeSection);
   CComPtr<ICompositeSectionItemEx> csi;
   compositeSection->get_Item(0,&csi);
   CComPtr<IShape> primary_shape;
   csi->get_Shape(&primary_shape);

   // Strand, Rebar, and Tendon coordinates are relative to the girder....
   // need to get the offset distance so the strand, bar, tendon can
   // be put in the correct location of the cross section
   CComQIPtr<IXYPosition> position(primary_shape);
   CComPtr<IPoint2d> pntTopCenter;
   position->get_LocatorPoint(lpTopCenter,&pntTopCenter);
   Float64 xTop,yTop;
   pntTopCenter->Location(&xTop,&yTop);

   CComPtr<IPoint2d> pntBottomCenter;
   position->get_LocatorPoint(lpBottomCenter,&pntBottomCenter);
   Float64 xBottom,yBottom;
   pntBottomCenter->Location(&xBottom,&yBottom);

   // background properties are the foreground properties of the girder concrete (the holes are in the girder)
   Float64 Econc,Dconc;
   csi->get_Efg(&Econc);
   csi->get_Dfg(&Dconc);

   // on the segment, get the PrecastGirder item data
   CComQIPtr<IItemData> item_data(segment);
   ATLASSERT(item_data); // segments must have item data
   CComPtr<IUnknown> punk;
   item_data->GetItemData(CComBSTR("Precast Girder"),&punk);
   ATLASSERT(punk != NULL);
   CComQIPtr<IPrecastGirder> girder(punk);
   ATLASSERT(girder != NULL);

   Float64 segment_length; // end-to-end segment length
   girder->get_GirderLength(&segment_length);

   // need to make sure the location we are looking at is actually
   // on the precast girder or if it is in a closure pour region
   CComPtr<IGirderLine> girderLine;
   segment->get_GirderLine(&girderLine);
   Float64 brgOffset,endDistance;
   girderLine->get_BearingOffset(etStart,&brgOffset);
   girderLine->get_EndDistance(etStart,&endDistance);

   // Distace measure from the face of the segment (not from the CLPier/CLTempSupport)
   Float64 distFromFaceOfSegment = distFromStartOfSegment - (brgOffset-endDistance);
   bool bIsPointOnSegment = ( 0 <= distFromFaceOfSegment && distFromFaceOfSegment <= segment_length ) ? true : false;

   // Add Strands and Rebar
   if ( sectionPropMethod != spmGross )
   {
      if ( bIsPointOnSegment )
      {
         // The point under consideration must be on the precast girder segment, otherwise there aren't any strands
         // or girder rebar

         // Add Strands
         for ( int i = 0; i < 3; i++ )
         {
            CComPtr<IMaterial> material;
            CComPtr<IPrestressingStrand> strandMaterial;

            if ( i == 0 )
               girder->get_StraightStrandMaterial(&strandMaterial);
            else if ( i == 1 )
               girder->get_HarpedStrandMaterial(&strandMaterial);
            else
               girder->get_TemporaryStrandMaterial(&strandMaterial);

            strandMaterial.QueryInterface(&material);
            Float64 Estrand, Dstrand;
            material->get_E(stageIdx,&Estrand);
            material->get_Density(stageIdx,&Dstrand);
            CComPtr<IPoint2dCollection> strandLocations;
            if ( i == 0 )
               girder->get_StraightStrandPositions(distFromFaceOfSegment,&strandLocations);
            else if ( i == 1 )
               girder->get_HarpedStrandPositions(distFromFaceOfSegment,&strandLocations);
            else
               girder->get_TemporaryStrandPositions(distFromFaceOfSegment,&strandLocations);

            CComPtr<IPoint2d> point;
            CComPtr<IEnumPoint2d> enum_points;
            strandLocations->get__Enum(&enum_points);
            while ( enum_points->Next(1,&point,NULL) != S_FALSE )
            {
               // x measured from CL girder
               // y measured from bottom of girder
               Float64 x,y;
               point->Location(&x,&y);

               Float64 Aps;
               strandMaterial->get_NominalArea(&Aps);

               // models strand as an object with area. Moment of inertia is taken to be zero
               CComPtr<IGenericShape> strandShape;
               strandShape.CoCreateInstance(CLSID_GenericShape);
               strandShape->put_Area(Aps);
               strandShape->put_Ixx(0);
               strandShape->put_Iyy(0);
               strandShape->put_Ixy(0);
               strandShape->put_Perimeter(0);

               CComPtr<IPoint2d> centroid;
               strandShape->get_Centroid(&centroid);

               centroid->Move(x,yBottom + y);

               // If the strand doesn't have strength or density in this stage, then it
               // doesn't really exist in the section. 
               // Make the foreground material properties the same as the background
               // material properties. This will eliminate strand bar from the section
               // (e.g EA = Aps(Estrand - Econc) = Aps(Econc - Econc) = 0)
               if ( sectionPropMethod == spmTransformed )
               {
                  if ( IsZero(Estrand) )
                     Estrand = Econc;

                  if ( IsZero(Dstrand) )
                     Dstrand = Dconc;
               }
               else if ( sectionPropMethod == spmNet )
               {
                  // If we are computing net properties, we want to
                  // model the hole and not the strand
                  // (e.g. EA = EconcAg + Astrand(0 - Econc) = EconcAg - Astrand(Econc) = (Ag-Astrand)Econc
                  Estrand = 0;
                  Dstrand = 0;
               }

               // EA = EgAg + Astrand(Estrand-Eg) = Eg(Ag-Astrand) + (Estrand)(Astrand)
               // models the strand and makes a hole in the concrete for the strand
               CComQIPtr<IShape> strand_shape(strandShape);
               compositeSection->AddSection(strand_shape,Estrand,Econc,Dstrand,Dconc,VARIANT_TRUE);
               point.Release();
            }
         } // End of Strand
      } // is point on precast girder

      // Add Longitudinal Reinforcement Bars
      CComPtr<IRebarLayout> rebarLayout;
      girder->get_RebarLayout(&rebarLayout);

      CComPtr<IRebarSection> rebarSection;
      rebarLayout->CreateRebarSection(distFromFaceOfSegment,&rebarSection);

      CComPtr<IEnumRebarSectionItem> enumRebarSectionItem;
      rebarSection->get__EnumRebarSectionItem(&enumRebarSectionItem);

      CComPtr<IRebarSectionItem> rebarSectionItem;
      while ( enumRebarSectionItem->Next(1,&rebarSectionItem,NULL) != S_FALSE )
      {
         CComPtr<IPoint2d> pntRebar;
         rebarSectionItem->get_Location(&pntRebar);

         // x measured from CL girder
         // y measured from bottom of girder
         Float64 x,y;
         pntRebar->Location(&x,&y);

         CComPtr<IRebar> rebar;
         rebarSectionItem->get_Rebar(&rebar);

         Float64 Abar;
         rebar->get_NominalArea(&Abar);

         // models bar as an object with area. Moment of inertia is taken to be zero
         CComPtr<IGenericShape> rebarShape;
         rebarShape.CoCreateInstance(CLSID_GenericShape);
         rebarShape->put_Area(Abar);
         rebarShape->put_Ixx(0);
         rebarShape->put_Iyy(0);
         rebarShape->put_Ixy(0);
         rebarShape->put_Perimeter(0);

         CComPtr<IPoint2d> centroid;
         rebarShape->get_Centroid(&centroid);

         centroid->Move(x,yBottom + y);

         CComQIPtr<IMaterial> material(rebar);
         ATLASSERT(material);

         Float64 Ebar, Dbar;
         material->get_E(stageIdx,&Ebar);
         material->get_Density(stageIdx,&Dbar);

         // If the bar doesn't have strength or density, then it isn't in the girder yet.
         // Make the foreground material properties the same as the background
         // material properties. This will eliminate the bar from the section
         // (e.g EA = Ab(Ebar - Econc) = Ab(Econc - Econc) = 0)
         if ( sectionPropMethod == spmTransformed )
         {
            if ( IsZero(Ebar) )
               Ebar = Econc;

            if ( IsZero(Dbar) )
               Dbar = Dconc;
         }
         else if ( sectionPropMethod == spmNet )
         {
            // If we are computing net properties, we want to
            // model the hole and not the bar
            // (e.g. EA = EconcAg + Abar(0 - Econc) = EconcAg - Abar(Econc) = (Ag-Abar)Econc
            Ebar = 0;
            Dbar = 0;
         }

         // EA = EgAg + Abar(Ebar-Eg) = Eg(Ag-Abar) + EbarAbar
         // models the bar and makes a hole in the concrete for the bar
         CComQIPtr<IShape> rebar_shape(rebarShape);
         compositeSection->AddSection(rebar_shape,Ebar,Econc,Dbar,Dconc,VARIANT_TRUE);
         rebarSectionItem.Release();
      }
   } // if not gross properties


   // add holes for tendons/ducts if the stage is before the grouting stage
   // otherwise, omit the holes
   
   // get the tendon model. it is stored as item data on the superstructure member
   CComQIPtr<IItemData> itemData(ssmbr);
   CComPtr<IUnknown> unk;
   itemData->GetItemData(CComBSTR("Tendons"),&unk);
   CComQIPtr<ITendonCollection> tendons(unk);

   DuctIndexType nTendons = 0; // # tendons is the same as # ducts in this context
   if ( tendons )
      tendons->get_Count(&nTendons);

   for ( DuctIndexType tendonIdx = 0; tendonIdx < nTendons; tendonIdx++ )
   {
      CComPtr<ITendon> tendon;
      tendons->get_Item(tendonIdx,&tendon);

      CComPtr<IPrestressingStrand> strand;
      tendon->get_Material(&strand);

      CComQIPtr<IMaterial> material(strand);
      ATLASSERT(material);

      Float64 Etendon;
      material->get_E(stageIdx,&Etendon);

      Float64 Dtendon;
      material->get_Density(stageIdx,&Dtendon);

      // create a circle for the tendon
      Float64 distFromStart; // measured in girder path coordinates
      ssmbr->GetDistanceFromStart(segIdx,distFromStartOfSegment,&distFromStart);


      // convert distFromStart to be measured from the actual physical start of the girder
      CComPtr<ISegment> firstSegment;
      ssmbr->get_Segment(0,&firstSegment);

      CComPtr<IGirderLine> girderLine;
      firstSegment->get_GirderLine(&girderLine);

      Float64 brgOffset,endDist;
      girderLine->get_BearingOffset(etStart,&brgOffset);
      girderLine->get_EndDistance(etStart,&endDist);
      distFromStart -= (brgOffset-endDist);


      CComPtr<IPoint3d> pntCG;
      tendon->get_CG(distFromStart,tmPath,&pntCG);

      // location of duct in cross section coordinates
      Float64 x,y,z;
      pntCG->Location(&x,&y,&z);

      // if Etendon is zero, the tendon is not installed yet
      // Model the hole for the duct. Model this hole for gross, transformed and net properties
      if ( IsZero(Etendon) )
      {
         // Put holes for ducts into girder
         Float64 ductDiameter;
         tendon->get_DuctDiameter(&ductDiameter);

         CComPtr<ICircle> duct;
         duct.CoCreateInstance(CLSID_Circle);
         duct->put_Radius(ductDiameter/2);

         CComPtr<IPoint2d> center;
         duct->get_Center(&center);
         center->Move(xTop+x,yTop+y);

         CComQIPtr<IShape> duct_shape(duct);

         // If E is 0, then this models a hole in the section (E-Eg = -Eg)
         // and Summation of EA = EgAg - EgAhole = Eg(Ag - Ahole)
         compositeSection->AddSection(duct_shape,0.0,Econc,0.0,Dconc,VARIANT_TRUE);
      }
      else
      {
         // Add Tendon
         if ( sectionPropMethod == spmNet )
         {
            // If we are computing net properties, we want to
            // model the hole and not the tendon 
            // (e.g. EA = EconcAg + Atendon(0 - Econc) = EconcAg - Atendon(Econc) = (Ag-Atendon)Econc
            Etendon = 0;
            Dtendon = 0;
         }

#pragma Reminder("UPDATE: need to model tendon offsets")
         // distance from the CG of the duct to the CG of the strand within the duct
         Float64 cg_offset_x = 0.0;
         Float64 cg_offset_y = 0.0;

         Float64 Apt;
         tendon->get_TendonArea(&Apt);

         // models tendon as an object with area. Moment of inertia is taken to be zero
         CComPtr<IGenericShape> tendonShape;
         tendonShape.CoCreateInstance(CLSID_GenericShape);
         tendonShape->put_Area(Apt);
         tendonShape->put_Ixx(0);
         tendonShape->put_Iyy(0);
         tendonShape->put_Ixy(0);
         tendonShape->put_Perimeter(0);

         CComPtr<IPoint2d> centroid;
         tendonShape->get_Centroid(&centroid);

         centroid->Move(x+cg_offset_x,yTop + y + cg_offset_y);

         CComQIPtr<IShape> tendon_shape(tendonShape);

         // EA = EgAg + Apt(Ept-Eg) = Eg(Ag-Apt) + EptApt: Tendon is added and a hole is created in the concrete
         compositeSection->AddSection(tendon_shape,Etendon,Econc,Dtendon,Dconc,VARIANT_TRUE);
      }
   } // next duct

   return S_OK;
}

HRESULT CSectionCutTool::CreateBridgeDeckSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,StageIndexType stageIdx,Float64 elevBottomDeck,ICompositeSectionItemEx** deckitem)
{
   // This method creates a rectangular approximation of the bridge deck cross section.
   // The rectangle width is the edge-to-edge width of the deck, measured normal to the alignment
   // at distFromStartOfBridge. The height of the rectangle is the structural thickness of the deck
   // (gross depth - wearing depth). The depth of precast deck panels is included in the height
   // of the rectangular approximation.
   HRESULT hr = S_OK;

   (*deckitem) = NULL;
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);
   if ( deck )
   {
      VARIANT_BOOL vbIsComposite;
      deck->get_Composite(&vbIsComposite);

      if ( vbIsComposite == VARIANT_TRUE )
      {
         // deck is composite so it is part of the structural section
         CComPtr<IDeckBoundary> deckBoundary;
         deck->get_DeckBoundary(&deckBoundary);

         CComPtr<IPath> leftPath, rightPath;
         deckBoundary->get_LeftEdgePath(VARIANT_TRUE,&leftPath);
         deckBoundary->get_RightEdgePath(VARIANT_TRUE,&rightPath);

         Float64 station = DistanceToStation(bridge,distFromStartOfBridge);

         CComPtr<IAlignment> alignment;
         bridge->get_Alignment(&alignment);

         CComPtr<IDirection> normal;
         alignment->Normal(CComVariant(station),&normal);

         Float64 dir;
         normal->get_Value(&dir);

         CComPtr<ILine2d> line;
         line.CoCreateInstance(CLSID_Line2d);

         CComPtr<IVector2d> v;
         CComPtr<IPoint2d> p;
         line->GetExplicit(&p,&v);
         v->put_Direction(dir);
         line->SetExplicit(p,v);

         CComPtr<IPoint2d> pntAlignment;
         alignment->LocatePoint(CComVariant(station),omtNormal,0.0,CComVariant(normal),&pntAlignment);

         CComPtr<IPoint2d> pntLeft, pntRight;
         leftPath->Intersect(line,pntAlignment,&pntLeft);
         rightPath->Intersect(line,pntAlignment,&pntRight);

         // get slab depth and width
         Float64 ttl_width;
         pntLeft->DistanceEx(pntRight,&ttl_width);

         Float64 depth;
         CComQIPtr<ICastSlab> cip(deck);
         CComQIPtr<IPrecastSlab> sip(deck);
         CComQIPtr<IOverlaySlab> overlay(deck);

         if ( cip == NULL && sip == NULL && overlay == NULL )
         {
            return Error(IDS_E_UNKNOWNDECKTYPE,IID_ISectionCutTool,GBMT_E_UNKNOWNDECKTYPE);
         }

         if ( cip )
         {
            Float64 gross_depth, sac_depth;
            cip->get_GrossDepth(&gross_depth);
            cip->get_SacrificialDepth(&sac_depth);

            depth = gross_depth - sac_depth;
         }
         else if ( sip )
         {
            Float64 panel_depth, cast_depth, sac_depth;
            sip->get_PanelDepth(&panel_depth);
            sip->get_CastDepth(&cast_depth);
            sip->get_SacrificialDepth(&sac_depth);

            depth = panel_depth + cast_depth - sac_depth;
         }
         else if ( overlay )
         {
            Float64 gross_depth, sac_depth;
            overlay->get_GrossDepth(&gross_depth);
            overlay->get_SacrificialDepth(&sac_depth);

            depth = gross_depth - sac_depth;
         }
         else
         {
            ATLASSERT(false); // should never get here
         }

         CComPtr<IRectangle> rect;
         rect.CoCreateInstance(CLSID_Rect);
         rect->put_Width( ttl_width );
         rect->put_Height( depth );

         CComPtr<IPoint2d> hp;
         rect->get_HookPoint(&hp);
         hp->put_Y(elevBottomDeck + depth/2);

         CComPtr<ICompositeSectionItemEx> csi;
         csi.CoCreateInstance(CLSID_CompositeSectionItemEx);

         CComQIPtr<IShape> shape(rect);
         csi->putref_Shape(shape);

         CComPtr<IMaterial> material;
         deck->get_Material(&material);

         Float64 E, density;
         material->get_E(stageIdx,&E);
         material->get_Density(stageIdx,&density);

         csi->put_Efg(E);
         csi->put_Ebg(0);

         csi->put_Dfg(density);
         csi->put_Dbg(0);

         (*deckitem) = csi;
         (*deckitem)->AddRef();
      }
   }

   return hr;
}

HRESULT CSectionCutTool::CreateGirderShape(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,IShape** ppShape)
{
   // distFromStartOfSegment is in segment coordinates
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   CComPtr<IShape> primary_shape;
   segment->get_PrimaryShape(distFromStartOfSegment,&primary_shape);

   primary_shape.CopyTo(ppShape);

   CComQIPtr<ICompositeShape> compositeShape(primary_shape);
   ATLASSERT(compositeShape); // primary_shape must be a composite so we can put holes in it

   // Internal shapes, such as ducts, have coordinates that are relative to the girder....
   // need to get the offset distance so these objects can
   // be put in the correct location of the cross section
   CComQIPtr<IXYPosition> position(primary_shape);
   CComPtr<IPoint2d> pntTopCenter;
   position->get_LocatorPoint(lpTopCenter,&pntTopCenter);
   Float64 xTop,yTop;
   pntTopCenter->Location(&xTop,&yTop);

#pragma Reminder("UPDATE: the code here is very similiar to building the section model")
   // find a way to consolidate it for to make it easier to maintain

   ////////////////////////////////////
   // Tendons/Ducts
   ////////////////////////////////////

   // get the tendon model. it is stored as item data on the superstructure member
   CComQIPtr<IItemData> itemData(ssmbr);
   CComPtr<IUnknown> unk;
   itemData->GetItemData(CComBSTR("Tendons"),&unk);
   CComQIPtr<ITendonCollection> tendons(unk);

   if ( tendons )
   {
      DuctIndexType nTendons; // # tendons is the same as # ducts in this context
      tendons->get_Count(&nTendons);
      for ( DuctIndexType tendonIdx = 0; tendonIdx < nTendons; tendonIdx++ )
      {
         CComPtr<ITendon> tendon;
         tendons->get_Item(tendonIdx,&tendon);

         CComPtr<IPrestressingStrand> strand;
         tendon->get_Material(&strand);

         CComQIPtr<IMaterial> material(strand);
         ATLASSERT(material);

         Float64 Etendon;
         material->get_E(stageIdx,&Etendon);

         // create a circle for the tendon
         Float64 distFromStart; // in girder path coordinates
         ssmbr->GetDistanceFromStart(segIdx,distFromStartOfSegment,&distFromStart);

         // Adjust distFromStart to girder coordinates
         CComPtr<ISegment> segment;
         ssmbr->get_Segment(0,&segment);
         CComPtr<IGirderLine> girderLine;
         segment->get_GirderLine(&girderLine);
         Float64 brgOffset, endDist;
         girderLine->get_BearingOffset(etStart,&brgOffset);
         girderLine->get_EndDistance(etStart,&endDist);
         Float64 offset = brgOffset-endDist;
         distFromStart -= offset; // now measured in Girder Coordinates


         CComPtr<IPoint3d> pntCG;
         tendon->get_CG(distFromStart,tmPath,&pntCG); // distFromStart needs to be in Girder Coordinates

         if ( pntCG == NULL )
         {
#pragma Reminder("UPDATE: review this code")
            // this code was put here to deal with the case that tendon->get_CG() fails
            // and allows testing to continue
            ATLASSERT(false);
            continue;
         }

         // location of duct in cross section coordinates
         Float64 x,y,z;
         pntCG->Location(&x,&y,&z);

         // Tendon is not installed in this stage
         if ( IsZero(Etendon) )
         {
            Float64 ductDiameter;
            tendon->get_DuctDiameter(&ductDiameter);

            CComPtr<ICircle> duct;
            duct.CoCreateInstance(CLSID_Circle);
            duct->put_Radius(ductDiameter/2);

            CComPtr<IPoint2d> center;
            duct->get_Center(&center);
            center->Move(xTop+x,yTop+y);

            CComQIPtr<IShape> duct_shape(duct);

            compositeShape->AddShape(duct_shape,VARIANT_TRUE);
         } // adding hole
      } // next duct
   }


   ///////////////////
   // Model deck
   ///////////////////

   // Get bridge deck and determine type
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   Float64 Edeck = 0;
   if ( deck )
   {
      CComPtr<IMaterial> deck_material;
      deck->get_Material(&deck_material);
      deck_material->get_E(stageIdx,&Edeck);
   }

   if ( deck && 0 < Edeck )
   {
      // if there is a deck and its E is > 0, then
      // include it in the model. Edeck will be zero in stages before it
      // is cast
      CComQIPtr<ICastSlab> cip(deck);
      CComQIPtr<IPrecastSlab> sip(deck);
      CComQIPtr<IOverlaySlab> overlay(deck);

      if ( cip == NULL && sip == NULL && overlay == NULL )
      {
         return Error(IDS_E_UNKNOWNDECKTYPE,IID_ISectionCutTool,GBMT_E_UNKNOWNDECKTYPE);
      }

      // Need to get effective flange width of the slab
      Float64 eff_flange_width;
      HRESULT hr = m_EffFlangeTool->EffectiveFlangeWidthBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,&eff_flange_width);
      if ( FAILED(hr) )
         return hr;

      // get structural thickness of deck
      Float64 structural_depth = 0;
      if ( cip != NULL )
      {
         Float64 gross,wearing;
         cip->get_GrossDepth(&gross);
         cip->get_SacrificialDepth(&wearing);
         structural_depth = gross - wearing;
      }
      else if ( sip != NULL )
      {
         Float64 panel, cast, wearing;
         sip->get_PanelDepth(&panel);
         sip->get_CastDepth(&cast);
         sip->get_SacrificialDepth(&wearing);

         structural_depth = panel + cast - wearing;
      }
      else if ( overlay != NULL )
      {
         Float64 gross,wearing;
         overlay->get_GrossDepth(&gross);
         overlay->get_SacrificialDepth(&wearing);
         structural_depth = gross - wearing;
      }
      else
      {
         ATLASSERT(false); // should never get here
      }

      // Build a slab shape and add it to the section
      CComPtr<IRectangle> slab;
      slab.CoCreateInstance(CLSID_Rect);
      slab->put_Height(structural_depth);
      slab->put_Width(eff_flange_width);

      // put slab on top of beam
      CComQIPtr<IXYPosition> slab_position(slab);
      slab_position->put_LocatorPoint(lpBottomCenter,pntTopCenter);

      CComQIPtr<IShape> slab_shape(slab);
      compositeShape->AddShape(slab_shape,VARIANT_FALSE);
   }

   return S_OK;
}

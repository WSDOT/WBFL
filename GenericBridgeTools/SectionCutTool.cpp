///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 2009  Washington State Department of Transportation
//                   Bridge and Structures Office
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

   CComPtr<IPoint2d> deckPoint;
   deckPoint.CoCreateInstance(CLSID_Point2d);
   deckPoint->Move(Left_deck_offset,elev);

   CComPtr<IBarrier> barrier;
   bridge->get_LeftBarrier(&barrier);

   CComPtr<IShape> barrier_shape;
   barrier->get_Shape(&barrier_shape);

   barrier_shape->Clone(shape);

   CComQIPtr<IXYPosition> position(*shape);
   position->put_LocatorPoint(lpHookPoint,deckPoint);

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

   CComPtr<IPoint2d> deckPoint;
   deckPoint.CoCreateInstance(CLSID_Point2d);
   deckPoint->Move(right_deck_offset,elev);

   CComPtr<IBarrier> barrier;
   bridge->get_RightBarrier(&barrier);

   CComPtr<IShape> barrier_shape;
   barrier->get_Shape(&barrier_shape);

   barrier_shape->Clone(shape);

   CComQIPtr<IXYPosition> position(*shape);
   position->put_LocatorPoint(lpHookPoint,deckPoint);

   return S_OK;
}

STDMETHODIMP CSectionCutTool::CreateLeftBarrierSection(IGenericBridge* bridge,Float64 station,VARIANT_BOOL bStructuralOnly,ICompositeSectionItem** section)
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

   CComPtr<IPoint2d> HP;
   HP.CoCreateInstance(CLSID_Point2d);
   HP->Move(left_deck_offset,elev);

   CComPtr<IBarrier> left_barrier;
   bridge->get_LeftBarrier(&left_barrier);

   CComPtr<IBarrier> barrier;
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
   position->put_LocatorPoint(lpHookPoint,HP);

   CComPtr<IMaterial> material;
   barrier->get_Material(&material);

   Float64 E,density;
   material->get_E(&E);
   material->get_Density(&density);

   CComPtr<ICompositeSectionItem> sectionItem;
   sectionItem.CoCreateInstance(CLSID_CompositeSectionItem);
   sectionItem->putref_Shape(shape);
   sectionItem->put_E(E);
   sectionItem->put_Density(density);
   sectionItem->put_Void(VARIANT_FALSE);
   sectionItem->put_Structural(VARIANT_TRUE);

   (*section) = sectionItem;
   (*section)->AddRef();

   return S_OK;
}

STDMETHODIMP CSectionCutTool::CreateRightBarrierSection(IGenericBridge* bridge,Float64 station,VARIANT_BOOL bStructuralOnly,ICompositeSectionItem** section)
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

   CComPtr<IPoint2d> HP;
   HP.CoCreateInstance(CLSID_Point2d);
   HP->Move(right_deck_offset,elev);

   CComPtr<IBarrier> right_barrier;
   bridge->get_RightBarrier(&right_barrier);

   CComPtr<IBarrier> barrier;
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
   position->put_LocatorPoint(lpHookPoint,HP);

   CComPtr<IMaterial> material;
   barrier->get_Material(&material);

   Float64 E,density;
   material->get_E(&E);
   material->get_Density(&density);

   CComPtr<ICompositeSectionItem> sectionItem;
   sectionItem.CoCreateInstance(CLSID_CompositeSectionItem);
   sectionItem->putref_Shape(shape);
   sectionItem->put_E(E);
   sectionItem->put_Density(density);
   sectionItem->put_Void(VARIANT_FALSE);
   sectionItem->put_Structural(VARIANT_TRUE);

   (*section) = sectionItem;
   (*section)->AddRef();

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

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   CComPtr<IProfile> profile;
   alignment->get_Profile(&profile);

   CComPtr<ISpan> span;
   bridge->SpanFromStation(station,&span);

   CComPtr<IPier> prev_pier;
   span->get_PrevPier(&prev_pier);
   pier_station.Release();
   prev_pier->get_Station(&pier_station);
   Float64 prev_pier_station;
   pier_station->get_Value(&prev_pier_station);
   Float64 distFromStartOfSpan = station - prev_pier_station;

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

   // Haunches along bottom of slab
   // haunch is defined by 6 points per mating surface
   //
   //    --------1\      /6------
   //             2      5
   //             |      |
   //             3------4
   //
   GirderIndexType nGirders;
   span->get_GirderCount(&nGirders);
   for ( GirderIndexType girderIdx = 0; girderIdx < nGirders; girderIdx++ )
   {
      CComPtr<ISuperstructureMember> ssmbr;
      span->get_SuperstructureMember(girderIdx,&ssmbr);

      CComPtr<ISegmentItem> segItem;
      Float64 dist_along_segment;
      ssmbr->GetSegmentForMemberLocation(distFromStartOfSpan,&dist_along_segment,&segItem);

      if ( !segItem )
         continue;

      CComPtr<ISegment> segment;
      segItem->get_Segment(&segment);

      if ( !segment )
         continue;

      // orientation of girder in radians... 0 = plumb, rotated CW is +
      Float64 orientation;
      segment->get_Orientation(&orientation);

      CComPtr<IShape> girder_shape;
      segment->get_Shape(dist_along_segment,&girder_shape);

      CComQIPtr<IGirderSection> girder_section(girder_shape);

      Float64 min_top_flange_thickness = 0;
      FlangeIndexType nTopFlanges;
      girder_section->get_TopFlangeCount(&nTopFlanges);
      if ( nTopFlanges != 0 )
         girder_section->get_MinTopFlangeThickness(&min_top_flange_thickness);

      SpanIndexType spanIdx;
      Float64 spanDist;

      // get the span index for this girder point
      m_BridgeGeometryTool->GirderLinePoint(bridge,distFromStart,girderIdx,&spanIdx,&spanDist);

      // if this points is off the bridge, use the index of the first/last span
      if ( spanIdx == INVALID_INDEX )
      {
         spanIdx = 0;
      }
      else if ( spanIdx == -2 )
      {
         ATLASSERT(false); // how can span index == -2?
         spanIdx = nSpans-1;
      }

      // get offset of CL girder from CL alignment ( < 0 means left of CL alignment )
      Float64 girder_offset;
      m_BridgeGeometryTool->GirderPathOffset(bridge,spanIdx,girderIdx,CComVariant(station),&girder_offset);

      Float64 location;
      SpanIndexType span_index;
      m_BridgeGeometryTool->GirderLinePoint(bridge,distFromStart,girderIdx,&span_index,&location);

      if (span_index == INVALID_INDEX) // this girder point is before/after the limits of the bridge (typically happens with skews)
         continue; // go to the next girder

      Float64 haunch;
      GetGirderHaunch(bridge,spanIdx,girderIdx,location,&haunch);

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
               if (girderIdx != nGirders-1 || msIdx != nMatingSurfaces-1)
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

STDMETHODIMP CSectionCutTool::CreateGirderSection(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,Float64 distFromStartOfGirder,BSTR stage,ISection** section)
{
   HRESULT hr;

   // Validate input
   CHECK_RETOBJ(section);
   CHECK_IN(bridge);
   CHECK_IN(stage);

   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);
   SpanIndexType nSpans;
   spans->get_Count(&nSpans);
   if ( spanIdx < 0 || nSpans <= spanIdx )
      return E_INVALIDARG;

   CComPtr<ISpan> span;
   spans->get_Item(spanIdx,&span);

   CComPtr<IGirderSpacing> spacing;
   span->get_GirderSpacing(etStart,&spacing);

   GirderIndexType nGirders;
   span->get_GirderCount(&nGirders);
   if ( gdrIdx < 0 || nGirders <= gdrIdx )
      return E_INVALIDARG;

   // See if bridge has a deck... if it does, we might have to do composite properties
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   bool bIsComposite = false;
   if ( deck )
   {
      VARIANT_BOOL bComposite;
      deck->get_Composite(&bComposite);

      if ( bComposite == VARIANT_TRUE )
      {
         CComBSTR bstrCompositeStage;
         deck->get_CompositeStage(&bstrCompositeStage);

         CComPtr<IStageCollection> stages;
         bridge->get_Stages(&stages);

         long cmp;
         hr = stages->Compare(stage,bstrCompositeStage,&cmp);
         if ( hr == S_FALSE )
            return E_INVALIDARG; // one of the stage names is not valid

         if ( 0 <= cmp ) // stage is equal to or comes after the composite stage
            bIsComposite = true;
      }
   }

   if ( bIsComposite )
   {
      return CreateCompositeSection(bridge,spanIdx,gdrIdx,distFromStartOfGirder,stage,section);
   }
   else
   {
      return CreateNoncompositeSection(bridge,spanIdx,gdrIdx,distFromStartOfGirder,stage,section);
   }

   return S_OK;
}

STDMETHODIMP CSectionCutTool::CreateBridgeSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,BSTR stage,BarrierSectionCut bsc,ISection** section)
{
   // location is measured along the alignment, from the station of the first pier. The section cut is made
   // normal to the alignment.
   HRESULT hr = S_OK;

   // Need to determine span,girder,location along each girder line so we can call CreateNoncompositeSection correctly
   CComPtr<ICompositeSection> bridge_section;
   bridge_section.CoCreateInstance(CLSID_CompositeSection);

   CComPtr<ISpan> span;
   bridge->SpanFromOffset(distFromStartOfBridge,&span);
   ATLASSERT(span);

   Float64 bottom_deck_elevation = -DBL_MAX;

   GirderIndexType nGirders;
   span->get_GirderCount(&nGirders);
   for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirders; gdrIdx++ )
   {
      SpanIndexType spanIdx;
      Float64 distFromStartOfSpan;
      m_BridgeGeometryTool->GirderLinePoint(bridge,distFromStartOfBridge,gdrIdx,&spanIdx,&distFromStartOfSpan);

      // Create a noncomposite section for each girder
      CComPtr<ISection> girder_section;
      CreateNoncompositeSection(bridge,spanIdx,gdrIdx,distFromStartOfSpan,stage,&girder_section);

      if ( spanIdx < 0 || girder_section == NULL )
         continue; // this girder does not cross the section cut... must be a short, highly skewed bridge

      CComPtr<IRect2d> boundbox;
      girder_section->get_BoundingBox(&boundbox);
      Float64 top;
      boundbox->get_Top(&top);

      bottom_deck_elevation = _cpp_max(bottom_deck_elevation,top);
      
      // Store into a composite container
      CComQIPtr<ICompositeSection> cmpsection(girder_section);
      ATLASSERT(cmpsection);
      CollectionIndexType item_count;
      cmpsection->get_Count(&item_count);
      for ( CollectionIndexType i = 0; i < item_count; i++ )
      {
         CComPtr<ICompositeSectionItem> item;
         cmpsection->get_Item(i,&item);

         bridge_section->AddSectionEx(item);
      }
   }

   // If appropriate for the bridge and stage, add the bridge deck
   CComPtr<ICompositeSectionItem> deckitem;
   hr = CreateBridgeDeckSection(bridge,distFromStartOfBridge,stage,bottom_deck_elevation,&deckitem);
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

      CComPtr<ICompositeSectionItem> leftBarrier, rightBarrier;
      CreateLeftBarrierSection( bridge,station,bStructuralOnly,&leftBarrier);
      CreateRightBarrierSection(bridge,station,bStructuralOnly,&rightBarrier);

      if ( leftBarrier )
         bridge_section->AddSectionEx(leftBarrier);

      if ( rightBarrier )
         bridge_section->AddSectionEx(rightBarrier);
   }

   bridge_section.QueryInterface(section);
   return S_OK;
}

HRESULT CSectionCutTool::CreateCompositeSection(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,Float64 distFromStartOfGirder,BSTR stage,ISection** section)
{
   CComPtr<ISection> ncsection;
   HRESULT hr = CreateNoncompositeSection(bridge,spanIdx,gdrIdx,distFromStartOfGirder,stage,&ncsection);
   if ( FAILED(hr) )
      return hr;

   // Get bridge deck and determine type
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   CComQIPtr<ICastSlab> cip(deck);
   CComQIPtr<IPrecastSlab> sip(deck);
   CComQIPtr<IOverlaySlab> overlay(deck);

   if ( cip == NULL && sip == NULL && overlay == NULL )
   {
      return Error(IDS_E_UNKNOWNDECKTYPE,IID_ISectionCutTool,GBMT_E_UNKNOWNDECKTYPE);
   }

   // Need to get tributary width of the slab
   Float64 eff_flange_width;
   hr = m_EffFlangeTool->EffectiveFlangeWidth(bridge,spanIdx,gdrIdx,distFromStartOfGirder,&eff_flange_width);
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

   Float64 E;
   Float64 density;
   CComPtr<IMaterial> material;
   deck->get_Material(&material);
   material->get_E(&E);
   material->get_Density(&density);

   // Build a slab shape and add it to the section
   CComPtr<IRectangle> slab;
   slab.CoCreateInstance(CLSID_Rect);
   slab->put_Height(structural_depth);
   slab->put_Width(eff_flange_width);

   // put slab on top of beam
   CComQIPtr<ICompositeSection> cmpSection(ncsection);
   CComPtr<ICompositeSectionItem> si;
   cmpSection->get_Item(0,&si);
   CComPtr<IShape> beam_shape;
   si->get_Shape(&beam_shape);
   CComQIPtr<IXYPosition> beam_position(beam_shape);
   CComPtr<IPoint2d> beam_top_center;
   beam_position->get_LocatorPoint(lpTopCenter,&beam_top_center);

   CComQIPtr<IXYPosition> slab_position(slab);
   slab_position->put_LocatorPoint(lpBottomCenter,beam_top_center);

   CComQIPtr<IShape> shape(slab);
   cmpSection->AddSection(shape,E,density,VARIANT_FALSE,VARIANT_TRUE);

   (*section) = ncsection;
   (*section)->AddRef();
   return S_OK;
}

HRESULT CSectionCutTool::CreateNoncompositeSection(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,Float64 distFromStartOfGirder,BSTR stage,ISection** section)
{
#pragma Reminder("REVIEW: Consider changing this function so it returns a CompositeSectionItem")
   // Get the girder section at the desired location
   CComPtr<IGirderSection> gdrSection;
   CComPtr<ISegment> segment;
   HRESULT hr = GetGirderSection(bridge,spanIdx,gdrIdx,distFromStartOfGirder,&segment,&gdrSection);
   if ( FAILED(hr) )
      return Error(IDS_E_GIRDERSECTION,IID_ISectionCutTool,GBMT_E_GIRDERSECTION);

   // girder sections should implement the IShape interface
   CComQIPtr<IShape> shape(gdrSection);
   if ( shape == NULL )
      return Error(IDS_E_SHAPE,IID_ISectionCutTool,GBMT_E_SHAPE);

   //
   // Position the shape so that its centerline is on the centerline of its girder path
   //

   // get the station and offset of the point
   Float64 offset;
   CComPtr<IStation> station;
   m_BridgeGeometryTool->StationAndOffset(bridge,spanIdx,gdrIdx,distFromStartOfGirder,&station,&offset);

   // get the roadway elevation at that point
   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   CComPtr<IProfile> profile;
   alignment->get_Profile(&profile);

   Float64 elevation;
   profile->Elevation(CComVariant(station),offset,&elevation);

   // get the deck thickness and haunch depth at that point
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);
   Float64 gross_slab_depth = 0;
   Float64 haunch = 0;

   if ( deck )
   {
      deck->get_GrossDepth(&gross_slab_depth);
      GetGirderHaunch(bridge,spanIdx,gdrIdx,distFromStartOfGirder,&haunch);
   }

   // move the top center point of the girder
   CComQIPtr<IXYPosition> xypos(gdrSection);
   CComPtr<IPoint2d> point;
   xypos->get_LocatorPoint(lpTopCenter,&point);
   point->Move(offset,elevation - gross_slab_depth - haunch);
   xypos->put_LocatorPoint(lpTopCenter,point);

   //
   // Make the shape into a section
   //

   // Need to get material for this section, or at least this segment...
   CComPtr<IMaterial> material;
   segment->get_Material(&material);
   if ( material == NULL )
      return Error(IDS_E_MATERIAL,IID_ISectionCutTool,GBMT_E_MATERIAL);


   Float64 E;
   Float64 density;
   material->get_E(&E);
   material->get_Density(&density);
    

   CComPtr<ICompositeSection> cmpsection;
   cmpsection.CoCreateInstance(CLSID_CompositeSection);
   cmpsection->AddSection(shape,E,density,VARIANT_FALSE,VARIANT_TRUE);

   CComQIPtr<ISection> s(cmpsection);
   (*section) = s;
   (*section)->AddRef();

   return S_OK;
}

HRESULT CSectionCutTool::CreateBridgeDeckSection(IGenericBridge* bridge,Float64 location,BSTR stage,Float64 elevBottomDeck,ICompositeSectionItem** deckitem)
{
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
         CComBSTR bstrCompositeStage;
         deck->get_CompositeStage(&bstrCompositeStage);

         CComPtr<IStageCollection> stages;
         bridge->get_Stages(&stages);

         long result;
         stages->Compare(bstrCompositeStage,stage,&result);
         if ( result <= 0 )
         {
            // Deck is composite and the composite stage is before or equal this stage.
            CComQIPtr<ICastSlab> cip(deck);
            CComQIPtr<IPrecastSlab> sip(deck);
            CComQIPtr<IOverlaySlab> overlay(deck);

            if ( cip == NULL && sip == NULL && overlay == NULL )
            {
               return Error(IDS_E_UNKNOWNDECKTYPE,IID_ISectionCutTool,GBMT_E_UNKNOWNDECKTYPE);
            }

            if ( cip )
               hr = CreateCIPBridgeDeckSection(bridge,location,elevBottomDeck,deckitem);
            else if ( sip )
               hr = CreateSIPBridgeDeckSection(bridge,location,elevBottomDeck,deckitem);
            else if ( overlay )
               hr = CreateOverlayBridgeDeckSection(bridge,location,elevBottomDeck,deckitem);
            else
               ATLASSERT(false); // should never get here
         }
      }
   }

   return hr;
}

HRESULT CSectionCutTool::CreateCIPBridgeDeckSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,Float64 elevBottomDeck,ICompositeSectionItem** deckitem)
{
#pragma Reminder("UPDATE: Creating a simple rectangle... crude approximation")
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);
   CComQIPtr<ICastSlab> cip(deck);

   Float64 station = DistanceToStation(bridge,distFromStartOfBridge);

   Float64 left_overhang, right_overhang;
   m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbLeft,&left_overhang);
   m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbRight,&right_overhang);

   Float64 gross_depth, sac_depth;
   cip->get_GrossDepth(&gross_depth);
   cip->get_SacrificialDepth(&sac_depth);

   Float64 depth = gross_depth - sac_depth;

   CComPtr<ISpan> span;
   bridge->SpanFromStation(station,&span);

   CComPtr<IGirderSpacing> spacing;
   span->get_GirderSpacing(etStart,&spacing);

   // get the distance from the start of the span
   CComPtr<IPier> prevPier;
   span->get_PrevPier(&prevPier);
   CComPtr<IStation> objStation;
   prevPier->get_Station(&objStation);
   Float64 prevPierStation;
   objStation->get_Value(&prevPierStation);
   Float64 distFromStartOfSpan = station - prevPierStation;

   // get the width of the girder spacing 
   Float64 width;
   spacing->get_Width(distFromStartOfSpan,mtNormal,&width);

   Float64 ttl_width = left_overhang + width + right_overhang;

   CComPtr<IRectangle> rect;
   rect.CoCreateInstance(CLSID_Rect);
   rect->put_Width( ttl_width );
   rect->put_Height( depth );

   CComPtr<IPoint2d> hp;
   rect->get_HookPoint(&hp);
   hp->put_Y(elevBottomDeck + depth/2);

   CComPtr<ICompositeSectionItem> csi;
   csi.CoCreateInstance(CLSID_CompositeSectionItem);

   CComQIPtr<IShape> shape(rect);
   csi->putref_Shape(shape);

   CComPtr<IMaterial> material;
   deck->get_Material(&material);

   Float64 E, density;
   material->get_E(&E);
   material->get_Density(&density);

   csi->put_E(E);
   csi->put_Density(density);

   (*deckitem) = csi;
   (*deckitem)->AddRef();

   return S_OK;
}

HRESULT CSectionCutTool::CreateSIPBridgeDeckSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,Float64 elevBottomDeck,ICompositeSectionItem** deckitem)
{
#pragma Reminder("UPDATE: Creating a simple rectangle... crude approximation")
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);
   CComQIPtr<IPrecastSlab> sip(deck);

   Float64 station = DistanceToStation(bridge,distFromStartOfBridge);
   CComPtr<ISpan> span;
   bridge->SpanFromStation(station,&span);

   Float64 left_overhang, right_overhang;
   m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbLeft,&left_overhang);
   m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbRight,&right_overhang);

   Float64 panel_depth, cast_depth, sac_depth;
   sip->get_PanelDepth(&panel_depth);
   sip->get_CastDepth(&cast_depth);
   sip->get_SacrificialDepth(&sac_depth);

   Float64 depth = panel_depth + cast_depth - sac_depth;

   CComPtr<IGirderSpacing> spacing;
   span->get_GirderSpacing(etStart,&spacing);

   CComPtr<IPier> pier;
   span->get_PrevPier(&pier);
   CComPtr<IStation> objStation;
   pier->get_Station(&objStation);
   Float64 pier_station;
   objStation->get_Value(&pier_station);
   Float64 distFromStartOfSpan = station - pier_station;

   Float64 width;
   spacing->get_Width(distFromStartOfSpan,mtNormal,&width);

   Float64 ttl_width = left_overhang + width + right_overhang;

   CComPtr<IRectangle> rect;
   rect.CoCreateInstance(CLSID_Rect);
   rect->put_Width( ttl_width );
   rect->put_Height( depth );

   CComPtr<IPoint2d> hp;
   rect->get_HookPoint(&hp);
   hp->put_Y(elevBottomDeck + depth/2);


   CComPtr<ICompositeSectionItem> csi;
   csi.CoCreateInstance(CLSID_CompositeSectionItem);

   CComQIPtr<IShape> shape(rect);
   csi->putref_Shape(shape);

   CComPtr<IMaterial> material;
   deck->get_Material(&material);

   Float64 E, density;
   material->get_E(&E);
   material->get_Density(&density);

   csi->put_E(E);
   csi->put_Density(density);

   (*deckitem) = csi;
   (*deckitem)->AddRef();

   return S_OK;
}

HRESULT CSectionCutTool::CreateOverlayBridgeDeckSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,Float64 elevBottomDeck,ICompositeSectionItem** deckitem)
{
#pragma Reminder("UPDATE: Creating a simple rectangle... crude approximation")
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);
   CComQIPtr<IOverlaySlab> overlay(deck);

   Float64 station = DistanceToStation(bridge,distFromStartOfBridge);

   CComPtr<ISpan> span;
   bridge->SpanFromStation(station,&span);

   Float64 left_overhang, right_overhang;
   m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbLeft,&left_overhang);
   m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbRight,&right_overhang);

   Float64 gross_depth, sac_depth;
   overlay->get_GrossDepth(&gross_depth);
   overlay->get_SacrificialDepth(&sac_depth);

   Float64 depth = gross_depth - sac_depth;

   CComPtr<IGirderSpacing> spacing;
   span->get_GirderSpacing(etStart,&spacing);

   CComPtr<IPier> pier;
   span->get_PrevPier(&pier);
   CComPtr<IStation> objStation;
   pier->get_Station(&objStation);
   Float64 pier_station;
   objStation->get_Value(&pier_station);
   Float64 distFromStartOfSpan = station - pier_station;

   Float64 width;
   spacing->get_Width(distFromStartOfSpan,mtNormal,&width);

   Float64 ttl_width = left_overhang + width + right_overhang;

   CComPtr<IRectangle> rect;
   rect.CoCreateInstance(CLSID_Rect);
   rect->put_Width( ttl_width );
   rect->put_Height( depth );

   CComPtr<IPoint2d> hp;
   rect->get_HookPoint(&hp);
   hp->put_Y(elevBottomDeck + depth/2);

   CComPtr<ICompositeSectionItem> csi;
   csi.CoCreateInstance(CLSID_CompositeSectionItem);

   CComQIPtr<IShape> shape(rect);
   csi->putref_Shape(shape);

   CComPtr<IMaterial> material;
   deck->get_Material(&material);

   Float64 E, density;
   material->get_E(&E);
   material->get_Density(&density);

   csi->put_E(E);
   csi->put_Density(density);

   (*deckitem) = csi;
   (*deckitem)->AddRef();

   return S_OK;
}

///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <WBFLCogo\CogoHelpers.h>

#include <algorithm>
#include <array>

#if defined _DEBUG
#include <map>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

template <class T>
HRESULT GetMaterial(T* pSlab, GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, SectionBias sectionBias, IMaterial** ppMaterial)
{
   CComPtr<ICastingRegions> regions;
   pSlab->get_CastingRegions(&regions);

   IndexType regionIdx;
   CComPtr<ICastingRegion> region;
   HRESULT hr = regions->FindRegionEx(ssMbrID, segIdx, Xs, sectionBias, &regionIdx, &region);
   if (FAILED(hr))
   {
      (*ppMaterial) = nullptr;
      return hr;
   }

   return region->get_Material(ppMaterial);
}

HRESULT GetMaterial(IBridgeDeck* deck, GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, SectionBias sectionBias, IMaterial** ppMaterial)
{
   HRESULT hr = S_OK;
   CComQIPtr<ICastSlab> castSlab(deck);
   CComQIPtr<IPrecastSlab> precastSlab(deck);
   CComQIPtr<IOverlaySlab> overlaySlab(deck);
   if (castSlab)
   {
      hr = GetMaterial<ICastSlab>(castSlab, ssMbrID, segIdx, Xs, sectionBias, ppMaterial);
   }
   else if (precastSlab)
   {
      hr = GetMaterial<IPrecastSlab>(precastSlab, ssMbrID, segIdx, Xs, sectionBias, ppMaterial);
   }
   else
   {
      ATLASSERT(overlaySlab);
      hr = overlaySlab->get_Material(ppMaterial);
   }
   return hr;
}

template <class T>
HRESULT GetMaterial(T* pSlab, Float64 Xb, SectionBias sectionBias, IMaterial** ppMaterial)
{
   CComPtr<ICastingRegions> regions;
   pSlab->get_CastingRegions(&regions);

   IndexType regionIdx;
   CComPtr<ICastingRegion> region;
   HRESULT hr = regions->FindRegion(Xb, sectionBias, &regionIdx, &region);
   if (FAILED(hr))
   {
      (*ppMaterial) = nullptr;
      return hr;
   }

   return region->get_Material(ppMaterial);
}

HRESULT GetMaterial(IBridgeDeck* deck, Float64 Xb, SectionBias sectionBias, IMaterial** ppMaterial)
{
   HRESULT hr = S_OK;
   CComQIPtr<ICastSlab> castSlab(deck);
   CComQIPtr<IPrecastSlab> precastSlab(deck);
   CComQIPtr<IOverlaySlab> overlaySlab(deck);
   if (castSlab)
   {
      hr = GetMaterial<ICastSlab>(castSlab, Xb, sectionBias, ppMaterial);
   }
   else if (precastSlab)
   {
      hr = GetMaterial<IPrecastSlab>(precastSlab, Xb, sectionBias, ppMaterial);
   }
   else
   {
      ATLASSERT(overlaySlab);
      hr = overlaySlab->get_Material(ppMaterial);
   }
   return hr;
}


inline Float64 ComputeStructuralHaunchDepth(ISuperstructureMemberSegment* segment, Float64 Xs, HaunchDepthMethod haunchMethod)
{
   if (haunchMethod == hdmHaunchIsZero)
   {
      return 0.0;
   }
   else if (haunchMethod == hdmHaunchEqualsFillet)
   {
      Float64 fillet;
      segment->get_Fillet(&fillet);
      return fillet;
   }
   else
   {
      ATLASSERT(haunchMethod == hdmHaunchIsParabolic);
      Float64 haunch;
      segment->ComputeHaunchDepth(Xs, &haunch);
      haunch = max(0.0, haunch); // don't allow negative haunch
      return haunch;
   }
}

/////////////////////////////////////////////////////////////////////////////
// CSectionCutTool
HRESULT CSectionCutTool::FinalConstruct()
{
   CComObject<CEffectiveFlangeWidthTool>* pTool;
   HRESULT hr = CComObject<CEffectiveFlangeWidthTool>::CreateInstance(&pTool);
   if ( FAILED(hr) || pTool == nullptr )
   {
      return E_FAIL;
   }

   m_EffFlangeTool = pTool;


   CComObject<CBridgeGeometryTool>* pBGTool;
   hr = CComObject<CBridgeGeometryTool>::CreateInstance(&pBGTool);
   if ( FAILED(hr) || pBGTool == nullptr )
   {
      return E_FAIL;
   }

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
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}

STDMETHODIMP CSectionCutTool::CreateLeftBarrierShape(IGenericBridge* bridge,Float64 station,IDirection* pDirection,IShape** ppShape)
{
   return CreateBarrierShape(qcbLeft,bridge,station,pDirection,ppShape);
}

STDMETHODIMP CSectionCutTool::CreateRightBarrierShape(IGenericBridge* bridge,Float64 station,IDirection* pDirection,IShape** ppShape)
{
   return CreateBarrierShape(qcbRight,bridge,station,pDirection,ppShape);
}

STDMETHODIMP CSectionCutTool::CreateLeftBarrierSection(IGenericBridge* bridge,Float64 station,VARIANT_BOOL bStructuralOnly,ISection** section)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(section);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   IDType profileID;
   bridge->get_ProfileID(&profileID);

   CComPtr<IProfile> profile;
   alignment->GetProfile(profileID,&profile);

   // Get left top point
   CComPtr<IStation> offsetStation;
   Float64 left_deck_offset; // distance from alignment to left edge of deck
   m_BridgeGeometryTool->DeckOffset(bridge,station,nullptr,qcbLeft,&offsetStation,&left_deck_offset);

   IDType surfaceID;   
   bridge->get_SurfaceID(&surfaceID);

   Float64 elev;
   profile->Elevation(surfaceID,CComVariant(offsetStation),left_deck_offset,&elev);

   CComPtr<ISidewalkBarrier> left_barrier;
   bridge->get_LeftBarrier(&left_barrier);

   if ( left_barrier == nullptr )
   {
      *section = nullptr;
      return S_FALSE;
   }

   CComPtr<ISidewalkBarrier> barrier;
   left_barrier->Clone(&barrier);

   // returns the whole railing system shape including sidewalk and interior railing
   CComPtr<IShape> shape;
   if ( bStructuralOnly == VARIANT_TRUE )
   {
      barrier->get_StructuralShape(&shape);
   }
   else
   {
      barrier->get_Shape(&shape);
   }


   if ( !shape )
   {
      *section = nullptr;
      return S_FALSE;
   }

   Float64 wearing_surface_adjustment = 0;
   VARIANT_BOOL vbHasFutureOverlay;
   bridge->HasFutureOverlay(&vbHasFutureOverlay);
   StageIndexType wearingSurfaceStage;
   bridge->get_WearingSurfaceStage(&wearingSurfaceStage);
   if (wearingSurfaceStage != INVALID_INDEX && vbHasFutureOverlay == VARIANT_FALSE)
   {
      bridge->get_WearingSurfaceDepth(&wearing_surface_adjustment);
   }

   CComQIPtr<IXYPosition> position(shape);
   position->Offset(left_deck_offset,elev - wearing_surface_adjustment);

   // use material for exterior barrier as material for entire section
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

   IDType profileID;
   bridge->get_ProfileID(&profileID);
   
   IDType surfaceID;
   bridge->get_SurfaceID(&surfaceID);
   CComPtr<IProfile> profile;
   alignment->GetProfile(profileID, &profile);

   // Get right top point
   CComPtr<IStation> offsetStation;
   Float64 right_deck_offset; // distance from alignment to right edge of deck
   m_BridgeGeometryTool->DeckOffset(bridge,station,nullptr,qcbRight,&offsetStation,&right_deck_offset);

   Float64 elev;
   profile->Elevation(surfaceID,CComVariant(offsetStation),right_deck_offset,&elev);

   CComPtr<ISidewalkBarrier> right_barrier;
   bridge->get_RightBarrier(&right_barrier);

   if ( right_barrier == nullptr )
   {
      *section = nullptr;
      return S_FALSE;
   }

   CComPtr<ISidewalkBarrier> barrier;
   right_barrier->Clone(&barrier);

   // returns the whole railing system shape including sidewalk and interior railing
   CComPtr<IShape> shape;
   if ( bStructuralOnly == VARIANT_TRUE )
   {
      barrier->get_StructuralShape(&shape);
   }
   else
   {
      barrier->get_Shape(&shape);
   }

   if ( !shape )
   {
      *section = nullptr;
      return S_FALSE;
   }

   Float64 wearing_surface_adjustment = 0;
   VARIANT_BOOL vbHasFutureOverlay;
   bridge->HasFutureOverlay(&vbHasFutureOverlay);
   StageIndexType wearingSurfaceStage;
   bridge->get_WearingSurfaceStage(&wearingSurfaceStage);
   if (wearingSurfaceStage != INVALID_INDEX && vbHasFutureOverlay == VARIANT_FALSE)
   {
      bridge->get_WearingSurfaceDepth(&wearing_surface_adjustment);
   }

   CComQIPtr<IXYPosition> position(shape);
   position->Offset(right_deck_offset,elev - wearing_surface_adjustment);

   // use material for exterior barrier as material for entire section
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

STDMETHODIMP CSectionCutTool::CreateSlabShape(IGenericBridge* bridge,Float64 station,IDirection* pDirection,VARIANT_BOOL bIncludeHaunch,IShape** shape)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(shape);

   CComPtr<IBridgeGeometry> bridgeGeometry;
   bridge->get_BridgeGeometry(&bridgeGeometry);

   CComPtr<ICogoModel> cogoModel;
   bridgeGeometry->get_CogoModel(&cogoModel);

   CComPtr<ICogoEngine> cogoEngine;
   cogoModel->get_Engine(&cogoEngine);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   IDType profileID;
   bridgeGeometry->get_ProfileID(&profileID);

   IDType surfaceID;
   bridgeGeometry->get_SurfaceID(&surfaceID);

   // many of the calls below are most efficient with a station object
   // create one and use it.
   CComPtr<IStation> objStation;
   objStation.CoCreateInstance(CLSID_Station);
   objStation->SetStation(INVALID_INDEX,station); // normalized station

   CComPtr<IDirection> dirCutLine;
   bool bIsNormal = false;
   if ( pDirection == nullptr )
   {
      alignment->GetNormal(CComVariant(objStation),&dirCutLine); // normal to the right
      dirCutLine->IncrementBy(CComVariant(M_PI)); // normal to the left
      bIsNormal = true;
   }
   else
   {
      dirCutLine = pDirection;
   }

   Float64 dirCutLineValue;
   dirCutLine->get_Value(&dirCutLineValue);

   CComPtr<IPoint2d> pntAlignment; // point on the alignment at station
   alignment->LocatePoint(CComVariant(objStation),omtAlongDirection,0.0,CComVariant(dirCutLine),&pntAlignment);

   CComPtr<IProfile> profile;
   alignment->GetProfile(profileID, &profile);

   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   CComQIPtr<ICastSlab> cip(deck);
   CComQIPtr<IPrecastSlab> sip(deck);
   CComQIPtr<IOverlaySlab> overlay(deck);
   ATLASSERT(cip != nullptr || sip != nullptr || overlay != nullptr);

   // create the deck shape object
   CComPtr<IPolyShape> slab_shape;
   slab_shape.CoCreateInstance(CLSID_PolyShape);

   // get left and right deck edge points
   CComPtr<IPoint2d> pntLeftDeckEdge, pntRightDeckEdge;
   m_BridgeGeometryTool->DeckEdgePoint(bridge,station,dirCutLine,qcbLeft,&pntLeftDeckEdge);
   m_BridgeGeometryTool->DeckEdgePoint(bridge,station,dirCutLine,qcbRight,&pntRightDeckEdge);

   // get the location (station and offset) of the deck edge points
   CComPtr<IStation> leftOffsetStation;
   Float64 left_deck_edge_normal_offset;
   alignment->StationAndOffset(pntLeftDeckEdge,&leftOffsetStation,&left_deck_edge_normal_offset);

   CComPtr<IStation> rightOffsetStation;
   Float64 right_deck_edge_normal_offset;
   alignment->StationAndOffset(pntRightDeckEdge,&rightOffsetStation,&right_deck_edge_normal_offset);

   // get the offset from the alignment, to the deck edge points, measured along the cut direction
   Float64 left_deck_offset;
   pntAlignment->DistanceEx(pntLeftDeckEdge,&left_deck_offset); // distance is always a positive value
   left_deck_offset *= ::BinarySign(left_deck_edge_normal_offset); // match the sign of the edge offset

   Float64 right_deck_offset;
   pntAlignment->DistanceEx(pntRightDeckEdge,&right_deck_offset);
   right_deck_offset *= ::BinarySign(right_deck_edge_normal_offset);

   // Get roadway surface at cut station
   CComPtr<ISurface> surface;
   IDType id;
   profile->GetSurfaceContainingStation(CComVariant(objStation),&id,&surface);
   ATLASSERT(id == surfaceID); // expected to find the one and only surface we created
   ATLASSERT(surface != nullptr); // there must be a surface

   // get the alignment point
   IndexType alignmentPointIdx;
   surface->get_AlignmentPoint(&alignmentPointIdx);

   // get deck dimensions
   Float64 gross_depth;
   deck->get_GrossDepth(&gross_depth);

   std::array<Float64,2> overhang_depth;
   std::array<DeckOverhangTaper,2> overhang_taper;
   if ( cip )
   {
      cip->GetOverhang(&overhang_depth[qcbLeft], &overhang_taper[qcbLeft], &overhang_depth[qcbRight], &overhang_taper[qcbRight]);
   }
   else if ( sip )
   {
      sip->GetOverhang(&overhang_depth[qcbLeft], &overhang_taper[qcbLeft], &overhang_depth[qcbRight], &overhang_taper[qcbRight]);
   }
   else
   {
      overhang_depth[qcbLeft] = gross_depth;
      overhang_depth[qcbRight] = gross_depth;
      overhang_taper[qcbLeft] = dotNone;
      overhang_taper[qcbRight] = dotNone;
   }

   // Top of Deck
   // Work right to left across the top of deck.

   // Begin at Right Edge, Bottom of deck
   // This is the same point as top of deck, except for the overhang_depth
   Float64 elev;
   profile->Elevation(surfaceID,CComVariant(rightOffsetStation), right_deck_edge_normal_offset,&elev);
   slab_shape->AddPoint(right_deck_offset,elev-overhang_depth[qcbRight]);

   // Right Edge, Top
   slab_shape->AddPoint(right_deck_offset,elev);

   // work right to left across the deck and get the elevation and offset of each ridge point
   // with offset being measured from the alignment point

   // create a surface template at the cut station. this is the top of the slab
   IndexType nRidgePoints;
   CComPtr<ISurfaceProfile> surfaceProfile;
   if ( bIsNormal )
   {
      // surface templates are faster than surface profiles but they only work if the section
      // cut is normal to the alignment
      CComPtr<ISurfaceTemplate> surfaceTemplate;
      surface->CreateSurfaceTemplateSectionCut(CComVariant(objStation),VARIANT_TRUE,&surfaceTemplate);
      surfaceTemplate->get_Count(&nRidgePoints); // this is number of segments
      nRidgePoints++; // this is the number of ridge points
      for ( IndexType ridgePointIdx = nRidgePoints-1; ridgePointIdx != INVALID_INDEX; ridgePointIdx-- )
      {
         // get offset (measured from the alignment) and the elevation of the ridge point
         Float64 offset, elev;
         profile->GetRidgePointOffsetAndElevation(surfaceID,CComVariant(objStation),alignmentPointIdx,ridgePointIdx,&offset,&elev);

         // if the ridge point is between the edges of the deck, add it to the deck shape
         if ( ::InRange(left_deck_offset,offset,right_deck_offset) )
         {
            slab_shape->AddPoint(offset,elev);
         }
      }
   }
   else
   {
      surface->CreateSurfaceProfileSectionCut(CComVariant(objStation),CComVariant(dirCutLine),VARIANT_TRUE,&surfaceProfile);
      surfaceProfile->get_Count(&nRidgePoints); // this is the number of surface points
      for ( IndexType ridgePointIdx = nRidgePoints-1; ridgePointIdx != INVALID_INDEX; ridgePointIdx-- )
      {
         // get offset (measured from the alignment) and the elevation of the surface point
         Float64 offset, elev;
         surfaceProfile->GetSurfacePointElevation(ridgePointIdx,&offset,&elev);

         // if the ridge point is between the edges of the deck, add it to the deck shape
         if ( ::InRange(left_deck_offset,offset,right_deck_offset) )
         {
            slab_shape->AddPoint(offset,elev);
         }
      }
   }
   
   // Left Edge - top of deck
   profile->Elevation(surfaceID,CComVariant(leftOffsetStation), left_deck_edge_normal_offset,&elev);
   slab_shape->AddPoint(left_deck_offset,elev);

   // Left Edge - bottom of deck
   slab_shape->AddPoint(left_deck_offset,elev - overhang_depth[qcbLeft]);

   // work left to right across bottom of deck back to the bottom-right corner
   if ( bIncludeHaunch == VARIANT_TRUE )
   {
      std::vector<GirderPointRecord> vGirderPoints = GetGirderPoints(bridge,objStation,dirCutLine);
      if ( vGirderPoints.size() == 0 )
      {
         // cut does not intersect any girders. make the bottom of the slab parallel the top of the slab
         for ( IndexType ridgePointIdx = 0; ridgePointIdx < nRidgePoints; ridgePointIdx++ )
         {
            // get offset (measured from the alignment) and the elevation of the ridge point
            Float64 offset, elev;
            if ( bIsNormal )
            {
               profile->GetRidgePointOffsetAndElevation(surfaceID,CComVariant(objStation),ridgePointIdx,alignmentPointIdx,&offset,&elev);
            }
            else
            {
               surfaceProfile->GetSurfacePointElevation(ridgePointIdx,&offset,&elev);
            }

            // if the ridge point is between the edges of the deck, add it to the deck shape
            if ( ::InRange(left_deck_offset,offset,right_deck_offset) )
            {
               slab_shape->AddPoint(offset,elev-gross_depth);
            }
         }
      }
      else
      {
         // Haunches along bottom of slab
         // haunch is defined by 6 (or more) points per mating surface
         // Points 3 and 4, and possibily additional points in between, are defined by the section mating surface profile
         // If the section does not provide a mating surface profile, use points 2 and 5 with an elevation offset equal to the build up depth
         //
         //    --------1\      /6------
         //             2      5
         //             |      |
         //             3------4
         //
         for ( const auto& girderPoint : vGirderPoints)
         {
            CComPtr<ISuperstructureMember> ssmbr;
            bridge->get_SuperstructureMember(girderPoint.girderID,&ssmbr);

            CComPtr<ISuperstructureMemberSegment> segment;
            ssmbr->get_Segment(girderPoint.segIdx,&segment);

            // orientation of girder in radians... 0 = plumb, rotated CW is +
            Float64 orientation;
            segment->get_Orientation(&orientation); // section view orientation

            CComPtr<IShape> girder_shape;
            segment->get_GirderShape(girderPoint.Xs,sbLeft,cstBridge,&girder_shape);

            CComQIPtr<IGirderSection> girder_section(girder_shape);
            ATLASSERT(girder_section);

            // get skew angle. its not just the pier skew
            CComPtr<IGirderLine> girderLine;
            segment->get_GirderLine(&girderLine);
            CComPtr<IDirection> objGirderLineDirection;
            girderLine->get_Direction(&objGirderLineDirection);
            Float64 dirGirderLine;
            objGirderLineDirection->get_Value(&dirGirderLine);
            Float64 skew = fabs(dirCutLineValue - (dirGirderLine + PI_OVER_2));

            Float64 cos_skew = cos(skew); // we only want to do this once

            Float64 min_top_flange_thickness;
            girder_section->get_MinTopFlangeThickness(&min_top_flange_thickness);

            Float64 haunch = 0;
            segment->ComputeHaunchDepth(girderPoint.Xs,&haunch);

            FilletShape fillet_shape;
            segment->get_FilletShape(&fillet_shape);

            Float64 xfillet=0;
            if (fillet_shape == flsAngled)
            {
               segment->get_Fillet(&xfillet);
            }

            Float64 yfillet = min(xfillet, haunch); // don't draw fillet deeper than the haunch depth

            Float64 elclg; // elevation at CL of girder
            profile->Elevation(surfaceID,CComVariant(girderPoint.objGirderStation), girderPoint.normalOffset,&elclg);

            MatingSurfaceIndexType nMatingSurfaces;
            girder_section->get_MatingSurfaceCount(&nMatingSurfaces);
            for ( CollectionIndexType msIdx = 0; msIdx < nMatingSurfaces; msIdx++ )
            {
               Float64 ms_width;
               girder_section->get_MatingSurfaceWidth(msIdx, VARIANT_FALSE, &ms_width);

               Float64 ms_location; // relative to center of beam
               girder_section->get_MatingSurfaceLocation(msIdx, VARIANT_FALSE, &ms_location);

               // adjust for skew
               ms_width /= cos_skew;
               ms_location /= cos_skew;

               CComPtr<IPoint2dCollection> matingSurfaceProfile;
               bool bHasMSProfile = (FAILED(girder_section->get_MatingSurfaceProfile(msIdx, VARIANT_FALSE, &matingSurfaceProfile)) || matingSurfaceProfile == nullptr) ? false : true;

               Float64 x23; // x location of points 2 & 3
               Float64 x45; // x location of points 4 & 5
               Float64 xcl; // x location of centerline of flange
               xcl = girderPoint.cutLineOffset + ms_location;
               x23 = xcl - ms_width / 2;
               x45 = xcl + ms_width / 2;

               Float64 el23; // deck elevation above points 2 & 3
               Float64 el45; // deck elevation above points 4 & 5
               Float64 elcl; // deck elevation above centerline of flange
               profile->Elevation(surfaceID, CComVariant(girderPoint.objGirderStation), x23, &el23);
               profile->Elevation(surfaceID, CComVariant(girderPoint.objGirderStation), x45, &el45);
               profile->Elevation(surfaceID, CComVariant(girderPoint.objGirderStation), xcl, &elcl);

               if (InRange(left_deck_offset, x23, right_deck_offset) && InRange(left_deck_offset, x45, right_deck_offset))
               {
                  Float64 el3; // top of girder elevation on left side of flange (point 3)
                  Float64 el4; // top of girder elevation on right side of flange (point 4)
                  el3 = elclg - gross_depth - haunch - (ms_location - ms_width / 2)*orientation;
                  el4 = elclg - gross_depth - haunch - (ms_location + ms_width / 2)*orientation;

                  if (!bHasMSProfile)
                  {
                     if (girderPoint.girderLocation != ltLeftExteriorGirder || msIdx != 0 || overhang_taper[qcbLeft] == dotNone || overhang_taper[qcbLeft] == dotBottomTopFlange)
                     {
                        // only use this point if this is an interior girder or an interior web
                        // on the first girder, or the deck overhang is not tapered
                        Float64 dy;
                        Float64 dx;
                        if (girderPoint.girderLocation != ltLeftExteriorGirder || msIdx != 0)
                        {
                           // not exterior girder, or exterior web of exterior girder
                           dy = gross_depth;
                           dx = 0;
                        }
                        else
                        {
                           // this is the left exterior web on the left exterior girder
                           if (overhang_taper[qcbLeft] == dotNone)
                           {
                              dy = overhang_depth[qcbLeft];
                              dx = 0;
                           }
                           else
                           {
                              // slab overhang taper goes to the bottom of the top flange
                              dy = gross_depth + haunch - (elcl - el23) + min_top_flange_thickness;

                              Float64 slope;
                              profile->CrossSlope( surfaceID, CComVariant(girderPoint.objGirderStation),x23, &slope);
                              dx = slope*min_top_flange_thickness / cos(skew);
                           }
                        }

                        if (overhang_taper[qcbLeft] == dotBottomTopFlange || xfillet == 0.0 || girderPoint.girderLocation == ltLeftExteriorGirder)
                        {
                           slab_shape->AddPoint(x23 - dx, el23 - dy); // 1,2
                        }
                        else
                        {
                           slab_shape->AddPoint(x23 - dx - xfillet, el23 - dy); // 1
                           slab_shape->AddPoint(x23 - dx, el23 - dy - yfillet); // 2
                        }
                     }
                  }

                  if (!bHasMSProfile)
                  {
                     slab_shape->AddPoint(x23, el3); // 3
                     slab_shape->AddPoint(x45, el4); // 4
                  }
                  else
                  {
                     // points 3 and 4 and possibly points between 3 and 4
                     CComQIPtr<IXYPosition> position(girder_section);
                     CComPtr<IPoint2d> pntTC;
                     position->get_LocatorPoint(lpTopCenter, &pntTC);

                     CComPtr<IEnumPoint2d> enum_points;
                     matingSurfaceProfile->get__Enum(&enum_points);
                     CComPtr<IPoint2d> msPoint;
                     while (enum_points->Next(1, &msPoint, nullptr) != S_FALSE)
                     {
                        Float64 x, y;
                        if (!IsZero(orientation))
                        {
                           msPoint->RotateEx(pntTC, -orientation);
                        }
                        msPoint->Location(&x, &y);
                        x /= cos_skew;

                        slab_shape->AddPoint(x, y);
                        msPoint.Release();
                     }
                  }
               }

               if (girderPoint.girderLocation != ltRightExteriorGirder || msIdx != nMatingSurfaces - 1 || overhang_taper[qcbRight] == dotNone || overhang_taper[qcbRight] == dotBottomTopFlange)
               {
                  // only use this point if this is an interior girder or an interior web
                  // on the last girder, or the deck overhang is not tapered
                  if (!bHasMSProfile)
                  {
                     Float64 dy;
                     Float64 dx;
                     if (girderPoint.girderLocation != ltRightExteriorGirder || msIdx != nMatingSurfaces - 1)
                     {
                        // not exterior girder, or exterior web of exterior girder
                        dy = gross_depth;
                        dx = 0;
                     }
                     else
                     {
                        if (overhang_taper[qcbRight] == dotNone)
                        {
                           dy = overhang_depth[qcbRight];
                           dx = 0;
                        }
                        else
                        {
                           dy = gross_depth + haunch - (elcl - el45) + min_top_flange_thickness; // slab overhang to bottom of girder top flange

                           Float64 slope;
                           profile->CrossSlope(surfaceID, CComVariant(girderPoint.objGirderStation), x45, &slope);
                           dx = slope*min_top_flange_thickness / cos(skew);
                        }
                     }

                     if (overhang_taper[qcbRight] == dotBottomTopFlange || xfillet == 0.0 || girderPoint.girderLocation == ltRightExteriorGirder)
                     {
                        slab_shape->AddPoint(x45 + dx, el45 - dy); // 5, 6
                     }
                     else
                     {
                        slab_shape->AddPoint(x45 + dx, el45 - dy - yfillet); // 5
                        slab_shape->AddPoint(x45 + dx + xfillet, el45 - dy); // 6
                     }
                  }
               }
            }
         }
      }
   }
   else
   {
      // No haunch.... need to model the bottom of the slab
      if (bIsNormal)
      {
         // surface templates are faster than surface profiles but they only work if the section
         // cut is normal to the alignment
         for ( IndexType ridgePointIdx = 0; ridgePointIdx < nRidgePoints; ridgePointIdx++)
         {
            // get offset (measured from the alignment) and the elevation of the ridge point
            Float64 offset, elev;
            profile->GetRidgePointOffsetAndElevation(surfaceID, CComVariant(objStation), ridgePointIdx, alignmentPointIdx, &offset, &elev);

            // if the ridge point is between the edges of the deck, add it to the deck shape
            if (::InRange(left_deck_offset, offset, right_deck_offset))
            {
               slab_shape->AddPoint(offset, elev - gross_depth);
            }
         }
      }
      else
      {
         for (IndexType ridgePointIdx = 0; ridgePointIdx < nRidgePoints; ridgePointIdx++)
         {
            // get offset (measured from the alignment) and the elevation of the ridge point
            Float64 offset, elev;
            surfaceProfile->GetSurfacePointElevation(ridgePointIdx, &offset, &elev);

            // if the ridge point is between the edges of the deck, add it to the deck shape
            if (::InRange(left_deck_offset, offset, right_deck_offset))
            {
               slab_shape->AddPoint(offset, elev - gross_depth);
            }
         }
      }
   }

   // if there is a wearing surface that is not a future overlay,
   // lower the deck because the finished grade is the top of the wearing surface
   VARIANT_BOOL vbHasFutureOverlay;
   bridge->HasFutureOverlay(&vbHasFutureOverlay);
   StageIndexType wearingSurfaceStage;
   bridge->get_WearingSurfaceStage(&wearingSurfaceStage);
   if (wearingSurfaceStage != INVALID_INDEX && vbHasFutureOverlay == VARIANT_FALSE)
   {
      Float64 wearing_surface_depth;
      bridge->get_WearingSurfaceDepth(&wearing_surface_depth);

      CComQIPtr<IXYPosition> position(slab_shape);
      position->Offset(0, -wearing_surface_depth);
   }

   slab_shape.QueryInterface(shape);

   return S_OK;
}

STDMETHODIMP CSectionCutTool::GetDeckProperties(IGenericBridge* bridge,IndexType nSectionsPerSpan,Float64* pSurfaceArea,Float64* pVolume)
{
   CHECK_IN(bridge);
   CHECK_RETVAL(pSurfaceArea);
   CHECK_RETVAL(pVolume);

   if ( nSectionsPerSpan < 1 )
   {
      return E_INVALIDARG;
   }

   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   // No deck, no surface area or volume
   if ( deck == nullptr )
   {
      *pSurfaceArea = 0;
      *pVolume = 0;
      return S_OK;
   }

   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);
   PierIndexType nPiers;
   piers->get_Count(&nPiers);

   SpanIndexType nSpans = nPiers-1;

   Float64 V = 0;
   Float64 S = 0;

   CComPtr<IBridgePier> startPier;
   piers->get_Item(0,&startPier);
   CComPtr<IStation> objStartStation;
   startPier->get_Station(&objStartStation);
   Float64 startStation;
   alignment->ConvertToNormalizedStation(CComVariant(objStartStation), &startStation);

   Float64 station = startStation;
   CComPtr<IShape> prevDeckShape;
   CreateSlabShape(bridge,startStation,nullptr,VARIANT_TRUE/*include haunch*/,&prevDeckShape);

   Float64 prevPerimeter;
   prevDeckShape->get_Perimeter(&prevPerimeter);

   CComPtr<IShapeProperties> shapeProps;
   prevDeckShape->get_ShapeProperties(&shapeProps);
   Float64 prevArea;
   shapeProps->get_Area(&prevArea);

   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      PierIndexType endPierIdx = (spanIdx+1);
      CComPtr<IBridgePier> endPier;
      piers->get_Item(endPierIdx,&endPier);
      CComPtr<IStation> objEndStation;
      endPier->get_Station(&objEndStation);
      Float64 endStation;
      alignment->ConvertToNormalizedStation(CComVariant(objEndStation), &endStation);

      Float64 increment = (endStation - startStation)/nSectionsPerSpan;

      for ( IndexType i = 1; i < nSectionsPerSpan; i++ )
      {
         station += increment;

         CComPtr<IShape> deckShape;
         CreateSlabShape(bridge,station,nullptr,VARIANT_TRUE/*include haunch*/,&deckShape);

         Float64 perimeter;
         deckShape->get_Perimeter(&perimeter);
         Float64 dS = increment*(prevPerimeter + perimeter)/2;
         S += dS;

         shapeProps.Release();
         deckShape->get_ShapeProperties(&shapeProps);

         Float64 area;
         shapeProps->get_Area(&area);
         Float64 dV = increment*(prevArea + area)/2;
         V += dV;

         // The end for this loop is the previous values in the next loop
         prevPerimeter = perimeter;
         prevArea = area;
      } // next section

      startStation = endStation;
   } // next span

   *pSurfaceArea = S;
   *pVolume = V;

   return S_OK;
}

STDMETHODIMP CSectionCutTool::GetStructuralHaunchDepth(IGenericBridge * bridge, GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, HaunchDepthMethod haunchMethod, Float64 * pHaunchDepth)
{
   CHECK_RETVAL(pHaunchDepth);

   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);
   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   // Get haunch depth
   *pHaunchDepth = ComputeStructuralHaunchDepth(segment, Xs, haunchMethod);

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

STDMETHODIMP CSectionCutTool::CreateGirderSectionBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 Xg,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,StageIndexType stageIdx,
                                          SectionPropertyMethod sectionPropMethod, HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile, IndexType* pBeamIdx, IndexType* pSlabIdx,ISection** section)
{
   CComPtr<ISuperstructureMember> ssMbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssMbr);

   Float64 Xs;
   SegmentIndexType segIdx;
   CComPtr<ISuperstructureMemberSegment> segment;
   ssMbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);

   return CreateGirderSectionBySegment(bridge,ssMbrID,segIdx,Xs,sectionBias,coordinateSystem,stageIdx,sectionPropMethod,haunchMethod,bFollowMatingSurfaceProfile,pBeamIdx,pSlabIdx,section);
}

STDMETHODIMP CSectionCutTool::CreateGirderSectionBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,
   StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod, HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile, IndexType* pBeamIdx, IndexType* pSlabIdx,ISection** section)
{
   // Validate input
   CHECK_RETOBJ(section);
   CHECK_IN(bridge);

   return CreateCompositeSection(bridge,ssMbrID,segIdx,Xs,sectionBias,coordinateSystem,stageIdx,sectionPropMethod,haunchMethod,bFollowMatingSurfaceProfile,pBeamIdx,pSlabIdx,section);
}

STDMETHODIMP CSectionCutTool::CreateNetDeckSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,StageIndexType stageIdx,HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile,ISection** section)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(section);

   // the girder section is required to create the deck shape
   CComPtr<ISection> ncsection;
   HRESULT hr = CreateNoncompositeSection(bridge,ssMbrID,segIdx,Xs, sectionBias,coordinateSystem,stageIdx,spmGrossNoncomposite,&ncsection);
   if ( FAILED(hr) )
   {
      return hr;
   }

   // mess of casting here to get right interface
   CComQIPtr<ICompositeSectionEx> cmpSection(ncsection);
   CComPtr<ICompositeSectionItemEx> si;
   cmpSection->get_Item(0,&si);
   CComPtr<IShape> sishape;
   si->get_Shape(&sishape);
   CComQIPtr<IGirderSection> girder_section(sishape);
   ATLASSERT(girder_section);

   return CreateDeckSection(bridge,ssMbrID,segIdx,Xs, sectionBias, stageIdx,spmNet,haunchMethod,bFollowMatingSurfaceProfile,girder_section,section);
}

STDMETHODIMP CSectionCutTool::CreateDeckAnalysisShape(IGenericBridge * bridge,IGirderSection* pSection, GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, SectionBias sectionBias, Float64 haunchDepth, BOOL bFollowMatingSurfaceProfile, StageIndexType stageIdx, IShape ** shape)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(shape);

   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   // this model doesn't have a deck... get the heck outta here
   if (deck == nullptr)
   {
      return S_FALSE;
   }

   VARIANT_BOOL bComposite;
   deck->get_Composite(&bComposite);
   if (bComposite == VARIANT_FALSE)
   {
      // if deck is not composite, we are done
      return S_FALSE;
   }

   CComPtr<IMaterial> material;
   HRESULT hr = GetMaterial(deck, ssMbrID, segIdx, Xs, sectionBias, &material);
   if (FAILED(hr) || material == nullptr)
   {
      ATLASSERT(false); // if this asserts, then the casting region model may be wrong
      return S_FALSE; // no casting region in this location... e.g. no deck at this location
   }

   Float64 Econc;
   material->get_E(stageIdx, &Econc);

   if (IsZero(Econc))
   {
      // Deck isn't cast yet, we are done
      return S_FALSE;
   }

   return CreateDeckShape(bridge, ssMbrID, segIdx, Xs, sectionBias, haunchDepth, bFollowMatingSurfaceProfile, pSection, shape);
}

STDMETHODIMP CSectionCutTool::CreateBridgeSection(IGenericBridge* bridge,Float64 Xb,SectionBias sectionBias,StageIndexType stageIdx,BarrierSectionCut bsc,ISection** section)
{
   // location is measured along the alignment, from the station of the first pier. The section cut is made
   // normal to the alignment.
   HRESULT hr = S_OK;
   
   Float64 bottom_deck_elevation = -DBL_MAX;

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IBridgePier> first_pier;
   piers->get_Item(0,&first_pier);

   CComPtr<IStation> station;
   first_pier->get_Station(&station);

   Float64 first_pier_station;
   station->get_Value(&first_pier_station);

   Float64 target_station = first_pier_station + Xb;

   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   // Need to determine span,girder,location along each girder line so we can call CreateNoncompositeSection correctly
   CComPtr<ICompositeSectionEx> bridge_section;
   bridge_section.CoCreateInstance(CLSID_CompositeSectionEx);

   CComPtr<IEnumSuperstructureMembers> enumSSMbrs;
   bridge->get__EnumSuperstructureMembers(&enumSSMbrs);
   CComPtr<ISuperstructureMember> ssMbr;
   while ( enumSSMbrs->Next(1,&ssMbr,nullptr) != S_FALSE )
   {
      GirderIDType ssMbrID;
      ssMbr->get_ID(&ssMbrID);

      SegmentIndexType nSegments;
      ssMbr->get_SegmentCount(&nSegments);
      Float64 brgOffset = 0;
      Float64 endDist = 0;
      for ( SegmentIndexType segIdx = 0; segIdx < nSegments; segIdx++ )
      {
         CComPtr<ISuperstructureMemberSegment> segment;
         ssMbr->get_Segment(segIdx,&segment);

         CComPtr<IGirderLine> girderLine;
         segment->get_GirderLine(&girderLine);

         if (segIdx == 0 )
         {
            girderLine->get_BearingOffset(etStart,&brgOffset);
            girderLine->get_EndDistance(etStart,&endDist);
         }

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
         alignment->StationAndOffset(pntStart,&station,&offset);
         station->get_Value(&startStation);
         station.Release();
         alignment->StationAndOffset(pntEnd,&station,&offset);
         station->get_Value(&endStation);

         if ( ::InRange(startStation,target_station,endStation) )
         {
            Float64 dist_from_start_of_segment = target_station - startStation;

            // Create a noncomposite section for the segment that is being cut
            CComPtr<ISection> girder_section;
            CreateNoncompositeSection(bridge,ssMbrID,segIdx,dist_from_start_of_segment,sectionBias,cstBridge,stageIdx,spmGross,&girder_section);

            if ( girder_section == nullptr )
            {
               continue; // this girder does not cross the section cut... must be a short, highly skewed bridge
            }

            CComPtr<IRect2d> boundbox;
            girder_section->get_BoundingBox(&boundbox);
            Float64 top;
            boundbox->get_Top(&top);

            bottom_deck_elevation = Max(bottom_deck_elevation,top);
            
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
   hr = CreateBridgeDeckSection(bridge,Xb,sectionBias,stageIdx,bottom_deck_elevation,&deckitem);
   if ( FAILED(hr) )
   {
      return hr;
   }

   if ( deckitem )
   {
      bridge_section->AddSectionEx(deckitem);
   }


   // include the traffic barrier
   VARIANT_BOOL bStructuralOnly = (bsc == bscStructurallyContinuousOnly ? VARIANT_TRUE : VARIANT_FALSE);
   if ( bsc != bscNone )
   {
      Float64 station = DistanceToStation(bridge,Xb);

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

STDMETHODIMP CSectionCutTool::CreateLongitudinalJointShapeBySSMbr(IGenericBridge* bridge, GirderIDType ssMbrID, Float64 Xg, SectionCoordinateSystemType coordinateSystem, IShape** ppLeftJointShape, IShape** ppRightJointShape)
{
   CComPtr<ISuperstructureMember> ssMbr;
   bridge->get_SuperstructureMember(ssMbrID, &ssMbr);

   Float64 Xs;
   SegmentIndexType segIdx;
   CComPtr<ISuperstructureMemberSegment> segment;
   ssMbr->GetDistanceFromStartOfSegment(Xg, &Xs, &segIdx, &segment);

   return CreateLongitudinalJointShapeBySegment(bridge, ssMbrID, segIdx, Xs, coordinateSystem, ppLeftJointShape,ppRightJointShape);
}

STDMETHODIMP CSectionCutTool::CreateLongitudinalJointShapeBySegment(IGenericBridge* bridge, GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, SectionCoordinateSystemType coordinateSystem, IShape** ppLeftJointShape, IShape** ppRightJointShape)
{
   // Validate input
   CHECK_RETOBJ(ppLeftJointShape);
   CHECK_RETOBJ(ppRightJointShape);
   CHECK_IN(bridge);

   return CreateJointShapes(bridge, ssMbrID, segIdx, Xs,coordinateSystem, ppLeftJointShape,ppRightJointShape);
}

STDMETHODIMP CSectionCutTool::CreateGirderShapeBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 Xg,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,VARIANT_BOOL bIncludeDeck,HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile,IShape** ppShape)
{
   CComPtr<ISuperstructureMember> ssMbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssMbr);

   Float64 Xs;
   SegmentIndexType segIdx;
   CComPtr<ISuperstructureMemberSegment> segment;
   ssMbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);

   return CreateGirderShapeBySegment(bridge,ssMbrID,segIdx,Xs,sectionBias,coordinateSystem,bIncludeDeck,haunchMethod,bFollowMatingSurfaceProfile,ppShape);
}

STDMETHODIMP CSectionCutTool::CreateGirderShapeBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,VARIANT_BOOL bIncludeDeck,HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile,IShape** ppShape)
{
   // Validate input
   CHECK_RETOBJ(ppShape);
   CHECK_IN(bridge);

   return CreateGirderShape(bridge,ssMbrID,segIdx,Xs,sectionBias,coordinateSystem,bIncludeDeck,haunchMethod,bFollowMatingSurfaceProfile,ppShape);
}

HRESULT CSectionCutTool::CreateCompositeSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod, HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile, IndexType* pBeamIdx, IndexType* pSlabIdx,ISection** section)
{
   CComPtr<ISection> ncsection;
   HRESULT hr = CreateNoncompositeSection(bridge,ssMbrID,segIdx,Xs,sectionBias,coordinateSystem,stageIdx,sectionPropMethod,&ncsection);
   if ( FAILED(hr) )
   {
      return hr;
   }

   (*section) = ncsection;
   (*section)->AddRef();

   *pBeamIdx = 0;
   *pSlabIdx = INVALID_INDEX; // at this point, we have no slab

   // for net properties, we only want the girder
   if ( sectionPropMethod == spmGrossNoncomposite || sectionPropMethod == spmTransformedNoncomposite || sectionPropMethod == spmNet )
   {
      return S_OK;
   }

   // mess of casting here to get right interface
   CComQIPtr<ICompositeSectionEx> cmpSection(ncsection);
   CComPtr<ICompositeSectionItemEx> si;
   cmpSection->get_Item(0,&si);
   CComPtr<IShape> sishape;
   si->get_Shape(&sishape);
   CComQIPtr<IGirderSection> girder_section(sishape);

   CComPtr<ISection> deckSection;
   hr = CreateDeckSection(bridge,ssMbrID,segIdx,Xs,sectionBias,stageIdx,sectionPropMethod,haunchMethod,bFollowMatingSurfaceProfile,girder_section,&deckSection);
   if ( FAILED(hr) )
   {
      return hr;
   }

   if ( hr == S_OK )
   {
      // put slab on top of beam
      CComQIPtr<IXYPosition> beam_position(cmpSection);

      Float64 xTC, yTC;
      CComPtr<IPoint2d> beam_top_center;

      CComQIPtr<IFlangedDeckedSection> flanged_section(girder_section);
      if (flanged_section)
      {
         CComPtr<IPoint2d> beam_bottom_center;
         flanged_section->GetBottomCLPoint(&beam_bottom_center);
         Float64 xBC, yBC;
         beam_bottom_center->Location(&xBC, &yBC);
         Float64 Hcl; // height at nominal centerline
         flanged_section->GetCLHeight(&Hcl);
         xTC = xBC;
         yTC = yBC + Hcl;

         beam_top_center.CoCreateInstance(CLSID_Point2d);
         beam_top_center->Move(xTC, yTC);
      }
      else
      {
         beam_position->get_LocatorPoint(lpTopCenter, &beam_top_center);
         beam_top_center->Location(&xTC,&yTC);
      }

      // Tricky: We need xTC to be at the CL of the top flange but,
      //         get_LocatorPoint above is based on the top CL of the girder bounding box. This works 
      //         for our needs if the top flange is wider than the bottom, or if the section is symmetric, but may
      //         not be true for assym box sections. So we may need to adjust xTC so it's centered on the top flange
      Float64 wTopLeft, wTopRight, wBotLeft, wBotRight;
      girder_section->get_TopWidth(&wTopLeft, &wTopRight);
      girder_section->get_BottomWidth(&wBotLeft, &wBotRight);

      // We could do a bunch of if() statements here before making an adjustment, but it's just easier and faster to
      // just compute how much we need to move xTC so that it's at the top CL flange(s).
      // Compute bounding box (bb) left/right edges -> wrt the nominal girder CL (as defined in library)
      Float64 bbleft = max(wTopLeft, wBotLeft);
      Float64 bbright = max(wTopRight, wBotRight);
      Float64 bbcl = (-bbleft + bbright) / 2.0;  // center of bb 

      Float64 topcl = (-wTopLeft + wTopRight) / 2.0; // center of top flange

      Float64 adjust = topcl - bbcl; // distance bounding box cl must be moved to get to top flange(s) cl

      if (!IsZero(adjust))
      {
         // make adjustment
         xTC += adjust;                   
         beam_top_center->Move(xTC, yTC);
      }

      // move the composite so all the rebar inside the deck moves too
      if (bFollowMatingSurfaceProfile == FALSE)
      {
         // if the deck shape follows the mating surface profile, it is in the correct position already
         CComQIPtr<IXYPosition> deck_position(deckSection);
         deck_position->put_LocatorPoint(lpBottomCenter, beam_top_center);
      }

      // can't put a composite section inside of another composite section so
      // take each section item from the deck and put it into the main composite 
      // section object

      // The slab is the next item in the container... get the item count,
      // which is the next index. This is the slab index
      CollectionIndexType nItems;
      cmpSection->get_Count(&nItems);
      *pSlabIdx = nItems;

      CComQIPtr<ICompositeSectionEx> cmpDeckSection(deckSection);
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
   
HRESULT CSectionCutTool::CreateDeckShape(IGenericBridge* bridge, GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, SectionBias sectionBias, Float64 haunchDepth,BOOL bFollowMatingSurfaceProfile,IGirderSection* pGirderSection, IShape** pShape)
{
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   // this model doesn't have a deck... get the heck outta here
   if ( deck == nullptr )
   {
      return S_FALSE;
   }

   // Need to get effective flange width of the slab
   Float64 effFlangew;
   m_EffFlangeTool->EffectiveFlangeWidthBySegment(bridge,ssMbrID,segIdx,Xs,&effFlangew);

   Float64 deck_width = effFlangew;

   // get structural thickness of deck
   Float64 structural_depth = 0;
   deck->get_StructuralDepth(&structural_depth);

   // location of top cl of girder
   CComQIPtr<IXYPosition> position(pGirderSection);
   CComPtr<IPoint2d> pntTC;
   position->get_LocatorPoint(lpTopCenter, &pntTC);
   Float64 xTC,yTC;
   pntTC->get_X(&xTC);
   pntTC->get_Y(&yTC);

   // Build a slab shape and add it to the section
   CComPtr<IShape> shape;

   if (IsZero(haunchDepth) && bFollowMatingSurfaceProfile == FALSE)
   {
      // No haunch - just use a rectangle
      CComPtr<IRectangle> slab;
      slab.CoCreateInstance(CLSID_Rect);
      slab->put_Height(structural_depth);
      slab->put_Width(deck_width);

      CComQIPtr<IXYPosition> rposition(slab);
      rposition->put_LocatorPoint(lpBottomCenter, pntTC);

      slab.QueryInterface(&shape);
   }
   else
   {
      // We have a haunch. Build a section that looks like below centered on girder CL
      //
      //    7---------------------6
      //    |                     |  .... we can have multiple of these if more than one mating surface
      //    8-------1       4-----5
      //            |       |
      //            |       |
      //            2---+---3
      //
      //                ^ the point "+" above is the origin of our slab cooridinates, located at top center of our beam
      //
      // haunch is defined by 4 (or more) points per mating surface
      // Points 2 and 3, and possibily addition points in between, are defined by the section mating surface profile
      // Points 5-8 come after all mating surface points are laid out
      // create the deck shape object
      CComPtr<IPolyShape> slab_shape;
      slab_shape.CoCreateInstance(CLSID_PolyShape);

      CComPtr<ISuperstructureMember> ssmbr;
      bridge->get_SuperstructureMember(ssMbrID,&ssmbr);
      CComPtr<ISuperstructureMemberSegment> segment;
      ssmbr->get_Segment(segIdx,&segment);

      Float64 ybhaunch = yTC;        // y location of bottom of haunch
      Float64 ybslab   = ybhaunch + haunchDepth; // y location of bottom of slab
      Float64 ytslab   = ybhaunch + haunchDepth + structural_depth; // y location of top of slab

      // orientation of girder in radians... 0 = plumb, rotated CW is positive
      Float64 orientation;
      segment->get_Orientation(&orientation); // section view orientation

      MatingSurfaceIndexType nMatingSurfaces;
      pGirderSection->get_MatingSurfaceCount(&nMatingSurfaces);

      // Determine out to out location of all mating surfaces. We will center our slab shape over this
      Float64 msleft, msright;
      Float64 msloc, mswid;
      pGirderSection->get_MatingSurfaceWidth(0, VARIANT_FALSE, &mswid);
      pGirderSection->get_MatingSurfaceLocation(0, VARIANT_FALSE, &msloc);
      msleft = msloc - mswid / 2.0;

      pGirderSection->get_MatingSurfaceWidth(nMatingSurfaces-1, VARIANT_FALSE, &mswid);
      pGirderSection->get_MatingSurfaceLocation(nMatingSurfaces-1, VARIANT_FALSE, &msloc);
      msright = msloc + mswid / 2.0;

      Float64 xms_cl = xTC + (msleft + msright) / 2.0; // CL of all mating surfaces in bridge coords. This is where our slab is centered over

      // loop over all mating surfaces and build our hanch shape (points 1-4ish)
      for ( CollectionIndexType msIdx = 0; msIdx < nMatingSurfaces; msIdx++ )
      {
         Float64 ms_width;
         pGirderSection->get_MatingSurfaceWidth(msIdx, VARIANT_FALSE, &ms_width);

         Float64 ms_location; // relative to center of beam
         pGirderSection->get_MatingSurfaceLocation(msIdx, VARIANT_FALSE, &ms_location);

         ms_location += xTC; // make relative bridge coords

         CComPtr<IPoint2dCollection> matingSurfaceProfile;
         bool bHasMSProfile = (FAILED(pGirderSection->get_MatingSurfaceProfile(msIdx, VARIANT_FALSE, &matingSurfaceProfile)) || matingSurfaceProfile == nullptr) ? false : true;

         Float64 x12; // x location of points 1 & 2
         Float64 x34; // x location of points 3 & 4
         Float64 xcl; // x location of centerline of flange
         xcl = ms_location;
         x12 = xcl - ms_width / 2;
         x34 = xcl + ms_width / 2;


         // points 2-3
         if (!bHasMSProfile)
         {
            slab_shape->AddPoint(x12, ybslab); // 1
            slab_shape->AddPoint(x12, ybhaunch); // 2
            slab_shape->AddPoint(x34, ybhaunch); // 3
            slab_shape->AddPoint(x34, ybslab); // 4
         }
         else
         {
            // points 2 and 3 and possibly points between 2 and 3
            CComPtr<IPoint2d> msPoint;

            // Point 1
            matingSurfaceProfile->get_Item(0, &msPoint);
            Float64 x, y;
            msPoint->Location(&x, &y);
            slab_shape->AddPoint(x,y+haunchDepth);
            msPoint.Release();

            CComPtr<IEnumPoint2d> enum_points;
            matingSurfaceProfile->get__Enum(&enum_points);
            while (enum_points->Next(1, &msPoint, nullptr) != S_FALSE)
            {
               // Tricky: The girder section and mating profile comes to us in bridge coordinates. 
               //         We must rotate and translate the points to our local slab coord system.
               Float64 x, y;
               if (!IsZero(orientation))
               {
                  msPoint->RotateEx(pntTC, -orientation);
               }
               msPoint->Location(&x, &y);

               slab_shape->AddPoint(x, y);
               msPoint.Release();
            }

            // Point 4
            IndexType nPoints;
            matingSurfaceProfile->get_Count(&nPoints);
            matingSurfaceProfile->get_Item(nPoints-1, &msPoint);
            msPoint->Location(&x, &y);
            slab_shape->AddPoint(x, y + haunchDepth);
            msPoint.Release();
         }

      }

      // Points 5-8
      CComQIPtr<IBulbTeeSection> bulbTeeSection(pGirderSection);
      if (bulbTeeSection && bFollowMatingSurfaceProfile == TRUE)
      {
         // This is a hack for bulb tee sections... we should have a more general solution
         // so it works for all asymmetric girders that have sloped top flanges

         CComPtr<IPoint2dCollection> matingSurfaceProfile;
         bool bHasMSProfile = (FAILED(pGirderSection->get_MatingSurfaceProfile(0, VARIANT_FALSE, &matingSurfaceProfile)) || matingSurfaceProfile == nullptr) ? false : true;
         ATLASSERT(bHasMSProfile);
         matingSurfaceProfile->Reverse();

         CComPtr<IEnumPoint2d> enum_points;
         matingSurfaceProfile->get__Enum(&enum_points);
         CComPtr<IPoint2d> msPoint;
         while (enum_points->Next(1, &msPoint, nullptr) != S_FALSE)
         {
            // Tricky: The girder section and mating profile comes to us in bridge coordinates. 
            //         We must rotate and translate the points to our local slab coord system.
            Float64 x, y;
            if (!IsZero(orientation))
            {
               msPoint->RotateEx(pntTC, -orientation);
            }
            msPoint->Location(&x, &y);

            slab_shape->AddPoint(x, y + haunchDepth + structural_depth);
            msPoint.Release();
         }
      }
      else
      {
         Float64 half_width = deck_width / 2.0;
         Float64 x56 = xms_cl + half_width;
         Float64 x78 = xms_cl - half_width;

         slab_shape->AddPoint(x56, ybslab); // 5
         slab_shape->AddPoint(x56, ytslab); // 6
         slab_shape->AddPoint(x78, ytslab); // 7
         slab_shape->AddPoint(x78, ybslab); // 8
      }

      slab_shape.QueryInterface(&shape);
   }

   return shape.CopyTo(pShape);
}

HRESULT CSectionCutTool::CreateDeckSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs, SectionBias sectionBias,
             StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,HaunchDepthMethod haunchMethod,BOOL bFollowMatingSurfaceProfile,IGirderSection* pGirderSection,ISection** section)
{
   CComPtr<ICompositeSectionEx> cmpSection;
   cmpSection.CoCreateInstance(CLSID_CompositeSectionEx);
   cmpSection.QueryInterface(section);

   // Get bridge deck and determine type
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   // this model doesn't have a deck... get the heck outta here
   if ( deck == nullptr )
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

   Float64 Econc;
   Float64 Dconc;
   CComPtr<IMaterial> material;
   if (FAILED(GetMaterial(deck, ssMbrID, segIdx, Xs, sectionBias, &material)))
   {
      ATLASSERT(false); // if this asserts, then the casting region model may be wrong
      return S_FALSE; // no casting region in this location... e.g. no deck at this location
   }

   material->get_E(stageIdx,&Econc);
   material->get_Density(stageIdx,&Dconc);

   if ( IsZero(Econc) )
   {
      // Deck isn't cast yet, we are done
      return S_FALSE;
   }

   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);
   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   // Get haunch depth
   Float64 haunch_depth = ComputeStructuralHaunchDepth(segment, Xs, haunchMethod);

   // Build a slab shape and add it to the section
   CComPtr<IShape> shape;

   HRESULT hr = CreateDeckShape(bridge, ssMbrID, segIdx, Xs, sectionBias, haunch_depth, bFollowMatingSurfaceProfile, pGirderSection, &shape);
   if (FAILED(hr))
   {
      return hr;
   }

   cmpSection->AddSection(shape, Econc, 0.0, Dconc, 0.0, IsZero(Econc) ? VARIANT_FALSE : VARIANT_TRUE);

#if defined _DEBUG
   std::map<Float64,Float64> rebarLog;
#endif
   if ( sectionPropMethod == spmTransformed || sectionPropMethod == spmNet )
   {
      // Add Longitudinal Reinforcement Bars

      // get the location of the bottom of the slab... the rebar are located from the bottom
      CComQIPtr<IXYPosition> position(shape);
      CComPtr<IPoint2d> pntBottomCenter;
      position->get_LocatorPoint(lpBottomCenter,&pntBottomCenter);
      Float64 xBottom, yBottom;
      pntBottomCenter->get_X(&xBottom);
      pntBottomCenter->get_Y(&yBottom);

      yBottom += haunch_depth;

      CComPtr<IBridgeDeckRebarLayout> rebarLayout;
      deck->get_RebarLayout(&rebarLayout);

      CComPtr<IRebarSection> rebarSection;
      rebarLayout->CreateRebarSection(ssMbrID,segIdx,Xs,&rebarSection);

      CComPtr<IEnumRebarSectionItem> enumRebarSectionItem;
      rebarSection->get__EnumRebarSectionItem(&enumRebarSectionItem);

      CComPtr<IRebarSectionItem> rebarSectionItem;
      while ( enumRebarSectionItem->Next(1,&rebarSectionItem,nullptr) != S_FALSE )
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

         x = xBottom; // Place X of all bars at CL of slab. This will need to be changed if we start drawing
                      // bars in the girder section view, and the change will need to happen in the implementation
                      // of IRebarSectionItem. The implementation does not currently center the bars within the 
                      // effective flange.
         y += yBottom;
         centroid->Move(x,y);

#if defined _DEBUG
         std::map<Float64,Float64>::iterator found = rebarLog.find(y);
         if ( found == rebarLog.end() )
         {
            rebarLog.insert(std::make_pair(y,Abar));
         }
         else
         {
            found->second += Abar;
         }
#endif

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
            {
               Ebar = Econc;
            }

            if ( IsZero(Dbar) )
            {
               Dbar = Dconc;
            }
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

HRESULT CSectionCutTool::CreateNoncompositeSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** ppSection)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   CComPtr<IGirderLine> girderLine;
   segment->get_GirderLine(&girderLine);

   Float64 segment_layout_length;
   girderLine->get_LayoutLength(&segment_layout_length);

   // this is the primary section (the girder)
   CComPtr<ISection> section;
   HRESULT hr = segment->get_Section(stageIdx,Xs,sectionBias,coordinateSystem,&section);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
   {
      return hr;
   }

   section.CopyTo(ppSection);

   // get the girder shape
   // the girder is the primary shape so it is the first item in the section model
   CComQIPtr<ICompositeSectionEx> compositeSection(section);
   ATLASSERT(compositeSection);
   CComPtr<ICompositeSectionItemEx> compositeSectionItem;
   compositeSection->get_Item(0,&compositeSectionItem);
   CComPtr<IShape> primary_shape;
   compositeSectionItem->get_Shape(&primary_shape);

   CComQIPtr<IXYPosition> position(primary_shape);
   CComPtr<IPoint2d> pntTopCenter;
   position->get_LocatorPoint(lpTopCenter,&pntTopCenter);


   // Need to determine if the bridge has a deck.
   // If it DOES NOT have a deck...
   // Need to get girder material.
   // Get the last stage defined in the material and compare it to stageIdx
   // If this IS THE LAST STAGE, and the sacrificial depth is > 0
   // then clip the sacrifical depth of the top of the girder without
   // altering the vertical or horizontal position of the girder.
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);
   Float64 sacDepth;
   bridge->get_SacrificialDepth(&sacDepth);
   if (deck == nullptr && !IsZero(sacDepth))
   {
      // The bridge does not have a deck and there is a sacrifical depth that
      // must be deducted from the top of the girder to account for the girder 
      // being worn down over time.
      StageIndexType sacStageIdx;
      bridge->get_SacrificialDepthStage(&sacStageIdx);

      if (sacStageIdx <= stageIdx && sacStageIdx != INVALID_INDEX)
      {
         CComQIPtr<IPrestressedGirderSection> psgSection(primary_shape);
         if (!psgSection || psgSection->RemoveSacrificalDepth(sacDepth) != S_OK)
         {
            // need to clip sacrificial depth from top of girder
            CComPtr<IPoint2d> point;
            pntTopCenter->Clone(&point);
            point->Offset(0, -sacDepth);

            CComPtr<IVector2d> v;
            v.CoCreateInstance(CLSID_Vector2d);
            v->put_X(1.0);
            v->put_Y(0.0);

            CComPtr<ILine2d> line;
            line.CoCreateInstance(CLSID_Line2d);
            line->SetExplicit(point, v);

            CComPtr<IShape> newShape;
            primary_shape->ClipWithLine(line, &newShape);

            primary_shape.Release();
            primary_shape = newShape;
         }
         compositeSectionItem->putref_Shape(primary_shape);
      }
   }

   // The girder is located in Bridge Section Coordinates.
   // Strand, Rebar, and Tendon coordinates are in Girder Section Coordinates.
   // Need to get the offset distance so the strand, bar, tendon can
   // be put in the girder section in Bridge Section Coordinates.
   Float64 xTop,yTop;
   pntTopCenter->Location(&xTop,&yTop);

   // background properties are the foreground properties of the girder concrete (the holes are in the girder)
   Float64 Econc,Dconc;
   compositeSectionItem->get_Efg(&Econc);
   compositeSectionItem->get_Dfg(&Dconc);

   // get the PrecastGirder item data
   CComQIPtr<IItemData> item_data(segment);
   ATLASSERT(item_data); // segments must have item data
   CComPtr<IUnknown> punk;
   item_data->GetItemData(CComBSTR("Precast Girder"),&punk);
   ATLASSERT(punk != nullptr);
   CComQIPtr<IPrecastGirder> girder(punk);
   ATLASSERT(girder != nullptr);

   // need to make sure the location we are looking at is actually
   // on the precast girder or if it is in a closure pour region
   Float64 segment_length; // end-to-end segment length
   segment->get_Length(&segment_length);
   bool bIsPointOnSegment = ( InRange(0.0,Xs,segment_length) ? true : false );

   // Add Plant Installed Tendons, Strands and Rebar
   if ( sectionPropMethod != spmGross && sectionPropMethod != spmGrossNoncomposite )
   {
      if ( bIsPointOnSegment )
      {
         // The point under consideration must be on the precast girder segment, otherwise there aren't any strands
         // or girder rebar

         // Add Plant installed tendons
         CComPtr<ITendonCollection> tendons;
         girder->get_Tendons(&tendons);
         if (tendons)
         {
            CComPtr<IEnumTendons> enumTendons;
            tendons->get__EnumTendons(&enumTendons);
            ULONG nFetched;
            CComPtr<ITendon> tendon;
            while (enumTendons->Next(1, &tendon, &nFetched) != S_FALSE)
            {
#if defined _DEBUG
               // tendons run full length of segment, but double check to make sure
               // the cut put is between segment start/end
               CComPtr<IPoint3d> pntStart, pntEnd;
               tendon->get_Start(&pntStart);
               tendon->get_End(&pntEnd);
               Float64 Xss, Xes;
               pntStart->get_Z(&Xss);
               pntEnd->get_Z(&Xes);
               ATLASSERT(IsZero(Xss));
               ATLASSERT(IsEqual(Xes, segment_length));
               ATLASSERT(InRange(Xss, Xs, Xes));
#endif
               ModelTendon(Xs, stageIdx, xTop, yTop, tendon, sectionPropMethod, Econc, Dconc, compositeSection);
               tendon.Release();
            } // next tendon
         }


         // Add Strands
         CComPtr<IStrandModel> strandModel;
         girder->get_StrandModel(&strandModel);
         if (strandModel)
         {
            for (int i = 0; i < 3; i++)
            {
               CComPtr<IMaterial> material;
               CComPtr<IPrestressingStrand> strandMaterial;
               CComPtr<IPoint2dCollection> strandLocations;
               CComPtr<IIndexArray> debondPositions;

               StrandType strandType = StrandType(i);
               strandModel->get_StrandMaterial(strandType, &strandMaterial);
               strandModel->GetStrandPositions(strandType, Xs, &strandLocations);

               if (i == 0)
               {
                  strandModel->GetStraightStrandsDebondedByPositionIndex(Xs, &debondPositions);
               }
               else if (i == 1)
               {
                  debondPositions.CoCreateInstance(CLSID_IndexArray); // empty array
               }
               else
               {
                  debondPositions.CoCreateInstance(CLSID_IndexArray); // empty array
               }

               strandMaterial.QueryInterface(&material);
               Float64 Estrand, Dstrand;
               material->get_E(stageIdx, &Estrand);
               material->get_Density(stageIdx, &Dstrand);

#if defined LUMP_STRANDS
               // bonded strands
               Float64 A = 0;
               Float64 AX = 0;
               Float64 AY = 0;

               // debonded strands
               Float64 Adb = 0;
               Float64 AdbX = 0;
               Float64 AdbY = 0;
#endif // LUMP_STRANDS

               CComPtr<IPoint2d> point;
               CComPtr<IEnumPoint2d> enum_points;
               strandLocations->get__Enum(&enum_points);
               StrandIndexType strandIndex = 0;
               while (enum_points->Next(1, &point, nullptr) != S_FALSE)
               {
                  // x measured from CL girder
                  // y measured from top of girder
                  Float64 x, y;
                  point->Location(&x, &y);

                  Float64 Aps;
                  strandMaterial->get_NominalArea(&Aps);

                  IndexType foundIndex;
                  HRESULT hr = debondPositions->Find(strandIndex, &foundIndex);
                  bool bIsDebonded = SUCCEEDED(hr) ? true : false;

#if defined LUMP_STRANDS
                  if (bIsDebonded)
                  {
                     Adb += Aps;
                     AdbY += Aps*y;
                     AdbX += Aps*x;
                  }
                  else
                  {
                     A += Aps;
                     AY += Aps*y;
                     AX += Aps*x;
                  }
#else
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

                  centroid->Move(xTop + x, yTop + y);

                  if (sectionPropMethod == spmTransformed || sectionPropMethod == spmTransformedNoncomposite)
                  {
                     if (bDebonded)
                     {
                        // Strand is debonded so it just creates a hole in the cross section here
                        // model the hole and not the strand
                        // (e.g. EA = EconcAg + Astrand(0 - Econc) = EconcAg - Astrand(Econc) = (Ag-Astrand)Econc
                        Estrand = 0;
                        Dstrand = 0;
                     }
                  }
                  else if (sectionPropMethod == spmNet)
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
                  compositeSection->AddSection(strand_shape, Estrand, Econc, Dstrand, Dconc, VARIANT_TRUE);
#endif // LUMP_STRANDS
                  point.Release();
                  strandIndex++;
               }

#if defined LUMP_STRANDS
               if (!IsZero(A))
               {
                  Float64 Aps = A;
                  Float64 x = AX / A;
                  Float64 y = AY / A;

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

                  centroid->Move(xTop + x, yTop + y);

                  if (sectionPropMethod == spmNet)
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
                  compositeSection->AddSection(strand_shape, Estrand, Econc, Dstrand, Dconc, VARIANT_TRUE);
               }

               if (!IsZero(Adb))
               {
                  Float64 Aps = Adb;
                  Float64 x = AdbX / Adb;
                  Float64 y = AdbY / Adb;

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

                  centroid->Move(xTop + x, yTop + y);

                  // Debonded strands just create a hole in the cross section
                  // model the hole and not the strand
                  // (e.g. EA = EconcAg + Astrand(0 - Econc) = EconcAg - Astrand(Econc) = (Ag-Astrand)Econc
                  Estrand = 0;
                  Dstrand = 0;

                  // EA = EgAg + Astrand(Estrand-Eg) = Eg(Ag-Astrand) + (Estrand)(Astrand)
                  // models the strand and makes a hole in the concrete for the strand
                  CComQIPtr<IShape> strand_shape(strandShape);
                  compositeSection->AddSection(strand_shape, Estrand, Econc, Dstrand, Dconc, VARIANT_TRUE);
               }
#endif // LUMP_STRANDS
            } // End of Strand
         }

         // Layout girder rebar
         CComPtr<IRebarLayout> rebarLayout;
         girder->get_RebarLayout(&rebarLayout);

         CComPtr<IRebarSection> rebarSection;
         rebarLayout->CreateRebarSection(Xs,stageIdx,&rebarSection);

         LayoutRebar(compositeSection,Econc,Dconc,rebarSection,xTop,yTop,stageIdx,sectionPropMethod);

      } // is point on precast girder
      else
      {
         // beyond the end of this girder so this must be in the closure joint
         
         CComPtr<IRebarLayout> rebarLayout;
         girder->get_ClosureJointRebarLayout(&rebarLayout);

         CComPtr<IRebarSection> rebarSection;
         rebarLayout->CreateRebarSection(Xs,stageIdx,&rebarSection);

         LayoutRebar(compositeSection,Econc,Dconc,rebarSection,xTop,yTop,stageIdx,sectionPropMethod);
      } // is point on precast girder

      // add holes for tendons/ducts if the stage is before the grouting stage
      // otherwise, omit the holes
      
      // get the tendon model. it is stored as item data on the superstructure member
      Float64 Xg; // measured in girder coordinates
      ssmbr->GetDistanceFromStart(segIdx, Xs, &Xg);

      CComQIPtr<IItemData> itemData(ssmbr);
      CComPtr<IUnknown> unk;
      itemData->GetItemData(CComBSTR("Tendons"),&unk);
      CComQIPtr<ITendonCollection> tendons(unk);
      if (tendons)
      {
         CComPtr<IEnumTendons> enumTendons;
         tendons->get__EnumTendons(&enumTendons);
         ULONG nFetched;
         CComPtr<ITendon> tendon;
         while (enumTendons->Next(1, &tendon, &nFetched) != S_FALSE)
         {
            CComPtr<IPoint3d> pntStart, pntEnd;
            tendon->get_Start(&pntStart);
            tendon->get_End(&pntEnd);
            Float64 Xgs, Xge;
            pntStart->get_Z(&Xgs);
            pntEnd->get_Z(&Xge);

            if (!InRange(Xgs, Xg, Xge))
            {
               // location is not between the ends of the tendon
               tendon.Release();
               continue;
            }

            ModelTendon(Xg, stageIdx, xTop, yTop, tendon, sectionPropMethod, Econc, Dconc, compositeSection);

            tendon.Release();
         } // next tendon
      }
   } // if not gross properties

   return S_OK;
}

HRESULT CSectionCutTool::ModelTendon(Float64 X,StageIndexType stageIdx,Float64 xTop,Float64 yTop,ITendon* pTendon, SectionPropertyMethod sectionPropMethod,Float64 Econc,Float64 Dconc,ICompositeSectionEx* pCompositeSection)
{
   CComPtr<IPrestressingStrand> strand;
   pTendon->get_Material(&strand);
   CComQIPtr<IMaterial> material(strand);
   ATLASSERT(material);

   Float64 Etendon;
   material->get_E(stageIdx, &Etendon);

   Float64 Dtendon;
   material->get_Density(stageIdx, &Dtendon);

   // create a circle for the tendon
   CComPtr<IPoint3d> pntCG;
   pTendon->get_CG(X, tmPath, &pntCG);

   // location of duct in Girder Section Coordinates
   if (pntCG)
   {
      Float64 x, y, z;
      pntCG->Location(&x, &y, &z);
      ATLASSERT(IsEqual(X, z));
      ATLASSERT(y <= 0); // below top of girder

      // if Etendon is zero, the tendon is not installed yet
      // Model the hole for the duct. Model this hole for gross, transformed and net properties
      if (IsZero(Etendon))
      {
         // Put holes for ducts into girder
         Float64 ductDiameter;
         pTendon->get_OutsideDiameter(&ductDiameter);

         CComPtr<ICircle> duct;
         duct.CoCreateInstance(CLSID_Circle);
         duct->put_Radius(ductDiameter / 2);

         CComPtr<IPoint2d> center;
         duct->get_Center(&center);
         center->Move(xTop + x, yTop + y);

         CComQIPtr<IShape> duct_shape(duct);

         // If E is 0, then this models a hole in the section (E-Eg = -Eg)
         // and Summation of EA = EgAg - EgAhole = Eg(Ag - Ahole)
         pCompositeSection->AddSection(duct_shape, 0.0, Econc, 0.0, Dconc, VARIANT_TRUE);
      }
      else
      {
         // Add Tendon
         if (sectionPropMethod == spmNet)
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
         pTendon->get_TendonArea(&Apt);

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

         centroid->Move(xTop + x + cg_offset_x, yTop + y + cg_offset_y);

         CComQIPtr<IShape> tendon_shape(tendonShape);

         // EA = EgAg + Apt(Ept-Eg) = Eg(Ag-Apt) + EptApt: Tendon is added and a hole is created in the concrete
         pCompositeSection->AddSection(tendon_shape, Etendon, Econc, Dtendon, Dconc, VARIANT_TRUE/*shape is structural element*/);
      }
   } // if pntCG

   return S_OK;
}

HRESULT CSectionCutTool::LayoutRebar(ICompositeSectionEx* compositeSection,Float64 Econc,Float64 Dconc,IRebarSection* rebarSection,Float64 xTop,Float64 yTop,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod)
{
   CComPtr<IEnumRebarSectionItem> enumRebarSectionItem;
   rebarSection->get__EnumRebarSectionItem(&enumRebarSectionItem);

   CComPtr<IRebarSectionItem> rebarSectionItem;
   while ( enumRebarSectionItem->Next(1,&rebarSectionItem,nullptr) != S_FALSE )
   {
      CComPtr<IPoint2d> pntRebar;
      rebarSectionItem->get_Location(&pntRebar);

      // x measured from CL girder
      // y measured from top of girder
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

      centroid->Move(xTop + x,yTop + y);

      CComQIPtr<IMaterial> material(rebar);
      ATLASSERT(material);

      Float64 Ebar, Dbar;
      material->get_E(stageIdx,&Ebar);
      material->get_Density(stageIdx,&Dbar);

      if ( sectionPropMethod == spmNet )
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

   return S_OK;
}

HRESULT CSectionCutTool::CreateBridgeDeckSection(IGenericBridge* bridge,Float64 Xb,SectionBias sectionBias,StageIndexType stageIdx,Float64 elevBottomDeck,ICompositeSectionItemEx** deckitem)
{
   // This method creates a rectangular approximation of the bridge deck cross section.
   // The rectangle width is the edge-to-edge width of the deck, measured normal to the alignment
   // at distFromStartOfBridge. The height of the rectangle is the structural thickness of the deck
   // (gross depth - wearing depth). The depth of precast deck panels is included in the height
   // of the rectangular approximation.
   HRESULT hr = S_OK;

   (*deckitem) = nullptr;
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);
   if (deck)
   {
      VARIANT_BOOL vbIsComposite;
      deck->get_Composite(&vbIsComposite);

      if (vbIsComposite == VARIANT_TRUE)
      {
         // deck is composite so it is part of the structural section
         CComPtr<IDeckBoundary> deckBoundary;
         deck->get_DeckBoundary(&deckBoundary);

         CComPtr<IPath> leftPath, rightPath;
         deckBoundary->get_EdgePath(stLeft, VARIANT_TRUE, &leftPath);
         deckBoundary->get_EdgePath(stRight, VARIANT_TRUE, &rightPath);

         Float64 station = DistanceToStation(bridge, Xb);

         CComPtr<IAlignment> alignment;
         bridge->get_Alignment(&alignment);

         CComPtr<IDirection> normal;
         alignment->GetNormal(CComVariant(station), &normal);

         CComPtr<IPoint2d> pntAlignment;
         alignment->LocatePoint(CComVariant(station), omtNormal, 0.0, CComVariant(normal), &pntAlignment);

         // create a line normal to the alignment
         CComPtr<ILine2d> line;
         line.CoCreateInstance(CLSID_Line2d);
         CComPtr<IVector2d> v;
         CComPtr<IPoint2d> p;
         line->GetExplicit(&p, &v);
         Float64 dir;
         normal->get_Value(&dir);
         v->put_Direction(dir);
         line->SetExplicit(pntAlignment, v);

         // intersect the line with the left and right edge paths... we want the point closest to the alignment
         CComPtr<IPoint2d> pntLeft, pntRight;
         leftPath->Intersect(line, pntAlignment, &pntLeft);
         rightPath->Intersect(line, pntAlignment, &pntRight);

         // get slab depth and width
         Float64 ttl_width;
         pntLeft->DistanceEx(pntRight, &ttl_width);

         Float64 depth;
         deck->get_StructuralDepth(&depth);

         CComPtr<IRectangle> rect;
         rect.CoCreateInstance(CLSID_Rect);
         rect->put_Width(ttl_width);
         rect->put_Height(depth);

         CComPtr<IPoint2d> hp;
         rect->get_HookPoint(&hp);
         hp->put_Y(elevBottomDeck + depth / 2);

         CComPtr<ICompositeSectionItemEx> csi;
         csi.CoCreateInstance(CLSID_CompositeSectionItemEx);

         CComQIPtr<IShape> shape(rect);
         csi->putref_Shape(shape);

         CComPtr<IMaterial> material;
         HRESULT hr = GetMaterial(deck, Xb, sectionBias, &material);
         ATLASSERT(SUCCEEDED(hr)); // if this asserts, then the casting region model may be wrong

         Float64 E, density;
         material->get_E(stageIdx, &E);
         material->get_Density(stageIdx, &density);

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

HRESULT CSectionCutTool::CreateGirderShape(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,VARIANT_BOOL bIncludeDeck,HaunchDepthMethod haunchMethod,BOOL bFollowMatingSurfaceProfile,IShape** ppShape)
{
   // Xs is in segment coordinates
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   CComPtr<IShape> primary_shape;
   segment->get_GirderShape(Xs,sectionBias,coordinateSystem,&primary_shape);

   CComQIPtr<ICompositeShape> compositeShape(primary_shape);
   ATLASSERT(compositeShape); // primary_shape must be a composite so we can put holes in it

   // Internal shapes, such as ducts, are in Girder Section Coordinates.
   // The shape is in Bridge Section Coordinates. Get the top center of the
   // shape so that the internal shapes can be moved into Bridge Section Coordinates
   CComQIPtr<IXYPosition> position(primary_shape);
   CComPtr<IPoint2d> pntTopCenter;
   position->get_LocatorPoint(lpTopCenter,&pntTopCenter);
   Float64 xTop,yTop;
   pntTopCenter->Location(&xTop,&yTop);

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

         // create a circle for the tendon
         Float64 Xg; // in girder coordinates
         ssmbr->GetDistanceFromStart(segIdx,Xs,&Xg);

         CComPtr<IPoint3d> pntCG;
         tendon->get_CG(Xg,tmPath,&pntCG); // Xg is in Girder Coordinates

         ATLASSERT(pntCG != nullptr);

         if ( pntCG == nullptr )
         {
            // this code was put here to deal with the case that tendon->get_CG() fails
            // and allows processing to continue
            continue;
         }

         // location of duct in Girde Section Coordinates
         Float64 x,y,z;
         pntCG->Location(&x,&y,&z);
         ATLASSERT(IsEqual(Xg,z));
         ATLASSERT(y <= 0); // tendon must be below top of girder

         Float64 ductDiameter;
         tendon->get_OutsideDiameter(&ductDiameter);

         CComPtr<ICircle> duct;
         duct.CoCreateInstance(CLSID_Circle);
         duct->put_Radius(ductDiameter/2);

         CComPtr<IPoint2d> center;
         duct->get_Center(&center);
         center->Move(xTop+x,yTop+y);

         CComQIPtr<IShape> duct_shape(duct);

         compositeShape->AddShape(duct_shape,VARIANT_TRUE);
      } // next duct
   }

   ///////////////////
   // Model deck
   ///////////////////
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   if (deck && bIncludeDeck == VARIANT_TRUE)
   {
      // Get haunch depth
      Float64 haunch_depth = ComputeStructuralHaunchDepth(segment, Xs, haunchMethod);

      CComQIPtr<IGirderSection> girder_section(compositeShape);
      ATLASSERT(girder_section);

      CComPtr<IShape> slab_shape;
      HRESULT hr = CreateDeckShape(bridge, ssMbrID, segIdx, Xs, sectionBias, haunch_depth, bFollowMatingSurfaceProfile, girder_section, &slab_shape);
      if (FAILED(hr))
      {
         return hr;
      }


      ATLASSERT(slab_shape != nullptr);
      compositeShape->AddShape(slab_shape, VARIANT_FALSE);
   }

   primary_shape.CopyTo(ppShape);

   return S_OK;
}

HRESULT CSectionCutTool::CreateJointShapes(IGenericBridge* bridge, GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, SectionCoordinateSystemType coordinateSystem, IShape** ppLeftJointShape, IShape** ppRightJointShape)
{
   // Xs is in segment coordinates
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID, &ssmbr);

   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIdx, &segment);

   CComQIPtr<ILongitudinalJoints> jointSegment(segment);
   if (jointSegment)
   {
      CComPtr<IShape> leftJointShape, rightJointShape;
      jointSegment->get_JointShapes(Xs, coordinateSystem, &leftJointShape, &rightJointShape);
      leftJointShape.CopyTo(ppLeftJointShape);
      rightJointShape.CopyTo(ppRightJointShape);
   }

   return S_OK;
}

HRESULT CSectionCutTool::SkewShape(Float64 skewAngle,IShape* pShape,IShape** ppSkewedShape)
{
   if ( IsZero(skewAngle) )
   {
      // Not skewed... nothing to do
      (*ppSkewedShape) = pShape;
      (*ppSkewedShape)->AddRef();
      return S_OK;
   }

   Float64 cos_angle = cos(skewAngle);

   CComPtr<IShape> s;

   CComQIPtr<ICompositeShape> compositeShape(pShape);
   if (compositeShape)
   {
      CComPtr<ICompositeShape> skewedCompositeShape;
      skewedCompositeShape.CoCreateInstance(CLSID_CompositeShape);

      IndexType nShapes;
      compositeShape->get_Count(&nShapes);
      for (IndexType i = 0; i < nShapes; i++)
      {
         CComPtr<ICompositeShapeItem>  item;
         compositeShape->get_Item(i, &item);

         CComPtr<IShape> shape;
         item->get_Shape(&shape);

         VARIANT_BOOL bVoid;
         item->get_Void(&bVoid);

         CComPtr<IRect2d> bbox;
         shape->get_BoundingBox(&bbox);
         CComPtr<IPoint2d> pntTC;
         bbox->get_TopCenter(&pntTC);
         Float64 xcl;
         pntTC->get_X(&xcl);

         CComPtr<IPoint2dCollection> points;
         shape->get_PolyPoints(&points);
         CComPtr<IPoint2d> pnt;
         CComPtr<IEnumPoint2d> enumPoints;
         points->get__Enum(&enumPoints);
         while (enumPoints->Next(1, &pnt, nullptr) != S_FALSE)
         {
            Float64 x;
            pnt->get_X(&x);
            x -= xcl;
            x /= cos_angle;
            x += xcl;
            pnt->put_X(x);

            pnt.Release();
         }
         CComPtr<IPolyShape> polyShape;
         polyShape.CoCreateInstance(CLSID_PolyShape);
         polyShape->AddPoints(points);

         CComQIPtr<IShape> ps(polyShape);
         skewedCompositeShape->AddShape(ps, bVoid);
      }
      skewedCompositeShape.QueryInterface(&s);
   }
   else
   {
      CComPtr<IRect2d> bbox;
      pShape->get_BoundingBox(&bbox);
      CComPtr<IPoint2d> pntTC;
      bbox->get_TopCenter(&pntTC);
      Float64 xcl;
      pntTC->get_X(&xcl);

      CComPtr<IPoint2dCollection> points;
      pShape->get_PolyPoints(&points);
      CComPtr<IPoint2d> pnt;
      CComPtr<IEnumPoint2d> enumPoints;
      points->get__Enum(&enumPoints);
      while (enumPoints->Next(1, &pnt, nullptr) != S_FALSE)
      {
         Float64 x;
         pnt->get_X(&x);
         x -= xcl;
         x /= cos_angle;
         x += xcl;
         pnt->put_X(x);

         pnt.Release();
      }
      CComPtr<IPolyShape> polyShape;
      polyShape.CoCreateInstance(CLSID_PolyShape);
      polyShape->AddPoints(points);
      polyShape.QueryInterface(&s);
   }

   return s.CopyTo(ppSkewedShape);
}

HRESULT CSectionCutTool::CreateBarrierShape(DirectionType side,IGenericBridge* bridge,Float64 station,IDirection* pDirection,IShape** ppShape)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(ppShape);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   IDType profileID;
   bridge->get_ProfileID(&profileID);

   IDType surfaceID;
   bridge->get_SurfaceID(&surfaceID);

   CComPtr<IProfile> profile;
   alignment->GetProfile(profileID, &profile);

   // many of the calls below are most efficient with a station object
   // create one and use it.
   CComPtr<IStation> objStation;
   objStation.CoCreateInstance(CLSID_Station);
   objStation->SetStation(INVALID_INDEX,station); // normalized station

   CComPtr<IDirection> dirCutLine;
   if ( pDirection == nullptr )
   {
      alignment->GetNormal(CComVariant(objStation),&dirCutLine); // normal to the right
      dirCutLine->IncrementBy(CComVariant(M_PI)); // normal to the left
   }
   else
   {
      dirCutLine = pDirection;
   }

   CComPtr<IPoint2d> pntAlignment; // point on the alignment at station
   alignment->LocatePoint(CComVariant(objStation),omtAlongDirection,0.0,CComVariant(pDirection),&pntAlignment);

   // get deck edge point
   CComPtr<IPoint2d> pntDeckEdge;
   m_BridgeGeometryTool->DeckEdgePoint(bridge,station,dirCutLine,side,&pntDeckEdge);

   // get station and offset
   CComPtr<IStation> offsetStation;
   Float64 offset_normal_to_alignment;
   alignment->StationAndOffset(pntDeckEdge,&offsetStation,&offset_normal_to_alignment);

   // get elevation
   Float64 deck_edge_elev;
   profile->Elevation(surfaceID,CComVariant(offsetStation),offset_normal_to_alignment,&deck_edge_elev);

   // get the offset from the alignment, to the deck edge points, measured along the cut direction
   Float64 deck_offset;
   pntAlignment->DistanceEx(pntDeckEdge, &deck_offset); // distance is always a positive value
   deck_offset *= ::BinarySign(offset_normal_to_alignment); // match the sign of the edge offset  


   CComPtr<ISidewalkBarrier> barrier;
   if ( side == qcbLeft )
   {
      bridge->get_LeftBarrier(&barrier);
   }
   else
   {
      bridge->get_RightBarrier(&barrier);
   }

   CComPtr<IShape> barrier_shape;
   barrier->get_Shape(&barrier_shape);

   // clone the basic shape so we aren't changing it
   CComPtr<IShape> shape;
   barrier_shape->Clone(&shape);

   // rotate shape to match deck slope
   CComPtr<IStation> deckEdgeStation;
   Float64 deckEdgeOffset;
   alignment->StationAndOffset(pntDeckEdge, &deckEdgeStation, &deckEdgeOffset);
   Float64 slope;
   profile->CrossSlope(surfaceID, CComVariant(deckEdgeStation), deckEdgeOffset, &slope);
   Float64 angle = atan(slope);

   CComQIPtr<IXYPosition> position(shape);
   CComPtr<IPoint2d> hook_point;
   position->get_LocatorPoint(lpHookPoint,&hook_point);
   position->RotateEx(hook_point,angle);

   Float64 wearing_surface_adjustment = 0;
   VARIANT_BOOL vbHasFutureOverlay;
   bridge->HasFutureOverlay(&vbHasFutureOverlay);
   StageIndexType wearingSurfaceStage;
   bridge->get_WearingSurfaceStage(&wearingSurfaceStage);
   if (wearingSurfaceStage != INVALID_INDEX && vbHasFutureOverlay == VARIANT_FALSE)
   {
      bridge->get_WearingSurfaceDepth(&wearing_surface_adjustment);
   }

   // move shape into bridge section coordinates
   position->Offset(deck_offset,deck_edge_elev - wearing_surface_adjustment);

   // Project shape onto cut line
   CComPtr<IDirection> normal;
   alignment->GetNormal(CComVariant(objStation),&normal); // normal to right
   normal->IncrementBy(CComVariant(M_PI)); // want normal to left

   CComPtr<IAngle> objAngle;
   normal->AngleBetween(dirCutLine,&objAngle);
   Float64 skewAngle = 0;
   objAngle->get_Value(&skewAngle);

   CComPtr<IShape> skewedShape;
   SkewShape(skewAngle,shape,&skewedShape);

   skewedShape.CopyTo(ppShape);

   return S_OK;
}

std::vector<CSectionCutTool::GirderPointRecord> CSectionCutTool::GetGirderPoints(IGenericBridge* pBridge,IStation* pStation,IDirection* pDirection)
{
   std::vector<GirderPointRecord> vGirderPoints;

   // Create a line that pass throught the alignment at the specified station
   // in the specified direction. 
   CComPtr<IAlignment> alignment;
   GetAlignment(pBridge,&alignment);

   CComPtr<IPoint2d> pntAlignment;
   alignment->LocatePoint(CComVariant(pStation),omtAlongDirection,0.0,CComVariant(pDirection),&pntAlignment);

   Float64 cutDir;
   pDirection->get_Value(&cutDir);
   CComPtr<IVector2d> vDirection;
   vDirection.CoCreateInstance(CLSID_Vector2d);
   vDirection->put_Direction(cutDir);

   CComPtr<ILine2d> cutLine;
   cutLine.CoCreateInstance(CLSID_Line2d);
   cutLine->SetExplicit(pntAlignment,vDirection);

   CComPtr<ILineSegment2d> lineSegment;
   lineSegment.CoCreateInstance(CLSID_LineSegment2d);

   CComPtr<IGeomUtil2d> geomUtil;
   geomUtil.CoCreateInstance(CLSID_GeomUtil);

   // If the cut line intersects the girder lines, add it to the collection
   CComPtr<IEnumSuperstructureMembers> enumMbrs;
   pBridge->get__EnumSuperstructureMembers(&enumMbrs);

   CComPtr<ISuperstructureMember> mbr;
   while ( enumMbrs->Next(1,&mbr,nullptr) != S_FALSE )
   {
      GirderIDType girderID;
      mbr->get_ID(&girderID);

      CollectionIndexType nSegments;
      mbr->get_SegmentCount(&nSegments);

      for ( IndexType segIdx = 0; segIdx < nSegments; segIdx++ )
      {
         CComPtr<ISuperstructureMemberSegment> segment;
         mbr->get_Segment(segIdx,&segment);

         CComPtr<IGirderLine> gdrLine;
         segment->get_GirderLine(&gdrLine);

         CComPtr<IPoint2d> pntStart, pntEnd;
         gdrLine->get_EndPoint(etStart,&pntStart);
         gdrLine->get_EndPoint(etEnd,&pntEnd);
         //gdrLine->get_PierPoint(etStart,&pntStart);
         //gdrLine->get_PierPoint(etEnd,&pntEnd);
         lineSegment->ThroughPoints(pntStart,pntEnd);

         CComPtr<IPoint2d> pntIntersect;
         geomUtil->IntersectLineWithLineSegment(cutLine,lineSegment,&pntIntersect);
         if ( pntIntersect != nullptr )
         {
            CComPtr<IStation> objGirderStation;
            Float64 normalOffset;
            alignment->StationAndOffset(pntIntersect,&objGirderStation,&normalOffset);
            Float64 cutLineOffset;
            pntAlignment->DistanceEx(pntIntersect,&cutLineOffset);
            cutLineOffset *= ::BinarySign(normalOffset);

            Float64 Xs;
            pntIntersect->DistanceEx(pntStart,&Xs);

            LocationType locationType;
            mbr->get_LocationType(&locationType);

            GirderPointRecord girderPoint;
            girderPoint.objGirderStation = objGirderStation;
            girderPoint.normalOffset = normalOffset;
            girderPoint.cutLineOffset = cutLineOffset;
            girderPoint.girderID = girderID;
            girderPoint.girderLocation = locationType;
            girderPoint.segIdx = segIdx;
            girderPoint.Xs = Xs;
            vGirderPoints.push_back(girderPoint);
            break;
         }
      }
      mbr.Release();
   }

   std::sort(vGirderPoints.begin(),vGirderPoints.end());
   return vGirderPoints;
}

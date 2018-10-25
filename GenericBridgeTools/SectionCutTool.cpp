///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2015  Washington State Department of Transportation
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

#include <algorithm>

#if defined _DEBUG
#include <map>
#endif

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
   {
      return E_FAIL;
   }

   m_EffFlangeTool = pTool;


   CComObject<CBridgeGeometryTool>* pBGTool;
   hr = CComObject<CBridgeGeometryTool>::CreateInstance(&pBGTool);
   if ( FAILED(hr) || pBGTool == NULL )
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
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
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

   CComPtr<IProfile> profile;
   alignment->get_Profile(&profile);

   // Get left top point
   CComPtr<IStation> offsetStation;
   Float64 left_deck_offset; // distance from alignment to left edge of deck
   m_BridgeGeometryTool->DeckOffset(bridge,station,NULL,qcbLeft,&offsetStation,&left_deck_offset);

   Float64 elev;
   profile->Elevation(CComVariant(offsetStation),left_deck_offset,&elev);

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
   {
      barrier->get_StructuralShape(&shape);
   }
   else
   {
      barrier->get_Shape(&shape);
   }


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
   CComPtr<IStation> offsetStation;
   Float64 right_deck_offset; // distance from alignment to right edge of deck
   m_BridgeGeometryTool->DeckOffset(bridge,station,NULL,qcbRight,&offsetStation,&right_deck_offset);

   Float64 elev;
   profile->Elevation(CComVariant(offsetStation),right_deck_offset,&elev);

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
   {
      barrier->get_StructuralShape(&shape);
   }
   else
   {
      barrier->get_Shape(&shape);
   }

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

STDMETHODIMP CSectionCutTool::CreateSlabShape(IGenericBridge* bridge,Float64 station,IDirection* pDirection,IShape** shape)
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

   // many of the calls below are most efficient with a station object
   // create one and use it.
   CComPtr<IStation> objStation;
   objStation.CoCreateInstance(CLSID_Station);
   objStation->SetStation(INVALID_INDEX,station); // normalized station

   CComPtr<IDirection> dirCutLine;
   bool bIsNormal = false;
   if ( pDirection == NULL )
   {
      alignment->Normal(CComVariant(objStation),&dirCutLine); // normal to the right
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
   alignment->get_Profile(&profile);

   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   CComQIPtr<ICastSlab> cip(deck);
   CComQIPtr<IPrecastSlab> sip(deck);
   CComQIPtr<IOverlaySlab> overlay(deck);
   ATLASSERT(cip != NULL || sip != NULL || overlay != NULL);

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
   alignment->Offset(pntLeftDeckEdge,&leftOffsetStation,&left_deck_edge_normal_offset);

   CComPtr<IStation> rightOffsetStation;
   Float64 right_deck_edge_normal_offset;
   alignment->Offset(pntRightDeckEdge,&rightOffsetStation,&right_deck_edge_normal_offset);

   // get the offset from the alignment, to the deck edge points, measured along the cut direction
   Float64 left_deck_offset;
   pntAlignment->DistanceEx(pntLeftDeckEdge,&left_deck_offset); // distance is always a positive value
   left_deck_offset *= ::BinarySign(left_deck_edge_normal_offset); // match the sign of the edge offset

   Float64 right_deck_offset;
   pntAlignment->DistanceEx(pntRightDeckEdge,&right_deck_offset);
   right_deck_offset *= ::BinarySign(right_deck_edge_normal_offset);

   // Get roadway surface at cut station
   CComPtr<ISurface> surface;
   profile->GetSurface(COGO_FINISHED_SURFACE_ID,CComVariant(objStation),&surface);
   ATLASSERT(surface != NULL); // there must be a surface

   // get the alignment point
   IndexType alignmentPointIdx;
   surface->get_AlignmentPoint(&alignmentPointIdx);

   // get deck dimensions
   Float64 gross_depth;
   deck->get_GrossDepth(&gross_depth);

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

   // Top of Deck
   // Work right to left across the top of deck.

   // Begin at Right Edge, Bottom of deck
   // This is the same point as top of deck, except for the overhang_depth
   Float64 elev;
   profile->Elevation(CComVariant(rightOffsetStation),right_deck_edge_normal_offset,&elev);
   slab_shape->AddPoint(right_deck_offset,elev-overhang_depth);

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
      surface->CreateSurfaceTemplate(CComVariant(objStation),VARIANT_TRUE,&surfaceTemplate);
      surfaceTemplate->get_Count(&nRidgePoints); // this is number of segments
      nRidgePoints++; // this is the number of ridge points
      for ( IndexType ridgePointIdx = nRidgePoints; 0 < ridgePointIdx; ridgePointIdx-- )
      {
         // get offset (measured from the alignment) and the elevation of the ridge point
         Float64 offset, elev;
         profile->RidgePointElevation(COGO_FINISHED_SURFACE_ID,CComVariant(objStation),ridgePointIdx,alignmentPointIdx,&offset,&elev);

         // if the ridge point is between the edges of the deck, add it to the deck shape
         if ( ::InRange(left_deck_offset,offset,right_deck_offset) )
         {
            slab_shape->AddPoint(offset,elev);
         }
      }
   }
   else
   {
      surface->CreateSurfaceProfile(CComVariant(objStation),CComVariant(dirCutLine),VARIANT_TRUE,&surfaceProfile);
      surfaceProfile->get_Count(&nRidgePoints);
      for ( IndexType ridgePointIdx = nRidgePoints-1; 0 < ridgePointIdx; ridgePointIdx-- )
      {
         // get offset (measured from the alignment) and the elevation of the ridge point
         Float64 offset, elev;
         surfaceProfile->GetRidgePointElevation(ridgePointIdx,&offset,&elev);

         // if the ridge point is between the edges of the deck, add it to the deck shape
         if ( ::InRange(left_deck_offset,offset,right_deck_offset) )
         {
            slab_shape->AddPoint(offset,elev);
         }
      }
   }
   
   // Left Edge - top of deck
   profile->Elevation(CComVariant(leftOffsetStation),left_deck_edge_normal_offset,&elev);
   slab_shape->AddPoint(left_deck_offset,elev);

   // Left Edge - bottom of deck
   slab_shape->AddPoint(left_deck_offset,elev - overhang_depth);

   // work left to right across bottom of deck back to the bottom-right corner

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
            profile->RidgePointElevation(COGO_FINISHED_SURFACE_ID,CComVariant(objStation),ridgePointIdx,alignmentPointIdx,&offset,&elev);
         }
         else
         {
            surfaceProfile->GetRidgePointElevation(ridgePointIdx,&offset,&elev);
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
      // haunch is defined by 6 points per mating surface
      //
      //    --------1\      /6------
      //             2      5
      //             |      |
      //             3------4
      //
      BOOST_FOREACH(GirderPointRecord& girderPoint,vGirderPoints)
      {
         CComPtr<ISuperstructureMember> ssmbr;
         bridge->get_SuperstructureMember(girderPoint.girderID,&ssmbr);

         CComPtr<ISuperstructureMemberSegment> segment;
         ssmbr->get_Segment(girderPoint.segIdx,&segment);

         // orientation of girder in radians... 0 = plumb, rotated CW is +
         Float64 orientation;
         segment->get_Orientation(&orientation); // section view orientation

         CComPtr<IShape> girder_shape;
         segment->get_PrimaryShape(girderPoint.Xs,&girder_shape);

         CComQIPtr<IGirderSection> girder_section(girder_shape);

         // get skew angle. its not just the pier skew
         CComPtr<IGirderLine> girderLine;
         segment->get_GirderLine(&girderLine);
         CComPtr<IDirection> objGirderLineDirection;
         girderLine->get_Direction(&objGirderLineDirection);
         Float64 dirGirderLine;
         objGirderLineDirection->get_Value(&dirGirderLine);
         Float64 skew = fabs(dirCutLineValue - (dirGirderLine + PI_OVER_2));

         Float64 min_top_flange_thickness;
         girder_section->get_MinTopFlangeThickness(&min_top_flange_thickness);

         Float64 haunch = 0;
         segment->GetHaunchDepth(girderPoint.Xs,&haunch);

         Float64 elclg; // elevation at CL of girder
         profile->Elevation(CComVariant(girderPoint.objGirderStation),girderPoint.normalOffset,&elclg);

         MatingSurfaceIndexType nMatingSurfaces;
         girder_section->get_MatingSurfaceCount(&nMatingSurfaces);
         for ( CollectionIndexType msIdx = 0; msIdx < nMatingSurfaces; msIdx++ )
         {
            Float64 ms_width;
            girder_section->get_MatingSurfaceWidth(msIdx,&ms_width);

            Float64 ms_location; // relative to center of beam
            girder_section->get_MatingSurfaceLocation(msIdx,&ms_location);

            // adjust for skew
            ms_width /= cos(skew);
            ms_location /= cos(skew);

            Float64 x23; // x location of points 2 & 3
            Float64 x45; // x location of points 4 & 5
            Float64 xcl; // x location of centerline of flange
            xcl = girderPoint.cutLineOffset + ms_location;
            x23 = xcl - ms_width/2;
            x45 = xcl + ms_width/2;

            if ( InRange(left_deck_offset,x23,right_deck_offset) && InRange(left_deck_offset,x45,right_deck_offset))
            {
               Float64 el23; // deck elevation above points 2 & 3
               Float64 el45; // deck elevation above points 4 & 5
               Float64 elcl; // deck elevation above centerline of flange
               profile->Elevation(CComVariant(girderPoint.objGirderStation),x23,&el23);
               profile->Elevation(CComVariant(girderPoint.objGirderStation),x45,&el45);
               profile->Elevation(CComVariant(girderPoint.objGirderStation),xcl,&elcl);

               Float64 el3; // top of girder elevation on left side of flange (point 3)
               el3 = elclg - gross_depth - haunch - (ms_location - ms_width/2)*sin(orientation);

               Float64 el4; // top of girder elevation on right side of flange (point 4)
               el4 = elclg - gross_depth - haunch - (ms_location + ms_width/2)*sin(orientation);

               if ( girderPoint.girderLocation != ltLeftExteriorGirder || msIdx != 0 || overhang_taper == dotNone || overhang_taper == dotBottomTopFlange )
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
                     if ( overhang_taper == dotNone )
                     {
                        dy = overhang_depth;
                        dx = 0;
                     }
                     else
                     {
                        // slab overhang taper goes to the bottom of the top flange
                        dy = gross_depth + haunch - (elcl-el23) + min_top_flange_thickness;

                        Float64 slope;
                        profile->Slope(CComVariant(girderPoint.objGirderStation),x23,&slope);
                        dx = slope*min_top_flange_thickness/cos(skew);
                     }
                  }

                  if ( overhang_taper == dotBottomTopFlange )
                  {
                     slab_shape->AddPoint(x23-dx,el23-dy); // 1,2
                  }
                  else
                  {
                     slab_shape->AddPoint(x23-dx-fillet,el23-dy); // 1
                     slab_shape->AddPoint(x23-dx,el23-dy-fillet); // 2
                  }
               }

               slab_shape->AddPoint(x23,el3); // 3
               slab_shape->AddPoint(x45,el4); // 4

               if ( girderPoint.girderLocation != ltRightExteriorGirder || msIdx != nMatingSurfaces-1 || overhang_taper == dotNone || overhang_taper == dotBottomTopFlange)
               {
                  // only use this point if this is an interior girder or an interior web
                  // on the last girder, or the deck overhang is not tapered
                  Float64 dy;
                  Float64 dx;
                  if ( girderPoint.girderLocation != ltRightExteriorGirder || msIdx != nMatingSurfaces-1)
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

                        Float64 slope;
                        profile->Slope(CComVariant(girderPoint.objGirderStation),x45,&slope);
                        dx = slope*min_top_flange_thickness/cos(skew);
                     }
                  }

                  if ( overhang_taper == dotBottomTopFlange )
                  {
                     slab_shape->AddPoint(x45+dx,el45-dy); // 5, 6
                  }
                  else
                  {
                     slab_shape->AddPoint(x45+dx,el45-dy-fillet); // 5
                     slab_shape->AddPoint(x45+dx+fillet,el45-dy); // 6
                  }
               }
            }
         }
      }
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
   if ( deck == NULL )
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
   objStartStation->get_NormalizedValue(alignment,&startStation);

   Float64 station = startStation;
   CComPtr<IShape> prevDeckShape;
   CreateSlabShape(bridge,startStation,NULL,&prevDeckShape);

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
      objEndStation->get_NormalizedValue(alignment,&endStation);

      Float64 increment = (endStation - startStation)/nSectionsPerSpan;

      for ( IndexType i = 1; i < nSectionsPerSpan; i++ )
      {
         station += increment;

         CComPtr<IShape> deckShape;
         CreateSlabShape(bridge,station,NULL,&deckShape);

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

         // The end for this loop is the previoius values in the next loop
         prevPerimeter = perimeter;
         prevArea = area;
      } // next section

      startStation = endStation;
   } // next span

   *pSurfaceArea = S;
   *pVolume = V;

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

STDMETHODIMP CSectionCutTool::CreateGirderSectionBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 Xg,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section)
{
   CComPtr<ISuperstructureMember> ssMbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssMbr);

   Float64 Xs;
   SegmentIndexType segIdx;
   CComPtr<ISuperstructureMemberSegment> segment;
   ssMbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);

   return CreateGirderSectionBySegment(bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,sectionPropMethod,section);
}

STDMETHODIMP CSectionCutTool::CreateGirderSectionBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section)
{
   // Validate input
   CHECK_RETOBJ(section);
   CHECK_IN(bridge);

   return CreateCompositeSection(bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,sectionPropMethod,section);
}

STDMETHODIMP CSectionCutTool::CreateNetDeckSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,ISection** section)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(section);

   return CreateDeckSection(bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,spmNet,section);
}

STDMETHODIMP CSectionCutTool::CreateBridgeSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,StageIndexType stageIdx,BarrierSectionCut bsc,ISection** section)
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
            {
               continue; // this girder does not cross the section cut... must be a short, highly skewed bridge
            }

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

STDMETHODIMP CSectionCutTool::CreateGirderShapeBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 Xg,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,IShape** ppShape)
{
   CComPtr<ISuperstructureMember> ssMbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssMbr);

   Float64 Xs;
   SegmentIndexType segIdx;
   CComPtr<ISuperstructureMemberSegment> segment;
   ssMbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);

   return CreateGirderShapeBySegment(bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,ppShape);
}

STDMETHODIMP CSectionCutTool::CreateGirderShapeBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx, IShape** ppShape)
{
   // Validate input
   CHECK_RETOBJ(ppShape);
   CHECK_IN(bridge);

   return CreateGirderShape(bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,ppShape);
}

HRESULT CSectionCutTool::CreateCompositeSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section)
{
   CComPtr<ISection> ncsection;
   HRESULT hr = CreateNoncompositeSection(bridge,ssMbrID,segIdx,Xs,stageIdx,sectionPropMethod,&ncsection);
   if ( FAILED(hr) )
   {
      return hr;
   }

   (*section) = ncsection;
   (*section)->AddRef();

   // for net properties, we only want the girder
   if ( sectionPropMethod == spmGrossNoncomposite || sectionPropMethod == spmTransformedNoncomposite || sectionPropMethod == spmNet )
   {
      return S_OK;
   }

   CComPtr<ISection> deckSection;
   hr = CreateDeckSection(bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,sectionPropMethod,&deckSection);
   if ( FAILED(hr) )
   {
      return hr;
   }

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

HRESULT CSectionCutTool::CreateDeckSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section)
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

   Float64 Econc;
   Float64 Dconc;
   CComPtr<IMaterial> material;
   deck->get_Material(&material);
   material->get_E(stageIdx,&Econc);
   material->get_Density(stageIdx,&Dconc);

   if ( IsZero(Econc) )
   {
      // Deck isn't cast yet, we are done
      return S_FALSE;
   }

   // Need to get effective flange width of the slab
   Float64 eff_flange_width;
   HRESULT hr = m_EffFlangeTool->EffectiveFlangeWidthBySegment(bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,&eff_flange_width);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 trib_flange_width;
   hr = m_EffFlangeTool->TributaryFlangeWidthBySegment(bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,&trib_flange_width);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 deck_width = Min(eff_flange_width,trib_flange_width);

   // get structural thickness of deck
   Float64 structural_depth = 0;
   deck->get_StructuralDepth(&structural_depth);

   // Build a slab shape and add it to the section
   CComPtr<IRectangle> slab;
   slab.CoCreateInstance(CLSID_Rect);
   slab->put_Height(structural_depth);
   slab->put_Width(deck_width);

   CComQIPtr<IShape> shape(slab);
   cmpSection->AddSection(shape,Econc,0.0,Dconc,0.0,IsZero(Econc) ? VARIANT_FALSE : VARIANT_TRUE );

#if defined _DEBUG
   std::map<Float64,Float64> rebarLog;
#endif
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
      rebarLayout->CreateRebarSection(ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,&rebarSection);

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

HRESULT CSectionCutTool::CreateNoncompositeSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** ppSection)
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
   HRESULT hr = segment->get_Section(stageIdx,Xs,&section);
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
   if ( deck == NULL && !IsZero(sacDepth) )
   {
      // The bridge does not have a deck and there is a sacrifical depth that
      // must be deducted from the top of the girder to account for the girder 
      // being worn down over time.
      StageIndexType sacStageIdx;
      bridge->get_SacrificialDepthStage(&sacStageIdx);

      if ( sacStageIdx <= stageIdx && sacStageIdx != INVALID_INDEX )
      {
         // need to clip sacrificial depth from top of girder
         CComPtr<IPoint2d> point;
         pntTopCenter->Clone(&point);
         point->Offset(0,-sacDepth);

         CComPtr<IVector2d> v;
         v.CoCreateInstance(CLSID_Vector2d);
         v->put_X(1.0);
         v->put_Y(0.0);

         CComPtr<ILine2d> line;
         line.CoCreateInstance(CLSID_Line2d);
         line->SetExplicit(point,v);

         CComPtr<IShape> newShape;
         primary_shape->ClipWithLine(line,&newShape);

         primary_shape.Release();
         primary_shape = newShape;
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
   ATLASSERT(punk != NULL);
   CComQIPtr<IPrecastGirder> girder(punk);
   ATLASSERT(girder != NULL);

   // need to make sure the location we are looking at is actually
   // on the precast girder or if it is in a closure pour region
   Float64 segment_length; // end-to-end segment length
   segment->get_Length(&segment_length);
   bool bIsPointOnSegment = ( InRange(0.0,Xs,segment_length) ? true : false );

   // Add Strands and Rebar
   if ( sectionPropMethod != spmGross && sectionPropMethod != spmGrossNoncomposite )
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
            CComPtr<IPoint2dCollection> strandLocations;
            CComPtr<IIndexArray> debondPositions;

            if ( i == 0 )
            {
               girder->get_StraightStrandMaterial(&strandMaterial);
               girder->get_StraightStrandPositions(Xs,&strandLocations);
               girder->GetStraightStrandsDebondedByPositionIndex(etStart,Xs,&debondPositions);
            }
            else if ( i == 1 )
            {
               girder->get_HarpedStrandMaterial(&strandMaterial);
               girder->get_HarpedStrandPositions(Xs,&strandLocations);
               debondPositions.CoCreateInstance(CLSID_IndexArray); // empty array
            }
            else
            {
               girder->get_TemporaryStrandMaterial(&strandMaterial);
               girder->get_TemporaryStrandPositions(Xs,&strandLocations);
               debondPositions.CoCreateInstance(CLSID_IndexArray); // empty array
            }

            strandMaterial.QueryInterface(&material);
            Float64 Estrand, Dstrand;
            material->get_E(stageIdx,&Estrand);
            material->get_Density(stageIdx,&Dstrand);

#if defined LUMP_STRANDS
            // bonded strands
            Float64 A  = 0;
            Float64 AX = 0;
            Float64 AY = 0;

            // debonded strands
            Float64 Adb  = 0;
            Float64 AdbX = 0;
            Float64 AdbY = 0;
#endif // LUMP_STRANDS

            CComPtr<IPoint2d> point;
            CComPtr<IEnumPoint2d> enum_points;
            strandLocations->get__Enum(&enum_points);
            StrandIndexType strandIndex = 0;
            while ( enum_points->Next(1,&point,NULL) != S_FALSE )
            {
               // x measured from CL girder
               // y measured from top of girder
               Float64 x,y;
               point->Location(&x,&y);

               Float64 Aps;
               strandMaterial->get_NominalArea(&Aps);

               IndexType foundIndex;
               HRESULT hr = debondPositions->Find(strandIndex,&foundIndex);
               bool bIsDebonded = SUCCEEDED(hr) ? true : false;

#if defined LUMP_STRANDS
               if ( bIsDebonded )
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

               centroid->Move(xTop + x,yTop + y);

               if ( sectionPropMethod == spmTransformed || sectionPropMethod == spmTransformedNoncomposite )
               {
                  if ( bDebonded )
                  {
                     // Strand is debonded so it just creates a hole in the cross section here
                     // model the hole and not the strand
                     // (e.g. EA = EconcAg + Astrand(0 - Econc) = EconcAg - Astrand(Econc) = (Ag-Astrand)Econc
                     Estrand = 0;
                     Dstrand = 0;
                  }
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
#endif // LUMP_STRANDS
               point.Release();
               strandIndex++;
            }

#if defined LUMP_STRANDS
            if ( !IsZero(A) )
            {
               Float64 Aps = A;
               Float64 x = AX/A;
               Float64 y = AY/A;

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

               centroid->Move(xTop + x,yTop + y);

               if ( sectionPropMethod == spmNet )
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
            }

            if ( !IsZero(Adb) )
            {
               Float64 Aps = Adb;
               Float64 x = AdbX/Adb;
               Float64 y = AdbY/Adb;

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

               centroid->Move(xTop + x,yTop + y);

               // Debonded strands just create a hole in the cross section
               // model the hole and not the strand
               // (e.g. EA = EconcAg + Astrand(0 - Econc) = EconcAg - Astrand(Econc) = (Ag-Astrand)Econc
               Estrand = 0;
               Dstrand = 0;

               // EA = EgAg + Astrand(Estrand-Eg) = Eg(Ag-Astrand) + (Estrand)(Astrand)
               // models the strand and makes a hole in the concrete for the strand
               CComQIPtr<IShape> strand_shape(strandShape);
               compositeSection->AddSection(strand_shape,Estrand,Econc,Dstrand,Dconc,VARIANT_TRUE);
            }
#endif // LUMP_STRANDS
         } // End of Strand

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
      CComQIPtr<IItemData> itemData(ssmbr);
      CComPtr<IUnknown> unk;
      itemData->GetItemData(CComBSTR("Tendons"),&unk);
      CComQIPtr<ITendonCollection> tendons(unk);

      DuctIndexType nTendons = 0; // # tendons is the same as # ducts in this context
      if ( tendons )
      {
         tendons->get_Count(&nTendons);
      }

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
         Float64 Xg; // measured in girder coordinates
         ssmbr->GetDistanceFromStart(segIdx,Xs,&Xg);


         CComPtr<IPoint3d> pntCG;
         tendon->get_CG(Xg,tmPath,&pntCG);

         // location of duct in Gross Section Coordinates
         if ( pntCG )
         {
            Float64 x,y,z;
            pntCG->Location(&x,&y,&z);
            ATLASSERT(IsEqual(Xg,z));
            ATLASSERT(y <= 0); // below top of girder

            // if Etendon is zero, the tendon is not installed yet
            // Model the hole for the duct. Model this hole for gross, transformed and net properties
            if ( IsZero(Etendon) )
            {
               // Put holes for ducts into girder
               Float64 ductDiameter;
               tendon->get_OutsideDiameter(&ductDiameter);

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
         } // if pntCG
      } // next duct
   } // if not gross properties

   return S_OK;
}

HRESULT CSectionCutTool::LayoutRebar(ICompositeSectionEx* compositeSection,Float64 Econc,Float64 Dconc,IRebarSection* rebarSection,Float64 xTop,Float64 yTop,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod)
{
   CComPtr<IEnumRebarSectionItem> enumRebarSectionItem;
   rebarSection->get__EnumRebarSectionItem(&enumRebarSectionItem);

   CComPtr<IRebarSectionItem> rebarSectionItem;
   while ( enumRebarSectionItem->Next(1,&rebarSectionItem,NULL) != S_FALSE )
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
         deckBoundary->get_EdgePath(stLeft,VARIANT_TRUE,&leftPath);
         deckBoundary->get_EdgePath(stRight,VARIANT_TRUE,&rightPath);

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
         deck->get_StructuralDepth(&depth);

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

HRESULT CSectionCutTool::CreateGirderShape(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,IShape** ppShape)
{
   // distFromStartOfSegment is in segment coordinates
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   CComPtr<IShape> primary_shape;
   segment->get_PrimaryShape(Xs,&primary_shape);

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

#pragma Reminder("UPDATE: the code here is very similiar to building the section model")
   // find a way to consolidate it for to make it easier to maintain

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
   if ( deck == NULL && !IsZero(sacDepth) )
   {
      // The bridge does not have a deck and there is a sacrifical depth that
      // must be deducted from the top of the girder to account for the girder 
      // being worn down over time.
      StageIndexType sacStageIdx;
      bridge->get_SacrificialDepthStage(&sacStageIdx);

      if ( sacStageIdx <= stageIdx && sacStageIdx != INVALID_INDEX )
      {
         // need to clip sacrificial depth from top of girder
         CComPtr<IPoint2d> point;
         pntTopCenter->Clone(&point);
         point->Offset(0,-sacDepth);

         CComPtr<IVector2d> v;
         v.CoCreateInstance(CLSID_Vector2d);
         v->put_X(1.0);
         v->put_Y(0.0);

         CComPtr<ILine2d> line;
         line.CoCreateInstance(CLSID_Line2d);
         line->SetExplicit(point,v);

         CComPtr<IShape> newShape;
         primary_shape->ClipWithLine(line,&newShape);

         primary_shape.Release();
         primary_shape = newShape;
      }
   }

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
         Float64 Xg; // in girder coordinates
         ssmbr->GetDistanceFromStart(segIdx,Xs,&Xg);

         CComPtr<IPoint3d> pntCG;
         tendon->get_CG(Xg,tmPath,&pntCG); // Xg is in Girder Coordinates

         ATLASSERT(pntCG != NULL);

         if ( pntCG == NULL )
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

         // Tendon is not installed in this stage
         if ( IsZero(Etendon) )
         {
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
         } // adding hole
      } // next duct
   }


   ///////////////////
   // Model deck
   ///////////////////

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

      // Need to get tributary flange width of the slab
      // This is the big difference between CreateGirderSection and CreateGirderShape.... Section is structural
      // and uses the effective flange width, Shape is graphical and uses the tributary width
      Float64 trib_flange_width, twLeft, twRight;
      HRESULT hr = m_EffFlangeTool->TributaryFlangeWidthBySegmentEx(bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,&twLeft,&twRight,&trib_flange_width);
      if ( FAILED(hr) )
      {
         return hr;
      }

      // get structural thickness of deck
      Float64 structural_depth = 0;
      deck->get_StructuralDepth(&structural_depth);

      // Build a slab shape and add it to the section
      CComPtr<IRectangle> slab;
      slab.CoCreateInstance(CLSID_Rect);
      slab->put_Height(structural_depth);
      slab->put_Width(trib_flange_width);

      // put slab on top of beam 
      // for exterior girders, overhang and spacing may not be the same.
      // since we want a graphical representation here, offset the slab so that it is in the correct location
      Float64 X;
      pntTopCenter->get_X(&X);
      X -= twLeft;
      X += trib_flange_width/2;
      pntTopCenter->put_X(X);
      CComQIPtr<IXYPosition> slab_position(slab);
      slab_position->put_LocatorPoint(lpBottomCenter,pntTopCenter);

      CComQIPtr<IShape> slab_shape(slab);
      compositeShape->AddShape(slab_shape,VARIANT_FALSE);
   }

   primary_shape.CopyTo(ppShape);

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

   CComPtr<IPoint2dCollection> points;
   pShape->get_PolyPoints(&points);
   CComPtr<IPoint2d> pnt;
   CComPtr<IEnumPoint2d> enumPoints;
   points->get__Enum(&enumPoints);
   while ( enumPoints->Next(1,&pnt,NULL) != S_FALSE )
   {
      Float64 x;
      pnt->get_X(&x);
      x /= cos(skewAngle);
      pnt->put_X(x);

      pnt.Release();
   }

   CComPtr<IPolyShape> polyShape;
   polyShape.CoCreateInstance(CLSID_PolyShape);
   polyShape->AddPoints(points);

   CComQIPtr<IShape> s(polyShape);
   return s.CopyTo(ppSkewedShape);
}

HRESULT CSectionCutTool::CreateBarrierShape(DirectionType side,IGenericBridge* bridge,Float64 station,IDirection* pDirection,IShape** ppShape)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(ppShape);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   CComPtr<IProfile> profile;
   alignment->get_Profile(&profile);

   // many of the calls below are most efficient with a station object
   // create one and use it.
   CComPtr<IStation> objStation;
   objStation.CoCreateInstance(CLSID_Station);
   objStation->SetStation(INVALID_INDEX,station); // normalized station

   CComPtr<IDirection> dirCutLine;
   if ( pDirection == NULL )
   {
      alignment->Normal(CComVariant(objStation),&dirCutLine); // normal to the right
      dirCutLine->IncrementBy(CComVariant(M_PI)); // normal to the left
   }
   else
   {
      dirCutLine = pDirection;
   }

   CComPtr<IPoint2d> pntAlignment; // point on the alignment at station
   alignment->LocatePoint(CComVariant(objStation),omtAlongDirection,0.0,CComVariant(pDirection),&pntAlignment);

   // Get Left top point of deck
   CComPtr<IPoint2d> pntDeckEdge;
   m_BridgeGeometryTool->DeckEdgePoint(bridge,station,dirCutLine,side,&pntDeckEdge);

   CComPtr<IStation> offsetStation;
   Float64 offset_normal_to_alignment;
   alignment->Offset(pntDeckEdge,&offsetStation,&offset_normal_to_alignment);

   Float64 deck_edge_elev;
   profile->Elevation(CComVariant(offsetStation),offset_normal_to_alignment,&deck_edge_elev);

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

   CComQIPtr<IXYPosition> position(shape);
   // rotate shape to match deck slope
   Float64 dx;
   pntAlignment->DistanceEx(pntDeckEdge,&dx);
   Float64 alignment_elev;
   profile->Elevation(CComVariant(objStation),0.0,&alignment_elev);
   Float64 dy = (side == qcbLeft ? alignment_elev - deck_edge_elev : deck_edge_elev - alignment_elev);
   Float64 slope = dy/dx;
   Float64 angle = atan(slope);
   CComPtr<IPoint2d> hook_point;
   position->get_LocatorPoint(lpHookPoint,&hook_point);
   position->RotateEx(hook_point,angle);

   // move shape into bridge section coordinates
   position->Offset(offset_normal_to_alignment,deck_edge_elev);

   // Project shape onto cut line
   CComPtr<IDirection> normal;
   alignment->Normal(CComVariant(objStation),&normal); // normal to right
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
   while ( enumMbrs->Next(1,&mbr,NULL) != S_FALSE )
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
         if ( pntIntersect != NULL )
         {
            CComPtr<IStation> objGirderStation;
            Float64 normalOffset;
            alignment->Offset(pntIntersect,&objGirderStation,&normalOffset);
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

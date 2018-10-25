///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2014  Washington State Department of Transportation
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

// EffectiveFlangeWidthTool.cpp : Implementation of CEffectiveFlangeWidthTool

#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "EffectiveFlangeWidthTool.h"
#include "EffectiveFlangeWidthDetails.h"
#include "BridgeGeometryTool.h"
#include "Helpers.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEffectiveFlangeWidthTool
HRESULT CEffectiveFlangeWidthTool::FinalConstruct()
{
   CComObject<CBridgeGeometryTool>* pBGTool;
   HRESULT hr = CComObject<CBridgeGeometryTool>::CreateInstance(&pBGTool);
   if ( FAILED(hr) || pBGTool == NULL )
      return E_FAIL;

   m_BridgeGeometryTool = pBGTool;

   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthTool::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IEffectiveFlangeWidthTool
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CEffectiveFlangeWidthTool::TributaryFlangeWidthBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 distFromStartOfSSMbr, GirderIDType leftSSMbrID, GirderIDType rightSSMbrID, Float64 *tribFlangeWidth)
{
   Float64 twLeft, twRight;
   return TributaryFlangeWidthBySSMbrEx(bridge,ssMbrID,distFromStartOfSSMbr,leftSSMbrID,rightSSMbrID,&twLeft,&twRight,tribFlangeWidth);
}

STDMETHODIMP CEffectiveFlangeWidthTool::TributaryFlangeWidthBySSMbrEx(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 distFromStartOfSSMbr,GirderIDType leftSSMbrID, GirderIDType rightSSMbrID, Float64* twLeft,Float64* twRight,Float64 *tribFlangeWidth)
{
   CComPtr<ISuperstructureMember> ssMbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssMbr);

   Float64 distFromStartOfSegment;
   SegmentIndexType segIdx;
   CComPtr<ISegment> segment;
   ssMbr->GetDistanceFromStartOfSegment(distFromStartOfSSMbr,&distFromStartOfSegment,&segIdx,&segment);
   return TributaryFlangeWidthBySegmentEx(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,twLeft,twRight,tribFlangeWidth);
}

STDMETHODIMP CEffectiveFlangeWidthTool::TributaryFlangeWidthBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment, GirderIDType leftSSMbrID, GirderIDType rightSSMbrID, Float64 *tribFlangeWidth)
{
   Float64 twLeft, twRight;
   return TributaryFlangeWidthBySegmentEx(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,&twLeft,&twRight,tribFlangeWidth);
}

STDMETHODIMP CEffectiveFlangeWidthTool::TributaryFlangeWidthBySegmentEx(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment, GirderIDType leftSSMbrID, GirderIDType rightSSMbrID, Float64* twLeft,Float64* twRight,Float64 *tribFlangeWidth)
{
   CHECK_IN(bridge);
   CHECK_RETVAL(twLeft);
   CHECK_RETVAL(twRight);
   CHECK_RETVAL(tribFlangeWidth);

   Float64 leftSpacing;
   if ( leftSSMbrID == INVALID_ID )
   {
      m_BridgeGeometryTool->DeckOverhangBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,NULL,qcbLeft,&leftSpacing);
   }
   else
   {
      m_BridgeGeometryTool->GirderSpacingBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,&leftSpacing);
   }

   Float64 rightSpacing;
   if ( rightSSMbrID == INVALID_ID )
   {
      m_BridgeGeometryTool->DeckOverhangBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,NULL,qcbRight,&rightSpacing);
   }
   else
   {
      m_BridgeGeometryTool->GirderSpacingBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,rightSSMbrID,&rightSpacing);
   }

   if ( leftSSMbrID == INVALID_ID )
   {
      if ( leftSpacing < 0 )
      {
         // centerline of the girder is not under the slab
         *twLeft = 0.0;
         if ( 0.0 < rightSpacing/2 + leftSpacing )
         {
            *twRight = rightSpacing/2 + leftSpacing;
         }
         else
         {
            *twRight = 0.0;
         }
      }
      else
      {
         *twLeft = leftSpacing;
         *twRight = rightSpacing/2;
      }
   }
   else if ( rightSSMbrID == INVALID_INDEX )
   {
      if ( rightSpacing < 0 )
      {
         // centerline of girder is not under the slab
         *twRight = 0.0;
         if ( 0.0 < leftSpacing/2 + rightSpacing )
         {
            *twLeft = leftSpacing/2 + rightSpacing;
         }
         else
         {
            *twLeft = 0.0;
         }
      }
      else
      {
         *twLeft = leftSpacing/2;
         *twRight = rightSpacing;
      }
   }
   else
   {
      *twLeft  = leftSpacing/2;
      *twRight = rightSpacing/2;
   }

   ATLASSERT( 0 <= *twLeft );
   ATLASSERT( 0 <= *twRight );

   *tribFlangeWidth = (*twLeft) + (*twRight);

   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthTool::EffectiveFlangeWidthBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 distFromStartOfSSMbr, GirderIDType leftSSMbrID, GirderIDType rightSSMbrID,Float64 *effFlangeWidth)
{
   CComPtr<IEffectiveFlangeWidthDetails> details;
   HRESULT hr = EffectiveFlangeWidthBySSMbrEx(bridge,ssMbrID,distFromStartOfSSMbr,leftSSMbrID,rightSSMbrID,&details);
   if ( FAILED(hr) )
      return hr;

   details->EffectiveFlangeWidth(effFlangeWidth);

   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthTool::EffectiveFlangeWidthBySSMbrEx(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 distFromStartOfSSMbr, GirderIDType leftSSMbrID, GirderIDType rightSSMbrID,IEffectiveFlangeWidthDetails** details)
{
   CComPtr<ISuperstructureMember> ssMbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssMbr);

   Float64 distFromStartOfSegment;
   SegmentIndexType segIdx;
   CComPtr<ISegment> segment;
   ssMbr->GetDistanceFromStartOfSegment(distFromStartOfSSMbr,&distFromStartOfSegment,&segIdx,&segment);

   return EffectiveFlangeWidthBySegmentEx(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,details);
}

STDMETHODIMP CEffectiveFlangeWidthTool::EffectiveFlangeWidthBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment, GirderIDType leftSSMbrID, GirderIDType rightSSMbrID,Float64 *effFlangeWidth)
{
   CComPtr<IEffectiveFlangeWidthDetails> details;
   HRESULT hr = EffectiveFlangeWidthBySegmentEx(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,&details);
   if ( FAILED(hr) )
      return hr;

   details->EffectiveFlangeWidth(effFlangeWidth);

   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthTool::EffectiveFlangeWidthBySegmentEx(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment, GirderIDType leftSSMbrID, GirderIDType rightSSMbrID,IEffectiveFlangeWidthDetails** details)
{
   CHECK_IN(bridge);
   CHECK_RETOBJ(details);

   CComObject<CEffectiveFlangeWidthDetails>* pDetails;
   CComObject<CEffectiveFlangeWidthDetails>::CreateInstance(&pDetails);

   (*details) = pDetails;
   (*details)->AddRef();

   HRESULT hr;

   // Get the effective span length
   // Because a structural analysis is needed to determine the effective span length, and
   // this tools isn't setup to deal with that, we will simply use the segment length
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISegment> segment;
   ssmbr->get_Segment(segIdx,&segment);
   ATLASSERT(segment);

   CComQIPtr<IItemData> item_data(segment);
   ATLASSERT(item_data); // segments must have item data
   CComPtr<IUnknown> punk;
   item_data->GetItemData(CComBSTR("Precast Girder"),&punk);

   Float64 span_length;

   if ( punk )
   {
      CComQIPtr<IPrecastGirder> girder(punk);
      girder->get_SpanLength(&span_length);
   }
   else
   {
      // we don't have a girder of a known type so just use the girder line length
      segment->get_Length(&span_length);
   }

   pDetails->put_EffectiveSpanLength(span_length);


   LocationType locationType;
   ssmbr->get_LocationType(&locationType);

   // Get the girder section at the desired location
   CComPtr<IGirderSection> section;
   hr = GetGirderSectionBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,&section);
   if ( FAILED(hr) )
      return Error(IDS_E_GIRDERSECTION,IID_IEffectiveFlangeWidthTool,GBMT_E_GIRDERSECTION);

   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);
   if ( deck == NULL )
      return Error(IDS_E_NODECK,IID_IEffectiveFlangeWidthTool,GBMT_E_NODECK);

   VARIANT_BOOL bComposite;
   deck->get_Composite(&bComposite);
   if ( bComposite == VARIANT_FALSE )
   {
      return Error(IDS_E_COMPOSITEDECK,IID_IEffectiveFlangeWidthTool,GBMT_E_COMPOSITEDECK);
   }

   CComQIPtr<ICastSlab> cip(deck);
   CComQIPtr<IPrecastSlab> sip(deck);
   CComQIPtr<IOverlaySlab> overlay(deck);

   if ( cip == NULL && sip == NULL && overlay == NULL )
      return Error(IDS_E_UNKNOWNDECKTYPE,IID_IEffectiveFlangeWidthTool,GBMT_E_UNKNOWNDECKTYPE);

   // Get slab parameters
   Float64 tSlab;
   deck->get_StructuralDepth(&tSlab);
   pDetails->put_SlabThickness(tSlab);
   pDetails->put_SlabThickness(tSlab);

   Float64 left_overhang;
   Float64 right_overhang;

   m_BridgeGeometryTool->DeckOverhangBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,NULL,qcbLeft,&left_overhang);
   m_BridgeGeometryTool->DeckOverhangBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,NULL,qcbRight,&right_overhang);

   // Get parameters for each top flange on the girder
   CollectionIndexType nFlanges;
   hr = section->get_TopFlangeCount(&nFlanges);
   if ( FAILED(hr) )
      return hr;

   Float64 tWeb;
   section->get_EffectiveWebThickness(&tWeb);

   if (nFlanges == 1 && (locationType == ltLeftExteriorGirder || locationType == ltRightExteriorGirder))
   {
      // The following is admittedly a hack for exterior, single-flange girders.
      // Previously, there was a bug where exterior girders were treated exaclty like interior,
      // and the easiest way to fix the bug is to treat left/right girder spacing equal to the overhang.
      // This "hack" is justified because effective flange width went to tributary width in 2004, and should no longer change.
      Float64 wFlange;
      section->get_TopFlangeWidth(0,&wFlange);

      Float64 spacing;
      if ( locationType == ltLeftExteriorGirder )
      {
         spacing = left_overhang;
      }
      else
      {
         spacing = right_overhang;
      }

      pDetails->AddFlangeParameters(tWeb,wFlange,spacing,spacing);

   }
   else
   {
      // multi flange and all interior girders
      Float64 left_spacing, right_spacing, prev_right_spacing;
      for ( CollectionIndexType flangeIdx = 0; flangeIdx < nFlanges; flangeIdx++ )
      {
         Float64 wFlange;
         section->get_TopFlangeWidth(flangeIdx,&wFlange);


         if ( flangeIdx == 0)
         {
            if ( locationType == ltLeftExteriorGirder )
            {
               // Exterior flange of left exterior girder
               Float64 flange_loc;
               section->get_TopFlangeLocation(flangeIdx,&flange_loc);
               ATLASSERT(flange_loc < 0); // web_loc should be neg (left of CL)
               left_spacing = left_overhang + flange_loc; 
            }
            else
            {
               // Left exterior flange of interior girder or right exterior girder

               // Need half the distance to right exterior flange of the girder to the left of this girder
               // Girder Spacing - (previous girder right flange location) - (this girder left flange location)

               Float64 s;
               m_BridgeGeometryTool->GirderSpacingBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,&s);

               CComPtr<IGirderSection> prev_section;
               CComPtr<ISegment> prev_segment;

               // this protects against the adjacent girder being shorter because of skews
               Float64 x = distFromStartOfSegment;
               //Float64 gdr_length;
               //span->get_GirderLineLength(gdrIdx-1,&gdr_length);
               //if ( gdr_length < location )
               //   x = gdr_length;

               hr = GetGirderSectionBySegment(bridge,leftSSMbrID,segIdx,x,&prev_section);
               if ( FAILED(hr) )
                  return Error(IDS_E_GIRDERSECTION,IID_IEffectiveFlangeWidthTool,GBMT_E_GIRDERSECTION);

               CollectionIndexType prev_nFlanges;
               prev_section->get_TopFlangeCount(&prev_nFlanges);

               Float64 prev_flange_loc;
               prev_section->get_TopFlangeLocation(prev_nFlanges-1,&prev_flange_loc);

               Float64 flange_loc;
               section->get_TopFlangeLocation(flangeIdx,&flange_loc);

               Float64 overhang = s + flange_loc - prev_flange_loc; // + flange_loc because it should be a neg value.

               left_spacing = overhang/2;
            }
         }

         if ( flangeIdx > 0 )
         {
            left_spacing = prev_right_spacing;
         }

         if ( flangeIdx != nFlanges-1 )
         {
            Float64 spacing;
            section->get_TopFlangeSpacing(flangeIdx,&spacing);
            right_spacing = spacing/2;
         } 

         if ( flangeIdx == nFlanges-1 )
         {
            if (locationType == ltRightExteriorGirder)
            {
               // Exterior flange of right exterior girder
               Float64 flange_loc;
               section->get_TopFlangeLocation(flangeIdx,&flange_loc);
               right_spacing = right_overhang - flange_loc;
            }
            else
            {
               // Right exterior flange of interior girder

               // Need distance to exterior flange of previous girder (half)
               // Girder Spacing - (next girder left flange location) - (this girder right flange location)
               Float64 s;
               m_BridgeGeometryTool->GirderSpacingBySegment(bridge,ssMbrID,segIdx,distFromStartOfSegment,rightSSMbrID,&s);

               CComPtr<IGirderSection> next_section;
               CComPtr<ISegment> next_segment;

               // this protects against the adjacent girder being shorter because of skews
               Float64 x = distFromStartOfSegment;
               //Float64 gdr_length;
               //span->get_GirderLineLength(gdrIdx+1,&gdr_length);
               //if ( gdr_length < location )
               //   x = gdr_length;

               hr = GetGirderSectionBySegment(bridge,rightSSMbrID,segIdx,x,&next_section);
               if ( FAILED(hr) )
                  return Error(IDS_E_GIRDERSECTION,IID_IEffectiveFlangeWidthTool,GBMT_E_GIRDERSECTION);

               Float64 next_flange_loc;
               next_section->get_TopFlangeLocation(0,&next_flange_loc);

               Float64 flange_loc;
               section->get_TopFlangeLocation(flangeIdx,&flange_loc);

               Float64 overhang = s - flange_loc + next_flange_loc; // + next_flange_loc because it should be a neg value.

               right_spacing = overhang/2;
            }
         }

         pDetails->AddFlangeParameters(tWeb,wFlange,left_spacing,right_spacing);
         prev_right_spacing = right_spacing;
      }
   } 

   return S_OK;
}

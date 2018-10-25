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

STDMETHODIMP CEffectiveFlangeWidthTool::TributaryFlangeWidth(IGenericBridge* bridge,SpanIndexType span,GirderIndexType gdr,Float64 location,Float64 *tribFlangeWidth)
{
   Float64 twLeft, twRight;
   return TributaryFlangeWidthEx(bridge,span,gdr,location,&twLeft,&twRight,tribFlangeWidth);
}

STDMETHODIMP CEffectiveFlangeWidthTool::TributaryFlangeWidthEx(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,Float64 location,Float64* twLeft,Float64* twRight,Float64 *tribFlangeWidth)
{
   CHECK_IN(bridge);
   CHECK_RETVAL(twLeft);
   CHECK_RETVAL(twRight);
   CHECK_RETVAL(tribFlangeWidth);

   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);
   CComPtr<ISpan> span;
   spans->get_Item(spanIdx,&span);

   CComPtr<IGirderSpacing> spacing;
   span->get_GirderSpacing(etStart,&spacing);

   GirderIndexType nGirders;
   span->get_GirderCount(&nGirders);

   Float64 station;
   CComPtr<IStation> objStation;
   Float64 offset;
   m_BridgeGeometryTool->StationAndOffset(bridge,spanIdx,gdrIdx,location,&objStation,&offset);
   objStation->get_Value(&station);

   if (nGirders==1)
   {
      // we have a single girder structure
      ATLASSERT(gdrIdx == 0);
      Float64 ol,or;
      m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbLeft ,&ol);
      m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbRight,&or);

      *twLeft  = ol;
      *twRight = or;
   }
   else if ( gdrIdx == 0 )
   {
      // Left exterior girder
      Float64 sl,sr;
      spacing->get_SpacingAlongGirder(gdrIdx,location,qcbRight,&sr);

      m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbLeft,&sl);

      *twLeft  = sl;
      *twRight = sr/2.0;
   }
   else if ( gdrIdx == nGirders - 1 )
   {
      // Right exterior girder
      Float64 sl,sr;
      spacing->get_SpacingAlongGirder(gdrIdx,location,qcbLeft,&sl);

      m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbRight,&sr);

      *twLeft  = sl/2.0;
      *twRight = sr;
   }
   else
   {
      // Typical interior girder
      Float64 sl, sr;
      spacing->get_SpacingAlongGirder(gdrIdx,location,qcbLeft, &sl);
      spacing->get_SpacingAlongGirder(gdrIdx,location,qcbRight,&sr);

      ATLASSERT(0 < sl && 0 < sr);

      *twLeft  = sl/2;
      *twRight = sr/2;
   }

   ATLASSERT( 0 <= *twLeft );
   ATLASSERT( 0 <= *twRight );

   *tribFlangeWidth = (*twLeft) + (*twRight);

   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthTool::EffectiveFlangeWidth(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,Float64 location, Float64 *effFlangeWidth)
{
   CComPtr<IEffectiveFlangeWidthDetails> details;
   HRESULT hr = EffectiveFlangeWidthEx(bridge,spanIdx,gdrIdx,location,&details);
   if ( FAILED(hr) )
      return hr;

   details->EffectiveFlangeWidth(effFlangeWidth);

   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthTool::EffectiveFlangeWidthEx(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,Float64 location, IEffectiveFlangeWidthDetails** details)
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
   // this tools isn't setup to deal with that, we will simply use the pier-to-pier length
   CComPtr<ISpanCollection> spans;
   hr = bridge->get_Spans(&spans);
   if ( FAILED(hr) )
      return hr;

   CComPtr<ISpan> span;
   hr = spans->get_Item(spanIdx,&span);
   if ( FAILED(hr) )
      return hr;

   CComPtr<ISuperstructureMember> ssmbr;
   span->get_SuperstructureMember(gdrIdx,&ssmbr);

   CComQIPtr<IItemData> item_data(ssmbr);
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
      hr = span->get_GirderLineLength(gdrIdx,&span_length);
      if ( FAILED(hr) )
         return hr;
   }

   pDetails->put_EffectiveSpanLength(span_length);


   GirderIndexType nGirders;
   span->get_GirderCount(&nGirders);

   // Get the girder section at the desired location
   CComPtr<IGirderSection> section;
   CComPtr<ISegment> segment;
   hr = GetGirderSection(bridge,spanIdx,gdrIdx,location,&segment,&section);
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

   if ( location < 0 )
   {
      // location is fraction girder length
      CComPtr<ISpan> span;
      spans->get_Item(spanIdx,&span);
      Float64 gdr_length;
      span->get_GirderLineLength(gdrIdx,&gdr_length);
      location *= -gdr_length;
   }

   CComPtr<IStation> objStation;
   Float64 offset;
   m_BridgeGeometryTool->StationAndOffset(bridge,spanIdx,gdrIdx,location,&objStation,&offset);
   Float64 station;
   objStation->get_Value(&station);

   // Get slab parameters
   Float64 tSlab;
   Float64 left_overhang;
   Float64 right_overhang;
   if ( cip )
   {
      Float64 gross, sacrificial;
      cip->get_GrossDepth(&gross);
      cip->get_SacrificialDepth(&sacrificial);
      tSlab = gross - sacrificial;

   }
   else if ( sip )
   {
      Float64 panel, cast, sacrificial;
      sip->get_PanelDepth(&panel);
      sip->get_CastDepth(&cast);
      sip->get_SacrificialDepth(&sacrificial);
      tSlab = panel + cast - sacrificial;
   }
   else if (overlay)
   {
      Float64 gross, sacrificial;
      overlay->get_GrossDepth(&gross);
      overlay->get_SacrificialDepth(&sacrificial);
      tSlab = gross - sacrificial;
   }

   m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbLeft,&left_overhang);
   m_BridgeGeometryTool->DeckOverhang(bridge,station,NULL,qcbRight,&right_overhang);

   pDetails->put_SlabThickness(tSlab);

   // Get parameters for each top flange on the girder
   CollectionIndexType nFlanges;
   hr = section->get_TopFlangeCount(&nFlanges);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IGirderSpacing> spacing;
   span->get_GirderSpacing(etStart,&spacing);

   Float64 tWeb;
    section->get_EffectiveWebThickness(&tWeb);

   if (nFlanges==1 && (gdrIdx==0 || gdrIdx==nGirders-1))
   {
      // The following is admittedly a hack for exterior, single-flange girders.
      // Previously, there was a bug where exterior girders were treated exaclty like interior,
      // and the easiest way to fix the bug is to treat left/right girder spacing equal to the overhang.
      // This "hack" is justified because effective flange width went to tributary width in 2004, and should no longer change.
      Float64 wFlange;
      section->get_TopFlangeWidth(0,&wFlange);

      Float64 spacing;
      if (gdrIdx==0)
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
            if ( gdrIdx == 0 )
            {
               // Exterior flange of left exterior girder
               //params->LeftSpacing.push_back(left_overhang);
               Float64 flange_loc;
               section->get_TopFlangeLocation(flangeIdx,&flange_loc);

               left_spacing = left_overhang + flange_loc; // web_loc should be neg (left of CL)
            }
            else
            {
               // Left exterior flange of interior girder

               // Need distance to exterior flange of previous girder (half)
               // Girder Spacing - (previous girder right flange location) - (this girder left flange location)
               Float64 s;
               spacing->get_SpacingAlongGirder(gdrIdx,location,qcbLeft,&s);

               CComPtr<IGirderSection> prev_section;
               CComPtr<ISegment> prev_segment;

               // this protects against the adjacent girder being shorter because of skews
               Float64 x = location;
               Float64 gdr_length;
               span->get_GirderLineLength(gdrIdx-1,&gdr_length);
               if ( gdr_length < location )
                  x = gdr_length;

               hr = GetGirderSection(bridge,spanIdx,gdrIdx-1,x,&prev_segment,&prev_section);
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
            if (gdrIdx == nGirders-1)
            {
               // Exterior flange of right exterior girder
               Float64 flange_loc;
               section->get_TopFlangeLocation(flangeIdx,&flange_loc);
               right_spacing = right_overhang - flange_loc;
            }
            else
            {
               // Right exterior flangeof interior girder

               // Need distance to exterior flange of previous girder (half)
               // Girder Spacing - (next girder left flange location) - (this girder right flange location)
               Float64 s;
               spacing->get_SpacingAlongGirder(gdrIdx,location,qcbRight,&s);

               CComPtr<IGirderSection> next_section;
               CComPtr<ISegment> next_segment;

               // this protects against the adjacent girder being shorter because of skews
               Float64 x = location;
               Float64 gdr_length;
               span->get_GirderLineLength(gdrIdx+1,&gdr_length);
               if ( gdr_length < location )
                  x = gdr_length;

               hr = GetGirderSection(bridge,spanIdx,gdrIdx+1,x,&next_segment,&next_section);
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


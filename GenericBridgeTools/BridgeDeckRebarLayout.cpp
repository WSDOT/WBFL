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

// BridgeDeckRebarLayout.cpp : Implementation of CBridgeDeckRebarLayout
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "BridgeDeckRebarLayout.h"
#include "EffectiveFlangeWidthTool.h"
#include "BridgeGeometryTool.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBridgeDeckRebarLayout
HRESULT CBridgeDeckRebarLayout::FinalConstruct()
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

void CBridgeDeckRebarLayout::FinalRelease()
{
   m_EffFlangeTool.Release();
   m_BridgeGeometryTool.Release();
   m_Bridge.Detach();
}

STDMETHODIMP CBridgeDeckRebarLayout::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBridgeDeckRebarLayout,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CBridgeDeckRebarLayout::get__EnumRebarLayoutItems(IEnumBridgeDeckRebarLayoutItems** enumRebarLayoutItems)
{
   return get__EnumElements(enumRebarLayoutItems);
}

/////////////////////////////////////////////////////////////////
HRESULT CBridgeDeckRebarLayout::DoSaveItem(IStructuredSave2* save,IRebarPattern* item)
{
   CComQIPtr<IStructuredStorage2> ssRebarPattern(item);
   return ssRebarPattern->Save(save);
}

HRESULT CBridgeDeckRebarLayout::DoLoadItem(IStructuredLoad2* load,IRebarPattern* *ppItem)
{
//   // Create a new span object
//   CComObject<CSpan>* pSpan;
//   CComObject<CSpan>::CreateInstance(&pSpan);
//   CComPtr<ISpan> newSpan = pSpan;
//
//   ATLASSERT(m_pBridge != NULL);
//   pSpan->SetBridge(m_pBridge);
//
//   CComQIPtr<IStructuredStorage2> ssSpan(newSpan);
//   HRESULT hr = ssSpan->Load(load);
//   if ( FAILED(hr) )
//      return hr;
//
//   (*ppItem) = newSpan;
//   (*ppItem)->AddRef();
//
//   return S_OK;

   // Need to polymorphically create rebar pattern item
   return E_FAIL;
}

STDMETHODIMP CBridgeDeckRebarLayout::putref_Bridge(IGenericBridge* pBridge)
{
   CHECK_IN(pBridge);
   m_Bridge.Attach(pBridge); // does not call add ref
   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarLayout::get_Bridge(IGenericBridge** ppBridge)
{
   CHECK_RETOBJ(ppBridge);
   return m_Bridge.CopyTo(ppBridge);
}

STDMETHODIMP CBridgeDeckRebarLayout::putref_EffectiveFlangeWidthTool(IEffectiveFlangeWidthTool* pTool)
{
   CHECK_IN(pTool);
   m_EffFlangeTool = pTool;
   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarLayout::get_EffectiveFlangeWidthTool(IEffectiveFlangeWidthTool* *pTool)
{
   CHECK_RETOBJ(pTool);
   (*pTool) = m_EffFlangeTool;
   (*pTool)->AddRef();
   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarLayout::CreateRebarSection(IDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,IDType leftSSMbrID,IDType rightSSMbrID,IRebarSection** section)
{
   CHECK_RETOBJ(section);
   CComPtr<IRebarSection> pSection;
   pSection.CoCreateInstance(CLSID_RebarSection);
   (*section) = pSection;
   (*section)->AddRef();

   // The reinforcing in this section is the amount of reinforcing within
   // the effective flange width
   Float64 effectiveFlangeWidth;
   m_EffFlangeTool->EffectiveFlangeWidthBySegment(m_Bridge,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,&effectiveFlangeWidth);

   // Get the distance from the start of the bridge to the point under consideration

   // station and offset of point under consideration
   CComPtr<IStation> station;
   Float64 offset;
   m_BridgeGeometryTool->StationAndOffsetBySegment(m_Bridge,ssMbrID,segIdx,distFromStartOfSegment,&station,&offset);

   // station of first pier in the bridge
   CComPtr<IPierCollection> piers;
   m_Bridge->get_Piers(&piers);
   CComPtr<IPier> pier;
   piers->get_Item(0,&pier);
   CComPtr<IStation> firstStation;
   pier->get_Station(&firstStation);

   // location is distance between stations
   CComPtr<IAlignment> alignment;
   m_Bridge->get_Alignment(&alignment);
   Float64 cutLocation;
   alignment->DistanceBetweenStations(CComVariant(station),CComVariant(firstStation),&cutLocation);
   
   CComPtr<IEnumBridgeDeckRebarLayoutItems> enumItems;
   get__EnumRebarLayoutItems(&enumItems);
   
   CComPtr<IBridgeDeckRebarLayoutItem> rebarLayoutItem;
   while ( enumItems->Next(1,&rebarLayoutItem,NULL) != S_FALSE )
   {
      CComPtr<IEnumBridgeDeckRebarPatterns> enumPatterns;
      rebarLayoutItem->get__EnumRebarPatterns(&enumPatterns);

      VARIANT_BOOL bContainsLocation;
      rebarLayoutItem->ContainsLocation(cutLocation,&bContainsLocation);
      if ( bContainsLocation == VARIANT_TRUE )
      {
         Float64 start,length;
         rebarLayoutItem->get_Start(&start);
         rebarLayoutItem->get_Length(&length);

         CComPtr<IBridgeDeckRebarPattern> rebarPattern;
         while ( enumPatterns->Next(1,&rebarPattern,NULL) != S_FALSE )
         {
            CComPtr<IRebar> rebar;
            rebarPattern->get_Rebar(&rebar);

            Float64 spacing;
            rebarPattern->get_Spacing(&spacing);

            Float64 Y;
            rebarPattern->get_Location(&Y);

            VARIANT_BOOL bLumped;
            rebarPattern->get_IsLumped(&bLumped);

            Float64 X = 0;
            CollectionIndexType nBars = 1;

            // If the rebar is "Lumped", the nominal area is Area/Length
            // Clone the rebar object, multiple nominal area by effective flange width
            // to get total area, and then update the clone.... use the clone in
            // the section cut
            if ( bLumped == VARIANT_TRUE )
            {
               CComPtr<IRebar> clone;
               rebar->Clone(&clone);

               Float64 Aps;
               clone->get_NominalArea(&Aps);
               Aps *= effectiveFlangeWidth;
               clone->put_NominalArea(Aps);
               rebar.Release();
               rebar = clone;
            }
            else
            {
               nBars = IsZero(spacing) ? 1 : CollectionIndexType(effectiveFlangeWidth/spacing) + 1;
               X = -1.0*nBars*spacing/2.0;
            }

            for ( CollectionIndexType barIdx = 0; barIdx < nBars; barIdx++ )
            {
               CComPtr<IPoint2d> point;
               point.CoCreateInstance(CLSID_Point2d);
               point->Move(X,Y);

               CComPtr<IRebarSectionItem> sectionItem;
               sectionItem.CoCreateInstance(CLSID_RebarSectionItem);
               sectionItem->Init(point,cutLocation-start,start+length-cutLocation,rebar);

               (*section)->Add(sectionItem);

               X += spacing;
            }

            rebarPattern.Release();
         }
      }

      rebarLayoutItem.Release();
   }

   return S_OK;
}

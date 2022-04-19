///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2022  Washington State Department of Transportation
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
   if ( FAILED(hr) || pTool == nullptr )
      return E_FAIL;

   m_EffFlangeTool = pTool;

   CComObject<CBridgeGeometryTool>* pBGTool;
   hr = CComObject<CBridgeGeometryTool>::CreateInstance(&pBGTool);
   if ( FAILED(hr) || pBGTool == nullptr )
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
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
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
//   ATLASSERT(m_pBridge != nullptr);
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

STDMETHODIMP CBridgeDeckRebarLayout::CreateRebarSection(IDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,IRebarSection** section)
{
   CHECK_RETOBJ(section);
   CComPtr<IRebarSection> pSection;
   pSection.CoCreateInstance(CLSID_RebarSection);
   (*section) = pSection;
   (*section)->AddRef();

   // The reinforcing in this section is the amount of reinforcing within
   // the rebar section width. The rebar section width is the lessor of
   // the effective flange width and the tributary width.
   // Effective flange width can be greater than the tributary flange width
   // when the traffic barrier is structurally continuous and additional
   // width, based on barrier stiffness, is added to the effective flange width
   Float64 effFlangeWidth;
   m_EffFlangeTool->EffectiveFlangeWidthBySegment(m_Bridge,ssMbrID,segIdx,Xs,&effFlangeWidth);

   Float64 tribFlangeWidth;
   m_EffFlangeTool->TributaryFlangeWidthBySegment(m_Bridge,ssMbrID,segIdx,Xs,&tribFlangeWidth);

   Float64 rebarSectionWidth = Min(effFlangeWidth,tribFlangeWidth);

   // Get the distance from the start of the bridge to the point under consideration
   // What we really want is the distance projected onto the alignment because
   // this is how rebar is layed out.

   // Consider negative moment deck rebar... The layout out is located based on the pier location
   // from the start of the bridge, measured along the alignment. Then the cutoff lengths are
   // measured from this reference point. However, we are asking for information based on the
   // distance along a segment in a superstructure member. We need to convert the (ssMbrID,segIdx,Xs)
   // into a point on the alignment. We want to project this point along a line that is parallel
   // to the closest pier.

   // station and offset of point under consideration
   CComPtr<IStation> station;
   Float64 offset;
   m_BridgeGeometryTool->StationAndOffsetBySegment(m_Bridge,ssMbrID,segIdx,Xs,&station,&offset);

   CComPtr<IAlignment> alignment;
   m_Bridge->get_Alignment(&alignment);

   // station of first pier in the bridge
   CComPtr<IPierCollection> piers;
   m_Bridge->get_Piers(&piers);
   CComPtr<IBridgePier> pier;
   piers->get_Item(0,&pier);
   CComPtr<IStation> firstStation;
   pier->get_Station(&firstStation);

   // location is distance between stations
   Float64 cutLocation; // location of where we cutting through the deck to get the rebar. This is measured 
                        // as a distance along the bridge measured from the first pier.
   alignment->DistanceBetweenStations(CComVariant(firstStation),CComVariant(station),&cutLocation);

   if ( cutLocation < 0 )
   {
      // when the first pier reference line is after the start of the segment (typically happens when
      // the pier location is at the CL Bearing), the cut location will be negative... cut at zero
      cutLocation = 0;
   }

   Float64 bridgeLength;
   m_Bridge->get_Length(&bridgeLength);
   if ( bridgeLength < cutLocation )
   {
      // when the last pier reference line is before the end of the segment (typically happens when
      // the pier location is at the CL Bearing), the cut location will be beyond the end of the bridge...
      // cut at the end of bridge
      cutLocation = bridgeLength;
   }
   
   CComPtr<IEnumBridgeDeckRebarLayoutItems> enumItems;
   get__EnumRebarLayoutItems(&enumItems);
   
   CComPtr<IBridgeDeckRebarLayoutItem> rebarLayoutItem;
   while ( enumItems->Next(1,&rebarLayoutItem,nullptr) != S_FALSE )
   {
      CComPtr<IEnumBridgeDeckRebarPatterns> enumPatterns;
      rebarLayoutItem->get__EnumRebarPatterns(&enumPatterns);

      VARIANT_BOOL bContainsLocation;
      rebarLayoutItem->ContainsLocation(cutLocation,offset,&bContainsLocation);
      if ( bContainsLocation == VARIANT_TRUE )
      {
         Float64 start,length;
         rebarLayoutItem->get_Start(&start);
         rebarLayoutItem->get_Length(&length);

         CComPtr<IBridgeDeckRebarPattern> rebarPattern;
         while ( enumPatterns->Next(1,&rebarPattern,nullptr) != S_FALSE )
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
               Aps *= rebarSectionWidth;
               clone->put_NominalArea(Aps);
               rebar.Release();
               rebar = clone;
            }
            else
            {
               if (IsZero(spacing))
               {
                  nBars = 1;
               }
               else
               {
                  Float64 fnBars = rebarSectionWidth / spacing;
                  nBars = (CollectionIndexType)::Round(fnBars); // round to nearest integer
               }
               X = -1.0*nBars*spacing/2.0;
            }

            for ( CollectionIndexType barIdx = 0; barIdx < nBars; barIdx++ )
            {
               CComPtr<IPoint2d> point;
               point.CoCreateInstance(CLSID_Point2d);
               point->Move(X,Y);

               CComPtr<IRebarSectionItem> sectionItem;
               sectionItem.CoCreateInstance(CLSID_RebarSectionItem);
               sectionItem->Init(point,cutLocation-start,start+length-cutLocation,htNone,htNone,rebar);

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

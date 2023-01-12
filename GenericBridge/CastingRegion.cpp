///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// CastingRegion.cpp : Implementation of CCastingRegion
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "CastingRegion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCastingRegion
HRESULT CCastingRegion::FinalConstruct()
{
   return S_OK;
}

void CCastingRegion::FinalRelease()
{
}

void CCastingRegion::Init(ICastingRegions* pParent, PierIDType startPierID, Float64 Xstart, PierIDType endPierID, Float64 Xend, IMaterial* pMaterial)
{
   m_pParent = pParent;
   m_StartPierID = startPierID;
   m_Xstart = Xstart;
   m_EndPierID = endPierID;
   m_Xend = Xend;
   m_Material = pMaterial;
}

STDMETHODIMP CCastingRegion::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICastingRegion,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//////////////////////////////////////////////////////
// ICastingRegion
STDMETHODIMP CCastingRegion::GetRange(Float64* pXbStart, Float64* pXbEnd)
{
   CComPtr<IGenericBridge> bridge;
   m_pParent->get_Bridge(&bridge);

   CComPtr<IPierCollection>piers;
   bridge->get_Piers(&piers);

   CComPtr<IBridgePier> startPier;
   piers->FindPierByID(m_StartPierID, &startPier);

   CComPtr<IBridgePier> endPier;
   piers->FindPierByID(m_EndPierID, &endPier);

   Float64 XbStart;
   startPier->get_Location(&XbStart);
   *pXbStart = XbStart + m_Xstart;

   Float64 XbEnd;
   endPier->get_Location(&XbEnd);
   ATLASSERT(::IsLE(XbStart, XbEnd)); // start pier must be before end pier

   *pXbEnd = XbEnd + m_Xend;

   return S_OK;
}

STDMETHODIMP CCastingRegion::ContainsPoint(Float64 Xb,VARIANT_BOOL* pvbContainsPoint)
{
   Float64 XbStart, XbEnd;
   GetRange(&XbStart, &XbEnd);
   *pvbContainsPoint = InRange(XbStart, Xb, XbEnd) ? VARIANT_TRUE : VARIANT_FALSE;
   return S_OK;
}

STDMETHODIMP CCastingRegion::Perimeter(CollectionIndexType nMinPointsPerSide,IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   CComPtr<IGenericBridge> bridge;
   m_pParent->get_Bridge(&bridge);

   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   ATLASSERT(deck);

   CComPtr<IDeckBoundary> deckBoundary;
   deck->get_DeckBoundary(&deckBoundary);

   CastingRegionBoundary boundary;
   m_pParent->get_Boundary(&boundary);

   VARIANT_BOOL vbParallelToPier = (boundary == crbParallelToPier ? VARIANT_TRUE : VARIANT_FALSE);

   deckBoundary->get_PerimeterEx(nMinPointsPerSide, m_StartPierID, m_Xstart, m_EndPierID, m_Xend, vbParallelToPier, ppPoints);

   return S_OK;
}

STDMETHODIMP CCastingRegion::putref_Material(IMaterial* pMaterial)
{
   CHECK_IN(pMaterial);
   m_Material = pMaterial;
   return S_OK;
}

STDMETHODIMP CCastingRegion::get_Material(IMaterial** ppMaterial)
{
   CHECK_RETOBJ(ppMaterial);
   return m_Material.CopyTo(ppMaterial);
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CCastingRegion::Load(IStructuredLoad2* load)
{
   load->BeginUnit(CComBSTR("CastingRegion"));

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CCastingRegion::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("CastingRegion"),1.0);

   save->EndUnit();
   return S_OK;
}

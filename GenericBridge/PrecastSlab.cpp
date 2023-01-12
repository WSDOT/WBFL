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

// PrecastSlab.cpp : Implementation of CPrecastSlab
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "PrecastSlab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrecastSlab
HRESULT CPrecastSlab::FinalConstruct()
{
   m_CastingRegions.CoCreateInstance(CLSID_CastingRegions);
   return IBridgeDeckImpl::Init();
}

void CPrecastSlab::FinalRelease()
{
}

STDMETHODIMP CPrecastSlab::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPrecastSlab,
      &IID_IBridgeDeck,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


void CPrecastSlab::OnBridge()
{
   m_CastingRegions->putref_Bridge(m_pBridge);
}

////////////////////////////////////////////////////////////////////////
// IBridgeDeck implementation
STDMETHODIMP CPrecastSlab::get_StructuralDepth(Float64* depth)
{
   CHECK_RETVAL(depth);

   Float64 sacDepth = 0;
   if ( m_pBridge )
      m_pBridge->get_SacrificialDepth(&sacDepth);

   *depth = m_PanelDepth + m_CastDepth - sacDepth;

   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_GrossDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_PanelDepth + m_CastDepth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::putref_DeckBoundary(IDeckBoundary* deckBoundary)
{
   CHECK_IN(deckBoundary);
   m_pDeckBoundary = deckBoundary;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_DeckBoundary(IDeckBoundary** deckBoundary)
{
   CHECK_RETOBJ(deckBoundary);
   if ( m_pDeckBoundary )
   {
      (*deckBoundary) = m_pDeckBoundary;
      (*deckBoundary)->AddRef();
   }
   else
   {
      (*deckBoundary) = nullptr;
   }

   return S_OK;
}


////////////////////////////////////////////////////////////////////////
// IPrecastSlab implementation
STDMETHODIMP CPrecastSlab::get_CastingRegions(ICastingRegions** ppRegions)
{
   CHECK_RETOBJ(ppRegions);
   return m_CastingRegions.CopyTo(ppRegions);
}

STDMETHODIMP CPrecastSlab::putref_CastingRegions(ICastingRegions* pRegions)
{
   CHECK_IN(pRegions);
   m_CastingRegions = pRegions;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_PanelDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_PanelDepth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::put_PanelDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_PanelDepth,depth) )
      return S_OK;

   m_PanelDepth = depth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_CastDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_CastDepth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::put_CastDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_CastDepth,depth) )
      return S_OK;

   m_CastDepth = depth;

   return S_OK;
}


STDMETHODIMP CPrecastSlab::get_OverhangDepth(DirectionType side, Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_OverhangDepth[side];
   return S_OK;
}

STDMETHODIMP CPrecastSlab::put_OverhangDepth(DirectionType side, Float64 depth)
{
   if (depth < 0)
      return E_INVALIDARG;

   m_OverhangDepth[side] = depth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_OverhangTaper(DirectionType side, DeckOverhangTaper* taper)
{
   CHECK_RETVAL(taper);
   *taper = m_Taper[side];
   return S_OK;
}

STDMETHODIMP CPrecastSlab::put_OverhangTaper(DirectionType side, DeckOverhangTaper taper)
{
   if (taper != dotNone && taper != dotTopTopFlange && taper != dotBottomTopFlange)
      return E_INVALIDARG;

   m_Taper[side] = taper;

   return S_OK;
}

STDMETHODIMP CPrecastSlab::GetOverhang(Float64* leftDepth, DeckOverhangTaper* leftTaper, Float64* rightDepth, DeckOverhangTaper* rightTaper)
{
   CHECK_RETVAL(leftDepth);
   CHECK_RETVAL(leftTaper);
   CHECK_RETVAL(rightDepth);
   CHECK_RETVAL(rightTaper);

   *leftDepth = m_OverhangDepth[qcbLeft];
   *leftTaper = m_Taper[qcbLeft];
   *rightDepth = m_OverhangDepth[qcbRight];
   *rightTaper = m_Taper[qcbRight];

   return S_OK;
}

STDMETHODIMP CPrecastSlab::SetOverhang(Float64 leftDepth, DeckOverhangTaper leftTaper, Float64 rightDepth, DeckOverhangTaper rightTaper)
{
   HRESULT hr;
   hr = put_OverhangDepth(qcbLeft, leftDepth);
   if (FAILED(hr))
   {
      return hr;
   }

   hr = put_OverhangTaper(qcbLeft, leftTaper);
   if (FAILED(hr))
   {
      return hr;
   }

   hr = put_OverhangDepth(qcbRight, rightDepth);
   if (FAILED(hr))
   {
      return hr;
   }

   hr = put_OverhangTaper(qcbRight, rightTaper);
   if (FAILED(hr))
   {
      return hr;
   }

   return S_OK;
}

/////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CPrecastSlab::Load(IStructuredLoad2* load)
{
   load->BeginUnit(CComBSTR("PrecastSlab"));

   Float64 version;
   load->get_Version(&version);

   CComVariant var;

   load->get_Property(CComBSTR("PanelDepth"),&var);
   m_PanelDepth = var.dblVal;

   load->get_Property(CComBSTR("CastDepth"),&var);
   m_CastDepth = var.dblVal;

   if (version < 2)
   {
      // removed in version 2
      load->get_Property(CComBSTR("OverhangDepth"), &var);
      m_OverhangDepth[qcbLeft] = var.dblVal;
      m_OverhangDepth[qcbRight] = var.dblVal;

      load->get_Property(CComBSTR("Taper"), &var);
      m_Taper[qcbLeft] = (DeckOverhangTaper)var.lVal;
      m_Taper[qcbRight] = (DeckOverhangTaper)var.lVal;
   }
   else
   {
      // added in version 2
      load->get_Property(CComBSTR("LeftOverhangDepth"), &var);
      m_OverhangDepth[qcbLeft] = var.dblVal;

      load->get_Property(CComBSTR("LeftTaper"), &var);
      m_Taper[qcbLeft] = (DeckOverhangTaper)var.lVal;

      load->get_Property(CComBSTR("RightOverhangDepth"), &var);
      m_OverhangDepth[qcbRight] = var.dblVal;

      load->get_Property(CComBSTR("RightTaper"), &var);
      m_Taper[qcbRight] = (DeckOverhangTaper)var.lVal;
   }

   IBridgeDeckImpl<CPrecastSlab>::Load(load);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CPrecastSlab::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("PrecastSlab"),2.0);

   save->put_Property(CComBSTR("PanelDepth"),CComVariant(m_PanelDepth));
   save->put_Property(CComBSTR("CastDepth"),CComVariant(m_CastDepth));
   //save->put_Property(CComBSTR("OverhangDepth"),CComVariant(m_OverhangDepth)); // removed in version 2
   //save->put_Property(CComBSTR("Taper"),CComVariant(m_Taper)); // removed in version 2

   // Added in version 2
   save->put_Property(CComBSTR("LeftOverhangDepth"), CComVariant(m_OverhangDepth[qcbLeft]));
   save->put_Property(CComBSTR("LeftTaper"), CComVariant(m_Taper[qcbLeft]));
   save->put_Property(CComBSTR("RightOverhangDepth"), CComVariant(m_OverhangDepth[qcbRight]));
   save->put_Property(CComBSTR("RightTaper"), CComVariant(m_Taper[qcbRight]));

   IBridgeDeckImpl<CPrecastSlab>::Save(save);

   save->EndUnit();
   return S_OK;
}

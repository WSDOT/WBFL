///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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

// CastSlab.cpp : Implementation of CCastSlab
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "CastSlab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCastSlab
HRESULT CCastSlab::FinalConstruct()
{
   return IBridgeDeckImpl::Init();
}

void CCastSlab::FinalRelease()
{
   //if ( m_LeftPathStrategy )
   //{
   //   InternalAddRef();
   //   AtlUnadvise(m_LeftPathStrategy,IID_IOverhangPathStrategyEvents,m_dwLeftPathStrategyCookie);
   //}

   //if ( m_RightPathStrategy )
   //{
   //   InternalAddRef();
   //   AtlUnadvise(m_RightPathStrategy,IID_IOverhangPathStrategyEvents,m_dwRightPathStrategyCookie);
   //}
}

STDMETHODIMP CCastSlab::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICastSlab,
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

////////////////////////////////////////////////////////////////////////
// IBridgeDeck implementation
STDMETHODIMP CCastSlab::get_StructuralDepth(Float64* depth)
{
   CHECK_RETVAL(depth);

   Float64 sacDepth = 0;
   if ( m_pBridge )
      m_pBridge->get_SacrificialDepth(&sacDepth);

   *depth = m_GrossDepth - sacDepth;
   return S_OK;
}

STDMETHODIMP CCastSlab::putref_DeckBoundary(IDeckBoundary* deckBoundary)
{
   CHECK_IN(deckBoundary);
   m_pDeckBoundary = deckBoundary;
   return S_OK;
}

STDMETHODIMP CCastSlab::get_DeckBoundary(IDeckBoundary** deckBoundary)
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
// ICastSlab implementation
STDMETHODIMP CCastSlab::get_GrossDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_GrossDepth;
   return S_OK;
}

STDMETHODIMP CCastSlab::put_GrossDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   m_GrossDepth = depth;
   return S_OK;
}

STDMETHODIMP CCastSlab::get_OverhangDepth(DirectionType side, Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_OverhangDepth[side];
   return S_OK;
}

STDMETHODIMP CCastSlab::put_OverhangDepth(DirectionType side, Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   m_OverhangDepth[side] = depth;
   return S_OK;
}

STDMETHODIMP CCastSlab::get_OverhangTaper(DirectionType side, DeckOverhangTaper* taper)
{
   CHECK_RETVAL(taper);
   *taper = m_Taper[side];
   return S_OK;
}

STDMETHODIMP CCastSlab::put_OverhangTaper(DirectionType side, DeckOverhangTaper taper)
{
   if ( taper != dotNone && taper != dotTopTopFlange && taper != dotBottomTopFlange )
      return E_INVALIDARG;

   m_Taper[side] = taper;

   return S_OK;
}

STDMETHODIMP CCastSlab::GetOverhang(Float64* leftDepth, DeckOverhangTaper* leftTaper, Float64* rightDepth, DeckOverhangTaper* rightTaper)
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

STDMETHODIMP CCastSlab::SetOverhang(Float64 leftDepth, DeckOverhangTaper leftTaper, Float64 rightDepth, DeckOverhangTaper rightTaper)
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
STDMETHODIMP CCastSlab::Load(IStructuredLoad2* load)
{
   load->BeginUnit(CComBSTR("CastSlab"));

   Float64 version;
   load->get_Version(&version);

   CComVariant var;

   load->get_Property(CComBSTR("GrossDepth"),&var);
   m_GrossDepth = var.dblVal;

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

   IBridgeDeckImpl<CCastSlab>::Load(load);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CCastSlab::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("CastSlab"),2.0);

   save->put_Property(CComBSTR("GrossDepth"),CComVariant(m_GrossDepth));
   //save->put_Property(CComBSTR("OverhangDepth"),CComVariant(m_OverhangDepth)); // removed in version 2
   //save->put_Property(CComBSTR("Taper"),CComVariant(m_Taper)); // removed in version 2
   
   // Added in version 2
   save->put_Property(CComBSTR("LeftOverhangDepth"), CComVariant(m_OverhangDepth[qcbLeft]));
   save->put_Property(CComBSTR("LeftTaper"), CComVariant(m_Taper[qcbLeft]));
   save->put_Property(CComBSTR("RightOverhangDepth"), CComVariant(m_OverhangDepth[qcbRight]));
   save->put_Property(CComBSTR("RightTaper"), CComVariant(m_Taper[qcbRight]));

   IBridgeDeckImpl<CCastSlab>::Save(save);

   save->EndUnit();
   return S_OK;
}

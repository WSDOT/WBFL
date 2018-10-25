///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// OverlaySlab.cpp : Implementation of COverlaySlab
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "OverlaySlab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COverlaySlab
HRESULT COverlaySlab::FinalConstruct()
{
   return IBridgeDeckImpl::Init();
}

void COverlaySlab::FinalRelease()
{
}

STDMETHODIMP COverlaySlab::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IOverlaySlab,
      &IID_IBridgeDeck,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////
// IBridgeDeck implementation
STDMETHODIMP COverlaySlab::get_StructuralDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_GrossDepth - m_SacrificialDepth;
   return S_OK;
}

STDMETHODIMP COverlaySlab::putref_DeckBoundary(IDeckBoundary* deckBoundary)
{
   CHECK_IN(deckBoundary);
   m_pDeckBoundary = deckBoundary;
   return S_OK;
}

STDMETHODIMP COverlaySlab::get_DeckBoundary(IDeckBoundary** deckBoundary)
{
   CHECK_RETOBJ(deckBoundary);
   if ( m_pDeckBoundary )
   {
      (*deckBoundary) = m_pDeckBoundary;
      (*deckBoundary)->AddRef();
   }
   else
   {
      (*deckBoundary) = NULL;
   }

   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IOverlaySlab implementation
STDMETHODIMP COverlaySlab::get_GrossDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_GrossDepth;
   return S_OK;
}

STDMETHODIMP COverlaySlab::put_GrossDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_GrossDepth,depth) )
      return S_OK;

   m_GrossDepth = depth;
   return S_OK;
}

STDMETHODIMP COverlaySlab::get_SacrificialDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_SacrificialDepth;
   return S_OK;
}

STDMETHODIMP COverlaySlab::put_SacrificialDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_SacrificialDepth,depth) )
      return S_OK;

   m_SacrificialDepth = depth;
   return S_OK;
}

/////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP COverlaySlab::Load(IStructuredLoad2* load)
{
   load->BeginUnit(CComBSTR("OverlaySlab"));

   CComVariant var;

   load->get_Property(CComBSTR("GrossDepth"),&var);
   m_GrossDepth = var.dblVal;

   load->get_Property(CComBSTR("SacrificialDepth"),&var);
   m_SacrificialDepth = var.dblVal;

   IBridgeDeckImpl<COverlaySlab>::Load(load);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP COverlaySlab::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("OverlaySlab"),1.0);

   save->put_Property(CComBSTR("GrossDepth"),CComVariant(m_GrossDepth));
   save->put_Property(CComBSTR("SacrificalDepth"),CComVariant(m_SacrificialDepth));
   
   IBridgeDeckImpl<COverlaySlab>::Save(save);

   save->EndUnit();
   return S_OK;
}

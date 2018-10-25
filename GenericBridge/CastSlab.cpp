///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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
   return S_OK;
}

void CCastSlab::FinalRelease()
{
   if ( m_LeftPathStrategy )
   {
      InternalAddRef();
      AtlUnadvise(m_LeftPathStrategy,IID_IOverhangPathStrategyEvents,m_dwLeftPathStrategyCookie);
   }

   if ( m_RightPathStrategy )
   {
      InternalAddRef();
      AtlUnadvise(m_RightPathStrategy,IID_IOverhangPathStrategyEvents,m_dwRightPathStrategyCookie);
   }
}

STDMETHODIMP CCastSlab::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICastSlab,
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
STDMETHODIMP CCastSlab::get_StructuralDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_GrossDepth - m_SacrificialDepth;
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

   if ( IsEqual(m_GrossDepth,depth) )
      return S_OK;

   m_GrossDepth = depth;
   Fire_OnBridgeDeckChanged(this);
   return S_OK;
}

STDMETHODIMP CCastSlab::get_OverhangDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_OverhangDepth;
   return S_OK;
}

STDMETHODIMP CCastSlab::put_OverhangDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_OverhangDepth,depth) )
      return S_OK;

   m_OverhangDepth = depth;
   Fire_OnBridgeDeckChanged(this);
   return S_OK;
}

STDMETHODIMP CCastSlab::get_SacrificialDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_SacrificialDepth;
   return S_OK;
}

STDMETHODIMP CCastSlab::put_SacrificialDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_SacrificialDepth,depth) )
      return S_OK;

   m_SacrificialDepth = depth;
   Fire_OnBridgeDeckChanged(this);
   return S_OK;
}

STDMETHODIMP CCastSlab::get_Fillet(Float64* fillet)
{
   CHECK_RETVAL(fillet);
   *fillet = m_Fillet;
   return S_OK;
}

STDMETHODIMP CCastSlab::put_Fillet(Float64 fillet)
{
   if ( fillet < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_Fillet,fillet) )
      return S_OK;

   m_Fillet = fillet;
   Fire_OnBridgeDeckChanged(this);
   return S_OK;
}

STDMETHODIMP CCastSlab::get_OverhangTaper(DeckOverhangTaper* taper)
{
   CHECK_RETVAL(taper);
   *taper = m_Taper;
   return S_OK;
}

STDMETHODIMP CCastSlab::put_OverhangTaper(DeckOverhangTaper taper)
{
   if ( taper != dotNone && taper != dotTopTopFlange && taper != dotBottomTopFlange )
      return E_INVALIDARG;

   if ( m_Taper == taper )
      return S_OK;

   m_Taper = taper;
   Fire_OnBridgeDeckChanged(this);

   return S_OK;
}

STDMETHODIMP CCastSlab::get_LeftOverhangPathStrategy(IOverhangPathStrategy** strategy)
{
   CHECK_RETOBJ(strategy);
   (*strategy) = m_LeftPathStrategy;

   if ( *strategy )
      (*strategy)->AddRef();

   return S_OK;
}

STDMETHODIMP CCastSlab::putref_LeftOverhangPathStrategy(IOverhangPathStrategy* strategy)
{
   if ( m_LeftPathStrategy.IsEqualObject(strategy) )
      return S_OK;

   CComPtr<IUnknown> punk;
   QueryInterface(IID_IUnknown,(void**)&punk);

   HRESULT hr;
   DWORD dwCookie;
   if ( strategy )
   {
      hr = AtlAdvise(strategy,punk,IID_IOverhangPathStrategyEvents,&dwCookie);
      if ( FAILED(hr) )
         return hr; // can't sink on new path... get outta here before anything gets changed

      InternalRelease(); // break circular reference
   }

   // unsink on the old strategy (if there was on)
   if ( m_LeftPathStrategy )
   {
      InternalAddRef();

      hr = AtlUnadvise(m_LeftPathStrategy,IID_IOverhangPathStrategyEvents,m_dwLeftPathStrategyCookie);
      ATLASSERT( SUCCEEDED(hr) );
   }

   m_LeftPathStrategy = strategy;

   if ( m_LeftPathStrategy )
   {
      m_dwLeftPathStrategyCookie = dwCookie;
   }
   
   Fire_OnBridgeDeckChanged(this);
   return S_OK;
}

STDMETHODIMP CCastSlab::get_RightOverhangPathStrategy(IOverhangPathStrategy** strategy)
{
   CHECK_RETOBJ(strategy);
   (*strategy) = m_RightPathStrategy;

   if ( *strategy )
      (*strategy)->AddRef();

   return S_OK;
}

STDMETHODIMP CCastSlab::putref_RightOverhangPathStrategy(IOverhangPathStrategy* strategy)
{
   if ( m_RightPathStrategy.IsEqualObject(strategy) )
      return S_OK;

   CComPtr<IUnknown> punk;
   QueryInterface(IID_IUnknown,(void**)&punk);

   HRESULT hr;
   DWORD dwCookie;
   if ( strategy )
   {
      hr = AtlAdvise(strategy,punk,IID_IOverhangPathStrategyEvents,&dwCookie);
      if ( FAILED(hr) )
         return hr; // can't sink on new path... get outta here before anything gets changed

      InternalRelease(); // break circular reference
   }

   // unsink on the old strategy (if there was on)
   if ( m_RightPathStrategy )
   {
      InternalAddRef();

      hr = AtlUnadvise(m_RightPathStrategy,IID_IOverhangPathStrategyEvents,m_dwRightPathStrategyCookie);
      ATLASSERT( SUCCEEDED(hr) );
   }

   m_RightPathStrategy = strategy;

   if ( m_RightPathStrategy )
   {
      m_dwRightPathStrategyCookie = dwCookie;
   }
   
   Fire_OnBridgeDeckChanged(this);
   return S_OK;
}

STDMETHODIMP CCastSlab::get_LeftOverhangPath(IPath** path)
{
   CHECK_RETOBJ(path);

   if ( m_LeftPathStrategy )
      return m_LeftPathStrategy->get_Path(path);

   return E_FAIL;
}

STDMETHODIMP CCastSlab::get_RightOverhangPath(IPath** path)
{
   CHECK_RETOBJ(path);

   if ( m_RightPathStrategy )
      return m_RightPathStrategy->get_Path(path);

   return E_FAIL;
}

STDMETHODIMP CCastSlab::Clone(IBridgeDeck** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CCastSlab>* pClone;
   CComObject<CCastSlab>::CreateInstance(&pClone);

   CComPtr<ICastSlab> slab;
   slab = pClone;

   CComQIPtr<IBridgeDeck> deck(slab);

   IBridgeDeckImpl<CCastSlab>::Clone(&deck);

   slab->put_Fillet(m_Fillet);
   slab->put_GrossDepth(m_GrossDepth);
   slab->put_SacrificialDepth(m_SacrificialDepth);
   slab->put_OverhangTaper(m_Taper);
   slab->put_OverhangDepth(m_OverhangDepth);
   slab->putref_LeftOverhangPathStrategy(m_LeftPathStrategy);
   slab->putref_RightOverhangPathStrategy(m_RightPathStrategy);

   (*clone) = deck;
   (*clone)->AddRef();

   return S_OK;
}

/////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CCastSlab::Load(IStructuredLoad2* load)
{
   load->BeginUnit(CComBSTR("CastSlab"));

   CComVariant var;

   load->get_Property(CComBSTR("LeftOverhangPathStrategy"),&var);
   CComPtr<IOverhangPathStrategy> left_path_strategy;
   var.punkVal->QueryInterface(&left_path_strategy);
   putref_LeftOverhangPathStrategy(left_path_strategy);

   load->get_Property(CComBSTR("RightOverhangPathStrategy"),&var);
   CComPtr<IOverhangPathStrategy> right_path_strategy;
   var.punkVal->QueryInterface(&right_path_strategy);
   putref_RightOverhangPathStrategy(right_path_strategy);

   load->get_Property(CComBSTR("Fillet"),&var);
   m_Fillet = var.dblVal;

   load->get_Property(CComBSTR("GrossDepth"),&var);
   m_GrossDepth = var.dblVal;

   load->get_Property(CComBSTR("OverhangDepth"),&var);
   m_OverhangDepth = var.dblVal;

   load->get_Property(CComBSTR("SacrificialDepth"),&var);
   m_SacrificialDepth = var.dblVal;

   load->get_Property(CComBSTR("Taper"),&var);
   m_Taper = (DeckOverhangTaper)var.lVal;

   IBridgeDeckImpl<CCastSlab>::Load(load);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CCastSlab::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("CastSlab"),1.0);

   save->put_Property(CComBSTR("LeftOverhangPathStrategy"),CComVariant(m_LeftPathStrategy));
   save->put_Property(CComBSTR("RightOverhangPathStrategy"),CComVariant(m_RightPathStrategy));
   save->put_Property(CComBSTR("Fillet"),CComVariant(m_Fillet));
   save->put_Property(CComBSTR("GrossDepth"),CComVariant(m_GrossDepth));
   save->put_Property(CComBSTR("OverhangDepth"),CComVariant(m_OverhangDepth));
   save->put_Property(CComBSTR("SacrificalDepth"),CComVariant(m_SacrificialDepth));
   save->put_Property(CComBSTR("Taper"),CComVariant(m_Taper));
   
   IBridgeDeckImpl<CCastSlab>::Save(save);

   save->EndUnit();
   return S_OK;
}

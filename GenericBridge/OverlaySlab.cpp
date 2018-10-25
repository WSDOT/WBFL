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
   return S_OK;
}

void COverlaySlab::FinalRelease()
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
   Fire_OnBridgeDeckChanged(this);
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
   Fire_OnBridgeDeckChanged(this);
   return S_OK;
}

STDMETHODIMP COverlaySlab::get_LeftOverhangPathStrategy(IOverhangPathStrategy** strategy)
{
   CHECK_RETOBJ(strategy);
   (*strategy) = m_LeftPathStrategy;

   if ( *strategy )
      (*strategy)->AddRef();

   return S_OK;
}

STDMETHODIMP COverlaySlab::putref_LeftOverhangPathStrategy(IOverhangPathStrategy* strategy)
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

STDMETHODIMP COverlaySlab::get_RightOverhangPathStrategy(IOverhangPathStrategy** strategy)
{
   CHECK_RETOBJ(strategy);
   (*strategy) = m_RightPathStrategy;

   if ( *strategy )
      (*strategy)->AddRef();

   return S_OK;
}

STDMETHODIMP COverlaySlab::putref_RightOverhangPathStrategy(IOverhangPathStrategy* strategy)
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

STDMETHODIMP COverlaySlab::get_LeftOverhangPath(IPath** path)
{
   CHECK_RETOBJ(path);

   if ( m_LeftPathStrategy )
      return m_LeftPathStrategy->get_Path(path);

   return E_FAIL;
}

STDMETHODIMP COverlaySlab::get_RightOverhangPath(IPath** path)
{
   CHECK_RETOBJ(path);

   if ( m_RightPathStrategy )
      return m_RightPathStrategy->get_Path(path);

   return E_FAIL;
}

STDMETHODIMP COverlaySlab::Clone(IBridgeDeck** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<COverlaySlab>* pClone;
   CComObject<COverlaySlab>::CreateInstance(&pClone);

   CComPtr<IOverlaySlab> slab;
   slab = pClone;

   CComQIPtr<IBridgeDeck> deck(slab);

   IBridgeDeckImpl<COverlaySlab>::Clone(&deck);

   slab->put_GrossDepth(m_GrossDepth);
   slab->put_SacrificialDepth(m_SacrificialDepth);
   slab->putref_LeftOverhangPathStrategy(m_LeftPathStrategy);
   slab->putref_RightOverhangPathStrategy(m_RightPathStrategy);

   (*clone) = deck;
   (*clone)->AddRef();

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

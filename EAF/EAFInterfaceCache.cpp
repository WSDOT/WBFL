///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright � 1999-2025  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


#include "StdAfx.h"
#include <EAF\EAFInterfaceCache.h>
#include "backdoor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CEAFInterfaceCache::CEAFInterfaceCache(void)
{
   m_pBroker = nullptr;
}

CEAFInterfaceCache::~CEAFInterfaceCache(void)
{
   ClearCache();
}

void CEAFInterfaceCache::SetBroker(IBroker* pBroker)
{
   m_pBroker = pBroker;
}

STDMETHODIMP_(ULONG) CEAFInterfaceCache::AddRef()
{
   // do nothing
   return 1;
}

STDMETHODIMP_(ULONG) CEAFInterfaceCache::Release()
{
   // do nothing
   return 1;
}

STDMETHODIMP CEAFInterfaceCache::QueryInterface(REFIID riid,void** ppv)
{
   return m_pBroker->QueryInterface(riid,ppv);
}

STDMETHODIMP CEAFInterfaceCache::GetInterface(REFIID riid,IUnknown** ppUnk)
{
   Interfaces::iterator found = m_Interfaces.find(riid);
   if ( found != m_Interfaces.end() )
   {
      IUnknown* pUnk = (*found).second;
      pUnk->AddRef();
      (*ppUnk) = pUnk;

      return S_OK;
   }

   // interface not found... go to the broker
   HRESULT hr = m_pBroker->GetInterface(riid,ppUnk); // calls AddRef(), released by caller
   if ( FAILED(hr) )
      return hr; // interface not found

   // interface found, cache it
   IUnknown* pUnk = *ppUnk;
   pUnk->AddRef();  // calls AddRef(), released in ClearCache()
   m_Interfaces.insert( std::make_pair(riid,*ppUnk) );

   return S_OK;
}

STDMETHODIMP CEAFInterfaceCache::Reset()
{
   ATLASSERT(false); // should never get here... agent's shouldn't be calling Reset()
   return S_OK;
}

STDMETHODIMP CEAFInterfaceCache::ShutDown()
{
   ATLASSERT(false); // should never get here... agent's shouldn't be calling ShutDown()
   return S_OK;
}

void CEAFInterfaceCache::ClearCache()
{
   Interfaces::iterator iter(m_Interfaces.begin());
   Interfaces::iterator end(m_Interfaces.end());
   for ( ; iter != end; iter++ )
   {
      (*iter).second->Release();
      (*iter).second = nullptr;
   }
   m_Interfaces.clear();
}

///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

#pragma once

#include <EAF\EAFExp.h>
#include <atlcomcli.h> // for CAdapt
#include <EAF\EAFTypes.h>
#include <map>
#include <WBFLCore.h>
#include <EAF\EAFStatusCenter.h>
#include <EAF\EAFUtilities.h>

// provides a localized interface cache so the agent doesn't
// have to go to the broker over and over again to get an interface
//
// once an agent has received an interface pointer, it is stored
// in this cache object. The next time the interface is requested
// it is retreived from this local cache before going to the broker
//
// This object implements the IBroker interface in a non-COM way
// This object is designed to be a regular data member of an agent
// and serve as a wrapper class for the real IBroker interface
//
// Using the DECLARE_AGENT_DATA and IMPLEMENT_AGENT_DATA #define's given
// below, no code changes have to be made to an agent to implement
// this class. Simply use these macros
class EAFCLASS CEAFInterfaceCache : public IBroker
{
public:
   CEAFInterfaceCache(void);
   ~CEAFInterfaceCache(void);

   void SetBroker(IBroker* pBroker);

   STDMETHOD_(ULONG,AddRef)();
   STDMETHOD_(ULONG,Release)();
   STDMETHOD(QueryInterface)(REFIID riid,void** ppv);
   STDMETHOD(GetInterface)(REFIID riid,void** ppv);
   STDMETHOD(Reset)();
   STDMETHOD(ShutDown)();

   void ClearCache();

private:
   IBroker* m_pBroker; // weak reference
   typedef std::map<IID, IUnknown*> Interfaces;
   Interfaces m_Interfaces;
};

#if defined NO_INTERFACE_CACHE
#define DECLARE_AGENT_DATA \
   IBroker* m_pBroker; \
   StatusGroupIDType m_StatusGroupID;

#define AGENT_SET_BROKER(broker) m_pBroker = broker
#define AGENT_INIT     GET_IFACE(IEAFStatusCenter,pStatusCenter); m_StatusGroupID = pStatusCenter->CreateStatusGroupID()
#define AGENT_CLEAR_INTERFACE_CACHE m_pBroker = NULL

#else

// declares the requirement data components for an agent
// In the private data area of the agent class declairation add
// DECLARE_AGENT_DATA
#define DECLARE_AGENT_DATA \
   IBroker* m_pBroker; \
   CEAFInterfaceCache m_InterfaceCache; \
   StatusGroupIDType m_StatusGroupID

#define AGENT_SET_BROKER(broker) m_InterfaceCache.SetBroker(broker); m_pBroker = &m_InterfaceCache
#define AGENT_INIT     GET_IFACE(IEAFStatusCenter,pStatusCenter); m_StatusGroupID = pStatusCenter->CreateStatusGroupID()
#define AGENT_CLEAR_INTERFACE_CACHE  m_InterfaceCache.ClearCache(); m_InterfaceCache.SetBroker(NULL); m_pBroker = NULL


#endif // NO_INTERFACE_CACHE
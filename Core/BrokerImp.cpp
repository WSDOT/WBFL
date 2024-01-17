///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2024  Washington State Department of Transportation
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

// BrokerImp.cpp : implementation file
//

#include "stdafx.h"
#include <WBFLCore.h>
//#include "Core.h"
#include "BrokerImp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrokerImp
HRESULT CBrokerImp::FinalConstruct()
{
   return S_OK;
}

void CBrokerImp::FinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.
   ClearAgents();
}

void CBrokerImp::ClearAgents()
{
   WATCH(_T("Clearing Agents"));
   std::vector< IAgent* >::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      IAgent* pAgent = *i;
      ULONG cRef = pAgent->Release();
      WATCH(_T("Ref Count = ") << cRef);

      pAgent = 0;
   }
   m_Agents.clear();
}

/////////////////////////////////////////////////////////////////////////////
// CBrokerImp message handlers
STDMETHODIMP CBrokerImp::GetInterface( REFIID riid, IUnknown** ppUnk)
{
   HRESULT hr = E_NOINTERFACE;
   Interfaces::iterator found;
   found = m_Interfaces.find( riid );
   if ( found == m_Interfaces.end() )
      return E_NOINTERFACE;

   IAgent* pAgent = (*found).second;
   return pAgent->QueryInterface( riid, (void**)ppUnk );
}

STDMETHODIMP CBrokerImp::Reset()
{
   std::vector< IAgent* >::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      IAgent* pAgent = *i;
      pAgent->Reset();
   }

   return S_OK;
}

STDMETHODIMP CBrokerImp::ShutDown()
{
   std::vector< IAgent* >::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      IAgent* pAgent = *i;
      pAgent->ShutDown();
   }

   return S_OK;
}

//////////////////////////////////////////////////////
// IBrokerInit2
STDMETHODIMP CBrokerImp::LoadAgents( CLSID * clsid, IndexType nClsid,IndexType* lErrIndex )
{
   HRESULT hr;

   // Load all the agents, wire them up with the broker, and tell them
   // to register their interfaces
   for ( IndexType i = 0; i < nClsid; i++ )
   {
      IAgent* pAgent;
      hr = ::CoCreateInstance( clsid[i], nullptr, CLSCTX_INPROC_SERVER, IID_IAgent, (void**)&pAgent );
      if ( SUCCEEDED( hr ) )
      {
         m_Agents.push_back( pAgent );
         if ( FAILED( pAgent->SetBroker( this ) ) || 
              FAILED(pAgent->RegInterfaces() ) )
         {
            ClearAgents();
            if ( lErrIndex )
               *lErrIndex = i;
            return BROKER_E_LOADAGENT;
         }
      }
      else
      {
         ClearAgents();
         if ( lErrIndex )
            *lErrIndex = i;
         return hr;
      }
   }

   // All agents are now available... Give each agent an opportunity to initialize
   // itself.  This might consist of attaching to a connection point of another agent
   // (Hence the need to wait until all agents are available).
   if ( !m_DelayInit )
   {
      IndexType count = 0;
      std::vector< IAgent* >::iterator iter;
      for ( iter = m_Agents.begin(); iter != m_Agents.end(); iter++ )
      {
         IAgent* pAgent = *iter;
         if ( FAILED(pAgent->Init()) )
         {
            if ( lErrIndex )
               *lErrIndex = count;
            
            ClearAgents();
            return BROKER_E_LOADAGENT;
         }
         count++;
      }
   }

	return S_OK;
}

STDMETHODIMP CBrokerImp::AddAgent(IAgent* pAgent)
{
   HRESULT hr = S_OK;

   hr = pAgent->SetBroker( this );
   if ( FAILED(hr) )
      return BROKER_E_ADDAGENT;

   hr = pAgent->RegInterfaces();
   if ( FAILED(hr) )
      return BROKER_E_ADDAGENT;

   if ( !m_DelayInit )
   {
      hr = pAgent->Init();
      if ( FAILED(hr) )
         return BROKER_E_ADDAGENT;
   }

   pAgent->AddRef();
   m_Agents.push_back( pAgent );
   return S_OK;
}

STDMETHODIMP CBrokerImp::FindConnectionPoint( REFIID riid, IConnectionPoint** ppCP)
{
   IConnectionPointContainer* pCPC;
   HRESULT hr = E_NOINTERFACE;
   std::vector< IAgent* >::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      IAgent* pAgent = *i;

      hr = pAgent->QueryInterface( IID_IConnectionPointContainer, (void**)&pCPC );
      if ( SUCCEEDED( hr ) )
      {
         hr = pCPC->FindConnectionPoint( riid, ppCP );

         // Done with this connection point container
         pCPC->Release();
         pCPC = 0;

         if ( SUCCEEDED(hr) )
            return hr;
      }
   }

	return hr;
}

STDMETHODIMP CBrokerImp::RegInterface( REFIID riid, IAgent* pAgent)
{
   m_Interfaces.insert( std::make_pair(riid, pAgent) );

   return S_OK;
}

STDMETHODIMP CBrokerImp::DelayInit()
{
   m_DelayInit = true;
   return S_OK;
}

STDMETHODIMP CBrokerImp::InitAgents()
{
   std::vector< IAgent* >::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      IAgent* pAgent = *i;
      HRESULT hr = pAgent->Init();
      if ( FAILED(hr) )
         return BROKER_E_ADDAGENT;
   }

   return S_OK;
}

//////////////////////////////////////////////
// IBrokerPersist
STDMETHODIMP CBrokerImp::Load(IStructuredLoad* pStrLoad)
{
   std::vector< IAgent* >::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      HRESULT hr = S_OK;
      IAgent* pAgent = *i;
      IAgentPersist* pPersist;
      hr = pAgent->QueryInterface( IID_IAgentPersist, (void**)&pPersist );
      if ( SUCCEEDED(hr) )
      {
         hr = pPersist->Load( pStrLoad );
         pPersist->Release();
         if ( FAILED(hr) )
            return hr;
      }
   }

   return S_OK;
}

STDMETHODIMP CBrokerImp::Save(IStructuredSave* pStrSave)
{
   std::vector< IAgent* >::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      HRESULT hr = S_OK;
      IAgent* pAgent = *i;
      IAgentPersist* pPersist;
      hr = pAgent->QueryInterface( IID_IAgentPersist, (void**)&pPersist );
      if ( SUCCEEDED(hr) )
      {
         hr = pPersist->Save( pStrSave );
         pPersist->Release();
         if ( FAILED(hr) )
            return hr;
      }
   }

   return S_OK;
}


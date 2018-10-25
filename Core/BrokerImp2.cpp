///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2010  Washington State Department of Transportation
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

// BrokerImp2.cpp : implementation file
//

#include "stdafx.h"
#include <WBFLCore.h>
//#include "Core.h"
#include "BrokerImp2.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DIAG_DEFINE_GROUP(IFC,DIAG_GROUP_DISABLE,0);

/////////////////////////////////////////////////////////////////////////////
// CBrokerImp2

HRESULT CBrokerImp2::FinalConstruct()
{
   return S_OK;
}

void CBrokerImp2::FinalRelease()
{
}

#if defined _DEBUG
void CBrokerImp2::ListConnectionPointLeaks(IAgentEx* pAgent)
{
   CComQIPtr<IConnectionPointContainer> pCPC(pAgent);
   if ( pCPC )
   {
      CComPtr<IEnumConnectionPoints> pEnumCP;
      pCPC->EnumConnectionPoints(&pEnumCP);

      CComPtr<IConnectionPoint> pCP;
      while ( pEnumCP->Next(1,&pCP,NULL) != S_FALSE )
      {
         CComPtr<IEnumConnections> pEnumConnections;
         pCP->EnumConnections(&pEnumConnections);

         CONNECTDATA cdata;
         while ( pEnumConnections->Next(1,&cdata,NULL) != S_FALSE )
         {
            WATCHX(IFC,0,"Leaked connection point cookie " << cdata.dwCookie);
            cdata.pUnk->Release(); // documtation says caller must call Release
         }

         pCP.Release();
      }
   }
}
#endif // _DEBUG

void CBrokerImp2::ClearAgents()
{
   WATCHX(IFC,0,"Clearing Agents");
   Agents::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      IAgentEx* pAgent = (*i).second;

#if defined _DEBUG
      USES_CONVERSION;
      OLECHAR szGUID[39];
      CLSID clsid;
      pAgent->GetClassID(&clsid);
      ::StringFromGUID2(clsid,szGUID,39);

      ListConnectionPointLeaks(pAgent);
#endif

      ULONG cRef = pAgent->Release();

#if defined _DEBUG
      WATCHX(IFC,0,"CLSID = " << OLE2A(szGUID) << " Ref Count = " << cRef);
#endif

      pAgent = 0;
   }
   m_Agents.clear();
}

/////////////////////////////////////////////////////////////////////////////
// IBroker

// returns whether item1 has a greater usage count than item 2
bool SortByUsageFrequency(const InterfaceItem& item1,const InterfaceItem& item2)
{
   return *(item1.pUsageCount) > *(item2.pUsageCount);
}

STDMETHODIMP CBrokerImp2::GetInterface( REFIID riid, void** ppv)
{
   // first check the most frequently used list
   InterfaceItem key;
   key.iid = riid;
   boost::circular_buffer<InterfaceItem>::iterator found = std::find(m_MostFrequentlyUsed.begin(),m_MostFrequentlyUsed.end(),key);
   if ( found != m_MostFrequentlyUsed.end() )
   {
      InterfaceItem& item = *found;
      ASSERT( riid == item.iid );

      // this IID is on the frequently used list
      // increment the usage count (updates in the main list of all interfaces as well)
      (*item.pUsageCount)++;

      // get the interface
      HRESULT hr = item.pAgent->QueryInterface( riid, ppv );
      if ( FAILED(hr) )
         return hr;

      // sort the MFU list based on usage count
      std::sort( m_MostFrequentlyUsed.begin(),m_MostFrequentlyUsed.end(), SortByUsageFrequency );

      return hr;
   }

   // IID is not in the most frequently used list... search for it in the regular list of interfaces
   HRESULT hr = E_NOINTERFACE;
   Interfaces::iterator interface_found;
   interface_found = m_Interfaces.find( key );
   if ( interface_found == m_Interfaces.end() )
      return E_NOINTERFACE;

   InterfaceItem& item = *interface_found;
   IAgentEx* pAgent = item.pAgent;
   hr = pAgent->QueryInterface( riid, ppv );

   if ( SUCCEEDED(hr) )
   {
      // update the usage count
      (*item.pUsageCount)++;

      // See if the usage count is high enough to be in the most frequently used list
      if ( !m_MostFrequentlyUsed.empty() )
      {
         const InterfaceItem& least_used_item = m_MostFrequentlyUsed.back();

         // a quick check to make sure sorting is ok
         ASSERT( *(least_used_item.pUsageCount) <= *(m_MostFrequentlyUsed.front().pUsageCount) );

         if ( *(least_used_item.pUsageCount) <= *(item.pUsageCount) )
         {
            // current interface item has been used more times then the least used interface item
            // in the MFU list. add the current item to the MFU list and re-sort. the least used
            // item will drop out
            m_MostFrequentlyUsed.push_front(item);

            // sort the MFU list based on usage count
            std::sort( m_MostFrequentlyUsed.begin(),m_MostFrequentlyUsed.end(), SortByUsageFrequency );
         }
      }
      else
      {
         m_MostFrequentlyUsed.push_front(item);
      }
   }

   return hr;
}

STDMETHODIMP CBrokerImp2::Reset()
{
   Agents::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      IAgentEx* pAgent = (*i).second;
      pAgent->Reset();
   }

   return S_OK;
}

#if defined _DEBUG
bool CompareCLSID(InterfaceItem& item1,InterfaceItem& item2)
{
   CLSID clsid1, clsid2;
   item1.pAgent->GetClassID(&clsid1);
   item2.pAgent->GetClassID(&clsid2);
   return clsid1 < clsid2;
}
#endif

STDMETHODIMP CBrokerImp2::ShutDown()
{
   WATCHX(IFC,0,"Broker ShutDown");
   Agents::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      IAgent* pAgent = (*i).second;
      pAgent->ShutDown();
   }

#if defined _DEBUG
   USES_CONVERSION;
   WATCHX(IFC,0,"Most frequently used interfaces");
   boost::circular_buffer<InterfaceItem>::iterator iter;
   for ( iter = m_MostFrequentlyUsed.begin(); iter != m_MostFrequentlyUsed.end(); iter++ )
   {
      InterfaceItem& item = *iter;

      OLECHAR szGUID[39];
      ::StringFromGUID2(item.iid,szGUID,39);
      WATCHX(IFC,0,"IID = " << OLE2A(szGUID) << " Usage Count = " << (*item.pUsageCount));

   }

   WATCHX(IFC,0,"");
   WATCHX(IFC,0,"Total interface usage count");

   // fill up a temporary vector so we can sort and report by CLSID
   std::vector<InterfaceItem> interfaces;
   Interfaces::iterator j;
   for ( j = m_Interfaces.begin(); j != m_Interfaces.end(); j++ )
   {
      InterfaceItem& item = *j;
      interfaces.push_back(item);
   }

   std::sort(interfaces.begin(),interfaces.end(),CompareCLSID);

   Uint64 count = 0;
   std::vector<InterfaceItem>::iterator k;
   for ( k = interfaces.begin(); k != interfaces.end(); k++ )
   {
      InterfaceItem& item = *k;

      UINT cRef = item.pAgent->AddRef();
      item.pAgent->Release();

      // every agent gets two more Release calls... decrement by 2 so that we can compare with
      // the agent ref count that gets dump in ClearArents()
      cRef -= 2;

      OLECHAR szGUID[39];
      ::StringFromGUID2(item.iid,szGUID,39);

      CLSID clsid;
      item.pAgent->GetClassID(&clsid);
      OLECHAR szCLSID[39];
      ::StringFromGUID2(clsid,szCLSID,39);
      WATCHX(IFC,0,"CLSID = " << OLE2A(szCLSID) << " IID = " << OLE2A(szGUID) << " Usage Count = " << (*item.pUsageCount) << " Agent Ref Count = " << cRef);

      count += (*item.pUsageCount);
   }
   WATCHX(IFC,0,"Total count = " << count);
#endif // _DEBUG

   ClearAgents();

   return S_OK;
}

//////////////////////////////////////////////////////
// IBrokerInitEx2
STDMETHODIMP CBrokerImp2::LoadAgents( CLSID * clsid, long nClsid,long* lErrIndex )
{
   HRESULT hr;

   // Load all the agents, wire them up with the broker, and tell them
   // to register their interfaces
   for ( long i = 0; i < nClsid; i++ )
   {
      IAgentEx* pAgent;
      hr = ::CoCreateInstance( clsid[i], NULL, CLSCTX_INPROC_SERVER, IID_IAgentEx, (void**)&pAgent );
      if ( SUCCEEDED( hr ) )
      {
         m_Agents.insert( std::make_pair(clsid[i],pAgent) );
         if ( FAILED( pAgent->SetBroker( this) ) || 
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
      long count = 0;
      Agents::iterator iter;
      for ( iter = m_Agents.begin(); iter != m_Agents.end(); iter++ )
      {
         IAgentEx* pAgent = (*iter).second;
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

STDMETHODIMP CBrokerImp2::AddAgent(IAgentEx* pAgent)
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
   CLSID clsid;
   pAgent->GetClassID(&clsid);

   m_Agents.insert( std::make_pair(clsid,pAgent) );

   return S_OK;
}

STDMETHODIMP CBrokerImp2::FindConnectionPoint( REFIID riid, IConnectionPoint** ppCP)
{
   IConnectionPointContainer* pCPC;
   HRESULT hr = E_NOINTERFACE;
   Agents::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      IAgentEx* pAgent = (*i).second;

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

STDMETHODIMP CBrokerImp2::RegInterface( REFIID riid, IAgentEx* pAgent)
{
   InterfaceItem item;
   item.iid = riid;
   item.pAgent = pAgent;
   (*item.pUsageCount) = 0;
   m_Interfaces.insert( item );

   return S_OK;
}

STDMETHODIMP CBrokerImp2::DelayInit()
{
   m_DelayInit = true;
   return S_OK;
}

STDMETHODIMP CBrokerImp2::InitAgents()
{
   std::vector<IAgentEx*> secondPassAgents;

   Agents::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      IAgentEx* pAgent = (*i).second;
      HRESULT hr = pAgent->Init();
      if ( FAILED(hr) )
         return BROKER_E_ADDAGENT;

      if ( hr == AGENT_S_SECONDPASSINIT )
      {
         IAgentEx* pAgentEx;
         hr = pAgent->QueryInterface( IID_IAgentEx, (void**)&pAgentEx );
         if ( SUCCEEDED(hr) && pAgentEx )
            secondPassAgents.push_back(pAgentEx);
      }
   }

   std::vector< IAgentEx* >::iterator j;
   for ( j = secondPassAgents.begin(); j != secondPassAgents.end(); j++ )
   {
      IAgentEx* pAgent = *j;
      HRESULT hr = pAgent->Init2();
      pAgent->Release(); // release the AddRef call from QueryInterace above
      if ( FAILED(hr) )
         return BROKER_E_ADDAGENT;
   }

   WATCHX(IFC,0,"# Agents = " << m_Agents.size() << " # Interfaces = " << m_Interfaces.size());

   return S_OK;
}

////////////////////////////////////////////////////////
// IBrokerPersist
STDMETHODIMP CBrokerImp2::Load(IStructuredLoad* pStrLoad)
{
   HRESULT hr = pStrLoad->BeginUnit("Broker");
   if ( FAILED(hr) )
   {
      // the data isn't saved in the current format
      // it was probably created using CBrokerImp
      return LoadOldFormat(pStrLoad); 
   }

   // until we run out of "Agent"units
   while ( SUCCEEDED(pStrLoad->BeginUnit("Agent")) )
   {
      // get CLSID of the agent
      CComVariant varCLSID;
      varCLSID.vt = VT_BSTR;
      HRESULT hr = pStrLoad->get_Property("CLSID", &varCLSID);
      if ( FAILED(hr) )
         return hr;

      CLSID clsid;
      hr = ::CLSIDFromString(CComBSTR(varCLSID.bstrVal), &clsid);
      if ( FAILED(hr) )
         return hr;

      // get the agent
      Agents::iterator found = m_Agents.find(clsid);
      if ( found != m_Agents.end() )
      {
         IAgentEx* pAgent = (*found).second;

         IAgentPersist* pPersist;
         hr = pAgent->QueryInterface(IID_IAgentPersist,(void**)&pPersist);
         if ( SUCCEEDED(hr) )
         {
            hr = pPersist->Load( pStrLoad );
            pPersist->Release();
            if ( FAILED(hr) )
               return hr;
         }
         else
         {
            // agent previous saved data, but it isn't capable of loading it ???
         }
      }
      else
      {
         // agent not found... 
         // this could be because it is a 3rd party agent and it isn't installed
         // skip to the next "Agent" unit
      }

      pStrLoad->EndUnit(); // end of "Agent" unit
   };

   pStrLoad->EndUnit(); // Broker

   return S_OK;
}

STDMETHODIMP CBrokerImp2::Save(IStructuredSave* pStrSave)
{
   pStrSave->BeginUnit("Broker",1.0);

   Agents::iterator iter;
   for ( iter = m_Agents.begin(); iter != m_Agents.end(); iter++ )
   {
      HRESULT hr = S_OK;
      IAgentEx* pAgent = (*iter).second;
      IAgentPersist* pPersist;
      hr = pAgent->QueryInterface( IID_IAgentPersist, (void**)&pPersist );
      if ( SUCCEEDED(hr) )
      {
         // create a unit around each agent's data
         pStrSave->BeginUnit("Agent",1.0);

         LPOLESTR postr = 0;
         hr = StringFromCLSID((*iter).first, &postr);

         // capture the class id of the agent
         pStrSave->put_Property("CLSID",CComVariant(postr));

         CoTaskMemFree(postr);

         hr = pPersist->Save( pStrSave ); // agent to save its own data
         pPersist->Release();
         if ( FAILED(hr) )
            return hr;

         pStrSave->EndUnit(); // end of "Agent" unit
      }
   }

   pStrSave->EndUnit(); // Broker

   return S_OK;
}

HRESULT CBrokerImp2::LoadOldFormat(IStructuredLoad* pStrLoad)
{
   Agents::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      HRESULT hr = S_OK;
      IAgentEx* pAgent = (*i).second;
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

///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2012  Washington State Department of Transportation
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
#if defined _DEBUG
   WATCHX(IFC,0,"Clearing Agents");
   Agents::iterator i;
   for ( i = m_ExtensionAgents.begin(); i != m_ExtensionAgents.end(); i++ )
   {
      CComPtr<IAgentEx> pAgent = (*i).second;

      USES_CONVERSION;
      OLECHAR szGUID[39];
      CLSID clsid;
      pAgent->GetClassID(&clsid);
      ::StringFromGUID2(clsid,szGUID,39);

      ListConnectionPointLeaks(pAgent);
   }

   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      CComPtr<IAgentEx> pAgent = (*i).second;

      USES_CONVERSION;
      OLECHAR szGUID[39];
      CLSID clsid;
      pAgent->GetClassID(&clsid);
      ::StringFromGUID2(clsid,szGUID,39);

      ListConnectionPointLeaks(pAgent);
   }
#endif

   m_ExtensionAgents.clear();
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
   ATLASSERT( m_bAgentsInitialized == true ); // agents have to be initialized

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
   WATCHX(IFC,0,"Broker Reset");

   if ( !m_bAgentsInitialized )
      return S_OK; // do nothing if the agents weren't initialized

   Agents::iterator i;
   for ( i = m_ExtensionAgents.begin(); i != m_ExtensionAgents.end(); i++ )
   {
      IAgentEx* pAgent = (*i).second;
      pAgent->Reset();
   }

   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      IAgentEx* pAgent = (*i).second;
      pAgent->Reset();
   }


   m_bAgentsInitialized = false;

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

   Reset();

   m_bAgentsInitialized = true;

   Agents::iterator i;
   for ( i = m_ExtensionAgents.begin(); i != m_ExtensionAgents.end(); i++ )
   {
      IAgent* pAgent = (*i).second;
      pAgent->ShutDown();
   }

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
      WATCHX(IFC,0,"IID = " << OLE2T(szGUID) << " Usage Count = " << (*item.pUsageCount));

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
      WATCHX(IFC,0,"CLSID = " << OLE2T(szCLSID) << " IID = " << OLE2T(szGUID) << " Usage Count = " << (*item.pUsageCount) << " Agent Ref Count = " << cRef);

      count += (*item.pUsageCount);
   }
   WATCHX(IFC,0,"Total count = " << count);
#endif // _DEBUG

   ClearAgents();

   m_bAgentsInitialized = false;

   return S_OK;
}

//////////////////////////////////////////////////////
// IBrokerInitEx2/3
STDMETHODIMP CBrokerImp2::LoadExtensionAgents( CLSID * clsid, long nClsid,IIndexArray** plErrIndex )
{
   return LoadAgents(clsid,nClsid,plErrIndex,m_ExtensionAgents);
}

STDMETHODIMP CBrokerImp2::LoadAgents( CLSID * clsid, long nClsid,IIndexArray** plErrIndex )
{
   return LoadAgents(clsid,nClsid,plErrIndex,m_Agents);
}

HRESULT CBrokerImp2::LoadAgents( CLSID * clsid, long nClsid,IIndexArray** plErrIndex, Agents& agents )
{
   CHECK_RETOBJ(plErrIndex);

   CComPtr<IIndexArray> arr;
   arr.CoCreateInstance(CLSID_IndexArray);
   (*plErrIndex) = arr;
   (*plErrIndex)->AddRef();

   HRESULT hr;

   // Load all the agents, wire them up with the broker, and tell them
   // to register their interfaces
   for ( long i = 0; i < nClsid; i++ )
   {
      CComPtr<IAgentEx> pAgent;
      hr = ::CoCreateInstance( clsid[i], NULL, CLSCTX_INPROC_SERVER, IID_IAgentEx, (void**)&pAgent );
      if ( SUCCEEDED( hr ) )
      {
         agents.insert( std::make_pair(clsid[i],pAgent) );
         if ( FAILED(pAgent->SetBroker(this)) || FAILED(pAgent->RegInterfaces()) )
         {
            if ( *plErrIndex )
               (*plErrIndex)->Add(i);
         }
      }
      else
      {
         if ( *plErrIndex )
            (*plErrIndex)->Add(i);
      }
   }

   // All agents are now available... Give each agent an opportunity to initialize
   // itself.  This might consist of attaching to a connection point of another agent
   // (Hence the need to wait until all agents are available).
   if ( !m_DelayInit )
   {
      long count = 0;
      Agents::iterator iter;
      for ( iter = agents.begin(); iter != agents.end(); iter++ )
      {
         CComPtr<IAgentEx> pAgent = (*iter).second;
         if ( FAILED(pAgent->Init()) )
         {
            if ( *plErrIndex )
               (*plErrIndex)->Add( count );
         }
         count++;
      }
   }

   CollectionIndexType nErrors;
   (*plErrIndex)->get_Count(&nErrors);
   if ( 0 < nErrors )
   {
      return BROKER_E_LOADAGENT;
   }

	return S_OK;
}

STDMETHODIMP CBrokerImp2::AddExtensionAgent(IAgentEx* pAgent)
{
   return AddAgent(pAgent,m_ExtensionAgents);
}

STDMETHODIMP CBrokerImp2::AddAgent(IAgentEx* pAgent)
{
   return AddAgent(pAgent,m_Agents);
}

HRESULT CBrokerImp2::AddAgent(IAgentEx* pAgent,Agents& agents)
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

   agents.insert( std::make_pair(clsid,pAgent) );

   return S_OK;
}

STDMETHODIMP CBrokerImp2::FindConnectionPoint( REFIID riid, IConnectionPoint** ppCP)
{
   HRESULT hr = FindConnectionPoint( riid, m_Agents.begin(), m_Agents.end(), ppCP );
   if ( SUCCEEDED(hr) )
      return hr;

   hr = FindConnectionPoint( riid, m_ExtensionAgents.begin(), m_ExtensionAgents.end(), ppCP );

   return hr;
}

HRESULT CBrokerImp2::FindConnectionPoint( REFIID riid, Agents::iterator begin,Agents::iterator end,IConnectionPoint** ppCP)
{
   IConnectionPointContainer* pCPC;
   HRESULT hr = E_NOINTERFACE;
   while ( begin != end )
   {
      IAgentEx* pAgent = (*begin).second;

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

      begin++;
   }

   return hr;
}


STDMETHODIMP CBrokerImp2::RegInterface( REFIID riid, IAgentEx* pAgent)
{
   InterfaceItem item;
   item.iid = riid;
   item.pAgent = pAgent;
   (*item.pUsageCount) = 0;
   std::pair<std::set<InterfaceItem>::iterator,bool> result = m_Interfaces.insert( item );
   ASSERT(result.second); // if this fires, the interface was already registered by a different agent
   if ( result.second == false )
      return E_FAIL;

   return S_OK;
}

STDMETHODIMP CBrokerImp2::DelayInit()
{
   m_DelayInit = true;
   return S_OK;
}

STDMETHODIMP CBrokerImp2::InitAgents()
{
   HRESULT hr = InitAgents(m_Agents.begin(),m_Agents.end());
   if ( FAILED(hr) )
      return hr;

   m_bAgentsInitialized = false;

   return InitAgents(m_ExtensionAgents.begin(),m_ExtensionAgents.end());
}

HRESULT CBrokerImp2::InitAgents(Agents::iterator begin,Agents::iterator end)
{
   ATLASSERT(m_bAgentsInitialized == false); // should not be initializing agents more than once
   if ( m_bAgentsInitialized )
      return S_OK;

   std::vector<IAgentEx*> secondPassAgents;

   m_bAgentsInitialized = true;

   while ( begin != end )
   {
      IAgentEx* pAgent = (*begin).second;
      HRESULT hr = pAgent->Init();
      if ( FAILED(hr) )
         return BROKER_E_INITAGENT;

      if ( hr == AGENT_S_SECONDPASSINIT )
      {
         IAgentEx* pAgentEx;
         hr = pAgent->QueryInterface( IID_IAgentEx, (void**)&pAgentEx );
         if ( SUCCEEDED(hr) && pAgentEx )
            secondPassAgents.push_back(pAgentEx);
      }

      begin++;
   }

   std::vector<IAgentEx*>::iterator j;
   for ( j = secondPassAgents.begin(); j != secondPassAgents.end(); j++ )
   {
      IAgentEx* pAgent = *j;
      HRESULT hr = pAgent->Init2();
      pAgent->Release(); // release the AddRef call from QueryInterace above
      if ( FAILED(hr) )
         return BROKER_E_INITAGENT;
   }

   return S_OK;
}

STDMETHODIMP CBrokerImp2::IntegrateWithUI(BOOL bIntegrate)
{
   if ( bIntegrate )
   {
      // when integrating, do the main agents first, then the extensions
      IntegrateWithUI(true,m_Agents.begin(),m_Agents.end());
      IntegrateWithUI(true,m_ExtensionAgents.begin(),m_ExtensionAgents.end());
   }
   else
   {
      // when removing, let the extensions go first
      IntegrateWithUI(false,m_ExtensionAgents.begin(),m_ExtensionAgents.end());
      IntegrateWithUI(false,m_Agents.begin(),m_Agents.end());
   }

   return S_OK;
}

HRESULT CBrokerImp2::IntegrateWithUI(BOOL bIntegrate,Agents::iterator begin,Agents::iterator end)
{
   while ( begin != end )
   {
      IAgentEx* pAgent = (*begin).second;
      CComQIPtr<IAgentUIIntegration> pUI(pAgent);
      if ( pUI )
      {
         pUI->IntegrateWithUI(bIntegrate);
      }

      begin++;
   }

   return S_OK;
}

////////////////////////////////////////////////////////
// IBrokerPersist

STDMETHODIMP CBrokerImp2::Load(IStructuredLoad* pStrLoad)
{
   USES_CONVERSION;

   HRESULT hr = pStrLoad->BeginUnit(_T("Broker"));
   if ( FAILED(hr) )
   {
      // the data isn't saved in the current format
      // it was probably created using CBrokerImp
      return LoadOldFormat(pStrLoad); 
   }

   // until we run out of "Agent"units
   while ( SUCCEEDED(pStrLoad->BeginUnit(_T("Agent"))) )
   {
      // get CLSID of the agent
      CComVariant varCLSID;
      varCLSID.vt = VT_BSTR;
      HRESULT hr = pStrLoad->get_Property(_T("CLSID"), &varCLSID);
      if ( FAILED(hr) )
         return hr;

      CLSID clsid;
      hr = ::CLSIDFromString(CComBSTR(varCLSID.bstrVal), &clsid);
      if ( FAILED(hr) )
         return hr;

      // get the agent
      IAgentEx* pAgent;
      if ( SUCCEEDED( FindAgent(clsid,&pAgent) ) )
      {
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
         CComBSTR bstrRawUnit;
         hr = pStrLoad->LoadRawUnit(&bstrRawUnit);
         if ( FAILED(hr) )
            return hr;

         m_MissingAgentData.push_back(OLE2T(bstrRawUnit));
      }

      pStrLoad->EndUnit(); // end of "Agent" unit
   };

   pStrLoad->EndUnit(); // Broker

   return S_OK;
}

STDMETHODIMP CBrokerImp2::Save(IStructuredSave* pStrSave)
{
   pStrSave->BeginUnit(_T("Broker"),1.0);

   HRESULT hr = SaveAgentData(pStrSave,m_Agents.begin(),m_Agents.end());
   if ( FAILED(hr) )
      return hr;

   hr = SaveAgentData(pStrSave,m_ExtensionAgents.begin(),m_ExtensionAgents.end());
   if ( FAILED(hr) )
      return hr;

   if ( m_bSaveMissingAgentData == VARIANT_TRUE )
   {
      std::vector<std::_tstring>::iterator iter2;
      for ( iter2 = m_MissingAgentData.begin(); iter2 != m_MissingAgentData.end(); iter2++ )
      {
         pStrSave->SaveRawUnit(iter2->c_str());
      }
   }

   pStrSave->EndUnit(); // Broker

   return S_OK;
}

HRESULT CBrokerImp2::SaveAgentData(IStructuredSave* pStrSave,Agents::iterator begin,Agents::iterator end)
{
   while ( begin != end )
   {
      HRESULT hr = S_OK;
      IAgentEx* pAgent = (*begin).second;
      IAgentPersist* pPersist;
      hr = pAgent->QueryInterface( IID_IAgentPersist, (void**)&pPersist );
      if ( SUCCEEDED(hr) )
      {
         // create a unit around each agent's data
         pStrSave->BeginUnit(_T("Agent"),1.0);

         LPOLESTR postr = 0;
         hr = StringFromCLSID((*begin).first, &postr);

         // capture the class id of the agent
         pStrSave->put_Property(_T("CLSID"),CComVariant(postr));

         CoTaskMemFree(postr);

         hr = pPersist->Save( pStrSave ); // agent to save its own data
         pPersist->Release();
         if ( FAILED(hr) )
            return hr;

         pStrSave->EndUnit(); // end of "Agent" unit
      }

      begin++;
   }

   return S_OK;
}

STDMETHODIMP CBrokerImp2::SetSaveMissingAgentDataFlag(VARIANT_BOOL bSetFlag)
{
   m_bSaveMissingAgentData = bSetFlag;
   return S_OK;
}

STDMETHODIMP CBrokerImp2::GetSaveMissingAgentDataFlag(VARIANT_BOOL* bFlag)
{
   CHECK_RETVAL(bFlag);
   *bFlag = m_bSaveMissingAgentData;
   return S_OK;
}

STDMETHODIMP CBrokerImp2::get_AgentCount(CollectionIndexType* nAgents)
{
   CHECK_RETVAL(nAgents);
   *nAgents = m_Agents.size();
   return S_OK;
}

STDMETHODIMP CBrokerImp2::get_Agent(CollectionIndexType idx,IAgent** ppAgent)
{
   CHECK_RETOBJ(ppAgent);

   Agents::iterator iter;
   CollectionIndexType i = 0;
   for ( iter = m_Agents.begin(); iter != m_Agents.end() && i != idx; iter++, i++ )
   {   }

   (*ppAgent) = iter->second;
   (*ppAgent)->AddRef();

   return S_OK;
}

STDMETHODIMP CBrokerImp2::get_ExtensionAgentCount(CollectionIndexType* nAgents)
{
   CHECK_RETVAL(nAgents);
   *nAgents = m_ExtensionAgents.size();
   return S_OK;
}

STDMETHODIMP CBrokerImp2::get_ExtensionAgent(CollectionIndexType idx,IAgent** ppAgent)
{
   CHECK_RETOBJ(ppAgent);

   Agents::iterator iter;
   CollectionIndexType i = 0;
   for ( iter = m_ExtensionAgents.begin(); iter != m_ExtensionAgents.end() && i != idx; iter++, i++ )
   {   }

   (*ppAgent) = iter->second;
   (*ppAgent)->AddRef();

   return S_OK;
}

HRESULT CBrokerImp2::LoadOldFormat(IStructuredLoad* pStrLoad)
{
   Agents::iterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      HRESULT hr = S_OK;
      CComPtr<IAgentEx> pAgent = (*i).second;
      CComQIPtr<IAgentPersist> pPersist(pAgent);
      if ( pPersist )
      {
         hr = pPersist->Load( pStrLoad );
         if ( FAILED(hr) )
            return hr;


         // The when we had the old format there was only one agent
         // that persisted data. New, extension agents also implement the
         // IAgentPersist interface and will get called if they are loaded.
         // Since this is an old format file, there is no way they will
         // have data in the file....
         //
         // Load from the first agent supporting IAgentPersist and break out of the loop
         break;
      }
   }

   return S_OK;
}

HRESULT CBrokerImp2::FindAgent(const CLSID& clsid,IAgentEx** ppAgent)
{
   Agents::iterator found = m_Agents.find(clsid);
   if ( found != m_Agents.end() )
   {
      (*ppAgent) = (*found).second;
      return S_OK;
   }

   found = m_ExtensionAgents.find(clsid);
   if ( found != m_ExtensionAgents.end() )
   {
      (*ppAgent) = (*found).second;
      return S_OK;
   }

   return E_FAIL;
}

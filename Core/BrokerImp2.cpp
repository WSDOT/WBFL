///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2015  Washington State Department of Transportation
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

DIAG_DEFINE_GROUP(IFC,DIAG_GROUP_ENABLE,0);

#if defined _DEBUG
bool CompareCLSID(InterfaceItem& item1,InterfaceItem& item2)
{
   CLSID clsid1, clsid2;
   item1.pAgent->GetClassID(&clsid1);
   item2.pAgent->GetClassID(&clsid2);
   return clsid1 < clsid2;
}
#endif

InterfaceItem::InterfaceItem() : 
pUsageCount(new Uint64) 
{ 
   *pUsageCount = 0; 
}

bool InterfaceItem::operator<(const InterfaceItem& other) const 
{ 
   return iid < other.iid; 
}

bool InterfaceItem::operator==(const InterfaceItem& other) const 
{ 
   return (iid == other.iid ? true : false); 
}


/////////////////////////////////////////////////////////////////////////////
// CBrokerImp2
CBrokerImp2::CBrokerImp2() :
   m_MostFrequentlyUsed(10) // 10 most recently used interfaces
{
   m_DelayInit = false;
   m_bAgentsInitialized = false;
   m_bSaveMissingAgentData = VARIANT_TRUE;
   m_bIntegrateWithUI = FALSE;
   m_bIntegrateWithReporting = FALSE;
   m_bIntegrateWithGraphing = FALSE;
}

CBrokerImp2::~CBrokerImp2()
{
}

HRESULT CBrokerImp2::FinalConstruct()
{
   return S_OK;
}

void CBrokerImp2::FinalRelease()
{
}

#if defined _DEBUG
void CBrokerImp2::ListInterfaceUsage()
{
   USES_CONVERSION;
   WATCHX(IFC,0,_T("Most frequently used interfaces"));
   boost::circular_buffer<InterfaceItem>::iterator mfuIter(m_MostFrequentlyUsed.begin());
   boost::circular_buffer<InterfaceItem>::iterator mfuIterEnd(m_MostFrequentlyUsed.end());
   for ( ; mfuIter != mfuIterEnd; mfuIter++ )
   {
      InterfaceItem& item = *mfuIter;

      OLECHAR szGUID[39];
      ::StringFromGUID2(item.iid,szGUID,39);
      WATCHX(IFC,0,_T("IID = ") << OLE2T(szGUID) << _T(" Usage Count = ") << (*item.pUsageCount));

   }

   WATCHX(IFC,0,_T(""));
   WATCHX(IFC,0,_T("Total interface usage count"));

   // fill up a temporary vector so we can sort and report by CLSID
   std::vector<InterfaceItem> interfaces;
   Interfaces::iterator ifaceIter(m_Interfaces.begin());
   Interfaces::iterator ifaceIterEnd(m_Interfaces.end());
   for ( ; ifaceIter != ifaceIterEnd; ifaceIter++ )
   {
      InterfaceItem& item = *ifaceIter;
      interfaces.push_back(item);
   }

   std::sort(interfaces.begin(),interfaces.end(),CompareCLSID);

   IndexType count = 0;
   std::vector<InterfaceItem>::iterator ifaceItemIter(interfaces.begin());
   std::vector<InterfaceItem>::iterator ifaceItemIterEnd(interfaces.end());
   for ( ; ifaceItemIter != ifaceItemIterEnd; ifaceItemIter++ )
   {
      InterfaceItem& item = *ifaceItemIter;

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
      WATCHX(IFC,0,_T("CLSID = ") << OLE2T(szCLSID) << _T(" IID = ") << OLE2T(szGUID) << _T(" Usage Count = ") << (*item.pUsageCount) << _T(" Agent Ref Count = ") << cRef);

      count += (*item.pUsageCount);
   }
   WATCHX(IFC,0,_T("Total count = ") << count);
}

void CBrokerImp2::ListConnectionPointLeaks(IAgentEx* pAgent)
{
   Uint32 leakCount = 0;
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
            WATCHX(IFC,0,_T("Leaked connection point cookie ") << cdata.dwCookie);
            cdata.pUnk->Release(); // documtation says caller must call Release
            leakCount++;
         }

         pCP.Release();
      }
   }

   ATLASSERT(leakCount == 0); // if this fires, there are connection point leaks
}

void CBrokerImp2::ListConnectionPointLeaks()
{
   WATCHX(IFC,0,_T("Clearing Agents"));
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

      pAgent.p->AddRef();
      ULONG refCount = pAgent.p->Release();
      // ref count should be 2 (one for the container, and one for the pAgent pointer)
      if ( refCount != 2 )
      {
         WATCHX(IFC,0,_T("Extension Agent ") << szGUID << _T(" Ref Count ") << refCount);
      }
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

      pAgent.p->AddRef();
      ULONG refCount = pAgent.p->Release();
      // ref count should be 2 (one for the container, and one for the pAgent pointer)
      if ( refCount != 2 )
      {
         WATCHX(IFC,0,_T("Agent ") << szGUID << _T(" Ref Count ") << refCount);
      }
   }
}
#endif // _DEBUG

void CBrokerImp2::ClearAgents()
{
#if defined _DEBUG
   ListConnectionPointLeaks();
#endif

   m_ExtensionAgents.clear();
   m_Agents.clear();
}

/////////////////////////////////////////////////////////////////////////////
// IBroker

// returns whether item1 has a greater usage count than item 2
bool SortByUsageFrequency(const InterfaceItem& item1,const InterfaceItem& item2)
{
   return *(item2.pUsageCount) < *(item1.pUsageCount);
}

STDMETHODIMP CBrokerImp2::GetInterface( REFIID riid, IUnknown** ppUnk)
{
   ATLASSERT( m_bAgentsInitialized == true ); // agents have to be initialized

   // first check the most frequently used list
   InterfaceItem key;
   key.iid = riid;
   boost::circular_buffer<InterfaceItem>::iterator found( std::find(m_MostFrequentlyUsed.begin(),m_MostFrequentlyUsed.end(),key) );
   if ( found != m_MostFrequentlyUsed.end() )
   {
      InterfaceItem& item = *found;
      ATLASSERT( riid == item.iid );

      ATLASSERT( item.m_pUnk != NULL);
      HRESULT hr = item.m_pUnk.CopyTo(ppUnk);
      if ( FAILED(hr) )
      {
         ATLASSERT(false);
         return hr;
      }

      // this IID is on the frequently used list
      // increment the usage count (updates in the main list of all interfaces as well)
      (*item.pUsageCount)++;

      // sort the MFU list based on usage count
      std::sort( m_MostFrequentlyUsed.begin(),m_MostFrequentlyUsed.end(), SortByUsageFrequency );

      return hr;
   }

   // IID is not in the most frequently used list... search for it in the regular list of interfaces
   Interfaces::iterator interface_found( m_Interfaces.find( key ) );
   if ( interface_found == m_Interfaces.end() )
   {
      // the interface wasn't found
      return E_NOINTERFACE;
   }

   InterfaceItem& item = *interface_found;
   HRESULT hr = S_OK;
   if ( item.m_pUnk == NULL )
   {
      // this is the first time the interface has been requested
      ATLASSERT(*(item.pUsageCount) == 0);

      IAgentEx* pAgent = item.pAgent;
      hr = pAgent->QueryInterface( riid, (void**)&item.m_pUnk );
      ATLASSERT(SUCCEEDED(hr));
   }

   hr = item.m_pUnk.CopyTo(ppUnk);

   if ( SUCCEEDED(hr) )
   {
      // update the usage count
      (*item.pUsageCount)++;

      // See if the usage count is high enough to be in the most frequently used list
      if ( m_MostFrequentlyUsed.empty() )
      {
         m_MostFrequentlyUsed.push_front(item);
      }
      else
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
   }

   return hr;
}

STDMETHODIMP CBrokerImp2::Reset()
{
   WATCHX(IFC,0,_T("Broker Reset"));

   if ( !m_bAgentsInitialized )
      return S_OK; // do nothing if the agents weren't initialized

   Agents::iterator extensionAgentIter(m_ExtensionAgents.begin());
   Agents::iterator extensionAgentIterEnd(m_ExtensionAgents.end());
   for ( ; extensionAgentIter != extensionAgentIterEnd; extensionAgentIter++ )
   {
      IAgentEx* pAgent = (*extensionAgentIter).second;
      pAgent->Reset();
   }

   Agents::iterator agentIter(m_Agents.begin());
   Agents::iterator agentIterEnd(m_Agents.end());
   for ( ; agentIter != agentIterEnd; agentIter++ )
   {
      IAgentEx* pAgent = (*agentIter).second;
      pAgent->Reset();
   }


   m_bAgentsInitialized = false;

   return S_OK;
}

STDMETHODIMP CBrokerImp2::ShutDown()
{
   WATCHX(IFC,0,_T("Broker ShutDown"));

   Reset();

#if defined _DEBUG
   ListInterfaceUsage();
#endif // _DEBUG

   m_Interfaces.clear();
   m_MostFrequentlyUsed.clear();

   m_bAgentsInitialized = true;

   Agents::iterator extensionAgentIter(m_ExtensionAgents.begin());
   Agents::iterator extensionAgentIterEnd(m_ExtensionAgents.end());
   for ( ; extensionAgentIter != extensionAgentIterEnd; extensionAgentIter++ )
   {
      IAgentEx* pAgent = (*extensionAgentIter).second;
      pAgent->ShutDown();
   }

   Agents::iterator agentIter(m_Agents.begin());
   Agents::iterator agentIterEnd(m_Agents.end());
   for ( ; agentIter != agentIterEnd; agentIter++ )
   {
      IAgentEx* pAgent = (*agentIter).second;
      pAgent->ShutDown();
   }

   ClearAgents();

   m_bAgentsInitialized = false;

   return S_OK;
}

//////////////////////////////////////////////////////
// IBrokerInitEx2/3
STDMETHODIMP CBrokerImp2::LoadExtensionAgents( CLSID * clsid, IndexType nClsid,IIndexArray** plErrIndex )
{
   return LoadAgents(clsid,nClsid,plErrIndex,m_ExtensionAgents);
}

STDMETHODIMP CBrokerImp2::LoadAgents( CLSID * clsid, IndexType nClsid,IIndexArray** plErrIndex )
{
   return LoadAgents(clsid,nClsid,plErrIndex,m_Agents);
}

HRESULT CBrokerImp2::LoadAgents( CLSID * clsid, IndexType nClsid,IIndexArray** plErrIndex, Agents& agents )
{
   CHECK_RETOBJ(plErrIndex);

   CComPtr<IIndexArray> arr;
   arr.CoCreateInstance(CLSID_IndexArray);
   (*plErrIndex) = arr;
   (*plErrIndex)->AddRef();

   HRESULT hr;

   // Load all the agents, wire them up with the broker, and tell them
   // to register their interfaces
   for ( IndexType i = 0; i < nClsid; i++ )
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
      IndexType count = 0;
      Agents::iterator iter(agents.begin());
      Agents::iterator iterEnd(agents.end());
      for ( ; iter != iterEnd; iter++ )
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
   std::pair<std::set<InterfaceItem>::iterator,bool> result( m_Interfaces.insert( item ) );
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

   std::vector<IAgentEx*>::iterator j(secondPassAgents.begin());
   std::vector<IAgentEx*>::iterator j_end(secondPassAgents.end());
   for ( ; j != j_end; j++ )
   {
      IAgentEx* pAgent = *j;
      HRESULT hr = pAgent->Init2();
      pAgent->Release(); // release the AddRef call from QueryInterace above
      if ( FAILED(hr) )
         return BROKER_E_INITAGENT;
   }

   return S_OK;
}

STDMETHODIMP CBrokerImp2::Integrate(BOOL bIntegrateWithUI,BOOL bIntegrateWithReporting,BOOL bIntegrateWithGraphing)
{
   m_bIntegrateWithUI        = bIntegrateWithUI;
   m_bIntegrateWithReporting = bIntegrateWithReporting;
   m_bIntegrateWithGraphing  = bIntegrateWithGraphing;

   Integrate(TRUE,m_Agents.begin(),m_Agents.end());
   Integrate(TRUE,m_ExtensionAgents.begin(),m_ExtensionAgents.end());

   return S_OK;
}

STDMETHODIMP CBrokerImp2::RemoveIntegration()
{
   Integrate(FALSE,m_ExtensionAgents.begin(),m_ExtensionAgents.end());
   Integrate(FALSE,m_Agents.begin(),m_Agents.end());
   return S_OK;
}

HRESULT CBrokerImp2::Integrate(BOOL bIntegrating,Agents::iterator begin,Agents::iterator end)
{
   while ( begin != end )
   {
      IAgentEx* pAgent = (*begin).second;
      if ( m_bIntegrateWithUI )
      {
         CComQIPtr<IAgentUIIntegration> pUI(pAgent);
         if ( pUI )
         {
            pUI->IntegrateWithUI(bIntegrating);
         }
      }

      if ( m_bIntegrateWithReporting )
      {
         CComQIPtr<IAgentReportingIntegration> pUI(pAgent);
         if ( pUI )
         {
            pUI->IntegrateWithReporting(bIntegrating);
         }
      }

      if ( m_bIntegrateWithGraphing )
      {
         CComQIPtr<IAgentGraphingIntegration> pUI(pAgent);
         if ( pUI )
         {
            pUI->IntegrateWithGraphing(bIntegrating);
         }
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

   // until we run out of "Agent" units
   while ( SUCCEEDED(pStrLoad->BeginUnit(_T("Agent"))) )
   {
      // get CLSID of the agent
      CComVariant varCLSID;
      varCLSID.vt = VT_BSTR;
      HRESULT hr = pStrLoad->get_Property(_T("CLSID"), &varCLSID);
      if ( FAILED(hr) )
         return hr;

      CComBSTR bstrCLSID(varCLSID.bstrVal);
      bstrCLSID.ToUpper();
      bstrCLSID = TranslateCLSID(bstrCLSID);

      CLSID clsid;
      hr = ::CLSIDFromString(bstrCLSID, &clsid);
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
      std::vector<std::_tstring>::iterator iter2(m_MissingAgentData.begin());
      std::vector<std::_tstring>::iterator iter2End(m_MissingAgentData.end());
      for ( ; iter2 != iter2End; iter2++ )
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

STDMETHODIMP CBrokerImp2::AddCLSID(BSTR bstrOldCLSID,BSTR bstrNewCLSID)
{
   m_CLSIDMap.insert(std::make_pair(CComBSTR(bstrOldCLSID),CComBSTR(bstrNewCLSID)));
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

   CollectionIndexType i = 0;
   Agents::iterator iter(m_Agents.begin());
   Agents::iterator iterEnd(m_Agents.end());
   for ( ; iter != iterEnd && i != idx; iter++, i++ )
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

   CollectionIndexType i = 0;
   Agents::iterator iter(m_ExtensionAgents.begin());
   Agents::iterator iterEnd(m_ExtensionAgents.end());
   for ( ; iter != iterEnd && i != idx; iter++, i++ )
   {   }

   (*ppAgent) = iter->second;
   (*ppAgent)->AddRef();

   return S_OK;
}

HRESULT CBrokerImp2::LoadOldFormat(IStructuredLoad* pStrLoad)
{
   Agents::iterator i(m_Agents.begin());
   Agents::iterator i_end(m_Agents.end());
   for ( ; i != i_end; i++ )
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
   Agents::iterator found( m_Agents.find(clsid) );
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

CComBSTR CBrokerImp2::TranslateCLSID(const CComBSTR bstrCLSID)
{
   std::map<CComBSTR,CComBSTR>::iterator found(m_CLSIDMap.find(bstrCLSID));
   if ( found == m_CLSIDMap.end() )
      return bstrCLSID;

   return found->second;
}

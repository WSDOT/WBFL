///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
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

#if !defined(AFX_BROKERIMP2_H__99C34AA3_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_)
#define AFX_BROKERIMP2_H__99C34AA3_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BrokerImp2.h : header file
//

#include <WBFLAtlExt.h>

#include <set>
#include <map>

#include <boost\circular_buffer.hpp>

struct InterfaceItem
{
   IID iid; // IID of the interface
   CComPtr<IUnknown> m_pUnk; // the interface pointer
   std::shared_ptr<IndexType> pUsageCount; // count of the number of times the interface has been requested
   IAgentEx* pAgent; // weak reference.. agent that implements the interface

   InterfaceItem();
   bool operator<(const InterfaceItem& other) const;
   bool operator==(const InterfaceItem& other) const;
};

/////////////////////////////////////////////////////////////////////////////
// CBrokerImp2 command target
class ATL_NO_VTABLE CBrokerImp2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CBrokerImp2,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CBrokerImp2, &CLSID_Broker2>,
   public IBroker,
   public IBrokerInitEx3,
   public IBrokerPersist2,
   public ICLSIDMap,
   public IManageAgents
{
public:
   CBrokerImp2();
   ~CBrokerImp2();

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_BROKER2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBrokerImp2)
	COM_INTERFACE_ENTRY(IBroker)
	COM_INTERFACE_ENTRY(IBrokerInitEx)
	COM_INTERFACE_ENTRY(IBrokerInitEx2)
	COM_INTERFACE_ENTRY(IBrokerInitEx3)
	COM_INTERFACE_ENTRY(IBrokerPersist)
	COM_INTERFACE_ENTRY(IBrokerPersist2)
   COM_INTERFACE_ENTRY(ICLSIDMap)
   COM_INTERFACE_ENTRY(IManageAgents)
END_COM_MAP()

// IBroker
public:
   STDMETHOD(GetInterface)(/*[in]*/ REFIID riid, /*[out,iid_is(riid)]*/ IUnknown** ppUnk) override;
   STDMETHOD(Reset)() override;
	STDMETHOD(ShutDown)() override;

// IBrokerInitEx3
public:
   STDMETHOD(LoadAgents)(/*[in]*/ CLSID* pClsid, /*[in]*/ IndexType nClsid,/*[out]*/ IIndexArray** lErrIndex) override;
   STDMETHOD(LoadExtensionAgents)(/*[in]*/ CLSID * clsid,/*[in]*/  IndexType nClsid,/*[out]*/ IIndexArray** plErrIndex ) override;
   STDMETHOD(AddAgent)(/*[in]*/ IAgentEx* pAgent) override;
   STDMETHOD(AddExtensionAgent)(/*[in]*/ IAgentEx* pAgent) override;
	STDMETHOD(FindConnectionPoint)(/*[in]*/ REFIID riid,/*[out]*/ IConnectionPoint** ppCP) override;
	STDMETHOD(RegInterface)(/*[in]*/ REFIID riid,/*[in]*/ IAgentEx* pAgent) override;
   STDMETHOD(DelayInit)() override;
	STDMETHOD(InitAgents)() override;
   STDMETHOD(Integrate)(BOOL bIntegrateWithUI,BOOL bIntegrateWithReporting,BOOL bIntegrateWithGraphing,BOOL bIntegrateWithDocumentation) override;
   STDMETHOD(RemoveIntegration)() override;

// IBrokerPersist2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad* pStrLoad) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave* pStrSave) override;
   STDMETHOD(SetSaveMissingAgentDataFlag)(/*[in]*/VARIANT_BOOL bSetFlag) override;
   STDMETHOD(GetSaveMissingAgentDataFlag)(/*[out]*/VARIANT_BOOL* bFlag) override;

// ICLSIDMap
public:
   STDMETHOD(AddCLSID)(BSTR bstrOldCLSID,BSTR bstrNewCLSID) override;

// IManageAgents
public:
   STDMETHOD(get_AgentCount)(/*[out,retval]*/IndexType* nAgents) override;
   STDMETHOD(get_Agent)(/*[in]*/IndexType idx,/*[out,retval]*/IAgent** ppAgent) override;
   STDMETHOD(get_ExtensionAgentCount)(/*[out,retval]*/IndexType* nAgents) override;
   STDMETHOD(get_ExtensionAgent)(/*[in]*/IndexType idx,/*[out,retval]*/IAgent** ppAgent) override;

private:
   using Interfaces = std::set<InterfaceItem>;
   Interfaces m_Interfaces; // collection of all interface records
   boost::circular_buffer<InterfaceItem> m_MostFrequentlyUsed; // collection of most frequently used interfaces
                                             // this collection will be searched first

   std::map<CComBSTR,CComBSTR> m_CLSIDMap;

   class Key : public std::pair<IndexType, CLSID>
   {
   public:
      Key(IndexType idx, CLSID clsid) : std::pair<IndexType,CLSID>(idx, clsid) {}
      bool operator<(const Key& key) 
      {
         if (first == key.first)
            return second < key.second;
         else if (first < key.first)
            return true;
         else
            return false;
      }
   };

   using Agents = std::map<Key,CComPtr<IAgentEx>>; // interface pointers are referenced counted
   Agents m_Agents;
   Agents m_ExtensionAgents;

   bool m_DelayInit;
   bool m_bAgentsInitialized; // true if the agents where initialized

   VARIANT_BOOL m_bSaveMissingAgentData;
   std::vector<std::_tstring> m_MissingAgentData; // holds the entire unit data block
                                                // for agent data that is in the file, but
                                                // the agent can't be created

   // loads agents using the file format for Class Broker
   HRESULT LoadOldFormat(IStructuredLoad* strLoad);
   void ClearAgents();

   HRESULT LoadAgents( CLSID * clsid, IndexType nClsid,IIndexArray** plErrIndex, Agents& agents );
   HRESULT AddAgent(IAgentEx* pAgent,Agents& agents);
   HRESULT FindConnectionPoint( REFIID riid, Agents::iterator begin,Agents::iterator end,IConnectionPoint** ppCP);
   HRESULT InitAgents(Agents::iterator begin,Agents::iterator end);
   HRESULT SaveAgentData(IStructuredSave* pStrSave,Agents::iterator begin,Agents::iterator end);
   HRESULT FindAgent(const CLSID& clsid,IAgentEx** ppAgent);

   BOOL m_bIntegrateWithUI;
   BOOL m_bIntegrateWithReporting;
   BOOL m_bIntegrateWithGraphing;

   CComBSTR TranslateCLSID(const CComBSTR bstrCLSID);


#if defined _DEBUG
   void ListInterfaceUsage();
   void ListConnectionPointLeaks();
   void ListConnectionPointLeaks(IAgentEx* pAgent);
#endif
};

OBJECT_ENTRY_AUTO(CLSID_Broker2,CBrokerImp2)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROKERIMP2_H__99C34AA3_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_)

///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2014  Washington State Department of Transportation
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

#if !defined(AFX_BROKERIMP_H__99C34AA3_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_)
#define AFX_BROKERIMP_H__99C34AA3_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BrokerImp.h : header file
//
#include <vector>
#include <map>


/////////////////////////////////////////////////////////////////////////////
// CBrokerImp command target
class ATL_NO_VTABLE CBrokerImp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBrokerImp, &CLSID_Broker>,
   public IBroker,
   public IBrokerInit2,
   public IBrokerPersist
{
public:
	CBrokerImp()
	{
      m_DelayInit = false;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_BROKER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBrokerImp)
	COM_INTERFACE_ENTRY(IBroker)
	COM_INTERFACE_ENTRY(IBrokerInit)
	COM_INTERFACE_ENTRY(IBrokerInit2)
	COM_INTERFACE_ENTRY(IBrokerPersist)
END_COM_MAP()


// IBroker
public:
   STDMETHOD(GetInterface)(/*[in]*/ REFIID riid, /*[out,iid_is(riid)]*/ void** ppv);
   STDMETHOD(Reset)();
	STDMETHOD(ShutDown)();

// IBrokerInit2
public:
   STDMETHOD(LoadAgents)(/*[in]*/ CLSID* pClsid, /*[in]*/ IndexType nClsid,/*[out]*/ IndexType* lErrIndex);
   STDMETHOD(AddAgent)(/*[in]*/ IAgent* pAgent);
	STDMETHOD(FindConnectionPoint)(/*[in]*/ REFIID riid,/*[out]*/ IConnectionPoint** ppCP);
	STDMETHOD(RegInterface)(/*[in]*/ REFIID riid,/*[in]*/ IAgent* pAgent);
   STDMETHOD(DelayInit)();
	STDMETHOD(InitAgents)();

// IBrokerPersist
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad* pStrLoad);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave* pStrSave);

private:
   typedef std::map<IID, IAgent* >Interfaces; // does not effect ref-counts
   Interfaces m_Interfaces;
   std::vector< IAgent* > m_Agents; // holds a ref count
   bool m_DelayInit;

   void ClearAgents();
};

OBJECT_ENTRY_AUTO(CLSID_Broker,CBrokerImp)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROKERIMP_H__99C34AA3_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_)

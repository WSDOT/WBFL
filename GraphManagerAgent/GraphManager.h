///////////////////////////////////////////////////////////////////////
// GraphManagerAgent - Provides Graph manager as an Agent
// Copyright © 1999-2022  Washington State Department of Transportation
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

// GraphManager.h : Declaration of the CGraphManager

#pragma once

#include "resource.h"       // main symbols
#include "IGraphManager.h"
#include <Graphing/GraphBuilder.h>

/////////////////////////////////////////////////////////////////////////////
// CGraphManager
class ATL_NO_VTABLE CGraphManagerAgent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGraphManagerAgent, &CLSID_GraphManagerAgent>,
   public IAgentEx,
	public IGraphManager
{
public:
	CGraphManagerAgent()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GRAPHMANAGER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGraphManagerAgent)
	COM_INTERFACE_ENTRY(IAgent)
	COM_INTERFACE_ENTRY(IAgentEx)
	COM_INTERFACE_ENTRY(IGraphManager)
END_COM_MAP()

private:
   WBFL::Graphing::GraphManager m_GraphManager;
   IBroker* m_pBroker; // weak reference

// IAgentEx
public:
   STDMETHOD(SetBroker)(/*[in]*/ IBroker* pBroker) override;
   STDMETHOD(RegInterfaces)() override;
	STDMETHOD(Init)() override;
	STDMETHOD(Init2)() override;
	STDMETHOD(Reset)() override;
	STDMETHOD(ShutDown)() override;
   STDMETHOD(GetClassID)(CLSID* pCLSID) override;


// IGraphManager
public:
   virtual void SortByName(bool bSort) override;
   virtual bool AddGraphBuilder(const WBFL::Graphing::GraphBuilder& graphBuilder) override;
   virtual bool AddGraphBuilder(std::unique_ptr<WBFL::Graphing::GraphBuilder>&& pGraphBuilder) override;
   virtual IndexType GetGraphBuilderCount() const override;
   virtual std::unique_ptr<WBFL::Graphing::GraphBuilder>& GetGraphBuilder(IndexType index) override;
   virtual std::unique_ptr<WBFL::Graphing::GraphBuilder>& GetGraphBuilder(LPCTSTR strGraphName) override;
   virtual std::unique_ptr<WBFL::Graphing::GraphBuilder>& GetGraphBuilder(const std::_tstring& strGraphName) override;
   virtual bool RemoveGraphBuilder(LPCTSTR strGraphName) override;
   virtual bool RemoveGraphBuilder(const std::_tstring& strGraphName) override;
   virtual std::vector<std::_tstring> GetGraphNames() const override;
   virtual const CBitmap* GetMenuBitmap(LPCTSTR strGraphName) override;
   virtual const CBitmap* GetMenuBitmap(const std::_tstring& strGraphName) override;
};


///////////////////////////////////////////////////////////////////////
// GraphManagerAgent - Provides graph manager as an Agent
// Copyright © 1999-2021  Washington State Department of Transportation
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

// GraphManager.cpp : Implementation of CGraphManager
#include "stdafx.h"
#include "WBFLGraphManagerAgent.h"
#include "GraphManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CGraphManagerAgent

//
// IAgentEx
//
STDMETHODIMP CGraphManagerAgent::SetBroker(IBroker* pBroker)
{
   m_pBroker = pBroker;
   return S_OK;
}

STDMETHODIMP CGraphManagerAgent::RegInterfaces()
{
   CComQIPtr<IBrokerInitEx2,&IID_IBrokerInitEx2> pBrokerInit(m_pBroker);

   pBrokerInit->RegInterface(IID_IGraphManager,this);

   return S_OK;
}

STDMETHODIMP CGraphManagerAgent::Init()
{
   return S_OK;
}

STDMETHODIMP CGraphManagerAgent::Init2()
{
   return S_OK;
}

STDMETHODIMP CGraphManagerAgent::Reset()
{
   return S_OK;
}

STDMETHODIMP CGraphManagerAgent::ShutDown()
{
   m_GraphManager.ClearAll();
   return S_OK;
}

STDMETHODIMP CGraphManagerAgent::GetClassID(CLSID* pCLSID)
{
   *pCLSID = CLSID_GraphManagerAgent;
   return S_OK;
}

///////////////////////////////////////////////////////////////////
// IGraphManager
///////////////////////////////////////////////////////////////////
bool CGraphManagerAgent::AddGraphBuilder(CGraphBuilder* pGraphBuilder)
{
   return m_GraphManager.AddGraphBuilder(pGraphBuilder);
}

bool CGraphManagerAgent::AddGraphBuilder(std::shared_ptr<CGraphBuilder>& pGraphBuilder)
{
   return m_GraphManager.AddGraphBuilder(pGraphBuilder);
}

CollectionIndexType CGraphManagerAgent::GetGraphBuilderCount() const
{
   return m_GraphManager.GetGraphBuilderCount();
}

std::shared_ptr<CGraphBuilder> CGraphManagerAgent::GetGraphBuilder(LPCTSTR strGraphName)
{
   return m_GraphManager.GetGraphBuilder(strGraphName);
}

std::shared_ptr<CGraphBuilder> CGraphManagerAgent::GetGraphBuilder(CollectionIndexType index)
{
   return m_GraphManager.GetGraphBuilder(index);
}

std::shared_ptr<CGraphBuilder> CGraphManagerAgent::GetGraphBuilder(const std::_tstring& strGraphName)
{
   return m_GraphManager.GetGraphBuilder(strGraphName);
}

std::shared_ptr<CGraphBuilder> CGraphManagerAgent::RemoveGraphBuilder(LPCTSTR strGraphName)
{
   return m_GraphManager.RemoveGraphBuilder(strGraphName);
}

std::shared_ptr<CGraphBuilder> CGraphManagerAgent::RemoveGraphBuilder(const std::_tstring& strGraphName)
{
   return m_GraphManager.RemoveGraphBuilder(strGraphName);
}

std::vector<std::_tstring> CGraphManagerAgent::GetGraphNames() const
{
   return m_GraphManager.GetGraphNames();
}

const CBitmap* CGraphManagerAgent::GetMenuBitmap(LPCTSTR strGraphName)
{
   return m_GraphManager.GetMenuBitmap(strGraphName);
}

const CBitmap* CGraphManagerAgent::GetMenuBitmap(const std::_tstring& strGraphName)
{
   return m_GraphManager.GetMenuBitmap(strGraphName);
}

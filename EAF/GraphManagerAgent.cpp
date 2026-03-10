///////////////////////////////////////////////////////////////////////
// GraphManagerAgent - Provides graph manager as an Agent
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include "GraphManagerAgent.h"
#include "AgentTools.h"

using namespace WBFL::EAF;


bool GraphManagerAgent::RegisterInterfaces()
{
   EAF_AGENT_REGISTER_INTERFACES;
   REGISTER_INTERFACE(IEAFGraphManager);
   return true;
}

CLSID GraphManagerAgent::GetCLSID() const
{
   return CLSID_GraphManagerAgent;
}

///////////////////////////////////////////////////////////////////
// IGraphManager
///////////////////////////////////////////////////////////////////
void GraphManagerAgent::SortByName(bool bSort)
{
   return m_GraphManager.SortByName(bSort);
}

bool GraphManagerAgent::AddGraphBuilder(const WBFL::Graphing::GraphBuilder& graphBuilder)
{
   return m_GraphManager.AddGraphBuilder(graphBuilder);
}

bool GraphManagerAgent::AddGraphBuilder(std::unique_ptr<WBFL::Graphing::GraphBuilder>&& pGraphBuilder)
{
   return m_GraphManager.AddGraphBuilder(std::move(pGraphBuilder));
}

IndexType GraphManagerAgent::GetGraphBuilderCount() const
{
   return m_GraphManager.GetGraphBuilderCount();
}

WBFL::Graphing::GraphBuilder& GraphManagerAgent::GetGraphBuilder(LPCTSTR strGraphName)
{
   return m_GraphManager.GetGraphBuilder(strGraphName);
}

WBFL::Graphing::GraphBuilder& GraphManagerAgent::GetGraphBuilder(IndexType index)
{
   return m_GraphManager.GetGraphBuilder(index);
}

WBFL::Graphing::GraphBuilder& GraphManagerAgent::GetGraphBuilder(const std::_tstring& strGraphName)
{
   return m_GraphManager.GetGraphBuilder(strGraphName);
}

std::unique_ptr<WBFL::Graphing::GraphBuilder> GraphManagerAgent::RemoveGraphBuilder(LPCTSTR strGraphName)
{
   return m_GraphManager.RemoveGraphBuilder(strGraphName);
}

std::unique_ptr<WBFL::Graphing::GraphBuilder> GraphManagerAgent::RemoveGraphBuilder(const std::_tstring& strGraphName)
{
   return m_GraphManager.RemoveGraphBuilder(strGraphName);
}

std::vector<std::_tstring> GraphManagerAgent::GetGraphNames() const
{
   return m_GraphManager.GetGraphNames();
}

const CBitmap* GraphManagerAgent::GetMenuBitmap(LPCTSTR strGraphName)
{
   return m_GraphManager.GetMenuBitmap(strGraphName);
}

const CBitmap* GraphManagerAgent::GetMenuBitmap(const std::_tstring& strGraphName)
{
   return m_GraphManager.GetMenuBitmap(strGraphName);
}

///////////////////////////////////////////////////////////////////////
// Graphing - Line graph plotting and graph definition management library
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

// GraphManager.cpp: implementation of the GraphManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Graphing/GraphManager.h>

using namespace WBFL::Graphing;

GraphManager::GraphManager(bool bSortByName) : m_bSort(bSortByName)
{
}

void GraphManager::SortByName(bool bSort)
{
   if (bSort != m_bSort)
   {
      m_bSort = bSort;
      if (m_bSort) Sort();
   }
}

bool GraphManager::SortByName() const
{
   return m_bSort;
}

void GraphManager::ClearAll()
{
   m_GraphBuilders.clear();
}

bool GraphManager::AddGraphBuilder(const GraphBuilder& graphBuilder)
{
   return AddGraphBuilder(graphBuilder.Clone());
}

bool GraphManager::AddGraphBuilder(std::unique_ptr<GraphBuilder>&& pGraphBuilder)
{
   PRECONDITION(pGraphBuilder != nullptr);
   std::_tstring strName = pGraphBuilder->GetName();
   try
   {
      auto& builder = GetGraphBuilder(strName);
      return false; // if the exception doesn't throw, a graph building already exists
   }
   catch (...)
   {
      // Failed to get the graph builder - that means we can add this one
      m_GraphBuilders.emplace_back(std::move(pGraphBuilder));
   }

   if (m_bSort) Sort();

   return true;
}

IndexType GraphManager::GetGraphBuilderCount() const
{
   return m_GraphBuilders.size();
}

GraphBuilder& GraphManager::GetGraphBuilder(LPCTSTR strGraphName)
{
   return GetGraphBuilder(std::_tstring(strGraphName));
}

GraphBuilder& GraphManager::GetGraphBuilder(IndexType index)
{
   if (m_GraphBuilders.size() <= index)
      throw std::invalid_argument("GraphManager::GetGraphBuilder - invalid index");

   return *m_GraphBuilders[index].get();
}

GraphBuilder& GraphManager::GetGraphBuilder(const std::_tstring& strGraphName)
{
   auto found = std::find_if(m_GraphBuilders.begin(), m_GraphBuilders.end(), [strGraphName](auto& builder) {return builder->GetName() == strGraphName;});
   if (found == m_GraphBuilders.end())
   {
      throw std::invalid_argument("GraphManager::GetGraphBuilder - invalid graph builder name");
   }

   auto& graph_builder = (*found);
   return *graph_builder.get();
}

std::unique_ptr<GraphBuilder> GraphManager::RemoveGraphBuilder(IndexType index)
{
   if (m_GraphBuilders.size() <= index)
      throw std::invalid_argument("GraphManager::RemoveGraphBuilder - invalid index");

   auto graphBuilder = std::move(m_GraphBuilders[index]); // move the graph builder from the unique_ptr inside the container to a unique_ptr outside the container
   m_GraphBuilders.erase(m_GraphBuilders.begin() + index);
   return graphBuilder;
}

std::unique_ptr<GraphBuilder> GraphManager::RemoveGraphBuilder(LPCTSTR strGraphName)
{
   return RemoveGraphBuilder(std::_tstring(strGraphName));
}

std::unique_ptr<GraphBuilder> GraphManager::RemoveGraphBuilder(const std::_tstring& strGraphName)
{
   auto found = std::find_if(m_GraphBuilders.begin(), m_GraphBuilders.end(), [strGraphName](auto& builder) {return builder->GetName() == strGraphName; });
   if (found == m_GraphBuilders.end())
   {
      CHECK(false); // bad graph name, but not an exceptional condition since no operation is performed
      return std::unique_ptr<GraphBuilder>();
   }

   auto graphBuilder = std::move(*found); // move the graph builder from the unique_ptr inside the container to a unique_ptr outside the container
   m_GraphBuilders.erase(found);

   return graphBuilder;
}

std::vector<std::_tstring> GraphManager::GetGraphNames() const
{
   std::vector<std::_tstring> names;
   std::for_each(std::begin(m_GraphBuilders), std::end(m_GraphBuilders), [&names](const auto& entry) {names.emplace_back(entry->GetName()); });

   return names;
}

const CBitmap* GraphManager::GetMenuBitmap(LPCTSTR strGraphName)
{
   return GetMenuBitmap(std::_tstring(strGraphName));
}

const CBitmap* GraphManager::GetMenuBitmap(const std::_tstring& strGraphName)
{
   auto& graphBuilder = GetGraphBuilder(strGraphName);
   return graphBuilder.GetMenuBitmap();
}

void GraphManager::Sort()
{
   std::sort(m_GraphBuilders.begin(), m_GraphBuilders.end(), [](auto& a, auto& b) {return a->GetName() < b->GetName(); });
}


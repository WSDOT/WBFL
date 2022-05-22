///////////////////////////////////////////////////////////////////////
// Graphing - Line graph plotting and graph definition management library
// Copyright � 1999-2022  Washington State Department of Transportation
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

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace WBFL::Graphing;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GraphManager::GraphManager(bool bSortByName) : m_bSort(bSortByName)
{
}

GraphManager::~GraphManager()
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
   std::_tstring strName = graphBuilder.GetName();
   auto& builder = GetGraphBuilder(strName);
   if (builder != nullptr) return false;

   m_GraphBuilders.emplace_back(std::move(graphBuilder.Clone()));

   if (m_bSort) Sort();

   return true;
}

bool GraphManager::AddGraphBuilder(std::unique_ptr<GraphBuilder>&& pGraphBuilder)
{
   std::_tstring strName = pGraphBuilder->GetName();
   auto& builder = GetGraphBuilder(strName);
   if (builder != nullptr) return false;

   m_GraphBuilders.emplace_back(std::move(pGraphBuilder));

   if (m_bSort) Sort();

   return true;
}

IndexType GraphManager::GetGraphBuilderCount() const
{
   return m_GraphBuilders.size();
}

std::unique_ptr<GraphBuilder>& GraphManager::GetGraphBuilder(LPCTSTR strGraphName)
{
   return GetGraphBuilder(std::_tstring(strGraphName));
}

std::unique_ptr<GraphBuilder>& GraphManager::GetGraphBuilder(IndexType index)
{
   if (m_GraphBuilders.size() <= index) return m_Nullptr;
   return m_GraphBuilders[index];
}

std::unique_ptr<GraphBuilder>& GraphManager::GetGraphBuilder(const std::_tstring& strGraphName)
{
   auto found = std::find_if(m_GraphBuilders.begin(), m_GraphBuilders.end(), [strGraphName](auto& builder) {return builder->GetName() == strGraphName;});
   if (found != m_GraphBuilders.end())
      return *found;
   else
      return m_Nullptr;
}

std::unique_ptr<GraphBuilder> GraphManager::RemoveGraphBuilder(IndexType index)
{
   if (m_GraphBuilders.size() <= index) return false;
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
      return std::unique_ptr<GraphBuilder>();

   auto graphBuilder = std::move(*found); // move the graph builder from the unique_ptr inside the container to a unique_ptr outside the container
   m_GraphBuilders.erase(found);

   return graphBuilder;
}

std::vector<std::_tstring> GraphManager::GetGraphNames() const
{
   std::vector<std::_tstring> names;
   for( const auto& entry : m_GraphBuilders)
   {
      names.emplace_back( entry->GetName() );
   }

   return names;
}

const CBitmap* GraphManager::GetMenuBitmap(LPCTSTR strGraphName)
{
   return GetMenuBitmap(std::_tstring(strGraphName));
}

const CBitmap* GraphManager::GetMenuBitmap(const std::_tstring& strGraphName)
{
   std::unique_ptr<GraphBuilder>& pGraphBuilder = GetGraphBuilder(strGraphName);
   ATLASSERT( pGraphBuilder != nullptr ); // graph builder not found

   return pGraphBuilder->GetMenuBitmap();
}

void GraphManager::Sort()
{
   std::sort(m_GraphBuilders.begin(), m_GraphBuilders.end(), [](auto& a, auto& b) {return a->GetName() < b->GetName(); });
}

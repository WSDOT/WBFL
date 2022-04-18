///////////////////////////////////////////////////////////////////////
// Graphing - Line graph plotting and graph definition management library
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

GraphManager::GraphManager()
{
}

GraphManager::~GraphManager()
{
}

void GraphManager::ClearAll()
{
   m_GraphBuilders.clear();
}

bool GraphManager::AddGraphBuilder(GraphBuilder& graphBuilder)
{
   return AddGraphBuilder(std::move(graphBuilder.Clone()));
}

bool GraphManager::AddGraphBuilder(std::unique_ptr<GraphBuilder>&& pGraphBuilder)
{
   std::_tstring strName = pGraphBuilder->GetName();
   std::pair<GraphBuilderContainer::iterator,bool> result = m_GraphBuilders.insert( std::make_pair( strName, std::move(pGraphBuilder) ) );
   return result.second;
}

CollectionIndexType GraphManager::GetGraphBuilderCount() const
{
   return m_GraphBuilders.size();
}

std::unique_ptr<GraphBuilder>& GraphManager::GetGraphBuilder(LPCTSTR strGraphName)
{
   return GetGraphBuilder(std::_tstring(strGraphName));
}

std::unique_ptr<GraphBuilder>& GraphManager::GetGraphBuilder(IndexType index)
{
   GraphBuilderContainer::iterator iter = m_GraphBuilders.begin();
   for ( IndexType i = 0; i < index; i++, iter++ )
   {}

   return iter->second;
}

std::unique_ptr<GraphBuilder>& GraphManager::GetGraphBuilder(const std::_tstring& strGraphName)
{
   GraphBuilderContainer::iterator found = m_GraphBuilders.find(strGraphName);
   if (found == m_GraphBuilders.end())
      return m_NullPtr; // we must return a refernce to a real object

   return (*found).second;
}

bool GraphManager::RemoveGraphBuilder(IndexType index)
{
   GraphBuilderContainer::iterator iter = m_GraphBuilders.begin();
   for (IndexType i = 0; i < index; i++, iter++)
   {
   }
   m_GraphBuilders.erase(iter);
   return true;
}

bool GraphManager::RemoveGraphBuilder(LPCTSTR strGraphName)
{
   return RemoveGraphBuilder(std::_tstring(strGraphName));
}

bool GraphManager::RemoveGraphBuilder(const std::_tstring& strGraphName)
{
   GraphBuilderContainer::iterator found = m_GraphBuilders.find(strGraphName);
   if (found == m_GraphBuilders.end())
      return false;

   m_GraphBuilders.erase(found);

   return true;
}

std::vector<std::_tstring> GraphManager::GetGraphNames() const
{
   std::vector<std::_tstring> names;
   for( const auto& entry : m_GraphBuilders)
   {
      names.push_back( entry.first );
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

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

// GraphManager.h: interface for the CGraphManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <Graphing/GraphingExp.h>
#include <Graphing/GraphBuilder.h>

#include <map>
#include <vector>

#include <memory>

namespace WBFL
{
   namespace Graphing
   {

/// Class to manage graph builders for an application
class GRAPHINGCLASS GraphManager
{
public:
   GraphManager();
	virtual ~GraphManager();

   /// Adds a graph builder to the manager. Makes a clone of the graph builder
   bool AddGraphBuilder(GraphBuilder& graphBuilder);

   /// Adds a graph builder to the manager.
   bool AddGraphBuilder(std::unique_ptr<GraphBuilder>&& pGraphBuilder);

   /// Returns the number of builders
   CollectionIndexType GetGraphBuilderCount() const;

   /// Returns a graph builder by index
   std::unique_ptr<GraphBuilder>& GetGraphBuilder(IndexType index);

   /// Returns a graph builder by name
   std::unique_ptr<GraphBuilder>& GetGraphBuilder(LPCTSTR strGraphName);

   /// Returns a graph builder by name
   std::unique_ptr<GraphBuilder>& GetGraphBuilder(const std::_tstring& strGraphName);

   /// Removes a graph builder by index
   bool RemoveGraphBuilder(IndexType index);

   /// Removes a graph builder by name
   bool RemoveGraphBuilder(LPCTSTR strGraphName);

   /// Removes a graph builder by name
   bool RemoveGraphBuilder(const std::_tstring& strGraphName);

   /// Clears all graph builders
   virtual void ClearAll();

   /// Returns a list of graph builder names
   std::vector<std::_tstring> GetGraphNames() const;

   /// Gets a bitmap that represents the graph
   const CBitmap* GetMenuBitmap(LPCTSTR strReportName);

   /// Gets a bitmap that represents the graph
   const CBitmap* GetMenuBitmap(const std::_tstring& strReportName);

private:
   typedef std::pair<std::_tstring, std::unique_ptr<GraphBuilder>> GraphBuilderEntry;
   typedef std::map<std::_tstring, std::unique_ptr<GraphBuilder>> GraphBuilderContainer;
   std::unique_ptr<GraphBuilder> m_NullPtr{ nullptr };
   GraphBuilderContainer m_GraphBuilders;
};

   }; // Graphing
}; // WBFL

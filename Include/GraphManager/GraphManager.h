///////////////////////////////////////////////////////////////////////
// GraphManager - Manages graph definitions
// Copyright © 1999-2016  Washington State Department of Transportation
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

#include <GraphManager\GraphManagerExp.h>
#include <GraphManager\GraphBuilder.h>
#include <boost\shared_ptr.hpp>
#include <map>
#include <vector>

class GRAPHMANAGERCLASS CGraphManager
{
public:
	CGraphManager();
	virtual ~CGraphManager();
   virtual void ClearAll();  // deletes all graph builders

   bool AddGraphBuilder(CGraphBuilder* pBuilder);
   bool AddGraphBuilder(boost::shared_ptr<CGraphBuilder>& pGraphBuilder);
   CollectionIndexType GetGraphBuilderCount() const;
   boost::shared_ptr<CGraphBuilder> GetGraphBuilder(CollectionIndexType index);
   boost::shared_ptr<CGraphBuilder> GetGraphBuilder(LPCTSTR strGraphName);
   boost::shared_ptr<CGraphBuilder> GetGraphBuilder(const std::_tstring& strGraphName);
   boost::shared_ptr<CGraphBuilder> RemoveGraphBuilder(LPCTSTR strGraphName);
   boost::shared_ptr<CGraphBuilder> RemoveGraphBuilder(const std::_tstring& strGraphName);
   std::vector<std::_tstring> GetGraphNames() const;
   const CBitmap* GetMenuBitmap(LPCTSTR strReportName);
   const CBitmap* GetMenuBitmap(const std::_tstring& strReportName);

private:
   typedef std::pair<std::_tstring, boost::shared_ptr<CGraphBuilder>> GraphBuilderEntry;
   typedef std::map<std::_tstring, boost::shared_ptr<CGraphBuilder>> GraphBuilderContainer;
   GraphBuilderContainer m_GraphBuilders;
};

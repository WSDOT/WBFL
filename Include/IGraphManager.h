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

#pragma once

#include <GraphManager\GraphManager.h>


// {FBA71046-0C05-4946-83DD-4C71A973C18D}
DEFINE_GUID(IID_IGraphManager, 
0xfba71046, 0xc05, 0x4946, 0x83, 0xdd, 0x4c, 0x71, 0xa9, 0x73, 0xc1, 0x8d);
interface IGraphManager : IUnknown
{
   virtual void SortByName(bool bSort) = 0;
   virtual bool AddGraphBuilder(CGraphBuilder* pRptBuilder) = 0;
   virtual bool AddGraphBuilder(std::shared_ptr<CGraphBuilder>& pGraphBuilder) = 0;
   virtual IndexType GetGraphBuilderCount() const = 0;
   virtual std::shared_ptr<CGraphBuilder> GetGraphBuilder(IndexType index) = 0;
   virtual std::shared_ptr<CGraphBuilder> GetGraphBuilder(LPCTSTR strGraphName) = 0;
   virtual std::shared_ptr<CGraphBuilder> GetGraphBuilder(const std::_tstring& strGraphName) = 0;
   virtual std::shared_ptr<CGraphBuilder> RemoveGraphBuilder(LPCTSTR strGraphName) = 0;
   virtual std::shared_ptr<CGraphBuilder> RemoveGraphBuilder(const std::_tstring& strGraphName) = 0;
   virtual std::vector<std::_tstring> GetGraphNames() const = 0;
   virtual const CBitmap* GetMenuBitmap(LPCTSTR strGraphName) = 0;
   virtual const CBitmap* GetMenuBitmap(const std::_tstring& strGraphName) = 0;
};

///////////////////////////////////////////////////////////////////////
// GraphManagerAgent - Provides Graph manager as an Agent
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

// GraphManager.h : Declaration of the CGraphManager

#pragma once

#include <EAF/Agent.h>
#include <EAF/EAFGraphManager.h>
#include <Graphing/GraphBuilder.h>
#include <Graphing/GraphManager.h>

namespace WBFL
{
   namespace EAF
   {

      // {1611AC48-FDC6-4f3d-AE54-DB9F7615821D}
      DEFINE_GUID(CLSID_GraphManagerAgent,
         0x1611AC48, 0xFDC6, 0x4f3d, 0xAE, 0x54, 0xDB, 0x9F, 0x76, 0x15, 0x82, 0x1D);

      /// @brief A specialized agent that implements the IEAFGraphManager interface
      class GraphManagerAgent : public WBFL::EAF::Agent,
         public IEAFGraphManager
      {
      public:
         GraphManagerAgent() = default;

         WBFL::Graphing::GraphManager m_GraphManager;

         // Agent
      public:
         std::_tstring GetName() const override { return _T("GraphManagerAgent"); }
         bool RegisterInterfaces() override;
         CLSID GetCLSID() const override;


      // IEAFGraphManager
      public:
         void SortByName(bool bSort) override;
         bool AddGraphBuilder(const WBFL::Graphing::GraphBuilder& graphBuilder) override;
         bool AddGraphBuilder(std::unique_ptr<WBFL::Graphing::GraphBuilder>&& pGraphBuilder) override;
         IndexType GetGraphBuilderCount() const override;
         WBFL::Graphing::GraphBuilder& GetGraphBuilder(IndexType index) override;
         WBFL::Graphing::GraphBuilder& GetGraphBuilder(LPCTSTR strGraphName) override;
         WBFL::Graphing::GraphBuilder& GetGraphBuilder(const std::_tstring& strGraphName) override;
         std::unique_ptr<WBFL::Graphing::GraphBuilder> RemoveGraphBuilder(LPCTSTR strGraphName) override;
         std::unique_ptr<WBFL::Graphing::GraphBuilder> RemoveGraphBuilder(const std::_tstring& strGraphName) override;
         std::vector<std::_tstring> GetGraphNames() const override;
         const CBitmap* GetMenuBitmap(LPCTSTR strGraphName) override;
         const CBitmap* GetMenuBitmap(const std::_tstring& strGraphName) override;
      };

   };
};

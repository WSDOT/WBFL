///////////////////////////////////////////////////////////////////////
// ReportManagerAgent - Provides report manager as an Agent
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

// ReportManager.h : Declaration of the CReportManager

#pragma once

#include <EAF\Agent.h>
#include <EAF\EAFReportManager.h>
#include <ReportManager\ReportBuilderManager.h>
#include <ReportManager\ReportBuilder.h>

namespace WBFL
{
   namespace EAF
   {
      // {809889B1-69F0-49FC-B8F5-50B0BC169EB0}
      DEFINE_GUID(CLSID_ReportManagerAgent,
         0x809889B1, 0x69F0, 0x49FC, 0xB8, 0xF5, 0x50, 0xB0, 0xBC, 0x16, 0x9E, 0xB0);

      /// @brief A specialized agent that implements the IEAFReportManager interface
      class ReportManagerAgent : public WBFL::EAF::Agent,
         public IEAFReportManager
      {
      public:
         ReportManagerAgent() : Agent()
         {
            m_pRptMgr = WBFL::Reporting::ReportBuilderManager::Create();
         }

      private:
         std::shared_ptr<WBFL::Reporting::ReportBuilderManager> m_pRptMgr;

         // Agent
      public:
         std::_tstring GetName() const override { return _T("ReportManagerAgent"); }
         bool RegisterInterfaces() override;
         CLSID GetCLSID() const override;

         // IReportManager
      public:
         void AddReportBuilder(std::shared_ptr<WBFL::Reporting::ReportBuilder>& pReportBuilder) override;
         IndexType GetReportBuilderCount(bool bIncludeHidden) const override;
         std::shared_ptr<WBFL::Reporting::ReportBuilder> GetReportBuilder(LPCTSTR strReportName) override;
         std::shared_ptr<WBFL::Reporting::ReportBuilder> GetReportBuilder(const std::_tstring& strReportName) override;
         std::shared_ptr<WBFL::Reporting::ReportBuilder> RemoveReportBuilder(LPCTSTR strReportName) override;
         std::shared_ptr<WBFL::Reporting::ReportBuilder> RemoveReportBuilder(const std::_tstring& strReportName) override;
         std::vector<std::_tstring> GetReportNames(bool bIncludeHidden) const override;
         WBFL::Reporting::ReportDescription GetReportDescription(LPCTSTR strReportName) override;
         WBFL::Reporting::ReportDescription GetReportDescription(const std::_tstring& strReportName) override;
         const CBitmap* GetMenuBitmap(LPCTSTR strReportName) override;
         const CBitmap* GetMenuBitmap(const std::_tstring& strReportName) override;
         std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> GetReportSpecificationBuilder(LPCTSTR strReportName) override;
         std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> GetReportSpecificationBuilder(const std::_tstring& strReportName) override;
         std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> GetReportSpecificationBuilder(const WBFL::Reporting::ReportDescription& rptDesc) override;
         void SetReportBrowserType(WBFL::Reporting::ReportBrowser::Type browserType) override;
         WBFL::Reporting::ReportBrowser::Type GetReportBrowserType() const;
         std::shared_ptr<WBFL::Reporting::ReportBrowser> CreateReportBrowser(HWND hwndParent, DWORD dwStyle, const std::shared_ptr<WBFL::Reporting::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pRptSpecBuilder) override;
         INT_PTR DisplayReportDialog(DWORD flags, const std::shared_ptr<WBFL::Reporting::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pRptSpecBuilder) override;
      };
   };
};

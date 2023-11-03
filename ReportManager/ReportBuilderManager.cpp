///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include "stdafx.h"
#include "ReportManager.h"
#include <ReportManager\ReportBuilderManager.h>
#include <Reporter\Reporter.h>
#include "ReportDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace WBFL::Reporting;

std::shared_ptr<ReportBuilderManager> ReportBuilderManager::Create()
{
   return std::shared_ptr<ReportBuilderManager>(new ReportBuilderManager());
}

void ReportBuilderManager::ClearAll()
{
   m_RptBuilders.clear();
}

void ReportBuilderManager::AddReportBuilder(std::shared_ptr<ReportBuilder>& pRptBuilder)
{
   std::_tstring strName = pRptBuilder->GetName();
   m_RptBuilders.insert( std::make_pair( strName, pRptBuilder ) );
}

IndexType ReportBuilderManager::GetReportBuilderCount(bool bIncludeHidden) const
{
   if ( bIncludeHidden )
   {
      return m_RptBuilders.size();
   }

   IndexType nReportBuilders = 0;
   for(const auto& entry : m_RptBuilders)
   {
      if ( !entry.second->Hidden() )
      {
         nReportBuilders++;
      }
   }

   return nReportBuilders;
}

std::shared_ptr<ReportBuilder> ReportBuilderManager::GetReportBuilder(LPCTSTR strReportName)
{
   return GetReportBuilder(std::_tstring(strReportName));
}

std::shared_ptr<ReportBuilder> ReportBuilderManager::GetReportBuilder(const std::_tstring& strReportName)
{
   RptBuilderContainer::iterator found = m_RptBuilders.find(strReportName);
   if ( found == m_RptBuilders.end() )
   {
      return nullptr;
   }

   return (*found).second;
}

std::shared_ptr<const ReportBuilder> ReportBuilderManager::GetReportBuilder(LPCTSTR strReportName) const
{
   return GetReportBuilder(std::_tstring(strReportName));
}

std::shared_ptr<const ReportBuilder> ReportBuilderManager::GetReportBuilder(const std::_tstring& strReportName) const
{
   RptBuilderContainer::const_iterator found = m_RptBuilders.find(strReportName);
   if (found == m_RptBuilders.end())
   {
      return nullptr;
   }

   return (*found).second;
}

std::shared_ptr<ReportBuilder> ReportBuilderManager::RemoveReportBuilder(LPCTSTR strReportName)
{
   return RemoveReportBuilder(std::_tstring(strReportName));
}

std::shared_ptr<ReportBuilder> ReportBuilderManager::RemoveReportBuilder(const std::_tstring& strReportName)
{
   RptBuilderContainer::iterator found = m_RptBuilders.find(strReportName);
   if ( found == m_RptBuilders.end() )
   {
      return nullptr;
   }

   std::shared_ptr<ReportBuilder> rptBuilder = (*found).second;

   m_RptBuilders.erase(found);

   return rptBuilder;
}

std::vector<std::_tstring> ReportBuilderManager::GetReportNames(bool bIncludeHidden) const
{
   std::vector<std::_tstring> names;
   for (const auto& [name,builder] : m_RptBuilders)
   {
      if (bIncludeHidden || !builder->Hidden())
      {
         names.emplace_back(name);
      }
   }

   return names;
}

ReportDescription ReportBuilderManager::GetReportDescription(LPCTSTR strReportName) const
{
   return GetReportDescription(std::_tstring(strReportName));
}

ReportDescription ReportBuilderManager::GetReportDescription(const std::_tstring& strReportName) const
{
   auto pRptBuilder = GetReportBuilder(strReportName);
   ATLASSERT( pRptBuilder != nullptr ); // report builder not found

   return pRptBuilder->GetReportDescription();
}

const CBitmap* ReportBuilderManager::GetMenuBitmap(LPCTSTR strReportName)
{
   return GetMenuBitmap(std::_tstring(strReportName));
}

const CBitmap* ReportBuilderManager::GetMenuBitmap(const std::_tstring& strReportName)
{
   std::shared_ptr<ReportBuilder> pRptBuilder = GetReportBuilder(strReportName);
   ATLASSERT( pRptBuilder != nullptr ); // report builder not found

   return pRptBuilder->GetMenuBitmap();
}

std::shared_ptr<ReportSpecificationBuilder> ReportBuilderManager::GetReportSpecificationBuilder(LPCTSTR strReportName)
{
   return GetReportSpecificationBuilder(std::_tstring(strReportName));
}

std::shared_ptr<ReportSpecificationBuilder> ReportBuilderManager::GetReportSpecificationBuilder(const std::_tstring& strReportName)
{
   std::shared_ptr<ReportBuilder> pRptBuilder = GetReportBuilder(strReportName);
   if ( pRptBuilder == nullptr )
   {
      return nullptr;
   }

   return pRptBuilder->GetReportSpecificationBuilder();
}

std::shared_ptr<ReportSpecificationBuilder> ReportBuilderManager::GetReportSpecificationBuilder(const ReportDescription& rptDesc)
{
   return GetReportSpecificationBuilder( rptDesc.GetReportName() );
}

void ReportBuilderManager::SetReportBrowserType(ReportBrowser::Type browserType)
{
   m_BrowserType = browserType;
}

ReportBrowser::Type ReportBuilderManager::GetReportBrowserType() const
{
   return m_BrowserType;
}

std::shared_ptr<ReportBrowser> ReportBuilderManager::CreateReportBrowser(HWND hwndParent, DWORD dwStyle, const std::shared_ptr<ReportSpecification>& pRptSpec,const std::shared_ptr<const ReportSpecificationBuilder>& pRptSpecBuilder) const
{
   std::shared_ptr<rptReport> pReport = CreateReport(pRptSpec);
   std::shared_ptr<ReportBrowser> pBrowser( std::make_shared<ReportBrowser>(m_BrowserType) );
   bool bSuccess = pBrowser->Initialize(hwndParent, dwStyle ,shared_from_this(), pRptSpec, pRptSpecBuilder, pReport);
   if ( !bSuccess )
   {
      pBrowser = nullptr;
   }

   return pBrowser;
}

INT_PTR ReportBuilderManager::DisplayReportDialog(DWORD flags, const std::shared_ptr<ReportSpecification>& pRptSpec, const std::shared_ptr<const ReportSpecificationBuilder>& pRptSpecBuilder)
{
   // flags will be used in the future to control attribues of the dialog
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   CReportDlg dlg(shared_from_this(), pRptSpec, pRptSpecBuilder);
   return dlg.DoModal();
}

std::shared_ptr<rptReport> ReportBuilderManager::CreateReport(const std::shared_ptr<ReportSpecification>& pRptSpec) const
{
   auto pRptBuilder = GetReportBuilder(pRptSpec->GetReportName());
   return pRptBuilder->CreateReport( pRptSpec );
}

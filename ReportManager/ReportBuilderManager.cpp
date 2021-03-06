///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright � 1999-2021  Washington State Department of Transportation
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

// ReportBuilderManager.cpp: implementation of the CReportBuilderManager class.
//
//////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportBuilderManager::CReportBuilderManager()
{
}

CReportBuilderManager::~CReportBuilderManager()
{
}

void CReportBuilderManager::ClearAll()
{
   m_RptBuilders.clear();
}

void CReportBuilderManager::AddReportBuilder(CReportBuilder* pRptBuilder)
{
   std::_tstring strName = pRptBuilder->GetName();
   std::shared_ptr<CReportBuilder> p(pRptBuilder);
   m_RptBuilders.insert( std::make_pair( strName, p ) );
}

void CReportBuilderManager::AddReportBuilder(std::shared_ptr<CReportBuilder>& pRptBuilder)
{
   std::_tstring strName = pRptBuilder->GetName();
   m_RptBuilders.insert( std::make_pair( strName, pRptBuilder ) );
}

CollectionIndexType CReportBuilderManager::GetReportBuilderCount(bool bIncludeHidden) const
{
   if ( bIncludeHidden )
   {
      return m_RptBuilders.size();
   }

   CollectionIndexType nReportBuilders = 0;
   RptBuilderContainer::const_iterator iter(m_RptBuilders.begin());
   RptBuilderContainer::const_iterator end(m_RptBuilders.end());
   for ( ; iter != end; iter++ )
   {
      const RptBuilderEntry& entry = *iter;
      if ( !entry.second->Hidden() )
      {
         nReportBuilders++;
      }
   }

   return nReportBuilders;
}

std::shared_ptr<CReportBuilder> CReportBuilderManager::GetReportBuilder(LPCTSTR strReportName)
{
   return GetReportBuilder(std::_tstring(strReportName));
}

std::shared_ptr<CReportBuilder> CReportBuilderManager::GetReportBuilder(const std::_tstring& strReportName)
{
   RptBuilderContainer::iterator found = m_RptBuilders.find(strReportName);
   if ( found == m_RptBuilders.end() )
   {
      return nullptr;
   }

   return (*found).second;
}

std::shared_ptr<CReportBuilder> CReportBuilderManager::RemoveReportBuilder(LPCTSTR strReportName)
{
   return RemoveReportBuilder(std::_tstring(strReportName));
}

std::shared_ptr<CReportBuilder> CReportBuilderManager::RemoveReportBuilder(const std::_tstring& strReportName)
{
   RptBuilderContainer::iterator found = m_RptBuilders.find(strReportName);
   if ( found == m_RptBuilders.end() )
   {
      return nullptr;
   }

   std::shared_ptr<CReportBuilder> rptBuilder = (*found).second;

   m_RptBuilders.erase(found);

   return rptBuilder;
}

std::vector<std::_tstring> CReportBuilderManager::GetReportNames(bool bIncludeHidden) const
{
   std::vector<std::_tstring> names;
   RptBuilderContainer::const_iterator iter;
   for ( iter = m_RptBuilders.begin(); iter != m_RptBuilders.end(); iter++ )
   {
      if ( bIncludeHidden || !(*iter).second->Hidden() )
      {
         names.push_back( (*iter).first );
      }
   }

   return names;
}

CReportDescription CReportBuilderManager::GetReportDescription(LPCTSTR strReportName)
{
   return GetReportDescription(std::_tstring(strReportName));
}

CReportDescription CReportBuilderManager::GetReportDescription(const std::_tstring& strReportName)
{
   std::shared_ptr<CReportBuilder> pRptBuilder = GetReportBuilder(strReportName);
   ATLASSERT( pRptBuilder != nullptr ); // report builder not found

   return pRptBuilder->GetReportDescription();
}

const CBitmap* CReportBuilderManager::GetMenuBitmap(LPCTSTR strReportName)
{
   return GetMenuBitmap(std::_tstring(strReportName));
}

const CBitmap* CReportBuilderManager::GetMenuBitmap(const std::_tstring& strReportName)
{
   std::shared_ptr<CReportBuilder> pRptBuilder = GetReportBuilder(strReportName);
   ATLASSERT( pRptBuilder != nullptr ); // report builder not found

   return pRptBuilder->GetMenuBitmap();
}

std::shared_ptr<CReportSpecificationBuilder> CReportBuilderManager::GetReportSpecificationBuilder(LPCTSTR strReportName)
{
   return GetReportSpecificationBuilder(std::_tstring(strReportName));
}

std::shared_ptr<CReportSpecificationBuilder> CReportBuilderManager::GetReportSpecificationBuilder(const std::_tstring& strReportName)
{
   std::shared_ptr<CReportBuilder> pRptBuilder = GetReportBuilder(strReportName);
   if ( pRptBuilder == nullptr )
   {
      return nullptr;
   }

   return pRptBuilder->GetReportSpecificationBuilder();
}

std::shared_ptr<CReportSpecificationBuilder> CReportBuilderManager::GetReportSpecificationBuilder(const CReportDescription& rptDesc)
{
   return GetReportSpecificationBuilder( rptDesc.GetReportName() );
}

std::shared_ptr<CReportBrowser> CReportBuilderManager::CreateReportBrowser(HWND hwndParent, std::shared_ptr<CReportSpecification>& pRptSpec,std::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder)
{
   std::shared_ptr<rptReport> pReport = CreateReport(pRptSpec);
   std::shared_ptr<CReportBrowser> pBrowser( std::make_shared<CReportBrowser>() );
   bool bSuccess = pBrowser->Initialize(hwndParent,this,pRptSpec,pRptSpecBuilder,pReport);
   if ( !bSuccess )
   {
      pBrowser = nullptr;
   }

   return pBrowser;
}

INT_PTR CReportBuilderManager::DisplayReportDialog(DWORD flags, std::shared_ptr<CReportSpecification>& pRptSpec, std::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder)
{
   // flags will be used in the future to control attribues of the dialog
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   CReportDlg dlg(*this,pRptSpec,pRptSpecBuilder);
   return dlg.DoModal();
}

std::shared_ptr<rptReport> CReportBuilderManager::CreateReport(std::shared_ptr<CReportSpecification>& pRptSpec)
{
   std::shared_ptr<CReportBuilder> pRptBuilder = GetReportBuilder(pRptSpec->GetReportName());
   return pRptBuilder->CreateReport( pRptSpec );
}

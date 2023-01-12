///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2023  Washington State Department of Transportation
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

// ReportBuilder.cpp: implementation of the CReportBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportManager.h"
#include <ReportManager\ReportBuilder.h>
#include <ReportManager\ReportSpecificationBuilder.h>
#include <ReportManager\TimeChapterBuilder.h>
#include <Reporter\Reporter.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportBuilder::CReportBuilder(LPCTSTR strName,bool bHidden,bool bIncludeTimingChapter) :
m_Name(strName),
m_bHidden(bHidden),
m_bIncludeTimingChapter(bIncludeTimingChapter),
m_pRptSpecBuilder( new CReportSpecificationBuilder )
{
   m_pBitmap = nullptr;
}

CReportBuilder::~CReportBuilder()
{

}

LPCTSTR CReportBuilder::GetName() const
{
   return m_Name.c_str();
}

void CReportBuilder::Hidden(bool bHide)
{
   m_bHidden = bHide;
}

bool CReportBuilder::Hidden() const
{
   return m_bHidden;
}

void CReportBuilder::IncludeTimingChapter(bool bInclude)
{
   m_bIncludeTimingChapter = bInclude;
}

bool CReportBuilder::IncludeTimingChapter() const
{
   return m_bIncludeTimingChapter;
}

void CReportBuilder::AddTitlePageBuilder(std::shared_ptr<CTitlePageBuilder>& pTitlePageBuilder)
{
   m_pTitlePageBuilder = pTitlePageBuilder;
}

std::shared_ptr<CTitlePageBuilder> CReportBuilder::GetTitlePageBuilder()
{
   return m_pTitlePageBuilder;
}

void CReportBuilder::AddChapterBuilder(std::shared_ptr<CChapterBuilder>& pChapterBuilder)
{
   m_ChapterBuilders.push_back( pChapterBuilder );
}

bool CReportBuilder::InsertChapterBuilder(std::shared_ptr<CChapterBuilder>& pNewChapterBuilder,LPCTSTR strAfterChapter)
{
   std::_tstring tstrAfterChapter(strAfterChapter);

   ChapterBuilderContainer::iterator iter(m_ChapterBuilders.begin());
   ChapterBuilderContainer::iterator end(m_ChapterBuilders.end());
   for ( ; iter != end; iter++ )
   {
      std::shared_ptr<CChapterBuilder>& pChapterBuilder(*iter);
      if ( std::_tstring(pChapterBuilder->GetName()) == tstrAfterChapter )
      {
         iter++;
         std::shared_ptr<CChapterBuilder>& pChBldr(*iter);
         if ( std::_tstring(pChBldr->GetName()) == std::_tstring(pNewChapterBuilder->GetName()) )
         {
            // a chapter with that name already exists
            return false;
         }

         m_ChapterBuilders.insert(iter,pNewChapterBuilder);
         return true;
      }
   }

   return false;
}

bool CReportBuilder::RemoveChapterBuilder(LPCTSTR lpszChapterName)
{
   std::_tstring strAfterChapter(lpszChapterName);

   ChapterBuilderContainer::iterator iter(m_ChapterBuilders.begin());
   ChapterBuilderContainer::iterator end(m_ChapterBuilders.end());
   for ( ; iter != end; iter++ )
   {
      std::shared_ptr<CChapterBuilder>& pChapterBuilder(*iter);
      if ( std::_tstring(pChapterBuilder->GetName()) == strAfterChapter )
      {
         m_ChapterBuilders.erase(iter);
         return true;
      }
   }

   return false;
}

CollectionIndexType CReportBuilder::GetChapterBuilderCount() const
{
   return m_ChapterBuilders.size();
}

std::shared_ptr<CChapterBuilder> CReportBuilder::GetChapterBuilder(CollectionIndexType idx)
{
   return m_ChapterBuilders[idx];
}

std::shared_ptr<CChapterBuilder> CReportBuilder::GetChapterBuilder(LPCTSTR strKey)
{
   for( const auto& pChBuilder : m_ChapterBuilders)
   {
      if ( std::_tstring(pChBuilder->GetKey()) == std::_tstring(strKey) )
      {
         return pChBuilder;
      }
   }

   return nullptr;
}

CReportDescription CReportBuilder::GetReportDescription()
{
   CReportDescription rptDesc(m_Name.c_str());

   for( const auto& pChBuilder : m_ChapterBuilders)
   {
      const CChapterBuilder* pBuilder = pChBuilder.get();
      rptDesc.AddChapter( pBuilder );
   }

   return rptDesc;
}

void CReportBuilder::SetReportSpecificationBuilder(std::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder)
{
   m_pRptSpecBuilder = pRptSpecBuilder;
}

std::shared_ptr<CReportSpecificationBuilder> CReportBuilder::GetReportSpecificationBuilder()
{
   return m_pRptSpecBuilder;
}

bool CReportBuilder::NeedsUpdate(CReportHint* pHint, std::shared_ptr<CReportSpecification>& pRptSpec)
{
   std::vector<CChapterInfo> vchInfo = pRptSpec->GetChapterInfo();

   if ( m_pTitlePageBuilder.get() != nullptr && m_pTitlePageBuilder->NeedsUpdate(pHint,pRptSpec) )
   {
      return true;
   }

   for( const auto& chInfo : vchInfo)
   {
      std::shared_ptr<CChapterBuilder> pChBuilder = GetChapterBuilder( chInfo.Key.c_str() );
      if ( pChBuilder && pChBuilder->NeedsUpdate(pHint,pRptSpec.get(),chInfo.MaxLevel) )
      {
         return true;
      }
   }

   return false;
}

std::shared_ptr<rptReport> CReportBuilder::CreateReport(std::shared_ptr<CReportSpecification>& pRptSpec)
{
   sysTime start;

   std::shared_ptr<rptReport> pReport( std::make_shared<rptReport>(pRptSpec->GetReportName()) );
   std::vector<CChapterInfo> vchInfo = pRptSpec->GetChapterInfo();

   for( const auto& chInfo : vchInfo)
   {
      std::shared_ptr<CChapterBuilder> pChBuilder = GetChapterBuilder( chInfo.Key.c_str() );
      if ( pChBuilder )
      {
         rptChapter* pChapter = pChBuilder->Build( pRptSpec.get(), chInfo.MaxLevel );
         if ( pChapter )
         {
            (*pReport) << pChapter;
         }
      }
   }

   // Build title page after all others to assure that all status items have been created
   if ( m_pTitlePageBuilder.get() )
   {
      rptChapter* pTitlePage = m_pTitlePageBuilder->Build( pRptSpec );
      pReport->InsertChapterAt(0, pTitlePage);
   }

   sysTime end;
   if ( m_bIncludeTimingChapter )
   {
      CTimeChapterBuilder timeChapterBuilder;
      rptChapter* pChapter = timeChapterBuilder.Build(start,end);
      (*pReport) << pChapter;
   }

   return pReport;
}

void CReportBuilder::SetMenuBitmap(const CBitmap* pBmp)
{
   m_pBitmap = pBmp;
}

const CBitmap* CReportBuilder::GetMenuBitmap()
{
   return m_pBitmap;
}

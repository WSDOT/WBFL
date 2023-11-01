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

using namespace WBFL::Reporting;

ReportBuilder::ReportBuilder(LPCTSTR strName,bool bHidden,bool bIncludeTimingChapter) :
m_Name(strName),
m_bHidden(bHidden),
m_bIncludeTimingChapter(bIncludeTimingChapter)
{
}

LPCTSTR ReportBuilder::GetName() const
{
   return m_Name.c_str();
}

void ReportBuilder::Hidden(bool bHide)
{
   m_bHidden = bHide;
}

bool ReportBuilder::Hidden() const
{
   return m_bHidden;
}

void ReportBuilder::IncludeTimingChapter(bool bInclude)
{
   m_bIncludeTimingChapter = bInclude;
}

bool ReportBuilder::IncludeTimingChapter() const
{
   return m_bIncludeTimingChapter;
}

void ReportBuilder::AddTitlePageBuilder(std::shared_ptr<TitlePageBuilder> pTitlePageBuilder)
{
   m_pTitlePageBuilder = pTitlePageBuilder;
}

std::shared_ptr<TitlePageBuilder> ReportBuilder::GetTitlePageBuilder()
{
   return m_pTitlePageBuilder;
}

void ReportBuilder::AddChapterBuilder(std::shared_ptr<ChapterBuilder> pChapterBuilder)
{
   m_ChapterBuilders.push_back( pChapterBuilder );
}

bool ReportBuilder::InsertChapterBuilder(std::shared_ptr<ChapterBuilder> pNewChapterBuilder,LPCTSTR strKey)
{
   std::_tstring tstrAfterChapterKey(strKey);

   ChapterBuilderContainer::iterator iter(m_ChapterBuilders.begin());
   ChapterBuilderContainer::iterator end(m_ChapterBuilders.end());
   for ( ; iter != end; iter++ )
   {
      std::shared_ptr<ChapterBuilder>& pChapterBuilder(*iter);
      if ( std::_tstring(pChapterBuilder->GetKey()) == tstrAfterChapterKey )
      {
         iter++;
         std::shared_ptr<ChapterBuilder>& pChBldr(*iter);
         if ( std::_tstring(pChBldr->GetKey()) == std::_tstring(pNewChapterBuilder->GetKey()) )
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

bool ReportBuilder::RemoveChapterBuilder(LPCTSTR strKey)
{
   std::_tstring strAfterChapterKey(strKey);

   ChapterBuilderContainer::iterator iter(m_ChapterBuilders.begin());
   ChapterBuilderContainer::iterator end(m_ChapterBuilders.end());
   for ( ; iter != end; iter++ )
   {
      std::shared_ptr<ChapterBuilder>& pChapterBuilder(*iter);
      if ( std::_tstring(pChapterBuilder->GetKey()) == strAfterChapterKey )
      {
         m_ChapterBuilders.erase(iter);
         return true;
      }
   }

   return false;
}

IndexType ReportBuilder::GetChapterBuilderCount() const
{
   return m_ChapterBuilders.size();
}

std::shared_ptr<ChapterBuilder> ReportBuilder::GetChapterBuilder(IndexType idx)
{
   return m_ChapterBuilders[idx];
}

std::shared_ptr<ChapterBuilder> ReportBuilder::GetChapterBuilder(LPCTSTR strKey)
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

std::shared_ptr<const ChapterBuilder> ReportBuilder::GetChapterBuilder(IndexType idx) const
{
   return m_ChapterBuilders[idx];
}

std::shared_ptr<const ChapterBuilder> ReportBuilder::GetChapterBuilder(LPCTSTR strKey) const
{
   for (const auto& pChBuilder : m_ChapterBuilders)
   {
      if (std::_tstring(pChBuilder->GetKey()) == std::_tstring(strKey))
      {
         return pChBuilder;
      }
   }

   return nullptr;
}

ReportDescription ReportBuilder::GetReportDescription() const
{
   ReportDescription rptDesc(m_Name.c_str());

   for( const auto& pChBuilder : m_ChapterBuilders)
   {
      rptDesc.AddChapter(pChBuilder);
   }

   return rptDesc;
}

void ReportBuilder::SetReportSpecificationBuilder(std::shared_ptr<ReportSpecificationBuilder> pRptSpecBuilder)
{
   m_pRptSpecBuilder = pRptSpecBuilder;
}

std::shared_ptr<ReportSpecificationBuilder> ReportBuilder::GetReportSpecificationBuilder()
{
   return m_pRptSpecBuilder;
}

std::shared_ptr<const ReportSpecificationBuilder> ReportBuilder::GetReportSpecificationBuilder() const
{
   return m_pRptSpecBuilder;
}

bool ReportBuilder::NeedsUpdate(const std::shared_ptr<const ReportHint> pHint, const std::shared_ptr<const ReportSpecification> pRptSpec) const
{
   std::vector<ChapterInfo> vchInfo = pRptSpec->GetChapterInfo();

   if ( m_pTitlePageBuilder.get() != nullptr && m_pTitlePageBuilder->NeedsUpdate(pHint,pRptSpec) )
   {
      return true;
   }

   for( const auto& chInfo : vchInfo)
   {
      auto pChBuilder = GetChapterBuilder( chInfo.Key.c_str() );
      if ( pChBuilder && pChBuilder->NeedsUpdate(pHint,pRptSpec,chInfo.MaxLevel) )
      {
         return true;
      }
   }

   return false;
}

std::shared_ptr<rptReport> ReportBuilder::CreateReport(const std::shared_ptr<const ReportSpecification> pRptSpec) const
{
   WBFL::System::Time start;

   std::shared_ptr<rptReport> pReport( std::make_shared<rptReport>(pRptSpec->GetReportName()) );

   if (m_headingNumbersEnabled)
   {
       pReport->EnableHeadingNumbers(true);
   }

   std::vector<ChapterInfo> vchInfo = pRptSpec->GetChapterInfo();

   for( const auto& chInfo : vchInfo)
   {
      auto pChBuilder = GetChapterBuilder( chInfo.Key.c_str() );
      if ( pChBuilder )
      {
         rptChapter* pChapter = pChBuilder->Build( pRptSpec, chInfo.MaxLevel );
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

   WBFL::System::Time end;
   if ( m_bIncludeTimingChapter )
   {
      TimeChapterBuilder timeChapterBuilder;
      rptChapter* pChapter = timeChapterBuilder.Build(start,end);
      (*pReport) << pChapter;
   }

   return pReport;
}

void ReportBuilder::EnableHeadingNumbers(bool enabled)
{
    m_headingNumbersEnabled = enabled;
}

bool ReportBuilder::HeadingNumbersEnabled() const
{
    return m_headingNumbersEnabled;
}

void ReportBuilder::SetMenuBitmap(const CBitmap* pBmp)
{
   m_pBitmap = pBmp;
}

const CBitmap* ReportBuilder::GetMenuBitmap()
{
   return m_pBitmap;
}

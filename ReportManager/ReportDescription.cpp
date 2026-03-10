///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
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

#include "stdafx.h"
#include "ReportManager.h"
#include <ReportManager\ReportDescription.h>
#include <ReportManager\ChapterBuilder.h>
#include <ReportManager\ReportSpecification.h>


using namespace WBFL::Reporting;

ReportDescription::ReportDescription(const std::_tstring& strReportName) :
m_ReportName(strReportName)
{

}

const std::_tstring& ReportDescription::GetReportName() const
{
   return m_ReportName;
}

void ReportDescription::AddChapter(const std::shared_ptr<const ChapterBuilder>& pChapterBuilder)
{
   m_ChapterBuilders.push_back(pChapterBuilder);
}

IndexType ReportDescription::GetChapterCount() const
{
   return m_ChapterBuilders.size();
}

std::vector<ChapterInfo> ReportDescription::GetChapterInfo() const
{
   std::vector<ChapterInfo> v;

   for( const auto& pChBuilder : m_ChapterBuilders)
   {
      ChapterInfo chInfo;
      chInfo.Name     = pChBuilder->GetName();
      chInfo.Key      = pChBuilder->GetKey();
      chInfo.MaxLevel = pChBuilder->GetMaxLevel();
      chInfo.Select   = pChBuilder->Select();

      v.push_back(chInfo);
   }

   return v;
}

void ReportDescription::ConfigureReportSpecification(std::shared_ptr<ReportSpecification>& pRptSpec) const
{
   std::vector<ChapterInfo> vChInfo = GetChapterInfo();

   pRptSpec->ClearChapters();

   for( const auto& chInfo : vChInfo)
   {
      if (chInfo.Select)
      {
         pRptSpec->AddChapter(chInfo.Name.c_str(),chInfo.Key.c_str(),chInfo.MaxLevel);
      }
   }
}

void ReportDescription::ConfigureReportSpecification(const std::vector<std::_tstring>& chList, std::shared_ptr<ReportSpecification>& pRptSpec) const
{
   std::vector<ChapterInfo> vChInfo = GetChapterInfo();

   pRptSpec->ClearChapters();

   for( const auto& strChKey : chList)
   {
      ChapterInfo search;
      search.Key= strChKey;

      std::vector<ChapterInfo>::iterator found = std::find(vChInfo.begin(),vChInfo.end(),search);
      ASSERT( found != vChInfo.end() ); // if this fires, the supplied chapter list isn't consistent with the report description
      ChapterInfo chInfo = *found;
      ASSERT( chInfo.Key == strChKey);
      pRptSpec->AddChapter(chInfo.Name.c_str(),chInfo.Key.c_str(),chInfo.MaxLevel);
   }
}

void ReportDescription::ConfigureReportSpecification(const std::vector<ChapterInfo>& vChInfo, std::shared_ptr<ReportSpecification>& pRptSpec) const
{
   pRptSpec->ClearChapters();

   for( const auto& chInfo : vChInfo)
   {
      pRptSpec->AddChapter(chInfo.Name.c_str(),chInfo.Key.c_str(),chInfo.MaxLevel);
   }
}

///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2015  Washington State Department of Transportation
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

// ReportDescription.cpp: implementation of the CReportDescription class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportManager.h"
#include <ReportManager\ReportDescription.h>
#include <ReportManager\ChapterBuilder.h>
#include <ReportManager\ReportSpecification.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportDescription::CReportDescription(LPCTSTR strReportName) :
m_ReportName(strReportName)
{

}

CReportDescription::~CReportDescription()
{

}

LPCTSTR CReportDescription::GetReportName() const
{
   return m_ReportName.c_str();
}

void CReportDescription::AddChapter(const CChapterBuilder* pChapterBuilder)
{
   m_ChapterBuilders.push_back(pChapterBuilder);
}

std::vector<CChapterInfo> CReportDescription::GetChapterInfo() const
{
   std::vector<CChapterInfo> v;

   BOOST_FOREACH(const CChapterBuilder* pChBuilder,m_ChapterBuilders)
   {
      CChapterInfo chInfo;
      chInfo.Name     = pChBuilder->GetName();
      chInfo.Key      = pChBuilder->GetKey();
      chInfo.MaxLevel = pChBuilder->GetMaxLevel();
      chInfo.Select   = pChBuilder->Select();

      v.push_back(chInfo);
   }

   return v;
}

void CReportDescription::ConfigureReportSpecification(boost::shared_ptr<CReportSpecification>& pRptSpec) const
{
   std::vector<CChapterInfo> vChInfo = GetChapterInfo();

   BOOST_FOREACH(const CChapterInfo& chInfo,vChInfo)
   {
      if (chInfo.Select)
      {
         pRptSpec->AddChapter(chInfo.Name.c_str(),chInfo.Key.c_str(),chInfo.MaxLevel);
      }
   }
}

void CReportDescription::ConfigureReportSpecification(const std::vector<std::_tstring>& chList,boost::shared_ptr<CReportSpecification>& pRptSpec) const
{
   std::vector<CChapterInfo> vChInfo = GetChapterInfo();

   BOOST_FOREACH(const std::_tstring& strChName,chList)
   {
      CChapterInfo search;
      search.Name = strChName;

      std::vector<CChapterInfo>::iterator found = std::find(vChInfo.begin(),vChInfo.end(),search);
      ATLASSERT( found != vChInfo.end() ); // if this fires, the supplied chapter list isn't consistent with the report description
      CChapterInfo chInfo = *found;
      ATLASSERT( chInfo.Name == strChName);
      pRptSpec->AddChapter(chInfo.Name.c_str(),chInfo.Key.c_str(),chInfo.MaxLevel);
   }
}

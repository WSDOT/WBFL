///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2010  Washington State Department of Transportation
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
#include <Reporter\Reporter.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportBuilder::CReportBuilder(const char* strName,bool bHidden) :
m_Name(strName),
m_bHidden(bHidden),
m_pRptSpecBuilder( new CReportSpecificationBuilder )
{
   m_pBitmap = NULL;
}

CReportBuilder::~CReportBuilder()
{

}

const char* CReportBuilder::GetName() const
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

void CReportBuilder::AddTitlePageBuilder(boost::shared_ptr<CTitlePageBuilder>& pTitlePageBuilder)
{
   m_pTitlePageBuilder = pTitlePageBuilder;
}

void CReportBuilder::AddChapterBuilder(boost::shared_ptr<CChapterBuilder>& pChapterBuilder)
{
   m_ChapterBuilders.push_back( pChapterBuilder );
}

Uint16 CReportBuilder::GetChapterBuilderCount() const
{
   return m_ChapterBuilders.size();
}

boost::shared_ptr<CChapterBuilder> CReportBuilder::GetChapterBuilder(Uint16 idx)
{
   return m_ChapterBuilders[idx];
}

boost::shared_ptr<CChapterBuilder> CReportBuilder::GetChapterBuilder(const char* strKey)
{
   ChapterBuilderContainer::iterator iter;
   for ( iter = m_ChapterBuilders.begin(); iter != m_ChapterBuilders.end(); iter++ )
   {
      boost::shared_ptr<CChapterBuilder> pChBuilder = (*iter);
      if ( std::string(pChBuilder->GetKey()) == std::string(strKey) )
         return pChBuilder;
   }

   return boost::shared_ptr<CChapterBuilder>();
}

CReportDescription CReportBuilder::GetReportDescription()
{
   CReportDescription rptDesc(m_Name.c_str());

   ChapterBuilderContainer::iterator iter;
   for ( iter = m_ChapterBuilders.begin(); iter < m_ChapterBuilders.end(); iter++ )
   {
      const CChapterBuilder* pBuilder = (*iter).get();
      rptDesc.AddChapter( pBuilder );
   }

   return rptDesc;
}

void CReportBuilder::SetReportSpecificationBuilder(boost::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder)
{
   m_pRptSpecBuilder = pRptSpecBuilder;
}

boost::shared_ptr<CReportSpecificationBuilder> CReportBuilder::GetReportSpecificationBuilder()
{
   return m_pRptSpecBuilder;
}

boost::shared_ptr<rptReport> CReportBuilder::CreateReport(boost::shared_ptr<CReportSpecification>& pRptSpec)
{
   boost::shared_ptr<rptReport> pReport( new rptReport(pRptSpec->GetReportName()) );
   std::vector<CChapterInfo> vchInfo = pRptSpec->GetChapterInfo();

   if ( m_pTitlePageBuilder.get() )
   {
      rptChapter* pTitlePage = m_pTitlePageBuilder->Build( pRptSpec );
      (*pReport) << pTitlePage;
   }

   std::vector<CChapterInfo>::iterator iter;
   for ( iter = vchInfo.begin(); iter != vchInfo.end(); iter++ )
   {
      CChapterInfo chInfo = *iter;
      boost::shared_ptr<CChapterBuilder> pChBuilder = GetChapterBuilder( chInfo.Key.c_str() );
      rptChapter* pChapter = pChBuilder->Build( pRptSpec.get(), chInfo.MaxLevel );
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

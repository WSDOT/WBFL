///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2017  Washington State Department of Transportation
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

// ReportBuilder.h: interface for the CReportBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTBUILDER_H__07C5A21D_72E4_4142_879F_F3432E8ECF60__INCLUDED_)
#define AFX_REPORTBUILDER_H__07C5A21D_72E4_4142_879F_F3432E8ECF60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ReportManager\ReportManagerExp.h>
#include <ReportManager\ChapterBuilder.h>
#include <ReportManager\TitlePageBuilder.h>
#include <ReportManager\ReportSpecificationBuilder.h>



class rptReport;

class REPORTMANAGERCLASS CReportBuilder  
{
public:
	CReportBuilder(LPCTSTR strName,bool bHidden = false,bool bIncludeTimingChapter=false);
	virtual ~CReportBuilder();

   // report builders may be hidden so that they don't show up in
   // lists of available reports
   void Hidden(bool bHide);
   bool Hidden() const;

   void IncludeTimingChapter(bool bInclude=true);
   bool IncludeTimingChapter() const;

   LPCTSTR GetName() const;
   void AddTitlePageBuilder(std::shared_ptr<CTitlePageBuilder>& pTitlePageBuilder);
   std::shared_ptr<CTitlePageBuilder> GetTitlePageBuilder();
   void AddChapterBuilder(std::shared_ptr<CChapterBuilder>& pChapterBuilder);
   bool InsertChapterBuilder(std::shared_ptr<CChapterBuilder>& pChapterBuilder,LPCTSTR strAfterChapter);
   bool RemoveChapterBuilder(LPCTSTR lpszChapterName);
   CollectionIndexType GetChapterBuilderCount() const;
   std::shared_ptr<CChapterBuilder> GetChapterBuilder(CollectionIndexType idx);
   std::shared_ptr<CChapterBuilder> GetChapterBuilder(LPCTSTR strKey);
   CReportDescription GetReportDescription();
   void SetReportSpecificationBuilder(std::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder);
   std::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder();
   
   virtual std::shared_ptr<rptReport> CreateReport(std::shared_ptr<CReportSpecification>& pRptSpec);

   void SetMenuBitmap(const CBitmap* pBmp);
   const CBitmap* GetMenuBitmap();

   virtual bool NeedsUpdate(CReportHint* pHint, std::shared_ptr<CReportSpecification>& pRptSpec);

private:
   std::_tstring m_Name;
   bool m_bHidden;
   bool m_bIncludeTimingChapter;
   const CBitmap* m_pBitmap;

   std::shared_ptr<CTitlePageBuilder> m_pTitlePageBuilder;
   std::shared_ptr<CReportSpecificationBuilder> m_pRptSpecBuilder;

   typedef std::vector<std::shared_ptr<CChapterBuilder>> ChapterBuilderContainer;
   ChapterBuilderContainer m_ChapterBuilders;
};

#endif // !defined(AFX_REPORTBUILDER_H__07C5A21D_72E4_4142_879F_F3432E8ECF60__INCLUDED_)

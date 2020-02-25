///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2020  Washington State Department of Transportation
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

// ChapterBuilder.h: interface for the CChapterBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAPTERBUILDER_H__9B2BF99A_0562_4755_8CA3_C657F931390E__INCLUDED_)
#define AFX_CHAPTERBUILDER_H__9B2BF99A_0562_4755_8CA3_C657F931390E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ReportManager\ReportManagerExp.h>
#include <ReportManager\ReportSpecification.h>
#include <ReportManager\ReportHint.h>

class rptChapter;

class REPORTMANAGERCLASS CChapterBuilder  
{
public:
	CChapterBuilder();
	virtual ~CChapterBuilder();

   virtual LPCTSTR GetKey() const;
   virtual LPCTSTR GetName() const = 0;
   virtual Uint16 GetMaxLevel() const = 0;
   virtual bool Select() const = 0; // return true if this chapter is to be selected by default
   virtual rptChapter* Build(CReportSpecification* pRptSpec,Uint16 level) const = 0;
   virtual CChapterBuilder* Clone() const = 0;
   virtual bool NeedsUpdate(CReportHint* pHint,CReportSpecification* pRptSpec,Uint16 level) const;
};

#endif // !defined(AFX_CHAPTERBUILDER_H__9B2BF99A_0562_4755_8CA3_C657F931390E__INCLUDED_)

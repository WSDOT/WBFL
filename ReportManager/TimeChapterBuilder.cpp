///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2022  Washington State Department of Transportation
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

// ChapterBuilder.cpp: implementation of the CChapterBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportManager.h"
#include <ReportManager\TimeChapterBuilder.h>
#include <Reporter\Chapter.h>
#include <Reporter\RcFlowModifier.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimeChapterBuilder::CTimeChapterBuilder()
{
}

CTimeChapterBuilder::~CTimeChapterBuilder()
{

}
LPCTSTR CTimeChapterBuilder::GetName() const
{
   return _T("Reporting Time");
}

Uint16 CTimeChapterBuilder::GetMaxLevel() const
{
   return 1;
}

bool CTimeChapterBuilder::Select() const
{
   return true;
}

rptChapter* CTimeChapterBuilder::Build(CReportSpecification* pRptSpec,Uint16 level) const
{
   ATLASSERT(false); // don't call this method
   rptChapter* pChapter = new rptChapter(GetName());
   rptParagraph* pPara = new rptParagraph;
   *pPara << _T("DON'T CALL THE STANDARD BUILD METHOD") << rptNewLine;
   return pChapter;
}

rptChapter* CTimeChapterBuilder::Build(sysTime& start,sysTime& end) const
{
   Uint32 elapsedTime = end.Seconds() - start.Seconds();
   rptChapter* pChapter = new rptChapter(GetName());
   rptParagraph* pPara = new rptParagraph;
   *pChapter << pPara;
   *pPara << _T("Elapsed Time = ") << elapsedTime << _T(" sec") << rptNewLine;
   return pChapter;
}

CChapterBuilder* CTimeChapterBuilder::Clone() const
{
   return new CTimeChapterBuilder;
}

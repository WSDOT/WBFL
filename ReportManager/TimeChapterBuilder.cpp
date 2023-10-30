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
#include <ReportManager\TimeChapterBuilder.h>
#include <Reporter\Chapter.h>
#include <Reporter\RcFlowModifier.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace WBFL::Reporting;

LPCTSTR TimeChapterBuilder::GetName() const
{
   return _T("Reporting Time");
}

Uint16 TimeChapterBuilder::GetMaxLevel() const
{
   return 1;
}

bool TimeChapterBuilder::Select() const
{
   return true;
}

rptChapter* TimeChapterBuilder::Build(const std::shared_ptr<const ReportSpecification>& pRptSpec,Uint16 level) const
{
   ATLASSERT(false); // don't call this method
   rptChapter* pChapter = new rptChapter(GetName());
   rptParagraph* pPara = new rptParagraph;
   *pPara << _T("DON'T CALL THE STANDARD BUILD METHOD") << rptNewLine;
   return pChapter;
}

rptChapter* TimeChapterBuilder::Build(WBFL::System::Time& start, WBFL::System::Time& end) const
{
   Uint32 elapsedTime = end.Seconds() - start.Seconds();
   rptChapter* pChapter = new rptChapter(GetName());
   rptParagraph* pPara = new rptParagraph;
   *pChapter << pPara;
   *pPara << _T("Elapsed Time = ") << elapsedTime << _T(" sec") << rptNewLine;
   return pChapter;
}

std::unique_ptr<ChapterBuilder> TimeChapterBuilder::Clone() const
{
   return std::make_unique<TimeChapterBuilder>();
}

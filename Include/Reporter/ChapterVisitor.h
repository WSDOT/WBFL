///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright � 1999-2025  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_CHAPTERVISITOR_H_
#define INCLUDED_REPORTER_CHAPTERVISITOR_H_
#pragma once

#include <Reporter\ReporterExp.h>

class REPORTERCLASS rptChapter;

/// Abstract class for visiting a chapter in a report.
class REPORTERCLASS rptChapterVisitor
{
public:
   rptChapterVisitor();
   virtual ~rptChapterVisitor();

   /// Visit a chapter
   virtual void VisitChapter(rptChapter* pChapter) = 0;

private:
   rptChapterVisitor(const rptChapterVisitor&) = delete;
   rptChapterVisitor& operator=(const rptChapterVisitor&) = delete;
};

#endif // INCLUDED_REPORTER_CHAPTERVISITOR_H_

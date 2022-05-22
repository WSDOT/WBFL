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

// TimeChapterBuilder.h
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <ReportManager\ReportManagerExp.h>
#include <ReportManager\ChapterBuilder.h>
#include <System\Time.h>

class REPORTMANAGERCLASS CTimeChapterBuilder : public CChapterBuilder
{
public:
	CTimeChapterBuilder();
	virtual ~CTimeChapterBuilder();

   virtual LPCTSTR GetName() const override;
   virtual Uint16 GetMaxLevel() const override;
   virtual bool Select() const override; // return true if this chapter is to be selected by default
   virtual rptChapter* Build(CReportSpecification* pRptSpec,Uint16 level) const override;
   virtual rptChapter* Build(WBFL::System::Time& start, WBFL::System::Time& end) const;
   virtual CChapterBuilder* Clone() const override;
};

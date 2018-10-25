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

// ReportDescription.h: interface for the CReportDescription class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTDESCRIPTION_H__D25A0902_EA73_40C0_AD7A_336442C2A746__INCLUDED_)
#define AFX_REPORTDESCRIPTION_H__D25A0902_EA73_40C0_AD7A_336442C2A746__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ReportManager\ReportManagerExp.h>

class CChapterBuilder;

class REPORTMANAGERCLASS CChapterInfo
{
public:
   std::string Name;
   std::string Key;
   Uint16 MaxLevel;

   CChapterInfo() { Name = "Bad Chapter Name"; Key = "Bad Chapter Key"; MaxLevel = 0; }
   CChapterInfo(const CChapterInfo& other): Name(other.Name), Key(other.Key), MaxLevel(other.MaxLevel) {}

   bool operator==(const CChapterInfo& other) const
   {
      return (Name == other.Name ? true : false);
   }
};

class REPORTMANAGERCLASS CReportDescription  
{
public:
	CReportDescription(const char* strRptName);
	virtual ~CReportDescription();

   const char* GetReportName() const;
   void AddChapter(const CChapterBuilder* pChapterBuilder);
   std::vector<CChapterInfo> GetChapterInfo() const;

private:
   std::string m_ReportName;
   std::vector<const CChapterBuilder*> m_ChapterBuilders; // do not delete these pointers
};

#endif // !defined(AFX_REPORTDESCRIPTION_H__D25A0902_EA73_40C0_AD7A_336442C2A746__INCLUDED_)

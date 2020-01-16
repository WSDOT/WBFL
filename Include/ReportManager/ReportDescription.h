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

// ReportDescription.h: interface for the CReportDescription class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <ReportManager\ReportManagerExp.h>
#include <string>
#include <vector>

#include <memory>


class CChapterBuilder;
class CReportSpecification;

class REPORTMANAGERCLASS CChapterInfo
{
public:
   std::_tstring Name;
   std::_tstring Key;
   Uint16 MaxLevel;
   bool Select;

   CChapterInfo() { Name = _T("Bad Chapter Name"); Key = _T("Bad Chapter Key"); MaxLevel = 0; Select = true;}
   CChapterInfo(const CChapterInfo& other): Name(other.Name), Key(other.Key), MaxLevel(other.MaxLevel), Select(other.Select) {}

   bool operator==(const CChapterInfo& other) const
   {
      return (Name == other.Name ? true : false);
   }
};

class REPORTMANAGERCLASS CReportDescription  
{
public:
	CReportDescription(LPCTSTR strRptName);
	virtual ~CReportDescription();

   LPCTSTR GetReportName() const;
   void AddChapter(const CChapterBuilder* pChapterBuilder);
   std::vector<CChapterInfo> GetChapterInfo() const;
   IndexType GetChapterCount() const;

   void ConfigureReportSpecification(std::shared_ptr<CReportSpecification>& pRptSpec) const;
   void ConfigureReportSpecification(const std::vector<CChapterInfo>& vChInfo, std::shared_ptr<CReportSpecification>& pRptSpec) const;
   void ConfigureReportSpecification(const std::vector<std::_tstring>& chList, std::shared_ptr<CReportSpecification>& pRptSpec) const;

private:
   std::_tstring m_ReportName;
   std::vector<const CChapterBuilder*> m_ChapterBuilders; // do not delete these pointers
};

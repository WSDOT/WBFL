///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <ReportManager\ReportSpecification.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace WBFL::Reporting;

ReportSpecification::ReportSpecification(const std::_tstring& strReportName) :
   m_ReportName(strReportName)
{
}

void ReportSpecification::SetReportName(const std::_tstring& strName)
{
   m_ReportName = strName;
}

const std::_tstring& ReportSpecification::GetReportName() const
{
   return m_ReportName;
}

std::_tstring ReportSpecification::GetReportTitle() const
{
   auto context = GetReportContextString();
   if(context.empty())
      return GetReportName();
   else
      return GetReportName() + _T(" for ") + context;
}

std::_tstring ReportSpecification::GetReportContextString() const
{
   // blank string by default
   return std::_tstring();
}

void ReportSpecification::AddChapter(LPCTSTR strName,LPCTSTR strKey,Uint16 level)
{
   ChapterInfo chInfo;
   chInfo.Name = strName;
   chInfo.Key = strKey;
   chInfo.MaxLevel = level;
   m_Chapters.push_back(chInfo);
}

void ReportSpecification::SetChapterInfo(const std::vector<ChapterInfo>& chInfo)
{
   m_Chapters = chInfo;
}

const std::vector<ChapterInfo>& ReportSpecification::GetChapterInfo() const
{
   return m_Chapters;
}

IndexType ReportSpecification::GetChapterCount() const
{
   return m_Chapters.size();
}

void ReportSpecification::ClearChapters()
{
   m_Chapters.clear();
}


bool ReportSpecification::IsValid() const
{
   return true;
}

void ReportSpecification::SetLeftHeader(const std::_tstring& text)
{
   m_LeftHeader = text;
}

const std::_tstring& ReportSpecification::GetLeftHeader() const
{
   return m_LeftHeader;
}

void ReportSpecification::SetCenterHeader(const std::_tstring& text)
{
   m_CenterHeader = text;
}

const std::_tstring& ReportSpecification::GetCenterHeader() const
{
   return m_CenterHeader;
}

void ReportSpecification::SetLeftFooter(const std::_tstring& text)
{
   m_LeftFooter = text;
}

const std::_tstring& ReportSpecification::GetLeftFooter() const
{
   return m_LeftFooter;
}

void ReportSpecification::SetCenterFooter(const std::_tstring& text)
{
   m_CenterFooter = text;
}

const std::_tstring& ReportSpecification::GetCenterFooter() const
{
   return m_CenterFooter;
}

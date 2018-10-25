///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2016  Washington State Department of Transportation
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

// ReportSpecification.cpp: implementation of the CReportSpecification class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportManager.h"
#include <ReportManager\ReportSpecification.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportSpecification::CReportSpecification(LPCTSTR strReportName) :
m_ReportName(strReportName)
{

}

CReportSpecification::CReportSpecification(const CReportSpecification& other)
{
   m_ReportName = other.m_ReportName;
   m_Chapters = other.m_Chapters;

   m_LeftHeader = other.m_LeftHeader;
   m_CenterHeader = other.m_CenterHeader;
   m_LeftFooter = other.m_LeftFooter;
   m_CenterFooter = other.m_CenterFooter;
}

CReportSpecification::~CReportSpecification()
{

}

void CReportSpecification::SetReportName(LPCTSTR strName)
{
   m_ReportName = strName;
}

std::_tstring CReportSpecification::GetReportName() const
{
   return m_ReportName.c_str();
}

std::_tstring CReportSpecification::GetReportTitle() const
{
   return GetReportName();
}

void CReportSpecification::AddChapter(LPCTSTR strName,LPCTSTR strKey,Uint16 level)
{
   CChapterInfo chInfo;
   chInfo.Name = strName;
   chInfo.Key = strKey;
   chInfo.MaxLevel = level;
   m_Chapters.push_back(chInfo);
}

void CReportSpecification::SetChapterInfo(const std::vector<CChapterInfo>& chInfo)
{
   m_Chapters = chInfo;
}

std::vector<CChapterInfo> CReportSpecification::GetChapterInfo() const
{
   return m_Chapters;
}

IndexType CReportSpecification::GetChapterCount() const
{
   return m_Chapters.size();
}

HRESULT CReportSpecification::Validate() const
{
   return S_OK;
}

void CReportSpecification::SetLeftHeader(LPCTSTR text)
{
   m_LeftHeader = text;
}

std::_tstring CReportSpecification::GetLeftHeader() const
{
   return m_LeftHeader;
}

void CReportSpecification::SetCenterHeader(LPCTSTR text)
{
   m_CenterHeader = text;
}

std::_tstring CReportSpecification::GetCenterHeader() const
{
   return m_CenterHeader;
}

void CReportSpecification::SetLeftFooter(LPCTSTR text)
{
   m_LeftFooter = text;
}

std::_tstring CReportSpecification::GetLeftFooter() const
{
   return m_LeftFooter;
}

void CReportSpecification::SetCenterFooter(LPCTSTR text)
{
   m_CenterFooter = text;
}

std::_tstring CReportSpecification::GetCenterFooter() const
{
   return m_CenterFooter;
}

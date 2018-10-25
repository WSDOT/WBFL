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

CReportSpecification::CReportSpecification(const char* strReportName) :
m_ReportName(strReportName)
{

}

CReportSpecification::~CReportSpecification()
{

}

std::string CReportSpecification::GetReportName() const
{
   return m_ReportName.c_str();
}

std::string CReportSpecification::GetReportTitle() const
{
   return GetReportName();
}

void CReportSpecification::AddChapter(const char* strName,const char* strKey,Uint16 level)
{
   CChapterInfo chInfo;
   chInfo.Name = strName;
   chInfo.Key = strKey;
   chInfo.MaxLevel = level;
   m_Chapters.push_back(chInfo);
}

std::vector<CChapterInfo> CReportSpecification::GetChapterInfo() const
{
   return m_Chapters;
}

HRESULT CReportSpecification::Validate() const
{
   return S_OK;
}

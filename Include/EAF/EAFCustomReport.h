///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

// EAFCustomReport.h : implementation file
//
#pragma once 

#include <EAF\EAFExp.h>
#include <set>
#include "intsafe.h" // for SHORT_MAX

// Simple data classes for storing custom report data

class EAFCLASS CEAFCustomReport
{
   // basically a simple struct with some member functions
public:
   std::_tstring m_ReportName;

   // name of report we are based on
   std::_tstring m_ParentReportName;

   std::vector<std::_tstring> m_Chapters;

public:

   // For life in a set
   bool operator<(const CEAFCustomReport& rOther) const 
   { 
      return m_ReportName < rOther.m_ReportName;
   }
};


// A collection of custom reports
class EAFCLASS CEAFCustomReports
{
public:
   typedef std::set<CEAFCustomReport> ReportContainer;
   typedef ReportContainer::iterator ReportIterator;
   typedef ReportContainer::const_iterator ReportConstIterator;
   ReportContainer m_Reports;

   void LoadFromRegistry(CWinApp* theApp);
   void SaveToRegistry(CWinApp* theApp) const;
 };

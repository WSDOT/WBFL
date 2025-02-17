///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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
   using ReportContainer = std::set<CEAFCustomReport>;
   using ReportIterator = ReportContainer::iterator;
   using ReportConstIterator = ReportContainer::const_iterator;
   ReportContainer m_Reports;

   void LoadFromRegistry(CWinApp* theApp);
   void SaveToRegistry(CWinApp* theApp) const;
 };

// A mix-in class to add custom reporting
// capabilities to an IEAFAppPlugin object
class EAFCLASS CEAFCustomReportMixin
{
public:
   CEAFCustomReportMixin();
   virtual ~CEAFCustomReportMixin();

   void SaveCustomReports(BOOL bSave);

   // Determine whether to display favorite reports or all reports in menu dropdowns
   BOOL DisplayFavoriteReports() const;
   void DisplayFavoriteReports(BOOL doDisplay);

   // Current list of favorite reports
   const std::vector<std::_tstring>& GetFavoriteReports() const;
   void SetFavoriteReports(const std::vector<std::_tstring>& reports);

   // Custom, user-defined reports
   const CEAFCustomReports& GetCustomReports() const;
   void SetCustomReports(const CEAFCustomReports& reports);

   // Loads and saves the custom report information in the registry.
   // Call these methods from IEAFAppPlugin::Init() and IEAFAppPlugin::Terminate().
   // Base class must call AFX_MANAGE_STATE(AfxGetStaticModuleState()) before
   // calling into these methods.
   virtual void LoadCustomReportInformation() = 0;
   virtual void SaveCustomReportInformation() = 0;

protected:
   BOOL m_bDisplayFavoriteReports;
   std::vector<std::_tstring> m_FavoriteReports;
   CEAFCustomReports m_CustomReports;

   BOOL m_bSaveCustomReports;
};
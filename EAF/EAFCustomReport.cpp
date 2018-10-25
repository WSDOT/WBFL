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
// EAFCustomReport.cpp : implementation file
//
#include "stdafx.h"
#include <EAF\EAFCustomReport.h>


void CEAFCustomReports::LoadFromRegistry(CWinApp* theApp)
{
   m_Reports.clear();

   HKEY hAppKey = theApp->GetAppRegistryKey();
   HKEY hSecKey = theApp->GetSectionKey(_T("CustomReports"));
   if ( hSecKey )
   {
      DWORD dwIndex = 0;
      TCHAR reportName[SHORT_MAX];
      TCHAR reportString[SHORT_MAX];
      DWORD type;
      while (true) 
      {
         DWORD reportNameSize = sizeof(reportName);
         DWORD reportStringSize = sizeof(reportString);
         LONG st = ::RegEnumValue(hSecKey,dwIndex++,&reportName[0],&reportNameSize,NULL,&type,(LPBYTE)&reportString[0],&reportStringSize);
         if (st== ERROR_NO_MORE_ITEMS)
         {
            // normal end
            break;
         }
         else if( st != ERROR_SUCCESS )
         {
            // hmm...
            ATLASSERT(0);
            break;
         }

         CEAFCustomReport report;
         report.m_ReportName = reportName;

         // Report data is tab separated
         sysTokenizer tokenizer(_T("\t"));
         tokenizer.push_back(reportString);
         if (tokenizer.size() > 0)
         {
            sysTokenizer::iterator it = tokenizer.begin();
            // name of parent report is first in list
            report.m_ParentReportName = *it++;

            if (!tokenizer.empty())
            {
               while( it != tokenizer.end() )
               {
                  report.m_Chapters.push_back( *it );
                  it++;
               }

               m_Reports.insert( report );
            }
            else
            {
               ATLASSERT(0); // Reports written to the registry should always have chapters.
            }
         }
         else
         {
            ATLASSERT(0); // should not have empty report string
         }
      };

      ::RegCloseKey(hSecKey);
   }

   ::RegCloseKey(hAppKey);
}

void CEAFCustomReports::SaveToRegistry(CWinApp* theApp) const
{
   HKEY hSecKey = theApp->GetSectionKey(_T("CustomReports"));
   if ( hSecKey )
   {
      LONG ret = RegDeleteTree(hSecKey,NULL);
      bool suc = ret==ERROR_SUCCESS;
      ::RegCloseKey(hSecKey);
   }

   ReportConstIterator iter;
   for ( iter = m_Reports.begin(); iter != m_Reports.end(); iter++ )
   {
      const CEAFCustomReport& rReport = *iter;

      // report names are stored as tab separated values. build string
      CString reportString(rReport.m_ParentReportName.c_str());
      std::vector<std::_tstring>::const_iterator it = rReport.m_Chapters.begin();
      while (it != rReport.m_Chapters.end())
      {
         reportString += _T("\t");
         reportString += it->c_str();

         it++;
      }

      CString key(rReport.m_ReportName.c_str());
      theApp->WriteProfileString(_T("CustomReports"), key, reportString);
   }
}

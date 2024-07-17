///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#ifndef INCLUDED_REPORTER_HTMLHELPER_H_
#define INCLUDED_REPORTER_HTMLHELPER_H_
#pragma once

#include <map>
#include <ostream>
#include <Reporter\ReporterExp.h>
#include <Reporter\FontStyleLibrary.h>

class rptRiStyle;
class rptPageLayout;
class rptReport;

/// This class contains helper functions to aid the htmlVisitor classses in getting their job done.
class REPORTERCLASS rptHtmlHelper
{
public:
   /// enum for chapters and paragraph anchor starting values. for toc generation
   /// 1000 chapters - should be a realistic limitation
   enum {ChapterStart=0, ParaStart=1000};

   enum class BrowserType
   {
      IE, // based on IWebBrowser2 control (Internet Explorer)
      Edge// based on WebView2 (Edge)
   };


   rptHtmlHelper(BrowserType type);

   /// Get stylistic information to put into HTML style block.
   static std::_tstring GetStyleString(const rptRiStyle& MyStyle);

   /// Get page layout information to put into HTML style block.
   static std::_tstring GetPageLayoutString(const rptPageLayout& MyLayout);

   /// Visit font library. Write library style information to the ostream, and set
   /// up style name - html element name mapping.
   void VisitFontLibrary(std::_tostream& os);

   /// Get html element name for a given style name (e.g., H1,H2...)
   /// string is returned empty if no name exists
   std::_tstring GetElementName(const rptStyleName& rstyleName) const;

   BrowserType GetBrowserType() const { return m_BrowserType; }

private:
   rptHtmlHelper();

   bool m_DidVisit;
   BrowserType m_BrowserType;

   using StyleElementMap = std::map<rptStyleName, std::_tstring, std::less<rptStyleName>>;
   StyleElementMap m_StyleElementMap;
   StyleElementMap m_headingStyleElementMap;
};

#endif // INCLUDED_REPORTER_HTMLHELPER_H_

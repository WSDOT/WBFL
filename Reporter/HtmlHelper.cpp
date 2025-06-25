///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include <Reporter\ReporterLib.h>
#include <Reporter\HtmlHelper.h>
#include <Reporter\PageLayout.h>
#include <Reporter\Report.h>
#include <Reporter\Paragraph.h>
#include <Reporter\RiStyle.h>
#include <Reporter\FontStyleLibrary.h>
#include <ostream>
#include <vector>


// a mapping list for fonts for html
// Note: This list is dependent of the order of the enum FontType in 
//       ReportingUtils.h - If you touch one, you bust the other
static LPCTSTR  HtmlFontList[] = { _T("Times"),      // - default (pot luck)
                                        _T("Times"),      // - typically times new roman
                                        _T("Arial"),      // - arial
                                        _T("Courier New"),    // - fixed pitch - courier
                                        _T("Symbol")};    // - symbol font (not portable)



rptHtmlHelper::rptHtmlHelper(BrowserType type):
   m_BrowserType(type)
{
   // no visits have happened yet
   m_DidVisit=false;
}

std::_tstring rptHtmlHelper::GetStyleString(const rptRiStyle& MyStyle)
{
   std::_tostringstream ms;

   Uint16 fs = MyStyle.GetFontSize();

   ms << "font-size: "<<fs<<"pt; ";

   // alignment
   rptRiStyle::AlignmentType my_align = MyStyle.GetAlignment();
   switch (my_align)
   {
   case rptRiStyle::LEFT:
        ms << "text-align: left; ";
        break;
   case rptRiStyle::RIGHT:
        ms << "text-align: right; ";
      break;
   case rptRiStyle::CENTER:
        ms << "text-align: center; ";
      break;
   case rptRiStyle::FULL:
        ms << "text-align: left; ";  // full not supported
      break;
   }

   // weight
   if (MyStyle.GetBold())
      ms << "font-weight: bold; ";
   else
      ms << "font-weight: normal; ";

   // italics
   if (MyStyle.GetItalic())
      ms << "font-style: italic; ";
   else
      ms << "font-style: normal; ";

   // underline
   if (MyStyle.GetUnderlined())
      ms << "text-decoration: underline; ";

   // overline
   if (MyStyle.GetOverlined())
      ms << "text-decoration: overline; ";

   // line-through
   if (MyStyle.GetLineThrough())
      ms << "text-decoration: line-through; ";

   // color
   rptRiStyle::FontColor mc = MyStyle.GetColor();
   if (rptRiStyle::Default != mc)
   {
      ms << "color: " << rptRiStyle::GetColorCode(mc) << "; ";
   }

   // background color
   // NOTE: This code causes grief when changing background color on the fly. Take out of class, and use an inline <span>
//   mc = MyStyle.GetBGColor();
//   ms << "background-color: " << rptRiStyle::GetColorCode(mc) << "; ";

   // Make margin space above if style is a heading
   if (MyStyle.IsHeading())
   {
      Uint16 marg = fs/3;
      ms << "margin-top: +" << marg <<"pt; white-space: nowrap; "; // don't allow headings to wrap
   }

   // family is last in list because of a 'feature' in IE
   ms << "font-family: " << HtmlFontList[MyStyle.GetFontType()] << "; ";

   return std::_tstring(ms.str());
}

std::_tstring rptHtmlHelper::GetPageLayoutString(const rptPageLayout& MyLayout)
{
   std::_tostringstream ms;
   ms<< "margin-left: "<< MyLayout.GetLeftMargin() <<"in; "
     << "margin-right: "<< MyLayout.GetRightMargin() <<"in;";

// top margin is of little use for screen documents
//   << "margin-top: "<< MyLayout.GetTopMargin() <<"in;";

   return std::_tstring(ms.str());
}

void rptHtmlHelper::VisitFontLibrary(std::_tostream& os)
{
   // different stream for each media type
   std::_tostringstream osPrint, osScreen, osBoth;

   // clear out the existing map if there is one
   m_StyleElementMap.clear();

   // get the font library singleton
   rptFontStyleLibrary* plib = rptFontStyleLibrary::Instance();

   // get a vector of all named styles in library
   std::vector<rptStyleName> svec;
   plib->GetStyleNames(svec);

   IndexType numels = svec.size();

   std::_tstring ss;

   // cycle over all styles add to style-element map and write out style-element mapping
   for (IndexType i = 0; i<numels; i++)
   {
      const rptRiStyle& style = plib->GetNamedStyle( svec[i] );

      ss = GetStyleString(style);
      std::_tstring mystr = svec[i];
      std::_tostringstream ms;
      ms << _T("S") << i;
      m_StyleElementMap.insert( std::pair<std::_tstring, std::_tstring> (mystr, ms.str()));
      if (i==0)
      {
         // body text has block of its own
         os << std::endl;
         os << _T("<style>") << std::endl;
         os << _T("   ") << _T("body") << _T(" {  background: white; }") << std::endl;
         os << _T("   ") << _T("P") << _T(" { margin: 0pt 0pt 0pt 0pt; ") << ss << _T(" }") << std::endl;

         // Tooltip for table caption copy tool
         os << _T("   ") << "/* Tooltip container - only active on screen */" << std::endl;
         os << _T("   ") << "P.tableCaptionToolTip{ text-decoration-line: underline; text-decoration-style: dotted;}" << std::endl;
         os << _T("   ") << "/* Table Caption ToolTip text */" << std::endl;
         os << _T("   ") << "P.tableCaptionToolTip .tableCaptionToolTiptext{ visibility: hidden; width:auto; background-color: rgb(78, 78, 78); color: #fff; text-align: center; padding: 5px 0; border-radius: 6px; position: absolute; z-index: 1; }" << std::endl;
         os << _T("   ") << "/* Show the ToolTip text when you mouse over the table caption container */" << std::endl;
         os << _T("   ") << "P.tableCaptionToolTip:hover .tableCaptionToolTiptext{visibility: visible;}" << std::endl;
         os << _T("</style>") << std::endl;
      }
      else
      {
         if ( style.GetMediaType() == rptRiStyle::Print )
         {
            // style only applies to print
            osPrint << _T("/* ") << mystr << _T(" */") << std::endl;
            osPrint << _T("   ") << _T("P.") << ms.str() << _T(" {") << ss << _T(" }") << std::endl;

            osScreen << _T("/* ") << mystr << _T(" */") << std::endl;
            osScreen << _T("   ") << _T("P.") << ms.str() << _T(" {display: none;} ") << std::endl;
         }
         else if ( style.GetMediaType() == rptRiStyle::Screen )
         {
            // style only applies to screen
            osScreen << _T("/* ") << mystr << _T(" */") << std::endl;
            osScreen << _T("   ") << _T("P.") << ms.str() << _T(" {") << ss << _T(" }") << std::endl;

            osPrint << _T("/* ") << mystr << _T(" */") << std::endl;
            osPrint << _T("   ") << _T("P.") << ms.str() << _T(" {display: none;} ") << std::endl;
         }
         else
         {
            // style applies to both
            osBoth << _T("/* ") << mystr << _T(" */") << std::endl;
            osBoth << _T("   ") << _T("P.") << ms.str() << _T(" {") << ss << _T(" }") << std::endl;
         }
      }
   }

   // cycle over all styles add to style-element map and write out style-element mapping
   std::_tstring hss;
 
   for (IndexType hLevel = 1; hLevel <= 6; hLevel++)
   {
       PRECONDITION(1 <= hLevel && hLevel <= 6);

       const rptRiStyle& style = plib->GetHeadingStyle(hLevel);

       hss = GetStyleString(style);


        if (style.GetMediaType() == rptRiStyle::Print)
        {
            // style only applies to print
            osPrint << _T("/* ") << _T(" */") << std::endl;
            osPrint << _T("   ") << _T("h") << hLevel << _T(" {") << hss << _T(" }") << std::endl;

            osScreen << _T("/* ") << _T(" */") << std::endl;
            osScreen << _T("   ") << _T("h") << hLevel << _T(" {display: none;} ") << std::endl;
        }
        else if (style.GetMediaType() == rptRiStyle::Screen)
        {
            // style only applies to screen
            osScreen << _T("/* ")  << _T(" */") << std::endl;
            osScreen << _T("   ") << _T("h") << hLevel << _T(" {") << hss << _T(" }") << std::endl;

            osPrint << _T("/* ") << _T(" */") << std::endl;
            osPrint << _T("   ") << _T("h") << hLevel << _T(" {display: none;} ") << std::endl;
        }
        else
        {
            // style applies to both
            osBoth << _T("/* ") << _T(" */") << std::endl;
            osBoth << _T("   ") << _T("h") << hLevel << _T(" {") << hss << _T(" }") << std::endl;
        }
   }

   os << std::endl;

   // We have styles for each media type. Now write to file with start-end info
   os << _T("<style media=\"print\">") << std::endl;
   os << _T("   ") << _T("THEAD {display: table-header-group;}") << std::endl;
   os << _T("   ") << _T("TFOOT {display: table-footer-group;}") << std::endl;
   os << std::endl;
   // tooltips don't show for print
   os << _T("   ") << _T("/* Tooltip container - do nothing for print */") << std::endl;
   os << _T("   ") << _T("P.tableCaptionToolTip{ text-decoration-line:none; }") << std::endl;
   os << _T("   ") << _T("P.tableCaptionToolTip .tableCaptionToolTiptext{ visibility: hidden; }") << std::endl;
   os << _T("   ") << _T("P.tableCaptionToolTip:hover .tableCaptionToolTiptext{ visibility: hidden; }") << std::endl;
   os << osPrint.str() << std::endl;
   os << _T("</style>") << std::endl;
   os << std::endl;

   os << _T("<style media=\"screen\">") << std::endl;
   os << osScreen.str() << std::endl;
   os << _T("</style>") << std::endl;
   os << std::endl;

   os << _T("<style>") << std::endl;
   os << osBoth.str() << std::endl;
   os << _T("</style>") << std::endl;
   os << std::endl;

   m_DidVisit = true;
}

std::_tstring rptHtmlHelper::GetElementName(const rptStyleName& rstyleName) const
{
   StyleElementMap::const_iterator it = m_StyleElementMap.find(rstyleName);
   if (it != m_StyleElementMap.end() )
      return (*it).second;
   else
   {
       StyleElementMap::const_iterator itx = m_headingStyleElementMap.find(rstyleName);
       if (itx != m_headingStyleElementMap.end())
           return (*itx).second;
       else
       {
           CHECKX(0, _T("Failed to find library entry"));
           return _T("BODY");
       }
   }
}

///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
#include <Reporter\RiStyle.h>
#include <Reporter\FontStyleLibrary.h>
#include <ostream>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptHtmlHelper
****************************************************************************/




// a mapping list for fonts for html
// Note: This list is dependent of the order of the enum FontType in 
//       ReportingUtils.h - If you touch one, you bust the other
static const char * HtmlFontList[] = { "Times",      // - default (pot luck)
                                       "Times",      // - typically times new roman
                                       "Arial",      // - arial
                                       "Courier New",    // - fixed pitch - courier
                                       "Symbol"};    // - symbol font (not portable)





////////////////////////// PUBLIC     ///////////////////////////////////////
//======================== LIFECYCLE  =======================================

rptHtmlHelper::rptHtmlHelper()
{
   // no visits have happened yet
   m_DidVisit=false;
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

//------------------------------------------------------------------------
//
// Get stylistic information to put into HTML style block.
std::string rptHtmlHelper::GetStyleString(const rptRiStyle& MyStyle)
{
   std::stringstream ms;

   ms << "font-size: "<<MyStyle.GetFontSize()<<"pt; ";

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
      ms << "font-weight: medium; ";

   // italics
   if (MyStyle.GetItalic())
      ms << "font-style: italic; ";
   else
      ms << "font-style: normal; ";

   // underline
   if (MyStyle.GetUnderlined())
      ms << "text-decoration: underline; ";

   // color
   rptRiStyle::FontColor mc = MyStyle.GetColor();
   ms << "color: " << rptRiStyle::GetColorCode(mc) << "; ";

   // background color
   mc = MyStyle.GetBGColor();
   ms << "background-color: " << rptRiStyle::GetColorCode(mc) << "; ";

   // family is last in list because of a 'feature' in IE
   ms << "font-family: " << HtmlFontList[MyStyle.GetFontType()] << "; ";

   return std::string(ms.str());
}
//------------------------------------------------------------------------
//
// Get page layout information to put into HTML style block.
std::string rptHtmlHelper::GetPageLayoutString(const rptPageLayout& MyLayout)
{
   std::stringstream ms;
   ms<< "margin-left: "<< MyLayout.GetLeftMargin() <<"in; "
     << "margin-right: "<< MyLayout.GetRightMargin() <<"in;";

// top margin is of little use for screen documents
//   << "margin-top: "<< MyLayout.GetTopMargin() <<"in;";

   return std::string(ms.str());
}

// a list of useable html elements.

void rptHtmlHelper::VisitFontLibrary(std::ostream& os)
{
   std::ostringstream osPrint, osScreen, osBoth;

   osPrint << "@media print" << std::endl;
   osPrint << "{" << std::endl;

   osScreen << "@media screen" << std::endl;
   osScreen << "{" << std::endl;

   osBoth << "@media screen,print" << std::endl;
   osBoth << "{" << std::endl;

   // clear out the existing map if there is one
   m_StyleElementMap.clear();

   // get the font library singleton
   rptFontStyleLibrary* plib = rptFontStyleLibrary::Instance();

   // write out the beginning of the style block
   os << std::endl;
   os << " <STYLE TYPE=\"text/css\">" << std::endl;

   // get a vector of all named styles in library
   std::vector<rptStyleName> svec;
   plib->GetStyleNames(svec);

   int numels = svec.size();

   std::string ss;

   // cycle over all styles add to style-element map and write out style-element mapping
   for (int i=0; i<numels; i++)
   {
      const rptRiStyle& style = plib->GetNamedStyle( svec[i] );

      ss = GetStyleString(style);
      std::string mystr = svec[i];
      std::stringstream ms;
      ms << "S" << i;
      m_StyleElementMap.insert( std::pair<std::string, std::string> (mystr, ms.str()));
      if (i==0) // body text
      {
         os << "   "<< "BODY" << " {  background: white; " << ss << 
            " display: block; }"<< std::endl;

         os << "   "<< "P" << " {  background: white; " << ss << 
            " display: block}"<< std::endl;
      }
      else
      {
         if ( style.GetMediaType() == rptRiStyle::Print )
         {
            // style only applies to print
            osPrint << "/* "<< mystr << " */" << std::endl;
            osPrint << "   "<< "P."<< ms.str() << " {" << ss << 
               " display: block" <<
               " margin-top: -1; margin-bottom: -2}"<< std::endl;

            osScreen << "/* "<< mystr << " */" << std::endl;
            osScreen << "   "<< "P."<< ms.str() << " {display: none}; " << std::endl;
         }
         else if ( style.GetMediaType() == rptRiStyle::Screen )
         {
            // style only applies to screen
            osScreen << "/* "<< mystr << " */" << std::endl;
            osScreen << "   "<< "P."<< ms.str() << " {" << ss << 
               " display: block" <<
               " margin-top: -1; margin-bottom: -2}"<< std::endl;

            osPrint << "/* "<< mystr << " */" << std::endl;
            osPrint << "   "<< "P."<< ms.str() << " {display: none}; " << std::endl;
         }
         else
         {
            // style applies to both
            osBoth << "/* "<< mystr << " */" << std::endl;
            osBoth << "   "<< "P."<< ms.str() << " {" << ss << 
               " display: block" <<
               " margin-top: -1; margin-bottom: -2}"<< std::endl;
         }
      }
   }

   osPrint << "}" << std::endl;
   osScreen << "}" << std::endl;
   osBoth << "}" << std::endl;

   os << osPrint.str() << std::endl;
   os << osScreen.str() << std::endl;
   os << osBoth.str() << std::endl;

   // end of style block
   os << " </STYLE>" << std::endl;
   m_DidVisit = true;
}

std::string rptHtmlHelper::GetElementName(const rptStyleName& rstyleName) const
{
   StyleElementMap::const_iterator it = m_StyleElementMap.find(rstyleName);
   if (it != m_StyleElementMap.end() )
      return (*it).second;
   else
   {
      CHECKX(0,"Failed to find library entry");
      return "BODY";
   }
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2021  Washington State Department of Transportation
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
#include <Reporter\HtmlParagraphVisitor.h>
#include <Reporter\PageLayout.h>
#include <Reporter\HtmlHelper.h>
#include <Reporter\HtmlRcVisitor.h>
#include <Reporter\RiStyle.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptHtmlParagraphVisitor
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptHtmlParagraphVisitor::rptHtmlParagraphVisitor(std::_tostream* pMyOstream, 
                                                 const rptPageLayout*   MypPageLayout,
                                                 const rptHtmlHelper&   rmyHelper,
                                                 Uint32 logPixelsX,
                                                 Uint32 logPixelsY):
   rptOutputParagraphVisitor( pMyOstream ),
   m_Helper(rmyHelper),
   m_CurrAnchor(rptHtmlHelper::ParaStart),
   m_LogPixelsX(logPixelsX),
   m_LogPixelsY(logPixelsY)
{
   CHECK(MypPageLayout);
   m_pPageLayout = MypPageLayout;
}


rptHtmlParagraphVisitor::~rptHtmlParagraphVisitor()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rptHtmlParagraphVisitor::VisitParagraph(rptParagraph* pPara)
{
   bool lib_style = false;

   // get the paragraph's style name
   rptStyleName style = pPara->GetStyleName();
   // get corresponding element name for style name
   std::_tstring el_name = m_Helper.GetElementName(style);

   // create a hypertext anchor for this chapter - to be placed in toc
   LPCTSTR name = pPara->GetName();
   if (name!=0)
   {
      Uint32 anchor = GetNextAnchor();
      std::_tstring sname(name);
      *m_pOstream<< _T("<A ID=\"_") << anchor << _T("\" TITLE=\"") << sname << _T("\" NAME=\"_") << anchor << _T("\">");
   }

   // Default styles use the <P> style
   if (style == _T("Default"))
      *m_pOstream << _T("<P>");
   else
   {
      *m_pOstream << _T("<P CLASS=") << el_name << _T(">");
      lib_style=true;
   }

   // bullets - need to pull style from library

   // get the font library singleton
   rptFontStyleLibrary* plib = rptFontStyleLibrary::Instance();
   const rptRiStyle& rstyle = plib->GetNamedStyle(style);

   rptRiStyle::BulletType my_btype = rstyle.GetBullet();
   switch (my_btype)
   {
   case rptRiStyle::DASH:
      *m_pOstream << _T("<UL><LI>")<<std::endl; // dash doesn't work in html
      break;
   case rptRiStyle::ROUND:
      *m_pOstream << _T("<UL><LI>")<<std::endl;
      break;
   }

   // background color
   rptRiStyle::FontColor bg_color = rstyle.GetBGColor();
   if (rptRiStyle::Default != bg_color)
   {
      *m_pOstream << _T("<SPAN STYLE=\"background-color: ") << rptRiStyle::GetColorCode(bg_color) << _T("\">");
   }


   // borders dont work for html
   // TODO:could try table later if paragraph borders are really needed

   // create a report content visitor
   rptHtmlRcVisitor my_visitor(m_pOstream, m_pPageLayout, m_Helper, m_LogPixelsX, m_LogPixelsY);

   // iterate over all report content 
   rptParagraph::ConstParagraphContentIterator pci;
   for (pci=pPara->ConstBegin(); pci!=pPara->ConstEnd(); pci++)
   {
      (*pci)->Accept( my_visitor );
   }

   if (rptRiStyle::Default != bg_color)
   {
      *m_pOstream << _T("</SPAN>");
   }


   // close out bullet if needed
   if (my_btype != rptRiStyle::NOBULLET)
      *m_pOstream << _T("</LI></UL>")<<std::endl;
   else

   // send paragraph end
   if (!lib_style)
      *m_pOstream << _T("</P>")<<std::endl;
   else
      // only "Hn" elements include a line break
      *m_pOstream << _T("</P>")<< std::endl;



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


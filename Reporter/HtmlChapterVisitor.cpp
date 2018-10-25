///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#include <Reporter\ReporterLib.h>
#include <Reporter\HtmlChapterVisitor.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
CLASS
   rptHtmlChapterVisitor
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

rptHtmlChapterVisitor::rptHtmlChapterVisitor(std::_tostream* pMyOstream, /*const rptUnitSnapShot* MypUnitSnapShot,*/
                     const rptHtmlHelper& rmyHelper,
                     Uint32 logPixelsX,Uint32 logPixelsY):
   rptOutputChapterVisitor(pMyOstream/*, MypUnitSnapShot*/),
   m_Helper(rmyHelper),
   m_CurrAnchor(0),
   m_CurrParagraphAnchor(rptHtmlHelper::ParaStart),
   m_LogPixelsX(logPixelsX),
   m_LogPixelsY(logPixelsY)
{
}

rptHtmlChapterVisitor::~rptHtmlChapterVisitor()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void rptHtmlChapterVisitor::VisitChapter(rptChapter* pChapter)
{
   // Eject page if requested
   if (pChapter->GetEjectPageBreakBefore())
   {
      *m_pOstream << _T("<DIV STYLE=\"page-break-after: always\"><BR></DIV>")<<std::endl;
   }

   // treat chapters like an Html DIV
   // do page sizing and layout

   const rptPageLayout* pr_layout = pChapter->GetpPageLayout();

/*  KLUDGE: Due to a feature in Internet Explorer. Page margins are additive.
            Don't deal with page layouts in chapters for now.
            If you fix this, make sure to uncomment </DIV> at bottom also. -rdp 6/97

   // get the current page layout and send out page layout html

   *m_pOstream << "<DIV STYLE=\""
      << rptHtmlHelper::GetPageLayoutString(*pr_layout)
      << "\">"<<std::endl;
*/

   // create a hypertext anchor for this chapter - to be placed in toc
   LPCTSTR name = pChapter->GetName();
   if (name!=0)
   {
      Uint32 anchor = GetNextAnchor();
      std::_tstring sname(name);
      *m_pOstream<<_T("<A ID=\"_")<<anchor<<_T("\" TITLE=\"")<<sname<<_T("\" NAME=\"_")<<anchor<<_T("\">");
   }
   // create a paragraph visitor
   rptHtmlParagraphVisitor my_visitor(m_pOstream, /*m_pUnitSnapShot,*/ pr_layout, m_Helper, m_LogPixelsX, m_LogPixelsY);
   my_visitor.SetLastAnchor(m_CurrParagraphAnchor);

   // deal with page headers and footers

   // No Headers or Footers in Html


   // iterate over all paragraphs in the chapter
 
   rptChapter::ConstChapterParagraphIterator pci;
   for (pci=pChapter->ConstBegin(); pci!=pChapter->ConstEnd(); pci++)
   {

      (*pci)->Accept( my_visitor );

   }

   // get current paragraph anchor 
   m_CurrParagraphAnchor = my_visitor.GetLastAnchor();

   // close off chapter settings

//   *m_pOstream << "</DIV>";

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


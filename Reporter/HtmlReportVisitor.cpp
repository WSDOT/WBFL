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

#include <Reporter\ReporterLib.h>
#include <Reporter\HtmlReportVisitor.h>
#include <System\Time.h>
#include <Reporter\HtmlHelper.h>
#include <Reporter\PageLayout.h>

rptHtmlReportVisitor::~rptHtmlReportVisitor()
{
}

void rptHtmlReportVisitor::VisitReport(rptReport* pReport)
{

   WBFL::System::Time my_time;
   // dump control information out to the report
   *m_pOstream << _T("<!DOCTYPE HTML PUBLIC \"-//Spyglass//DTD HTML 2.0 Extended//EN\">") << std::endl
               << _T("<html>") << std::endl
               << _T("<head>") << std::endl
               << _T("<meta title=\"WSDOT Engineering Reporter on ")
               <<  my_time << _T("\">") << std::endl;

   if (pReport->GetName().empty())
      *m_pOstream << _T("<title>\"WSDOT Engineering Reporter on ")
                  <<  my_time << _T("\"</title>") << std::endl;
   else
      *m_pOstream << _T("<title>") << pReport->GetName() << _T("</title>") << std::endl<<std::endl;

   // If heading numbers are enabled, include CSS for heading numbers in the generated HTML
   if (pReport->HeadingNumbersEnabled()) {
        *m_pOstream << _T("<style>") << std::endl;
        *m_pOstream << _T("body {counter-reset: h1}") << std::endl;
        *m_pOstream << _T("h1 {counter-reset: h2}") << std::endl;
        *m_pOstream << _T("h2 {counter-reset: h3}") << std::endl;
        *m_pOstream << _T("h3 {counter-reset: h4}") << std::endl;
        *m_pOstream << _T("h4 {counter-reset: h5}") << std::endl;
        *m_pOstream << _T("h5 {counter-reset: h6}") << std::endl;
        *m_pOstream << _T("h1:before {counter-increment: h1; content: counter(h1) '. '}") << std::endl;
        *m_pOstream << _T("h2:before {counter-increment: h2; content: counter(h1) '.' counter(h2, lower-alpha) '. '}") << std::endl;
        *m_pOstream << _T("h3:before {counter-increment: h3; content: counter(h1) '.' counter(h2, lower-alpha) '.' counter(h3, decimal) '. '}") << std::endl;
        *m_pOstream << _T("h4:before {counter-increment: h4; content: counter(h1) '.' counter(h2, lower-alpha) '.' counter(h3, decimal) '.' counter(h4, upper-alpha) '. '}") << std::endl;
        *m_pOstream << _T("h5:before {counter-increment: h5; content: counter(h1) '.' counter(h2, lower-alpha) '.' counter(h3, decimal) '.' counter(h4, upper-alpha) '.' counter(h5, lower-roman) '. '}") << std::endl;
        *m_pOstream << _T("h6:before {counter-increment: h6; content: counter(h1) '.' counter(h2, lower-alpha) '.' counter(h3, decimal) '.' counter(h4, upper-alpha) '.' counter(h5, lower-roman) '.' counter(h6, decimal) '. '}") << std::endl;
        *m_pOstream << _T("h1.nocount:before, h2.nocount:before, h3.nocount:before, h4.nocount:before, h5.nocount:before, h6.nocount:before { content: ''; counter-increment: none; }") << std::endl;
        *m_pOstream << _T("</style>") << std::endl;

    }

   // Use html helper to Write out style block
   m_Helper.VisitFontLibrary(*m_pOstream);

   // Use MEDIA attribute of STYLE tag to handle differences between
   // printing and viewing.
   //
   const rptPageLayout* pl = pReport->GetPageLayout();
   *m_pOstream << "<STYLE MEDIA=\"SCREEN\">" << std::endl;
   *m_pOstream << "   BODY {margin:0,0,0,0}" << std::endl;
   *m_pOstream << "</STYLE>" << std::endl;

   *m_pOstream << _T("<STYLE MEDIA=\"PRINT\">") << std::endl;
   *m_pOstream << _T("   BODY {");
   *m_pOstream           << _T("margin-top:")    << (pl->GetTopMargin()*m_LogPixelsY) << _T("; ");
   *m_pOstream           << _T("margin-bottom:") << (pl->GetBottomMargin()*m_LogPixelsY) << _T("; ");
   *m_pOstream           << _T("margin-left:")   << (pl->GetLeftMargin()*m_LogPixelsX) << _T("; ");
   *m_pOstream           << _T("margin-right:")  << (pl->GetRightMargin()*m_LogPixelsX) << _T("; ");
   *m_pOstream           << _T("}") << std::endl;
   *m_pOstream << _T("</STYLE>") << std::endl;

//   // force landscape page layout during printing
// // browsers don't support this very will... skip it for now!
//   if ( pl->GetPageOrientation() == rptPageLayout::poLandscape )
//   {
//      *m_pOstream << "<STYLE type=\"text/css\" MEDIA=\"PRINT\">" << std::endl;
//      *m_pOstream << "@page {size: landscape; }" << std::endl;
//      *m_pOstream << "</STYLE>" << std::endl;
//   }


   
   if (m_Helper.GetBrowserType() == rptHtmlHelper::BrowserType::Edge)
   {
       *m_pOstream << _T("<script type = \"text/javascript\"") << std::endl;
       *m_pOstream << _T("    src = \"http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML\">") << std::endl;
       *m_pOstream << _T("</script>") << std::endl;
   }


   *m_pOstream << _T("</head>") << std::endl<<std::endl;

   *m_pOstream << _T("<BODY onDragStart=\"onde()\" >") << std::endl;

   // now we're ready to start iterating over chapters.    
   // create a chapter visitor
   rptHtmlChapterVisitor my_visitor(m_pOstream, m_Helper, m_LogPixelsX, m_LogPixelsY);

   rptReport::ConstChapterListIterator pci;
   for (pci=pReport->ConstBegin(); pci!=pReport->ConstEnd(); pci++)
   {
      (*pci)->Accept( my_visitor );
   }

   // end of report - should only have to write out the final closing brace
   // and we're done!
   //
   *m_pOstream << _T("</body>") << std::endl;

   // javascript to disable drag & drop
   *m_pOstream << _T("<SCRIPT LANGUAGE=\"JavaScript\">") << std::endl;
   *m_pOstream << _T("function onde(){") << std::endl;
   *m_pOstream << _T("    var oEvent = window.event;") << std::endl;
   *m_pOstream << _T("    oEvent.returnValue = false;") << std::endl;
   *m_pOstream << _T("    oEvent.cancelBubble = true;") << std::endl;
   *m_pOstream << _T("}") << std::endl;
   *m_pOstream << _T("</SCRIPT>") << std::endl << std::endl;
   *m_pOstream << std::endl;

   if (m_Helper.GetBrowserType() == rptHtmlHelper::BrowserType::Edge)
   {
      // table caption script
      *m_pOstream << _T("<script>") << std::endl;
      *m_pOstream << _T("   function TableCaptionFunction(x) {") << std::endl;
      *m_pOstream << _T("   var table = x.parentElement;") << std::endl;
      *m_pOstream << _T("   var range = document.createRange();") << std::endl;
      *m_pOstream << _T("   range.selectNodeContents(table);") << std::endl;
      *m_pOstream << _T("   var sel = window.getSelection();") << std::endl;
      *m_pOstream << _T("   sel.removeAllRanges();") << std::endl;
      *m_pOstream << _T("   sel.addRange(range);") << std::endl;

      //
      // Code below could change this to copy the selected item directly. Seems like Select is less obtrusive
      //   *m_pOstream << _T("   document.execCommand(\"copy\");") << std::endl;
      //   *m_pOstream << _T("   alert(\"Table copied to clipboard. You can now past into Word or Excel\");") << std::endl;
      *m_pOstream << _T("}") << std::endl;
      *m_pOstream << _T("</script>") << std::endl;

   }

   *m_pOstream << _T("</html>") <<std::endl;

}

std::vector<rptHtmlReportVisitor::ChapterTocItem> rptHtmlReportVisitor::GenerateTOC(rptReport* pReport)
{
   std::vector<rptHtmlReportVisitor::ChapterTocItem> tableOfContents;

   Uint32 chapterID = rptHtmlHelper::ChapterStart;
   Uint32 paraID = rptHtmlHelper::ParaStart;

   rptReport::ConstChapterListIterator pci;
   for (pci = pReport->ConstBegin(); pci != pReport->ConstEnd(); pci++)
   {
      // Note that order and adding of ID's must match those in rptHtmlChapterVisitor and rptHtmlParagraphVisitor
      const rptChapter& chapter(**pci);
      LPCTSTR chname = chapter.GetName();
      if (chname != 0)
      {
         rptHtmlReportVisitor::ChapterTocItem chaptertocitem;
         chaptertocitem.m_TocItem = TocItem(chname, chapterID++);

         rptChapter::ConstChapterParagraphIterator pch;
         for (pch = chapter.ConstBegin(); pch != chapter.ConstEnd(); pch++)
         {
            const rptParagraph& para(**pch);
            LPCTSTR paraname = para.GetName();
            if (paraname != 0)
            {
               chaptertocitem.m_ParagraphTOCItems.push_back(rptHtmlReportVisitor::TocItem(paraname, paraID++));
            }
         }

         tableOfContents.push_back(chaptertocitem);
      }
   }

   return tableOfContents;
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


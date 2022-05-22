///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

   // Use html helper to Write out style block
   m_Helper.VisitFontLibrary(*m_pOstream);

   // Use MEDIA attribute of STYLE tag to handle differences between
   // printing and viewing.
   //
   const rptPageLayout* pl = pReport->GetPageLayout();
//   *m_pOstream << "<STYLE MEDIA=\"PRINT\">" << std::endl;
//   *m_pOstream << "   BODY {margin:0,0,0,0}" << std::endl;
//   *m_pOstream << "</STYLE>" << std::endl;

   *m_pOstream << _T("<STYLE MEDIA=\"SCREEN\">") << std::endl;
   *m_pOstream << _T("   BODY {");
   *m_pOstream           << _T("margin-top:")    << (pl->GetTopMargin()*m_LogPixelsY) << _T(" ");
   *m_pOstream           << _T("margin-bottom:") << (pl->GetBottomMargin()*m_LogPixelsY) << _T(" ");
   *m_pOstream           << _T("margin-left:")   << (pl->GetLeftMargin()*m_LogPixelsX) << _T(" ");
   *m_pOstream           << _T("margin-right:")  << (pl->GetRightMargin()*m_LogPixelsX) << _T(" ");
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
   *m_pOstream << _T("<SCRIPT LANGUAGE=\"JavaScript\">") <<std::endl;
   *m_pOstream << _T("function onde(){") <<std::endl;
   *m_pOstream << _T("    var oEvent = window.event;")<<std::endl;
   *m_pOstream << _T("    oEvent.returnValue = false;")<<std::endl;
   *m_pOstream << _T("    oEvent.cancelBubble = true;")<<std::endl;
   *m_pOstream << _T("}")<<std::endl;
   *m_pOstream << _T("</SCRIPT>")<<std::endl<<std::endl;

   *m_pOstream << _T("</html>") <<std::endl;

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


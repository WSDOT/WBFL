///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <Reporter\HtmlRcVisitor.h>
#include <Reporter\HtmlParagraphVisitor.h>
#include <Reporter\RiStyle.h>
#include <Reporter\RcInt.h>
#include <Reporter\RcUnsigned.h>
#include <Reporter\RcString.h>
#include <Reporter\RcStringLiteral.h>
#include <Reporter\RcFontModifier.h>
#include <Reporter\RcFlowModifier.h>
#include <Reporter\RcColor.h>
#include <Reporter\RcBgColor.h>
#include <Reporter\Paragraph.h>
#include <Reporter\RcTable.h>
#include <Reporter\RcDateTime.h>
#include <Reporter\RcHyperTarget.h>
#include <Reporter\RcImage.h>
#include <Reporter\RcSymbol.h>
#include <Reporter\RcScalar.h>
#include <Reporter\RcPercentage.h>
#include <Reporter\RcUnitTag.h>
#include <Reporter\RcUnitValue.h>
#include <Reporter\RcSectionValue.h>
#include <Reporter\RcSectionScalar.h>
#include <Reporter\RcStation.h>
#include <Reporter\RcComposite.h>

// Private include files
#include "HtmlUnitTagFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
CLASS
   rptHtmlRcVisitor
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

rptHtmlRcVisitor::rptHtmlRcVisitor(std::_tostream* pMyOstream, const rptPageLayout* MypPageLayout, const rptHtmlHelper& rmyHelper, Uint32 logPixelsX, Uint32 logPixelsY) :
   rptOutputRcVisitor(pMyOstream),
   m_Helper(rmyHelper),
   m_LogPixelsX(logPixelsX),
   m_LogPixelsY(logPixelsY)
{
   CHECK(MypPageLayout);
   m_pPageLayout = MypPageLayout;
}


rptHtmlRcVisitor::~rptHtmlRcVisitor()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void rptHtmlRcVisitor::VisitRcString(rptRcString* pString)
{
   HyperStart(pString); // deal with hyperlinks

   std::_tstring str = pString->GetString();

   // "strings that look like <this>" would report as
   // "strings that look like " if we don't replace < and > with their HTML equivalent

   std::_tstring::size_type pos;
   while ((pos = str.find(_T("<"))) != std::_tstring::npos)
   {
      str.replace(pos, 1, _T("&lt;"));
   }

   while ((pos = str.find(_T(">"))) != std::_tstring::npos)
   {
      str.replace(pos, 1, _T("&gt;"));
   }

   while ((pos = str.find(_T("—"))) != std::_tstring::npos)
   {
      str.replace(pos, 1, _T("&mdash;"));
   }

   while ((pos = str.find(L'–')) != std::_tstring::npos)
   {
      str.replace(pos, 1, _T("&ndash;"));
   }

   if ( 0 < str.size() )
   {
      if ( pString->NoWrap() )
      {
         *m_pOstream<< _T("<span style=\"white-space: nowrap\">") << str << _T("</span>");
      }
      else
      {
         *m_pOstream << str;
      }
   }
   else
   {
      *m_pOstream << _T("&nbsp;");
   }

   HyperEnd(pString);
}


void rptHtmlRcVisitor::VisitRcStringLiteral(rptRcStringLiteral* pString)
{
   HyperStart(pString); // deal with hyperlinks

   std::_tstring str = pString->GetString();

   if ( 0 < str.size() )
   {
      if ( pString->NoWrap() )
      {
         *m_pOstream<< _T("<span style=\"white-space: nowrap\">") << str << _T("</span>");
      }
      else
      {
         *m_pOstream << str;
      }
   }
   else
   {
      *m_pOstream << _T("&nbsp;");
   }

   HyperEnd(pString);
}

void rptHtmlRcVisitor::VisitRcTable(rptRcTable* pTable)
{
   // get number of rorpt and columns in the table
   RowIndexType num_rows = pTable->GetNumberOfRows();
   ColumnIndexType num_cols = pTable->GetNumberOfColumns();

   // get the table width
   // values are in inches, and html wants pixels - need to do some conversions
   Float64 table_width = pTable->GetTableWidth();

   Uint32 table_width_px  = (Uint32)(table_width*m_LogPixelsX);
   Uint32 cell_pad_pixels = (Uint32)(pTable->GetCellPad()*m_LogPixelsX);

   // table border size in pixels
   // no control over horizontal style or border under header
   Uint16 out_pixels = BorderToPixels(pTable->GetOutsideBorderStyle());
   Uint16 in_pixels  = BorderToPixels(pTable->GetInsideBorderStyle());

   rptRiStyle::AlignmentType align = pTable->GetAlignment();

   // can now start spewing html

   switch (align)
   {
   case rptRiStyle::RIGHT:
      *m_pOstream << _T("<DIV STYLE=\"text-align: right\">") <<std::endl;
      break;
   case rptRiStyle::CENTER:
      *m_pOstream << _T("<DIV STYLE=\"text-align: center\">") <<std::endl;
      break;
   }

   // table setup
   *m_pOstream << _T("<TABLE BORDER=")<< out_pixels<<_T(" RULES=ALL CELLSPACING=")<<in_pixels
               << _T(" CELLPADDING=")<<cell_pad_pixels;

   if ( 0 < table_width_px )
      *m_pOstream <<_T(" WIDTH=\"")<<table_width_px;
   
   *m_pOstream << _T("\">");
      
   *m_pOstream << std::endl;

   // create a paragraph visitor
   rptHtmlParagraphVisitor my_visitor(m_pOstream, /*m_pUnitSnapShot,*/ m_pPageLayout, m_Helper,m_LogPixelsX,m_LogPixelsY);

   // table caption & label
   rptParagraph& cap = pTable->TableCaption();
   rptParagraph& label = pTable->TableLabel();

   bool is_cap = !(cap.IsEmpty() && label.IsEmpty());
   if (is_cap)
   {
      *m_pOstream << _T("<CAPTION>");

      if (!cap.IsEmpty())
         // visit the caption paragraph
         cap.Accept(my_visitor);

      if (!label.IsEmpty())
          // visit the label paragraph
         label.Accept(my_visitor);

      *m_pOstream << _T("</CAPTION>")<<std::endl;
   }

   RowIndexType num_head_rows = pTable->GetNumberOfHeaderRows();

   rptFontStyleLibrary* plib = rptFontStyleLibrary::Instance();

   bool bHeading = false;
   for (RowIndexType rowno = 0; rowno<num_rows; rowno++)
   {
      if (rowno == 0)
      {
         bHeading = true;
         *m_pOstream << _T("<THEAD>")<<std::endl; // first row is start of header row
      }
      
      if (num_head_rows == rowno)
      {
         // first row of body
         *m_pOstream << _T("</THEAD>")<<std::endl;

         *m_pOstream << _T("<TBODY>")<<std::endl; // first row is start of header row
         bHeading = false;
      }

      // row information
      *m_pOstream << _T("<TR>");

      for (ColumnIndexType colno = 0; colno<num_cols; colno++)
      {
         Uint32 column_width_px = (Uint32)(pTable->GetColumnWidth(colno)*m_LogPixelsX);

         RowIndexType row_span;
         ColumnIndexType col_span;
         pTable->GetCellSpans(rowno, colno, &row_span, &col_span);

         // only output cell information if not a skipped spanning cell
         //if ( 0 < row_span && 0 <= col_span )
         if ( row_span != SKIP_CELL && col_span != SKIP_CELL )
         {
            rptTableCellParagraph& rpar = (*pTable)(rowno,colno);

            std::_tstring styleName = rpar.GetStyleName();
            rptRiStyle& style = plib->GetNamedStyle(styleName);
            rptRiStyle::AlignmentType align = style.GetAlignment();
            rptRiStyle::VerticalAlignmentType valign = style.GetVerticalAlignment();
            std::_tstring strAlign;
            switch(align)
            {
            case rptRiStyle::RIGHT:
               strAlign = _T("RIGHT");
               break;
            case rptRiStyle::LEFT:
               strAlign = _T("LEFT");
               break;
            case rptRiStyle::CENTER:
               strAlign = _T("CENTER");
               break;
            }

            std::_tstring strVAlign;
            switch(valign)
            {
            case rptRiStyle::BASELINE:
               strVAlign = _T("BASELINE");
               break;
            case rptRiStyle::TOP:
               strVAlign = _T("TOP");
               break;
            case rptRiStyle::MIDDLE:
               strVAlign = _T("MIDDLE");
               break;
            case rptRiStyle::BOTTOM:
               strVAlign = _T("BOTTOM");
               break;
            }

            std::_tstring startTag( bHeading ? _T("<TH ") : _T("<TD ") );
            std::_tstring endTag( bHeading ? _T("</TH>") : _T("</TD>"));
            if (row_span==1 && col_span==1)
            {
               *m_pOstream << startTag << _T("ALIGN=") << strAlign << _T(" VALIGN=") << strVAlign;
               if ( 0 < column_width_px )
                  *m_pOstream << startTag << _T("WIDTH=\"") << column_width_px << _T("\"");
               
            }
            else
            {
               // don't write width if colspan or rowpan is set
               *m_pOstream<<startTag << _T("ALIGN=") << strAlign<< _T(" VALIGN=")<<strVAlign<<_T(" ROWSPAN=")<<row_span<<_T(" COLSPAN=")<<col_span;
            }

            // explicitely set background colors overrule those set by headings or striping
            rptRiStyle::FontColor color = rpar.GetFillBackGroundColor();
            if (rptRiStyle::Default != color )
            {
               *m_pOstream << _T(" BGCOLOR=\"") << rptRiStyle::GetColorCode(color ) << ("\"");
            }
            else if ( bHeading || pTable->IsStripedRow(rowno) )
            {
               *m_pOstream << _T(" BGCOLOR=\"") << rptRiStyle::GetColorCode( style.GetBGColor() ) << ("\"");
            }

            *m_pOstream << _T(">");
            // visit the paragraph cells in the row
            rpar.Accept(my_visitor);

            *m_pOstream << endTag <<std::endl;
         }
      }

      *m_pOstream << _T("</TR>") <<std::endl;

   }
      // get out of table mode
      *m_pOstream << _T("</TBODY>")<<std::endl;
      *m_pOstream << _T("</TABLE>")<<std::endl;

   // close off alignment
   if (align==rptRiStyle::CENTER || align==rptRiStyle::RIGHT)
   {
      *m_pOstream << _T("</DIV>")<<std::endl;
   }

}

//------------------------------------------------------------------------
void rptHtmlRcVisitor::VisitRcFlowModifier(rptRcFlowModifier* pMyFlow)
{

   // loop over number of times and issue either a page break or
   // a new line

   Uint16 nt = pMyFlow->GetRepeatCount();
   for (Uint16 i = 0; i<nt; i++)
   {
      if(pMyFlow->GetModifierType()==rptRcFlowModifier::NEW_LINE)
         *m_pOstream << _T("<BR/>")<<std::endl;
      else if(pMyFlow->GetModifierType()==rptRcFlowModifier::NEW_PAGE)
         *m_pOstream << _T("<DIV STYLE=\"page-break-after: always\"><BR></DIV>")<<std::endl;
      else if(pMyFlow->GetModifierType()==rptRcFlowModifier::TAB)
         ;
         // TODO: figure out how to implement tabs
         //       It appears that tabs of this sort will not work. Could possibly
         //       add levels of indenting to tables.

      else
         CHECKX(0,_T("Bad FlowModifier type"));
   }
}

//------------------------------------------------------------------------

void rptHtmlRcVisitor::VisitRcFontModifier(rptRcFontModifier* my_m)
{

   rptRiStyle::FontModifier mfm = my_m->GetFontModifier();
   rptRcFontModifier::StateType    mst = my_m->GetState();

   switch (mfm)
   {
   case rptRiStyle::BOLD:
      if (mst==rptRcFontModifier::ON)
         *m_pOstream << _T("<SPAN STYLE=\"font-weight: bold;\">");
      else
         *m_pOstream << _T("</SPAN>");
      break;
   case rptRiStyle::ITALIC:
      if (mst==rptRcFontModifier::ON)
         *m_pOstream << _T("<SPAN STYLE=\"font-style: italic;\">");
      else
         *m_pOstream << _T("</SPAN>");
      break;
   case rptRiStyle::UNDERLINE:
      if (mst==rptRcFontModifier::ON)
         *m_pOstream << _T("<SPAN STYLE=\"text-decoration: underline;\">");
      else
         *m_pOstream << _T("</SPAN>");
      break;
   case rptRiStyle::OVERLINE:
      if (mst==rptRcFontModifier::ON)
         *m_pOstream << _T("<SPAN STYLE=\"text-decoration: overline;\">");
      else
         *m_pOstream << _T("</SPAN>");
      break;
   case rptRiStyle::LINETHROUGH:
      if (mst==rptRcFontModifier::ON)
         *m_pOstream << _T("<SPAN STYLE=\"text-decoration: line-through;\">");
      else
         *m_pOstream << _T("</SPAN>");
      break;
   case rptRiStyle::SUBSCRIPT:
      if (mst==rptRcFontModifier::ON)
         *m_pOstream << _T("<SUB>");
      else
         *m_pOstream << _T("</SUB>");
      break;
   case rptRiStyle::SUPERSCRIPT:
      if (mst==rptRcFontModifier::ON)
         *m_pOstream << _T("<SUP>");
      else
         *m_pOstream << _T("</SUP>");
      break;
   default:
      CHECKX(0,_T("Bad FontModifier"));
      break;
   }
}


//------------------------------------------------------------------------
//
// change the foreground color of the stream
//
void rptHtmlRcVisitor::VisitRcColor(rptRcColor* my_m)
{
   rptRiStyle::FontColor my_color = my_m->GetFontColor();
   if (rptRiStyle::Default != my_color)
   {
      *m_pOstream << _T("<SPAN STYLE=\"color:") << rptRiStyle::GetColorCode(my_color) << _T("\";>");
   }
}

//------------------------------------------------------------------------
//
// change the background color of the stream
//
void rptHtmlRcVisitor::VisitRcBgColor(rptRcBgColor* my_m)
{
   rptRiStyle::FontColor my_color = my_m->GetColor();
   if (rptRiStyle::Default != my_color)
   {
      *m_pOstream << _T("<SPAN STYLE=\"background-color: ") << rptRiStyle::GetColorCode(my_color) << _T("\";>");
   }
}

//------------------------------------------------------------------------
//
// Insert a hyperlink target into the stream
//
void rptHtmlRcVisitor::VisitRcHyperTarget(rptRcHyperTarget* my_m)
{
   *m_pOstream << _T("<A NAME=\"")<< my_m->GetTargetName() << _T("\"></A>");
}

//------------------------------------------------------------------------
//
// Insert an image into the stream
//
void rptHtmlRcVisitor::VisitRcImage(rptRcImage* pImage)
{
   std::_tstring file_name = pImage->GetFileName();
   std::_tstring picture_description = pImage->GetPictureDescription();
   std::_tstring align = _T("bottom");
   switch( pImage->GetImageAlignment() )
   {
   case rptRcImage::Baseline:
      align = _T("baseline");
      break;

   case rptRcImage::Middle:
      align = _T("middle");
      break;

   case rptRcImage::Subscript:
      align = _T("sub");
      break;

   case rptRcImage::Superscript:
      align = _T("super");
      break;

   case rptRcImage::TextTop:
      align = _T("text-top");
      break;

   case rptRcImage::TextBottom:
      align = _T("text-bottom");
      break;

   case rptRcImage::Top:
      align = _T("top");
      break;

   case rptRcImage::Bottom:
      align = _T("bottom");
      break;
   }

   std::_tstring align_style = _T("style=\"vertical-align:");
   align_style += align;
   align_style += _T("\"");


   std::_tstring flt = _T("none");
   switch( pImage->GetImageFloat() )
   {
   case rptRcImage::Left:
      flt = _T("left");
      break;

   case rptRcImage::Right:
      flt = _T("right");
      break;

   case rptRcImage::None:
      flt = _T("none");
      break;
   }

   std::_tstring float_style = _T("style=\"float:");
   float_style += flt;
   float_style += _T("\"");

   if(!file_name.empty())
   {
      *m_pOstream << _T("<img ") 
                  << align_style << _T(" ") 
                  << float_style << _T(" ")
                  << _T("src=\"") << file_name << _T("\"");

      if ( !picture_description.empty() )
      {
         *m_pOstream << _T(" alt=\"") << picture_description << _T("\"");
      }

      *m_pOstream << _T("/>") << std::endl;
   }
}

//------------------------------------------------------------------------
//
// Insert a symbol into the stream
//
void rptHtmlRcVisitor::VisitRcSymbol(rptRcSymbol* pSymbol)
{
   // get symbol type
   rptRcSymbol::SymbolType sym = pSymbol->GetSymbolType();

   // return if symbol is none
   if (sym == rptRcSymbol::NONE)
   {
      return;
   }
   else if (sym == rptRcSymbol::NBSP)
   {
      *m_pOstream << _T("&nbsp;");
   }
   else
   {
      // get the roman equivalent for the symbol
      TCHAR symlet = GetRomanForGreek(sym);

      *m_pOstream << _T("<SPAN STYLE=\"font-family: Symbol\">") << (TCHAR)symlet << _T("</SPAN>");
   }
}

//------------------------------------------------------------------------
//
// stream out the current time and/or date
//
void rptHtmlRcVisitor::VisitRcDateTime(rptRcDateTime* my_d)
{
   HyperStart(my_d); // deal with hyperlinks

   // check to see if date and/or time were requested and stream them out
   if (my_d->IsPrintDateEnabled())
   {
      sysDate md = my_d->GetDate();
      *m_pOstream << md;
   }
   // if both are requested stream out a space
   if (my_d->IsPrintDateEnabled()&&my_d->IsPrintTimeEnabled())
      *m_pOstream << _T(" ");

   if (my_d->IsPrintTimeEnabled())
   {
      sysTime mt = my_d->GetTime();
      *m_pOstream << mt;
   }

   HyperEnd(my_d); // deal with hyperlinks
}

//------------------------------------------------------------------------

void rptHtmlRcVisitor::VisitRcInt(rptRcInt* pInt)
{
   HyperStart(pInt); // deal with hyperlinks
   //
   // set up an ostream to toss value into
   //
   std::_tostringstream my_stm;

   // if width, fill with zeros
   int my_width = pInt->GetWidth();
   if (my_width > 0)
   {
      my_stm.width(my_width);
      my_stm.fill( _T('0') );
   }

   my_stm << _T("<span style=\"white-space: nowrap\">") << pInt->GetValue() << _T("</span>");

   // send the finished string up the pipe

   *m_pOstream << my_stm.str().c_str();

   HyperEnd(pInt); // deal with hyperlinks
}


//------------------------------------------------------------------------

void rptHtmlRcVisitor::VisitRcUnsigned(rptRcUnsigned* pUs)
{
   HyperStart(pUs); // deal with hyperlinks
   //
   // set up an ostream to toss value into
   //
   std::_tostringstream my_stm;

   // if width, fill with zeros
   int my_width = pUs->GetWidth();
   if (my_width > 0)
   {
      my_stm.width(my_width);
      my_stm.fill(_T('0'));
   }

   my_stm << pUs->GetValue();

   // send the finished string up the pipe

   *m_pOstream << my_stm.str().c_str();

   HyperEnd(pUs); // deal with hyperlinks
}

void rptHtmlRcVisitor::VisitRcScalar(rptRcScalar* pRC)
{
   HyperStart(pRC); // deal with hyperlinks

   //
   // set up an ostream to toss value into
   //
   std::_tostringstream my_stm;

   my_stm << _T("<span style=\"white-space: nowrap\">") << pRC->AsString() << _T("</span>");

   // send the finished string up the pipe
   *m_pOstream << my_stm.str().c_str();

   HyperEnd(pRC); // deal with hyperlinks
}

void rptHtmlRcVisitor::VisitRcPercentage(rptRcPercentage* pRC)
{
   HyperStart(pRC); // deal with hyperlinks

   //
   // set up an ostream to toss value into
   //
   std::_tostringstream my_stm;

   my_stm << _T("<span style=\"white-space: nowrap\">") << pRC->AsString() << _T("</span>");

   // send the finished string up the pipe
   *m_pOstream << my_stm.str().c_str();

   HyperEnd(pRC); // deal with hyperlinks
}

void rptHtmlRcVisitor::VisitRcUnitTag(rptRcUnitTag* pRC)
{
   HyperStart(pRC); // deal with hyperlinks

   //
   // set up an ostream to toss value into
   //
   std::_tostringstream my_stm;

   my_stm << rptHtmlUnitTagFormat::Format(pRC->AsString());

   // send the finished string up the pipe
   *m_pOstream << my_stm.str().c_str();

   HyperEnd(pRC); // deal with hyperlinks
}

void rptHtmlRcVisitor::VisitRcUnitValue(rptRcUnitValue* pRC)
{
   HyperStart(pRC); // deal with hyperlinks

   //
   // set up an ostream to toss value into
   //
   std::_tostringstream my_stm;

   if ( pRC->GetValue() < 0 )
      my_stm << _T("<span style=\"white-space: nowrap\">") << rptHtmlUnitTagFormat::Format(pRC->AsString()) << _T("</span>");
   else
      my_stm << rptHtmlUnitTagFormat::Format(pRC->AsString());

   // send the finished string up the pipe
   *m_pOstream << my_stm.str().c_str();

   HyperEnd(pRC); // deal with hyperlinks
}

void rptHtmlRcVisitor::VisitRcSectionValue(rptRcSectionValue* pRC)
{
   HyperStart(pRC); // deal with hyperlinks

   //
   // set up an ostream to toss value into
   //
   std::_tostringstream my_stm;

   my_stm << _T("<span style=\"white-space: nowrap\">") << rptHtmlUnitTagFormat::Format(pRC->AsString(0)) << _T("</span>");

   if ( pRC->IsDualValued() )
   {
      my_stm << _T("<BR>") << _T("<span style=\"white-space: nowrap\">") << rptHtmlUnitTagFormat::Format(pRC->AsString(1)) << _T("</span>");
   }

   // send the finished string up the pipe
   *m_pOstream << my_stm.str().c_str();

   HyperEnd(pRC); // deal with hyperlinks
}

void rptHtmlRcVisitor::VisitRcSectionScalar(rptRcSectionScalar* pRC)
{
   HyperStart(pRC); // deal with hyperlinks

   //
   // set up an ostream to toss value into
   //
   std::_tostringstream my_stm;

   my_stm << _T("<span style=\"white-space: nowrap\">") << pRC->AsString(0) << _T("</span>");
   if ( pRC->IsDualValued() )
   {
      my_stm << _T("<BR>") << _T("<span style=\"white-space: nowrap\">") << pRC->AsString(1) << _T("</span>");
   }

   // send the finished string up the pipe
   *m_pOstream << my_stm.str().c_str();

   HyperEnd(pRC); // deal with hyperlinks
}

void rptHtmlRcVisitor::VisitRcStation(rptRcStation* pRC)
{
   HyperStart(pRC); // deal with hyperlinks

   //
   // set up an ostream to toss value into
   //
   std::_tostringstream my_stm;

   my_stm << _T("<span style=\"white-space: nowrap\">") << pRC->AsString() << _T("</span>");

   // send the finished string up the pipe
   *m_pOstream << my_stm.str().c_str();

   HyperEnd(pRC); // deal with hyperlinks
}

void rptHtmlRcVisitor::VisitRcComposite(rptRcComposite* pRC)
{
   rptRcComposite::ContentIterator it = pRC->Begin();
   while (it != pRC->End())
   {
      (*it)->Accept(*this);

      it++;
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

// return pixel width based on border style
//
Uint16 rptHtmlRcVisitor::BorderToPixels( rptRiStyle::BorderStyle BStyle)
{
   switch (BStyle)
   {
   case rptRiStyle::NOBORDER:
      return 0;

   case rptRiStyle::HAIR_THICK:
      return 1;

   case rptRiStyle::SINGLE_THICK:
      return 2;

   case rptRiStyle::DOUBLE_THICK:
      return 6;

   case rptRiStyle::DOUBLE_LINE:
      return 8;

   case rptRiStyle::DASHED:
      return 2;

   case rptRiStyle::DOTTED:
      return 1;

   default:
      CHECKX(0,_T("Bad BorderStyle"));
      return 1;
   }
}

// write the start tag for a hyper link
void rptHtmlRcVisitor::HyperStart(const rptReportContent* pC)
{
   if (pC->IsHyperLink())
      *m_pOstream << _T("<A href=\"#")<<pC->GetHyperTarget()<<_T("\">");
}

void rptHtmlRcVisitor::HyperEnd(const rptReportContent* pC)
{
   if (pC->IsHyperLink())
      *m_pOstream << _T("</A>");
}
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


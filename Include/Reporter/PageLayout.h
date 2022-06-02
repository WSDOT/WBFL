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

#ifndef INCLUDED_REPORTER_PAGELAYOUT_H_
#define INCLUDED_REPORTER_PAGELAYOUT_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\Paragraph.h>

/// Class that defines a page layout
///
/// A page layout consists of page margins and the headers & footers for a report or for a chapter
class REPORTERCLASS rptPageLayout
{
public:
   /// Defines page orientation
   enum PageOrientation
   {
      poDefault, ///< Default orientation
      poPortrait, ///< Page is portrait
      poLandscape ///< Page is landscape
   };

   rptPageLayout();
   rptPageLayout(const rptPageLayout& rOther) = default;
   virtual ~rptPageLayout();

   rptPageLayout& operator=(const rptPageLayout& rOther) = default;

   /// Sets the page orientation
   void SetPageOrientation(PageOrientation po)
   {
      m_PageOrientation = po;
   }

   /// Returns the page orientation
   PageOrientation GetPageOrientation() const
   {
      return m_PageOrientation;
   }

   /// set page height & width (inches)
   void SetPageSize(Float64 MyHeight, Float64 MyWidth) 
   {
      CHECK(MyHeight>0);
      CHECK(MyWidth>0);
      m_PageHeight = MyHeight;
      m_PageWidth  = MyWidth;
   }
   
   /// set top margin (inches)
   void SetTopMargin(Float64 MyMargin)     { m_TopMargin    = MyMargin; }

   /// set bottom margin (inches)
   void SetBottomMargin(Float64 MyMargin)  { m_BottomMargin = MyMargin; }

   /// set left margin (inches)
   void SetLeftMargin(Float64 MyMargin)    { m_LeftMargin   = MyMargin; }

   /// set right margin (inches)
   void SetRightMargin(Float64 MyMargin)   { m_RightMargin  = MyMargin; }

   /// get page height (inches)
   Float64 GetPageHeight() const    { return m_PageHeight; }

   /// get page width (inches)
   Float64 GetPageWidth()  const   { return m_PageWidth; }

   /// get top margin (inches)
   Float64 GetTopMargin()  const   { return m_TopMargin; }

   /// get bottom margin (inches)
   Float64 GetBottomMargin() const { return m_BottomMargin; }

   /// get left margin (inches)
   Float64 GetLeftMargin()  const  { return m_LeftMargin; }

   /// get right margin (inches)
   Float64 GetRightMargin() const  { return m_RightMargin; }

   /// set the header style
   void SetHeaderStyleName(const rptStyleName& MyStyleName) { m_HeaderParagraph.SetStyleName(MyStyleName);}
   
   /// set the footer style
   void SetFooterStyleName(const rptStyleName& MyStyleName) { m_FooterParagraph.SetStyleName(MyStyleName);}
   
   // Header and Footer Paragraphs
   // Note that these paragraphs are not in the chain of responsibility for
   // style information. They get a default style at construction and their
   // styles must be explicitly changed if you want to modify them.
   rptParagraph m_HeaderParagraph; ///< Paragraph for page header
   rptParagraph m_FooterParagraph; ///< Paragraph for page footer


private:
   PageOrientation m_PageOrientation;

   Float64 m_PageHeight; ///< Page height in inches
   Float64 m_PageWidth; ///< Page width in inches
   Float64 m_TopMargin; ///< Top margin in inches
   Float64 m_BottomMargin; ///< Bottom margin in inches
   Float64 m_LeftMargin; ///< Left margin in inches
   Float64 m_RightMargin; ///< Right margin in inches

   // Function to aid in copying and assignment
   void MakeCopy(const rptPageLayout& rOther);
};

#endif // INCLUDED_REPORTER_PAGELAYOUT_H_

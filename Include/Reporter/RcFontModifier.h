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

#ifndef INCLUDED_REPORTER_RCFONTMODIFIER_H_
#define INCLUDED_REPORTER_RCFONTMODIFIER_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>
#include <string>


/// This class is used to modify font information of report content
///
/// This class is to be used as a stream manipulator to change the state of
/// the current font in the report content stream. Properties that may be
/// modified are Bold, Italics, Underline, Overline, Linethrough, Superscript and Subscript.
class REPORTERCLASS rptRcFontModifier : public rptReportContent
{
public:

   // Flag for turning states on and off
   //
   /// Defines the state of the flow modifier
   enum StateType     
   { 
      ON, ///< Turns the font modifier on
      OFF  ///< Turns the font modifer off
   };

   rptRcFontModifier(
      rptRiStyle::FontModifier MyFm, ///< Font modifier type
      StateType MyState ///< Font modifier state
   );

   rptRcFontModifier(const rptRcFontModifier& rOther);

   virtual ~rptRcFontModifier();

   rptRcFontModifier& operator=(const rptRcFontModifier& rOther);

   /// Creates a clone
   rptReportContent* CreateClone() const;

   /// Accept a visitor and calls VisitRcFlowModifier(this)
   void Accept( rptRcVisitor& MyVisitor );

   /// Returns the font modifier type
   rptRiStyle::FontModifier GetFontModifier();

   /// Sets the font modifier type
   void SetFontModifier(rptRiStyle::FontModifier MyFont);

   /// Returns the font modifier state
   StateType GetState();

   /// Sets the font modifier state
   void SetState(StateType MyState);

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcFontModifier& rOther);
   
   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRcFontModifier& rOther);

private:
   rptRiStyle::FontModifier m_FontModifier;
   StateType    m_State;

   rptRcFontModifier() = delete;
};


/// Toggles bold text
///
///     *pPara << bold(ON) << _T("This is bold text") << bold(OFF) << rptNewLine;
#define bold(a)      new rptRcFontModifier(rptRiStyle::BOLD, rptRcFontModifier::a)

/// Toggles italic text
///
///     *pPara << italic(ON) << _T("This is italic text") << italic(OFF) << rptNewLine;
#define italic(a)    new rptRcFontModifier(rptRiStyle::ITALIC, rptRcFontModifier::a)

/// Toggles underline text
///
///     *pPara << underline(ON) << _T("This is underline text") << underline(OFF) << rptNewLine;
#define underline(a) new rptRcFontModifier(rptRiStyle::UNDERLINE, rptRcFontModifier::a)

/// Toggles overline text
///
///     *pPara << overline(ON) << _T("This is overline text") << overline(OFF) << rptNewLine;
#define overline(a)  new rptRcFontModifier(rptRiStyle::OVERLINE, rptRcFontModifier::a)

/// Toggles linethrough text
///
///     *pPara << linethrough(ON) << _T("This is linethrough text") << linethrough(OFF) << rptNewLine;
#define linethrough(a)  new rptRcFontModifier(rptRiStyle::LINETHROUGH, rptRcFontModifier::a)

/// Toggles subscripting
///
///    *pPara << _T("Y") << subscript(ON) << _T("2") << subscript(OFF) << rptNewLine;
#define subscript(a) new rptRcFontModifier(rptRiStyle::SUBSCRIPT, rptRcFontModifier::a)

/// Toggles superscripting
///
///     *pPara << _T("Y = X") << superscript(ON) << _T("2") << superscript(OFF) << rptNewLine;
#define superscript(a) new rptRcFontModifier(rptRiStyle::SUPERSCRIPT, rptRcFontModifier::a)

#endif // INCLUDED_REPORTER_RCFONTMODIFIER_H_

///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

// :WARNING: This looks dangerous
//
// define some macros to aid in using these font modifiers
// 
#define bold(a)      new rptRcFontModifier(rptRiStyle::BOLD, rptRcFontModifier::a)
#define italic(a)    new rptRcFontModifier(rptRiStyle::ITALIC, rptRcFontModifier::a)
#define underline(a) new rptRcFontModifier(rptRiStyle::UNDERLINE, rptRcFontModifier::a)
#define overline(a)  new rptRcFontModifier(rptRiStyle::OVERLINE, rptRcFontModifier::a)
#define linethrough(a)  new rptRcFontModifier(rptRiStyle::LINETHROUGH, rptRcFontModifier::a)
#define subscript(a) new rptRcFontModifier(rptRiStyle::SUBSCRIPT, rptRcFontModifier::a)
#define superscript(a) new rptRcFontModifier(rptRiStyle::SUPERSCRIPT, rptRcFontModifier::a)


/*****************************************************************************
CLASS 
   rptRcFontModifier

   This class is used to modify font information of report content


DESCRIPTION
   This class is to be used as a stream manipulator to change the state of
   the current font in the report content stream. Properties that may be
   modified are Bold, Underline, Overline, Line-through, and Italics.


   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 04.11.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcFontModifier : public rptReportContent
{
public:

   // Flag for turning states on and off
   //
   enum StateType     { ON, OFF };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   rptRcFontModifier(rptRiStyle::FontModifier MyFm, StateType MyState);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcFontModifier(const rptRcFontModifier& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcFontModifier();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   // Returns reference to itself
   rptRcFontModifier& operator = (const rptRcFontModifier& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Clone thyself
   rptReportContent* CreateClone() const;

   //------------------------------------------------------------------------
   // accept a visitor
   void Accept( rptRcVisitor& MyVisitor );
   //
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Get the font modifier type
   rptRiStyle::FontModifier GetFontModifier();

   //------------------------------------------------------------------------
   // Set the font modifier type
   void SetFontModifier(rptRiStyle::FontModifier MyFont);

   //------------------------------------------------------------------------
   // Get the state flag
   StateType GetState();

   //------------------------------------------------------------------------
   // Set the state flag
   void SetState(StateType MyState);

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Function to aid in copying
   void MakeCopy(const rptRcFontModifier& rOther);

   //------------------------------------------------------------------------
   // Function to aid in assignment
   virtual void MakeAssignment(const rptRcFontModifier& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //------------------------------------------------------------------------
   // What type of font modifier are we?
   rptRiStyle::FontModifier m_FontModifier;

   //------------------------------------------------------------------------
   // State: OFF or ON
   StateType    m_State;
   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default construction not allowed
   rptRcFontModifier();
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_RCFONTMODIFIER_H_

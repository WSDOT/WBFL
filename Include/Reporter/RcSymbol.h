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

#ifndef INCLUDED_REPORTER_RCSYMBOL_H_
#define INCLUDED_REPORTER_RCSYMBOL_H_
#pragma once

// :COCOON: rdp 05.12.1997 : Cocoon limitations
// :FILE:   RcSymbol.h
//
// All preprocessor stuff must go up here because of limitations in
// Cocoon.

// SYSTEM INCLUDES
//
#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>
#include <Reporter\ReportingUtils.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS

// :WARNING: This is probably dangerous!!!
// define a macro to insert a symbol
#define symbol(a) new rptRcSymbol(rptRcSymbol::a)

/*****************************************************************************
CLASS 
   rptRcSymbol

   Report Content that Defines an Symbol


DESCRIPTION
   The class may be used to put in-line Symbols into the report stream. The symbols
   that are available are defined the SymbolType enum below.


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
   rdp : 05.12.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcSymbol : public rptReportContent
{
public:

   //------------------------------------------------------------------------
   // symbol types available for insertion by the RcSymbol class.
   // For an example of what all of the symbols look like, run the 
   // Reporter test application.
   enum SymbolType { NONE,     // no symbol
                     alpha,    // lower-case and upper-case greek symbols
                     ALPHA,    //   |
                     beta,     //   V
                     BETA,
                     delta,
                     DELTA,
                     epsilon,
                     EPSILON,
                     eta,
                     ETA,
                     gamma, 
                     GAMMA,
                     kappa,
                     KAPPA,
                     lambda,
                     LAMBDA,
                     mu,
                     MU,
                     nu,
                     NU,
                     omega,
                     OMEGA,
                     pi,
                     PI,
                     phi,
                     PHI,
                     psi,
                     PSI,
                     rho,
                     RHO,
                     SIGMA,
                     sigma,
                     theta,
                     THETA,
                     QED,                     // Little triangle made of dots
                     INFINITY,                // lazy 8
                     DEGREES,                 // degree symbol
                     OMICRON,                 // looks like a bug
                     PARTIAL,                 // partial differential
                     DOT,                     // nice black dot
                     DIAMOND,                 // hollow diamond
                     FUNCTION,                // fancy f - good for function def's
                     PRODUCT,                 // product sum-like thing
                     SUM,                     // summation symbol - simalar to SIGMA
                     INTEGRAL,                // integral symbol
                     ROOT,                    // vertical part of root enclosure
                     TIMES,                   // nice multiplication symbol
                     DIVIDE,                  // two dots over and under a horizontal bar
                     LTE,                     // less than or equal to
                     GTE,                     // greater than or equal to
                     NE,                      // not equal to
                     EXACTLY,                 // three horizontal bars
                     PLUS_MINUS,              // the old +/- symbol
                     ABOUT_EQUAL,             // tilde over two bars
                     APPROXIMATELY,           // two tildes over/under
                     ELLIPSES,                // ...
                     VERTICAL_BAR,            // long vertical bar
                     HORIZONTAL_BAR,          // long horizontal bar
                     ENTER,                   // cr symbol
                     EMPTY_SET,               // ghostbusters
                     REGISTER,                // R in a circle
                     COPYRIGHT,               // C in a circle
                     TRADEMARK,               // TM superscript
                     LEFT_RIGHT_SINGLE_ARROW, // single line arrow pointing both ways
                     LEFT_SINGLE_ARROW,       // single line arrow pointing left
                     UP_SINGLE_ARROW,         // single line arrow pointing up
                     RIGHT_SINGLE_ARROW,      // single line arrow pointing right
                     DOWN_SINGLE_ARROW,       // single line arrow pointing down
                     LEFT_RIGHT_DOUBLE_ARROW, // Double line arrow pointing both ways
                     LEFT_DOUBLE_ARROW,       // Double line arrow pointing left
                     UP_DOUBLE_ARROW,         // Double line arrow pointing up
                     RIGHT_DOUBLE_ARROW,      // Double line arrow pointing right
                     DOWN_DOUBLE_ARROW,       // Double line arrow pointing down
                     NORMAL                   // upside down T
                     };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor: set the Symbol expression
   rptRcSymbol(SymbolType Symbol);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcSymbol(const rptRcSymbol& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcSymbol();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   rptRcSymbol& operator = (const rptRcSymbol& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   //
   // Get the symbol type
   SymbolType GetSymbolType() {return m_SymbolType;}

   //------------------------------------------------------------------------
   // create a type correct clone
   //
   rptReportContent* CreateClone() const;

   //------------------------------------------------------------------------
   // Accept a report content visitor
   //
   void Accept( rptRcVisitor& MyVisitor )
   {
      MyVisitor.VisitRcSymbol(this);
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const rptRcSymbol& rOther);
   void MakeAssignment(const rptRcSymbol& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   SymbolType m_SymbolType;
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_RCSYMBOL_H_

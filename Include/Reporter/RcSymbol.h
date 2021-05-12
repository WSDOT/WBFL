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

#ifndef INCLUDED_REPORTER_RCSYMBOL_H_
#define INCLUDED_REPORTER_RCSYMBOL_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>
#include <Reporter\ReportingUtils.h>
#include <string>

///< Creates a new symbol report content object
#define symbol(a) new rptRcSymbol(rptRcSymbol::a)

/// Report Content that defines an symbol
class REPORTERCLASS rptRcSymbol : public rptReportContent
{
public:
   /// Symbol types
   enum SymbolType { NONE,     ///< no symbol
                     alpha,    // lower-case and upper-case greek symbols
                     ALPHA,    //   |
                     beta,     //   V
                     BETA,
                     chi,
                     CHI,
                     delta,
                     DELTA,
                     epsilon,
                     EPSILON,
                     zeta,
                     ZETA,
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
                     varphi,
                     phi,
                     PHI,
                     psi,
                     PSI,
                     rho,
                     RHO,
                     sigma,
                     SIGMA,
                     tau,
                     TAU,
                     theta,
                     THETA,
                     QED,                     ///< Little triangle made of dots
                     infinity,                ///< lazy 8
                     DEGREES,                 ///< degree symbol
                     OMICRON,                 ///< looks like a bug
                     PARTIAL,                 ///< partial differential
                     DOT,                     ///< nice black dot
                     DIAMOND,                 ///< hollow diamond
                     FUNCTION,                ///< fancy f - good for function def's
                     PRODUCT,                 ///< product sum-like thing
                     SUM,                     ///< summation symbol - simalar to SIGMA
                     INTEGRAL,                ///< integral symbol
                     ROOT,                    ///< vertical part of root enclosure
                     TIMES,                   ///< nice multiplication symbol
                     DIVIDE,                  ///< two dots over and under a horizontal bar
                     LTE,                     ///< less than or equal to
                     GTE,                     ///< greater than or equal to
                     NE,                      ///< not equal to
                     EXACTLY,                 ///< three horizontal bars
                     PLUS_MINUS,              ///< the old +/- symbol
                     ABOUT_EQUAL,             ///< tilde over two bars
                     APPROXIMATELY,           ///< two tildes over/under
                     ELLIPSES,                ///< ...
                     VERTICAL_BAR,            ///< long vertical bar
                     HORIZONTAL_BAR,          // /<long horizontal bar
                     ENTER,                   ///< cr symbol
                     EMPTY_SET,               ///< ghostbusters
                     REGISTER,                ///< R in a circle
                     COPYRIGHT,               ///< C in a circle
                     TRADEMARK,               ///< TM superscript
                     LEFT_RIGHT_SINGLE_ARROW, ///< single line arrow pointing both ways
                     LEFT_SINGLE_ARROW,       ///< single line arrow pointing left
                     UP_SINGLE_ARROW,         ///< single line arrow pointing up
                     RIGHT_SINGLE_ARROW,      ///< single line arrow pointing right
                     DOWN_SINGLE_ARROW,       ///< single line arrow pointing down
                     LEFT_RIGHT_DOUBLE_ARROW, ///< Double line arrow pointing both ways
                     LEFT_DOUBLE_ARROW,       ///< Double line arrow pointing left
                     UP_DOUBLE_ARROW,         ///< Double line arrow pointing up
                     RIGHT_DOUBLE_ARROW,      ///< Double line arrow pointing right
                     DOWN_DOUBLE_ARROW,       ///< Double line arrow pointing down
                     NORMAL,                  ///< upside down T
                     NBSP                     ///< non-breaking space. works like in html to force blank in a table, or can uses as a sequence of multiple spaces when needed
                     };

   rptRcSymbol(SymbolType Symbol);
   rptRcSymbol(const rptRcSymbol& rOther);
   virtual ~rptRcSymbol();

   rptRcSymbol& operator=(const rptRcSymbol& rOther);

   /// Returns the symbol type
   SymbolType GetSymbolType() {return m_SymbolType;}

   /// Create a clone
   virtual rptReportContent* CreateClone() const override;

   /// Accepts a visitor and calls VisitRcSymbol(this)
   void Accept( rptRcVisitor& MyVisitor )
   {
      MyVisitor.VisitRcSymbol(this);
   }

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcSymbol& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRcSymbol& rOther);

private:
   rptRcSymbol() = delete;
   SymbolType m_SymbolType;
};

#endif // INCLUDED_REPORTER_RCSYMBOL_H_

///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

#if !defined INCLUDED_REPORTER_REPORTINGUTILS_H_
#define INCLUDED_REPORTER_REPORTINGUTILS_H_
#pragma once

// Some convinent macros for common engineering symbols
#define Super(a) superscript(ON) << (a) << superscript(OFF)
#define Sub(a) subscript(ON) << (a) << subscript(OFF)
#define Sub2(a,b) (a) << subscript(ON) << (b) << subscript(OFF)
#define Bold(a) bold(ON) << (a) << bold(OFF)
#define Italic(a) italic(ON) << (a) << italic(OFF)

#define INIT_UV_PROTOTYPE( type, proto, im, _bShowTag ) \
   type proto( &im.UnitOfMeasure, im.Tol, _bShowTag ); \
   proto.SetFormat( im.Format );\
   proto.SetWidth( im.Width ); \
   proto.SetPrecision( im.Precision )

#define INIT_FRACTIONAL_LENGTH_PROTOTYPE( proto, english, denom, im, _bShowTag,_bFractionOnly) \
   rptFormattedLengthUnitValue proto(&im.UnitOfMeasure, im.Tol ,_bShowTag,english,denom,_bFractionOnly); \
   proto.SetFormat( im.Format );\
   proto.SetWidth( im.Width ); \
   proto.SetPrecision( im.Precision )

#define COLHDR(hdr,ut,u) hdr << rptNewLine << "(" << ut(&u.UnitOfMeasure) << ")"

#define RPT_EC  "E" << Sub("c")
#define RPT_ECI "E" << Sub("ci")
#define RPT_ES  "E" << Sub("s")
#define RPT_EPS "E" << Sub("ps")
#define RPT_EP  "E" << Sub("p")
#define RPT_FY  "f" << subscript(ON) << "y"  << subscript(OFF)
#define RPT_FPU "f" << subscript(ON) << "pu" << subscript(OFF)
#define RPT_FPJ "f" << subscript(ON) << "pj" << subscript(OFF)
#define RPT_FPT "f" << subscript(ON) << "pt" << subscript(OFF)
#define RPT_FPY "f" << subscript(ON) << "py" << subscript(OFF)
#define RPT_FPS "f" << subscript(ON) << "ps" << subscript(OFF)
#define RPT_FPE "f" << subscript(ON) << "pe" << subscript(OFF)
#define RPT_FPC "f" << subscript(ON) << "pc" << subscript(OFF)
#define RPT_FPO "f" << subscript(ON) << "po" << subscript(OFF)
#define RPT_AC  "A" << Sub("c")
#define RPT_AS  "A" << Sub("s")
#define RPT_APS "A" << Sub("ps")
#define RPT_FC "f'" << Sub("c")
#define RPT_FCI "f'" << Sub("ci")
#define RPT_YTOP "Y" << Sub("t")
#define RPT_YBOT "Y" << Sub("b")
#define RPT_STOP "S" << Sub("t")
#define RPT_SBOT "S" << Sub("b")
#define RPT_IX   "I" << Sub("x")
#define RPT_IXX  "I" << Sub("xx")
#define RPT_IY   "I" << Sub("y")
#define RPT_IYY  "I" << Sub("yy")
#define RPT_IXY  "I" << Sub("xy")
#define RPT_FTOP symbol(sigma) << Sub("t")
#define RPT_FBOT symbol(sigma) << Sub("b")

#define RPT_PASS color(Green) << "Pass" << color(Black)
#define RPT_FAIL color(Red) << bold(ON) << "Fail" << bold(OFF) << color(Black)
#define RPT_NA color(Blue) << "N/A" << color(Black)

#endif // INCLUDED_REPORTER_REPORTINGUTILS_H_

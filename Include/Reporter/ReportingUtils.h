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

#define RPT_EC  Sub2("E","c")
#define RPT_ECI Sub2("E","ci")
#define RPT_ES  Sub2("E","s")
#define RPT_EPS Sub2("E","ps")
#define RPT_EP  Sub2("E","p")
#define RPT_FY  italic(ON) << Sub2("f","y") << italic(OFF)
#define RPT_FPU italic(ON) << Sub2("f","pu") << italic(OFF)
#define RPT_FPJ italic(ON) << Sub2("f","pj") << italic(OFF)
#define RPT_FPT italic(ON) << Sub2("f","pt") << italic(OFF)
#define RPT_FPY italic(ON) << Sub2("f","py") << italic(OFF)
#define RPT_FPS italic(ON) << Sub2("f","ps") << italic(OFF)
#define RPT_FPE italic(ON) << Sub2("f","pe") << italic(OFF)
#define RPT_FPC italic(ON) << Sub2("f","pc") << italic(OFF)
#define RPT_FPO italic(ON) << Sub2("f","po") << italic(OFF)
#define RPT_AC  Sub2("A","c")
#define RPT_AS  Sub2("A","s")
#define RPT_APS Sub2("A","ps")
#define RPT_FC italic(ON) << Sub2("f'","c") << italic(OFF)
#define RPT_FCI italic(ON) << Sub2("f'","ci") << italic(OFF)
#define RPT_YTOP Sub2("Y","t")
#define RPT_YBOT Sub2("Y","b")
#define RPT_STOP Sub2("S","t")
#define RPT_SBOT Sub2("S","b")
#define RPT_IX   Sub2("I","x")
#define RPT_IXX  Sub2("I","xx")
#define RPT_IY   Sub2("I","y")
#define RPT_IYY  Sub2("I","yy")
#define RPT_IXY  Sub2("I","xy")
#define RPT_FTOP italic(ON) << Sub2("f","t") << italic(OFF)
#define RPT_FBOT italic(ON) << Sub2("f","b") << italic(OFF)
#define RPT_STRESS(_subscript_) italic(ON) << Sub2("f",_subscript_) << italic(OFF)

#define RPT_PASS color(Green) << "Pass" << color(Black)
#define RPT_FAIL color(Red) << bold(ON) << "Fail" << bold(OFF) << color(Black)
#define RPT_NA color(Blue) << "N/A" << color(Black)

#endif // INCLUDED_REPORTER_REPORTINGUTILS_H_

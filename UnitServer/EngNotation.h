///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2010  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_ENGNOTATION_H_
#define INCLUDED_ENGNOTATION_H_

#if !defined INCLUDED_IOSTREAM_
#include <iostream>
#define INCLUDED_IOSTREAM_
#endif

#if !defined INCLUDED_IOMANIP_
#include <iomanip>
#define INCLUDED_IOMANIP_
#endif

class sysEngNotationData
{
public:
   Float64 value;
   long nDigits;
   long sigDigits; // if 0, treat nDigits as the number of decimal points
                   // otherwise, treat nDigits as the number of significant
                   // digits
};

#pragma warning ( disable : 4231 )
template struct std::_Smanip<sysEngNotationData>;
typedef std::_Smanip<sysEngNotationData> eng_notation_manip;

eng_notation_manip eng_notation(Float64 value,long nDigits,long sigDigits = 0);

#endif // INCLUDED_ENGNOTATION_H_

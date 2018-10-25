///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#ifndef INCLUDED_SYSTEM_ENGNOTATION_H_
#define INCLUDED_SYSTEM_ENGNOTATION_H_
#pragma once

#include <iostream>
#include <iomanip>

class sysEngNotationData
{
public:
   Float64 value;
   int nDigits;
   int sigDigits; // if 0, treat nDigits as the number of decimal points
                    // otherwise, treat nDigits as the number of significant
                    // digits
};

// Can't use standard import/export macros becuase _Smanip is a struct
// and not a class
#if defined (BUILDSYSLIB) && !defined(SYSLIB)
#define SYSSTRUCTTPL   template struct SYSCLASS
#elif defined(SYSLIB)
#define SYSSTRUCTTPL
#else
#define SYSSTRUCTTPL   extern template struct SYSCLASS
#endif

#pragma warning ( disable : 4231 )
SYSSTRUCTTPL std::_Smanip<sysEngNotationData>;
typedef std::_Smanip<sysEngNotationData> eng_notation_manip;

SYSFUNC eng_notation_manip eng_notation(Float64 value,int nDigits,int sigDigits = 0);

#endif

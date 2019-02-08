///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2019  Washington State Department of Transportation
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

#ifndef INCLUDED_UNITS_UNITSEXP_H_
#define INCLUDED_UNITS_UNITSEXP_H_
#pragma once

// Define BUILDUNITSLIB when building this library
// For static builds, define UNITSLIB
// For static binding, define UNITSLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDUNITSLIB) && !defined(UNITSLIB)
#define UNITSCLASS __declspec(dllexport)
#define UNITSFUNC  __declspec(dllexport)
#define UNITSTPL   template class UNITSCLASS
#elif defined(UNITSLIB)
#define UNITSCLASS
#define UNITSFUNC
#define UNITSTPL
#else
#define UNITSCLASS __declspec(dllimport)
#define UNITSFUNC
#define UNITSTPL   extern template class UNITSCLASS
#endif

#include <WbflAll.h>
#include <Units\AutoLib.h>

#endif // INCLUDED_UNITS_UNITSEXP_H_
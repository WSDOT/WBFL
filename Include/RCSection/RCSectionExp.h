///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
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

#pragma once

// Define BUILDRCSECTIONLIB when building this library
// For static builds, define RCSECTIONLIB
// For static binding, define RCSECTIONLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDRCSECTIONLIB) && !defined(RCSECTIONLIB)
#define RCSCLASS __declspec(dllexport)
#define RCSFUNC  __declspec(dllexport)
#define RCSTPL   template class RCSCLASS
#elif defined(RCSECTIONLIB)
#define RCSCLASS
#define RCSFUNC
#define RCSTPL
#else
#define RCSCLASS __declspec(dllimport)
#define RCSFUNC
#define RCSTPL   extern template class RCSCLASS
#endif

#include <RCSection\AutoLib.h>
#include <WbflAll.h>

///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// Define BUILDUNITSERVERLIB when building this library
// For static builds, define UNITSERVERLIB
// For static binding, define UNITSERVERLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDUNITSERVERLIB) && !defined(UNITSERVERLIB)
#define UNITSERVERCLASS __declspec(dllexport)
#define UNITSERVERFUNC  __declspec(dllexport)
#define UNITSERVERTPL   template class UNITSERVERCLASS
#elif defined(UNITSERVERLIB)
#define UNITSERVERCLASS
#define UNITSERVERFUNC
#define UNITSERVERTPL
#else
#define UNITSERVERCLASS __declspec(dllimport)
#define UNITSERVERFUNC  __declspec(dllimport)
#define UNITSERVERTPL   extern template class UNITSERVERCLASS
#endif

#include <WbflAll.h>
#include <WBFLUnitServer\AutoLib.h>

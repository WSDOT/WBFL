///////////////////////////////////////////////////////////////////////
// Stability
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

// Define BUILDSTABILITY when building this library
// For static builds, define STABILITYLIB
// For static binding, define STABILITYLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDSTABILITY) && !defined(STABILITYLIB)
#define STABILITYCLASS __declspec(dllexport)
#define STABILITYFUNC  __declspec(dllexport)
#define STABILITYTPL   template class STABILITYCLASS
#elif defined(STABILITYLIB)
#define STABILITYCLASS
#define STABILITYFUNC
#define STABILITYTPL
#else
#define STABILITYCLASS __declspec(dllimport)
#define STABILITYFUNC
#define STABILITYTPL   extern template class STABILITYCLASS
#endif

#include <Stability/AutoLib.h>
#include <WBFLAll.h>

#define SHOW_FULL_CRACKING_TABLE
#define REBAR_FOR_DIRECT_TENSION // adequacy of reinforcement to use the higher tension stress limit is based on direct tension (plumb section only) when this is defined, otherwise it is based on total tension (plumb + tilt)

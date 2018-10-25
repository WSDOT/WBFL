///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#pragma once

// Define BUILDBRIDGEGEOMETRYLIB when building this library
// For static builds, define BGLIB
// For static binding, define BGLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDBRIDGEGEOMETRYLIB) && !defined(BGLIB)
#define BGCLASS __declspec(dllexport)
#define BGFUNC  __declspec(dllexport)
#define BGTPL   template class BGCLASS
#elif defined(BGLIB)
#define BGCLASS
#define BGFUNC
#define BGTPL
#else
#define BGCLASS __declspec(dllimport)
#define BGFUNC
#define BGTPL   extern template class BGCLASS
#endif

#include <WbflAll.h>
#include <BridgeGeometry\AutoLib.h>

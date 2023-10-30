///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

// Define BUILDCOORDGEOMLIB when building this library
// For static builds, define COORDGEOMLIB
// For static binding, define COORDGEOMLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDCOORDGEOMLIB) && !defined(COORDGEOMLIB)
#define COORDGEOMCLASS __declspec(dllexport)
#define COORDGEOMFUNC  __declspec(dllexport)
#define COORDGEOMTPL   template class COORDGEOMCLASS
#elif defined(COORDGEOMLIB)
#define COORDGEOMCLASS
#define COORDGEOMFUNC
#define COORDGEOMTPL
#else
#define COORDGEOMCLASS __declspec(dllimport)
#define COORDGEOMFUNC
#define COORDGEOMTPL   extern template class COORDGEOMCLASS
#endif

#include <CoordGeom\AutoLib.h>
#include <WBFLAll.h>
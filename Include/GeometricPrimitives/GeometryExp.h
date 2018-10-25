///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2012  Washington State Department of Transportation
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

#ifndef INCLUDED_GEOMETRY_GEOMETRYEXP_H_
#define INCLUDED_GEOMETRY_GEOMETRYEXP_H_
#pragma once

// Define BUILDGEOMLIB when building this library
// For static builds, define GEOMLIB
// For static binding, define GEOMLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDGEOMLIB) && !defined(GEOMLIB)
#define GEOMCLASS __declspec(dllexport)
#define GEOMFUNC  __declspec(dllexport)
#define GEOMTPL   template class GEOMCLASS
#elif defined(GEOMLIB)
#define GEOMCLASS
#define GEOMFUNC
#define GEOMTPL
#else
#define GEOMCLASS __declspec(dllimport)
#define GEOMFUNC
#define GEOMTPL   extern template class GEOMCLASS
#endif

#if !defined INCLUDED_WBFLALL_H_
#include <WbflAll.h>
#endif

#if !defined INCLUDED_GEOMETRY_AUTOLIB_H_
#include <GeometricPrimitives\AutoLib.h>
#endif

#endif // INCLUDED_GEOMETRY_GEOMETRYEXP_H_
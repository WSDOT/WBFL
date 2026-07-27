///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
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

// Define BUILDFEA2DLIB when building this library
// For static binding, define FEA2DLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDFEA2DLIB) && !defined(FEA2DLIB)
#define FEA2DCLASS __declspec(dllexport)
#define FEA2DFUNC  __declspec(dllexport)
#define FEA2DTPL   template class FEA2DCLASS
#elif defined(FEA2DLIB)
#define FEA2DCLASS
#define FEA2DFUNC
#define FEA2DTPL
#else
#define FEA2DCLASS __declspec(dllimport)
#define FEA2DFUNC
#define FEA2DTPL   extern template class FEA2DCLASS
#endif

#include <FEA2D\AutoLib.h>
#include <WbflAll.h>

///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifndef INCLUDED_MATERIAL_MATERIALEXP_H_
#define INCLUDED_MATERIAL_MATERIALEXP_H_
#pragma once

// Define BUILDMATLIB when building this library
// For static builds, define MATLIB
// For static binding, define MATLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDMATLIB) && !defined(MATLIB)
#define MATCLASS __declspec(dllexport)
#define MATFUNC  __declspec(dllexport)
#define MATTPL   template class MATCLASS
#elif defined(MATLIB)
#define MATCLASS
#define MATFUNC
#define MATTPL
#else
#define MATCLASS __declspec(dllimport)
#define MATFUNC
#define MATTPL   extern template class MATCLASS
#endif

#if !defined INCLUDED_WBFLALL_H_
#include <WbflAll.h>
#endif

#if !defined INCLUDED_MATERIAL_AUTOLIB_H_
#include <Material\AutoLib.h>
#endif

#endif // INCLUDED_MATERIAL_MATERIALEXP_H_
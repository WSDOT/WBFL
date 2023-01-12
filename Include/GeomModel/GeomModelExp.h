///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#ifndef INCLUDED_GEOMMODEL_GEOMMODELEXP_H_
#define INCLUDED_GEOMMODEL_GEOMMODELEXP_H_
#pragma once

// Define BUILDGEOMMODELLIB when building this library
// For static builds, define GEOMMODELLIB
// For static binding, define GEOMMODELLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDGEOMMODELLIB) && !defined(GEOMMODELLIB)
#define GEOMMODELCLASS __declspec(dllexport)
#define GEOMMODELFUNC  __declspec(dllexport)
#define GEOMMODELTPL   template class GEOMMODELCLASS
#elif defined(GEOMMODELLIB)
#define GEOMMODELCLASS
#define GEOMMODELFUNC
#define GEOMMODELTPL
#else
#define GEOMMODELCLASS __declspec(dllimport)
#define GEOMMODELFUNC
#define GEOMMODELTPL   extern template class GEOMMODELCLASS
#endif

#if !defined INCLUDED_WBFLALL_H_
#include <WbflAll.h>
#endif

#if !defined INCLUDED_GEOMMODEL_AUTOLIB_H_
#include <GeomModel\AutoLib.h>
#endif

#endif // INCLUDED_GEOMMODEL_GEOMMODELEXP_H_
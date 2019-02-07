///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#ifndef INCLUDED_REINFORCEDCONCRETE_REINFCONCEXP_H_
#define INCLUDED_REINFORCEDCONCRETE_REINFCONCEXP_H_
#pragma once

// Define BUILDREINFCONCLIB when building this library
// For static builds, define REINFCONCLIB
// For static binding, define REINFCONCLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDREINFCONCLIB) && !defined(REINFCONCLIB)
#define REINFCONCCLASS __declspec(dllexport)
#define REINFCONCFUNC  __declspec(dllexport)
#define REINFCONCTPL   template class REINFCONCCLASS
#elif defined(REINFCONCLIB)
#define REINFCONCCLASS
#define REINFCONCFUNC
#define REINFCONCTPL
#else
#define REINFCONCCLASS __declspec(dllimport)
#define REINFCONCFUNC
#define REINFCONCTPL   extern template class REINFCONCCLASS
#endif

#include <WbflAll.h>
#include <ReinforcedConcrete\AutoLib.h>

#endif // INCLUDED_REINFORCEDCONCRETE_REINFCONCEXP_H_
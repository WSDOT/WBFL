///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
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
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_ROARK_ROARKEXP_H_
#define INCLUDED_ROARK_ROARKEXP_H_
#pragma once

// Define BUILDROARK when building this library
// For static builds, define ROARKLIB
// For static binding, define ROARKLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDROARK) && !defined(ROARKLIB)
#define ROARKCLASS __declspec(dllexport)
#define ROARKFUNC  __declspec(dllexport)
#define ROARKTPL   template class ROARKCLASS
#elif defined(ROARKLIB)
#define ROARKCLASS
#define ROARKFUNC
#define ROARKTPL
#else
#define ROARKCLASS __declspec(dllimport)
#define ROARKFUNC
#define ROARKTPL   extern template class ROARKCLASS
#endif

#include <WbflAll.h>
#include <Roark\AutoLib.h>

#endif // INCLUDED_ROARK_ROARKEXP_H_
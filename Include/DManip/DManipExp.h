///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_DMANIPEXP_H_
#define INCLUDED_DMANIPEXP_H_
#pragma once

// Define BUILDDMANIPLIB when building this library
// For static builds, define DMANIPLIB
// For static binding, define DMANIPLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDDMANIPLIB) && !defined(DMANIPLIB)
#define DMANIPCLASS __declspec(dllexport)
#define DMANIPFUNC  __declspec(dllexport)
#define DMANIPTPL   template class DMANIPCLASS
#elif defined(DMANIPLIB)
#define DMANIPCLASS
#define DMANIPFUNC
#define DMANIPTPL
#else
#define DMANIPCLASS __declspec(dllimport)
#define DMANIPFUNC
#define DMANIPTPL   extern template class DMANIPCLASS
#endif

#if !defined INCLUDED_DMANIP_AUTOLIB_H_
#include <DManip\AutoLib.h>
#endif // INCLUDED_DMANIP_AUTOLIB_H_

#endif // INCLUDED_DMANIPEXP_H_
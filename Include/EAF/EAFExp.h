///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

#ifndef INCLUDED_EAF_EAFEXP_H_
#define INCLUDED_EAF_EAFEXP_H_
#pragma once

// Define BUILDEAFLIB when building this library
// For static builds, define EAFLIB
// For static binding, define EAFLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDEAFLIB) && !defined(EAFLIB)
#define EAFCLASS __declspec(dllexport)
#define EAFFUNC  __declspec(dllexport)
#define EAFTPL   template class EAFCLASS
#elif defined(EAFLIB)
#define EAFCLASS
#define EAFFUNC
#define EAFTPL
#else
#define EAFCLASS __declspec(dllimport)
#define EAFFUNC
#define EAFTPL   extern template class EAFCLASS
#endif

#include <EAF\AutoLib.h>

#endif // INCLUDED_EAF_EAFEXP_H_
///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifndef INCLUDED_ENGTOOLS_ENGTOOLSEXP_H_
#define INCLUDED_ENGTOOLS_ENGTOOLSEXP_H_
#pragma once

// Define BUILDENGTOOLSLIB when building this library
// For static builds, define ENGTOOLSLIB
// For static binding, define ENGTOOLSLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDENGTOOLSLIB) && !defined(ENGTOOLSLIB)
#define ENGTOOLSCLASS __declspec(dllexport)
#define ENGTOOLSFUNC  __declspec(dllexport)
#define ENGTOOLSTPL   template class ENGTOOLSCLASS
#elif defined(ENGTOOLSLIB)
#define ENGTOOLSCLASS
#define ENGTOOLSFUNC
#define ENGTOOLSTPL
#else
#define ENGTOOLSCLASS __declspec(dllimport)
#define ENGTOOLSFUNC
#define ENGTOOLSTPL   extern template class ENGTOOLSCLASS
#endif

#if !defined INCLUDED_WBFLALL_H_
#include <WbflAll.h>
#endif

#if !defined INCLUDED_ENGTOOLS_AUTOLIB_H_
#include <EngTools\AutoLib.h>
#endif

#endif // INCLUDED_ENGTOOLS_ENGTOOLSEXP_H_
///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
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

#ifndef INCLUDED_LIBRARYFW_LIBRARYFWEXP_H_
#define INCLUDED_LIBRARYFW_LIBRARYFWEXP_H_
#pragma once

// Define BUILDLIBRARYFWLIB when building this library
// For static builds, define LIBRARYFWLIB
// For static binding, define LIBRARYFWLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDLIBRARYFWLIB) && !defined(LIBRARYFWLIB)
#define LIBRARYFWCLASS __declspec(dllexport)
#define LIBRARYFWFUNC  __declspec(dllexport)
#define LIBRARYFWTPL   template class LIBRARYFWCLASS
#elif defined(LIBRARYFWLIB)
#define LIBRARYFWCLASS
#define LIBRARYFWFUNC
#define LIBRARYFWTPL
#else
#define LIBRARYFWCLASS __declspec(dllimport)
#define LIBRARYFWFUNC
#define LIBRARYFWTPL   extern template class LIBRARYFWCLASS
#endif

#if !defined INCLUDED_WBFLALL_H_
#include <WbflAll.h>
#endif

#if !defined INCLUDED_LIBRARYFW_AUTOLIB_H_
#include <LibraryFw\AutoLib.h>
#endif

#endif // INCLUDED_LIBRARYFW_LIBRARYFWEXP_H_
///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#ifndef INCLUDED_MFCTOOLS_MFCTOOLSEXP_H_
#define INCLUDED_MFCTOOLS_MFCTOOLSEXP_H_
#pragma once

// Define BUILDMFCTOOLSLIB when building this library
// For static builds, define MFCTOOLSLIB
// For static binding, define MFCTOOLSLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDMFCTOOLSLIB) && !defined(MFCTOOLSLIB)
#define MFCTOOLSCLASS __declspec(dllexport)
#define MFCTOOLSFUNC  __declspec(dllexport)
#define MFCTOOLSTPL   template class MFCTOOLSCLASS
#elif defined(MFCTOOLSLIB)
#define MFCTOOLSCLASS
#define MFCTOOLSFUNC
#define MFCTOOLSTPL
#else
#define MFCTOOLSCLASS __declspec(dllimport)
#define MFCTOOLSFUNC
#define MFCTOOLSTPL   extern template class MFCTOOLSCLASS
#endif

#if !defined INCLUDED_WBFLALL_H_
#include <WbflAll.h>
#endif

#if !defined INCLUDED_MFCTOOLS_AUTOLIB_H_
#include <MfcTools\AutoLib.h>
#endif

#endif // INCLUDED_MFCTOOLS_MFCTOOLSEXP_H_
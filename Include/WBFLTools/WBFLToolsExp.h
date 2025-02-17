///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright � 1999-2025  Washington State Department of Transportation
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

#ifndef INCLUDED_WBFLTOOLS_EXPORT_H_
#define INCLUDED_WBFLTOOLS_EXPORT_H_
#pragma once

#if defined (BUILDWBFLTOOLSLIB) && !defined(WBFLTOOLSLIB)
#define WBFLTOOLSCLASS __declspec(dllexport)
#define WBFLTOOLSFUNC  __declspec(dllexport)
#define WBFLTOOLSTPL   template class WBFLTOOLSCLASS
#elif defined(WBFLTOOLSLIB)
#define WBFLTOOLSCLASS
#define WBFLTOOLSFUNC
#define WBFLTOOLSTPL
#else
#define WBFLTOOLSCLASS __declspec(dllimport)
#define WBFLTOOLSFUNC  __declspec(dllimport)
#define WBFLTOOLSTPL   extern template class WBFLTOOLSCLASS
#endif

#if !defined INCLUDED_WBFLTOOLS_AUTOLIB_H_
#include <WBFLTools\AutoLib.h>
#endif

#endif // INCLUDED_WBFLTOOLS_EXPORT_H_
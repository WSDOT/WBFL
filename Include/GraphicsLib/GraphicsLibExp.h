///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
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

#ifndef INCLUDED_GRAPHICSLIB_GRAPHICSLIBEXP_H_
#define INCLUDED_GRAPHICSLIB_GRAPHICSLIBEXP_H_
#pragma once

// Define BUILDGRLIB when building this library
// For static builds, define GRLIB
// For static binding, define GRLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDGRLIB) && !defined(GRLIB)
#define GRCLASS __declspec(dllexport)
#define GRFUNC  __declspec(dllexport)
#define GRTPL   template class GRCLASS
#elif defined(GRLIB)
#define GRCLASS
#define GRFUNC
#define GRTPL
#else
#define GRCLASS __declspec(dllimport)
#define GRFUNC
#define GRTPL   extern template class GRCLASS
#endif

#if !defined INCLUDED_WBFLALL_H_
#include <WbflAll.h>
#endif

#if !defined INCLUDED_GRAPHICSLIB_AUTOLIB_H_
#include <GraphicsLib\AutoLib.h>
#endif

#endif // INCLUDED_GRAPHICSLIB_GRAPHICSLIBEXP_H_
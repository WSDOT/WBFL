///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

#ifndef INCLUDED_WBFLGENERICBRIDGE_GENERICBRIDGEEXP_H_
#define INCLUDED_WBFLGENERICBRIDGE_GENERICBRIDGEEXP_H_
#pragma once

// Define BUILDWBFLGENERICGBRIDGELIB when building this library
// For static builds, define WBFLGENERICBRIDGELIB
// For static binding, define WBFLGENERICBRIDGELIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDWBFLGENERICBRIDGELIB) && !defined(WBFLGENERICBRIDGELIB)
#define WBFLGENERICBRIDGECLASS __declspec(dllexport)
#define WBFLGENERICBRIDGEFUNC  __declspec(dllexport)
#define WBFLGENERICBRIDGETPL   template class WBFLGENERICBRIDGECLASS
#elif defined(WBFLGENERICBRIDGELIB)
#define WBFLGENERICBRIDGECLASS
#define WBFLGENERICBRIDGEFUNC
#define WBFLGENERICBRIDGETPL
#else
#define WBFLGENERICBRIDGECLASS __declspec(dllimport)
#define WBFLGENERICBRIDGEFUNC
#define WBFLGENERICBRIDGETPL   extern template class WBFLGENERICBRIDGECLASS
#endif

#if !defined INCLUDED_WBFLALL_H_
#include <WbflAll.h>
#endif

#if !defined INCLUDED_WBFLGENERICBRIDGE_AUTOLIB_H_
#include <GenericBridge\AutoLib.h>
#endif

#endif // INCLUDED_WBFLGENERICBRIDGE_GENERICBRIDGEEXP_H_
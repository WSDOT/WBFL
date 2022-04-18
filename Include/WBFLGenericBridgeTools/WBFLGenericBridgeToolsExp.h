///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#ifndef INCLUDED_WBFLGENERICBRIDGETOOLS_EXPORT_H_
#define INCLUDED_WBFLGENERICBRIDGETOOLS_EXPORT_H_
#pragma once

#if defined (BUILDWBFLGENERICBRIDGETOOLSLIB) && !defined(WBFLGENERICBRIDGETOOLSLIB)
#define WBFLGENERICBRIDGETOOLSCLASS __declspec(dllexport)
#define WBFLGENERICBRIDGETOOLSFUNC  __declspec(dllexport)
#define WBFLGENERICBRIDGETOOLSTPL   template class WBFLGENERICBRIDGETOOLSCLASS 
#elif defined(WBFLGENERICBRIDGETOOLSLIB)
#define WBFLGENERICBRIDGETOOLSCLASS 
#define WBFLGENERICBRIDGETOOLSFUNC  
#define WBFLGENERICBRIDGETOOLSTPL   
#else
#define WBFLGENERICBRIDGETOOLSCLASS __declspec(dllimport)
#define WBFLGENERICBRIDGETOOLSFUNC  __declspec(dllimport)
#define WBFLGENERICBRIDGETOOLSTPL   extern template class WBFLGENERICBRIDGETOOLSCLASS 
#endif

#if !defined INCLUDED_WBFLGENERICBRIDGETOOLS_AUTOLIB_H_
#include <WBFLGenericBridgeTools\AutoLib.h>
#endif

#endif // INCLUDED_WBFLTOOLS_EXPORT_H_
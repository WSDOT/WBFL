///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

#pragma once

// Define BUILDCOGOLIB when building this library
// For static builds, define COGOLIB
// For static binding, define COGOLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDCOGOLIB) && !defined(COGOLIB)
#define COGOCLASS __declspec(dllexport)
#define COGOFUNC  __declspec(dllexport)
#define COGOTPL   template class COGOCLASS
#elif defined(COGOLIB)
#define COGOCLASS
#define COGOFUNC
#define COGOTPL
#else
#define COGOCLASS __declspec(dllimport)
#define COGOFUNC  __declspec(dllimport)
#define COGOTPL   extern template class COGOCLASS
#endif

#include <WBFLCogo\AutoLib.h>

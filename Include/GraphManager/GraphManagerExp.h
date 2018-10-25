///////////////////////////////////////////////////////////////////////
// GraphManager - Manages graph definitions
// Copyright © 1999-2018  Washington State Department of Transportation
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

// Define BUILDGRAPHMANAGERLIB when building this library
// For static builds, define GRAPHMANAGERLIB
// For static binding, define GRAPHMANAGERLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDGRAPHMANAGERLIB) && !defined(GRAPHMANAGERLIB)
#define GRAPHMANAGERCLASS __declspec(dllexport)
#define GRAPHMANAGERFUNC  __declspec(dllexport)
#define GRAPHMANAGERFUNCTEMPLATE   template class GRAPHMANAGERCLASS
#elif defined(GRLIB)
#define GRAPHMANAGERCLASS
#define GRAPHMANAGERFUNC
#define GRAPHMANAGERFUNCTEMPLATE
#else
#define GRAPHMANAGERCLASS __declspec(dllimport)
#define GRAPHMANAGERFUNC
#define GRAPHMANAGERFUNCTEMPLATE   extern template class GRAPHMANAGERCLASS
#endif

#include <WbflAll.h>
#include <GraphManager\AutoLib.h>

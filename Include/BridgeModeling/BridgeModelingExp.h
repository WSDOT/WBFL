///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#ifndef INCLUDED_BRIDGEMODELING_BRIDGEMODELINGEXP_H_
#define INCLUDED_BRIDGEMODELING_BRIDGEMODELINGEXP_H_

// Define BUILDBMFLIB when building this library
// For static builds, define BMFLIB
// For static binding, define BMFLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDBMFLIB) && !defined(BMFLIB)
#define BMFCLASS __declspec(dllexport)
#define BMFFUNC  __declspec(dllexport)
#define BMFTPL   template class BMFCLASS
#elif defined(BMFLIB)
#define BMFCLASS
#define BMFFUNC
#define BMFTPL
#else
#define BMFCLASS __declspec(dllimport)
#define BMFFUNC
#define BMFTPL   extern template class BMFCLASS
#endif

#include <WbflAll.h>
#include <BridgeModeling\BmfTypes.h>
#include <BridgeModeling\AutoLib.h>

#define BMF_LEVEL_DRAW 0


#endif // INCLUDED_BRIDGEMODELING_BRIDGEMODELINGEXP_H_
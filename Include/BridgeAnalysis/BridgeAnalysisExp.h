///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_BRIDGEANALYSISEXP_H_
#define INCLUDED_BRIDGEANALYSIS_BRIDGEANALYSISEXP_H_

// Define BUILDBAMLIB when building this library
// For static builds, define BAMLIB
// For static binding, define BAMLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDBAMLIB) && !defined(BAMLIB)
#define BAMCLASS __declspec(dllexport)
#define BAMFUNC  __declspec(dllexport)
#define BAMTPL   template class BAMCLASS
#elif defined(BAMLIB)
#define BAMCLASS
#define BAMFUNC
#define BAMTPL
#else
#define BAMCLASS __declspec(dllimport)
#define BAMFUNC
#define BAMTPL   extern template class BAMCLASS
#endif

#if !defined INCLUDED_WBFLALL_H_
#include <WbflAll.h>
#endif

#if !defined INCLUDED_BRIDGEANALYSIS_BAMTYPES_H_
#include <BridgeAnalysis\BamTypes.h>
#endif

#if !defined INCLUDED_BRIDGEANALYSIS_AUTOLIB_H_
#include <BridgeAnalysis\AutoLib.h>
#endif


#endif // INCLUDED_BRIDGEANALYSIS_BRIDGEANALYSISEXP_H_
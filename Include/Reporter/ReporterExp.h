///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#ifndef INCLUDED_REPORTER_REPORTEREXP_H_
#define INCLUDED_REPORTER_REPORTEREXP_H_
#pragma once

// Define BUILDREPORTERLIB when building this library
// For static builds, define EXAMPLEIB
// For static binding, define REPORTERLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDREPORTERLIB) && !defined(REPORTERLIB)
#define REPORTERCLASS __declspec(dllexport)
#define REPORTERFUNC  __declspec(dllexport)
#define REPORTERTPL   template class REPORTERCLASS
#elif defined(REPORTERLIB)
#define REPORTERCLASS
#define REPORTERFUNC
#define REPORTERTPL
#else
#define REPORTERCLASS __declspec(dllimport)
#define REPORTERFUNC
#define REPORTERTPL   extern template class REPORTERCLASS
#endif

#include <WbflAll.h>
#include <Reporter\AutoLib.h>

#endif // INCLUDED_REPORTER_REPORTEREXP_H_
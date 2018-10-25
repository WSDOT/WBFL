///////////////////////////////////////////////////////////////////////
// ReportManager - Report Builder Management
// Copyright (C) 2009  Washington State Department of Transportation
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_REPORTMANAGER_REPORTMANAGEREXP_H_
#define INCLUDED_REPORTMANAGER_REPORTMANAGEREXP_H_

// Define BUILDREPORTMANAGERLIB when building this library
// For static builds, define REPORTMANAGERLIB
// For static binding, define REPORTMANAGERLIB
// For dynamic binding, nothing is required to be defined

#if defined (BUILDREPORTMANAGERLIB) && !defined(REPORTMANAGERLIB)
#define REPORTMANAGERCLASS __declspec(dllexport)
#define REPORTMANAGERFUNC  __declspec(dllexport)
#define REPORTMANAGERTPL   template class REPORTMANAGERCLASS
#elif defined(REPORTERLIB)
#define REPORTMANAGERCLASS
#define REPORTMANAGERFUNC
#define REPORTMANAGERTPL
#else
#define REPORTMANAGERCLASS __declspec(dllimport)
#define REPORTMANAGERFUNC
#define REPORTMANAGERTPL   extern template class REPORTMANAGERCLASS
#endif

#if !defined INCLUDED_WBFLALL_H_
#include <WbflAll.h>
#endif

#include <ReportManager\AutoLib.h>

#endif // INCLUDED_REPORTMANAGER_REPORTMANAGEREXP_H_
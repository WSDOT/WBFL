///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_EAF_EAF_H_
#define INCLUDED_EAF_EAF_H_
#pragma once

// This is a master include file for the EAF Package
#if defined(BUILDEAFLIB)
	#error Do not use this header file in the EAF Package
   #error It is for external users only
#endif

#include <afxext.h> // required for EAFMainFrame.h

#include <EAF\EAFTypes.h>
#include <EAF\EAFApp.h>
#include <EAF\EAFDocTemplate.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFChildFrame.h>

#endif //  INCLUDED_EAF_EAF_H_
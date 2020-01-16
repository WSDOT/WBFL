///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

// User Interface Hints
// Create any hints you like in the range 0x0002 to 0xFFFE
#define EAF_UIHINT_ENABLE_ALL                 0x0000  // all hints are enabled
#define EAF_UIHINT_FAVORITES_MENU             0x0001  // UI Hint for favorite report menu
#define EAF_UIHINT_DISABLE_ALL                0xFFFF  // disables all hints


// Doc/View update hints
#define EAF_HINT_BASE                     1000        
#define EAF_HINT_UPDATEERROR              EAF_HINT_BASE + 0
#define EAF_HINT_UNITS_CHANGING           EAF_HINT_BASE + 1 // units are about to be changed
#define EAF_HINT_UNITS_CHANGED            EAF_HINT_BASE + 2 // units have changed
#define EAF_HINT_FAVORITE_REPORTS_CHANGED EAF_HINT_BASE + 3
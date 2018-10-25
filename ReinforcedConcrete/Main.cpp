///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#include <ReinforcedConcrete\ReinfConcLib.h>
#include <ReinforcedConcrete\UnitTest.h>
#include <System\dllTest.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DIAG_DEFINE_GROUP(rca,DIAG_GROUP_DISABLE,0);


// Every DLL has an entry point DllEntryPoint
BOOL WINAPI DllEntryPoint( HINSTANCE /*hinstDll*/,
                           DWORD     /*fdwRreason*/,
                           LPVOID    /*plvReserved*/)
{
    return 1;   // Indicate that the DLL was initialized successfully.
}

// call unit test routines for all packages belonging to this dll.
bool WINAPI UnitTest(dbgLog& rlog)
{
   return rcaUnitTest::TestMe(rlog);
}

///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2019  Washington State Department of Transportation
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

#include <System\SysLib.h>
#include <System\UnitTest.h>
#include <System\dllTest.h>
#include <stdio.h>
#include <vector>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

HANDLE g_hModule = 0;

/*---------------------------------------------------------------------------
DllMain   Required for Windows DLL, called on process/thread attach/detach.
---------------------------------------------------------------------------*/
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD reason, 
                       LPVOID  )
{
   switch( reason ) {
   case DLL_PROCESS_ATTACH:
      break;

   case DLL_PROCESS_DETACH:
      break;

   case DLL_THREAD_ATTACH:
      break;

   case DLL_THREAD_DETACH:
      break;
   }

   return TRUE;
}


// call unit test routines for all packages belonging to this dll.
bool WINAPI UnitTest(dbgLog& rlog)
{
   return sysUnitTest::TestMe(rlog);
}

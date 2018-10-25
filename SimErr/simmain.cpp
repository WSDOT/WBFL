///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

/*---------------------------------------------------------------------------
Copyright (c) 1998 by On Target Software. Permission is granted to use this
source code only if this copyright notice and the web address
http://www.targetsoft.com both appear at the beginning of all source files
that contain excerpts or complete copies of the code herein.

Dave Pomerantz, March 1998.  Updates available at http://www.targetsoft.com
-----------------------------------------------------------------------------
simMain.cpp   Main program for error simulation DLL
              This includes the procedures that create and initialize
              the CSimulator object and call it to simulate errors.
---------------------------------------------------------------------------*/
#include <System\SysLib.h>

#define WIN32_LEAN_AND_MEAN
#if defined _AFXDLL
#include <afxwin.h>
#else
#if !defined STRICT
#define STRICT
#endif
#include <Windows.h>
#endif

#include <System\UnitTest.h>
#include <System\dllTest.h>

#include <stdio.h>
#include <vector>
using namespace std;

#include "SimErr\simdef.h"  // data definitions used in the function prototypes
#include "SimErr\simerr.h"  // error simulation functions
#include "simulate.h"

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

#if defined SIMERR

         /*******************
          *** Static Data ***
          *******************/

/*---------------------------------------------------------------------------
g_pErrorSimulator points to the one error simulator. 

This static pointer is in process global memory under Win32.  If you plan to 
use this DLL in Windows 3.1, do not use a static pointer.  Keep the pointer 
in the caller's address space and allocate from there.
---------------------------------------------------------------------------*/
CErrorSimulator *g_pErrorSimulator = 0;


         /**************************
          *** External Functions ***
          **************************/

/*---------------------------------------------------------------------------
SimErrInit  Allocate and initialize the error simulator.
---------------------------------------------------------------------------*/
bool SimErrInit(simerrInit_t *pInit)
{
   bool bOK = true;
   if (g_pErrorSimulator != 0)
   {
      bOK = false;
   }
   else
   {
      g_pErrorSimulator = new CErrorSimulator();
      if (g_pErrorSimulator)
      {
         bOK = g_pErrorSimulator->Init(pInit);
      }
   }
   return bOK;
}

/*---------------------------------------------------------------------------
SimErrExit  Write log file and print full report.
---------------------------------------------------------------------------*/
void SimErrExit(bool bFull)
{
   if (g_pErrorSimulator != 0)
   {
      g_pErrorSimulator->Exit(bFull);
      delete g_pErrorSimulator;
      g_pErrorSimulator = 0;
   }
}

/*---------------------------------------------------------------------------
SimErrEnable   Start or stop the tests.
---------------------------------------------------------------------------*/
bool SimErrEnable(bool enable)      // if true, enable error testing
{
   bool bWasEnabled = false;
   if (g_pErrorSimulator != 0)
   {
      bWasEnabled = g_pErrorSimulator->Enable(enable);
   }
   return bWasEnabled;
}

/*---------------------------------------------------------------------------
SimErr       Returns true to simulate an error
             If the error type is an exception, throws the exception.
             The error at this source file/line number will be simulated
             exactly once.
---------------------------------------------------------------------------*/
bool SimErr(const char * sourcePath, // name of source file   
            int nLine,               // line number in source file   
            int nType,               // caller-defined type of error
            long nCount,             // # times to simulate
            double nProb)            // probability each time
{
   bool bOK = false;  // false means don't simulate the error
   if (g_pErrorSimulator != 0)
   {
      char filename[CSimStmt::FILENAME_LEN];
      CSimStmt::TrimFilePath(filename, sourcePath);

      CSimStmt simStmt(filename, nLine, nType, nCount, nProb);
      bOK = g_pErrorSimulator->SimErr(simStmt);
   }
   return bOK;
}

#endif // SIMERR

// call unit test routines for all packages belonging to this dll.
bool WINAPI UnitTest(dbgLog& rlog)
{
   return sysUnitTest::TestMe(rlog);
}

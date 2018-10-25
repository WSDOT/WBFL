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
simcust.cpp  Customized error simulation for the sample program

The error simulator DLL has to be initialized with print functions and error 
types that are specific to each application.

This is the specific information for the sample program.
---------------------------------------------------------------------------*/
#include <System\SysLib.h>

#include <stdio.h>
#include <stdarg.h>
#include "SimErr\simcust.h"

//==================== DEFINE IF SIMULATING ERRORS ====================
#ifdef SIMERR 

const char *SAMPLE_ERROR_LOG = "simerr.txt";

/*---------------------------------------------------------------------------
g_errorInfo    defines each error type and whether it throws an exception
---------------------------------------------------------------------------*/
static const errorInfo_t g_errorInfo[] = 
{
{ SIMERR_RESULT_ERROR,       "RESULT",    SIMERR_TYPE_ERROR      },
{ SIMERR_MEMORY_ERROR,       "MEMORY",    SIMERR_TYPE_ERROR      },
{ SIMERR_XBASE_EXCEPTION,    "XBASE",     SIMERR_TYPE_EXCEPTION  },
{ SIMERR_MFC_EXCEPTION,      "MFC_XPT",   SIMERR_TYPE_EXCEPTION  }
};

/*---------------------------------------------------------------------------
PrintSimulatorMessage  Redirect messages from error simulator
---------------------------------------------------------------------------*/
static void PrintSimulatorMessage(const char *pMsg)
{
   char message[256];
   sprintf(message,"<SIMERR> %s\n", pMsg );
   ::OutputDebugString( message );
}

/*---------------------------------------------------------------------------
ThrowSimulatorException  Throw an exception corresponding to an error type.

The simulator calls this function to simulate an application-specific exception.
---------------------------------------------------------------------------*/
static void ThrowSimulatorException(int nErrorType,
                                    const char *pSourceFilename,
                                    int nSourceLine)
{
   switch(nErrorType)
   {
   case SIMERR_XBASE_EXCEPTION:
   case SIMERR_MFC_EXCEPTION:
	   // Do nothing. Exception is thrown from the simulator method
	   break;

   default:
      PrintSimulatorMessage("Invalid exception type");
   }
}

/****************************************************************************
****** NOTE: YOU SHOULD NOT NEED TO CHANGE ANYTHING BELOW THIS COMMENT ******
****************************************************************************/

/*---------------------------------------------------------------------------
ValidateErrorTypes  Make sure error info array matches ERROR_TYPE enum
---------------------------------------------------------------------------*/
static bool ValidateErrorTypes(void) 
{
   bool bOK = true;
   int nErrorTypes = sizeof(g_errorInfo) / sizeof(errorInfo_t);
   if (nErrorTypes == NUM_SIMERR_TYPES)
   {
      for (int i=0; bOK && (i < NUM_SIMERR_TYPES); ++i)
      {
         if (g_errorInfo[i].m_nErrorType != i)
         {
            bOK = false;
         }
      }
   }
   else
   {
      bOK = false;
   }
   if (!bOK)
   {
      PrintSimulatorMessage("error type enum does not match g_errorInfo.");
   }
   return bOK;
}

/*---------------------------------------------------------------------------
SimErrSampleInit  Allocate and initialize the sample error simulator.
---------------------------------------------------------------------------*/
bool SimErrCustomInit(int nSeed, SIMERR_TEST_TYPE testType) 
{
   bool bOK = false;

   // Make sure we didn't add an error type without modifying g_errorInfo
   bOK = ValidateErrorTypes();

   if (bOK)
   {
      // Fill in information that initializes the simulator
      simerrInit_t init;
      init.m_nVersion     = SIMERR_VERSION;  
      init.m_pFilename    = "errlog.txt"; 
      init.m_nSeed        = nSeed;     
      init.m_testType     = testType;  
      init.m_pfMsg        = PrintSimulatorMessage;     
      init.m_pfThrow      = ThrowSimulatorException;   
      init.m_pErrInfo     = g_errorInfo;  
      init.m_nErrTypes    = NUM_SIMERR_TYPES; 

      // Init simulator
      bOK = SimErrInit(&init);
   }
   if (!bOK)
   {
      PrintSimulatorMessage("error simulator could not be initialized.");
   }
   return bOK;
}

#endif //SIMERR

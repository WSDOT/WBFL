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
simulator.h  definition of CErrorSimulator

CErrorSimulator tracks all the statements that simulate failures in a
program, and decides when each statement should be triggered.
---------------------------------------------------------------------------*/
#ifndef SIMULATOR_H
#define SIMULATOR_H

#ifndef SIMSTMT_H
#include "simstmt.h"
#endif 

// typedef of STL vector containing list of error functions
typedef vector<CSimStmt>      CErrorArray;
typedef CErrorArray::iterator CErrorIterator;

//---------------------------------------------------------------------------
class CErrorSimulator 
{
//--- Public Operations ---
public:
   // Construction, destruction
   CErrorSimulator(void);
   virtual ~CErrorSimulator(void);

   // Initialization, termination
   bool Init(simerrInit_t *pInit);
   void Exit(bool bFull);

   // Error simulation: return true for error or throw exception
   bool SimErr(CSimStmt &testLine);

   // Enable/disable error simulations at runtime
   bool Enable(bool bEnable);

   // Set random number seed and systematic vs. random testing
   void SetProbability(int nSeed, SIMERR_TEST_TYPE testType);

   // Print report of which errors have fired
   void Report(bool bFullReport = true);

//--- Internal Implementation ---
protected:

   // Read & write the simulation log file
   bool Load(const char *pFilename = 0);
   bool Store(const char *pFilename = 0);

   // Lookup a simulation function entry in the array,
   //   add new entry if not found
   CSimStmt *GetSimStmt(CSimStmt &testLine);

   // Decide if a simulation should fire
   bool IsTriggered(CSimStmt *pSimStmt);

   // Reports: detail is each error, totals sums all errors
   void DetailReport(void);
   void TotalsReport(void);
   const char * FormatTargetCount(int nCount);

   // Information on an error type: name, whether it's an exception
   const char * GetTypeName(int nType);
   bool IsException(int nType);

   // All messages are routed through this function
   //   which calls the callback function
   void PrintMessage(const char *pFmtString, ...);

//--- Data Members ---
protected:
   // log of error functions in the source files
   char               m_pFilename[CSimStmt::FILENAME_LEN + 1];            
   CErrorArray        m_errorArray;   

   // status of testing
   bool               m_bEnabled;     // Testing is turned on
   SIMERR_TEST_TYPE   m_testType;     // whether to test each error exactly once

   // callbacks to customized functions
   pfSimErrMessage_t  m_pfMessage;   // error message function
   pfThrowException_t m_pfThrow;     // function that throws exceptions

   // definition of error types
   const errorInfo_t *m_pErrInfo;     // ptr to array of definitions
   int                m_nErrTypes;    // number of entries in array

   bool               m_bInitialized; // true if ready to simulate errors
};

#endif //SIMULATOR_H

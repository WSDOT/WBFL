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
simulator.cpp  implementation of CErrorSimulator

CErrorSimulator tracks program statements that simulate failures and decides
when each statement should be triggered.
---------------------------------------------------------------------------*/
#include <System\SysLib.h>

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <vector>
#include <typeinfo.h>
using namespace std;

#include <SimErr\simdef.h>  // data definitions used in the function prototypes
#include <SimErr\simerr.h>  // error simulation functions
#include "simulate.h"

/*---------------------------------------------------------------------------
CErrorSimulator   void constructor
---------------------------------------------------------------------------*/
CErrorSimulator::CErrorSimulator(void)
{
   m_pFilename[0]= '\0';

   m_bEnabled = false;
   m_testType = SIMERR_SYSTEMATIC;
   srand(1000);   // Seed random number generator
   m_pfMessage = 0;
   m_pfThrow   = 0;
   m_pErrInfo  = 0;
   m_nErrTypes = 0;
   m_bInitialized = false;
}
   
/*---------------------------------------------------------------------------
CErrorSimulator   destructor

NOTE: do not write a report or save the log file in here.  If the user 
      program fails, it's easier to reproduce the problem if the log file 
      is not updated on termination.
---------------------------------------------------------------------------*/
CErrorSimulator::~CErrorSimulator(void)
{
   m_errorArray.erase(m_errorArray.begin(), m_errorArray.end());
}

/*---------------------------------------------------------------------------
Init   Initialize error simulation
---------------------------------------------------------------------------*/
bool CErrorSimulator::Init(simerrInit_t *pInit) 
{
   bool bOK = true;
   // make sure the caller's version is correct
   if (pInit->m_nVersion != 1) // this library is version 1
   {
      bOK = false;
   }
   if (bOK)
   {
      // setup function pointers for callbacks
      m_pfMessage = pInit->m_pfMsg;
      m_pfThrow   = pInit->m_pfThrow;

      // get information on the error types
      m_pErrInfo  = pInit->m_pErrInfo;
      m_nErrTypes = pInit->m_nErrTypes;

      // determine how to handle random error generation
      SetProbability(pInit->m_nSeed, pInit->m_testType);

      // load simulator log file with error line entries from previous tests
      strncpy(m_pFilename, pInit->m_pFilename, CSimStmt::FILENAME_LEN);
      m_pFilename[CSimStmt::FILENAME_LEN] = '\0';
      Load(m_pFilename);

      // ready for testing
      Enable(true);
      m_bInitialized = true;
   }
   return bOK;
}

/*---------------------------------------------------------------------------
Exit  End the error simulation
---------------------------------------------------------------------------*/
void CErrorSimulator::Exit(bool bFull)   // if true, print full report
{
   if (m_bInitialized)
   {
      // print a report on test results
      Report(bFull);

      // write a new log file with the status of the error functions
      if (m_pFilename)
      {
         Store(m_pFilename);
      }
   }
}
   
/*---------------------------------------------------------------------------
Enable   Turn error simulation on or off.
---------------------------------------------------------------------------*/
bool CErrorSimulator::Enable(bool bEnable)
{
   bool bWasEnabled = m_bEnabled;

   m_bEnabled = bEnable;
   return bWasEnabled;
}

/*---------------------------------------------------------------------------
Load   Read an error-simulator log file into a vector of CSimStmt 
       entries.  Make a backup copy to permit repeatable testing.
---------------------------------------------------------------------------*/
bool CErrorSimulator::Load(const char *pFilename)
{
   bool bOK = true;
   FILE *pFile = 0;
   const char *ARCHIVE_COPY_NAME = "bkuplog.txt";

   try
   {
      // open the old simulator log file
      pFile = fopen(pFilename, "rt");
      if (pFile == 0)
      {
         PrintMessage("log file \"%s\" not found, test begins with first error",
            pFilename);
         bOK = false;
      }
      if (bOK)
      {  // read each line in the log into a CSimStmt object
         //  and append the object to the array.
         CSimStmt entry;
         while (entry.Read(pFile))
         {
            m_errorArray.push_back(entry);
         }
         if (ferror(pFile))
         {
            PrintMessage("error reading log file \"%s\", test begins with first error");
            bOK = false;
         }
      }
      if (pFile)
      {
         fclose(pFile);
      }
      if (bOK)
      {  // Before starting, make a copy of the current log
         // so the programmer can reproduce errors found in this session.
         PrintMessage("backup log file written to \"%s\"",
            ARCHIVE_COPY_NAME);
         bOK = Store(ARCHIVE_COPY_NAME);
      }
   }
   catch(...)
   {
      if (pFile)
      {
         PrintMessage("error reading log file \"%s\", test begins with first error");
         fclose(pFile);
      }
      bOK = false;
   }
   return bOK;
}

/*---------------------------------------------------------------------------
Store  Write the list of error functions to the log file.
---------------------------------------------------------------------------*/
bool CErrorSimulator::Store(const char *pFilename) // name of log file
{
   bool bOK = false;
   FILE *pFile = 0;

   try
   {  // Create or overwrite the simulator log with the array of 
      // CSimStmt objects; one object per ASCII line.
      pFile = fopen(pFilename, "wt");
      bOK = (pFile) ? true : false;

      CErrorIterator iter = m_errorArray.begin();
      while (bOK && (iter != m_errorArray.end()))
      {
         bOK = iter->Write(pFile);
         ++iter;
      }
      if (pFile)
      {
         fclose(pFile);
      }
   }
   catch(...)
   {
      if (pFile)
      {
         fclose(pFile);
      }
      bOK = false;
   }
   return bOK;
}

/*---------------------------------------------------------------------------
SetProbability    Seed the random number generator, or force all errors
                  to trigger regardless of probability
---------------------------------------------------------------------------*/
void CErrorSimulator::SetProbability(int nSeedArg,    // seed for random numbers
                                                      //   or use -1 for random seed
                                     SIMERR_TEST_TYPE testType) // systematic or random
{
   unsigned int nSeed;   
   if (nSeedArg == -1)
   {
      time_t nTime;
      time(&nTime);
      // Swap the bytes in the low word of the time.
      // This produces greater changes between  successive program runs.
      // I've found that slight variations in the seed produce only slight
      // variations in the random numbers.  
      unsigned int loByte  = (unsigned int) (nTime & 0x7F);
      unsigned int hiByte  = (unsigned int) ((nTime & 0xFF00) >> 8);
      nSeed = (loByte << 8) | hiByte;
   }
   else
   {
      nSeed = nSeedArg;
   }
   srand(nSeed);   // Seed the random number generator

   // if m_testType is SIMERR_SYSTEMATIC, trigger each error exactly once
   m_testType = testType;
   if (m_testType == SIMERR_SYSTEMATIC)
   {
      PrintMessage("Starting error simulator with a systematic test.");
   }
   else
   {
      PrintMessage("Starting error simulator with random number seed %d.", 
         nSeed);
   }
}

/*---------------------------------------------------------------------------
GetSimStmt  Look up the simulator statement corresponding to a given 
            source file and line number.  If not there, create a new entry.
            Return a pointer to the entry.
---------------------------------------------------------------------------*/
CSimStmt *CErrorSimulator::GetSimStmt(CSimStmt &newEntry)  
{
   bool           bMatch = false;
   CErrorIterator iter;
   CSimStmt *   pEntry = 0;    // points to error function record in the array

   // See if we already logged an entry at the same source file/line number.
   iter = m_errorArray.begin();
   while (!bMatch && (iter != m_errorArray.end()))
   {
      if ( (iter->m_nLine == newEntry.m_nLine) &&
           (strcmp(iter->m_strFile, newEntry.m_strFile)==0) )
      {
         bMatch = true;
         pEntry = iter;

         // update entry with any changes
         pEntry->m_nType        = newEntry.m_nType;
         pEntry->m_nTargetCount = newEntry.m_nTargetCount;
         pEntry->m_nProb        = newEntry.m_nProb;
      }
      ++iter;
   }
   if (!bMatch)
   {  // couldn't find an existing entry, create a new entry
      try
      {
         m_errorArray.push_back(newEntry);
         pEntry = &m_errorArray.back();
      }
      catch(...)
      {  // out of memory
         // This is a test utility: report the error but keep going.
         PrintMessage("**** memory exception in CErrorSimulator::GetSimStmt ****");
      }
   }
   return pEntry;
}

/*---------------------------------------------------------------------------
IsTriggered    Determine if an error should be triggered or an exception
               should be thrown.  
---------------------------------------------------------------------------*/
bool CErrorSimulator::IsTriggered(CSimStmt *pSimStmt)
{
   if (pSimStmt == 0)
   {  
      return false;
   }

   bool bIsTriggered = false;
   // get count of times triggered in this and previous sessions
   int nTotalCount = pSimStmt->m_nPrevCount + pSimStmt->m_nSessCount;

   // in a systematic test, every error is simulated exactly once,
   //   the first time it's encountered, regardless of the count
   //   and probability given in the SIMxxx function call.
   double nProb        = pSimStmt->m_nProb;
   int    nTargetCount = pSimStmt->m_nTargetCount;
   if (m_testType == SIMERR_SYSTEMATIC)
   {
      nProb        = 1.1;     // always trigger
      nTargetCount = 1;       //   exactly once
   }

   // if this statement allows an infinite count or if the
   //   target count hasn't been reached, OK to trigger failure
   if ((nTargetCount == -1) ||
       (nTargetCount > nTotalCount))
   {
      // always trigger if likelihood is greater than 1
      if (nProb >= 1.0)
      {
         bIsTriggered = true;
      }
      // otherwise roll the dice and see it it's time to trigger
      else
      {
         double nRollOfDice = double(rand()) / double(RAND_MAX);
         if (nProb >= nRollOfDice)
         {
            bIsTriggered = true;
         }
      }
   }
   return bIsTriggered;
}

/*---------------------------------------------------------------------------
SimErr  Tell the calling function that it should simulate an error.
        If the error type is for an exception, throw the exception here.
           If triggered, 
              print message
              for exceptions, throw exception. 
              for non-exceptions, return true.
           Otherwise return false.
---------------------------------------------------------------------------*/
bool CErrorSimulator::SimErr(CSimStmt &newSimStmt)
{
   bool bTriggered = false;
   if (m_bInitialized && m_bEnabled)
   {
      // Find the error entry or create a new one
      CSimStmt *pSimStmt = GetSimStmt(newSimStmt);

      // Determine if the error should be triggered.
      if (pSimStmt && IsTriggered(pSimStmt))
      {  
         bTriggered = true;
         pSimStmt->m_nSessCount++;

         PrintMessage("at %s(%d) *** SIMULATING %s %s ***",
                pSimStmt->m_strFile, pSimStmt->m_nLine,
                GetTypeName(pSimStmt->m_nType),
                IsException(pSimStmt->m_nType) ? "EXCEPTION" : "ERROR");

         if (IsException(pSimStmt->m_nType))
         {  // call the callback function to throw an exception
            (*m_pfThrow)(pSimStmt->m_nType,
                         pSimStmt->m_strFile,
                         pSimStmt->m_nLine);
         }
      }
   }
   return bTriggered;
}

/*---------------------------------------------------------------------------
Report         write detailed and summary reports of the number of errors
               triggered and the number not yet triggered.
---------------------------------------------------------------------------*/
void CErrorSimulator::Report(bool bFullReport)
{
   if (bFullReport)
   {
      DetailReport();
   }
   TotalsReport();
}

/*---------------------------------------------------------------------------
DetailReport   print a line for each error that was triggered and each
               test line that executed but has not yet triggered an error.
---------------------------------------------------------------------------*/
void CErrorSimulator::DetailReport(void)
{
   // print detail report header for triggered errors
   PrintMessage("");
   PrintMessage("*** ERRORS SIMULATED ***");
   PrintMessage("");
   PrintMessage("    File                 Line Error-Type Requested Total New");
   PrintMessage("------------------------------------------------------------");

   // for each simulation statement that has triggered, print its status
   CErrorIterator iter = m_errorArray.begin();
   int nUnsimulated = 0;   // count errors found but not yet simulated
   while (iter != m_errorArray.end())
   {
      if (iter->m_nSessCount || iter->m_nPrevCount)
      {
         PrintMessage("%s %-20s %4d %10s   %s  %4d %3d",
            (iter->m_nSessCount) ? "NEW" : "   ",
            iter->m_strFile, 
            iter->m_nLine, 
            GetTypeName(iter->m_nType),
            FormatTargetCount(iter->m_nTargetCount),
            iter->m_nPrevCount + iter->m_nSessCount, 
            iter->m_nSessCount);
      }
      else
      {  // SimErr calls found at runtime but not yet simulated
         ++nUnsimulated;
      }
      ++iter;
   }

   if (nUnsimulated != 0)
   {  // if errors were found at runtime, but not yet simulated,
      //    print detail report for untriggered errors
      PrintMessage("");
      PrintMessage("*** ERRORS NOT YET SIMULATED ***");
      PrintMessage("");

      PrintMessage("    File                 Line Error-Type Requested Probability");
      PrintMessage("--------------------------------------------------------------");

      // for each simulation statement that has not triggered, print its status
      iter = m_errorArray.begin();
      while (iter != m_errorArray.end())
      {
         if ((iter->m_nSessCount == 0) && (iter->m_nPrevCount == 0))
         {
            PrintMessage("    %-20s %4d %10s   %s     %7.2lf",
               iter->m_strFile, iter->m_nLine, 
               GetTypeName(iter->m_nType),
               FormatTargetCount(iter->m_nTargetCount),
               iter->m_nProb);
         }
         ++iter;
      }
   }

}

/*---------------------------------------------------------------------------
TotalsReport   Summarize the number of errors triggered and waiting for
               each type of error.
---------------------------------------------------------------------------*/
void CErrorSimulator::TotalsReport(void)
{
   // the last entry in the array is the grand total of all previous entries
   int *pnRemaining = new int[m_nErrTypes+1];
   int *pnTriggered = new int[m_nErrTypes+1];
   int nType;
   int nSessCount = 0;

   if ((pnRemaining == 0) || (pnTriggered == 0))
   {
      PrintMessage("insufficient memory to prepare error simulation report");
   }

   // Clear totals
   for (nType=0; nType <= m_nErrTypes; ++nType)
   {
      pnRemaining[nType] = 0;
      pnTriggered[nType] = 0;
   }

   // Sum triggered & remaining errors by error type
   CErrorIterator iter = m_errorArray.begin();
   while (iter != m_errorArray.end())
   {
      nType = iter->m_nType;
      if ((nType >= 0) && (nType <= m_nErrTypes))
      {
         if (iter->m_nSessCount)
         {
            ++nSessCount;
         }
         if (iter->m_nPrevCount || iter->m_nSessCount)
         {
            pnTriggered[nType]++;
         }
         else
         {
            pnRemaining[nType]++;
         }
      }
      else
      {
         PrintMessage("invalid exception type at %s(%d)",
             iter->m_strFile, iter->m_nLine);
      }
      ++iter;
   }

   // print summary header
   PrintMessage("");
   PrintMessage("*** ERROR SIMULATION TOTALS ***");
   PrintMessage("");
   PrintMessage("Type        Triggered Remaining Total");
   PrintMessage("-------------------------------------");

   // print totals for each error type and add to grand totals
   for (nType=0; nType<m_nErrTypes; ++nType)
   {
      PrintMessage("%-10s       %4d      %4d  %4d",
         GetTypeName(nType), 
         pnTriggered[nType],
         pnRemaining[nType], 
         pnTriggered[nType] + pnRemaining[nType]);

      pnTriggered[m_nErrTypes] += pnTriggered[nType];
      pnRemaining[m_nErrTypes] += pnRemaining[nType];
   }

   // report the grand totals for all error types
   PrintMessage("-------------------------------------");
   PrintMessage("%-10s       %4d      %4d  %4d",
         "ALL TYPES", 
         pnTriggered[m_nErrTypes],
         pnRemaining[m_nErrTypes], 
         pnTriggered[m_nErrTypes] + pnRemaining[m_nErrTypes]);
   PrintMessage("");
   PrintMessage("Triggered %d error(s) in this session.", nSessCount);

   delete [] pnRemaining;
   delete [] pnTriggered;
}

/*---------------------------------------------------------------------------
GetTypeName    return the descriptive name for a given error type
---------------------------------------------------------------------------*/
const char * CErrorSimulator::GetTypeName(int nType)
{
   const char *pUnknown = "UNKNOWN";
   const char *pName;
   if ((nType >= 0) &&
       (nType < m_nErrTypes))
   {
      pName = m_pErrInfo[nType].m_pName;
   }
   else
   {
      pName = pUnknown;
   }
   return pName;
}

/*---------------------------------------------------------------------------
FormatTargetCount    Format text description of target count
---------------------------------------------------------------------------*/
const char * CErrorSimulator::FormatTargetCount(int nCount)
{
   static char strTarget[32];

   if (nCount != SIMERR_FOREVER)
   {
      sprintf(strTarget, "%7d", nCount);
   }
   else
   {
      strcpy(strTarget, "FOREVER");
   }
   return strTarget;
}

/*---------------------------------------------------------------------------
IsException    return true if an error type throws an exception
---------------------------------------------------------------------------*/
bool CErrorSimulator::IsException(int nType)
{
   bool bException = false;
   if ((nType >= 0) &&
       (nType < m_nErrTypes))
   {
      if (m_pErrInfo[nType].m_bException == SIMERR_TYPE_EXCEPTION)
      {
         bException = true;
      }
   }
   return bException;
}

/*---------------------------------------------------------------------------
PrintMessage   All messages goes through this function.
               This calls the m_pfMessage callback function to write the
               message.
---------------------------------------------------------------------------*/
void CErrorSimulator::PrintMessage(const char *pFmtString, ...)
{
#define MSG_LIMIT 512   // long enough to accommodate full pathnames
   char     msg[MSG_LIMIT+1];
   va_list  argPtr;

   // Format the message
   va_start(argPtr, pFmtString);
   vsprintf(msg, pFmtString, argPtr);

   // send the formatted message to the callback function
   //    this allows the caller to decide where to send the messages
   (*m_pfMessage)(msg);
}


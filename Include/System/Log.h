///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_LOG_H_
#define INCLUDED_SYSTEM_LOG_H_
#pragma once

#include <WBFLTypes.h>
#include <ostream>
#include <string>
#include <vector>
#include <System\DbgBuild.h>
#include <System\DumpContext.h>
#include <tchar.h>

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//
// Test macros

#define TESTME_PROLOGUE(className) bool bpf=true; \
                                   std::_tostringstream erro; \
                                   rlog <<endl<< _T("Begin Testing class ")<<_T(className)<<_T(" at ")<<__LINE__<<_T(" in ")<<_T(__FILE__)<<endl;

#define TESTME_EPILOG(className)   rlog<<_T("End Testing class ")<<_T(className)<<_T(" at ")<<__LINE__<<_T(" in ")<<_T(__FILE__)<<endl; \
                                   return bpf;

#define TEST_FAIL       {bpf = false; \
                         erro.flush(); \
                         erro.seekp(std::ios_base::beg); \
                         erro.clear(); \
                         erro <<_T("*** Failed at ")<<_T(__FILE__)<<_T(" Line ")<<__LINE__; \
                         rlog.AddEntryToLog(erro.str(), dbgLog::Failed); \
                         rlog << erro.str();} 

#define TEST_PASS       {erro.flush(); \
                         erro.seekp(std::ios_base::beg); \
                         erro.clear(); \
                         erro <<_T("    Passed at ")<<_T(__FILE__)<<_T(" Line ")<<__LINE__; \
                         rlog.AddEntryToLog(erro.str(), dbgLog::Passed); \
                         rlog << erro.str();}

#define TEST_NOT_IMPLEMENTED(msg) {erro.flush(); \
                                   erro.seekp(std::ios_base::beg); \
                                   erro.clear(); \
                                   erro <<_T("         Missing test at ")<<_T(__FILE__)<<_T(" Line ")<<__LINE__<<std::endl; \
                                   erro <<_T("... ") << msg << std::endl; \
                                   rlog.AddEntryToLog(erro.str(), dbgLog::NotImplemented); \
                                   rlog << erro.str();}

#define TRY_TESTME(pf)    {if ((pf)) \
                        { \
                           TEST_PASS \
                           rlog << endl; \
                        } \
                        else \
                        { \
                           TEST_FAIL  \
                           rlog << endl; \
                        }}

#define TEST_FAIL_EX(msg) TEST_FAIL \
                          rlog <<_T(" ")<< msg <<endl;
                            
#define TEST_PASS_EX(msg) TEST_PASS \
                          rlog<<_T(" ")<< msg <<endl;

#define TRY_TESTME_EX(pf,msg) if ((pf)) \
                            { \
                              TEST_PASS_EX(msg) \
                            } \
                            else \
                            { \
                              TEST_FAIL_EX(msg) \
                            }

/*****************************************************************************
CLASS 
   dbgLog

   Message Logging class for unit testing


DESCRIPTION


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 05.27.1998 : Created file
*****************************************************************************/

class SYSCLASS dbgLog
{
public:
   // GROUP: LIFECYCLE
   enum EntryType {Passed, Failed, NotImplemented};

   //------------------------------------------------------------------------
   // Default constructor - all information gets dumped to screen
   dbgLog();

   //------------------------------------------------------------------------
   // Constructor - specify where information piped to ostream goes to.
   dbgLog(dbgDumpContext* pDumpCtx);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~dbgLog();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Add an entry to the error log.
   void AddEntryToLog(std::_tstring& msg, EntryType type);

   //------------------------------------------------------------------------
   // Get total number of entries in log
   size_t GetNumEntries() const;

   //------------------------------------------------------------------------
   // Get number of failed tests in log
   size_t GetNumErrors() const;

   //------------------------------------------------------------------------
   // Get number of tests of a given type
   size_t GetTestCount(EntryType type) const;

   //------------------------------------------------------------------------
   // Dump Only Entries of a certain type
   void DumpFilteredLog(EntryType type);

   //------------------------------------------------------------------------
   // Dump all entries in log
   void DumpEntireLog();

   // GROUP: ACCESS
   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // 
   // Inserters for various built-ins
   dbgLog& operator<<(const std::_tstring& s);
   dbgLog& operator<<(LPCTSTR s);
   dbgLog& operator<<(TCHAR c);    
   dbgLog& operator<<(bool n);
   dbgLog& operator<<(Int16 n);
   dbgLog& operator<<(Uint16 n);
   dbgLog& operator<<(Int32 n);
   dbgLog& operator<<(Uint32 n);
   dbgLog& operator<<(Int64 n);
   dbgLog& operator<<(Uint64 n);
   dbgLog& operator<<(Float32 n);    
   dbgLog& operator<<(Float64 n);
   dbgLog& operator<<(Float80 n);
   dbgLog& operator<<(void * n);
   dbgLog& operator<<(dbgLog& (*pf)(dbgLog&));
   
   //------------------------------------------------------------------------
   void SetDumpContext(dbgDumpContext* pDumpCtx);

   //------------------------------------------------------------------------
   // Access to a dump context for testing Dump functions.
   dbgDumpContext& GetDumpCtx();

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //------------------------------------------------------------------------
   // store the error log as a vector of strings
   struct LogEntry
   {
      EntryType   Type;
      std::_tstring Msg;
   };
   typedef std::vector<LogEntry> EntryVec;
   typedef EntryVec::iterator    EntryVecIterator;
   typedef EntryVec::const_iterator    ConstEntryVecIterator;
#pragma warning ( disable : 4251 ) // never used by clients
   EntryVec m_ErrorLog;

   dbgDumpContext m_DefDumpCtx; // Use this if one is not supplied.
   dbgDumpContext* m_pDumpCtx;

   size_t    m_NumErrors;

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Copy constructor
   dbgLog(const dbgLog& rOther);
   //------------------------------------------------------------------------
   // Assignment operator
   dbgLog& operator = (const dbgLog& rOther);
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
};

// INLINE METHODS
//
inline void dbgLog::SetDumpContext(dbgDumpContext* pDumpCtx) { m_pDumpCtx = pDumpCtx; }
inline dbgDumpContext& dbgLog::GetDumpCtx() {return *m_pDumpCtx;}

// EXTERNAL REFERENCES
//

//------------------------------------------------------------------------
// define our own endl function
inline dbgLog& endl(dbgLog& rl) {rl<<_T("\n"); return rl;}




#endif // INCLUDED_SYSTEM_LOG_H_

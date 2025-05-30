///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include <System\SysExp.h>
#include <System\LogContext.h>
#include <System\DebugWindowLogContext.h>
#include <ostream>
#include <string>
#include <vector>
#include <tchar.h>

/// @def TESTME_PROLOGUE(className) 
/// @brief Prologue code for a unit test method
/// @remark This macro is obsolete
#define TESTME_PROLOGUE(className) bool bpf=true; \
                                   std::_tostringstream erro; \
                                   rlog <<WBFL::Debug::endl<< _T("Begin Testing class ")<<_T(className)<<_T(" at ")<<__LINE__<<_T(" in ")<<_T(__FILE__)<<WBFL::Debug::endl;

/// @def TESTME_EPILOG(className)
/// @brief Epilog code for a unit test method
/// @remark This macro is obsolete
#define TESTME_EPILOG(className)   rlog<<_T("End Testing class ")<<_T(className)<<_T(" at ")<<__LINE__<<_T(" in ")<<_T(__FILE__)<<WBFL::Debug::endl; \
                                   return bpf;

/// @def TEST_FAIL
/// @brief Logs a failed unit test
/// @remark This macro is obsolete
#define TEST_FAIL       {bpf = false; \
                         erro.flush(); \
                         erro.seekp(std::ios_base::beg); \
                         erro.clear(); \
                         erro <<_T("*** Failed at ")<<_T(__FILE__)<<_T(" Line ")<<__LINE__; \
                         rlog.LogTestResult(erro.str(), WBFL::Debug::UnitTestLog::TestResult::Failed); \
                         rlog << erro.str();} 

/// @def TEST_PASS
/// @brief Logs a successful unit test
/// @remark This macro is obsolete
#define TEST_PASS       {erro.flush(); \
                         erro.seekp(std::ios_base::beg); \
                         erro.clear(); \
                         erro <<_T("    Passed at ")<<_T(__FILE__)<<_T(" Line ")<<__LINE__; \
                         rlog.LogTestResult(erro.str(), WBFL::Debug::UnitTestLog::TestResult::Passed); \
                         rlog << erro.str();}

/// @def TEST_NOT_IMPLEMENTED(msg)
/// @brief Logs a unit these that is not implemented. This helps to identify code blocks that need to be revisited and completed
/// @remark This macro is obsolete
#define TEST_NOT_IMPLEMENTED(msg) {erro.flush(); \
                                   erro.seekp(std::ios_base::beg); \
                                   erro.clear(); \
                                   erro <<_T("         Missing test at ")<<_T(__FILE__)<<_T(" Line ")<<__LINE__<<std::endl; \
                                   erro <<_T("... ") << msg << std::endl; \
                                   rlog.LogTestResult(erro.str(), WBFL::Debug::UnitTestLog::TestResult::NotImplemented); \
                                   rlog << erro.str();}

/// @def TRY_TESTME(pf)
/// @brief Logs a unit test
/// @remark This macro is obsolete
#define TRY_TESTME(pf)    {if ((pf)) \
                        { \
                           TEST_PASS \
                           rlog << WBFL::Debug::endl; \
                        } \
                        else \
                        { \
                           TEST_FAIL  \
                           rlog << WBFL::Debug::endl; \
                        }}

/// @def TRY_TESTME_CATCH(pf)
/// @brief Logs a unit test expected to throw an exception
/// @remark This macro is obsolete
#define TRY_TESTME_CATCH(pf) {try{if((pf)) TRY_TESTME(false);}catch(...){TRY_TESTME(true);}}

/// @def TEST_FAIL_EX(msg)
/// @brief Logs a failed unit test with a custom message
/// @remark This macro is obsolete
#define TEST_FAIL_EX(msg) TEST_FAIL \
                          rlog <<_T(" ")<< msg <<WBFL::Debug::endl;
                            
/// @def TEST_PASS_EX(msg)
/// @brief Logs a successful unit test with a custom message
/// @remark This macro is obsolete
#define TEST_PASS_EX(msg) TEST_PASS \
                          rlog<<_T(" ")<< msg <<WBFL::Debug::endl;

/// @def 
/// @brief Logs a unit test with a custom message
/// @remark This macro is obsolete
#define TRY_TESTME_EX(pf,msg) if ((pf)) \
                            { \
                              TEST_PASS_EX(msg) \
                            } \
                            else \
                            { \
                              TEST_FAIL_EX(msg) \
                            }

namespace WBFL
{
   namespace Debug
   {
      /// Logs unit tests results to a LogContext
      /// @remark This class is obsolete. Unit tests should be implemented in the Visual Studio unit test framework
      class SYSCLASS UnitTestLog
      {
      public:
         enum class TestResult {Passed, Failed, NotImplemented};

         /// Logs messages to the debugger output window
         UnitTestLog();

         /// Logs messages to the provided logging context
         UnitTestLog(LogContext& context);

         UnitTestLog(const UnitTestLog&) = delete;

         virtual ~UnitTestLog();

         UnitTestLog& operator=(const UnitTestLog&) = delete;

         /// Add an entry to the error log.
         void LogTestResult(const std::_tstring& msg, TestResult type);

         /// Get total number of entries in log
         size_t GetNumEntries() const;

         /// Get number of failed tests in log
         size_t GetNumErrors() const;

         /// Get number of tests of a given type
         size_t GetTestCount(TestResult type) const;

         /// Dump Only Entries of a certain type
         void DumpFilteredLog(TestResult type) const;

         /// Dump all entries in log
         void DumpEntireLog() const;

         UnitTestLog& operator<<(const std::_tstring& s);
         UnitTestLog& operator<<(LPCTSTR s);
         UnitTestLog& operator<<(TCHAR c);    
         UnitTestLog& operator<<(bool n);
         UnitTestLog& operator<<(Int16 n);
         UnitTestLog& operator<<(Uint16 n);
         UnitTestLog& operator<<(Int32 n);
         UnitTestLog& operator<<(Uint32 n);
         UnitTestLog& operator<<(Int64 n);
         UnitTestLog& operator<<(Uint64 n);
         UnitTestLog& operator<<(Float32 n);    
         UnitTestLog& operator<<(Float64 n);
         UnitTestLog& operator<<(Float80 n);
         UnitTestLog& operator<<(void * n);
         UnitTestLog& operator<<(UnitTestLog& (*pf)(UnitTestLog&));
   
         /// Sets the logging context
         void SetLogContext(LogContext& context);

         // Gets the logging context
         LogContext& GetLogContext();

      private:
#pragma warning ( disable : 4251 ) // m_ErrorLog is not accessible to clients
         std::vector<std::pair<TestResult, std::_tstring>> m_ErrorLog;

         DebugWindowLogContext m_DefaultContext; // Use this if one is not supplied.
         LogContext* m_pContext{ &m_DefaultContext };

         size_t    m_NumErrors{ 0 };
      };

      SYSFUNC UnitTestLog& endl(UnitTestLog& rl);
   };
};

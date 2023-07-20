///////////////////////////////////////////////////////////////////////
// UnitTest - Utility program to run unit tests on WBFL DLL's
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <System\System.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// DLLs using this unit test framework must
// 1) Add "EXPORTS UnitTest @1" to their .def file
// 2) Implement the UnitTest method (typically done in main)
// 
// #include <System/dllTest.h>
// #include <Header_for_class_to_be_tested.h>
// bool WINAPI UnitTest(WBFL::Debug::Log& rlog)
// {
//    bool tst = true;
//    tst &= Class_to_be_tested::TestMe(rlog);
//    return tst;
// }
// 
// 3) Implement TestMe static methods on each class
// 
// #if defined _UNITTEST
// bool Class_to_be_tested::TestMe(WBFL::Debug::Log& rlog)
// {
//    TESTME_PROLOGUE("Class_to_be_tested");
// 
//    TRY_TESTME(IsZero(0.0));
// 
//    TESTME_EPILOG("Class_to_be_tested");
// }
// #endif // _UNITTEST

bool TestDll(LPCTSTR plibname, WBFL::Debug::Log& rlog);

// put names of all dll's to be tested here:
static LPCTSTR lib_list[] = { _T("Dummy.dll") // the initializer list needs at least one entry
                                 //_T("WBFLRCSection.dll"), // converted to VS unit test framework
                                 //_T("WBFLStability.dll"), // converted to VS unit test framework
                                 //_T("WBFLSystem.dll"),// converted to VS unit test framework
                                 // _T("WBFLRoark.dll"), // converted to VS unit test framework
                                 //_T("WBFLGraphing.dll"),// converted to VS unit test framework
                                 //_T("WBFLGeomModel.dll"), // converted to VS unit test framework
                                 //_T("WBFLLibraryFw.dll"), // converted to VS unit test framework
                                 //_T("WBFLLrfd.dll"), // converted to VS unit test framework
                                 //_T("WBFLMaterials.dll"), // converted to VS unit test framework
                                 //_T("WBFLMath.dll"), // converted to VS unit test framework
                                 //_T("WBFLUnits.dll"), // converted to VS unit test framework
                                 //_T("WBFLEAF.dll"), // converted to VS unit test framework
                                 //_T("WBFLEngTools.dll"), // converted to VS unit test framework
                                 //_T("WBFLCoordGeom.dll") //converted to VS unit test framework
                                 //_T("WBFLBridgeAnalysis.dll"), // not implemented - just stub code
                                 //_T("WBFLBridgeModeling.dll") // not implemented - just stub code
                                };

int main()
{
   bool st = 0;

   WBFL::Debug::Diagnostics::EnableWarnPopup(false);

   // create a test logger
#if defined _DEBUG
   WBFL::Debug::FileLogContext dc(_T("UnitTest_Debug.Log"));
#else
   WBFL::Debug::FileLogContext dc(_T("UnitTest_Release.Log"));
#endif
   WBFL::Debug::Log tl(dc);


   // send intro messages to screen and file
   WBFL::System::Date now_start;
   tl << _T("*** Start WBFL Unit Testing at ") << now_start.AsString() << _T(" ***") << WBFL::Debug::endl;
   std::_tcout << _T("*** Start WBFL Unit Testing at ")<< now_start <<_T("  ***") << std::endl;


   // run testme's for all libraries
   int n = sizeof(lib_list)/sizeof(TCHAR*);
   for (int i = 0; i<n; i++)
      st |= TestDll(lib_list[i], tl);

   // Test reporting
   tl << WBFL::Debug::endl;
   tl << _T("Total number of tests           : ") << tl.GetNumEntries() << WBFL::Debug::endl;
   tl << _T("Number of Passing tests         : ") << tl.GetTestCount( WBFL::Debug::Log::TestResult::Passed ) << WBFL::Debug::endl;
   tl << _T("Number of Failing tests         : ") << tl.GetTestCount( WBFL::Debug::Log::TestResult::Failed ) << WBFL::Debug::endl;
   tl << _T("Number of tests not implemented : ") << tl.GetTestCount( WBFL::Debug::Log::TestResult::NotImplemented ) << WBFL::Debug::endl;

   dc << WBFL::Debug::endl;
   tl.DumpFilteredLog( WBFL::Debug::Log::TestResult::Failed );

   WBFL::System::Date now_end;
   tl << _T("*** Finished WBFL Unit Testing at ") << now_end.AsString() << _T(" ***") << WBFL::Debug::endl;
   std::_tcout << _T("*** Finished WBFL Unit Testing at ")<< now_end <<_T("  ***") << std::endl;

   return st ? 1 : 0;
}


bool TestDll(LPCTSTR plibname, WBFL::Debug::Log& rlog)
{
   HINSTANCE hLibrary;
   pUnitTest ptst;
   bool      bt = false;
   std::_tostringstream ost;

   std::_tstring dllname(plibname);

   rlog << WBFL::Debug::endl<<_T("**** Begin Testing DLL: ")<< dllname <<_T(" ****")<< WBFL::Debug::endl;

   hLibrary = LoadLibrary(dllname.c_str());
   if (hLibrary!=nullptr)
   {
      ptst = (pUnitTest)GetProcAddress(hLibrary, "UnitTest");
      if (ptst!=nullptr)
      {
         // run UnitTest routine for dll.
         try
         {
             bt = (*ptst)(rlog);
         }
         catch(WBFL::System::XBase* xb)
         {
            ost<<_T("*** Failed *** Handled uncaught sysXBase exception from :")<< dllname<<std::endl
               <<_T("Reason was ")<<xb->GetReason()<<std::endl;
            rlog << ost.str();
            rlog.LogTestResult(ost.str(), WBFL::Debug::Log::TestResult::Failed);
         }
         catch (WBFL::System::XBase& xb)
         {
            ost << _T("*** Failed *** Handled uncaught sysXBase exception from :") << dllname << std::endl
               << _T("Reason was ") << xb.GetReason() << std::endl;
            rlog << ost.str();
            rlog.LogTestResult(ost.str(), WBFL::Debug::Log::TestResult::Failed);
         }
         catch (std::exception& e)
         {
            ost << _T("*** Failed *** Handled uncaught std::exception from :") << dllname << std::endl
               << _T("Reason was ") << e.what() << std::endl;
            rlog << ost.str();
            rlog.LogTestResult(ost.str(), WBFL::Debug::Log::TestResult::Failed);
         }
         catch(...)
         {
            ost<<_T("*** Failed *** Handled uncaught exception from :")<< dllname<<std::endl;
            rlog << ost.str();
            rlog.LogTestResult(ost.str(), WBFL::Debug::Log::TestResult::Failed);
         }

         FreeLibrary(hLibrary);

      }
      else
      {
         //failed to get UnitTest from dll
         ost<<_T("*** Failed *** Failed to load UnitTest function from: ")<< dllname<<std::endl;
         rlog << ost.str();
         rlog.LogTestResult(ost.str(), WBFL::Debug::Log::TestResult::Failed);
      }
   }
   else
   {
      // dll failed to load
      ost<<_T("Error Loading DLL: ")<< dllname;
      DWORD dwError = GetLastError();
      LPSTR messageBuffer = nullptr;
      size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);


      ost << _T(" Error ") << dwError << _T(" ") << messageBuffer << std::endl;

      rlog << ost.str();
      rlog.LogTestResult(ost.str(), WBFL::Debug::Log::TestResult::Failed);

      //Free the buffer.
      LocalFree(messageBuffer);
   }

   rlog << _T("**** End Testing DLL: ")<< dllname <<_T(" ****")<< WBFL::Debug::endl;

   return bt;
}

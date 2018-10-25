///////////////////////////////////////////////////////////////////////
// UnitTest - Utility program to run unit tests on WBFL DLL's
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

#include <System\System.h>
#include <tchar.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


bool TestDll(LPCTSTR plibname, dbgLog& rlog);

// put names of all dll's to be tested here:
static LPCTSTR lib_list[] = {_T("WBFLSystem.dll"),
                                 _T("WBFLRoark.dll"),
                                 _T("WBFLGeometricPrimitives.dll"),
                                 _T("WBFLGraphicsLib.dll"),
                                 _T("WBFLGeomModel.dll"),
                                 _T("WBFLLibraryFw.dll"),
                                 _T("WBFLLrfd.dll"),
                                 _T("WBFLMaterial.dll"),
                                 _T("WBFLMath.dll"),
                                 _T("WBFLReinforcedConcrete.dll"),
                                 _T("WBFLUnitMgt.dll"),
                                 _T("WBFLUnits.dll"),
                                 _T("WBFLBridgeAnalysis.dll"),
                                 _T("WBFLBridgeModeling.dll")};

int main()
{
   bool st=0;

   dbgDiagBase::EnableWarnPopup(false);

   // create a test logger
#if defined _DEBUG
   dbgFileDumpContext dc(_T("UnitTest_Debug.Log"));
#else
   dbgFileDumpContext dc(_T("UnitTest_Release.Log"));
#endif
   dbgLog tl(&dc);


   // send intro messages to screen and file
   sysDate now_start;
   tl << _T("*** Start WBFL Unit Testing at ") << now_start.AsString() << _T(" ***") << endl;
   std::_tcout << _T("*** Start WBFL Unit Testing at ")<< now_start <<_T("  ***") << std::endl;


   // run testme's for all libraries
   int n = sizeof(lib_list)/sizeof(TCHAR*);
   for (int i=0; i<n; i++)
      st |= TestDll(lib_list[i], tl);

   // Test reporting
   tl << endl;
   tl << _T("Total number of tests           : ") << tl.GetNumEntries() << endl;
   tl << _T("Number of Passing tests         : ") << tl.GetTestCount( dbgLog::Passed ) << endl;
   tl << _T("Number of Failing tests         : ") << tl.GetTestCount( dbgLog::Failed ) << endl;
   tl << _T("Number of tests not implemented : ") << tl.GetTestCount( dbgLog::NotImplemented ) << endl;

   dc << endl;
   tl.DumpFilteredLog( dbgLog::Failed );

   sysDate now_end;
   tl << _T("*** Finished WBFL Unit Testing at ") << now_end.AsString() << _T(" ***") << endl;
   std::_tcout << _T("*** Finished WBFL Unit Testing at ")<< now_end <<_T("  ***") << std::endl;

   return st ? 1 : 0;
}


bool TestDll(LPCTSTR plibname, dbgLog& rlog)
{
   HINSTANCE hLibrary;
   pUnitTest ptst;
   bool      bt;
   std::_tostringstream ost;

   std::_tstring dllname(plibname);

   rlog << endl<<_T("**** Begin Testing DLL: ")<< dllname <<_T(" ****")<<endl;

   hLibrary = LoadLibrary(dllname.c_str());
   if (hLibrary!=NULL)
   {
      ptst = (pUnitTest)GetProcAddress(hLibrary, "UnitTest");
      if (ptst!=NULL)
      {
         // run UnitTest routine for dll.
         try
         {
             bt = (*ptst)(rlog);
         }
         catch(sysXBase* xb)
         {
            ost<<_T("Handled uncaught sysXBase exception from :")<< dllname<<std::endl
               <<_T("Reason was ")<<xb->GetReason()<<std::endl;
            rlog << ost;
            rlog.AddEntryToLog(ost.str(), dbgLog::Failed);
         }
         catch(...)
         {
            ost<<_T("Handled uncaught exception from :")<< dllname<<std::endl;
            rlog << ost;
            rlog.AddEntryToLog(ost.str(), dbgLog::Failed);
         }

         FreeLibrary(hLibrary);

      }
      else
      {
         //failed to get UnitTest from dll
         ost<<_T("Failed to load UnitTest function from: ")<< dllname<<std::endl;
         rlog << ost;
         rlog.AddEntryToLog(ost.str(), dbgLog::Failed);
      }
   }
   else
   {
      // dll failed to load
      ost<<_T("Error Loading DLL: ")<< dllname<<std::endl;
      rlog << ost;
      rlog.AddEntryToLog(ost.str(), dbgLog::Failed);
   }

   rlog << _T("**** End Testing DLL: ")<< dllname <<_T(" ****")<<endl;

   return bt;
}

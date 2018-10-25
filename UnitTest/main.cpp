///////////////////////////////////////////////////////////////////////
// UnitTest - Utility program to run unit tests on WBFL DLL's
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


bool TestDll(const char* plibname, dbgLog& rlog);

// put names of all dll's to be tested here:
static const char* lib_list[] = {"WBFLSystem.dll",
                                 "WBFLRoark.dll",
                                 "WBFLGeometricPrimitives.dll",
                                 "WBFLGraphicsLib.dll",
                                 "WBFLGeomModel.dll",
                                 "WBFLLibraryFw.dll",
                                 "WBFLLrfd.dll",
                                 "WBFLMaterial.dll",
                                 "WBFLMath.dll",
                                 "WBFLReinforcedConcrete.dll",
                                 "WBFLUnitMgt.dll",
                                 "WBFLUnits.dll",
                                 "WBFLBridgeAnalysis.dll",
                                 "WBFLBridgeModeling.dll"};

int main()
{
   bool st=0;

   dbgDiagBase::EnableWarnPopup(false);

   // create a test logger
#if defined _DEBUG
   dbgFileDumpContext dc("UnitTest_Debug.Log");
#else
   dbgFileDumpContext dc("UnitTest_Release.Log");
#endif
   dbgLog tl(&dc);


   // send intro messages to screen and file
   sysDate now_start;
   tl << "*** Start WBFL Unit Testing at " << now_start.AsString() << " ***" << endl;
   std::cout << "*** Start WBFL Unit Testing at "<< now_start <<"  ***" << std::endl;


   // run testme's for all libraries
   int n = sizeof(lib_list)/sizeof(char*);
   for (int i=0; i<n; i++)
      st |= TestDll(lib_list[i], tl);

   // Test reporting
   tl << endl;
   tl << "Total number of tests           : " << tl.GetNumEntries() << endl;
   tl << "Number of Passing tests         : " << tl.GetTestCount( dbgLog::Passed ) << endl;
   tl << "Number of Failing tests         : " << tl.GetTestCount( dbgLog::Failed ) << endl;
   tl << "Number of tests not implemented : " << tl.GetTestCount( dbgLog::NotImplemented ) << endl;

   dc << endl;
   tl.DumpFilteredLog( dbgLog::Failed );

   sysDate now_end;
   tl << "*** Finished WBFL Unit Testing at " << now_end.AsString() << " ***" << endl;
   std::cout << "*** Finished WBFL Unit Testing at "<< now_end <<"  ***" << std::endl;

   return st ? 1 : 0;
}


bool TestDll(const char* plibname, dbgLog& rlog)
{
   HINSTANCE hLibrary;
   pUnitTest ptst;
   bool      bt;
   std::ostringstream ost;

   std::string dllname(plibname);

   rlog << endl<<"**** Begin Testing DLL: "<< dllname <<" ****"<<endl;

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
            ost<<"Handled uncaught sysXBase exception from :"<< dllname<<std::endl
               <<"Reason was "<<xb->GetReason()<<std::endl;
            rlog << ost;
            rlog.AddEntryToLog(ost.str(), dbgLog::Failed);
         }
         catch(...)
         {
            ost<<"Handled uncaught exception from :"<< dllname<<std::endl;
            rlog << ost;
            rlog.AddEntryToLog(ost.str(), dbgLog::Failed);
         }

         FreeLibrary(hLibrary);

      }
      else
      {
         //failed to get UnitTest from dll
         ost<<"Failed to load UnitTest function from: "<< dllname<<std::endl;
         rlog << ost;
         rlog.AddEntryToLog(ost.str(), dbgLog::Failed);
      }
   }
   else
   {
      // dll failed to load
      ost<<"Error Loading DLL: "<< dllname<<std::endl;
      rlog << ost;
      rlog.AddEntryToLog(ost.str(), dbgLog::Failed);
   }

   rlog << "**** End Testing DLL: "<< dllname <<" ****"<<endl;

   return bt;
}

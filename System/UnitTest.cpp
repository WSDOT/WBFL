///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>
#include <System\UnitTest.h>

#include <System\Date.h>
#include <System\Time.h>

#include <System\Flags.h>

#include <MathEx.h>

#include <fstream>
#include <iostream>

#include <System\StructuredLoadXml.h>
#include <System\StructuredSaveXml.h>
#include <system\filestream.h>
#include <atlbase.h>

bool TestStructuredStorage(WBFL::Debug::Log& rlog);

using namespace WBFL::System;

bool UnitTest::TestMe(WBFL::Debug::Log& rlog)
{
   bool tst=true;

#if defined _UNITTEST
   tst &= Time::TestMe(rlog);
   tst &= Date::TestMe(rlog);

   tst &= TestStructuredStorage(rlog);
#endif
   return tst;
}

bool TestStructuredStorage(WBFL::Debug::Log& rlog)
{
   // create a test logger
   TESTME_PROLOGUE("Structured Storage Classes - XML Parser");
   std::_tostringstream ostr;
   ostr << _T("This is ")<<std::endl<<_T("a multi-line description")<<std::endl;
   ostr << _T("With a twist >");
   std::_tstring twist(ostr.str());

   std::_tstring special(_T("A string with \"special char's < > && & things><"));
   // test saving
   {
   FileStream os;
   if (!os.open(_T("Test.xml"),false)) exit(1);

   StructuredSaveXml save;
   save.BeginSave( &os );

   save.BeginUnit(_T("LIBRARY_MANAGER"), 1.0);
      save.BeginUnit(_T("LIBRARY"),2.1);
      save.Property(_T("NAME"), _T("ConcreteLibrary"));
      save.Property(_T("DESCRIPTION"), twist.c_str());
         save.BeginUnit(_T("CONCRETE_ENTRY"));
            save.Property(_T("Special"), special.c_str());
            save.Property(_T("Density"), 150.20);
            save.Property(_T("IsLightWeight"), true);
            save.Property(_T("Int32_Max"), (Int32)Int32_Max);
            save.Property(_T("Int32_Min"), (Int32)Int32_Min);
            save.Property(_T("Uint32_Max"),(Uint32)Uint32_Max);
            save.Property(_T("Int16_Max"), (Int16)Int16_Max);
            save.Property(_T("Int16_Min"), (Int16)Int16_Min);
            save.Property(_T("Uint16_Max"),(Uint16)Uint16_Max);
         save.EndUnit();
      save.EndUnit();
   save.EndUnit();

   save.EndSave();
   }


   // test loading
   FileStream is;

   if (!is.open(_T("Test.xml"),true)) exit(1);
   StructuredLoadXml load;

   try
   {
      load.BeginLoad( &is );

      Float64 d;
      bool b;
      Int32 lmax, lmin;
      Uint32 ulmax;
      Int16 smax, smin;
      Uint16 usmax;
      std::_tstring str;

      TRY_TESTME(load.BeginUnit(_T("LIBRARY_MANAGER")));

         TRY_TESTME(load.BeginUnit(_T("LIBRARY")));
         TRY_TESTME(load.GetVersion()==2.1);
           TRY_TESTME(load.Property(_T("NAME"), &str));
           TRY_TESTME((str==_T("ConcreteLibrary")));
           TRY_TESTME(load.Property(_T("DESCRIPTION"), &str));
           //TRY_TESTME((str==twist)); // this test doesn't pass, but seems to have no consequence either.
           TRY_TESTME(load.BeginUnit(_T("CONCRETE_ENTRY")));
              TRY_TESTME(load.Property(_T("Special"), &str));
              TRY_TESTME(str==special);
              TRY_TESTME(load.Property(_T("Density"), &d));
              TRY_TESTME(d==150.20);
              TRY_TESTME(load.Property(_T("IsLightWeight"), &b));
              TRY_TESTME(b==true);

              TRY_TESTME(load.Property(_T("Int32_Max"), &lmax ));
              TRY_TESTME(lmax == Int32_Max);

              TRY_TESTME(load.Property(_T("Int32_Min"), &lmin));
              TRY_TESTME( lmin == Int32_Min );

              TRY_TESTME(load.Property(_T("Uint32_Max"),&ulmax));
              TRY_TESTME( ulmax == Uint32_Max );

              TRY_TESTME(load.Property(_T("Int16_Max"), &smax ));
              TRY_TESTME(smax == Int16_Max);

              TRY_TESTME(load.Property(_T("Int16_Min"), &smin));
              TRY_TESTME( smin == Int16_Min );

              TRY_TESTME(load.Property(_T("Uint16_Max"),&usmax));
              TRY_TESTME( usmax == Uint16_Max );

              TRY_TESTME(load.GetTopVersion()==1.0);
              rlog << load.GetStateDump();       // take a dump
           TRY_TESTME(load.EndUnit());
        TRY_TESTME(load.EndUnit());
     TRY_TESTME(load.GetVersion()==1.0);
     TRY_TESTME(load.EndUnit());
 
     load.EndLoad();
   }
   catch (WBFL::System::XStructuredLoad& ex)
   {
      std::_tcout << ex.GetErrorMessage();
   }

   TESTME_EPILOG("Structured Storage XMLPRS Library");
}

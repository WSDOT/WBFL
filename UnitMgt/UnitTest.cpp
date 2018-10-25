///////////////////////////////////////////////////////////////////////
// UnitMgt - Service for managing display units indirectly
// Copyright © 1999-2012  Washington State Department of Transportation
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

#include <UnitMgt\UnitMgtLib.h>
#include <UnitMgt\UnitTest.h>

#if defined _UNITTEST
#include <UnitMgt\Library.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool test_iter(dbgLog& rlog);

/****************************************************************************
CLASS
   unitmgtUnitTest
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bool unitmgtUnitTest::TestMe(dbgLog& rlog)
{
   bool tst=true;
#if defined _UNITTEST
   tst = test_iter( rlog);
#endif
   return tst;
}

#if defined _UNITTEST


bool test_iter(dbgLog& rlog)
{
   TESTME_PROLOGUE("UnitMgt Package");

   unitmgtLibrary my_lib;

   my_lib.AddEntry(_T("SI"),unitmgtIndirectMeasure() );
   my_lib.AddEntry(_T("English"),unitmgtIndirectMeasure() );
   my_lib.AddEntry(_T("Bob's Favorite"),unitmgtIndirectMeasure() );


   rlog << _T("Iterator test") << endl;
   unitmgtLibraryIter iter(my_lib);
   for ( iter.First(); !iter.IsDone(); iter.Next() )
   {
      rlog << iter.CurrentKey().c_str() << endl;
      CHECK( iter.CurrentValue().AssertValid() );
#if defined _DEBUG
      iter.CurrentValue().Dump( rlog.GetDumpCtx() );
#endif
   }

   rlog << endl;

   rlog << _T("Const Iterator test") << endl;
   unitmgtConstLibraryIter const_iter(my_lib);
   for ( const_iter.First(); !const_iter.IsDone(); const_iter.Next() )
   {
      rlog << const_iter.CurrentKey().c_str() << endl;
#if defined _DEBUG
      iter.CurrentValue().Dump( rlog.GetDumpCtx() );
#endif
   }

   TESTME_EPILOG("UnitMgt Package");
}
#endif
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================

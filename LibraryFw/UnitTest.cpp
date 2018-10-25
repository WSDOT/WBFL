///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2013  Washington State Department of Transportation
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

#include <LibraryFw\LibraryFwLib.h>
#include <LibraryFw\UnitTest.h>
#include <fstream>
#include <iostream>
#include <System\StructuredSaveXml.h>
#include <System\StructuredLoadXml.h>

#include <LibraryFw\Library.h>
#include <LibraryFw\LibraryManager.h>
#include ".\UnitTests\ConcreteMaterial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   libUnitTest
****************************************************************************/

bool TestLib(dbgLog& rlog);



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bool libUnitTest::TestMe(dbgLog& rlog)
{

   return TestLib(rlog);
}


bool TestLib(dbgLog& rlog)
{
   TESTME_PROLOGUE("Library Persistence");
   // create some libaries, fill them with data to save
   typedef libLibrary<libConcreteMaterial,0> LibType;
   LibType* psav1 = new LibType(_T("CONC_LIB1"), _T("Concrete Library 1"));
   libConcreteMaterial mat;
   TRY_TESTME(mat.GetRefCount()==0);
   TRY_TESTME(psav1->IsEmpty());
   psav1->AddEntry(mat, _T("Item1"));
   psav1->NewEntry(_T("Item2"));
   psav1->NewEntry(_T("Item3"));
   psav1->CloneEntry(_T("Item3"), _T("Item4"));

   LibType* psav2 = new LibType(_T("CONC_LIB2"), _T("Concrete Library 2"));
   psav2->NewEntry(_T("Item21"));
   psav2->NewEntry(_T("Item22"));
   psav2->NewEntry(_T("Item23"));

   // add libaries to be saved to a library manager
   libLibraryManager saveman;
   saveman.AddLibrary(psav1);
   saveman.AddLibrary(psav2);

   // test some library functions
   TRY_TESTME(!psav1->IsEmpty());
   TRY_TESTME(psav1->GetCount()==4);
   libKeyListType list;
   psav1->KeyList(list);
   TRY_TESTME(list.size()==4);
   TRY_TESTME(psav1->GetDisplayName()==_T("Concrete Library 1"));
   TRY_TESTME(psav1->GetIdName()==_T("CONC_LIB1"));
   std::_tstring tmp;
   const libConcreteMaterial* pmat = psav1->LookupEntry(_T("Item1"));
   PRECONDITION(pmat);
   psav1->GetEntryKey(*pmat, tmp);
   TRY_TESTME(tmp==_T("Item1"));
   TRY_TESTME(&saveman==psav1->GetLibraryManager());
   TRY_TESTME(psav1->IsEntry(_T("Item1")));
   TRY_TESTME(!psav1->IsEntry(_T("BogusItem")));
   TRY_TESTME(psav1->RemoveEntry(_T("Item1"))==libILibrary::RemReferenced);
   pmat->Release();
   TRY_TESTME(psav1->RemoveEntry(_T("Item1"))==libILibrary::RemOk);
   TRY_TESTME(psav1->GetCount()==3);
   TRY_TESTME(psav1->RemoveEntry(_T("BogusItem"))==libILibrary::RemNotFound);
   TRY_TESTME(psav1->RenameEntry(_T("Item2"),_T("RenamedItem2")));
   TRY_TESTME(psav1->IsEntry(_T("RenamedItem2")));
   TRY_TESTME(!psav1->IsEntry(_T("Item2")));
   psav1->SetDisplayName(_T("Concrete Libarary 1 - Renamed"));
   TRY_TESTME(psav1->GetDisplayName()==_T("Concrete Libarary 1 - Renamed"));
   mat.SetName(_T("New Material Name"));
   mat.SetFc(123.456);
   TRY_TESTME(psav1->UpdateEntry(mat,_T("Item3")));
   const libConcreteMaterial* pmat3 = psav1->LookupEntry(_T("Item3"));
   PRECONDITION(pmat3);
   TRY_TESTME(pmat3->GetFc()==123.456);
   TRY_TESTME(pmat3->GetRefCount()==1);
   pmat3->Release();

   // save manager and libraries and close stream
   {
      std::_tofstream os(_T("TestLib.xml"));
      sysStructuredSaveXml save;
      save.BeginSave(&os);
      saveman.SaveMe(&save);
      save.EndSave();
   }

   // create a new librarymanager with empty libraries to load
   LibType* pload1 = new LibType(_T("CONC_LIB1"), _T("Concrete Library 1")); // note id's must match above
   LibType* pload2 = new LibType(_T("CONC_LIB2"), _T("Concrete Library 2"));
   libLibraryManager loadman;
   loadman.AddLibrary(pload1);
   loadman.AddLibrary(pload2);

   // load it up
   try
   {
      std::_tifstream is(_T("TestLib.xml"));
      sysStructuredLoadXml load;
      load.BeginLoad(&is);
      loadman.LoadMe(&load);
      load.EndLoad();
   }
   catch(const sysXStructuredLoad& rex)
   {
      std::_tstring msg;
      rex.GetErrorMessage(&msg);
      std::_tcout << msg << std::endl;
   }

   // dump loaded one
#if defined _DEBUG
   loadman.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("Library Persistence");
};


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


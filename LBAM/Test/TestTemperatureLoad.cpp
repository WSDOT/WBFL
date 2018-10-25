///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2013  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestTemperatureLoad.cpp: implementation of the CTestTemperatureLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestTemperatureLoad.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_LOAD_FIRED() TRY_TEST(pMe->m_csTemperatureLoadFired, true); pMe->m_csTemperatureLoadFired=false;
#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csTemperatureLoadFired, true); pMe->m_csTemperatureLoadFired=false;

#include "TestLoadContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestTemperatureLoad::CTestTemperatureLoad():
m_csTemperatureLoadFired(false),
m_CsCookie(0)
{
}

CTestTemperatureLoad::~CTestTemperatureLoad()
{
}

void CTestTemperatureLoad::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestTemperatureLoad>* pMe;
   CComObject<CTestTemperatureLoad>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for TemperatureLoads
   hr = LoadContainerTester<ITemperatureLoad,&CLSID_TemperatureLoad,ITemperatureLoadItem, ITemperatureLoads,&CLSID_TemperatureLoads,CTestTemperatureLoad,ITemperatureLoadsEvents,&IID_ITemperatureLoadsEvents, IEnumTemperatureLoad>::TestContainer(pMe);
   TRY_TEST(hr, S_OK);

   // first test a poi by itself
   CComPtr<ITemperatureLoad> pTemperatureLoad;
   TRY_TEST(pTemperatureLoad.CoCreateInstance( CLSID_TemperatureLoad ), S_OK );
   CComBSTR bst;
   Float64 d;
   MemberType mt;
   TRY_TEST( pTemperatureLoad->get_MemberType(&mt), S_OK );
   TRY_TEST( mt, mtUndefined );
   MemberIDType i;
   TRY_TEST( pTemperatureLoad->get_MemberID(&i), S_OK );
   TRY_TEST( i, -1 );
   TRY_TEST( pTemperatureLoad->get_TTop(&d), S_OK );
   TRY_TEST( d, 0.0);
   TRY_TEST( pTemperatureLoad->get_TBottom(&d), S_OK );
   TRY_TEST( d, 0.0);


   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<ITemperatureLoadEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pTemperatureLoad,punk,IID_ITemperatureLoadEvents,&dwCookie),S_OK);

   // cause some events to fire
   TRY_TEST( pTemperatureLoad->put_MemberType(mtSpan), S_OK );
   TEST_LOAD_FIRED();
   TRY_TEST( pTemperatureLoad->get_MemberType(&mt), S_OK );
   TRY_TEST( mt, mtSpan );
   TRY_TEST( pTemperatureLoad->put_MemberID(3), S_OK );
   TEST_LOAD_FIRED();
   MemberIDType l;
   TRY_TEST( pTemperatureLoad->get_MemberID(&l), S_OK );
   TRY_TEST( l, 3 );

   TRY_TEST( pTemperatureLoad->put_TTop(1.1), S_OK );
   TEST_LOAD_FIRED();
   TRY_TEST( pTemperatureLoad->get_TTop(&d), S_OK );
   TRY_TEST( d, 1.1);
   TRY_TEST( pTemperatureLoad->put_TBottom(2.2), S_OK );
   TEST_LOAD_FIRED();
   TRY_TEST( pTemperatureLoad->get_TBottom(&d), S_OK );
   TRY_TEST( d, 2.2);

   // test persistence by saving and retrieving data and comparing raw xml

   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestTemperatureLoad"), 1.0);

      // get interface TemperatureLoadnter to Save
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pTemperatureLoad.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<ITemperatureLoad> pTemperatureLoad2;
      TRY_TEST(pTemperatureLoad2.CoCreateInstance( CLSID_TemperatureLoad ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestTemperatureLoad"));

         IStructuredStorage2* piss2=NULL;
         TRY_TEST( pTemperatureLoad2.QueryInterface(&piss2), S_OK);

         // Load 
         TRY_TEST( piss2->Load(psl), S_OK );

         piss2->Release();

         VARIANT_BOOL end;
         hr = psl->EndUnit(&end);

         TRY_TEST( psl->Close(), S_OK );

         // now save to a different file so we can compare files
         CComPtr<IStructuredSave2> pss2;
         TRY_TEST( pss2.CoCreateInstance( CLSID_StructuredSave2 ), S_OK );
         TRY_TEST( pss2->Open( CComBSTR("Test2.xml")), S_OK );

         // save our loaded version
         hr = pss2->BeginUnit(CComBSTR("TestTemperatureLoad"), 1.0);
         TRY_TEST( piss2->Save(pss2), S_OK );
         hr = pss2->EndUnit();
         TRY_TEST( pss2->Close(), S_OK );
      }
   }

   // compare two files by comparing strings. note that xml parser based files have only two lines
   // the first line is the xml processing instruction and the second line is all of the data
   // for this simple case we can simply compare the two data strings. For huge files, we
   // might have to resort to less memory intensive methods.
   try
   {
      std::_tstring x1;
      std::_tifstream if1("Test.xml");
      std::getline(if1, x1);
      std::getline(if1, x1); // second line is the data

      std::_tstring x2;
      std::_tifstream if2("Test2.xml");
      std::getline(if2, x2);
      std::getline(if2, x2);

      TRY_TEST( x1, x2 );

   }
   catch(...)
   {
      ATLASSERT(0); // big problems
      TRY_TEST(0,1); 
   }

   // create a clone and save it
   CComPtr<ITemperatureLoad> pclone;
   TRY_TEST(pTemperatureLoad->Clone(&pclone), S_OK);

   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestTemperatureLoad"), 1.0);

      // get interface pointer to Save
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pclone.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }


   // compare clone's file with original
   try
   {
      std::_tstring x1;
      std::_tifstream if1("Test.xml");
      std::getline(if1, x1);
      std::getline(if1, x1); // second line is the data

      std::_tstring x2;
      std::_tifstream if2("Test2.xml");
      std::getline(if2, x2);
      std::getline(if2, x2);

      TRY_TEST( x1, x2 );

   }
   catch(...)
   {
      ATLASSERT(0); // big problems
      TRY_TEST(0,1); 
   }

   // disconnect our connections
   TRY_TEST(AtlUnadvise(pTemperatureLoad,IID_ITemperatureLoadEvents,dwCookie),S_OK);
   pMe->Release();
}



HRESULT CTestTemperatureLoad::OnTemperatureLoadChanged(ITemperatureLoad* TemperatureLoad)
{
   m_csTemperatureLoadFired = true;

   return S_OK;
}

HRESULT CTestTemperatureLoad::OnTemperatureLoadsChanged(ITemperatureLoadItem* TemperatureLoad)
{
   m_csTemperatureLoadFired = true;
   return S_OK;
}
HRESULT CTestTemperatureLoad::OnTemperatureLoadsAdded(ITemperatureLoadItem* TemperatureLoad)
{
   m_csTemperatureLoadFired = true;
   return S_OK;
}
HRESULT CTestTemperatureLoad::OnTemperatureLoadsBeforeRemove(ITemperatureLoadItem* TemperatureLoad)
{
   m_csTemperatureLoadFired = true;
   return S_OK;
}

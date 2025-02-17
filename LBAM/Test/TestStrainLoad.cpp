///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// TestStrainLoad.cpp: implementation of the CTestStrainLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestStrainLoad.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_LOAD_FIRED() TRY_TEST(pMe->m_csStrainLoadFired, true); pMe->m_csStrainLoadFired=false;
#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csStrainLoadFired, true); pMe->m_csStrainLoadFired=false;

#include "TestLoadContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestStrainLoad::CTestStrainLoad():
m_csStrainLoadFired(false),
m_CsCookie(0)
{
}

CTestStrainLoad::~CTestStrainLoad()
{
}

void CTestStrainLoad::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestStrainLoad>* pMe;
   CComObject<CTestStrainLoad>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for StrainLoads
   hr = LoadContainerTester<IStrainLoad,&CLSID_StrainLoad,IStrainLoadItem, IStrainLoads,&CLSID_StrainLoads,CTestStrainLoad,IStrainLoadsEvents,&IID_IStrainLoadsEvents, IEnumStrainLoad>::TestContainer(pMe);
   TRY_TEST(hr, S_OK);

   // first test a poi by itself
   CComPtr<IStrainLoad> pStrainLoad;
   TRY_TEST(pStrainLoad.CoCreateInstance( CLSID_StrainLoad ), S_OK );
   CComBSTR bst;
   Float64 d;
   MemberIDType i;
   TRY_TEST( pStrainLoad->get_MemberID(&i), S_OK );
   TRY_TEST( i, -1 );
   TRY_TEST( pStrainLoad->get_AxialStrain(&d), S_OK );
   TRY_TEST( d, 0.0);
   TRY_TEST( pStrainLoad->get_CurvatureStrain(&d), S_OK );
   TRY_TEST( d, 0.0);


   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<IStrainLoadEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pStrainLoad,punk,IID_IStrainLoadEvents,&dwCookie),S_OK);

   // cause some events to fire
   TRY_TEST( pStrainLoad->put_MemberID(3), S_OK );
   TEST_LOAD_FIRED();
   MemberIDType l;
   TRY_TEST( pStrainLoad->get_MemberID(&l), S_OK );
   TRY_TEST( l, 3 );

   TRY_TEST( pStrainLoad->put_AxialStrain(1.1), S_OK );
   TEST_LOAD_FIRED();
   TRY_TEST( pStrainLoad->get_AxialStrain(&d), S_OK );
   TRY_TEST( d, 1.1);
   TRY_TEST( pStrainLoad->put_CurvatureStrain(2.2), S_OK );
   TEST_LOAD_FIRED();
   TRY_TEST( pStrainLoad->get_CurvatureStrain(&d), S_OK );
   TRY_TEST( d, 2.2);

   // test persistence by saving and retrieving data and comparing raw xml

   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestStrainLoad"), 1.0);

      // get interface StrainLoadnter to Save
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pStrainLoad.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<IStrainLoad> pStrainLoad2;
      TRY_TEST(pStrainLoad2.CoCreateInstance( CLSID_StrainLoad ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestStrainLoad"));

         IStructuredStorage2* piss2=nullptr;
         TRY_TEST( pStrainLoad2.QueryInterface(&piss2), S_OK);

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
         hr = pss2->BeginUnit(CComBSTR("TestStrainLoad"), 1.0);
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
      ATLASSERT(false); // big problems
      TRY_TEST(0,1); 
   }

   // create a clone and save it
   CComPtr<IStrainLoad> pclone;
   TRY_TEST(pStrainLoad->Clone(&pclone), S_OK);

   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestStrainLoad"), 1.0);

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
      ATLASSERT(false); // big problems
      TRY_TEST(0,1); 
   }

   // disconnect our connections
   TRY_TEST(AtlUnadvise(pStrainLoad,IID_IStrainLoadEvents,dwCookie),S_OK);
   pMe->Release();
}



HRESULT CTestStrainLoad::OnStrainLoadChanged(IStrainLoad* StrainLoad)
{
   m_csStrainLoadFired = true;

   return S_OK;
}

HRESULT CTestStrainLoad::OnStrainLoadsChanged(IStrainLoadItem* StrainLoad)
{
   m_csStrainLoadFired = true;
   return S_OK;
}
HRESULT CTestStrainLoad::OnStrainLoadsAdded(IStrainLoadItem* StrainLoad)
{
   m_csStrainLoadFired = true;
   return S_OK;
}
HRESULT CTestStrainLoad::OnStrainLoadsBeforeRemove(IStrainLoadItem* StrainLoad)
{
   m_csStrainLoadFired = true;
   return S_OK;
}

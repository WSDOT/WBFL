///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 2009  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// TestPOI.cpp: implementation of the CTestPOI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPOI.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_POI_FIRED() TRY_TEST(pMe->m_csPOIFired, true); pMe->Init();
#define TEST_DF_FIRED() TRY_TEST(pMe->m_csDFFired, true);  pMe->Init();
#define TEST_SP_FIRED() TRY_TEST(pMe->m_csSPFired, true);  pMe->Init();
#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csPOIFired, true);  pMe->Init();

#include "TestSetContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestPOI::CTestPOI():
m_csPOIFired(false),
m_csDFFired(false),
m_csSPFired(false),
m_CsCookie(0)
{
}

void CTestPOI::Init()
{
   m_csPOIFired=false; 
   m_csDFFired=false;
   m_csSPFired=false;
}

CTestPOI::~CTestPOI()
{
}

void CTestPOI::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestPOI>* pMe;
   CComObject<CTestPOI>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for POIs
   hr = LongSetContainerTester<IPOI,&CLSID_POI,IPOIs,&CLSID_POIs,CTestPOI,IPOIsEvents,&IID_IPOIsEvents, IEnumPOI>::TestContainer(pMe);
   TRY_TEST(hr, S_OK);

   // first test a poi by itself
   CComPtr<IPOI> ppoi;
   TRY_TEST(ppoi.CoCreateInstance( CLSID_POI ), S_OK );
   long id;
   Float64 d;
   TRY_TEST( ppoi->get_ID(&id), S_OK );
   TRY_TEST( id, -1 );
   TRY_TEST( ppoi->get_Location(&d), S_OK );
   TRY_TEST( d, 0.0 );
   MemberType mt;
   TRY_TEST( ppoi->get_MemberType(&mt), S_OK );
   TRY_TEST( mt, mtUndefined );
   MemberIDType i;
   TRY_TEST( ppoi->get_MemberID(&i), S_OK );
   TRY_TEST( i, -1 );

   CollectionIndexType count;
   CComPtr<IPOIStressPoints> poisps;
   TRY_TEST( ppoi->get_POIStressPoints(&poisps), S_OK );
   TRY_TEST( poisps->get_Count(&count), S_OK );
   TRY_TEST(count, 0);

   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<IPOIEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(ppoi,punk,IID_IPOIEvents,&dwCookie),S_OK);

   // cause some events to fire
   TRY_TEST( ppoi->put_ID(102), S_OK );
   TEST_POI_FIRED();
   TRY_TEST( ppoi->get_ID(&id), S_OK );
   TRY_TEST( id, 102 );
   TRY_TEST( ppoi->put_MemberType(mtSpan), S_OK );
   TEST_POI_FIRED();
   TRY_TEST( ppoi->get_MemberType(&mt), S_OK );
   TRY_TEST( mt, mtSpan );
   TRY_TEST( ppoi->put_Location(-0.2), S_OK );
   TEST_POI_FIRED();
   TRY_TEST( ppoi->get_Location(&d), S_OK );
   TRY_TEST( d, -0.2 );
   TRY_TEST( ppoi->put_Location(2.0), S_OK );
   TEST_POI_FIRED();
   TRY_TEST( ppoi->get_Location(&d), S_OK );
   TRY_TEST( d, 2.0 );
   TRY_TEST( ppoi->put_MemberID(3), S_OK );
   TEST_POI_FIRED();
   MemberIDType l;
   TRY_TEST( ppoi->get_MemberID(&l), S_OK );
   TRY_TEST( l, 3 );

   CComPtr<IStressPoints> right_sps, left_sps;
   right_sps.CoCreateInstance(CLSID_StressPoints);
   left_sps.CoCreateInstance(CLSID_StressPoints);
   TRY_TEST(poisps->Insert(CComBSTR("Stage 1"), left_sps, right_sps), S_OK);
   TEST_SP_FIRED();
   TRY_TEST( poisps->get_Count(&count), S_OK );
   TRY_TEST(count, 1);
   TRY_TEST(poisps->Insert(CComBSTR("Stage 2"), left_sps, right_sps), S_OK);
   TEST_SP_FIRED();
   TRY_TEST( poisps->get_Count(&count), S_OK );
   TRY_TEST(count, 2);

   CComPtr<IStressPoint> sp1, sp2;
   sp1.CoCreateInstance(CLSID_StressPoint);
   sp2.CoCreateInstance(CLSID_StressPoint);
   TRY_TEST(right_sps->Add(sp1), S_OK);
   TEST_SP_FIRED();
   TRY_TEST(left_sps->Add(sp2), S_OK);
   TEST_SP_FIRED();

   TRY_TEST(sp1->put_Sa(1.2), S_OK);
   TEST_SP_FIRED();
   TRY_TEST(sp2->put_Sm(1.3), S_OK);
   TEST_SP_FIRED();

   CComPtr<IPOIStressPointsItem> item1, item2;
   TRY_TEST(poisps->get_Item(CComVariant(CComBSTR("Stage 2")), &item1), S_OK);
   CComBSTR stgn;
   TRY_TEST(item1->get_Stage(&stgn), S_OK);
   TRY_TEST(stgn, CComBSTR("Stage 2"));

   TRY_TEST(poisps->get_Item(CComVariant((long)1), &item2), S_OK);
   stgn.Empty();
   TRY_TEST(item1->get_Stage(&stgn), S_OK);
   TRY_TEST(stgn, CComBSTR("Stage 2"));

   TRY_TEST(poisps->Remove(CComBSTR("Stage 2")), S_OK);
   TEST_SP_FIRED();
   TRY_TEST( poisps->get_Count(&count), S_OK );
   TRY_TEST(count, 1);

   item1.Release();
   TRY_TEST(poisps->get_Item(CComVariant(CComBSTR("Stage Bogus")), &item1), LBAM_E_POI_NO_STAGE);
   TRY_TEST(poisps->get_Item(CComVariant((long)12), &item1), E_INVALIDARG);
   TRY_TEST(poisps->Remove(CComBSTR("Stage Bogus")), LBAM_E_POI_NO_STAGE);

   TRY_TEST( ppoi->put_Location(-1.1), E_INVALIDARG );

   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestPOI"), 1.0);

      // get interface pointer to Save
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( ppoi.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<IPOI> ppoi2;
      TRY_TEST(ppoi2.CoCreateInstance( CLSID_POI ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestPOI"));

         IStructuredStorage2* piss2=NULL;
         TRY_TEST( ppoi2.QueryInterface(&piss2), S_OK);

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
         hr = pss2->BeginUnit(CComBSTR("TestPOI"), 1.0);
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
      std::string x1;
      std::ifstream if1("Test.xml");
      std::getline(if1, x1);
      std::getline(if1, x1); // second line is the data

      std::string x2;
      std::ifstream if2("Test2.xml");
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
   CComPtr<IPOI> pclone;
   TRY_TEST(ppoi->Clone(&pclone), S_OK);

   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestPOI"), 1.0);

      // get interface pointer to Save
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pclone.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   CComPtr<IPOIStressPoints> poispsc;
   TRY_TEST( pclone->get_POIStressPoints(&poispsc), S_OK );
   TRY_TEST( poispsc->get_Count(&count), S_OK );
   TRY_TEST(count, 1);
   TRY_TEST( poispsc->Clear(), S_OK );
   TRY_TEST( poispsc->get_Count(&count), S_OK );
   TRY_TEST(count, 0);

// NOTE: Clones will no longer compare because left and right stress points are cloned independently.
//       This is the price of deep cloning.
/*
   // compare clone's file with original
   try
   {
      std::string x1;
      std::ifstream if1("Test.xml");
      std::getline(if1, x1);
      std::getline(if1, x1); // second line is the data

      std::string x2;
      std::ifstream if2("Test2.xml");
      std::getline(if2, x2);
      std::getline(if2, x2);

      TRY_TEST( x1, x2 );

   }
   catch(...)
   {
      ATLASSERT(0); // big problems
      TRY_TEST(0,1); 
   }
*/

   // disconnect our connections
   TRY_TEST(AtlUnadvise(ppoi,IID_IPOIEvents,dwCookie),S_OK);
   pMe->Release();
}



STDMETHODIMP CTestPOI::OnPOIChanged(IPOI* POI, ChangeType change)
{
   if (change==cgtPOI)
      m_csPOIFired = true;
   else if (change==cgtDistributionFactor)
      m_csDFFired = true;
   else if (change==cgtStress)
      m_csSPFired = true;
   else
      ATLASSERT(0);

   return S_OK;
}

STDMETHODIMP CTestPOI::OnPOIRenamed(long oldID, long newID)
{
   m_csPOIFired = true;

   return S_OK;
}

STDMETHODIMP CTestPOI::OnPOIsChanged(IPOI* POI, ChangeType change)
{
   if (change==cgtPOI)
      m_csPOIFired = true;
   else if (change==cgtDistributionFactor)
      m_csDFFired = true;
   else
      ATLASSERT(0);

   return S_OK;
}

STDMETHODIMP CTestPOI::OnPOIsRenamed(long oldId, long newId)
{
   m_csPOIFired = true;

   return S_OK;
}

STDMETHODIMP CTestPOI::OnPOIsAdded(IPOI* POI)
{
      m_csPOIFired = true;

   return S_OK;
}

STDMETHODIMP CTestPOI::OnPOIsBeforeRemove(IPOI* POI)
{
      m_csPOIFired = true;

   return S_OK;
}


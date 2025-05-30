///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// TestAxle.cpp: implementation of the CTestAxle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAxle.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_AXLE_FIRED() TRY_TEST(pMe->m_csAxleFired, true); pMe->m_csAxleFired=false; pMe->m_csAxlesFired=false;
#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csAxlesFired, true); pMe->m_csAxlesFired=false; pMe->m_csAxleFired=false;

#include "TestSegmentContainer.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestAxle::CTestAxle():
m_csAxleFired(false),
m_csAxlesFired(false),
m_CsCookie(0)
{
}

CTestAxle::~CTestAxle()
{
}

void CTestAxle::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestAxle>* pMe;
   CComObject<CTestAxle>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for axles
   hr = ContainerTester<IAxle,&CLSID_Axle,IAxles,&CLSID_Axles,CTestAxle,IAxlesEvents,&IID_IAxlesEvents,IEnumAxle,AxleIndexType>::TestSegmentContainer(pMe);
   TRY_TEST(hr, S_OK);

   // test a Axle by itself
   CComPtr<IAxle> paxle;
   TRY_TEST(paxle.CoCreateInstance( CLSID_Axle ), S_OK );
   Float64 d;
   TRY_TEST( paxle->get_Weight(&d), S_OK );
   TRY_TEST( d, 0.0 );
   TRY_TEST( paxle->get_Spacing(&d), S_OK );
   TRY_TEST( d, 0.0 );

   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<IAxleEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(paxle,punk,IID_IAxleEvents,&dwCookie),S_OK);


   // cause some events to fire
   TRY_TEST( paxle->put_Weight(12.3), S_OK );
   TEST_AXLE_FIRED();
   TRY_TEST( paxle->get_Weight(&d), S_OK );
   TRY_TEST( d, 12.3 );
   TRY_TEST( paxle->put_Weight(-0.02), E_INVALIDARG );

   TRY_TEST( paxle->put_Spacing(12.1), S_OK );
   TEST_AXLE_FIRED();
   TRY_TEST( paxle->get_Spacing(&d), S_OK );
   TRY_TEST( d, 12.1 );
   TRY_TEST( paxle->put_Spacing(-0.02), E_INVALIDARG );

   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestAxle"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( paxle.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<IAxle> psm2;
      TRY_TEST(psm2.CoCreateInstance( CLSID_Axle ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestAxle"));

         IStructuredStorage2* piss2=nullptr;
         TRY_TEST( psm2.QueryInterface(&piss2), S_OK);

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
         hr = pss2->BeginUnit(CComBSTR("TestAxle"), 1.0);
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

   // disconnect our connections
   TRY_TEST(AtlUnadvise(paxle,IID_IAxleEvents,dwCookie),S_OK);
   pMe->Release();
}


HRESULT CTestAxle::OnAxleChanged(IAxle* Axle)
{
   m_csAxleFired = true;

   return S_OK;
}

HRESULT CTestAxle::OnAxlesChanged(IAxle* Axle)
{
   m_csAxlesFired = true;

   return S_OK;
}

STDMETHODIMP CTestAxle::OnAxlesAdded(IAxle* item, AxleIndexType idx)
{
   m_csAxlesFired = true;
   return S_OK;
}
STDMETHODIMP CTestAxle::OnAxlesBeforeRemove(IAxle* item, AxleIndexType idx)
{
   m_csAxlesFired = true;
   return S_OK;
}
STDMETHODIMP CTestAxle::OnAxlesMoveTo(AxleIndexType from, AxleIndexType to)
{
   m_csAxlesFired = true;
   return S_OK;
}
STDMETHODIMP CTestAxle::OnAxlesCopyTo(AxleIndexType from, AxleIndexType to)
{
   m_csAxlesFired = true;
   return S_OK;
}
STDMETHODIMP CTestAxle::OnAxlesReverse()
{
   m_csAxlesFired = true;
   return S_OK;
}

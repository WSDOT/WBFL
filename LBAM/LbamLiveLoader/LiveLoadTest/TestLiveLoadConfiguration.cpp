///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
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

// TestLiveLoadConfiguration.cpp: implementation of the TestLiveLoadConfiguration class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestLiveLoadConfiguration.h"

#include <string>
#include <fstream>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEST_FIRED() TRY_TEST(pMe->m_csChangedFired, true); pMe->m_csChangedFired=false;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TestLiveLoadConfiguration::TestLiveLoadConfiguration():
m_csChangedFired(false),
m_Cookie(0)
{

}

TestLiveLoadConfiguration::~TestLiveLoadConfiguration()
{

}


void TestLiveLoadConfiguration::Test()
{
   HRESULT hr;
   // create a listener
   CComObject<TestLiveLoadConfiguration>* pMe;
   CComObject<TestLiveLoadConfiguration>::CreateInstance(&pMe);
   pMe->AddRef();

   // make an item to test
   CComPtr<ILiveLoadConfiguration> pllc;
   TRY_TEST(pllc.CoCreateInstance( CLSID_LiveLoadConfiguration ), S_OK );

   // let's listen to it
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pMe);
   TRY_TEST(AtlAdvise(pllc,punk,IID_ILiveLoadConfigurationEvents,&dwCookie),S_OK);

   // test some defaults
   CComPtr<IIndexArray> axles;
   TRY_TEST( pllc->get_AxleConfig(&axles), S_OK);
   IndexType size;
   axles->get_Count(&size);
   TRY_TEST(size, 0);
   DistributionFactorType dft;
   TRY_TEST( pllc->get_DistributionFactorType(&dft), S_OK);
   TRY_TEST( dft, dftNone);
   VARIANT_BOOL vb;
   TRY_TEST( pllc->get_DoApplyImpact(&vb), S_OK);
   TRY_TEST( vb, VARIANT_FALSE);
   ForceEffectType fet;
   TRY_TEST( pllc->get_ForceEffect(&fet), S_OK);
   TRY_TEST( fet, fetMz);
   TRY_TEST( pllc->get_IsApplicable(&vb), S_OK);
   TRY_TEST( vb, VARIANT_FALSE);
   LiveLoadModelType llm;
   TRY_TEST( pllc->get_LiveLoadModel(&llm), S_OK);
   TRY_TEST( llm, lltNone);
   OptimizationType opt;
   TRY_TEST( pllc->get_Optimization(&opt), S_OK);
   TRY_TEST( opt, optMaximize);
   TruckDirectionType td;
   TRY_TEST( pllc->get_TruckDirection(&td), S_OK);
   TRY_TEST( td, ltdForward);
   Float64 d;
   TRY_TEST( pllc->get_TruckPosition(&d), S_OK);
   TRY_TEST( d, 0.0);
   TRY_TEST( pllc->get_VariableSpacing(&d), S_OK);
   TRY_TEST( d, 0.0);
   VehicleIndexType l;
   TRY_TEST( pllc->get_VehicleIndex(&l), S_OK);
   TRY_TEST( l, 0);
   VehicularLoadConfigurationType vlc;
   TRY_TEST( pllc->get_VehicularLoadConfiguration(&vlc), S_OK);
   TRY_TEST( vlc, vlcDefault);

   // test some puts
   axles->Clear();
   axles->Add(3);
   axles->Add(5);
   TRY_TEST( pllc->put_AxleConfig(axles), S_OK);
   TEST_FIRED();
   axles = nullptr;
   TRY_TEST( pllc->get_AxleConfig(&axles), S_OK);
   axles->get_Count(&size);
   TRY_TEST(size, 2);
   TRY_TEST( pllc->put_DistributionFactorType(dftSingleLane), S_OK);
   TEST_FIRED();
   TRY_TEST( pllc->get_DistributionFactorType(&dft), S_OK);
   TRY_TEST( dft, dftSingleLane);
   TRY_TEST( pllc->put_DoApplyImpact(VARIANT_TRUE), S_OK);
   TEST_FIRED();
   TRY_TEST( pllc->get_DoApplyImpact(&vb), S_OK);
   TRY_TEST( vb, VARIANT_TRUE);
   TRY_TEST( pllc->put_ForceEffect(fetFy), S_OK);
   TEST_FIRED();
   TRY_TEST( pllc->get_ForceEffect(&fet), S_OK);
   TRY_TEST( fet, fetFy);
   TRY_TEST( pllc->put_IsApplicable(VARIANT_TRUE), S_OK);
   TEST_FIRED();
   TRY_TEST( pllc->get_IsApplicable(&vb), S_OK);
   TRY_TEST( vb, VARIANT_TRUE);
   TRY_TEST( pllc->put_LiveLoadModel(lltDesign), S_OK);
   TEST_FIRED();
   TRY_TEST( pllc->get_LiveLoadModel(&llm), S_OK);
   TRY_TEST( llm, lltDesign);
   TRY_TEST( pllc->put_Optimization(optMinimize), S_OK);
   TEST_FIRED();
   TRY_TEST( pllc->get_Optimization(&opt), S_OK);
   TRY_TEST( opt, optMinimize);
   TRY_TEST( pllc->put_TruckDirection(ltdReverse), S_OK);
   TEST_FIRED();
   TRY_TEST( pllc->get_TruckDirection(&td), S_OK);
   TRY_TEST( td, ltdReverse);
   TRY_TEST( pllc->put_TruckPosition(-20), S_OK);
   TEST_FIRED();
   TRY_TEST( pllc->get_TruckPosition(&d), S_OK);
   TRY_TEST( d, -20.0);
   TRY_TEST( pllc->put_VariableSpacing(12.0), S_OK);
   TEST_FIRED();
   TRY_TEST( pllc->get_VariableSpacing(&d), S_OK);
   TRY_TEST( d, 12.0);
   TRY_TEST( pllc->put_VehicleIndex(3), S_OK);
   TEST_FIRED();
   TRY_TEST( pllc->get_VehicleIndex(&l), S_OK);
   TRY_TEST( l, 3);
   TRY_TEST( pllc->put_VehicularLoadConfiguration(vlcTruckOnly), S_OK);
   TEST_FIRED();
   TRY_TEST( pllc->get_VehicularLoadConfiguration(&vlc), S_OK);
   TRY_TEST( vlc, vlcTruckOnly);

   // error conditions
   axles = nullptr;
   TRY_TEST( pllc->put_AxleConfig(axles), E_INVALIDARG);
   TRY_TEST( pllc->put_VariableSpacing(-12.0), E_INVALIDARG);
//   TRY_TEST( pllc->put_VehicleIndex(-1), E_INVALIDARG);

   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestCS"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pllc.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a cross section to work with
      CComPtr<ILiveLoadConfiguration> pcs2;
      TRY_TEST(pcs2.CoCreateInstance( CLSID_LiveLoadConfiguration ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestCS"));

         IStructuredStorage2* piss2=nullptr;
         TRY_TEST( pcs2.QueryInterface(&piss2), S_OK);

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
         hr = pss2->BeginUnit(CComBSTR("TestCS"), 1.0);
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
   TRY_TEST(AtlUnadvise(pllc,IID_ILiveLoadConfigurationEvents,dwCookie),S_OK);
   pMe->Release();
}

HRESULT TestLiveLoadConfiguration::OnLiveLoadConfigurationChanged( ILiveLoadConfiguration* config)
{
   m_csChangedFired = true;

   return S_OK;
}


///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// TestLiveLoadModel.cpp: implementation of the CTestLiveLoadModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestLiveLoadModel.h"
#include <string>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEST_LIVELOAD_FIRED() TRY_TEST(pMe->m_csLiveLoadFired, true); pMe->m_csLiveLoadFired=false;
#define TEST_VEHICULAR_FIRED() TEST_LIVELOAD_FIRED()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestLiveLoadModel::CTestLiveLoadModel():
m_csLiveLoadFired(false),
m_CsCookie(0)
{
}

CTestLiveLoadModel::~CTestLiveLoadModel()
{
}

void CTestLiveLoadModel::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestLiveLoadModel>* pMe;
   CComObject<CTestLiveLoadModel>::CreateInstance(&pMe);
   pMe->AddRef();

   // first test  by itself
   CComPtr<ILiveLoadModel> pcs;
   TRY_TEST(pcs.CoCreateInstance( CLSID_LiveLoadModel ), S_OK );
   CComBSTR str;
   TRY_TEST( pcs->get_Name(&str), S_OK );
   TRY_TEST( str.Length(), 0 );
   DistributionFactorType dt;
   TRY_TEST( pcs->get_DistributionFactorType(&dt), S_OK );
   TRY_TEST( dt, dftNone );

   // let's listen to pcs
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pMe);
   TRY_TEST(AtlAdvise(pcs,punk,IID_ILiveLoadModelEvents,&dwCookie),S_OK);

   // cause some events to fire
   TRY_TEST( pcs->put_Name(CComBSTR("MyName")), S_OK );
   TEST_LIVELOAD_FIRED();
   str.Empty();
   TRY_TEST( pcs->get_Name(&str), S_OK );
   TRY_TEST( str, CComBSTR("MyName") );
   TRY_TEST( pcs->put_DistributionFactorType(dftEnvelope), S_OK );
   TEST_LIVELOAD_FIRED();
   TRY_TEST( pcs->get_DistributionFactorType(&dt), S_OK );
   TRY_TEST( dt, dftEnvelope );


   // muck with vehicles
   CComPtr<IVehicularLoads> psps;
   VehicleIndexType cnt;
   TRY_TEST( pcs->get_VehicularLoads(&psps), S_OK );
   TRY_TEST( psps->get_Count(&cnt), S_OK );
   TRY_TEST( cnt, 0 );

   CComPtr<IVehicularLoad> pss1, pss2;
   TRY_TEST( pss1.CoCreateInstance( CLSID_VehicularLoad ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( CLSID_VehicularLoad ) , S_OK );

   TRY_TEST(pss1->put_Name(CComBSTR("Truck 1")), S_OK);
   TRY_TEST(pss2->put_Name(CComBSTR("Truck 2")), S_OK);

   TRY_TEST( psps->Add(pss1), S_OK);
   TEST_VEHICULAR_FIRED();
   TRY_TEST( psps->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);

   TRY_TEST( psps->Add(pss2), S_OK);
   TEST_VEHICULAR_FIRED();
   TRY_TEST( pss2->put_LaneLoad(21.2), S_OK );
   TEST_VEHICULAR_FIRED();
   TRY_TEST( pss2->put_TruckFactor(2.141), S_OK );
   TEST_VEHICULAR_FIRED();

   CComBSTR tstr;
   TRY_TEST( psps->Remove(1), S_OK);
   TEST_VEHICULAR_FIRED();

   // create our own vehicles collection and add it
   CComPtr<IVehicularLoads> pspcnew;
   TRY_TEST(pspcnew.CoCreateInstance( CLSID_VehicularLoads ), S_OK );

   CComPtr<IVehicularLoad> pss3, pss4;
   TRY_TEST( pss3.CoCreateInstance( CLSID_VehicularLoad ) , S_OK );
   TRY_TEST( pss4.CoCreateInstance( CLSID_VehicularLoad ) , S_OK );
   TRY_TEST(pss3->put_Name(CComBSTR("Truck 3")), S_OK);
   TRY_TEST(pss4->put_Name(CComBSTR("Truck 4")), S_OK);

   TRY_TEST( pspcnew->Add(pss1), S_OK);   
   TRY_TEST( pspcnew->Add(pss2), S_OK);   

   TRY_TEST( pcs->putref_VehicularLoads(pspcnew), S_OK );
   TEST_VEHICULAR_FIRED();

   TRY_TEST( pspcnew->Add(pss3), S_OK);   
   TEST_VEHICULAR_FIRED();
   TRY_TEST( pspcnew->Add(pss4), S_OK);   
   TEST_VEHICULAR_FIRED();

   TRY_TEST( pspcnew->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 4);

   TRY_TEST( pss3->put_LaneLoad(211.2), S_OK );
   TEST_VEHICULAR_FIRED();
   TRY_TEST( pss2->put_TruckFactor(31.1), S_OK );
   TEST_VEHICULAR_FIRED();

   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestLL"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pcs.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a cross section to work with
      CComPtr<ILiveLoadModel> pcs2;
      TRY_TEST(pcs2.CoCreateInstance( CLSID_LiveLoadModel ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestLL"));

         IStructuredStorage2* piss2=NULL;
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
         hr = pss2->BeginUnit(CComBSTR("TestLL"), 1.0);
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

   // disconnect our connections
   TRY_TEST(AtlUnadvise(pcs,IID_ILiveLoadModelEvents,dwCookie),S_OK);
   pMe->Release();
}

HRESULT CTestLiveLoadModel::OnLiveLoadModelChanged(ILiveLoadModel* LiveLoadModel, ChangeType change)
{
   m_csLiveLoadFired = true;

   return S_OK;
}

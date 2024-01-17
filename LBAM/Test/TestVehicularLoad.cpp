///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// TestVehicularLoad.cpp: implementation of the CTestVehicularLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestVehicularLoad.h"
#include <string>
#include <fstream>

#define TEST_VL_FIRED() TRY_TEST(pMe->m_csLiveLoadFired, true); pMe->m_csLiveLoadFired=false;
#define TEST_AXLES_FIRED() TEST_VL_FIRED()
#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csVehicularLoadsFired, true); pMe->m_csLiveLoadFired=false; pMe->m_csVehicularLoadsFired=false;

HRESULT TestContainer(CTestVehicularLoad* pMe);

#include "TestSegmentContainer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestVehicularLoad::CTestVehicularLoad():
m_csLiveLoadFired(false),
m_csAxlesFired(false),
m_CsCookie(0),
m_LastID(0)
{
}

CTestVehicularLoad::~CTestVehicularLoad()
{
}

void CTestVehicularLoad::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestVehicularLoad>* pMe;
   CComObject<CTestVehicularLoad>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for VehicularLoads
   hr = ContainerTester<IVehicularLoad,&CLSID_VehicularLoad,IVehicularLoads,&CLSID_VehicularLoads,CTestVehicularLoad,IVehicularLoadsEvents,&IID_IVehicularLoadsEvents, IEnumVehicularLoad, VehicleIndexType>::TestVectorContainer(pMe);
   TRY_TEST(hr, S_OK);

   // first test a cs by itself
   CComPtr<IVehicularLoad> pcs;
   TRY_TEST(pcs.CoCreateInstance( CLSID_VehicularLoad ), S_OK );
   Float64 s;
   AxleIndexType l;

   // test default values
   TRY_TEST( pcs->get_IMLane(&s), S_OK );
   TRY_TEST( s, 0.0 );
   TRY_TEST( pcs->get_IMTruck(&s), S_OK );
   TRY_TEST( s, 0.0 );
   TRY_TEST( pcs->get_LaneFactor(&s), S_OK );
   TRY_TEST( s, 1.0 );
   TRY_TEST( pcs->get_TruckFactor(&s), S_OK );
   TRY_TEST( s, 1.0 );
   TRY_TEST( pcs->get_SidewalkLoad(&s), S_OK );
   TRY_TEST( s, 0.0 );
   TRY_TEST( pcs->get_VariableMaxSpacing(&s), S_OK );
   TRY_TEST( s, 0.0 );
   TRY_TEST( pcs->get_VariableAxle(&l), S_OK );
   TRY_TEST( l, FIXED_AXLE_TRUCK );
   LiveLoadApplicabilityType at;
   TRY_TEST( pcs->get_Applicability(&at), S_OK );
   TRY_TEST( at, llaEntireStructure );
   VARIANT_BOOL un;
   TRY_TEST( pcs->get_UseNotional(&un), S_OK );
   TRY_TEST( un, VARIANT_TRUE );
   VehicularLoadConfigurationType ct;
   TRY_TEST( pcs->get_Configuration(&ct), S_OK );
   TRY_TEST( ct, vlcDefault );
   CComBSTR str;
   TRY_TEST( pcs->get_Name(&str), S_OK );
   TRY_TEST( str.Length(), 0 );

   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<IVehicularLoadEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pcs,punk,IID_IVehicularLoadEvents,&dwCookie),S_OK);

   TRY_TEST( pcs->put_IMLane(0.33), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( pcs->get_IMLane(&s), S_OK );
   TRY_TEST( s, 0.33 );
   TRY_TEST( pcs->put_IMTruck(0.22), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( pcs->get_IMTruck(&s), S_OK );
   TRY_TEST( s, 0.22 );
   TRY_TEST( pcs->put_LaneFactor(0.5), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( pcs->get_LaneFactor(&s), S_OK );
   TRY_TEST( s, 0.5 );
   TRY_TEST( pcs->put_TruckFactor(0.6), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( pcs->get_TruckFactor(&s), S_OK );
   TRY_TEST( s, 0.6 );
   TRY_TEST( pcs->put_SidewalkLoad(12.0), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( pcs->get_SidewalkLoad(&s), S_OK );
   TRY_TEST( s, 12.0 );
   TRY_TEST( pcs->put_VariableMaxSpacing(11.0), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( pcs->get_VariableMaxSpacing(&s), S_OK );
   TRY_TEST( s, 11.0 );
   TRY_TEST( pcs->put_VariableAxle(9), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( pcs->get_VariableAxle(&l), S_OK );
   TRY_TEST( l, 9 );
   TRY_TEST( pcs->put_Applicability(llaContraflexure), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( pcs->get_Applicability(&at), S_OK );
   TRY_TEST( at, llaContraflexure );
   TRY_TEST( pcs->put_UseNotional(VARIANT_FALSE), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( pcs->get_UseNotional(&un), S_OK );
   TRY_TEST( un, VARIANT_FALSE );
   TRY_TEST( pcs->put_Configuration(vlcTruckPlusLane), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( pcs->get_Configuration(&ct), S_OK );
   TRY_TEST( ct, vlcTruckPlusLane );
   str.Empty();
   TRY_TEST( pcs->put_Name(CComBSTR("TestName")), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( pcs->get_Name(&str), S_OK );
   TRY_TEST( str, CComBSTR("TestName") );


   // cause some events to fire
   CComPtr<IAxles> psps;
   AxleIndexType cnt;
   TRY_TEST( pcs->get_Axles(&psps), S_OK );
   TRY_TEST( psps->get_Count(&cnt), S_OK );
   TRY_TEST( cnt, 0 );

   CComPtr<IAxle> pss1, pss2;
   TRY_TEST( pss1.CoCreateInstance( CLSID_Axle ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( CLSID_Axle ) , S_OK );

   TRY_TEST( pss1->put_Weight(11.2), S_OK );
   TRY_TEST( pss1->put_Spacing(11.141), S_OK );

   TRY_TEST( psps->Add(pss1), S_OK);
   TEST_AXLES_FIRED();
   TRY_TEST( psps->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);

   TRY_TEST( psps->Add(pss2), S_OK);
   TEST_AXLES_FIRED();
   TRY_TEST( pss2->put_Weight(211.2), S_OK );
   TEST_AXLES_FIRED();
   TRY_TEST( pss2->put_Spacing(211.141), S_OK );
   TEST_AXLES_FIRED();

   TRY_TEST( psps->Remove(1), S_OK);
   TEST_AXLES_FIRED();

   // create our own axle point collection and add it
   CComPtr<IAxles> pspcnew;
   TRY_TEST(pspcnew.CoCreateInstance( CLSID_Axles ), S_OK );

   CComPtr<IAxle> pss3, pss4;
   TRY_TEST( pss3.CoCreateInstance( CLSID_Axle ) , S_OK );
   TRY_TEST( pss4.CoCreateInstance( CLSID_Axle ) , S_OK );

   TRY_TEST( pspcnew->Add(pss1), S_OK);   
   TRY_TEST( pspcnew->Insert(1,pss2), S_OK);   

   TRY_TEST( pcs->putref_Axles(pspcnew), S_OK );
   TEST_AXLES_FIRED();

   TRY_TEST( pspcnew->Add(pss3), S_OK);   
   TEST_AXLES_FIRED();
   TRY_TEST( pspcnew->Add(pss4), S_OK);   
   TEST_AXLES_FIRED();

   TRY_TEST( pspcnew->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 4);

   TRY_TEST( pss3->put_Weight(211.2), S_OK );
   TEST_AXLES_FIRED();
   TRY_TEST( pss2->put_Spacing(31.1), S_OK );
   TEST_AXLES_FIRED();

   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestVL"), 1.0);

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
      CComPtr<IVehicularLoad> pcs2;
      TRY_TEST(pcs2.CoCreateInstance( CLSID_VehicularLoad ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestVL"));

         CComPtr<IStructuredStorage2> piss2;
         TRY_TEST( pcs2.QueryInterface(&piss2), S_OK);

         // Load 
         TRY_TEST( piss2->Load(psl), S_OK );

         VARIANT_BOOL end;
         hr = psl->EndUnit(&end);

         TRY_TEST( psl->Close(), S_OK );

         // now save to a different file so we can compare files
         CComPtr<IStructuredSave2> pss2;
         TRY_TEST( pss2.CoCreateInstance( CLSID_StructuredSave2 ), S_OK );
         TRY_TEST( pss2->Open( CComBSTR("Test2.xml")), S_OK );

         // save our loaded version
         hr = pss2->BeginUnit(CComBSTR("TestVL"), 1.0);
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
   TRY_TEST(AtlUnadvise(pcs,IID_IVehicularLoadEvents,dwCookie),S_OK);
   pMe->Release();
}

HRESULT CTestVehicularLoad::OnVehicularLoadChanged(IVehicularLoad* VehicularLoad, ChangeType change)
{
   m_csLiveLoadFired = true;

   return S_OK;
}

HRESULT CTestVehicularLoad::OnVehicularLoadsChanged(IVehicularLoad* VehicularLoad, ChangeType change)
{
   m_csVehicularLoadsFired = true;
   return S_OK;
}

HRESULT CTestVehicularLoad::OnVehicularLoadsRenamed(/*[in]*/BSTR oldName, /*[in]*/BSTR newName)
{
   m_csVehicularLoadsFired = true;
   return S_OK;
}

HRESULT CTestVehicularLoad::OnVehicularLoadsAdded(/*[in]*/IVehicularLoad* load)
{
   m_csVehicularLoadsFired = true;
   return S_OK;
}

HRESULT CTestVehicularLoad::OnVehicularLoadsBeforeRemove(/*[in]*/IVehicularLoad* load)
{
   m_csVehicularLoadsFired = true;
   return S_OK;
}

HRESULT CTestVehicularLoad::OnCreateSegment(IVehicularLoad* pVehicularLoad)
{
   // give VehicularLoad a unique name
   TCHAR str[45];
   int cOut = _stprintf_s( str, 45, _T("VehicularLoad %d"), m_LastID++);
   ATLASSERT( cOut < 45 );

   CComBSTR name(str);

   return pVehicularLoad->put_Name(name);
}

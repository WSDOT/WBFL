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
m_CsCookie(0)
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
   hr = ContainerTester<ldIVehicularLoad,ldIVehicularLoads,CTestVehicularLoad,ldIVehicularLoadsEvents,&IID_ldIVehicularLoadsEvents, ldIEnumVehicularLoad>::TestVectorContainer(pMe,CLSID_ldVehicularLoad,CLSID_ldVehicularLoads);
   TRY_TEST(hr, S_OK);

   // first test a VehicleLoad by itself
   CComPtr<ldIVehicularLoad> vehicularLoad;
   TRY_TEST(vehicularLoad.CoCreateInstance( CLSID_ldVehicularLoad ), S_OK );
   Float64 s;
   AxleIndexType l;

   // test default values
   TRY_TEST( vehicularLoad->get_IMLane(&s), S_OK );
   TRY_TEST( s, 0.0 );
   TRY_TEST( vehicularLoad->get_IMTruck(&s), S_OK );
   TRY_TEST( s, 0.0 );
   TRY_TEST( vehicularLoad->get_LaneFactor(&s), S_OK );
   TRY_TEST( s, 1.0 );
   TRY_TEST( vehicularLoad->get_TruckFactor(&s), S_OK );
   TRY_TEST( s, 1.0 );
   TRY_TEST( vehicularLoad->get_SidewalkLoad(&s), S_OK );
   TRY_TEST( s, 0.0 );
   TRY_TEST( vehicularLoad->get_VariableMaxSpacing(&s), S_OK );
   TRY_TEST( s, 0.0 );
   TRY_TEST( vehicularLoad->get_VariableAxle(&l), S_OK );
   TRY_TEST( l, FIXED_AXLE_TRUCK );
   ldLiveLoadApplicabilityType at;
   TRY_TEST( vehicularLoad->get_Applicability(&at), S_OK );
   TRY_TEST( at, ldlaEntireStructure );
   VARIANT_BOOL un;
   TRY_TEST( vehicularLoad->get_UseNotional(&un), S_OK );
   TRY_TEST( un, VARIANT_TRUE );
   ldVehicularLoadConfigurationType ct;
   TRY_TEST( vehicularLoad->get_Configuration(&ct), S_OK );
   TRY_TEST( ct, ldvcDefault );
   CComBSTR str;
   TRY_TEST( vehicularLoad->get_Name(&str), S_OK );
   TRY_TEST( str.Length(), 0 );

   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<ldIVehicularLoadEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(vehicularLoad,punk,IID_ldIVehicularLoadEvents,&dwCookie),S_OK);

   TRY_TEST( vehicularLoad->put_IMLane(0.33), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( vehicularLoad->get_IMLane(&s), S_OK );
   TRY_TEST( s, 0.33 );
   TRY_TEST( vehicularLoad->put_IMTruck(0.22), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( vehicularLoad->get_IMTruck(&s), S_OK );
   TRY_TEST( s, 0.22 );
   TRY_TEST( vehicularLoad->put_LaneFactor(0.5), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( vehicularLoad->get_LaneFactor(&s), S_OK );
   TRY_TEST( s, 0.5 );
   TRY_TEST( vehicularLoad->put_TruckFactor(0.6), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( vehicularLoad->get_TruckFactor(&s), S_OK );
   TRY_TEST( s, 0.6 );
   TRY_TEST( vehicularLoad->put_SidewalkLoad(12.0), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( vehicularLoad->get_SidewalkLoad(&s), S_OK );
   TRY_TEST( s, 12.0 );
   TRY_TEST( vehicularLoad->put_VariableMaxSpacing(11.0), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( vehicularLoad->get_VariableMaxSpacing(&s), S_OK );
   TRY_TEST( s, 11.0 );
   TRY_TEST( vehicularLoad->put_VariableAxle(9), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( vehicularLoad->get_VariableAxle(&l), S_OK );
   TRY_TEST( l, 9 );
   TRY_TEST( vehicularLoad->put_Applicability(ldlaContraflexure), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( vehicularLoad->get_Applicability(&at), S_OK );
   TRY_TEST( at, ldlaContraflexure );
   TRY_TEST( vehicularLoad->put_UseNotional(VARIANT_FALSE), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( vehicularLoad->get_UseNotional(&un), S_OK );
   TRY_TEST( un, VARIANT_FALSE );
   TRY_TEST( vehicularLoad->put_Configuration(ldvcTruckPlusLane), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( vehicularLoad->get_Configuration(&ct), S_OK );
   TRY_TEST( ct, ldvcTruckPlusLane );
   str.Empty();
   TRY_TEST( vehicularLoad->put_Name(CComBSTR("TestName")), S_OK );
   TEST_VL_FIRED();
   TRY_TEST( vehicularLoad->get_Name(&str), S_OK );
   TRY_TEST( str, CComBSTR("TestName") );


   // cause some events to fire
   CComPtr<ldIAxles> psps;
   AxleIndexType cnt;
   TRY_TEST( vehicularLoad->get_Axles(&psps), S_OK );
   TRY_TEST( psps->get_Count(&cnt), S_OK );
   TRY_TEST( cnt, 0 );

   CComPtr<ldIAxle> pss1, pss2;
   TRY_TEST( pss1.CoCreateInstance( CLSID_ldAxle ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( CLSID_ldAxle ) , S_OK );

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
   CComPtr<ldIAxles> pspcnew;
   TRY_TEST(pspcnew.CoCreateInstance( CLSID_ldAxles ), S_OK );

   CComPtr<ldIAxle> pss3, pss4;
   TRY_TEST( pss3.CoCreateInstance( CLSID_ldAxle ) , S_OK );
   TRY_TEST( pss4.CoCreateInstance( CLSID_ldAxle ) , S_OK );

   TRY_TEST( pspcnew->Add(pss1), S_OK);   
   TRY_TEST( pspcnew->Insert(1,pss2), S_OK);   

   TRY_TEST( vehicularLoad->putref_Axles(pspcnew), S_OK );
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
      CComPtr<IStructuredSave2> pSave;
      TRY_TEST( pSave.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pSave->Open( CComBSTR("Test.xml")), S_OK );

      hr = pSave->BeginUnit(CComBSTR("TestVL"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> pStorage;
      TRY_TEST( vehicularLoad.QueryInterface(&pStorage), S_OK);

      // save
      pStorage->Save( pSave );

      hr = pSave->EndUnit();
      TRY_TEST( pSave->Close(), S_OK );
   }

   {
      // make a second vehicular load to work with
      CComPtr<ldIVehicularLoad> vehicularLoad2;
      TRY_TEST(vehicularLoad2.CoCreateInstance( CLSID_ldVehicularLoad ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> pLoad;
         TRY_TEST( pLoad.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( pLoad->Open( CComBSTR("Test.xml")), S_OK );

         hr = pLoad->BeginUnit(CComBSTR("TestVL"));

         CComPtr<IStructuredStorage2> pStorage2;
         TRY_TEST( vehicularLoad2.QueryInterface(&pStorage2), S_OK);

         // Load 
         TRY_TEST( pStorage2->Load(pLoad), S_OK );

         VARIANT_BOOL end;
         hr = pLoad->EndUnit(&end);

         TRY_TEST( pLoad->Close(), S_OK );

         // now save to a different file so we can compare files
         CComPtr<IStructuredSave2> pSave2;
         TRY_TEST( pSave2.CoCreateInstance( CLSID_StructuredSave2 ), S_OK );
         TRY_TEST( pSave2->Open( CComBSTR("Test2.xml")), S_OK );

         // save our loaded version
         hr = pSave2->BeginUnit(CComBSTR("TestVL"), 1.0);
         TRY_TEST( pStorage2->Save(pSave2), S_OK );
         hr = pSave2->EndUnit();
         TRY_TEST( pSave2->Close(), S_OK );
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
   TRY_TEST(AtlUnadvise(vehicularLoad,IID_ldIVehicularLoadEvents,dwCookie),S_OK);
   pMe->Release();
}

HRESULT CTestVehicularLoad::OnVehicularLoadChanged(ldIVehicularLoad* VehicularLoad, ldLoadingChangeType change)
{
   m_csLiveLoadFired = true;

   return S_OK;
}

HRESULT CTestVehicularLoad::OnVehicularLoadsChanged(ldIVehicularLoad* VehicularLoad, ldLoadingChangeType change)
{
   m_csVehicularLoadsFired = true;
   return S_OK;
}

HRESULT CTestVehicularLoad::OnVehicularLoadsRenamed(/*[in]*/BSTR oldName, /*[in]*/BSTR newName)
{
   m_csVehicularLoadsFired = true;
   return S_OK;
}

HRESULT CTestVehicularLoad::OnVehicularLoadsAdded(/*[in]*/ldIVehicularLoad* load)
{
   m_csVehicularLoadsFired = true;
   return S_OK;
}

HRESULT CTestVehicularLoad::OnVehicularLoadsBeforeRemove(/*[in]*/ldIVehicularLoad* load)
{
   m_csVehicularLoadsFired = true;
   return S_OK;
}

HRESULT CTestVehicularLoad::OnCreateSegment(ldIVehicularLoad* pVehicularLoad)
{
   // give VehicularLoad a unique name
   TCHAR str[45];
   int cOut = _stprintf_s( str, 45, _T("VehicularLoad %d"), m_LastID++);
   ATLASSERT( cOut < 45 );

   CComBSTR name(str);

   return pVehicularLoad->put_Name(name);
}

// TestSettlementLoad.cpp: implementation of the CTestSettlementLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSettlementLoad.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_LOAD_FIRED() TRY_TEST(pMe->m_csSettlementLoadFired, true); pMe->m_csSettlementLoadFired=false;
#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csSettlementLoadFired, true); pMe->m_csSettlementLoadFired=false;

#include "TestLoadContainer.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestSettlementLoad::CTestSettlementLoad():
m_csSettlementLoadFired(false),
m_CsCookie(0)
{
}

CTestSettlementLoad::~CTestSettlementLoad()
{
}

void CTestSettlementLoad::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestSettlementLoad>* pMe;
   CComObject<CTestSettlementLoad>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for SettlementLoads
   hr = LoadContainerTester<ldISettlementLoad,ldISettlementLoadItem,ldISettlementLoads,CTestSettlementLoad,ldISettlementLoadsEvents,&IID_ldISettlementLoadsEvents, ldIEnumSettlementLoad>::TestContainer(pMe,CLSID_ldSettlementLoad,CLSID_ldSettlementLoads);
   TRY_TEST(hr, S_OK);

   // first test a poi by itself
   CComPtr<ldISettlementLoad> pSettlementLoad;
   TRY_TEST(pSettlementLoad.CoCreateInstance( CLSID_ldSettlementLoad ), S_OK );
   CComBSTR bst;
   Float64 d;
   MemberIDType i;
   TRY_TEST( pSettlementLoad->get_MemberID(&i), S_OK );
   TRY_TEST( i, -1 );
   TRY_TEST( pSettlementLoad->get_Dx(&d), S_OK );
   TRY_TEST( d, 0.0);
   TRY_TEST( pSettlementLoad->get_Dy(&d), S_OK );
   TRY_TEST( d, 0.0);
   TRY_TEST( pSettlementLoad->get_Rz(&d), S_OK );
   TRY_TEST( d, 0.0);


   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<ldISettlementLoadEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pSettlementLoad,punk,IID_ldISettlementLoadEvents,&dwCookie),S_OK);

   // cause some events to fire
   TRY_TEST( pSettlementLoad->put_MemberID(3), S_OK );
   TEST_LOAD_FIRED();
   MemberIDType l;
   TRY_TEST( pSettlementLoad->get_MemberID(&l), S_OK );
   TRY_TEST( l, 3 );

   TRY_TEST( pSettlementLoad->put_Dx(1.1), S_OK );
   TEST_LOAD_FIRED();
   TRY_TEST( pSettlementLoad->get_Dx(&d), S_OK );
   TRY_TEST( d, 1.1);
   TRY_TEST( pSettlementLoad->put_Dy(2.2), S_OK );
   TEST_LOAD_FIRED();
   TRY_TEST( pSettlementLoad->get_Dy(&d), S_OK );
   TRY_TEST( d, 2.2);
   TRY_TEST( pSettlementLoad->put_Rz(3.3), S_OK );
   TEST_LOAD_FIRED();
   TRY_TEST( pSettlementLoad->get_Rz(&d), S_OK );
   TRY_TEST( d, 3.3);

   TRY_TEST( pSettlementLoad->put_MemberID(-1), E_INVALIDARG );

   // test persistence by saving and retrieving data and comparing raw xml

   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestSettlementLoad"), 1.0);

      // get interface SettlementLoadnter to Save
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pSettlementLoad.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<ldISettlementLoad> pSettlementLoad2;
      TRY_TEST(pSettlementLoad2.CoCreateInstance( CLSID_ldSettlementLoad ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestSettlementLoad"));

         IStructuredStorage2* piss2=nullptr;
         TRY_TEST( pSettlementLoad2.QueryInterface(&piss2), S_OK);

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
         hr = pss2->BeginUnit(CComBSTR("TestSettlementLoad"), 1.0);
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
   CComPtr<ldISettlementLoad> pclone;
   TRY_TEST(pSettlementLoad->Clone(&pclone), S_OK);

   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestSettlementLoad"), 1.0);

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
   TRY_TEST(AtlUnadvise(pSettlementLoad,IID_ldISettlementLoadEvents,dwCookie),S_OK);
   pMe->Release();
}



HRESULT CTestSettlementLoad::OnSettlementLoadChanged(ldISettlementLoad* SettlementLoad)
{
   m_csSettlementLoadFired = true;

   return S_OK;
}

HRESULT CTestSettlementLoad::OnSettlementLoadsChanged(ldISettlementLoadItem* SettlementLoad)
{
   m_csSettlementLoadFired = true;
   return S_OK;
}
HRESULT CTestSettlementLoad::OnSettlementLoadsAdded(ldISettlementLoadItem* SettlementLoad)
{
   m_csSettlementLoadFired = true;
   return S_OK;
}
HRESULT CTestSettlementLoad::OnSettlementLoadsBeforeRemove(ldISettlementLoadItem* SettlementLoad)
{
   m_csSettlementLoadFired = true;
   return S_OK;
}

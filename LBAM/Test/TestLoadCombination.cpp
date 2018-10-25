///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2012  Washington State Department of Transportation
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

// TestLoadCombination.cpp: implementation of the CTestLoadCombination class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TestLoadCombination.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_LoadCombination_FIRED()     TRY_TEST(pMe->m_csLoadCombinationFired, true); pMe->m_csLoadCombinationFired=false; pMe->m_csLoadCombinationsFired=false;
#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csLoadCombinationsFired, true); pMe->m_csLoadCombinationFired=false; pMe->m_csLoadCombinationsFired=false;

HRESULT TestContainer(CTestLoadCombination* pMe);

#include "TestSetContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestLoadCombination::CTestLoadCombination():
m_csLoadCombinationFired(false),
m_CsCookie(0),
m_LastID(0)
{
}

CTestLoadCombination::~CTestLoadCombination()
{
}

void CTestLoadCombination::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestLoadCombination>* pMe;
   CComObject<CTestLoadCombination>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for LoadCombinations
   hr = BSTRSetContainerTester<ILoadCombination,&CLSID_LoadCombination,ILoadCombinations,&CLSID_LoadCombinations,CTestLoadCombination,ILoadCombinationsEvents,&IID_ILoadCombinationsEvents, IEnumLoadCombination>::TestContainer(pMe);
   TRY_TEST(hr, S_OK);

   // test a LoadCombination by itself
   CComPtr<ILoadCombination> pLoadCombination;
   TRY_TEST(pLoadCombination.CoCreateInstance( CLSID_LoadCombination ), S_OK );
   CComBSTR str;
   TRY_TEST( pLoadCombination->get_Name(&str), S_OK );
   TRY_TEST( str.Length(), 0 );
   str.Empty();
   TRY_TEST( pLoadCombination->get_Description(&str), S_OK );
   TRY_TEST( str.Length(), 0 );

   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<ILoadCombinationEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pLoadCombination,punk,IID_ILoadCombinationEvents,&dwCookie),S_OK);

   // cause some events to fire
   TRY_TEST( pLoadCombination->put_Name(CComBSTR("LoadCombination 1")), S_OK );
   TEST_LoadCombination_FIRED();
   CComBSTR name;
   TRY_TEST( pLoadCombination->get_Name(&name), S_OK );
   TRY_TEST( name, CComBSTR("LoadCombination 1"));

   TRY_TEST( pLoadCombination->put_Description(CComBSTR("This is a description")), S_OK );
   TEST_LoadCombination_FIRED();
   CComBSTR desc;
   TRY_TEST( pLoadCombination->get_Description(&desc), S_OK );
   TRY_TEST( desc, CComBSTR("This is a description"));

   CComVariant varint = 2;
   TRY_TEST( pLoadCombination->put_ItemData(varint), S_OK );
   TEST_LoadCombination_FIRED();
   VARIANT vint;
   TRY_TEST( pLoadCombination->get_ItemData(&vint), S_OK );
   TRY_TEST( vint.intVal , 2);
   TRY_TEST( vint.vt , VT_I4);

   LiveLoadModelType llmt;
   TRY_TEST( pLoadCombination->GetLiveLoadModel(0,&llmt), E_INVALIDARG );

   TRY_TEST( pLoadCombination->AddLiveLoadModel(lltDesign), S_OK );
   TEST_LoadCombination_FIRED();
   TRY_TEST( pLoadCombination->GetLiveLoadModel(0,&llmt), S_OK );
   TRY_TEST( llmt, lltDesign);

   TRY_TEST( pLoadCombination->put_LiveLoadFactor(1.1), S_OK );
   TEST_LoadCombination_FIRED();
   Float64 factor;
   TRY_TEST( pLoadCombination->get_LiveLoadFactor(&factor), S_OK );
   TRY_TEST( factor, 1.1);

   LoadCombinationType lct;
   TRY_TEST( pLoadCombination->get_LoadCombinationType(&lct), S_OK );
   TRY_TEST( lct, lctUserDefined);

   TRY_TEST( pLoadCombination->put_LoadCombinationType(lctService), S_OK );
   TEST_LoadCombination_FIRED();
   TRY_TEST( pLoadCombination->get_LoadCombinationType(&lct), S_OK );
   TRY_TEST( lct, lctService);

   LiveLoadModelApplicationType lmat;
   TRY_TEST( pLoadCombination->get_LiveLoadModelApplicationType(&lmat), S_OK );
   TRY_TEST( lmat, llmaSum);

   TRY_TEST( pLoadCombination->put_LiveLoadModelApplicationType(llmaEnvelope), S_OK );
   TEST_LoadCombination_FIRED();
   TRY_TEST( pLoadCombination->get_LiveLoadModelApplicationType(&lmat), S_OK );
   TRY_TEST( lmat, llmaEnvelope);

   CollectionIndexType cnt;
   TRY_TEST( pLoadCombination->get_LoadCaseFactorCount(&cnt), S_OK );
   TRY_TEST(cnt, 0);

   TRY_TEST( pLoadCombination->AddLoadCaseFactor(CComBSTR("Load Case 0"), 0.9, 1.2), S_OK );
   TEST_LoadCombination_FIRED();
   TRY_TEST( pLoadCombination->get_LoadCaseFactorCount(&cnt), S_OK );
   TRY_TEST(cnt, 1);

   TRY_TEST( pLoadCombination->AddLoadCaseFactor(CComBSTR("Load Case 1"), 0.8, 1.3), S_OK );
   TEST_LoadCombination_FIRED();
   TRY_TEST( pLoadCombination->get_LoadCaseFactorCount(&cnt), S_OK );
   TRY_TEST(cnt, 2);

   CComBSTR lgnm;
   Float64 minf, maxf;
   TRY_TEST( pLoadCombination->GetLoadCaseFactor(0, &lgnm, &minf, &maxf), S_OK );
   TRY_TEST( lgnm, CComBSTR("Load Case 0"));
   TRY_TEST( minf, 0.9);
   TRY_TEST( maxf, 1.2);

   lgnm.Empty();
   TRY_TEST( pLoadCombination->GetLoadCaseFactor(1, &lgnm, &minf, &maxf), S_OK );
   TRY_TEST( lgnm, CComBSTR("Load Case 1"));
   TRY_TEST( minf, 0.8);
   TRY_TEST( maxf, 1.3);

   TRY_TEST( pLoadCombination->SetLoadCaseFactor(1, CComBSTR("New Load Case 1"), 0.95, 1.5), S_OK );
   TEST_LoadCombination_FIRED();

   lgnm.Empty();
   TRY_TEST( pLoadCombination->GetLoadCaseFactor(1, &lgnm, &minf, &maxf), S_OK );
   TRY_TEST( lgnm, CComBSTR("New Load Case 1"));
   TRY_TEST( minf, 0.95);
   TRY_TEST( maxf, 1.5);

   TRY_TEST( pLoadCombination->AddLoadCaseFactor(CComBSTR("Load Case 2"), 0.4, 0.8), S_OK );
   TEST_LoadCombination_FIRED();
   TRY_TEST( pLoadCombination->get_LoadCaseFactorCount(&cnt), S_OK );
   TRY_TEST(cnt, 3);

   TRY_TEST( pLoadCombination->RemoveLoadCaseFactor(1), S_OK );
   TEST_LoadCombination_FIRED();
   TRY_TEST( pLoadCombination->get_LoadCaseFactorCount(&cnt), S_OK );
   TRY_TEST(cnt, 2);

   lgnm.Empty();
   TRY_TEST( pLoadCombination->GetLoadCaseFactor(1, &lgnm, &minf, &maxf), S_OK );
   TRY_TEST( lgnm, CComBSTR("Load Case 2"));

   TRY_TEST( pLoadCombination->RemoveLoadCaseFactor(2), E_INVALIDARG);
   TRY_TEST( pLoadCombination->RemoveLoadCaseFactor(-1), E_INVALIDARG);
   lgnm.Empty();
   TRY_TEST( pLoadCombination->GetLoadCaseFactor(2, &lgnm, &minf, &maxf), E_INVALIDARG );
   TRY_TEST( pLoadCombination->SetLoadCaseFactor(2, CComBSTR("New Load Group 1"), 2, 3), E_INVALIDARG );
   TRY_TEST( pLoadCombination->SetLoadCaseFactor(0, CComBSTR(""), 4, 5), LBAM_E_BLANK_NAMES_NOT_ALLOWED );

   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestLoadCombination"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pLoadCombination.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<ILoadCombination> psm2;
      TRY_TEST(psm2.CoCreateInstance( CLSID_LoadCombination ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestLoadCombination"));

         IStructuredStorage2* piss2=NULL;
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
         hr = pss2->BeginUnit(CComBSTR("TestLoadCombination"), 1.0);
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
   CComPtr<ILoadCombination> pclone;
   TRY_TEST(pLoadCombination->Clone(&pclone), S_OK);

   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestLoadCombination"), 1.0);

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
   TRY_TEST(AtlUnadvise(pLoadCombination,IID_ILoadCombinationEvents,dwCookie),S_OK);
   pMe->Release();
}

HRESULT CTestLoadCombination::OnLoadCombinationRenamed(BSTR oldName, BSTR newName)
{
   m_csLoadCombinationFired = true;

   return S_OK;
}

HRESULT CTestLoadCombination::OnLoadCombinationChanged(ILoadCombination* LoadCombination, ChangeType change)
{
   if (change==cgtCombination)
      m_csLoadCombinationFired = true;
   else if (change==cgtDescription)
      m_csLoadCombinationFired = true;
   else if (change==cgtLoads)
      m_csLoadCombinationFired = true;
   else if (change==cgtUserItemData)
      m_csLoadCombinationFired = true;
   else
      ATLASSERT(0);

   return S_OK;
}

HRESULT CTestLoadCombination::OnLoadCombinationsChanged(ILoadCombination* LoadCombination, ChangeType change)
{
   if (change==cgtLoads)
      m_csLoadCombinationsFired = true;
   else if (change==cgtDescription)
      m_csLoadCombinationsFired = true;
   else
      ATLASSERT(0);

   return S_OK;
}

HRESULT CTestLoadCombination::OnLoadCombinationsRenamed(/*[in]*/BSTR oldName, /*[in]*/BSTR newName)
{
   m_csLoadCombinationsFired = true;
   return S_OK;
}

HRESULT CTestLoadCombination::OnLoadCombinationsAdded(/*[in]*/ILoadCombination* load)
{
   m_csLoadCombinationsFired = true;
   return S_OK;
}

HRESULT CTestLoadCombination::OnLoadCombinationsBeforeRemove(/*[in]*/ILoadCombination* load)
{
   m_csLoadCombinationsFired = true;
   return S_OK;
}

HRESULT CTestLoadCombination::OnCreateSegment(ILoadCombination* pLoadCombination)
{
   // give LoadCombination a unique name
   TCHAR str[45];
   int cOut = _stprintf_s( str, 45, _T("LoadCombination %d"), m_LastID++);
   ATLASSERT( cOut < 45 );

   CComBSTR name(str);

   return pLoadCombination->put_Name(name);
}

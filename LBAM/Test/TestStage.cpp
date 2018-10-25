///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// TestStage.cpp: implementation of the CTestStage class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TestStage.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_STAGE_FIRED()     TRY_TEST(pMe->m_csStageFired, true); pMe->m_csStageFired=false; pMe->m_csStagesFired=false;
#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csStagesFired, true); pMe->m_csStageFired=false; pMe->m_csStagesFired=false;

HRESULT TestContainer(CTestStage* pMe);

#include "TestSegmentContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestStage::CTestStage():
m_csStageFired(false),
m_CsCookie(0),
m_LastID(0)
{
}

CTestStage::~CTestStage()
{
}

void CTestStage::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestStage>* pMe;
   CComObject<CTestStage>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for Stages
   hr = TestContainer(pMe);
   TRY_TEST(hr, S_OK);

   // test a Stage by itself
   CComPtr<IStage> pStage;
   TRY_TEST(pStage.CoCreateInstance( CLSID_Stage ), S_OK );
   CComBSTR str;
   TRY_TEST( pStage->get_Name(&str), S_OK );
   TRY_TEST( str.Length(), 0 );
   str.Empty();
   TRY_TEST( pStage->get_Description(&str), S_OK );
   TRY_TEST( str.Length(), 0 );

   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<IStageEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pStage,punk,IID_IStageEvents,&dwCookie),S_OK);

   // cause some events to fire
   TRY_TEST( pStage->put_Name(CComBSTR("Stage 1")), S_OK );
   TEST_STAGE_FIRED();
   CComBSTR name;
   TRY_TEST( pStage->get_Name(&name), S_OK );
   TRY_TEST( name, CComBSTR("Stage 1"));

   TRY_TEST( pStage->put_Description(CComBSTR("This is a description")), S_OK );
   TEST_STAGE_FIRED();
   CComBSTR desc;
   TRY_TEST( pStage->get_Description(&desc), S_OK );
   TRY_TEST( desc, CComBSTR("This is a description"));

   // normal container tests do not test code to handle duplicate entries.
   // test them here
   CComPtr<IStages> pStages;
   TRY_TEST(pStages.CoCreateInstance( CLSID_Stages ), S_OK );

   TRY_TEST(pStages->Add(pStage), S_OK);
   TRY_TEST(pStages->Add(pStage), WCC_E_NAME_ALREADY_EXISTS);
   TRY_TEST(pStages->Insert(1, pStage), WCC_E_NAME_ALREADY_EXISTS);
   StageIndexType idx;
   TRY_TEST(pStages->FindIndex(CComBSTR("Stage 1"), &idx), S_OK);
   TRY_TEST(idx, 0);
   TRY_TEST(pStages->FindIndex(CComBSTR("Stage 21"), &idx), S_OK);
   TRY_TEST(idx, -1);

   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestSSM"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pStage.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<IStage> psm2;
      TRY_TEST(psm2.CoCreateInstance( CLSID_Stage ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestSSM"));

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
         hr = pss2->BeginUnit(CComBSTR("TestSSM"), 1.0);
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

   // disconnect our connections
   TRY_TEST(AtlUnadvise(pStage,IID_IStageEvents,dwCookie),S_OK);
   pMe->Release();
}


HRESULT TestContainer(CTestStage* pMe)
{
   StageIndexType cnt;

   // create some segments
   CComPtr<IStage> pss0, pss1, pss2,pss3,pss4, pss5, pss6;
   TRY_TEST( pss0.CoCreateInstance( CLSID_Stage ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss0), S_OK);
   TRY_TEST( pss1.CoCreateInstance( CLSID_Stage ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss1), S_OK);
   TRY_TEST( pss2.CoCreateInstance( CLSID_Stage ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss2), S_OK);
   TRY_TEST( pss3.CoCreateInstance( CLSID_Stage ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss3), S_OK);
   TRY_TEST( pss4.CoCreateInstance( CLSID_Stage ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss4), S_OK);
   TRY_TEST( pss5.CoCreateInstance(CLSID_Stage ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss5), S_OK);
   TRY_TEST( pss6.CoCreateInstance(CLSID_Stage ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss6), S_OK);

   // create the container
   CComPtr<IStages> pcnt1, pcnt2;
   TRY_TEST( pcnt1.CoCreateInstance( CLSID_Stages ) , S_OK );

   // set up the listener for the container
   DWORD dwCookie;
   CComQIPtr<IStageEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pcnt1,punk,IID_IStagesEvents,&dwCookie),S_OK);

   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 0);
   TRY_TEST( pcnt1->Add(pss0) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 1);
   TRY_TEST( pcnt1->Add(pss1) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 2);
   TRY_TEST( pcnt1->Add(pss3) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 3);
   TRY_TEST( pcnt1->Insert(2,pss2) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 4);
   TRY_TEST( pcnt1->Insert(4,pss4) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);
   TRY_TEST( pcnt1->Insert(0,pss5) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);
   TRY_TEST( pcnt1->MoveTo(0,5) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);
   TRY_TEST( pcnt1->Add(pss6) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 7);

   CComPtr<IStage> pss0t, pss1t, pss2t,pss3t,pss4t, pss5t, pss6t;
   TRY_TEST( pcnt1->get_Item(0,&pss0t) , S_OK );
   TRY_TEST(pss0t.IsEqualObject(pss0), true);
   TRY_TEST( pcnt1->get_Item(1,&pss1t) , S_OK );
   TRY_TEST(pss1t.IsEqualObject(pss1), true);
   TRY_TEST( pcnt1->get_Item(2,&pss2t) , S_OK );
   TRY_TEST(pss2t.IsEqualObject(pss2), true);
   TRY_TEST( pcnt1->get_Item(3,&pss3t) , S_OK );
   TRY_TEST(pss3t.IsEqualObject(pss3), true);
   TRY_TEST( pcnt1->get_Item(4,&pss4t) , S_OK );
   TRY_TEST(pss4t.IsEqualObject(pss4), true);
   TRY_TEST( pcnt1->get_Item(5,&pss5t) , S_OK );
   TRY_TEST(pss5t.IsEqualObject(pss5), true);
   TRY_TEST( pcnt1->get_Item(6,&pss6t) , S_OK );
   TRY_TEST(pss6t.IsEqualObject(pss6), true);

   TRY_TEST( pcnt1->RemoveByIndex(6) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);

   TRY_TEST( pcnt1->RemoveByIndex(0) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);

   TRY_TEST( pcnt1->Reverse() , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);

   CComPtr<IStage> pss1r, pss2r,pss3r,pss4r, pss5r;
   TRY_TEST( pcnt1->get_Item(4,&pss1r) , S_OK );
   TRY_TEST(pss1r.IsEqualObject(pss1), true);
   TRY_TEST( pcnt1->get_Item(3,&pss2r) , S_OK );
   TRY_TEST(pss2r.IsEqualObject(pss2), true);
   TRY_TEST( pcnt1->get_Item(2,&pss3r) , S_OK );
   TRY_TEST(pss3r.IsEqualObject(pss3), true);
   TRY_TEST( pcnt1->get_Item(1,&pss4r) , S_OK );
   TRY_TEST(pss4r.IsEqualObject(pss4), true);
   TRY_TEST( pcnt1->get_Item(0,&pss5r) , S_OK );
   TRY_TEST(pss5r.IsEqualObject(pss5), true);

   // check some bounds
   TRY_TEST( pcnt1->RemoveByIndex(-1) , E_INVALIDARG );
   TRY_TEST( pcnt1->RemoveByIndex(6) , E_INVALIDARG );
   TRY_TEST( pcnt1->MoveTo(-1, 2) , E_INVALIDARG );
   TRY_TEST( pcnt1->MoveTo( 2,-2) , E_INVALIDARG );
   TRY_TEST( pcnt1->MoveTo( 6, 2) , E_INVALIDARG );
   TRY_TEST( pcnt1->MoveTo( 2, 6) , E_INVALIDARG );
   pss0t.Release();
   TRY_TEST( pcnt1->get_Item(-1,&pss0t) , E_INVALIDARG );
   TRY_TEST( pcnt1->get_Item( 6,&pss0t) , E_INVALIDARG );

   // clone
   TRY_TEST( pcnt1->Clone(&pcnt2) , S_OK );
   TRY_TEST( pcnt2->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);

   // enumerators
   CComPtr<IEnumStage> penum;
   pcnt1->get__EnumElements(&penum);//, S_OK);
   cnt = 0;
   ULONG fetched=1;
   while(fetched==1)
   {
      CComPtr<IStage> isegi;
      TRY_TEST( SUCCEEDED( penum->Next(1, &isegi, &fetched) ), TRUE);
      if (fetched)
         cnt++;
   }
   TRY_TEST(cnt, 5);

   // stop listening
   TRY_TEST(AtlUnadvise(pcnt1,IID_IStagesEvents,dwCookie),S_OK);

   return S_OK;
}

HRESULT CTestStage::OnStageChanged(IStage* Stage, ChangeType change)
{
   if (change==cgtStage || change==cgtDescription)
      m_csStageFired = true;
   else
      ATLASSERT(0);

   return S_OK;
}

HRESULT CTestStage::OnStagesChanged(IStage* Stage, ChangeType change)
{
   if (change==cgtStage || change==cgtDescription)
      m_csStageFired = true;
   else
      ATLASSERT(0);

   return S_OK;
}

STDMETHODIMP CTestStage::OnStagesAdded(IStage* item, StageIndexType idx)
{
   m_csStagesFired = true;
   return S_OK;
}

STDMETHODIMP CTestStage::OnStagesBeforeRemove(IStage* item, StageIndexType idx)
{
   m_csStagesFired = true;
   return S_OK;
}

STDMETHODIMP CTestStage::OnStagesMoveTo(StageIndexType from, StageIndexType to)
{
   m_csStagesFired = true;
   return S_OK;
}

STDMETHODIMP CTestStage::OnStagesCopyTo(StageIndexType from, StageIndexType to)
{
   m_csStagesFired = true;
   return S_OK;
}

STDMETHODIMP CTestStage::OnStagesReverse()
{
   m_csStagesFired = true;
   return S_OK;
}


HRESULT CTestStage::OnCreateSegment(IStage* pstage)
{
   // give stage a unique name
   TCHAR str[45];
   int cOut = sprintf_s( str, 45, "Stage %d", m_LastID++);
   ATLASSERT( cOut < 45 );

   CComBSTR name(str);

   return pstage->put_Name(name);
}

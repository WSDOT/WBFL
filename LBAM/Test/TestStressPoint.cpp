///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// TestStressPoint.cpp: implementation of the CTestStressPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestStressPoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define TEST_SP_FIRED() TRY_TEST(pMe->m_spFired, true); pMe->m_spFired=false;
#define TEST_SP_COLL_FIRED(id) TRY_TEST(pMe->m_spCollFired, id); pMe->m_spCollFired=-1;

CTestStressPoint::CTestStressPoint()
{
   // set our triggers
   m_spFired = false;
   m_spCollFired = -1;
}

CTestStressPoint::~CTestStressPoint()
{
}

HRESULT CTestStressPoint::OnStressPointChanged(/*[in]*/IStressPoint* StressPoint)
{
   m_spFired = true;
   return S_OK;
}

HRESULT CTestStressPoint::OnStressPointsChanged(CollectionIndexType idx)
{
   m_spCollFired = idx;
   return S_OK;
}

HRESULT CTestStressPoint::OnStressPointsAdded(CollectionIndexType idx)
{
   m_spCollFired = idx;
   return S_OK;
}

HRESULT CTestStressPoint::OnStressPointsRemoved(CollectionIndexType idx)
{
   m_spCollFired = idx;
   return S_OK;
}

void CTestStressPoint::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestStressPoint>* pMe;
   CComObject<CTestStressPoint>::CreateInstance(&pMe);

   // first test a stress point by itself
   CComPtr<IStressPoint> pss0;
   TRY_TEST( pss0.CoCreateInstance( CLSID_StressPoint ) , S_OK );
   Float64 s;
   TRY_TEST( pss0->get_Sm(&s), S_OK );
   TRY_TEST( s, 0.0 );
   TRY_TEST( pss0->get_Sa(&s), S_OK );
   TRY_TEST( s, 0.0 );

   // let's listen to pss0
   DWORD dwSPCookie;
   CComQIPtr<IStressPointEvents> events(pMe);
   CComQIPtr<IUnknown,&IID_IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pss0,punk,IID_IStressPointEvents,&dwSPCookie),S_OK);

   TRY_TEST( pss0->put_Sm(1.2), S_OK );
   TEST_SP_FIRED();
   TRY_TEST( pss0->put_Sa(1.141), S_OK );
   TEST_SP_FIRED();
   TRY_TEST( s, 0.0 );

   TRY_TEST( pss0->get_Sm(&s), S_OK );
   TRY_TEST( s, 1.2 );
   TRY_TEST( pss0->get_Sa(&s), S_OK );
   TRY_TEST( s, 1.141 );

   // now let's create a container and test it
   CComPtr<IStressPoints> psc;
   hr = psc.CoCreateInstance( CLSID_StressPoints );// , S_OK );

   CollectionIndexType cnt;
   TRY_TEST( psc->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 0 );

   // let's listen to our container
   DWORD dwSPSCookie;
   TRY_TEST(AtlAdvise(psc,punk,IID_IStressPointsEvents,&dwSPSCookie),S_OK);

   TRY_TEST( psc->Add(pss0), S_OK);
   TEST_SP_COLL_FIRED(0);
   TRY_TEST( psc->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);

   CComPtr<IStressPoint> pss1, pss2;
   TRY_TEST( pss1.CoCreateInstance( CLSID_StressPoint ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( CLSID_StressPoint ) , S_OK );

   TRY_TEST( pss1->put_Sm(11.2), S_OK );
   TRY_TEST( pss1->put_Sa(11.141), S_OK );
   TRY_TEST( psc->Add(pss1), S_OK);
   TEST_SP_COLL_FIRED(1);

   TRY_TEST( psc->Add(pss0), S_OK);
   TEST_SP_COLL_FIRED(2);
   TRY_TEST( psc->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 3);

   TRY_TEST( psc->Insert(1, pss2), S_OK);
   TEST_SP_COLL_FIRED(1);
   TRY_TEST( pss2->put_Sm(211.2), S_OK );
   TEST_SP_COLL_FIRED(1);
   TRY_TEST( pss2->put_Sa(211.141), S_OK );
   TEST_SP_COLL_FIRED(1);
   TRY_TEST( psc->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 4);

   CComPtr<IStressPoint> psst;
   TRY_TEST( psc->get_Item(1, &psst), S_OK);
   TRY_TEST( psst==pss2, true );

   TRY_TEST( psc->Remove(1), S_OK);
   TEST_SP_COLL_FIRED(1);
   TRY_TEST( psc->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 3);

   psst.Release();
   TRY_TEST( psc->get_Item(1, &psst), S_OK);
   TRY_TEST( psst==pss1, true );

   // try C++ enumerators
   CComPtr<IEnumStressPoint> penum;
   psc->get__EnumElements(&penum);// , S_OK);

   IStressPoint* pj=0;
   unsigned long num_fetched=0;
   long i=0;
   penum->Next(1, &pj, &num_fetched);//, S_OK);
   while (num_fetched==1)
   {
      Float64 sm, sa;
      TRY_TEST(pj->get_Sa(&sa), S_OK);
      TRY_TEST(pj->get_Sm(&sm), S_OK);

      if (i==0)
      {
         TRY_TEST(sm, 1.2);
         TRY_TEST(sa, 1.141);
      }
      else if (i==1)
      {
         TRY_TEST(sm, 11.2);
         TRY_TEST(sa, 11.141);
      }

      pj->Release();
      TRY_TEST(FAILED(penum->Next(1, &pj, &num_fetched)),FALSE);
      i++;
   }

   // disconnect our connections
   TRY_TEST(AtlUnadvise(psc,IID_IStressPointsEvents,dwSPSCookie),S_OK);
   TRY_TEST(AtlUnadvise(pss0,IID_IStressPointEvents,dwSPCookie),S_OK);

}




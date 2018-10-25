///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2018  Washington State Department of Transportation
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

// TestSupport.cpp: implementation of the CTestSupport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSupport.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_STIFFNESS_FIRED() TRY_TEST(pMe->m_csStiffnessFired, true); pMe->InitEvents();
#define TEST_STRESS_FIRED() TRY_TEST(pMe->m_csStressPointsFired, true);  pMe->InitEvents();
#define TEST_DF_FIRED() TRY_TEST(pMe->m_csDfFired, true);  pMe->InitEvents();

#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csStiffnessFired, true); pMe->InitEvents();

#include "TestSegmentContainer.h"
#include "TestSeg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestSupport::CTestSupport():
m_csStiffnessFired(false),
m_csStressPointsFired(false),
m_CsCookie(0)
{
}

CTestSupport::~CTestSupport()
{
}

void CTestSupport::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestSupport>* pMe;
   CComObject<CTestSupport>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for Supports
   hr = ContainerTester<ISupport,&CLSID_Support,ISupports,&CLSID_Supports,CTestSupport,ISupportsEvents,&IID_ISupportsEvents,IEnumSupport,SupportIndexType>::TestSegmentContainer(pMe);
   TRY_TEST(hr, S_OK);

   // first test a sm by itself
   CComPtr<ISupport> psm;
   TRY_TEST(psm.CoCreateInstance( CLSID_Support ), S_OK );
   Float64 d;
   TRY_TEST( psm->get_Length(&d), S_OK );
   TRY_TEST( d, 0.0 );
   TRY_TEST( psm->get_BottomOffset(&d), S_OK );
   TRY_TEST( d, 0.0 );
   BoundaryConditionType ct;
   TRY_TEST( psm->get_BoundaryCondition(&ct), S_OK );
   TRY_TEST( ct, bcPinned );

   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<ISupportEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(psm,punk,IID_ISupportEvents,&dwCookie),S_OK);

   // cause some events to fire
   TRY_TEST( psm->put_Length(12.3), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( psm->get_Length(&d), S_OK );
   TRY_TEST( d, 12.3 );
   TRY_TEST( psm->put_BottomOffset(1.3), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( psm->get_BottomOffset(&d), S_OK );
   TRY_TEST( d, 1.3 );
   TRY_TEST( psm->put_BoundaryCondition(bcFixed), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( psm->get_BoundaryCondition(&ct), S_OK );
   TRY_TEST( ct, bcFixed );
   TRY_TEST( psm->put_BoundaryCondition(bcRoller), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( psm->get_BoundaryCondition(&ct), S_OK );
   TRY_TEST( ct, bcRoller );
   TRY_TEST( psm->put_BoundaryCondition(bcPinned), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( psm->get_BoundaryCondition(&ct), S_OK );
   TRY_TEST( ct, bcPinned );

   VARIANT_BOOL sym;
   TRY_TEST( psm->get_IsSymmetrical(&sym), S_OK );
   TRY_TEST( sym, VARIANT_FALSE );
   TRY_TEST( psm->put_IsSymmetrical(VARIANT_TRUE), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( psm->get_IsSymmetrical(&sym), S_OK );
   TRY_TEST( sym, VARIANT_TRUE );
   TRY_TEST( psm->put_IsSymmetrical(VARIANT_FALSE), S_OK  );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( psm->get_IsSymmetrical(&sym), S_OK );
   TRY_TEST( sym, VARIANT_FALSE );

   // distribution factor
   CComPtr<IDistributionFactor> df;
   TRY_TEST( psm->get_DistributionFactor(&df), S_OK );
   TRY_TEST( df->get_GPMSgl(&d), S_OK);
   TRY_TEST(d, 1.0);
   TRY_TEST( df->put_GPMSgl(1.2), S_OK);
   TEST_DF_FIRED();
   CComPtr<IDistributionFactor> df2;
   TRY_TEST( df2.CoCreateInstance(CLSID_DistributionFactor), S_OK);
   TRY_TEST( psm->putref_DistributionFactor(df2), S_OK );
   TEST_DF_FIRED();

   // muck with segments
   hr = TestSegments(pMe, psm.p);
   TRY_TEST(hr, S_OK);

   // test persistence by saving and retrieving data and comparing raw xml

   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestSSM"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( psm.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<ISupport> psm2;
      TRY_TEST(psm2.CoCreateInstance( CLSID_Support ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestSSM"));

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
   TRY_TEST(AtlUnadvise(psm,IID_ISupportEvents,dwCookie),S_OK);
   pMe->Release();
}


HRESULT CTestSupport::OnSupportChanged(ISupport* Support, BSTR stage, ChangeType change)
{
   if (change==cgtStiffness)
      m_csStiffnessFired = true;
   else if (change==cgtStress)
      m_csStressPointsFired = true;
   else if (change==cgtDistributionFactor)
      m_csDfFired = true;
   else
      ATLASSERT(false);

   return S_OK;
}


HRESULT CTestSupport::OnSupportsChanged(ISupport* Support, BSTR stage, ChangeType change)
{
   if (change==cgtStiffness)
      m_csStiffnessFired = true;
   else if (change==cgtStress)
      m_csStressPointsFired = true;
   else if (change==cgtDistributionFactor)
      m_csDfFired = true;
   else
      ATLASSERT(false);

   return S_OK;
}

STDMETHODIMP CTestSupport::OnSupportsAdded(ISupport* item, SupportIndexType idx)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSupport::OnSupportsBeforeRemove(ISupport* item, SupportIndexType idx)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSupport::OnSupportsMoveTo(SupportIndexType from, SupportIndexType to)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSupport::OnSupportsCopyTo(SupportIndexType from, SupportIndexType to)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSupport::OnSupportsReverse()
{
   m_csStiffnessFired = true;
   return S_OK;
}

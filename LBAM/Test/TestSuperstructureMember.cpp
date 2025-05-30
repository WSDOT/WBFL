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

// TestSuperstructureMember.cpp: implementation of the CTestSuperstructureMember class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSuperstructureMember.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_STIFFNESS_FIRED() TRY_TEST(pMe->m_csStiffnessFired, true); pMe->m_csStiffnessFired=false; pMe->m_csStressPointsFired=false;
#define TEST_STRESS_FIRED() TRY_TEST(pMe->m_csStressPointsFired, true);  pMe->m_csStiffnessFired=false; pMe->m_csStressPointsFired=false;

#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csStiffnessFired, true); pMe->m_csStiffnessFired=false; pMe->m_csStressPointsFired=false;

#include "TestSegmentContainer.h"
#include "TestSeg.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestSuperstructureMember::CTestSuperstructureMember():
m_csStiffnessFired(false),
m_csStressPointsFired(false),
m_CsCookie(0)
{
}

CTestSuperstructureMember::~CTestSuperstructureMember() 
{
}

void CTestSuperstructureMember::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestSuperstructureMember>* pMe;
   CComObject<CTestSuperstructureMember>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for SuperstructureMembers
   CComPtr<ISuperstructureMember> psm;
   TRY_TEST(psm.CoCreateInstance( CLSID_SuperstructureMember ), S_OK );
   hr = ContainerTester<ISuperstructureMember,&CLSID_SuperstructureMember,ISuperstructureMembers,&CLSID_SuperstructureMembers,CTestSuperstructureMember,ISuperstructureMembersEvents,&IID_ISuperstructureMembersEvents,IEnumSuperstructureMember,IndexType>::TestSegmentContainer(pMe);
   TRY_TEST(hr, S_OK);

   // first test a sm by itself
   Float64 d;
   TRY_TEST( psm->get_Length(&d), S_OK );
   TRY_TEST( d, 0.0 );
   VARIANT_BOOL bIsReleased;
   CComBSTR relStage;
   TRY_TEST( psm->GetEndReleaseRemovalStage(ssLeft,&relStage), S_OK);
   TRY_TEST( psm->IsEndReleased(ssLeft,mrtNone,&bIsReleased), S_OK );
   TRY_TEST( bIsReleased, VARIANT_TRUE );
   TRY_TEST( relStage.Length(), 0 );
   relStage.Empty();
   TRY_TEST( psm->GetEndReleaseRemovalStage(ssRight,&relStage), S_OK);
   TRY_TEST( psm->IsEndReleased(ssRight, mrtNone, &bIsReleased), S_OK );
   TRY_TEST( bIsReleased, VARIANT_TRUE );
   TRY_TEST( relStage.Length(), 0 );

   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<ISuperstructureMemberEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(psm,punk,IID_ISuperstructureMemberEvents,&dwCookie),S_OK);

   // cause some events to fire
   TRY_TEST( psm->put_Length(12.3), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( psm->get_Length(&d), S_OK );
   TRY_TEST( d, 12.3 );
   TRY_TEST( psm->SetEndReleaseRemovalStage(ssLeft, CComBSTR("Stage 2")), S_OK );
   TRY_TEST( psm->SetEndRelease(ssLeft, mrtMz), S_OK );
   TEST_STIFFNESS_FIRED();
   relStage.Empty();
   TRY_TEST( psm->GetEndReleaseRemovalStage(ssLeft,&relStage), S_OK);
   TRY_TEST( psm->IsEndReleased(ssLeft, mrtMz, &bIsReleased), S_OK );
   TRY_TEST( bIsReleased, VARIANT_TRUE );
   TRY_TEST( relStage, "Stage 2" );
   TRY_TEST( psm->SetEndReleaseRemovalStage(ssLeft, CComBSTR("Stage 3")), S_OK );
   TRY_TEST( psm->SetEndRelease(ssLeft, mrtMz), S_OK );
   TEST_STIFFNESS_FIRED();
   relStage.Empty();
   TRY_TEST( psm->GetEndReleaseRemovalStage(ssLeft,&relStage), S_OK);
   TRY_TEST( psm->IsEndReleased(ssLeft, mrtMz, &bIsReleased), S_OK );
   TRY_TEST( bIsReleased, VARIANT_TRUE );
   TRY_TEST( relStage, "Stage 3" );
   relStage.Empty();
   TRY_TEST( psm->SetEndReleaseRemovalStage(ssRight,CComBSTR("Stage 2")),S_OK);
   TRY_TEST( psm->SetEndRelease(ssRight, mrtMz), S_OK );
   TEST_STIFFNESS_FIRED();
   relStage.Empty();
   TRY_TEST( psm->GetEndReleaseRemovalStage(ssRight,&relStage), S_OK);
   TRY_TEST( psm->IsEndReleased(ssRight, mrtMz, &bIsReleased), S_OK );
   TRY_TEST( bIsReleased, VARIANT_TRUE );
   TRY_TEST( relStage, "Stage 2" );
   TRY_TEST( psm->SetEndReleaseRemovalStage(ssRight,CComBSTR("Stage 4")),S_OK);
   TRY_TEST( psm->SetEndRelease(ssRight, mrtMz), S_OK );
   TEST_STIFFNESS_FIRED();
   relStage.Empty();
   TRY_TEST( psm->GetEndReleaseRemovalStage(ssRight,&relStage),S_OK);
   TRY_TEST( psm->IsEndReleased(ssRight, mrtMz, &bIsReleased), S_OK );
   TRY_TEST( relStage, "Stage 4" );
   TRY_TEST( bIsReleased, VARIANT_TRUE );
   TRY_TEST( psm->SetEndRelease(ssRight, mrtNone), S_OK );
   TEST_STIFFNESS_FIRED();
   relStage.Empty();
   TRY_TEST( psm->IsEndReleased(ssRight, mrtNone, &bIsReleased), S_OK );
   TRY_TEST( bIsReleased, VARIANT_TRUE );


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
      CComPtr<ISuperstructureMember> psm2;
      TRY_TEST(psm2.CoCreateInstance( CLSID_SuperstructureMember ), S_OK );

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
   TRY_TEST(AtlUnadvise(psm,IID_ISuperstructureMemberEvents,dwCookie),S_OK);
   pMe->Release();
}




HRESULT CTestSuperstructureMember::OnSuperstructureMemberChanged(ISuperstructureMember* SuperstructureMember, BSTR stage, ChangeType change)
{
   if (change==cgtStiffness)
      m_csStiffnessFired = true;
   else if (change==cgtStress)
      m_csStressPointsFired = true;
   else
      ATLASSERT(false);

   return S_OK;
}

STDMETHODIMP CTestSuperstructureMember::OnSuperstructureMembersChanged(ISuperstructureMember* SuperstructureMember, BSTR stage, ChangeType change)
{
   if (change==cgtStiffness)
      m_csStiffnessFired = true;
   else if (change==cgtStress)
      m_csStressPointsFired = true;
   else
      ATLASSERT(false);

   return S_OK;
}

STDMETHODIMP CTestSuperstructureMember::OnSuperstructureMembersAdded(ISuperstructureMember* item, IndexType idx)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSuperstructureMember::OnSuperstructureMembersBeforeRemove(ISuperstructureMember* item, IndexType idx)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSuperstructureMember::OnSuperstructureMembersMoveTo(IndexType from, IndexType to)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSuperstructureMember::OnSuperstructureMembersCopyTo(IndexType from, IndexType to)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSuperstructureMember::OnSuperstructureMembersReverse()
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSuperstructureMember::OnSuperstructureMembersOffset()
{
   m_csStiffnessFired = true;
   return S_OK;
}


///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2019  Washington State Department of Transportation
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

// TestCrossSection.cpp: implementation of the CTestCrossSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCrossSection.h"
#include <string>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEST_STIFFNESS_FIRED() TRY_TEST(pMe->m_csStiffnessFired, true); pMe->m_csStiffnessFired=false; pMe->m_csStressPointsFired=false;
#define TEST_STRESS_FIRED() TRY_TEST(pMe->m_csStressPointsFired, true);  pMe->m_csStiffnessFired=false; pMe->m_csStressPointsFired=false;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCrossSection::CTestCrossSection():
m_csStiffnessFired(false),
m_csStressPointsFired(false),
m_CsCookie(0)
{
}

CTestCrossSection::~CTestCrossSection()
{
}

void CTestCrossSection::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestCrossSection>* pMe;
   CComObject<CTestCrossSection>::CreateInstance(&pMe);
   pMe->AddRef();

   // first test a cs by itself
   CComPtr<ISegmentCrossSection> pcs;
   TRY_TEST(pcs.CoCreateInstance( CLSID_SegmentCrossSection ), S_OK );
   Float64 s;
   TRY_TEST( pcs->get_EAForce(&s), S_OK );
   TRY_TEST( s, 1.0 );
   TRY_TEST( pcs->get_EIForce(&s), S_OK );
   TRY_TEST( s, 1.0 );
   TRY_TEST( pcs->get_EADefl(&s), S_OK );
   TRY_TEST( s, 1.0 );
   TRY_TEST( pcs->get_EIDefl(&s), S_OK );
   TRY_TEST( s, 1.0 );
   TRY_TEST( pcs->get_ThermalCoeff(&s), S_OK );
   TRY_TEST( s, 0.0 );
   TRY_TEST( pcs->get_Depth(&s), S_OK );
   TRY_TEST( s, 1.0 );

   // let's listen to pcs
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pMe);
   TRY_TEST(AtlAdvise(pcs,punk,IID_ISegmentCrossSectionEvents,&dwCookie),S_OK);

   // cause some events to fire
   TRY_TEST( pcs->put_EAForce(1.1), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pcs->put_EIForce(1.2), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pcs->put_EADefl(1.3), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pcs->put_EIDefl(1.4), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pcs->put_ThermalCoeff(1.5), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pcs->put_Depth(1.6), S_OK );
   TEST_STIFFNESS_FIRED();

   // test get/put
   TRY_TEST( pcs->get_EAForce(&s), S_OK );
   TRY_TEST( s, 1.1 );
   TRY_TEST( pcs->get_EIForce(&s), S_OK );
   TRY_TEST( s, 1.2 );
   TRY_TEST( pcs->get_EADefl(&s), S_OK );
   TRY_TEST( s, 1.3 );
   TRY_TEST( pcs->get_EIDefl(&s), S_OK );
   TRY_TEST( s, 1.4 );
   TRY_TEST( pcs->get_ThermalCoeff(&s), S_OK );
   TRY_TEST( s, 1.5 );
   TRY_TEST( pcs->get_Depth(&s), S_OK );
   TRY_TEST( s, 1.6 );

   TRY_TEST( pcs->SetStiffness(1,2,3,4), S_OK );
   TEST_STIFFNESS_FIRED();
   Float64 eaf, eif, ead, eid;
   TRY_TEST( pcs->GetStiffness(&eaf, &eif, &ead, &eid), S_OK );
   TRY_TEST( eaf, 1 );
   TRY_TEST( eif, 2 );
   TRY_TEST( ead, 3 );
   TRY_TEST( eid, 4 );
   TRY_TEST( pcs->SetStiffness(-1,2,3,4), E_INVALIDARG );
   TRY_TEST( pcs->SetStiffness(1,-2,3,4), E_INVALIDARG );
   TRY_TEST( pcs->SetStiffness(1,2,-3,4), E_INVALIDARG );
   TRY_TEST( pcs->SetStiffness(1,2,3,-4), E_INVALIDARG );

   TRY_TEST( pcs->put_EAForce(-1.1), E_INVALIDARG );
   TRY_TEST( pcs->put_EIForce(-1.2), E_INVALIDARG );
   TRY_TEST( pcs->put_EADefl(-1.3), E_INVALIDARG );
   TRY_TEST( pcs->put_EIDefl(-1.4), E_INVALIDARG );
   TRY_TEST( pcs->put_ThermalCoeff(-1.5), E_INVALIDARG );
   TRY_TEST( pcs->put_Depth(-1.6), E_INVALIDARG );

   // muck with stress points
   CComPtr<IStressPoints> psps;
   CollectionIndexType cnt;
   TRY_TEST( pcs->get_StressPoints(&psps), S_OK );
   TRY_TEST( psps->get_Count(&cnt), S_OK );
   TRY_TEST( cnt, 0 );

   CComPtr<IStressPoint> pss1, pss2;
   TRY_TEST( pss1.CoCreateInstance( CLSID_StressPoint ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( CLSID_StressPoint ) , S_OK );

   TRY_TEST( pss1->put_Sm(11.2), S_OK );
   TRY_TEST( pss1->put_Sa(11.141), S_OK );

   TRY_TEST( psps->Add(pss1), S_OK);
   TEST_STRESS_FIRED();
   TRY_TEST( psps->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);

   TRY_TEST( psps->Add(pss2), S_OK);
   TEST_STRESS_FIRED();
   TRY_TEST( pss2->put_Sm(211.2), S_OK );
   TEST_STRESS_FIRED();
   TRY_TEST( pss2->put_Sa(211.141), S_OK );
   TEST_STRESS_FIRED();

   TRY_TEST( psps->Remove(1), S_OK);
   TEST_STRESS_FIRED();

   // create our own stress point collection and add it
   CComPtr<IStressPoints> pspcnew;
   TRY_TEST(pspcnew.CoCreateInstance( CLSID_StressPoints ), S_OK );

   CComPtr<IStressPoint> pss3, pss4;
   TRY_TEST( pss3.CoCreateInstance( CLSID_StressPoint ) , S_OK );
   TRY_TEST( pss4.CoCreateInstance( CLSID_StressPoint ) , S_OK );

   TRY_TEST( pspcnew->Add(pss1), S_OK);   
   TRY_TEST( pspcnew->Insert(1,pss2), S_OK);   

   TRY_TEST( pcs->putref_StressPoints(pspcnew), S_OK );
   TEST_STRESS_FIRED();

   TRY_TEST( pspcnew->Add(pss3), S_OK);   
   TEST_STRESS_FIRED();
   TRY_TEST( pspcnew->Add(pss4), S_OK);   
   TEST_STRESS_FIRED();

   TRY_TEST( pspcnew->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 4);

   TRY_TEST( pss3->put_Sm(211.2), S_OK );
   TEST_STRESS_FIRED();
   TRY_TEST( pss2->put_Sa(31.1), S_OK );
   TEST_STRESS_FIRED();

   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestCS"), 1.0);

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
      CComPtr<ISegmentCrossSection> pcs2;
      TRY_TEST(pcs2.CoCreateInstance( CLSID_SegmentCrossSection ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestCS"));

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
         hr = pss2->BeginUnit(CComBSTR("TestCS"), 1.0);
         TRY_TEST( piss2->Save(pss2), S_OK );
         hr = pss2->EndUnit();
         TRY_TEST( pss2->Close(), S_OK );

         piss2.Release();
         pss2.Release();
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
      if1.close();

      TRY_TEST( x1, x2 );

   }
   catch(...)
   {
      ATLASSERT(false); // big problems
      TRY_TEST(0,1); 
   }

   // disconnect our connections
   TRY_TEST(AtlUnadvise(pcs,IID_ISegmentCrossSectionEvents,dwCookie),S_OK);
   pMe->Release();
}

HRESULT CTestCrossSection::OnSegmentCrossSectionChanged(ISegmentCrossSection* CrossSection, ChangeType change)
{
   if (change==cgtStiffness)
      m_csStiffnessFired = true;
   else if (change==cgtStress)
      m_csStressPointsFired = true;
   else
      ATLASSERT(false);

   return S_OK;
}

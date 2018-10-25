///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// TestSpan.cpp: implementation of the CTestSpan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSpan.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_STIFFNESS_FIRED() TRY_TEST(pMe->m_csStiffnessFired, true); pMe->m_csStiffnessFired=false; pMe->m_csStressPointsFired=false; pMe->m_csCombinationFired=false;
#define TEST_STRESS_FIRED() TRY_TEST(pMe->m_csStressPointsFired, true); pMe->m_csStiffnessFired=false; pMe->m_csStressPointsFired=false; pMe->m_csCombinationFired=false;
#define TEST_COMBO_FIRED() TRY_TEST(pMe->m_csCombinationFired, true);   pMe->m_csStiffnessFired=false; pMe->m_csStressPointsFired=false; pMe->m_csCombinationFired=false;

#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csStiffnessFired, true); pMe->m_csStiffnessFired=false; pMe->m_csStressPointsFired=false; pMe->m_csCombinationFired=false;


#include "TestSegmentContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestSpan::CTestSpan():
m_csStiffnessFired(false),
m_csStressPointsFired(false),
m_csCombinationFired(false),
m_CsCookie(0)
{
}

CTestSpan::~CTestSpan()
{
}

void CTestSpan::Test()
{
   HRESULT hr;


   // create a listener
   CComObject<CTestSpan>* pMe;
   CComObject<CTestSpan>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for spans
   hr = ContainerTester<ISpan,&CLSID_Span,ISpans,&CLSID_Spans,CTestSpan,ISpansEvents,&IID_ISpansEvents,IEnumSpan,SpanIndexType>::TestSegmentContainer(pMe);
   TRY_TEST(hr, S_OK);

   // test a span by itself
   CComPtr<ISpan> pspan;
   TRY_TEST(pspan.CoCreateInstance( CLSID_Span ), S_OK );
   Float64 d;
   TRY_TEST( pspan->get_Length(&d), S_OK );
   TRY_TEST( d, 0.0 );

   // let's listen to pcs
   DWORD dwSpanCookie;
   CComQIPtr<ISpanEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pspan,punk,IID_ISpanEvents,&dwSpanCookie),S_OK);


   // cause some events to fire
   TRY_TEST( pspan->put_Length(12.3), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pspan->get_Length(&d), S_OK );
   TRY_TEST( d, 12.3 );
   TRY_TEST( pspan->put_Length(-0.02), E_INVALIDARG );


   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestSSM"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pspan.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<ISpan> psm2;
      TRY_TEST(psm2.CoCreateInstance( CLSID_Span ), S_OK );

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
   TRY_TEST(AtlUnadvise(pspan,IID_ISpanEvents,dwSpanCookie),S_OK);
   pMe->Release();
}


HRESULT CTestSpan::OnSpanChanged(ISpan* Span, BSTR stage, ChangeType change)
{
   if (change==cgtStiffness)
      m_csStiffnessFired = true;
   else if (change==cgtStress)
      m_csStressPointsFired = true;
   else if (change==cgtCombination)
      m_csCombinationFired = true;
   else
      ATLASSERT(false);

   return S_OK;
}


HRESULT CTestSpan::OnSpansChanged(ISpan* Span, BSTR stage, ChangeType change)
{
   if (change==cgtStiffness)
      m_csStiffnessFired = true;
   else if (change==cgtStress)
      m_csStressPointsFired = true;
   else if (change==cgtCombination)
      m_csCombinationFired = true;
   else
      ATLASSERT(false);

   return S_OK;
}

STDMETHODIMP CTestSpan::OnSpansAdded(ISpan* item, SpanIndexType idx)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSpan::OnSpansBeforeRemove(ISpan* item, SpanIndexType idx)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSpan::OnSpansMoveTo(SpanIndexType from, SpanIndexType to)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSpan::OnSpansCopyTo(SpanIndexType from, SpanIndexType to)
{
   m_csStiffnessFired = true;
   return S_OK;
}
STDMETHODIMP CTestSpan::OnSpansReverse()
{
   m_csStiffnessFired = true;
   return S_OK;
}

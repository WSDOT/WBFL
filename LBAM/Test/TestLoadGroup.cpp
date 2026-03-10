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

// TestLoadGroup.cpp: implementation of the CTestLoadGroup class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TestLoadGroup.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_LOADGROUP_FIRED()     TRY_TEST(pMe->m_csLoadGroupFired, true); pMe->m_csLoadGroupFired=false; pMe->m_csLoadGroupsFired=false;
#define TEST_CONTAINER_FIRED() TRY_TEST(pMe->m_csLoadGroupsFired, true); pMe->m_csLoadGroupFired=false; pMe->m_csLoadGroupsFired=false;

HRESULT TestContainer(CTestLoadGroup* pMe);

#include "TestSetContainer.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestLoadGroup::CTestLoadGroup():
m_csLoadGroupFired(false),
m_CsCookie(0),
m_LastID(0)
{
}

CTestLoadGroup::~CTestLoadGroup()
{
}

void CTestLoadGroup::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestLoadGroup>* pMe;
   CComObject<CTestLoadGroup>::CreateInstance(&pMe);
   pMe->AddRef();

   // test the container for LoadGroups
   hr = BSTRSetContainerTester<ILoadGroup,&CLSID_LoadGroup,ILoadGroups,&CLSID_LoadGroups,CTestLoadGroup,ILoadGroupsEvents,&IID_ILoadGroupsEvents, IEnumLoadGroup>::TestContainer(pMe);
   TRY_TEST(hr, S_OK);

   // test a LoadGroup by itself
   CComPtr<ILoadGroup> pLoadGroup;
   TRY_TEST(pLoadGroup.CoCreateInstance( CLSID_LoadGroup ), S_OK );
   CComBSTR str;
   TRY_TEST( pLoadGroup->get_Name(&str), S_OK );
   TRY_TEST( str.Length(), 0 );
   str.Empty();
   TRY_TEST( pLoadGroup->get_Description(&str), S_OK );
   TRY_TEST( str.Length(), 0 );

   // let's listen to pcs
   DWORD dwCookie;
   CComQIPtr<ILoadGroupEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pLoadGroup,punk,IID_ILoadGroupEvents,&dwCookie),S_OK);

   // cause some events to fire
   TRY_TEST( pLoadGroup->put_Name(CComBSTR("LoadGroup 1")), S_OK );
   TEST_LOADGROUP_FIRED();
   CComBSTR name;
   TRY_TEST( pLoadGroup->get_Name(&name), S_OK );
   TRY_TEST( name, CComBSTR("LoadGroup 1"));

   TRY_TEST( pLoadGroup->put_Description(CComBSTR("This is a description")), S_OK );
   TEST_LOADGROUP_FIRED();
   CComBSTR desc;
   TRY_TEST( pLoadGroup->get_Description(&desc), S_OK );
   TRY_TEST( desc, CComBSTR("This is a description"));

   VARIANT_BOOL trans;
   TRY_TEST( pLoadGroup->get_Transient(&trans), S_OK );
   TRY_TEST( trans, VARIANT_FALSE);
   TRY_TEST( pLoadGroup->put_Transient(VARIANT_TRUE), S_OK );
   TEST_LOADGROUP_FIRED();
   TRY_TEST( pLoadGroup->get_Transient(&trans), S_OK );
   TRY_TEST( trans, VARIANT_TRUE);
   TRY_TEST( pLoadGroup->put_Transient(VARIANT_FALSE), S_OK );
   TEST_LOADGROUP_FIRED();
   TRY_TEST( pLoadGroup->get_Transient(&trans), S_OK );
   TRY_TEST( trans, VARIANT_FALSE);


   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestSSM"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pLoadGroup.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<ILoadGroup> psm2;
      TRY_TEST(psm2.CoCreateInstance( CLSID_LoadGroup ), S_OK );

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
   TRY_TEST(AtlUnadvise(pLoadGroup,IID_ILoadGroupEvents,dwCookie),S_OK);
   pMe->Release();
}

HRESULT CTestLoadGroup::OnLoadGroupRenamed(BSTR oldName, BSTR newName)
{
   m_csLoadGroupFired = true;

   return S_OK;
}

HRESULT CTestLoadGroup::OnLoadGroupChanged(ILoadGroup* LoadGroup, ChangeType change)
{
   if (change==cgtCombination)
      m_csLoadGroupFired = true;
   else if (change==cgtDescription)
      m_csLoadGroupFired = true;
   else if (change==cgtLoads)
      m_csLoadGroupFired = true;
   else
      ATLASSERT(false);

   return S_OK;
}

HRESULT CTestLoadGroup::OnLoadGroupsChanged(ILoadGroup* LoadGroup, ChangeType change)
{
   if (change==cgtLoads)
      m_csLoadGroupsFired = true;
   else if (change==cgtDescription)
      m_csLoadGroupsFired = true;
   else
      ATLASSERT(false);

   return S_OK;
}

HRESULT CTestLoadGroup::OnLoadGroupsRenamed(/*[in]*/BSTR oldName, /*[in]*/BSTR newName)
{
   m_csLoadGroupsFired = true;
   return S_OK;
}

HRESULT CTestLoadGroup::OnLoadGroupsAdded(/*[in]*/ILoadGroup* load)
{
   m_csLoadGroupsFired = true;
   return S_OK;
}

HRESULT CTestLoadGroup::OnLoadGroupsBeforeRemove(/*[in]*/ILoadGroup* load)
{
   m_csLoadGroupsFired = true;
   return S_OK;
}

HRESULT CTestLoadGroup::OnCreateSegment(ILoadGroup* pLoadGroup)
{
   // give LoadGroup a unique name
   TCHAR str[45];
   int cOut = _stprintf_s( str, 45, _T("LoadGroup %d"), m_LastID++);
   ATLASSERT( cOut < 45 );

   CComBSTR name(str);

   return pLoadGroup->put_Name(name);
}

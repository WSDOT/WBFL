///////////////////////////////////////////////////////////////////////
// Tools Test - Test driver for WBFLTools library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// TestStructuredStorage2.cpp: implementation of the CTestStructuredStorage2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestStructuredStorage2.h"
#include <vector>
#include <string>
#include <fstream>
#include <COMDEF.H>
#include <memory>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestStructuredStorage2::CTestStructuredStorage2()
{

}

CTestStructuredStorage2::~CTestStructuredStorage2()
{

}

void CTestStructuredStorage2::Test()
{
   // create a saver, open a file and save ourself
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance( CLSID_StructuredSave2 ), S_OK );
      TRY_TEST( pss->Open(CComBSTR("Test.xml")), S_OK );

      // make one of us to work with and initialize
      auto pSaved = std::make_unique<CTestStructuredStorage2>();
      pSaved->Initialize();

      // save ourself
      TRY_TEST( pSaved->SaveMe(pss), S_OK );
      TRY_TEST( pss->Close(), S_OK );
   }

   // now let's load and save to another file
   {
      CComPtr<IStructuredLoad2> psl;
      TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
      TRY_TEST( psl->Open(CComBSTR("Test.xml")), S_OK );

      // make one of us to work with and initialize
      auto pLoaded = std::make_unique<CTestStructuredStorage2>();

      // Load ourself
      TRY_TEST( pLoaded->LoadMe(psl), S_OK );
      TRY_TEST( psl->Close(), S_OK );

      // now save to a different file so we can compare files
      CComPtr<IStructuredSave2> pss2;
      TRY_TEST( pss2.CoCreateInstance( CLSID_StructuredSave2 ), S_OK );
      TRY_TEST( pss2->Open(CComBSTR("Test2.xml")), S_OK );

      // save our loaded version
      TRY_TEST( pLoaded->SaveMe(pss2), S_OK );
      TRY_TEST( pss2->Close(), S_OK );
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

   // Try testing the capability to load parts of a file

   // now let's load and save to another file
   {
      CComPtr<IStructuredLoad2> psl;
      TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
      TRY_TEST( psl->Open(CComBSTR("Test.xml")), S_OK );

      // make one of us to work with and initialize
      auto pLoaded = std::make_unique<CTestStructuredStorage2>();

      // Load ourself
      TRY_TEST( pLoaded->LoadPartial(psl), S_OK );
      TRY_TEST( psl->Close(), S_OK );
   }
}

HRESULT CTestStructuredStorage2::SaveMe(IStructuredSave2 *psave)
{
   // start off by saving properties
   psave->BeginUnit(CComBSTR("CTestStructuredStorage2"), 2.0); //, S_OK);

   TRY_TEST( psave->put_Property(CComBSTR("BSTR"), m_BSTR), S_OK);
   TRY_TEST( psave->put_Property(CComBSTR("Float64"), m_Float64), S_OK);
   TRY_TEST( psave->put_Property(CComBSTR("Float"), m_Float), S_OK);
   TRY_TEST( psave->put_Property(CComBSTR("BOOL"), m_BOOL), S_OK);
   TRY_TEST( psave->put_Property(CComBSTR("Short"), m_Short), S_OK);
   TRY_TEST( psave->put_Property(CComBSTR("Long"), m_Long), S_OK); 

   Float64 ver;
   TRY_TEST( psave->get_Version(&ver), S_OK); 
   TRY_TEST(ver, 2.0);
   TRY_TEST( psave->get_TopVersion(&ver), S_OK); 
   TRY_TEST(ver, 2.0);


   TRY_TEST( psave->BeginUnit(CComBSTR("Shapes"), 1.0), S_OK);
   TRY_TEST( psave->put_Property(CComBSTR("Count"), CComVariant((long)m_TestShapes.size())), S_OK);

   // now save container objects
   for (ShapeIterator i = m_TestShapes.begin(); i!=m_TestShapes.end(); i++)
   {
      CComVariant cp(*i);
      TRY_TEST( psave->put_Property(CComBSTR("Shape"), cp), S_OK);
   }

   TRY_TEST( psave->EndUnit(), S_OK); // shapes

   TRY_TEST( psave->put_Property(CComBSTR("UShort"), m_UShort), S_OK);
   TRY_TEST( psave->put_Property(CComBSTR("ULong"), m_ULong), S_OK);

   TRY_TEST( psave->EndUnit(), S_OK);

   return S_OK;
}

HRESULT CTestStructuredStorage2::LoadMe(IStructuredLoad2* pload)
{
   HRESULT hr = S_OK;
   TRY_TEST( pload->BeginUnit(CComBSTR("CTestStructuredStorage2")), S_OK);

   TRY_TEST( pload->get_Property(CComBSTR("BSTR"), &m_BSTR), S_OK);
   TRY_TEST( pload->get_Property(CComBSTR("Float64"), &m_Float64), S_OK);
   TRY_TEST( pload->get_Property(CComBSTR("Float"), &m_Float), S_OK);
   TRY_TEST( pload->get_Property(CComBSTR("BOOL"), &m_BOOL), S_OK);
   TRY_TEST( pload->get_Property(CComBSTR("Short"), &m_Short), S_OK);
   TRY_TEST( pload->get_Property(CComBSTR("Long"), &m_Long), S_OK);

   TRY_TEST( pload->BeginUnit(CComBSTR("Shapes")), S_OK);
   Float64 ver;
   pload->get_Version(&ver);
   TRY_TEST(ver, 1.0);

   _variant_t vcnt;
   TRY_TEST( pload->get_Property(CComBSTR("Count"), &vcnt), S_OK);

   long cnt = (long)vcnt;
   // now load container objects
   for (long i = 0; i<cnt; i++)
   {
      _variant_t cp;
      TRY_TEST( pload->get_Property(CComBSTR("Shape"), &cp), S_OK);

      IUnknown* piu = cp.punkVal;
      IPShape*  pis = nullptr;
      TRY_TEST( piu->QueryInterface(IID_IPShape, (void**)&pis), S_OK);

      m_TestShapes.push_back(pis);

      pis->Release();
   }

   VARIANT_BOOL b;
   TRY_TEST( pload->EndUnit(&b), S_OK); // shapes
   TRY_TEST(b, VARIANT_TRUE);

   TRY_TEST( pload->get_Property(CComBSTR("UShort"), &m_UShort), S_OK);
   TRY_TEST( pload->get_Property(CComBSTR("ULong"), &m_ULong), S_OK);

   TRY_TEST( pload->EndUnit(&b), S_OK);
   TRY_TEST(b, VARIANT_TRUE);

   return S_OK;
}

HRESULT CTestStructuredStorage2::LoadPartial(IStructuredLoad2* pload)
{
   // this routine test the ability of the parser to search for nodes
   // within a unit
   HRESULT hr = S_OK;
   TRY_TEST( pload->BeginUnit(CComBSTR("CTestStructuredStorage2")), S_OK);

   TRY_TEST( pload->get_Property(CComBSTR("BSTR"), &m_BSTR), S_OK);
   TRY_TEST( pload->get_Property(CComBSTR("Short"), &m_Short), S_OK);

   TRY_TEST( pload->get_Property(CComBSTR("UShort"), &m_UShort), S_OK);
   TRY_TEST( pload->get_Property(CComBSTR("ULong"), &m_ULong), S_OK);

   VARIANT_BOOL b;
   TRY_TEST( pload->EndUnit(&b), S_OK);
   TRY_TEST(b, VARIANT_TRUE);

   return S_OK;
}


void CTestStructuredStorage2::Initialize()
{
   m_BSTR   = CComVariant(OLESTR("Name of BSTR"));
   m_Float64 = Float64(3.14);
   m_Float  = float(2.71);
   m_BOOL   = true;
   m_Short  = short(-42);
   m_Long   = long(32);
   VARIANT var;
   var.vt = VT_UI2;
   var.uiVal = (unsigned short)322;
   m_UShort    = var;
   var.vt = VT_UI4;
   var.ulVal = (unsigned long)4242424332;
   m_ULong = var;

   // create some shapes and add them to us
   CComPtr<IPCircle> pcr;
   TRY_TEST( pcr.CoCreateInstance( CLSID_PCircle ), S_OK );
   pcr->put_X(1.1);
   pcr->put_Y(1.1);
   pcr->put_Diameter(1.0);

   CComPtr<IPCircle> pcr2;
   TRY_TEST( pcr2.CoCreateInstance( CLSID_PCircle ), S_OK );
   pcr2->put_X(1.2);
   pcr2->put_Y(1.2);
   pcr2->put_Diameter(2.0);

   // composite shape with circle in it
   CComPtr<IPCompositeShape> pcmp;
   TRY_TEST( pcmp.CoCreateInstance( CLSID_PCompositeShape ), S_OK );
   pcmp->put_X(1.0);
   pcmp->put_Y(1.0);
   pcmp->Add(pcr2);

   // another composite with the other composite in it, and the first circle
   CComPtr<IPCompositeShape> pcmp2;
   TRY_TEST( pcmp2.CoCreateInstance( CLSID_PCompositeShape ), S_OK );
   pcmp2->put_X(1.0);
   pcmp2->put_Y(1.0);
   pcmp2->Add(pcmp);
   pcmp2->Add(pcr);

   // add shapes
   ShapePtr pshpcr(pcr);
   m_TestShapes.push_back(pshpcr);
   pshpcr = pcmp;
   m_TestShapes.push_back(pshpcr);
   pshpcr = pcmp2;
   m_TestShapes.push_back(pshpcr);
}

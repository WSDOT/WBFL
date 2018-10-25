///////////////////////////////////////////////////////////////////////
// LBAM Analysis Test - Test driver for LBAM analysis library
// Copyright © 2009  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// TestInfluenceLine.cpp: implementation of the CTestInfluenceLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestInfluenceLine.h"

#include <string>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestInfluenceLine::CTestInfluenceLine()
{

}

CTestInfluenceLine::~CTestInfluenceLine()
{

}

HRESULT CTestInfluenceLine::Test()
{

   HRESULT hr;
   CComPtr<IInfluenceLine> pil;
   TRY_TEST( pil.CoCreateInstance(CLSID_InfluenceLine), S_OK );

   // test empty il
   Float64 d, d2;
   CollectionIndexType l;
   TRY_TEST(pil->get_Count(ilsBoth,&l), S_OK);
   TRY_TEST(l, 0);
   TRY_TEST(pil->get_Count(ilsPositive,&l), S_OK);
   TRY_TEST(l, 0);
   TRY_TEST(pil->get_Count(ilsNegative,&l), S_OK);
   TRY_TEST(l, 0);
   TRY_TEST(pil->ComputeArea(ilsBoth,&d), S_OK);
   TRY_TEST(d, 0);
   TRY_TEST(pil->ComputeArea(ilsPositive,&d), S_OK);
   TRY_TEST(d, 0);
   TRY_TEST(pil->ComputeArea(ilsNegative,&d), S_OK);
   TRY_TEST(d, 0);
   TRY_TEST(pil->Bounds(&d, &d2), S_OK);
   TRY_TEST(d, 0);
   TRY_TEST(d2, 0);
   TRY_TEST(pil->Clear(), S_OK);

   // fill up a line with some test values
   TRY_TEST(pil->Add(   iflSingle, -10.0,   0.0), S_OK);
   TRY_TEST(pil->Add(   iflSingle,   0.0,   0.0), S_OK);
   TRY_TEST(pil->Add(   iflSingle,  10.0,   0.0), S_OK);
   TRY_TEST(pil->Add(   iflSingle,  20.0,  10.0), S_OK);
   TRY_TEST(pil->Add(   iflSingle,  30.0, -15.0), S_OK);
   TRY_TEST(pil->Add(   iflSingle,  40.0,   0.0), S_OK);
   TRY_TEST(pil->Add( iflDualLeft,  50.0,   0.0), S_OK);
   TRY_TEST(pil->Add(iflDualRight,  50.0,  12.0), S_OK);
   TRY_TEST(pil->Add( iflDualLeft,  60.0,  12.0), S_OK);
   TRY_TEST(pil->Add(iflDualRight,  60.0, -10.0), S_OK);
   TRY_TEST(pil->Add( iflDualLeft,  70.0, -10.0), S_OK);
   TRY_TEST(pil->Add(iflDualRight,  70.0,   0.0), S_OK);
   TRY_TEST(pil->Add(   iflSingle,  80.0,   0.0), S_OK);
   TRY_TEST(pil->Add(   iflSingle,  90.0,  20.0), S_OK);

   TRY_TEST(pil->get_Count(ilsBoth,&l), S_OK);
   TRY_TEST(l, 13);
   InfluenceLocationType ltp;
   Float64 loc, val;
   TRY_TEST(pil->Item(0, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc, -10.0);
   TRY_TEST(pil->Item(1, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc,  10.0);
   TRY_TEST(pil->Item(2, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,  10.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc,  20.0);
   TRY_TEST(pil->Item(3, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val, -15.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc,  30.0);
   TRY_TEST(pil->Item(4, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc,  40.0);
   TRY_TEST(pil->Item(5, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflDualLeft);
   TRY_TEST(loc,  50.0);
   TRY_TEST(pil->Item(6, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,  12.0);
   TRY_TEST(ltp,  iflDualRight);
   TRY_TEST(loc,  50.0);
   TRY_TEST(pil->Item(7, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,  12.0);
   TRY_TEST(ltp,  iflDualLeft);
   TRY_TEST(loc,  60.0);
   TRY_TEST(pil->Item(8, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val, -10.0);
   TRY_TEST(ltp,  iflDualRight);
   TRY_TEST(loc,  60.0);
   TRY_TEST(pil->Item(9, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val, -10.0);
   TRY_TEST(ltp,  iflDualLeft);
   TRY_TEST(loc,  70.0);
   TRY_TEST(pil->Item(10, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflDualRight);
   TRY_TEST(loc,  70.0);
   TRY_TEST(pil->Item(11, ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc,  80.0);
   TRY_TEST(pil->Item(12,ilsBoth, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,  20.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc,  90.0);


   TRY_TEST(pil->get_Count(ilsPositive,&l), S_OK);
   TRY_TEST(l, 10);

   TRY_TEST(pil->Item(0, ilsPositive, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc, -10.0);
   TRY_TEST(pil->Item(1, ilsPositive, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc,  10.0);
   TRY_TEST(pil->Item(2, ilsPositive, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,  10.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc,  20.0);
   TRY_TEST(pil->Item(3, ilsPositive, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc,  24.0);
   TRY_TEST(pil->Item(4, ilsPositive, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflDualLeft);
   TRY_TEST(loc,  50.0);
   TRY_TEST(pil->Item(5, ilsPositive, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,  12.0);
   TRY_TEST(ltp,  iflDualRight);
   TRY_TEST(loc,  50.0);
   TRY_TEST(pil->Item(6, ilsPositive, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,  12.0);
   TRY_TEST(ltp,  iflDualLeft);
   TRY_TEST(loc,  60.0);
   TRY_TEST(pil->Item(7, ilsPositive, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflDualRight);
   TRY_TEST(loc,  60.0);
   TRY_TEST(pil->Item(8 , ilsPositive, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,   0.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc,  80.0);
   TRY_TEST(pil->Item(9 ,ilsPositive, &val, &ltp, &loc), S_OK);
   TRY_TEST(val,  20.0);
   TRY_TEST(ltp,  iflSingle);
   TRY_TEST(loc,  90.0);

   VARIANT_BOOL idv;
   Float64 lv, rv;
   TRY_TEST(pil->Evaluate(0.0 ,ilsBoth, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  0.0);
   TRY_TEST(pil->Evaluate(0.0 ,ilsPositive, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  0.0);
   TRY_TEST(pil->Evaluate(0.0 ,ilsNegative, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  0.0);
   TRY_TEST(pil->Evaluate(15.0 ,ilsBoth, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  5.0);
   TRY_TEST(pil->Evaluate(15.0 ,ilsPositive, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  5.0);
   TRY_TEST(pil->Evaluate(15.0 ,ilsNegative, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  0.0);
   TRY_TEST(pil->Evaluate(24.0 ,ilsBoth, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  0.0);
   TRY_TEST(pil->Evaluate(24.0 ,ilsPositive, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  0.0);
   TRY_TEST(pil->Evaluate(24.0 ,ilsNegative, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  0.0);
   TRY_TEST(pil->Evaluate(50.0 ,ilsBoth, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_TRUE);
   TRY_TEST(lv,  0.0);
   TRY_TEST(rv, 12.0);
   TRY_TEST(pil->Evaluate(50.0 ,ilsPositive, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_TRUE);
   TRY_TEST(lv,  0.0);
   TRY_TEST(rv, 12.0);
   TRY_TEST(pil->Evaluate(50.0 ,ilsNegative, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  0.0);
   TRY_TEST(pil->Evaluate(60.0 ,ilsBoth, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_TRUE);
   TRY_TEST(lv, 12.0);
   TRY_TEST(rv,-10.0);
   TRY_TEST(pil->Evaluate(60.0 ,ilsPositive, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_TRUE);
   TRY_TEST(lv, 12.0);
   TRY_TEST(rv,  0.0);
   TRY_TEST(pil->Evaluate(60.0 ,ilsNegative, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_TRUE);
   TRY_TEST(lv,  0.0);
   TRY_TEST(rv,-10.0);
   TRY_TEST(pil->Evaluate(90.0 ,ilsBoth, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  20.0);
   TRY_TEST(pil->Evaluate(90.0 ,ilsPositive, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  20.0);
   TRY_TEST(pil->Evaluate(90.0 ,ilsNegative, &idv, &lv, &rv), S_OK);
   TRY_TEST(idv,  VARIANT_FALSE);
   TRY_TEST(lv,  0.0);


   TRY_TEST(pil->get_Count(ilsNegative,&l), S_OK);
   TRY_TEST(l, 9);
   TRY_TEST(pil->ComputeArea(ilsBoth,&d), S_OK);
   TRY_TEST(d, 70.0);
   TRY_TEST(pil->ComputeArea(ilsPositive,&d), S_OK);
   TRY_TEST(d, 290.0);
   TRY_TEST(pil->ComputeArea(ilsNegative,&d), S_OK);
   TRY_TEST(d, -220.0);
   TRY_TEST(pil->Bounds(&d, &d2), S_OK);
   TRY_TEST(d, -10.0);
   TRY_TEST(d2, 90.0);

   CComPtr<IDblArray> izb, izp, izn;
   TRY_TEST(pil->ComputeNonZeroRegions(ilsBoth, &izb), S_OK);
   TIArrayHelper<Float64, IDblArray, CollectionIndexType> zb(izb);
   TRY_TEST(zb.Size(), 6);
   TRY_TEST(zb[0], 10.0);
   TRY_TEST(zb[1], 40.0);
   TRY_TEST(zb[2], 50.0);
   TRY_TEST(zb[3], 70.0);
   TRY_TEST(zb[4], 80.0);
   TRY_TEST(zb[5], 90.0);
   TRY_TEST(pil->ComputeNonZeroRegions(ilsPositive, &izp), S_OK);
   TIArrayHelper<Float64, IDblArray, CollectionIndexType> zp(izp);
   TRY_TEST(zp.Size(), 6);
   TRY_TEST(zp[0], 10.0);
   TRY_TEST(zp[1], 24.0);
   TRY_TEST(zp[2], 50.0);
   TRY_TEST(zp[3], 60.0);
   TRY_TEST(zp[4], 80.0);
   TRY_TEST(zp[5], 90.0);
   TRY_TEST(pil->ComputeNonZeroRegions(ilsNegative, &izn), S_OK);
   TIArrayHelper<Float64, IDblArray, CollectionIndexType> zn(izn);
   TRY_TEST(zn.Size(), 4);
   TRY_TEST(zn[0], 24.0);
   TRY_TEST(zn[1], 40.0);
   TRY_TEST(zn[2], 60.0);
   TRY_TEST(zn[3], 70.0);

   TRY_TEST(pil->ComputeAreaInRegions(izb,&d), S_OK);
   TRY_TEST(d, 70.0);
   TRY_TEST(pil->ComputeAreaInRegions(izp,&d), S_OK);
   TRY_TEST(d, 290.0);
   TRY_TEST(pil->ComputeAreaInRegions(izn,&d), S_OK);
   TRY_TEST(d, -220.0);

   CComPtr<IDblArray> zall;
   zall.CoCreateInstance(CLSID_DblArray);
   zall->Add(-10.0);
   zall->Add(90.0);
   TRY_TEST(pil->ComputeAreaInRegions(zall,&d), S_OK);
   TRY_TEST(d,   70.0);

   zall->put_Item(0,-20.0);
   zall->put_Item(1,100.0);
   TRY_TEST(pil->ComputeAreaInRegions(zall,&d), LBAMA_E_INVALID_REGION);
   zall->put_Item(0, 0.0);
   TRY_TEST(pil->ComputeAreaInRegions(zall,&d), LBAMA_E_INVALID_REGION);

   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestInfluenceLine"), 1.0);

      // get interface pointer to Save
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pil.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<IInfluenceLine> pInfluenceLine2;
      TRY_TEST(pInfluenceLine2.CoCreateInstance( CLSID_InfluenceLine ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestInfluenceLine"));

         IStructuredStorage2* piss2=NULL;
         TRY_TEST( pInfluenceLine2.QueryInterface(&piss2), S_OK);

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
         hr = pss2->BeginUnit(CComBSTR("TestInfluenceLine"), 1.0);
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

   // create a clone and save it
   CComPtr<IInfluenceLine> pclone;
   TRY_TEST(pil->Clone(&pclone), S_OK);

   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestInfluenceLine"), 1.0);

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


   // test Clear
   TRY_TEST(pil->Clear(), S_OK);
   TRY_TEST(pil->get_Count(ilsBoth,&l), S_OK);
   TRY_TEST(l, 0);
   TRY_TEST(pil->get_Count(ilsPositive,&l), S_OK);
   TRY_TEST(l, 0);
   TRY_TEST(pil->get_Count(ilsNegative,&l), S_OK);
   TRY_TEST(l, 0);
   TRY_TEST(pil->ComputeArea(ilsBoth,&d), S_OK);
   TRY_TEST(d, 0);
   TRY_TEST(pil->ComputeArea(ilsPositive,&d), S_OK);
   TRY_TEST(d, 0);
   TRY_TEST(pil->ComputeArea(ilsNegative,&d), S_OK);
   TRY_TEST(d, 0);
   TRY_TEST(pil->Bounds(&d, &d2), S_OK);
   TRY_TEST(d, 0);
   TRY_TEST(d2, 0);


   return S_OK;
}

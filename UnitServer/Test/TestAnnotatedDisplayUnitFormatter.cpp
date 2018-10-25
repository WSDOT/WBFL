///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2013  Washington State Department of Transportation
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

// TestAnnotatedDisplayUnitFormatter.cpp: implementation of the CTestAnnotatedDisplayUnitFormatter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAnnotatedDisplayUnitFormatter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestAnnotatedDisplayUnitFormatter::CTestAnnotatedDisplayUnitFormatter()
{

}

CTestAnnotatedDisplayUnitFormatter::~CTestAnnotatedDisplayUnitFormatter()
{

}

void CTestAnnotatedDisplayUnitFormatter::Test()
{
   CComPtr<IAnnotatedDisplayUnitFormatter> pADUF;
   TRY_TEST( pADUF.CoCreateInstance( CLSID_AnnotatedDisplayUnitFormatter ), S_OK );

   // Feet and inches
   Uint32 lVal;
   Float64 dVal;
   CComBSTR bstrTest;
   NumericFormatType notation;
   TextJustificationType justify;

   //TRY_TEST(pADUF->put_OffsetDigits(-1),E_INVALIDARG);
   TRY_TEST(pADUF->put_OffsetDigits(0),S_OK);
   TRY_TEST(pADUF->put_Multiplier(12.0),S_OK);
   //TRY_TEST(pADUF->FormatSpecifiers(-1,1,tjRight,nftFixed,0.0001),E_INVALIDARG);
   //TRY_TEST(pADUF->FormatSpecifiers(1,-1,tjRight,nftFixed,0.0001),E_INVALIDARG);
   TRY_TEST(pADUF->FormatSpecifiers(6,3,tjRight,nftFixed,0.0001),S_OK);
   TRY_TEST(pADUF->put_Annotation(NULL),E_INVALIDARG);
   TRY_TEST(pADUF->put_Annotation(CComBSTR("ft-,in")),S_OK);

   TRY_TEST(pADUF->get_OffsetDigits(NULL),E_POINTER);
   TRY_TEST(pADUF->get_OffsetDigits(&lVal),S_OK);
   TRY_TEST(lVal,0);

   TRY_TEST(pADUF->get_Width(NULL),E_POINTER);
   TRY_TEST(pADUF->get_Width(&lVal),S_OK);
   TRY_TEST(lVal,6);

   TRY_TEST(pADUF->get_Precision(NULL),E_POINTER);
   TRY_TEST(pADUF->get_Precision(&lVal),S_OK);
   TRY_TEST(lVal,3);

   TRY_TEST(pADUF->get_Notation(NULL),E_POINTER);
   TRY_TEST(pADUF->get_Notation(&notation),S_OK);
   TRY_TEST(notation,nftFixed);

   TRY_TEST(pADUF->get_Justification(NULL),E_POINTER);
   TRY_TEST(pADUF->get_Justification(&justify),S_OK);
   TRY_TEST(justify,tjRight);

   TRY_TEST(pADUF->get_Multiplier(NULL),E_POINTER);
   TRY_TEST(pADUF->get_Multiplier(&dVal),S_OK);
   TRY_TEST( IsEqual(dVal,12.0), true );

   TRY_TEST(pADUF->get_Annotation(NULL),E_POINTER);
   TRY_TEST(pADUF->get_Annotation(&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("ft-,in")),0);

   TRY_TEST(pADUF->Format(1.5,CComBSTR("ft"),NULL),E_POINTER);
   bstrTest.Empty();
   TRY_TEST(pADUF->Format(1.5,CComBSTR("ft"),&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1ft-6.000in")),0);

   bstrTest.Empty();
   TRY_TEST(pADUF->Format(-1.5,CComBSTR("ft"),&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("-1ft-6.000in")),0);

   bstrTest.Empty();
   TRY_TEST(pADUF->Format(54.9999999,CComBSTR("ft"),&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("55ft-0.000in")),0);

   bstrTest.Empty();
   TRY_TEST(pADUF->Format(1.91666666666666666666667,CComBSTR("ft"),&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1ft-11.000in")),0);
   
   bstrTest.Empty();
   TRY_TEST(pADUF->Format(1.5,NULL,&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1 6.000")),0);

   bstrTest.Empty();
   TRY_TEST(pADUF->Format(1.9166666666666666667,NULL,&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1 11.000")),0);

   TRY_TEST(pADUF->put_Annotation(CComBSTR("' ,\"")),S_OK);
   TRY_TEST(pADUF->FormatSpecifiers(0,0,tjRight,nftFixed,0.0001),S_OK);

   bstrTest.Empty();
   TRY_TEST(pADUF->Format(1.25,CComBSTR("ft"),&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1' 3\"")),0);

   bstrTest.Empty();
   TRY_TEST(pADUF->Format(1.25,NULL,&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1 3")),0);

   bstrTest.Empty();
   TRY_TEST(pADUF->Format(1.9166666666666666667,CComBSTR("ft"),&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1' 11\"")),0);

   bstrTest.Empty();
   TRY_TEST(pADUF->Format(1.9166666666666666667,NULL,&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1 11")),0);

   bstrTest.Empty();
   TRY_TEST(pADUF->Format(1.9999999999999999999,NULL,&bstrTest),S_OK);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("2 0")),0);

   // US Stationing
   pADUF->put_OffsetDigits(2);
   pADUF->put_Multiplier(1.0);
   pADUF->put_Annotation(CComBSTR("+"));
   pADUF->FormatSpecifiers(4,2,tjRight,nftFixed,0.0001);

   bstrTest.Empty();
   pADUF->Format(123.456,CComBSTR("ft"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("1+23.46")),0);

   bstrTest.Empty();
   pADUF->Format(69500.00,CComBSTR("ft"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("695+00.00")),0);

   bstrTest.Empty();
   pADUF->Format(-999.99,CComBSTR("ft"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("-9+99.99")),0);

   bstrTest.Empty();
   pADUF->Format(14800.019,CComBSTR("ft"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("148+00.02")),0);

   bstrTest.Empty();
   pADUF->Format(14800.0019,CComBSTR("ft"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("148+00.00")),0);

   // SI Stationing
   pADUF->put_OffsetDigits(3);
   pADUF->put_Multiplier(1.0);
   pADUF->put_Annotation(CComBSTR("+"));
   pADUF->FormatSpecifiers(6,3,tjRight,nftFixed,0.0001);

   bstrTest.Empty();
   pADUF->Format(123.456,CComBSTR("m"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("0+123.456")),0);

   // Test SI Stationing with different format specifiers
   // Annotated Display Unit Formatter ignores numeric format type, but
   // handles width, precision, and justification

   // Width > required & right justified
   pADUF->FormatSpecifiers(14,3,tjRight,nftFixed,0.0001);
   bstrTest.Empty();
   pADUF->Format(123.456,CComBSTR("m"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("     0+123.456")),0);

   // Width > required & left justified
   pADUF->FormatSpecifiers(14,3,tjLeft,nftFixed,0.0001);
   bstrTest.Empty();
   pADUF->Format(123.456,CComBSTR("m"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("0+123.456     ")),0);

   // Width > required & right justified
   pADUF->FormatSpecifiers(14,3,tjRight,nftAutomatic,0.0001);
   bstrTest.Empty();
   pADUF->Format(123.456,CComBSTR("m"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("     0+123.456")),0);

   // Width > required & left justified
   pADUF->FormatSpecifiers(14,3,tjLeft,nftAutomatic,0.0001);
   bstrTest.Empty();
   pADUF->Format(123.456,CComBSTR("m"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("0+123.456     ")),0);

   // Width > required & right justified
   pADUF->FormatSpecifiers(14,3,tjRight,nftScientific,0.0001);
   bstrTest.Empty();
   pADUF->Format(123.456,CComBSTR("m"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("     0+123.456")),0);

   // Width > required & left justified
   pADUF->FormatSpecifiers(14,3,tjLeft,nftScientific,0.0001);
   bstrTest.Empty();
   pADUF->Format(123.456,CComBSTR("m"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("0+123.456     ")),0);

   // Width > required & right justified
   pADUF->FormatSpecifiers(14,3,tjRight,nftEngineering,0.0001);
   bstrTest.Empty();
   pADUF->Format(123.456,CComBSTR("m"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("     0+123.456")),0);

   // Width > required & left justified
   pADUF->FormatSpecifiers(14,3,tjLeft,nftEngineering,0.0001);
   bstrTest.Empty();
   pADUF->Format(123.456,CComBSTR("m"),&bstrTest);
   TRY_TEST(wcscmp(bstrTest,CComBSTR("0+123.456     ")),0);

   // Odd annotations
   pADUF->put_OffsetDigits(0);
   pADUF->put_Multiplier(12.0);
   pADUF->put_Annotation(CComBSTR(",Junk"));
   pADUF->FormatSpecifiers(0,3,tjRight,nftFixed,0.0001);
   bstrTest.Empty();
   pADUF->Format(1.5,CComBSTR("ft"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("16.000Junk")),0);

   pADUF->FormatSpecifiers(0,3,tjRight,nftFixed,0.0001);
   pADUF->put_Annotation(CComBSTR(" ,Junk"));
   bstrTest.Empty();
   pADUF->Format(1.5,CComBSTR("ft"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1 6.000Junk")),0);

   // UsesTag
   VARIANT_BOOL bUsesTag;
   TRY_TEST(pADUF->get_UsesTag(NULL),E_POINTER);
   TRY_TEST(pADUF->get_UsesTag(&bUsesTag),S_OK);
   TRY_TEST(bUsesTag,VARIANT_FALSE);

   // Verify that an AnnotatedDisplayUnitFormatter can go 
   // anywhere a DisplayUnitFormatter can go.
   // The following code will compile if pADUF can go where a IDisplayUnitFormatter
   // pointer is specified.
   CComPtr<IUnitSystem> pUnitSystem;
   pUnitSystem.CoCreateInstance( CLSID_UnitSystem );

   CComPtr<IDisplayUnitMgr> pDispUnitMgr;
   pUnitSystem->get_DisplayUnitMgr(&pDispUnitMgr);

   CComPtr<IDisplayUnitGroup> pGroup;
   pDispUnitMgr->Add(CComBSTR("Length"),CComBSTR("Length"),&pGroup);

   CComPtr<IDisplayUnit> pDispUnit;
   pGroup->Add(CComBSTR("ft"),unitsUS,pADUF,VARIANT_TRUE,&pDispUnit);

   // ****************************************************
   // * Test ISupportErrorInfo
   // ****************************************************
   CComQIPtr<ISupportErrorInfo>  pSEI(pADUF);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IAnnotatedDisplayUnitFormatter ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IDisplayUnitFormatter ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}

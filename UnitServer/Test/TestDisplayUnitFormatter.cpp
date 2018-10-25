///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// TestDisplayUnitFormatter.cpp: implementation of the CTestDisplayUnitFormatter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDisplayUnitFormatter.h"
#include <limits>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestDisplayUnitFormatter::CTestDisplayUnitFormatter()
{

}

CTestDisplayUnitFormatter::~CTestDisplayUnitFormatter()
{

}

void CTestDisplayUnitFormatter::Test()
{
   CComPtr<IDisplayUnitFormatter> pFormatter;
   TRY_TEST( pFormatter.CoCreateInstance( CLSID_DisplayUnitFormatter ), S_OK );

   Uint32 width,precision;
   NumericFormatType notation;
   TextJustificationType justify;
   TRY_TEST(pFormatter->get_Width(NULL), E_POINTER);
   TRY_TEST(pFormatter->get_Width(&width), S_OK );
   TRY_TEST( width, 0 );

   TRY_TEST(pFormatter->get_Precision(NULL), E_POINTER);
   TRY_TEST(pFormatter->get_Precision(&precision), S_OK );
   TRY_TEST(precision, 6 );

   TRY_TEST(pFormatter->get_Justification(NULL), E_POINTER );
   TRY_TEST(pFormatter->get_Justification(&justify),S_OK);
   TRY_TEST(justify,tjRight);

   TRY_TEST(pFormatter->get_Notation(NULL), E_POINTER);
   TRY_TEST(pFormatter->get_Notation(&notation), S_OK );
   TRY_TEST(notation,nftAutomatic );

   // Negative values aren't permitted
   //TRY_TEST(pFormatter->FormatSpecifiers(-10,2,tjLeft,nftFixed,0.0001), E_INVALIDARG );
   //TRY_TEST(pFormatter->FormatSpecifiers(2,-10,tjLeft,nftFixed,0.0001), E_INVALIDARG );
   TRY_TEST(pFormatter->FormatSpecifiers(8,5,tjLeft,nftFixed,0.0001), S_OK);

   TRY_TEST(pFormatter->get_Width(&width), S_OK );
   TRY_TEST( width, 8 );
   TRY_TEST(pFormatter->get_Precision(&precision), S_OK );
   TRY_TEST(precision, 5 );
   TRY_TEST(pFormatter->get_Justification(&justify),S_OK);
   TRY_TEST(justify,tjLeft);
   TRY_TEST(pFormatter->get_Notation(&notation), S_OK );
   TRY_TEST(notation,nftFixed );


   CComBSTR bstrTest;

   // Fixed format
   pFormatter->FormatSpecifiers(8,5,tjRight,nftFixed,0.0001);
   TRY_TEST(pFormatter->Format(12.345,NULL,NULL),E_POINTER);
   TRY_TEST(pFormatter->Format(12.345,NULL,&bstrTest),S_OK);
   TRY_TEST( wcscmp( bstrTest, CComBSTR("12.34500")), 0);
   TRY_TEST(pFormatter->Format(12.345,CComBSTR(),&bstrTest),S_OK);
   TRY_TEST( wcscmp( bstrTest, CComBSTR("12.34500")), 0);
   TRY_TEST(pFormatter->Format(12.345,CComBSTR(""),&bstrTest),S_OK);
   TRY_TEST( wcscmp( bstrTest, CComBSTR("12.34500 ")), 0);
   TRY_TEST(pFormatter->Format(12.345,CComBSTR("Junk"),&bstrTest),S_OK);
   TRY_TEST( wcscmp( bstrTest, CComBSTR("12.34500 Junk")), 0);

   // Right justified & width > required
   pFormatter->FormatSpecifiers(8,5,tjRight,nftFixed,0.0001);
   pFormatter->Format(1.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR(" 1.10000 Tag")),0);

   // Left justified & width > required
   pFormatter->FormatSpecifiers(8,5,tjLeft,nftFixed,0.0001);
   pFormatter->Format(1.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1.10000  Tag")),0);

   // Right justified & width < required
   pFormatter->FormatSpecifiers(1,5,tjRight,nftFixed,0.0001);
   pFormatter->Format(10.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1.01000e+001 Tag")),0);

   // Left justified & width < required
   pFormatter->FormatSpecifiers(1,5,tjLeft,nftFixed,0.0001);
   pFormatter->Format(10.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1.01000e+001 Tag")),0);

   //Automatic

   // Right justified & width > required
   pFormatter->FormatSpecifiers(8,5,tjRight,nftAutomatic,0.0001);
   pFormatter->Format(1.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("     1.1 Tag")),0);

   // Left justified & width > required
   pFormatter->FormatSpecifiers(8,5,tjLeft,nftAutomatic,0.0001);
   pFormatter->Format(1.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1.1      Tag")),0);

   // Right justified & width < required
   pFormatter->FormatSpecifiers(1,5,tjRight,nftAutomatic,0.0001);
   pFormatter->Format(10.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1.01000e+001 Tag")),0);

   // Left justified & width < required
   pFormatter->FormatSpecifiers(1,5,tjLeft,nftAutomatic,0.0001);
   pFormatter->Format(10.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1.01000e+001 Tag")),0);

   //Scientific notation

   // Right justified & width > required
   pFormatter->FormatSpecifiers(14,5,tjRight,nftScientific,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("  1.00001e+004 Tag")),0);

   // Left justified & width > required
   pFormatter->FormatSpecifiers(14,5,tjLeft,nftScientific,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1.00001e+004   Tag")),0);

   // Right justified & width < required
   pFormatter->FormatSpecifiers(1,5,tjRight,nftScientific,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1.00001e+004 Tag")),0);

   // Left justified & width < required
   pFormatter->FormatSpecifiers(1,5,tjLeft,nftScientific,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1.00001e+004 Tag")),0);

   // Right justified & width < required & precision < required
   pFormatter->FormatSpecifiers(1,4,tjRight,nftScientific,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1.0000e+004 Tag")),0);

   // Left justified & width < required & precision < required
   pFormatter->FormatSpecifiers(1,4,tjLeft,nftScientific,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("1.0000e+004 Tag")),0);

   //Engineering notation
   // Right justified & width > required
   pFormatter->FormatSpecifiers(14,4,tjRight,nftEngineering,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("  10.0001e+003 Tag")),0);

   // Left justified & width > required
   pFormatter->FormatSpecifiers(14,4,tjLeft,nftEngineering,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("10.0001e+003   Tag")),0);

   // Right justified & width < required
   pFormatter->FormatSpecifiers(1,4,tjRight,nftEngineering,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("10.0001e+003 Tag")),0);

   // Left justified & width < required
   pFormatter->FormatSpecifiers(1,4,tjLeft,nftEngineering,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("10.0001e+003 Tag")),0);

   // Right justified & width < required & precision < required
   pFormatter->FormatSpecifiers(1,3,tjRight,nftEngineering,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("10.000e+003 Tag")),0);

   // Left justified & width < required & precision < required
   pFormatter->FormatSpecifiers(1,3,tjLeft,nftEngineering,0.0001);
   pFormatter->Format(10000.1,CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("10.000e+003 Tag")),0);

   // Infinity
#undef max
   pFormatter->FormatSpecifiers(1,4,tjRight,nftFixed,0.0001);
   pFormatter->Format(std::numeric_limits<Float64>::max(),CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("INF Tag")),0);
   pFormatter->Format(-1*std::numeric_limits<Float64>::max(),CComBSTR("Tag"),&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("-INF Tag")),0);

   pFormatter->FormatSpecifiers(1,4,tjRight,nftFixed,0.0001);
   pFormatter->Format(std::numeric_limits<Float64>::max(),NULL,&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("INF")),0);
   pFormatter->Format(-1*std::numeric_limits<Float64>::max(),NULL,&bstrTest);
   TRY_TEST( wcscmp(bstrTest,CComBSTR("-INF")),0);

   // UsesTag
   VARIANT_BOOL bUsesTag;
   TRY_TEST(pFormatter->get_UsesTag(NULL),E_POINTER);
   TRY_TEST(pFormatter->get_UsesTag(&bUsesTag),S_OK);
   TRY_TEST(bUsesTag,VARIANT_TRUE);

   // ****************************************************
   // * Test ISupportErrorInfo
   // ****************************************************
   CComQIPtr<ISupportErrorInfo>  pSEI(pFormatter);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IDisplayUnitFormatter ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}

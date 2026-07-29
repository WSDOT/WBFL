///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestDirectionDisplayUnitFormatter.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestDirectionDisplayUnitFormatter.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h).
#include "pch.h"

namespace CogoUnitTests
{

TEST_CLASS(TestDirectionDisplayUnitFormatter)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<IDirectionDisplayUnitFormatter> fmtr;
         ASSERT_EQ(fmtr.CoCreateInstance(CLSID_DirectionDisplayUnitFormatter),S_OK);

         // Test ISupportErrorInfo
         CComQIPtr<ISupportErrorInfo> eInfo(fmtr);
         ASSERT_EQ( eInfo != nullptr, true );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IDirectionDisplayUnitFormatter ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IDisplayUnitFormatter ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

         // Test back numeric formatting using default annotations
         CComBSTR bstrTest;
         ASSERT_EQ(fmtr->Format(0.0,nullptr,nullptr),E_POINTER);
         ASSERT_EQ(fmtr->Format(0.0,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("N 90° 00\' 00.00\" E")), 0);

         ASSERT_EQ(fmtr->Format(PI_OVER_2,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("N 0° 00\' 00.00\" E")), 0);

         ASSERT_EQ(fmtr->Format(-M_PI/4,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("S 45° 00\' 00.00\" E")), 0);

         ASSERT_EQ(fmtr->Format(-M_PI/4,nullptr,&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("S 45 00 00.00 E")), 0);

         ASSERT_EQ(fmtr->Format(-3*M_PI/4,nullptr,&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("S 45 00 00.00 W")), 0);

         // test condensed format
         VARIANT_BOOL bValue;
         ASSERT_EQ( fmtr->get_CondensedFormat(nullptr),E_POINTER);
         ASSERT_EQ( fmtr->get_CondensedFormat(&bValue),S_OK);
         ASSERT_EQ( bValue, VARIANT_FALSE );
         ASSERT_EQ(fmtr->put_CondensedFormat(VARIANT_TRUE),S_OK);
         ASSERT_EQ(fmtr->Format(-M_PI/4,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("S 45° E")), 0);

         ASSERT_EQ(fmtr->Format(M_PI/4 + (1.0/60.0)*M_PI/180.0 ,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("N 44° 59\' 00.00\" E")), 0);

         ASSERT_EQ(fmtr->Format(4*M_PI + (1.0/60.0)*M_PI/180.0 ,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("N 89° 59\' 00.00\" E")), 0);

         ASSERT_EQ( fmtr->get_UsesTag(nullptr), E_POINTER );
         ASSERT_EQ( fmtr->get_UsesTag(&bValue), S_OK );
         ASSERT_EQ( bValue, VARIANT_TRUE );

         ASSERT_EQ( fmtr->get_BearingFormat(nullptr), E_POINTER );
         ASSERT_EQ( fmtr->get_BearingFormat(&bValue), S_OK );
         ASSERT_EQ( bValue, VARIANT_TRUE );

         // use custom annotations
         fmtr->put_CondensedFormat(VARIANT_FALSE);

         ASSERT_EQ(fmtr->Format(M_PI/4,CComBSTR("xxx"),&bstrTest),E_INVALIDARG);

         ASSERT_EQ(fmtr->Format(M_PI/4,CComBSTR("d,m,s"),&bstrTest),S_OK);
         ASSERT_EQ( wcscmp(bstrTest,CComBSTR("N 45d 00m 00.00s E")), 0);

         ASSERT_EQ(fmtr->Format(M_PI/4,CComBSTR("deg,min,sec"),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("N 45deg 00min 00.00sec E")), 0);

         // Format Specifiers
         //ASSERT_EQ( fmtr->FormatSpecifiers(-1,3,tjRight,nftScientific,1.0), E_INVALIDARG );
         //ASSERT_EQ( fmtr->FormatSpecifiers(8,-1,tjRight,nftScientific,1.0), E_INVALIDARG );
         ASSERT_EQ( fmtr->FormatSpecifiers(8,3,tjRight,nftScientific,-1.0), E_INVALIDARG );
         ASSERT_EQ( fmtr->FormatSpecifiers(8,3,tjRight,nftScientific,1.0), S_OK );

         Uint32 lValue;
         ASSERT_EQ( fmtr->get_Width(nullptr), E_POINTER );
         ASSERT_EQ( fmtr->get_Width(&lValue), S_OK );
         ASSERT_EQ( lValue, 8 );

         ASSERT_EQ( fmtr->get_Precision(nullptr), E_POINTER );
         ASSERT_EQ( fmtr->get_Precision(&lValue), S_OK );
         ASSERT_EQ( lValue, 3 );

         TextJustificationType tj;
         ASSERT_EQ( fmtr->get_Justification(nullptr), E_POINTER );
         ASSERT_EQ( fmtr->get_Justification(&tj), S_OK );
         ASSERT_EQ( tj, tjRight );

         NumericFormatType nft;
         ASSERT_EQ( fmtr->get_Notation(nullptr), E_POINTER );
         ASSERT_EQ( fmtr->get_Notation(&nft), S_OK );
         ASSERT_EQ( nft, nftScientific );

         Float64 dblValue;
         ASSERT_EQ( fmtr->get_ZeroTolerance(nullptr), E_POINTER );
         ASSERT_EQ( fmtr->get_ZeroTolerance(&dblValue), S_OK );
         ASSERT_EQ( IsEqual(dblValue, 1.0), true );

         ASSERT_EQ(fmtr->Format(3*M_PI/4 + (1.0/60.0)*M_PI/180.0 + (1.1/3600.0)*M_PI/180.0 ,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("N 45° 01\' 0001.100\" W")), 0);

         ASSERT_EQ(fmtr->Format(0.1,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("N 90° 00\' 0000.000\" E")), 0);

         // Azimuth format
         fmtr.Release();
         fmtr.CoCreateInstance(CLSID_DirectionDisplayUnitFormatter);
         fmtr->put_BearingFormat(VARIANT_FALSE);
         fmtr->put_CondensedFormat(VARIANT_FALSE);

         ASSERT_EQ(fmtr->Format(M_PI/4,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("45° 00\' 00.00\"")), 0);

         ASSERT_EQ(fmtr->Format(-M_PI/4,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("135° 00\' 00.00\"")), 0);

         ASSERT_EQ(fmtr->Format(3*M_PI/4,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("315° 00\' 00.00\"")), 0);

         ASSERT_EQ(fmtr->Format(5*M_PI/4,CComBSTR("d,m,s"),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("225d 00m 00.00s")), 0);

         fmtr->put_CondensedFormat(VARIANT_TRUE);

         ASSERT_EQ(fmtr->Format(3*M_PI/4,CComBSTR("°,\',\""),&bstrTest),S_OK);
         ASSERT_EQ( _tcscmp(bstrTest,CComBSTR("315°")), 0);

         // Test IObjectSafety
         ASSERT_EQ( TestIObjectSafety(CLSID_DirectionDisplayUnitFormatter,IID_IDirectionDisplayUnitFormatter,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
         ASSERT_EQ( TestIObjectSafety(CLSID_DirectionDisplayUnitFormatter,IID_IDisplayUnitFormatter,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   }
};
} // namespace CogoUnitTests

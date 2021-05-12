///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// GenericBridgeTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <initguid.h>
#include <WBFLTools_i.c>
#include <WBFLGeometry_i.c>
#include <WBFLCogo_i.c>
#include <WBFLGenericBridge_i.c>
#include <WBFLBridgeGeometry_i.c>

#include "TestSegment.h"
#include "TestSuperstructureMember.h"
#include "TestSuperstructureMemberCollection.h"
#include "TestLongitudinalPierDescription.h"
#include "TestPier.h"
#include "TestPierCollection.h"
#include "TestGenericBridge.h"
#include "TestColumn.h"
#include "TestCrossBeam.h"
#include "TestColumnSpacing.h"
#include "TestTransversePierDescription.h"
#include "TestPersistance.h"
#include "TestMaterial.h"
#include "TestCastSlab.h"
#include "TestPrecastSlab.h"
#include "TestOverlaySlab.h"
#include "TestAlignmentOffsetStrategy.h"
#include "TestBoxBeamSection.h"
#include "TestDeckedSlabBeamSection.h"
#include "TestMultiWebSection.h"
#include "TestMultiWebSection2.h"
#include "TestUGirderSection.h"
#include "TestUGirderSection2.h"
#include "TestVoidedSlabSection.h"
#include "TestVoidedSlabSection2.h"
#include "TestFlangedGirderSection.h"
#include "TestFlangedGirderSection2.h"
#include "TestNUGirderSection.h"
#include "TestBulbTeeGirderSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

int main(int argc, TCHAR* argv[])
{
   //_crtBreakAlloc = 526; // causes program to break at a specific memory allocation

   ::CoInitialize(nullptr);

   try
   {
      CTestBoxBeamSection::Test();
      CTestDeckedSlabBeamSection::Test();
      CTestMultiWebSection::Test();
      CTestMultiWebSection2::Test();
      CTestUGirderSection::Test();
      CTestUGirderSection2::Test();
      CTestVoidedSlabSection::Test();
      CTestVoidedSlabSection2::Test();
      CTestFlangedGirderSection::Test();
      CTestFlangedGirderSection2::Test();
      CTestNUGirderSection::Test();
      CTestBulbTeeGirderSection::Test();

      CTestGenericBridge::Test();
      CTestAlignmentOffsetStrategy::Test();
      CTestCastSlab::Test();
      CTestPrecastSlab::Test();
      CTestOverlaySlab::Test();
      CTestMaterial::Test();
      CTestSegment::Test();
      CTestSuperstructureMember::Test();
      CTestSuperstructureMemberCollection::Test();
      CTestLongitudinalPierDescription::Test();
      CTestPier::Test();
      CTestPierCollection::Test();
      CTestColumn::Test();
      CTestCrossBeam::Test();
      CTestColumnSpacing::Test();
      CTestTransversePierDescription::Test();
      CTestPersistance::Test();
   }
   catch (...)
   {
      TRY_TEST(true, false);
   }

   ::CoUninitialize();

	return 0;
}

bool TestIObjectSafety(IUnknown* punk,REFIID riid,DWORD dwSupportedOptions)
{
   CComQIPtr<IObjectSafety> safety(punk);

   if ( safety == nullptr )
      return false;


   DWORD dwSupported, dwEnabled;
   safety->GetInterfaceSafetyOptions(riid,&dwSupported,&dwEnabled);
   return dwSupported == dwSupportedOptions;
}

void TestWebSections(IPrestressedGirderSection* pSection, const std::vector<std::pair<Float64, Float64>>& vExpectedValues)
{
   TRY_TEST(pSection != nullptr, true);

   CComPtr<IDblArray> vY;
   CComPtr<IDblArray> vW;
   CComPtr<IBstrArray> vDesc;
   TRY_TEST(pSection->GetWebSections(&vY, &vW, &vDesc), S_OK);

   IndexType nItems;
   TRY_TEST(vY->get_Count(&nItems), S_OK);
   TRY_TEST(nItems, vExpectedValues.size());

   IndexType i = 0;
   for (const auto& expected_value : vExpectedValues)
   {
      Float64 Yg, bw;
      vY->get_Item(i, &Yg);
      vW->get_Item(i, &bw);
      TRY_TEST(IsEqual(Yg, std::get<0>(expected_value)), true);
      TRY_TEST(IsEqual(bw, std::get<1>(expected_value)), true);
      i++;
   }
}

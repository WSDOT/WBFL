///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
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

// GenericBridgeTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <initguid.h>
#include <WBFLTools_i.c>
#include <WBFLGeometry_i.c>
#include <WBFLCogo_i.c>
#include <WBFLGenericBridge_i.c>

#include "TestSegment.h"
#include "TestSuperstructureMember.h"
#include "TestSuperstructureMemberCollection.h"
#include "TestLongitudinalPierDescription.h"
#include "TestPier.h"
#include "TestPierCollection.h"
#include "TestTemporaryPierItem.h"
#include "TestTemporaryPierItemCollection.h"
#include "TestSpan.h"
#include "TestSpanCollection.h"
#include "TestStage.h"
#include "TestStageCollection.h"
#include "TestCogoInfo.h"
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

int main(int argc, TCHAR* argv[])
{
   ::CoInitialize(NULL);

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
   CTestTemporaryPierItem::Test();
   CTestTemporaryPierItemCollection::Test();
   CTestSpan::Test();
   CTestSpanCollection::Test();
   CTestStage::Test();
   CTestStageCollection::Test();
   CTestCogoInfo::Test();
   CTestColumn::Test();
   CTestCrossBeam::Test();
   CTestColumnSpacing::Test();
   CTestTransversePierDescription::Test();
   CTestGenericBridge::Test();
   CTestPersistance::Test();

   ::CoUninitialize();

	return 0;
}

bool TestIObjectSafety(IUnknown* punk,REFIID riid,DWORD dwSupportedOptions)
{
   CComQIPtr<IObjectSafety> safety(punk);

   if ( safety == NULL )
      return false;


   DWORD dwSupported, dwEnabled;
   safety->GetInterfaceSafetyOptions(riid,&dwSupported,&dwEnabled);
   return dwSupported == dwSupportedOptions;
}
///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// CogoTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <initguid.h>
#include <WBFLGeometry_i.c>
#include <WBFLCogo_i.c>
#include <WBFLTools_i.c>
#include <WBFLUnitServer_i.c>

#include "TestAngle.h"
#include "TestDirection.h"
#include "TestPoint.h"
#include "TestPointCollection.h"
#include "TestLineSegmentCollection.h"
#include "TestProfilePoint.h"
#include "TestProfilePointCollection.h"
#include "TestCogoModel.h"
#include "TestLocate.h"
#include "TestIntersect.h"
#include "TestMeasure.h"
#include "TestProject.h"
#include "TestDivide.h"
#include "TestTangent.h"
#include "TestCogoModelEvents.h"
#include "TestVertCurve.h"
#include "TestVertCurveCollection.h"
#include "TestHorzCurve.h"
#include "TestHorzCurveCollection.h"
#include "TestCrossSection.h"
#include "TestCrossSectionCollection.h"
#include "TestProfileElement.h"
#include "TestProfile.h"
#include "TestPathElement.h"
#include "TestPathCollection.h"
#include "TestAlignment.h"
#include "TestAngleDisplayUnitFormatter.h"
#include "TestDirectionDisplayUnitFormatter.h"
#include "TestStation.h"
#include "TestCubicSpline.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

int main(int argc, TCHAR* argv[])
{
   ::CoInitialize(NULL);

   CTestAngle::Test();
   CTestDirection::Test();
   CTestPoint::Test();
   CTestPointCollection::Test();
   CTestLineSegmentCollection::Test();
   CTestProfilePoint::Test();
   CTestProfilePointCollection::Test();
   CTestVertCurve::Test();
   CTestVertCurveCollection::Test();
   CTestHorzCurve::Test();
   CTestHorzCurveCollection::Test();
   CTestCubicSpline::Test();

   CTestCrossSection::Test();
   CTestCrossSectionCollection::Test();
   CTestProfileElement::Test();
   CTestProfile::Test();
   CTestPathElement::Test();
   CTestPathCollection::Test();
   CTestAlignment::Test();

   CTestAngleDisplayUnitFormatter::Test();
   CTestDirectionDisplayUnitFormatter::Test();

   CTestStation::Test();

   CTestCogoModel::Test();
   CTestCogoModelEvents::Test();
   CTestMeasure::Test();
   CTestLocate::Test();
   CTestIntersect::Test();
   CTestProject::Test();
   CTestDivide::Test();
   CTestTangent::Test();

   ::CoUninitialize();

	return 1;
}

HRESULT CheckPointType(IPoint2d* point)
{
   CComPtr<IConnectionPointContainer> pCPC;
   point->QueryInterface(&pCPC);

   if ( pCPC == NULL )
      return E_FAIL;

   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint(IID_IPoint2dEvents,&pCP);
   
   if ( pCP == NULL )
      return E_FAIL;

   return S_OK;
}

bool TestIObjectSafety(REFCLSID rclsid,REFIID riid,DWORD dwSupportedOptions)
{
   CComPtr<IObjectSafety> safety;
   safety.CoCreateInstance(rclsid);

   if ( safety == NULL )
      return false;


   DWORD dwSupported, dwEnabled;
   safety->GetInterfaceSafetyOptions(riid,&dwSupported,&dwEnabled);
   return dwSupported == dwSupportedOptions;
}
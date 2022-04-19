///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <initguid.h>
#include <WBFLTools_i.c>
#include <WBFLGeometry_i.c>

#include "TestSize2d.h"
#include "TestPoint2d.h"
#include "TestRect2d.h"
#include "TestPoint2dCollection.h"
#include "TestVector2d.h"
#include "TestLineSegment2d.h"
#include "TestLine2d.h"

#include "TestSize3d.h"
#include "TestVector3d.h"
#include "TestPoint3d.h"
#include "TestPoint3dCollection.h"
#include "TestPlane3d.h"
#include "TestLineSegment3d.h"

#include "TestCoordinateXform2d.h"
#include "TestCoordinateXform3d.h"
#include "TestGeomUtil.h"

#include "TestShapeProperties.h"
#include "TestGenericShape.h"
#include "TestPolyShape.h"
#include "TestCircle.h"
#include "TestCircularSegment.h"
#include "TestRectangle.h"
#include "TestTriangle.h"
#include "TestBulbTee.h"
#include "TestBulbTee2.h"
#include "TestPrecastBeam.h"
#include "TestPrecastBeam2.h"
#include "TestNUBeam.h"
#include "TestUBeam.h"
#include "TestUBeam2.h"
#include "TestMultiWeb.h"
#include "TestMultiWeb2.h"
#include "TestPlateGirder.h"
#include "TestTrafficBarrier.h"

#include "TestCompositeShapeItem.h"
#include "TestCompositeShape.h"

#include "TestVoidedSlab.h"
#include "TestVoidedSlab2.h"
#include "TestBoxBeam.h"
#include "TestDeckedSlabBeam.h"

#include "TestBeamShapeFactory.h"

#include "TestNUDeckedIBeam.h"
#include "TestPCIDeckedIBeam.h"

#include "TestMassProperties.h"
#include "TestElasticProperties.h"
#include "TestCompositeBeam.h"
#include "TestCompositeSectionEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int main(int argc, LPTSTR  argv[])
{
   ::CoInitialize(nullptr);

   CTestSize2d::Test();
   CTestPoint2d::Test();
   CTestRect2d::Test();
   CTestPoint2dCollection::Test();
   CTestVector2d::Test();
   CTestLineSegment2d::Test();
   CTestLine2d::Test();
   CTestSize3d::Test();
   CTestVector3d::Test();
   CTestPoint3d::Test();
   CTestPoint3dCollection::Test();
   CTestLineSegment3d::Test();
   CTestPlane3d::Test();
   CTestCoordinateXform2d::Test();
   CTestCoordinateXform3d::Test();
   CTestGeomUtil::Test();
   CTestShapeProperties::Test();
   CTestCompositeShapeItem::Test();
   CTestCompositeShape::Test();
   CTestPolyShape::Test();
   CTestCircle::Test();
   CTestCircularSegment::Test();
   CTestRectangle::Test();
   CTestTriangle::Test();
   CTestBulbTee::Test();
   CTestBulbTee2::Test();
   CTestPrecastBeam::Test();
   CTestPrecastBeam2::Test();
   CTestNUBeam::Test();
   CTestUBeam::Test();
   CTestUBeam2::Test();
   CTestMultiWeb::Test();
   CTestMultiWeb2::Test();
   CTestPlateGirder::Test();
   CTestTrafficBarrier::Test();
   CTestVoidedSlab::Test();
   CTestVoidedSlab2::Test();
   CTestBoxBeam::Test();
   CTestDeckedSlabBeam::Test();
   CTestNUDeckedIBeam::Test();
   CTestPCIDeckedIBeam::Test();
   CTestBeamShapeFactory::Test();
   CTestGenericShape::Test();
   CTestMassProperties::Test();
   CTestElasticProperties::Test();
   CTestCompositeBeam::Test();
   CTestCompositeSectionEx::Test();

   ::CoUninitialize();

	return 1;
}

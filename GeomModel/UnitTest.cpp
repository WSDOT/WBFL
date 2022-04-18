///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <GeomModel\GeomModelLib.h>

/****************************************************************************
CLASS
   gmUnitTest
****************************************************************************/

#include <GeomModel\UnitTest.h>
#include <GeomModel\Circle.h>
#include <GeomModel\CircularSegment.h>
#include <GeomModel\CompositeShape.h>
#include <GeomModel\ElasticProperties.h>
#include <GeomModel\MassProperties.h>
#include <GeomModel\Polygon.h>
#include <GeomModel\PrecastBeam.h>
#include <GeomModel\UBeam.h>
#include <GeomModel\NUBeam.h>
#include <GeomModel\Properties.h>
#include <GeomModel\Rectangle.h>
#include <GeomModel\Section.h>
#include <GeomModel\ShapeImp.h>
#include <GeomModel\ShapeListener.h>
#include <GeomModel\ShapeUtils.h>
#include <GeomModel\Triangle.h>
#include <GeomModel\WsdotPrecastBeams.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bool gmUnitTest::TestMe(dbgLog& rlog)
{
   bool tst = true;

#if defined _UNITTEST

   tst &= gmCircle::TestMe(rlog);
   tst &= gmCircularSegment::TestMe(rlog);
   tst &= gmCompositeShape::TestMe(rlog);
   tst &= gmShapeIter::TestMe(rlog);
   tst &= gmConstShapeIter::TestMe(rlog);
   tst &= gmElasticProperties::TestMe(rlog);
   tst &= gmPolygon::TestMe(rlog);
   tst &= gmPolyPointIter::TestMe(rlog);
   tst &= gmPrecastBeam::TestMe(rlog);
   tst &= gmUBeam::TestMe(rlog);
   tst &= gmNUBeam::TestMe(rlog);
   tst &= gmProperties::TestMe(rlog);
   tst &= gmRectangle::TestMe(rlog);
   tst &= gmSection::TestMe(rlog);
   tst &= gmSectionComponent::TestMe(rlog);
   tst &= gmSectionComponentIter::TestMe(rlog);
   tst &= gmSectionListener::TestMe(rlog);
   tst &= gmShapeImp::TestMe(rlog);
   tst &= gmShapeListener::TestMe(rlog);
   tst &= gmShapeUtils::TestMe(rlog);
   tst &= gmTriangle::TestMe(rlog);
   tst &= gmWsdotPrecastBeams::TestMe(rlog);

#endif

   return tst;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================

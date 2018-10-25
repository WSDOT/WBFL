///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#include <GeometricPrimitives\GeometryLib.h>
#include <GeometricPrimitives\UnitTest.h>

#include <GeometricPrimitives\Primitives.h>
#include <GeometricPrimitives\Primitives3d.h>
#include <GeometricPrimitives\Line2d.h>
#include <GeometricPrimitives\LineSegment2d.h>
#include <GeometricPrimitives\Vector2d.h>
#include <GeometricPrimitives\Vector3d.h>
#include <GeometricPrimitives\Polygon2d.h>
#include <GeometricPrimitives\Circle.h>
#include <GeometricPrimitives\Arc.h>
#include <GeometricPrimitives\GeomOp2d.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gpUnitTest
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bool gpUnitTest::TestMe(dbgLog& rlog)
{
   bool tst = true;

#if defined _UNITTEST

   // gpPoint2d
   tst &= gpPoint2d::TestMe(rlog);
   //tst &= gpPoint3d::TestMe(rlog); // doesn't have a TestMe method
   tst &= gpLine2d::TestMe(rlog);
   tst &= gpLineSegment2d::TestMe(rlog);
   tst &= gpPolygon2d::TestMe(rlog);
   tst &= gpPolyPointIter2d::TestMe(rlog);
   tst &= gpRect2d::TestMe(rlog);
   tst &= gpSize2d::TestMe(rlog);
   //tst &= gpSize3d::TestMe(rlog); // doesn't have a TestMe method
   tst &= gpVector2d::TestMe(rlog);
   tst &= gpVector3d::TestMe(rlog);
   tst &= gpCircle::TestMe(rlog);
   tst &= gpArc::TestMe(rlog);
   tst &= gpGeomOp2d::TestMe(rlog);

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

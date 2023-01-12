///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/UnitTest.h>
#include <GeomModel/Primitives.h>
#include <GeomModel/Primitives3d.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/LineSegment2d.h>
#include <GeomModel/LineSegment3d.h>
#include <GeomModel/Vector2d.h>
#include <GeomModel/Vector3d.h>
#include <GeomModel/Plane3d.h>
#include <GeomModel/Circle2d.h>
#include <GeomModel/Arc.h>
#include <GeomModel/GeomOp2d.h>
#include <GeomModel/Circle.h>
#include <GeomModel/CircularSegment.h>
#include <GeomModel/CompositeShape.h>
#include <GeomModel/ElasticProperties.h>
#include <GeomModel/MassProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/PrecastBeam.h>
#include <GeomModel/UBeam.h>
#include <GeomModel/UBeam2.h>
#include <GeomModel/NUBeam.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Rectangle.h>
#include <GeomModel/Section.h>
#include <GeomModel/SectionComponent.h>
#include <GeomModel/ShapeImpl.h>
#include <GeomModel/Triangle.h>
#include <GeomModel/CoordinateXform2d.h>
#include <GeomModel/CoordinateXform3d.h>
#include <GeomModel/BulbTee.h>
#include <GeomModel/PlateGirder.h>
#include <GeomModel/MultiWeb.h>
#include <GeomModel/MultiWeb2.h>
#include <GeomModel/NUDeckedIBeam.h>
#include <GeomModel/PCIDeckedIBeam.h>
#include <GeomModel/VoidedSlab.h>
#include <GeomModel/VoidedSlab2.h>
#include <GeomModel/BoxBeam.h>
#include <GeomModel/DeckedSlabBeam.h>
#include <GeomModel/GenericShape.h>
#include <GeomModel/CompositeBeam.h>
#include "MohrCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

bool UnitTest::TestMe(WBFL::Debug::Log& log)
{
   bool tst = true;

#if defined _UNITTEST
   tst &= Point2d::TestMe(log);
   tst &= Point3d::TestMe(log);
   tst &= Line2d::TestMe(log);
   tst &= LineSegment2d::TestMe(log);
   tst &= LineSegment3d::TestMe(log);
   tst &= Rect2d::TestMe(log);
   tst &= Size2d::TestMe(log);
   tst &= Size3d::TestMe(log);
   tst &= Vector2d::TestMe(log);
   tst &= Vector3d::TestMe(log);
   tst &= Plane3d::TestMe(log);
   tst &= Circle2d::TestMe(log);
   tst &= Arc::TestMe(log);
   tst &= GeometricOperations::TestMe(log);
   tst &= Circle::TestMe(log);
   tst &= CircularSegment::TestMe(log);
   tst &= CompositeShape::TestMe(log);
   tst &= Polygon::TestMe(log);
   tst &= PrecastBeam::TestMe(log);
   tst &= UBeam::TestMe(log);
   tst &= UBeam2::TestMe(log);
   tst &= NUBeam::TestMe(log);
   tst &= ShapeProperties::TestMe(log);
   tst &= ElasticProperties::TestMe(log);
   tst &= Rectangle::TestMe(log);
   tst &= Section::TestMe(log);
   tst &= SectionComponent::TestMe(log);
   tst &= ShapeImpl::TestMe(log);
   tst &= Triangle::TestMe(log);
   tst &= CoordinateXform2d::TestMe(log);
   tst &= CoordinateXform3d::TestMe(log);
   tst &= BulbTee::TestMe(log);
   tst &= PlateGirder::TestMe(log);
   tst &= MultiWeb::TestMe(log);
   tst &= MultiWeb2::TestMe(log);
   tst &= NUDeckedIBeam::TestMe(log);
   tst &= PCIDeckedIBeam::TestMe(log);
   tst &= VoidedSlab::TestMe(log);
   tst &= VoidedSlab2::TestMe(log);
   tst &= BoxBeam::TestMe(log);
   tst &= DeckedSlabBeam::TestMe(log);
   tst &= GenericShape::TestMe(log);
   tst &= CompositeBeam::TestMe(log);

   tst &= MohrCircle::TestMe(log);

#endif

   return tst;
}

bool UnitTest::TestHookPoint(Shape& shape)
{
   // Hook point must have by-reference semantics
   auto hookPnt = shape.GetHookPoint();
   Point2d original_point(*hookPnt);

   // set the hook point, expecting hookPnt to change
   shape.SetHookPoint(Point2d(15, 15));
   if (*hookPnt != Point2d(15, 15)) return false;

   // replace the hook point with a new point object
   std::shared_ptr<Point2d> new_hook_point(std::make_shared<Point2d>(50, 50));
   shape.SetHookPoint(new_hook_point);

   // hookPnt is no longer associated with shape
   auto hookPnt2 = shape.GetHookPoint();
   if (hookPnt == hookPnt2) return false;

   // moving the old hook point shoudn't alter the new hook point
   hookPnt->Move(100, 100);
   if (*hookPnt == *hookPnt2) return false;

   if (*hookPnt2 != Point2d(50, 50)) return false;

   // put the shape back the way it was when this method started
   hookPnt->Move(original_point);
   shape.SetHookPoint(hookPnt);

   return true;
}

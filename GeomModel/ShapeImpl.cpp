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
#include <GeomModel/ShapeImpl.h>
#include <GeomModel/Primitives.h>

using namespace WBFL::Geometry;

ShapeImpl::ShapeImpl() : Shape()
{
   m_CachedHookPoint = *m_pHookPoint;
}

ShapeImpl::ShapeImpl(std::shared_ptr<Point2d>& hookPnt) : Shape(),
m_pHookPoint(hookPnt)
{
   m_CachedHookPoint = *m_pHookPoint;
}

ShapeImpl::ShapeImpl(const Point2d& hookPnt) : Shape()
{
   m_pHookPoint->Move(hookPnt);
   m_CachedHookPoint = *m_pHookPoint;
}

ShapeImpl::ShapeImpl(const ShapeImpl& other) : Shape(other)
{
   Copy(other);
}

ShapeImpl::~ShapeImpl()
{
}

ShapeImpl& ShapeImpl::operator=(const ShapeImpl& other)
{
   if (this != &other)
   {
      __super::operator=(other);
      Copy(other);
   }
   return *this;
}

void ShapeImpl::Offset(const Size2d& delta)
{
   DoOffset(delta);
}

void ShapeImpl::Rotate(const Point2d& center, Float64 angle)
{
   DoRotate(center, angle);
}

void ShapeImpl::Offset(Float64 dx, Float64 dy)
{
   Offset(Size2d(dx, dy));
}

void ShapeImpl::Move(LocatorPoint lp, const Point2d& to)
{
   Offset(to - GetLocatorPoint(lp));
}

void ShapeImpl::Move(const Point2d& from, const Point2d& to)
{
   Offset(to - from);
}

void ShapeImpl::Rotate(Float64 cx, Float64 cy, Float64 angle)
{
   Rotate(Point2d(cx, cy), angle);
}

std::unique_ptr<Shape> ShapeImpl::CreateReflectedShape(const Line2d& line) const
{
   auto clone = CreateClone();
   clone->Reflect(line);
   return clone;
}

void ShapeImpl::SetLocatorPoint(LocatorPoint lp, Point2d& position)
{
   Move(lp, position);
}

Point2d ShapeImpl::GetLocatorPoint(LocatorPoint point) const
{
   ASSERTVALID;

   Rect2d rct;
   Point2d pnt;

   rct = GetBoundingBox();

   switch(point)
   {
   case LocatorPoint::HookPoint:
      pnt = *GetHookPoint();
      break;

   case LocatorPoint::TopLeft:
        pnt = rct.TopLeft();
        break;

   case LocatorPoint::TopCenter:
        pnt = rct.TopCenter();
        break;

   case LocatorPoint::TopRight:
        pnt = rct.TopRight();
        break;

   case LocatorPoint::CenterLeft:
        pnt = rct.LeftCenter();
        break;

   case LocatorPoint::CenterCenter:
        pnt = rct.Center();
        break;

   case LocatorPoint::CenterRight:
        pnt = rct.RightCenter();
        break;

   case LocatorPoint::BottomLeft:
        pnt = rct.BottomLeft();
        break;

   case LocatorPoint::BottomCenter:
        pnt = rct.BottomCenter();
        break;

   case LocatorPoint::BottomRight:
        pnt = rct.BottomRight();
        break;

   default:
      CHECK( false );
      break;
   }

   return pnt;
}

void ShapeImpl::SetHookPoint(std::shared_ptr<Point2d>& hookPnt)
{
   m_pHookPoint = hookPnt;
}

void ShapeImpl::SetHookPoint(const Point2d& hookPnt)
{
   m_pHookPoint->Move(hookPnt);
}

std::shared_ptr<Point2d>& ShapeImpl::GetHookPoint()
{
   return m_pHookPoint;
}

const std::shared_ptr<Point2d>& ShapeImpl::GetHookPoint() const
{
   return m_pHookPoint;
}

bool ShapeImpl::IsHookPointChanged() const
{
   return (*m_pHookPoint) != m_CachedHookPoint;
}

void ShapeImpl::ShapeCurrentWithHookPoint() const
{
   m_CachedHookPoint = *m_pHookPoint;
}


void ShapeImpl::Copy(const ShapeImpl& other)
{
   // make a copy of the hook point so these are independent shapes
   m_pHookPoint = std::make_shared<Point2d>(*other.m_pHookPoint);
   m_CachedHookPoint = *m_pHookPoint;
}

#if defined _DEBUG
bool ShapeImpl::AssertValid() const
{
   return true;
}

void ShapeImpl::Dump(WBFL::Debug::LogContext& os) const
{
   ASSERTVALID;
   os << _T("Dump for ShapeImpl") << WBFL::Debug::endl;
}
#endif // _DEBUG


#if defined _UNITTEST
bool ShapeImpl::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ShapeImpl");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented");
   TESTME_EPILOG("ShapeImpl");
}
#endif // _UNITTEST

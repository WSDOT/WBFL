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
#include <GeomModel/ShapeProperties.h>

#include "MohrCircle.h"
#include <MathEx.h>
#include <iostream>

using namespace WBFL::Geometry;

ShapeProperties::ShapeProperties(Float64 area,
   const Point2d& centroid,
   Float64 ixx, Float64 iyy, Float64 ixy,
   Float64 xLeft, Float64 yBottom,
   Float64 xRight, Float64 yTop)
{
   m_Properties.area = area;
   m_Properties.centroid = centroid;
   m_Properties.ixx = ixx;
   m_Properties.iyy = iyy;
   m_Properties.ixy = ixy;
   m_Properties.xLeft = xLeft;
   m_Properties.xRight = xRight;
   m_Properties.yTop = yTop;
   m_Properties.yBottom = yBottom;
   SetProperties(m_Properties); // causes the coordinate system and orientation to be set
}

ShapeProperties::ShapeProperties(const ShapePropertyParameters& properties)
{
   SetProperties(m_Properties); // causes the coordinate system and orientation to be set
}

ShapeProperties::~ShapeProperties()
{
}

bool ShapeProperties::operator==(const ShapeProperties& rhs) const
{
   return IsEqual(m_Properties.area, rhs.m_Properties.area) &&
      m_Properties.centroid == rhs.m_Properties.centroid &&
      IsEqual(m_Properties.ixx, rhs.m_Properties.ixx) &&
      IsEqual(m_Properties.iyy, rhs.m_Properties.iyy) &&
      IsEqual(m_Properties.ixy, rhs.m_Properties.ixy) &&
      IsEqual(m_Properties.xLeft,rhs.m_Properties.xLeft) &&
      IsEqual(m_Properties.xRight,rhs.m_Properties.xRight) &&
      IsEqual(m_Properties.yTop,rhs.m_Properties.yTop) &&
      IsEqual(m_Properties.yBottom,rhs.m_Properties.yBottom);
}

bool ShapeProperties::operator!=(const ShapeProperties& rhs) const
{
   return !(*this == rhs);
}

ShapeProperties ShapeProperties::operator+ (const ShapeProperties& rhs) const
{
   ShapeProperties tmp(*this);
   return tmp += rhs;
}

ShapeProperties ShapeProperties::operator- (const ShapeProperties& rhs) const
{
   ShapeProperties tmp(*this);
   return tmp -= rhs;
}

ShapeProperties& ShapeProperties::operator+= (const ShapeProperties& rhs)
{
   return Join(rhs, 1.0);
}

ShapeProperties& ShapeProperties::operator-= (const ShapeProperties& rhs)
{
   return Join(rhs, -1.0);
}

void ShapeProperties::SetProperties(Float64 area, const Point2d& centroid, Float64 ixx, Float64 iyy, Float64 ixy, Float64 xLeft, Float64 yBottom, Float64 xRight, Float64 yTop)
{
   m_Properties.area = area;
   m_Properties.centroid = centroid;
   m_Properties.ixx = ixx;
   m_Properties.iyy = iyy;
   m_Properties.ixy = ixy;
   m_Properties.xLeft = xLeft;
   m_Properties.xRight = xRight;
   m_Properties.yTop = yTop;
   m_Properties.yBottom = yBottom;
   SetProperties(m_Properties);
}

void ShapeProperties::SetProperties(const ShapePropertyParameters& properties)
{
   PRECONDITION(0 <= properties.xLeft && 0 <= properties.yBottom && 0 <= properties.xRight && 0 <= properties.yTop);
   m_Properties = properties;

   m_CoordType = CoordinateSystemType::Centroidal;
   m_Orientation = 0;

   UpdateOrientation();
}

const ShapePropertyParameters& ShapeProperties::GetProperties() const
{
   return m_Properties;
}

void ShapeProperties::Clear()
{
   m_Properties = ShapePropertyParameters();
}

void ShapeProperties::SetArea(Float64 area)
{
   m_Properties.area = area;
}

Float64 ShapeProperties::GetArea() const
{
   return m_Properties.area;
}

void ShapeProperties::SetCentroid(const Point2d& centroid)
{
   m_Properties.centroid = centroid;
   UpdateOrientation();
}

const Point2d& ShapeProperties::GetCentroid() const
{
   return m_CurrCentroid;
}

void ShapeProperties::SetIxx(Float64 ixx)
{
   m_Properties.ixx = ixx;
   UpdateOrientation();
}

Float64 ShapeProperties::GetIxx() const
{
   return m_CurrIxx;
}

void ShapeProperties::SetIyy(Float64 iyy)
{
   m_Properties.iyy = iyy;
   UpdateOrientation();
}

Float64 ShapeProperties::GetIyy() const
{
   return m_CurrIyy;
}

void ShapeProperties::SetIxy(Float64 ixy)
{
   m_Properties.ixy = ixy;
   UpdateOrientation();
}

Float64 ShapeProperties::GetIxy() const
{
   return m_CurrIxy;
}

void ShapeProperties::SetYtop(Float64 yTop)
{
   PRECONDITION(0 <= yTop);
   m_Properties.yTop = yTop;
}

Float64 ShapeProperties::GetYtop() const
{
   return m_Properties.yTop;
}

void ShapeProperties::SetYbottom(Float64 yBottom)
{
   PRECONDITION(0 <= yBottom);
   m_Properties.yBottom = yBottom;
}

Float64 ShapeProperties::GetYbottom() const
{
   return m_Properties.yBottom;
}

void ShapeProperties::SetXleft(Float64 xLeft)
{
   PRECONDITION(0 <= xLeft);
   m_Properties.xLeft = xLeft;
}

Float64 ShapeProperties::GetXleft() const
{
   return m_Properties.xLeft;
}

void ShapeProperties::SetXright(Float64 xRight)
{
   PRECONDITION(0 <= xRight);
   m_Properties.xRight = xRight;
}

Float64 ShapeProperties::GetXright() const
{
   return m_Properties.xRight;
}

Float64 ShapeProperties::GetI11() const
{
   MohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   Float64 ixx, iyy, ixy, angle;
   angle = ms.GetPrincipalDirection();
   std::tie(ixx,iyy,ixy) = ms.ComputeState(angle);
   return ixx;
}

Float64 ShapeProperties::GetI22() const
{
   MohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   Float64 ixx, iyy, ixy, angle;
   angle = ms.GetPrincipalDirection();
   std::tie(ixx,iyy,ixy) = ms.ComputeState(angle);
   return iyy;
}

Float64 ShapeProperties::GetPrincipalDirection() const
{
   MohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   return ms.GetPrincipalDirection();
}

Float64 ShapeProperties::GetI12Max() const
{
   MohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   return ms.GetTmax();
}

Float64 ShapeProperties::GetI12Min() const
{
   MohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   return -ms.GetTmax();
}

void ShapeProperties::SetCoordinateSystem(ShapeProperties::CoordinateSystemType sys)
{
   switch(sys)
   {
   case CoordinateSystemType::Centroidal:
      {
         m_CoordType = sys;
         m_Origin = m_Properties.centroid;
         m_Orientation = 0;
         UpdateOrientation();
         break;
      }
      case CoordinateSystemType::Global:
      {
         m_CoordType = sys;
         m_Origin = Point2d(0,0);
         m_Orientation = 0;
         UpdateOrientation();
         break;
      }
      case CoordinateSystemType::Principal:
      {
         // first have to get principal orientation angle
         SetCoordinateSystem(CoordinateSystemType::Centroidal);
         m_Orientation = GetPrincipalDirection();
         m_CoordType = sys;
         UpdateOrientation();
         break;
      }
      case CoordinateSystemType::UserDefined:
      {
         m_CoordType = sys;
         break;
      }
      default:
         CHECKX(0,_T("Bad coordinate type"));
   }
}

ShapeProperties::CoordinateSystemType ShapeProperties::GetCoordinateSystem() const
{
   return m_CoordType;
}

void ShapeProperties::SetOrigin(const Point2d& origin)
{
      m_CoordType = CoordinateSystemType::UserDefined;
      m_Origin = origin;
      UpdateOrientation();
}

const Point2d& ShapeProperties::GetOrigin() const
{
   return m_Origin;
}

void ShapeProperties::SetOrientation(Float64 angle)
{
      m_CoordType = CoordinateSystemType::UserDefined;
      m_Orientation = angle;
      UpdateOrientation();
}

Float64 ShapeProperties::GetOrientation() const
{
   return m_Orientation;
}

void ShapeProperties::UpdateOrientation()
{
   switch (m_CoordType)
   {
   case (CoordinateSystemType::Centroidal):
      {
         // in centroidal system = just copy values
         m_CurrCentroid = m_Properties.centroid;
         m_CurrIxx      = m_Properties.ixx;
         m_CurrIyy      = m_Properties.iyy;
         m_CurrIxy      = m_Properties.ixy;
         break;
      }
   default:
      {
         // not centroidal - need to rotate into orientation
         // first rotate about centroid
         Float64 ixx, iyy, ixy;
         MohrCircle ms(m_Properties.ixx, m_Properties.iyy, m_Properties.ixy);
         std::tie(ixx,iyy,ixy) = ms.ComputeState(m_Orientation);

         // next need to transform into origin coordinates
         Point2d delta( m_Properties.centroid.X() - m_Origin.X(), m_Properties.centroid.Y() - m_Origin.Y());
         delta.Rotate(Point2d(0,0), -m_Orientation);

         Float64 dx = delta.X();
         Float64 dy = delta.Y();

         // use parallel axis theorem to put properties into new system
         m_CurrCentroid = delta;
         m_CurrIxx      = ixx + m_Properties.area * dy * dy;
         m_CurrIyy      = iyy + m_Properties.area * dx * dx;
         m_CurrIxy      = ixy + m_Properties.area * dx * dy;
         break;
      }
   }
}

ShapeProperties& ShapeProperties::Join(const ShapeProperties& rOther, Float64 scale)
{
   auto currCoordinateSystemType = m_CoordType; // reserve the current coordinate system type

   // convert to global coordinates
   SetCoordinateSystem(CoordinateSystemType::Global);
   ShapeProperties other(rOther);
   other.SetCoordinateSystem(CoordinateSystemType::Global);

   Float64 ixx = 0, iyy = 0, ixy = 0; // about global axes
   Float64 mxx = 0, myy = 0;        // first moments

   Float64 cx1, cy1;
   std::tie(cx1,cy1) = m_Properties.centroid.GetLocation();

   Float64 cx2, cy2;
   std::tie(cx2,cy2) = other.GetCentroid().GetLocation();

   mxx = m_Properties.area * m_Properties.centroid.Y() + scale* other.m_Properties.area * other.m_Properties.centroid.Y();
   myy = m_Properties.area * m_Properties.centroid.X() + scale * other.m_Properties.area * other.m_Properties.centroid.X();

   // Get centroidal I for each shape and transform it to the global axes
   ixx = (m_Properties.ixx + m_Properties.area * m_Properties.centroid.Y() * m_Properties.centroid.Y() +
      scale * other.m_Properties.ixx + scale * other.m_Properties.area * other.m_Properties.centroid.Y() * other.m_Properties.centroid.Y());

   iyy = (m_Properties.iyy + m_Properties.area * m_Properties.centroid.X() * m_Properties.centroid.X() +
      scale * other.m_Properties.iyy + scale * other.m_Properties.area * other.m_Properties.centroid.X() * other.m_Properties.centroid.X());

   ixy = (m_Properties.ixy + m_Properties.area * m_Properties.centroid.X() * m_Properties.centroid.Y() +
      scale * other.m_Properties.ixy + scale * other.m_Properties.area * other.m_Properties.centroid.X() * other.m_Properties.centroid.Y());

   m_Properties.area += scale * other.m_Properties.area;

   m_Properties.centroid.Y() = mxx / m_Properties.area;
   m_Properties.centroid.X() = myy / m_Properties.area;

   Float64 cgx, cgy;
   std::tie(cgx,cgy) = m_Properties.centroid.GetLocation();

   m_Properties.ixx = ixx - m_Properties.area * m_Properties.centroid.Y() * m_Properties.centroid.Y();
   m_Properties.iyy = iyy - m_Properties.area * m_Properties.centroid.X() * m_Properties.centroid.X();
   m_Properties.ixy = ixy - m_Properties.area * m_Properties.centroid.X() * m_Properties.centroid.Y();

   // Update the distance from the edges to the centroid
   Float64 l2 = other.GetXleft();
   Float64 r2 = other.GetXright();
   Float64 t2 = other.GetYtop();
   Float64 b2 = other.GetYbottom();

   Float64 l, r, t, b; // distance from the global axes to the extreme edges
   l = Min(cx1 - m_Properties.xLeft, cx2 - l2);
   r = Max(cx1 + m_Properties.xRight, cx2 + r2);
   t = Max(cy1 + m_Properties.yTop, cy2 + t2);
   b = Min(cy1 - m_Properties.yBottom, cy2 - b2);

   m_Properties.xLeft = cgx - l;
   m_Properties.xRight = r - cgx;
   m_Properties.yTop = t - cgy;
   m_Properties.yBottom = cgy - b;

   UpdateOrientation();

   // restore the original coordinate system
   SetCoordinateSystem(currCoordinateSystemType);

   return *this;
}

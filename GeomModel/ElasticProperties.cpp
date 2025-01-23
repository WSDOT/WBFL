///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <GeomModel/ElasticProperties.h>

#include <MathEx.h>
#include <iostream>

using namespace WBFL::Geometry;

ElasticProperties::ElasticProperties()
{
}

ElasticProperties::ElasticProperties(Float64 eA,
                           const Point2d& centroid,
                           Float64 eIxx, Float64 eIyy, Float64 eIxy,
                           Float64 xLeft, Float64 yBottom,
                           Float64 xRight, Float64 yTop):
m_Properties(eA, centroid, eIxx, eIyy, eIxy, xLeft, yBottom, xRight,yTop)
{
}

ElasticProperties::~ElasticProperties()
{
}

bool ElasticProperties::operator==(const ElasticProperties& rhs) const
{
   return m_Properties == rhs.m_Properties;
}

bool ElasticProperties::operator!=(const ElasticProperties& rhs) const
{
   return !(*this == rhs);
}

ElasticProperties ElasticProperties::operator+ (const ElasticProperties& rhs) const
{
   ElasticProperties tmp(*this);
   return tmp+=rhs;
}


ElasticProperties& ElasticProperties::operator+= (const ElasticProperties& rhs)
{
   m_Properties+=rhs.m_Properties;
   return *this;
}

ElasticProperties ElasticProperties::operator- (const ElasticProperties& rhs) const
{
   ElasticProperties tmp(*this);
   return tmp -= rhs;
}

ElasticProperties& ElasticProperties::operator-= (const ElasticProperties& rhs)
{
   m_Properties -= rhs.m_Properties;
   return *this;
}

void ElasticProperties::SetEA(Float64 eA)
{
   m_Properties.SetArea(eA);
}

Float64 ElasticProperties::GetEA() const
{
   return m_Properties.GetArea();
}

void ElasticProperties::SetCentroid(const Point2d& cent)
{
   m_Properties.SetCentroid(cent);
}

const Point2d& ElasticProperties::GetCentroid() const
{
   return m_Properties.GetCentroid();
}

void ElasticProperties::SetEIxx(Float64 eIxx)
{
   m_Properties.SetIxx(eIxx);
}

Float64 ElasticProperties::GetEIxx() const
{
   return m_Properties.GetIxx();
}

void ElasticProperties::SetEIyy(Float64 eIyy)
{
   m_Properties.SetIyy(eIyy);
}

Float64 ElasticProperties::GetEIyy() const
{
   return m_Properties.GetIyy();
}

void ElasticProperties::SetEIxy(Float64 eIxy)
{
   m_Properties.SetIxy(eIxy);
}

Float64 ElasticProperties::GetEIxy() const
{
   return m_Properties.GetIxy();
}

void ElasticProperties::SetYtop(Float64 ytop)
{
   m_Properties.SetYtop(ytop);
}

Float64 ElasticProperties::GetYtop() const
{
   return m_Properties.GetYtop();
}

void ElasticProperties::SetYbottom(Float64 ybot)
{
   m_Properties.SetYbottom(ybot);
}

Float64 ElasticProperties::GetYbottom() const
{
   return m_Properties.GetYbottom();
}

void ElasticProperties::SetXleft(Float64 xleft)
{
   m_Properties.SetXleft(xleft);
}

Float64 ElasticProperties::GetXleft() const
{
   return m_Properties.GetXleft();
}

void ElasticProperties::SetXright(Float64 xright)
{
   m_Properties.SetXright(xright);
}

Float64 ElasticProperties::GetXright() const
{
   return m_Properties.GetXright();
}

Float64 ElasticProperties::GetEI11() const
{
   return m_Properties.GetI11();
}

Float64 ElasticProperties::GetEI22() const
{
   return m_Properties.GetI22();
}

Float64 ElasticProperties::GetPrincipalDirection() const
{
   return m_Properties.GetPrincipalDirection();
}

Float64 ElasticProperties::GetEI12Max() const
{
   return m_Properties.GetI12Max();
}

Float64 ElasticProperties::GetEI12Min() const
{
   return m_Properties.GetI12Min();
}

void ElasticProperties::SetCoordinateSystem(ElasticProperties::CoordinateSystemType sys)
{
   ShapeProperties::CoordinateSystemType pct;
   switch(sys)
   {
   case CoordinateSystemType::Centroidal:
      {
         pct= ShapeProperties::CoordinateSystemType::Centroidal;
         break;
      }
      case CoordinateSystemType::Global:
      {
         pct= ShapeProperties::CoordinateSystemType::Global;
         break;
      }
      case CoordinateSystemType::Principal:
      {
         pct= ShapeProperties::CoordinateSystemType::Principal;
         break;
      }
      case CoordinateSystemType::UserDefined:
      {
         pct= ShapeProperties::CoordinateSystemType::UserDefined;
         break;
      }
      default:
         CHECKX(0, _T("Bad coordinate type"));
   }

   m_Properties.SetCoordinateSystem(pct);
}

ElasticProperties::CoordinateSystemType ElasticProperties::GetCoordinateSystem() const
{
   ElasticProperties::CoordinateSystemType epct= CoordinateSystemType::UserDefined;

   ShapeProperties::CoordinateSystemType pct = m_Properties.GetCoordinateSystem();
   switch(pct)
   {
      case ShapeProperties::CoordinateSystemType::Centroidal:
      {
         epct= CoordinateSystemType::Centroidal;
         break;
      }
      case ShapeProperties::CoordinateSystemType::Global:
      {
         epct= CoordinateSystemType::Global;
         break;
      }
      case ShapeProperties::CoordinateSystemType::Principal:
      {
         epct= CoordinateSystemType::Principal;
         break;
      }
      case ShapeProperties::CoordinateSystemType::UserDefined:
      {
         epct= CoordinateSystemType::UserDefined;
         break;
      }
      default:
         CHECKX(0,_T("Bad coordinate type"));
   }

   return epct;
}

void ElasticProperties::SetOrigin(const Point2d& origin)
{
   m_Properties.SetOrigin(origin);
}

const Point2d& ElasticProperties::GetOrigin() const
{
   return m_Properties.GetOrigin();
}

void ElasticProperties::SetOrientation(Float64 angle)
{
   m_Properties.SetOrientation(angle);
}

Float64 ElasticProperties::GetOrientation() const
{
   return m_Properties.GetOrientation();
}

ShapeProperties ElasticProperties::TransformProperties(Float64 E) const
{
   ShapeProperties props = m_Properties;
   props.SetArea( props.GetArea()/E );
   props.SetIxx( props.GetIxx()/E );
   props.SetIxy( props.GetIxy()/E );
   props.SetIyy( props.GetIyy()/E );

   return props;
}

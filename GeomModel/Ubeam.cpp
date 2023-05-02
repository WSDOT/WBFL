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
#include <GeomModel/UBeam.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Primitives3d.h>
#include <MathEx.h>
#include <memory>

using namespace WBFL::Geometry;

UBeam::UBeam()
{
}

UBeam::UBeam(Float64 w1, Float64 w2, Float64 w3,Float64 w4,Float64 w5,
                 Float64 d1, Float64 d2, Float64 d3,Float64 d4,Float64 d5,Float64 d6,Float64 d7,
                 Float64 t,
   std::shared_ptr<Point2d>& hookPnt) :
   FlangedBeam(hookPnt),
m_W1(w1),
m_W2(w2),
m_W3(w3),
m_W4(w4),
m_W5(w5),
m_D1(d1),
m_D2(d2),
m_D3(d3),
m_D4(d4),
m_D5(d5),
m_D6(d6),
m_D7(d7),
m_T(t)
{
   PRECONDITION(w1    >  0);
   PRECONDITION(w2    >  0);
   PRECONDITION(w3    >= 0);
   PRECONDITION(w4    >= 0);
   PRECONDITION(d1    >  0);
   PRECONDITION(d2    >  0);
   PRECONDITION(d3    >= 0);
   PRECONDITION(d4    >= 0);
   PRECONDITION(d5    >= 0);
   PRECONDITION(d6    >= 0);
   PRECONDITION(t     >  0);
}

UBeam::UBeam(Float64 w1, Float64 w2, Float64 w3, Float64 w4, Float64 w5,
   Float64 d1, Float64 d2, Float64 d3, Float64 d4, Float64 d5, Float64 d6, Float64 d7,
   Float64 t,
   const Point2d& hookPnt) :
   FlangedBeam(hookPnt),
   m_W1(w1),
   m_W2(w2),
   m_W3(w3),
   m_W4(w4),
   m_W5(w5),
   m_D1(d1),
   m_D2(d2),
   m_D3(d3),
   m_D4(d4),
   m_D5(d5),
   m_D6(d6),
   m_D7(d7),
   m_T(t)
{
   PRECONDITION(w1 > 0);
   PRECONDITION(w2 > 0);
   PRECONDITION(w3 >= 0);
   PRECONDITION(w4 >= 0);
   PRECONDITION(d1 > 0);
   PRECONDITION(d2 > 0);
   PRECONDITION(d3 >= 0);
   PRECONDITION(d4 >= 0);
   PRECONDITION(d5 >= 0);
   PRECONDITION(d6 >= 0);
   PRECONDITION(t > 0);
}
UBeam::~UBeam()
{
}

void UBeam::SetW1(Float64 w1)
{
   PRECONDITION(w1>0);
   m_W1 = w1;
   SetDirtyFlag();
}

Float64 UBeam::GetW1() const
{
   return m_W1;
}

void UBeam::SetW2(Float64 w2)
{
   PRECONDITION(w2>0);
   m_W2 = w2;
   SetDirtyFlag();
}

Float64 UBeam::GetW2() const
{
   return m_W2;
}

void UBeam::SetW3(Float64 w3)
{
   PRECONDITION(w3>=0);
   m_W3 = w3;
   SetDirtyFlag();
}

Float64 UBeam::GetW3() const
{
   return m_W3;
}

void UBeam::SetW4(Float64 w4)
{
   PRECONDITION(w4>=0);
   m_W4 = w4;
   SetDirtyFlag();
}

Float64 UBeam::GetW4() const
{
   return m_W4;
}

void UBeam::SetW5(Float64 w5)
{
   PRECONDITION(w5>=0);
   m_W5 = w5;
   SetDirtyFlag();
}

Float64 UBeam::GetW5() const
{
   return m_W5;
}

void UBeam::SetD1(Float64 d1)
{
   PRECONDITION(d1>0);
   m_D1 = d1;
   SetDirtyFlag();
}

Float64 UBeam::GetD1() const
{
   return m_D1;
}

void UBeam::SetD2(Float64 d2)
{
   PRECONDITION(d2>0);
   m_D2 = d2;
   SetDirtyFlag();
}

Float64 UBeam::GetD2() const
{
   return m_D2;
}

void UBeam::SetD3(Float64 d3)
{
   PRECONDITION(d3>=0);
   m_D3 = d3;
   SetDirtyFlag();
}

Float64 UBeam::GetD3() const
{
   return m_D3;
}

void UBeam::SetD4(Float64 d4)
{
   PRECONDITION(d4>=0);
   m_D4 = d4;
   SetDirtyFlag();
}

Float64 UBeam::GetD4() const
{
   return m_D4;
}

void UBeam::SetD5(Float64 d5)
{
   PRECONDITION(d5>=0);
   m_D5 = d5;
   SetDirtyFlag();
}

Float64 UBeam::GetD5() const
{
   return m_D5;
}

void UBeam::SetD6(Float64 d6)
{
   PRECONDITION(d6>=0);
   m_D6 = d6;
   SetDirtyFlag();
}

Float64 UBeam::GetD6() const
{
   return m_D6;
}

void UBeam::SetD7(Float64 d7)
{
   PRECONDITION(d7>=0);
   m_D7 = d7;
   SetDirtyFlag();
}

Float64 UBeam::GetD7() const
{
   return m_D7;
}

void UBeam::SetT(Float64 t)
{
   PRECONDITION(t>=0);
   m_T = t;
   SetDirtyFlag();
}

Float64 UBeam::GetT() const
{
   return m_T;
}

Float64 UBeam::GetSlope(WebIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   GetPolygon(); // causes the slope to be updated
   return (webIdx == 0 ? -1.0 : 1.0) * m_Slope;
}

Float64 UBeam::GetHeight() const
{
   return m_D1;
}

Float64 UBeam::GetWebLocation(WebIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   GetPolygon(); // causes the slope to be updated
   Float64 sign = (webIdx == 0) ? -1 : 1;

   return sign * (m_D1 / m_Slope - 0.5 * m_T * sqrt(m_Slope * m_Slope + 1) / m_Slope + m_W1 / 2);
}

Float64 UBeam::GetWebSpacing() const
{
   GetPolygon(); // causes the slope to be updated
   return m_W1 - m_T * sqrt(m_Slope * m_Slope + 1) / m_Slope + 2 * m_D1 / m_Slope;
}

void UBeam::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void UBeam::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

IndexType UBeam::GetTopFlangeCount() const
{
   return 2;
}

Float64 UBeam::GetTopFlangeLocation(IndexType flangeIdx) const
{
   if (1 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   Float64 sign = (flangeIdx == 0) ? -1 : 1;
   return sign * (GetTopWidth() - GetTopFlangeWidth(flangeIdx)) / 2;
}

Float64 UBeam::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (1 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   GetPolygon(); // causes m_Slope to be updated
   Float64 t = m_T*sqrt(m_Slope * m_Slope + 1)/ m_Slope;
   return (m_W4 + (m_D6 + m_D7) / m_Slope) + (m_W5 - (m_D4 + m_D5) / m_Slope) + t;
}

IndexType UBeam::GetBottomFlangeCount() const
{
   return 1;
}

Float64 UBeam::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 UBeam::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetBottomWidth();
}

Float64 UBeam::GetTopWidth() const
{
   return m_W2;
}

Float64 UBeam::GetBottomWidth() const
{
   return m_W1;
}

MatingSurfaceIndexType UBeam::GetMatingSurfaceCount() const
{
   return 2;
}

Float64 UBeam::GetMatingSurfaceWidth(MatingSurfaceIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopFlangeWidth(webIdx)/2;
}

Float64 UBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopFlangeLocation(webIdx);
}

IndexType UBeam::GetWebCount() const
{
   return 2;
}

Plane3d UBeam::GetWebPlane(WebIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   Float64 slope = GetSlope(webIdx);

   Float64 sign = (webIdx == 0 ? -1.0 : 1.0);

   Float64 x, y, z;
   Float64 t = fabs((m_T/2)*(sqrt(slope*slope+1)/slope));
   x = 0;
   y = 0;
   z = sign*(m_W1/2 - t);

   Point3d p1(x, y, z);

   x = 100;
   y = 0;
   z = sign*(m_W1/2 - t);

   Point3d p2(x, y, z);

   x = 0;
   y = 100;
   z = sign*(m_W1/2 - t - y/slope);
   Point3d p3(x, y, z);
   
   return Plane3d(p1, p2, p3);
}

Float64 UBeam::GetShearWidth() const
{
   return GetMinWebWidth() * 2;
}

Float64 UBeam::GetAvgWebWidth() const
{
   return m_T;
}

Float64 UBeam::GetMinWebWidth() const
{
   return m_T;
}

Float64 UBeam::GetMinBottomFlangeThickness() const
{
   return m_D2;
}

Float64 UBeam::GetMinTopFlangeThickness() const
{
   return Min(m_D4,m_D6);
}

std::unique_ptr<Shape> UBeam::CreateClone() const
{
   return std::make_unique<UBeam>(*this);
}

#if defined _DEBUG
bool UBeam::AssertValid() const
{
   if ( m_W1 < 0 || m_W2 < 0 || m_W3 < 0 || m_W4 < 0 ) return false;
   if ( m_D1 < 0 || m_D2 < 0 || m_D3 < 0 || m_D4 < 0 || m_D5 < 0 || m_D6 < 0 ) return false;
   if ( m_T  < 0)                          return false;

   return __super::AssertValid();
}

void UBeam::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for UBeam ***") << WBFL::Debug::endl;
   ShapeImpl::Dump( os );
   os << _T("  Hook Point      = (")<<GetHookPoint()->X()<<_T(", ")<<GetHookPoint()->Y()<<_T(")")<< WBFL::Debug::endl;
   os << _T("  Rotation        =  ")<<m_Rotation<< WBFL::Debug::endl;
   os << _T("  D1              =  ")<<m_D1 << WBFL::Debug::endl;
   os << _T("  D2              =  ")<<m_D2 << WBFL::Debug::endl;
   os << _T("  D3              =  ")<<m_D3 << WBFL::Debug::endl;
   os << _T("  D4              =  ")<<m_D4 << WBFL::Debug::endl;
   os << _T("  D5              =  ")<<m_D5 << WBFL::Debug::endl;
   os << _T("  D6              =  ")<<m_D6 << WBFL::Debug::endl;
   os << _T("  D7              =  ")<<m_D7 << WBFL::Debug::endl;
   os << _T("  W1              =  ")<<m_W1 << WBFL::Debug::endl;
   os << _T("  W2              =  ")<<m_W2 << WBFL::Debug::endl;
   os << _T("  W3              =  ")<<m_W3 << WBFL::Debug::endl;
   os << _T("  W4              =  ")<<m_W4 << WBFL::Debug::endl;
   os << _T("  W5              =  ")<<m_W5 << WBFL::Debug::endl;
   os << _T("  T               =  ")<<m_T  << WBFL::Debug::endl;
   os << _T("Polygon rep of beam") << WBFL::Debug::endl;
   GetPolygon()->Dump(os);
}
#endif // _DEBUG

void UBeam::UpdateSlope() const
{
   Float64 rise = m_D1 - m_D4 - m_D5;
   Float64 run = (m_W2 - m_W1)/2 - m_W5;

   m_Slope = IsZero(run) ? DBL_MAX : rise / run;
}

void UBeam::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   ASSERTVALID;

   UpdateSlope();

   Float64 T = m_T;
   if (!IsZero(m_Slope))
      T = m_T * sqrt(m_Slope * m_Slope + 1) / m_Slope;

   Float64 D4(m_D4), D5(m_D5), D6(m_D6), D7(m_D7);
   if (IsZero(m_W4))
   {
      // D6 and D7 must be zero if W4 is zero
      CHECK(IsZero(m_D6));
      CHECK(IsZero(m_D7));
      D6 = 0;
      D7 = 0;
   }

   if (IsZero(m_W5))
   {
      // D4 and D5 must be zero if W5 is zero
      CHECK(IsZero(m_D4));
      CHECK(IsZero(m_D5));
      D4 = 0;
      D5 = 0;
   }

   // start at the bottom center and go around clockwise
   // Hook point is at bottom center (0,0)
   // Compute left side points, mirror for right side
   Float64 p1_x = 0.;
   Float64 p1_y = 0.;

   Float64 p2_x = -m_W1 / 2;
   Float64 p2_y = 0.;

   Float64 p3_x = p2_x - (IsZero(m_Slope) ? 0 : (m_D1 - D4 - D5) / m_Slope);
   Float64 p3_y = m_D1 - D4 - D5;

   Float64 p4_x = -m_W2 / 2;
   Float64 p4_y = m_D1 - D4;

   Float64 p5_x = -m_W2 / 2;
   Float64 p5_y = m_D1;

   Float64 p6_x;
   if (IsZero(D4) && IsZero(D5) && !IsZero(D6) & !IsZero(D7))
   {
      // Flange only on the inside
      p6_x = -m_W2 / 2 + m_W4 + T + (IsZero(m_Slope) ? 0 : (D6 + D7) / m_Slope);
   }
   else if (!IsZero(D4) && !IsZero(D5) && IsZero(D6) & IsZero(D7))
   {
      // Flange only on the outside
      p6_x = -m_W2 / 2 + m_W5 + T - (IsZero(m_Slope) ? 0 : (D4 + D5) / m_Slope);
   }
   else
   {
      // Flange on both sides or no flange
      p6_x = -m_W2 / 2 + m_W4 + m_W5 + T;
   }
   Float64 p6_y = m_D1;

   Float64 p7_x = p6_x;
   Float64 p7_y = m_D1 - D6;

   Float64 p8_x = p7_x - m_W4;
   Float64 p8_y = m_D1 - D6 - D7;

   Float64 p9_x = p8_x + (IsZero(m_Slope) ? 0 : (m_D1 - m_D2 - m_D3 - D6 - D7) / m_Slope);
   Float64 p9_y = m_D2 + m_D3;

   Float64 p10_x = p9_x + m_W3;
   Float64 p10_y = m_D2;

   polygon->AddPoint(Point2d( p1_x, p1_y));
   polygon->AddPoint(Point2d( p2_x, p2_y));
   polygon->AddPoint(Point2d( p3_x, p3_y));
   polygon->AddPoint(Point2d( p4_x, p4_y));
   polygon->AddPoint(Point2d( p5_x, p5_y));
   polygon->AddPoint(Point2d( p6_x, p6_y));
   polygon->AddPoint(Point2d( p7_x, p7_y));
   polygon->AddPoint(Point2d( p8_x, p8_y));
   polygon->AddPoint(Point2d( p9_x, p9_y));
   polygon->AddPoint(Point2d( p10_x, p10_y));
   polygon->AddPoint(Point2d( 0.0, p10_y));

   polygon->SetSymmetry(Polygon::Symmetry::Y);

   //// mirror points
   //polygon->AddPoint(Point2d(-p10_x, p10_y));
   //polygon->AddPoint(Point2d(-p9_x, p9_y));
   //polygon->AddPoint(Point2d(-p8_x, p8_y));
   //polygon->AddPoint(Point2d(-p7_x, p7_y));
   //polygon->AddPoint(Point2d(-p6_x, p6_y)); 
   //polygon->AddPoint(Point2d(-p5_x, p5_y));
   //polygon->AddPoint(Point2d(-p4_x, p4_y));
   //polygon->AddPoint(Point2d(-p3_x, p3_y));
   //polygon->AddPoint(Point2d(-p2_x, p2_y));

   if (!IsZero(m_Rotation))
      polygon->Rotate(Point2d(0,0), m_Rotation);

   polygon->Move(Point2d(0, 0), *GetHookPoint());
}

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool UBeam::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("UBeam");

   // let's try a U48G4
   Float64 t  = 7.;
   Float64 w1 = 48;
   Float64 w2 = 61.71428571;
   Float64 w3 = 12;
   Float64 w4 = 0;
   Float64 w5 = 0;
   Float64 d1 = 48;
   Float64 d2 = 6;
   Float64 d3 = 6;
   Float64 d4 = 0;
   Float64 d5 = 0;
   Float64 d6 = 0;
   Float64 d7 = 0;

   UBeam U48G4(w1,w2,w3,w4,w5,d1,d2,d3,d4,d5,d6,d7,t,Point2d());
   ShapeProperties aprops = U48G4.GetProperties();
   TRY_TESTME (U48G4.GetBoundingBox() == Rect2d(-30.857142857143,0.0,30.857142857143,48.)) ;
   TRY_TESTME ( IsEqual(aprops.GetArea(), 953.9697)) ;
   TRY_TESTME ( IsEqual(aprops.GetIxx(),  208841.6, 0.1)) ;
   TRY_TESTME ( IsEqual(aprops.GetIxy(),  0.)) ;
   TRY_TESTME ( IsEqual(aprops.GetCentroid().X(),  0.)) ;
   TRY_TESTME ( IsEqual(aprops.GetCentroid().Y(), 18.29891)) ;
   TRY_TESTME ( IsEqual(U48G4.GetHeight(), 48.0)) ;
   TRY_TESTME(IsEqual(U48G4.GetTopFlangeWidth(0), 7.0710678118212806));
   TRY_TESTME(IsEqual(U48G4.GetTopFlangeWidth(1), 7.0710678118212806));
   TRY_TESTME ( IsEqual(U48G4.GetBottomFlangeWidth(0), 48.0)) ;
   TRY_TESTME ( IsEqual(U48G4.GetT(), 7.)) ;
   TRY_TESTME ( IsEqual(U48G4.GetSlope(0), -7.)) ;
   TRY_TESTME ( IsEqual(U48G4.GetW1(), w1));
   TRY_TESTME ( IsEqual(U48G4.GetW2(), w2));
   TRY_TESTME ( IsEqual(U48G4.GetW3(), w3));
   TRY_TESTME ( IsEqual(U48G4.GetW4(), w4));
   TRY_TESTME ( IsEqual(U48G4.GetW5(), w5));
   TRY_TESTME ( IsEqual(U48G4.GetD1(), d1));
   TRY_TESTME ( IsEqual(U48G4.GetD2(), d2));
   TRY_TESTME ( IsEqual(U48G4.GetD3(), d3));
   TRY_TESTME ( IsEqual(U48G4.GetD4(), d4));
   TRY_TESTME ( IsEqual(U48G4.GetD5(), d5));
   TRY_TESTME ( IsEqual(U48G4.GetD6(), d6));
   TRY_TESTME ( IsEqual(U48G4.GetD7(), d7));
   TRY_TESTME ( IsEqual(U48G4.GetT(),  t ));


   // let's try a UF48G4
   t  = 7.;
   w1 = 48;
   w2 = 70;
   w3 = 12;
   w4 = 3;
   w5 = 5;
   d1 = 48;
   d2 = 6;
   d3 = 6;
   d4 = 4.5;
   d5 = 1.5;
   d6 = 4.5;
   d7 = 1.5;

   UBeam UF48G4(w1,w2,w3,w4,w5,d1,d2,d3,d4,d5,d6,d7,t,Point2d());
   aprops = UF48G4.GetProperties();
   TRY_TESTME (UF48G4.GetBoundingBox() == Rect2d(-35,0.0,35,48.)) ;
   TRY_TESTME ( IsEqual(aprops.GetArea(), 1037.9696961966997)) ;
   TRY_TESTME(IsEqual(aprops.GetIxx(), 265565.70300474146));
   TRY_TESTME(IsEqual(aprops.GetIyy(), 496020.14081542683));
   TRY_TESTME ( IsEqual(aprops.GetIxy(),  0.)) ;
   TRY_TESTME ( IsEqual(aprops.GetCentroid().X(),  0.)) ;
   TRY_TESTME ( IsEqual(aprops.GetCentroid().Y(), 20.488662093569786)) ;
   TRY_TESTME ( IsEqual(UF48G4.GetHeight(), 48.0)) ;
   TRY_TESTME(IsEqual(UF48G4.GetTopFlangeWidth(0), 15.071067811865476));
   TRY_TESTME(IsEqual(UF48G4.GetTopFlangeWidth(1), 15.071067811865476));
   TRY_TESTME ( IsEqual(UF48G4.GetBottomFlangeWidth(0), 48.0)) ;
   TRY_TESTME ( IsEqual(UF48G4.GetT(), 7.)) ;
   TRY_TESTME ( IsEqual(UF48G4.GetSlope(1), 7.)) ;
   TRY_TESTME ( IsEqual(UF48G4.GetW1(), w1));
   TRY_TESTME ( IsEqual(UF48G4.GetW2(), w2));
   TRY_TESTME ( IsEqual(UF48G4.GetW3(), w3));
   TRY_TESTME ( IsEqual(UF48G4.GetW4(), w4));
   TRY_TESTME ( IsEqual(UF48G4.GetW5(), w5));
   TRY_TESTME ( IsEqual(UF48G4.GetD1(), d1));
   TRY_TESTME ( IsEqual(UF48G4.GetD2(), d2));
   TRY_TESTME ( IsEqual(UF48G4.GetD3(), d3));
   TRY_TESTME ( IsEqual(UF48G4.GetD4(), d4));
   TRY_TESTME ( IsEqual(UF48G4.GetD5(), d5));
   TRY_TESTME ( IsEqual(UF48G4.GetD6(), d6));
   TRY_TESTME ( IsEqual(UF48G4.GetD7(), d7));
   TRY_TESTME ( IsEqual(UF48G4.GetT(),  t ));

#ifdef _DEBUG
   U48G4.Dump(rlog.GetLogContext());
#endif 

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(UF48G4) == true);

   //
   // Height,TopFlangeWidth,BottomFlangeWidth,AvgWebWidth
   //

   // Use some real dimensions (WSDOT UF60G5 girder)
   UBeam beam;
   beam.SetD1(60.00);
   beam.SetD2(6.00);
   beam.SetD3(6.00);
   beam.SetD4(4.50);
   beam.SetD5(1.50);
   beam.SetD6(4.50);
   beam.SetD7(1.50);
   beam.SetW1(60.00);
   beam.SetW2(85.43);
   beam.SetW3(12.00);
   beam.SetW4(3.00);
   beam.SetW5(5.00);
   beam.SetT(7.00);

   TRY_TESTME(IsEqual(beam.GetHeight(), 60.0));

   TRY_TESTME(beam.GetWebCount() == 2);
   TRY_TESTME(IsEqual(beam.GetSlope(0), -6.9993519118600096)); // not exactly 7 because W2 is rounded off
   TRY_TESTME(IsEqual(beam.GetSlope(1), 6.9993519118600096));
   TRY_TESTME(IsEqual(beam.GetWebSpacing(), 70.073363537414849));
   TRY_TESTME(IsEqual(beam.GetWebLocation(0), -35.036681768707425));
   TRY_TESTME(IsEqual(beam.GetWebLocation(1), 35.036681768707425));

   TRY_TESTME(IsEqual(beam.GetTopWidth(), 85.43));
   TRY_TESTME(beam.GetTopFlangeCount() == 2);
   TRY_TESTME(IsEqual(beam.GetTopFlangeLocation(0), -35.179459546485205));
   TRY_TESTME(IsEqual(beam.GetTopFlangeLocation(1),  35.179459546485205));
   TRY_TESTME(IsEqual(beam.GetTopFlangeWidth(0), 15.071080907029602));
   TRY_TESTME(IsEqual(beam.GetTopFlangeWidth(1), 15.071080907029602));

   TRY_TESTME(beam.GetBottomFlangeCount() == 1);
   TRY_TESTME(IsEqual(beam.GetBottomFlangeLocation(0), 0.0));
   TRY_TESTME(IsEqual(beam.GetBottomFlangeWidth(0), 60.0));
   TRY_TESTME(IsEqual(beam.GetBottomWidth(), 60.0));

   //
   // Bounding Box
   //
   Rect2d box = beam.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), -42.715));
   TRY_TESTME(IsEqual(box.Right(), 42.715));
   TRY_TESTME(IsEqual(box.Top(), 60.00));
   TRY_TESTME(IsEqual(box.Bottom(), 0.00));

   //
   // ShapeProperties
   //
   ShapeProperties props = beam.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), 1279.67674));
   TRY_TESTME(IsEqual(props.GetIxx(), 519561.213035));
   TRY_TESTME(IsEqual(props.GetIyy(), 999211.50319));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 24.73653));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetXleft(), 42.715));
   TRY_TESTME(IsEqual(props.GetXright(), 42.715));
   TRY_TESTME(IsEqual(props.GetYtop(), 60.0 - props.GetCentroid().Y()));
   TRY_TESTME(IsEqual(props.GetYbottom(), props.GetCentroid().Y()));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(beam.GetPerimeter(), 371.35986));

   //
   // FurthestDistance
   //
   Point2d p1(0, 20);
   Point2d p2(100, 20);
   Line2d line(p1, p2);

   // Shape on right
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 20.000));

   // shape on left
   p1.Move(0, -20);
   p2.Move(100, -20);
   line.ThroughPoints(p1, p2);
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -20.000));

   // 
   // PolyPoints
   //
   auto points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 21);
   int i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-30.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-37.715000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(-42.715000, 55.500000));
   TRY_TESTME(points[i++] == Point2d(-42.715000, 60.000000));
   TRY_TESTME(points[i++] == Point2d(-27.643919, 60.000000));
   TRY_TESTME(points[i++] == Point2d(-27.643919, 55.500000));
   TRY_TESTME(points[i++] == Point2d(-30.643919, 54.000000));
   TRY_TESTME(points[i++] == Point2d(-24.643364, 12.000000));
   TRY_TESTME(points[i++] == Point2d(-12.643364, 6.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 6.000000));
   TRY_TESTME(points[i++] == Point2d(12.643364, 6.000000));
   TRY_TESTME(points[i++] == Point2d(24.643364, 12.000000));
   TRY_TESTME(points[i++] == Point2d(30.643919, 54.000000));
   TRY_TESTME(points[i++] == Point2d(27.643919, 55.500000));
   TRY_TESTME(points[i++] == Point2d(27.643919, 60.000000));
   TRY_TESTME(points[i++] == Point2d(42.715000, 60.000000));
   TRY_TESTME(points[i++] == Point2d(42.715000, 55.500000));
   TRY_TESTME(points[i++] == Point2d(37.715000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(30.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(i == points.size());

   //
   // PointInShape
   //
   Point2d pnt(0, 0.5);
   TRY_TESTME(beam.PointInShape(pnt) == true);

   pnt.Move(500, 500);
   TRY_TESTME(beam.PointInShape(pnt) == false);

   pnt.Move(0, 0); // Point on perimeter
   TRY_TESTME(beam.PointInShape(pnt) == false);

   //
   // ClipWithLine
   //

   // setup clipping line
   p1.Move(-50, 0.50);
   p2.Move(50, 0.50);
   Line2d clipLine(p1, p2);

   auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   TRY_TESTME(clip != nullptr);

   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 6);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-30.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-30.071435, 0.500000));
   TRY_TESTME(points[i++] == Point2d(30.071435, 0.500000));
   TRY_TESTME(points[i++] == Point2d(30.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(i == points.size());

   // clip in other direction
   p1.Move(50, 0.50);
   p2.Move(-50, 0.50);

   clipLine.ThroughPoints(p1, p2);

   clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   TRY_TESTME(clip != nullptr);

   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 19);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(-30.071435, 0.500000));
   TRY_TESTME(points[i++] == Point2d(-37.715000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(-42.715000, 55.500000));
   TRY_TESTME(points[i++] == Point2d(-42.715000, 60.000000));
   TRY_TESTME(points[i++] == Point2d(-27.643919, 60.000000));
   TRY_TESTME(points[i++] == Point2d(-27.643919, 55.500000));
   TRY_TESTME(points[i++] == Point2d(-30.643919, 54.000000));
   TRY_TESTME(points[i++] == Point2d(-24.643364, 12.000000));
   TRY_TESTME(points[i++] == Point2d(-12.643364, 6.000000));
   TRY_TESTME(points[i++] == Point2d(0.0, 6.000000));
   TRY_TESTME(points[i++] == Point2d(12.643364, 6.000000));
   TRY_TESTME(points[i++] == Point2d(24.643364, 12.000000));
   TRY_TESTME(points[i++] == Point2d(30.643919, 54.000000));
   TRY_TESTME(points[i++] == Point2d(27.643919, 55.500000));
   TRY_TESTME(points[i++] == Point2d(27.643919, 60.000000));
   TRY_TESTME(points[i++] == Point2d(42.715000, 60.000000));
   TRY_TESTME(points[i++] == Point2d(42.715000, 55.500000));
   TRY_TESTME(points[i++] == Point2d(37.715000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(30.071435, 0.500000));
   TRY_TESTME(i == points.size());

   //
   // ClipIn
   //
   Rect2d clipRect(-100, 0.5, 100, 0.6);
   clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(clip != nullptr);

   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 4);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(-30.071435, 0.500000));
   TRY_TESTME(points[i++] == Point2d(-30.085722, 0.600000));
   TRY_TESTME(points[i++] == Point2d(30.085722, 0.600000));
   TRY_TESTME(points[i++] == Point2d(30.071435, 0.500000));
   TRY_TESTME(i == points.size());

   //
   // MoveEx (tests Offset as well)
   //
   Point2d from(0, 0);
   Point2d to(100, 100);

   beam.Move(from, to);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 21);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(100.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(70.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(62.285000, 154.000000));
   TRY_TESTME(points[i++] == Point2d(57.285000, 155.500000));
   TRY_TESTME(points[i++] == Point2d(57.285000, 160.000000));
   TRY_TESTME(points[i++] == Point2d(72.356081, 160.000000));
   TRY_TESTME(points[i++] == Point2d(72.356081, 155.500000));
   TRY_TESTME(points[i++] == Point2d(69.356081, 154.000000));
   TRY_TESTME(points[i++] == Point2d(75.356636, 112.000000));
   TRY_TESTME(points[i++] == Point2d(87.356636, 106.000000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 106.000000));
   TRY_TESTME(points[i++] == Point2d(112.643364, 106.000000));
   TRY_TESTME(points[i++] == Point2d(124.643364, 112.000000));
   TRY_TESTME(points[i++] == Point2d(130.643919, 154.000000));
   TRY_TESTME(points[i++] == Point2d(127.643919, 155.500000));
   TRY_TESTME(points[i++] == Point2d(127.643919, 160.000000));
   TRY_TESTME(points[i++] == Point2d(142.715000, 160.000000));
   TRY_TESTME(points[i++] == Point2d(142.715000, 155.500000));
   TRY_TESTME(points[i++] == Point2d(137.715000, 154.000000));
   TRY_TESTME(points[i++] == Point2d(130.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 100.000000));
   TRY_TESTME(i == points.size());

   //
   // OffsetEx
   //
   Size2d size(-100, -100);
   beam.Offset(size);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 21);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-30.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-37.715000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(-42.715000, 55.500000));
   TRY_TESTME(points[i++] == Point2d(-42.715000, 60.000000));
   TRY_TESTME(points[i++] == Point2d(-27.643919, 60.000000));
   TRY_TESTME(points[i++] == Point2d(-27.643919, 55.500000));
   TRY_TESTME(points[i++] == Point2d(-30.643919, 54.000000));
   TRY_TESTME(points[i++] == Point2d(-24.643364, 12.000000));
   TRY_TESTME(points[i++] == Point2d(-12.643364, 6.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 6.000000));
   TRY_TESTME(points[i++] == Point2d(12.643364, 6.000000));
   TRY_TESTME(points[i++] == Point2d(24.643364, 12.000000));
   TRY_TESTME(points[i++] == Point2d(30.643919, 54.000000));
   TRY_TESTME(points[i++] == Point2d(27.643919, 55.500000));
   TRY_TESTME(points[i++] == Point2d(27.643919, 60.000000));
   TRY_TESTME(points[i++] == Point2d(42.715000, 60.000000));
   TRY_TESTME(points[i++] == Point2d(42.715000, 55.500000));
   TRY_TESTME(points[i++] == Point2d(37.715000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(30.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(i == points.size());

   //
   // LocatorPoint property
   //
   auto hookPnt = beam.GetHookPoint();

   // BottomLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(142.715, 100.0));

   // BottomCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   // BottomRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(57.285, 100.0));

   // CenterLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(142.715, 70.0));

   // CenterCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 70.0));

   // CenterRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(57.285, 70.0));

   // TopLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(142.715, 40.0));

   // TopCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 40.0));

   // TopRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(57.285, 40.0));

   // HookPoint
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::HookPoint, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::HookPoint);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   //
   // RotateEx (Provides coverage of Rotate)
   //
   hookPnt->Move(0, 0);
   Point2d c(0, 0);

   beam.Rotate(c, M_PI);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 21);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(30.000000, -0.000000));
   TRY_TESTME(points[i++] == Point2d(37.715000, -54.000000));
   TRY_TESTME(points[i++] == Point2d(42.715000, -55.500000));
   TRY_TESTME(points[i++] == Point2d(42.715000, -60.000000));
   TRY_TESTME(points[i++] == Point2d(27.643919, -60.000000));
   TRY_TESTME(points[i++] == Point2d(27.643919, -55.500000));
   TRY_TESTME(points[i++] == Point2d(30.643919, -54.000000));
   TRY_TESTME(points[i++] == Point2d(24.643364, -12.000000));
   TRY_TESTME(points[i++] == Point2d(12.643364, -6.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, -6.000000));
   TRY_TESTME(points[i++] == Point2d(-12.643364, -6.000000));
   TRY_TESTME(points[i++] == Point2d(-24.643364, -12.000000));
   TRY_TESTME(points[i++] == Point2d(-30.643919, -54.000000));
   TRY_TESTME(points[i++] == Point2d(-27.643919, -55.500000));
   TRY_TESTME(points[i++] == Point2d(-27.643919, -60.000000));
   TRY_TESTME(points[i++] == Point2d(-42.715000, -60.000000));
   TRY_TESTME(points[i++] == Point2d(-42.715000, -55.500000));
   TRY_TESTME(points[i++] == Point2d(-37.715000, -54.000000));
   TRY_TESTME(points[i++] == Point2d(-30.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(i == points.size());

   TESTME_EPILOG("UBeam");
}

#endif // _UNITTEST



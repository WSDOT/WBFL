///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2014  Washington State Department of Transportation
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
#include <GeomModel\UBeam.h>
#include <GeomModel\Properties.h>
#include <GeomModel\ShapeUtils.h>
#include <GeomModel\Polygon.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmUBeam
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////
//======================== LIFECYCLE  =======================================
gmUBeam::gmUBeam()
{
   Init();
}

gmUBeam::gmUBeam(Float64 w1, Float64 w2, Float64 w3,Float64 w4,Float64 w5,
                 Float64 d1, Float64 d2, Float64 d3,Float64 d4,Float64 d5,Float64 d6,Float64 d7,
                 Float64 t,
                 const gpPoint2d& hookPnt)
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

   Init();

   m_HookPoint = hookPnt;
   m_W1    = w1;
   m_W2    = w2;
   m_W3    = w3;
   m_W4    = w4;
   m_W5    = w5;
   m_D1    = d1;
   m_D2    = d2;
   m_D3    = d3;
   m_D4    = d4;
   m_D5    = d5;
   m_D6    = d6;
   m_D7    = d7;
   m_T     = t;

   UpdatePolygon();
}


gmUBeam::~gmUBeam()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

gpPoint2d gmUBeam::SetHookPoint(const gpPoint2d& hookPnt)
{
   gpPoint2d tmp = m_HookPoint;
   m_HookPoint = hookPnt;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

gpPoint2d gmUBeam::GetHookPoint() const
{
   return m_HookPoint;
}

Float64 gmUBeam::SetW1(Float64 w1)
{
   PRECONDITION(w1>0);
   Float64 tmp = m_W1;
   m_W1 = w1;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetW1() const
{
   return m_W1;
}

Float64 gmUBeam::SetW2(Float64 w2)
{
   PRECONDITION(w2>0);
   Float64 tmp = m_W2;
   m_W2 = w2;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetW2() const
{
   return m_W2;
}

Float64 gmUBeam::SetW3(Float64 w3)
{
   PRECONDITION(w3>=0);
   Float64 tmp = m_W3;
   m_W3 = w3;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetW3() const
{
   return m_W3;
}

Float64 gmUBeam::SetW4(Float64 w4)
{
   PRECONDITION(w4>=0);
   Float64 tmp = m_W4;
   m_W4 = w4;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetW4() const
{
   return m_W4;
}

Float64 gmUBeam::SetW5(Float64 w5)
{
   PRECONDITION(w5>0);
   Float64 tmp = m_W5;
   m_W5 = w5;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetW5() const
{
   return m_W5;
}

Float64 gmUBeam::SetD1(Float64 d1)
{
   PRECONDITION(d1>0);
   Float64 tmp = m_D1;
   m_D1 = d1;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetD1() const
{
   return m_D1;
}

Float64 gmUBeam::SetD2(Float64 d2)
{
   PRECONDITION(d2>0);
   Float64 tmp = m_D2;
   m_D2 = d2;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetD2() const
{
   return m_D2;
}

Float64 gmUBeam::SetD3(Float64 d3)
{
   PRECONDITION(d3>=0);
   Float64 tmp = m_D3;
   m_D3 = d3;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetD3() const
{
   return m_D3;
}

Float64 gmUBeam::SetD4(Float64 d4)
{
   PRECONDITION(d4>=0);
   Float64 tmp = m_D4;
   m_D4 = d4;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetD4() const
{
   return m_D4;
}

Float64 gmUBeam::SetD5(Float64 d5)
{
   PRECONDITION(d5>=0);
   Float64 tmp = m_D5;
   m_D5 = d5;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetD5() const
{
   return m_D5;
}

Float64 gmUBeam::SetD6(Float64 d6)
{
   PRECONDITION(d6>=0);
   Float64 tmp = m_D6;
   m_D6 = d6;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetD6() const
{
   return m_D6;
}

Float64 gmUBeam::SetD7(Float64 d7)
{
   PRECONDITION(d7>0);
   Float64 tmp = m_D7;
   m_D7 = d7;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetD7() const
{
   return m_D7;
}

Float64 gmUBeam::SetT(Float64 t)
{
   PRECONDITION(t>=0);
   Float64 tmp = m_T;
   m_T = t;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmUBeam::GetT() const
{
   return m_T;
}

Float64 gmUBeam::GetSlope(WebIndexType webIdx) const
{
   return (webIdx == 0 ? -1.0 : 1.0) * m_Slope;
}

Float64 gmUBeam::GetHeight() const
{
   return m_D1;
}

Float64 gmUBeam::GetTopFlangeWidth() const
{
   Float64 slope = GetSlope(1);
   Float64 t = m_T*sqrt(slope*slope + 1)/slope;

   return 2.0*(m_W4 + m_W5 + t);
}

Float64 gmUBeam::GetBottomFlangeWidth() const
{
   return m_W1;
}

Float64 gmUBeam::GetTopWidth() const
{
   return m_W2;
}

Int32 gmUBeam::GetNumberOfMatingSurfaces() const
{
   return 2;
}

Float64 gmUBeam::GetMatingSurfaceWidth(MatingSurfaceIndexType idx) const
{
   return GetTopFlangeWidth()/2;
}

Float64 gmUBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType idx) const
{
   Float64 sign = (idx == 0) ? -1 : 1;
   return sign*(GetTopWidth()/2 - GetTopFlangeWidth()/4);
}


void gmUBeam::GetWebPlane(WebIndexType webIdx,IPlane3d** ppPlane) const
{
   Float64 slope = GetSlope(webIdx);

   Float64 sign = (webIdx == 0 ? -1.0 : 1.0);

   IPlane3d* pPlane;
   ::CoCreateInstance(CLSID_Plane3d,NULL,CLSCTX_INPROC_SERVER,IID_IPlane3d,(void**)&pPlane);

   Float64 x, y, z;
   Float64 t = fabs((m_T/2)*(sqrt(slope*slope+1)/slope));
   x = 0;
   y = 0;
   z = sign*(m_W1/2 - t);
   IPoint3d* pP1;
   ::CoCreateInstance(CLSID_Point3d,NULL,CLSCTX_INPROC_SERVER,IID_IPoint3d,(void**)&pP1);
   pP1->Move(x,y,z);

   IPoint3d* pP2;
   ::CoCreateInstance(CLSID_Point3d,NULL,CLSCTX_INPROC_SERVER,IID_IPoint3d,(void**)&pP2);
   x = 100;
   y = 0;
   z = sign*(m_W1/2 - t);
   pP2->Move(x,y,z);

   IPoint3d* pP3;
   ::CoCreateInstance(CLSID_Point3d,NULL,CLSCTX_INPROC_SERVER,IID_IPoint3d,(void**)&pP3);
   x = 0;
   y = 100;
   z = sign*(m_W1/2 - t - y/slope);
   pP3->Move(x,y,z);

   pPlane->ThroughPoints(pP1,pP2,pP3);

   (*ppPlane) = pPlane;
   (*ppPlane)->AddRef();

   pPlane->Release();
   pP1->Release();
   pP2->Release();
   pP3->Release();
}

Float64 gmUBeam::GetShearWidth() const
{
   return GetMinWebWidth() * 2;
}

Float64 gmUBeam::GetMinWebWidth() const
{
   return m_T;
}

Float64 gmUBeam::GetMinBottomFlangeThickness() const
{
   return m_D2;
}

Float64 gmUBeam::GetMinTopFlangeThickness() const
{
   return _cpp_min(m_D4,m_D6);
}

void gmUBeam::GetProperties(gmProperties* pProperties) const
{
   ASSERTVALID;

   Float64 area, ixx, iyy, ixy, perimeter;
   gpPoint2d  cg;
   m_PolyImp.GetProperties(&area, &ixx, &iyy, &ixy, &cg);
   perimeter = m_PolyImp.Perimeter();

   // deal with signs and hollowness
   if( (area>0 && !IsSolid() || (area<0 && IsSolid())))
   {
      area *= -1;
      ixx  *= -1;
      iyy  *= -1;
      ixy  *= -1;
   }
   // bounding box in centroidal coords
   gpRect2d bb = m_PolyImp.GetBoundingBox();
   bb.Offset(-cg.X(), -cg.Y());

   *pProperties =  gmProperties(area , cg, ixx, iyy, ixy, 
                                bb.Top(),bb.Bottom(),bb.Left(),bb.Right(),
                                perimeter);
}

gpRect2d gmUBeam::GetBoundingBox() const
{
   return m_PolyImp.GetBoundingBox();
}

gmIShape* gmUBeam::CreateClone(bool bRegisterListeners) const
{
   std::auto_ptr<gmUBeam> ph(new gmUBeam( *this ));// no memory leaks if DoRegister() throws

   // copy listeners if requested.
   if (bRegisterListeners)
      ph->DoRegisterListeners(*this);

   return ph.release();
}

gmIShape* gmUBeam::CreateClippedShape(const gpLine2d& line, 
                                    gpLine2d::Side side) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(line,side);
}

gmIShape* gmUBeam::CreateClippedShape(const gpRect2d& r,
                                     gmShapeImp::ClipRegion region
                                     ) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(r, region);
}

Float64 gmUBeam::GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->GetFurthestDistance(line,side);
}

void gmUBeam::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   poly->Draw(hDC,mapper);
}

bool gmUBeam::Contains(const gpPoint2d& pnt) const
{
   return m_PolyImp.Contains(pnt);
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmUBeam::AssertValid() const
{
   if ( m_W1 < 0 || m_W2 < 0 || m_W3 < 0 || m_W4 < 0 ) return false;
   if ( m_D1 < 0 || m_D2 < 0 || m_D3 < 0 || m_D4 < 0 || m_D5 < 0 || m_D6 < 0 ) return false;
   if ( m_T  < 0)                          return false;

   return gmShapeImp::AssertValid();
}

void gmUBeam::Dump(dbgDumpContext& os) const
{
   os << _T("*** Dump for gmUBeam ***") <<endl;
   gmShapeImp::Dump( os );
   os << _T("  Hook Point      = (")<<m_HookPoint.X()<<_T(", ")<<m_HookPoint.Y()<<_T(")")<<endl;
   os << _T("  Rotation        =  ")<<m_Rotation<<endl;
   os << _T("  D1              =  ")<<m_D1 <<endl;
   os << _T("  D2              =  ")<<m_D2 <<endl;
   os << _T("  D3              =  ")<<m_D3 <<endl;
   os << _T("  D4              =  ")<<m_D4 <<endl;
   os << _T("  D5              =  ")<<m_D5 <<endl;
   os << _T("  D6              =  ")<<m_D6 <<endl;
   os << _T("  D7              =  ")<<m_D7 <<endl;
   os << _T("  W1              =  ")<<m_W1 <<endl;
   os << _T("  W2              =  ")<<m_W2 <<endl;
   os << _T("  W3              =  ")<<m_W3 <<endl;
   os << _T("  W4              =  ")<<m_W4 <<endl;
   os << _T("  W5              =  ")<<m_W5 <<endl;
   os << _T("  T               =  ")<<m_T  <<endl;
   os << _T("Polygon rep of beam") << endl;
   m_PolyImp.Dump( os );
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmUBeam::gmUBeam(const gmUBeam& rOther) :
gmIPrecastBeam(rOther)
{
   Init();
   MakeCopy(rOther);
}

gmUBeam& gmUBeam::operator= (const gmUBeam& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void gmUBeam::DoTranslate(const gpSize2d& delta)
{
   m_HookPoint.Offset(delta);
   UpdatePolygon();
}

void gmUBeam::DoRotate(const gpPoint2d& center, Float64 angle)
{
   m_Rotation += angle;
   m_HookPoint.Rotate(center, angle);
   UpdatePolygon();
}

void gmUBeam::MakeCopy(const gmUBeam& rOther)
{
   m_HookPoint = rOther.m_HookPoint;
   m_Rotation  = rOther.m_Rotation;
   m_W1        = rOther.m_W1;
   m_W2        = rOther.m_W2;
   m_W3        = rOther.m_W3;
   m_W4        = rOther.m_W4;
   m_W5        = rOther.m_W5;
   m_D1        = rOther.m_D1;
   m_D2        = rOther.m_D2;
   m_D3        = rOther.m_D3;
   m_D4        = rOther.m_D4;
   m_D5        = rOther.m_D5;
   m_D6        = rOther.m_D6;
   m_D7        = rOther.m_D7;
   m_T         = rOther.m_T;
   m_PolyImp   = rOther.m_PolyImp;
   m_Slope     = rOther.m_Slope;
}

void gmUBeam::MakeAssignment(const gmUBeam& rOther)
{
   gmShapeImp::MakeAssignment( rOther );
   MakeCopy( rOther );
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
gmPolygon* gmUBeam::CreatePolygon() const
{
   // make a polygon with same traits as this.
   std::auto_ptr<gmPolygon> ph(new gmPolygon(m_PolyImp));
   gmShapeUtils::CopyTraits(*this, ph.get());

   return ph.release();
}

//class SlopeFn : public mathFunction2d
//{
//public:
//   SlopeFn(const gmUBeam* pBeam)
//   {
//      T  = pBeam->GetT();
//      D1 = pBeam->GetD1();
//      D6 = pBeam->GetD6();
//      W1 = pBeam->GetW1();
//      W2 = pBeam->GetW2();
//      W4 = pBeam->GetW4();
//   }
//
//   Float64 Evaluate(Float64 x) const
//   {
//      return T*sqrt(x*x+1) + D6 + ((W2/2) - W4 - (W1)/2)*x - D1;
//   }
//
//private:
//   Float64 T, D1, D6, W1, W2, W4;
//};

void gmUBeam::UpdateSlope()
{
//   mathBrentsRootFinder2d rootfinder;
//   Float64 slope;
//   try
//   {
//      slope = rootfinder.FindRootInRange(SlopeFn(this),0,1000,0.00001);
//   }
//   catch(...)
//   {
//      slope = DBL_MAX;
//   }
//
//   m_Slope = slope;

   Float64 rise = m_D1 - m_D4 - m_D5;
   Float64 run = (m_W2 - m_W1)/2 - m_W5;

   if ( IsZero(run) )
      m_Slope = DBL_MAX;
   else
      m_Slope = rise/run;
}

void gmUBeam::UpdatePolygon()
{
   // clear the polygon implemenation and recalculate all of the points
   m_PolyImp.Clear();

   UpdateSlope();

   // start at the bottom center and go around clockwise
   // Hook point is at bottom center (0,0)
   // Compute left side points, mirror for right side
   Float64 slope = GetSlope(1);
   Float64 p1_x =  0.;
   Float64 p1_y =  0.;

   Float64 p2_x = -m_W1/2;
   Float64 p2_y =  0.;

   Float64 p3_x =  p2_x - (IsZero(slope) ? 0: (m_D1 - m_D4 - m_D5)/slope);
   Float64 p3_y =  m_D1 - m_D4 - m_D5;

   Float64 p4_x =  -m_W2/2;
   Float64 p4_y =  m_D1 - m_D4;

   Float64 p5_x =  -m_W2/2;
   Float64 p5_y =  m_D1;

   Float64 p6_x =  -m_W2/2 + m_W4 + m_W5 + (IsZero(slope) ? m_T : m_T*sqrt(slope*slope+1)/slope) + (IsZero(slope) ? 0 : (m_D6 + m_D7)/slope);
   Float64 p6_y =  m_D1;

   Float64 p7_x =  p6_x;
   Float64 p7_y =  m_D1 - m_D6;

   Float64 p8_x =  p7_x - m_W4;
   Float64 p8_y =  m_D1 - m_D6 - m_D7;

   Float64 p9_x =  p8_x + (IsZero(slope) ? 0 : (m_D1 - m_D2 - m_D3 - m_D6 - m_D7)/slope);
   Float64 p9_y =  m_D2 + m_D3;

   Float64 p10_x = p9_x + m_W3;
   Float64 p10_y = m_D2;

   m_PolyImp.AddPoint(gpPoint2d( p1_x, p1_y));  // 1
   m_PolyImp.AddPoint(gpPoint2d( p2_x, p2_y));
   m_PolyImp.AddPoint(gpPoint2d( p3_x, p3_y));
   m_PolyImp.AddPoint(gpPoint2d( p4_x, p4_y));
   m_PolyImp.AddPoint(gpPoint2d( p5_x, p5_y));
   m_PolyImp.AddPoint(gpPoint2d( p6_x, p6_y));
   m_PolyImp.AddPoint(gpPoint2d( p7_x, p7_y));
   m_PolyImp.AddPoint(gpPoint2d( p8_x, p8_y));
   m_PolyImp.AddPoint(gpPoint2d( p9_x, p9_y));
   m_PolyImp.AddPoint(gpPoint2d( p10_x, p10_y));

   // mirror points
   m_PolyImp.AddPoint(gpPoint2d(-p10_x, p10_y));
   m_PolyImp.AddPoint(gpPoint2d(-p9_x, p9_y));
   m_PolyImp.AddPoint(gpPoint2d(-p8_x, p8_y));
   m_PolyImp.AddPoint(gpPoint2d(-p7_x, p7_y));
   m_PolyImp.AddPoint(gpPoint2d(-p6_x, p6_y)); 
   m_PolyImp.AddPoint(gpPoint2d(-p5_x, p5_y));
   m_PolyImp.AddPoint(gpPoint2d(-p4_x, p4_y));
   m_PolyImp.AddPoint(gpPoint2d(-p3_x, p3_y));
   m_PolyImp.AddPoint(gpPoint2d(-p2_x, p2_y));

   if (!IsZero(m_Rotation))
      m_PolyImp.Rotate(gpPoint2d(0,0), m_Rotation);

   if (!( IsZero(m_HookPoint.X())&&IsZero(m_HookPoint.Y()) ))
   m_PolyImp.Offset(m_HookPoint);
}


void gmUBeam::Init()
{
   m_HookPoint = gpPoint2d(0,0);
   m_Rotation  = 0;
   m_W1        = 0;
   m_W2        = 0;
   m_W3        = 0;
   m_W4        = 0;
   m_W5        = 0;
   m_D1        = 0;
   m_D2        = 0;
   m_D3        = 0;
   m_D4        = 0;
   m_D5        = 0;
   m_D6        = 0;
   m_D7        = 0;
   m_T         = 0;
   m_PolyImp.Clear();
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST

bool gmUBeam::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmUBeam");

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

   gmUBeam U48G4(w1,w2,w3,w4,w5,d1,d2,d3,d4,d5,d6,d7,t,gpPoint2d());
   gmProperties aprops;
   U48G4.GetProperties(&aprops);
   TRY_TESTME (U48G4.GetBoundingBox() == gpRect2d(-30.857142857143,0.0,30.857142857143,48.)) ;
   TRY_TESTME ( IsEqual(aprops.Area(), 953.9697)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  208841.6, 0.1)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), 18.29891)) ;
   TRY_TESTME ( IsEqual(U48G4.GetHeight(), 48.0)) ;
   TRY_TESTME ( IsEqual(U48G4.GetTopFlangeWidth(), 14.14213563)) ;
   TRY_TESTME ( IsEqual(U48G4.GetBottomFlangeWidth(), 48.0)) ;
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

   gmUBeam UF48G4(w1,w2,w3,w4,w5,d1,d2,d3,d4,d5,d6,d7,t,gpPoint2d());
   UF48G4.GetProperties(&aprops);
   TRY_TESTME (UF48G4.GetBoundingBox() == gpRect2d(-35,0.0,35,48.)) ;
   TRY_TESTME ( IsEqual(aprops.Area(), 1109.9696961966997)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  279004.31125131005)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), 20.911030677927876)) ;
   TRY_TESTME ( IsEqual(UF48G4.GetHeight(), 48.0)) ;
   TRY_TESTME ( IsEqual(UF48G4.GetTopFlangeWidth(), 30.142135623731)) ;
   TRY_TESTME ( IsEqual(UF48G4.GetBottomFlangeWidth(), 48.0)) ;
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
   U48G4.Dump(rlog.GetDumpCtx());
#endif 

   TESTME_EPILOG("gmUBeam");
}

#endif // _UNITTEST



///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2015  Washington State Department of Transportation
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
#include <GeomModel\PrecastBeam.h>
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
   gmPrecastBeam
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////
//======================== LIFECYCLE  =======================================
gmPrecastBeam::gmPrecastBeam()
{
   Init();
}

gmPrecastBeam::gmPrecastBeam(Float64 w1, Float64 w2, Float64 w3, Float64 w4,
                 Float64 d1, Float64 d2, Float64 d3,
                 Float64 d4, Float64 d5, Float64 d6,
                 Float64 d7,
                 Float64 t1, Float64 t2,
                 const gpPoint2d& hookPnt)
{
   PRECONDITION(w1>=0);
   PRECONDITION(w2>=0);
   PRECONDITION(w3>=0);
   PRECONDITION(w4>=0);
   PRECONDITION(d1>=0);
   PRECONDITION(d2>=0);
   PRECONDITION(d3>=0);
   PRECONDITION(d4>=0);
   PRECONDITION(d5>=0);
   PRECONDITION(d6>=0);
   PRECONDITION(d7>=0);
   PRECONDITION(t1>=0);
   PRECONDITION(t2>=0);

   Init();

   m_HookPoint = hookPnt;
   m_W1=w1;
   m_W2=w2;
   m_W3=w3;
   m_W4=w4;
   m_D1=d1;
   m_D2=d2;
   m_D3=d3;
   m_D4=d4;
   m_D5=d5;
   m_D6=d6;
   m_D7=d7;
   m_T1=t1;
   m_T2=t2;

   UpdatePolygon();
}


gmPrecastBeam::~gmPrecastBeam()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

gpPoint2d gmPrecastBeam::SetHookPoint(const gpPoint2d& hookPnt)
{
   gpPoint2d tmp = m_HookPoint;
   m_HookPoint = hookPnt;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

gpPoint2d gmPrecastBeam::GetHookPoint() const
{
   return m_HookPoint;
}

Float64 gmPrecastBeam::SetW1(Float64 w1)
{
   PRECONDITION(w1>=0);
   Float64 tmp = m_W1;
   m_W1 = w1;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetW1() const
{
   return m_W1;
}

Float64 gmPrecastBeam::SetW2(Float64 w2)
{
   PRECONDITION(w2>=0);
   Float64 tmp = m_W2;
   m_W2 = w2;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetW2() const
{
   return m_W2;
}
Float64 gmPrecastBeam::SetW3(Float64 w3)
{
   PRECONDITION(w3>=0);
   Float64 tmp = m_W3;
   m_W3 = w3;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetW3() const
{
   return m_W3;
}

Float64 gmPrecastBeam::SetW4(Float64 w4)
{
   PRECONDITION(w4>=0);
   Float64 tmp = m_W4;
   m_W4 = w4;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetW4() const
{
   return m_W4;
}

Float64 gmPrecastBeam::SetD1(Float64 d1)
{
   PRECONDITION(d1>=0);
   Float64 tmp = m_D1;
   m_D1 = d1;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetD1() const
{
   return m_D1;
}

Float64 gmPrecastBeam::SetD2(Float64 d2)
{
   PRECONDITION(d2>=0);
   Float64 tmp = m_D2;
   m_D2 = d2;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetD2() const
{
   return m_D2;
}

Float64 gmPrecastBeam::SetD3(Float64 d3)
{
   PRECONDITION(d3>=0);
   Float64 tmp = m_D3;
   m_D3 = d3;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetD3() const
{
   return m_D3;
}

Float64 gmPrecastBeam::SetD4(Float64 d4)
{
   PRECONDITION(d4>=0);
   Float64 tmp = m_D4;
   m_D4 = d4;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetD4() const
{
   return m_D4;
}

Float64 gmPrecastBeam::SetD5(Float64 d5)
{
   PRECONDITION(d5>=0);
   Float64 tmp = m_D5;
   m_D5 = d5;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetD5() const
{
   return m_D5;
}

Float64 gmPrecastBeam::SetD6(Float64 d6)
{
   PRECONDITION(d6>=0);
   Float64 tmp = m_D6;
   m_D6 = d6;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetD6() const
{
   return m_D6;
}

Float64 gmPrecastBeam::SetD7(Float64 d7)
{
   PRECONDITION(d7>=0);
   Float64 tmp = m_D7;
   m_D7 = d7;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetD7() const
{
   return m_D7;
}

Float64 gmPrecastBeam::SetT1(Float64 t1)
{
   PRECONDITION(t1>=0);
   Float64 tmp = m_T1;
   m_T1 = t1;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetT1() const
{
   return m_T1;
}

Float64 gmPrecastBeam::SetT2(Float64 t2)
{
   PRECONDITION(t2>=0);
   Float64 tmp = m_T2;
   m_T2 = t2;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmPrecastBeam::GetT2() const
{
   return m_T2;
}

Float64 gmPrecastBeam::GetHeight() const
{
   return m_D1+m_D2+m_D3+m_D7+m_D6+m_D5+m_D4;
}

Float64 gmPrecastBeam::GetTopFlangeWidth() const
{
   return m_T1 + 2.*(m_W1+m_W2);
}

Float64 gmPrecastBeam::GetBottomFlangeWidth() const
{
   return m_T2 + 2.*(m_W3+m_W4);
}

Float64 gmPrecastBeam::GetTopWidth() const
{
   return GetTopFlangeWidth();
}

MatingSurfaceIndexType gmPrecastBeam::GetNumberOfMatingSurfaces() const
{
   return 1;
}

Float64 gmPrecastBeam::GetMatingSurfaceWidth(MatingSurfaceIndexType idx) const
{
   return GetTopFlangeWidth();
}

Float64 gmPrecastBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType idx) const
{
   return 0;
}

void gmPrecastBeam::GetWebPlane(WebIndexType webIdx,IPlane3d** ppPlane) const
{
   IPlane3d* pPlane;
   ::CoCreateInstance(CLSID_Plane3d,NULL,CLSCTX_INPROC_SERVER,IID_IPlane3d,(void**)&pPlane);

   IPoint2d* pP1;
   ::CoCreateInstance(CLSID_Point2d,NULL,CLSCTX_INPROC_SERVER,IID_IPoint2d,(void**)&pP1);
   pP1->Move(0,0);

   IPoint2d* pP2;
   ::CoCreateInstance(CLSID_Point2d,NULL,CLSCTX_INPROC_SERVER,IID_IPoint2d,(void**)&pP2);
   pP2->Move(100,0);

   ILine2d* pLine;
   ::CoCreateInstance(CLSID_Line2d,NULL,CLSCTX_INPROC_SERVER,IID_ILine2d,(void**)&pLine);
   pLine->ThroughPoints(pP1,pP2);

   IPoint3d* pP3;
   ::CoCreateInstance(CLSID_Point3d,NULL,CLSCTX_INPROC_SERVER,IID_IPoint3d,(void**)&pP3);
   pP3->Move(0,100,0);

   pPlane->ThroughLineEx(pLine,pP3);

   (*ppPlane) = pPlane;
   (*ppPlane)->AddRef();

   pPlane->Release();
   pP1->Release();
   pP2->Release();
   pP3->Release();
   pLine->Release();
}

Float64 gmPrecastBeam::GetShearWidth() const
{
   return GetMinWebWidth();
}

Float64 gmPrecastBeam::GetMinWebWidth() const
{
   return _cpp_min(m_T1,m_T2);
}

Float64 gmPrecastBeam::GetMinBottomFlangeThickness() const
{
   return m_D4;
}

Float64 gmPrecastBeam::GetMinTopFlangeThickness() const
{
   return m_D1;
}

void gmPrecastBeam::GetProperties(gmProperties* pProperties) const
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

gpRect2d gmPrecastBeam::GetBoundingBox() const
{
   return m_PolyImp.GetBoundingBox();
}

gmIShape* gmPrecastBeam::CreateClone(bool bRegisterListeners) const
{
   std::auto_ptr<gmPrecastBeam> ph(new gmPrecastBeam( *this ));// no memory leaks if DoRegister() throws

   // copy listeners if requested.
   if (bRegisterListeners)
      ph->DoRegisterListeners(*this);

   return ph.release();
}

gmIShape* gmPrecastBeam::CreateClippedShape(const gpLine2d& line, 
                                    gpLine2d::Side side) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(line,side);
}

gmIShape* gmPrecastBeam::CreateClippedShape(const gpRect2d& r,
                                     gmShapeImp::ClipRegion region
                                     ) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(r, region);
}

Float64 gmPrecastBeam::GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->GetFurthestDistance(line,side);
}

void gmPrecastBeam::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   poly->Draw(hDC,mapper);
}

bool gmPrecastBeam::Contains(const gpPoint2d& pnt) const
{
   return m_PolyImp.Contains(pnt);
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmPrecastBeam::AssertValid() const
{
   if ( m_W1<0 || m_W2<0 || m_W3<0 || m_W4<0 || m_D1<0 )return false;
   if ( m_D2<0 || m_D3<0 || m_D4<0 || m_D5<0 || m_D6<0 )return false;
   if ( m_D7<0 || m_T1<0 || m_T2<0) return false;

   return gmShapeImp::AssertValid();
}

void gmPrecastBeam::Dump(dbgDumpContext& os) const
{
   os << _T("*** Dump for gmPrecastBeam ***")<<endl;
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
   os << _T("  T1              =  ")<<m_T1 <<endl;
   os << _T("  T2              =  ")<<m_T2 <<endl;
   os << _T("Polygon rep of beam") << endl;
   m_PolyImp.Dump( os );
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmPrecastBeam::gmPrecastBeam(const gmPrecastBeam& rOther) :
gmIPrecastBeam(rOther)
{
   Init();
   MakeCopy(rOther);
}

gmPrecastBeam& gmPrecastBeam::operator= (const gmPrecastBeam& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void gmPrecastBeam::DoTranslate(const gpSize2d& delta)
{
   m_HookPoint.Offset(delta);
   UpdatePolygon();
}

void gmPrecastBeam::DoRotate(const gpPoint2d& center, Float64 angle)
{
   m_Rotation += angle;
   m_HookPoint.Rotate(center, angle);
   UpdatePolygon();
}

void gmPrecastBeam::MakeCopy(const gmPrecastBeam& rOther)
{
   m_HookPoint = rOther.m_HookPoint;
   m_Rotation  = rOther.m_Rotation;
   m_W1        = rOther.m_W1;
   m_W2        = rOther.m_W2;
   m_W3        = rOther.m_W3;
   m_W4        = rOther.m_W4;
   m_D1        = rOther.m_D1;
   m_D2        = rOther.m_D2;
   m_D3        = rOther.m_D3;
   m_D4        = rOther.m_D4;
   m_D5        = rOther.m_D5;
   m_D6        = rOther.m_D6;
   m_D7        = rOther.m_D7;
   m_T1        = rOther.m_T1;
   m_T2        = rOther.m_T2;
   m_PolyImp   = rOther.m_PolyImp;
}

void gmPrecastBeam::MakeAssignment(const gmPrecastBeam& rOther)
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
gmPolygon* gmPrecastBeam::CreatePolygon() const
{
   // make a polygon with same traits as this.
   std::auto_ptr<gmPolygon> ph(new gmPolygon(m_PolyImp));
   gmShapeUtils::CopyTraits(*this, ph.get());

   return ph.release();
}

void gmPrecastBeam::UpdatePolygon()
{
   // clear the polygon implemenation and recalculate all of the points
   m_PolyImp.Clear();

   // start at top center and go around counter-clockwise
   // there are 19 points total. point 1 is top center. point 10 is bottom
   // center. 
   Float64 p1_x =  0.;
   Float64 p1_y =  0.;
   Float64 p2_x = -m_T1/2-m_W2-m_W1;
   Float64 p2_y =  0.;
   Float64 p3_x =  p2_x;
   Float64 p3_y = -m_D1;
   Float64 p4_x = -m_T1/2-m_W2;
   Float64 p4_y = -m_D1-m_D2;
   Float64 p5_x = -m_T1/2;
   Float64 p5_y = -m_D1-m_D2-m_D3;
   Float64 p6_x = -m_T2/2;
   Float64 p6_y = -m_D1-m_D2-m_D3-m_D7;
   Float64 p7_x = -m_T2/2-m_W4;
   Float64 p7_y = -m_D1-m_D2-m_D3-m_D7-m_D6;
   Float64 p8_x = -m_T2/2-m_W4-m_W3;
   Float64 p8_y = -m_D1-m_D2-m_D3-m_D7-m_D6-m_D5;
   Float64 p9_x =  p8_x;
   Float64 p9_y =  -m_D1-m_D2-m_D3-m_D7-m_D6-m_D5-m_D4;

   m_PolyImp.AddPoint(gpPoint2d( p1_x, p1_y));  // 1
   m_PolyImp.AddPoint(gpPoint2d( p2_x, p2_y));
   m_PolyImp.AddPoint(gpPoint2d( p3_x, p3_y));
   m_PolyImp.AddPoint(gpPoint2d( p4_x, p4_y));
   m_PolyImp.AddPoint(gpPoint2d( p5_x, p5_y));  // 5
   m_PolyImp.AddPoint(gpPoint2d( p6_x, p6_y));
   m_PolyImp.AddPoint(gpPoint2d( p7_x, p7_y));
   m_PolyImp.AddPoint(gpPoint2d( p8_x, p8_y));
   m_PolyImp.AddPoint(gpPoint2d( p9_x, p9_y));
   m_PolyImp.AddPoint(gpPoint2d(    0, p9_y));  // 10
   m_PolyImp.AddPoint(gpPoint2d(-p9_x, p9_y));
   m_PolyImp.AddPoint(gpPoint2d(-p8_x, p8_y));
   m_PolyImp.AddPoint(gpPoint2d(-p7_x, p7_y));
   m_PolyImp.AddPoint(gpPoint2d(-p6_x, p6_y));
   m_PolyImp.AddPoint(gpPoint2d(-p5_x, p5_y));  // 15
   m_PolyImp.AddPoint(gpPoint2d(-p4_x, p4_y));
   m_PolyImp.AddPoint(gpPoint2d(-p3_x, p3_y));
   m_PolyImp.AddPoint(gpPoint2d(-p2_x, p2_y));
   m_PolyImp.AddPoint(gpPoint2d(-p1_x, p1_y));  // 19

   if (!IsZero(m_Rotation))
      m_PolyImp.Rotate(gpPoint2d(0,0), m_Rotation);

   if (!( IsZero(m_HookPoint.X())&&IsZero(m_HookPoint.Y()) ))
   m_PolyImp.Offset(m_HookPoint);
}


void gmPrecastBeam::Init()
{
   m_HookPoint = gpPoint2d(0,0);
   m_Rotation=0;
   m_W1=0;
   m_W2=0;
   m_W3=0;
   m_W4=0;
   m_D1=0;
   m_D2=0;
   m_D3=0;
   m_D4=0;
   m_D5=0;
   m_D6=0;
   m_D7=0;
   m_T1=0;
   m_T2=0;
   m_PolyImp.Clear();
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST

bool gmPrecastBeam::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmPrecastBeam");

   // let's try a w74g
   Float64 t1 = 6.;
   Float64 t2 = 6.;
   Float64 w1 = 16.5;
   Float64 w2 = 2.;
   Float64 w3 = 9.5;
   Float64 w4 = 0.;
   Float64 d1 = 2.875;
   Float64 d2 = 2.625;
   Float64 d3 = 2.;
   Float64 d4 = 6.;
   Float64 d5 = 3.;
   Float64 d6 = 0.;
   Float64 d7 = 73.5-d1-d2-d3-d4-d5-d6;

   gmPrecastBeam w74g(w1,w2,w3,w4,d1,d2,d3,d4,d5,d6,d7,t1,t2,gpPoint2d());
   gmProperties aprops;
   w74g.GetProperties(&aprops);
   TRY_TESTME (w74g.GetBoundingBox() == gpRect2d(-21.5,-73.5,21.5,0.)) ;
   TRY_TESTME ( IsEqual(aprops.Area(), 747.7  ,1.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  547384., 1000.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.     ,100.)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.     ,.1)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), -35.5   ,.1)) ;
   TRY_TESTME ( IsEqual(w74g.GetHeight(), 73.5)) ;
   TRY_TESTME ( IsEqual(w74g.GetTopFlangeWidth(), 43.0)) ;
   TRY_TESTME ( IsEqual(w74g.GetBottomFlangeWidth(), 25.0)) ;
   TRY_TESTME ( IsEqual(w74g.GetT1(), 6.)) ;
   TRY_TESTME ( IsEqual(w74g.GetT2(), 6.)) ;
   TRY_TESTME ( IsEqual(w74g.GetW1(), 16.5)) ;
   TRY_TESTME ( IsEqual(w74g.GetW2(), 2.)) ;
   TRY_TESTME ( IsEqual(w74g.GetW3(), 9.5)) ;
   TRY_TESTME ( IsEqual(w74g.GetW4(), 0.)) ;
   TRY_TESTME ( IsEqual(w74g.GetD1(), 2.875)) ;
   TRY_TESTME ( IsEqual(w74g.GetD2(), 2.625)) ;
   TRY_TESTME ( IsEqual(w74g.GetD3(), 2.)) ;
   TRY_TESTME ( IsEqual(w74g.GetD4(), 6.)) ;
   TRY_TESTME ( IsEqual(w74g.GetD5(), 3.)) ;
   TRY_TESTME ( IsEqual(w74g.GetD6(), 0.)) ;

   // Turn our w74g into a w58g
   w74g.SetT1(6.);
   w74g.SetT2(6.);
   w74g.SetW1(9.5);
   w74g.SetW2(0.);
   w74g.SetW3(9.5);
   w74g.SetW4(0.);
   w74g.SetD1(5.);
   w74g.SetD2(2.);
   w74g.SetD3(0.);
   w74g.SetD4(6.);
   w74g.SetD5(3.);
   w74g.SetD6(0.);
   w74g.SetD7(58.-w74g.GetD1()-w74g.GetD2()-w74g.GetD3()-w74g.GetD4()-w74g.GetD5()-w74g.GetD6());
   w74g.GetProperties(&aprops);
   TRY_TESTME (w74g.GetBoundingBox() == gpRect2d(-12.5,-58.,12.5,0.)) ;
   TRY_TESTME ( IsEqual(aprops.Area(), 604.5  ,1.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  265357., 1000.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.     ,100.)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.     ,.1)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), -30.04   ,.1)) ;
   TRY_TESTME ( IsEqual(w74g.GetHeight(), 58.)) ;
   TRY_TESTME ( IsEqual(w74g.GetTopFlangeWidth(), 25.0)) ;
   TRY_TESTME ( IsEqual(w74g.GetBottomFlangeWidth(), 25.0)) ;

#ifdef _DEBUG
   w74g.Dump(rlog.GetDumpCtx());
#endif 

   TESTME_EPILOG("gmPrecastBeam");
}

#endif // _UNITTEST



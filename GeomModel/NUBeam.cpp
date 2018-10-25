///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2017  Washington State Department of Transportation
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
#include <GeomModel\NUBeam.h>
#include <GeomModel\Properties.h>
#include <GeomModel\ShapeUtils.h>
#include <GeomModel\Polygon.h>
#include <MathEx.h>
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmNUBeam
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////
//======================== LIFECYCLE  =======================================
gmNUBeam::gmNUBeam()
{
   Init();
}

gmNUBeam::gmNUBeam(Float64 w1, Float64 w2, 
                   Float64 d1, Float64 d2, Float64 d3, Float64 d4, Float64 d5,
                   Float64 t, 
                   Float64 r1, Float64 r2, Float64 r3, Float64 r4,
                   const gpPoint2d& hookPnt)

{
   Init();

   m_HookPoint = hookPnt;
   m_W1 = w1;
   m_W2 = w2;
   m_D1 = d1;
   m_D2 = d2;
   m_D3 = d3;
   m_D4 = d4;
   m_D5 = d5;
   m_T  = t;
   m_R1 = r1;
   m_R2 = r2;
   m_R3 = r3;
   m_R4 = r4;

   UpdatePolygon();
}


gmNUBeam::~gmNUBeam()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

gpPoint2d gmNUBeam::SetHookPoint(const gpPoint2d& hookPnt)
{
   gpPoint2d tmp = m_HookPoint;
   m_HookPoint = hookPnt;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

gpPoint2d gmNUBeam::GetHookPoint() const
{
   return m_HookPoint;
}

Float64 gmNUBeam::SetW1(Float64 w1)
{
   PRECONDITION(w1>=0);
   Float64 tmp = m_W1;
   m_W1 = w1;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetW1() const
{
   return m_W1;
}

Float64 gmNUBeam::SetW2(Float64 w2)
{
   PRECONDITION(w2>=0);
   Float64 tmp = m_W2;
   m_W2 = w2;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetW2() const
{
   return m_W2;
}

Float64 gmNUBeam::SetD1(Float64 d1)
{
   PRECONDITION(d1>=0);
   Float64 tmp = m_D1;
   m_D1 = d1;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetD1() const
{
   return m_D1;
}

Float64 gmNUBeam::SetD2(Float64 d2)
{
   PRECONDITION(d2>=0);
   Float64 tmp = m_D2;
   m_D2 = d2;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetD2() const
{
   return m_D2;
}

Float64 gmNUBeam::SetD3(Float64 d3)
{
   PRECONDITION(d3>=0);
   Float64 tmp = m_D3;
   m_D3 = d3;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetD3() const
{
   return m_D3;
}

Float64 gmNUBeam::SetD4(Float64 d4)
{
   PRECONDITION(d4>=0);
   Float64 tmp = m_D4;
   m_D4 = d4;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetD4() const
{
   return m_D4;
}

Float64 gmNUBeam::SetD5(Float64 d5)
{
   PRECONDITION(d5>=0);
   Float64 tmp = m_D5;
   m_D5 = d5;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetD5() const
{
   return m_D5;
}

Float64 gmNUBeam::SetT(Float64 t)
{
   PRECONDITION(t>=0);
   Float64 tmp = m_T;
   m_T = t;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetT() const
{
   return m_T;
}

Float64 gmNUBeam::SetR1(Float64 r1)
{
   PRECONDITION(r1>=0);
   Float64 tmp = m_R1;
   m_R1 = r1;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetR1() const
{
   return m_R1;
}

Float64 gmNUBeam::SetR2(Float64 r2)
{
   PRECONDITION(r2>=0);
   Float64 tmp = m_R2;
   m_R2 = r2;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetR2() const
{
   return m_R2;
}

Float64 gmNUBeam::SetR3(Float64 r3)
{
   PRECONDITION(r3>=0);
   Float64 tmp = m_R3;
   m_R3 = r3;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetR3() const
{
   return m_R3;
}

Float64 gmNUBeam::SetR4(Float64 r4)
{
   PRECONDITION(r4>=0);
   Float64 tmp = m_R4;
   m_R4 = r4;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmNUBeam::GetR4() const
{
   return m_R4;
}

Float64 gmNUBeam::GetHeight() const
{
   return m_D1 + m_D2 + m_D3 + m_D4 + m_D5;
}

Float64 gmNUBeam::GetTopFlangeWidth() const
{
   return m_W1;
}

Float64 gmNUBeam::GetBottomFlangeWidth() const
{
   return m_W2;
}

Float64 gmNUBeam::GetTopWidth() const
{
   return GetTopFlangeWidth();
}

MatingSurfaceIndexType gmNUBeam::GetNumberOfMatingSurfaces() const
{
   return 1;
}

Float64 gmNUBeam::GetMatingSurfaceWidth(MatingSurfaceIndexType idx) const
{
   return GetTopFlangeWidth();
}

Float64 gmNUBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType idx) const
{
   return 0;
}

void gmNUBeam::GetWebPlane(WebIndexType webIdx,IPlane3d** ppPlane) const
{
   IPlane3d* pPlane;
   ::CoCreateInstance(CLSID_Plane3d,nullptr,CLSCTX_INPROC_SERVER,IID_IPlane3d,(void**)&pPlane);

   IPoint2d* pP1;
   ::CoCreateInstance(CLSID_Point2d,nullptr,CLSCTX_INPROC_SERVER,IID_IPoint2d,(void**)&pP1);
   pP1->Move(0,0);

   IPoint2d* pP2;
   ::CoCreateInstance(CLSID_Point2d,nullptr,CLSCTX_INPROC_SERVER,IID_IPoint2d,(void**)&pP2);
   pP2->Move(100,0);

   ILine2d* pLine;
   ::CoCreateInstance(CLSID_Line2d,nullptr,CLSCTX_INPROC_SERVER,IID_ILine2d,(void**)&pLine);
   pLine->ThroughPoints(pP1,pP2);

   IPoint3d* pP3;
   ::CoCreateInstance(CLSID_Point3d,nullptr,CLSCTX_INPROC_SERVER,IID_IPoint3d,(void**)&pP3);
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

Float64 gmNUBeam::GetShearWidth() const
{
   return GetMinWebWidth();
}

Float64 gmNUBeam::GetMinWebWidth() const
{
   return m_T;
}

Float64 gmNUBeam::GetMinBottomFlangeThickness() const
{
   return m_D5;
}

Float64 gmNUBeam::GetMinTopFlangeThickness() const
{
   return m_D1;
}

void gmNUBeam::GetProperties(gmProperties* pProperties) const
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

gpRect2d gmNUBeam::GetBoundingBox() const
{
   return m_PolyImp.GetBoundingBox();
}

gmIShape* gmNUBeam::CreateClone(bool bRegisterListeners) const
{
   std::unique_ptr<gmNUBeam> ph(new gmNUBeam( *this ));// no memory leaks if DoRegister() throws

   // copy listeners if requested.
   if (bRegisterListeners)
      ph->DoRegisterListeners(*this);

   return ph.release();
}

gmIShape* gmNUBeam::CreateClippedShape(const gpLine2d& line, 
                                    gpLine2d::Side side) const
{
   // make shape into a gmpolygon and use its clip
   std::unique_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(line,side);
}

gmIShape* gmNUBeam::CreateClippedShape(const gpRect2d& r,
                                     gmShapeImp::ClipRegion region
                                     ) const
{
   // make shape into a gmpolygon and use its clip
   std::unique_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(r, region);
}

Float64 gmNUBeam::GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const
{
   // make shape into a gmpolygon and use its clip
   std::unique_ptr<gmPolygon> poly(CreatePolygon());
   return poly->GetFurthestDistance(line,side);
}

void gmNUBeam::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   std::unique_ptr<gmPolygon> poly(CreatePolygon());
   poly->Draw(hDC,mapper);
}

bool gmNUBeam::Contains(const gpPoint2d& pnt) const
{
   return m_PolyImp.Contains(pnt);
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmNUBeam::AssertValid() const
{
//   if ( m_W1<0 || m_W2<0 || m_W3<0 || m_W4<0 || m_D1<0 )return false;
//   if ( m_D2<0 || m_D3<0 || m_D4<0 || m_D5<0 || m_D6<0 )return false;
//   if ( m_D7<0 || m_T1<0 || m_T2<0) return false;

   return gmShapeImp::AssertValid();
}

void gmNUBeam::Dump(dbgDumpContext& os) const
{
   os << _T("*** Dump for gmNUBeam ***") <<endl;
//   gmShapeImp::Dump( os );
//   os << "  Hook Point      = ("<<m_HookPoint.X()<<", "<<m_HookPoint.Y()<<")"<<endl;
//   os << "  Rotation        =  "<<m_Rotation<<endl;
//   os << "  D1              =  "<<m_D1 <<endl;
//   os << "  D2              =  "<<m_D2 <<endl;
//   os << "  D3              =  "<<m_D3 <<endl;
//   os << "  D4              =  "<<m_D4 <<endl;
//   os << "  D5              =  "<<m_D5 <<endl;
//   os << "  D6              =  "<<m_D6 <<endl;
//   os << "  D7              =  "<<m_D7 <<endl;
//   os << "  W1              =  "<<m_W1 <<endl;
//   os << "  W2              =  "<<m_W2 <<endl;
//   os << "  W3              =  "<<m_W3 <<endl;
//   os << "  W4              =  "<<m_W4 <<endl;
//   os << "  T1              =  "<<m_T1 <<endl;
//   os << "  T2              =  "<<m_T2 <<endl;
//   os << "Polygon rep of beam" << endl;
//   m_PolyImp.Dump( os );
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmNUBeam::gmNUBeam(const gmNUBeam& rOther) :
gmIPrecastBeam(rOther)
{
   Init();
   MakeCopy(rOther);
}

gmNUBeam& gmNUBeam::operator= (const gmNUBeam& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void gmNUBeam::DoTranslate(const gpSize2d& delta)
{
   m_HookPoint.Offset(delta);
   UpdatePolygon();
}

void gmNUBeam::DoRotate(const gpPoint2d& center, Float64 angle)
{
   m_Rotation += angle;
   m_HookPoint.Rotate(center, angle);
   UpdatePolygon();
}

void gmNUBeam::MakeCopy(const gmNUBeam& rOther)
{
   m_HookPoint = rOther.m_HookPoint;
   m_Rotation  = rOther.m_Rotation;
   m_W1        = rOther.m_W1;
   m_W2        = rOther.m_W2;
   m_D1        = rOther.m_D1;
   m_D2        = rOther.m_D2;
   m_D3        = rOther.m_D3;
   m_D4        = rOther.m_D4;
   m_D5        = rOther.m_D5;
   m_T         = rOther.m_T;
   m_R1        = rOther.m_R1;
   m_R2        = rOther.m_R2;
   m_R3        = rOther.m_R3;
   m_R4        = rOther.m_R4;
   m_PolyImp   = rOther.m_PolyImp;
}

void gmNUBeam::MakeAssignment(const gmNUBeam& rOther)
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
gmPolygon* gmNUBeam::CreatePolygon() const
{
   // make a polygon with same traits as this.
   std::unique_ptr<gmPolygon> ph(std::make_unique<gmPolygon>(m_PolyImp));
   gmShapeUtils::CopyTraits(*this, ph.get());

   return ph.release();
}

void gmNUBeam::UpdatePolygon()
{
   // clear the polygon implemenation and recalculate all of the points
   m_PolyImp.Clear();

   const Int32 nSpaces = 20; // number of spaces to approximate curved fillets
   Float64 cx,cy;            // center of arc
   Float64 delta;            // sweep angle of arc
   Float64 startAngle;       // start angle for generating points along arch

   // Start at the lower left cornder of the shape
   m_PolyImp.AddPoint(gpPoint2d( -m_W2/2, 0.0) );

   // compute angle of bottom flange (measured from vertical)
   delta = atan2( (m_W2-m_T)/2, m_D4 );

   // generate lower left fillet
   cx = -m_W2/2 + m_R4;
   cy = m_D5 - m_R4*tan(delta/2);
   startAngle = M_PI;
   GenerateFillet(&m_PolyImp,cx,cy,m_R4,startAngle,-delta,nSpaces);

   // generate bottom left flange-web fillet
   cx = -m_T/2 - m_R2;
   cy = m_D5 + m_D4 + m_R2*tan(delta/2);
   startAngle = TWO_PI - delta;
   GenerateFillet(&m_PolyImp,cx,cy,m_R2,startAngle,delta,nSpaces);

   // compute angle of top flange (measured from vertical)
   delta = atan2( (m_W1-m_T)/2, m_D2 );

   // generate top left flange-web fillet
   cx = -m_T/2 - m_R1;
   cy = m_D5 + m_D4 + m_D3 - m_R1*tan(delta/2);
   startAngle = 0.0;
   GenerateFillet(&m_PolyImp,cx,cy,m_R1,startAngle,delta,nSpaces);

   // generate top flange left fillet
   cx = -m_W1/2 + m_R3;
   cy = m_D5 + m_D4 + m_D3 + m_D2 + m_R3*tan(delta/2);
   startAngle = M_PI + delta;
   GenerateFillet(&m_PolyImp,cx,cy,m_R3,startAngle,-delta,nSpaces);

   // extreme points on top flange
   m_PolyImp.AddPoint(gpPoint2d(-m_W1/2,m_D5 + m_D4 + m_D3 + m_D2 + m_D1));
   m_PolyImp.AddPoint(gpPoint2d( m_W1/2,m_D5 + m_D4 + m_D3 + m_D2 + m_D1));

   // generate top flange right fillet
   cx = m_W1/2 - m_R3;
   cy = m_D5 + m_D4 + m_D3 + m_D2 + m_R3*tan(delta/2);
   startAngle = 0;
   GenerateFillet(&m_PolyImp,cx,cy,m_R3,startAngle,-delta,nSpaces);

   // generate top right flange-web fillet
   cx = m_T/2 + m_R1;
   cy = m_D5 + m_D4 + m_D3 - m_R1*tan(delta/2);
   startAngle = M_PI - delta;
   GenerateFillet(&m_PolyImp,cx,cy,m_R1,startAngle,delta,nSpaces);

   // compute angle of bottom flange (measured from vertical)
   delta = atan2( (m_W2-m_T)/2, m_D4 );

   // generate bottom right flange-web fillet
   cx = m_T/2 + m_R2;
   cy = m_D5 + m_D4 + m_R2*tan(delta/2);
   startAngle = M_PI;
   GenerateFillet(&m_PolyImp,cx,cy,m_R2,startAngle,delta,nSpaces);

   // generate bottom flange right fillet
   cx = m_W2/2 - m_R4;
   cy = m_D5 - m_R4*tan(delta/2);
   startAngle = delta;
   GenerateFillet(&m_PolyImp,cx,cy,m_R4,startAngle,-delta,nSpaces);

   // bottom right point
   m_PolyImp.AddPoint(gpPoint2d(m_W2/2,0.0));

   if (!IsZero(m_Rotation))
      m_PolyImp.Rotate(gpPoint2d(0,0), m_Rotation);

   if (!( IsZero(m_HookPoint.X())&&IsZero(m_HookPoint.Y()) ))
      m_PolyImp.Offset(m_HookPoint);
}


void gmNUBeam::Init()
{
   m_HookPoint = gpPoint2d(0,0);
   m_Rotation = 0;
   m_W1 = 0;
   m_W2 = 0;
   m_D1 = 0;
   m_D2 = 0;
   m_D3 = 0;
   m_D4 = 0;
   m_D5 = 0;
   m_T  = 0;
   m_R1 = 0;
   m_R2 = 0;
   m_R3 = 0;
   m_R4 = 0;
   m_PolyImp.Clear();
}

void gmNUBeam::GenerateFillet(gpPolygon2d* pShape,Float64 cx,Float64 cy,Float64 r,Float64 startAngle,Float64 delta,Int32 nSpaces)
{
   Float64 dAngle = delta/nSpaces;
   for ( Int32 i = 0; i <= nSpaces; i++ )
   {
      Float64 x = cx + r*cos(startAngle + i*dAngle);
      Float64 y = cy + r*sin(startAngle + i*dAngle);

      pShape->AddPoint(gpPoint2d(x,y));
   }
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST

bool gmNUBeam::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmNUBeam");

   // let's try a NU4200
   Float64 t  = 150;
   Float64 w1 = 1225;
   Float64 w2 = 975;
   Float64 d1 = 65;
   Float64 d2 = 45;
   Float64 d3 = 2015;
   Float64 d4 = 140;
   Float64 d5 = 135;
   Float64 r1 = 200;
   Float64 r2 = 200;
   Float64 r3 = 50;
   Float64 r4 = 50;

   gmNUBeam nu4200(w1,w2,d1,d2,d3,d4,d5,t,r1,r2,r3,r4,gpPoint2d());
   gmProperties aprops;
   nu4200.GetProperties(&aprops);
   TRY_TESTME (nu4200.GetBoundingBox() == gpRect2d(-612.5,0,612.5,2400.)) ;
   TRY_TESTME ( IsEqual(aprops.Area(), 643591.88418736, 1.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  514253978920.25, 1.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.     , 1.)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.     ,.1)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), 1093.1459162077   ,.1)) ;
   TRY_TESTME ( IsEqual(nu4200.GetHeight(), 2400.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetTopFlangeWidth(), 1225.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetBottomFlangeWidth(), 975.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetT(),  150.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetW1(), 1225.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetW2(), 975.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetD1(), 65.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetD2(), 45.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetD3(), 2015.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetD4(), 140.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetD5(), 135.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetR1(), 200.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetR2(), 200.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetR3(), 50.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetR4(), 50.)) ;


#ifdef _DEBUG
   nu4200.Dump(rlog.GetDumpCtx());
#endif 

   TESTME_EPILOG("gmNUBeam");
}

#endif // _UNITTEST



///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2011  Washington State Department of Transportation
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
#include <GeomModel\Rectangle.h>
#include <GeomModel\Properties.h>
#include <GeomModel\ShapeUtils.h>
#include <EngTools\MohrCircle.h>
#include <math.h>
#include <mathEx.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmRectangle
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmRectangle::gmRectangle()
{
   Init();
}

gmRectangle::gmRectangle(const gpPoint2d& hookPnt,Float64 w,Float64 h)
{
   PRECONDITION(w>=0);
   PRECONDITION(h>=0);
   Init();
   m_HookPoint = hookPnt;
   m_Height    = h;
   m_Width     = w;
}


gmRectangle::~gmRectangle()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

gpPoint2d gmRectangle::SetHookPoint(const gpPoint2d& hookPnt)
{
   gpPoint2d tmp = m_HookPoint;
   m_HookPoint = hookPnt;
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

gpPoint2d gmRectangle::GetHookPoint() const
{
   return m_HookPoint;
}

Float64 gmRectangle::SetWidth(Float64 w)
{
   PRECONDITION(w>=0);
   Float64 tmp = m_Width;
   if (m_Width != w)
   {
   m_Width = w;
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   }
   return tmp;
}

Float64 gmRectangle::GetWidth() const
{
   return m_Width;
}

Float64 gmRectangle::SetHeight(Float64 h)
{
   PRECONDITION(h>=0);
   Float64 tmp = m_Height;
   if (m_Height != h)
   {
   m_Height = h;
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   }
   return tmp;
}

Float64 gmRectangle::GetHeight() const
{
   return m_Height;
}

void gmRectangle::GetProperties(gmProperties* pProperties) const
{
   Compute();
   *pProperties = m_Properties;
}

void gmRectangle::GetArea(Float64* pArea, gpPoint2d* pCG) const
   {
   Compute();
   *pArea = m_Properties.Area();
   if( (*pArea>0 && !IsSolid()) || (*pArea<0 && IsSolid()) )
   {
      *pArea *= -1;
   }

   *pCG   = m_Properties.Centroid();
}

gpRect2d gmRectangle::GetBoundingBox() const
{
   Compute();

   // get bb from properties in centroidal coords
   gpRect2d bb(m_Properties.Xleft(),m_Properties.Ybottom(),m_Properties.Xright(),m_Properties.Ytop());
   return bb.Offset(m_HookPoint.X(), m_HookPoint.Y());
}

gmIShape* gmRectangle::CreateClone(bool bRegisterListeners) const
{
   std::auto_ptr<gmRectangle> ph(new gmRectangle( *this ));// no memory leaks if DoRegister() throws

   // copy listeners if requested.
   if (bRegisterListeners)
      ph->DoRegisterListeners(*this);

   return ph.release();
}

gmIShape* gmRectangle::CreateClippedShape(const gpLine2d& line, 
                                    gpLine2d::Side side) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(line,side);
}

gmIShape* gmRectangle::CreateClippedShape(const gpRect2d& r,
                                     gmShapeImp::ClipRegion region
                                     ) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(r, region);
}

void gmRectangle::ComputeClippedArea(const gpLine2d& line, gpLine2d::Side side,
                                Float64* pArea, gpPoint2d* pCG) const
{
   Compute();

   // The definition of side is exactlly opposite for the gpPolygon2d class
   // than it is for gmIShape. For this reason, side must be reversed.
   gpLine2d::Side local_side = (side == gpLine2d::Left ? gpLine2d::Right : gpLine2d::Left); 

   std::auto_ptr<gpPolygon2d> pclipped( m_Poly.CreateClippedPolygon(line,local_side) );
   if (pclipped.get()!=0)
   {
      pclipped->GetArea(pArea, pCG);

      // deal with signs and hollowness
      if( (*pArea>0 && !IsSolid()) || (*pArea<0 && IsSolid()) )
      {
         *pArea *= -1;
      }
   }
   else
   {
      *pArea=0.0;
   }
}

Float64 gmRectangle::GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const
{
   Compute();
   return m_Poly.GetFurthestDistance(line,side);
}

void gmRectangle::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   if (poly.get()!=0)
      poly->Draw(hDC,mapper);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmRectangle::AssertValid() const
{
   if (m_Width<0) return false;
   if (m_Height<0) return false;
   return gmShapeImp::AssertValid();
}

void gmRectangle::Dump(dbgDumpContext& os) const
{
   os << _T("*** Dump for gmRectangle ***")<<endl;
   gmShapeImp::Dump( os );
   os << _T("  (Height, Width) = (")<<m_Height<<_T(", ")<<m_Width<<_T(")")<<endl;
   os << _T("  Hook Point      = (")<<m_HookPoint.X()<<_T(", ")<<m_HookPoint.Y()<<_T(")")<<endl;
   os << _T("  Rotation        =  ")<<m_Rotation<<endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmRectangle::gmRectangle(const gmRectangle& rOther) :
gmShapeImp(rOther)
{
   MakeCopy(rOther);
}

gmRectangle& gmRectangle::operator= (const gmRectangle& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmRectangle::NotifyAllListeners( Int32 lHint )
{
   // want to keep track if something has been changed
   if (lHint!=gmShapeListener::DISPLAY)
      m_Dirty = true;

   gmShapeImp::NotifyAllListeners(lHint);
}



void gmRectangle::DoTranslate(const gpSize2d& delta)
{
   m_HookPoint.Offset(delta);
}

void gmRectangle::DoRotate(const gpPoint2d& center, Float64 angle)
{
   m_Rotation += angle;
   m_HookPoint.Rotate(center, angle);
}

void gmRectangle::MakeCopy(const gmRectangle& rOther)
{
   m_Height    = rOther.m_Height;
   m_Width     = rOther.m_Width;
   m_HookPoint = rOther.m_HookPoint;
   m_Rotation  = rOther.m_Rotation;

   m_Dirty = true;
}

void gmRectangle::MakeAssignment(const gmRectangle& rOther)
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
gmPolygon* gmRectangle::CreatePolygon() const
{
   if (m_Width<=0 || m_Height<=0) return 0;

   Compute();

   // create shape and copy traits
   std::auto_ptr<gmPolygon> ph(new gmPolygon(m_Poly));
   gmShapeUtils::CopyTraits(*this, ph.get());
   return ph.release();
}

void gmRectangle::Init()
{
   m_Height    = 0.;
   m_Width     = 0.;
   m_Rotation  = 0.;
   m_HookPoint = gpPoint2d(0,0);
   m_Dirty     = true;
   m_Poly.Clear();
}

void gmRectangle::Compute() const
{
   if (m_Dirty)
   {
      // compute things we want to cache for later
      // Build our polygon rep
      m_Poly.Clear();
   Float64 cx = m_HookPoint.X();
   Float64 cy = m_HookPoint.Y();
      Float64 w2 = m_Width/2.;
      Float64 h2 = m_Height/2.;
   gpPoint2d br(cx-w2, cy-h2);
   gpPoint2d bl(cx+w2, cy-h2);
   gpPoint2d tr(cx+w2, cy+h2);
   gpPoint2d tl(cx-w2, cy+h2);

   // rotate points if needed
   if (m_Rotation!=0.)
   {
      br.Rotate(m_HookPoint, m_Rotation);
      bl.Rotate(m_HookPoint, m_Rotation);
      tr.Rotate(m_HookPoint, m_Rotation);
      tl.Rotate(m_HookPoint, m_Rotation);
   }

      m_Poly.AddPoint(br);
      m_Poly.AddPoint(bl);
      m_Poly.AddPoint(tr);
      m_Poly.AddPoint(tl);

      // properties
      // get non-rotated properties
      Float64 area = m_Height * m_Width;
      Float64 l_ixx = (m_Width * pow(m_Height,3))/ 12.;
      Float64 l_iyy = (m_Height * pow(m_Width,3))/ 12.;

      // rotate properties into correct orientation.
      Float64 ixx,iyy,ixy;
      etMohrCircle mc(l_ixx, l_iyy, 0.);
      mc.ComputeState(&ixx, &iyy, &ixy, m_Rotation);

      // deal with signs and hollowness
      if( (area>0 && !IsSolid()) || (area<0 && IsSolid()) )
{
         area *= -1;
         ixx  *= -1;
         iyy  *= -1;
         ixy  *= -1;
      }
      // bounding box in centroidal coords
      gpRect2d bb = m_Poly.GetBoundingBox();
      bb.Offset(-m_HookPoint.X(), -m_HookPoint.Y());

      // Compute perimeter
      Float64 perimeter;
      perimeter = 2.0*(m_Height + m_Width);

      m_Properties =  gmProperties(area , m_HookPoint, ixx, iyy, ixy, 
                                   bb.Top(),bb.Bottom(),bb.Left(),bb.Right(), perimeter);

      m_Dirty = false;
   }
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST

bool gmRectangle::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmRectangle");

   gmRectangle rt(gpPoint2d(1,2),2,4);
   TRY_TESTME( IsEqual(2., rt.GetWidth())) ;
   TRY_TESTME( IsEqual(4., rt.GetHeight())) ;
   TRY_TESTME( gpPoint2d(1,2) == rt.GetHookPoint()); 
   gmProperties aprops;
   rt.GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), 8.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  10.66, .1)) ;
   TRY_TESTME ( IsEqual(aprops.Iyy(),   2.66, .1)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),   0.00, .001)) ;
   TRY_TESTME ( rt.GetBoundingBox() == gpRect2d(0,0,2,4)) ;

   rt.SetHookPoint(gpPoint2d(0,0));
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(-1,-2,1,2)) ;
   rt.Move(gmIShape::CenterCenter, gpPoint2d(1,2));
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(0,0,2,4)) ;

   Float64 ang = atan(.5);
   Float64 dis = 2*cos(ang);
   rt.Rotate(gpPoint2d(0,0),ang);
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(-dis,0,dis,sqrt(20.))) ;
   rt.Rotate(gpPoint2d(0,0),-ang);

   // resize rectangle and clip it into a triangle
   rt.SetWidth(40);
   rt.SetHeight(50);
   rt.SetHookPoint(gpPoint2d(20,25));
   gpLine2d up_left(gpPoint2d(0,0), gpVector2d(gpSize2d(1,1)));
   gpLine2d up_rgt(gpPoint2d(40,0), gpVector2d(gpSize2d(-3,5)));
   std::auto_ptr<gmIShape> pfirst(rt.CreateClippedShape(up_left, gpLine2d::Left));
   std::auto_ptr<gmIShape> ptriang(pfirst->CreateClippedShape(up_rgt, gpLine2d::Right));
   ptriang->GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), 500.)) ;
   TRY_TESTME ( ptriang->GetBoundingBox() == gpRect2d(0,0,40,25)) ;

   pfirst->GetProperties(&aprops);
   Float64 area;
   gpPoint2d cg;
   rt.ComputeClippedArea(up_left, gpLine2d::Left, &area, &cg);
   TRY_TESTME(area==aprops.Area());
   TRY_TESTME(cg==aprops.Centroid());

#if defined _DEBUG
   rt.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gmRectangle");
}

#endif // _UNITTEST




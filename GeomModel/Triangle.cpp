///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2016  Washington State Department of Transportation
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
#include <GeomModel\Triangle.h>
#include <GeomModel\Polygon.h>
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
   gmTriangle
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

gmTriangle::gmTriangle()
{
   Init();
}

gmTriangle::gmTriangle(const gpPoint2d& hookPnt,Float64 h, Float64 w, Float64 c,
                       Float64 rotAngle)
{
   PRECONDITION(w>=0);
   PRECONDITION(h>=0);
   Init();
   m_HookPoint = hookPnt;
   m_Height    = h;
   m_Width     = w;
   m_Offset    = c;
   m_Rotation  = rotAngle;
}


gmTriangle::~gmTriangle()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

gpPoint2d gmTriangle::SetHookPoint(const gpPoint2d& hookPnt)
{
   gpPoint2d tmp = m_HookPoint;
   m_HookPoint = hookPnt;
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

gpPoint2d gmTriangle::GetHookPoint() const
{
   return m_HookPoint;
}

Float64 gmTriangle::SetWidth(Float64 w)
{
   PRECONDITION(w>=0);
   Float64 tmp = m_Width;
   m_Width = w;
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTriangle::GetWidth() const
{
   return m_Width;
}

Float64 gmTriangle::SetHeight(Float64 h)
{
   PRECONDITION(h>=0);
   Float64 tmp = m_Height;
   m_Height = h;
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTriangle::GetHeight() const
{
   return m_Height;
}

Float64 gmTriangle::SetOffset(Float64 c)
{
   Float64 tmp = m_Offset;
   m_Offset = c;
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTriangle::GetOffset() const
{
   return m_Offset;
}

Float64 gmTriangle::SetRotationAngle(Float64 rotAngle)
{
   Float64 tmp = m_Rotation;
   m_Rotation = rotAngle;
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTriangle::GetRotationAngle() const
{
   return m_Rotation;
}


void gmTriangle::GetProperties(gmProperties* pProperties) const
{
   // Simple triangles are easy to get properties of, but this is not necessarily
   // a simple triangle (consider m_Offset<0). 
   // Consult gpPolygon2d for the right answer.

   std::auto_ptr<gpPolygon2d> pgp(CreategpPolygon());

   Float64 area, ixx, iyy, ixy;
   gpPoint2d  cg;
   pgp->GetProperties(&area, &ixx, &iyy, &ixy, &cg);

   // deal with signs and hollowness
   if( (area>0 && !IsSolid()) || (area<0 && IsSolid()) )
   {
      area *= -1;
      ixx  *= -1;
      iyy  *= -1;
      ixy  *= -1;
   }
   // bounding box in centroidal coords
   gpRect2d bb = pgp->GetBoundingBox();
   bb.Offset(-cg.X(), -cg.Y());

   Float64 perimeter;
   perimeter = pgp->Perimeter();

   *pProperties =  gmProperties(area , cg, ixx, iyy, ixy, 
                                bb.Top(),bb.Bottom(),bb.Left(),bb.Right(),
                                perimeter);

}

gpRect2d gmTriangle::GetBoundingBox() const
{
   // again, simple triangles are easy, but...
   std::auto_ptr<gpPolygon2d> pgp(CreategpPolygon());

   return pgp->GetBoundingBox();
}

gmIShape* gmTriangle::CreateClone(bool bRegisterListeners) const
{
   std::auto_ptr<gmTriangle> ph(new gmTriangle( *this ));// no memory leaks if DoRegister() throws

   // copy listeners if requested.
   if (bRegisterListeners)
      ph->DoRegisterListeners(*this);

   return ph.release();
}

gmIShape* gmTriangle::CreateClippedShape(const gpLine2d& line, 
                                    gpLine2d::Side side) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(line,side);
}

gmIShape* gmTriangle::CreateClippedShape(const gpRect2d& r,
                                     gmShapeImp::ClipRegion region
                                     ) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(r, region);
}

Float64 gmTriangle::GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->GetFurthestDistance(line,side);
}

void gmTriangle::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   poly->Draw(hDC,mapper);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmTriangle::AssertValid() const
{
   if (m_Width<0) return false;
   if (m_Height<0) return false;
   return gmShapeImp::AssertValid();
}

void gmTriangle::Dump(dbgDumpContext& os) const
{
   os << _T("*** Dump for gmTriangle ***")<<endl;
   gmShapeImp::Dump( os );
   os << _T("  (Height, Width) = (")<<m_Height<<_T(", ")<<m_Width<<_T(")")<<endl;
   os << _T("  Hook Point      = (")<<m_HookPoint.X()<<_T(", ")<<m_HookPoint.Y()<<_T(")")<<endl;
   os << _T("  Offset          =  ")<<m_Offset<<endl;
   os << _T("  Rotation        =  ")<<m_Rotation<<endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmTriangle::gmTriangle(const gmTriangle& rOther) :
gmShapeImp(rOther)
{
   MakeCopy(rOther);
}

gmTriangle& gmTriangle::operator= (const gmTriangle& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void gmTriangle::DoTranslate(const gpSize2d& delta)
{
   m_HookPoint.Offset(delta);
}

void gmTriangle::DoRotate(const gpPoint2d& center, Float64 angle)
{
   m_Rotation += angle;
   m_HookPoint.Rotate(center, angle);
}


void gmTriangle::MakeCopy(const gmTriangle& rOther)
{
   m_Height    = rOther.m_Height;
   m_Width     = rOther.m_Width;
   m_Offset    = rOther.m_Offset;
   m_HookPoint = rOther.m_HookPoint;
   m_Rotation  = rOther.m_Rotation;
}

void gmTriangle::MakeAssignment(const gmTriangle& rOther)
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
gpPolygon2d* gmTriangle::CreategpPolygon() const
{
   if (m_Width<=0 || m_Height<=0) return 0;

   std::auto_ptr<gpPolygon2d> ph(new gpPolygon2d());

   // create polygon geometry
   gpPoint2d p1(0,0);
   gpPoint2d p2(m_Width,0);
   gpPoint2d p3(m_Offset,m_Height);

   ph->AddPoint(p1);
   ph->AddPoint(p2);
   ph->AddPoint(p3);

   // move to hookpoint coordinates
   ph->Offset(m_HookPoint.X(),m_HookPoint.Y());

   // rotate if needed
   if (m_Rotation!=0.)
      ph->Rotate(m_HookPoint, m_Rotation);

   return ph.release();
}

gmPolygon* gmTriangle::CreatePolygon() const
{
   std::auto_ptr<gpPolygon2d> pgp(CreategpPolygon());

   // make an empty polygon with same traits as this.
   std::auto_ptr<gmPolygon> ph(new gmPolygon(*pgp));
   gmShapeUtils::CopyTraits(*this, ph.get());

   return ph.release();
}

void gmTriangle::Init()
{
   m_Height    = 0.;
   m_Width     = 0.;
   m_Rotation  = 0.;
   m_Offset    = 0.;
   m_HookPoint = gpPoint2d(0,0);
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST

bool gmTriangle::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmTriangle");

   gmTriangle rt(gpPoint2d(1,2),4,2,1);
   TRY_TESTME( IsEqual(2., rt.GetWidth())) ;
   TRY_TESTME( IsEqual(4., rt.GetHeight())) ;
   TRY_TESTME( IsEqual(1., rt.GetOffset())) ;
   TRY_TESTME( gpPoint2d(1,2) == rt.GetHookPoint()); 
   gmProperties aprops;
   rt.GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), 4.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),   3.55, .1)) ;
   TRY_TESTME ( IsEqual(aprops.Iyy(),   0.67, .1)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),   0.00, .001)) ;
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(1,2,3,6)) ;

   rt.SetHookPoint(gpPoint2d(0,0));
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(0,0,2,4)) ;
   rt.Move(gmIShape::CenterCenter, gpPoint2d(0,0));
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(-1,-2,1,2)) ;

   Float64 ang = atan(.25);
   Float64 cosa = cos(ang);
   rt.SetHookPoint(gpPoint2d(0,0));
   rt.Rotate(gpPoint2d(0,0),ang);
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(0,0,2*cosa,4/cosa)) ;
   rt.SetRotationAngle(0);
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(0,0,2,4)) ;

#if defined _DEBUG
   rt.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gmTriangle");
}
#endif // _UNITTEST




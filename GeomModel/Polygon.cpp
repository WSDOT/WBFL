///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2013  Washington State Department of Transportation
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
#include <GeomModel\Polygon.h>
#include <GeomModel\Properties.h>
#include <GeomModel\ShapeUtils.h>
#include <GraphicsLib\PointMapper.h>
#include <mathex.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmPolygon
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmPolygon::gmPolygon() :
gmShapeImp()
{
   Init();
}

//------------------------------------------------------------------------
// Explicit constructor - construct from a gpPolygon2d
gmPolygon::gmPolygon(const gpPolygon2d& rp):
gmShapeImp(),
m_PolygonImp(rp)
{
   // WARNING: Don't call Init() here.  The initialization list above calls the copy
   //          c'tor for m_PolygonImp.  Init(), clears the points in the polygon.
   //          We obviously don't want this to happen since the whole point of this
   //          c'tor is the create a gmPolygon from a gpPolygon2d
   //Init();
}

gmPolygon::gmPolygon(const gmPolygon& rOther) :
gmShapeImp(rOther)
{
   Init();
   MakeCopy(rOther);
}

gmPolygon::~gmPolygon()
{
   Init();
}

//======================== OPERATORS  =======================================
gmPolygon& gmPolygon::operator= (const gmPolygon& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }
   return *this;
}

//======================== OPERATIONS =======================================

Uint32 gmPolygon::AddPoint(const gpPoint2d& p)
{
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return  m_PolygonImp.AddPoint(p);
}

void gmPolygon::Clear()
{
   m_PolygonImp.Clear();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
}

bool gmPolygon::RemovePoint(Uint32 key)
{
   if (m_PolygonImp.RemovePoint(key))
   {
      NotifyAllListeners(gmShapeListener::PROPERTIES);
      return true;
   }
   else
      return false;
}

const gpPoint2d* gmPolygon::GetPoint(Uint32 key) const
{
   return  m_PolygonImp.GetPoint(key);
}

CollectionIndexType gmPolygon::GetNumPoints() const
{
   return m_PolygonImp.GetNumPoints();
}

bool gmPolygon::ReplacePoint(Uint32 key,const gpPoint2d& p)
{
   if ( m_PolygonImp.ReplacePoint(key, p))
   {
      NotifyAllListeners(gmShapeListener::PROPERTIES);
      return true;
   }
   else
      return false;
}

void gmPolygon::GetProperties(gmProperties* pProperties) const
{

   Float64 area, ixx, iyy, ixy;
   gpPoint2d cg;

   m_PolygonImp.GetProperties(&area, &ixx, &iyy, &ixy, &cg);
   Float64 perimeter = m_PolygonImp.Perimeter();

   // deal with signs and hollowness
   if( (area>0 && !IsSolid()) || (area<0 && IsSolid()) )
   {
      area *= -1;
      ixx  *= -1;
      iyy  *= -1;
      ixy  *= -1;
   }

   gpRect2d bb = GetBoundingBox();
   bb.Offset(-cg.X(), -cg.Y());

   *pProperties = gmProperties(area , cg, ixx, iyy, ixy,
                               bb.Top(),bb.Bottom(),bb.Left(),bb.Right(),
                               perimeter);
}

void gmPolygon::GetArea(Float64* pArea, gpPoint2d* pCG) const
{
   m_PolygonImp.GetArea(pArea, pCG);

   if( (*pArea>0 && !IsSolid()) || (*pArea<0 && IsSolid()) )
   {
      *pArea *= -1;
   }
}


gpRect2d gmPolygon::GetBoundingBox() const
{
   return m_PolygonImp.GetBoundingBox();
}


gmIShape* gmPolygon::CreateClone(bool bRegisterListeners) const
{
   std::auto_ptr<gmPolygon> ph(new gmPolygon( *this ));// no memory leaks if DoRegister() throws

   // copy listeners if requested.
   if (bRegisterListeners)
      ph->DoRegisterListeners(*this);

   return ph.release();
}

gmIShape* gmPolygon::CreateClippedShape(const gpLine2d& line, gpLine2d::Side side) const
{
   // create a clipped polygon of this' polgonimp
   // The definition of side is exactlly opposite for the gpPolygon2d class
   // then it is for gmIShape. For this reason, side must be reversed.
   gpPolygon2d* pt = m_PolygonImp.CreateClippedPolygon(line,side == gpLine2d::Left ? gpLine2d::Right : gpLine2d::Left); 

   // if nothing there, return
   if (pt!=0)
   {
      std::auto_ptr<gpPolygon2d> pi(pt);
      // construct gmPolygon and copy this' traits to it
      std::auto_ptr<gmPolygon> ph(new gmPolygon( *pi ));
      gmShapeUtils::CopyTraits(*this, ph.get());
      return ph.release();
   }
   else
      return 0;
}

gmIShape* gmPolygon::CreateClippedShape(const gpRect2d& rect, gmShapeImp::ClipRegion region) const
{
   // convert enums
   gpPolygon2d::ClipRegion gpr;
   if (region==gmShapeImp::In)
      gpr=gpPolygon2d::In;
   else
      gpr=gpPolygon2d::Out;

   // create a clipped polygon of this' polgonimp
   std::auto_ptr<gpPolygon2d> pi( m_PolygonImp.CreateClippedPolygon(rect,gpr) );
   if (pi.get()!=0)
   {
      std::auto_ptr<gmPolygon> ph(new gmPolygon( *pi ));
      gmShapeUtils::CopyTraits(*this, ph.get());
      return ph.release();
   }
   else
      return 0;
}

void gmPolygon::ComputeClippedArea(const gpLine2d& line, gpLine2d::Side side,
                                Float64* pArea, gpPoint2d* pCG) const
{

   // The definition of side is exactlly opposite for the gpPolygon2d class
   // than it is for gmIShape. For this reason, side must be reversed.
   gpLine2d::Side local_side = (side == gpLine2d::Left ? gpLine2d::Right : gpLine2d::Left); 

   std::auto_ptr<gpPolygon2d> pclipped( m_PolygonImp.CreateClippedPolygon(line,local_side) );
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



Float64 gmPolygon::GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const
{
   return m_PolygonImp.GetFurthestDistance(line,side);
   
}

void gmPolygon::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   CollectionIndexType num_points = m_PolygonImp.GetNumPoints();
   if (num_points==0) return;

   POINT* device_points;
   
   // Setup pens and brushes

   HBRUSH brush     = ::CreateSolidBrush( this->GetFillColor() );
   HBRUSH old_brush = (HBRUSH)::SelectObject( hDC, brush );

   HPEN pen     = ::CreatePen( PS_SOLID, 1, this->GetBorderColor() );
   HPEN old_pen = (HPEN)::SelectObject( hDC, pen );


   device_points = new POINT[num_points+1];  // add one for closure point

   LONG point=0;
   gpPolyPointIter2d it(&(this->m_PolygonImp));
   for (it.Begin(); it; it.Next())
   {
      LONG dx,dy;

      const gpPoint2d* wp = it.CurrentPoint();
      mapper.WPtoDP(wp->X(),wp->Y(),&dx,&dy);
      device_points[point].x = dx;
      device_points[point].y = dy;
      point++;
   }

   device_points[num_points] = device_points[0]; // <<<< Force closure

   if (IsFillModeEnabled())
   {
      // ALTERNATE is the Windows default, I will set it here
      // anyway just incase someone decides to change the default.
      ::SetPolyFillMode(hDC,ALTERNATE);
      ::Polygon(hDC,device_points,(int)num_points+1);
   }
   else
   {
      ::Polyline(hDC,device_points,(int)num_points+1);
   }

   delete[] device_points;

   // Cleanup
   ::SelectObject( hDC, old_brush );
   ::DeleteObject( brush );
   ::SelectObject( hDC, old_pen );
   ::DeleteObject( pen );
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmPolygon::AssertValid() const
{
   // could add test for bowties here if a suitable algorithm can be found
   return gmShapeImp::AssertValid();
}

void gmPolygon::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for gmPolygon") << endl;
   m_PolygonImp.Dump(os);
   gmShapeImp::Dump( os );
}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void gmPolygon::DoTranslate(const gpSize2d& delta)
{
   m_PolygonImp.Offset(delta);
}

void gmPolygon::DoRotate(const gpPoint2d& center, Float64 angle)
{
   m_PolygonImp.Rotate(center,angle);
}

void gmPolygon::MakeCopy(const gmPolygon& rOther)
{
   m_PolygonImp = rOther.m_PolygonImp;
}

void gmPolygon::MakeAssignment(const gmPolygon& rOther)
{
   Init();

   gmShapeImp::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmPolygon::Init()
{
   m_PolygonImp.Clear();
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


/****************************************************************************
CLASS
   gmPolyPointIter
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmPolyPointIter::gmPolyPointIter()
{
   Init();
}

gmPolyPointIter::gmPolyPointIter(const gmPolygon* pPolygon)
{
   SetPolygon(pPolygon);
}


gmPolyPointIter::gmPolyPointIter(const gmPolyPointIter& rOther)
{
   Init();
   MakeCopy(rOther);
}

gmPolyPointIter::~gmPolyPointIter()
{
   Clean();
}

//======================== OPERATORS  =======================================
gmPolyPointIter& gmPolyPointIter::operator= (const gmPolyPointIter& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void gmPolyPointIter::SetPolygon(const gmPolygon* pPolygon)
{
   PRECONDITION(pPolygon!=0);
   m_pPolygon = pPolygon;
   m_Iterator.SetPolygon(&(pPolygon->m_PolygonImp));
}


void gmPolyPointIter::Begin()
{
   PRECONDITION(m_pPolygon!=0);
   m_Iterator.Begin();
}

void gmPolyPointIter::End()
{
   PRECONDITION(m_pPolygon!=0);
   m_Iterator.End();
}

void gmPolyPointIter::Next()
{
   PRECONDITION(m_pPolygon!=0);
   CHECK(m_Iterator);
   m_Iterator.Next();
}

void gmPolyPointIter::Prev()
{
   PRECONDITION(m_pPolygon!=0);
   m_Iterator.Prev();
}

gmPolyPointIter::operator void *() 
{
   if (m_pPolygon)
      return m_Iterator;
   else
      return 0;
}

// code duplication of above -- watch out!!
gmPolyPointIter::operator void *() const
{
   if (m_pPolygon)
      return m_Iterator;
   else
      return 0;
}

const gpPoint2d* gmPolyPointIter::CurrentPoint() const
{
   PRECONDITION(*this);
   return m_Iterator.CurrentPoint();
}

const Uint32* gmPolyPointIter::CurrentKey() const
{
   PRECONDITION(*this);
   return m_Iterator.CurrentKey();
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmPolyPointIter::AssertValid() const
{
   return true;
}

void gmPolyPointIter::Dump(dbgDumpContext& os) const
{
   os<< _T("Dump for gmPolyPointIter") <<endl;
   m_Iterator.Dump(os);
}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmPolyPointIter::MakeCopy(const gmPolyPointIter& rOther)
{
   m_pPolygon = rOther.m_pPolygon;
   m_Iterator = rOther.m_Iterator;
}

void gmPolyPointIter::MakeAssignment(const gmPolyPointIter& rOther)
{
   Clean();
   Init();

   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmPolyPointIter::Init()
{
   m_pPolygon = 0;
}

void gmPolyPointIter::Clean()
{
   // nothing to clean up.
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST

bool gmPolygon::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmPolygon");

   // create an angle shape. Taken from "Statics" 1st Ed. by J.L. Merriam, page 373

   gmPolygon anglep;
   Uint32 p1 = anglep.AddPoint(gpPoint2d(0 , 0));
   Uint32 p2 = anglep.AddPoint(gpPoint2d(0 ,50));
   Uint32 p3 = anglep.AddPoint(gpPoint2d(10,50));
   Uint32 p4 = anglep.AddPoint(gpPoint2d(10,10));
   Uint32 p5 = anglep.AddPoint(gpPoint2d(40,10));
   Uint32 p6 = anglep.AddPoint(gpPoint2d(40, 0));  // don't close polygon

   gmProperties aprops;
   anglep.GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), 800.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  181666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Iyy(),  101666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(), -75000., 10.)) ;
   TRY_TESTME (anglep.GetBoundingBox() == gpRect2d(0,0,40,50)) ;

   // test assignment
   gmPolygon anglec = anglep;
   anglec.GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), 800.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  181666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Iyy(),  101666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(), -75000., 10.)) ;
   TRY_TESTME (anglep.GetBoundingBox() == gpRect2d(0,0,40,50)) ;

   // try translation
   gpPoint2d center    = anglec.GetLocatorPoint(gmShapeImp::CenterCenter);
   TRY_TESTME (center == gpPoint2d(20,25)) ;
   gpPoint2d top_right = anglec.GetLocatorPoint(gmShapeImp::TopRight);
   TRY_TESTME (top_right == gpPoint2d(40,50)) ;

   anglec.Move(center, top_right);
   anglec.GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), 800.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  181666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Iyy(),  101666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(), -75000., 10.)) ;
   TRY_TESTME (anglec.GetBoundingBox() == gpRect2d(20,25,60,75)) ;

   // rotate to principal axes
   anglep.Rotate(center, -0.54105);
   anglep.GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), 800.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  226666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Iyy(),   56666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),     107., 10.)) ;

   // make hollow
   anglec.MakeSolid(false);
   anglec.GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), -800.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  -181666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Iyy(),  -101666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(), 75000., 10.)) ;
   TRY_TESTME (anglec.GetBoundingBox() == gpRect2d(20,25,60,75)) ;

   // make solid again and turn our angle into a rectangle
   anglec.MakeSolid(true);
   TRY_TESTME ( anglec.RemovePoint(p4) ) ;
   TRY_TESTME ( anglec.RemovePoint(p5) ) ;
   TRY_TESTME ( anglec.ReplacePoint(p3,gpPoint2d(60,75)) );
   anglec.GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), 2000.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  416666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Iyy(),  266666., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0., 1.)) ;
   TRY_TESTME (anglec.GetBoundingBox() == gpRect2d(20,25,60,75)) ;

   // create a line and find farthest point
   gpLine2d down_left(gpPoint2d(25,25), gpVector2d(gpSize2d(1,-1)));
   Float64 dist = anglec.GetFurthestDistance(down_left, gpLine2d::Left);
   TRY_TESTME ( IsEqual(60.1,dist,.1)) ;
   dist = anglec.GetFurthestDistance(down_left, gpLine2d::Right);
   TRY_TESTME ( IsEqual(3.53, dist, .01)) ;

   // create a rectangle and clip it into a triangle
   gmPolygon rect;
   p1 = rect.AddPoint(gpPoint2d(0 , 0));
   p2 = rect.AddPoint(gpPoint2d(0 ,50));
   p3 = rect.AddPoint(gpPoint2d(40,50));
   p4 = rect.AddPoint(gpPoint2d(40,0));
   gpLine2d up_left(gpPoint2d(0,0), gpVector2d(gpSize2d(1,1)));
   gpLine2d up_rgt(gpPoint2d(40,0), gpVector2d(gpSize2d(-3,5)));
   std::auto_ptr<gmIShape> pfirst(rect.CreateClippedShape(up_left, gpLine2d::Left));
   pfirst->GetProperties(&aprops);
   TRY_TESTME( IsEqual(aprops.Area(), 800.) );

   Float64 area;
   gpPoint2d cg;
   rect.ComputeClippedArea(up_left, gpLine2d::Left, &area, &cg);
   TRY_TESTME(area==aprops.Area());
   TRY_TESTME(cg==aprops.Centroid());

   std::auto_ptr<gmIShape> ptriang(pfirst->CreateClippedShape(up_rgt, gpLine2d::Right));
   ptriang->GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), 500.)) ;
   TRY_TESTME (ptriang->GetBoundingBox() == gpRect2d(0,0,40,25)) ;

   gmIShapeEx* exptr = dynamic_cast<gmIShapeEx*>(ptriang.get());
   exptr->ComputeClippedArea(up_rgt, gpLine2d::Right, &area, &cg);
   TRY_TESTME(area==aprops.Area());
   TRY_TESTME(cg==aprops.Centroid());

   // clip triangle into a right triangle
   gpRect2d clip_box(0,5,20,25);
   std::auto_ptr<gmIShape> prtri(ptriang->CreateClippedShape(clip_box, gmShapeImp::In));
   prtri->GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), 112.5)) ;
   TRY_TESTME (prtri->GetBoundingBox() == gpRect2d(5,5,20,20)) ;

#if defined _DEBUG
   prtri->Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gmPolygon");
}


bool gmPolyPointIter::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmPolyPointIter");

   // create a polygon and iterate through its points
   gmPolygon anglep;
   Uint32 p1 = anglep.AddPoint(gpPoint2d(0 , 0));
   Uint32 p2 = anglep.AddPoint(gpPoint2d(0 ,50));
   Uint32 p3 = anglep.AddPoint(gpPoint2d(10,50));
   Uint32 p4 = anglep.AddPoint(gpPoint2d(10,10));
   Uint32 p5 = anglep.AddPoint(gpPoint2d(40,10));
   Uint32 p6 = anglep.AddPoint(gpPoint2d(40, 0));

   gmPolyPointIter my_it(&anglep);
   Uint32 i = 0;
   for(my_it.Begin(); my_it; my_it.Next())
   {
      i++;
      if (i==3)
         TRY_TESTME ( p3 == *my_it.CurrentKey()) ;
      if (i==4)
         TRY_TESTME (gpPoint2d(10,10) == *my_it.CurrentPoint()) ;
      if (i==5)
         TRY_TESTME (p5 == *my_it.CurrentKey()) ;
   }

   my_it.Prev();
   TRY_TESTME (p6 == *my_it.CurrentKey()) ;

   TRY_TESTME ( anglep.RemovePoint(p4) ) ;
   TRY_TESTME ( anglep.RemovePoint(p5) ) ;
   TRY_TESTME ( anglep.ReplacePoint(p3,gpPoint2d(60,75)) );

   my_it.End();
   gmPolyPointIter new_it = my_it;
   new_it.Prev();
   new_it.Prev();
   TRY_TESTME (gpPoint2d(60,75) == *new_it.CurrentPoint()) ;

#if defined _DEBUG
   my_it.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gmPolyPointIter");
}

#endif // _UNITTEST



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
#include <GeomModel\CompositeShape.h>

#include <GeomModel\Properties.h>
#include <MathEx.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmCompositeShape
****************************************************************************/


//
// Create a phony class for composite testing
//
class gmTestShape : public gmShapeImp
{
public:
   gmTestShape(const gmProperties& prop):m_Props(prop){;}
   void GetProperties(gmProperties* pProps) const {*pProps=m_Props;}
   void Draw(HDC hDC, const grlibPointMapper& mapper)const{;}
   gmIShape* CreateClone(bool bRegisterListeners = false) const {return new gmTestShape(*this);}
   gmIShape* CreateClippedShape(const gpLine2d& line, 
                               gpLine2d::Side side) const {return new gmTestShape(*this);}
   gmIShape* CreateClippedShape(const gpRect2d& r,
                                gmShapeImp::ClipRegion region
                                ) const {return new gmTestShape(*this);}
   Float64 GetFurthestDistance(const gpLine2d& line,
                               gpLine2d::Side side) const {return 0;}
   void DoTranslate(const gpSize2d& delta) {}
   void DoRotate(const gpPoint2d& center, Float64 angle) {}
   virtual gpRect2d GetBoundingBox() const {return gpRect2d(
                                     m_Props.Xleft(),m_Props.Ybottom(),
                                     m_Props.Xright(),m_Props.Ytop());}
   bool operator==(const gmTestShape& rhs) const{return m_Props==rhs.m_Props;}
private:
   gmProperties m_Props;
};

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmCompositeShape::gmCompositeShape() :
gmShapeImp()
{
   Init();
}

gmCompositeShape::~gmCompositeShape()
{
   Clean();
}

//======================== OPERATORS  =======================================

//======================== OPERATIONS =======================================

gmIShape* gmCompositeShape::CreateClone(bool bRegisterListeners) const
{
   std::auto_ptr<gmCompositeShape> ph(new gmCompositeShape( *this ));// no memory leaks if DoRegister() throws

   // copy listeners if requested.
   if (bRegisterListeners)
      ph->DoRegisterListeners(*this);

   return ph.release();
}

void gmCompositeShape::GetProperties(gmProperties* pProperties) const
{
   gmProperties sum, tmp;
   // add up properties for all members of the composite
   for (ConstShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      (*it).second->GetProperties(&tmp);
      sum += tmp;
   }

   *pProperties = sum;
}

gpRect2d gmCompositeShape::GetBoundingBox() const
{
   gpRect2d tmp;
   bool first = true;
   for (ConstShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      if (first)
      {
         tmp = (*it).second->GetBoundingBox();
         first=false;
      }
      else
         tmp.Union((*it).second->GetBoundingBox());
   }

   return tmp;
}

gmIShape* gmCompositeShape::CreateClippedShape(const gpLine2d& line, gpLine2d::Side side
                            ) const
{
   std::auto_ptr<gmCompositeShape> pclipped(new gmCompositeShape());
   // cycle through all shapes and clip 'em
   for (ConstShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      std::auto_ptr<gmIShape> tmp((*it).second->CreateClippedShape(line, side));
      if(tmp.get())
         pclipped->AddShape(*tmp);
   }

   if (pclipped->GetNumShapes() > 0)
      return pclipped.release();
   else
      return 0;
}

gmIShape* gmCompositeShape::CreateClippedShape(const gpRect2d& r,
                             gmShapeImp::ClipRegion region
                            ) const
{
   std::auto_ptr<gmCompositeShape> pclipped(new gmCompositeShape());
   // cycle through all shapes and clip 'em
   for (ConstShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      std::auto_ptr<gmIShape> tmp((*it).second->CreateClippedShape(r, region));
      if(tmp.get())
         pclipped->AddShape(*tmp);
   }

   if (pclipped->GetNumShapes() > 0)
      return pclipped.release();
   else
      return 0;
}

void gmCompositeShape::MakeSolid(bool flag)
{
   BeginDamage();
   gmShapeImp::MakeSolid(flag);

   for (ShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      (*it).second->MakeSolid(flag);
   }
   EndDamage();

   NotifyAllListeners(gmShapeListener::PROPERTIES);
}


bool gmCompositeShape::EnableBorderMode(bool bEnable)
{
   bool tmp = IsBorderModeEnabled();
   BeginDamage();
   gmShapeImp::EnableBorderMode(bEnable);

   for (ShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      (*it).second->EnableBorderMode(bEnable);
   }
   EndDamage();

   NotifyAllListeners(gmShapeListener::DISPLAY);
   return tmp;
}

COLORREF gmCompositeShape::SetBorderColor(COLORREF color)
{
   COLORREF tmp = GetBorderColor();
   BeginDamage();
   gmShapeImp::SetBorderColor(color);

   for (ShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      (*it).second->SetBorderColor(color);
   }
   EndDamage();
   NotifyAllListeners(gmShapeListener::DISPLAY);
   return tmp;
}

bool gmCompositeShape::EnableFillMode(bool bEnable)
{
   bool tmp = IsFillModeEnabled();
   BeginDamage();
   gmShapeImp::EnableFillMode(bEnable);

   for (ShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      (*it).second->EnableFillMode(bEnable);
   }
   EndDamage();

   NotifyAllListeners(gmShapeListener::DISPLAY);
   return tmp;
}

COLORREF gmCompositeShape::SetFillColor(COLORREF color)
{
   COLORREF tmp = GetFillColor();
   BeginDamage();
   gmShapeImp::SetFillColor(color);

   for (ShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      (*it).second->SetFillColor(color);
   }
   EndDamage();

   NotifyAllListeners(gmShapeListener::DISPLAY);
   return tmp;
}


void gmCompositeShape::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   for (ConstShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      (*it).second->Draw(hDC, mapper);
   }
}

Uint32 gmCompositeShape::AddShape(const gmIShape& rShape, bool bRegisterListeners)
{
   m_LastKey++;
   ShapePtr tmp(rShape.CreateClone(bRegisterListeners));
   tmp->SetParent(this);
   m_ShapeContainer.insert(ShapeEntry(m_LastKey, tmp));

   NotifyAllListeners(gmShapeListener::PROPERTIES);

   return m_LastKey;
}

bool gmCompositeShape::RemoveShape(Uint32 key)
{
   ShapeIterator iter = m_ShapeContainer.find(key);
   if ( iter != m_ShapeContainer.end() )
   {
      m_ShapeContainer.erase(iter);

      NotifyAllListeners(gmShapeListener::PROPERTIES);

      return true;
   }
   else
      return false;
}

void gmCompositeShape::Clear()
{
   Clean();
   Init();
}

const gmIShape* gmCompositeShape::GetShape(Uint32 key) const
{
   ConstShapeIterator iter = m_ShapeContainer.find(key);

   if ( iter != m_ShapeContainer.end() )
      return (*iter).second.get();
   else
      return -0;
}

gmIShape* gmCompositeShape::GetShape(Uint32 key)
{
   ShapeIterator iter = m_ShapeContainer.find(key);

   if ( iter != m_ShapeContainer.end() )
      return (*iter).second.get();
   else
      return -0;
}

CollectionIndexType gmCompositeShape::GetNumShapes() const
{
   return m_ShapeContainer.size();
}

Float64 gmCompositeShape::GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const
{
   bool first=false;
   Float64 fd;
   for (ConstShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      if (first)
      {
         fd = (*it).second->GetFurthestDistance(line,side);
         first = false;
      }
      else
         fd = max(fd, (*it).second->GetFurthestDistance(line,side));
   }
   return fd;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmCompositeShape::AssertValid() const
{
   return gmShapeImp::AssertValid();
}

void gmCompositeShape::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for gmCompositeShape") << endl;
   gmShapeImp::Dump( os );
   os << _T("Contained shapes in gmCompositeShape") << endl;
   os << _T("   m_LastKey   = ")<<m_LastKey<<endl;
   os << _T("   # of Shapes = ")<<m_ShapeContainer.size()<<endl;
   Uint32 i=0;
   for (ConstShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      os<<_T(" Shape Number: ")<<++i<<_T(" Key = ")<<(*it).first<<endl;
      (*it).second->Dump(os);
   }
}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

gmCompositeShape::gmCompositeShape(const gmCompositeShape& rOther) :
gmShapeImp(rOther)
{
   Init();
   MakeCopy(rOther);
}

gmCompositeShape& gmCompositeShape::operator= (const gmCompositeShape& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void gmCompositeShape::DoTranslate(const gpSize2d& delta)
{
   BeginDamage();
   for (ShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      (*it).second->Translate(delta);
   }
   EndDamage();
}

void gmCompositeShape::DoRotate(const gpPoint2d& center, Float64 angle)
{
   BeginDamage();
   for (ShapeIterator it=m_ShapeContainer.begin();it!=m_ShapeContainer.end(); it++)
   {
      (*it).second->Rotate(center, angle);
   }
   EndDamage();
}


void gmCompositeShape::MakeCopy(const gmCompositeShape& rOther)
{
   m_LastKey        = rOther.m_LastKey;
   for (ConstShapeIterator it=rOther.m_ShapeContainer.begin(); 
        it!=rOther.m_ShapeContainer.end(); it++)
   {
      ShapePtr tmp( ((*it).second)->CreateClone(false) );
      tmp->SetParent(this);
      m_ShapeContainer.insert(ShapeEntry((*it).first, tmp));
   }
}

void gmCompositeShape::MakeAssignment(const gmCompositeShape& rOther)
{
   Clean();
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
void gmCompositeShape::Init()
{
   m_LastKey = 0;
}

void gmCompositeShape::Clean()
{
   m_ShapeContainer.clear();
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================



/****************************************************************************
CLASS
   gmShapeIter
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmShapeIter::gmShapeIter()
{
   Init();
}

gmShapeIter::gmShapeIter(gmCompositeShape* pComposite)
{
   SetComposite(pComposite);
}


gmShapeIter::gmShapeIter(const gmShapeIter& rOther)
{
   Init();
   MakeCopy(rOther);
}

gmShapeIter::~gmShapeIter()
{
   Clean();
}

//======================== OPERATORS  =======================================
gmShapeIter& gmShapeIter::operator= (const gmShapeIter& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void gmShapeIter::SetComposite(gmCompositeShape* pComposite)
{
   PRECONDITION(pComposite!=0);
   m_pComposite = pComposite;
   m_Iterator = pComposite->m_ShapeContainer.begin();
}

void gmShapeIter::Begin()
{
   PRECONDITION(m_pComposite!=0);
   m_Iterator = m_pComposite->m_ShapeContainer.begin();
}

void gmShapeIter::End()
{
   PRECONDITION(m_pComposite!=0);
   m_Iterator = m_pComposite->m_ShapeContainer.end();
}

void gmShapeIter::Next()
{
   PRECONDITION(m_pComposite!=0);
   CHECK(m_Iterator!=m_pComposite->m_ShapeContainer.end());
   m_Iterator++;
}

void gmShapeIter::Prev()
{
   PRECONDITION(m_pComposite!=0);
   CHECK(m_Iterator!=m_pComposite->m_ShapeContainer.begin());
   m_Iterator--;
}

gmShapeIter::operator void *() const
{
   if (m_pComposite==0)
      return 0;
   else if (m_Iterator==m_pComposite->m_ShapeContainer.end())
      return 0;
   else
      return (*m_Iterator).second.get();
}

gmIShape* gmShapeIter::CurrentShape() const
{
   PRECONDITION(*this);
   return (*m_Iterator).second.get();
}

const Uint32* gmShapeIter::CurrentKey() const
{
   PRECONDITION(*this);
   return &((*m_Iterator).first);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmShapeIter::AssertValid() const
{
   return true;
}

void gmShapeIter::Dump(dbgDumpContext& os) const
{
   os<< _T("Dump for gmShapeIter")<<endl;
   os<< _T("   m_pComposite = ")<<m_pComposite<<endl;
}

#endif // _DEBUG


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmShapeIter::MakeCopy(const gmShapeIter& rOther)
{
   m_pComposite = rOther.m_pComposite;
   m_Iterator = rOther.m_Iterator;
}

void gmShapeIter::MakeAssignment(const gmShapeIter& rOther)
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
void gmShapeIter::Init()
{
   m_pComposite = 0;
}

void gmShapeIter::Clean()
{
   // nothing to clean up.
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================



/****************************************************************************
CLASS
   gmConstShapeIter
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmConstShapeIter::gmConstShapeIter()
{
   Init();
}

gmConstShapeIter::gmConstShapeIter(const gmCompositeShape* pComposite)
{
   SetComposite(pComposite);
}


gmConstShapeIter::gmConstShapeIter(const gmConstShapeIter& rOther)
{
   Init();
   MakeCopy(rOther);
}

gmConstShapeIter::~gmConstShapeIter()
{
   Clean();
}

//======================== OPERATORS  =======================================
gmConstShapeIter& gmConstShapeIter::operator= (const gmConstShapeIter& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void gmConstShapeIter::SetComposite(const gmCompositeShape* pComposite)
{
   PRECONDITION(pComposite!=0);
   m_pComposite = pComposite;
   m_Iterator = pComposite->m_ShapeContainer.begin();
}


void gmConstShapeIter::Begin()
{
   PRECONDITION(m_pComposite!=0);
   m_Iterator = m_pComposite->m_ShapeContainer.begin();
}

void gmConstShapeIter::End()
{
   PRECONDITION(m_pComposite!=0);
   m_Iterator = m_pComposite->m_ShapeContainer.end();
}

void gmConstShapeIter::Next()
{
   PRECONDITION(m_pComposite!=0);
   CHECK(m_Iterator!=m_pComposite->m_ShapeContainer.end());
   m_Iterator++;
}

void gmConstShapeIter::Prev()
{
   PRECONDITION(m_pComposite!=0);
   CHECK(m_Iterator!=m_pComposite->m_ShapeContainer.begin());
   m_Iterator--;
}

gmConstShapeIter::operator void *() const
{
   if (m_pComposite==0)
      return 0;
   else if (m_Iterator==m_pComposite->m_ShapeContainer.end())
      return 0;
   else
      return (*m_Iterator).second.get();
}

const gmIShape* gmConstShapeIter::CurrentShape() const
{
   PRECONDITION(*this);
   return (*m_Iterator).second.get();
}

const Uint32* gmConstShapeIter::CurrentKey() const
{
   PRECONDITION(*this);
   return &((*m_Iterator).first);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmConstShapeIter::AssertValid() const
{
   return true;
}

void gmConstShapeIter::Dump(dbgDumpContext& os) const
{
   os<< _T("Dump for gmConstShapeIter")<<endl;
}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmConstShapeIter::MakeCopy(const gmConstShapeIter& rOther)
{
   m_pComposite = rOther.m_pComposite;
   m_Iterator = rOther.m_Iterator;
}

void gmConstShapeIter::MakeAssignment(const gmConstShapeIter& rOther)
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
void gmConstShapeIter::Init()
{
   m_pComposite = 0;
}

void gmConstShapeIter::Clean()
{
   // nothing to clean up.
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


#if defined _UNITTEST

bool gmCompositeShape::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmCompositeShape");

   // create an angle shape. by composing two rectangles
   // Taken from "Statics" 1st Ed. by J.L. Merriam, page 373
   gmTestShape outer(gmProperties(2000,gpPoint2d(20,25),416666.,266666.,0,50,0,0,40,0));
   gmTestShape inner(gmProperties(-1200,gpPoint2d(25,30),-160000.,-90000.,0,50,10,10,40,0));
   gmCompositeShape anglec;
   Uint32 okey, ikey;
   gmIShape* sp;
   okey = anglec.AddShape(outer);
   TRY_TESTME( okey >= 0 ) ;
   ikey = anglec.AddShape(inner);
   TRY_TESTME( ikey >= 0 ) ;
   sp = anglec.GetShape(ikey);
   TRY_TESTME( sp != NULL ) ;
   sp->MakeSolid(false);  // set inner shape to be hollow (does nothing for gmtestshape)

   gmProperties aprops;
   anglec.GetProperties(&aprops);
   TRY_TESTME (IsEqual(aprops.Area(), 800.)) 
   TRY_TESTME (IsEqual(aprops.Ixx(),  181666., 10.)) 
   TRY_TESTME (IsEqual(aprops.Iyy(),  101666., 10.)) 
   TRY_TESTME (IsEqual(aprops.Ixy(), -75000., 10.)) 
   TRY_TESTME (anglec.GetBoundingBox() == gpRect2d(0,0,40,50)) 

   // take a dump
#if defined _DEBUG
   anglec.Dump(rlog.GetDumpCtx());
#endif

   // delete inner rectangle
   TRY_TESTME( anglec.RemoveShape(ikey) )
   anglec.GetProperties(&aprops);
   TRY_TESTME (IsEqual(aprops.Area(), 2000.)) 
   TRY_TESTME (IsEqual(aprops.Ixx(),  416666., 10.)) 
   TRY_TESTME (IsEqual(aprops.Iyy(),  266666., 10.)) 
   TRY_TESTME (IsEqual(aprops.Ixy(),       0., 10.)) 
   TRY_TESTME (anglec.GetBoundingBox() == gpRect2d(0,0,40,50)) 


   TESTME_EPILOG("gmCompositeShape");
}

bool gmShapeIter::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmShapeIter");

   // create a composite and iterate through its shapes
   gmTestShape s1(gmProperties(2000,gpPoint2d(20,25),416666.,266666.,0,50,0,0,40,0));
   gmTestShape s2(gmProperties(1200,gpPoint2d(25,30),-160000.,-90000.,0,50,10,10,40,0));
   gmTestShape s3(gmProperties( 200,gpPoint2d( 0, 0),    220.,   300.,0,5,1,1,4,0));
   gmCompositeShape ctest;
   Uint32 p1 = ctest.AddShape(s1);
   Uint32 p2 = ctest.AddShape(s2);
   Uint32 p3 = ctest.AddShape(s3);
   Uint32 p4 = ctest.AddShape(s2);
   Uint32 p5 = ctest.AddShape(s3);
   Uint32 p6 = ctest.AddShape(s1);

   gmShapeIter my_it(&ctest);
   Uint32 i = 0;
   for(my_it.Begin(); my_it; my_it.Next())
   {
      i++;
      if (i==3)
         TRY_TESTME (p3 == *my_it.CurrentKey()) ;
      if (i==4)
         TRY_TESTME (s2 == *(gmTestShape*)my_it.CurrentShape());
      if (i==5)
         TRY_TESTME (p5 == *my_it.CurrentKey()) ;
   }

   my_it.Prev();
   TRY_TESTME (p6 == *my_it.CurrentKey());

   TRY_TESTME ( ctest.RemoveShape(p4) ) ;
   TRY_TESTME ( ctest.RemoveShape(p5) ) ;

   my_it.End();
   gmShapeIter new_it = my_it;
   new_it.Prev();
   new_it.Prev();
   TRY_TESTME ( s3 == *(gmTestShape*)new_it.CurrentShape() );

#if defined _DEBUG
   my_it.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gmShapeIter");
}


bool gmConstShapeIter::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmConstShapeIter");

   // create a composite and iterate through its shapes
   gmTestShape s1(gmProperties(2000,gpPoint2d(20,25),416666.,266666.,0,50,0,0,40,0));
   gmTestShape s2(gmProperties(1200,gpPoint2d(25,30),-160000.,-90000.,0,50,10,10,40,0));
   gmTestShape s3(gmProperties( 200,gpPoint2d( 0, 0),    220.,   300.,0,5,1,1,4,0));
   gmCompositeShape ctest;
   Uint32 p1 = ctest.AddShape(s1);
   Uint32 p2 = ctest.AddShape(s2);
   Uint32 p3 = ctest.AddShape(s3);
   Uint32 p4 = ctest.AddShape(s2);
   Uint32 p5 = ctest.AddShape(s3);
   Uint32 p6 = ctest.AddShape(s1);

   gmConstShapeIter my_it(&ctest);
   Uint32 i = 0;
   for(my_it.Begin(); my_it; my_it.Next())
   {
      i++;
      if (i==3)
         TRY_TESTME ( p3 == *my_it.CurrentKey() );
      if (i==4)
         TRY_TESTME ( s2 == *(gmTestShape*)my_it.CurrentShape() );
      if (i==5)
         TRY_TESTME ( p5 == *my_it.CurrentKey() ) ;
   }

   my_it.Prev();
   TRY_TESTME (p6 == *my_it.CurrentKey()) ;

   TRY_TESTME ( ctest.RemoveShape(p4) ) ;
   TRY_TESTME ( ctest.RemoveShape(p5) ) ;

   my_it.End();
   gmConstShapeIter new_it = my_it;
   new_it.Prev();
   new_it.Prev();
   TRY_TESTME ( s3 == *(gmTestShape*)new_it.CurrentShape() );

#if defined _DEBUG
  my_it.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gmConstShapeIter");
}

#endif // _UNITTEST



///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
#include <GeomModel\Section.h>
#include <GeomModel\IShape.h>
#include <GeomModel\ElasticProperties.h>
#include <GeomModel\MassProperties.h>

#include <GeomModel\Polygon.h>
#include <MathEx.h>
#include <iostream>

#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmSection
****************************************************************************/


// create elastic props from a component
gmElasticProperties make_elastic_properties(const gmSectionComponent& rCmp);
gmMassProperties    make_mass_properties(const gmSectionComponent& rCmp);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmSection::gmSection()
{
   Init();
}

gmSection::~gmSection()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

gmSection* gmSection::CreateClone(bool bRegisterListeners) const
{
   std::auto_ptr<gmSection> ps(new gmSection());

   // copy member data
   ps->m_ComponentContainer = m_ComponentContainer;
   ps->m_DamageCount        = m_DamageCount;
   ps->m_DamageTypeTally    = m_DamageTypeTally;
   ps->m_LastKey            = m_LastKey;

   // copy listeners if requested.
   if (bRegisterListeners)
      ps->DoRegisterListeners(*this);

   return ps.release();
}


void gmSection::Translate(const gpSize2d& delta)
{
   BeginDamage();
   for (ComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      gmIShape& rs = (*it).second->GetShape();
      rs.Translate(delta);
   }

   NotifyAllListeners(gmSectionListener::PROPERTIES);
   EndDamage();
}

void gmSection::Rotate(const gpPoint2d& center, Float64 angle)
{
   BeginDamage();
   for (ComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      gmIShape& rs = (*it).second->GetShape();
      rs.Rotate(center, angle);
   }

   NotifyAllListeners(gmSectionListener::PROPERTIES);
   EndDamage();
}

Uint32 gmSection::AddComponent(const gmIShape& rShape,
                    Float64 modE, Float64 density,
                    bool bIsStructural,
                    bool bRegisterListeners)
{
   std::auto_ptr<gmIShape> psh(rShape.CreateClone(bRegisterListeners));
   ComponentPtr psc(new gmSectionComponent(psh.get(), modE, 
                                             density, bIsStructural));
   psh.release();
   psc->SetParent(this);
   m_LastKey++;

   m_ComponentContainer.insert(ComponentEntry(m_LastKey, psc));

   NotifyAllListeners(gmSectionListener::PROPERTIES);

   return m_LastKey;
}

const gmSectionComponent* gmSection::GetComponent(Uint32 key) const
{
   ConstComponentIterator const_iter = m_ComponentContainer.find(key);

   if ( const_iter != m_ComponentContainer.end() )
      return (*const_iter).second.get();
   else
      return -0;
}

gmSectionComponent* gmSection::GetComponent(Uint32 key)
{
   ComponentIterator iter = m_ComponentContainer.find(key);

   if ( iter != m_ComponentContainer.end() )
      return (*iter).second.get();
   else
      return -0;
}

bool gmSection::RemoveComponent(Uint32 key)
{
   ComponentIterator iter = m_ComponentContainer.find(key);
   if ( iter != m_ComponentContainer.end() )
   {
      m_ComponentContainer.erase(iter);

      NotifyAllListeners(gmSectionListener::PROPERTIES);

      return true;
   }
   else
      return false;
}

void gmSection::RemoveAllComponents()
{
   m_ComponentContainer.clear();
   NotifyAllListeners(gmSectionListener::PROPERTIES);
}

void gmSection::GetElasticProperties(gmElasticProperties* pProperties) const
{
   gmElasticProperties sum;

   // add up properties for all members of the composite
   // ignore non-structural members.
   for (ConstComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      const gmSectionComponent* pCmp = (*it).second.get();
      if ( pCmp->IsStructural() )
      {
         gmElasticProperties tmp = make_elastic_properties(*pCmp);
         sum += tmp;
      }
   }

   *pProperties = sum;
}

void gmSection::GetMassProperties(gmMassProperties* pProperties) const
{
   Float64 sum=0;
   // add up properties for all members of the composite
   for (ConstComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      const gmIShape& rs= (*(*it).second).GetShape();
      Float64 dens      = (*(*it).second).GetDensity();
      gmProperties gp;
      rs.GetProperties(&gp);

      sum += dens*gp.Area();
   }

   pProperties->SetMassPerLength(sum);
}

gpRect2d gmSection::GetBoundingBox(bool bExcludeNonstructuralComponents) const
{
   gpRect2d sum;

   bool first = true;
   for (ConstComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      const gmIShape& rs= (*(*it).second).GetShape();
      if (first)
      {
         sum = rs.GetBoundingBox();
         first = false;
      }
      else
         sum.Union(rs.GetBoundingBox());
   }
   return sum;
}

gmSection* gmSection::CreateClippedSection(const gpLine2d& line,
                                  gpLine2d::Side side) const
{
   std::auto_ptr<gmSection> pcs(new gmSection());

   for (ConstComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      const gmSectionComponent& sc = (*(*it).second);
      const gmIShape& rs= sc.GetShape();
      std::auto_ptr<gmIShape> pps (rs.CreateClippedShape(line, side));
      if (pps.get()!=0)
      {
         pcs->AddComponent(*pps, sc.GetModE(), sc.GetDensity(), sc.IsStructural());
      }
   }

   return pcs.release();
}

gmSection* gmSection::CreateClippedSection(const gpRect2d& r,
                                gmSection::ClipRegion& region) const
{
   std::auto_ptr<gmSection> pcs(new gmSection());

   for (ConstComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      const gmSectionComponent& sc = (*(*it).second);
      const gmIShape& rs= sc.GetShape();

      gmIShape::ClipRegion sreg;
      if (region== In)
         sreg = gmIShape::In;
      else
         sreg = gmIShape::Out;

      std::auto_ptr<gmIShape> pps (rs.CreateClippedShape(r, sreg));
      if (pps.get()!=0)
      {
         pcs->AddComponent(*pps, sc.GetModE(), sc.GetDensity(), sc.IsStructural());
      }
   }

   return pcs.release();
}

void gmSection::EnableBorderMode(bool bEnable)
{
   for (ComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      gmIShape& rs= (*(*it).second).GetShape();
      rs.EnableBorderMode(bEnable);
   }
}

void gmSection::SetBorderColor(COLORREF color)
{
   for (ComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      gmIShape& rs= (*(*it).second).GetShape();
      rs.SetBorderColor(color);
   }
}

void gmSection::EnableFillMode(bool bEnable)
{
   for (ComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      gmIShape& rs= (*(*it).second).GetShape();
      rs.EnableFillMode(bEnable);
   }
}

void gmSection::SetFillColor(COLORREF color)
{
   for (ComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      gmIShape& rs= (*(*it).second).GetShape();
      rs.SetFillColor(color);
   }
}

void gmSection::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   for (ConstComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      gmIShape& rs= (*(*it).second).GetShape();
      rs.Draw(hDC, mapper);
   }
}

void gmSection::RegisterListener(gmSectionListener* pListener)
{
   ASSERTVALID;
   DoRegisterListener(pListener);
}

void gmSection::UnregisterListener(const gmSectionListener* pListener)
{
   ASSERTVALID;
   PRECONDITION(pListener);

   // have to do cast here because erase won't work otherwise
   if(!m_ListenerList.erase((gmSectionListener*)pListener))
   {
      WARN(0,"Listener removal failed - probably unregistered twice");
   }

   pListener->OnUnregistered(this);
}

Int32 gmSection::ListenerCount() const
{
   ASSERTVALID;
   return m_ListenerList.size();
}

void gmSection::BeginDamage()
{
   ASSERTVALID;
   m_DamageCount++;
}

void gmSection::EndDamage()
{
   ASSERTVALID;
   if (m_DamageCount!=0)
   {
      if (--m_DamageCount == 0)
      {
         // damage count is zero - notify listeners as to what has happened during the
         // damaged period.
         NotifyAllListeners(m_DamageTypeTally);
         m_DamageTypeTally = 0;
      }
   }
   else
      WARN(0, "Call to EndDamage when damage count is zero");

   ASSERTVALID;
}

bool gmSection::IsDamaged() const
{
   ASSERTVALID;
   if (m_DamageCount > 0)
      return true;
   else
      return false;
}

Int32 gmSection::DamagedCount() const
{
   ASSERTVALID;
   return m_DamageCount;
}

void gmSection::NotifyAllListeners( Int32 lHint, const gmSectionComponent* pComponent)
{
   if (m_DamageCount > 0)
   {
      // we're damaged goods - just save the damage hint and wait until
      // we've been repaired
      m_DamageTypeTally |= lHint;
   }
   else
   {
      // we're flying in good shape - let our listeners know what happened
      ListenerListIterator it;
      for (it=m_ListenerList.begin(); it!=m_ListenerList.end(); it++)
      {
         (*it)->OnUpdate(this, lHint, pComponent);
      }
   }
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmSection::AssertValid() const
{
   return true;
}

void gmSection::Dump(dbgDumpContext& os) const
{
   os << "Dump for gmSection" << endl;
   os << "  m_DamageCount     = " << m_DamageCount << endl;
   os << "  m_DamageTypeTally = " << m_DamageTypeTally << endl;
   os << "  m_LastKey         = " << m_LastKey << endl;
   os << "  Component Container has "<< m_ComponentContainer.size()<<endl;
   for (ConstComponentIterator it=m_ComponentContainer.begin();it!=m_ComponentContainer.end(); it++)
   {
      (*it).second->Dump(os);
   }

}
#endif // _DEBUG

#if defined _UNITTEST
#include <GeomModel\Rectangle.h>
bool gmSection::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmSection");

//#pragma Reminder("Implement Unit Tests")
//   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented");

   // Test to verify non-structural components are not included in elastic properties,
   // but are included in mass properties
   gmRectangle rect1( gpPoint2d(0,0), 20, 10 );
   gmRectangle rect2( gpPoint2d(0,0), 20, 10 );
   rect2.Move( gmIShape::BottomCenter, rect1.GetLocatorPoint( gmIShape::TopCenter ) );
   gmSection section;
   section.AddComponent( rect1, 1, 1, true );
   section.AddComponent( rect2, 1, 2, false );
   gmElasticProperties eProp;
   gmMassProperties mProp;

   section.GetMassProperties( &mProp );
   TRY_TESTME( IsEqual( mProp.MassPerLength(), 600. ) );

// RAB: I added this code to debug a release build problem.
//
//   rlog << "# Shapes = " << section.m_ComponentContainer.size() << endl;
//   Float64 sum=0;
//   // add up properties for all members of the composite
//   for (ConstComponentIterator it=section.m_ComponentContainer.begin();it!=section.m_ComponentContainer.end(); it++)
//   {
//      const gmIShape& rs= (*(*it).second).GetShape();
//      Float64 dens      = (*(*it).second).GetDensity();
//      gmProperties gp;
//      rs.GetProperties(&gp);
//
//      sum += dens*gp.Area();
//
//      rlog << "Density = " << dens << endl;
//      rlog << "Area = " << gp.Area() << endl;
//
//      const gmRectangle& rect = dynamic_cast<const gmRectangle&>(rs);
//      rlog << "Height = " << rect.GetHeight() << endl;
//      rlog << "Width = " << rect.GetWidth() << endl;
//      rlog << "Top = " << rect.GetBoundingBox().Top() << endl;
//      rlog << "Bottom = " << rect.GetBoundingBox().Bottom() << endl;
//      rlog << "Left = " << rect.GetBoundingBox().Left() << endl;
//      rlog << "Right = " << rect.GetBoundingBox().Right() << endl;
//   }
//   rlog << "MassPerLength = " << mProp.MassPerLength() << endl;

   section.GetElasticProperties( &eProp );
   TRY_TESTME( IsEqual( eProp.EA(), 200. ) );

   TESTME_EPILOG("gmSection");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void gmSection::SetShapeDirty(gmSectionComponent* psc, Int32 lHint)
{
   NotifyAllListeners(lHint, psc);
}


void gmSection::DoRegisterListeners(const gmSection& rOwner)
{
   // copy listeners from owner section to this. Append them if
   // this already has listeners.
   ConstListenerListIterator it;
   for (it=rOwner.m_ListenerList.begin(); it!=rOwner.m_ListenerList.end(); it++)
   {
      DoRegisterListener(*it);
   }
}

void gmSection::DoRegisterListener(gmSectionListener* pListener)
{
   PRECONDITION(pListener);
   // add listener to list
   if (!m_ListenerList.insert(pListener).second)
      WARN(0,"Listener insertion failed - probably duplicate");

   pListener->OnRegistered(this);
}

void gmSection::Init()
{
   m_DamageCount=0;
   m_DamageTypeTally=0;
   m_LastKey = 0;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


/****************************************************************************
CLASS
   gmSectionComponent
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmSectionComponent::gmSectionComponent(gmIShape* pShape,
                                       Float64 modE, Float64 density,
                                       bool bIsStructural) :
gmShapeListener(),
m_bIsStructural(bIsStructural),
m_Density(density),
m_ModE(modE),
m_pParent(0)  // no parent section yet.
{
   PRECONDITION(pShape);
   m_pShape = pShape;
   m_pShape->RegisterListener(this);
}

gmSectionComponent::~gmSectionComponent()
{
   m_pShape->UnregisterListener(this);
   delete m_pShape;
}

//======================== OPERATORS  =======================================

//======================== OPERATIONS =======================================


gmSectionComponent* gmSectionComponent::CreateClone(bool bRegisterListeners) const
{
   // clone the shape and unregister it from this
   std::auto_ptr<gmIShape> ps(m_pShape->CreateClone(bRegisterListeners));
   if(bRegisterListeners)
      ps->UnregisterListener((gmShapeListener*)this);
   // create a new componenent
   return new gmSectionComponent(ps.get(), m_ModE, m_Density, m_bIsStructural);
}

const gmIShape& gmSectionComponent::GetShape() const
{
   return *m_pShape;
}

gmIShape& gmSectionComponent::GetShape()
{
   return *m_pShape;
}

Float64 gmSectionComponent::GetModE() const
{
   return m_ModE;
}

Float64 gmSectionComponent::SetModE(Float64 modE)
{
   Float64 tmp = m_ModE;
   m_ModE = modE;
   return tmp;
}

Float64 gmSectionComponent::GetDensity() const
{
   return m_Density;
}

Float64 gmSectionComponent::SetDensity(Float64 density)
{
   Float64 tmp = m_Density;
   m_Density = density;
   return tmp;
}

void gmSectionComponent::MakeStructural()
{
   m_bIsStructural = true;
}

void gmSectionComponent::MakeNonstructural()
{
   m_bIsStructural = false;
}

bool gmSectionComponent::IsStructural()const
{
   return m_bIsStructural;
}

void gmSectionComponent::OnUpdate(const gmIShape* pShape, Int32 lHint)
{
   if (m_pParent!=0)
   {
      // tell the parent section we're dirty
      m_pParent->SetShapeDirty(this, lHint);
   }
   else
      WARN(0,"SectionComponent has no parent section");
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmSectionComponent::AssertValid() const
{
   return gmShapeListener::AssertValid();
}

void gmSectionComponent::Dump(dbgDumpContext& os) const
{
   os << "Begin Dump for SectionComponent"<<endl;
   gmShapeListener::Dump( os );
   m_pShape->Dump(os);
   os << "m_ModE          = "<< m_ModE<<endl;
   os << "m_Density       = "<< m_Density<<endl;
   os << "m_bIsStructural = "<< m_bIsStructural<<endl;
   os << "m_pParent       = "<< m_pParent<<endl;
   os << "end Dump for SectionComponent"<<endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool gmSectionComponent::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmSectionComponent");


   TESTME_EPILOG("gmSectionComponent");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmSectionComponent::SetParent(gmSection* ps)
{
   PRECONDITION(ps);
   m_pParent = ps;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


/****************************************************************************
CLASS
   gmSectionComponentIter
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmSectionComponentIter::gmSectionComponentIter()
{
   Init();
}

gmSectionComponentIter::gmSectionComponentIter(gmSection* pSection)
{
   SetSection(pSection);
}

gmSectionComponentIter::gmSectionComponentIter(const gmSectionComponentIter& rOther)
{
   Init();
   MakeCopy(rOther);
}

gmSectionComponentIter::~gmSectionComponentIter()
{
   Clean();
}

//======================== OPERATORS  =======================================
gmSectionComponentIter& gmSectionComponentIter::operator= (const gmSectionComponentIter& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }
   return *this;
}

//======================== OPERATIONS =======================================

void gmSectionComponentIter::SetSection(gmSection* pSection)
{
   PRECONDITION(pSection!=0);
   m_pSection = pSection;
   m_Iterator = pSection->m_ComponentContainer.begin();
}

void gmSectionComponentIter::Begin()
{
   PRECONDITION(m_pSection!=0);
   m_Iterator = m_pSection->m_ComponentContainer.begin();
}

void gmSectionComponentIter::End()
{
   PRECONDITION(m_pSection!=0);
   m_Iterator = m_pSection->m_ComponentContainer.end();
}

void gmSectionComponentIter::Next()
{
   PRECONDITION(m_pSection!=0);
   CHECK(m_Iterator!=m_pSection->m_ComponentContainer.end());
   m_Iterator++;
}

void gmSectionComponentIter::Prev()
{
   PRECONDITION(m_pSection!=0);
   CHECK(m_Iterator!=m_pSection->m_ComponentContainer.begin());
   m_Iterator--;
}

gmSectionComponentIter::operator void *() const
{
   if (m_pSection==0)
      return 0;
   else if (m_Iterator==m_pSection->m_ComponentContainer.end())
      return 0;
   else
      return (*m_Iterator).second.get();
}

gmSectionComponent* gmSectionComponentIter::CurrentComponent() const
{
   PRECONDITION(*this);
   return (*m_Iterator).second.get();
}

const Uint32* gmSectionComponentIter::CurrentKey() const
{
   PRECONDITION(*this);
   return &((*m_Iterator).first);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmSectionComponentIter::AssertValid() const
{
   return true;
}

void gmSectionComponentIter::Dump(dbgDumpContext& os) const
{
   os<< "Dump for gmSectionComponentIter"<<endl;
   os<< "   m_pSection = "<<m_pSection<<endl;
}

#endif // _DEBUG


#if defined _UNITTEST
bool gmSectionComponentIter::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmSectionComponentIter");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented");
   TESTME_EPILOG("gmSectionComponentIter");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmSectionComponentIter::MakeCopy(const gmSectionComponentIter& rOther)
{
   m_pSection = rOther.m_pSection;
   m_Iterator = rOther.m_Iterator;
}

void gmSectionComponentIter::MakeAssignment(const gmSectionComponentIter& rOther)
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
void gmSectionComponentIter::Init()
{
   m_pSection = 0;
}

void gmSectionComponentIter::Clean()
{
   // nothing to clean up.
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


/****************************************************************************
CLASS
   gmConstSectionComponentIter
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmConstSectionComponentIter::gmConstSectionComponentIter()
{
   Init();
}

gmConstSectionComponentIter::gmConstSectionComponentIter(const gmSection* pSection)
{
   SetSection(pSection);
}

gmConstSectionComponentIter::gmConstSectionComponentIter(const gmConstSectionComponentIter& rOther)
{
   Init();
   MakeCopy(rOther);
}

gmConstSectionComponentIter::~gmConstSectionComponentIter()
{
   Clean();
}

//======================== OPERATORS  =======================================
gmConstSectionComponentIter& gmConstSectionComponentIter::operator= (const gmConstSectionComponentIter& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }
   return *this;
}

//======================== OPERATIONS =======================================

void gmConstSectionComponentIter::SetSection(const gmSection* pSection)
{
   PRECONDITION(pSection!=0);
   m_pSection = pSection;
   m_Iterator = pSection->m_ComponentContainer.begin();
}

void gmConstSectionComponentIter::Begin()
{
   PRECONDITION(m_pSection!=0);
   m_Iterator = m_pSection->m_ComponentContainer.begin();
}

void gmConstSectionComponentIter::End()
{
   PRECONDITION(m_pSection!=0);
   m_Iterator = m_pSection->m_ComponentContainer.end();
}

void gmConstSectionComponentIter::Next()
{
   PRECONDITION(m_pSection!=0);
   CHECK(m_Iterator!=m_pSection->m_ComponentContainer.end());
   m_Iterator++;
}

void gmConstSectionComponentIter::Prev()
{
   PRECONDITION(m_pSection!=0);
   CHECK(m_Iterator!=m_pSection->m_ComponentContainer.begin());
   m_Iterator--;
}

gmConstSectionComponentIter::operator void *() const
{
   if (m_pSection==0)
      return 0;
   else if (m_Iterator==m_pSection->m_ComponentContainer.end())
      return 0;
   else
      return (*m_Iterator).second.get();
}

const gmSectionComponent* gmConstSectionComponentIter::CurrentComponent() const
{
   PRECONDITION(*this);
   return (*m_Iterator).second.get();
}

const Uint32* gmConstSectionComponentIter::CurrentKey() const
{
   PRECONDITION(*this);
   return &((*m_Iterator).first);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmConstSectionComponentIter::AssertValid() const
{
   return true;
}

void gmConstSectionComponentIter::Dump(dbgDumpContext& os) const
{
   os<< "Dump for gmConstSectionComponentIter"<<endl;
}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmConstSectionComponentIter::MakeCopy(const gmConstSectionComponentIter& rOther)
{
   m_pSection = rOther.m_pSection;
   m_Iterator = rOther.m_Iterator;
}

void gmConstSectionComponentIter::MakeAssignment(const gmConstSectionComponentIter& rOther)
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
void gmConstSectionComponentIter::Init()
{
   m_pSection = 0;
}

void gmConstSectionComponentIter::Clean()
{
   // nothing to clean up.
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST
bool gmConstSectionComponentIter::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmConstSectionComponentIter");

   // create an angle shape. Taken from "Statics" 1st Ed. by J.L. Merriam, page 373
   gmPolygon anglep;
   Uint32 p1 = anglep.AddPoint(gpPoint2d(0 , 0));
   Uint32 p2 = anglep.AddPoint(gpPoint2d(0 ,50));
   Uint32 p3 = anglep.AddPoint(gpPoint2d(10,50));
   Uint32 p4 = anglep.AddPoint(gpPoint2d(10,10));
   Uint32 p5 = anglep.AddPoint(gpPoint2d(40,10));
   Uint32 p6 = anglep.AddPoint(gpPoint2d(40, 0));  // don't close polygon

   gmSection sang;
   Int32 sid = sang.AddComponent(anglep, 1000., 10.);

   gmElasticProperties aprops;
   sang.GetElasticProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.EA(), 800000.)) ;
   TRY_TESTME ( IsEqual(aprops.EIxx(),  181670000., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.EIyy(),  101670000., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.EIxy(), -750000000., 10.)) ;
   TRY_TESTME ( sang.GetBoundingBox(false) == gpRect2d(0,0,40,50)) ;

   gmMassProperties mprops;
   sang.GetMassProperties(&mprops);
   TRY_TESTME ( IsEqual(mprops.MassPerLength(), 8000.)) ;

   // move things around a bit
   sang.Translate(gpSize2d(20,20));
   TRY_TESTME ( sang.GetBoundingBox(false) == gpRect2d(20,20,60,70)) ;

   gmSectionComponent* pmycomp = sang.GetComponent(sid);
   gmIShape& rshape = pmycomp->GetShape();
   rshape.Translate(gpSize2d(-20,-20));
   TRY_TESTME (sang.GetBoundingBox(false) == gpRect2d(0,0,40,50)) ;

   // take a dump
#if defined _DEBUG
  sang.Dump(rlog.GetDumpCtx());
#endif

   // copy
   std::auto_ptr<gmSection> sang2 (sang.CreateClone());
   sang2->GetElasticProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.EA(), 800000.)) ;
   TRY_TESTME ( IsEqual(aprops.EIxx(),  181670000., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.EIyy(),  101670000., 10.)) ;
   TRY_TESTME ( IsEqual(aprops.EIxy(), -750000000., 10.)) ;
   TRY_TESTME ( sang2->GetBoundingBox(false) == gpRect2d(0,0,40,50)) ;

   // clip
   std::auto_ptr<gmSection> pclip (sang2->CreateClippedSection(
                       gpLine2d(gpPoint2d(10,0),gpPoint2d(10,20)), gpLine2d::Left));
   pclip->GetElasticProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.EA(), 500000.)) ;
   TRY_TESTME ( pclip->GetBoundingBox(false) == gpRect2d(0,0,10,50)) ;

   // rotate
   pclip->Rotate(gpPoint2d(0,0), -M_PI/2.);
   pclip->GetElasticProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.EA(), 500000.)) ;
   TRY_TESTME ( pclip->GetBoundingBox(false) == gpRect2d(0,-10,50,0)) ;

   TESTME_EPILOG("gmConstSectionComponentIter");
}

#endif // _UNITTEST

gmElasticProperties make_elastic_properties(const gmSectionComponent& rCmp)
{
   const gmIShape& rs= rCmp.GetShape();
   Float64 e         = rCmp.GetModE();
   gmProperties gp;
   rs.GetProperties(&gp);

   return gmElasticProperties(e*gp.Area(), gp.Centroid(), 
                              e*gp.Ixx(),  e*gp.Iyy(), e*gp.Ixy(),
                              gp.Ytop(),   gp.Ybottom(), gp.Xleft(), gp.Xright(), gp.Perimeter());
}


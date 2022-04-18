///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <GeomModel\ShapeImp.h>
#include <GeomModel\Properties.h>
#include <GeomModel\CompositeShape.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmShapeImp
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmShapeImp::gmShapeImp()
{
   Init();
}

gmShapeImp::gmShapeImp(const gmShapeImp& rOther)
{
   Init();
   MakeCopy(rOther);
}

gmShapeImp::~gmShapeImp()
{
   Clean();
}

//======================== OPERATORS  =======================================
gmShapeImp& gmShapeImp::operator= (const gmShapeImp& rOther)
{
   ASSERTVALID;

   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   ASSERTVALID;

   return *this;
}

//======================== OPERATIONS =======================================


void gmShapeImp::Translate(const gpSize2d& delta)
{
   ASSERTVALID;

   DoTranslate(delta);
   NotifyAllListeners(gmShapeListener::PROPERTIES);

   ASSERTVALID;
}

void gmShapeImp::Move(LocatorPoint point,const gpPoint2d& to)
{
   gpPoint2d from;

   from = GetLocatorPoint( point );
   Move(from, to);
}

void gmShapeImp::Move(const gpPoint2d& from,const gpPoint2d& to)
{
   Translate(to-from);
}


void gmShapeImp::Rotate(const gpPoint2d& center, Float64 angle)
{
   ASSERTVALID;

   DoRotate(center, angle);
   NotifyAllListeners(gmShapeListener::PROPERTIES);

   ASSERTVALID;
}


gpPoint2d gmShapeImp::GetLocatorPoint(LocatorPoint point) const
{
   ASSERTVALID;

   gpRect2d rct;
   gpPoint2d pnt;

   rct = GetBoundingBox();

   switch(point)
   {
   case TopLeft:
        pnt = rct.TopLeft();
        break;

   case TopCenter:
        pnt = rct.TopCenter();
        break;

   case TopRight:
        pnt = rct.TopRight();
        break;

   case LeftCenter:
        pnt = rct.LeftCenter();
        break;

   case CenterCenter:
        pnt = rct.Center();
        break;

   case RightCenter:
        pnt = rct.RightCenter();
        break;

   case BottomLeft:
        pnt = rct.BottomLeft();
        break;

   case BottomCenter:
        pnt = rct.BottomCenter();
        break;

   case BottomRight:
        pnt = rct.BottomRight();
        break;

   default:
      CHECK( false );
      break;
   }

   return pnt;

}

void gmShapeImp::MakeSolid(bool isSolid)
{
   ASSERTVALID;

   if (isSolid!=m_IsSolid)
   {
      m_IsSolid = isSolid;
      NotifyAllListeners(gmShapeListener::PROPERTIES);
   }
}


bool gmShapeImp::IsSolid() const
{
   ASSERTVALID;

   return m_IsSolid;
}


bool gmShapeImp::EnableBorderMode(bool bEnable)
{
   ASSERTVALID;

   bool tmp = m_BorderMode;
   m_BorderMode = bEnable;
   NotifyAllListeners(gmShapeListener::DISPLAY);
   return tmp;
}

bool gmShapeImp::IsBorderModeEnabled() const
{
   ASSERTVALID;

   return m_BorderMode;
}

COLORREF gmShapeImp::SetBorderColor(COLORREF color)
{
   ASSERTVALID;

   COLORREF tmp = m_BorderColor;
   m_BorderColor = color;
   NotifyAllListeners(gmShapeListener::DISPLAY);
   return tmp;
}

COLORREF gmShapeImp::GetBorderColor() const
{
   ASSERTVALID;

   return m_BorderColor;
}

bool gmShapeImp::EnableFillMode(bool bEnable)
{
   ASSERTVALID;

   bool tmp = m_FillMode;
   m_FillMode = bEnable;
   NotifyAllListeners(gmShapeListener::DISPLAY);
   return tmp;
}

bool gmShapeImp::IsFillModeEnabled() const
{
   ASSERTVALID;

   return m_FillMode;
}

COLORREF gmShapeImp::SetFillColor(COLORREF color)
{
   ASSERTVALID;

   COLORREF tmp = m_FillColor;
   m_FillColor = color;
   NotifyAllListeners(gmShapeListener::DISPLAY);
   return tmp;
}

COLORREF gmShapeImp::GetFillColor() const
{
   ASSERTVALID;
   return m_FillColor;
}


gmCompositeShape* gmShapeImp::GetComposite()
{
   ASSERTVALID;
   // no composite here!
   return nullptr;
}

const gmCompositeShape* gmShapeImp::GetComposite() const
{
   ASSERTVALID;
   return nullptr;
}


gmCompositeShape* gmShapeImp::GetParent()
{
   ASSERTVALID;
   return m_pParent;
}

const gmCompositeShape* gmShapeImp::GetParent() const
{
   ASSERTVALID;
   return m_pParent;
}


void gmShapeImp::RegisterListener(gmShapeListener* pListener)
{
   ASSERTVALID;
   DoRegisterListener(pListener);
}

void gmShapeImp::UnregisterListener(const gmShapeListener* pListener)
{
   ASSERTVALID;
   PRECONDITION(pListener);

   // have to do cast here because erase won't work otherwise
   if(!m_ListenerList.erase((gmShapeListener*)pListener))
   {
      WARN(0,"Listener removal failed - probably unregistered twice");
   }

   pListener->OnUnregistered(this);

}

CollectionIndexType gmShapeImp::ListenerCount() const
{
   ASSERTVALID;
   return m_ListenerList.size();
}

void gmShapeImp::BeginDamage()
{
   ASSERTVALID;
   m_DamageCount++;
}

void gmShapeImp::EndDamage()
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

bool gmShapeImp::IsDamaged() const
{
   ASSERTVALID;
   if (m_DamageCount > 0)
      return true;
   else
      return false;
}

Int32 gmShapeImp::DamagedCount() const
{
   ASSERTVALID;
   return m_DamageCount;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmShapeImp::AssertValid() const
{
   if (m_DamageCount<0) return false;

   return true;
}

void gmShapeImp::Dump(dbgDumpContext& os) const
{
   ASSERTVALID;
   os << _T("Dump for gmShapeImp") << endl;
   os << _T("  m_IsSolid           = ")<<m_IsSolid <<endl;
   os << _T("  m_pParent           = ")<<m_pParent <<endl;           
   os << _T("  m_BorderMode        = ")<<m_BorderMode  <<endl;       
   os << _T("  m_FillMode          = ")<<m_FillMode  <<endl;         
   os << _T("  m_BorderColor       = ")<<m_BorderColor <<endl;      
   os << _T("  m_FillColor         = ")<<m_FillColor  <<endl;        

   os << _T("  m_ListenerList size = ")<<m_ListenerList.size()<<endl;
   os << _T("  m_DamageCount       = ")<<m_DamageCount <<endl;       
   os << _T("  m_DamageTypeTally   = ")<<m_DamageTypeTally <<endl;   
}
#endif // _DEBUG


#if defined _UNITTEST
bool gmShapeImp::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmShapeImp");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented");
   TESTME_EPILOG("gmShapeImp");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void gmShapeImp::MakeCopy(const gmShapeImp& rOther)
{
   m_IsSolid            = rOther.m_IsSolid;
   m_pParent            = rOther.m_pParent;            
   m_BorderMode         = rOther.m_BorderMode;         
   m_FillMode           = rOther.m_FillMode;           
   m_BorderColor        = rOther.m_BorderColor;        
   m_FillColor          = rOther.m_FillColor;          

   m_ListenerList       = rOther.m_ListenerList;       
   m_DamageCount        = rOther.m_DamageCount;        
   m_DamageTypeTally    = rOther.m_DamageTypeTally;    
}

void gmShapeImp::MakeAssignment(const gmShapeImp& rOther)
{
   Clean();
   Init();

   MakeCopy( rOther );
}


void gmShapeImp::SetParent(gmCompositeShape* pParent)
{
   ASSERTVALID;
   m_pParent = pParent;
}

void gmShapeImp::NotifyAllListeners( Int32 lHint)
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
         (*it)->OnUpdate(this, lHint);
      }

      // notify the parent also
      if (m_pParent)
         m_pParent->NotifyAllListeners(lHint);
   }
}

void gmShapeImp::DoRegisterListeners(const gmShapeImp& rOwner)
{
   // copy listeners from owner shape to this shape. Append them if
   // this already has listeners.
   ConstListenerListIterator it;
   for (it=rOwner.m_ListenerList.begin(); it!=rOwner.m_ListenerList.end(); it++)
   {
      DoRegisterListener(*it);
   }
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmShapeImp::Init()
{
   m_IsSolid = true;  // solid by default
   m_pParent  = nullptr;
   m_BorderMode = true;
   m_FillMode   = true;
   m_BorderColor = RGB(0,0,0); // black border
   m_FillColor   = RGB(255,255,255); // white fill

   // listeners
   m_DamageCount      = 0;
   m_DamageTypeTally  = 0;
   ASSERTVALID;
}

void gmShapeImp::Clean()
{
   ASSERTVALID;

   // Check if all listeners have been unregistered - crap in debug if not.
   // Clean up as best we can in release.
   if (m_ListenerList.size() > 0)
   {
      CHECKX(0,_T("Tried to delete shape that still has listeners"));
      ListenerListIterator it;
      for (it=m_ListenerList.begin(); it!=m_ListenerList.end(); it++)
      {
         (*it)->OnUnregistered(this);
      }
      m_ListenerList.clear();

   }
}

void gmShapeImp::DoRegisterListener(gmShapeListener* pListener)
{
   PRECONDITION(pListener);
   // add listener to list
   if (!m_ListenerList.insert(pListener).second)
      WARN(0,_T("Listener insertion failed - probably duplicate"));

   pListener->OnRegistered(this);
}


//======================== ACCESS     =======================================
//======================== INQUERY    =======================================



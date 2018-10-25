///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#include <Material\MatLib.h>
#include <Material\Metal.h>
#include <Material\MetalListener.h>
#include <Float.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matMetal
****************************************************************************/


typedef std::set<matMetalListener*, std::less<matMetalListener*>, std::allocator<matMetalListener*> > MatListeners;

void unregister_all_listeners(MatListeners* pListeners,matMetal* pMetal)
{
   MatListeners::iterator i;
   for ( i = pListeners->begin(); i != pListeners->end(); i++ )
   {
      (*i)->OnUnregistered( pMetal );
   }
   pListeners->clear();
}

void register_all_listeners(const MatListeners& listeners,matMetal* pMetal)
{
   MatListeners::const_iterator i;
   for ( i = listeners.begin(); i != listeners.end(); i++ )
   {
      (*i)->OnRegistered( pMetal );
   }
}

void notify_listeners(const MatListeners& listeners, matMetal* pMetal)
{
   MatListeners::const_iterator i;
   for ( i = listeners.begin(); i != listeners.end(); i++ )
   {
      (*i)->OnMetalChanged( pMetal );
   }
}

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matMetal::matMetal(const std::_tstring& name,
                   Float64 density,
                   Float64 modE,
                   Float64 yieldStress,
                   Float64 ultStrain,
                   Float64 ultStress,
                   Float64 ruptureStrain,
                   Float64 ruptureStress) :
m_Name( name )
{
   m_Density       = density;
   m_ModE          = modE;
   m_YieldStress   = yieldStress;
   m_UltStrain     = ultStrain;
   m_UltStress     = ultStress;
   m_RuptureStrain = ruptureStrain;
   m_RuptureStress = ruptureStress;

   m_bIsDamaged = false;

   ASSERTVALID;
}

matMetal::matMetal(const std::_tstring& name,
                   Float64 density,
                   Float64 modE,
                   Float64 yieldStress) :
m_Name( name )
{
   m_Density       = density;
   m_ModE          = modE;
   m_YieldStress   = yieldStress;
   m_UltStrain     = DBL_MAX;
   m_UltStress     = yieldStress;
   m_RuptureStrain = DBL_MAX;
   m_RuptureStress = yieldStress;

   m_bIsDamaged = false;

   ASSERTVALID;
}


matMetal::~matMetal()
{
   CHECK( ListenerCount() == 0 );
}

//======================== OPERATORS  =======================================

//======================== OPERATIONS =======================================
void matMetal::RegisterListener(matMetalListener* pListener)
{
   WARN( pListener == 0, "pListener is zero" );

   if ( pListener )
   {
      m_Listeners.insert( pListener );
      pListener->OnRegistered( this );
   }
}

void matMetal::UnregisterListener(matMetalListener* pListener)
{
   if ( pListener == 0 )
   {
      unregister_all_listeners( &m_Listeners, this );
   }
   else
   {
      MatListeners::iterator found;
      found = m_Listeners.find( pListener );
      WARN( found == m_Listeners.end(), "pListener was not previously registered" );
      if ( found != m_Listeners.end() )
      {
         (*found)->OnUnregistered( this );
         m_Listeners.erase( found );
      }
   }
}

matMetal* matMetal::CreateClone(bool bRegisterListeners) const
{
   matMetal* p_clone = new matMetal( *this );
   if ( bRegisterListeners )
      register_all_listeners( m_Listeners, p_clone );

   return p_clone;
}

void matMetal::BeginDamage()
{
   m_bIsDamaged = true;
}

void matMetal::EndDamage()
{
   m_bIsDamaged = false;
   NotifyAllListeners();
}

//======================== ACCESS     =======================================
void matMetal::SetName(const std::_tstring& name)
{
   m_Name = name;
   NotifyAllListeners();
}

std::_tstring matMetal::GetName() const
{
   return m_Name;
}

void matMetal::SetDensity(Float64 density)
{
   PRECONDITION( density > 0 );
   m_Density = density;
   NotifyAllListeners();
   ASSERTVALID;
}

Float64 matMetal::GetDensity() const
{
   return m_Density;
}

void matMetal::SetE(Float64 modE)
{
   PRECONDITION( modE > 0 );
   m_ModE = modE;
   NotifyAllListeners();
   ASSERTVALID;
}

Float64 matMetal::GetE() const
{
   return m_ModE;
}

void matMetal::SetYieldStress(Float64 yieldStress)
{
   PRECONDITION( yieldStress >= 0 );
   m_YieldStress = yieldStress;
   NotifyAllListeners();
   ASSERTVALID;
}

Float64 matMetal::GetYieldStress() const
{
   return m_YieldStress;
}

Float64 matMetal::GetYieldStrain() const
{
   return m_YieldStress/m_ModE;
}

void matMetal::SetUltStrain(Float64 ultStrain)
{
   PRECONDITION( ultStrain >= 0 );
   m_UltStrain = ultStrain;
   NotifyAllListeners();
   ASSERTVALID;
}

Float64 matMetal::GetUltStrain() const
{
   return m_UltStrain;
}

void matMetal::SetUltStress(Float64 ultStress)
{
   PRECONDITION( ultStress >= 0 );
   m_UltStress = ultStress;
   NotifyAllListeners();
   ASSERTVALID;
}

Float64 matMetal::GetUltStress() const
{
   return m_UltStress;
}

void matMetal::SetRuptureStrain(Float64 ruptureStrain)
{
   PRECONDITION( ruptureStrain >= 0 );
   m_RuptureStrain = ruptureStrain;
   NotifyAllListeners();
   ASSERTVALID;
}

Float64 matMetal::GetRuptureStrain() const
{
   return m_RuptureStrain;
}

void matMetal::SetRuptureStress(Float64 ruptureStress)
{
   PRECONDITION( ruptureStress >= 0 );
   m_RuptureStress = ruptureStress;
   NotifyAllListeners();
   ASSERTVALID;
}

Float64 matMetal::GetRuptureStress() const
{
   return m_RuptureStress;
}

//======================== INQUIRY    =======================================
CollectionIndexType matMetal::ListenerCount() const
{
   return m_Listeners.size();
}

bool matMetal::IsDamaged() const
{
   return m_bIsDamaged;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool matMetal::AssertValid() const
{
   if ( m_Density <= 0 )
      return false;

   if ( m_ModE <= 0 )
      return false;

   if ( m_YieldStress <= 0 )
      return false;

   if ( m_UltStrain <= 0 )
      return false;

   if ( m_UltStress <= 0 )
      return false;

   if ( m_RuptureStrain <= 0 )
      return false;

   if ( m_RuptureStress <= 0 )
      return false;

   if ( m_RuptureStrain < m_UltStrain )
      return false;

   if ( m_UltStress < m_YieldStress || m_UltStress < m_RuptureStress )
      return false;

   return true;
}

void matMetal::Dump(dbgDumpContext& os) const
{
   os << "Dump for matMetal" << endl;
   os << "=================" << endl;
   os << "Name           : " << m_Name.c_str() << endl;
   os << "Density        : " << m_Density << endl;
   os << "Mod E          : " << m_ModE << endl;
   os << "Yield Stess    : " << m_YieldStress << endl;
   os << "Ult Strain     : " << m_UltStrain << endl;
   os << "Ult Stress     : " << m_UltStress << endl;
   os << "Rupture Strain : " << m_RuptureStrain << endl;
   os << "Rupture Stress : " << m_RuptureStress << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool matMetal::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("matMetal");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for matMetal");
   TESTME_EPILOG("matMetal");
}
#endif // _UNITTEST


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

matMetal::matMetal(const matMetal& rOther)
{
   m_bIsDamaged = false;

   MakeCopy(rOther);
}

//======================== OPERATORS  =======================================
matMetal& matMetal::operator= (const matMetal& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void matMetal::MakeCopy(const matMetal& rOther)
{
   m_Name          = rOther.m_Name;
   m_Density       = rOther.m_Density;
   m_ModE          = rOther.m_ModE;
   m_YieldStress   = rOther.m_YieldStress;
   m_UltStrain     = rOther.m_UltStrain;
   m_UltStress     = rOther.m_UltStress;
   m_RuptureStrain = rOther.m_RuptureStrain;
   m_RuptureStress = rOther.m_RuptureStress;

   ASSERTVALID;
}

void matMetal::MakeAssignment(const matMetal& rOther)
{
   MakeCopy( rOther );
}

void matMetal::NotifyAllListeners()
{
   if ( !m_bIsDamaged )
      notify_listeners( m_Listeners, this );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================




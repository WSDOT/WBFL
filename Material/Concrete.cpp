///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2010  Washington State Department of Transportation
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
#include <Material\Concrete.h>
#include <Material\ConcreteListener.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matConcrete
****************************************************************************/


typedef std::set<matConcreteListener*, std::less<matConcreteListener*>, std::allocator<matConcreteListener*> > ConcListener;
void unregister_all_listeners(ConcListener* pListeners,matConcrete* pConcrete)
{
   ConcListener::iterator i;
   for ( i = pListeners->begin(); i != pListeners->end(); i++ )
   {
      (*i)->OnUnregistered( pConcrete );
   }
   pListeners->clear();
}

void register_all_listeners(const ConcListener& listeners,matConcrete* pConcrete)
{
   ConcListener::const_iterator i;
   for ( i = listeners.begin(); i != listeners.end(); i++ )
   {
      pConcrete->RegisterListener( *i );
   }
}

void notify_listeners(const ConcListener& listeners, matConcrete* pConcrete)
{
   ConcListener::const_iterator i;
   for ( i = listeners.begin(); i != listeners.end(); i++ )
   {
      (*i)->OnConcreteChanged( pConcrete );
   }
}

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matConcrete::matConcrete() :
m_Name( _T("Unknown") ),
m_Fc( 0 ),
m_Density( 0 ),
m_ModE( 0 ),
m_MaxAggregateSize(0),
m_Type(matConcrete::Normal),
m_Fct(0),
m_bHasFct(false)
{
   m_bIsDamaged = false;
   // Don't call assert value because this material model is not valid.
}

matConcrete::matConcrete(const std::_tstring& name,Float64 fc,Float64 density,Float64 modE) :
m_Name(name),
m_Fc(fc),
m_Density(density),
m_ModE( modE ),
m_MaxAggregateSize(0.0),
m_Type(matConcrete::Normal),
m_Fct(0),
m_bHasFct(false)
{
   m_bIsDamaged = false;
   ASSERTVALID;
}

matConcrete::~matConcrete()
{
   CHECK( ListenerCount() == 0 );
}

//======================== OPERATORS  =======================================
void matConcrete::SetType(matConcrete::Type type)
{
   if ( m_Type != type )
   {
      m_Type = type;
      NotifyAllListeners();
   }
}

matConcrete::Type matConcrete::GetType() const
{
   return m_Type;
}

void matConcrete::SetAggSplittingStrength(Float64 fct)
{
   if ( !IsEqual(m_Fct,fct) )
   {
      m_Fct = fct;
      NotifyAllListeners();
   }
}

Float64 matConcrete::GetAggSplittingStrength() const
{
   return m_Fct;
}

void matConcrete::HasAggSplittingStrength(bool bHasFct)
{
   m_bHasFct = bHasFct;
}

bool matConcrete::HasAggSplittingStrength() const
{
   return m_bHasFct;
}

std::_tstring matConcrete::GetTypeName(matConcrete::Type type,bool bFull)
{
   switch(type)
   {
   case matConcrete::Normal:
      return bFull ? _T("Normal Weight Concrete") : _T("Normal");

   case matConcrete::AllLightweight:
      return bFull ? _T("All Lightweight Concrete") : _T("AllLightweight");

   case matConcrete::SandLightweight:
      return bFull ? _T("Sand Lightweight Concrete") : _T("SandLightweight");

   default:
      ATLASSERT(false); // is there a new type?
      return bFull ? _T("Normal Weight Concrete") : _T("Normal");
   }
}

matConcrete::Type matConcrete::GetTypeFromName(LPCTSTR strName)
{
   if ( std::_tstring(strName) == _T("Normal") )
      return matConcrete::Normal;

   if ( std::_tstring(strName) == _T("AllLightweight") )
      return matConcrete::AllLightweight;

   if ( std::_tstring(strName) == _T("SandLightweight") )
      return matConcrete::SandLightweight;

   ATLASSERT(false); // invalid name
   return matConcrete::Normal;
}

//======================== OPERATIONS =======================================
void matConcrete::RegisterListener(matConcreteListener* pListener)
{
   WARN( pListener == 0, _T("pListener is zero") );

   if ( pListener )
   {
      m_Listeners.insert( pListener );
      pListener->OnRegistered( this );
   }
}

void matConcrete::UnregisterListener(matConcreteListener* pListener)
{
   if ( pListener == 0 )
   {
      unregister_all_listeners( &m_Listeners, this );
   }
   else
   {
      ConcListener::iterator found;
      found = m_Listeners.find( pListener );
      WARN( found == m_Listeners.end(), _T("pListener was not previously registered") );
      if ( found != m_Listeners.end() )
      {
         (*found)->OnUnregistered( this );
         m_Listeners.erase( found );
      }
   }
}

matConcrete* matConcrete::CreateClone(bool bRegisterListeners) const
{
   matConcrete* p_clone = new matConcrete( *this );

   if ( bRegisterListeners )
      register_all_listeners( m_Listeners, p_clone );

   return p_clone;
}

void matConcrete::BeginDamage()
{
   m_bIsDamaged = true;
}

void matConcrete::EndDamage()
{
   m_bIsDamaged = false;
   NotifyAllListeners();
}

//======================== ACCESS     =======================================
void matConcrete::SetName(const std::_tstring& name)
{
   m_Name = name;
   NotifyAllListeners();
}

std::_tstring matConcrete::GetName() const
{
   return m_Name;
}

void matConcrete::SetFc(Float64 fc)
{
   PRECONDITION( fc > 0 );
   if ( !IsEqual( m_Fc, fc ) )
   {
      m_Fc = fc;
      NotifyAllListeners();
      ASSERTVALID;
   }
}

Float64 matConcrete::GetFc() const
{
   return m_Fc;
}

void matConcrete::SetDensity(Float64 density)
{
   PRECONDITION( density > 0 );
   if ( !IsEqual( m_Density, density ) )
   {
      m_Density = density;
      NotifyAllListeners();
      ASSERTVALID;
   }
}

Float64 matConcrete::GetDensity() const
{
   return m_Density;
}

void matConcrete::SetE(Float64 modE)
{
   PRECONDITION( modE > 0 );
   if ( !IsEqual( m_ModE, modE ) )
   {
      m_ModE = modE;
      NotifyAllListeners();
      ASSERTVALID;
   }
}

Float64 matConcrete::GetE() const
{
   return m_ModE;
}

void matConcrete::SetMaxAggregateSize(Float64 size)
{
   if ( !IsEqual(m_MaxAggregateSize,size) )
   {
      m_MaxAggregateSize = size;
      NotifyAllListeners();
   }
}

Float64 matConcrete::GetMaxAggregateSize() const
{
   return m_MaxAggregateSize;
}

//======================== INQUIRY    =======================================
Int32 matConcrete::ListenerCount() const
{
   return m_Listeners.size();
}

bool matConcrete::IsDamaged() const
{
   return m_bIsDamaged;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool matConcrete::AssertValid() const
{
   if ( !(m_Fc > 0) )
      return false;

   if ( !(m_Density > 0) )
      return false;

   if ( !(m_ModE > 0) )
      return false;

   return true;
}

void matConcrete::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for matConcrete")         << endl;
   os << _T("====================")         << endl;
   os << _T("Name    : ") << m_Name.c_str() << endl;
   os << _T("Fc      : ") << m_Fc           << endl;
   os << _T("Density : ") << m_Density      << endl;
   os << _T("Mod E   : ") << m_ModE         << endl;
   os << _T("Max Aggr: ") << m_MaxAggregateSize<<endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool matConcrete::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("matConcrete");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for matConcrete");
   TESTME_EPILOG("matConcrete");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

matConcrete::matConcrete(const matConcrete& rOther)
{
   m_bIsDamaged = false;
   MakeCopy(rOther);
}

//======================== OPERATORS  =======================================
matConcrete& matConcrete::operator= (const matConcrete& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
      NotifyAllListeners();
   }

   return *this;
}

//======================== OPERATIONS =======================================
void matConcrete::MakeCopy(const matConcrete& rOther)
{
   m_Name      = rOther.m_Name;
   m_Fc        = rOther.m_Fc;
   m_Density   = rOther.m_Density;
   m_ModE      = rOther.m_ModE;
   m_MaxAggregateSize = rOther.m_MaxAggregateSize;
   m_Type      = rOther.m_Type;
   m_Fct        = rOther.m_Fct;
   m_bHasFct    = rOther.m_bHasFct;

   ASSERTVALID;
}

void matConcrete::MakeAssignment(const matConcrete& rOther)
{
   MakeCopy( rOther );
}

void matConcrete::RegisterListenersWithOther(matConcrete* pOther) const
{
   register_all_listeners(m_Listeners,pOther);
}

void matConcrete::NotifyAllListeners()
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



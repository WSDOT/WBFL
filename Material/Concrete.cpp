///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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
m_FiberLength(0),
m_Type(matConcrete::Normal),
m_Fct(0),
m_bHasFct(false),
m_Lambda(1.0),
m_ffc(0),
m_frr(0),
m_AutogenousShrinkage(0)
{
   m_bIsDamaged = false;
   // Don't call assert value because this material model is not valid.
}

matConcrete::matConcrete(const std::_tstring& name, Float64 fc, Float64 density, Float64 modE) :
   m_Name(name),
   m_Fc(fc),
   m_Density(density),
   m_ModE(modE),
   m_MaxAggregateSize(0.0),
   m_FiberLength(0.0),
   m_Type(matConcrete::Normal),
   m_Fct(0),
   m_bHasFct(false),
   m_Lambda(1.0),
   m_ffc(0),
   m_frr(0),
   m_AutogenousShrinkage(0)
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

   case matConcrete::PCI_UHPC:
      return bFull ? _T("PCI Ultra High Performance Concrete (PCI-UHPC)") : _T("PCI-UHPC");

   default:
      ATLASSERT(false); // is there a new type?
      return bFull ? _T("Normal Weight Concrete") : _T("Normal");
   }
}

matConcrete::Type matConcrete::GetTypeFromTypeName(LPCTSTR strName)
{
   if ( std::_tstring(strName) == _T("Normal") )
      return matConcrete::Normal;

   if ( std::_tstring(strName) == _T("AllLightweight") )
      return matConcrete::AllLightweight;

   if ( std::_tstring(strName) == _T("SandLightweight") )
      return matConcrete::SandLightweight;

   if (std::_tstring(strName) == _T("PCI-UHPC"))
      return matConcrete::PCI_UHPC;

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

void matConcrete::SetFiberLength(Float64 length)
{
   if (!IsEqual(m_FiberLength, length))
   {
      m_FiberLength = length;
      NotifyAllListeners();
   }
}

Float64 matConcrete::GetFiberLength() const
{
   return m_FiberLength;
}

void matConcrete::SetLambda(Float64 lambda)
{
   if ( !IsEqual(m_Lambda,lambda) )
   {
      m_Lambda = lambda;
      NotifyAllListeners();
   }
}

Float64 matConcrete::GetLambda() const
{
   return m_Lambda;
}

void matConcrete::SetFirstCrackStrength(Float64 ffc)
{
   if (!IsEqual(m_ffc, ffc))
   {
      m_ffc = ffc;
      NotifyAllListeners();
   }
}

Float64 matConcrete::GetFirstCrackStrength() const
{
   return m_ffc;
}

void matConcrete::SetPostCrackingTensileStrength(Float64 frr)
{
   if (!IsEqual(m_frr, frr))
   {
      m_frr = frr;
      NotifyAllListeners();
   }
}

Float64 matConcrete::GetPostCrackingTensileStrength() const
{
   return m_frr;
}

void matConcrete::SetAutogenousShrinkage(Float64 as)
{
   if (!IsEqual(m_AutogenousShrinkage, as))
   {
      m_AutogenousShrinkage = as;
      NotifyAllListeners();
   }
}

Float64 matConcrete::GetAutogenousShrinkage() const
{
   return m_AutogenousShrinkage;
}

//======================== INQUIRY    =======================================
CollectionIndexType matConcrete::ListenerCount() const
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
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void matConcrete::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for matConcrete")         << WBFL::Debug::endl;
   os << _T("====================")         << WBFL::Debug::endl;
   os << _T("Name    : ") << m_Name.c_str() << WBFL::Debug::endl;
   os << _T("Fc      : ") << m_Fc           << WBFL::Debug::endl;
   os << _T("Density : ") << m_Density      << WBFL::Debug::endl;
   os << _T("Mod E   : ") << m_ModE         << WBFL::Debug::endl;
   os << _T("Max Aggr: ") << m_MaxAggregateSize<< WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool matConcrete::TestMe(WBFL::Debug::Log& rlog)
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

bool matConcrete::operator==(const matConcrete& rOther) const
{
   if ( m_Name != rOther.m_Name )
      return false;

   if ( !::IsEqual(m_Fc,rOther.m_Fc) )
      return false;

   if ( !::IsEqual(m_Density,rOther.m_Density) )
      return false;

   if ( !::IsEqual(m_ModE,rOther.m_ModE) )
      return false;

   if (!::IsEqual(m_MaxAggregateSize, rOther.m_MaxAggregateSize))
      return false;

   if (!::IsEqual(m_FiberLength, rOther.m_FiberLength))
      return false;

   if ( m_Type != rOther.m_Type )
      return false;

   if ( !::IsEqual(m_Fct,rOther.m_Fct) )
      return false;

   if ( m_bHasFct != rOther.m_bHasFct )
      return false;

   if ( !::IsEqual(m_Lambda,rOther.m_Lambda) )
      return false;

   if (!::IsEqual(m_ffc, rOther.m_ffc))
      return false;

   if (!::IsEqual(m_frr, rOther.m_frr))
      return false;

   if (!::IsEqual(m_AutogenousShrinkage, rOther.m_AutogenousShrinkage))
      return false;

   return true;
}

bool matConcrete::operator!=(const matConcrete& rOther) const
{
   return !operator==(rOther);
}

//======================== OPERATIONS =======================================
void matConcrete::MakeCopy(const matConcrete& rOther)
{
   m_Name      = rOther.m_Name;
   m_Fc        = rOther.m_Fc;
   m_Density   = rOther.m_Density;
   m_ModE      = rOther.m_ModE;
   m_MaxAggregateSize = rOther.m_MaxAggregateSize;
   m_FiberLength = rOther.m_FiberLength;
   m_Type      = rOther.m_Type;
   m_Fct        = rOther.m_Fct;
   m_bHasFct    = rOther.m_bHasFct;
   m_Lambda     = rOther.m_Lambda;
   m_ffc = rOther.m_ffc;
   m_frr = rOther.m_frr;
   m_AutogenousShrinkage = rOther.m_AutogenousShrinkage;

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



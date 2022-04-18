///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\LoadModifier.h>
#include <Lrfd\VersionMgr.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdLoadModifier
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdLoadModifier::lrfdLoadModifier()
{
   m_Ductility  = 1.0;
   m_Redundancy = 1.0;
   m_Importance = 1.0;
   m_DuctilityLevel = Normal;
   m_ImportanceLevel = Normal;
   m_RedundancyLevel = Normal;
}

lrfdLoadModifier::lrfdLoadModifier(const lrfdLoadModifier& rOther)
{
   MakeCopy(rOther);
}

lrfdLoadModifier::~lrfdLoadModifier()
{
}

//======================== OPERATORS  =======================================
lrfdLoadModifier& lrfdLoadModifier::operator= (const lrfdLoadModifier& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 lrfdLoadModifier::LoadModifier(lrfdTypes::LimitState ls,lrfdTypes::Optimization opt) const
{
   Float64 n;
   if ( ls == lrfdTypes::StrengthI   ||
        ls == lrfdTypes::StrengthII  ||
        ls == lrfdTypes::StrengthIII ||
        ls == lrfdTypes::StrengthIV )
   {
      n = m_Ductility * m_Importance * m_Redundancy;

      if ( lrfdVersionMgr::GetVersion() == lrfdVersionMgr::FirstEdition1994 )
      {
         n = max(n,0.95);
      }
      else
      {
         if ( opt == lrfdTypes::Max )
         {
            n = max(n,0.95);
         }
         else
         {
            n = 1.0/n;
            n = min(n,1.00);
         }
      }   
   }
   else
   {
      n = 1.0;
   }

   return n;
}

//======================== ACCESS     =======================================
void set_load_modifiers(lrfdLoadModifier::Level level,Float64 np,Float64* pn)
{
   if ( level == lrfdLoadModifier::Normal )
   {
      *pn = 1.0;
   }
   else
   {
      if ( IsZero(np) )
      {
         if ( level == lrfdLoadModifier::High )
            *pn = 1.05;
         else
            *pn = 0.95;
      }
      else
      {
         *pn = np;
      }
   }
}

void lrfdLoadModifier::SetDuctilityFactor(Level level,Float64 nd)
{
   m_DuctilityLevel = level;
   set_load_modifiers(level,nd,&m_Ductility);
   ASSERTVALID;
}

Float64 lrfdLoadModifier::GetDuctilityFactor() const
{
   return m_Ductility;
}

lrfdLoadModifier::Level lrfdLoadModifier::GetDuctilityLevel() const
{
   return m_DuctilityLevel;
}

void lrfdLoadModifier::SetImportanceFactor(Level level,Float64 ni)
{
   m_ImportanceLevel = level;
   set_load_modifiers(level,ni,&m_Importance);
   ASSERTVALID;
}

Float64 lrfdLoadModifier::GetImportanceFactor() const
{
   return m_Importance;
}

lrfdLoadModifier::Level lrfdLoadModifier::GetImportanceLevel() const
{
   return m_ImportanceLevel;
}

void lrfdLoadModifier::SetRedundancyFactor(Level level,Float64 nr)
{
   m_RedundancyLevel = level;
   set_load_modifiers(level,nr,&m_Redundancy);
   ASSERTVALID;
}

Float64 lrfdLoadModifier::GetRedundancyFactor() const
{
   return m_Redundancy;
}

lrfdLoadModifier::Level lrfdLoadModifier::GetRedundancyLevel() const
{
   return m_RedundancyLevel;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdLoadModifier::MakeCopy(const lrfdLoadModifier& rOther)
{
   // Add copy code here...
   m_Ductility  = rOther.m_Ductility;
   m_Redundancy = rOther.m_Redundancy;
   m_Importance = rOther.m_Importance;
   m_DuctilityLevel  = rOther.m_DuctilityLevel;
   m_ImportanceLevel = rOther.m_ImportanceLevel;
   m_RedundancyLevel = rOther.m_RedundancyLevel;
}

void lrfdLoadModifier::MakeAssignment(const lrfdLoadModifier& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool is_valid(lrfdLoadModifier::Level level,Float64 n)
{
   if ( level == lrfdLoadModifier::Normal && IsEqual(n,1.0) )
      return true;

   if ( level == lrfdLoadModifier::Low && !(n < 0.95) )
      return true;

   if ( level == lrfdLoadModifier::High && !(n < 1.05) )
      return true;

   return false;
}

bool lrfdLoadModifier::AssertValid() const
{
   if ( !is_valid(m_DuctilityLevel,m_Ductility) )
      return false;

   if ( !is_valid(m_ImportanceLevel,m_Importance) )
      return false;

   if ( !is_valid(m_RedundancyLevel,m_Redundancy) )
      return false;

   return true;
}

void lrfdLoadModifier::Dump(dbgDumpContext& os) const
{
   os << "Dump for lrfdLoadModifier" << endl;
   os << "m_Ductility  = " << m_Ductility << endl;
   os << "m_Redundancy = " << m_Redundancy << endl;
   os << "m_Importance = " << m_Importance << endl;
   os << "m_DuctilityLevel  = " << m_DuctilityLevel << endl;
   os << "m_ImportanceLevel = " << m_ImportanceLevel << endl;
   os << "m_RedundancyLevel = " << m_RedundancyLevel << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <Lrfd\AutoVersion.h>
bool lrfdLoadModifier::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdLoadModifier");

   lrfdAutoVersion av;

   lrfdLoadModifier lm;

   // Test First Edition Implementation
   lrfdVersionMgr::SetVersion( lrfdVersionMgr::FirstEdition1994 );
   lm.SetDuctilityFactor( lrfdLoadModifier::High );
   lm.SetImportanceFactor( lrfdLoadModifier::High );
   lm.SetRedundancyFactor( lrfdLoadModifier::High );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI), 1.157625 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Min), 1.157625 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueII,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Max), 1.157625 ) );

   lm.SetDuctilityFactor( lrfdLoadModifier::Normal );
   lm.SetImportanceFactor( lrfdLoadModifier::Normal );
   lm.SetRedundancyFactor( lrfdLoadModifier::Normal );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI), 1.0 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Min), 1.0 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Max), 1.0 ) );

   lm.SetDuctilityFactor( lrfdLoadModifier::Low );
   lm.SetImportanceFactor( lrfdLoadModifier::Low );
   lm.SetRedundancyFactor( lrfdLoadModifier::Low );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI), 0.95 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Min), 0.95 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Max), 0.95 ) );

   lm.SetDuctilityFactor( lrfdLoadModifier::Low, 0.98 );
   lm.SetImportanceFactor( lrfdLoadModifier::Low, 0.98 );
   lm.SetRedundancyFactor( lrfdLoadModifier::Normal, 10.0 ); // Should ignore the 10.0

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI), 0.9604 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Min), 0.9604 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Max), 0.9604 ) );


   // Test First Edition + 1996, 1997 Interims and Second Edition Implementation
   lrfdVersionMgr::SetVersion( lrfdVersionMgr::SecondEdition1998 );
   lm.SetDuctilityFactor( lrfdLoadModifier::High );
   lm.SetImportanceFactor( lrfdLoadModifier::High );
   lm.SetRedundancyFactor( lrfdLoadModifier::High );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Min), 0.863837598531 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Max), 1.157625 ) );

   lm.SetDuctilityFactor( lrfdLoadModifier::Normal );
   lm.SetImportanceFactor( lrfdLoadModifier::Normal );
   lm.SetRedundancyFactor( lrfdLoadModifier::Normal );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Min), 1.0 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Max), 1.0 ) );

   lm.SetDuctilityFactor( lrfdLoadModifier::Low );
   lm.SetImportanceFactor( lrfdLoadModifier::Low );
   lm.SetRedundancyFactor( lrfdLoadModifier::Low );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Min), 1.0 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Max), 0.95 ) );

   lm.SetDuctilityFactor( lrfdLoadModifier::Low, 0.98 );
   lm.SetImportanceFactor( lrfdLoadModifier::Low, 0.98 );
   lm.SetRedundancyFactor( lrfdLoadModifier::Normal, 10.0 ); // Should ignore the 10.0

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Min), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Min), 1.0 ) );

   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ServiceI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::ExtremeEventI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::FatigueI,lrfdTypes::Max), 1.0 ) );
   TRY_TESTME( IsEqual( lm.LoadModifier(lrfdTypes::StrengthI,lrfdTypes::Max), 0.9604 ) );

   TESTME_EPILOG("LoadModifier");
}
#endif // _UNITTEST

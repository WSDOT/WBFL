///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <Lrfd/BDSManager.h>
#include <MathEx.h>

using namespace WBFL::LRFD;

Float64 LoadModifier::GetLoadModifier(LimitState ls,Optimization opt) const
{
   Float64 n;
   if ( ls == LimitState::StrengthI   ||
        ls == LimitState::StrengthII  ||
        ls == LimitState::StrengthIII ||
        ls == LimitState::StrengthIV )
   {
      n = m_Ductility * m_Importance * m_Redundancy;

      if ( BDSManager::GetEdition() == BDSManager::Edition::FirstEdition1994 )
      {
         n = max(n,0.95);
      }
      else
      {
         if ( opt == Optimization::Max )
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

void set_load_modifiers(LoadModifier::Level level,Float64 np,Float64* pn)
{
   if ( level == LoadModifier::Level::Normal )
   {
      *pn = 1.0;
   }
   else
   {
      if ( IsZero(np) )
      {
         if ( level == LoadModifier::Level::High )
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

void LoadModifier::SetDuctilityFactor(Level level,Float64 nd)
{
   m_DuctilityLevel = level;
   set_load_modifiers(level,nd,&m_Ductility);
   ASSERTVALID;
}

Float64 LoadModifier::GetDuctilityFactor() const
{
   return m_Ductility;
}

LoadModifier::Level LoadModifier::GetDuctilityLevel() const
{
   return m_DuctilityLevel;
}

void LoadModifier::SetImportanceFactor(Level level,Float64 ni)
{
   m_ImportanceLevel = level;
   set_load_modifiers(level,ni,&m_Importance);
   ASSERTVALID;
}

Float64 LoadModifier::GetImportanceFactor() const
{
   return m_Importance;
}

LoadModifier::Level LoadModifier::GetImportanceLevel() const
{
   return m_ImportanceLevel;
}

void LoadModifier::SetRedundancyFactor(Level level,Float64 nr)
{
   m_RedundancyLevel = level;
   set_load_modifiers(level,nr,&m_Redundancy);
   ASSERTVALID;
}

Float64 LoadModifier::GetRedundancyFactor() const
{
   return m_Redundancy;
}

LoadModifier::Level LoadModifier::GetRedundancyLevel() const
{
   return m_RedundancyLevel;
}

#if defined _DEBUG
bool is_valid(LoadModifier::Level level,Float64 n)
{
   if ( level == LoadModifier::Level::Normal && IsEqual(n,1.0) )
      return true;

   if ( level == LoadModifier::Level::Low && !(n < 0.95) )
      return true;

   if ( level == LoadModifier::Level::High && !(n < 1.05) )
      return true;

   return false;
}

bool LoadModifier::AssertValid() const
{
   if ( !is_valid(m_DuctilityLevel,m_Ductility) )
      return false;

   if ( !is_valid(m_ImportanceLevel,m_Importance) )
      return false;

   if ( !is_valid(m_RedundancyLevel,m_Redundancy) )
      return false;

   return true;
}
#endif // _DEBUG

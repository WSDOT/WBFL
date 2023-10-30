///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <Lrfd\NoncompositeApproximateLosses2005.h>
#include <Lrfd\ElasticShortening.h>
#include <Lrfd/BDSManager.h>
#include <Lrfd\XPsLosses.h>
#include <System\XProgrammingError.h>

using namespace WBFL::LRFD;

NoncompositeApproximateLosses2005::NoncompositeApproximateLosses2005()
{
   Init();

   m_BeamType = BeamType::SingleT;
   m_Level = Level::Average;
   m_Grade = WBFL::Materials::PsStrand::Grade::Gr1860;
   m_Type  = WBFL::Materials::PsStrand::Type::LowRelaxation;
   m_Eci   = WBFL::Units::ConvertToSysUnits(  25000, WBFL::Units::Measure::MPa );
   m_Ep    = PsStrand::GetModE();
   m_Fpu   = PsStrand::GetUltimateStrength( m_Grade );
   m_Fpj   = 0.80*m_Fpu;
   m_Fpy   = PsStrand::GetYieldStrength( m_Grade, m_Type );
   m_Aps   = WBFL::Units::ConvertToSysUnits( 1, WBFL::Units::Measure::Millimeter2 );
   m_Ag    = WBFL::Units::ConvertToSysUnits( 1, WBFL::Units::Measure::Millimeter2 );
   m_Ig    = WBFL::Units::ConvertToSysUnits( 1, WBFL::Units::Measure::Millimeter4 );
   m_Ybg   = 0;
   m_e     = 0;
   m_eperm = 0;
   m_Mdlg  = 0;
   m_Fc    = WBFL::Units::ConvertToSysUnits(  48, WBFL::Units::Measure::MPa );;
   m_PPR   = 1.0;
   m_K = 1;
}

NoncompositeApproximateLosses2005::NoncompositeApproximateLosses2005(WBFL::Materials::PsStrand::Grade gr,
                           WBFL::Materials::PsStrand::Type type,
                           BeamType beamType,
                           Level level,
                           Float64 fpj,
                           Float64 Ag,   // area of girder
                           Float64 Ig,   // moment of inertia of girder
                           Float64 Ybg,  // Centroid of girder measured from bottom
                           Float64 e,   // eccentricity of ps strands
                           Float64 eperm,
                           Float64 aps,
                           Float64 Mdlg,  // Dead load moment of girder only
                           Float64 K,
                           Float64 Eci, // Modulus of elasticity of concrete at transfer
                           Float64 Fc,
                           Float64 PPR,
                           Float64 t )   // Time until prestress transfer
{
   Init();

   m_Grade = gr;
   m_Type  = type;
   m_BeamType = beamType;
   m_Level = level;
   m_Fpj   = fpj;
   m_Eci   = Eci;
   m_Ep    = PsStrand::GetModE();
   m_Fpu   = PsStrand::GetUltimateStrength( m_Grade );
   m_Fpy   = PsStrand::GetYieldStrength( m_Grade, m_Type );
   m_Time  = t;
   m_Ag    = Ag;
   m_Ig    = Ig;
   m_Ybg   = Ybg;
   m_e     = e;
   m_eperm = eperm;
   m_Aps   = aps;
   m_Mdlg  = Mdlg;
   m_Fc    = Fc;
   m_PPR   = PPR;
   m_K     = K;
}

void NoncompositeApproximateLosses2005::OnUpdate()
{
   BDSManagerListener::OnUpdate();

   // Nothing actually changes.
}

Float64 NoncompositeApproximateLosses2005::ElasticShorteningLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfES;
}

Float64 NoncompositeApproximateLosses2005::RelaxationLossesAtXfer() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfR1;
}

Float64 NoncompositeApproximateLosses2005::ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfR1;
}

Float64 NoncompositeApproximateLosses2005::ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfES + m_dfR1;
}

Float64 NoncompositeApproximateLosses2005::ApproxLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfApprox;
}

Float64 NoncompositeApproximateLosses2005::FinalLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfES + m_dfApprox - m_dfR1;
}

Float64 NoncompositeApproximateLosses2005::GetFcgp() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Fcgp;
}

Float64 NoncompositeApproximateLosses2005::GetFpy() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Fpy;
}

Float64 NoncompositeApproximateLosses2005::GetP() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_P;
}

Float64 NoncompositeApproximateLosses2005::GetEp() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Ep;
}

void NoncompositeApproximateLosses2005::Init()
{
   m_IsDirty = true;
   m_Fcgp = 0;
}

void NoncompositeApproximateLosses2005::UpdateLosses() const
{
   if ( !IsZero( m_Fpj ) && !(0.5*m_Fpu < m_Fpj) )
      WBFL_LRFD_THROW(XPsLosses,fpjOutOfRange);

   bool is_si = (BDSManager::GetUnits() == BDSManager::Units::SI);
   // Use a values that are just out of spec to avoid throwing for boundary values
   // that have a little round-off error in them.
   Float64 fcMin = (is_si ? WBFL::Units::ConvertToSysUnits( 27.95, WBFL::Units::Measure::MPa ) : WBFL::Units::ConvertToSysUnits( 3.95, WBFL::Units::Measure::KSI ) );
   Float64 fcMax = (is_si ? WBFL::Units::ConvertToSysUnits( 70.05, WBFL::Units::Measure::MPa ) : WBFL::Units::ConvertToSysUnits( 10.05, WBFL::Units::Measure::KSI ) );
   if ( m_Fc < fcMin || fcMax < m_Fc )
      WBFL_LRFD_THROW(XPsLosses,fcOutOfRange);

   UpdateInitialLosses();
   UpdateLongTermLosses();

   m_IsDirty = false;
}

void NoncompositeApproximateLosses2005::UpdateInitialLosses() const
{
   // Losses from jacking to release
   Float64 t_days = WBFL::Units::ConvertFromSysUnits( m_Time, WBFL::Units::Measure::Day );
   Float64 A = (m_Type == WBFL::Materials::PsStrand::Type::LowRelaxation ? 40. : 10. );

   if ( t_days*24. < 1 )
      m_dfR1 = 0; // log10(<1) = < 0... t_days < 1/24 is less than one hour
   else
      m_dfR1 = (log10(24.*t_days)/A) * (m_Fpj/m_Fpy - 0.55) * m_Fpj;

   // Elastic shortening
   ElasticShortening es(m_Fpj,
                            0,
                            m_dfR1,
                            0,
                            m_Aps,
                            0,
                            true, // gross section properties
                            m_Ag,
                            m_Ig,
                            m_Ig,
                            0,
                            WBFL::Geometry::Point2d(0,m_eperm),
                            WBFL::Geometry::Point2d(0,0),
                            m_Mdlg,
                            1.0,
                            m_Eci,
                            m_Ep,
                            ElasticShortening::FcgpComputationMethod::Iterative);

   m_Fcgp = es.PermanentStrand_Fcgp();
   m_dfES = es.PermanentStrand_ElasticShorteningLosses();
   m_P    = es.P();
}

void NoncompositeApproximateLosses2005::UpdateLongTermLosses() const
{
   // need to make sure spec version is ok
   if (BDSManager::GetEdition() < BDSManager::Edition::ThirdEditionWith2005Interims || BDSManager::Edition::FourthEditionWith2009Interims < BDSManager::GetEdition())
   {
      // Introduced in 3rd edition 2005 and after 4th edition 2009
      WBFL_LRFD_THROW(XPsLosses, Specification);
   }

   if ( IsZero( m_Fpj ) )
   {
      // If the strands aren't jacked, then there can't be losses.
      m_dfApprox = 0.0;
   }
   else
   {
      Float64 losses;
      const WBFL::Units::Stress* p_unit;

      bool is_si = (BDSManager::GetUnits() == BDSManager::Units::SI);

      if ( is_si )
         p_unit = &WBFL::Units::Measure::MPa;
      else
         p_unit = &WBFL::Units::Measure::KSI;

      Float64 lowRelaxReduction = 0.0;
      Float64 fc = WBFL::Units::ConvertFromSysUnits( m_Fc, *p_unit );

      switch (m_BeamType )
      {
      case BeamType::SolidSlab:
          if ( m_Level == Level::UpperBound )
              losses = (is_si ? 200 : 29) + (is_si ? 28 : 4)*m_PPR;
          else
              losses = (is_si ? 180 : 26) + (is_si ? 28 : 4)*m_PPR;

          lowRelaxReduction = is_si ? 41 : 6;
          break;

      case BeamType::BoxBeam:
          if ( m_Level == Level::UpperBound )
              losses = (is_si ? 145 : 21) + (is_si ? 28 : 4)*m_PPR;
          else
              losses = (is_si ? 130 : 19) + (is_si ? 28 : 4)*m_PPR;


          lowRelaxReduction = is_si ? 28 : 4;
          break;

      case BeamType::SingleT:
      case BeamType::DoubleT:
      case BeamType::TripleT:
      case BeamType::HollowCore:
      case BeamType::VoidedSlab:
          if ( m_Level == Level::UpperBound )
              losses = (is_si ? 270 : 39)*(1.0 - 0.15*(fc-(is_si?41:6))/(is_si?41:6)) + (is_si?41:6)*m_PPR;
          else
              losses = (is_si ? 230 : 33)*(1.0 - 0.15*(fc-(is_si?41:6))/(is_si?41:6)) + (is_si?41:6)*m_PPR;

          lowRelaxReduction = is_si ? 55 : 8;
          break;
      }

      if ( m_Type == WBFL::Materials::PsStrand::Type::LowRelaxation )
         losses -= lowRelaxReduction;

      m_dfApprox = WBFL::Units::ConvertToSysUnits( losses, *p_unit );
   }
}

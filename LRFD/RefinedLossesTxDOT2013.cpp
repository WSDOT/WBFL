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
#include <Lrfd\RefinedLossesTxDOT2013.h>
#include <Lrfd\ElasticShortening.h>
#include <Lrfd/BDSManager.h>
#include <Lrfd\XPsLosses.h>
#include <System\XProgrammingError.h>

using namespace WBFL::LRFD;

static Float64 shrinkage_losses(Float64 h, Float64 fci, Float64 Ep);
static Float64 creep_losses(Float64 h, Float64 fci, Float64 Eci, Float64 Ep, Float64 fcgp, Float64 dfcdp);

RefinedLossesTxDOT2013::RefinedLossesTxDOT2013()
{
   Init();

   m_FcgpMethod = ElasticShortening::FcgpComputationMethod::Iterative;
}

RefinedLossesTxDOT2013::RefinedLossesTxDOT2013(Float64 x, // location along girder where losses are computed
                         Float64 Lg,    // girder length
                         Losses::SectionPropertiesType sectionProperties,
                         WBFL::Materials::PsStrand::Grade gradePerm, // strand grade
                         WBFL::Materials::PsStrand::Type typePerm, // strand type
                         WBFL::Materials::PsStrand::Coating coatingPerm, // strand coating (none, epoxy)
                         WBFL::Materials::PsStrand::Grade gradeTemp, // strand grade
                         WBFL::Materials::PsStrand::Type typeTemp, // strand type
                         WBFL::Materials::PsStrand::Coating coatingTemp, // strand coating (none, epoxy)
                         Float64 fpjPerm, // fpj permanent strands
                         Float64 fpjTemp, // fpj of temporary strands
                         Float64 ApsPerm,  // area of permanent strand
                         Float64 ApsTemp,  // area of TTS 
                         Float64 aps,      // area of one strand
                         const WBFL::Geometry::Point2d& epermRelease, // eccentricity of permanent ps strands with respect to CG of girder at release
                         const WBFL::Geometry::Point2d& epermFinal, // eccentricity of permanent ps strands with respect to CG of girder at final
                         const WBFL::Geometry::Point2d& etemp, // eccentricity of temporary strands with respect to CG of girder
                         TempStrandUsage usage,
                         Float64 anchorSet,
                         Float64 wobble,
                         Float64 friction,
                         Float64 angleChange,

                         Float64 Fc,   // 28 day strength of girder concrete
                         Float64 Fci,  // Release strength
                         Float64 FcSlab,   
                         Float64 Ec,   // Modulus of elasticity of girder
                         Float64 Eci,  // Modulus of elasticity of girder at transfer
                         Float64 Ecd,  // Modulus of elasticity of deck

                         Float64 Mdlg,  // Dead load moment of girder only
                         const std::vector<std::pair<Float64, Float64>>& Madlg,  // Additional dead load on girder section (first value is moment, second is elastic gain reduction factor)
                         const std::vector<std::pair<Float64, Float64>>& Msidl1, // Superimposed dead loads, stage 1
                         const std::vector<std::pair<Float64, Float64>>& Msidl2, // Superimposed dead loads, stage 2

                         Float64 Ag,    // Area of girder
                         Float64 Ixx,    // Moment of inertia of girder
                         Float64 Iyy,
                         Float64 Ixy,
                         Float64 Ybg,   // Centroid of girder measured from bottom
                         Float64 Ac1,    // Area of the composite girder and deck
                         Float64 Ic1,    // Moment of inertia of composite
                         Float64 Ybc1,   // Centroid of composite measured from bottom
                         Float64 Ac2,    // Area of the composite girder and deck
                         Float64 Ic2,    // Moment of inertia of composite
                         Float64 Ybc2,   // Centroid of composite measured from bottom

                         Float64 An,   // area of girder
                         Float64 Ixxn,   // moment of inertia of girder
                         Float64 Iyyn,
                         Float64 Ixyn,
                         Float64 Ybn,  // Centroid of girder measured from bottom
                         Float64 Acn,   // area of composite girder
                         Float64 Icn,   // moment of inertia of composite
                         Float64 Ybcn,  // Centroid of composite measured from bottom

                         Float64 rh, // relative humidity

                         Float64 ti,   // Time until prestress transfer
                         Float64 shipping,
                         ElasticShortening::FcgpComputationMethod method,
                         bool bValidateParameters
                         ) :
Losses(x,Lg,sectionProperties,gradePerm,typePerm,coatingPerm,gradeTemp,typeTemp,coatingTemp,fpjPerm,fpjTemp,ApsPerm,ApsTemp,aps,epermRelease,epermFinal,etemp,usage,anchorSet,wobble,friction,angleChange,Fc,Fci,FcSlab,Ec,Eci,Ecd,Mdlg,Madlg,Msidl1,Msidl2, Ag,Ixx,Iyy,Ixy,Ybg,Ac1,Ic1,Ybc1,Ac2,Ic2,Ybc2,An,Ixxn,Iyyn,Ixyn,Ybn,Acn,Icn,Ybcn,rh,ti,/* ignore initial relaxation */ true,bValidateParameters)
{
   Init();

   m_Shipping = shipping;
   m_FcgpMethod = method;
}

Float64 RefinedLossesTxDOT2013::TemporaryStrand_TimeDependentLossesAtShipping() const
{
   return PermanentStrand_TimeDependentLossesAtShipping();
}

Float64 RefinedLossesTxDOT2013::PermanentStrand_TimeDependentLossesAtShipping() const
{
   if ( m_Shipping < 0 )
   {
      return -m_Shipping*TimeDependentLosses();
   }
   else
   {
      return m_Shipping;
   }
}

Float64 RefinedLossesTxDOT2013::TimeDependentLossesBeforeDeck() const
{
   return TimeDependentLosses();
}

Float64 RefinedLossesTxDOT2013::TimeDependentLossesAfterDeck() const
{
   return 0;
}

Float64 RefinedLossesTxDOT2013::TimeDependentLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSR + m_dfpCR + m_dfpR1 + m_dfpR2;
}

Float64 RefinedLossesTxDOT2013::ShrinkageLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSR;
}

Float64 RefinedLossesTxDOT2013::CreepLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpCR;
}

Float64 RefinedLossesTxDOT2013::RelaxationLossBeforeDeckPlacement() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }
   return m_dfpR1;
}

Float64 RefinedLossesTxDOT2013::RelaxationLossAfterDeckPlacement() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpR2;
}

Float64 RefinedLossesTxDOT2013::TemporaryStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[TEMPORARY_STRAND];
}

Float64 RefinedLossesTxDOT2013::PermanentStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[PERMANENT_STRAND];
}

Float64 RefinedLossesTxDOT2013::TemporaryStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[TEMPORARY_STRAND] + m_dfpR0[TEMPORARY_STRAND];
}

Float64 RefinedLossesTxDOT2013::PermanentStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[PERMANENT_STRAND] + m_dfpR0[PERMANENT_STRAND];
}

void RefinedLossesTxDOT2013::ValidateParameters() const
{
}

void RefinedLossesTxDOT2013::UpdateLongTermLosses() const
{
   if ( IsZero( m_FpjPerm ) )
   {
      // If the strands aren't jacked, then there can't be losses.
      Init();
   }
   else
   {
      m_dfpSR = shrinkage_losses( m_H, m_Fci, m_Ep );

      m_Msd = m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] + m_Msidl1[WITH_ELASTIC_GAIN_REDUCTION] + m_Msidl2[WITH_ELASTIC_GAIN_REDUCTION];
      Float64 msd = m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] + m_Msidl1[WITHOUT_ELASTIC_GAIN_REDUCTION] + m_Msidl2[WITHOUT_ELASTIC_GAIN_REDUCTION];

      m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION] = -1 * m_Msd * m_epermFinal.Y() / m_Ixx;
      m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION] = -1 * msd * m_epermFinal.Y() / m_Ixx;

      m_dfpCR = creep_losses( m_H, m_Fci, m_Eci, m_Ep, m_ElasticShortening.PermanentStrand_Fcgp(), m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION]);

      if (ElasticShortening::FcgpComputationMethod::AssumedFpe == m_ElasticShortening.GetFcgpComputationMethod())
      {
         // assumed to be 0.7fpu
         m_fpt = 0.7 * this->m_FpuPerm;
      }
      else
      {
         m_fpt = m_FpjPerm - m_dfpR0[PERMANENT_STRAND] - m_dfpES[PERMANENT_STRAND];
      }

      m_KL = (m_TypePerm == WBFL::Materials::PsStrand::Type::LowRelaxation ? 30 : 7);

      m_dfpR1 = (m_fpt <= 0.0) ? 0 : (m_fpt/m_KL)*(m_fpt/m_FpyPerm - 0.55);
      m_dfpR1 = (m_dfpR1 < 0 ? 0 : m_dfpR1); // Fpt can't be less than 0.55Fpy

      if ( m_CoatingPerm != WBFL::Materials::PsStrand::Coating::None )
      {
         // See PCI Guidelines for the use of epoxy-coated strand
         // PCI Journal July-August 1993. Section 5.3
         m_dfpR1 *= 2;
      }

      m_dfpR2 = m_dfpR1; // Relaxation loss at deck placement is 1/2 of total
   }
}

void RefinedLossesTxDOT2013::UpdateHaulingLosses() const
{
   UpdateLongTermLosses();
}

void RefinedLossesTxDOT2013::UpdateElasticShortening() const
{
   // Elastic shortening
   ElasticShortening es(m_FpjPerm,
                            (m_TempStrandUsage == TempStrandUsage::Pretensioned ? m_FpjTemp : 0),
                            m_dfpR0[PERMANENT_STRAND], // perm
                            m_dfpR0[TEMPORARY_STRAND], // temp
                            m_ApsPerm,
                            (m_TempStrandUsage == TempStrandUsage::Pretensioned ? m_ApsTemp : 0),
                            m_SectionProperties == SectionPropertiesType::Gross ? true : false,
                            m_Ag,
                            m_Ixx,
                            m_Iyy,
                            m_Ixy,
                            m_epermRelease,
                            m_etemp,
                            m_Mdlg,
                            1.0,
                            m_Eci,
                            m_Ep,
                            m_FcgpMethod);

   m_ElasticShortening = es;

   m_dfpES[TEMPORARY_STRAND] = m_ElasticShortening.TemporaryStrand_ElasticShorteningLosses();
   m_dfpES[PERMANENT_STRAND] = m_ElasticShortening.PermanentStrand_ElasticShorteningLosses();
}

Float64 RefinedLossesTxDOT2013::GetKL() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_KL;
}

Float64 RefinedLossesTxDOT2013::Getfpt() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_fpt;
}

Float64 RefinedLossesTxDOT2013::GetSdMoment() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_Msd;
}

void RefinedLossesTxDOT2013::Init() const
{
   m_dfpSR = 0.0;
   m_dfpCR = 0.0;

   m_KL = 0.0;
   m_fpt = 0.0;
   m_Msd = 0.0;

   m_dfpR1 = 0.0;
   m_dfpR2 = 0.0;
   m_Shipping = 0.0;
}

Float64 shrinkage_losses(Float64 H, Float64 fci, Float64 Ep)
{
   CHECK( InRange(0.,H,100.) );

   // No si unit conversion in Texas
   fci = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::KSI );
   Ep  = WBFL::Units::ConvertFromSysUnits(Ep, WBFL::Units::Measure::KSI );

   Float64 losses = Ep*( (140-H)/(4.8+fci) )*4.4e-05;

   losses = WBFL::Units::ConvertToSysUnits(losses, WBFL::Units::Measure::KSI );
   CHECK( losses >= 0. );

   return losses;
}

Float64 creep_losses(Float64 H, Float64 fci, Float64 Eci, Float64 Ep, Float64 fcgp, Float64 dfcdp)
{
   CHECK( InRange(0.,H,100.) );
   fci   = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::KSI );
   Eci   = WBFL::Units::ConvertFromSysUnits(Eci, WBFL::Units::Measure::KSI );
   Ep    = WBFL::Units::ConvertFromSysUnits(Ep, WBFL::Units::Measure::KSI );
   fcgp  = WBFL::Units::ConvertFromSysUnits(fcgp, WBFL::Units::Measure::KSI );
   dfcdp = WBFL::Units::ConvertFromSysUnits(dfcdp, WBFL::Units::Measure::KSI );
                                                     
   Float64 loss = 0.1*((195-H)/(4.8+fci))*(Ep/Eci)*(fcgp+0.6*dfcdp);

   loss = WBFL::Units::ConvertToSysUnits(loss, WBFL::Units::Measure::KSI );
   loss = (loss < 0 ) ? 0 : loss;
   return loss;
}

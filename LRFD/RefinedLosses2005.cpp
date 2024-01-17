///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <Lrfd\RefinedLosses2005.h>
#include <Lrfd/BDSManager.h>
#include <Lrfd\XPsLosses.h>
#include <System\XProgrammingError.h>

using namespace WBFL::LRFD;

RefinedLosses2005::RefinedLosses2005()
{
   //m_V                     = WBFL::Units::ConvertToSysUnits(747.7,WBFL::Units::Measure::Inch3);
   //m_S                     = WBFL::Units::ConvertToSysUnits(258.747,WBFL::Units::Measure::Inch2);
   m_th                    = WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Day);
   m_td                    = WBFL::Units::ConvertToSysUnits(90.0, WBFL::Units::Measure::Day);
   m_tf                    = WBFL::Units::ConvertToSysUnits(120.0, WBFL::Units::Measure::Day);
   //m_CuringMethod          = lrfdCreepCoefficient2005::Accelerated;
   m_Ad                    = WBFL::Units::ConvertToSysUnits(600., WBFL::Units::Measure::Inch2);
   m_ed                    = WBFL::Units::ConvertToSysUnits(-25.865, WBFL::Units::Measure::Inch);
   m_Ksh                   = 1.0;
   //m_CuringMethodTimeAdjustmentFactor = WBFL::Units::ConvertToSysUnits(7,WBFL::Units::Measure::Day);
   m_RelaxationMethod = RelaxationLossMethod::Simplified;
}

RefinedLosses2005::RefinedLosses2005(
                         Float64 x,
                         Float64 Lg,
                         Losses::SectionPropertiesType sectionProperties,
                         WBFL::Materials::PsStrand::Grade gradePerm, // strand grade
                         WBFL::Materials::PsStrand::Type typePerm, // strand type
                         WBFL::Materials::PsStrand::Coating coatingPerm, // strand coating (none, epoxy)
                         WBFL::Materials::PsStrand::Grade gradeTemp, // strand grade
                         WBFL::Materials::PsStrand::Type typeTemp, // strand type
                         WBFL::Materials::PsStrand::Coating coatingTemp, // strand coating (none, epoxy)
                         Float64 fpjPerm, // fpj permanent strands
                         Float64 fpjTemp,  // fpj of temporary strands
                         Float64 ApsPerm,  // area of permanent strand
                         Float64 ApsTemp,   // area of TTS 
                         Float64 aps,      // area of one temp strand
                         const WBFL::Geometry::Point2d& epermRelease, // eccentricity of permanent ps strands with respect to CG of girder
                         const WBFL::Geometry::Point2d& epermFinal,
                         const WBFL::Geometry::Point2d& etemp, // eccentricity of temporary strands with respect to CG of girder
                         Losses::TempStrandUsage usage,
                         Float64 anchorSet,
                         Float64 wobble,
                         Float64 friction,
                         Float64 angleChange,

                         Float64 ShrinkageK1,
                         Float64 ShrinkageK2,
                         
                         Float64 DeckShrinkageK1,
                         Float64 DeckShrinkageK2,

                         Float64 Fc,   // 28 day strength of girder concrete
                         Float64 Fci,  // Release strength
                         Float64 FcSlab,   
                         Float64 Ec,   // Modulus of elasticity of girder
                         Float64 Eci,  // Modulus of elasticity of girder at transfer
                         Float64 Ecd,  // Modulus of elasticity of deck
                         
                         Float64 Ag,   // area of girder
                         Float64 Ixx,   // moment of inertia of girder
                         Float64 Iyy,
                         Float64 Ixy,
                         Float64 Ybg,  // Centroid of girder measured from bottom
                         Float64 Ac1,   // area of composite girder
                         Float64 Ic1,   // moment of inertia of composite
                         Float64 Ybc1,  // Centroid of composite measured from bottom
                         Float64 Ac2,   // area of composite girder
                         Float64 Ic2,   // moment of inertia of composite
                         Float64 Ybc2,  // Centroid of composite measured from bottom

                         Float64 An,   // area of girder
                         Float64 Ixxn,   // moment of inertia of girder
                         Float64 Iyyn,
                         Float64 Ixyn,
                         Float64 Ybn,  // Centroid of girder measured from bottom
                         Float64 Acn,   // area of composite girder
                         Float64 Icn,   // moment of inertia of composite
                         Float64 Ybcn,  // Centroid of composite measured from bottom
                         
                         Float64 Ad,   // area of deck
                         Float64 ed,   // eccentricity of deck CG with respect to CG of composite
                         Float64 Ksh,  // deck shrinkage strain effectiveness
                         
                         Float64 Mdlg,  // Dead load moment of girder only
                         const std::vector<std::pair<Float64, Float64>>& Madlg,  // Additional dead load on girder section (first value is moment, second is elastic gain reduction factor)
                         const std::vector<std::pair<Float64, Float64>>& Msidl1, // Superimposed dead loads, stage 1
                         const std::vector<std::pair<Float64, Float64>>& Msidl2, // Superimposed dead loads, stage 2

                         Float64 rh,  // Relative humidity [0,100]
                         Float64 ti,   // Time until prestress transfer
                         Float64 th,   // Time at hauling
                         Float64 td,   // Time to deck placement
                         Float64 tf,   // Final time
                         bool bIgnoreInitialRelaxation,
                         bool bValidateParameters,
                         RelaxationLossMethod relaxationMethod,
                         std::shared_ptr<const CreepCoefficient2005> pGirderCreep,
                         std::shared_ptr<const CreepCoefficient2005> pDeckCreep
) :
Losses(x,Lg,sectionProperties,gradePerm,typePerm,coatingPerm,gradeTemp,typeTemp,coatingTemp,fpjPerm,fpjTemp,ApsPerm,ApsTemp,aps,epermRelease,epermFinal,etemp,usage,anchorSet,wobble,friction,angleChange,Fc,Fci,FcSlab,Ec,Eci,Ecd,Mdlg,Madlg,Msidl1,Msidl2, Ag,Ixx,Iyy,Ixy,Ybg,Ac1,Ic1,Ybc1,Ac2,Ic2,Ybc2,An,Ixxn,Iyyn,Ixyn,Ybn,Acn,Icn,Ybcn,rh,ti,bIgnoreInitialRelaxation,bValidateParameters),
m_pGirderCreep(pGirderCreep),m_pDeckCreep(pDeckCreep)
{
   m_Ad                    = Ad;
   m_ed                    = ed;
   m_Ksh                   = Ksh;
   m_ti                    = ti;
   m_th                    = th;
   m_td                    = td;
   m_tf                    = tf;

   m_ShrinkageK1 = ShrinkageK1;
   m_ShrinkageK2 = ShrinkageK2;
                         
   m_DeckShrinkageK1 = DeckShrinkageK1;
   m_DeckShrinkageK2 = DeckShrinkageK2;

   m_RelaxationMethod = relaxationMethod;
}

Float64 RefinedLosses2005::TemporaryStrand_ShrinkageLossAtShipping() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpSRH[TEMPORARY_STRAND];
}

Float64 RefinedLosses2005::TemporaryStrand_CreepLossAtShipping() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }
   return m_dfpCRH[TEMPORARY_STRAND];
}

Float64 RefinedLosses2005::TemporaryStrand_RelaxationLossAtShipping() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpR1H[TEMPORARY_STRAND];
}

Float64 RefinedLosses2005::PermanentStrand_ShrinkageLossAtShipping() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpSRH[PERMANENT_STRAND];
}

Float64 RefinedLosses2005::PermanentStrand_CreepLossAtShipping() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpCRH[PERMANENT_STRAND];
}

Float64 RefinedLosses2005::PermanentStrand_RelaxationLossAtShipping() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpR1H[PERMANENT_STRAND];
}

Float64 RefinedLosses2005::ShrinkageLossBeforeDeckPlacement() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpSR;
}

Float64 RefinedLosses2005::CreepLossBeforeDeckPlacement() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpCR;
}

Float64 RefinedLosses2005::RelaxationLossBeforeDeckPlacement() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpR1;
}

Float64 RefinedLosses2005::ShrinkageLossAfterDeckPlacement() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpSD;
}

Float64 RefinedLosses2005::CreepLossAfterDeckPlacement() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpCD;
}

Float64 RefinedLosses2005::RelaxationLossAfterDeckPlacement() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpR2;
}

Float64 RefinedLosses2005::TemporaryStrand_TimeDependentLossesAtShipping() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSRH[TEMPORARY_STRAND] + m_dfpCRH[TEMPORARY_STRAND] + m_dfpR1H[TEMPORARY_STRAND];
}

Float64 RefinedLosses2005::PermanentStrand_TimeDependentLossesAtShipping() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSRH[PERMANENT_STRAND] + m_dfpCRH[PERMANENT_STRAND] + m_dfpR1H[PERMANENT_STRAND];
}

Float64 RefinedLosses2005::TimeDependentLossesBeforeDeck() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSR + m_dfpCR + m_dfpR1;
}

Float64 RefinedLosses2005::TimeDependentLossesAfterDeck() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = m_dfpSD + m_dfpCD + m_dfpR2 - m_dfpSS;
   return loss;
}

Float64 RefinedLosses2005::TimeDependentLosses() const
{
   return TimeDependentLossesBeforeDeck() + TimeDependentLossesAfterDeck();
}

std::shared_ptr<const CreepCoefficient2005> RefinedLosses2005::GetGirderCreep() const
{
    return m_pGirderCreep;
}

std::shared_ptr<const CreepCoefficient2005> RefinedLosses2005::GetDeckCreep() const
{
    return m_pDeckCreep;
}

Float64 RefinedLosses2005::GetTemporaryStrandFcgp() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_ElasticShortening.TemporaryStrand_Fcgp();
}

Float64 RefinedLosses2005::GetPermanentStrandFcgp() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_ElasticShortening.PermanentStrand_Fcgp();
}

Float64 RefinedLosses2005::GetTemporaryStrandFpt() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_FpjTemp - m_dfpR0[TEMPORARY_STRAND] - m_dfpES[TEMPORARY_STRAND];
}

Float64 RefinedLosses2005::GetPermanentStrandFpt() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_FpjPerm - m_dfpR0[PERMANENT_STRAND] - m_dfpES[PERMANENT_STRAND];
}

Float64 RefinedLosses2005::GetDeltaFcd() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_DeltaFcd;
}

Float64 RefinedLosses2005::GetDeltaFcdf() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_DeltaFcdf;
}

Float64 RefinedLosses2005::Getkhs_Girder() const
{
   return GetShrinkageHumidityFactor_Girder();
}

Float64 RefinedLosses2005::Getkhs_Deck() const
{
   return GetShrinkageHumidityFactor_Deck();
}

Float64 RefinedLosses2005::Get_ebid() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_ebid;
}

Float64 RefinedLosses2005::Get_ebih() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_ebih;
}

Float64 RefinedLosses2005::GetKid() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_Kid;
}

Float64 RefinedLosses2005::GetTemporaryStrandKih() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_Kih[TEMPORARY_STRAND];
}

Float64 RefinedLosses2005::GetPermanentStrandKih() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_Kih[PERMANENT_STRAND];
}

Float64 RefinedLosses2005::GetTemporaryStrandKL() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_KL[TEMPORARY_STRAND];
}

Float64 RefinedLosses2005::GetPermanentStrandKL() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_KL[PERMANENT_STRAND];
}

Float64 RefinedLosses2005::Get_ebdf() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_ebdf;
}

Float64 RefinedLosses2005::Get_ebif() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_ebif;
}

Float64 RefinedLosses2005::GetKdf() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_Kdf;
}

Float64 RefinedLosses2005::Get_eddf() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_eddf;
}

void RefinedLosses2005::SetAgeAtHauling(Float64 th)
{
   if ( !IsEqual(m_th,th) )
   {
      m_th = th;
      m_IsDirty = true;
   }
}

Float64 RefinedLosses2005::GetAgeAtHauling() const
{
   return m_th;
}

void RefinedLosses2005::SetAgeAtDeckPlacement(Float64 td)
{
   if ( !IsEqual(m_td,td) )
   {
      m_td = td;
      m_IsDirty = true;
   }
}

Float64 RefinedLosses2005::GetAgeAtDeckPlacement() const
{
   return m_td;
}

void RefinedLosses2005::SetFinalAge(Float64 tf)
{
   if ( !IsEqual(m_tf,tf) )
   {
      m_tf = tf;
      m_IsDirty = true;
   }
}

Float64 RefinedLosses2005::GetFinalAge() const
{
   return m_tf;
}

Float64 RefinedLosses2005::GetMaturityAtHauling() const 
{
    return m_th - m_ti;
}

Float64 RefinedLosses2005::GetMaturityAtDeckPlacement() const
{
    return m_td - m_ti;
}

Float64 RefinedLosses2005::GetMaturityAtFinal() const
{
    return m_tf - m_ti;
}

Float64 RefinedLosses2005::GetMaturityDeckPlacementToFinal() const
{
    return m_tf - m_td;
}

Float64 RefinedLosses2005::GetDeckInitialAge() const
{
    return WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Day);
}

Float64 RefinedLosses2005::GetDeckMaturityAtFinal() const
{
    return m_tf - m_td;
}

void RefinedLosses2005::SetRelaxationLossMethod(RefinedLosses2005::RelaxationLossMethod method)
{
   m_RelaxationMethod = method;
   m_IsDirty = true;
}

RefinedLosses2005::RelaxationLossMethod RefinedLosses2005::GetRelaxationLossMethod() const
{
   return m_RelaxationMethod;
}

void RefinedLosses2005::GetDeckShrinkageEffects(Float64* pA,Float64* pM) const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   *pA = m_eddf*m_Ad*m_Ecd/(1 + 0.7* m_pDeckCreep->GetCreepCoefficient(GetDeckMaturityAtFinal(),GetDeckInitialAge()));
   *pM = (*pA)*(m_ed);
}


void RefinedLosses2005::ValidateParameters() const
{
   // need to make sure spec version is ok
   if ( BDSManager::GetEdition() < BDSManager::Edition::ThirdEditionWith2005Interims )
   {
      WBFL_LRFD_THROW(XPsLosses,Specification);
   }

   bool is_si = (BDSManager::GetUnits() == BDSManager::Units::SI);
   // Use a values that are just out of spec to avoid throwing for boundary values
   // that have a little round-off error in them.
   // 5.4.2.1 - Sets limits between 4 and 10KSI, but allows greater than 10 KSI when specific articles permit it
   // 5.9.5.1 permits up to 15KSI for loss calculations
   Float64 fcMin = (is_si ? WBFL::Units::ConvertToSysUnits(27.95, WBFL::Units::Measure::MPa) : WBFL::Units::ConvertToSysUnits(3.95, WBFL::Units::Measure::KSI));
   Float64 fcMax = (is_si ? WBFL::Units::ConvertToSysUnits(105.05, WBFL::Units::Measure::MPa) : WBFL::Units::ConvertToSysUnits(15.05, WBFL::Units::Measure::KSI));
   if ( m_Fc < fcMin || fcMax < m_Fc )
   {
      WBFL_LRFD_THROW(XPsLosses,fcOutOfRange);
   }

   // strand type must be low relaxation if lump sum relaxation loss is used
   if ( m_RelaxationMethod == RelaxationLossMethod::LumpSum && m_TypePerm != WBFL::Materials::PsStrand::Type::LowRelaxation && m_TypeTemp != WBFL::Materials::PsStrand::Type::LowRelaxation )
   {
      WBFL_LRFD_THROW(XPsLosses,StrandType);
   }
}


void RefinedLosses2005::UpdateLongTermLosses() const
{
   //////////////////////////////////////////////////////////////////////////////////////
   // Losses: Time of Transfer to Time of Deck Placement [5.9.5.4.2]
   //////////////////////////////////////////////////////////////////////////////////////

   // Shrinkage of Girder Concrete [5.9.5.4.2a]

   // 1. Compute creep coefficient for use in computing Kid
   // Handled as part of Hauling losses

   // 2. Compute Kid
   Float64 Aps = m_ApsPerm;
   WBFL::Geometry::Point2d e = m_epermRelease;
   if ( m_TempStrandUsage == RefinedLosses2005::TempStrandUsage::Pretensioned )
   {
      Aps += m_ApsTemp;
      e = GetEccpgRelease();
   }

   Float64 D = m_Ixxn*m_Iyyn - m_Ixyn*m_Ixyn;
   Float64 DE = (e.Y()*m_Iyyn + e.X()*m_Ixyn)*m_epermRelease.Y() - (e.X()*m_Ixxn + e.Y()*m_Ixyn)*m_epermRelease.X(); // e(X,Y) is where the total prestress force is acting... m_epermRelease(X,Y) is where we want the change in stress
   m_Kid = 1 + (m_Ep / m_Eci) * (Aps / m_An) * (1 + m_An * DE / D) * (1 + 0.7 * m_pGirderCreep->GetCreepCoefficient(GetMaturityAtFinal(),m_ti));
   m_Kid = 1/m_Kid;

   // 3. Compute shrinkage strain
   m_ebid = GetShrinkageStrainAtDeckPlacement();

   m_dfpSR = IsZero(m_ApsPerm) ? 0 : m_ebid * m_Ep * m_Kid;

   // Creep of Girder Concrete [5.9.5.4.2b]
   Float64 fcgp = m_ElasticShortening.PermanentStrand_Fcgp();
   m_dfpCR = (m_Ep / m_Eci) * (fcgp + m_dfpp) * m_pGirderCreep->GetCreepCoefficient(GetMaturityAtDeckPlacement(),m_ti) * m_Kid;

   // Relaxation of Prestressing Strands [5.9.5.4.2c]
   // do we have to consider effect of PT if used???
   Float64 fpt = m_FpjPerm - m_dfpR0[PERMANENT_STRAND] - m_dfpES[PERMANENT_STRAND];
   Float64 td  = WBFL::Units::ConvertFromSysUnits(m_td,WBFL::Units::Measure::Day);
   Float64 ti  = WBFL::Units::ConvertFromSysUnits(m_ti,WBFL::Units::Measure::Day);

   switch( m_RelaxationMethod )
   {
   case RelaxationLossMethod::Simplified:
      m_dfpR1 = IsZero(fpt) ? 0 : (fpt/m_KL[PERMANENT_STRAND])*(fpt/m_FpyPerm - 0.55);
      m_dfpR1 = (m_dfpR1 < 0 ? 0 : m_dfpR1); // Fpt can't be less than 0.55Fpy
      break;

   case RelaxationLossMethod::Refined:
      m_dfpR1 = IsZero(fpt) ? 0 : (fpt/m_KL[PERMANENT_STRAND])*(log10(24*td)/log10(24*ti))*(fpt/m_FpyPerm - 0.55)*(1 - 3*(m_dfpSR + m_dfpCR)/fpt)*m_Kid;
      m_dfpR1 = (m_dfpR1 < 0 ? 0 : m_dfpR1); // Fpt can't be less than 0.55Fpy
      break;

   case RelaxationLossMethod::LumpSum:
      // strand type must be low relaxation if lump sum relaxation loss is used
      if ( m_TypePerm != WBFL::Materials::PsStrand::Type::LowRelaxation )
      {
         WBFL_LRFD_THROW(XPsLosses,StrandType);
      }
      m_dfpR1 = IsZero(fpt) ? 0 : WBFL::Units::ConvertToSysUnits(1.2,WBFL::Units::Measure::KSI);
      break;

   default:
      CHECK(false); // should never get here
      m_dfpR1 = 0;
   }

   if ( m_CoatingPerm != WBFL::Materials::PsStrand::Coating::None )
   {
      // See PCI Guidelines for the use of epoxy-coated strand
      // PCI Journal July-August 1993. Section 5.3
      m_dfpR1 *= 2;
   }

   //////////////////////////////////////////////////////////////////////////////////////
   // Losses: Time of Deck Placement to Final Time
   //////////////////////////////////////////////////////////////////////////////////////

   // Shrinkage of Girder Concrete [5.9.5.4.3a]

   // Compute Kdf
   Float64 epc = GetEccpc();
   m_Kdf = 1 + (m_Ep / m_Eci) * (m_ApsPerm / m_Acn) * (1 + m_Acn * epc * epc / m_Icn) * (1 + 0.7 * m_pGirderCreep->GetCreepCoefficient(GetMaturityAtFinal(),m_ti));
   m_Kdf = 1/m_Kdf;

   // 2. Compute shrinkage strain
   m_ebif = GetShrinkageStrainAtFinal();
   m_ebdf = m_ebif - m_ebid;

   // if there aren't any strands then there can't be loss due to shrinkage
   m_dfpSD = IsZero(m_ApsPerm) ? 0.0 : m_ebdf*m_Ep*m_Kdf;

   // Compute Delta Fcd
   D = m_Ixx*m_Iyy - m_Ixy*m_Ixy;
   if (IsZero(m_ApsPerm))
   {
      m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION] = 0;
      m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION] = 0;
   }
   else
   {
      m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION] = (/*my * m_Ixx +*/ m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] * m_Ixy) * m_epermFinal.X() / D + (m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] * m_Iyy/* + my * m_Ixy*/) * m_epermFinal.Y() / D; // biaxial on non-composite section
      m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION] = (/*my * m_Ixx +*/ m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] * m_Ixy) * m_epermFinal.X() / D + (m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] * m_Iyy/* + my * m_Ixy*/) * m_epermFinal.Y() / D; // biaxial on non-composite section
   }
   
   // uniaxial stresses on composite section
   std::array<Float64, 2> deltaFcd2a{// stage 1 composite... typically, longitudinal joints are composite but before topping is composite
      IsZero(m_ApsPerm) ? 0 : (m_Msidl1[WITH_ELASTIC_GAIN_REDUCTION] * (m_Ybc1 - m_Ybg + m_epermFinal.Y()) / m_Ic1),
      IsZero(m_ApsPerm) ? 0 : (m_Msidl1[WITHOUT_ELASTIC_GAIN_REDUCTION] * (m_Ybc1 - m_Ybg + m_epermFinal.Y()) / m_Ic1)
   };
   std::array<Float64, 2> deltaFcd2b{// stage 2 composite... typically, topping is now composite
      IsZero(m_ApsPerm) ? 0 : (m_Msidl2[WITH_ELASTIC_GAIN_REDUCTION] * (m_Ybc2 - m_Ybg + m_epermFinal.Y()) / m_Ic2),
      IsZero(m_ApsPerm) ? 0 : (m_Msidl2[WITHOUT_ELASTIC_GAIN_REDUCTION] * (m_Ybc2 - m_Ybg + m_epermFinal.Y()) / m_Ic2)
   };
   m_DeltaFcd2[WITH_ELASTIC_GAIN_REDUCTION] = deltaFcd2a[WITH_ELASTIC_GAIN_REDUCTION] + deltaFcd2b[WITH_ELASTIC_GAIN_REDUCTION];
   m_DeltaFcd2[WITHOUT_ELASTIC_GAIN_REDUCTION] = deltaFcd2a[WITHOUT_ELASTIC_GAIN_REDUCTION] + deltaFcd2b[WITHOUT_ELASTIC_GAIN_REDUCTION];

   Float64 P = (m_dfpCR + m_dfpSR + m_dfpR1)*m_ApsPerm;
   Float64 mx = P*m_epermFinal.Y();
   m_DeltaFcd3 = P/m_Ag + (/*my*m_Ixx +*/ mx*m_Ixy)*-m_epermFinal.X()/D - (mx*m_Iyy /*+ my*m_Ixy*/)*-m_epermFinal.Y()/D;
   
   // change sign because these moments cause tension at the level of
   // the strands which reduces creep - use WITHOUT_ELASTIC_GAIN_REDUCTION because this elastic gain is baked into the LRFD/NCHRP 496 forumulation
   // and can't be reduced. the reduction only applies to the elastic gains that approximate transformed section analysis
   m_DeltaFcd = -1.0*(m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION] + m_DeltaFcd2[WITHOUT_ELASTIC_GAIN_REDUCTION] + m_DeltaFcd3);

   if ( IsZero(m_ApsPerm) )
   {
      m_dfpCD = 0;
   }
   else
   {
      m_dfpCD = (m_Ep / m_Eci) * (fcgp + m_dfpp) * (m_pGirderCreep->GetCreepCoefficient(GetMaturityAtFinal(),m_ti) - m_pGirderCreep->GetCreepCoefficient(GetMaturityAtDeckPlacement(),m_ti)) * m_Kdf;
      m_dfpCD += (m_Ep / m_Ec) * (m_DeltaFcd + m_dfptr) * m_pGirderCreep->GetCreepCoefficient(GetMaturityDeckPlacementToFinal(),m_td) * m_Kdf;
   }


   if ( BDSManager::GetEdition() < BDSManager::Edition::FourthEdition2007 && m_dfpCD < 0 )
   {
      // removed inequality forcing dfpCD >= 0 in 4th Edition, 2007
      m_dfpCD = 0;
   }

   // Elastic gain due to deck placement
   m_dfpED[WITH_ELASTIC_GAIN_REDUCTION] = IsZero(m_ApsPerm) ? 0 : (m_Ep / m_Ec) * m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION];
   m_dfpED[WITHOUT_ELASTIC_GAIN_REDUCTION] = IsZero(m_ApsPerm) ? 0 : (m_Ep / m_Ec) * m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION];

   // Elastic gain due to superimposed dead loads
   m_dfpSIDL[WITH_ELASTIC_GAIN_REDUCTION] = IsZero(m_ApsPerm) ? 0 : (m_Ep / m_Ec) * m_DeltaFcd2[WITH_ELASTIC_GAIN_REDUCTION];
   m_dfpSIDL[WITHOUT_ELASTIC_GAIN_REDUCTION] = IsZero(m_ApsPerm) ? 0 : (m_Ep / m_Ec) * m_DeltaFcd2[WITHOUT_ELASTIC_GAIN_REDUCTION];

   // Relaxation of Prestressing Strands [5.9.5.4.3c]
   m_dfpR2 = m_dfpR1;

   // Shrinkage of Deck Concrete [5.9.5.4.3d]
   m_eddf = -GetDeckShrinkageStrain();
   // LRFD 2007 has a "-" in 1/Ac - epc*ed/I
   // we use a "+" because ed is < 0 for typical construction per our sign convension
   m_DeltaFcdf = m_eddf * m_Ad * m_Ecd * (1 / m_Acn + (epc * m_ed) / m_Icn) / (1 + 0.7 * m_pDeckCreep->GetCreepCoefficient(GetDeckMaturityAtFinal(),GetDeckInitialAge()));

   // if there aren't any strands, then there can't be gain due to deck shrinkage
   m_dfpSS = IsZero(m_ApsPerm) ? 0.0 : (m_Ep / m_Ec) * m_DeltaFcdf * m_Kdf * (1 + 0.7 * m_pGirderCreep->GetCreepCoefficient(GetMaturityDeckPlacementToFinal(),m_td));
}

Float64 RefinedLosses2005::GetShrinkageHumidityFactor_Girder() const
{
   return 2.0 - 0.014 * m_H;
}

Float64 RefinedLosses2005::GetShrinkageHumidityFactor_Deck() const
{
   // the scope is important here - we always want to call the RefinedLosses2005
   // version of the function here, not a overwritten sub-class version   
   return RefinedLosses2005::GetShrinkageHumidityFactor_Girder();
}

Float64 RefinedLosses2005::GetShrinkageStrain_Girder() const
{
    return 0.48e-03;
}

Float64 RefinedLosses2005::GetShrinkageStrain_Deck() const
{
   // the scope is important here - we always want to call the RefinedLosses2005
   // version of the function here, not a overwritten sub-class version
    return RefinedLosses2005::GetShrinkageStrain_Girder();
}

Float64 RefinedLosses2005::GetShrinkageStrainAtHauling() const
{
   Float64 t = GetMaturityAtHauling();
   Float64 ktd = m_pGirderCreep->GetKtd(t);
   Float64 kvs = m_pGirderCreep->GetKvs();
   Float64 kf = m_pGirderCreep->GetKf();
   Float64 khs = GetShrinkageHumidityFactor_Girder();
   Float64 esh = GetShrinkageStrain_Girder();
   Float64 ebih = m_ShrinkageK1 * m_ShrinkageK2 * kvs * khs * kf * ktd * esh;
   if (AdjustShrinkageStrain())
   {
      // LRFD 5.4.2.3.3
      // If the concrete is exposed to drying before 5 days of curing have elapsed,
      // the shrinkage as determined in Eq 5.4.2.3.3-1 should be increased by 20%
      ebih *= 1.2;
   }

   return ebih;
}

Float64 RefinedLosses2005::GetShrinkageStrainAtDeckPlacement() const
{
   Float64 t = GetMaturityAtDeckPlacement();
   Float64 ktd = m_pGirderCreep->GetKtd(t);
   Float64 kvs = m_pGirderCreep->GetKvs();
   Float64 kf = m_pGirderCreep->GetKf();
   Float64 khs = GetShrinkageHumidityFactor_Girder();
   Float64 esh = GetShrinkageStrain_Girder();
   Float64 ebid = m_ShrinkageK1 * m_ShrinkageK2 * kvs * khs * kf * ktd * esh;

   if (AdjustShrinkageStrain())
   {
      // LRFD 5.4.2.3.3
      // If the concrete is exposed to drying before 5 days of curing have elapsed,
      // the shrinkage as determined in Eq 5.4.2.3.3-1 should be increased by 20%
      ebid *= 1.2;
   }

   return ebid;
}

Float64 RefinedLosses2005::GetShrinkageStrainAtFinal() const
{
   Float64 t = GetMaturityAtFinal();
   Float64 ktd = m_pGirderCreep->GetKtd(t);
   Float64 kvs = m_pGirderCreep->GetKvs();
   Float64 kf = m_pGirderCreep->GetKf();
   Float64 khs = GetShrinkageHumidityFactor_Girder();
   Float64 esh = GetShrinkageStrain_Girder();
   Float64 ebif = m_ShrinkageK1 * m_ShrinkageK2 * kvs * khs * kf * ktd * esh;
   if (AdjustShrinkageStrain())
   {
      // LRFD 5.4.2.3.3
      // If the concrete is exposed to drying before 5 days of curing have elapsed,
      // the shrinkage as determined in Eq 5.4.2.3.3-1 should be increased by 20%
      ebif *= 1.2;
   }

   return ebif;
}

Float64 RefinedLosses2005::GetDeckShrinkageStrain() const
{
   if (IsZero(m_pDeckCreep->GetVolume()) || IsZero(m_pDeckCreep->GetSurfaceArea()))
      return 0.0;

   Float64 t = GetDeckMaturityAtFinal();
   Float64 ktd = m_pDeckCreep->GetKtd(t);
   Float64 kvs = m_pDeckCreep->GetKvs();
   Float64 khs = GetShrinkageHumidityFactor_Deck();
   Float64 kf = m_pDeckCreep->GetKf();
   Float64 esh = GetShrinkageStrain_Deck();
   Float64 eddf = m_Ksh * m_DeckShrinkageK1 * m_DeckShrinkageK2 * kvs * khs * kf * ktd * esh;
   // Assume deck is cured for more than 5 days so 20% increase does not apply
   return eddf;
}

void RefinedLosses2005::UpdateHaulingLosses() const
{
   // Losses: Time of Transfer to Time of Lifting [5.9.5.4.2]
   if ( m_RelaxationMethod == RelaxationLossMethod::Simplified )
   {
      m_KL[TEMPORARY_STRAND] = (m_TypeTemp == WBFL::Materials::PsStrand::Type::LowRelaxation ? 30 : 7);
      m_KL[PERMANENT_STRAND] = (m_TypePerm == WBFL::Materials::PsStrand::Type::LowRelaxation ? 30 : 7);
   }
   else
   {
      m_KL[TEMPORARY_STRAND] = (m_TypeTemp == WBFL::Materials::PsStrand::Type::LowRelaxation ? 45 : 10);
      m_KL[PERMANENT_STRAND] = (m_TypePerm == WBFL::Materials::PsStrand::Type::LowRelaxation ? 45 : 10);
   }

   // Shrinkage of Girder Concrete [5.9.5.4.2a]
   Float64 Aps = m_ApsPerm;
   WBFL::Geometry::Point2d e = m_epermFinal;
   if ( m_TempStrandUsage == RefinedLosses2005::TempStrandUsage::Pretensioned )
   {
      Aps += m_ApsTemp;
      e = GetEccpgFinal();
   }

   Float64 tf = GetMaturityAtFinal();
   Float64 th = GetMaturityAtHauling();

   Float64 D = m_Ixxn*m_Iyyn - m_Ixyn*m_Ixyn;
   Float64 DE = (e.Y()*m_Iyyn + e.X()*m_Ixyn)*m_etemp.Y() - (e.X()*m_Ixxn + e.Y()*m_Ixyn)*m_etemp.X(); // e(X,Y) is where the total prestress force is acting... m_etemp(X,Y) is where we want the change in stress
   m_Kih[TEMPORARY_STRAND] = 1 + (m_Ep / m_Eci) * (Aps / m_An) * (1 + m_An * DE / D) * (1 + 0.7 * m_pGirderCreep->GetCreepCoefficient(tf, m_ti));
   m_Kih[TEMPORARY_STRAND] = 1/m_Kih[TEMPORARY_STRAND];

   DE = (e.Y()*m_Iyyn + e.X()*m_Ixyn)*m_epermFinal.Y() - (e.X()*m_Ixxn + e.Y()*m_Ixyn)*m_epermFinal.X(); // e(X,Y) is where the total prestress force is acting... m_epermFinal(X,Y) is where we want the change in stress
   m_Kih[PERMANENT_STRAND] = 1 + (m_Ep / m_Eci) * (Aps / m_An) * (1 + m_An * DE / D) * (1 + 0.7 * m_pGirderCreep->GetCreepCoefficient(tf, m_ti));
   m_Kih[PERMANENT_STRAND] = 1/m_Kih[PERMANENT_STRAND];


   // Compute shrinkage strain
   m_ebih = GetShrinkageStrainAtHauling();
   m_dfpSRH[TEMPORARY_STRAND] = IsZero(m_ApsTemp*m_FpjTemp) ? 0 : m_ebih * m_Ep * m_Kih[TEMPORARY_STRAND];
   m_dfpSRH[PERMANENT_STRAND] = IsZero(m_ApsPerm*m_FpjPerm) ? 0 : m_ebih * m_Ep * m_Kih[PERMANENT_STRAND];

   // Creep of Girder Concrete [5.9.5.4.2b]
   Float64 fcgp = m_ElasticShortening.TemporaryStrand_Fcgp();
   m_dfpCRH[TEMPORARY_STRAND] = (m_Ep / m_Eci) * (fcgp + m_dfpp) * m_pGirderCreep->GetCreepCoefficient(th, m_ti) * m_Kih[TEMPORARY_STRAND];

   fcgp = m_ElasticShortening.PermanentStrand_Fcgp();
   m_dfpCRH[PERMANENT_STRAND] = (m_Ep / m_Eci) * (fcgp + m_dfpp) * m_pGirderCreep->GetCreepCoefficient(th, m_ti) * m_Kih[PERMANENT_STRAND];

   // Relaxation of Prestressing Strands [5.9.5.4.2c]
   // consider m_dfpp???
   th = WBFL::Units::ConvertFromSysUnits(m_th, WBFL::Units::Measure::Day);
   Float64 ti = WBFL::Units::ConvertFromSysUnits(m_ti,WBFL::Units::Measure::Day); // need ti in days for creep calculations

   Float64 fpj = IsZero(m_ApsTemp) ? 0 : m_FpjTemp;
   Float64 fpt = fpj - m_dfpR0[TEMPORARY_STRAND];
   if ( m_SectionProperties == SectionPropertiesType::Gross )
   {
      fpt -= m_dfpES[TEMPORARY_STRAND];
   }

   switch(m_RelaxationMethod)
   {
   case RelaxationLossMethod::Simplified:
      m_dfpR1H[TEMPORARY_STRAND] = IsZero(fpt) ? 0 : (fpt/m_KL[TEMPORARY_STRAND])*(fpt/m_FpyTemp - 0.55);
      m_dfpR1H[TEMPORARY_STRAND] = (m_dfpR1H[TEMPORARY_STRAND] < 0 ? 0 : m_dfpR1H[TEMPORARY_STRAND]); // Fpt can't be less than 0.55Fpy
      break;
   
   case RelaxationLossMethod::Refined:
      m_dfpR1H[TEMPORARY_STRAND] = IsZero(fpt) ? 0 : (fpt/m_KL[TEMPORARY_STRAND])*(log10(24*th)/log10(24*ti))*(fpt/m_FpyTemp - 0.55)*(1 - 3*(m_dfpSRH[TEMPORARY_STRAND] + m_dfpCRH[TEMPORARY_STRAND])/fpt)*m_Kih[TEMPORARY_STRAND];
      m_dfpR1H[TEMPORARY_STRAND] = (m_dfpR1H[TEMPORARY_STRAND] < 0 ? 0 : m_dfpR1H[TEMPORARY_STRAND]); // Fpt can't be less than 0.55Fpy
      break;
   
   case RelaxationLossMethod::LumpSum:
      m_dfpR1H[TEMPORARY_STRAND] = WBFL::Units::ConvertToSysUnits(1.2,WBFL::Units::Measure::KSI);
      break;

   default:
      CHECK(false);
      m_dfpR1H[TEMPORARY_STRAND] = 0;
      break;
   }

   if ( m_CoatingTemp != WBFL::Materials::PsStrand::Coating::None )
   {
      // See PCI Guidelines for the use of epoxy-coated strand
      // PCI Journal July-August 1993. Section 5.3
      m_dfpR1H[TEMPORARY_STRAND] *= 2;
   }

   fpj = IsZero(m_ApsPerm) ? 0 : m_FpjPerm;
   fpt = fpj - m_dfpR0[PERMANENT_STRAND];
   if ( m_SectionProperties == SectionPropertiesType::Gross )
   {
      fpt -= m_dfpES[PERMANENT_STRAND];
   }

   switch(m_RelaxationMethod)
   {
   case RelaxationLossMethod::Simplified:
      m_dfpR1H[PERMANENT_STRAND] = IsZero(fpt) ? 0 : (fpt/m_KL[PERMANENT_STRAND])*(fpt/m_FpyPerm - 0.55);
      m_dfpR1H[PERMANENT_STRAND] = (m_dfpR1H[PERMANENT_STRAND] < 0 ? 0 : m_dfpR1H[PERMANENT_STRAND]); // Fpt can't be less than 0.55Fpy
      break;
   
   case RelaxationLossMethod::Refined:
      m_dfpR1H[PERMANENT_STRAND] = IsZero(fpt) ? 0 : (fpt/m_KL[PERMANENT_STRAND])*(log10(24*th)/log10(24*ti))*(fpt/m_FpyPerm - 0.55)*(1 - 3*(m_dfpSRH[PERMANENT_STRAND] + m_dfpCRH[PERMANENT_STRAND])/fpt)*m_Kih[PERMANENT_STRAND];
      m_dfpR1H[PERMANENT_STRAND] = (m_dfpR1H[PERMANENT_STRAND] < 0 ? 0 : m_dfpR1H[PERMANENT_STRAND]); // Fpt can't be less than 0.55Fpy
      break;
   
   case RelaxationLossMethod::LumpSum:
      m_dfpR1H[PERMANENT_STRAND] = WBFL::Units::ConvertToSysUnits(1.2,WBFL::Units::Measure::KSI);
      break;

   default:
      CHECK(false);
      m_dfpR1H[PERMANENT_STRAND] = 0;
      break;
   }

   if ( m_CoatingPerm != WBFL::Materials::PsStrand::Coating::None )
   {
      // See PCI Guidelines for the use of epoxy-coated strand
      // PCI Journal July-August 1993. Section 5.3
      m_dfpR1H[PERMANENT_STRAND] *= 2;
   }

   if ( m_CoatingTemp != WBFL::Materials::PsStrand::Coating::None )
   {
      // See PCI Guidelines for the use of epoxy-coated strand
      // PCI Journal July-August 1993. Section 5.3
      m_dfpR1H[TEMPORARY_STRAND] *= 2;
   }

   // Total time dependent losses at shipping
   m_dfpTH[TEMPORARY_STRAND] = m_dfpSRH[TEMPORARY_STRAND] + m_dfpCRH[TEMPORARY_STRAND] + m_dfpR1H[TEMPORARY_STRAND];
   m_dfpTH[PERMANENT_STRAND] = m_dfpSRH[PERMANENT_STRAND] + m_dfpCRH[PERMANENT_STRAND] + m_dfpR1H[PERMANENT_STRAND];
}

bool RefinedLosses2005::AdjustShrinkageStrain() const
{
   //if ( BDSManager::GetEdition() < BDSManager::FourthEdition2007 )
   //{
      //if ( GetAdjustedInitialAge() < WBFL::Units::ConvertToSysUnits(5.0,WBFL::Units::Measure::Day) )
      //   return true;
   //}
   //else
   //{
   //   // In LRFD 4th Edition, 2007 the 1 day of steam curing = 7 days normal curing
   //   // was removed.
   //   if ( GetInitialAge() < WBFL::Units::ConvertToSysUnits(5.0,WBFL::Units::Measure::Day) )
   //      return true;
   //}

   // not comfortable with increasing the strain by 20%. it is questionable whether it actually
   // applies to precast girders. PCI does not include it in their examples

   // keep this method as a placeholder, but don't actually adjust the shrinkage strain 

   return false;
}

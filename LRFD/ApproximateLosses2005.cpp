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
#include <Lrfd\ApproximateLosses2005.h>
#include <Lrfd\ElasticShortening.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\XPsLosses.h>
#include <System\XProgrammingError.h>

using namespace WBFL::LRFD;

ApproximateLosses2005::ApproximateLosses2005(Float64 x, // location along girder where losses are computed
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
                         const WBFL::Geometry::Point2d& epermRelease, // eccentricity of permanent ps strands with respect to CG of girder
                         const WBFL::Geometry::Point2d& epermFinal,
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

                         Float64 An,    // Area of girder
                         Float64 Ixxn,    // Moment of inertia of girder
                         Float64 Iyyn,
                         Float64 Ixyn,
                         Float64 Ybn,   // Centroid of girder measured from bottom
                         Float64 Acn,    // Area of the composite girder and deck
                         Float64 Icn,    // Moment of inertia of composite
                         Float64 Ybcn,   // Centroid of composite measured from bottom

                         Float64 rh,      // relative humidity
                         Float64 ti,   // Time until prestress transfer
                         bool bIgnoreInitialRelaxation,
                         bool bValidateParameters
                         ) :
Losses(x,Lg,sectionProperties,gradePerm,typePerm,coatingPerm,gradeTemp,typeTemp,coatingTemp,fpjPerm,fpjTemp,ApsPerm,ApsTemp,aps,epermRelease,epermFinal,etemp,usage,anchorSet,wobble,friction,angleChange,Fc,Fci,FcSlab,Ec,Eci,Ecd,Mdlg,Madlg,Msidl1,Msidl2, Ag,Ixx,Iyy,Ixy,Ybg,Ac1,Ic1,Ybc1,Ac2,Ic2,Ybc2,An,Ixxn,Iyyn,Ixyn,Ybn,Acn,Icn,Ybcn,rh,ti,bIgnoreInitialRelaxation,bValidateParameters)
{
}

Float64 ApproximateLosses2005::TemporaryStrand_RelaxationLossesAtXfer() const
{
   if ( IsZero(m_ApsTemp) || IsZero(m_FpjTemp) )
   {
      return 0;
   }
   else
   {
      return RelaxationLossesAtXfer(false);
   }
}

Float64 ApproximateLosses2005::PermanentStrand_RelaxationLossesAtXfer() const
{
   if ( IsZero(m_ApsPerm) || IsZero(m_FpjPerm) )
   {
      return 0;
   }
   else
   {
      return RelaxationLossesAtXfer(true);
   }
}

Float64 ApproximateLosses2005::RelaxationLossesAtXfer(bool bPerm) const
{
   Float64 loss = 0;
   bool is_si = (LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI);
   WBFL::Materials::PsStrand::Type type = (bPerm ? m_TypePerm : m_TypeTemp);
   if ( type == WBFL::Materials::PsStrand::Type::LowRelaxation )
   {
      if (is_si)
      {
         loss = WBFL::Units::ConvertToSysUnits(17.0,WBFL::Units::Measure::MPa);
      }
      else
      {
         if ( LRFDVersionMgr::Version::FourthEdition2007 <= LRFDVersionMgr::GetVersion() )
         {
            loss = WBFL::Units::ConvertToSysUnits(2.4,WBFL::Units::Measure::KSI);
         }
         else
         {
            loss = WBFL::Units::ConvertToSysUnits(2.5,WBFL::Units::Measure::KSI);
         }
      }
   }
   else
   {
      if (is_si)
      {
         loss = WBFL::Units::ConvertToSysUnits(70.0,WBFL::Units::Measure::MPa);
      }
      else
      {
         loss = WBFL::Units::ConvertToSysUnits(10.0,WBFL::Units::Measure::KSI);
      }
   }

   // See PCI Guidelines for the use of epoxy-coated strand
   // PCI Journal July-August 1993. Section 5.3
   WBFL::Materials::PsStrand::Coating coating = (bPerm ? m_CoatingPerm : m_CoatingTemp);
   if ( coating != WBFL::Materials::PsStrand::Coating::None )
   {
      loss *= 2;
   }

   return loss;
}

Float64 ApproximateLosses2005::TemporaryStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[0];
}

Float64 ApproximateLosses2005::PermanentStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[1];
}

Float64 ApproximateLosses2005::TemporaryStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[0] + TemporaryStrand_ImmediatelyBeforeXferLosses();
}

Float64 ApproximateLosses2005::PermanentStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[1] + PermanentStrand_ImmediatelyBeforeXferLosses();
}

Float64 ApproximateLosses2005::TemporaryStrand_TimeDependentLossesAtShipping() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   UpdateLongTermLosses();
   return m_dfpTH;
}

Float64 ApproximateLosses2005::PermanentStrand_TimeDependentLossesAtShipping() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   UpdateLongTermLosses();
   return m_dfpTH;
}

Float64 ApproximateLosses2005::TimeDependentLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpLT;
}

Float64 ApproximateLosses2005::TimeDependentLossesBeforeDeck() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return TimeDependentLosses();
}

Float64 ApproximateLosses2005::TimeDependentLossesAfterDeck() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return 0;
}

Float64 ApproximateLosses2005::PermanentStrand_Final() const
{
   // need to over ride this method because shipping losses could be a lump sum and it
   // doesn't have to be consistent with the other losses

   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AfterTransfer() // initial relaxation
                + TimeDependentLosses(); // total lump sum time dependent losses

   return loss;
}

Float64 ApproximateLosses2005::PermanentStrand_BeforeTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AtShipping();
   return loss;
}

Float64 ApproximateLosses2005::PermanentStrand_AfterTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_BeforeTemporaryStrandRemoval();
   return loss;
}

Float64 ApproximateLosses2005::GetFpi() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_FpjPerm - m_dfpR0[1];
}

Float64 ApproximateLosses2005::GetHumidityFactor() const
{
   return 1.7 - 0.01*m_H;
}

Float64 ApproximateLosses2005::GetStrengthFactor() const
{
   bool is_si = (LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI);
   if ( is_si )
   {
      return 35/(7 + WBFL::Units::ConvertFromSysUnits(m_Fci,WBFL::Units::Measure::MPa));
   }
   else
   {
      return 5/(1 + WBFL::Units::ConvertFromSysUnits(m_Fci,WBFL::Units::Measure::KSI));
   }
}

void ApproximateLosses2005::ValidateParameters() const
{
   // need to make sure spec version is ok
   if ( LRFDVersionMgr::GetVersion() < LRFDVersionMgr::Version::ThirdEditionWith2005Interims )
   {
      WBFL_LRFD_THROW(XPsLosses,Specification);
   }

   bool is_si = (LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI);
   // Use a values that are just out of spec to avoid throwing for boundary values
   // that have a little round-off error in them.
   // 5.4.2.1 - Sets limits between 4 and 10KSI, but allows greater than 10 KSI when specific articles permit it
   // 5.9.5.1 permits up to 15KSI for loss calculations
   Float64 fcMin = (is_si ? WBFL::Units::ConvertToSysUnits(27.95,WBFL::Units::Measure::MPa) : WBFL::Units::ConvertToSysUnits(3.95,WBFL::Units::Measure::KSI) );
   Float64 fcMax = (is_si ? WBFL::Units::ConvertToSysUnits(105.05,WBFL::Units::Measure::MPa) : WBFL::Units::ConvertToSysUnits(15.05,WBFL::Units::Measure::KSI) );

   // LRFD 2009 limits approximate stresses per 5.9.5.3 to 10 KSI
   if ( LRFDVersionMgr::Version::FourthEditionWith2009Interims <= LRFDVersionMgr::GetVersion() )
   {
      fcMax = (is_si ? WBFL::Units::ConvertToSysUnits(69.05,WBFL::Units::Measure::MPa) : WBFL::Units::ConvertToSysUnits(10.05,WBFL::Units::Measure::KSI) );
   }

   if ( m_Fc < fcMin || fcMax < m_Fc )
   {
      WBFL_LRFD_THROW(XPsLosses,fcOutOfRange);
   }
}

void ApproximateLosses2005::UpdateLongTermLosses() const
{
   if ( IsZero( m_FpjPerm ) )
   {
      // If the strands aren't jacked, then there can't be losses.
      m_dfpLT = 0.0;
      m_dfpTH = 0.0;
      m_dfpED[WITH_ELASTIC_GAIN_REDUCTION] = 0.0;
      m_dfpED[WITHOUT_ELASTIC_GAIN_REDUCTION] = 0.0;
   }
   else
   {
      Float64 gamma_H = GetHumidityFactor();
      Float64 gamma_ST = GetStrengthFactor();

      bool is_si = (LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI);
      Float64 fpj = (m_ApsPerm*m_FpjPerm+m_ApsTemp*m_FpjTemp)/(m_ApsPerm+m_ApsTemp);
      Float64 dfpR0 = (m_ApsTemp*m_dfpR0[TEMPORARY_STRAND] + m_ApsPerm*m_dfpR0[PERMANENT_STRAND])/(m_ApsPerm+m_ApsTemp);
      if ( is_si )
      {
         fpj = WBFL::Units::ConvertFromSysUnits( fpj,WBFL::Units::Measure::MPa);
         Float64 delta_fpR = WBFL::Units::ConvertFromSysUnits(PermanentStrand_RelaxationLossesAtXfer(),WBFL::Units::Measure::MPa);
         Float64 fpi = fpj - WBFL::Units::ConvertFromSysUnits(dfpR0,WBFL::Units::Measure::MPa);
         _ASSERTE(0 <= fpi);

         m_dfpLT = 10.*fpi*m_ApsPerm/m_Ag*gamma_H*gamma_ST + 83.*gamma_H*gamma_ST + delta_fpR;
         m_dfpLT = WBFL::Units::ConvertToSysUnits( m_dfpLT, WBFL::Units::Measure::MPa );

         m_dfpTH = 3.*fpi*m_ApsPerm/m_Ag*gamma_H*gamma_ST + 21*gamma_H*gamma_ST + delta_fpR/4;
         m_dfpTH = WBFL::Units::ConvertToSysUnits( m_dfpTH, WBFL::Units::Measure::MPa );
      }
      else
      {
         fpj = WBFL::Units::ConvertFromSysUnits( fpj ,WBFL::Units::Measure::KSI);
         Float64 delta_fpR = WBFL::Units::ConvertFromSysUnits(PermanentStrand_RelaxationLossesAtXfer(),WBFL::Units::Measure::KSI);

         Float64 fpi = fpj - WBFL::Units::ConvertFromSysUnits(dfpR0,WBFL::Units::Measure::KSI);
         _ASSERTE(0 <= fpi);

         m_dfpLT = 10.*fpi*m_ApsPerm/m_Ag*gamma_H*gamma_ST + 12.*gamma_H*gamma_ST + delta_fpR;
         m_dfpLT = WBFL::Units::ConvertToSysUnits( m_dfpLT, WBFL::Units::Measure::KSI );

         m_dfpTH = 3.*fpi*(m_ApsPerm+m_ApsTemp)/m_Ag*gamma_H*gamma_ST + 3*gamma_H*gamma_ST + delta_fpR/4;
         m_dfpTH = WBFL::Units::ConvertToSysUnits( m_dfpTH, WBFL::Units::Measure::KSI );
      }

      // Elastic gain due to deck placement
      Float64 D = m_Ixx*m_Iyy - m_Ixy*m_Ixy;
      m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION] = (m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] *m_Ixx/* + my*m_Ixy*/)*m_epermFinal.X() / D + (m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] *m_Iyy/* + my*m_Ixy*/)*m_epermFinal.Y() / D; // biaxial on non-composite section
      m_dfpED[WITH_ELASTIC_GAIN_REDUCTION] = (m_Ep/m_Ec)*m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION];

      m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION] = (m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] * m_Ixx/* + my*m_Ixy*/) * m_epermFinal.X() / D + (m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] * m_Iyy/* + my*m_Ixy*/) * m_epermFinal.Y() / D; // biaxial on non-composite section
      m_dfpED[WITHOUT_ELASTIC_GAIN_REDUCTION] = (m_Ep / m_Ec) * m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION];

      // Elastic gain due to superimposed dead loads
      m_DeltaFcd2[WITH_ELASTIC_GAIN_REDUCTION] = m_Msidl1[WITH_ELASTIC_GAIN_REDUCTION] *(m_Ybc1 - m_Ybg + m_epermFinal.Y()) / m_Ic1 + m_Msidl2[WITH_ELASTIC_GAIN_REDUCTION] *( m_Ybc2 - m_Ybg + m_epermFinal.Y() )/m_Ic2; // uniaxial on composite section
      m_dfpSIDL[WITH_ELASTIC_GAIN_REDUCTION] = (m_Ep/m_Ec)*m_DeltaFcd2[WITH_ELASTIC_GAIN_REDUCTION];

      m_DeltaFcd2[WITHOUT_ELASTIC_GAIN_REDUCTION] = m_Msidl1[WITHOUT_ELASTIC_GAIN_REDUCTION] * (m_Ybc1 - m_Ybg + m_epermFinal.Y()) / m_Ic1 + m_Msidl2[WITHOUT_ELASTIC_GAIN_REDUCTION] * (m_Ybc2 - m_Ybg + m_epermFinal.Y()) / m_Ic2; // uniaxial on composite section
      m_dfpSIDL[WITHOUT_ELASTIC_GAIN_REDUCTION] = (m_Ep / m_Ec) * m_DeltaFcd2[WITHOUT_ELASTIC_GAIN_REDUCTION];
   }
}

void ApproximateLosses2005::UpdateHaulingLosses() const
{
   // don't really need to do anything here because it is handled in UpdateLongTermLosses
}

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
#include <Lrfd\RefinedLosses.h>
#include <Lrfd\ElasticShortening.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\XPsLosses.h>
#include <System\XProgrammingError.h>

using namespace WBFL::LRFD;


Float64 shrinkage_losses(Float64 h);
Float64 creep_losses(Float64 fcgp, Float64 dfcdp);
Float64 relaxation_after_transfer(WBFL::Materials::PsStrand::Type type,Float64 es,Float64 sr,Float64 cr);

bool IsSI() 
{
   return (LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI);
}

RefinedLosses::RefinedLosses(Float64 x, // location along girder where losses are computed
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

                         Float64 rh, // relative humidity

                         Float64 ti,   // Time until prestress transfer
                         Float64 shipping,
                         bool bValidateParameters
                         ) :
Losses(x,Lg,sectionProperties,gradePerm,typePerm,coatingPerm,gradeTemp,typeTemp,coatingTemp,fpjPerm,fpjTemp,ApsPerm,ApsTemp,aps,epermRelease,epermFinal,etemp,usage,anchorSet,wobble,friction,angleChange,Fc,Fci,FcSlab,Ec,Eci,Ecd,Mdlg,Madlg,Msidl1,Msidl2, Ag,Ixx,Iyy,Ixy,Ybg,Ac1,Ic1,Ybc1,Ac2,Ic2,Ybc2,An,Ixxn,Iyyn,Ixyn,Ybn,Acn,Icn,Ybcn,rh,ti,false,bValidateParameters)
{
   m_Shipping = shipping;
}

Float64 RefinedLosses::TemporaryStrand_TimeDependentLossesAtShipping() const
{
   return PermanentStrand_TimeDependentLossesAtShipping();
}

Float64 RefinedLosses::PermanentStrand_TimeDependentLossesAtShipping() const
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

Float64 RefinedLosses::TimeDependentLossesBeforeDeck() const
{
   return TimeDependentLosses();
}

Float64 RefinedLosses::TimeDependentLossesAfterDeck() const
{
   return 0;
}

Float64 RefinedLosses::TimeDependentLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSR + m_dfpCR + m_dfpR2;
}

Float64 RefinedLosses::ShrinkageLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSR;
}

Float64 RefinedLosses::CreepLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpCR;
}

Float64 RefinedLosses::TemporaryStrand_RelaxationLossesAtXfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[TEMPORARY_STRAND];
}

Float64 RefinedLosses::PermanentStrand_RelaxationLossesAtXfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[PERMANENT_STRAND];
}

Float64 RefinedLosses::RelaxationLossesAfterXfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR2;
}

Float64 RefinedLosses::TemporaryStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[TEMPORARY_STRAND];
}

Float64 RefinedLosses::PermanentStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[PERMANENT_STRAND];
}

Float64 RefinedLosses::TemporaryStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[TEMPORARY_STRAND] + m_dfpR0[TEMPORARY_STRAND];
}

Float64 RefinedLosses::PermanentStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[PERMANENT_STRAND] + m_dfpR0[PERMANENT_STRAND];
}

void RefinedLosses::ValidateParameters() const
{
}

void RefinedLosses::UpdateLongTermLosses() const
{
   if ( IsZero( m_FpjPerm ) )
   {
      // If the strands aren't jacked, then there can't be losses.
      m_dfpSR = 0.0;
      m_dfpCR = 0.0;
      m_dfpR2 = 0.0;
   }
   else
   {
      m_dfpSR = shrinkage_losses( m_H );

      Float64 D = m_Ixx*m_Iyy - m_Ixy*m_Ixy;
      Float64 deltaFcd_nc = (m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] *m_Ixx/* + my*m_Ixy*/)*m_epermFinal.X() / D + (m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] *m_Iyy/* + my*m_Ixy*/)*m_epermFinal.Y() / D; // biaxial on non-composite section
      Float64 deltaFcd_c = m_Msidl1[WITH_ELASTIC_GAIN_REDUCTION] *(m_Ybc1 - m_Ybg + m_epermFinal.Y()) / m_Ic1 + m_Msidl2[WITH_ELASTIC_GAIN_REDUCTION] *(m_Ybc2 - m_Ybg + m_epermFinal.Y()) / m_Ic2; // uniaxial on composite section
      m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION] = -1 * (deltaFcd_nc + deltaFcd_c);

      deltaFcd_nc = (m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] * m_Ixx/* + my*m_Ixy*/) * m_epermFinal.X() / D + (m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] * m_Iyy/* + my*m_Ixy*/) * m_epermFinal.Y() / D; // biaxial on non-composite section
      deltaFcd_c = m_Msidl1[WITHOUT_ELASTIC_GAIN_REDUCTION] * (m_Ybc1 - m_Ybg + m_epermFinal.Y()) / m_Ic1 + m_Msidl2[WITHOUT_ELASTIC_GAIN_REDUCTION] * (m_Ybc2 - m_Ybg + m_epermFinal.Y()) / m_Ic2; // uniaxial on composite section
      m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION] = -1 * (deltaFcd_nc + deltaFcd_c);

      m_dfpCR = creep_losses( m_ElasticShortening.PermanentStrand_Fcgp()/* + m_DeltaFcgp*/, m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION] );

      m_dfpR2 = relaxation_after_transfer( m_TypePerm, m_dfpES[PERMANENT_STRAND] + m_dfpp, m_dfpSR, m_dfpCR );
   }

   if ( m_CoatingPerm != WBFL::Materials::PsStrand::Coating::None )
   {
      // See PCI Guidelines for the use of epoxy-coated strand
      // PCI Journal July-August 1993. Section 5.3
      m_dfpR2 *= 2;
   }
}

void RefinedLosses::UpdateHaulingLosses() const
{
   UpdateLongTermLosses();
}

Float64 shrinkage_losses(Float64 h)
{
   CHECK( InRange(0.,h,100.) );

   Float64 losses;
   Float64 A,B; // Coefficients in the loss equation
   const WBFL::Units::Stress* p_unit;

   bool is_si = IsSI();

   if ( is_si )
   {
      p_unit = &WBFL::Units::Measure::MPa;
   }
   else
   {
      p_unit = &WBFL::Units::Measure::KSI;
   }

   A = is_si ? 117. : 17.;
   B = is_si ? 1.03 : 0.150;

   losses = A - B*h;

   losses = WBFL::Units::ConvertToSysUnits(losses, *p_unit );
   CHECK( losses >= 0. );

   return losses;
}

Float64 creep_losses(Float64 fcgp, Float64 dfcdp)
{
   Float64 loss = 12.0* fcgp + 7.0*dfcdp;
   loss = (loss < 0 ) ? 0 : loss;
   return loss;
}

Float64 relaxation_after_transfer(WBFL::Materials::PsStrand::Type type,Float64 es,Float64 sr,Float64 cr)
{
   bool is_si = IsSI();
   const WBFL::Units::Stress* p_unit;
   Float64 A;

   if ( is_si )
   {
      p_unit = &WBFL::Units::Measure::MPa;
      A = 138.;
   }
   else
   {
      p_unit = &WBFL::Units::Measure::KSI;
      A = 20.;
   }

   // Convert input values from system units to code units
   es = WBFL::Units::ConvertFromSysUnits(es,*p_unit);
   sr = WBFL::Units::ConvertFromSysUnits(sr,*p_unit);
   cr = WBFL::Units::ConvertFromSysUnits(cr,*p_unit);

   Float64 losses;
   losses = A - 0.4*es - 0.2*(sr+cr);

   if ( type == WBFL::Materials::PsStrand::Type::LowRelaxation )
   {
      losses *= 0.3;
   }

   losses = WBFL::Units::ConvertToSysUnits(losses,*p_unit);

   if ( losses < 0 )
   {
      WATCH(_T("Losses less than zero. Setting them to zero"));
      losses = 0; // Per Bijan Khaleghi 12/18/98
   }

   return losses;
}

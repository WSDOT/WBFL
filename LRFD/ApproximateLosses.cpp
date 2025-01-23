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
#include <Lrfd\ApproximateLosses.h>
#include <Lrfd\ElasticShortening.h>
#include <Lrfd/BDSManager.h>
#include <Lrfd\XPsLosses.h>
#include <System\XProgrammingError.h>

using namespace WBFL::LRFD;

ApproximateLosses::ApproximateLosses(BeamType beamType,
                         Float64 shipping,
                         Float64 ppr,
                         Float64 x, // location along girder where losses are computed
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

                         WBFL::Materials::ConcreteType concreteType,
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
                         bool bValidateLosses
                         ) :
Losses(x,Lg,sectionProperties,gradePerm,typePerm,coatingPerm,gradeTemp,typeTemp,coatingTemp,fpjPerm,fpjTemp,ApsPerm,ApsTemp,aps,epermRelease,epermFinal,etemp,usage,anchorSet,wobble,friction,angleChange,Fc,Fci,FcSlab,Ec,Eci,Ecd,Mdlg,Madlg,Msidl1,Msidl2, Ag,Ixx,Iyy,Ixy,Ybg,Ac1,Ic1,Ybc1,Ac2,Ic2,Ybc2,An,Ixxn,Iyyn,Ixyn,Ybn,Acn,Icn,Ybcn,rh,ti,bIgnoreInitialRelaxation,bValidateLosses)

{
   m_ConcreteType = concreteType;
   m_Shipping = shipping;
   m_PPR = ppr;
   m_BeamType = beamType;
}

Float64 ApproximateLosses::TemporaryStrand_TimeDependentLossesAtShipping() const
{
   return PermanentStrand_TimeDependentLossesAtShipping();
}

Float64 ApproximateLosses::PermanentStrand_TimeDependentLossesAtShipping() const
{
   if ( m_Shipping < 0 )
   {
      // shipping loss is percentage of final losses
      // make sure long term losses are computed
      UpdateLongTermLosses();
      return -m_Shipping*TimeDependentLosses();
   }
   else
   {
      return m_Shipping;
   }
}

Float64 ApproximateLosses::TimeDependentLossesBeforeDeck() const
{
   return TimeDependentLosses();
}

Float64 ApproximateLosses::TimeDependentLossesAfterDeck() const
{
   return 0;
}

Float64 ApproximateLosses::TimeDependentLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpLT;
}

Float64 ApproximateLosses::PermanentStrand_Final() const
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

Float64 ApproximateLosses::PermanentStrand_BeforeTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AtShipping();
   return loss;
}

Float64 ApproximateLosses::PermanentStrand_AfterTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_BeforeTemporaryStrandRemoval();
   return loss;
}

void ApproximateLosses::ValidateParameters() const
{
}

void ApproximateLosses::UpdateLongTermLosses() const
{
   if ( IsZero( m_FpjPerm ) )
   {
      // If the strands aren't jacked, then there can't be losses.
      m_dfpLT = 0.0;
   }
   else
   {
      // approximate loss method was removed from LRFD 5th Edition, 2010
      if( BDSManager::Edition::FifthEdition2010 <= BDSManager::GetEdition())
         WBFL_LRFD_THROW(XPsLosses, Specification);

      Float64 losses;
      const WBFL::Units::Stress* p_unit;

      bool is_si = (BDSManager::GetUnits() == BDSManager::Units::SI);

      if ( is_si )
      {
         p_unit = &WBFL::Units::Measure::MPa;
      }
      else
      {
         p_unit = &WBFL::Units::Measure::KSI;
      }

      Float64 lowRelaxReduction = 0.0;
      if ( m_BeamType == BeamType::IBeam )
      {
         Float64 A,B; // Coefficients in the loss equation
         A = is_si ? 230. : 33.;
         B = is_si ?  41. :  6.;

         lowRelaxReduction = is_si ? 41. : 6.;

         Float64 fc = WBFL::Units::ConvertFromSysUnits( m_Fc, *p_unit );

         losses = A*(1.0 - 0.15*(fc - B)/B) + B*m_PPR;
      }
      else if ( m_BeamType == BeamType::UBeam )
      {
         losses = (is_si ? 145. + 28*m_PPR : 21.0 + 4.0*m_PPR);

         lowRelaxReduction = is_si ? 28.0 : 4.0;
      }
      else if ( m_BeamType == BeamType::SolidSlab )
      {
         losses = (is_si ? 180. + 28.*m_PPR : 26.0 + 4.0*m_PPR);

         lowRelaxReduction = is_si ? 41.0 : 6.0;
      }
      else if ( m_BeamType == BeamType::BoxBeam )
      {
         losses = (is_si ? 130. + 28*m_PPR : 19.0 + 4.0*m_PPR);

         lowRelaxReduction = is_si ? 28.0 : 4.0;
      }
      else if ( m_BeamType == BeamType::SingleT )
      {
         Float64 A,B; // Coefficients in the loss equation
         A = is_si ? 230. : 33.;
         B = is_si ?  41. :  6.;

         lowRelaxReduction = is_si ? 55. : 8.;

         Float64 fc = WBFL::Units::ConvertFromSysUnits( m_Fc, *p_unit );

         losses = A*(1.0 - 0.15*(fc - B)/B) + B*m_PPR;
      }


      if ( m_TypePerm == WBFL::Materials::PsStrand::Type::LowRelaxation )
      {
         losses -= lowRelaxReduction;
      }

      if ( m_ConcreteType != WBFL::Materials::ConcreteType::Normal )
      {
         losses += (is_si ? WBFL::Units::ConvertToSysUnits(35.,WBFL::Units::Measure::MPa) : WBFL::Units::ConvertToSysUnits(5.0,WBFL::Units::Measure::KSI));
      }

      m_dfpLT = WBFL::Units::ConvertToSysUnits( losses, *p_unit );
   }

   Float64 D = m_Ixx*m_Iyy - m_Ixy*m_Ixy;
   Float64 deltaFcd_nc = (m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] *m_Ixx/* + my*m_Ixy*/)*m_epermFinal.X() / D + (m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] *m_Iyy/* + my*m_Ixy*/)*m_epermFinal.Y() / D; // biaxial on non-composite section
   Float64 deltaFcd_c = m_Msidl1[WITH_ELASTIC_GAIN_REDUCTION] *(m_Ybc1 - m_Ybg + m_epermFinal.Y()) / m_Ic1 + m_Msidl2[WITH_ELASTIC_GAIN_REDUCTION] *(m_Ybc2 - m_Ybg + m_epermFinal.Y()) / m_Ic2; // uniaxial on composite section
   m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION] = -1*(deltaFcd_nc + deltaFcd_c);

   deltaFcd_nc = (m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] * m_Ixx/* + my*m_Ixy*/) * m_epermFinal.X() / D + (m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] * m_Iyy/* + my*m_Ixy*/) * m_epermFinal.Y() / D; // biaxial on non-composite section
   deltaFcd_c = m_Msidl1[WITHOUT_ELASTIC_GAIN_REDUCTION] * (m_Ybc1 - m_Ybg + m_epermFinal.Y()) / m_Ic1 + m_Msidl2[WITHOUT_ELASTIC_GAIN_REDUCTION] * (m_Ybc2 - m_Ybg + m_epermFinal.Y()) / m_Ic2; // uniaxial on composite section
   m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION] = -1 * (deltaFcd_nc + deltaFcd_c);
}

void ApproximateLosses::UpdateHaulingLosses() const
{
}

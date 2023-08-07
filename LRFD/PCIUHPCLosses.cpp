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
#include <Lrfd\PCIUHPCLosses.h>

using namespace WBFL::LRFD;

PCIUHPCLosses::PCIUHPCLosses(
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
                         Float64 AutogenousShrinkage,
                         
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
                         RefinedLosses2005::RelaxationLossMethod relaxationMethod,
                         std::shared_ptr<const CreepCoefficient2005> pGirderCreep,
                         std::shared_ptr<const CreepCoefficient2005> pDeckCreep,
                         bool bUHPCGirder,
                         bool bPCTTGirder
                         ) :
RefinedLosses2005(x, Lg, sectionProperties, gradePerm, typePerm, coatingPerm, gradeTemp, typeTemp, coatingTemp, fpjPerm, fpjTemp, ApsPerm, ApsTemp, aps, epermRelease, epermFinal, etemp, usage, anchorSet, wobble, friction, angleChange, ShrinkageK1, ShrinkageK2,  DeckShrinkageK1, DeckShrinkageK2, 
   Fc, Fci,FcSlab, Ec, Eci, Ecd, 
   Ag,Ixx, Iyy, Ixy, Ybg, Ac1, Ic1, Ybc1, Ac2, Ic2, Ybc2,
   An, Ixxn, Iyyn, Ixyn, Ybn, Acn, Icn, Ybcn,
   Ad, ed, Ksh,
   Mdlg, Madlg, Msidl1, Msidl2,
   rh, ti,th, td, tf, bIgnoreInitialRelaxation, bValidateParameters, relaxationMethod, pGirderCreep, pDeckCreep
)
{
   m_bUHPCGirder = bUHPCGirder;
   m_bPCTTGirder = bPCTTGirder;
   m_eAS = AutogenousShrinkage;
   m_dfpAS[TEMPORARY_STRAND] = 0;
   m_dfpAS[PERMANENT_STRAND] = 0;
}

Float64 PCIUHPCLosses::TemporaryStrand_AutogenousShrinkage() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpAS[TEMPORARY_STRAND];
}

Float64 PCIUHPCLosses::PermanentStrand_AutogenousShrinkage() const
{
   if (m_IsDirty)
   {
      UpdateLosses();
   }
   return m_dfpAS[PERMANENT_STRAND];
}

Float64 PCIUHPCLosses::TemporaryStrand_AtShipping() const
{
   // adds autogenous shrinkage loss to the Shipping losses
   // autogenous shrinkage occurs after release and initial lifting - the next stage is Shipping
   return __super::TemporaryStrand_AtShipping() + TemporaryStrand_AutogenousShrinkage();
}

Float64 PCIUHPCLosses::PermanentStrand_AtShipping() const
{
   // adds autogenous shrinkage loss to the Shipping losses
   // autogenous shrinkage occurs after release and initial lifting - the next stage is Shipping
   return __super::PermanentStrand_AtShipping() + PermanentStrand_AutogenousShrinkage();
}

Float64 PCIUHPCLosses::PermanentStrand_AfterDeckPlacement() const
{
   // adds autogenous shrinkage loss... shipping loss is not included in AfterDeckPlacement
   // so we need to add the autogenous shrinkage loss here as well
   return __super::PermanentStrand_AfterDeckPlacement() + PermanentStrand_AutogenousShrinkage();
}

Float64 PCIUHPCLosses::GetShrinkageHumidityFactor_Girder() const
{
   return 1.0;
}

Float64 PCIUHPCLosses::GetShrinkageStrain_Girder() const
{
    if (m_bUHPCGirder)
        return (m_bPCTTGirder ? 0.0 : 0.30e-03);
    else
        return __super::GetShrinkageStrain_Girder();
}

void PCIUHPCLosses::UpdateInitialLosses() const
{
   __super::UpdateInitialLosses();
   UpdateAutogenousShrinkageLoss();
}

void PCIUHPCLosses::UpdateAutogenousShrinkageLoss() const
{
   if (m_bUHPCGirder)
   {
      Float64 Aps = m_ApsPerm;
      WBFL::Geometry::Point2d e = m_epermFinal;
      if (m_TempStrandUsage == RefinedLosses2005::TempStrandUsage::Pretensioned)
      {
         Aps += m_ApsTemp;
         e = GetEccpgFinal();
      }

      Float64 D = m_Ixxn * m_Iyyn - m_Ixyn * m_Ixyn;
      Float64 DE = (e.Y() * m_Iyyn + e.X() * m_Ixyn) * m_etemp.Y() - (e.X() * m_Ixxn + e.Y() * m_Ixyn) * m_etemp.X(); // e(X,Y) is where the total prestress force is acting... m_etemp(X,Y) is where we want the change in stress
      Float64 K_temp = 1 + (m_Ep / m_Eci) * (Aps / m_An) * (1 + m_An * DE / D);
      K_temp = 1 / K_temp;

      DE = (e.Y() * m_Iyyn + e.X() * m_Ixyn) * m_epermFinal.Y() - (e.X() * m_Ixxn + e.Y() * m_Ixyn) * m_epermFinal.X(); // e(X,Y) is where the total prestress force is acting... m_epermFinal(X,Y) is where we want the change in stress
      Float64 K_perm = 1 + (m_Ep / m_Eci) * (Aps / m_An) * (1 + m_An * DE / D);
      K_perm = 1 / K_perm;


      m_dfpAS[TEMPORARY_STRAND] = m_eAS * m_Ep * K_temp;
      m_dfpAS[PERMANENT_STRAND] = m_eAS * m_Ep * K_perm;
   }
   else
   {
       m_dfpAS[TEMPORARY_STRAND] = 0;
       m_dfpAS[PERMANENT_STRAND] = 0;
   }
}

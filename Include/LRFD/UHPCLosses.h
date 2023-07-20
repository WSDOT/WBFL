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

#pragma once

#include <Lrfd\LrfdExp.h>
#include <Lrfd\Losses.h>
#include <LRFD\RefinedLosses2005.h>
#include <Lrfd\UHPCCreepCoefficient.h>

namespace WBFL
{
   namespace LRFD
   {
      class LRFDCLASS UHPCLosses : public RefinedLosses2005
      {
      public:
         UHPCLosses() = default;

         UHPCLosses(Float64 x, // location along girder where losses are computed
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
                               Float64 Ac1,   // area of composite girder, stage 1
                               Float64 Ic1,   // moment of inertia of composite, stage 1
                               Float64 Ybc1,  // Centroid of composite measured from bottom, stage 1
                               Float64 Ac2,   // area of composite girder, stage 2
                               Float64 Ic2,   // moment of inertia of composite, stage 2
                               Float64 Ybc2,  // Centroid of composite measured from bottom, stage 2

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
                               std::shared_ptr<const CreepCoefficient2005>& pGirderCreep,
                               std::shared_ptr<const CreepCoefficient2005>& pDeckCreep
                               );

         UHPCLosses(const UHPCLosses&) = default;
         ~UHPCLosses() = default;

         UHPCLosses& operator=(const UHPCLosses&) = default;

      protected:
         virtual Float64 GetShrinkageHumidityFactor_Girder() const override;
         virtual Float64 GetShrinkageStrain_Girder() const override;
      };
   };
};

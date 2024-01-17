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

#pragma once

#include <Lrfd\LrfdExp.h>
#include <Lrfd\PsStrand.h>
#include <Lrfd/BDSManagerListener.h>
#include <Lrfd\Losses.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Utility class for computing prestress losses using the TxDOT Project 0-6374 Refined Estimate Method.
      class LRFDCLASS RefinedLossesTxDOT2013 : public Losses
      {
      public:

         RefinedLossesTxDOT2013();

         RefinedLossesTxDOT2013(Float64 x, // location along girder where losses are computed
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
                               Float64 shippingLosses, // time dependent loss at shipping or % of final time dependent loss if < 0
                               ElasticShortening::FcgpComputationMethod method, // Method for computing fcgp
                               bool bValidateParameters
                               );

         RefinedLossesTxDOT2013(const RefinedLossesTxDOT2013&) = default;
         ~RefinedLossesTxDOT2013() = default;

         RefinedLossesTxDOT2013& operator=(const RefinedLossesTxDOT2013&) = default;


         Float64 ShrinkageLosses() const;
         Float64 CreepLosses() const;
         Float64 RelaxationLossBeforeDeckPlacement() const;
         Float64 RelaxationLossAfterDeckPlacement() const;

         Float64 TemporaryStrand_ImmediatelyBeforeXferLosses() const;
         Float64 PermanentStrand_ImmediatelyBeforeXferLosses() const;
         Float64 TemporaryStrand_ImmediatelyAfterXferLosses() const;
         Float64 PermanentStrand_ImmediatelyAfterXferLosses() const;

         //-------------------------------------------------------------
         virtual Float64 TemporaryStrand_TimeDependentLossesAtShipping() const override;
         virtual Float64 PermanentStrand_TimeDependentLossesAtShipping() const override;
         virtual Float64 TimeDependentLossesBeforeDeck() const override;
         virtual Float64 TimeDependentLossesAfterDeck() const override;
         virtual Float64 TimeDependentLosses() const override;

         Float64 GetKL() const;
         Float64 Getfpt() const;

         Float64 GetSdMoment() const;

      protected:
         virtual void ValidateParameters() const override;
         virtual void UpdateLongTermLosses() const override;
         virtual void UpdateHaulingLosses() const override;
         virtual void UpdateElasticShortening() const override;

         mutable Float64 m_dfpSR;
         mutable Float64 m_dfpCR;

         mutable Float64 m_Msd;

         mutable Float64 m_KL;
         mutable Float64 m_fpt;
         mutable Float64 m_dfpR1;
         mutable Float64 m_dfpR2;

         mutable Float64 m_Shipping;

         ElasticShortening::FcgpComputationMethod m_FcgpMethod;

      private:
         void Init() const;
      };
   };
};

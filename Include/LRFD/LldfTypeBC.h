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

#pragma once

#include <Lrfd\LrfdExp.h>
#include <Lrfd\LiveLoadDistributionFactorBase.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Live load distribution factor calculator for cross section types B and C with concrete decks.
      class LRFDCLASS LldfTypeBC : public LiveLoadDistributionFactorBase
      {
      public:
         LldfTypeBC() = delete;
         LldfTypeBC(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                        Uint32 Nl, Float64 wLane,
                        Float64 d,Float64 L,
                        Float64 leftDe,Float64 rightDe,
                        Float64 skewAngle1, Float64 skewAngle2,
                        bool bMomentSkew, bool bShearSkew);

         LldfTypeBC(const LldfTypeBC&) = default;
         virtual ~LldfTypeBC() override = default;

         LldfTypeBC& operator=(const LldfTypeBC&) = default;

         Float64 MomentSkewCorrectionFactor() const;
         Float64 ShearSkewCorrectionFactor() const;

      protected:
         Float64 m_d;
         Float64 m_L;
         Float64 m_LeftDe;
         Float64 m_RightDe;
         Float64 m_SkewAngle1;
         Float64 m_SkewAngle2;

         virtual bool TestRangeOfApplicability(Location loc) const override;
         virtual DFResult GetMomentDF_Int_1_Strength() const override;
         virtual DFResult GetMomentDF_Int_2_Strength() const override;
         virtual DFResult GetMomentDF_Ext_1_Strength() const override;
         virtual DFResult GetMomentDF_Ext_2_Strength() const override;
         virtual DFResult GetShearDF_Int_1_Strength() const override;
         virtual DFResult GetShearDF_Int_2_Strength() const override;
         virtual DFResult GetShearDF_Ext_1_Strength() const override;
         virtual DFResult GetShearDF_Ext_2_Strength() const override;

         // Rules for ROA
         bool InteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
         bool ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
         bool SpacingTriggersLeverRule(bool bSISpec) const;

         virtual bool DoApplySkew() const;
      };


      /// @brief Live load distribution factor calculator for cross section types B and C,
      /// accounting for WSDOT modifications.  These modifications are documented
      /// in a memorandum by C. C. Ruth, dated February 22, 1999.
      /// 
      /// The WSDOT modifications are:
      /// 1. For exterior girders with a slab cantilever length less than or equal to
      ///    one-half of the adjacent interior girder spacing,  compute the distribution
      ///    factor using the equations for an interior girder.  The slab cantilever
      ///    length is defined as the distance from the centerline of the exterior girder
      ///    to the edge of the slab.
      /// 2. For exterior girders with a slab cantilever length exceeding one-half
      ///    of the adjacent interior girder spacing, compute the live load distribution
      ///    factor in accordance with the LRFD specification, except use a multiple
      ///    presence factor of 1.0 for one design lane loaded.
      /// 3. The special analysis based on the conventional approximation of loads on 
      ///    piles per AASHTO-LRFD Article C4.6.2.2.2d shall not be used unless the
      ///    effectiveness of diaphragms on the laterial distribution of truck loads
      ///    is investigated.
      class LRFDCLASS WsdotLldfTypeBC : public LldfTypeBC
      {
      public:
         WsdotLldfTypeBC() = delete;
         WsdotLldfTypeBC(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                             Uint32 Nl, Float64 wLane,
                             Float64 d,Float64 L,
                             Float64 leftDe,Float64 rightDe,
                             Float64 leftSlabOverhang,Float64 rightSlabOverhang,
                             Float64 skewAngle1, Float64 skewAngle2,
                             bool bMomentSkew, bool bShearSkew);

         WsdotLldfTypeBC(const WsdotLldfTypeBC&) = default;
         virtual ~WsdotLldfTypeBC() override = default;

         WsdotLldfTypeBC& operator=(const WsdotLldfTypeBC&) = default;

      protected:
         virtual DFResult GetMomentDF_Ext_1_Strength() const override;
         virtual DFResult GetMomentDF_Ext_2_Strength() const override;
         virtual DFResult GetShearDF_Ext_1_Strength() const override;
         virtual DFResult GetShearDF_Ext_2_Strength() const override;

      private:
         Float64      m_LeftSlabOverhang; // cl beam to edge of slab
         Float64      m_RightSlabOverhang;
      };

      /// @brief Live load distribution factor calculator for cross section types B and C,
      /// accounting for TxDot modifications.  These modifications are documented
      /// in a memorandum by C. C. Ruth, dated February 22, 1999.
      /// 
      /// The TxDot modifications are:
      /// 1) Live load distribution factors must conform to AASHTO LRFD Bridge Design Specifications,
      ///    Article 4.6.2.2.2 for flexural moment and Article 4.6.2.2.3 for
      ///    shear, except for exterior beam design. For exterior beam design, use a distribution factor
      ///    for two or more design lanes loaded only. 
      /// 
      /// 2) Do not use the distribution factor for one design
      ///    lane loaded unless the clear roadway width is less than 20.0 ft. Use 1.0 for the multiple
      ///    presence factor for one lane loaded. For exterior beams,
      ///    multiply the result of the lever rule by 0.9 to account for continuity.
      /// 
      /// 3) The live load used to design the exterior beam must never be less than the live
      ///    load used to design an interior beam.
      class LRFDCLASS TxDotLldfTypeBC : public LldfTypeBC
      {
      public:
         TxDotLldfTypeBC() = delete;
         TxDotLldfTypeBC(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                        Uint32 Nl, Float64 wLane,
                        Float64 d,Float64 L,
                        Float64 leftDe,Float64 rightDe,
                        Float64 roadwayWidth,
                        Float64 skewAngle1, Float64 skewAngle2,
                        bool bMomentSkew, bool bShearSkew);

         TxDotLldfTypeBC(const TxDotLldfTypeBC&) = default;
         virtual ~TxDotLldfTypeBC() override = default;

         TxDotLldfTypeBC& operator=(const TxDotLldfTypeBC&) = default;

      protected:
         // TxDOT is more lax than aashto
         virtual bool TestRangeOfApplicability(Location loc) const override;
   
         // Override this method so 90% of lever rule is applied to exterior beams for continuity.
         virtual ILiveLoadDistributionFactor::LeverRuleMethod DistributeByLeverRule(GirderIndexType beamNum,const std::vector<Float64>& Spacings, Float64 leftOverhang, Float64 rightOverhang,Float64 wLane,IndexType Nl,bool applyMpf) const override;

         virtual DFResult GetMomentDF_Int_1_Strength() const override;
         virtual DFResult GetMomentDF_Int_2_Strength() const override;
         virtual DFResult GetMomentDF_Ext_1_Strength() const override;
         virtual DFResult GetMomentDF_Ext_2_Strength() const override;

         virtual DFResult GetShearDF_Int_1_Strength() const override;
         virtual DFResult GetShearDF_Int_2_Strength() const override;
         virtual DFResult GetShearDF_Ext_1_Strength() const override;
         virtual DFResult GetShearDF_Ext_2_Strength() const override;

         // For fatigue, we need to use single lane behavior only
         virtual DFResult GetMomentDF_Int_Fatigue() const;
         virtual DFResult GetMomentDF_Ext_Fatigue() const;
         virtual DFResult GetShearDF_Int_Fatigue() const;
         virtual DFResult GetShearDF_Ext_Fatigue() const;
         virtual DFResult GetReactionDF_Ext_Fatigue() const;
         virtual DFResult GetReactionDF_Int_Fatigue() const;

         virtual bool DoApplySkew() const override;

      private:
         Float64 m_RoadwayWidth;
      };
   };
};

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
      /// @brief Live load distribution factor calculator for cross section types H and I and J if not sufficiently connected.
      class LRFDCLASS LldfTypeG : public LiveLoadDistributionFactorBase
      {
      public:
         LldfTypeG() = delete;
         LldfTypeG(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                       Uint32 Nl, Float64 wLane,
                       Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                       Float64 leftDe,Float64 rightDe,
                       Float64 PossionRatio,
                       Float64 skewAngle1, Float64 skewAngle2,
                       bool bMomentSkew, bool bShearSkew);

         LldfTypeG(const LldfTypeG&) = default;
         virtual ~LldfTypeG() override = default;

         LldfTypeG& operator=(const LldfTypeG&) = default;

         virtual Float64 MomentSkewCorrectionFactor() const override;
         virtual Float64 ShearSkewCorrectionFactor() const override;

      protected:
         Float64 m_L;
         Float64 m_W;
         Float64 m_I;
         Float64 m_J;
         Float64 m_b;
         Float64 m_d;
         Float64 m_LeftDe;
         Float64 m_RightDe;
         Float64 m_PoissonRatio;
         Float64 m_SkewAngle1;
         Float64 m_SkewAngle2;

         virtual bool TestRangeOfApplicability(Location loc) const override;

         virtual bool InteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
         virtual bool ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
         bool InteriorShearEquationRule(bool bSISpec) const;
         bool ExteriorShearEquationRule(bool bSISpec) const;
         bool IandJOutOfRangeRule(bool bSISpec) const;

         virtual DFResult GetMomentDF_Int_1_Strength() const override;
         virtual DFResult GetMomentDF_Int_2_Strength() const override;
         virtual DFResult GetMomentDF_Ext_1_Strength() const override;
         virtual DFResult GetMomentDF_Ext_2_Strength() const override;
         virtual DFResult GetShearDF_Int_1_Strength() const override;
         virtual DFResult GetShearDF_Int_2_Strength() const override;
         virtual DFResult GetShearDF_Ext_1_Strength() const override;
         virtual DFResult GetShearDF_Ext_2_Strength() const override;
      };


      /// @brief Live load distribution factor calculator for cross section type F if not sufficiently connected.
      class LRFDCLASS LldfTypeF : public LldfTypeG
      {
      public:
         LldfTypeF() = delete;
         LldfTypeF(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                       Uint32 Nl, Float64 wLane,
                       Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                       Float64 leftDe,Float64 rightDe,
                       Float64 PossionRatio,
                       Float64 skewAngle1, Float64 skewAngle2,
                       bool bMomentSkew, bool bShearSkew);

         LldfTypeF(const LldfTypeF&) = default;

         virtual ~LldfTypeF() override = default;

         LldfTypeF& operator=(const LldfTypeF&) = default;

      protected:
         virtual DFResult GetMomentDF_Int_1_Strength() const override;
         virtual DFResult GetMomentDF_Int_2_Strength() const override;
         virtual bool TestRangeOfApplicability(Location loc) const override;
         virtual bool InteriorMomentEquationRule(bool bSISpec, bool doThrow) const override;
      };

      /// @brief Live load distribution factor calculator for cross section types F and G accounting for TxDOT modifications.
      /// The Txdot modifications are:
      /// 1) Live load distribution factors for all beams, both moment and shear, 
      ///    must conform to AASHTO LRFD Bridge Design Specifications. Table 4.6.2.2.2b-1, 
      ///    using cross section (g), if the beams are connected only enough to prevent 
      ///    relative vertical displacement at their interfaces. 
      ///    This is called S/D distribution.
      /// 
      /// 2) Do not apply the skew correction factors for moment as suggested in 
      ///    Article 4.6.2.2.2e nor for shear as suggested in Article 4.6.2.2.3c.
      /// 
      /// 3) TxDOT equations do not deal with slab overhangs. Force user to overrride for this case.
      class LRFDCLASS TxdotVoidedSlab : public LldfTypeG
      {
      public:
         TxdotVoidedSlab() = delete;
         TxdotVoidedSlab(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                       Uint32 Nl, Float64 wLane,
                       Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                       Float64 leftDe,Float64 rightDe,
                       Float64 PossionRatio,
                       Float64 skewAngle1, Float64 skewAngle2);

         TxdotVoidedSlab(const TxdotVoidedSlab&) = default;
         virtual ~TxdotVoidedSlab() override = default;

         TxdotVoidedSlab& operator=(const TxdotVoidedSlab&) = default;

      protected:
         virtual Float64 MomentSkewCorrectionFactor() const override;
         virtual Float64 ShearSkewCorrectionFactor() const override;

         virtual DFResult GetMomentDF_Int_2_Strength() const override;
         virtual DFResult GetMomentDF_Ext_1_Strength() const override;
         virtual DFResult GetMomentDF_Ext_2_Strength() const override;

         virtual DFResult GetShearDF_Int_1_Strength() const override;
         virtual DFResult GetShearDF_Int_2_Strength() const override;
         virtual DFResult GetShearDF_Ext_1_Strength() const override;
         virtual DFResult GetShearDF_Ext_2_Strength() const override;

         virtual bool InteriorMomentEquationRule(bool bSISpec, bool doThrow) const override;
         virtual bool ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const override;

         virtual bool TestRangeOfApplicability(Location loc) const override;
      };


      /// @brief Live load distribution factor calculator for adjacent box accounting for TxDOT modifications.
      /// The Txdot modifications are:
      /// 1) Beams are always treated a connected as unit transversely
      /// 
      /// 2) Do not apply the skew correction factors for moment as suggested in 
      ///    Article 4.6.2.2.2e nor for shear as suggested in Article 4.6.2.2.3c.
      /// 
      /// 3) Exterior g cannot exceed interior factor
      class LRFDCLASS TxdotLldfAdjacentBox : public LldfTypeF
      {
      public:
         TxdotLldfAdjacentBox() = delete;
         TxdotLldfAdjacentBox(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                  Uint32 Nl, Float64 wLane,
                                  Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                                  Float64 leftDe,Float64 rightDe,
                                  Float64 PossionRatio,
                                  Float64 skewAngle1, Float64 skewAngle2);

         TxdotLldfAdjacentBox(const TxdotLldfAdjacentBox&) = default;
         virtual ~TxdotLldfAdjacentBox() override = default;

         TxdotLldfAdjacentBox& operator=(const TxdotLldfAdjacentBox& rOther) = default;

      protected:
         // No skew correction for txdot
         virtual Float64 MomentSkewCorrectionFactor() const override;

         virtual DFResult GetMomentDF_Ext_1_Strength() const override;
         virtual DFResult GetMomentDF_Ext_2_Strength() const override;
      
         DFResult GetBaseShearDF_Ext_1_Strength() const;
         virtual DFResult GetShearDF_Ext_1_Strength() const override;
         DFResult GetBaseShearDF_Ext_2_Strength() const;
         virtual DFResult GetShearDF_Ext_2_Strength() const override;
      };
   };
};

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
#include <Lrfd\LiveLoadDistributionFactorBase.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Live load distribution factor calculator for cross section types A, E, K, I, and J.
      class LRFDCLASS LldfTypeAEKIJ : public LiveLoadDistributionFactorBase
      {
      public:
         LldfTypeAEKIJ(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                           Uint32 Nl, Float64 wLane,
                           Float64 deLeft,Float64 deRight,Float64 L,Float64 ts,Float64 n,
                           Float64 I, Float64 A, Float64 eg,
                           Float64 skewAngle1, Float64 skewAngle2,
                           bool bSkewMoment,
                           bool bSkewShear);

         LldfTypeAEKIJ(const LldfTypeAEKIJ&) = default;
         virtual ~LldfTypeAEKIJ() override = default;

         LldfTypeAEKIJ& operator=(const LldfTypeAEKIJ&) = default;

         Float64 MomentSkewCorrectionFactor() const;
         Float64 ShearSkewCorrectionFactor() const;
         Float64 GetKg() const;

         virtual bool TestRangeOfApplicability(Location loc) const override;
         virtual DFResult GetMomentDF_Int_1_Strength() const override;
         virtual DFResult GetMomentDF_Int_2_Strength() const override;
         virtual DFResult GetMomentDF_Ext_1_Strength() const override;
         virtual DFResult GetMomentDF_Ext_2_Strength() const override;
         virtual DFResult GetShearDF_Int_1_Strength() const override;
         virtual DFResult GetShearDF_Int_2_Strength() const override;
         virtual DFResult GetShearDF_Ext_1_Strength() const override;
         virtual DFResult GetShearDF_Ext_2_Strength() const override;

      protected:
         Float64 m_LeftDe;
         Float64 m_RightDe;
         Float64 m_L;
         Float64 m_ts;
         Float64 m_n;
         Float64 m_A;
         Float64 m_I;
         Float64 m_eg;
         Float64 m_SkewAngle1;
         Float64 m_SkewAngle2;
         bool m_bIgnoreDe; // not the best OO design, but some of our children would like to ignore the check for this

         Float64 m_Kg;

      protected:
         // rules for determining which equation to use
         bool SpGreaterThan16_Rule(bool bSISpec) const;
         bool InteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
         bool InteriorShearEquationRule(bool bSISpec, bool doThrow) const;
         bool ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
         bool DeRule(bool bSISpec, bool doThrow) const;
      };
   };
};

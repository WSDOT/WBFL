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

#pragma once

#include <Lrfd\LrfdExp.h>
#include <Lrfd\LiveLoadDistributionFactorBase.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Live load distribution factor calculator for cross section types H and I and J if not sufficiently connected
      /// in accordance with TxDOT Bridge Design Manual
      class LRFDCLASS TxdotLldfMultiWeb : public LiveLoadDistributionFactorBase
      {
      public:
         TxdotLldfMultiWeb(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                               Uint32 Nl, Float64 wLane,
                               Float64 W, Float64 L, Float64 Kfactor,
                               Float64 skewAngle1, Float64 skewAngle2);
         
         TxdotLldfMultiWeb(const TxdotLldfMultiWeb& rOther) = default;

         virtual ~TxdotLldfMultiWeb() override = default;

         TxdotLldfMultiWeb& operator=(const TxdotLldfMultiWeb& rOther) = default;

         Float64 MomentSkewCorrectionFactor() const;
         Float64 ShearSkewCorrectionFactor() const;

      protected:
         Float64 m_L;
         Float64 m_W;
         Float64 m_Kfactor;
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
      };
   };
};

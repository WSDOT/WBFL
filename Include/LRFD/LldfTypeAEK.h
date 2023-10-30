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
#include <Lrfd\LldfTypeAEKIJ.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Live load distribution factor calculator for cross section types A, E, K when cross frames or diaphragms are present.
      class LRFDCLASS LldfTypeAEK : public LldfTypeAEKIJ
      {
      public:
         LldfTypeAEK() = delete;
         LldfTypeAEK(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                         Uint32 Nl, Float64 wLane,
                         Float64 L,Float64 ts,Float64 n,
                         Float64 I, Float64 A, Float64 eg,
                         bool bXFrames, // if true, the rigid method is used
                         Float64 skewAngle1, Float64 skewAngle2,
                         bool bSkewMoment,
                         bool bSkewShear);

         LldfTypeAEK(const LldfTypeAEK&) = default;
         virtual ~LldfTypeAEK() override = default;

         LldfTypeAEK& operator=(const LldfTypeAEK&) = default;

      protected:
         virtual DFResult GetMomentDF_Ext_1_Strength() const override;
         virtual DFResult GetMomentDF_Ext_2_Strength() const override;
         virtual DFResult GetShearDF_Ext_1_Strength() const override;
         virtual DFResult GetShearDF_Ext_2_Strength() const override;

      private:
         bool m_bXFrames = true;
      };

      /// @brief Live load distribution factor calculator for cross section types A, E, K, accounting for WSDOT modifications.
      /// These modifications are documented in a memorandum by C. C. Ruth, dated February 22, 1999.
      /// 
      /// The WSDOT modifications are:
      /// 1. For exterior girders with a slab cantilever length less than or equal to
      ///    the overhang threshold of the adjacent interior girder spacing,  compute the distribution
      ///    factor using the equations for an interior girder.  The slab cantilever
      ///    length is defined as the distance from the centerline of the exterior girder
      ///    to the edge of the slab.
      /// 2. For exterior girders with a slab cantilever length exceeding the overhang threshold
      ///    of the adjacent interior girder spacing, compute the live load distribution
      ///    factor in accordance with the LRFD specification, except use a multiple
      ///    presence factor of 1.0 for one design lane loaded.
      /// 3. The special analysis based on the conventional approximation of loads on 
      ///    piles per AASHTO-LRFD Article C4.6.2.2.2d shall not be used unless the
      ///    effectiveness of diaphragms on the lateral distribution of truck loads
      ///    is investigated.
      /// 4. Do not use rigid method
      class LRFDCLASS WsdotLldfTypeAEK : public LldfTypeAEKIJ
      {
      public:
         WsdotLldfTypeAEK() = delete;
         WsdotLldfTypeAEK(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                              Uint32 Nl, Float64 wLane,
                              Float64 L,Float64 ts,Float64 n,
                              Float64 I, Float64 A, Float64 eg,
                              Float64 leftSlabOverhang,Float64 rightSlabOverhang,
                              bool bXFrames,
                              Float64 skewAngle1, Float64 skewAngle2,
                              bool bSkewMoment,
                              bool bSkewShear,
                              Float64 SlabCantileverThreshold);

         WsdotLldfTypeAEK(const WsdotLldfTypeAEK&) = default;
         virtual ~WsdotLldfTypeAEK() override = default;

         WsdotLldfTypeAEK& operator=(const WsdotLldfTypeAEK&) = default;

      protected:
         Float64 m_LeftSlabOverhang;
         Float64 m_RightSlabOverhang;

         Float64 m_SlabCantileverThreshold;

         // If test passes,  use the lever rule with the multiple presence factor of 1.0 for single
         // lane to determine the live load distribution. The live load used to design the exterior 
         // girder shall not be less than the live load used for the adjacent interior girder. 
         bool SlabCantileverTest() const;

         virtual DFResult GetMomentDF_Ext_1_Strength() const override;
         virtual DFResult GetMomentDF_Ext_2_Strength() const override;
         virtual DFResult GetShearDF_Ext_1_Strength() const override;
         virtual DFResult GetShearDF_Ext_2_Strength() const override;
      };
   };
};

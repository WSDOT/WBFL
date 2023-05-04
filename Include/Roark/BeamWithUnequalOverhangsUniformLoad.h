///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam formula, patterned after Roark's formulas
//         for Stress and Strain
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

#include <Roark/RoarkExp.h>
#include <Roark/RoarkBeam.h>
#include <System/SectionValue.h>

namespace WBFL
{
   namespace Beams
   {
     /// Beam with unequal overhangs and a uniform load applied along the entire length.

     //  ===============================================================
     //        ^                                             ^
     //  <- a ->                                             <--- b --->
     //  <-------------------------- L -------------------------------->

      class ROARKCLASS BeamWithUnequalOverhangsUniformLoad : public RoarkBeam
      {
      public:
         BeamWithUnequalOverhangsUniformLoad(Float64 length,Float64 a,Float64 b, Float64 w, Float64 e);
         BeamWithUnequalOverhangsUniformLoad(const BeamWithUnequalOverhangsUniformLoad&) = delete;
         virtual ~BeamWithUnequalOverhangsUniformLoad();

         BeamWithUnequalOverhangsUniformLoad& operator=(const BeamWithUnequalOverhangsUniformLoad&) = delete;

         Float64 GetLeftOverhang() const;
         Float64 GetRightOverhang() const;
         Float64 GetW() const; // load/length

         virtual std::shared_ptr<RoarkBeam> CreateClone() const override;

         virtual std::pair<Float64, Float64> GetReactions() const override;
         virtual std::pair<Float64, Float64> GetMoments() const override;
         virtual std::pair<Float64, Float64> GetRotations() const override;
         virtual std::pair<Float64, Float64> GetDeflections() const override;

         virtual WBFL::System::SectionValue ComputeShear(Float64 x) const override;
         virtual WBFL::System::SectionValue ComputeMoment(Float64 x) const override;
         virtual Float64 ComputeRotation(Float64 x) const override;
         virtual Float64 ComputeDeflection(Float64 x) const override;

      private:
         Float64 m_LeftOverhang;
         Float64 m_RightOverhang;
         Float64 m_W;

      public:
         #if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
         #endif // _DEBUG

         #if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
         #endif // _UNITTEST
      };
   };
};

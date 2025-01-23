///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam formula, patterned after Roark's formulas
//         for Stress and Strain
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

#include <Roark/RoarkExp.h>
#include <Roark/RoarkBeam.h>

namespace WBFL
{
   namespace Beams
   {
      /// Pinned-Pinned beam with intermediate couple. Table III, reference# 20
      class ROARKCLASS PPIntermediateCouple : public RoarkBeam
      {
      public:
         PPIntermediateCouple(
            Float64 Mo, ///< Intermediate couple
            Float64 La, ///< Location of couple from left end of beam
            Float64 l, ///< Beam Length
            Float64 ei ///< Flexural stiffness
         );
         PPIntermediateCouple(const PPIntermediateCouple&) = delete;
         virtual ~PPIntermediateCouple() {}

         PPIntermediateCouple& operator=(const PPIntermediateCouple&) = delete;

      public:
         virtual std::shared_ptr<RoarkBeam> CreateClone() const;

         /// Location of couple from left end of beam
         void SetLa(Float64 la);

         /// Location of couple from left end of beam
         Float64 GetLa() const;

         /// Intermediate couple
         void SetMo(Float64 mo);

         /// Intermediate couple
         Float64 GetMo() const;

         virtual std::pair<Float64, Float64> GetReactions() const override;
         virtual std::pair<Float64, Float64> GetMoments() const override;
         virtual std::pair<Float64, Float64> GetRotations() const override;
         virtual std::pair<Float64, Float64> GetDeflections() const override;

         virtual WBFL::System::SectionValue ComputeShear(Float64 x) const override;
         virtual WBFL::System::SectionValue ComputeMoment(Float64 x) const override;
         virtual Float64 ComputeRotation(Float64 x) const override;
         virtual Float64 ComputeDeflection(Float64 x) const override;

      private:
         Float64 a{ 0.0 }, M{ 0.0 };
      };
   };
};

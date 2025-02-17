///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam formula, patterned after Roark's formulas
//         for Stress and Strain
// Copyright � 1999-2025  Washington State Department of Transportation
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
      /// A composition of RoarkBeam objects. The results of the individual beams are summed.
      /// All beams must have the same length and flexural stiffness.
      class ROARKCLASS CompositeBeam : public RoarkBeam
      {
      public:
         CompositeBeam() = default;
         CompositeBeam(Float64 length, Float64 ei);
         CompositeBeam(const CompositeBeam& other) = default;
         virtual ~CompositeBeam() {}

         CompositeBeam& operator=(const CompositeBeam& other) = default;

      public:
         /// Adds a clone of beam to the composite. 
         void AddBeam(const RoarkBeam& beam);

         /// Adds beam to the composite
         void AddBeam(std::shared_ptr<RoarkBeam> beam);

         /// Returns the number of beams in the composite
         IndexType GetBeamCount() const;

         /// Returns a beam
         std::shared_ptr<const RoarkBeam> GetBeam(IndexType index) const;

         /// Removes all beams from the composite
         void RemoveAllBeams();

         virtual std::shared_ptr<RoarkBeam> CreateClone() const;

         virtual std::pair<Float64, Float64> GetReactions() const;
         virtual std::pair<Float64, Float64> GetMoments() const;
         virtual std::pair<Float64, Float64> GetRotations() const;
         virtual std::pair<Float64, Float64> GetDeflections() const;

         virtual WBFL::System::SectionValue ComputeShear(Float64 x) const;
         virtual WBFL::System::SectionValue ComputeMoment(Float64 x) const;
         virtual Float64 ComputeRotation(Float64 x) const;
         virtual Float64 ComputeDeflection(Float64 x) const;

      private:
         std::vector<std::shared_ptr<RoarkBeam>> m_Beams;
      };
   };
};

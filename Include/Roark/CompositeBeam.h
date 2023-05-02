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

namespace WBFL
{
   namespace Beams
   {
      /// A composition of RoarkBeam objects. The results of the individual beams are summed.
      /// All beams must have the same length and flexural stiffness.
      class ROARKCLASS CompositeBeam : public RoarkBeam
      {
      public:
         CompositeBeam();
         CompositeBeam(const CompositeBeam& other) = delete;
         virtual ~CompositeBeam() {}

         CompositeBeam& operator=(const CompositeBeam& other) = delete;

      public:
         /// Adds a clone of beam to the composite. 
         void AddBeam(const RoarkBeam& beam);

         /// Adds beam to the composite
         void AddBeam(std::unique_ptr<RoarkBeam>&& beam);

         /// Returns the number of beams in the composite
         CollectionIndexType GetBeamCount() const;

         /// Returns a beam
         const std::unique_ptr<RoarkBeam>& GetBeam(CollectionIndexType index) const;

         /// Removes all beams from the composite
         void RemoveAllBeams();

         virtual std::unique_ptr<RoarkBeam> CreateClone() const;

         virtual std::pair<Float64, Float64> GetReactions() const;
         virtual std::pair<Float64, Float64> GetMoments() const;
         virtual std::pair<Float64, Float64> GetRotations() const;
         virtual std::pair<Float64, Float64> GetDeflections() const;

         virtual WBFL::System::SectionValue ComputeShear(Float64 x) const;
         virtual WBFL::System::SectionValue ComputeMoment(Float64 x) const;
         virtual Float64 ComputeRotation(Float64 x) const;
         virtual Float64 ComputeDeflection(Float64 x) const;

      private:
         std::vector<std::unique_ptr<RoarkBeam>> m_Beams;
         
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

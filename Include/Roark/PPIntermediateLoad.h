///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
// Copyright © 1999-2022  Washington State Department of Transportation
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
      /// Pinned-Pinned beam with intermediate point load. Table III, reference# 12
      class ROARKCLASS PPIntermediateLoad : public RoarkBeam
      {
      public:
         PPIntermediateLoad(
            Float64 w, ///< The point load
            Float64 La, ///< Location of load from left end of beam
            Float64 l, ///< Beam length
            Float64 ei ///< Flexural stiffness
         );
         PPIntermediateLoad(const PPIntermediateLoad&) = delete;
         virtual ~PPIntermediateLoad() {}

         PPIntermediateLoad& operator=(const PPIntermediateLoad&) = delete;

      public:
         std::unique_ptr<RoarkBeam> CreateClone() const;

         /// Location of load from left end of beam
         void SetLa(Float64 la);

         /// Location of load from left end of beam
         Float64 GetLa() const;

         /// Location of load from right end of beam
         Float64 GetLb() const;

         /// Intermediate point load
         void SetW(Float64 w);

         /// Intermediate point load
         Float64 GetW() const;

         virtual void GetReactions(Float64 *pRa,Float64* pRb) const override;
         virtual void GetMoments(Float64* pMa,Float64* pMb) const override;
         virtual void GetRotations(Float64* pra,Float64* prb) const override;
         virtual void GetDeflections(Float64* pYa,Float64* pYb) const override;

         virtual WBFL::System::SectionValue ComputeShear(Float64 x) const override;
         virtual WBFL::System::SectionValue ComputeMoment(Float64 x) const override;
         virtual Float64 ComputeRotation(Float64 x) const override;
         virtual Float64 ComputeDeflection(Float64 x) const override;

      private:
         Float64 a, b, W;

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

///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
// Copyright � 1999-2022  Washington State Department of Transportation
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

/************************************************************************
   Refenence:
   Formulas For Stress and Strain 4th Edition R.J. Roark
   Table III pp 104-113

   Naming Convension:
      Class Names -
         Class Names are of the form [C|P|F][C|P|F]{loadtype}
         where :
         [C|P|F] = Cantilever, Pinned, or Fixed end support
         the first one is for the left support and the second for the right
         support.
         {loadtype} can be EndLoad, IntermediateLoad,UniformLoad,PartUniformLoad,
         LeftTriangle,PartLeftTriangle,RightTriangle,PartRightTriangle,
         EndCouple,IntermediateCouple,CenterLoad, or CenterCouple

         Example:  PFRightTriangle - Pinned-Fixed beam with a right triangle
                   load. See Loading 25.
*************************************************************************/

#include <Roark/RoarkExp.h>
#include <System/SectionValue.h>

namespace WBFL
{
   namespace Beams
   {
      /// Abstract base class for simple span beam analysis based on Roark's Formulas for Stress and Strain, 4th Edition, R.J. Roark
      /// Table III, pp 104-113
      class ROARKCLASS RoarkBeam
      {
      public:
         RoarkBeam(Float64 length,Float64 ei);
         RoarkBeam(const RoarkBeam&) = delete;
         virtual ~RoarkBeam() {}

         RoarkBeam& operator=(const RoarkBeam&) = delete;

      public:
         /// Beam length
         void SetL(Float64 l);

         /// Beam length
         Float64 GetL() const;

         /// Flexural stiffness
         void SetEI(Float64 ei);

         /// Flexural stiffness
         Float64 GetEI() const;

         /// Returns a copy of the sub-class beam
         virtual std::unique_ptr<RoarkBeam> CreateClone() const = 0;

         /// Gets the vertical reactions at the end supports
         virtual void GetReactions(Float64 *pRa,Float64* pRb) const = 0;

         /// Gets the moment reactions at the end supports
         virtual void GetMoments(Float64* pMa,Float64* pMb) const = 0;

         /// Gets the rotation at the end supports
         virtual void GetRotations(Float64* pra,Float64* prb) const = 0;

         /// Gets the deflection at the end supports
         virtual void GetDeflections(Float64* pYa,Float64* pYb) const = 0;

         /// Computes the shear at a specified point from the left end of the beam
         virtual WBFL::System::SectionValue ComputeShear(Float64 x) const = 0;

         /// Computes the moment at a specified point from the left end of the beam
         virtual WBFL::System::SectionValue ComputeMoment(Float64 x) const = 0;

         /// Computes the rotation at a specified point from the left end of the beam
         virtual Float64 ComputeRotation(Float64 x) const = 0;

         /// Computes the deflection at a specified point from the left end of the beam
         virtual Float64 ComputeDeflection(Float64 x) const = 0;

      protected:
         /// Gets the length and flexural stiffness of the beam
         void GetProperties(Float64* pL, Float64* pEI) const;

      private:
         Float64 L, EI;

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
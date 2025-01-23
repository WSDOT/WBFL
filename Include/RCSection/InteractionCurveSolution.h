///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
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

#include <RCSection/RCSectionExp.h>
#include <RCSection/MomentCurvatureSolution.h>

namespace WBFL
{
   namespace RCSection
   {
      class InteractionCurveSolutionImpl;

      /// Solution to a moment interaction curve analysis.
      /// Created by AxialInteractionCurveSolver and MomentInteractionCurveSolver
      class RCSCLASS InteractionCurveSolution
      {
      public:
         InteractionCurveSolution();
         InteractionCurveSolution(const InteractionCurveSolution& other) = delete; // can't copy because of unique_ptr - also don't need copy semantics
         ~InteractionCurveSolution();
         
         InteractionCurveSolution& operator=(const InteractionCurveSolution& other) = delete; // can't assign

         /// Adds a solution point
         void AddSolutionPoint(std::unique_ptr<MomentCapacitySolution>&& curvatureSolution);

         /// Neutral axis direction for an analysis point
         Float64 GetNeutralAxisDirection(IndexType index) const;

         /// Axial force for an analysis
         Float64 GetFz(IndexType index) const;

         /// MomentCapacitySolution for an interaction point
         const MomentCapacitySolution& GetSolutionPoint(IndexType index) const;

         /// Number of solution points
         IndexType GetSolutionPointCount() const;

         /// Sorts the solution object by axial force
         void SortByFz();

         /// Sorts the solution objects by neutral axis direction
         void SortByNeutralAxisDirection();

      private:
         std::unique_ptr<InteractionCurveSolutionImpl> m_pImpl;
      };
   };
};
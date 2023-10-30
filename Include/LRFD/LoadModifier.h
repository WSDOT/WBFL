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

#include <LRFD\LrfdExp.h>

namespace WBFL
{
   namespace LRFD
   {
       // @brief Computes the load modifier used in limit state combinations. See Article 1.3.2.1
      class LRFDCLASS LoadModifier
      {
      public:
         enum class Level { Low, Normal, High };

         LoadModifier() = default;
         LoadModifier(const LoadModifier&) = default;
         ~LoadModifier() = default;

         LoadModifier& operator=(const LoadModifier&) = default;

         /// @brief Computes the load modifier. The type parameter is ignored if the current 
         /// specification is BDSManager::Version::FirstEdition.
         Float64 GetLoadModifier(LimitState ls, Optimization opt = Optimization::Max) const;

         /// @brief Sets the load modifier for ductility.  If nd is zero, the load modifier
         /// for is taken as 0.95 for Low, 1.0 for Normal and 1.05 for high.  nd
         /// is ignored for Normal and the load modifier is always taken as 1.0.
         void SetDuctilityFactor(Level level,Float64 nd = 0.0);

         /// @brief Returns the load modifier for ductility.
         Float64 GetDuctilityFactor() const;

         /// @brief Returns an enumerated value indicating the level of ductility.
         Level GetDuctilityLevel() const;

         /// @brief Sets the load modifier for importance.  If ni is zero, the load modifier
         /// for is taken as 0.95 for Low, 1.0 for Normal and 1.05 for high.  ni
         /// is ignored for Normal and the load modifier is always taken as 1.0.
         void SetImportanceFactor(Level level,Float64 ni = 0.0);

         /// @brief Returns the load modifier for importance.
         Float64 GetImportanceFactor() const;

         /// @brief Returns an enumerated value indicating the level of importance.
         Level GetImportanceLevel() const;

         /// @brief Sets the load modifier for redundancy.  If nr is zero, the load modifier
         /// for is taken as 0.95 for Low, 1.0 for Normal and 1.05 for high.  nr
         /// is ignored for Normal and the load modifier is always taken as 1.0.
         void SetRedundancyFactor(Level level,Float64 nr = 0.0);

         /// @brief Returns the load modifier for redundancy.
         Float64 GetRedundancyFactor() const;

         /// @brief Returns an enumerated value indicating the level of redundancy.
         Level GetRedundancyLevel() const;

      private:
         Float64 m_Ductility = 1.0;
         Float64 m_Importance = 1.0;
         Float64 m_Redundancy = 1.0;
         Level   m_DuctilityLevel = Level::Normal;
         Level   m_ImportanceLevel = Level::Normal;
         Level   m_RedundancyLevel = Level::Normal;

#if defined _DEBUG
         bool AssertValid() const;
      #endif // _DEBUG
      };
   };
};

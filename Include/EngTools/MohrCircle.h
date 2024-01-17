///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <EngTools\EngToolsExp.h>

namespace WBFL
{
   namespace EngTools
   {
      /// Mohr's Circle.
      ///
      /// REFERENCES
      ///   Advanced Strength and Applied Elasticity
      ///   A.C. Ugural & S. K. Fenster
      class ENGTOOLSCLASS MohrCircle
      {
      public:
         MohrCircle();
         MohrCircle(
            Float64 sii, ///< Normal stress in direction ii
            Float64 sjj, ///< Normal stress in direction jj
            Float64 sij  ///< Shear stress
         );
         MohrCircle(const MohrCircle& rOther) = default;

         ~MohrCircle() = default;

         MohrCircle& operator=(const MohrCircle& rOther) = default;

         /// Sets the state of stresses
         void SetStresses(Float64 sii, Float64 sjj, Float64 sij);

         Float64 GetSii() const { return m_Sii; }
         Float64 GetSjj() const { return m_Sjj; }
         Float64 GetSij() const { return m_Sij; }
         void SetSii(Float64 sii);
         void SetSjj(Float64 sjj);
         void SetSij(Float64 sij);

         /// Computes the state of stresses at the specified angle.
         /// angle is measure counterclockwise from the positive i-direction
         /// If bSysUnits is true, angle is in system units, otherwise it is in radians.
         void ComputeState(Float64* pSii, Float64* pSjj, Float64* pSij, Float64 angle, bool bSysUnits = true);


         /// Returns the maximum principal stress
         Float64 GetSmax() const;

         /// Returns the minimum principal stress
         Float64 GetSmin() const;

         /// Returns the maximum shear stress
         Float64 GetTmax() const;

         /// Returns the direction of the principal stress. 
         /// If bSysUnits is true, the angle is returned in system units otherwise it is in radians.
         Float64 GetPrincipalDirection(bool bSysUnits = true) const;

         /// Returns center point of circle
         Float64 GetCenter() const;

         /// Returns radius of circle
         Float64 GetRadius() const;

#if defined _DEBUG
         bool AssertValid() const;
#endif // _DEBUG

      private:
         Float64 m_Sii;  // input variables
         Float64 m_Sjj;
         Float64 m_Sij;

         Float64 m_Smin;
         Float64 m_Smax;
         // Note: Internal principal angle is stored in clockwise direction.
         Float64 m_Angle;
         Float64 m_Radius;
         Float64 m_Center;

         void Init();
      };
   }; // EngTools
}; // WBFL

///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2026  Washington State Department of Transportation
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

#include <GeomModel/GeomModelExp.h>

namespace WBFL
{
   namespace Geometry
   {
      /// Implements a Mohr's Circle for computing stresses, strains, or moments of inertia.
      /// This class is documented in terms of stresses. For shearing strains, don't forget
      /// to apply the factor of 2 adjustment.
      ///
      /// Mohr's circle equations
      /// \f[ Center = \left( \frac{\sigma_{ii} + \sigma_{jj}}{2} \right) \f]
      /// \f[ Radius = \sqrt{ \left( \frac{\sigma_{ii} - \sigma_{jj}}{2} \right)^2 + \sigma_{ij}^2} \f]
      /// \f[ \sigma_{Max/Min} = \left( \frac{\sigma_{ii} + \sigma_{jj}}{2} \right) \pm \sqrt{ \left( \frac{\sigma_{ii} - \sigma_{jj}}{2} \right)^2 + \sigma_{ij}^2} \f]
      /// \f[ \tan{2\theta_p} = \frac{2\sigma_{ij}}{\sigma_{ii} - \sigma_{jj}} \f]
      ///
      /// Stress Transformations
      /// \f[ \sigma_{xx} = \frac{\sigma_{ii} + \sigma_{jj}}{2} + \frac{\sigma_{ii} - \sigma_{jj}}{2}\cos{2\theta} + \sigma_{ij}\sin{2\theta} \f]
      /// \f[ \sigma_{xy} = -\frac{\sigma_{ii} - \sigma_{jj}}{2}\sin{2\theta} + \sigma_{ij}\cos{2\theta} \f]
      /// \f[ \sigma_{xx} + \sigma_{yy} = \sigma_{ii} + \sigma_{jj} \f]
      ///
      /// Strain Transformations
      /// \f[ \epsilon_{xx} = \frac{\epsilon_{ii} + \epsilon_{jj}}{2} + \frac{\epsilon_{ii} - \epsilon_{jj}}{2}\cos{2\theta} + \frac{\epsilon_{ij}}{2}\sin{2\theta} \f]
      /// \f[ \frac{\epsilon_{xy}}{2} = -\frac{\epsilon_{ii} - \epsilon_{jj}}{2}\sin{2\theta} + \frac{\epsilon_{ij}}{2}\cos{2\theta} \f]
      /// \f[ \epsilon_{xx} + \epsilon_{yy} = \epsilon_{ii} + \epsilon_{jj} \f]
      ///
      /// Inertial Transformations
      /// \f[ I_{xx} = \frac{I_{ii} + I_{jj}}{2} + \frac{I_{ii} - I_{jj}}{2}\cos{2\theta} + I_{ij}\sin{2\theta} \f]
      /// \f[ I_{xy} = -\frac{I_{ii} - I_{jj}}{2}\sin{2\theta} + I_{ij}\cos{2\theta} \f]
      /// \f[ I_{xx} + I_{yy} = I_{ii} + I_{jj} \f]
      ///
      /// \note For strains transformations, you must divide the shearing strain by 2.0 before using. Computing shear strains must be multipled by 2.0
      ///
      /// REFERENCES
      ///   Advanced Strength and Applied Elasticity
      ///   A.C. Ugural & S. K. Fenster
      class GEOMMODELCLASS MohrCircle
      {
      public:
         MohrCircle();
         MohrCircle(Float64 sii, Float64 sjj, Float64 sij);
         MohrCircle(const MohrCircle& rOther) = default;
         ~MohrCircle();

         MohrCircle& operator=(const MohrCircle& rOther) = default;

         /// Computes the state of strains/stresses/etc. on a plane defined by
         /// angle. Angle is in radians and measured
         /// counterclockwise from the global X direction.
         /// Returns tuple of the form Sii, Sjj, Sij
         std::tuple<Float64,Float64,Float64> ComputeState(Float64 angle) const;

         void SetSii(Float64 sii);
         Float64 GetSii() const { return m_Sii; }

         void SetSjj(Float64 sjj);
         Float64 GetSjj() const { return m_Sjj; }

         void SetSij(Float64 sij);
         Float64 GetSij() const { return m_Sij; }

         /// Returns the maximum principal value.
         Float64 GetSmax() const;

         /// Returns the minimum principal value.
         Float64 GetSmin() const;

         /// Returns the maximum "shear" value.
         Float64 GetTmax() const;

         /// Returns the direction of the principal axis measured counterclockwise
         /// from the global X axis, measured in radians.
         Float64 GetPrincipalDirection() const;

         /// Returns the center point of the mohr's circle.
         Float64 GetCenter() const;

         /// Returns the radius of the mohr's circle.
         Float64 GetRadius() const;

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

      #if defined _DEBUG
         bool AssertValid() const;
      #endif // _DEBUG
      };
   };
};

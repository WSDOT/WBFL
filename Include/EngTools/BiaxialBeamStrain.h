///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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

#include <EngTools\EngToolsExp.h>
#include <GeomModel\Primitives.h>
#include <GeomModel\Plane3d.h>

namespace WBFL
{
   namespace EngTools
   {
      /// This class represents a beam strain plane in x-y space
      class ENGTOOLSCLASS BiaxialBeamStrain
      {
      public:
         /// Creates a uniform strain plane
         BiaxialBeamStrain(Float64 strain = 0.0);

         /// Creates a strain plane with the strain specifies at three points
         BiaxialBeamStrain(const WBFL::Geometry::Point2d& p1, Float64 s1,
                           const WBFL::Geometry::Point2d& p2, Float64 s2,
                           const WBFL::Geometry::Point2d& p3, Float64 s3);
         
         /// Creates a strain plane with a neutral axis line, a point, and the strain at the point
         BiaxialBeamStrain(const WBFL::Geometry::Line2d& rnaLine,const WBFL::Geometry::Point2d& p3, Float64 strain);

         /// Creates a strain plane with a neutral axis line, a perpendicular offset distance from the neutral axis, and the strain at the offset distance
         BiaxialBeamStrain(const WBFL::Geometry::Line2d& rnaLine,Float64 offset, Float64 strain);


         ~BiaxialBeamStrain() = default;
         BiaxialBeamStrain(const BiaxialBeamStrain& rOther) = default;
         BiaxialBeamStrain& operator=(const BiaxialBeamStrain& rOther) = default;

         /// Creates a strain plane with a neutral axis line, a point, and the strain at the point
         void SetStrainPlane(const WBFL::Geometry::Line2d& rnaLine, const WBFL::Geometry::Point2d& p3, Float64 strain);

         /// Creates a strain plane with the strain specifies at three points
         void SetStrainPlane(const WBFL::Geometry::Point2d& p1, Float64 s1,
            const WBFL::Geometry::Point2d& p2, Float64 s2,
            const WBFL::Geometry::Point2d& p3, Float64 s3);

         /// Creates a strain plane with a neutral axis line, a perpendicular offset distance from the neutral axis, and the strain at the offset distance
         void SetStrainPlane(const WBFL::Geometry::Line2d& rnaLine, Float64 offset, Float64 strain);

         /// Creates a uniform strain plane
         void SetStrainPlane(Float64 strain);

         /// Returns the strain at a point
         Float64 GetAxialStrain(Float64 x, Float64 y) const;

         /// Returns the strain at a point
         Float64 GetAxialStrain(const WBFL::Geometry::Point2d& pnt) const;

         /// Given a strain and Y-ordinate, returns the corresponding X-ordinate. 
         /// \param[in] strain the strain
         /// \param[in] Y the Y-ordinate
         /// \param[out] X the X-ordinate
         /// \return true if successful
         bool GetXStrainLocation(Float64 strain, Float64 Y, Float64& X) const;

         /// Given a strain and X-ordinate, returns the corresponding Y-ordinate. 
         /// \param[in] strain the strain
         /// \param[in] X the X-ordinate
         /// \param[out] Y the Y-ordinate
         /// \return true if successful
         bool GetYStrainLocation(Float64 strain, Float64 X, Float64& Y) const;


#if defined _DEBUG
         bool AssertValid() const;
         void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
         WBFL::Geometry::Plane3d m_Plane;
         void Update(const WBFL::Geometry::Point2d& p1, Float64 s1,
                     const WBFL::Geometry::Point2d& p2, Float64 s2,
                     const WBFL::Geometry::Point2d& p3, Float64 s3);
      };
   }; // EngTools
}; // WBFL

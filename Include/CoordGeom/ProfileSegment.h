///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/ProfileElement.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A linear ProfileElement defined by two ProfilePoint end points
      class COORDGEOMCLASS ProfileSegment : public ProfileElement
      {
      private:
         ProfileSegment() = default;
         ProfileSegment(const ProfileSegment&) = default;
         ProfileSegment& operator=(const ProfileSegment&) = delete;

      public:
         /// @brief Creates a default ProfileSegment
         /// @return 
         static std::shared_ptr<ProfileSegment> Create();

         /// @brief Creates a ProfileSegment between two ProfilePoint end points
         /// @param p1 Start of this segment
         /// @param p2 End of this segment
         /// @return 
         static std::shared_ptr<ProfileSegment> Create(const ProfilePoint& p1, const ProfilePoint& p2);
         ~ProfileSegment() = default;

         /// @brief Sets the start point
         /// @param start 
         void SetStartPoint(const ProfilePoint& start);

         /// @brief Sets the end point
         /// @param end 
         void SetEndPoint(const ProfilePoint& end);

         /// @brief Returns the start and end location
         /// @return Returns a pair in the format (Start,End)
         std::pair<ProfilePoint, ProfilePoint> GetLocation() const;

         /// @brief Moves this segment by moving its end points
         /// @param p1 Start of this segment
         /// @param p2 End of this segment
         void Move(const ProfilePoint& p1, const ProfilePoint& p2);

         //
         // ProfileElement methods
         //
         virtual std::shared_ptr<ProfileElement> Clone() const override;
         virtual const ProfilePoint& GetStartPoint() const override;
         virtual const ProfilePoint& GetEndPoint() const override;
         virtual Float64 GetLength() const override;
         virtual std::pair<Float64, Float64> ComputeGradeAndElevation(const Station& station) const override;

      private:
         ProfilePoint m_Start, m_End;
      };
   };
};

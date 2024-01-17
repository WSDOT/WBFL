///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief An angular measure. Angles are measured in radians. Counter-clockwise angles (left) are positive values,
      class COORDGEOMCLASS Angle
      {
      public:
         Angle() = default;
         Angle(const Angle&) = default;
         Angle(Float64 angle);
         /// @brief Creates an angle using degree-minute-second
         /// @param deg Degree
         /// @param min Minute
         /// @param sec Second
         Angle(short deg, unsigned short min, Float64 sec);
         Angle(const std::_tstring& strAngle);
         ~Angle() = default;
         Angle& operator=(const Angle&) = default;

         bool operator==(const Angle& other) const;
         bool operator!=(const Angle& other) const;

         operator Float64() const { return GetValue(); }

         /// @brief Sets the angle's value
         /// @param angle value in radians
         void SetValue(Float64 angle);

         /// @brief Returns the angle's value
         /// @return Angle in radians
         Float64 GetValue() const;

         /// @brief Sets the angle using degree-minute-second
         /// @param deg Degree
         /// @param min Minute
         /// @param sec Second
         void SetDMS(short deg, unsigned short min, Float64 sec);

         /// @brief Gets the angle in degree-minute-second
         /// @return Returns the tuple<Degree,Minute,Second>
         std::tuple<short,unsigned short,Float64> GetDMS() const;

         /// @brief Defines the angle using a text string. The format of the text string is described in \ref WBFL_COGO_Angles_Directions_Stations
         /// @param strAngle
         void FromString(const std::_tstring& strAngle);

         /// @brief Creates a string representation of the angle in DMS format
         /// @param strFormat Comma delimited string with symbols for the DMS portions of the angle
         /// @param bSigned If true, the angle has a sign, otherwise it is appended with L or R
         /// @param bCondensed If true, the string is in condensed format (minutes and seconds that are zero are omitted from the string)
         /// @return The angle as a string
         std::_tstring AsString(const std::_tstring& strFormat = _T("°,\',\""), bool bSigned = false, bool bCondensed = false) const;

         /// @brief Increments this angle with a specified angle. This angle is not normalized
         /// @param increment The angle that increments this angle.
         /// @return Reference to this
         Angle& Increment(const Angle& increment);

         /// @brief Creates a new Angle that is equal to this Angle plus an increment. The resulting angle is not normalized.
         /// @param increment The angular increment
         /// @return The resulting angle
         Angle IncrementBy(const Angle& increment) const;
         
         /// @brief Normalizes the angle by causing the value to be between 0 and \f$2\pi\f$ radians
         void Normalize();

      private:
         Float64 m_Angle{ 0.0 };
      };
   };
};

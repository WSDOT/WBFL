///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/Angle.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief Object representing a direction. A direction can be a bearing or an azimuth. The direction value is an angle in radius measured counter-clockwise from East
      class COORDGEOMCLASS Direction
      {
      public:
         enum class NSDirection{North,South};
         enum class EWDirection{East,West};

         Direction() = default;
         Direction(const Direction&) = default;
         Direction(Float64 direction);
         Direction(NSDirection ns,unsigned short deg, unsigned short min, Float64 sec,EWDirection ew);
         Direction(const std::_tstring& strDirection);
         ~Direction() = default;
         Direction& operator=(const Direction&) = default;

         bool operator==(const Direction& other) const;
         bool operator!=(const Direction& other) const;
         Direction& operator+=(const Angle& angle);
         Direction& operator-=(const Angle& angle);

         operator Float64() const { return GetValue(); }

         /// @brief Sets the value of the direction measured counter-clockwise from East
         /// @param value Value in radians
         void SetValue(Float64 value);

         /// @brief Returns the value of the direction measured counter-clockwise from East
         /// @return Returns the value in radians
         Float64 GetValue() const;

         /// @brief Defines the direction using an azimuth
         /// @param azimuth Angle measured from North, positive values are towards the West
         void SetAzimuth(Float64 azimuth);

         /// @brief Sets the direction using an azimuth defined by degree-minute-second
         /// @param deg 
         /// @param min 
         /// @param sec 
         void SetAzimuth(short deg, unsigned short min, Float64 sec);

         /// @brief Returns the direction as an azimuth
         /// @return Azimuth measured from North in radians
         Float64 GetAzimuth() const;

         /// @brief Sets the direction using degree-minute-second format
         /// @param ns 
         /// @param deg 
         /// @param min 
         /// @param sec 
         /// @param ew 
         void SetDMS(NSDirection ns, unsigned short deg, unsigned short min, Float64 sec, EWDirection ew);

         /// @brief Gets the direction in degree-minute-second format
         /// @return Returns the tuple<NS,deg,min,sec,EW>
         std::tuple<NSDirection,unsigned short, unsigned short,Float64,EWDirection> GetDMS() const;

         /// @brief Defines the direction using a text string. The format of the text string is described in \ref WBFL_COGO_Angles_Directions_Stations
         /// @param strDirection 
         void FromString(const std::_tstring& strDirection);

         /// @brief Creates a string representation of the direction in bearing or azimuth format
         /// @param strFormat Comma delimited string with symbols for the DMS portions of the angle
         /// @param bAsBearing If true, the string is in bearing format, otherwise azimuth format
         /// @param bSigned If true, the angle has a sign, otherwise it is appended with L or R
         /// @param bCondensed If true, the string is in condensed format (minutes and seconds that are zero are omitted from the string)
         /// @return The angle as a string
         std::_tstring AsString(const std::_tstring& strFormat = _T("°,\',\""), bool bAsBearing = true, bool bSigned = false, bool bCondensed = false) const;

         /// @brief Increments this direction by a specified angle
         /// @param increment 
         /// @return Reference to this
         Direction& Increment(const Angle& increment);
         
         /// @brief Creates a new direction that is equal to this direction plus an angular increment
         /// @param increment 
         /// @return 
         Direction IncrementBy(const Angle& increment) const;

         /// @brief Returns the angle between this direction object an another direction object
         /// \image html Images\AngleBetween.jpg
         /// @param dir 
         /// @return 
         Angle AngleBetween(const Direction& dir) const;

      private:
         Float64 m_Direction{ 0.0 }; // Zero is East and increases in a CCW direction

         void BadDirectionString();
         void BadAzimuth();
         void BadDirection();
      };
   };
};

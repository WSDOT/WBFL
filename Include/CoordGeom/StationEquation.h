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

namespace WBFL
{
   namespace COGO
   {
      /// @brief Object defines a station equation.
      /// A station equation is used when the stationing along an alignment is discontinuous. Station equations resolve overlapping or gaps in stationing.
      /// This might occur when an alignment is re-routed making it longer or shorter than the original. 
      /// A station equation is used to define the stationing back and ahead of the point where the original and new stationing no longer match.
      /// Stationing zones are the ranges of stationing between station equations. 
      /// Station objects are defined with respect to the zone where they are located. 
      /// 
      /// Examples:
      /// Overlap Equation 10+00 back = 7+50 ahead
      /// Gap Equation  10+00 back = 11+00 ahead
      class COORDGEOMCLASS StationEquation
      {
      public:
         StationEquation() = default;
         StationEquation(Float64 back,Float64 ahead,Float64 normalizedStation);
         StationEquation(const StationEquation&) = default;
         ~StationEquation() = default;
         StationEquation& operator=(const StationEquation&) = default;

         /// @brief Returns the station equation parameters
         /// @return Returns a tuple of the form (Back Stat,Ahead Station,NormalizedStation)
         std::tuple<Float64,Float64,Float64> GetEquationParameters() const;

         /// @brief Returns the back station
         /// @return 
         Float64 GetBack() const;

         /// @brief Returns the ahead station
         /// @return 
         Float64 GetAhead() const;

         /// @brief Returns the station value normalized from the start of the alignment
         /// @return 
         Float64 GetNormalizedStation() const;

      private:
         Float64 m_Back{ 0.0 }; // back station
         Float64 m_Ahead{ 0.0 }; // ahead station
         Float64 m_NormalizedStation{ 0.0 }; // location of this equation assuming there are no equations
      };
   };
};

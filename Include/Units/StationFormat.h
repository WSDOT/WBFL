///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <System\Exception.h>
#include <Units\UnitsExp.h>

namespace WBFL
{
   namespace Units
   {
      /// Converts a floating point number into stationing format.
      class UNITSCLASS StationFormat
      {
      public:
         enum class UnitOfMeasure { Meter, ///< Stations are in meters
                                    Feet   ///< Stations are in feet
         };

         StationFormat() = default;
         StationFormat(const StationFormat&) = default;
         
         StationFormat(UnitOfMeasure unitOfMeasure);

         virtual ~StationFormat();

         StationFormat& operator=(const StationFormat&) = default;

         /// Returns the station as a floating point number in system units.
         /// If station is ill-formed, an unitXUnit exception will
         /// be thrown.
         Float64 FromString(const std::_tstring& station) const;

         /// Returns a string that represents <i>station</i> in station format.
         std::_tstring AsString(Float64 station) const;

         void SetUnitOfMeasure(UnitOfMeasure unitOfMeasure);
         UnitOfMeasure GetUnitOfMeasure() const;

         /// Returns <b>true</b> if the string is in a valid format, otherwise
         /// <b>false</b>.  If the unit of measure is Meter, the string format is
         /// x+yyy.zzzzzz (there must be at least one digit before the +, exactly
         /// three digits between the + and the . and any number of digits after
         /// the decimal point).  If the unit of measure is Feet, the string format
         /// is x+yy.zzzz (basically the same as for Meter, except the number if
         /// digits between the + and . is exactly two).  x, y, and z must be
         /// digits 0-9.
         bool IsValidString(const std::_tstring& station) const;

      #if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      private:
         UnitOfMeasure m_UnitOfMeasure{ UnitOfMeasure::Meter };
      };


      /// Encapsulates instatiations of station formats for SI and US unit systems.
      class UNITSCLASS StationFormats
      {
      public:
         StationFormats() = delete;
         ~StationFormats();

         static const StationFormat SI;
         static const StationFormat US;
      };
   };
};

///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysExp.h>
#include <System\INumericFormatTool.h>
#include <string>

namespace WBFL
{
   namespace System
   {
      class SectionValue;

      /// Formats numeric values and returns them as strings.  Extends the standard iostream capabilities by adding engineering notation.
      ///
      /// Engineering notation is an exponential format where the exponent is a multiple of three. e.g. 1x10^3, 1x10^6, 1X10^9, etc.
      class SYSCLASS NumericFormatTool : public INumericFormatTool
      {
      public:
         enum class Format { Automatic,   //< Like fixed, except adjusts precision downwards to eliminate trailing zeros
                             Fixed,       //< Fixed format
                             Scientific,  //< Scientific notation exponential format
                             Engineering  //< Exponential format where the exponent is a multiple of three
         };

         NumericFormatTool(
            Format format = Format::Automatic, ///< Format of the output string
            Uint16 width = 0, ///< Overall width of the string (same as width specifier for std::cout)
            Uint16 precision = 0 ///< Numeric precision represented in the output string (same as the precision specifier for std::cout)
         );
         NumericFormatTool(const NumericFormatTool&) = default;
         virtual ~NumericFormatTool() = default;

         NumericFormatTool& operator=(const NumericFormatTool&) = default;

         /// Returns the value as formatted string
         virtual std::_tstring AsString(Float64 value) const override;

         /// Returns the value as formatted string
         virtual std::_tstring AsString(const WBFL::System::SectionValue& value) const;

         void SetFormat(Format f) { m_Format = f; }
         Format GetFormat() const { return m_Format; }

         void SetWidth(Uint16 w) { m_Width = w; }
         Uint16 GetWidth() const { return m_Width; }

         void SetPrecision(Uint16 p) { m_Precision = p; }
         Uint16 GetPrecision() const { return m_Precision; }

      protected:
         Format m_Format{ Format::Automatic };
         Uint16 m_Width{ 0 };
         Uint16 m_Precision{ 0 };
      };
   };
};

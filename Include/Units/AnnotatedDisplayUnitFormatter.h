///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright � 1999-2026  Washington State Department of Transportation
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

#include <Units\UnitsExp.h>
#include <System\NumericFormatTool.h>
#include <string>

namespace WBFL
{
   namespace Units
   {
      /// Formats a real number as a two-part annotated string (e.g. feet-inches: 6'-3.500", or
      /// stationing: 148+00.00), splitting the value at a configurable power-of-ten offset and
      /// applying a separator/suffix around the resulting parts. Native C++ port of the WBFLUnitServer
      /// COM object of the same name; kept behaviorally identical so it is a drop-in replacement.
      class UNITSCLASS AnnotatedDisplayUnitFormatter
      {
      public:
         /// Text justification of the formatted value within its field width.
         enum class Justify
         {
            Left,  ///< Left-justify the formatted text
            Right  ///< Right-justify the formatted text
         };

         AnnotatedDisplayUnitFormatter() = default;
         AnnotatedDisplayUnitFormatter(const AnnotatedDisplayUnitFormatter&) = default;
         AnnotatedDisplayUnitFormatter& operator=(const AnnotatedDisplayUnitFormatter&) = default;

         /// Sets the separator/suffix annotation, encoded as "separator,suffix" (e.g. "'-,\"" for
         /// feet-inches, or "+" for stationing with no suffix). If the string leads with a comma,
         /// there is no separator and the text after the comma is the suffix.
         void SetAnnotation(const std::_tstring& annotation);

         /// Returns the separator/suffix annotation string, in the same "separator,suffix" encoding
         /// accepted by SetAnnotation().
         std::_tstring GetAnnotation() const;

         /// Sets the power-of-ten offset at which the value is split into major/minor parts
         /// (e.g. 0 for feet-inches, 2 for US stationing, 3 for SI stationing).
         void SetOffsetDigits(Uint32 nDigits);

         /// Returns the power-of-ten offset at which the value is split into major/minor parts.
         Uint32 GetOffsetDigits() const;

         /// Sets the factor used to scale the minor part after the split (e.g. 12 to convert a
         /// fractional-feet remainder into inches).
         void SetMultiplier(Float64 multiplier);

         /// Returns the factor used to scale the minor part after the split.
         Float64 GetMultiplier() const;

         /// Sets the display width, precision, justification, and the tolerance below which a
         /// value is treated as zero. Note: notation is stored/retrievable for API completeness
         /// only; like the original COM object, it is not applied by AsString (minor part is
         /// always fixed-point).
         void SetFormatSpecifiers(Uint32 width, Uint32 precision, Justify justify, WBFL::System::NumericFormatTool::Format notation, Float64 zeroTolerance);

         /// Returns the display field width set by SetFormatSpecifiers().
         Uint32 GetWidth() const;

         /// Returns the display precision set by SetFormatSpecifiers().
         Uint32 GetPrecision() const;

         /// Returns the numeric notation set by SetFormatSpecifiers(). Stored/retrievable for API
         /// completeness only; it is not applied by AsString() (see SetFormatSpecifiers()).
         WBFL::System::NumericFormatTool::Format GetNotation() const;

         /// Returns the text justification set by SetFormatSpecifiers().
         Justify GetJustification() const;

         /// Returns the zero tolerance set by SetFormatSpecifiers().
         Float64 GetZeroTolerance() const;

         /// Formats value. When bIncludeAnnotation is false, the major/minor parts are separated
         /// by a single space and the separator/suffix are omitted.
         std::_tstring AsString(Float64 value, bool bIncludeAnnotation = true) const;

      private:
         Uint32 m_OffsetDigits{ 0 };
         Float64 m_Multiplier{ 12.0 };
         std::_tstring m_Annotation{ _T("ft-,in") };
         std::_tstring m_Separator{ _T("ft-") };
         std::_tstring m_Suffix{ _T("in") };
         Uint32 m_Width{ 0 };
         Uint32 m_Precision{ 6 };
         WBFL::System::NumericFormatTool::Format m_Notation{ WBFL::System::NumericFormatTool::Format::Automatic };
         Justify m_Justify{ Justify::Right };
         Float64 m_ZeroTolerance{ 1e-6 };
      };
   };
};

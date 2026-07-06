///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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

#include <Units\UnitsLib.h>
#include <Units\AnnotatedDisplayUnitFormatter.h>
#include <MathEx.h>

using namespace WBFL::Units;

void AnnotatedDisplayUnitFormatter::SetAnnotation(const std::_tstring& annotation)
{
   if (m_Annotation == annotation)
      return;

   m_Annotation = annotation;
   m_Separator.clear();
   m_Suffix.clear();

   if (annotation.empty())
      return;

   auto commaPos = annotation.find(_T(','));
   if (annotation.front() == _T(','))
   {
      // leads with the delimiter -- there is no separator, the text after the comma is the suffix
      if (commaPos != std::_tstring::npos)
         m_Suffix = annotation.substr(commaPos + 1);
   }
   else if (commaPos == std::_tstring::npos)
   {
      m_Separator = annotation;
   }
   else
   {
      m_Separator = annotation.substr(0, commaPos);
      m_Suffix = annotation.substr(commaPos + 1);
   }
}

std::_tstring AnnotatedDisplayUnitFormatter::GetAnnotation() const
{
   return m_Annotation;
}

void AnnotatedDisplayUnitFormatter::SetOffsetDigits(Uint32 nDigits)
{
   m_OffsetDigits = nDigits;
}

Uint32 AnnotatedDisplayUnitFormatter::GetOffsetDigits() const
{
   return m_OffsetDigits;
}

void AnnotatedDisplayUnitFormatter::SetMultiplier(Float64 multiplier)
{
   m_Multiplier = multiplier;
}

Float64 AnnotatedDisplayUnitFormatter::GetMultiplier() const
{
   return m_Multiplier;
}

void AnnotatedDisplayUnitFormatter::SetFormatSpecifiers(Uint32 width, Uint32 precision, Justify justify, WBFL::System::NumericFormatTool::Format notation, Float64 zeroTolerance)
{
   m_Width = width;
   m_Precision = precision;
   m_Justify = justify;
   m_Notation = notation;
   m_ZeroTolerance = zeroTolerance;
}

Uint32 AnnotatedDisplayUnitFormatter::GetWidth() const
{
   return m_Width;
}

Uint32 AnnotatedDisplayUnitFormatter::GetPrecision() const
{
   return m_Precision;
}

WBFL::System::NumericFormatTool::Format AnnotatedDisplayUnitFormatter::GetNotation() const
{
   return m_Notation;
}

AnnotatedDisplayUnitFormatter::Justify AnnotatedDisplayUnitFormatter::GetJustification() const
{
   return m_Justify;
}

Float64 AnnotatedDisplayUnitFormatter::GetZeroTolerance() const
{
   return m_ZeroTolerance;
}

std::_tstring AnnotatedDisplayUnitFormatter::AsString(Float64 value, bool bIncludeAnnotation) const
{
   if (IsZero(value, m_ZeroTolerance))
      value = 0.0;

   // This algorithm works with positive values; save the sign and restore it in the output
   int sign = BinarySign(value);
   value = fabs(value);

   Float64 separatorLocation = pow(10.0, (Float64)m_OffsetDigits); // where the value is split into major/minor parts

   long v1 = (long)floor(value / separatorLocation); // major part
   Float64 v2 = value - v1 * separatorLocation; // minor part, before scaling

   // Guard against v2 landing right on the separator boundary due to floating point round-off
   // e.g. station = 69500.00 must come out as 695+00.00, not 694+100.00
   if (IsEqual(v2, separatorLocation, 0.0001))
   {
      v2 = 0;
      v1++;
   }

   v2 *= m_Multiplier;

   Float64 accuracy = Max(1.0 / pow(10.0, (Float64)m_Precision), 0.0001);
   v2 = RoundOff(v2, accuracy);

   // width of the minor part's numeric field
   Uint32 width = m_Precision;
   width += (m_Precision > 0) ? 1 : 0; // for the decimal point

   Uint32 vfloor = (Uint32)v2;
   if (vfloor < separatorLocation)
   {
      width += Max(m_OffsetDigits, (Uint32)1);
   }
   else
   {
      width += (Uint32)log10(v2) + 1;
   }

   size_t nChar = (v1 == 0) ? 1 : (size_t)log10((Float64)v1) + 1;
   nChar += width;
   nChar += (sign < 0) ? 1 : 0;
   if (bIncludeAnnotation)
      nChar += m_Separator.length() + m_Suffix.length();
   else
      nChar += 1; // the literal space between the major and minor parts
   nChar += 1; // null terminator

   auto pBuffer(std::make_unique<TCHAR[]>(nChar));
   if (bIncludeAnnotation)
   {
      _stprintf_s(pBuffer.get(), nChar, _T("%s%d%s%0*.*f%s"), sign < 0 ? _T("-") : _T(""), v1, m_Separator.c_str(), width, m_Precision, v2, m_Suffix.c_str());
   }
   else
   {
      _stprintf_s(pBuffer.get(), nChar, _T("%s%d %0*.*f"), sign < 0 ? _T("-") : _T(""), v1, width, m_Precision, v2);
   }

   std::_tstring strValue(pBuffer.get());

   if (strValue.length() < m_Width)
   {
      if (m_Justify == Justify::Left)
         strValue.append(m_Width - strValue.length(), _T(' '));
      else
         strValue.insert(0, m_Width - strValue.length(), _T(' '));
   }

   return strValue;
}

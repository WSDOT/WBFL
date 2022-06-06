///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysExp.h>

namespace WBFL
{
   namespace System
   {
      /// Encapsulates the notion of a value at a section.  In section based
      /// analysis, it is not uncommon to have discontinuities at a section.
      /// This class supports that by providing left and right values.
      class SYSCLASS SectionValue
      {
      public:
         SectionValue(Float64 val = 0.);
         SectionValue(Float64 left,Float64 right);
         SectionValue(const SectionValue&) = default;
         ~SectionValue() = default;

         SectionValue& operator=(const SectionValue&) = default;

         bool operator==(const SectionValue& rOther);

         SectionValue& operator=(Float64 val);
         SectionValue& operator+=(const SectionValue& rOther);
         SectionValue& operator-=(const SectionValue& rOther);
         SectionValue& operator*=(const SectionValue& rOther);
         SectionValue& operator/=(const SectionValue& rOther);
         SectionValue  operator-();
         SectionValue& operator+=(Float64 val);
         SectionValue& operator-=(Float64 val);
         SectionValue& operator*=(Float64 val);
         SectionValue& operator/=(Float64 val);

         /// Returns the value on the left of the section
         Float64& Left();

         /// Returns the value on the left of the section
         const Float64& Left() const;

         /// Returns the value on the right of the section
         Float64& Right();

         /// Returns the value on the right of the section
         const Float64& Right() const;

         /// Returns the value as a string. If the left and right values, the string shows a single value,
         /// otherwise the string shows left\\right
         std::_tstring AsString() const;

      private:
         Float64 m_Left;
         Float64 m_Right;
      };
   };
};

SYSFUNC WBFL::System::SectionValue operator+(const WBFL::System::SectionValue& a,const WBFL::System::SectionValue& b);
SYSFUNC WBFL::System::SectionValue operator-(const WBFL::System::SectionValue& a,const WBFL::System::SectionValue& b);
SYSFUNC WBFL::System::SectionValue operator*(const WBFL::System::SectionValue& a,const WBFL::System::SectionValue& b);
SYSFUNC WBFL::System::SectionValue operator*(const WBFL::System::SectionValue& a,Float64 k);
SYSFUNC WBFL::System::SectionValue operator*(Float64 k,const WBFL::System::SectionValue& a);
SYSFUNC WBFL::System::SectionValue operator/(const WBFL::System::SectionValue& a,const WBFL::System::SectionValue& b);
SYSFUNC WBFL::System::SectionValue operator/(const WBFL::System::SectionValue& a,Float64 k);
SYSFUNC WBFL::System::SectionValue operator/(Float64 k,const WBFL::System::SectionValue& a);
SYSFUNC std::_tostream& operator<<(std::_tostream& os,const WBFL::System::SectionValue& a);

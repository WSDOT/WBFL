///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>
#include <System\SectionValue.h>
#include <sstream>
#include <MathEx.h>

using namespace WBFL::System;

SectionValue::SectionValue(Float64 val) :
m_Left(val), m_Right(val)
{
}

SectionValue::SectionValue(Float64 left,Float64 right) :
m_Left(left), m_Right(right)
{
}

bool SectionValue::operator==(const SectionValue& rOther) const
{
   return IsEqual(Left(),rOther.Left()) && IsEqual(Right(),rOther.Right());
}

SectionValue& SectionValue::operator=(Float64 val)
{
   m_Left = val; m_Right = val; return* this;
}

SectionValue& SectionValue::operator+=(const SectionValue& rOther)
{
   m_Left += rOther.m_Left; m_Right += rOther.m_Right; return *this; 
}

SectionValue& SectionValue::operator-=(const SectionValue& rOther)
{
   m_Left -= rOther.m_Left; m_Right -= rOther.m_Right; return *this; 
}

SectionValue& SectionValue::operator*=(const SectionValue& rOther)
{
   m_Left *= rOther.m_Left; m_Right *= rOther.m_Right; return *this; 
}

SectionValue& SectionValue::operator/=(const SectionValue& rOther)
{
   m_Left /= rOther.m_Left; m_Right /= rOther.m_Right; return *this; 
}

SectionValue SectionValue::operator-()
{
   return SectionValue( -m_Left, -m_Right ); 
}

SectionValue& SectionValue::operator+=(Float64 val)
{
   m_Left += val; m_Right += val; return *this; 
}

SectionValue& SectionValue::operator-=(Float64 val)
{
   m_Left -= val; m_Right -= val; return *this; 
}

SectionValue& SectionValue::operator*=(Float64 val)
{
   m_Left *= val; m_Right *= val; return *this; 
}

SectionValue& SectionValue::operator/=(Float64 val)
{
   m_Left /= val; m_Right /= val; return *this; 
}

std::_tstring SectionValue::AsString() const
{
   std::_tostringstream os;
   if ( !IsEqual( Left(), Right() ) )
      os << Left() << _T("\\") << Right();
   else
      os << Left();

   return os.str();
}

const Float64& SectionValue::Left() const
{
   return m_Left;
}

Float64& SectionValue::Left()
{
   return m_Left;
}

const Float64& SectionValue::Right() const
{
   return m_Right;
}

Float64& SectionValue::Right()
{
   return m_Right;
}

SYSFUNC WBFL::System::SectionValue operator+(const WBFL::System::SectionValue& a,const WBFL::System::SectionValue& b)
{
   return WBFL::System::SectionValue( a.Left()  + b.Left(),
                          a.Right() + b.Right() );
}

SYSFUNC WBFL::System::SectionValue operator-(const WBFL::System::SectionValue& a,const WBFL::System::SectionValue& b)
{
   return WBFL::System::SectionValue( a.Left()  - b.Left(),
                          a.Right() - b.Right() );
}

SYSFUNC WBFL::System::SectionValue operator*(const WBFL::System::SectionValue& a,const WBFL::System::SectionValue& b)
{
   return WBFL::System::SectionValue( a.Left()  * b.Left(), 
                          a.Right() * b.Right() );
}

SYSFUNC WBFL::System::SectionValue operator*(const WBFL::System::SectionValue& a,Float64 k)
{
   return WBFL::System::SectionValue(a.Left()*k,a.Right()*k);
}

SYSFUNC WBFL::System::SectionValue operator*(Float64 k,const WBFL::System::SectionValue& a)
{
   return WBFL::System::SectionValue(a.Left()*k,a.Right()*k);
}

SYSFUNC WBFL::System::SectionValue operator/(const WBFL::System::SectionValue& a,const WBFL::System::SectionValue& b)
{
   return WBFL::System::SectionValue( a.Left()  / b.Left(),
                          a.Right() / b.Right() );
}

SYSFUNC WBFL::System::SectionValue operator/(const WBFL::System::SectionValue& a,Float64 k)
{
   return WBFL::System::SectionValue(a.Left()/k,a.Right()/k);
}

SYSFUNC WBFL::System::SectionValue operator/(Float64 k,const WBFL::System::SectionValue& a)
{
   return WBFL::System::SectionValue(a.Left()/k,a.Right()/k);
}

SYSFUNC std::_tostream& operator<<(std::_tostream& os,const WBFL::System::SectionValue& a)
{
   if ( !IsEqual( a.Left(), a.Right() ) )
      os << a.Left() << _T("\\") << a.Right();
   else
      os << a.Left();

   return os;
}



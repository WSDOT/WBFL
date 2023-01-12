///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>

/****************************************************************************
CLASS
   sysSectionValue
****************************************************************************/

#include <System\SectionValue.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysSectionValue::sysSectionValue(Float64 val) :
m_Left(val), m_Right(val)
{
}

sysSectionValue::sysSectionValue(Float64 left,Float64 right) :
m_Left(left), m_Right(right)
{
}

sysSectionValue::sysSectionValue(const sysSectionValue& rOther)
{
   MakeCopy(rOther);
}

sysSectionValue::~sysSectionValue()
{
}

//======================== OPERATORS  =======================================
sysSectionValue& sysSectionValue::operator= (const sysSectionValue& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

sysSectionValue& sysSectionValue::operator=(Float64 val)
{
   m_Left = val; m_Right = val; return* this;
}

sysSectionValue& sysSectionValue::operator+=(const sysSectionValue& rOther)
{
   m_Left += rOther.m_Left; m_Right += rOther.m_Right; return *this; 
}

sysSectionValue& sysSectionValue::operator-=(const sysSectionValue& rOther)
{
   m_Left -= rOther.m_Left; m_Right -= rOther.m_Right; return *this; 
}

sysSectionValue& sysSectionValue::operator*=(const sysSectionValue& rOther)
{
   m_Left *= rOther.m_Left; m_Right *= rOther.m_Right; return *this; 
}

sysSectionValue& sysSectionValue::operator/=(const sysSectionValue& rOther)
{
   m_Left /= rOther.m_Left; m_Right /= rOther.m_Right; return *this; 
}

sysSectionValue sysSectionValue::operator-()
{
   return sysSectionValue( -m_Left, -m_Right ); 
}

sysSectionValue& sysSectionValue::operator+=(Float64 val)
{
   m_Left += val; m_Right += val; return *this; 
}

sysSectionValue& sysSectionValue::operator-=(Float64 val)
{
   m_Left -= val; m_Right -= val; return *this; 
}

sysSectionValue& sysSectionValue::operator*=(Float64 val)
{
   m_Left *= val; m_Right *= val; return *this; 
}

sysSectionValue& sysSectionValue::operator/=(Float64 val)
{
   m_Left /= val; m_Right /= val; return *this; 
}

//======================== OPERATIONS =======================================
std::_tstring sysSectionValue::AsString() const
{
   std::_tostringstream os;
   if ( !IsEqual( Left(), Right() ) )
      os << Left() << _T("\\") << Right();
   else
      os << Left();

   return os.str();
}

//======================== ACCESS     =======================================
const Float64& sysSectionValue::Left() const
{
   return m_Left;
}

Float64& sysSectionValue::Left()
{
   return m_Left;
}

const Float64& sysSectionValue::Right() const
{
   return m_Right;
}

Float64& sysSectionValue::Right()
{
   return m_Right;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void sysSectionValue::MakeCopy(const sysSectionValue& rOther)
{
   m_Left  = rOther.m_Left;
   m_Right = rOther.m_Right;
}

void sysSectionValue::MakeAssignment(const sysSectionValue& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

SYSFUNC sysSectionValue operator+(const sysSectionValue& a,const sysSectionValue& b)
{
   return sysSectionValue( a.Left()  + b.Left(),
                          a.Right() + b.Right() );
}

SYSFUNC sysSectionValue operator-(const sysSectionValue& a,const sysSectionValue& b)
{
   return sysSectionValue( a.Left()  - b.Left(),
                          a.Right() - b.Right() );
}

SYSFUNC sysSectionValue operator*(const sysSectionValue& a,const sysSectionValue& b)
{
   return sysSectionValue( a.Left()  * b.Left(), 
                          a.Right() * b.Right() );
}

SYSFUNC sysSectionValue operator*(const sysSectionValue& a,Float64 k)
{
   return sysSectionValue(a.Left()*k,a.Right()*k);
}

SYSFUNC sysSectionValue operator*(Float64 k,const sysSectionValue& a)
{
   return sysSectionValue(a.Left()*k,a.Right()*k);
}

SYSFUNC sysSectionValue operator/(const sysSectionValue& a,const sysSectionValue& b)
{
   return sysSectionValue( a.Left()  / b.Left(),
                          a.Right() / b.Right() );
}

SYSFUNC sysSectionValue operator/(const sysSectionValue& a,Float64 k)
{
   return sysSectionValue(a.Left()/k,a.Right()/k);
}

SYSFUNC sysSectionValue operator/(Float64 k,const sysSectionValue& a)
{
   return sysSectionValue(a.Left()/k,a.Right()/k);
}

SYSFUNC std::_tostream& operator<<(std::_tostream& os,const sysSectionValue& a)
{
   if ( !IsEqual( a.Left(), a.Right() ) )
      os << a.Left() << _T("\\") << a.Right();
   else
      os << a.Left();

   return os;
}



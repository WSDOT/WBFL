///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2013  Washington State Department of Transportation
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

#include <Material\MatLib.h>
#include <Material\ConcreteBase.h>
#include <Units\Units.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matConcreteBase
****************************************************************************/

matConcreteBase::matConcreteBase(LPCTSTR name) :
m_Name(name),
m_TimeAtCasting(0),
m_CureTime(1.0), // days
m_CureMethod(matConcreteBase::Moist),
m_StrengthDensity( 0 ),
m_WeightDensity( 0 ),
m_MaxAggregateSize(0),
m_Type(matConcreteBase::Normal),
m_Fct(0),
m_bHasFct(false),
m_RelativeHumidity(40.0),
m_VS(::ConvertToSysUnits(1.0,unitMeasure::Inch))
{
}

matConcreteBase::matConcreteBase(const matConcreteBase& rOther) :
m_Name(rOther.m_Name)
{
   m_TimeAtCasting    = rOther.m_TimeAtCasting;
   m_CureTime         = rOther.m_CureTime;
   m_CureMethod       = rOther.m_CureMethod;
   m_StrengthDensity  = rOther.m_StrengthDensity;
   m_WeightDensity    = rOther.m_WeightDensity;
   m_MaxAggregateSize = rOther.m_MaxAggregateSize;
   m_Type             = rOther.m_Type;
   m_Fct              = rOther.m_Fct;
   m_bHasFct          = rOther.m_bHasFct;
   m_RelativeHumidity = rOther.m_RelativeHumidity;
   m_VS               = rOther.m_VS;
}

matConcreteBase::~matConcreteBase()
{
}

//======================== OPERATORS  =======================================
void matConcreteBase::SetType(matConcreteBase::Type type)
{
   m_Type = type;
}

matConcreteBase::Type matConcreteBase::GetType() const
{
   return m_Type;
}

std::_tstring matConcreteBase::GetTypeName(matConcreteBase::Type type,bool bFull)
{
   switch(type)
   {
   case matConcreteBase::Normal:
      return bFull ? _T("Normal Weight Concrete") : _T("Normal");

   case matConcreteBase::AllLightweight:
      return bFull ? _T("All Lightweight Concrete") : _T("AllLightweight");

   case matConcreteBase::SandLightweight:
      return bFull ? _T("Sand Lightweight Concrete") : _T("SandLightweight");

   default:
      ATLASSERT(false); // is there a new type?
      return bFull ? _T("Normal Weight Concrete") : _T("Normal");
   }
}

matConcreteBase::Type matConcreteBase::GetTypeFromName(LPCTSTR strName)
{
   if ( std::_tstring(strName) == _T("Normal") )
      return matConcreteBase::Normal;

   if ( std::_tstring(strName) == _T("AllLightweight") )
      return matConcreteBase::AllLightweight;

   if ( std::_tstring(strName) == _T("SandLightweight") )
      return matConcreteBase::SandLightweight;

   ATLASSERT(false); // invalid name
   return matConcreteBase::Normal;
}

void matConcreteBase::SetName(const std::_tstring& name)
{
   m_Name = name;
}

std::_tstring matConcreteBase::GetName() const
{
   return m_Name;
}

void matConcreteBase::SetAggSplittingStrength(Float64 fct)
{
   m_Fct = fct;
}

Float64 matConcreteBase::GetAggSplittingStrength() const
{
   return m_Fct;
}

void matConcreteBase::HasAggSplittingStrength(bool bHasFct)
{
   m_bHasFct = bHasFct;
}

bool matConcreteBase::HasAggSplittingStrength() const
{
   return m_bHasFct;
}

void matConcreteBase::SetStrengthDensity(Float64 density)
{
   m_StrengthDensity = density;
}

Float64 matConcreteBase::GetStrengthDensity() const
{
   return m_StrengthDensity;
}

void matConcreteBase::SetWeightDensity(Float64 density)
{
   m_WeightDensity = density;
}

Float64 matConcreteBase::GetWeightDensity() const
{
   return m_WeightDensity;
}

void matConcreteBase::SetMaxAggregateSize(Float64 size)
{
   m_MaxAggregateSize = size;
}

Float64 matConcreteBase::GetMaxAggregateSize() const
{
   return m_MaxAggregateSize;
}

void matConcreteBase::SetRelativeHumidity(Float64 rh)
{
   m_RelativeHumidity = rh;
}

Float64 matConcreteBase::GetRelativeHumidity() const
{
   return m_RelativeHumidity;
}

void matConcreteBase::SetVSRatio(Float64 vs)
{
   m_VS = vs;
}

Float64 matConcreteBase::GetVSRatio() const
{
   return m_VS;
}

void matConcreteBase::SetTimeAtCasting(Float64 time)
{
   m_TimeAtCasting = time;
}

Float64 matConcreteBase::GetTimeAtCasting() const
{
   return m_TimeAtCasting;
}

void matConcreteBase::SetCureTime(Float64 t)
{
   m_CureTime = t;
}

Float64 matConcreteBase::GetCureTime() const
{
   return m_CureTime;
}

void matConcreteBase::SetCureMethod(matConcreteBase::CureMethod method)
{
   m_CureMethod = method;
}

matConcreteBase::CureMethod matConcreteBase::GetCureMethod() const
{
   return m_CureMethod;
}

Float64 matConcreteBase::GetAge(Float64 t) const
{
   return t - m_TimeAtCasting;
}

///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2017  Washington State Department of Transportation
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
m_AgeAtInitialLoading(1.0), // days
m_CureTime(1.0), // days
m_CureMethod(matConcreteBase::Moist),
m_StrengthDensity( 0 ),
m_WeightDensity( 0 ),
m_MaxAggregateSize(0),
m_Type(matConcreteBase::Normal),
m_Fct(0),
m_bHasFct(false),
m_RelativeHumidity(40.0),
m_VS(-9999)
{
}

matConcreteBase::matConcreteBase(const matConcreteBase& rOther) :
m_Name(rOther.m_Name)
{
   m_TimeAtCasting    = rOther.m_TimeAtCasting;
   m_AgeAtInitialLoading = rOther.m_AgeAtInitialLoading;
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
   if ( m_Type != type )
   {
      m_Type = type;
      OnChanged();
   }
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
   if ( m_Name != name )
   {
      m_Name = name; 
      OnChanged();
   }
}

std::_tstring matConcreteBase::GetName() const
{
   return m_Name;
}

void matConcreteBase::SetAggSplittingStrength(Float64 fct)
{
   if ( m_Fct != fct )
   {
      m_Fct = fct;
      OnChanged();
   }
}

Float64 matConcreteBase::GetAggSplittingStrength() const
{
   return m_Fct;
}

void matConcreteBase::HasAggSplittingStrength(bool bHasFct)
{
   if ( m_bHasFct != bHasFct )
   {
      m_bHasFct = bHasFct;
      OnChanged();
   }
}

bool matConcreteBase::HasAggSplittingStrength() const
{
   return m_bHasFct;
}

void matConcreteBase::SetStrengthDensity(Float64 density)
{
   if ( m_StrengthDensity != density )
   {
      m_StrengthDensity = density;
      OnChanged();
   }
}

Float64 matConcreteBase::GetStrengthDensity() const
{
   return m_StrengthDensity;
}

void matConcreteBase::SetWeightDensity(Float64 density)
{
   if ( m_WeightDensity != density )
   {
      m_WeightDensity = density;
      OnChanged();
   }
}

Float64 matConcreteBase::GetWeightDensity() const
{
   return m_WeightDensity;
}

void matConcreteBase::SetMaxAggregateSize(Float64 size)
{
   if ( m_MaxAggregateSize != size )
   {
      m_MaxAggregateSize = size;
      OnChanged();
   }
}

Float64 matConcreteBase::GetMaxAggregateSize() const
{
   return m_MaxAggregateSize;
}

void matConcreteBase::SetRelativeHumidity(Float64 rh)
{
   if ( m_RelativeHumidity != rh )
   {
      m_RelativeHumidity = rh;   
      OnChanged();
   }
}

Float64 matConcreteBase::GetRelativeHumidity() const
{
   return m_RelativeHumidity;
}

void matConcreteBase::SetVSRatio(Float64 vs)
{
   if ( m_VS != vs )
   {
      m_VS = vs;
      OnChanged();
   }
}

Float64 matConcreteBase::GetVSRatio() const
{
   return m_VS;
}

void matConcreteBase::SetTimeAtCasting(Float64 time)
{
   if ( m_TimeAtCasting != time )
   {
      m_TimeAtCasting = time;
      OnChanged();
   }
}

Float64 matConcreteBase::GetTimeAtCasting() const
{
   return m_TimeAtCasting;
}

void matConcreteBase::SetAgeAtInitialLoading(Float64 age)
{
   if ( m_AgeAtInitialLoading != age )
   {
      m_AgeAtInitialLoading = age;
      OnChanged();
   }
}

Float64 matConcreteBase::GetAgeAtInitialLoading() const
{
   return m_AgeAtInitialLoading;
}

void matConcreteBase::SetCureTime(Float64 t)
{
   if ( m_CureTime != t )
   {
      m_CureTime = t;
      OnChanged();
   }
}

Float64 matConcreteBase::GetCureTime() const
{
   return m_CureTime;
}

void matConcreteBase::SetCureMethod(matConcreteBase::CureMethod method)
{
   if ( m_CureMethod != method )
   {
      m_CureMethod = method;
      OnChanged();
   }
}

matConcreteBase::CureMethod matConcreteBase::GetCureMethod() const
{
   return m_CureMethod;
}

void matConcreteBase::OnChanged()
{
   // by default, do nothing
}

void matConcreteBase::InitializeShrinkageDetails(Float64 t,matConcreteBaseShrinkageDetails* pDetails) const
{
   pDetails->cureMethod = GetCureMethod();
   pDetails->shrinkage_duration = t - (m_CureTime + m_TimeAtCasting);
}

void matConcreteBase::InitializeCreepDetails(Float64 t,Float64 tla,matConcreteBaseCreepDetails* pDetails) const
{
   pDetails->age = GetAge(t);
   pDetails->age_at_loading = GetAge(tla);
}

Float64 matConcreteBase::GetAge(Float64 t) const
{
   return t - m_TimeAtCasting;
}

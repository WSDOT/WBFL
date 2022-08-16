///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MatLib.h>
#include <Materials/ConcreteBase.h>
#include <Units\Units.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

ConcreteBase::ConcreteBase(const std::_tstring& name) :
m_Name(name),
m_TimeAtCasting(0),
m_AgeAtInitialLoading(1.0), // days
m_CureTime(1.0), // days
m_CuringType(CuringType::Moist),
m_StrengthDensity( 0 ),
m_WeightDensity( 0 ),
m_MaxAggregateSize(0),
m_FiberLength(0),
m_Type(ConcreteType::Normal),
m_Fct(0),
m_bHasFct(false),
m_RelativeHumidity(40.0),
m_VS(-9999)
{
}

ConcreteBase::~ConcreteBase()
{
}

//======================== OPERATORS  =======================================
void ConcreteBase::SetType(ConcreteType type)
{
   if ( m_Type != type )
   {
      m_Type = type;
      OnChanged();
   }
}

ConcreteType ConcreteBase::GetType() const
{
   return m_Type;
}

std::_tstring ConcreteBase::GetTypeName(ConcreteType type,bool bFull)
{
   switch(type)
   {
   case ConcreteType::Normal:
      return bFull ? _T("Normal Weight Concrete") : _T("Normal");

   case ConcreteType::AllLightweight:
      return bFull ? _T("All Lightweight Concrete") : _T("AllLightweight");

   case ConcreteType::SandLightweight:
      return bFull ? _T("Sand Lightweight Concrete") : _T("SandLightweight");

   case ConcreteType::PCI_UHPC:
      return bFull ? _T("PCI Ultra High Performance Concrete (PCI-UHPC)") : _T("PCI-UHPC");

   default:
      ASSERT(false); // is there a new type?
      return bFull ? _T("Normal Weight Concrete") : _T("Normal");
   }
}

ConcreteType ConcreteBase::GetTypeFromTypeName(LPCTSTR strName)
{
   if ( std::_tstring(strName) == _T("Normal") )
      return ConcreteType::Normal;

   if ( std::_tstring(strName) == _T("AllLightweight") )
      return ConcreteType::AllLightweight;

   if ( std::_tstring(strName) == _T("SandLightweight") )
      return ConcreteType::SandLightweight;

   if (std::_tstring(strName) == _T("PCI-UHPC"))
      return ConcreteType::PCI_UHPC;

   ATLASSERT(false); // invalid name
   return ConcreteType::Normal;
}

std::_tstring ConcreteBase::GetCuringType(CuringType curingType)
{
   switch (curingType)
   {
   case CuringType::Moist:
      return _T("Moist");

   case CuringType::Steam:
      return _T("Steam");

   default:
      ASSERT(false); // is there a new type?
      return _T("Unknown");
   }
}

void ConcreteBase::SetName(const std::_tstring& name)
{
   if ( m_Name != name )
   {
      m_Name = name; 
      OnChanged();
   }
}

std::_tstring ConcreteBase::GetName() const
{
   return m_Name;
}

void ConcreteBase::SetAggSplittingStrength(Float64 fct)
{
   if ( m_Fct != fct )
   {
      m_Fct = fct;
      OnChanged();
   }
}

Float64 ConcreteBase::GetAggSplittingStrength() const
{
   return m_Fct;
}

void ConcreteBase::HasAggSplittingStrength(bool bHasFct)
{
   if ( m_bHasFct != bHasFct )
   {
      m_bHasFct = bHasFct;
      OnChanged();
   }
}

bool ConcreteBase::HasAggSplittingStrength() const
{
   return m_bHasFct;
}

void ConcreteBase::SetStrengthDensity(Float64 density)
{
   if ( m_StrengthDensity != density )
   {
      m_StrengthDensity = density;
      OnChanged();
   }
}

Float64 ConcreteBase::GetStrengthDensity() const
{
   return m_StrengthDensity;
}

void ConcreteBase::SetWeightDensity(Float64 density)
{
   if ( m_WeightDensity != density )
   {
      m_WeightDensity = density;
      OnChanged();
   }
}

Float64 ConcreteBase::GetWeightDensity() const
{
   return m_WeightDensity;
}

void ConcreteBase::SetMaxAggregateSize(Float64 size)
{
   if ( !IsEqual(m_MaxAggregateSize,size) )
   {
      m_MaxAggregateSize = size;
      OnChanged();
   }
}

Float64 ConcreteBase::GetMaxAggregateSize() const
{
   return m_MaxAggregateSize;
}

void ConcreteBase::SetFiberLength(Float64 length)
{
   if (!IsEqual(m_FiberLength, length))
   {
      m_FiberLength = length;
      OnChanged();
   }
}

Float64 ConcreteBase::GetFiberLength() const
{
   return m_FiberLength;
}

void ConcreteBase::SetRelativeHumidity(Float64 rh)
{
   if ( m_RelativeHumidity != rh )
   {
      m_RelativeHumidity = rh;   
      OnChanged();
   }
}

Float64 ConcreteBase::GetRelativeHumidity() const
{
   return m_RelativeHumidity;
}

void ConcreteBase::SetVSRatio(Float64 vs)
{
   if ( m_VS != vs )
   {
      m_VS = vs;
      OnChanged();
   }
}

Float64 ConcreteBase::GetVSRatio() const
{
   return m_VS;
}

void ConcreteBase::SetTimeAtCasting(Float64 time)
{
   if ( m_TimeAtCasting != time )
   {
      m_TimeAtCasting = time;
      OnChanged();
   }
}

Float64 ConcreteBase::GetTimeAtCasting() const
{
   return m_TimeAtCasting;
}

void ConcreteBase::SetAgeAtInitialLoading(Float64 age)
{
   if ( m_AgeAtInitialLoading != age )
   {
      m_AgeAtInitialLoading = age;
      OnChanged();
   }
}

Float64 ConcreteBase::GetAgeAtInitialLoading() const
{
   return m_AgeAtInitialLoading;
}

void ConcreteBase::SetCureTime(Float64 t)
{
   if ( m_CureTime != t )
   {
      m_CureTime = t;
      OnChanged();
   }
}

Float64 ConcreteBase::GetCureTime() const
{
   return m_CureTime;
}

void ConcreteBase::SetCuringType(CuringType method)
{
   if ( m_CuringType != method )
   {
      m_CuringType = method;
      OnChanged();
   }
}

CuringType ConcreteBase::GetCuringType() const
{
   return m_CuringType;
}

void ConcreteBase::OnChanged()
{
   // by default, do nothing
}

void ConcreteBase::InitializeShrinkageDetails(Float64 t,ConcreteBaseShrinkageDetails* pDetails) const
{
   pDetails->curingType = GetCuringType();
   pDetails->shrinkage_duration = t - (m_CureTime + m_TimeAtCasting);
}

void ConcreteBase::InitializeCreepDetails(Float64 t,Float64 tla,ConcreteBaseCreepDetails* pDetails) const
{
   pDetails->age = GetAge(t);
   pDetails->age_at_loading = GetAge(tla);
}

Float64 ConcreteBase::GetAge(Float64 t) const
{
   return t - m_TimeAtCasting;
}

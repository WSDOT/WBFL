///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
// Copyright � 1999-2022  Washington State Department of Transportation
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
#include <Materials/SimpleConcrete.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

SimpleConcrete::SimpleConcrete() :
m_Name( _T("Unknown") ),
m_Fc( 0 ),
m_Density( 0 ),
m_WeightDensity(0),
m_FrShear(0),
m_FrFlexure(0),
m_ModE( 0 ),
m_MaxAggregateSize(0),
m_FiberLength(0),
m_Type(ConcreteType::Normal),
m_Fct(0),
m_bHasFct(false),
m_Lambda(1.0),
m_ffc(0),
m_frr(0),
m_AutogenousShrinkage(0)
{
   // Don't call assert value because this material model is not valid.
}

SimpleConcrete::SimpleConcrete(const std::_tstring& name, Float64 fc, Float64 density, Float64 wDensity, Float64 modE, Float64 frShear, Float64 frFlexure) :
   m_Name(name),
   m_Fc(fc),
   m_Density(density),
   m_WeightDensity(wDensity),
   m_FrShear(frShear),
   m_FrFlexure(frFlexure),
   m_ModE(modE),
   m_MaxAggregateSize(0.0),
   m_FiberLength(0.0),
   m_Type(ConcreteType::Normal),
   m_Fct(0),
   m_bHasFct(false),
   m_Lambda(1.0),
   m_ffc(0),
   m_frr(0),
   m_AutogenousShrinkage(0)
{
   ASSERTVALID;
}

SimpleConcrete::~SimpleConcrete()
{
}

bool SimpleConcrete::operator==(const SimpleConcrete& rOther) const
{
   if (m_Name != rOther.m_Name)
      return false;

   if (!::IsEqual(m_Fc, rOther.m_Fc))
      return false;

   if (!::IsEqual(m_Density, rOther.m_Density))
      return false;
   
   if (!::IsEqual(m_WeightDensity, rOther.m_WeightDensity))
      return false;

   if (!::IsEqual(m_FrShear, rOther.m_FrShear))
      return false;

   if (!::IsEqual(m_FrFlexure, rOther.m_FrFlexure))
      return false;

   if (!::IsEqual(m_ModE, rOther.m_ModE))
      return false;

   if (!::IsEqual(m_MaxAggregateSize, rOther.m_MaxAggregateSize))
      return false;

   if (!::IsEqual(m_FiberLength, rOther.m_FiberLength))
      return false;

   if (m_Type != rOther.m_Type)
      return false;

   if (!::IsEqual(m_Fct, rOther.m_Fct))
      return false;

   if (m_bHasFct != rOther.m_bHasFct)
      return false;

   if (!::IsEqual(m_Lambda, rOther.m_Lambda))
      return false;

   if (!::IsEqual(m_ffc, rOther.m_ffc))
      return false;

   if (!::IsEqual(m_frr, rOther.m_frr))
      return false;

   if (!::IsEqual(m_AutogenousShrinkage, rOther.m_AutogenousShrinkage))
      return false;

   return true;
}

bool SimpleConcrete::operator!=(const SimpleConcrete& rOther) const
{
   return !operator==(rOther);
}

void SimpleConcrete::SetType(ConcreteType type)
{
   m_Type = type;
}

ConcreteType SimpleConcrete::GetType() const
{
   return m_Type;
}

void SimpleConcrete::SetAggSplittingStrength(Float64 fct)
{
   m_Fct = fct;
}

Float64 SimpleConcrete::GetAggSplittingStrength() const
{
   return m_Fct;
}

void SimpleConcrete::HasAggSplittingStrength(bool bHasFct)
{
   m_bHasFct = bHasFct;
}

bool SimpleConcrete::HasAggSplittingStrength() const
{
   return m_bHasFct;
}

std::_tstring SimpleConcrete::GetTypeName(ConcreteType type,bool bFull)
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

ConcreteType SimpleConcrete::GetTypeFromTypeName(LPCTSTR strName)
{
   if ( std::_tstring(strName) == _T("Normal") )
      return ConcreteType::Normal;

   if ( std::_tstring(strName) == _T("AllLightweight") )
      return ConcreteType::AllLightweight;

   if ( std::_tstring(strName) == _T("SandLightweight") )
      return ConcreteType::SandLightweight;

   if (std::_tstring(strName) == _T("PCI-UHPC"))
      return ConcreteType::PCI_UHPC;

   ASSERT(false); // invalid name
   return ConcreteType::Normal;
}

std::unique_ptr<SimpleConcrete> SimpleConcrete::CreateClone() const
{
   return std::make_unique<SimpleConcrete>(*this);
}

void SimpleConcrete::SetName(const std::_tstring& name)
{
   m_Name = name;
}

std::_tstring SimpleConcrete::GetName() const
{
   return m_Name;
}

void SimpleConcrete::SetFc(Float64 fc)
{
   m_Fc = fc;
   ASSERTVALID;
}

Float64 SimpleConcrete::GetFc() const
{
   return m_Fc;
}

void SimpleConcrete::SetDensity(Float64 density)
{
   m_Density = density;
   ASSERTVALID;
}

Float64 SimpleConcrete::GetDensity() const
{
   return m_Density;
}

void SimpleConcrete::SetDensityForWeight(Float64 d)
{
   m_WeightDensity = d;
   ASSERTVALID;
}

Float64 SimpleConcrete::GetDensityForWeight() const
{
   return m_WeightDensity;
}

void SimpleConcrete::SetShearFr(Float64 fr)
{
   m_FrShear = fr;
   ASSERTVALID;
}

Float64 SimpleConcrete::GetShearFr() const
{
   return m_FrShear;
}

void SimpleConcrete::SetFlexureFr(Float64 fr)
{
   m_FrFlexure = fr;
   ASSERTVALID;
}

Float64 SimpleConcrete::GetFlexureFr() const
{
   return m_FrFlexure;
}

void SimpleConcrete::SetE(Float64 modE)
{
   m_ModE = modE;
   ASSERTVALID;
}

Float64 SimpleConcrete::GetE() const
{
   return m_ModE;
}

void SimpleConcrete::SetMaxAggregateSize(Float64 size)
{
   m_MaxAggregateSize = size;
}

Float64 SimpleConcrete::GetMaxAggregateSize() const
{
   return m_MaxAggregateSize;
}

void SimpleConcrete::SetFiberLength(Float64 length)
{
   m_FiberLength = length;
}

Float64 SimpleConcrete::GetFiberLength() const
{
   return m_FiberLength;
}

void SimpleConcrete::SetLambda(Float64 lambda)
{
   m_Lambda = lambda;
}

Float64 SimpleConcrete::GetLambda() const
{
   return m_Lambda;
}

void SimpleConcrete::SetFirstCrackingStrength(Float64 ffc)
{
   m_ffc = ffc;
}

Float64 SimpleConcrete::GetFirstCrackingStrength() const
{
   return m_ffc;
}

void SimpleConcrete::SetPostCrackingTensileStrength(Float64 frr)
{
   m_frr = frr;
}

Float64 SimpleConcrete::GetPostCrackingTensileStrength() const
{
   return m_frr;
}

void SimpleConcrete::SetAutogenousShrinkage(Float64 as)
{
   m_AutogenousShrinkage = as;
}

Float64 SimpleConcrete::GetAutogenousShrinkage() const
{
   return m_AutogenousShrinkage;
}

#if defined _DEBUG
bool SimpleConcrete::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void SimpleConcrete::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for SimpleConcrete")         << WBFL::Debug::endl;
   os << _T("====================")         << WBFL::Debug::endl;
   os << _T("Name    : ") << m_Name.c_str() << WBFL::Debug::endl;
   os << _T("Fc      : ") << m_Fc           << WBFL::Debug::endl;
   os << _T("Density : ") << m_Density      << WBFL::Debug::endl;
   os << _T("Mod E   : ") << m_ModE         << WBFL::Debug::endl;
   os << _T("Max Aggr: ") << m_MaxAggregateSize<< WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool SimpleConcrete::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("SimpleConcrete");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for SimpleConcrete");
   TESTME_EPILOG("SimpleConcrete");
}
#endif // _UNITTEST
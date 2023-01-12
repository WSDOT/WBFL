///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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
m_AutogenousShrinkage(0),
m_alpha_u(0.85),
m_ecu(0),
m_etcr(0),
m_ftcri(0),
m_ftcr(0),
m_ftloc(0),
m_etloc(0),
m_bExperimental_ecu(false)
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
   m_AutogenousShrinkage(0),
   m_alpha_u(0.85),
   m_ecu(0),
   m_etcr(0),
   m_ftcri(0),
   m_ftcr(0),
   m_ftloc(0),
   m_etloc(0),
   m_bExperimental_ecu(false)
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

   // PCI UHPC
   if (!::IsEqual(m_ffc, rOther.m_ffc))
      return false;

   if (!::IsEqual(m_frr, rOther.m_frr))
      return false;

   if (!::IsEqual(m_AutogenousShrinkage, rOther.m_AutogenousShrinkage))
      return false;

   // FHWA UHPC
   if (!IsEqual(m_alpha_u, rOther.m_alpha_u))
      return false;

   if (m_bExperimental_ecu != rOther.m_bExperimental_ecu)
      return false;

   if(m_bExperimental_ecu && !::IsEqual(m_ecu, rOther.m_ecu)) // only check if experimental value
      return false;

   if (!::IsEqual(m_etcr, rOther.m_etcr))
      return false;

   if (!::IsEqual(m_ftcri, rOther.m_ftcri))
      return false;

   if (!::IsEqual(m_ftcr, rOther.m_ftcr))
      return false;

   if (!::IsEqual(m_ftloc, rOther.m_ftloc))
      return false;
   
   if (!::IsEqual(m_etloc, rOther.m_etloc))
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

void SimpleConcrete::SetCompressionResponseReductionFactor(Float64 alpha_u)
{
   m_alpha_u = alpha_u;
}

Float64 SimpleConcrete::GetCompressionResponseReductionFactor() const
{
   return m_alpha_u;
}

void SimpleConcrete::SetCompressiveStrainLimit(Float64 ecu)
{
   m_ecu = ecu;
   m_bExperimental_ecu = true;
}

void SimpleConcrete::SetElasticTensileStrainLimit(Float64 etcr)
{
   m_etcr = etcr;
}

Float64 SimpleConcrete::GetElasticTensileStrainLimit() const
{
   return m_etcr;
}

void SimpleConcrete::SetInitialEffectiveCrackingStrength(Float64 ft_cri)
{
   m_ftcri = ft_cri;
}

Float64 SimpleConcrete::GetInitialEffectiveCrackingStrength() const
{
   return m_ftcri;
}

void SimpleConcrete::SetDesignEffectiveCrackingStrength(Float64 ft_cr)
{
   m_ftcr = ft_cr;
}

Float64 SimpleConcrete::GetDesignEffectiveCrackingStrength() const
{
   return m_ftcr;
}

void SimpleConcrete::SetCrackLocalizationStrength(Float64 ft_loc)
{
   m_ftloc = ft_loc;
}

Float64 SimpleConcrete::GetCrackLocalizationStrength() const
{
   return m_ftloc;
}

void SimpleConcrete::SetCrackLocalizationStrain(Float64 et_loc)
{
   m_etloc = et_loc;
}

Float64 SimpleConcrete::GetCrackLocalizationStrain() const
{
   return m_etloc;
}

Float64 SimpleConcrete::GetElasticCompressiveStrainLimit() const
{
   Float64 e_cp = -1.0 * m_alpha_u * m_Fc / m_ModE; // GS Eq 1.4.2.4.2-1
   return e_cp;
}

Float64 SimpleConcrete::GetCompressiveStrainLimit(bool* pbIsExperimental) const
{
   if (pbIsExperimental)
   {
      *pbIsExperimental = m_bExperimental_ecu;
   }

   if (m_bExperimental_ecu)
   {
      return m_ecu;
   }
   else
   {
      // GS 1.4.2.4.2
      Float64 e_cp = GetElasticCompressiveStrainLimit();
      return Min(e_cp, -0.0035);
   }
}

//======================== DEBUG      =======================================
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

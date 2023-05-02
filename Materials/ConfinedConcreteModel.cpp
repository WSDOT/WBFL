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
#include <Materials/ConfinedConcreteModel.h>

#include <Units/Convert.h>
#include <Units/Measure.h>

using namespace WBFL::Materials;

ConfinedConcreteModel::ConfinedConcreteModel(const std::_tstring& strName) :
   StressStrainModel(strName)
{
}

void ConfinedConcreteModel::SetSection(const std::shared_ptr<const ManderModelSection>& section)
{
   m_Section = section;
}

const std::shared_ptr<const ManderModelSection>& ConfinedConcreteModel::GetSection() const
{
   return m_Section;
}

void ConfinedConcreteModel::Set_fco(Float64 fco)
{
   m_fco = WBFL::Units::ConvertFromSysUnits(fco, WBFL::Units::Measure::PSI);
}

Float64 ConfinedConcreteModel::Get_fco() const
{
   return WBFL::Units::ConvertToSysUnits(m_fco, WBFL::Units::Measure::PSI);
}

void ConfinedConcreteModel::Set_eco(Float64 eco)
{
   m_eco = eco;
}

Float64 ConfinedConcreteModel::Get_eco() const
{
   return m_eco;
}

void ConfinedConcreteModel::SetR(Float64 r)
{
   m_R = r;
}

Float64 ConfinedConcreteModel::GetR() const
{
   return m_R;
}

void ConfinedConcreteModel::ComputeConcreteProperties(Float64* pfr, Float64* pfcc, Float64* pecc) const
{
   Float64 ke = m_Section->GetConfinementEffectivenessCoefficient();
   Float64 ps = m_Section->GetTransvReinforcementRatio();
   Float64 fyh = m_Section->GetTransvYieldStrength();

   fyh = WBFL::Units::ConvertFromSysUnits(fyh, WBFL::Units::Measure::PSI);

   Float64 fr = 0.5 * ke * ps * fyh;
   Float64 fcc = m_fco * (-1.254 + 2.254 * sqrt(1 + 7.94 * (fr / m_fco)) - 2 * (fr / m_fco));
   Float64 ecc = m_eco * (1 + m_R * (fcc / m_fco - 1));

   fr = WBFL::Units::ConvertToSysUnits(fr, WBFL::Units::Measure::PSI);
   fcc = WBFL::Units::ConvertToSysUnits(fcc, WBFL::Units::Measure::PSI);

   *pfr = fr;
   *pfcc = fcc;
   *pecc = ecc;
}

std::unique_ptr<StressStrainModel> ConfinedConcreteModel::Clone() const
{
   return std::make_unique<ConfinedConcreteModel>(*this);
}

Float64 ConfinedConcreteModel::GetYieldStrain() const
{
   Float64 Ec = GetEc();
   Float64 ey = -m_fco / Ec;
   return ey;
}

Float64 ConfinedConcreteModel::GetModulusOfElasticity() const
{
   Float64 Ec = GetEc(); // this is in PSI, we need to return it in system units
   Ec = WBFL::Units::ConvertToSysUnits(Ec, WBFL::Units::Measure::PSI);
   return Ec;
}

std::pair<Float64, bool> ConfinedConcreteModel::ComputeStress(Float64 strain) const
{
   if (0 < strain)
   {
      // for tension strain.... stress is 0.0
      return std::make_pair(0.0,true);
   }

   strain *= -1.0; // swap signs so we are working with positive strains

   Float64 Ec = GetEc();
   Float64 fr, fcc, ecc;
   ComputeConcreteProperties(&fr, &fcc, &ecc);

   fr = WBFL::Units::ConvertFromSysUnits(fr, WBFL::Units::Measure::PSI);
   fcc = WBFL::Units::ConvertFromSysUnits(fcc, WBFL::Units::Measure::PSI);

   Float64 Esec = fcc / ecc;

   Float64 r = Ec / (Ec - Esec);
   Float64 x = strain / ecc;
   Float64 fc = fcc * x * r / (r - 1 + pow(x, r));

   Float64 stress = WBFL::Units::ConvertToSysUnits(fc, WBFL::Units::Measure::PSI);
   stress *= -1.0;

   Float64 minStrain, maxStrain;
   GetStrainLimits(&minStrain, &maxStrain);

   std::pair<Float64, bool> result(stress, strain < minStrain ? false : true);
   return result;
}

void ConfinedConcreteModel::GetStrainLimits(Float64* pMinStrain, Float64* pMaxStrain) const
{
   PRECONDITION(pMinStrain != nullptr);
   PRECONDITION(pMaxStrain != nullptr);

   Float64 fr, fcc, ecc;
   ComputeConcreteProperties(&fr, &fcc, &ecc);

   fr = WBFL::Units::ConvertFromSysUnits(fr, WBFL::Units::Measure::PSI);
   fcc = WBFL::Units::ConvertFromSysUnits(fcc, WBFL::Units::Measure::PSI);

   Float64 ps  = m_Section->GetTransvReinforcementRatio();
   Float64 fyh = m_Section->GetTransvYieldStrength();
   Float64 esu = m_Section->GetTransvReinforcementRuptureStrain();

   fyh = WBFL::Units::ConvertFromSysUnits(fyh, WBFL::Units::Measure::PSI);

   // see "Seismic Design and Retrofit of Bridges", Priestley,  Pg 272, Eqn 5.14
   Float64 ecu = 0.004 + 1.4 * ps * fyh * esu / fcc;

   *pMinStrain = -ecu;
   *pMaxStrain = DBL_MAX;
}

Float64 ConfinedConcreteModel::GetStrainAtPeakStress() const
{
   Float64 fr, fcc, ecc;
   ComputeConcreteProperties(&fr, &fcc, &ecc);
   return -ecc;
}

Float64 ConfinedConcreteModel::GetEc() const
{
   Float64 Es = 60000.0 * sqrt(m_fco); // psi
   Es = WBFL::Units::ConvertToSysUnits(Es, WBFL::Units::Measure::PSI);
   return Es;
}

#if defined _DEBUG
bool ConfinedConcreteModel::AssertValid() const
{
   return true;
}

void ConfinedConcreteModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ConfinedConcreteModel")         << WBFL::Debug::endl;
   os << _T("====================")         << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool ConfinedConcreteModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConfinedConcreteModel");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for ConfinedConcreteModel");

   TESTME_EPILOG("ConfinedConcreteModel");
}
#endif // _UNITTEST

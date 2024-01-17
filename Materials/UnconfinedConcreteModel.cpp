///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <Materials/UnconfinedConcreteModel.h>

#include <Units/Convert.h>
#include <Units/Measure.h>

using namespace WBFL::Materials;

UnconfinedConcreteModel::UnconfinedConcreteModel(const std::_tstring& strName,Float64 fc) :
   StressStrainModel(strName)
{
   SetFc(fc);
}

void UnconfinedConcreteModel::SetFc(Float64 fc)
{
   // inbound value is in system units
   // all the calculations in this object require KSI units
   // convert the inbound value to KSI
   PRECONDITION(0 <= fc);
   m_Fc = WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::KSI);
   UpdateParameters();
}

Float64 UnconfinedConcreteModel::GetFc() const
{
   // the internal value is in KSI, convert it back to system units
   return WBFL::Units::ConvertToSysUnits(m_Fc,WBFL::Units::Measure::KSI);
}

std::unique_ptr<StressStrainModel> UnconfinedConcreteModel::Clone() const
{
   return std::make_unique<UnconfinedConcreteModel>(*this);
}

Float64 UnconfinedConcreteModel::GetYieldStrain() const
{
   Float64 Ec = GetEc();
   Float64 ey = m_Fc / Ec;
   return ey;
}

Float64 UnconfinedConcreteModel::GetModulusOfElasticity() const
{
   Float64 Ec = GetEc(); // this is in KSI, we need to return it in system units
   Ec = WBFL::Units::ConvertToSysUnits(Ec, WBFL::Units::Measure::KSI);
   return Ec;
}

std::pair<Float64, bool> UnconfinedConcreteModel::ComputeStress(Float64 strain) const
{
   if (0 < strain)
      return std::make_pair(0.0,true); // no tensile response

   Float64 e = strain;

   if (e < m_MinStrain) e = m_MinStrain;

   e *= -1.0; // work with positive values, so change the sign of the strain

   // use local variables to make the equations a little cleaner to read
   // these parameters are updated when f'c is changed
   Float64 n = m_n;
   Float64 k = m_k;
   Float64 Ec = m_Ec;
   Float64 ec = m_ec;

   Float64 e_ratio = e / ec;
   if (e_ratio < 1.0)
      k = 1.00;

   if (k < 1.00)
      k = 1.00;

   Float64 f = m_Fc * (n * (e_ratio) / ((n - 1) + pow(e_ratio, n * k)));

   // The stress is in KSI, convert it to base units because that is what the caller expects
   // -1 because this should be a compression stress
   f = -1*WBFL::Units::ConvertToSysUnits(f, WBFL::Units::Measure::KSI);

   std::pair<Float64, bool> result(f, strain < m_MinStrain ? false : true);
   return result;
}

std::pair<Float64, Float64> UnconfinedConcreteModel::GetStrainLimits() const
{
   return { m_MinStrain,m_MaxStrain };
}

Float64 UnconfinedConcreteModel::GetStrainAtPeakStress() const
{
   Float64 Ec = GetEc();
   Float64 n = 0.8 + m_Fc / 2.5;

   Float64 strain = -(m_Fc / Ec) * (n / (n - 1));
   return strain;
}

void UnconfinedConcreteModel::UpdateParameters()
{
   m_n = 0.80 + m_Fc / 2.500;
   m_k = 0.67 + m_Fc / 9.000;
   m_Ec = GetEc();
   m_ec = m_Fc * m_n / (m_Ec * (m_n - 1));
}

Float64 UnconfinedConcreteModel::GetEc() const
{
   return (40.000 * sqrt(m_Fc * 1000) + 1000.000);
}

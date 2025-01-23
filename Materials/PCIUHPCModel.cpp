///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MatLib.h>
#include <Materials/PCIUHPCModel.h>
#include <Units/Convert.h>

using namespace WBFL::Materials;

PCIUHPCModel::PCIUHPCModel(const std::_tstring& strName) :
   StressStrainModel(strName)
{
}

void PCIUHPCModel::SetFc(Float64 fc)
{
   PRECONDITION(0 < fc);
   m_fc = WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::KSI);
   CHECK(17.4 <= m_fc); // 17.4 ksi is the minimum value for f'c, PCI-UHPC GS
}

Float64 PCIUHPCModel::GetFc() const
{
   return WBFL::Units::ConvertToSysUnits(m_fc,WBFL::Units::Measure::KSI);
}

std::unique_ptr<StressStrainModel> PCIUHPCModel::Clone() const
{
   return std::make_unique<PCIUHPCModel>(*this);
}

Float64 PCIUHPCModel::GetYieldStrain() const
{
   return 0.00012;
}

Float64 PCIUHPCModel::GetModulusOfElasticity() const
{
   Float64 Ec = GetEc(); // this is in KSI, we need to return it in system units
   Ec = WBFL::Units::ConvertToSysUnits(Ec, WBFL::Units::Measure::KSI);
   return Ec;
}

std::pair<Float64, bool> PCIUHPCModel::ComputeStress(Float64 strain) const
{
   Float64 Ec = GetEc();

   Float64 stress = 0;
   bool bWithinStrainLimits = true;
   if (0 < strain)
   {
      // tension
      Float64 e_tcr = 0.00012;
      if (strain < e_tcr)
      {
         // strain is less than cracking
         stress = strain * 0.75 / e_tcr;
      }
      else if (::IsLE(strain, 0.005))
      {
         stress = 0.75; // ksi
      }
      else
      {
         // beyond localization so can't carry any tension
         stress = 0.0; // ksi
      }
   }
   else
   {
      // compression
      strain = fabs(strain);
      stress = 0.001 < strain ? -0.85 * m_fc : -0.85 * m_fc * strain / 0.001;
   }

   // The stress is in KSI, convert it to base units because that is what the caller expects
   stress = WBFL::Units::ConvertToSysUnits(stress, WBFL::Units::Measure::KSI);

   // NOTE: This stress-strain accomodates strains that are beyond the strain limit. For this reason,
   // we don't return false for strains exceeding the limits. If we did, the moment capacity solver would
   // not converge.

   return std::make_pair(stress, bWithinStrainLimits);
}

std::pair<Float64, Float64> PCIUHPCModel::GetStrainLimits() const
{
   return { -0.003, 0.005 };
}

Float64 PCIUHPCModel::GetStrainAtPeakStress() const
{
   return -0.003;
}

Float64 PCIUHPCModel::GetEc() const
{
   return 2500 * pow(m_fc, 0.33);
}


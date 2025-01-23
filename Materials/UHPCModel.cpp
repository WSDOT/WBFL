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
#include <Materials/UHPCModel.h>

#include <Units/Convert.h>
#include <Units/Measure.h>

using namespace WBFL::Materials;

UHPCModel::UHPCModel(const std::_tstring& strName) :
   StressStrainModel(strName)
{
}

void UHPCModel::SetFc(Float64 fc)
{
   PRECONDITION(0 < fc);
   m_fc = WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::KSI);
   CHECK(18.0 <= m_fc); // 18 ksi is the minimum value for f'c per UHPC GS 1.1
}

Float64 UHPCModel::GetFc() const
{
   return WBFL::Units::ConvertToSysUnits(m_fc,WBFL::Units::Measure::KSI);
}

void UHPCModel::SetCompressiveStrainLimit(Float64 ecu)
{
   m_ecu = ecu;
}

Float64 UHPCModel::GetCompressiveStrainLimit() const
{
   return m_ecu;
}

void UHPCModel::SetK1(Float64 k1)
{
   m_K1 = k1;
}

Float64 UHPCModel::GetK1() const
{
   return m_K1;
}

void UHPCModel::SetAlpha(Float64 alpha)
{
   m_alpha = alpha;
}

Float64 UHPCModel::GetAlpha() const
{
   return m_alpha;
}

void UHPCModel::SetFtcr(Float64 ftcr)
{
   m_ftcr = WBFL::Units::ConvertFromSysUnits(ftcr, WBFL::Units::Measure::KSI);
}

Float64 UHPCModel::GetFtcr() const
{
   return WBFL::Units::ConvertToSysUnits(m_ftcr, WBFL::Units::Measure::KSI);
}

void UHPCModel::SetFtloc(Float64 ftloc)
{
   m_ftloc = WBFL::Units::ConvertFromSysUnits(ftloc, WBFL::Units::Measure::KSI);
}

Float64 UHPCModel::GetFtloc() const
{
   return WBFL::Units::ConvertToSysUnits(m_ftloc, WBFL::Units::Measure::KSI);
}

void UHPCModel::Set_etloc(Float64 etloc)
{
   m_etloc = etloc;
}

Float64 UHPCModel::Get_etloc() const
{
   return m_etloc;
}

void UHPCModel::SetGamma(Float64 gamma)
{
   m_gamma_u = gamma;
}

Float64 UHPCModel::GetGamma() const
{
   return m_gamma_u;
}

std::unique_ptr<StressStrainModel> UHPCModel::Clone() const
{
   return std::make_unique<UHPCModel>(*this);
}

Float64 UHPCModel::GetYieldStrain() const
{
   Float64 Ec = GetEc();
   Float64 ey = -1.0*m_alpha*m_fc / Ec;
   return ey;
}

Float64 UHPCModel::GetModulusOfElasticity() const
{
   Float64 Ec = GetEc(); // this is in KSI, we need to return it in system units
   Ec = WBFL::Units::ConvertToSysUnits(Ec, WBFL::Units::Measure::KSI);
   return Ec;
}

std::pair<Float64, bool> UHPCModel::ComputeStress(Float64 strain) const
{
   CHECK(m_ftcr <= m_ftloc); // ft,loc must be greater or equal to f,trc, UHPC GS 1.1

   Float64 Ec = GetEc();

   Float64 stress;
   bool bWithinStrainLimits = true;
   if (0 < strain)
   {
      // tension
      Float64 e_tcr = m_gamma_u * m_ftcr / Ec;
      if (strain < e_tcr)
      {
         // strain is less than cracking
         stress = strain * Ec;
      }
      else if (::IsLE(strain, m_gamma_u*m_etloc))
      {
         // if (ftloc < 1.2ftcr) then the tension is gamma_u*ftcr, otherwise there is strain hardening and stress continues to increase to gamma_u*ftloc at etloc
         stress = (m_ftloc < 1.2 * m_ftcr) ? m_gamma_u * m_ftcr : ::LinInterp(strain - e_tcr, m_gamma_u * m_ftcr, m_gamma_u * m_ftloc, m_gamma_u*m_etloc - e_tcr);
      }
      else
      {
         // beyond localization so can't carry any tension;
         stress = 0;
      }
   }
   else
   {
      // compression
      strain = fabs(strain);
      Float64 e_cp = 1.0 * m_alpha * m_fc / Ec;
      Float64 e_cu = Max(-m_ecu, e_cp);
      if (strain < e_cp)
      {
         stress = -strain * Ec;
      }
      else if (::IsLE(strain, e_cu))
      {
         stress = -1.0 * m_alpha * m_fc; // negative for compression
      }
      else
      {
         stress = -1.0 * m_alpha * m_fc;// 0.0; // beyond maximum strain
         bWithinStrainLimits = false;
      }
   }

   stress = WBFL::Units::ConvertToSysUnits(stress, WBFL::Units::Measure::KSI);
   return std::make_pair(stress, bWithinStrainLimits);
}

std::pair<Float64, Float64> UHPCModel::GetStrainLimits() const
{
   auto max = m_gamma_u*m_etloc;

   Float64 Ec = GetEc();
   Float64 e_cp = -1.0 * m_alpha * m_fc / Ec;
   auto min = Min(e_cp, m_ecu); // using Min because compression strain is negative. we want value that is furthest from zero on a number line. smaller negative values are further from zero.

   return { min,max };
}

Float64 UHPCModel::GetStrainAtPeakStress() const
{
   Float64 Ec = GetEc();
   Float64 e_cp = -1.0 * m_alpha * m_fc / Ec;
   return e_cp;
}

Float64 UHPCModel::GetEc() const
{
   return 2500*m_K1*pow(m_fc,0.33); // in KSI
}

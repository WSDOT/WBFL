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
#include <Materials/RebarModel.h>

#include <Units/Convert.h>
#include <Units/Measure.h>

using namespace WBFL::Materials;

RebarModel::RebarModel(const std::_tstring& strName, Float64 fy, Float64 Es, Float64 er) :
   StressStrainModel(strName)
{
   SetProperties(fy, Es, er);
}

RebarModel::RebarModel(const std::_tstring& strName, Float64 fy, Float64 fu, Float64 Es, Float64 esh, Float64 er) :
   StressStrainModel(strName)
{
   SetProperties(fy, fu, Es, esh, er);
}

void RebarModel::SetProperties(Float64 fy, Float64 Es, Float64 er)
{
   m_fy = fy;
   m_Es = Es;
   m_MaxStrain = er;
   m_bStrainHardeningModel = false;
}

void RebarModel::SetProperties(Float64 fy, Float64 fu, Float64 Es, Float64 esh, Float64 er)
{
   m_fy = fy;
   m_fu = fu;
   m_Es = Es;
   m_esh = esh;
   m_MaxStrain = er;
   m_bStrainHardeningModel = true;
}

void RebarModel::GetProperties(Float64* pfy, Float64* pfu, Float64* pEs, Float64* pesh, Float64* per, bool* pIsStrainHardening) const
{
   *pfy = m_fy;
   *pfu = m_fu;
   *pEs = m_Es;
   *pesh = m_esh;
   *per = m_MaxStrain;
   *pIsStrainHardening = m_bStrainHardeningModel;
}

std::unique_ptr<StressStrainModel> RebarModel::Clone() const
{
   return std::make_unique<RebarModel>(*this);
}

Float64 RebarModel::GetYieldStrain() const
{
   return m_fy / m_Es;
}

Float64 RebarModel::GetModulusOfElasticity() const
{
   return m_Es;
}

std::pair<Float64, bool> RebarModel::ComputeStress(Float64 strain) const
{
   Float64 ey = m_fy / m_Es;
   Float64 sign = BinarySign(strain);
   strain = fabs(strain);

   Float64 stress = 0;
   bool bIsWithinStrainLimits = true;
   if (m_bStrainHardeningModel)
   {
      if (InRange(0.0, strain, ey))
      {
         stress = m_Es * strain;
      }
      else if (InRange(ey, strain, m_esh))
      {
         stress = m_fy; // plateau
      }
      else if (InRange(m_esh, strain, m_MaxStrain))
      {
         stress = m_fu - (m_fu - m_fy) * pow((m_MaxStrain - strain), 2) / pow((m_esh - m_MaxStrain), 2); // strain hardening
      }
      else if (m_MaxStrain < strain)
      {
         stress = m_fu; // fractured, but just flatten out the line so that the solver doesn't have problems
         bIsWithinStrainLimits = (sign < 0 ? true : false);
      }
   }
   else
   {
      if (InRange(0.0, strain, ey))
      {
         stress = m_Es * strain;
      }
      else
      {
         stress = m_fy; // plateau
         bIsWithinStrainLimits = (sign < 0 ? true : false);
      }
   }

   stress *= sign;

   return std::make_pair(stress,::IsLT(m_MaxStrain, sign * strain) ? false : true);
}

std::pair<Float64, Float64> RebarModel::GetStrainLimits() const
{
   return { m_MinStrain, m_MaxStrain };
}

Float64 RebarModel::GetStrainAtPeakStress() const
{
   return m_MaxStrain;
}

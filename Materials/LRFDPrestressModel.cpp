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
#include <Materials/LRFDPrestressModel.h>


using namespace WBFL::Materials;

LRFDPrestressModel::LRFDPrestressModel(const std::_tstring& strName) :
   StressStrainModel(strName)
{
}

void LRFDPrestressModel::SetStrandType(StrandType type)
{
   m_Type = type;
}

StrandType LRFDPrestressModel::GetStrandType() const
{
   return m_Type;
}

void LRFDPrestressModel::SetFpu(Float64 fpu)
{
   m_fpu = fpu;
}

Float64 LRFDPrestressModel::GetFpu() const
{
   return m_fpu;
}

void LRFDPrestressModel::SetEps(Float64 Eps)
{
   m_Eps = Eps;
}

Float64 LRFDPrestressModel::GetEps() const
{
   return m_Eps;
}

void LRFDPrestressModel::SetStrainLimits(Float64 minStrain, Float64 maxStrain)
{
   m_MinStrain = minStrain;
   m_MaxStrain = maxStrain;
}

std::unique_ptr<StressStrainModel> LRFDPrestressModel::Clone() const
{
   return std::make_unique<LRFDPrestressModel>(*this);
}

Float64 LRFDPrestressModel::GetYieldStrain() const
{
   return (m_Type == StrandType::LowRelaxation ? 0.9 : 0.85)*m_fpu/m_Eps;
}

Float64 LRFDPrestressModel::GetModulusOfElasticity() const
{
   return GetEps();
}

std::pair<Float64, bool> LRFDPrestressModel::ComputeStress(Float64 strain) const
{
   Float64 sign = BinarySign(strain);
   strain = fabs(strain);

   Float64 k = (m_Type == StrandType::LowRelaxation ? 0.28 : 0.38); // LRFD Table C5.7.3.1.1-1

   Float64 c_over_d = 0.003 / (0.003 + strain);

   Float64 fps = m_fpu * (1 - k * c_over_d);

   fps *= sign;

   // this is a model for rebar and strand that is usually in tension and embedded in concrete. 
   // the return value assumes the material has infinite strain capacity in compression
   return std::make_pair(fps,::IsLT(m_MaxStrain, sign * strain) ? false : true);
}

std::pair<Float64, Float64> LRFDPrestressModel::GetStrainLimits() const
{
   return { m_MinStrain,m_MaxStrain };
}

Float64 LRFDPrestressModel::GetStrainAtPeakStress() const
{
   return m_MaxStrain;
}

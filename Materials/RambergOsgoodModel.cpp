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
#include <Materials/RambergOsgoodModel.h>

#include <Units/Convert.h>
#include <Units/Measure.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

RambergOsgoodModel::RambergOsgoodModel(const std::_tstring& strName) :
   StressStrainModel(strName)
{
}

void RambergOsgoodModel::SetModelParameters(Float64 A, Float64 B, Float64 C, Float64 Eps, Float64 fpu, Float64 minStrain, Float64 maxStrain)
{
   m_A = A;
   m_B = B;
   m_C = C;
   m_Eps = Eps;
   m_fpu = fpu;
   m_MinStrain = minStrain;
   m_MaxStrain = maxStrain;
}

void RambergOsgoodModel::GetModelParameters(Float64* pA, Float64* pB, Float64* pC, Float64* pEps, Float64* pfpu, Float64* pminStrain, Float64* pmaxStrain) const
{
   *pA = m_A;
   *pB = m_B;
   *pC = m_C;
   *pEps = m_Eps;
   *pfpu = m_fpu;
   *pminStrain = m_MinStrain;
   *pmaxStrain = m_MaxStrain;
}

std::unique_ptr<StressStrainModel> RambergOsgoodModel::Clone() const
{
   return std::make_unique<RambergOsgoodModel>(*this);
}

Float64 RambergOsgoodModel::GetYieldStrain() const
{
   return 0.9*m_fpu/m_Eps;
}

Float64 RambergOsgoodModel::GetModulusOfElasticity() const
{
   return m_Eps;
}

std::pair<Float64, bool> RambergOsgoodModel::ComputeStress(Float64 strain) const
{
   Float64 sign = BinarySign(strain);
   strain = fabs(strain);

   Float64 D = 1 + pow(m_B * strain, m_C);
   Float64 fps = Min(m_Eps * strain * (m_A + (1 - m_A) / pow(D, 1.0 / m_C)), m_fpu);

   Float64 stress = sign * fps;

   // this is a model for rebar and strand that is usually in tension and embedded in concrete. 
   // the return value assumes the material is infinite strain capacity in compression
   return std::make_pair(stress,::IsLT(m_MaxStrain, sign * strain) ? false : true);
}

void RambergOsgoodModel::GetStrainLimits(Float64* pMinStrain, Float64* pMaxStrain) const
{
   PRECONDITION(pMinStrain != nullptr);
   PRECONDITION(pMaxStrain != nullptr);

   *pMinStrain = -0.003;
   *pMaxStrain = 0.005;
}

Float64 RambergOsgoodModel::GetStrainAtPeakStress() const
{
   return -0.003;
}


#if defined _DEBUG
bool RambergOsgoodModel::AssertValid() const
{
   return true;
}

void RambergOsgoodModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for RambergOsgoodModel")         << WBFL::Debug::endl;
   os << _T("====================")         << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool RambergOsgoodModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("RambergOsgoodModel");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for RambergOsgoodModel");
   TESTME_EPILOG("RambergOsgoodModel");
}
#endif // _UNITTEST

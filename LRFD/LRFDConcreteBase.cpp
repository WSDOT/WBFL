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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\LRFDConcreteBase.h>

using namespace WBFL::LRFD;

LRFDConcreteBase::LRFDConcreteBase(LPCTSTR name) :
   WBFL::Materials::ConcreteBase(name)
{
}

void LRFDConcreteBase::SetEcCorrectionFactors(Float64 K1,Float64 K2)
{
   m_EcK1 = K1;
   m_EcK2 = K2;
}

void LRFDConcreteBase::GetEcCorrectionFactors(Float64* pK1,Float64* pK2) const
{
   *pK1 = m_EcK1;
   *pK2 = m_EcK2;
}

void LRFDConcreteBase::SetCreepCorrectionFactors(Float64 K1,Float64 K2)
{
   m_CreepK1 = K1;
   m_CreepK2 = K2;
}

void LRFDConcreteBase::GetCreepCorrectionFactors(Float64* pK1,Float64* pK2) const
{
   *pK1 = m_CreepK1;
   *pK2 = m_CreepK2;
}

void LRFDConcreteBase::SetShrinkageCorrectionFactors(Float64 K1,Float64 K2)
{
   m_ShrinkageK1 = K1;
   m_ShrinkageK2 = K2;
}

void LRFDConcreteBase::GetShrinkageCorrectionFactors(Float64* pK1,Float64* pK2) const
{
   *pK1 = m_ShrinkageK1;
   *pK2 = m_ShrinkageK2;
}

void LRFDConcreteBase::SetLambda(Float64 lambda)
{
   m_Lambda = lambda;
}

Float64 LRFDConcreteBase::GetLambda() const
{
   return m_Lambda;
}

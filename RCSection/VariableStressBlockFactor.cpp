///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
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

#include <RCSection\RCSectionLib.h>
#include <RCSection\VariableStressBlockFactor.h>
#include <MathEx.h>

using namespace WBFL::RCSection;

VariableStressBlockFactor::VariableStressBlockFactor(Float64 alpha1, Float64 fc1, Float64 alpha2, Float64 fc2,Float64 beta1) : 
   StressBlockFactor() 
{ 
   SetStressBlockParameters(alpha1, fc1, alpha2, fc2, beta1); 
}

void VariableStressBlockFactor::SetStressBlockParameters(Float64 alpha1, Float64 fc1, Float64 alpha2, Float64 fc2, Float64 beta1)
{
   m_Alpha1 = alpha1;
   m_Fc1 = fc1;
   m_Alpha2 = alpha2;
   m_Fc2 = fc2;
   m_Beta1 = beta1;
}

void VariableStressBlockFactor::GetStressBlockParameters(Float64& alpha1, Float64& fc1, Float64& alpha2, Float64& fc2,Float64& beta1) const
{
   alpha1 = m_Alpha1;
   fc1 = m_Fc1;
   alpha2 = m_Alpha2;
   fc2 = m_Fc2;
   beta1 = m_Beta1;
}

void VariableStressBlockFactor::SetFc(Float64 fc)
{
   m_Fc = fc;
}

Float64 VariableStressBlockFactor::GetFc() const
{
   return m_Fc;
}

Float64 VariableStressBlockFactor::GetIntensityFactor() const
{
   Float64 alpha = ::LinInterp(m_Fc - m_Fc1, m_Alpha1, m_Alpha2, m_Fc2 - m_Fc1);
   return ::ForceIntoRange(Min(m_Alpha1,m_Alpha2), alpha, Max(m_Alpha1, m_Alpha2));
}

Float64 VariableStressBlockFactor::GetDepthFactor() const
{
   return m_Beta1;
}

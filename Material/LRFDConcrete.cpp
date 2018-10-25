///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2014  Washington State Department of Transportation
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

#include <Material\MatLib.h>
#include <Material\LRFDConcrete.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

matLRFDConcrete::matLRFDConcrete(LPCTSTR name) :
matConcreteBase(name),
m_StepTime(0)
{
}

matLRFDConcrete::matLRFDConcrete(const matLRFDConcrete& rOther) :
matConcreteBase(rOther),
m_StepTime(rOther.m_StepTime),
m_InitialConcrete(rOther.m_InitialConcrete),
m_FinalConcrete(rOther.m_FinalConcrete)
{
}

matLRFDConcrete::~matLRFDConcrete()
{
}

void matLRFDConcrete::SetConcreteModels(const matConcreteEx& initial,const matConcreteEx& final)
{
   m_InitialConcrete = initial;
   m_FinalConcrete   = final;

   SetType((matConcreteBase::Type)m_FinalConcrete.GetType());
   SetStrengthDensity(m_FinalConcrete.GetDensity());
   SetWeightDensity(m_FinalConcrete.GetDensityForWeight());
   HasAggSplittingStrength(m_FinalConcrete.HasAggSplittingStrength());
   SetAggSplittingStrength(m_FinalConcrete.GetAggSplittingStrength());
   SetMaxAggregateSize(m_FinalConcrete.GetMaxAggregateSize());
}

const matConcreteEx& matLRFDConcrete::GetInitialConcreteModel() const
{
   return m_InitialConcrete;
}

const matConcreteEx& matLRFDConcrete::GetFinalConcreteModel() const
{
   return m_FinalConcrete;
}

void matLRFDConcrete::SetStepTime(Float64 t)
{
   m_StepTime = t;
}

Float64 matLRFDConcrete::GetStepTime() const
{
   return m_StepTime;
}

Float64 matLRFDConcrete::GetFc(Float64 t) const
{
   if ( t < m_StepTime )
      return m_InitialConcrete.GetFc();
   else
      return m_FinalConcrete.GetFc();
}

Float64 matLRFDConcrete::GetEc(Float64 t) const
{
   if ( t < m_StepTime )
      return m_InitialConcrete.GetE();
   else
      return m_FinalConcrete.GetE();
}

Float64 matLRFDConcrete::GetShearFr(Float64 t) const
{
   if ( t < m_StepTime )
      return m_InitialConcrete.GetShearFr();
   else
      return m_FinalConcrete.GetShearFr();
}

Float64 matLRFDConcrete::GetFlexureFr(Float64 t) const
{
   if ( t < m_StepTime )
      return m_InitialConcrete.GetFlexureFr();
   else
      return m_FinalConcrete.GetFlexureFr();
}

Float64 matLRFDConcrete::GetFreeShrinkageStrain(Float64 t) const
{
   //Validate();
#pragma Reminder("UPDATE: Implement this")

   // be careful with time... we want to use the time
   // since curing stopped
   return 0;
}

Float64 matLRFDConcrete::GetCreepCoefficient(Float64 t,Float64 tla) const
{
   //Validate();
#pragma Reminder("UPDATE: Implement this")

   // be careful with time... we want to use the time
   // since curing stopped
   return 0;
}

matConcreteBase* matLRFDConcrete::CreateClone() const
{
   return new matLRFDConcrete(*this);
}

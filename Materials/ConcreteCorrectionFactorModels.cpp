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
#include <Materials/ConcreteCorrectionFactorModels.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

VSRatioCorrectionFactorModel::VSRatioCorrectionFactorModel(Float64 vsRatio) : m_VSRatio(vsRatio)
{
}

void VSRatioCorrectionFactorModel::SetVSRatio(Float64 vs)
{
   m_VSRatio = vs;
}

Float64 VSRatioCorrectionFactorModel::GetVSRatio() const
{
   return m_VSRatio;
}

#if defined _DEBUG
bool VSRatioCorrectionFactorModel::AssertValid() const
{
   return true;
}

void VSRatioCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
}

#endif // _DEBUG

#if defined _UNITTEST
bool VSRatioCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("VSRatioCorrectionFactorModel");

   TESTME_EPILOG("VSRatioCorrectionFactorModel"); }
#endif // _UNITTEST

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

HumidityCorrectionFactorModel::HumidityCorrectionFactorModel(Float64 h) :
   m_H(h)
{
   ASSERTVALID;
}

void HumidityCorrectionFactorModel::SetH(Float64 h)
{
   m_H = h;
   ASSERTVALID;
}

Float64 HumidityCorrectionFactorModel::GetH() const
{
   return m_H;
}

#if defined _DEBUG
bool HumidityCorrectionFactorModel::AssertValid() const
{
   return (0 <= m_H && m_H <= 100.0);
}

void HumidityCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
}

#endif // _DEBUG

#if defined _UNITTEST
bool HumidityCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("HumidityCorrectionFactorModel");
   TESTME_EPILOG("HumidityCorrectionFactorModel");
}
#endif // _UNITTEST

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ConcreteStrengthCorrectionFactorModel::ConcreteStrengthCorrectionFactorModel(Float64 fci) :
   m_fci(fci)
{
}

void ConcreteStrengthCorrectionFactorModel::SetFci(Float64 fci)
{
   m_fci = fci;
}

Float64 ConcreteStrengthCorrectionFactorModel::GetFci() const
{
   return m_fci;
}

#if defined _DEBUG
bool ConcreteStrengthCorrectionFactorModel::AssertValid() const
{
   return true;
}

void ConcreteStrengthCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
}

#endif // _DEBUG

#if defined _UNITTEST
bool ConcreteStrengthCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConcreteStrengthCorrectionFactorModel");

   TESTME_EPILOG("ConcreteStrengthCorrectionFactorModel");
}
#endif // _UNITTEST


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
#pragma Reminder("WORKING HERE - Materials - ConcreteStrengthCorrectionFactorModel and ConcreteTimeDevelopmentCorrectionFactorModel have independent values of fci - can they be shared?")
// can we reference a concrete strength model and age at initial loading instead of a static f'ci value? That would time the correction factors to the actual concrete model and
// the correction factor f'ci wouldn't need to be updated if the base concrete model changed.
ConcreteTimeDevelopmentCorrectionFactorModel::ConcreteTimeDevelopmentCorrectionFactorModel(Float64 fci) :
   m_fci(fci)
{
}

void ConcreteTimeDevelopmentCorrectionFactorModel::SetFci(Float64 fci)
{
   m_fci = fci;
}

Float64 ConcreteTimeDevelopmentCorrectionFactorModel::GetFci() const
{
   return m_fci;
}


#if defined _DEBUG
bool ConcreteTimeDevelopmentCorrectionFactorModel::AssertValid() const
{
   return true;
}

void ConcreteTimeDevelopmentCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
}

#endif // _DEBUG

#if defined _UNITTEST
bool ConcreteTimeDevelopmentCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConcreteTimeDevelopmentCorrectionFactorModel");

   TESTME_EPILOG("ConcreteTimeDevelopmentCorrectionFactorModel");
}
#endif // _UNITTEST

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
#if defined _DEBUG
bool ConcreteLoadingAgeCorrectionFactorModel::AssertValid() const
{
   return true;
}

void ConcreteLoadingAgeCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
}
#endif // _DEBUG

#if defined _UNITTEST
bool ConcreteLoadingAgeCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConcreteLoadingAgeCorrectionFactorModel");
   TESTME_EPILOG("ConcreteLoadingAgeCorrectionFactorModel");
}
#endif // _UNITTEST

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ConcretePhysicalTestingCorrectionFactorModel::ConcretePhysicalTestingCorrectionFactorModel(Float64 k) : 
   m_K(k)
{
}

void ConcretePhysicalTestingCorrectionFactorModel::SetK(Float64 k)
{
   m_K = k;
}

Float64 ConcretePhysicalTestingCorrectionFactorModel::GetK() const
{
   return m_K;
}

Float64 ConcretePhysicalTestingCorrectionFactorModel::GetCorrectionFactor() const
{
   return m_K;
}

#if defined _DEBUG
bool ConcretePhysicalTestingCorrectionFactorModel::AssertValid() const
{
   return true;
}

void ConcretePhysicalTestingCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
}
#endif // _DEBUG

#if defined _UNITTEST
#include <MathEx.h>
bool ConcretePhysicalTestingCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConcretePhysicalTestingCorrectionFactorModel");
   ConcretePhysicalTestingCorrectionFactorModel model;
   model.SetK(0.41);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.41));
   TESTME_EPILOG("ConcretePhysicalTestingCorrectionFactorModel"); 
}
#endif // _UNITTEST

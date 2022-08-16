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
#include <Materials/PSPowerFormulaModel.h>

#include <Units/Convert.h>
#include <Units/Measure.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

PSPowerFormulaModel::PSPowerFormulaModel(const std::_tstring& strName) :
   StressStrainModel(strName)
{
}

void PSPowerFormulaModel::SetStrandGrade(StrandGrade grade)
{
   m_Grade = grade;
   switch (m_Grade)
   {
   case StrandGrade::Grade250: m_fpu = 250; break;
   case StrandGrade::Grade270: m_fpu = 270; break;
   case StrandGrade::Grade300: m_fpu = 300; break;
   default: ASSERT(false); // is there a new grade?
   }
}

StrandGrade PSPowerFormulaModel::GetStrandGrade() const
{
   return m_Grade;
}

void PSPowerFormulaModel::SetStrandType(StrandType type)
{
   m_Type = type;
}

StrandType PSPowerFormulaModel::GetStrandType() const
{
   return m_Type;
}

void PSPowerFormulaModel::SetScalingFactor(Float64 k)
{
   PRECONDITION(0 <= k);
   m_K = k;
}

Float64 PSPowerFormulaModel::GetScalingFactor() const
{
   return m_K;
}

void PSPowerFormulaModel::SetStrainLimits(Float64 minStrain, Float64 maxStrain)
{
   m_MinStrain = minStrain;
   m_MaxStrain = maxStrain;
}

std::unique_ptr<StressStrainModel> PSPowerFormulaModel::Clone() const
{
   return std::make_unique<PSPowerFormulaModel>(*this);
}

Float64 PSPowerFormulaModel::GetYieldStrain() const
{
   return 0.9*m_fpu/m_Eps;
}

Float64 PSPowerFormulaModel::GetModulusOfElasticity() const
{
   return WBFL::Units::ConvertToSysUnits(m_Eps, WBFL::Units::Measure::KSI);
}

std::pair<Float64, bool> PSPowerFormulaModel::ComputeStress(Float64 strain) const
{
   Float64 sign = BinarySign(strain);
   strain = fabs(strain);

   Float64 fps;

   if (m_Grade == StrandGrade::Grade250)
   {
      // Grade 250
      if (m_Type == StrandType::LowRelaxation)
      {
         // from PCI Bridge Design Manual
         if (strain < 0.0076)
            fps = strain * m_Eps;
         else
            fps = 250 - 0.04 / (strain - 0.00640239520958);

         if (250.0 < fps)
            fps = 250.0;
      }
      else
      {
         ASSERT(m_Type == StrandType::StressRelieved);
         // ################ NOTE ############
         // This is the formula for low relaxation strands
         // since I don't have one for stress relieved this is going to have to do for now

         // from PCI Bridge Design Manual
         if (strain < 0.0076)
            fps = strain * m_Eps;
         else
            fps = 250 - 0.04 / (strain - 0.00640239520958);

         if (250.0 < fps)
            fps = 250.0;
      }
   }
   else if (m_Grade == StrandGrade::Grade270)
   {
      if (m_Type == StrandType::LowRelaxation)
      {
         // from PCI Bridge Design Manual
         fps = strain * (887. + 27613. / pow((1 + pow(112.4 * strain, 7.36)), 1. / 7.36));

         if (270.0 < fps)
            fps = 270.0;
      }
      else
      {
         ASSERT(m_Type == StrandType::StressRelieved);
         // from Collins and Mitchell text book
         fps = strain * (885. + 27645. / pow((1 + pow(118 * strain, 6)), 1. / 6));

         if (270.0 < fps)
            fps = 270.0;
      }
   }
   else if (m_Grade == StrandGrade::Grade300)
   {
      if (m_Type == StrandType::LowRelaxation)
      {
         // An "official" published set of power formula coefficients haven't been found as of yet.
         // The coefficients used here are taken from "Bond and Material Properties of Grade 270 and Grade 300 Prestressing Strands", Bryan J. Loflin, Masters Thesis, Virginia Polytecnic Institute and State University, June 2008
         // The values for A, B, C, and D are averaged from the reported Grade 300 values from Table 4.19 on page 79 of the report
         fps = strain * (263. + 33811. / pow((1 + pow(120.4 * strain, 5.347)), 1. / 5.347));

         if (300.0 < fps)
            fps = 300.0;
      }
      else
      {
         ASSERT(m_Type == StrandType::StressRelieved);
         // There isn't an "Official" stress relieved power formula for grade 300 (probably never will be)
         // Use the low relaxation version of the formula here - see above
         fps = strain * (263. + 33811. / pow((1 + pow(120.4 * strain, 5.347)), 1. / 5.347));

         if (300.0 < fps)
            fps = 300.0;
      }
   }
   else
   {
      ATLASSERT(false); // is there a new type
   }

   // The stress is in KSI, convert it to base units because that is what the caller expects
   fps = WBFL::Units::ConvertToSysUnits(fps, WBFL::Units::Measure::KSI);

   Float64 stress = m_K * sign * fps;

   // this is a model for rebar and strand that is usually in tension and embedded in concrete. 
   // the return value assumes the material is infinite strain capacity in compression
   return std::make_pair(stress,::IsLT(m_MaxStrain, sign * strain) ? false : true);
}

void PSPowerFormulaModel::GetStrainLimits(Float64* pMinStrain, Float64* pMaxStrain) const
{
   PRECONDITION(pMinStrain != nullptr);
   PRECONDITION(pMaxStrain != nullptr);

   *pMinStrain = m_MinStrain;
   *pMaxStrain = m_MaxStrain;
}

Float64 PSPowerFormulaModel::GetStrainAtPeakStress() const
{
   return m_MaxStrain;
}


#if defined _DEBUG
bool PSPowerFormulaModel::AssertValid() const
{
   return true;
}

void PSPowerFormulaModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for PSPowerFormulaModel")         << WBFL::Debug::endl;
   os << _T("====================")         << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool PSPowerFormulaModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PSPowerFormulaModel");

   PSPowerFormulaModel model;

   auto result = model.ComputeStress(0.00764);
   TRY_TESTME(IsEqual(result.first, 1446556950.5987, 0.0001) && result.second == true);

   result = model.ComputeStress(-0.00764);
   TRY_TESTME(IsEqual(result.first, -1446556950.5987, 0.0001) && result.second == true);

   result = model.ComputeStress(0.1);
   TRY_TESTME(IsEqual(result.first, 1861584469.1559, 0.0001) && result.second == false); // exceeds tension strain

   result = model.ComputeStress(-0.1);
   TRY_TESTME(IsEqual(result.first, -1861584469.1559, 0.0001) && result.second == true); // assumes compression strain is infinite

   result = model.ComputeStress(0.035);
   TRY_TESTME(IsEqual(result.first, 1861584469.1559, 0.0001) && result.second == true);

   TESTME_EPILOG("PSPowerFormulaModel");
}
#endif // _UNITTEST

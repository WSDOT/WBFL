///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
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

#include <RCSection\RCSectionLib.h>
#include <RCSection\AxialInteractionCurveSolver.h>
#include "AxialInteractionCurveSolverImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::RCSection;

AxialInteractionCurveSolver::AxialInteractionCurveSolver()
{
   m_pImpl = std::make_unique<AxialInteractionCurveSolverImpl>();
}

AxialInteractionCurveSolver::~AxialInteractionCurveSolver() = default;

void AxialInteractionCurveSolver::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_pImpl->SetSection(section);
}

const std::shared_ptr<const IGeneralSection>& AxialInteractionCurveSolver::GetSection() const
{
   return m_pImpl->GetSection();
}

void AxialInteractionCurveSolver::SetSlices(IndexType nSlices)
{
   m_pImpl->SetSlices(nSlices);
}

IndexType AxialInteractionCurveSolver::GetSlices() const
{
   return m_pImpl->GetSlices();
}

void AxialInteractionCurveSolver::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_pImpl->SetSliceGrowthFactor(sliceGrowthFactor);
}

Float64 AxialInteractionCurveSolver::GetSliceGrowthFactor() const
{
   return m_pImpl->GetSliceGrowthFactor();
}

void AxialInteractionCurveSolver::SetTolerance(Float64 tolerance)
{
   m_pImpl->SetTolerance(tolerance);
}

Float64 AxialInteractionCurveSolver::GetTolerance() const
{
   return m_pImpl->GetTolerance();
}

void AxialInteractionCurveSolver::SetMaxIterations(IndexType maxIter)
{
   m_pImpl->SetMaxIterations(maxIter);
}

IndexType AxialInteractionCurveSolver::GetMaxIterations() const
{
   return m_pImpl->GetMaxIterations();
}

void AxialInteractionCurveSolver::GetCompressionLimit(Float64* Fz, Float64* Mx, Float64* My, Float64* eo) const
{
   return m_pImpl->GetCompressionLimit(Fz, Mx, My, eo);
}

void AxialInteractionCurveSolver::GetTensionLimit(Float64* Fz, Float64* Mx, Float64* My, Float64* eo) const
{
   return m_pImpl->GetTensionLimit(Fz, Mx, My, eo);
}

std::unique_ptr<InteractionCurveSolution> AxialInteractionCurveSolver::Solve(Float64 na, IndexType nFzSteps) const
{
   return m_pImpl->Solve(na, nFzSteps);
}

#if defined _UNITTEST
#include <Units/Units.h>
#include <Materials/Materials.h>
#include <GeomModel/GeomModel.h>
#include <RCSection/SectionBuilder.h>
bool AxialInteractionCurveSolver::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("AxialInteractionCurveSolver");

   // This example is from "Reinforced Concrete Design", 4th Edition, Salmon & Wang
   // Example 13.21.3
   // See interaction diagram soluion in Figure 13.21.14. Note that the examples X-Y is different than our X-Y
   // See scanned image in Supporting Documents folder

   // base units of kip and ksi
   WBFL::Units::AutoSystem au;
   WBFL::Units::System::SetBaseUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

   //
   // materials
   //

   // concrete
   std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0));

   // rebar
   std::shared_ptr<WBFL::Materials::RebarModel> rebar(std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11));

   //
   // shapes
   //
   // note that this provides a uniform layout of the reinforcing and the bars are slightly non-uniform in the example
   // expect results to differ slightly. also, these calculations use strain compatibility where the textbook uses equivalent stress block
   auto section = SectionBuilder::RectangularColumn(12, 18, 2.38, 4, 4, 0.79, concrete, rebar, true);

   AxialInteractionCurveSolver solver;
   solver.SetSection(section);

   auto solution = solver.Solve(0, 10); // bending about the horizontal axis

   static std::pair<Float64,Float64> datumX[] = {
      {1.13686837722e-13, -1234.77091299},
      {1043.53268257, -1034.37414231},
      {1629.26545653, -833.977378708},
      {2018.63677268, -633.580608661},
      {2249.57107982, -433.183840551},
      {2390.45874049, -232.787510104},
      {2137.11418465, -32.3903043431},
      {1617.90963108, 168.00646378},
      {884.947646707, 368.396579037},
      {8.03887338846e-14, 568.8}
   };

   auto nPoints = solution->GetSolutionPointCount();
   for (IndexType i = 0; i < nPoints; i++)
   {
      const auto& moment_capacity = solution->GetSolutionPoint(i);
      Float64 P = moment_capacity->GetFz();
      Float64 Mx = moment_capacity->GetMx();
      Float64 My = moment_capacity->GetMy();
      Float64 M = sqrt(Mx * Mx + My * My);
      //std::cout.precision(12);
      //std::cout << "{" << M << ", " << P << "}," << std::endl;
      TRY_TESTME(IsZero(My));
      TRY_TESTME(IsEqual(M, datumX[i].first));
      TRY_TESTME(IsEqual(P, datumX[i].second));
   }

   //std::cout << std::endl;

   solution = solver.Solve(PI_OVER_2, 10); // bending about the vertical axis
   static std::pair<Float64, Float64> datumY[] = {
      {1.13686837722e-13, -1234.77091299},
      {1759.54451017, -1034.37412901},
      {2729.72109723, -833.977376772},
      {3434.15161537, -633.580608661},
      {3999.97588195, -433.183840551},
      {4222.95399784, -232.789569773},
      {3705.08351015, -32.3909236928},
      {2768.37604035, 168.005577926},
      {1437.35997376, 368.393811996},
      {8.03887338846e-14, 568.8}
   };

   nPoints = solution->GetSolutionPointCount();
   for (IndexType i = 0; i < nPoints; i++)
   {
      const auto& moment_capacity = solution->GetSolutionPoint(i);
      Float64 P = moment_capacity->GetFz();
      Float64 Mx = moment_capacity->GetMx();
      Float64 My = moment_capacity->GetMy();
      Float64 M = sqrt(Mx * Mx + My * My);
      //std::cout.precision(12);
      //std::cout << "{" << M << ", " << P << "}," << std::endl;
      TRY_TESTME(IsZero(Mx));
      TRY_TESTME(IsEqual(M, datumY[i].first));
      TRY_TESTME(IsEqual(P, datumY[i].second));
   }

   TESTME_EPILOG("AxialInteractionCurveSolver");
}

#endif // _UNITTEST

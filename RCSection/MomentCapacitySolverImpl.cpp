///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
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

#include <RCSection/RCSectionLib.h>
#include "MomentCapacitySolverImpl.h"
#include <RCSection/XRCSection.h>
#include <GeomModel/GeomOp2d.h>

using namespace WBFL::RCSection;

void MomentCapacitySolverImpl::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_bUpdateLimits = true;
   m_GeneralSolver.SetSection(section);
}

const std::shared_ptr<const IGeneralSection>& MomentCapacitySolverImpl::GetSection() const
{
   return m_GeneralSolver.GetSection();
}

void MomentCapacitySolverImpl::SetSlices(IndexType nSlices)
{
   m_GeneralSolver.SetSlices(nSlices);
}

IndexType MomentCapacitySolverImpl::GetSlices() const
{
   return m_GeneralSolver.GetSlices();
}

void MomentCapacitySolverImpl::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_GeneralSolver.SetSliceGrowthFactor(sliceGrowthFactor);
}

Float64 MomentCapacitySolverImpl::GetSliceGrowthFactor() const
{
   return m_GeneralSolver.GetSliceGrowthFactor();
}

void MomentCapacitySolverImpl::SetTolerance(Float64 tolerance)
{
   m_AxialTolerance = tolerance;
}

Float64 MomentCapacitySolverImpl::GetTolerance() const
{
   return m_AxialTolerance;
}

void MomentCapacitySolverImpl::SetMaxIterations(IndexType maxIter)
{
   m_MaxIter = maxIter;
}

IndexType MomentCapacitySolverImpl::GetMaxIterations() const
{
   return m_MaxIter;
}

std::unique_ptr<MomentCapacitySolution> MomentCapacitySolverImpl::Solve(Float64 Fz, Float64 angle, Float64 k_or_ec, Float64 strainLocation, MomentCapacitySolver::SolutionMethod solutionMethod) const
{
   // initialize some parameters using during the solution
   m_bAnalysisPointUpdated = false;

   // Get the forces and strains that bound the solution

   // Get the maximum tension force and moments at the zero curvature case (pure tension case)
   const auto& tension_capacity_limit = GetTensionLimit();

   // Get the maximum compression force and moments at the zero curvature case (pure compression case)
   const auto& compression_capacity_limit = GetCompressionLimit();

   if ((IsZero(tension_capacity_limit.Fz) && IsZero(tension_capacity_limit.Mx) && IsZero(tension_capacity_limit.My)) || 
       (IsZero(compression_capacity_limit.Fz) && IsZero(compression_capacity_limit.Mx) && IsZero(compression_capacity_limit.My)))
   {
      // no tension or compression capacity so the capacity is zero
      return CreateMomentCapacitySolution();
   }

   if (IsEqual(Fz, compression_capacity_limit.Fz) || IsEqual(Fz, tension_capacity_limit.Fz))
   {
      // The axial force is equal to the tension or compression capacity so we have our solution

      // start with a zero capacity solution since it is initialized for the zero curvature case
      auto solution = CreateMomentCapacitySolution();
      const auto& incrementalStrainPlane = solution->GetIncrementalStrainPlane();

      UpdateAnalysisPoints(angle, solutionMethod, strainLocation);
      if (IsEqual(Fz, compression_capacity_limit.Fz))
      {
         solution->InitSolution(incrementalStrainPlane, m_ExtremeCompressionPoint, m_ExtremeTensionPoint, 0.0, std::move(std::make_unique<GeneralSectionSolution>(*m_CompressionSolution)));
      }
      else
      {
         solution->InitSolution(incrementalStrainPlane, m_ExtremeCompressionPoint, m_ExtremeTensionPoint, 0.0, std::move(std::make_unique<GeneralSectionSolution>(*m_TensionSolution)));
      }

      return solution;
   }

   return AnalyzeSection(Fz, angle, k_or_ec, solutionMethod, strainLocation);
}

WBFL::Geometry::Point2d MomentCapacitySolverImpl::GetPlasticCentroid() const
{
   const auto& compression_capacity_limit = GetCompressionLimit();

   Float64 x = -compression_capacity_limit.My / compression_capacity_limit.Fz;
   Float64 y =  compression_capacity_limit.Mx / compression_capacity_limit.Fz;

   x = IsZero(x) ? 0 : x;
   y = IsZero(y) ? 0 : y;

   return WBFL::Geometry::Point2d(x, y);
}

void MomentCapacitySolverImpl::UpdateLimits() const
{
   if (!m_bUpdateLimits)
   {
      return; // the limits are up to date
   }

   const auto& section = GetSection();

   Float64 compStrain = -Float64_Max;
   Float64 tensStrain = -Float64_Max;

   IndexType nShapes = section->GetShapeCount();
   for (IndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++)
   {
      const auto& material = section->GetForegroundMaterial(shapeIdx);

      if (material == nullptr)
      {
         continue; // shape is a void
      }

      auto [min_strain, max_strain] = material->GetStrainLimits();
      compStrain = Max(min_strain, compStrain);
      CHECK(compStrain <= 0);

      tensStrain = Max(max_strain, tensStrain);
      CHECK(0 <= tensStrain);
   }

   m_CompressionCapacityLimit.eo = compStrain;
   m_IncrementalStrainPlane.ThroughAltitude(compStrain);

   IndexType nSlices = GetSlices();
   m_GeneralSolver.SetSlices(1);

   m_CompressionSolution = m_GeneralSolver.Solve(m_IncrementalStrainPlane);
   
   //m_GeneralSolver.SetSlices(nSlices);

   m_CompressionCapacityLimit.Fz = m_CompressionSolution->GetFz();
   m_CompressionCapacityLimit.Mx = m_CompressionSolution->GetMx();
   m_CompressionCapacityLimit.My = m_CompressionSolution->GetMy();

   m_TensionCapacityLimit.eo = tensStrain;
   m_IncrementalStrainPlane.ThroughAltitude(tensStrain);

   //m_GeneralSolver.SetSlices(1);
   
   m_TensionSolution = m_GeneralSolver.Solve(m_IncrementalStrainPlane);
   
   m_GeneralSolver.SetSlices(nSlices);

   m_TensionCapacityLimit.Fz = m_TensionSolution->GetFz();
   m_TensionCapacityLimit.Mx = m_TensionSolution->GetMx();
   m_TensionCapacityLimit.My = m_TensionSolution->GetMy();

   m_bUpdateLimits = false;
}

const CapacityLimit& MomentCapacitySolverImpl::GetCompressionLimit() const
{
   UpdateLimits();
   return m_CompressionCapacityLimit;
}

const CapacityLimit& MomentCapacitySolverImpl::GetTensionLimit() const
{
   UpdateLimits();
   return m_TensionCapacityLimit;
}

void MomentCapacitySolverImpl::UpdateStrainPlane(Float64 angle, Float64 k_or_ec, Float64 strainLocation, MomentCapacitySolver::SolutionMethod solutionMethod, Float64 eo) const
{
   UpdateAnalysisPoints(angle, solutionMethod, strainLocation);

   if (solutionMethod == MomentCapacitySolver::SolutionMethod::FixedCurvature)
   {
      // curvature is fixed... move the strain plain up/down changing the strain at the extreme point
      Float64 k = k_or_ec;
      if (IsZero(k, 1e-6))
      {
         m_IncrementalStrainPlane.ThroughAltitude(eo);
      }
      else
      {
         // P1 and P2 are arbitrary points on the neutral axis where strain = 0.0
         Float64 d = 1000; // distance between P1 and P2.

         Float64 sin_angle = sin(angle);
         Float64 cos_angle = cos(angle);

         m_P1.Move(-eo * sin_angle / k - d * cos_angle,
            eo * cos_angle / k - d * sin_angle,
            0.0
         );

         m_P2.Move(-eo * sin_angle / k + d * cos_angle,
            eo * cos_angle / k + d * sin_angle,
            0.0
         );

         m_P3.Move(0, 0, eo);

         m_IncrementalStrainPlane.ThroughPoints(m_P1, m_P2, m_P3);
      }
   }
   else
   {
      // Curvature varies. 
      Float64 ec = k_or_ec;

#if defined _DEBUG
      if (solutionMethod == MomentCapacitySolver::SolutionMethod::FixedCompressionStrain)
      {
         CHECK(ec <= 0); // compression is negative
      }
      else if (solutionMethod == MomentCapacitySolver::SolutionMethod::FixedTensionStrain)
      {
         CHECK(0 <= ec); // tension is positive
      }
      else if (solutionMethod == MomentCapacitySolver::SolutionMethod::FixedStrain)
      {
      } // do nothing
      else
      {
         CHECK(false); // shouldn't get here
      }
#endif

      if (IsEqual(ec, eo))
      {
         m_IncrementalStrainPlane.ThroughAltitude(eo);
      }
      else
      {
         UpdateControlPoints(angle, solutionMethod, strainLocation);

         Float64 d = 1000; // distance between P1 and P2.
         Float64 sin_angle = sin(angle);
         Float64 cos_angle = cos(angle);
         if (solutionMethod == MomentCapacitySolver::SolutionMethod::FixedStrain)
         {
            Float64 yna = ec / eo; // distance from where strain is known to the neutral axis
            m_P1.Move(-yna * sin_angle - d * cos_angle, strainLocation + yna * cos_angle - d * sin_angle, 0.0);
            m_P2.Move(-yna * sin_angle + d * cos_angle, strainLocation + yna * cos_angle + d * sin_angle, 0.0);
         }
         else
         {
            auto [X,Y] = m_ControlPoint.GetLocation();
            m_P1.Move(X - d * cos_angle, Y - d * sin_angle, eo);
            m_P2.Move(X + d * cos_angle, Y + d * sin_angle, eo);
         }

         m_P3.Move(m_FixedPoint, ec);

         // The strain plain is defined by three points. One point is where the strain is fixed
         // The other two define a line of constant strain through the trial strain value
         m_IncrementalStrainPlane.ThroughPoints(m_P1, m_P2, m_P3);
      }
   }
}

void MomentCapacitySolverImpl::UpdateAnalysisPoints(Float64 angle, MomentCapacitySolver::SolutionMethod solutionMethod,Float64 strainLocation) const
{
   if (m_bAnalysisPointUpdated)
      return;

   const auto& section = GetSection();

   // create a line parallel to the neutral axis passing through (0,0)
   // The IShape::FurthestPoint method returns the furthest point of the shape on the right side of a line.
   // Compression is on the left side of the neutral axis. If the solutionMethod is smFixedCompressionStrain
   // then the line must be in the opposite direction of the neutral axis.
   WBFL::Geometry::Vector2d compression_line_direction, tension_line_direction;

   // for compression, add 180deg so the line is in the opposite direction of the neutral axis
   compression_line_direction.SetDirection(angle + M_PI);
   tension_line_direction.SetDirection(angle);

   WBFL::Geometry::Line2d compression_side_line, tension_side_line;

   WBFL::Geometry::Point2d origin(0,0);

   compression_side_line.SetExplicit(origin, compression_line_direction);
   tension_side_line.SetExplicit(origin, tension_line_direction);

   // Find the furthest distance from the right side of this line to the section.
   // This is the distance from the origin to the extreme tension or compression fiber, depending on the direction of the line.

   // Shape::FurthestPoint will return a value less than zero if the entire shape
   // is on the opposite side of the line than we are interested in.

   WBFL::Geometry::Point2d pntCompression, pntTension;
   Float64 dCompression = -Float64_Max;
   Float64 dTension = -Float64_Max;
   IndexType nShapes = section->GetShapeCount();
   for (IndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++)
   {
      const auto& shape = section->GetShape(shapeIdx);

      auto [pntC,dist_compression] = shape.GetFurthestPoint(compression_side_line, WBFL::Geometry::Line2d::Side::Right);
      auto [pntT,dist_tension] = shape.GetFurthestPoint(tension_side_line, WBFL::Geometry::Line2d::Side::Right);

      if (dCompression < dist_compression)
      {
         dCompression = dist_compression;
         pntCompression = pntC;
      }

      if (dTension < dist_tension)
      {
         dTension = dist_tension;
         pntTension = pntT;
      }
   }

   m_ExtremeCompressionPoint = pntCompression;
   m_ExtremeTensionPoint = pntTension;

   m_bAnalysisPointUpdated = true;
}

void MomentCapacitySolverImpl::UpdateControlPoints(Float64 angle, MomentCapacitySolver::SolutionMethod solutionMethod, Float64 strainLocation) const
{
   PRECONDITION(solutionMethod == MomentCapacitySolver::SolutionMethod::FixedCompressionStrain || solutionMethod == MomentCapacitySolver::SolutionMethod::FixedTensionStrain || solutionMethod == MomentCapacitySolver::SolutionMethod::FixedStrain);

   UpdateAnalysisPoints(angle, solutionMethod, strainLocation);

   switch (solutionMethod)
   {
   case MomentCapacitySolver::SolutionMethod::FixedCurvature:
      CHECK(false);
      break;

   case MomentCapacitySolver::SolutionMethod::FixedCompressionStrain:
      m_FixedPoint = m_ExtremeCompressionPoint;
      m_ControlPoint = m_ExtremeTensionPoint;
      break;

   case MomentCapacitySolver::SolutionMethod::FixedTensionStrain:
      m_FixedPoint = m_ExtremeTensionPoint;
      m_ControlPoint = m_ExtremeCompressionPoint;
      break;

   case MomentCapacitySolver::SolutionMethod::FixedStrain:
   {
      m_FixedPoint.Move(0, strainLocation);

      // fixed point is not guaranteed to be at pntCompression or pntTension
      // determine if pntCompression or pntTension should be the control point

      // create vectors from the fixed point to the tension and compression control points
      WBFL::Geometry::Vector2d vC(m_FixedPoint, m_ExtremeCompressionPoint);
      WBFL::Geometry::Vector2d vT(m_FixedPoint, m_ExtremeTensionPoint);

      // ... then get the direction of the vectors (in both directions)
      Float64 dirC1 = vC.GetDirection();
      vC.Reflect();
      Float64 dirC2 = vC.GetDirection();

      Float64 dirT1 = vT.GetDirection();
      vT.Reflect();
      Float64 dirT2 = vT.GetDirection();

      // ... if the direction of the vector between fixed point and the compression point are the same as the direction of the neutral axis (or in opposite directions)
      // the use the tension point, otherwise use the compression point. if the point with the same direction as the neutral axis is used, the strain plane
      // will be constructed from 3 co-linear points (bad)
      if (IsEqual(angle, dirC1) || IsEqual(angle, dirC2))
      {
         m_ControlPoint = m_ExtremeTensionPoint;
      }
      else
      {
         m_ControlPoint = m_ExtremeCompressionPoint;
      }
   }
   break;
   }
}

void MomentCapacitySolverImpl::GetNeutralAxisParameterRange(Float64 k_or_ec, Float64 strainLocation, MomentCapacitySolver::SolutionMethod solutionMethod, Float64 angle, Float64 Fz, Float64* peo_lower, Float64* peo_upper, Float64* pFz_lower, Float64* pFz_upper) const
{
   const auto& tension_capacity_limit = GetTensionLimit();
   const auto& compression_capacity_limit = GetCompressionLimit();

   auto FzMax = tension_capacity_limit.Fz;
   auto FzMin = compression_capacity_limit.Fz;

   *peo_upper = tension_capacity_limit.eo;
   *peo_lower = compression_capacity_limit.eo;

   if (!InRange(FzMin, Fz, FzMax))
   {
      THROW_RCSECTION(_T("Solution not found - neutral axis not bounded"));
   }

   Float64 eo_lower = (solutionMethod == MomentCapacitySolver::SolutionMethod::FixedCompressionStrain ? k_or_ec : *peo_lower);
   Float64 eo_upper = (solutionMethod == MomentCapacitySolver::SolutionMethod::FixedTensionStrain     ? k_or_ec : *peo_upper);

   Float64 Fz_lower = 0;
   Float64 Fz_upper = 0;

   // This method assumes increasing the difference between min and max will yield the desired range.
   // However, when the controlling strain is not at the extreme edges of the section the range can
   // grow infinitely. In these cases, the actual range is smaller than the initial guess.
   // Win the MaxStrain limit is reach, the initial guess is reduced by a factor of 100 (see code at end of this method)
   Float64 MaxStrain = 10.00; // this limit is established by trial and error - it may not be optimized.

   bool bReset = false; // reset state - if the solution isn't converging, reset the parameters and try again - this can only happen once
   bool bDone = false;
   while (!bDone)
   {
      UpdateStrainPlane(angle, k_or_ec, strainLocation, solutionMethod, eo_lower);

      m_GeneralSolution = std::move(m_GeneralSolver.Solve(m_IncrementalStrainPlane));

      Fz_lower = m_GeneralSolution->GetFz();
      auto Mx = m_GeneralSolution->GetMx();
      auto My = m_GeneralSolution->GetMy();

      Fz_lower -= Fz;

      UpdateStrainPlane(angle, k_or_ec, strainLocation, solutionMethod, eo_upper);
      m_GeneralSolution = std::move(m_GeneralSolver.Solve(m_IncrementalStrainPlane));

      Fz_upper = m_GeneralSolution->GetFz();
      Mx = m_GeneralSolution->GetMx();
      My = m_GeneralSolution->GetMy();

      Fz_upper -= Fz;

      if (Fz_lower * Fz_upper <= 0)
      {
         bDone = true;
      }
      else
      {
         eo_lower -= (eo_upper - eo_lower) / 2;
         eo_upper += (eo_upper - eo_lower) / 2;
      }

      if (solutionMethod == MomentCapacitySolver::SolutionMethod::FixedStrain && (eo_lower < -MaxStrain || MaxStrain < eo_upper))
      {
         if (!bReset)
         {
            bReset = true; // solution parameters are being reset, mark true because we only get to reset once
            // For fixed point analysis, the fixed point is typically somewhere within the depth of the section
            // and the control strain is at one of the extreme edges. The initial guess strains can be too
            // big and the solution is not bounded. The real bounding strains are on a smaller range
            // so retry bounding with smaller initial strains.
            eo_lower = *peo_lower / 100;
            eo_upper = *peo_upper / 100;
         }
         else
         {
            THROW_RCSECTION(_T("Solution not found - neutral axis not bounded"));
         }
      }
   }

   *peo_lower = eo_lower;
   *peo_upper = eo_upper;
   *pFz_lower = Fz_lower;
   *pFz_upper = Fz_upper;
}

std::unique_ptr<MomentCapacitySolution> MomentCapacitySolverImpl::AnalyzeSection(Float64 Fz, Float64 angle, Float64 k_or_ec, MomentCapacitySolver::SolutionMethod solutionMethod, Float64 strainLocation) const
{
   // solve with method of false position (aka regula falsi method)
   // http://en.wikipedia.org/wiki/False_position_method
   // http://mathworld.wolfram.com/MethodofFalsePosition.html

   Float64 Fz_lower, Fz_upper;
   Float64 eo_lower, eo_upper;
   GetNeutralAxisParameterRange(k_or_ec, strainLocation, solutionMethod, angle, Fz, &eo_lower, &eo_upper, &Fz_lower, &Fz_upper);

   CHECK(eo_lower < eo_upper);

   Float64 Mx, My;

   int side = 0;
   Float64 Fz_r = 0;
   Float64 eo_r = 0; // first guess is zero strain at the control point (we get better convergence this say)
   IndexType iter = 0;
   for (iter = 0; iter < m_MaxIter; iter++)
   {
      if (IsZero(Fz_r, m_AxialTolerance) && IsZero(Fz_lower, m_AxialTolerance) && IsZero(Fz_upper, m_AxialTolerance))
      {
         break; // converged
      }

      // update guess for strain at the control point
      eo_r = (Fz_upper * eo_lower - Fz_lower * eo_upper) / (Fz_upper - Fz_lower);

      UpdateStrainPlane(angle, k_or_ec, strainLocation, solutionMethod, eo_r);
      m_GeneralSolution = std::move(m_GeneralSolver.Solve(m_IncrementalStrainPlane));

      Fz_r = m_GeneralSolution->GetFz();
      Mx = m_GeneralSolution->GetMx();
      My = m_GeneralSolution->GetMy();

      Fz_r -= Fz;

      if (0 < Fz_r * Fz_upper)
      {
         eo_upper = eo_r;
         Fz_upper = Fz_r;
         if (side == -1)
         {
            Fz_lower /= 2;
         }

         side = -1;
      }
      else if (0 < Fz_lower * Fz_r)
      {
         eo_lower = eo_r;
         Fz_lower = Fz_r;
         if (side == 1)
         {
            Fz_upper /= 2;
         }

         side = 1;
      }
      else
      {
         break;
      }
   }

   CHECK(IsZero(m_GeneralSolution->GetCompressionResultant() + m_GeneralSolution->GetTensionResultant() - Fz, m_AxialTolerance));

   // Compute curvature
   const auto& section = GetSection();
   IndexType primaryShapeIdx = section->GetPrimaryShapeIndex();
   const auto& initial_strain_plane = section->GetInitialStrain(primaryShapeIdx);

   auto slices = m_GeneralSolution->FindSlices(primaryShapeIdx);
   const auto* pSlice1 = slices.front();
   const auto* pSlice2 = slices.back();
   Float64 dist = pSlice1->GetCentroid().Distance(pSlice2->GetCentroid());
   Float64 e1 = pSlice1->GetTotalStrain();
   Float64 e2 = pSlice2->GetTotalStrain();
   Float64 k = (e2 - e1) / dist;

#if defined _DEBUG
   if (solutionMethod == MomentCapacitySolver::SolutionMethod::FixedCurvature)
   {
      CHECK(IsEqual(k_or_ec, k));
   }
#endif

   auto solution = CreateMomentCapacitySolution();
   solution->InitSolution(m_IncrementalStrainPlane, m_ExtremeCompressionPoint, m_ExtremeTensionPoint, k, std::move(m_GeneralSolution));

   if (m_MaxIter <= iter)
   {
      THROW_RCSECTION(_T("Solution not found - did not converge before maximum number of iterations"));
   }

   return solution;
}

std::unique_ptr<MomentCapacitySolution> MomentCapacitySolverImpl::CreateMomentCapacitySolution() const
{
   return std::make_unique<MomentCapacitySolution>();
}

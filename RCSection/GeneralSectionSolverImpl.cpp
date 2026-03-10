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

#include <RCSection/RCSectionLib.h>
#include "GeneralSectionSolverImpl.h"
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/GeomOp2d.h>
#include <GeomModel/Primitives3d.h>

#if defined _DEBUG_LOGGING
#include <sstream>
#include <iomanip>
#include <Units\Units.h>

#define VALUE(_x_) (IsZero(_x_)  ? 0 : _x_)
#define LENGTH(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Inch))
#define AREA(_x_)   (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Inch2))
#define STRESS(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::KSI))
#define FORCE(_x_)  (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Kip))
#define MOMENT(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::KipFeet))
#endif // _DEBUG_LOGGING

using namespace WBFL::RCSection;

void GeneralSectionSolverImpl::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_Section = section;
   m_bDecomposed = false;
}

const std::shared_ptr<const IGeneralSection>& GeneralSectionSolverImpl::GetSection() const
{
   return m_Section;
}

void GeneralSectionSolverImpl::SetSlices(IndexType nSlices)
{
   if (m_nSlices != nSlices)
   {
      m_nSlices = nSlices;
      m_bDecomposed = false;
   }
}

IndexType GeneralSectionSolverImpl::GetSlices() const
{
   return m_nSlices;
}

void GeneralSectionSolverImpl::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   if (m_SliceGrowthFactor != sliceGrowthFactor)
   {
      m_SliceGrowthFactor = sliceGrowthFactor;
      m_bDecomposed = false;
   }
}

Float64 GeneralSectionSolverImpl::GetSliceGrowthFactor() const
{
   return m_SliceGrowthFactor;
}

#define COMPRESSION(_f_)  (_f_ < 0 ? 1 : 0)*(_f_)
#define TENSION(_f_)      (_f_ > 0 ? 1 : 0)*(_f_)

#define COMPRESSION_CG(_p_,_f_,_slice_) {auto[_Xcg,_Ycg] = _slice_.pntCG.GetLocation(); _p_.Offset( COMPRESSION(_f_)*_Xcg, COMPRESSION(_f_)*_Ycg ); }
#define TENSION_CG(_p_,_f_,_slice_)     {auto[_Xcg,_Ycg] = _slice_.pntCG.GetLocation(); _p_.Offset( TENSION(_f_)*_Xcg,     TENSION(_f_)*_Ycg ); }

std::unique_ptr<GeneralSectionSolution> GeneralSectionSolverImpl::Solve(const WBFL::Geometry::Plane3d& incrementalStrainPlane) const
{
   std::vector<std::unique_ptr<GeneralSectionSlice>> slices;

   DecomposeSection(incrementalStrainPlane);

   Float64 C = 0;
   Float64 T = 0;
   WBFL::Geometry::Point2d cgC;
   WBFL::Geometry::Point2d cgT;

   Float64 p = 0;
   Float64 mx = 0;
   Float64 my = 0;

   bool bExceededStrainLimits = false;

   // get distance from origin to neutral axis line
   auto [Yna,v] = m_NeutralAxis.GetImplicit();

#if defined _DEBUG_LOGGING
   WBFL::Debug::FileLogContext log(_T("GeneralSectionSolution.log"));
   auto& os = log.GetStream();
   os << _T("Neutral Axis Location: ") << LENGTH(Yna) << std::endl;
   Float64 _dir = v.GetDirection();
   os << "Neutral Axis Direction: " << VALUE((_dir - PI_OVER_2) * 180. / M_PI) << std::endl;
   os << std::setw(10) << "Area, " << std::setw(10) << "Side, " << std::setw(10) << "Top, " << std::setw(10) << "Bottom, " << std::setw(20) << "Xcg, " << std::setw(20) << "Ycg, " << std::setw(20) << "initial strain, " << std::setw(20) << "strain, " << std::setw(20) << "fg material, " << std::setw(10) << "fg stress, " << std::setw(20) << "bg material, " << std::setw(10) << "bg stress, " << std::setw(10) << "stress, " << std::setw(10) << "force" << std::endl;
#endif // _DEBUG_LOGGING

   for (const auto& slice : m_Slices)
   {
      Float64 P, Mx, My;
      Float64 fg_stress, bg_stress, stress, incremental_strain, total_strain;
      bool bExceededStrainLimitsThisSlice;
      if ((slice.Bottom < Yna) && (Yna < slice.Top))
      {
         // this slice spans the neutral axis... 
         // need to clip again 
         Float64 angle = GetNeutralAxisAngle();

         const auto& initial_strain = m_Section->GetInitialStrain(slice.ShapeIdx);
         SHAPEINFO shape_info(slice.ShapeIdx, slice.SliceShape, slice.FgMaterial, slice.BgMaterial, initial_strain, slice.Le);

         SLICEINFO top_slice;
         std::unique_ptr<GeneralSectionSlice> topSlice;
         bool bResult = SliceShape(shape_info, angle, slice.Top, Yna, top_slice);
         if (bResult)
         {
            AnalyzeSlice(top_slice, incrementalStrainPlane, P, Mx, My, fg_stress, bg_stress, stress, incremental_strain, total_strain, bExceededStrainLimitsThisSlice);

            C += COMPRESSION(P);
            T += TENSION(P);

            COMPRESSION_CG(cgC, P, top_slice);
            TENSION_CG(cgT, P, top_slice);

            p += P;
            mx += Mx;
            my -= My;

            bExceededStrainLimits |= bExceededStrainLimitsThisSlice;

            topSlice = std::make_unique<GeneralSectionSlice>(top_slice.ShapeIdx, std::move(top_slice.SliceShape), top_slice.Area, top_slice.pntCG, top_slice.ei, incremental_strain, total_strain, fg_stress, bg_stress, slice.FgMaterial, slice.BgMaterial, bExceededStrainLimitsThisSlice);

#if defined _DEBUG_LOGGING
            std::_tstring fgName(slice.FgMaterial ? slice.FgMaterial->GetName() : _T("-"));
            std::_tstring bgName(slice.BgMaterial ? slice.BgMaterial->GetName() : _T("-"));
            os << std::setw(10) << AREA(top_slice.Area) << ", " << std::setw(10) << "C, " << std::setw(10) << LENGTH(top_slice.Top) << ", " << std::setw(10) << LENGTH(top_slice.Bottom) << ", " << std::setw(20) << LENGTH(top_slice.pntCG.X()) << ", " << std::setw(20) << LENGTH(top_slice.pntCG.Y()) << ", " << std::setw(20) << top_slice.ei << ", " << std::setw(20) << total_strain << ", " << std::setw(20) << fgName << ", " << std::setw(10) << STRESS(fg_stress) << ", " << std::setw(20) << bgName << ", " << std::setw(10) << STRESS(bg_stress) << ", " << std::setw(10) << STRESS(stress) << ", " << std::setw(10) << FORCE(P) << std::endl;
#endif // _DEBUG_LOGGING
         }

         SLICEINFO bottom_slice;
         std::unique_ptr<GeneralSectionSlice> bottomSlice;
         bResult = SliceShape(shape_info, angle, Yna, slice.Bottom, bottom_slice);
         if (bResult)
         {
            AnalyzeSlice(bottom_slice, incrementalStrainPlane, P, Mx, My, fg_stress, bg_stress, stress, incremental_strain, total_strain, bExceededStrainLimitsThisSlice);

            C += COMPRESSION(P);
            T += TENSION(P);

            COMPRESSION_CG(cgC, P, bottom_slice);
            TENSION_CG(cgT, P, bottom_slice);

            p += P;
            mx += Mx;
            my -= My;

            bExceededStrainLimits |= bExceededStrainLimitsThisSlice;

            bottomSlice = std::make_unique<GeneralSectionSlice>(bottom_slice.ShapeIdx, std::move(bottom_slice.SliceShape), bottom_slice.Area, bottom_slice.pntCG, bottom_slice.ei, incremental_strain, total_strain, fg_stress, bg_stress, slice.FgMaterial, slice.BgMaterial, bExceededStrainLimitsThisSlice ? VARIANT_TRUE : VARIANT_FALSE);

#if defined _DEBUG_LOGGING
            std::_tstring fgName(slice.FgMaterial ? slice.FgMaterial->GetName() : _T("-"));
            std::_tstring bgName(slice.BgMaterial ? slice.BgMaterial->GetName() : _T("-"));
            os << std::setw(10) << AREA(bottom_slice.Area) << ", " << std::setw(10) << "T, " << std::setw(10) << LENGTH(bottom_slice.Top) << ", " << std::setw(10) << LENGTH(bottom_slice.Bottom) << ", " << std::setw(20) << LENGTH(bottom_slice.pntCG.X()) << ", " << std::setw(20) << LENGTH(bottom_slice.pntCG.Y()) << ", " << std::setw(20) << bottom_slice.ei << ", " << std::setw(20) << total_strain << ", " << std::setw(20) << fgName << ", " << std::setw(10) << STRESS(fg_stress) << ", " << std::setw(20) << bgName << ", " << std::setw(10) << STRESS(bg_stress) << ", " << std::setw(10) << STRESS(stress) << ", " << std::setw(10) << FORCE(P) << std::endl;
#endif // _DEBUG_LOGGING
         }

         if (PI_OVER_2 <= angle && angle < 3 * PI_OVER_2)
         {
            if (bottomSlice) slices.emplace_back(std::move(bottomSlice));
            if (topSlice) slices.emplace_back(std::move(topSlice));
         }
         else
         {
            if (topSlice) slices.emplace_back(std::move(topSlice));
            if (bottomSlice) slices.emplace_back(std::move(bottomSlice));
         }
      }
      else
      {
         AnalyzeSlice(slice, incrementalStrainPlane, P, Mx, My, fg_stress, bg_stress, stress, incremental_strain, total_strain, bExceededStrainLimitsThisSlice);

         C += COMPRESSION(P);
         T += TENSION(P);

         COMPRESSION_CG(cgC, P, slice);
         TENSION_CG(cgT, P, slice);

         p += P;
         mx += Mx;
         my -= My;

         bExceededStrainLimits |= bExceededStrainLimitsThisSlice;

         std::unique_ptr<GeneralSectionSlice> section_slice(std::make_unique<GeneralSectionSlice>(slice.ShapeIdx, std::move(slice.SliceShape), slice.Area, slice.pntCG, slice.ei, incremental_strain, total_strain, fg_stress, bg_stress, slice.FgMaterial, slice.BgMaterial, bExceededStrainLimitsThisSlice));
         slices.emplace_back(std::move(section_slice));

#if defined _DEBUG_LOGGING
         std::_tstring fgName(slice.FgMaterial ? slice.FgMaterial->GetName() : _T("-"));
         std::_tstring bgName(slice.BgMaterial ? slice.BgMaterial->GetName() : _T("-"));
         char cSide = (P < 0 ? 'C' : 'T');
         os << std::setw(10) << AREA(slice.Area) << ", " << std::setw(10) << cSide << ", " << std::setw(10) << LENGTH(slice.Top) << ", " << std::setw(10) << LENGTH(slice.Bottom) << ", " << std::setw(20) << LENGTH(slice.pntCG.X()) << ", " << std::setw(20) << LENGTH(slice.pntCG.Y()) << ", " << std::setw(20) << slice.ei << ", " << std::setw(20) << total_strain << ", " << std::setw(20) << fgName << ", " << std::setw(10) << STRESS(fg_stress) << ", " << std::setw(20) << bgName << ", " << std::setw(10) << STRESS(bg_stress) << ", " << std::setw(10) << STRESS(stress) << ", " << std::setw(10) << FORCE(P) << std::endl;
#endif // _DEBUG_LOGGING
      }
   }

   std::unique_ptr<GeneralSectionSolution> solution(std::make_unique<GeneralSectionSolution>());

   // locate centroid of resultant compression and tension forces
   // up to this point the cgC and cgT objects contain the sum of Force*CG
   if (IsZero(C)) cgC.Move(0, 0); else cgC /= C;
   if (IsZero(T)) cgT.Move(0, 0); else cgT /= T;

   solution->InitSolution(p, mx, my, m_NeutralAxis, cgC, C, cgT, T, std::move(slices), bExceededStrainLimits);

#if defined _DEBUG_LOGGING
   os << std::setw(10) << "Area, " << std::setw(10) << "Side, " << std::setw(10) << "Top, " << std::setw(10) << "Bottom, " << std::setw(20) << "Xcg, " << std::setw(20) << "Ycg, " << std::setw(20) << "initial strain, " << std::setw(20) << "strain, " << std::setw(20) << "fg material, " << std::setw(10) << "fg stress, " << std::setw(20) << "bg material, " << std::setw(10) << "bg stress, " << std::setw(10) << "stress, " << std::setw(10) << "force" << std::endl;
   os << std::endl;
   os << "P  = " << FORCE(p) << std::endl;
   os << "Mx = " << MOMENT(mx) << std::endl;
   os << "My = " << MOMENT(my) << std::endl;
#endif // _DEBUG_LOGGING

   return solution;
}

void GeneralSectionSolverImpl::DecomposeSection(const WBFL::Geometry::Plane3d& incrementalStrainPlane) const
{
   // NOTE: See Method of clipping the GeneralSection into analysis slices.docx in the Supporting Documents
   // folder for information about how this solver "slices" the section into slices parallel to a rotated
   // neutral axis

   // if neutral axis direction, determined from the strain plane, is different from the last time
   // we need to re-slice the section... slices must by parallel to the neutral axis
   if (m_bDecomposed && IsNeutralAxisParallel(incrementalStrainPlane))
   {
      UpdateNeutralAxis(incrementalStrainPlane, m_NeutralAxis); // update the neutral axis for the current strain plain
      return; // section is decomposed and NA direction hasn't changed... analysis is good to go
   }

   UpdateNeutralAxis(incrementalStrainPlane, m_NeutralAxis);

   // Get neutral axis angle
   Float64 angle = GetNeutralAxisAngle();

   // We are going to need a bounding box
   WBFL::Geometry::Rect2d bounding_box;

   // ... and something to hold the rotated shapes in
   std::vector<SHAPEINFO> shapes;

   // Rotate the shapes and determine the overall size of the section (bounding box)
   IndexType nShapes = m_Section->GetShapeCount();
   for (IndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++)
   {
      const auto& original_shape = m_Section->GetShape(shapeIdx);

      const auto& fgMaterial = m_Section->GetForegroundMaterial(shapeIdx);
      const auto& bgMaterial = m_Section->GetBackgroundMaterial(shapeIdx);

      const auto& initialStrain = m_Section->GetInitialStrain(shapeIdx);

      Float64 Le = m_Section->GetElongationLength(shapeIdx);

      // make a clone of the original shape so it can be altered
      auto shape = original_shape.CreateClone();

      // rotate the shape so that its primary axes are aligned with the neutral axis
      // we need to clip parallel to the neutral axis
      shape->Rotate(0, 0, -angle);

      auto bndbox = shape->GetBoundingBox();

      if (shapeIdx == 0)
      {
         bounding_box = bndbox;
      }
      else
      {
         bounding_box.Union(bndbox);
      }

      shapes.emplace_back(shapeIdx, std::move(shape), fgMaterial, bgMaterial, initialStrain, Le);
   }

   //
   // Determine slice parameters
   //
   Float64 top = bounding_box.Top();
   Float64 height = bounding_box.Height();

   // z = 0 + 1 + 2 + 3 + ... + (m_nSlices-1) = ( (m_nSlices-1)^2 + (m_nSlices-1) )/2
   // See http://www.math.com/tables/expansion/power.htm
   IndexType z = ((m_nSlices - 1) * (m_nSlices - 1) + (m_nSlices - 1)) / 2;

   // get the slice growth factor... if 0, then it wasn't set by the user
   // so set it to the number of slices so that all slices are of a uniform
   // height
   Float64 k;
   Float64 basic_slice_height;
   CHECK(0 < m_nSlices);
   if (m_nSlices == 1)
   {
      k = 0;
      basic_slice_height = height;
   }
   else
   {
      k = (m_SliceGrowthFactor - 1) / (m_nSlices - 1);
      basic_slice_height = height / (m_nSlices + k * z);
   }


   // Setup clipping box

   Float64 left = bounding_box.Left();
   Float64 right = bounding_box.Right();

   Float64 width = right - left;
   m_ClippingRect.Left() = left - width / 2;
   m_ClippingRect.Right() = right + width / 2;

   // Slice each shape
   m_Slices.clear();
   nShapes = shapes.size();
   for (IndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++)
   {
      // get shape and related information
      SHAPEINFO& shape_info = shapes[shapeIdx];

      // get the top and bottom of the shape... there is no reason to try to slice
      // if the slicer isn't passing through the shape
      auto shape_box = shape_info.Shape->GetBoundingBox();
      Float64 shape_top = shape_box.Top();
      Float64 shape_bottom = shape_box.Bottom();

      Float64 slice_top = top;

      for (IndexType sliceIdx = 0; sliceIdx < m_nSlices; sliceIdx++)
      {
         Float64 slice_height = (k * sliceIdx + 1) * basic_slice_height;
         Float64 slice_bottom = slice_top - slice_height;

         // expand the depth of the first and last slice just so nothing is missed
         if (sliceIdx == 0)
         {
            slice_top += slice_height / 2;
         }

         if (sliceIdx == m_nSlices - 1)
         {
            slice_bottom -= slice_height / 2;
         }

         SLICEINFO slice_info;
         bool bResult = SliceShape(shape_info, angle, slice_top, slice_bottom, slice_info);

         slice_top = slice_bottom; // top of next slice

         if (bResult == false)
         {
            continue; // go to next slice 
         }

         m_Slices.emplace_back(slice_info);

         // once the top of the slicer is below the shape... stop slicing
         if (slice_top < slice_bottom)
         {
            sliceIdx = m_nSlices;
         }
      }
   }

   // sort based on CG elevation
   std::sort(std::begin(m_Slices), std::end(m_Slices), [](auto& sliceA, auto& sliceB) {return sliceB.pntCG.Y() < sliceA.pntCG.Y();});
   m_bDecomposed = true;
}

bool GeneralSectionSolverImpl::IsNeutralAxisParallel(const WBFL::Geometry::Plane3d& incrementalStrainPlane) const
{
   UpdateNeutralAxis(incrementalStrainPlane, m_TestLine);
   return WBFL::Geometry::GeometricOperations::SameDirection(m_NeutralAxis, m_TestLine);
}

void GeneralSectionSolverImpl::UpdateNeutralAxis(const WBFL::Geometry::Plane3d& incrementalStrainPlane, WBFL::Geometry::Line2d& line) const
{
   // get the initial strain plane for the primary shape
   IndexType primaryShapeIdx = m_Section->GetPrimaryShapeIndex();
   const auto& initial_strain_plane = m_Section->GetInitialStrain(primaryShapeIdx);

   // get three points on the initial strain plane
   WBFL::Geometry::Point3d A1, A2, A3;
   Float64 X1 = -100;
   Float64 Y1 = 100;
   Float64 Z1 = 0;
   Float64 X2 = 100;
   Float64 Y2 = 100;
   Float64 Z2 = 0;
   Float64 X3 = -100;
   Float64 Y3 = -100;
   Float64 Z3 = 0;
   if (initial_strain_plane)
   {
      Z1 = initial_strain_plane->GetZ(X1, Y1);
      Z2 = initial_strain_plane->GetZ(X2, Y2);
      Z3 = initial_strain_plane->GetZ(X3, Y3);
   }
   A1.Move(X1, Y1, Z1);
   A2.Move(X2, Y2, Z2);
   A3.Move(X3, Y3, Z3);

   // get the incremental strain on these three points
   // and offset the initial strain by the increment strain
   Z1 = incrementalStrainPlane.GetZ(X1, Y1);
   A1.Offset(0, 0, Z1);
   Z2 = incrementalStrainPlane.GetZ(X2, Y2);
   A2.Offset(0, 0, Z2);
   Z3 = incrementalStrainPlane.GetZ(X3, Y3);
   A3.Offset(0, 0, Z3);

   // create a new plane... the total strain plane through these three points
   WBFL::Geometry::Plane3d total_strain_plane(A1, A2, A3);

   // find the line that passes through z = 0 (z is the strain axis)

   Float64 x1 = -1000;
   Float64 x2 = 1000;
   Float64 z = 0.00;
   Float64 y1, y2;

   bool by1 = true;
   try
   {
      y1 = total_strain_plane.GetY(x1, z);
   }
   catch (...)
   {
      by1 = false;
   }

   bool by2 = true;
   try
   {
      y2 = total_strain_plane.GetY(x2, z);
   }
   catch (...)
   {
      by2 = false;
   }

   bool bx1 = true;
   bool bx2 = true;

   if (by1 == false || by2 == false)
   {
      y1 = -1000;
      y2 = 1000;

      try
      {
         x1 = total_strain_plane.GetX(y1, z);
      }
      catch (...)
      {
         bx1 = false;
      }

      try
      {
         x2 = total_strain_plane.GetX(y2, z);
      }
      catch (...)
      {
         bx2 = false;
      }
   }

   if (bx1 == false || bx2 == false)
   {
      // the plane is parallel to the XY plane.... just pick some values... the direction
      // of the neutral axis doesn't matter
      x1 = -1000;
      y1 = -1000;

      x2 = 1000;
      y2 = -1000;
   }

   // create the neutral axis line with compression on the left side on the line
   WBFL::Geometry::Point2d p1, p2;

   p1.Move(x1, y1);
   p2.Move(x2, y2);
   line.ThroughPoints(p1, p2);

   // evaluate a point on the left side of the line
   auto [C,vN] = line.GetImplicit(); // vN, normal vector points to the left hand side of the line
   auto [dx,dy] = vN.GetDimensions();

   Float64 Offset = 10; // some offset from the line
   Float64 X = x1 + Offset * dx;
   Float64 Y = y1 + Offset * dy;
   Float64 Z;
   try
   {
      Z = total_strain_plane.GetZ(X, Y);
   }
   catch (...)
   {
      CHECK(false); // this exception is not expected
   }

   if (0 < Z)
   {
      // tension is on the left side, so reverse the direction the line
      // we want compression on the left side
      line.Reverse();
   }
}

void GeneralSectionSolverImpl::AnalyzeSlice(const SLICEINFO& slice, const WBFL::Geometry::Plane3d& incrementalStrainPlane, Float64& P, Float64& Mx, Float64& My, Float64& fg_stress, Float64& bg_stress, Float64& stress, Float64& incrementalStrain, Float64& totalStrain, bool& bExceededStrainLimits) const
{
   auto [Xcg,Ycg] = slice.pntCG.GetLocation();
   incrementalStrain = incrementalStrainPlane.GetZ(Xcg, Ycg);

   incrementalStrain /= slice.Le;

   totalStrain = incrementalStrain + slice.ei;

   fg_stress = 0;
   if (slice.FgMaterial)
   {
      auto [stress, bStrainWithinLimits] = slice.FgMaterial->ComputeStress(totalStrain);
      fg_stress = stress;
      bExceededStrainLimits = (bStrainWithinLimits ? false : true);
   }

   bg_stress = 0;
   if (slice.BgMaterial)
   {
      // it doesn't matter if you exceed the strain limit of the background material because it doesn't really exist
      auto [stress, bStrainWithinLimits] = slice.BgMaterial->ComputeStress(totalStrain);
      bg_stress = stress;
   }

   stress = fg_stress - bg_stress;

   P = slice.Area * stress;
   Mx = slice.Area * stress * Ycg;
   My = slice.Area * stress * Xcg;
}

bool GeneralSectionSolverImpl::SliceShape(const SHAPEINFO& shapeInfo, Float64 angle, Float64 sliceTop, Float64 sliceBottom, SLICEINFO& sliceInfo) const
{
   sliceInfo.ShapeIdx = shapeInfo.ShapeIdx; // record the index of the shape this slice is taken from

   m_ClippingRect.Top() = sliceTop;
   m_ClippingRect.Bottom() = sliceBottom;

   std::unique_ptr<WBFL::Geometry::Shape> clipped_shape = shapeInfo.Shape->CreateClippedShape(m_ClippingRect, WBFL::Geometry::Shape::ClipRegion::In);

   // sometimes the shape isn't even in the clipping box so
   // the result is nullptr... go to next slice
   if (clipped_shape == nullptr)
      return false;

   auto props = clipped_shape->GetProperties();

   sliceInfo.Top = IsZero(sliceTop) ? 0 : sliceTop;
   sliceInfo.Bottom = IsZero(sliceBottom) ? 0 : sliceBottom;
   sliceInfo.SliceShape = std::move(clipped_shape);
   sliceInfo.Area = props.GetArea();

   // rotate the CG point back into the original coordinate system
   sliceInfo.pntCG = props.GetCentroid();
   sliceInfo.pntCG.Rotate(0.00, 0.00, angle);

   // compute the initial strain at the CG of the slice using the shape's initial strain plane
   auto [cgX,cgY] = sliceInfo.pntCG.GetLocation();
   
   Float64 ei = shapeInfo.InitialStrain ? shapeInfo.InitialStrain->GetZ(cgX, cgY) : 0.0;

   sliceInfo.FgMaterial = shapeInfo.FgMaterial;
   sliceInfo.BgMaterial = shapeInfo.BgMaterial;
   sliceInfo.ei = ei;
   sliceInfo.Le = shapeInfo.Le;

   return true;
}

Float64 GeneralSectionSolverImpl::GetNeutralAxisAngle() const
{
   auto [p,v] = m_NeutralAxis.GetExplicit();
   return v.GetDirection();
}

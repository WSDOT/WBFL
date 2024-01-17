///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include "CrackedSectionSolverImpl.h"
#include <RCSection/XRCSection.h>

#if defined _DEBUG_LOGGING
#include <sstream>
#include <iomanip>
#include <Units\Units.h>

#define VALUE(_x_) (IsZero(_x_)  ? 0 : _x_)
#define LENGTH(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Inch))
#define AREA(_x_)   (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Inch2))
#define STRESS(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::KSI))
#endif // _DEBUG_LOGGING

using namespace WBFL::RCSection;

void CrackedSectionSolverImpl::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_Section = section;
   m_bDecomposed = false;
}

const std::shared_ptr<const IGeneralSection>& CrackedSectionSolverImpl::GetSection() const
{
   return m_Section;
}

void CrackedSectionSolverImpl::SetSlices(IndexType nSlices)
{
   if (m_nSlices != nSlices)
   {
      m_nSlices = nSlices;
      m_bDecomposed = false;
   }
}

IndexType CrackedSectionSolverImpl::GetSlices() const
{
   return m_nSlices;
}

void CrackedSectionSolverImpl::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_SliceGrowthFactor = sliceGrowthFactor;
}

Float64 CrackedSectionSolverImpl::GetSliceGrowthFactor() const
{
   return m_SliceGrowthFactor;
}

void CrackedSectionSolverImpl::SetTolerance(Float64 tolerance)
{
   m_Tolerance = tolerance;
}

Float64 CrackedSectionSolverImpl::GetTolerance() const
{
   return m_Tolerance;
}

void CrackedSectionSolverImpl::SetMaxIterations(IndexType maxIter)
{
   m_MaxIter = maxIter;
}

IndexType CrackedSectionSolverImpl::GetMaxIterations() const
{
   return m_MaxIter;
}

std::unique_ptr<CrackedSectionSolution> CrackedSectionSolverImpl::Solve(Float64 naAngle) const
{
   m_Angle = naAngle;
   DecomposeSection();

   Float64 Ylower = m_Ybottom;
   Float64 Yupper = m_Ytop;

   WBFL::Geometry::Point2d pntCG;
   std::vector<std::unique_ptr<CrackedSectionSlice>> slices;


   Float64 result_lower;
   AnalyzeSection(Ylower, slices, pntCG);

   Float64 resultY = pntCG.Y();
   result_lower = Ylower - resultY;

   Float64 result_upper;
   slices.clear();
   AnalyzeSection(Yupper, slices, pntCG);

   resultY = pntCG.Y();
   result_upper = Yupper - resultY;

   Float64 Y = Ylower;
   Float64 result = result_lower;

   int side = 0;
   IndexType iter = 0;
   for (iter = 0; iter < m_MaxIter; iter++)
   {
      if (IsZero(result, m_Tolerance) && IsZero(result_lower, m_Tolerance) && IsZero(result_upper, m_Tolerance))
         break; // converged

      // guess next value
      Y = (result_upper * Ylower - result_lower * Yupper) / (result_upper - result_lower);

      slices.clear();
      AnalyzeSection(Y, slices, pntCG);

      resultY = pntCG.Y();
      result = Y - resultY;

      if (result * result_upper > 0)
      {
         Yupper = Y;
         result_upper = result;
         if (side == -1)
            result_lower /= 2;

         side = -1;
      }
      else if (result_lower * result > 0)
      {
         Ylower = Y;
         result_lower = result;
         if (side == 1)
            result_upper /= 2;

         side = 1;
      }
      else
      {
         break;
      }
   }

   if (m_MaxIter <= iter)
   {
      THROW_RCSECTION(_T("Solution not found - did not converge before maximum number of iterations"));
   }

   return std::make_unique<CrackedSectionSolution>(pntCG,std::move(slices));
}

void CrackedSectionSolverImpl::DecomposeSection() const
{
   if (m_bDecomposed)
      return; // section is decomposed and NA direction hasn't changed... analysis is good to go

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

      auto shape = original_shape.CreateClone();
      shape->Rotate(0, 0, -m_Angle);

      auto bndbox = shape->GetBoundingBox();

      if (shapeIdx == 0)
      {
         bounding_box = bndbox;
      }
      else
      {
         bounding_box.Union(bndbox);
      }

      shapes.emplace_back(shapeIdx, std::move(shape), fgMaterial, bgMaterial);
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
         bool bResult = SliceShape(shape_info, slice_top, slice_bottom, slice_info);

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

   m_Ytop = bounding_box.Top();
   m_Ybottom = bounding_box.Bottom();

   std::sort(m_Slices.begin(), m_Slices.end());
   m_bDecomposed = true;
}

void CrackedSectionSolverImpl::AnalyzeSection(Float64 Yguess, std::vector<std::unique_ptr<CrackedSectionSlice>>& slices, WBFL::Geometry::Point2d& cg) const
{
   // Summations for first moment of area
   Float64 EA = 0;
   Float64 EAx = 0;
   Float64 EAy = 0;

#if defined _DEBUG_LOGGING
   std::_tostringstream os;
   os << "Yguess: " << LENGTH(Yguess) << std::endl;
   os << std::setw(10) << "Area, " << std::setw(10) << "Side, " << std::setw(10) << "Top, " << std::setw(10) << "Bottom, " << std::setw(20) << "Xcg, " << std::setw(20) << "Ycg, " << std::setw(20) << "FG, " << std::setw(20) << "BG" << std::endl;
#endif // _DEBUG_LOGGING

   for(auto& slice : m_Slices)
   {
      if ((slice.Bottom < Yguess) && (Yguess < slice.Top))
      {
         // this slice spans the guess location... 
         // need to clip again 
         SHAPEINFO shape_info;
         shape_info.BgMaterial = slice.BgMaterial;
         shape_info.FgMaterial = slice.FgMaterial;
         shape_info.Shape = slice.SliceShape;
         shape_info.ShapeIdx = slice.ShapeIdx;

         SLICEINFO top_slice;
         bool bResult = SliceShape(shape_info, slice.Top, Yguess, top_slice);
         if (bResult)
         {
            Float64 ea, eax, eay, Efg, Ebg;
            AnalyzeSlice(Yguess, top_slice, ea, eax, eay, Efg, Ebg);

            EA += ea;
            EAx += eax;
            EAy += eay;

            slices.emplace_back(std::make_unique<CrackedSectionSlice>(slice.ShapeIdx, top_slice.SliceShape, top_slice.Area, top_slice.pntCG, Efg, Ebg));

#if defined _DEBUG_LOGGING
            os << std::setw(10) << AREA(top_slice.Area) << ", " << std::setw(10) << "C, " << std::setw(10) << LENGTH(top_slice.Top) << ", " << std::setw(10) << LENGTH(top_slice.Bottom) << ", " << std::setw(20) << LENGTH(top_slice.pntCG.X()) << ", " << std::setw(20) << LENGTH(top_slice.pntCG.Y()) << ", " << std::setw(20) << STRESS(Efg) << ", " << std::setw(20) << STRESS(Ebg) << std::endl;
#endif // _DEBUG_LOGGING
         }

         SLICEINFO bottom_slice;
         bResult = SliceShape(shape_info, Yguess, slice.Bottom, bottom_slice);
         if (bResult)
         {
            Float64 ea, eax, eay, Efg, Ebg;
            AnalyzeSlice(Yguess, bottom_slice, ea, eax, eay, Efg, Ebg);

            EA += ea;
            EAx += eax;
            EAy += eay;

            slices.emplace_back(std::make_unique<CrackedSectionSlice>(slice.ShapeIdx, bottom_slice.SliceShape, bottom_slice.Area, bottom_slice.pntCG, Efg, Ebg));

#if defined _DEBUG_LOGGING
            os << std::setw(10) << AREA(bottom_slice.Area) << ", " << std::setw(10) << "C, " << std::setw(10) << LENGTH(bottom_slice.Top) << ", " << std::setw(10) << LENGTH(bottom_slice.Bottom) << ", " << std::setw(20) << LENGTH(bottom_slice.pntCG.X()) << ", " << std::setw(20) << LENGTH(bottom_slice.pntCG.Y()) << ", " << std::setw(20) << STRESS(Efg) << ", " << std::setw(20) << STRESS(Ebg) << std::endl;
#endif // _DEBUG_LOGGING
         }
      }
      else
      {
         Float64 ea, eax, eay, Efg, Ebg;
         AnalyzeSlice(Yguess, slice, ea, eax, eay, Efg, Ebg);

         EA += ea;
         EAx += eax;
         EAy += eay;

         slices.emplace_back(std::make_unique<CrackedSectionSlice>(slice.ShapeIdx, slice.SliceShape, slice.Area, slice.pntCG, Efg, Ebg));

#if defined _DEBUG_LOGGING
         char cSide = (Yguess < slice.pntCG.Y() ? 'C' : 'T');
         os << std::setw(10) << AREA(slice.Area) << ", " << std::setw(10) << cSide << ", " << std::setw(10) << LENGTH(slice.Top) << ", " << std::setw(10) << LENGTH(slice.Bottom) << ", " << std::setw(20) << LENGTH(slice.pntCG.X()) << ", " << std::setw(20) << LENGTH(slice.pntCG.Y()) << ", " << std::setw(20) << STRESS(Efg) << ", " << std::setw(20) << STRESS(Ebg) << std::endl;
#endif // _DEBUG_LOGGING
      }
   } // next slice

   // locate centroid of the cracked section
   Float64 x = IsZero(EA) ? 0 : EAx / EA;
   Float64 y = IsZero(EA) ? 0 : EAy / EA;

   cg.Move(x, y);

#if defined _DEBUG_LOGGING
   os << std::setw(10) << "Area, " << std::setw(10) << "Side, " << std::setw(10) << "Top, " << std::setw(10) << "Bottom, " << std::setw(20) << "Xcg, " << std::setw(20) << "Ycg, " << std::setw(20) << "FG, " << std::setw(20) << "BG" << std::endl;
   os << std::endl;
   os << "Y = " << LENGTH(y) << std::endl;
   os << "Yguess - Y = " << LENGTH(Yguess - y) << std::endl;
#endif // _DEBUG_LOGGING
}

void CrackedSectionSolverImpl::AnalyzeSlice(Float64 Yguess, SLICEINFO& slice, Float64& EA, Float64& EAx, Float64& EAy, Float64& Efg, Float64& Ebg) const
{
   auto fgMaterial = slice.FgMaterial.lock();

   if (slice.pntCG.Y() < Yguess)
   {
      // Slice is on the tension side of the assumed neutral axis
      // Get a realistic tension strain to determine if material has tension capacity

      // assume material doesn't have any tension capacity
      EA = 0;
      EAx = 0;
      EAy = 0;
      Efg = 0;
      Ebg = 0;

      if (!fgMaterial)
         return;

      auto [minStrain, maxStrain] = fgMaterial->GetStrainLimits();
      auto [stress, bStrainWithinLimits] = fgMaterial->ComputeStress(maxStrain);
      if (IsZero(stress))
      {
         return;
      }
   }

   Efg = fgMaterial->GetModulusOfElasticity();

   auto bgMaterial = slice.BgMaterial.lock();

   if (bgMaterial)
      Ebg = bgMaterial->GetModulusOfElasticity();
   else
      Ebg = 0.0;

   Float64 E = (Efg - Ebg);

   EA = E * slice.Area;
   EAx = EA * slice.pntCG.X();
   EAy = EA * slice.pntCG.Y();
}

bool CrackedSectionSolverImpl::SliceShape(const SHAPEINFO& shapeInfo, Float64 sliceTop, Float64 sliceBottom, SLICEINFO& sliceInfo) const
{
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
   sliceInfo.ShapeIdx = shapeInfo.ShapeIdx;
   sliceInfo.Area = props.GetArea();
   sliceInfo.pntCG = props.GetCentroid();

   sliceInfo.FgMaterial = shapeInfo.FgMaterial;
   sliceInfo.BgMaterial = shapeInfo.BgMaterial;

   return true;
}

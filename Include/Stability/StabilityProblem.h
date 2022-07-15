///////////////////////////////////////////////////////////////////////
// Stability
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

#pragma once

#include <Stability/StabilityExp.h>
#include <Stability/AnalysisPoint.h>

interface ISegment;

namespace WBFL
{
   namespace Geometry
   {
      class Point2d;
   };

   namespace Materials
   {
      class Concrete;
   };

   namespace Stability
   {
      ///  Abstract interface for defining a girder for stability analysis
      class STABILITYCLASS IGirder
      {
      public:
         /// Returns the overall length of the girder
         virtual Float64 GetGirderLength() const = 0;

         /// Assigns an ISegment object to ppSegment. 
         ///
         /// If a value is not assigned, then the girder is modeled with basic properties only.
         /// This section must be assigned to do the analysis for the alternative tensile stress limits (with rebar tension limit)
         virtual void GetSegment(ISegment** ppSegment) const = 0;

         /// Returns the number of sections used to define the girder
         virtual IndexType GetSectionCount() const = 0;

         /// Returns the length of a girder section
         virtual Float64 GetSectionLength(IndexType sectIdx) const = 0;

         /// Gets the properties associated with a girder section
         /// \param[in] sectIdx index of a girder section
         /// \param[in] section start or end of the girder section
         /// \param[out] pAg cross sectional area
         /// \param[out] pIxx X-axis moment of inertia
         /// \param[out] pIyy Y-axis moment of inertia
         /// \param[out] pIxy product of inertia
         /// \param[out] pXleft distance from the extreme left edge of the section to the centroid
         /// \param[out] pYtop distance from the top of the section to the centroid
         /// \param[out] pHg height of the section
         /// \param[out] pWtop top width
         /// \param[out] pWbot bottom width
         virtual void GetSectionProperties(IndexType sectIdx, Section section, Float64* pAg, Float64* pIxx, Float64* pIyy, Float64* pIxy, Float64* pXleft, Float64* pYtop, Float64* pHg, Float64* pWtop, Float64* pWbot) const = 0;

         /// Gets the properties of the girder at a specified location
         /// \param[in] X location along the girder
         /// \param[out] pAg cross sectional area
         /// \param[out] pIxx X-axis moment of inertia
         /// \param[out] pIyy Y-axis moment of inertia
         /// \param[out] pIxy product of inertia
         /// \param[out] pXleft distance from the extreme left edge of the section to the centroid
         /// \param[out] pYtop distance from the top of the section to the centroid
         /// \param[out] pHg height of the section
         /// \param[out] pWtop top width
         /// \param[out] pWbot bottom width
         virtual void GetSectionProperties(Float64 X, Float64* pAg, Float64* pIxx, Float64* pIyy, Float64* pIxy, Float64* pXleft, Float64* pYtop, Float64* pHg, Float64* pWtop, Float64* pWbot) const = 0;

         /// Gets the stress points associated with a girder section
         /// \param[in] sectIdx index of a girder section
         /// \param[in] section start or end of the girder section
         /// \param[out] pTL top left stress point
         /// \param[out] pTR top right stress point
         /// \param[out] pBL bottom left stress point
         /// \param[out] pBR bottom right stress point
         virtual void GetStressPoints(IndexType sectIdx, Section section, Point* pTL, Point* pTR, Point* pBL, Point* pBR) const = 0;

         /// Gets the stress points at a specified location
         /// \param[in] X location along the girder
         /// \param[out] pTL top left stress point
         /// \param[out] pTR top right stress point
         /// \param[out] pBL bottom left stress point
         /// \param[out] pBR bottom right stress point
         virtual void GetStressPoints(Float64 X, Point* pTL, Point* pTR, Point* pBL, Point* pBR) const = 0;

         /// Returns additional loads applied to the girder. The first parameters is the location of the load measured from
         /// the left end of the girder and the second is the magintude of the load. Positive values are in the direction of gravity (downwards).
         /// These loads can be used to model cast-in-place elements such as end diaphraphms in U-Beam girders
         virtual std::vector<std::pair<Float64, Float64>> GetAdditionalLoads() const = 0;

         /// Drag coefficient for wind loads
         virtual Float64 GetDragCoefficient() const = 0;

         /// Returns the precamber that is built into the girder
         virtual Float64 GetPrecamber() const = 0;
      };


      /// Abstract interface for defining the basic stability problem
      class STABILITYCLASS IStabilityProblem
      {
      public:
         /// Returns the names of prestressing, such as "straight" and "harped" for straight and harped strands.
         virtual std::vector<LPCTSTR> GetPrestressNames() const = 0;

         /// Returns effective prestress force parameters
         /// \param[in] strName name of the prestressing time
         /// \param[in] X location along the girder
         /// \param[out] pFpe effective prestress
         /// \param[out] pXps horizontal location from the CL of the girder to the prestress force
         /// \param[out] pYps vertical location from the top of the girder at a location along the girder to the prestress force
         virtual bool GetFpe(LPCTSTR strName, Float64 X, Float64* pFpe, Float64* pXps, Float64* pYps) const = 0;

         /// Returns the concrete model
         virtual const WBFL::Materials::Concrete& GetConcrete() const = 0;

         /// Returns the yield strength of rebar. Only used if the girder is modeled with an ISection object
         virtual Float64 GetRebarYieldStrength() const = 0;

         /// Returns the support locations. Support locations are measured from left and right ends of girder.
         virtual void GetSupportLocations(Float64* pLeft, Float64* pRight) const = 0;

         /// Returns the location of the roll axis in girder section coordinates.
         /// (0,0) is at the top center of the girder.
         /// Positive values mean the roll axis is above the top of the girder.
         virtual Float64 GetYRollAxis() const = 0;

         /// Returns the manufacturing sweep tolerance
         virtual Float64 GetSweepTolerance() const = 0;

         /// Returns the sweep growth. For hauling, PCI has total sweep as (1/8 in per 10 ft + 1").
         /// The 1" in the expression is the sweep growth.
         virtual Float64 GetSweepGrowth() const = 0;

         /// Lateral offset from CL Girder and Roll Axis to account for accidiental mis-alignment
         virtual Float64 GetSupportPlacementTolerance() const = 0;

         /// Returns the camber. This is the natural camber. Do not include formed camber (precamber).
         virtual Float64 GetCamber() const = 0;

         /// Returns the camber multiplier used to magnify camber
         virtual Float64 GetCamberMultiplier() const = 0;

         /// Returns the lateral camber, often due to asymmetric prestressing or prestressing of an asymmetric section.
         virtual Float64 GetLateralCamber() const = 0;

         /// Returns true if lateral offset of the CG from the roll axis and lateral camber are to be considered in the analysis.
         /// The roll axis is assumed to be the vertical centerline of the girder.
         /// Lateral offset of the CG generally occurs for asymmetric sections.
         virtual bool IncludeLateralRollAxisOffset() const = 0;

         /// Returns the impact up and down (fractional value, both positive)
         virtual void GetImpact(Float64* pIMup, Float64* pIMdown) const = 0;

         /// Returns the method that wind loading is defined and the wind load parameter
         virtual void GetWindLoading(
            WindType* pType, ///< Method for defining wind load
            Float64* pLoad ///< The wind load parameter (wind speed or wind pressure). 
         ) const = 0;

         ///  Gets the parameters for appurtenance loading such as overhang brackets attached to the girder
         /// \param[out] pex lateral eccentricty of the loading. Positive values are in the same direction as lateral sweep
         /// \param[out] pW uniform weight of loading uniformly distributed along the entire length of the girder. Positive values are in the direction of gravity (downwards).
         virtual void GetAppurtenanceLoading(Float64* pex, Float64* pW) const = 0;

         /// Returns a vector of points where stress and cracking analysis is performed
         virtual const std::vector<std::unique_ptr<IAnalysisPoint>>& GetAnalysisPoints() const = 0;

         /// Returns a specific analysis point
         virtual const std::unique_ptr<IAnalysisPoint>& GetAnalysisPoint(IndexType idx) const = 0;
      };


      /// Abstract interface that extends IStabilityProblem for lifting analysis
      class STABILITYCLASS ILiftingStabilityProblem : public IStabilityProblem
      {
      public:
         /// Returns the angle of lift cables, measured in radians from the horizontal. Return PI_OVER_2 for a vertical lift.
         virtual Float64 GetLiftAngle() const = 0;
      };


      /// Abstract interface that extends IStabilityProblem for analysis of seated girders
      class STABILITYCLASS ISeatedStabilityProblem : public IStabilityProblem
      {
      public:
         /// Returns the rotational stiffness (Ktheta)
         virtual Float64 GetRotationalStiffness() const = 0;

         /// Returns the width of the support (center-to-center wheel spacing (Wcc) or bearing pad width)
         virtual Float64 GetSupportWidth() const = 0;

         /// Returns the height of the roll axis above the support
         virtual Float64 GetHeightOfRollAxis() const = 0;

         /// Returns the slope of the support(always a positive value)
         virtual Float64 GetSupportSlope() const = 0;
      };
      /// Abstract interface that extends IStabilityProblem for hauling analysis
      class STABILITYCLASS IHaulingStabilityProblem : public ISeatedStabilityProblem
      {
      public:
         /// Returns how impact is used in the analysis
         virtual HaulingImpact GetImpactUsage() const = 0;

         /// Returns the superelevation rate (always a postive value)
         virtual Float64 GetSuperelevation() const = 0;

         /// Returns the velocity of the truck. Used for computing centrifugal force.
         virtual Float64 GetVelocity() const = 0;

         /// Returns the turning radius. Used for computing centrifugal force
         virtual Float64 GetTurningRadius() const = 0;

         /// Returns the type of centrifugal force
         virtual CFType GetCentrifugalForceType() const = 0;
      };

      /// Abstract interface that extends IStabilityProblem for analysis of girders seated at one end and hanging from the other
      class STABILITYCLASS IOneEndSeatedStabilityProblem : public ISeatedStabilityProblem
      {
      public:
         /// Returns the end of the girder that is seated
         virtual GirderSide GetSeatedEnd() const = 0;

         /// Returns the a factor to adjust rotational stiffness.
         /// When analyzing cases where the seated end is on a truck, it is often convenient to
         /// define the rotational stiffness of the full truck. This factor is multiplied with the
         /// rotational stiffness to estimate the stiffness of one end of the truck.
         virtual Float64 GetRotationalStiffnessAdjustmentFactor() const = 0;

         /// Returns the location of the roll axis at the lifted end of the girder in girder section coordinates.
         /// (0,0) is at the top center of the girder.
         /// Positive values mean the roll axis is above the top of the girder.
         /// For the seated at one end analysis, GetYRoll() and GetHeightOfRollAxis() pertain to the
         /// seated end of the girder
         virtual Float64 GetYRollLiftEnd() const = 0;

         /// Lateral offset from CL Girder and Roll Axis at the lifting point to account for accidiental mis-alignment
         virtual Float64 GetLiftPlacementTolerance() const = 0;
      };
   }
}

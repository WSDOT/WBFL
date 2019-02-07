///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2019  Washington State Department of Transportation
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

#include <Stability\StabilityExp.h>
#include <WBFLGenericBridge.h> // for ISegment
#include <Material\ConcreteEx.h>
#include <Stability\AnalysisPoint.h>

class gpPoint2d;

/*****************************************************************************
CLASS 
   stbIGirder

DESCRIPTION
   Abstract interface for defining a girder
*****************************************************************************/

class STABILITYCLASS stbIGirder
{
public:
   // returns the overall length of the girder
   virtual Float64 GetGirderLength() const = 0;

   // Assigns an ISegment object to ppSegment
   // if a value is not assigned, then the girder is modeled with basic properties only.
   // This section must be assigned to do the analysis for the alternative tensile stress limits (with rebar tension limit)
   virtual void GetSegment(ISegment** ppSegment) const = 0;

   // returns the number of sections used to define the girder
   virtual IndexType GetSectionCount() const = 0;

   // returns the length of a girder section
   virtual Float64 GetSectionLength(IndexType sectIdx) const = 0;

   // gets the properties associated with a girder section
   virtual void GetSectionProperties(IndexType sectIdx,stbTypes::Section section,Float64* pAg,Float64* pIxx,Float64* pIyy,Float64* pIxy,Float64* pXleft,Float64* pYtop,  Float64* pHg,Float64* pWtop,Float64* pWbot) const = 0;

   // gets the properties of the girder at a specified location
   virtual void GetSectionProperties(Float64 X,Float64* pAg,Float64* pIxx,Float64* pIyy,Float64* pIxy,Float64* pXleft,Float64* pYtop, Float64* pHg,Float64* pWtop,Float64* pWbot) const = 0;

   // gets the stress points associated with a girder section
   virtual void GetStressPoints(IndexType sectIdx, stbTypes::Section section, gpPoint2d* pTL,gpPoint2d* pTR,gpPoint2d* pBL,gpPoint2d* pBR) const = 0;

   // gets the stress points at a specified location
   virtual void GetStressPoints(Float64 X, gpPoint2d* pTL, gpPoint2d* pTR, gpPoint2d* pBL, gpPoint2d* pBR) const = 0;

   // returns additional loads applied to the girder. The first parameters is the location of the load measured from
   // the left end of the girder and the section is the magintude of the load. Positive values are in the direction of gravity.
   // These loads can be used to model cast-in-place elements such as end diaphraphms in U-Beam girders
   virtual std::vector<std::pair<Float64,Float64>> GetAdditionalLoads() const = 0;

   // drag coefficient for wind loads
   virtual Float64 GetDragCoefficient() const = 0;

   // returns the precamber that is built into the girder
   virtual Float64 GetPrecamber() const = 0;
};


/*****************************************************************************
CLASS 
   stbIStabilityProblem

DESCRIPTION
   Abstract interface for defining the basic stability problem
*****************************************************************************/
class STABILITYCLASS stbIStabilityProblem
{
public:
   // returns the effective prestress force and its vertical location from the top of the girder at a location along the girder
   virtual void GetFpe(stbTypes::StrandType strandType,Float64 X,Float64* pFpe,Float64* pXps,Float64* pYps) const = 0;

   // returns the concrete model
   virtual const matConcreteEx& GetConcrete() const = 0;

   // Returns the yield strength of rebar. Only used if the girder is modeled with an ISection object
   virtual Float64 GetRebarYieldStrength() const = 0;

   // returns the support locations. support locations are measured from left/right ends of girder
   virtual void GetSupportLocations(Float64* pLeft,Float64* pRight) const = 0;

   // returns the location of the roll axis in girder section coordinates
   // (0,0) is at the top center of the girder.
   // positive values mean the roll axis is above the top of the girder
   virtual Float64 GetYRollAxis() const = 0;
   
   // returns the manufacturing sweep tolerance
   virtual Float64 GetSweepTolerance() const = 0;

   // Lateral offset from CL Girder and Roll Axis to account for accidiental mis-alignment
   virtual Float64 GetSupportPlacementTolerance() const = 0;

   // returns the camber or camber parameter
   // bDirectCamber - if true, pCamber is a direct value, otherwise pCamber is a fraction (percentage)
   // by which to increasing the height from the CG to the roll center to estimate the effect of camber
   virtual void GetCamber(bool* pbDirectCamber,Float64* pCamber) const = 0;

   // returns the camber multiplier used to modify direct camber
   virtual Float64 GetCamberMultiplier() const = 0;

   // returns the lateral camber, often due to asymmetric prestressing or prestressing
   // of an asymmetric section
   virtual Float64 GetLateralCamber() const = 0;

   // returns true if lateral offset of the CG from the roll axis and lateral camber are to be considered in the analysis
   // the roll axis is assumed to be the vertical centerline of the girder
   // lateral offset of the CG generally occurs for asymmetric sections
   virtual bool IncludeLateralRollAxisOffset() const = 0;

   // returns the impact up and down (fractional value, both positive)
   virtual void GetImpact(Float64* pIMup,Float64* pIMdown) const = 0;

   // returns the method that wind loading is defined and the wind load parameter
   virtual void GetWindLoading(stbTypes::WindType* pType,Float64* pLoad) const = 0;

   // returns a vector of points where stress and cracking analysis is performed
   virtual std::vector<stbIAnalysisPoint*> GetAnalysisPoints() const = 0;

   // returns an analysis point
   virtual const stbIAnalysisPoint* GetAnalysisPoint(IndexType idx) const = 0;
};


/*****************************************************************************
CLASS 
   stbILiftingStabilityProblem

DESCRIPTION
   Abstract interface that extends stbIStabilityProblem for lifting analysis
*****************************************************************************/
class STABILITYCLASS stbILiftingStabilityProblem : public stbIStabilityProblem
{
public:
   // returns the angle of lift cables, measured from the horizontal
   // will return PI_OVER_2 for a vertical lift
   virtual Float64 GetLiftAngle() const = 0; 

   // returns true if stresses are to be evaluted in the tilted equilibrium condition
   virtual bool EvaluateStressesAtEquilibriumAngle() const = 0;
};



/*****************************************************************************
CLASS 
   stbIHaulingStabilityProblem

DESCRIPTION
   Abstract interface that extends stbIStabilityProblem for hauling analysis
*****************************************************************************/
class STABILITYCLASS stbIHaulingStabilityProblem :  public stbIStabilityProblem
{
public:
   // returns how impact is used
   virtual stbTypes::HaulingImpact GetImpactUsage() const = 0;

   // returns the truck rotational stiffness (Ktheta)
   virtual Float64 GetTruckRotationalStiffness() const = 0;

   // returns the center-to-center wheel spacing (Wcc)
   virtual Float64 GetWheelLineSpacing() const = 0;

   // returns the height of the roll axis above the roadway
   virtual Float64 GetHeightOfRollAxisAboveRoadway() const = 0;

   // returns the normal crown slope (always a positive value)
   virtual Float64 GetCrownSlope() const = 0;

   // returns the superelevation rate (always a postive value)
   virtual Float64 GetSuperelevation() const = 0;

   // returns the velocity of the truck
   // used for computing centrifugal force
   virtual Float64 GetVelocity() const = 0;

   // returns the turning radius
   // used for computing centrifugal force
   virtual Float64 GetTurningRadius() const = 0;

   // returns the type of centrifugal force
   virtual stbTypes::CFType GetCentrifugalForceType() const = 0;

   // returns true if stresses are to be evaluted in the tilted equilibrium condition
   virtual bool EvaluateStressesAtEquilibriumAngle(stbTypes::HaulingSlope slope) const = 0;
};

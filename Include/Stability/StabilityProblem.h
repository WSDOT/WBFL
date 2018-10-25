///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2016  Washington State Department of Transportation
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

#define LEFT  0
#define RIGHT 1

#define STRAIGHT  0
#define HARPED    1
#define TEMPORARY 2

#define SECTION_START 0
#define SECTION_END   1

/*****************************************************************************
CLASS 
   stbIGirder

DESCRIPTION
   Abstract interface for defining a girder


COPYRIGHT
   Copyright © 1997-2016
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class STABILITYCLASS stbIGirder
{
public:
   // returns the overall length of the girder
   virtual Float64 GetGirderLength() const = 0;

   // returns the total dead weight of the girder
   virtual Float64 GetGirderWeight() const = 0;

   // returns the location of a strand in girder section coordinates
   virtual Float64 GetStrandLocation(int strandType,Float64 X) const = 0;

   // returns the number of sections used to define the girder
   virtual IndexType GetSectionCount() const = 0;

   // returns the length of a girder section
   virtual Float64 GetSectionLength(IndexType sectIdx) const = 0;

   // gets the properties associated with a girder section
   virtual void GetSectionProperties(IndexType sectIdx,int face,Float64* pAg,Float64* pIx,Float64* pIy,Float64* pYt,Float64* pHg,Float64* pWtop,Float64* pWbot) const = 0;

   // gets the properties of the girder at a specified location
   virtual void GetSectionProperties(Float64 X,Float64* pAg,Float64* pIx,Float64* pIy,Float64* pYt,Float64* pHg,Float64* pWtop,Float64* pWbot) const = 0;

   // returns the density of the girder used for computing self-weight dead load
   virtual Float64 GetDensity() const = 0;

   // returns additional loads applied to the girder. The first parameters is the location of the load measured from
   // the left end of the girder and the section is the magintude of the load. Positive values are in the direction of gravity.
   // These loads can be used to model cast-in-place elements such as end diaphraphms in U-Beam girders
   virtual std::vector<std::pair<Float64,Float64>> GetAdditionalLoads() const = 0;
};


/*****************************************************************************
CLASS 
   stbIStabilityProblem

DESCRIPTION
   Abstract interface for defining the basic stability problem


COPYRIGHT
   Copyright © 1997-2016
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/
class STABILITYCLASS stbIStabilityProblem
{
public:
   // returns the effective prestress force at a location along the girder
   virtual Float64 GetFpe(int strandType,Float64 X) const = 0;

   // returns the concrete strength of the girder concrete
   virtual Float64 GetFc() const = 0;

   // returns the modulus of elasticity of the girder concrete
   virtual Float64 GetEc() const = 0;

   // returns the modulus of rupture of the girder concrete
   virtual Float64 GetFr() const = 0;

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

   // returns the impact up and down (fractional value, both positive)
   virtual void GetImpact(Float64* pIMup,Float64* pIMdown) const = 0;

   // returns true if impact is to be applied to the girder in a tilted configuration
   virtual bool ApplyImpactToTiltedGirder() const = 0;

   // returns the wind pressure applied laterally to the girder
   // this is a positive value and represents wind applied in both the left and right direction
   virtual Float64 GetWindPressure() const = 0;

   // returns a vector of points where stress and cracking analysis is performed
   virtual std::vector<Float64> GetAnalysisPoints() const = 0;
};


/*****************************************************************************
CLASS 
   stbILiftingStabilityProblem

DESCRIPTION
   Abstract interface that extends stbIStabilityProblem for lifting analysis


COPYRIGHT
   Copyright © 1997-2016
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/
class STABILITYCLASS stbILiftingStabilityProblem : public stbIStabilityProblem
{
public:
   // returns the angle of lift cables, measured from the horizontal
   // will return PI_OVER_2 for a vertical lift
   virtual Float64 GetLiftAngle() const = 0; 
};



/*****************************************************************************
CLASS 
   stbIHaulingStabilityProblem

DESCRIPTION
   Abstract interface that extends stbIStabilityProblem for hauling analysis


COPYRIGHT
   Copyright © 1997-2016
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/
class STABILITYCLASS stbIHaulingStabilityProblem :  public stbIStabilityProblem
{
public:
   // returns the truck rotational stiffness (Ktheta)
   virtual Float64 GetTruckRotationalStiffness() const = 0;

   // returns the center-to-center wheel spacing (Wcc)
   virtual Float64 GetWheelLineSpacing() const = 0;

   // returns the height of the roll axis above the roadway
   virtual Float64 GetHeightOfRollAxisAboveRoadway() const = 0;

   // returns the superelevation rate (always a postive value)
   virtual Float64 GetSuperelevation() const = 0;

   // returns the velocity of the truck
   // used for computing centrifugal force
   virtual Float64 GetVelocity() const = 0;

   // returns the turning radius
   // used for computing centrifugal force
   virtual Float64 GetTurningRadius() const = 0;
};

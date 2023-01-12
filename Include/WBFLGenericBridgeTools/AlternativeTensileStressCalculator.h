///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#pragma once

#include <WBFLGenericBridgeTools\WBFLGenericBridgeToolsExp.h>
#include <Material\Concrete.h>
#include <WBFLGeometry.h>
#include <GeometricPrimitives\Primitives3d.h>
#include <WBFLGenericBridge.h>

#include <WBFLRCCapacity.h> // for IGeneralSectionSolution

/*****************************************************************************
CLASS 
   gbtAlternativeTensileStressCalculator

   Utility class for dealing with alternative tensile stress in casting yard and at lifting
*****************************************************************************/

struct WBFLGENERICBRIDGETOOLSCLASS gbtAlternativeTensileStressRequirements
{
   // Input

   // reinforcement stress properties
   Float64 fy; // yield stress of rebar
   bool bLimitBarStress; // if true, allowable bar stress cannot exceed fsMax
   Float64 fsMax; // maximum bar stress if bLimitBarStress is true

   // concrete properties (only used if bAdjustForDevelopmentLength is true)
   matConcrete::Type concreteType;
   Float64 fc;
   bool bHasFct;
   Float64 Fct;
   Float64 density;
   bool bAdjustForDevelopmentLength;

   CComPtr<IShape> shape; // shape of girder (must be in Centroidal/Stress Point coordinates)
   CComPtr<IRebarSection> rebarSection; // longitudinal rebar in the girder (in Section coordinates)
   Float64 Ytg; // Ytop of Girder... added to Y location of rebar to convert it into centroidal coordinates
   
   // coordindate and stress on top and bottom, left and right of girder section
   // Z = stress
   gpPoint3d pntTopLeft;
   gpPoint3d pntTopRight;
   gpPoint3d pntBottomLeft;
   gpPoint3d pntBottomRight;

   // Output
   CComPtr<IShape> tensionArea; // area in tension
   Float64 AreaTension; // area in tension computed from tensionArea

   CComPtr<IGeneralSectionSolution> tensionForceSolution;
   Float64 T; // tension force

   Float64 Yna; // vertical location of neutral axis line, measure in Section Coordinates (0,0 at top CL of girder)
   Float64 NAslope; // slope of neutral axis

   Float64 AsProvided; // area of steel provided in the tension zone
   Float64 AsRequired; // area of steel required in the tension zone
   bool bIsAdequateRebar; // if true, the area of steel provide is adequate to use the higher tension stress limit

   gbtAlternativeTensileStressRequirements();
   gbtAlternativeTensileStressRequirements(const gbtAlternativeTensileStressRequirements& other) = default;
   gbtAlternativeTensileStressRequirements& operator=(const gbtAlternativeTensileStressRequirements& other) = default;
};

void WBFLGENERICBRIDGETOOLSFUNC gbtComputeAlternativeStressRequirements(gbtAlternativeTensileStressRequirements* pRequirements);


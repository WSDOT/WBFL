///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <WBFLGenericBridgeTools\WBFLGenericBridgeToolsExp.h>
#include <Material\Concrete.h>
#include <WBFLGeometry.h>
#include <GeometricPrimitives\Primitives3d.h>
#include <WBFLGenericBridge.h>

/*****************************************************************************
CLASS 
   gbtAlternativeTensileStressCalculator

   Utility class for dealing with alternative tensile stress in casting yard and at lifting
*****************************************************************************/

struct WBFLGENERICBRIDGETOOLSCLASS gbtAlternativeTensileStressRequirements
{
   // Input
   Float64 fy;
   bool bLimitBarStress;
   Float64 fsMax;
   matConcrete::Type concreteType;
   Float64 fc;
   bool bHasFct;
   Float64 Fct;
   Float64 density;
   bool bAdjustForDevelopmentLength;

   CComPtr<IShape> shape;
   CComPtr<IRebarSection> rebarSection;
   gpPoint3d pntTopLeft;
   gpPoint3d pntTopRight;
   gpPoint3d pntBottomLeft;
   gpPoint3d pntBottomRight;
   Float64 Ytg;

   // Output
   CComPtr<IShape> tensionArea;
   Float64 Yna;
   Float64 NAslope;
   Float64 AreaTension;
   Float64 T;
   Float64 AsProvided;
   Float64 AsRequired;
   bool bIsAdequateRebar;

   gbtAlternativeTensileStressRequirements();
   gbtAlternativeTensileStressRequirements(const gbtAlternativeTensileStressRequirements& other);
   void operator=(const gbtAlternativeTensileStressRequirements& other);
};

void WBFLGENERICBRIDGETOOLSFUNC gbtComputeAlternativeStressRequirements(gbtAlternativeTensileStressRequirements* pRequirements);


///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

#include <GenericBridge\GenericBridgeExp.h>
#include <WBFLGenericBridge.h>

enum class TransitionType 
{
   Linear, // linear transition between two points
   RightParabola, // parabalic transition with zero slope at left end (parabola is to the right of the Y axis)
   LeftParabola // parabolic transition with zero slope at right end (parabola is to the left of the Y axis)
};

typedef enum ZoneType
{
   LeftStraight,
   LeftSlope,
   MidStraight,
   RightSlope,
   RightStraight
} ZoneType;

typedef enum ZoneBreakType
{
   Start,
   LeftBreak,
   RightBreak,
   End
} ZoneBreakType;

std::array<Float64, 4> WBFLGENERICBRIDGEFUNC ResolveFractionalDistance(const std::array<Float64, 4>& X, Float64 L);
TransitionType WBFLGENERICBRIDGEFUNC TransitionTypeFromZone(ZoneType zone,bool bParabolas);
Float64 WBFLGENERICBRIDGEFUNC GetSectionDepth(Float64 X,Float64 X1, Float64 H1, Float64 X2, Float64 H2, TransitionType transition);
ZoneType WBFLGENERICBRIDGEFUNC GetZone(Float64 Xs, const std::array<Float64, 4>& X);
ZoneType WBFLGENERICBRIDGEFUNC GetControlPoints(Float64 Xs, Float64 Ls, const std::array<Float64, 4>& X, const std::array<Float64, 4>& Y, Float64* pXl, Float64* pYl, Float64* pXr, Float64* pYr);
void WBFLGENERICBRIDGEFUNC GetEndBlockWidth(Float64 Xs, Float64 Ls, SectionBias sectionBias, IPrecastBeam* pBeam, const std::array<Float64,2>& ebWidth, const std::array<Float64, 2>& ebLength, const std::array<Float64, 2>& ebTransLength,Float64* pWtop, Float64* pWbot);
void WBFLGENERICBRIDGEFUNC AdjustForEndBlocks(IPrecastBeam* pBeam, Float64 Wt, Float64 Wb);
void WBFLGENERICBRIDGEFUNC AdjustForVariableDepth(IPrecastBeam* pBeam, Float64 Hg,Float64 Hbf);

void WBFLGENERICBRIDGEFUNC GetEndBlockWidth(Float64 Xs, Float64 Ls, SectionBias sectionBias, INUBeam* pBeam, const std::array<Float64, 2>& ebWidth, const std::array<Float64, 2>& ebLength, const std::array<Float64, 2>& ebTransLength, Float64* pWeb);
void WBFLGENERICBRIDGEFUNC AdjustForEndBlocks(INUBeam* pBeam, Float64 Web);
void WBFLGENERICBRIDGEFUNC AdjustForVariableDepth(INUBeam* pBeam, Float64 Hg, Float64 Hbf);
Float64 WBFLGENERICBRIDGEFUNC ComputeTopFlangeThickening(Float64 Xs, Float64 Ls, ThickeningType thickeningType, Float64 tft);
Float64 WBFLGENERICBRIDGEFUNC ComputePrecamber(Float64 Xs, Float64 Ls, Float64 precamber);

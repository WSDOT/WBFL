///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2011  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_GENERICBRIDGEHELPERS_H_
#define INCLUDED_GENERICBRIDGEHELPERS_H_

#pragma once

#include "WBFLGenericBridge.h"

#define MAX_GIRDERLINES 1000

// Pier ID = -1(pierIdx+1)(PIER_ID_OFFSET)
// Girder Point ID = -1[(pierIdx+1)(PIER_ID_OFFSET) + (gdrIdx+1)(GIRDER_ID_OFFSET) + (0|1)LOCATION_OFFSET + (0|1)SIDE_OFFSET]
// Location -> CL Girder - CL Pier, 0
//          -> CL Girder - CL Brg,  1
// Side     -> Back/Behind,         0
//          -> Ahead                1
#define BRIDGE_ID_OFFSET 10000000  // cl-pier, cl-bridge point
#define PIER_ID_OFFSET     100000  // cl-pier, alignment point
#define GIRDER_ID_OFFSET      100
#define LOCATION_OFFSET        10
#define SIDE_OFFSET             1

extern const long g_AlignmentKey;
extern const long g_CLBridgeKey;

HRESULT GB_GetPierGirderPointId(PierIndexType pierIdx,GirderIndexType gdrIdx,PositionType posType,long* pVal);
HRESULT GB_GetBearingGirderPointId(PierIndexType pierIdx,GirderIndexType gdrIdx,PositionType posType,long* pVal);
HRESULT GB_GetGirderLineId(SpanIndexType spanIdx,GirderIndexType gdrIdx,long* pVal);
HRESULT GB_GetPierAlignmentPointId(PierIndexType pierIdx,long* pVal);
HRESULT GB_GetPierCLBridgePointId(PierIndexType pierIdx,long* pVal);
HRESULT GB_GetPierEndPoints(IGenericBridge* bridge,PierIndexType pierIdx,IPoint2d* *left,IPoint2d* *right);

//long GB_GetGirderLineIndex(IGenericBridge* pBridge,ISuperstructureMemberCollection* members);

// function to deal with fractional and absolute values
enum FracRes {frTooSmall, frTooBig};
Float64 GB_GetFracDistance(Float64 fracLoc, Float64 Length, bool ignoreTooBig=false); // throw FracRes

#endif // INCLUDED_GENERICBRIDGEHELPERS_H_
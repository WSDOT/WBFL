///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_HELPERS_H_
#define INCLUDED_HELPERS_H_


#include "WBFLGenericBridge.h"

HRESULT GetGirderSectionBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,IGirderSection** section);
HRESULT GetGirderHaunchBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,Float64* pHaunch);
HRESULT GetAlignment(IGenericBridge* bridge,IAlignment** alignment);
Float64 DistanceToStation(IGenericBridge* bridge,Float64 distFromStartOfBridge);
Float64 StationToDistance(IGenericBridge* bridge,Float64 station);
void GetPiers(IGenericBridge* bridge,Float64 station,PierIndexType* pPrevPier,PierIndexType* pNextPier);

#endif // INCLUDED_HELPERS_H_
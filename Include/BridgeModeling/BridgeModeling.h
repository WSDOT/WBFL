///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEMODELING_BRIDGEMODELING_H_
#define INCLUDED_BRIDGEMODELING_BRIDGEMODELING_H_
#pragma once

// Master include file for clients of the Bridge Modeling Framework

#if defined(BUILDBMFLIB)
	#error Do not use this header file in the Bridge Modeling Framework Package
   #error It is for external users only
#endif

#include <WBFLCogo.h>

#include <BridgeModeling\BmfTypes.h>
#include <BridgeModeling\Bridge.h>
#include <BridgeModeling\BundlePattern.h>
#include <BridgeModeling\CompGirderSection.h>
#include <BridgeModeling\ConcGirderSection.h>
#include <BridgeModeling\Connection.h>
#include <BridgeModeling\Girder.h>
#include <BridgeModeling\GirderPath.h>
#include <BridgeModeling\GirderSection.h>
#include <BridgeModeling\GirderShape.h>
#include <BridgeModeling\GirderTemplate.h>
#include <BridgeModeling\GirderProfile.h>
#include <BridgeModeling\EndBlockGirderProfile.h>
#include <BridgeModeling\IGirderSection.h>
#include <BridgeModeling\Pier.h>
#include <BridgeModeling\PierFactory.h>
#include <BridgeModeling\PierLayout.h>
#include <BridgeModeling\PrecastGirder.h>
#include <BridgeModeling\PrecastGirderSection.h>
#include <BridgeModeling\PrecastGirderTemplate.h>
#include <BridgeModeling\SplicedGirderTemplate.h>
#include <BridgeModeling\SplicedGirder.h>
#include <BridgeModeling\Slab.h>
#include <BridgeModeling\Span.h>
#include <BridgeModeling\SpanFactory.h>
#include <BridgeModeling\StrandPattern.h>
#include <BridgeModeling\TrafficBarrier.h>
#include <BridgeModeling\TrafficBarrierTemplate.h>
#include <BridgeModeling\XBridgeModel.h>

#endif // INCLUDED_BRIDGEMODELING_BRIDGEMODELING_H_
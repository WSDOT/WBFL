///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#include <BridgeAnalysis\BridgeAnalysisLib.h>
#include <BridgeAnalysis\LoadImp.h>
#include <BridgeAnalysis\LoaderImp.h>
#include <BridgeAnalysis\BridgeModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bamConcForceYImp::bamConcForceYImp(Int32 elementId,
                           bamElementType type,
                           Float64 location,
                           Float64 p,
                           bool isFractional,
                           bamLoadDirection direction) :
bamConcForceY(elementId,type,location,p,isFractional,direction)
{
}
 
bamConcForceYImp::~bamConcForceYImp()
{
}

bamLoader* bamConcForceYImp::CreateLoader()
{
   bamBridgeModel& pfbm = GetLoadCase().GetBridgeModel();
   bamBridgeModelImp& bm = dynamic_cast<bamBridgeModelImp&>(pfbm);
   return new bamConcForceYLoaderImp(&bm,this);
}

///////////////////////////////////////////////////////////////////////

bamUnifForceYImp::bamUnifForceYImp(Int32 elementId,
                           bamElementType type,
                           Float64 start,
                           Float64 end,
                           Float64 w,
                           bool isFractional,
                           bamLoadDirection direction) :
bamUnifForceY(elementId,type,start,end,w,isFractional,direction)
{
}

bamUnifForceYImp::~bamUnifForceYImp()
{
}

bamLoader* bamUnifForceYImp::CreateLoader()
{
   bamBridgeModel& pfbm = GetLoadCase().GetBridgeModel();
   bamBridgeModelImp& bm = dynamic_cast<bamBridgeModelImp&>(pfbm);
   return new bamUnifForceYLoaderImp(&bm,this);
}

///////////////////////////////////////////////////////////////////////

bamConcMomentZImp::bamConcMomentZImp(Int32 elementId,
                                     bamElementType type,
                                     Float64 location,
                                     Float64 m,
                                     bool isFractional) :
bamConcMomentZ(elementId,type,location,m,isFractional)
{
}
 
bamConcMomentZImp::~bamConcMomentZImp()
{
}

bamLoader* bamConcMomentZImp::CreateLoader()
{
   bamBridgeModel& pfbm = GetLoadCase().GetBridgeModel();
   bamBridgeModelImp& bm = dynamic_cast<bamBridgeModelImp&>(pfbm);
   return new bamConcMomentZLoaderImp(&bm,this);
}

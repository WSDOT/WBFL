///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
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

#include <BridgeAnalysis\BridgeAnalysisLib.h>
//////////////////X////////////////////X/////////////////////////////////////
// NAME:          bamLoadFactory           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeAnalysis\LoadFactoryImp.h>
#include <BridgeAnalysis\LoadImp.h>
#include <BridgeAnalysis\BridgeModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bamLoadFactoryImp::bamLoadFactoryImp(bamBridgeModel* pModel) :
bamLoadFactory(pModel)
{
} // bamLoadFactory

bamLoadFactoryImp::~bamLoadFactoryImp()
{
} // ~bamLoadFactory

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bamLoad* bamLoadFactoryImp::DoCreateConcForceY(IDType elementId,
                                          bamElementType type,
                                          Float64 location,
                                          Float64 p,
                                          bool isFractional,
                                          bamLoadDirection direction)
{
   return new bamConcForceYImp(elementId,
                           type,
                           location,
                           p,
                           isFractional,
                           direction);
} // DoCreateConcForceY

bamLoad* bamLoadFactoryImp::DoCreateUnifForceY(IDType elementId,
                                          bamElementType type,
                                          Float64 start,
                                          Float64 end,
                                          Float64 w,
                                          bool isFractional,
                                          bamLoadDirection direction)
{
   return new bamUnifForceYImp(elementId,
                           type,
                           start,
                           end,
                           w,
                           isFractional,
                           direction);
} // DoCreateUnifForceY

bamLoad* bamLoadFactoryImp::DoCreateConcMomentZ(IDType elementId,
                                                bamElementType type,
                                                Float64 location,
                                                Float64 m,
                                                bool isFractional)
{
   return new bamConcMomentZImp(elementId,type,location,m,isFractional);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY ==========================================

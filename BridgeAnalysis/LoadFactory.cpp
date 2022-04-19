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

#include <BridgeAnalysis\LoadFactory.h>
#include <BridgeAnalysis\BridgeModel.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bamLoadFactory::bamLoadFactory(bamBridgeModel* pModel)
{
   m_pModel = pModel;
} // bamLoadFactory

bamLoadFactory::~bamLoadFactory()
{
} // ~bamLoadFactory

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
CollectionIndexType bamLoadFactory::CreateConcForceY(IDType loadCaseId,
                                     IDType elementId,
                                     bamElementType type,
                                     Float64 location,
                                     Float64 p,
                                     bool isFractional,
                                     bamLoadDirection direction)
{
   PRECONDITION( !(location < 0) );
   PRECONDITION( isFractional ? (0.0 <= location && location <= 1.0) : true );

   return m_pModel->AddLoad(loadCaseId,
                            DoCreateConcForceY(elementId,
                                               type,
                                               location,
                                               p,
                                               isFractional,
                                               direction)
                            );
} // CreateConcForceY

CollectionIndexType bamLoadFactory::CreateUnifForceY(IDType loadCaseId,
                                     IDType elementId,
                                     bamElementType type,
                                     Float64 start,
                                     Float64 end,
                                     Float64 w,
                                     bool isFractional,
                                     bamLoadDirection direction)
{
   PRECONDITION( !(start < 0) );
   PRECONDITION( !(end < 0) );
   PRECONDITION( start < end || IsEqual(start,end) );
   PRECONDITION( isFractional ? (0.0 < start && start < 1.0) || IsZero(start) || IsEqual(start,1.0) : true );
   PRECONDITION( isFractional ? (0.0 < end && end < 1.0) || IsZero(end) || IsEqual(end,1.0) : true );

   return m_pModel->AddLoad(loadCaseId,
                            DoCreateUnifForceY(elementId,
                                               type,
                                               start,
                                               end,
                                               w,
                                               isFractional,
                                               direction)
                            );
} // CreateUnifForceY

CollectionIndexType bamLoadFactory::CreateConcMomentZ(IDType loadCaseId,
                                        IDType elementId,
                                        bamElementType type,
                                        Float64 location,
                                        Float64 m,
                                        bool isFractional)
{
   PRECONDITION( !(location < 0) );
   PRECONDITION( isFractional ? (0.0 <= location && location <= 1.0) : true );

   return m_pModel->AddLoad(loadCaseId,
                            DoCreateConcMomentZ(elementId,
                                                type,
                                                location,
                                                m,
                                                isFractional)
                            );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY ==========================================

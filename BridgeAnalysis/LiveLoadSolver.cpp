///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
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

#include <BridgeAnalysis\BridgeAnalysisLib.h>
#include <BridgeAnalysis\LiveLoadSolver.h>
#include <BridgeAnalysis\BridgeModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bamLiveLoadSolver::bamLiveLoadSolver()
{
   m_pBridgeModel = 0;
}

bamLiveLoadSolver::~bamLiveLoadSolver()
{
}

void bamLiveLoadSolver::SetBridgeModel(bamBridgeModel* pModel)
{
   m_pBridgeModel = pModel;
}

void bamLiveLoadSolver::WriteSectionResults(const bamSectionResultsKey& key, const bamSectionResults& sr)
{
   m_pBridgeModel->WriteSectionResults( key, sr );
}

bamSectionResults bamLiveLoadSolver::ReadSectionResults(const bamSectionResultsKey& key)
{
   return m_pBridgeModel->ReadSectionResults( key );
}

void bamLiveLoadSolver::WriteSectionStress(const bamSectionStressKey& key,const bamSectionStress& ss)
{
   m_pBridgeModel->WriteSectionStress( key, ss );
}

bamSectionStress bamLiveLoadSolver::ReadSectionStress(const bamSectionStressKey& key)
{
   return m_pBridgeModel->ReadSectionStress( key );
}

void bamLiveLoadSolver::WriteReaction( const bamReactionKey& key, const bamReaction& reaction )
{
   m_pBridgeModel->WriteReaction( key, reaction );
}

bamReaction bamLiveLoadSolver::ReadReaction( const bamReactionKey& key )
{
   return m_pBridgeModel->ReadReaction( key );
}

///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_BRUTEFORCESOLVER_H_
#define INCLUDED_BRIDGEANALYSIS_BRUTEFORCESOLVER_H_
#pragma once

#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\LiveLoadSolver.h>


class BAMCLASS bamBruteForceSolver : public bamLiveLoadSolver
{
public:
   bamBruteForceSolver();
   virtual ~bamBruteForceSolver();

   virtual void Solve(bamLiveLoad& ll);
   virtual void Solve(bamLiveLoad& ll,PoiIDType poi);
   virtual void SolveStress(bamLiveLoad& ll,PoiIDType poi,CollectionIndexType spid);

private:
   void SolveReactions(bamLiveLoad& ll);

#if defined _DEBUG
   static dbgFileDumpContext ms_Log;
#endif
};

#endif // INCLUDED_BRIDGEANALYSIS_BRUTEFORCESOLVER_H_
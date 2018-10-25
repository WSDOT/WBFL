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

#ifndef INCLUDED_BRIDGEANALYSIS_H_
#define INCLUDED_BRIDGEANALYSIS_H_
#pragma once

// Master include file for clients of the Bridge Analysis Framework

#if defined(BUILDBAMLIB)
	#error Do not use this header file in the Bridge Analysis Framework Package
   #error It is for external users only
#endif

#include <BridgeAnalysis\AnalysisResultsManager.h>
#include <BridgeAnalysis\AxleSpacing.h>
#include <BridgeAnalysis\BridgeModel.h>
#include <BridgeAnalysis\BruteForceSolver.h>
#include <BridgeAnalysis\Envelope.h>
#include <BridgeAnalysis\LinearLoadCombination.h>
#include <BridgeAnalysis\LiveLoad.h>
#include <BridgeAnalysis\LiveLoadSolver.h>
#include <BridgeAnalysis\LoadCase.h>
#include <BridgeAnalysis\LoadCombination.h>
#include <BridgeAnalysis\Loader.h>
#include <BridgeAnalysis\LoadFactory.h>
#include <BridgeAnalysis\LrfdLoadCombination.h>
#include <BridgeAnalysis\LoadImp.h>
#include <BridgeAnalysis\LoaderImp.h>
#include <BridgeAnalysis\LoadFactoryImp.h>
#include <BridgeAnalysis\OptimumLoadCombination.h>
#include <BridgeAnalysis\PointOfInterest.h>
#include <BridgeAnalysis\Reaction.h>
#include <BridgeAnalysis\SectionResults.h>
#include <BridgeAnalysis\SectionStress.h>
#include <BridgeAnalysis\SimpleResultsManager.h>
#include <BridgeAnalysis\TransientLdEnvelope.h>
#include <BridgeAnalysis\Truck.h>
#include <BridgeAnalysis\StagedLoadCombination.h>

#endif // INCLUDED_BRIDGEANALYSIS_H_
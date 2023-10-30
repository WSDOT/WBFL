///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam formula, patterned after Roark's formulas
//         for Stress and Strain
// Copyright © 1999-2023  Washington State Department of Transportation
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


// This is a master include file for the Roark Beam Package
#if defined(BUILDROARK)
#error Do not use this header file in the Roark Beam Package
#error It is for external users only
#endif


#include <Roark/BeamWithEqualOverhangsUniformLoad.h>
#include <Roark/BeamWithUnequalOverhangsUniformLoad.h>
#include <Roark/CompositeBeam.h>
#include <Roark/PPIntermediateCouple.h>
#include <Roark/PPIntermediateLoad.h>
#include <Roark/PPPartialUniformLoad.h>
#include <Roark/RoarkBeam.h>

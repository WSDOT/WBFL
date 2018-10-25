///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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

#ifndef INCLUDED_HELPER_H_
#define INCLUDED_HELPER_H_

#include <WBFLUnitServer.h>
#include "RCSolution.h"
#include "RCSolutionEx.h"

Float64 Alpha1(Float64 fc,IUnitServer* pUnitServer,SpecUnitType unitType);
Float64 Beta1(Float64 fc,IUnitServer* pUnitServer,SpecUnitType unitType);
Float64 GetStrain(Float64 ec,Float64 d,Float64 c,Float64 fpe,Float64 Eps);
void CreateSolution(Float64 Mn,Float64 c,Float64 fps,Float64 Cflange,Float64 Cweb,Float64 T,Float64 Yflange,Float64 Yweb,VARIANT_BOOL bIsOverReinforced,IRCSolution** solution);
void CreateSolution(Float64 Mn,Float64 c,IDblArray* fs,IDblArray* fps,Float64 Cflange,Float64 Cbeam,Float64 T,Float64 Yflange,Float64 Yweb,IRCSolutionEx** solution);
void CreateSolution(Float64 Mn,Float64 c,IDblArray* fs,IDblArray* fps,Float64 Cflange,Float64 Cbeam,Float64 T,Float64 Yflange,Float64 Yweb,Float64 beta1,IRCSolutionEx** solution);
void CopySolution(IRCSolutionEx* solution_ex,IRCSolution** solution);
void RCBeamToRCBeam2Ex(IRCBeam* rcbeam,IRCBeam2Ex** rcbeam2);
void RCBeam2ToRCBeam2Ex(IRCBeam2* rcbeam,IRCBeam2Ex** rcbeam2);

#endif // INCLUDED_HELPER_H_
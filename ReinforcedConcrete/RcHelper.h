///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#ifndef INCLUDED_RCHELPER_H_
#define INCLUDED_RCHELPER_H_
#pragma once

#include <GeometricPrimitives\Primitives.h>
#include <GeometricPrimitives\Line2d.h>
#include <GeometricPrimitives\GeomOp2d.h>
#include <ReinforcedConcrete\CapacityProblem.h>
#include <ReinforcedConcrete\CapacitySolution.h>
#include <Material\Concrete.h>
#include <MathEx.h>

//------------------------------------------------------------------------
// conversion routines for transforming back and forth between global (na)
// coordinates and plastic centroid coordinates
void Na2PcCoords(const gpPoint2d& pc, const gpLine2d& na, 
                 Float64* d, Float64* theta);

void PcCoords2Na(const gpPoint2d& pc, Float64 d, 
                 Float64 theta, gpLine2d* na);

bool IsZeroCapacityProblem(rcaCapacityProblem& problem);
rcaCapacitySolution MakeZeroCapacitySolution(rcaCapacityProblem& problem);

#endif // INCLUDED_RCHELPER_H_
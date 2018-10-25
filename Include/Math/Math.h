///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#ifndef INCLUDED_MATH_MATH_H_
#define INCLUDED_MATH_MATH_H_
#pragma once

// This is a master include file for the Math Package
#if defined(BUILDMATHLIB)
	#error Do not use this header file in the Math Package
   #error It is for external users only
#endif

#include <Math\BrentsRootFinder2d.h>
#include <Math\BisectionRootFinder2d.h>
#include <Math\CoordMapper1d.h>
#include <Math\Function2d.h>
#include <Math\LinFunc2d.h>
#include <Math\QuadraticSolver.h>
#include <Math\CubicSolver.h>
#include <Math\RootFinder2d.h>
#include <Math\PwLinearFunction2d.h>
#include <Math\PwLinearFunction2dUsingPoints.h>
#include <Math\FixedPointIteration.h>
#include <Math\NumericIntegrator2d.h>
#include <Math\TrapezoidalRuleIntegrator.h>

#endif // INCLUDED_MATH_MATH_H_
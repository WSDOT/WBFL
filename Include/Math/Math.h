///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <Math\BisectionRootFinder.h>
#include <Math\BrentsRootFinder.h>
#include <Math\CDRatio.h>
#include <Math\CompositeFunction.h>
#include <Math\CoordMapper1d.h>
#include <Math\CubicSolver.h>
#include <Math\FixedPointIteration.h>
#include <Math\Function.h>
#include <Math\LinearFunction.h>
#include <Math\MathUtils.h>
#include <Math\NumericIntegration.h>
#include <Math\PolynomialFunction.h>
#include <Math\PiecewiseFunction.h>
#include <Math\QuadraticSolver.h>
#include <Math\Range.h>
#include <Math\RootFinder.h>
#include <Math\TrapezoidalRuleIntegrator.h>
#include <Math\UnsymmetricBandedMatrix.h>
#include <Math\XFixedPointIteration.h>
#include <Math\XFunction.h>
#include <Math\XNumericIntegration.h>
#include <Math\XRootFinder.h>

#endif // INCLUDED_MATH_MATH_H_
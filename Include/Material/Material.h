///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#ifndef INCLUDED_MATERIAL_MATERIAL_H_
#define INCLUDED_MATERIAL_MATERIAL_H_
#pragma once

// This is a master include file for the Material Modeling Package
#if defined(BUILDMATLIB)
	#error Do not use this header file in the Material Modeling Package
   #error It is for external users only
#endif

#include <Material\Concrete.h>
#include <Material\ConcreteEx.h>
#include <Material\ConcreteListener.h>
#include <Material\LinearStressStrainCurve.h>
#include <Material\Metal.h>
#include <Material\MetalListener.h>
#include <Material\PsStrand.h>
#include <Material\PsStrandCurve.h>
#include <Material\Rebar.h>
#include <Material\StressStrainCurve.h>
#include <Material\YieldStressStrainCurve.h>

#endif // INCLUDED_MATERIAL_MATERIAL_H_
///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifndef INCLUDED_WBFL_H_
#define INCLUDED_WBFL_H_
#pragma once

//#pragma warning ( disable : 4231 4251 4786 )
#pragma warning( disable : 4251 )

// This is a master include file for WBFL.
#if defined(WBFL)
	#error Do not use this header file in any WBFL Files!!!
   #error It is for external users only
#endif

#include <WbflTypes.h>

#include <System\System.h>

#if defined USE_WBFL_DEPRECIATED
#include <Cogo\Cogo.h>
#include <BridgeAnalysis\BridgeAnalysis.h>
#include <BridgeModeling\BridgeModeling.h>
#endif // USE_WBFL_DEPRECIATED

#include <EngTools\EngTools.h>
#include <GeometricPrimitives\GeometricPrimitives.h>
#include <GeomModel\GeomModel.h>
#include <GraphicsLib\GraphicsLib.h>
#include <LibraryFw\LibraryFw.h>
#include <LRFD\LRFD.h>
#include <Material\Material.h>
#include <Math\Math.h>
#include <ReinforcedConcrete\ReinforcedConcrete.h>
#include <Reporter\Reporter.h>
#include <UnitMgt\UnitMgt.h>
#include <Units\Units.h>

#endif // INCLUDED_WBFL_H_

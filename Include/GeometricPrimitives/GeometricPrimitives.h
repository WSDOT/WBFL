///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#ifndef INCLUDED_GEOMETRY_GEOMETRY_H_
#define INCLUDED_GEOMETRY_GEOMETRY_H_
#pragma once

// This is a master include file for the Geometric Primitives Package
#if defined(BUILDGEOMLIB)
	#error Do not use this header file in the Geometric Primitives Package
   #error It is for external users only
#endif

#include <GeometricPrimitives\GeomOp2d.h>
#include <GeometricPrimitives\Line2d.h>
#include <GeometricPrimitives\LineSegment2d.h>
#include <GeometricPrimitives\Polygon2d.h>
#include <GeometricPrimitives\Primitives.h>
#include <GeometricPrimitives\Vector2d.h>


#endif // INCLUDED_GEOMETRY_GEOMETRY_H_

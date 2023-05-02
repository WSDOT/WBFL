///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

// This is a master include file for the CoordGeom package
#if defined(BUILDCOORDGEOMLIB)
	#error Do not use this header file in the CoordGeom Package
   #error It is for external users only
#endif

#include <CoordGeom/Alignment.h>
#include <CoordGeom/Angle.h>
#include <CoordGeom/CircularCurve.h>
#include <CoordGeom/CompoundCurve.h>
#include <CoordGeom/CoordGeomTypes.h>
#include <CoordGeom/CubicSpline.h>
#include <CoordGeom/Direction.h>
#include <CoordGeom/Model.h>
#include <CoordGeom/Path.h>
#include <CoordGeom/PathElement.h>
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/Profile.h>
#include <CoordGeom/ProfileSegment.h>
#include <CoordGeom/ProfilePoint.h>
#include <CoordGeom/ProfileSegment.h>
#include <CoordGeom/Station.h>
#include <CoordGeom/StationEquation.h>
#include <CoordGeom/Superelevation.h>
#include <CoordGeom/Surface.h>
#include <CoordGeom/SurfacePoint.h>
#include <CoordGeom/SurfaceProfile.h>
#include <CoordGeom/SurfaceTemplate.h>
#include <CoordGeom/SurfaceTemplateSegment.h>
#include <CoordGeom/TransitionCurve.h>
#include <CoordGeom/Utilities.h>
#include <CoordGeom/VerticalCurve.h>
#include <CoordGeom/Widening.h>
#include <CoordGeom/XCoordGeom.h>

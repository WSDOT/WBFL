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
#include <CoordGeom/CircularCurve.h>
#include <CoordGeom/PathElement.h>
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/ProfileElement.h>
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
#include <CoordGeom/UnitTest.h>
#include <CoordGeom/VerticalCurve.h>
#include <CoordGeom/Widening.h>
#include <CoordGeom/XCoordGeom.h>
#include <CoordGeom/Profile.h>
#include <CoordGeom/Direction.h>
#include <CoordGeom/Angle.h>
#include <CoordGeom/CompoundCurve.h>
#include <CoordGeom/CubicSpline.h>
#include <CoordGeom/Model.h>
#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/Path.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/CoordGeomTypes.h>
#include <CoordGeom/AlignmentOffsetLayoutLineFactory.h>
#include <CoordGeom/DiaphragmLineFactory.h>
#include <CoordGeom/GirderLineFactory.h>
#include <CoordGeom/SinglePierLineFactory.h>
#include <CoordGeom/SingleGirderLineFactory.h>
#include <CoordGeom/SimpleLayoutLineFactory.h>
#include <CoordGeom/SimpleGirderLineFactory.h>
#include <CoordGeom/PierLineFactory.h>
#include <CoordGeom/LayoutLineFactory.h>
#include <CoordGeom/UniformSpacingLayoutLineFactory.h>
#include <CoordGeom/ConnectionGeometry.h>
#include <CoordGeom/ThroughPointDiaphragmLineFactory.h>
#include <CoordGeom/SingleDiaphragmLineFactory.h>
#include <CoordGeom/EqualSpacingDiaphragmLineFactory.h>
#include <CoordGeom/CoordGeom.h>
#include <CoordGeom/CompositePierLineFactory.h>
#include <CoordGeom/CompositeLayoutLineFactory.h>
#include <CoordGeom/CompositeGirderLineFactory.h>
#include <CoordGeom/CompositeDiaphragmLineFactory.h>
#include <CoordGeom/GirderLine.h>
#include <CoordGeom/DiaphragmLine.h>
#include <CoordGeom/BridgeFramingGeometry.h>
#include <CoordGeom/PierLine.h>
#include <CoordGeom/DeckBoundaryFactory.h>
#include <CoordGeom/DeckBoundary.h>
#include <CoordGeom/SimpleDeckBoundaryFactory.h>
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/UnitTest.h>

#include <CoordGeom/Utilities.h>
#include <CoordGeom/Angle.h>
#include <CoordGeom/Direction.h>
#include <CoordGeom/Model.h>
#include <CoordGeom/CircularCurve.h>
#include <CoordGeom/TransitionCurve.h>
#include <CoordGeom/CompoundCurve.h>
#include <CoordGeom/CubicSpline.h>
#include <CoordGeom/StationEquation.h>
#include <CoordGeom/Station.h>
#include <CoordGeom/ProfilePoint.h>
#include <CoordGeom/ProfileSegment.h>
#include <CoordGeom/VerticalCurve.h>
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/Path.h>
#include <CoordGeom/Alignment.h>
#include <CoordGeom/Profile.h>
#include <CoordGeom/SurfacePoint.h>
#include <CoordGeom/SurfaceTemplate.h>
#include <CoordGeom/SurfaceProfile.h>
#include <CoordGeom/SurfaceTemplateSegment.h>
#include <CoordGeom/Superelevation.h>
#include <CoordGeom/Widening.h>
#include <CoordGeom/Surface.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool WBFL::COGO::UnitTest::TestMe(WBFL::Debug::Log& rlog)
{
   bool tst = true;

#if defined _UNITTEST
   tst &= Utilities::TestMe(rlog);
   tst &= Angle::TestMe(rlog);
   tst &= Direction::TestMe(rlog);
   tst &= Model::TestMe(rlog);
   tst &= CircularCurve::TestMe(rlog);
   tst &= TransitionCurve::TestMe(rlog);
   tst &= CompoundCurve::TestMe(rlog);
   tst &= CubicSpline::TestMe(rlog);
   tst &= StationEquation::TestMe(rlog);
   tst &= Station::TestMe(rlog);
   tst &= ProfilePoint::TestMe(rlog);
   tst &= ProfileSegment::TestMe(rlog);
   tst &= VerticalCurve::TestMe(rlog);

   tst &= PathSegment::TestMe(rlog);
   tst &= Path::TestMe(rlog);
   tst &= Alignment::TestMe(rlog);
   tst &= Profile::TestMe(rlog);
   tst &= SurfacePoint::TestMe(rlog);

   tst &= SurfaceTemplate::TestMe(rlog);
   tst &= SurfaceProfile::TestMe(rlog);
   tst &= SurfaceTemplateSegment::TestMe(rlog);
   tst &= Superelevation::TestMe(rlog);
   tst &= Widening::TestMe(rlog);
   tst &= Surface::TestMe(rlog);

#endif

   return tst;
}

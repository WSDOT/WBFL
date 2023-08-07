///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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


#include <EngTools/EngToolsLib.h>
#include <EngTools/BiaxialBeamStrain.h>        // class implementation
#include <GeomModel/Vector2d.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/Primitives3d.h>

using namespace WBFL::EngTools;
using namespace WBFL::Geometry;

BiaxialBeamStrain::BiaxialBeamStrain(Float64 strain)
{
   SetStrainPlane(strain);
}

BiaxialBeamStrain::BiaxialBeamStrain(const Point2d& p1, Float64 s1, 
                                     const Point2d& p2, Float64 s2,
                                     const Point2d& p3, Float64 s3)
{
   SetStrainPlane( p1, s1, p2, s2, p3, s3);
}

BiaxialBeamStrain::BiaxialBeamStrain(const Line2d& rnaLine, const Point2d& p3,Float64 strain)
{
   SetStrainPlane(rnaLine, p3, strain);
}

BiaxialBeamStrain::BiaxialBeamStrain(const Line2d& rnaLine, Float64 dist, Float64 strain)
{
   SetStrainPlane(rnaLine, dist, strain);
}

Float64 BiaxialBeamStrain::GetAxialStrain(const Point2d& pnt) const
{
   return GetAxialStrain(pnt.X(), pnt.Y());
}

Float64 BiaxialBeamStrain::GetAxialStrain(Float64 x, Float64 y) const
{
   return m_Plane.GetZ(x, y);
}


bool BiaxialBeamStrain::GetXStrainLocation(Float64 Strain, Float64 Y, Float64& X) const
{
   try
   {
      X = m_Plane.GetX(Y, Strain);
      return true;
   }
   catch(...)
   {
      X = -99999999;
      return false;
   }
}

bool BiaxialBeamStrain::GetYStrainLocation(Float64 Strain, Float64 X, Float64& Y) const
{
   try
   {
      Y = m_Plane.GetY(X, Strain);
      return true;
   }
   catch (...)
   {
      Y = -999999999;
      return false;
   }
}

void BiaxialBeamStrain::SetStrainPlane(const Line2d& rnaLine,const Point2d& p3,Float64 strain)
{
   // get two points on the line
   auto [p1,tv] = rnaLine.GetExplicit();
   auto p2 = p1.OffsetBy(tv.X(), tv.Y());

   SetStrainPlane(p1, 0., p2, 0., p3, strain);
}

void BiaxialBeamStrain::SetStrainPlane(const Point2d& p1, Float64 s1, 
                                       const Point2d& p2, Float64 s2,
                                       const Point2d& p3, Float64 s3)
{
   Update(p1, s1, p2, s2, p3, s3);
}

void BiaxialBeamStrain::SetStrainPlane(const Line2d& rnaLine, Float64 dist, Float64 strain)
{
   // get location of some p3
   Line2d tl = rnaLine.Parallel(dist,Line2d::Side::Left);
   auto [p3,tv] = tl.GetExplicit();  // get a point along offset line

   SetStrainPlane(rnaLine, p3, strain);
}

void BiaxialBeamStrain::SetStrainPlane(Float64 strain)
{
   m_Plane.ThroughAltitude(strain);
}

void BiaxialBeamStrain::Update(const Point2d& p1, Float64 s1, 
                               const Point2d& p2, Float64 s2,
                               const Point2d& p3, Float64 s3)
{
   m_Plane.ThroughPoints(Point3d(p1, s1), Point3d(p2, s2), Point3d(p3, s3));
}

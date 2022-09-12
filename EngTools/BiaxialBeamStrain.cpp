///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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


#include <EngTools/EngToolsLib.h>
#include <EngTools/BiaxialBeamStrain.h>        // class implementation
#include <GeomModel/Vector2d.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/Primitives3d.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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


Float64 BiaxialBeamStrain::GetXStrainLocation(Float64 Strain, Float64 Y, bool& Success) const
{
   try
   {
      Success = true;
      return m_Plane.GetX(Y, Strain);
   }
   catch(...)
   {
      Success = false;
      return 0;
   }
}

Float64 BiaxialBeamStrain::GetYStrainLocation(Float64 Strain, Float64 X, bool& Success) const
{
   try
   {
      Success = true;
      return m_Plane.GetY(X, Strain);
   }
   catch (...)
   {
      Success = false;
      return 0;
   }
}

void BiaxialBeamStrain::SetStrainPlane(const Line2d& rnaLine,const Point2d& p3,Float64 strain)
{
   // get two points on the line
   Point2d  p1, p2;
   Vector2d tv;
   rnaLine.GetExplicit(&p1, &tv);
   p2 = p1.OffsetBy(tv.X(), tv.Y());

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
   Point2d  p3;
   Vector2d tv;
   tl.GetExplicit(&p3, &tv);  // get a point along offset line

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

#if defined _DEBUG
bool BiaxialBeamStrain::AssertValid() const
{
   return m_Plane.AssertValid();
}

void BiaxialBeamStrain::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for BiaxialBeamStrain" << WBFL::Debug::endl;
   m_Plane.Dump(os);
}

#endif // _DEBUG

#if defined _UNITTEST
bool BiaxialBeamStrain::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("BiaxialBeamStrain");

   Point2d p1(1,2), p2(3,1), p3(3,4);
   Line2d naline(p1,p2);
   BiaxialBeamStrain bs(naline, p3, .2);

   bool flag;
   Point2d tp1(4,4), tp2(-4,-4);
   TRY_TESTME(IsEqual(bs.GetAxialStrain(tp1), .2333, .001));
   TRY_TESTME(IsEqual(bs.GetAxialStrain(tp2),-.56667,.001));
   TRY_TESTME(IsEqual(bs.GetXStrainLocation(-.56667,-4.,flag),-4.,.001));
   TRY_TESTME(IsEqual(bs.GetYStrainLocation(0.23333, 4.,flag), 4.,.001));

   // flip line around and test again
   naline.ThroughPoints(p2,p1);
   bs.SetStrainPlane(naline, p3, .2);
   TRY_TESTME(IsEqual(bs.GetAxialStrain(tp1),.2333,.001));
   TRY_TESTME(IsEqual(bs.GetAxialStrain(tp2),-.56667,.001));
   TRY_TESTME(IsEqual(bs.GetXStrainLocation(-.56667,-4.,flag),-4.,.001));
   TRY_TESTME(IsEqual(bs.GetYStrainLocation(0.23333, 4., flag), 4., .001));

   TESTME_EPILOG("BiaxialBeamStrain");
}

#endif // _UNITTEST



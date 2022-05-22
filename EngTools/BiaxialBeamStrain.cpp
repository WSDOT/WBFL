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


#include <EngTools\EngToolsLib.h>
#include <Engtools\BiaxialBeamStrain.h>        // class implementation
#include <GeomModel\Line2d.h>
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

BiaxialBeamStrain::BiaxialBeamStrain(const Line2d& rnaLine,
                                         const Point2d& p3,Float64 strain)
{
   SetStrainPlane(rnaLine, p3, strain);
}

BiaxialBeamStrain::BiaxialBeamStrain(const Line2d& rnaLine,
                                         Float64 dist, Float64 strain)
{
   SetStrainPlane(rnaLine, dist, strain);
}

BiaxialBeamStrain::~BiaxialBeamStrain()
{
}

Float64 BiaxialBeamStrain::GetAxialStrain(const Point2d& pnt) const
{
   return GetAxialStrain(pnt.X(), pnt.Y());
}

Float64 BiaxialBeamStrain::GetAxialStrain(Float64 x, Float64 y) const
{
   Float64 f;

   if (m_bIsConstantStrain)
      f = m_A;
   else if ( IsZero(m_C) )
      f = Float64_Max;
   else
      f = (m_A*x + m_B*y + m_D)/(-m_C);

   return f;
}


Float64 BiaxialBeamStrain::GetXStrainLocation(Float64 Strain, Float64 Y, bool& Success) const
{
   if ( IsZero(m_A) || m_bIsConstantStrain )
   {
      Success = false;
      return 0;
   }
   else
   {
      Success = true;
      return  (m_B*Y + m_C*Strain + m_D)/(-m_A);
   }
}

Float64 BiaxialBeamStrain::GetYStrainLocation(Float64 Strain, Float64 X, bool& Success) const
{
   if ( IsZero(m_B) || m_bIsConstantStrain )
   {
      Success = false;
      return 0;
   }
   else
   {
      Success = true;
      return (m_A*X + m_C*Strain + m_D)/(-m_B);
   }
}

//======================== ACCESS     =======================================

void BiaxialBeamStrain::SetStrainPlane(const Line2d& rnaLine,
                                         const Point2d& p3,Float64 strain)
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
   m_bIsConstantStrain = false;

   Update(p1, s1, p2, s2, p3, s3);
}

void BiaxialBeamStrain::SetStrainPlane(const Line2d& rnaLine,
                                         Float64 dist, Float64 strain)
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
   m_bIsConstantStrain = true;
   m_A = strain;
}


void BiaxialBeamStrain::Update(const Point2d& p1, Float64 s1, 
                                 const Point2d& p2, Float64 s2,
                                 const Point2d& p3, Float64 s3)
{
   PRECONDITION(!m_bIsConstantStrain);
   const int x = 0;
   const int y = 1;
   const int z = 2;
   Float64 v1[3];
   Float64 v2[3];

   v1[x] = p2.X() - p1.X();
   v1[y] = p2.Y() - p1.Y();
   v1[z] = s2 - s1;

   v2[x] = p3.X() - p1.X();
   v2[y] = p3.Y() - p1.Y();
   v2[z] = s3 - s1;

   m_A = v1[y]*v2[z] - v1[z]*v2[y];
   m_B = v1[z]*v2[x] - v1[x]*v2[z];
   m_C = v1[x]*v2[y] - v1[y]*v2[x];

   m_D = -1*(m_A*p1.X() + m_B*p1.Y() + m_C*s1);
}

#if defined _DEBUG
bool BiaxialBeamStrain::AssertValid() const
{
   return true;
}

void BiaxialBeamStrain::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for BiaxialBeamStrain" << WBFL::Debug::endl;
   os << " m_A  = "<< m_A<< WBFL::Debug::endl;  
   os << " m_B  = "<< m_B<< WBFL::Debug::endl;  
   os << " m_C  = "<< m_C<< WBFL::Debug::endl;  
   os << " m_D  = "<< m_D<< WBFL::Debug::endl;
   os << " m_IsConstantStrain = "<< m_bIsConstantStrain<< WBFL::Debug::endl;
}

#endif // _DEBUG

#if defined _UNITTEST
bool BiaxialBeamStrain::TestMe()
{
   Point2d p1(1,2), p2(3,1), p3(3,4);
   Line2d naline(p1,p2);
   BiaxialBeamStrain bs(naline, p3, .2);

   bool flag;
   Point2d tp1(4,4), tp2(-4,-4);
   if(!IsEqual(bs.GetAxialStrain(tp1),.2333,.001)) return false;;
   if(!IsEqual(bs.GetAxialStrain(tp2),-.56667,.001)) return false;
   if(!IsEqual(bs.GetXStrainLocation(-.56667,-4.,flag),-4.,.001)) return false;
   if(!IsEqual(bs.GetYStrainLocation(0.23333, 4.,flag), 4.,.001)) return false;

   // flip line around and test again
   naline.ThroughPoints(p2,p1);
   bs.SetStrainPlane(naline, p3, .2);
   if(!IsEqual(bs.GetAxialStrain(tp1),.2333,.001)) return false;;
   if(!IsEqual(bs.GetAxialStrain(tp2),-.56667,.001)) return false;
   if(!IsEqual(bs.GetXStrainLocation(-.56667,-4.,flag),-4.,.001)) return false;
   if(!IsEqual(bs.GetYStrainLocation(0.23333, 4.,flag), 4.,.001)) return false;

//   bs.Dump(std::_tcout);

   return true;
}

#endif // _UNITTEST



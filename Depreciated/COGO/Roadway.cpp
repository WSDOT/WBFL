///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <Cogo\CogoLib.h>

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          Roadway           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <Cogo\Roadway.h>         // class implementation
#include <Cogo\CogoModel.h>       // Uses
#include <Cogo\Engine.h>
#include <Cogo\Profile.h>
#include <MathEx.h>

#include <GeometricPrimitives\Primitives.h>
#include <GeometricPrimitives\Arc.h>
#include <GeometricPrimitives\Line2d.h>
#include <GeometricPrimitives\GeomOp2d.h>

// Return values for IsPointOnCurve
#define POC_TRUE 1
#define POC_FALSE 0
#define POC_BEFOREFIRSTCURVE -1
#define POC_AFTERLASTCURVE -2

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
cogoRoadway::cogoRoadway()
{
   m_Station = 0;
   m_pCogoModel = 0;
   m_Id = -1;
}

cogoRoadway::cogoRoadway(Int32 id,cogoModel* pCogoModel)
{
   m_Id = id;
   m_pCogoModel = pCogoModel;
   m_Station = 0.;
} // cogoRoadway

cogoRoadway::~cogoRoadway()
{
} // ~cogoRoadway

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
Int32 cogoRoadway::LocatePoint(Float64 station, Float64 offset)
{
   gpPoint2d new_point;
   LocatePoint( &new_point, station, offset );
   return m_pCogoModel->StorePoint( new_point );
} // LocatePoint

Int32 cogoRoadway::LocatePoint(Float64 station, Float64 offset, const cogoDirection& direction)
{
   gpPoint2d new_point;
   LocatePoint( &new_point, station, offset, direction );
   return m_pCogoModel->StorePoint( new_point );
} // LocatePoint

void cogoRoadway::LocatePoint(gpPoint2d* pPoint,Float64 station, Float64 offset) const
{
   PRECONDITION( pPoint != 0);
   cogoDirection direction;
   direction = BearingOfNormal(station);
   LocatePoint( pPoint, station,offset,direction);
} // LocatePoint

void cogoRoadway::LocatePoint(gpPoint2d* pPoint,Float64 station, Float64 offset, const cogoDirection& direction ) const
{
   PRECONDITION(pPoint != 0 );

   gpPoint2d point_on_alignment = GetPointOnAlignment( station );
   *pPoint = cogoEngine::LocateByDistDir( point_on_alignment, offset, direction );
} // LocatePoint

cogoDirection cogoRoadway::BearingAtStation(Float64 station) const
{
   const Segment& seg = FindSegment( station );
   cogoDirection dir;

   switch( seg.Type )
   {
   case stLine:
      {
         Float64 dist;
         cogoEngine::Inverse( &dist, &dir, seg.Line.GetStartPoint(), seg.Line.GetEndPoint() );
         break;
      }

   case stCurve:
      {
         // Is station before curve?
         if ( station < seg.StartStation )
            return seg.Curve.GetBackTangent();

         // Is station after curve?
         if ( seg.EndStation < station )
            return seg.Curve.GetAheadTangent();

         // Station is on curve
         Float64 dist;
         cogoDirection tanBrg;
         cogoEngine::Inverse( &dist, &tanBrg, seg.Curve.GetPC(), seg.Curve.GetPI() );

         Float64 sign = (seg.Curve.GetDirection() == gpLine2d::Left) ? -1 : 1;
         Float64 arcLength = station - seg.StartStation;
         CHECK( arcLength >= 0 );

         cogoAngle arcAngle( sign * arcLength / seg.Curve.GetR() );
         dir = tanBrg + arcAngle;
      }
   }

   return dir;
} // BearingOfNormal

cogoDirection cogoRoadway::BearingOfNormal(Float64 station) const
{
   cogoDirection dir = BearingAtStation( station );
   dir += cogoAngle(90,0,0,'L');
   return dir;
}

void cogoRoadway::GetStationAndOffset(const gpPoint2d& p,Float64* pStation,Float64* pOffset) const
{
   UpdateSegmentList();

   // Walk down the alignment checking out the point
   std::list<Segment>::const_iterator iter;
   for ( iter = m_Segments.begin(); iter != m_Segments.end(); iter++ )
   {
      const Segment& seg = *iter;

      if ( seg.Type == stLine )
      {
         // Find a line that is normal to the line segment and passes
         // through p.  See if the line segment and the normal intersect.
         gpLine2d line(seg.Line); // convert the segment to a line so we can
                                  // get the normal line.
         gpLine2d normal = line.Normal(p);

         gpPoint2d ip; // intersection point
         Int16 nIntersect;
         // If there is only one segment, intersection with the full line
         // otherwise, intersect with the line segment
         if ( m_Segments.size() == 1 )
            nIntersect = gpGeomOp2d::Intersect(&ip,normal,line);
         else
            nIntersect = gpGeomOp2d::Intersect(&ip,normal,seg.Line);

         if ( nIntersect == 1 )
         {
            // An intersection was found.
            cogoDirection dir;
            Float64 dist;
            cogoEngine::Inverse(&dist,&dir,seg.Line.GetStartPoint(),ip);
            
            *pStation = seg.StartStation + dist;
            *pOffset = -1*line.DistanceToPoint(p);

            return;
         }
      }
      else
      {
         CHECK( seg.Type == stCurve );

         // Create two local coordinate systems.  Local system 1 has its origin at PC with
         // its Y axis passing through CC.  Local system 2 has its origin at PT with its
         // Y axis passing  through CC.
         // Convert p to each of these coordinate systems.
         // If p1.X() is greater than zero in system 1 and p2.X() less than zero in system 2,
         // then point is in the sector.

         // Set up system 1.
         cogoDirection dir_x1 = BearingAtStation(seg.StartStation);
         Float64 angle1 = PI_OVER_2 - dir_x1.AsFloat64(); // CCW angle from global X
         gpPoint2d p1 = gpGeomOp2d::GlobalToLocal(seg.Curve.GetPC(),angle1,p);

         // Set up system 2.
         cogoDirection dir_x2 = BearingAtStation(seg.EndStation);
         Float64 angle2 = PI_OVER_2 - dir_x2.AsFloat64();
         gpPoint2d p2 = gpGeomOp2d::GlobalToLocal(seg.Curve.GetPT(),angle2,p);

         if ( p1.X() >= 0 && p2.X() <= 0 )
         {
            // Point is in the pie shaped sector defined by the curve.
            // Point projects onto curve

            // Use Arc-Line intersection to find the intersection between
            // the line normal to the curve, passing through p and the curve.

            // normal is a line normal to the curve, passing through CC and p.
            gpLine2d normal(seg.Curve.GetCC(),p);

            // geometric primitive arc that represents the curve
            gpArc arc(seg.Curve.GetPC(),seg.Curve.GetCC(),seg.Curve.GetPT());
            if ( seg.Curve.GetDirection() == gpLine2d::Right )
               arc.Reverse();

            CHECK( IsEqual(arc.GetCentralAngle(),seg.Curve.GetDelta().AsFloat64()) );

            gpPoint2d pi1,pi2; // line-arc can have up to two intersection points
            Int16 nIntersect = gpGeomOp2d::Intersect(&pi1,&pi2,normal,arc);

            // Since we already determined that p is in the sector and normal
            // is normal to the curve, there must be exactly one intersection.
            CHECK( nIntersect == 1 );

            // Compute distance along the arc to determine the station
            Float64 dist = arc.Distance(pi1);
            CHECK( dist <= arc.GetLength() );
            // If the curve is to the right, arc.Distance() returns the distance from
            // the PT to the point.
            if ( seg.Curve.GetDirection() == gpLine2d::Right )
               dist = arc.GetLength() - dist;
            *pStation = seg.StartStation + dist;

            // Compute the distance between the input point and the intersection point
            // This is the offset.  Adjust the sign of the offset for left and right
            Float64 offset;
            cogoDirection dir;
            cogoEngine::Inverse(&offset,&dir,p,pi1);

            // Use a line tangent to the curve at the intersection point to
            // determine left and right
            gpLine2d tangent = normal.Normal(pi1);
            // Note that tangent is going down station.  We need to reverse its direction
            // so we can determine the side of the alignment.
            tangent.Reverse();
            Float64 sign = 1;
            if ( tangent.GetSide(p) == gpLine2d::Right )
               sign = -1;

            *pOffset = sign*offset;
            return;
         }
         else
         {
            // Point projects onto tangents entering/exiting the curve
            // Project onto both... The one we want is the one with the smallest offset

            // Project onto back tangent
            gpVector2d vec1(1.0, angle1);
            gpLine2d tangent1(seg.Curve.GetPC(), vec1);

            // get point on line nearest (normal to our point)
            gpPoint2d normalpt1 = tangent1.PointOnLineNearest(p);

            // offset
            Float64 offset1 = normalpt1.Distance(p);
            if (gpLine2d::Right==tangent1.GetSide(p))
               offset1 = -offset1;

            // station
            Float64 dstat1 = normalpt1.Distance(seg.Curve.GetPC());
            Float64 station1 = seg.StartStation - dstat1;

            // Project onto forward tangent
            gpVector2d vec2(1.0, angle2);
            gpLine2d tangent2(seg.Curve.GetPT(), vec2);

            // get point on line nearest (normal to our point)
            gpPoint2d normalpt2 = tangent2.PointOnLineNearest(p);

            // offset
            Float64 offset2 = normalpt2.Distance(p);
            if (gpLine2d::Right==tangent2.GetSide(p))
               offset2 = -offset2;

            // station
            Float64 dstat2 = normalpt2.Distance(seg.Curve.GetPT());
            Float64 station2 = seg.EndStation + dstat2;

            if ( fabs(offset1) <= fabs(offset2) )
            {
               // point is closer to back tangent
               *pOffset  = offset1;
               *pStation = station1;
            }
            else
            {
               // point is closer to forward tangent
               *pOffset  = offset2;
               *pStation = station2;
            }
         }
      }
   }

   return;
}

//======================== ACCESS     =======================================

void cogoRoadway::SetStation(Float64 refStation)
{
   m_Station = refStation;
} // SetStation

Float64 cogoRoadway::GetStation() const
{
   return m_Station;
} // GetStation

cogoModel* cogoRoadway::GetCogoModel()
{
   return m_pCogoModel;
} // cogoModel

const cogoModel* cogoRoadway::GetCogoModel() const
{
   return m_pCogoModel;
} // cogoModel

bool cogoRoadway::AddPoint(Int32 id)
{
   gpPoint2d p;
   if ( m_pCogoModel->GetPoint(&p,id) )
   {
      Element el;
      el.ID = id;
      el.Type = etPoint;
      m_Elements.push_back(el);
      return true;
   }

   return false;
}

bool cogoRoadway::AddCurve(Int32 id)
{
   cogoCurve c;
   if ( m_pCogoModel->GetCurve(&c,id) )
   {
      Element el;
      el.ID = id;
      el.Type = etCurve;
      m_Elements.push_back(el);
      return true;
   }

   return false;
}


Int32 cogoRoadway::CreateProfile(Float64 sta1,Float64 elev1,Float64 sta2,Float64 elev2)
{
   cogoProfile profile(this);
   profile.AddPoint(sta1,elev1);
   profile.AddPoint(sta2,elev2);
   m_Profiles.push_back(profile);
   return m_Profiles.size()-1;
}

Int32 cogoRoadway::CreateProfile(const cogoVCurve& vcurve)
{
   cogoProfile profile(this);
   profile.AddCurve(vcurve);
   m_Profiles.push_back(profile);
   return m_Profiles.size()-1;
}

const cogoProfile* cogoRoadway::GetProfile(Int32 id) const
{
   if ( id < (Int32)m_Profiles.size() )
      return &m_Profiles[id];

   return 0;
}

cogoProfile* cogoRoadway::GetProfile(Int32 id)
{
   if ( id < (Int32)m_Profiles.size() )
      return &m_Profiles[id];

   return 0;
}


//======================== INQUIRY    =======================================

Int32 cogoRoadway::IsStationOnCurve(Float64 station) const
{
   // If there are not curves, we are outta here!
   if ( GetCurveCount() == 0 )
      return -1;

   const Segment& seg = FindSegment(station);
   Int32 id = -1;
   if ( InRange(seg.StartStation,station,seg.EndStation) && seg.Type == stCurve )
      id = seg.CurveID;

   return id;
}

Int32 cogoRoadway::IsPointInSector(Float64 station,Float64 offset,const cogoDirection& dir) const
{
   // If there are not curves, we are outta here!
   if ( GetCurveCount() == 0 )
      return -1;

   UpdateSegmentList();

   // Convert station, offset, direction into a point in the cogo space
   gpPoint2d p;
   LocatePoint(&p,station,offset,dir);

   // Start checking out the point
   std::list<Segment>::const_iterator iter;
   for ( iter = m_Segments.begin(); iter != m_Segments.end(); iter++ )
   {
      const Segment& seg = *iter;

      // Only need to worry if the segment is a curve.
      if ( seg.Type == stCurve )
      {
         // Create two local coordinate systems.  Local system 1 has its origin at PC with
         // its Y axis passing through CC.  Local system 2 has its origin at PT with its
         // Y axis passing  through CC.
         // Convert p to each of these coordinate systems.
         // If p1.X() is greater than zero in system 1 and p2.X() less than zero in system 2,
         // then point is in the sector.

         // Set up system 1.
         cogoDirection dir_x1 = BearingAtStation(seg.StartStation);
         Float64 angle1 = PI_OVER_2 - dir_x1.AsFloat64(); // CCW angle from global X
         gpPoint2d p1 = gpGeomOp2d::GlobalToLocal(seg.Curve.GetPC(),angle1,p);

         // Set up system 2.
         cogoDirection dir_x2 = BearingAtStation(seg.EndStation);
         Float64 angle2 = PI_OVER_2 - dir_x2.AsFloat64();
         gpPoint2d p2 = gpGeomOp2d::GlobalToLocal(seg.Curve.GetPT(),angle2,p);

         if ( p1.X() >= 0 && p2.X() <= 0 )
            return seg.CurveID;
      }
   }

   return -1;
}



////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void cogoRoadway::UpdateSegmentList() const
{
   WATCH("Updating segment list");

   m_Segments.clear();

   if ( m_Elements.size() == 1 )
   {
      // If there is only one element, it better be a curve
      // Just create a segment list with one curve in it and
      // get the heck outta here!
      const Element& element = m_Elements.front();
      CHECK(element.Type == etCurve );

      Segment seg;
      seg.Type = stCurve;
      bool bFound = m_pCogoModel->GetCurve( &seg.Curve, element.ID );
      if ( !bFound )
      {
         // Specified curve couldn't be found. Can't build segment list
#pragma Reminder("Throw an exception here")
      }

      seg.CurveID = element.ID;
      // Station the segment
      seg.StartStation = GetStation();
      seg.Length = seg.Curve.GetL();
      seg.EndStation = seg.StartStation + seg.Length;

      m_Segments.push_back( seg );
      return;
   }

   Float64 curStation = GetStation();

   std::list<Element>::const_iterator curr_iter = m_Elements.begin();
   std::list<Element>::const_iterator prev_iter = curr_iter++;

   // If the very first element is a curve, we need to create
   // a segment for it.
   const Element& element = *prev_iter;
   if ( element.Type == etCurve )
   {
      Segment seg;
      seg.Type = stCurve;
      bool bFound = m_pCogoModel->GetCurve( &seg.Curve, element.ID );
      if ( !bFound )
      {
         // Specified curve couldn't be found. Can't build segment list
#pragma Reminder("Throw an exception here")
      }

      seg.CurveID = element.ID;
      // Station the segment
      seg.StartStation = curStation;
      seg.Length = seg.Curve.GetL();
      seg.EndStation = seg.StartStation + seg.Length;
      curStation = seg.EndStation;

      m_Segments.push_back( seg );
   }

   // Work our way over each element, creating segments between
   // the last element and the current element
   while ( curr_iter != m_Elements.end() )
   {
      const Element& prevElement = *prev_iter;
      const Element& currElement = *curr_iter;

      Segment seg;
      
      // Create a line segment between the last these two elements
      seg.Type = stLine;
      gpPoint2d start_pnt, end_pnt;
      if ( prevElement.Type == etPoint )
      {
         m_pCogoModel->GetPoint( &start_pnt, prevElement.ID );
         m_pCogoModel->GetPoint( &end_pnt,   currElement.ID );
      }
      else
      {
         cogoCurve curve;
         m_pCogoModel->GetCurve( &curve, prevElement.ID );
         end_pnt = curve.GetPT();
      }

      seg.CurveID = -1;
      seg.Line.SetStartPoint( start_pnt );
      seg.Line.SetEndPoint( end_pnt );
      seg.StartStation = curStation;
      seg.Length = seg.Line.Length();
      seg.EndStation = seg.StartStation + seg.Length;
      curStation = seg.EndStation;

      // Only add the segment if it has length
      if ( !IsZero(seg.Length) )
         m_Segments.push_back( seg );

      if ( prevElement.Type == etCurve )
      {
         Segment seg;
         seg.Type = stCurve;
         bool bFound = m_pCogoModel->GetCurve( &seg.Curve, element.ID );
         if ( !bFound )
         {
            // Specified curve couldn't be found. Can't build segment list
   #pragma Reminder("Throw an exception here")
         }

         seg.CurveID = element.ID;
         // Station the segment
         seg.StartStation = curStation;
         seg.Length = seg.Curve.GetL();
         seg.EndStation = seg.StartStation + seg.Length;
         curStation = seg.EndStation;

         m_Segments.push_back( seg );
      }

      // Go to the next element
      prev_iter = curr_iter;
      curr_iter++;
   }
}

const cogoRoadway::Segment& cogoRoadway::FindSegment(Float64 station) const
{
   UpdateSegmentList();

   if ( station < m_Segments.front().StartStation )
      return m_Segments.front();

   std::list<Segment>::const_iterator iter;
   for ( iter = m_Segments.begin(); iter != m_Segments.end(); iter++ )
   {
      const Segment& seg = *iter;
      if ( seg.StartStation <= station && station < seg.EndStation )
         return seg;
   }

   // If we get here, return the last segment
   CHECK( m_Segments.back().EndStation <= station );
   return m_Segments.back();
}

gpPoint2d cogoRoadway::GetPointOnAlignment(Float64 station) const
{
   const Segment& seg = FindSegment(station);
   gpPoint2d point;

   if ( seg.Type == stLine )
   {
      Float64 dist = station - seg.StartStation;
      point = cogoEngine::LocatePointOnLine( seg.Line.GetStartPoint(), seg.Line.GetEndPoint(), dist );
   }
   else
   {
      CHECK( seg.Type == stCurve );

      // Before curve?
      if ( station < seg.StartStation )
      {
         point = cogoEngine::LocatePointOnLine(seg.Curve.GetPC(), seg.Curve.GetPI(), station - seg.StartStation);
         return point;
      }

      // After curve?
      if ( seg.EndStation < station )
      {
         point = cogoEngine::LocatePointOnLine(seg.Curve.GetPT(), seg.Curve.GetPI(), seg.EndStation - station);
         return point;
      }

      Float64 sign = (seg.Curve.GetDirection() == gpLine2d::Left) ? -1 : 1;
      Float64 arcLength = station - seg.StartStation;
      cogoAngle arcAngle( sign * arcLength / seg.Curve.GetR() );

      point = cogoEngine::LocateByDistAngle( seg.Curve.GetPC(), seg.Curve.GetCC(), seg.Curve.GetR(), arcAngle );
   }

   return point;
}

Int16 cogoRoadway::GetCurveCount() const
{
   std::list<Element>::const_iterator iter;
   Int16 cCurves = 0;
   for ( iter = m_Elements.begin(); iter != m_Elements.end(); iter++ )
   {
      const Element& e = *iter;
      if ( e.Type == etCurve )
         cCurves++;
   }

   return cCurves;
}

//======================== ACCESS     =======================================
//======================== INQUERY ==========================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool cogoRoadway::AssertValid() const
{
   return true;
}

void cogoRoadway::Dump(dbgDumpContext& os) const
{
   os << "Dump for cogoRoadway - Not Implemented" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool cogoRoadway::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("cogoRoadway");
#pragma Reminder("Implement Unit Tests")
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for cogoRoadway");

   cogoModel model;
   Int32 p1 = model.StorePoint(0,0);
   Int32 p2 = model.StorePoint(100,0);
   Int32 a1 = model.CreateAlignment(p1,p2);

   cogoRoadway* pAlignment = model.GetAlignment(a1);;

   Float64 sta,offset;
   pAlignment->GetStationAndOffset(gpPoint2d(0,100),&sta,&offset);
   TRY_TESTME( IsEqual(sta,0.00) );
   TRY_TESTME( IsEqual(offset,-100.) ); // left

   pAlignment->GetStationAndOffset(gpPoint2d(0,-100),&sta,&offset);
   TRY_TESTME( IsEqual(sta,0.00) );
   TRY_TESTME( IsEqual(offset,100.) ); // right

   TESTME_EPILOG("cogoRoadway");
}
#endif
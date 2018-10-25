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
// NAME:          Profile           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <Cogo\Profile.h>
#include <Cogo\Roadway.h>
#include <MathEx.h>

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
cogoProfile::cogoProfile(cogoRoadway* pAlignment)
{
   PRECONDITION( pAlignment != 0 );

   m_pAlignment = pAlignment;
   m_CrownPointOffset = 0;
} // cogoProfile

cogoProfile::cogoProfile(const cogoProfile& rOther)
{
   m_Elements = rOther.m_Elements;
   m_SuperElevations = rOther.m_SuperElevations;
   m_pAlignment = rOther.m_pAlignment;
   m_CrownPointOffset = rOther.m_CrownPointOffset;
}

cogoProfile::~cogoProfile()
{
} // ~cogoProfile

//======================== OPERATORS  =======================================
cogoProfile& cogoProfile::operator = (const cogoProfile& rOther)
{
   if ( this != &rOther )
   {
      m_Elements = rOther.m_Elements;
      m_SuperElevations = rOther.m_SuperElevations;
      m_pAlignment = rOther.m_pAlignment;
      m_CrownPointOffset = rOther.m_CrownPointOffset;
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 cogoProfile::GetElevation(Float64 station,Float64 offset) const
{
   Float64 nrmlStation = station;
   Float64 nrmlDist    = offset;

   // Get the elevation of the profile at this station
   Float64 profileElev = GetProfileElevation(nrmlStation);
   Float64 left,right;
   GetSuperElevation(nrmlStation,&left,&right);

   Float64 elev;
   if ( m_CrownPointOffset > 0 && nrmlDist > 0 )
   {
      if ( nrmlDist > m_CrownPointOffset )
         elev = profileElev - left*m_CrownPointOffset + right*(nrmlDist - m_CrownPointOffset);
      else
         elev = profileElev - left*nrmlDist;
   }
   else if ( m_CrownPointOffset > 0 && nrmlDist <= 0 )
   {
      elev = profileElev - left*nrmlDist;
   }
   else if ( m_CrownPointOffset <= 0 && nrmlDist > 0 )
   {
      elev = profileElev + right*nrmlDist;
   }
   else
   {
      if ( nrmlDist < m_CrownPointOffset )
         elev = profileElev + right*m_CrownPointOffset - left*(nrmlDist-m_CrownPointOffset);
      else
         elev = profileElev + right*nrmlDist;
   }

   return elev;
}

//======================== ACCESS     =======================================
cogoRoadway* cogoProfile::GetAlignment()
{
   return m_pAlignment;
} // cogoModel

const cogoRoadway* cogoProfile::GetAlignment() const
{
   return m_pAlignment;
} // cogoModel

void cogoProfile::SetCrownPointOffset(Float64 offset)
{
   m_CrownPointOffset = offset;
}

Float64 cogoProfile::GetCrownPointOffset() const
{
   return m_CrownPointOffset;
}

void cogoProfile::AddPoint(Float64 station,Float64 elev)
{
   Element element;
   element.Type = etPoint;
   element.Point = gpPoint2d(station,elev);
   m_Elements.push_back(element);
   SortElements();
}

void cogoProfile::AddCurve(const cogoVCurve& vcurve)
{
   Element element;
   element.Type = etCurve;
   element.Curve = vcurve;
   m_Elements.push_back(element);
   SortElements();
}

void cogoProfile::AddSuperElevation(Float64 station,Float64 left,Float64 right)
{
   SuperElevation super;
   super.Station = station;
   super.Left    = left;
   super.Right   = right;

   m_SuperElevations.push_back(super);
   SortSuperElevations();
}

void cogoProfile::GetSuperElevation(Float64 station, Float64* pLeft,Float64* pRight) const
{
   if ( m_SuperElevations.size() == 0 )
   {
      // No super elevation entries. Assume cross slope to be zero.
      *pLeft  = 0;
      *pRight = 0;
      return;
   }

   // If station is before first station, use first super elevation
   const SuperElevation& firstSuper = m_SuperElevations.front();
   if ( station < firstSuper.Station )
   {
      *pLeft  = firstSuper.Left;
      *pRight = firstSuper.Right;
      return;
   }

   // If station is after last station, use last super elevation
   const SuperElevation& lastSuper = m_SuperElevations.back();
   if ( lastSuper.Station < station )
   {
      *pLeft  = lastSuper.Left;
      *pRight = lastSuper.Right;
      return;
   }

   // station is somewhere between defined super elevations
   std::list<SuperElevation>::const_iterator iter;
   for ( iter = m_SuperElevations.begin(); iter != m_SuperElevations.end(); iter++ )
   {
      const SuperElevation& prevSuper = *iter;
      iter++;
      const SuperElevation& nextSuper = *iter;
      iter--;

      if ( InRange( prevSuper.Station, station, nextSuper.Station ) )
      {
         *pLeft = prevSuper.Left + ( nextSuper.Left - prevSuper.Left ) * ( station - prevSuper.Station ) / ( nextSuper.Station - prevSuper.Station );
         *pRight = prevSuper.Right + ( nextSuper.Right - prevSuper.Right ) * ( station - prevSuper.Station ) / ( nextSuper.Station - prevSuper.Station );
         return;
      }
   }
}


//======================== INQUIRY    =======================================

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
bool cogoProfile::Element::operator>(const cogoProfile::Element& el) const
{
   Float64 sta1;
   Float64 sta2;

   if ( Type == cogoProfile::etPoint )
      sta1 = Point.X();
   else
      sta1 = Curve.GetBVC().X();

   if ( el.Type == cogoProfile::etPoint )
      sta2 = el.Point.X();
   else
      sta2 = el.Curve.GetBVC().X();

   // Use less than operator because we want to sort from least to greatest.
   // std::list wants to sort from greatest to least
   return sta1 < sta2;
}

bool cogoProfile::SuperElevation::operator>(const cogoProfile::SuperElevation& super) const
{
   // Use less than operator because we want to sort from least to greatest.
   // std::list wants to sort from greatest to least
   return Station < super.Station;
}

void cogoProfile::SortElements()
{

   m_Elements.sort( std::greater<cogoProfile::Element>() );
}

void cogoProfile::SortSuperElevations()
{
   m_SuperElevations.sort( std::greater<cogoProfile::SuperElevation>() );
}

Float64 cogoProfile::GetProfileElevation(Float64 station) const
{
   // Check if station is before first element
   Float64 firstSta;
   const Element& first = m_Elements.front();
   if ( first.Type == etPoint )
   {
      firstSta = first.Point.X();
   }
   else
   {
      firstSta = first.Curve.GetBVC().X();
   }

   // Station is before first station.
   // Compute grade through first element
   if ( station < firstSta )
   {
      return BeforeProfileElevation(station);
   }

   // Check if station is after last element
   const Element& last = m_Elements.back();
   Float64 lastSta;
   if ( last.Type == etPoint )
   {
      lastSta = last.Point.X();
   }
   else
   {
      lastSta = last.Curve.GetEVC().X();
   }


   if ( lastSta < station )
   {
      return AfterProfileElevation(station);
   }

   // OK, station is somewhere within the profile range.

   return ProfileElevation(station);
}

Float64 cogoProfile::BeforeProfileElevation(Float64 station) const
{
   Float64 startStation;
   Float64 startElev;
   Float64 grade;

   const Element& e = m_Elements.front();

   if ( m_Elements.size() == 1 )
   {
      // If we have one element, it must be a vertical curve
      startStation = e.Curve.GetBVC().X();
      grade = (e.Curve.GetPVI().Y() - e.Curve.GetBVC().Y())/(e.Curve.GetPVI().X()-e.Curve.GetBVC().X());
      startElev = e.Curve.GetBVC().Y();
 
      Float64 elev = startElev - grade*(startStation-station);
      return elev;
   }

   if ( e.Type == etPoint )
   {
      startStation = e.Point.X();
      startElev = e.Point.Y();

      Float64 nextStation;
      Float64 nextElev;

      std::list<Element>::const_iterator iter;
      iter = m_Elements.begin();
      iter++;
      const Element& nextElement = *iter;
      if ( nextElement.Type == etPoint )
      {
         nextStation = nextElement.Point.X();
         nextElev    = nextElement.Point.Y();
      }
      else
      {
         nextStation = nextElement.Curve.GetBVC().X();
         nextElev    = nextElement.Curve.GetBVC().Y();
      }

      grade = ( nextElev - startElev)/(nextStation - startStation);
   }
   else
   {
      startStation = e.Curve.GetBVC().X();
      grade = (e.Curve.GetPVI().Y() - e.Curve.GetBVC().Y())/(e.Curve.GetPVI().X()-e.Curve.GetBVC().X());
      startElev = e.Curve.GetBVC().Y();
   }

   Float64 elev = startElev - grade*(startStation-station);
   return elev;
}

Float64 cogoProfile::AfterProfileElevation(Float64 station) const
{
   Float64 startStation;
   Float64 startElev;
   Float64 grade;

   const Element& e = m_Elements.back();
   if ( m_Elements.size() == 1 )
   {
      // If we have one element, it must be a vertical curve
      startStation = e.Curve.GetEVC().X();
      grade = (e.Curve.GetEVC().Y() - e.Curve.GetPVI().Y())/(e.Curve.GetEVC().X()-e.Curve.GetPVI().X());
      startElev = e.Curve.GetEVC().Y();
 
      Float64 elev = startElev + grade*(station - startStation);
      return elev;
   }

   if ( e.Type == etPoint )
   {
      startStation = e.Point.X();
      startElev    = e.Point.Y();

      Float64 prevStation;
      Float64 prevElev;

      std::list<Element>::const_iterator iter = m_Elements.end(); // one past last element
      iter--; // this is the last element
      iter--; // element before the last element
      const Element& prevElement = *iter;
      if ( prevElement.Type == etPoint )
      {
         prevStation = prevElement.Point.X();
         prevElev    = prevElement.Point.Y();
      }
      else
      {
         prevStation = prevElement.Curve.GetEVC().X();
         prevElev    = prevElement.Curve.GetEVC().Y();
      }

      grade = ( startElev - prevElev)/(startStation - prevStation);
   }
   else
   {
      startStation = e.Curve.GetEVC().X();
      grade = (e.Curve.GetEVC().Y() - e.Curve.GetPVI().Y())/(e.Curve.GetEVC().X()-e.Curve.GetPVI().X());
      startElev = e.Curve.GetEVC().Y();
   }

   Float64 elev = startElev + grade*(station - startStation);
   return elev;
}

Float64 cogoProfile::ProfileElevation(Float64 station) const
{
   if ( m_Elements.size() == 1 )
   {
      const Element& e = m_Elements.front();
      CHECK(e.Type == etCurve);
      return e.Curve.GetElevation(station);
   }

   std::list<Element>::const_iterator iter = m_Elements.begin();
   Float64 lastStation;
   do
   {
      const Element& e = *iter++;

      if ( e.Type == etPoint )
      {
         lastStation = e.Point.X();
      }
      else
      {
         lastStation = e.Curve.GetBVC().X();
      }

   } while ( lastStation < station );

   // These elements should be on either side of station
   iter--;
   const Element& nextElement = *iter--;
   const Element& prevElement = *iter;

   // Check to see if previous element is a vertical curve and if station is within
   // the limits of the curve.
   if ( prevElement.Type == etCurve && InRange( prevElement.Curve.GetBVC().X(), station, prevElement.Curve.GetEVC().X() ) )
   {
      return prevElement.Curve.GetElevation( station );
   }

   // Check to see if next element is a vertical curve and if station is within
   // the limits of the curve
   if ( nextElement.Type == etCurve && InRange( nextElement.Curve.GetBVC().X(), station, nextElement.Curve.GetEVC().X() ) )
   {
      return nextElement.Curve.GetElevation( station );
   }

   Float64 prevStation, nextStation;
   Float64 prevElev, nextElev;

   if ( prevElement.Type == etPoint )
   {
      prevStation = prevElement.Point.X();
      prevElev    = prevElement.Point.Y();
   }
   else
   {
      prevStation = prevElement.Curve.GetEVC().X();
      prevElev    = prevElement.Curve.GetEVC().Y();
   }


   if ( nextElement.Type == etPoint )
   {
      nextStation = nextElement.Point.X();
      nextElev    = nextElement.Point.Y();
   }
   else
   {
      nextStation = nextElement.Curve.GetBVC().X();
      nextElev    = nextElement.Curve.GetBVC().Y();
   }

   Float64 grade = ( nextElev - prevElev)/(nextStation - prevStation);
   Float64 elev = prevElev + grade*(station - prevStation);

   return elev;
}

//======================== ACCESS     =======================================
//======================== INQUERY ==========================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool cogoProfile::AssertValid() const
{
   return true;
}

void cogoProfile::Dump(dbgDumpContext& os) const
{
   os << "Dump for cogoProfile - Not Implemented" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <Cogo\Roadway.h>
bool cogoProfile::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("cogoProfile");
#pragma Reminder("Implement Unit Tests")
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for cogoProfile");

   cogoRoadway alignment;

   cogoProfile profile(&alignment);
   Float64 elev; 
   profile.AddPoint(0.00,0.00);
   profile.AddPoint(100.00, 10.00);
   elev = profile.GetElevation(200.00);
   TRY_TESTME( IsEqual(elev,20.00) );
   elev = profile.GetElevation(-200.00);
   TRY_TESTME( IsEqual(elev,-20.00) );

   profile.AddSuperElevation(0.00,-0.02,0.02);
   elev = profile.GetElevation(100.00,10);
   TRY_TESTME(IsEqual(elev,10.20)); // right
   elev = profile.GetElevation(100.00,-10);
   TRY_TESTME(IsEqual(elev,9.80)); // left

   TESTME_EPILOG("cogoProfile");
}
#endif
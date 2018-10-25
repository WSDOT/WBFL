///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfStrandPattern
****************************************************************************/

#include <BridgeModeling\StrandPattern.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfStrandPattern::bmfStrandPattern()
{
   m_bReflectEnabled = true;
   m_DebondLength = 0;
}

bmfStrandPattern::bmfStrandPattern(const bmfStrandPattern& rOther)
{
   MakeCopy(rOther);
}

bmfStrandPattern::~bmfStrandPattern()
{
}

//======================== OPERATORS  =======================================
bmfStrandPattern& bmfStrandPattern::operator= (const bmfStrandPattern& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void bmfStrandPattern::AddPatternPoint(const PatternPoint& p)
{
   m_PtrnPoints.push_back( p );

   // Build up the strand points as we go.
   StrandPoint sp(p);
   sp.FillSequence = m_StrandPoints.size();
   m_StrandPoints.push_back( sp );

   Row* the_row = NULL;
   Row target;
   target.Elevation = sp.Point.Y();
   std::set<Row>::iterator found = m_Rows.find(target);
   if ( found != m_Rows.end() )
   {
      Row& row = *found;
      row.StrandPoints.push_back(m_StrandPoints.size()-1);

      the_row = &row;
   }
   else
   {
      Row row;
      row.Elevation = sp.Point.Y();
      row.StrandPoints.push_back(m_StrandPoints.size()-1);
      std::pair<std::set<Row>::iterator,bool> result = m_Rows.insert(row);
      CHECK(result.second == true);
      the_row = &(*(result.first));
   }

   if ( sp.Point.X() > 0 )
   {
      StrandPoint sp2 = sp;
      sp2.Point.X() = -sp.Point.X();
      sp2.FillSequence = m_StrandPoints.size();
      m_StrandPoints.push_back( sp2 );

      the_row->StrandPoints.push_back(m_StrandPoints.size()-1);
   }

   ASSERTVALID;
}

void bmfStrandPattern::AddPatternPoints(const std::vector<PatternPoint>& points)
{
   std::vector<PatternPoint>::const_iterator iter;
   for ( iter = points.begin(); iter < points.end(); iter++ )
   {
      AddPatternPoint( *iter );
   }

   ASSERTVALID;
}

StrandIndexType bmfStrandPattern::GetPatternPointCount() const
{
   return m_PtrnPoints.size();
}

bmfStrandPattern::PatternPoint bmfStrandPattern::GetPatternPoint(StrandIndexType idx) const
{
   PRECONDITION( idx < m_PtrnPoints.size() );
   return m_PtrnPoints[idx];
}

std::vector<bmfStrandPattern::PatternPoint> bmfStrandPattern::GetPatternPoints() const
{
   return m_PtrnPoints;
}

void bmfStrandPattern::RemovePatternPoint(StrandIndexType idx)
{
   PRECONDITION( idx < m_PtrnPoints.size() );
   m_PtrnPoints.erase( m_PtrnPoints.begin() + idx );

   std::vector<PatternPoint> points = m_PtrnPoints;
   StrandIndexType nStrands = GetStrandCount();
   StrandIndexType nDebondStrands = GetDebondStrandCount();

   RemoveAllPatternPoints();
   AddPatternPoints(points);
   SetStrandCount(nStrands);
   SetDebondStrandCount(nDebondStrands);

   ASSERTVALID;
}

void bmfStrandPattern::RemoveAllPatternPoints()
{
   RemoveAllStrands();
   m_PtrnPoints.clear();
   m_StrandPoints.clear();
   m_Rows.clear();
}

bool bmfStrandPattern::EnablePointReflection(bool bEnable)
{
   bool bTemp = m_bReflectEnabled;
   m_bReflectEnabled = bEnable;
   return bTemp;
}

bool bmfStrandPattern::IsPointReflectionEnabled() const
{
   return m_bReflectEnabled;
}

StrandIndexType bmfStrandPattern::GetStrandPointCount() const
{
   ASSERTVALID;
   return m_StrandPoints.size();
}

StrandIndexType bmfStrandPattern::GetMaxStrandCount() const
{
   return GetStrandPointCount();
}

gpPoint2d bmfStrandPattern::GetStrandPatternPoint(StrandIndexType idx) const
{
   ASSERTVALID;

   PRECONDITION( idx < m_StrandPoints.size() );
   return m_StrandPoints[idx].Point;
}

gpPoint2d bmfStrandPattern::GetStrandPoint(StrandIndexType iStrand) const
{
   ASSERTVALID;

   // Get the raw strand pattern point.
   gpPoint2d pnt = GetStrandPatternPoint( iStrand );

   StrandIndexType nStrands = GetStrandCount();

   // It the request strand is the last strand in the fill sequence and
   // it is not on the Y axis and reflection is not enabled, then
   // force the strand to the Y axis.
   if ( iStrand == (nStrands-1) && pnt.X() > 0 && !m_bReflectEnabled )
      pnt.X() = 0;

   return pnt;
}

bmfStrandPattern::StrandPoint* bmfStrandPattern::GetDebondStrandPoint(StrandIndexType idxDebond)
{
   StrandIndexType idx = 0;
   std::vector<StrandPoint>::iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
   {
      StrandPoint& pp = *iter;
      if ( pp.bCanDebond )
      {
         if ( idx == idxDebond )
         {
            return &pp;
         }
         idx++;
      }
   }

   return NULL;
}

const bmfStrandPattern::StrandPoint* bmfStrandPattern::GetDebondStrandPoint(StrandIndexType idxDebond) const
{
   StrandIndexType idx = 0;
   std::vector<StrandPoint>::const_iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
   {
      const StrandPoint& pp = *iter;
      if ( pp.bCanDebond )
      {
         if ( idx == idxDebond )
         {
            return &pp;
         }
         idx++;
      }
   }

   return NULL;
}

StrandIndexType bmfStrandPattern::AddStrand()
{
   ASSERTVALID;

   StrandIndexType size = m_StrandPoints.size();
   if (size==0)
   {
      return 0;
   }

   StrandIndexType nStrands = GetStrandCount();

   Int16 inc = 0;
   if ( m_StrandPoints[nStrands].Point.X() > 0 && m_bReflectEnabled )
      inc = 2; // We have to add strands in pairs (unless it is on the Y axis
   else
      inc = 1; // Strand point on Y axis or reflection is disabled.

   // Make sure we haven't exceeded the limit
   if ( size < (nStrands + inc) )
   {
      return 0;
   }

   StrandPoint& sp = m_StrandPoints[nStrands];
   sp.bHasStrand = true;

   if ( inc == 2 )
   {
      StrandPoint& sp2 = m_StrandPoints[nStrands+1];
      sp2.bHasStrand = true;
   }

   return inc;
}

StrandIndexType bmfStrandPattern::RemoveStrand()
{
   ASSERTVALID;

   StrandIndexType nStrands = GetStrandCount();

   if ( nStrands == 0 )
      return 0;

   Int16 inc = 0;
   StrandPoint& pnt = *(m_StrandPoints.begin() + nStrands - 1);
   if ( pnt.Point.X() < 0 && m_bReflectEnabled )
      inc = 2;
   else
      inc = 1;

   pnt.bHasStrand = false;

   if ( inc == 2 )
   {
      StrandPoint& pnt2 = *(m_StrandPoints.begin() + nStrands - 2);
      pnt2.bHasStrand = false;
   }

   return inc;
}
   
StrandIndexType bmfStrandPattern::AddDebondedStrand()
{
   ASSERTVALID;

   std::vector<StrandPoint>::iterator iter = m_StrandPoints.begin();
   StrandPoint* psp;
   do
   {
      psp = &(*iter++);
   } while ( !(psp->bHasStrand && psp->bCanDebond && !psp->bIsDebonded) && iter != m_StrandPoints.end());

   if ( iter == m_StrandPoints.end() )
      return 0;

   Int16 inc = 0;
   if ( psp->Point.X() > 0 && m_bReflectEnabled )
      inc = 2; // We have to add strands in pairs (unless it is on the Y axis
   else
      inc = 1; // Strand point on Y axis or reflection is disabled.

   StrandIndexType nDebondStrands = GetDebondStrandCount();
   // Make sure we haven't exceeded the limit
   if ( GetMaxDebondStrandCount() < (nDebondStrands + inc) )
   {
      return 0;
   }

   psp->bIsDebonded = true;
   if ( inc == 2 )
   {
      psp = &(*iter);
      psp->bIsDebonded = true;
   }

   return inc;
}

StrandIndexType bmfStrandPattern::RemoveDebondedStrand()
{
   ASSERTVALID;

   StrandIndexType nDebondStrands = GetDebondStrandCount();

   if ( nDebondStrands == 0 )
      return 0;

   Int16 inc = 0;
   StrandPoint* sp = GetDebondStrandPoint(nDebondStrands-1);
   if ( sp->Point.X() < 0 && m_bReflectEnabled )
      inc = 2;
   else
      inc = 1;

   sp->bIsDebonded = false;

   if ( inc == 2 )
   {
      StrandPoint* sp2 = GetDebondStrandPoint(nDebondStrands-2);
      sp2->bIsDebonded = false;
   }

   return inc;
}

void bmfStrandPattern::RemoveAllStrands()
{
   ASSERTVALID;
   std::vector<StrandPoint>::iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
   {
      StrandPoint& sp = *iter;
      sp.bHasStrand = false;
      sp.bIsDebonded = false;
   }
}

StrandIndexType bmfStrandPattern::TestStrandCount(StrandIndexType nStrands) const
{
   ASSERTVALID;

   // If nStrands is more than the pattern can hold,
   // return the max value and get outta here.
   if ( (StrandIndexType)m_StrandPoints.size() < nStrands )
      return m_StrandPoints.size();

   // If nStrands is zero...
   if ( nStrands == 0 )
   {
      return 0;
   }


   if ( m_StrandPoints[nStrands-1].Point.X() > 0 && m_bReflectEnabled )
   {
      // Can't set the number of strands because the requested strand
      // is to the left of Y axis and strands must be reflected.  The
      // next highest valid number of strands is nStrands+1.
      return nStrands+1;
   }

   return 0;
}

StrandIndexType bmfStrandPattern::TestDebondStrandCount(StrandIndexType nStrands) const
{
   ASSERTVALID;

   // If nStrands is more than the pattern can hold,
   // return the max value and get outta here.
   StrandIndexType maxDebond = GetMaxDebondStrandCount();
   if ( maxDebond < nStrands )
      return maxDebond;

   // If nStrands is zero...
   if ( nStrands == 0 )
   {
      return 0;
   }

   const StrandPoint* sp = GetDebondStrandPoint(nStrands-1);
   if ( sp->Point.X() > 0 && m_bReflectEnabled )
   {
      // Can't set the number of strands because the requested strand
      // is to the left of Y axis and strands must be reflected.  The
      // next highest valid number of strands is nStrands+1.
      return nStrands+1;
   }

   return 0;
}

StrandIndexType bmfStrandPattern::SetStrandCount(StrandIndexType nStrands)
{
   ASSERTVALID;

   StrandIndexType next_strand = TestStrandCount( nStrands );
   if ( next_strand != 0 )
      return next_strand;

   StrandIndexType cStrands = 0;
   std::vector<StrandPoint>::iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
   {
      StrandPoint& sp = *iter;
      sp.bHasStrand = false;

      if ( cStrands < nStrands )
      {
         sp.bHasStrand = true;
         cStrands++;
      }
   }

   return 0;
}

StrandIndexType bmfStrandPattern::GetStrandCount() const
{
   StrandIndexType nStrands = 0;
   std::vector<StrandPoint>::const_iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
   {
      const StrandPoint& sp = *iter;
      if ( sp.bHasStrand )
         nStrands++;
   }

   return nStrands;
}

RowIndexType bmfStrandPattern::GetNumRowsWithStrand() const
{
   ASSERTVALID;

   RowIndexType rowCount = 0;
   std::set<Row>::const_iterator iter;
   for ( iter = m_Rows.begin(); iter != m_Rows.end(); iter++ )
   {
      const Row& row = *iter;

      std::vector<StrandIndexType>::const_iterator row_iter;
      for ( row_iter = row.StrandPoints.begin(); row_iter != row.StrandPoints.end(); row_iter++ )
      {
         RowIndexType index = *row_iter;
         const StrandPoint& sp = m_StrandPoints[index];
         if ( sp.bHasStrand )
         {
            rowCount++;
            break; // break out of row_iter loop
         }
      }
   }

   return rowCount;
}

StrandIndexType bmfStrandPattern::GetNumStrandsInRow(RowIndexType rowIndex) const
{
   ASSERTVALID;

   std::set<Row>::const_iterator iter = m_Rows.begin();
   for ( RowIndexType i = 0; i < rowIndex; i++ )
      iter++;

   const Row& row = *iter;
   StrandIndexType strandCount = 0;

   std::vector<StrandIndexType>::const_iterator sp_iter;
   for ( sp_iter = row.StrandPoints.begin(); sp_iter != row.StrandPoints.end(); sp_iter++ )
   {
      RowIndexType index = *sp_iter;
      const StrandPoint& sp = m_StrandPoints[index];

      if ( sp.bHasStrand )
         strandCount++;
   }

   return strandCount;
}

StrandIndexType bmfStrandPattern::GetNumDebondStrandsInRow(RowIndexType rowIndex) const
{
   ASSERTVALID;

   std::set<Row>::const_iterator iter = m_Rows.begin();
   for ( RowIndexType i = 0; i < rowIndex; i++ )
      iter++;

   const Row& row = *iter;
   StrandIndexType strandCount = 0;

   std::vector<StrandIndexType>::const_iterator sp_iter;
   for ( sp_iter = row.StrandPoints.begin(); sp_iter != row.StrandPoints.end(); sp_iter++ )
   {
      RowIndexType index = *sp_iter;
      const StrandPoint& sp = m_StrandPoints[index];

      if ( sp.bHasStrand && sp.bIsDebonded )
         strandCount++;
   }

   return strandCount;
}

bool bmfStrandPattern::IsExteriorStrandDebondedInRow(RowIndexType rowIndex) const
{
   ASSERTVALID;

   std::set<Row>::const_iterator iter = m_Rows.begin();
   for ( RowIndexType i = 0; i < rowIndex; i++ )
      iter++;

   const Row& row = *iter;
   StrandIndexType exteriorStrandIndex;
   Float64 xmax = 0;

   std::vector<StrandIndexType>::const_iterator sp_iter;
   for ( sp_iter = row.StrandPoints.begin(); sp_iter != row.StrandPoints.end(); sp_iter++ )
   {
      RowIndexType index = *sp_iter;
      const StrandPoint& sp = m_StrandPoints[index];

      if ( xmax <= fabs(sp.Point.X()) )
      {
         xmax = fabs(sp.Point.X());
         exteriorStrandIndex = index;
      }
   }

   const StrandPoint& sp = m_StrandPoints[exteriorStrandIndex];
   return sp.bIsDebonded;
}

StrandIndexType bmfStrandPattern::GetMaxDebondStrandCount(StrandIndexType nStrands) const
{
   ASSERTVALID;

   // Loop through all the strand points for the given number of strands
   // counting all of the points that can be debonded
   StrandIndexType nDebond     = 0;
   StrandIndexType strandCount = 0;
   std::vector<StrandPoint>::const_iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end() && strandCount < nStrands; iter++, strandCount++ )
   {
      const StrandPoint& point = *iter;
      if ( point.bCanDebond )
         nDebond++;
   }

   return nDebond;
}

StrandIndexType bmfStrandPattern::GetMaxDebondStrandCount() const
{
   return GetMaxDebondStrandCount(GetStrandCount());
}

StrandIndexType bmfStrandPattern::GetDebondStrandCount() const
{
   StrandIndexType nStrands = 0;
   std::vector<StrandPoint>::const_iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
   {
      const StrandPoint& sp = *iter;
      if ( sp.bIsDebonded )
         nStrands++;
   }

   return nStrands;
}

StrandIndexType bmfStrandPattern::SetDebondStrandCount(StrandIndexType nStrands)
{
   ASSERTVALID;

   StrandIndexType next_strand = TestDebondStrandCount( nStrands );
   if ( next_strand != 0 )
      return next_strand;

   StrandIndexType nDebondStrands = 0;
   std::vector<StrandPoint>::iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
   {
      StrandPoint& sp = *iter;
      sp.bIsDebonded = false;

      if ( nDebondStrands < nStrands && sp.bCanDebond )
      {
         sp.bIsDebonded = true;
         nDebondStrands++;
      }
   }

   return 0;
}

Float64 bmfStrandPattern::GetDebondLength() const
{
   return m_DebondLength;
}

void bmfStrandPattern::SetDebondLength(Float64 l)
{
   m_DebondLength = l;
}

bool bmfStrandPattern::IsStrandDebonded(StrandIndexType idx) const
{
   ASSERTVALID;

   PRECONDITION( idx < m_StrandPoints.size() );
   return m_StrandPoints[idx].bIsDebonded;
}

gpPoint2d bmfStrandPattern::GetCenterOfGravity() const
{
   ASSERTVALID;
   gpPoint2d cg = GetCenterOfGravity( GetStrandCount() );

   // Strand patterns are symmetrical...
   // CG will fall on the Y axis
   CHECK( IsZero( cg.X() ) );

   return cg;
}

gpPoint2d bmfStrandPattern::GetCenterOfGravity(StrandIndexType nStrands) const
{
   ASSERTVALID;
   PRECONDITION( nStrands <= GetStrandPointCount() );
   WARN( TestStrandCount(nStrands) != 0, "nStrands is not valid" );

   gpPoint2d cg;

   Float64 sum_x = 0.0;
   Float64 sum_y = 0.0;
   for ( StrandIndexType i = 0; i < nStrands; i++ )
   {
      const gpPoint2d& pnt = m_StrandPoints[i].Point;
      if ( i == nStrands-1 && pnt.X() > 0 && !m_bReflectEnabled )
         sum_x += 0;
      else
         sum_x += pnt.X();

      sum_y += pnt.Y();
   }

   if ( nStrands == 0 )
   {
      cg.X() = 0;
      cg.Y() = 0;
   }
   else
   {
      cg.X() = sum_x / nStrands;
      cg.Y() = sum_y / nStrands;
   }

   return cg;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfStrandPattern::MakeCopy(const bmfStrandPattern& rOther)
{
   ASSERTVALID;

   // Add copy code here...
   m_PtrnPoints      = rOther.m_PtrnPoints;
   m_StrandPoints    = rOther.m_StrandPoints;
   m_Rows            = rOther.m_Rows;
   m_bReflectEnabled = rOther.m_bReflectEnabled;
   m_DebondLength    = rOther.m_DebondLength;
}

void bmfStrandPattern::MakeAssignment(const bmfStrandPattern& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bmfStrandPattern::AssertValid() const
{
   // For the data in this class to be valid,  all pattern points must have
   // an X coordinate that is >= zero.
   std::vector<PatternPoint>::const_iterator iter;
   for ( iter = m_PtrnPoints.begin(); iter < m_PtrnPoints.end(); iter++ )
   {
      const PatternPoint& p = *iter;
      if ( p.Point.X() < 0 )
         return false;
   }

   return true;
}

void bmfStrandPattern::Dump(dbgDumpContext& os) const
{
   ASSERTVALID;

   os << "Dump for bmfStrandPattern" << endl;
   std::vector<PatternPoint>::const_iterator i;

   os << "Pattern Points" << endl;
   Int16 j = 0;
   for ( i = m_PtrnPoints.begin(); i < m_PtrnPoints.end(); i++, j++ )
   {
      os << "m_PtrnPoints[" << j << "] = " << endl;
      (*i).Point.Dump(os);
   }
   os << endl;
   
   os << "Strand Points" << endl;
   j = 0;
   std::vector<StrandPoint>::const_iterator iter;
   for ( iter = m_StrandPoints.begin(); iter < m_StrandPoints.end(); iter++, j++ )
   {
      os << "m_StrandPoints[" << j << "] = " << endl;
      (*iter).Point.Dump(os);
   }
   os << endl;

   os << "m_bReflectEnabled = " << m_bReflectEnabled << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfStrandPattern::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfStrandPattern");

//   bmfStrandPattern ptrn;
//
//   //
//   // Test the Pattern Point manipulation methods
//   //
//
//   // Load up some ptrn points
//   std::vector<gpPoint2d> ptrnPnts;
//   ptrnPnts.push_back( gpPoint2d(10,1) );
//   ptrnPnts.push_back( gpPoint2d( 5,1) );
//   ptrnPnts.push_back( gpPoint2d(10,2) );
//   ptrnPnts.push_back( gpPoint2d( 5,2) );
//   ptrnPnts.push_back( gpPoint2d( 0,3) );
//   ptrnPnts.push_back( gpPoint2d(10,4) );
//   ptrnPnts.push_back( gpPoint2d( 5,4) );
//   ptrnPnts.push_back( gpPoint2d(10,5) );
//   ptrnPnts.push_back( gpPoint2d( 5,5) );
//
//   ptrn.AddPatternPoints( ptrnPnts );
//   TRY_TEST( ptrn.GetPatternPointCount() == ptrnPnts.size() );
//
//   // Make sure the class is valid right from the get-go.
//#if defined _DEBUG
//   TRY_TEST( ptrn.AssertValid() );
//#endif
//
//   TRY_TEST( ptrn.GetMaxStrandCount() == ptrn.GetStrandPointCount() );
//
//   ptrnPnts.push_back( gpPoint2d( 0,6) );
//   ptrn.AddPatternPoint( ptrnPnts[ptrnPnts.size()-1] );
//   TRY_TEST( ptrn.GetPatternPointCount() == ptrnPnts.size() );
//
//   std::vector<gpPoint2d> ptrnPnts2 = ptrn.GetPatternPoints();
//   TRY_TEST( ptrnPnts2 == ptrnPnts );
//   for ( StrandIndexType i = 0; i < ptrn.GetPatternPointCount(); i++ )
//   {
//      TRY_TEST( ptrnPnts[i] == ptrn.GetPatternPoint(i) );
//   }
//
//   ptrn.RemovePatternPoint(3);
//   ptrnPnts.erase( ptrnPnts.begin() + 3 );
//   ptrnPnts2 = ptrn.GetPatternPoints();
//   TRY_TEST( ptrnPnts == ptrnPnts2 );
//
//   ptrn.RemoveAllPatternPoints();
//   TRY_TEST( ptrn.GetPatternPointCount() == 0 );
//   TRY_TEST( ptrn.GetStrandPointCount() == 0 );
//
//   //
//   // Test the Reflection state methods
//   //
//
//   bool bReflect;
//   bReflect = ptrn.EnablePointReflection( true ); // set it to a known state
//   TRY_TEST( ptrn.IsPointReflectionEnabled() == true ); // test the state
//   bReflect = ptrn.EnablePointReflection( false ); // reverse the state
//   TRY_TEST( bReflect == true ); // make sure last state was returned
//   TRY_TEST( ptrn.IsPointReflectionEnabled() == false ); // verify state is correct.
//
//   //
//   // Test the strand point methods
//   //
//
//   ptrn.RemoveAllPatternPoints();
//   ptrn.AddPatternPoints( ptrnPnts );
//   StrandIndexType cStrandPoints = 0;
//   for (std::vector<gpPoint2d>::iterator iter = ptrnPnts.begin(); iter < ptrnPnts.end(); iter++ )
//   {
//      const gpPoint2d& p = *iter;
//      cStrandPoints += ( p.X() > 0 ? 2 : 1 );
//   }
//   TRY_TEST( ptrn.GetStrandPointCount() == cStrandPoints );
//
//   // Generate some strand points based on the pattern points
//   std::vector<gpPoint2d> strPnts;
//   for ( iter = ptrnPnts.begin(); iter < ptrnPnts.end(); iter++ )
//   {
//      const gpPoint2d& p = *iter;
//      strPnts.push_back( p );
//      if ( p.X() > 0 )
//      {
//         strPnts.push_back( gpPoint2d( -p.X(), p.Y() ) );
//      }
//   }
//
//   for ( i = 0; i < cStrandPoints; i++ )
//   {
//      gpPoint2d p = ptrn.GetStrandPatternPoint( i );
//      TRY_TEST( p == strPnts[i] );
//   }
//
//   ptrn.EnablePointReflection( true );
//   TRY_TEST( ptrn.SetStrandCount( 2 ) == 0 );
//   TRY_TEST( ptrn.SetStrandCount( 3 ) != 0 );
//   TRY_TEST( ptrn.GetStrandCount() == 2 );
//   TRY_TEST( ptrn.GetStrandPoint(0) == gpPoint2d(10,1) );
//   TRY_TEST( ptrn.GetStrandPoint(1) == gpPoint2d(-10,1) );
//
//   ptrn.EnablePointReflection( false );
//   TRY_TEST( ptrn.SetStrandCount( 3 ) == 0 );
//   TRY_TEST( ptrn.GetStrandPoint(0) == gpPoint2d( 10,1) );
//   TRY_TEST( ptrn.GetStrandPoint(1) == gpPoint2d(-10,1) );
//   TRY_TEST( ptrn.GetStrandPoint(2) == gpPoint2d(  0,1) );
//
//
//   //
//   // Test AddStrand
//   //
//
//   // Reflection Enabled
//   ptrnPnts.clear();
//   ptrnPnts.push_back( gpPoint2d(10,1) );
//   ptrnPnts.push_back( gpPoint2d( 5,1) );
//   ptrnPnts.push_back( gpPoint2d( 0,2) );
//   ptrn.RemoveAllPatternPoints();
//   ptrn.AddPatternPoints( ptrnPnts );
//
//   StrandIndexType inc = 0;
//   ptrn.SetStrandCount( 0 );
//   ptrn.EnablePointReflection( true );
//   for ( i = 0; i < ptrn.GetPatternPointCount(); i++ )
//   {
//      inc = ptrn.AddStrand();
//
//      const gpPoint2d& pnt = ptrnPnts[i];
//      if ( pnt.X() > 0 )
//         TRY_TEST( inc == 2 )
//      else
//         TRY_TEST( inc == 1 )
//   }
//   TRY_TEST( ptrn.AddStrand() == 0 );
//   TRY_TEST( ptrn.GetStrandPointCount() == ptrn.GetStrandCount() );
//
//   // Reflection disabled
//   ptrnPnts.clear();
//   ptrnPnts.push_back( gpPoint2d(10,1) );
//   ptrnPnts.push_back( gpPoint2d( 5,1) );
//   ptrnPnts.push_back( gpPoint2d( 0,2) );
//   ptrn.RemoveAllPatternPoints();
//   ptrn.AddPatternPoints( ptrnPnts );
//
//   ptrn.SetStrandCount( 0 );
//   ptrn.EnablePointReflection( false );
//   for ( i = 0; i < ptrn.GetStrandPointCount(); i++ )
//   {
//      inc = ptrn.AddStrand();
//      TRY_TEST( inc == 1 );
//   }
//   TRY_TEST( ptrn.AddStrand() == 0 );
//   TRY_TEST( ptrn.GetStrandPointCount() == ptrn.GetStrandCount() );
//
//   //
//   // Test RemoveStrand
//   //
//
//   // Reflection enabled
//   ptrnPnts.clear();
//   ptrnPnts.push_back( gpPoint2d(10,1) );
//   ptrnPnts.push_back( gpPoint2d( 5,1) );
//   ptrnPnts.push_back( gpPoint2d( 0,2) );
//   ptrn.RemoveAllPatternPoints();
//   ptrn.AddPatternPoints( ptrnPnts );
//
//   ptrn.SetStrandCount( ptrn.GetStrandPointCount() );
//   TRY_TEST( ptrn.AddStrand() == 0 );
//   ptrn.EnablePointReflection( true );
//   for ( i = 0; i < ptrn.GetPatternPointCount(); i++ )
//   {
//      inc = ptrn.RemoveStrand();
//
//      const gpPoint2d& pnt = ptrnPnts[ptrn.GetPatternPointCount() - i - 1];
//      if ( pnt.X() > 0 )
//         TRY_TEST( inc == 2 )
//      else
//         TRY_TEST( inc == 1 )
//   }
//   TRY_TEST( ptrn.RemoveStrand() == 0 );
//   TRY_TEST( ptrn.GetStrandCount() == 0 );
//
//   // Reflection Disabled
//   ptrnPnts.clear();
//   ptrnPnts.push_back( gpPoint2d(10,1) );
//   ptrnPnts.push_back( gpPoint2d( 5,1) );
//   ptrnPnts.push_back( gpPoint2d( 0,2) );
//   ptrn.RemoveAllPatternPoints();
//   ptrn.AddPatternPoints( ptrnPnts );
//
//   ptrn.SetStrandCount( ptrn.GetStrandPointCount() );
//   TRY_TEST( ptrn.AddStrand() == 0 );
//   ptrn.EnablePointReflection( false );
//   for ( i = 0; i < ptrn.GetStrandPointCount(); i++ )
//   {
//      inc = ptrn.RemoveStrand();
//      TRY_TEST( inc == 1 );
//   }
//   TRY_TEST( ptrn.RemoveStrand() == 0 );
//   TRY_TEST( ptrn.GetStrandCount() == 0 );
//
//   // Test RemoveAllStrands
//   ptrn.SetStrandCount( ptrn.GetStrandPointCount() );
//   TRY_TEST( ptrn.AddStrand() == 0 );
//   ptrn.RemoveAllStrands();
//   TRY_TEST( ptrn.RemoveStrand() == 0 );
//   TRY_TEST( ptrn.GetStrandCount() == 0 );
//
//   // Test SetStrandCount
//   ptrn.RemoveAllPatternPoints();
//   ptrn.EnablePointReflection(true);
//   ptrn.AddPatternPoint( gpPoint2d(10,1 ) );
//   ptrn.AddPatternPoint( gpPoint2d(20,1 ) );
//   ptrn.AddPatternPoint( gpPoint2d(30,1 ) );
//   TRY_TEST( ptrn.SetStrandCount( 3 ) == 4 );
//   TRY_TEST( ptrn.SetStrandCount( 4 ) == 0 );
//   TRY_TEST( ptrn.SetStrandCount( 7 ) == 6 );
//
//   // Test GetCenterOfGravity
//   ptrn.RemoveAllPatternPoints();
//   ptrn.EnablePointReflection(true);
//   ptrn.AddPatternPoint( gpPoint2d(10,1 ) );
//   ptrn.AddPatternPoint( gpPoint2d(10,2 ) );
//   ptrn.AddPatternPoint( gpPoint2d(10,3 ) );
//   TRY_TEST( ptrn.GetCenterOfGravity(1) == gpPoint2d(10,1) );
//   TRY_TEST( ptrn.GetCenterOfGravity(2) == gpPoint2d( 0,1) );
//   TRY_TEST( ptrn.GetCenterOfGravity(4) == gpPoint2d( 0,1.5) );
//
//   ptrn.EnablePointReflection(false);
//   TRY_TEST( ptrn.GetCenterOfGravity(3) == gpPoint2d(0,4./3.) );

   TESTME_EPILOG("StrandPattern");
}
#endif // _UNITTEST

///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2012  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEMODELING_STRANDPATTERN_H_
#define INCLUDED_BRIDGEMODELING_STRANDPATTERN_H_
#pragma once

#include <BridgeModeling\BridgeModelingExp.h>

// SYSTEM INCLUDES
//
#include <set>
#include <MathEx.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfStrandPattern

   This class encapsulates a prestressed girder strand pattern.


DESCRIPTION
   This class encapsulates a prestressed girder strand pattern.  Strand
   patterns are symmetrical about the Y axis.  This class can be used for
   both straight and harped patterns.

   Pattern Point = Point used to define a strand pattern
                   If the x coordinate of a pattern point is greater than
                   zero,  the pattern point defines two strand points 
                   located symmetrically about the Y axis.

   Strand Point = Point in the actual strand pattern.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.02.1998 : Created file
*****************************************************************************/
class BMFCLASS bmfStrandPattern
{
public:
   struct PatternPoint
   {
      PatternPoint() { bCanDebond = false; }
      bool operator==(const PatternPoint& rOther) const { return Point == rOther.Point && bCanDebond == rOther.bCanDebond; }
      gpPoint2d Point;
      bool bCanDebond;
   };

   struct StrandPoint : public PatternPoint
   {
      StrandPoint() : PatternPoint() { FillSequence = -1; bHasStrand = false; bIsDebonded = false; }
      StrandPoint(const PatternPoint& p) { Point = p.Point; bCanDebond = p.bCanDebond; FillSequence = -1; bHasStrand = false; bIsDebonded = false; }
      bool operator==(const StrandPoint& rOther) const
      { return FillSequence == rOther.FillSequence && bHasStrand == rOther.bHasStrand && bIsDebonded == rOther.bIsDebonded; }
      StrandIndexType FillSequence;
      bool bHasStrand;
      bool bIsDebonded;
   };

   struct Row
   {
      Float64 Elevation;
      std::vector<StrandIndexType> StrandPoints;
      bool operator==(const Row& rOther) const { ::IsEqual(Elevation,rOther.Elevation); }
      bool operator<(const Row& rOther) const { return Elevation < rOther.Elevation; }
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfStrandPattern();

   //------------------------------------------------------------------------
   // Copy constructor
   bmfStrandPattern(const bmfStrandPattern& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfStrandPattern();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   bmfStrandPattern& operator = (const bmfStrandPattern& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Adds a pattern point to this strand pattern
   void AddPatternPoint(const PatternPoint& p);

   //------------------------------------------------------------------------
   // Adds a vector of pattern points.
   void AddPatternPoints(const std::vector<PatternPoint>& points);

   //------------------------------------------------------------------------
   // Returns the number of pattern points.
   StrandIndexType GetPatternPointCount() const;

   //------------------------------------------------------------------------
   // Returns a pattern point
   PatternPoint GetPatternPoint(StrandIndexType idx) const;

   //------------------------------------------------------------------------
   // Returns all the pattern points
   std::vector<PatternPoint> GetPatternPoints() const;

   //------------------------------------------------------------------------
   // Removes a pattern point
   void RemovePatternPoint(StrandIndexType idx);

   //------------------------------------------------------------------------
   // Removes all pattern points and sets the number of strands to zero.
   void RemoveAllPatternPoints();

   //------------------------------------------------------------------------
   // If enabled, pattern points that are located off of the Y axis are always
   // reflected about the Y axes.  If disabled,  off axis pattern points are
   // moved to the Y axes if the strand count is such that the -X strand point
   // is not needed.  (This is enabled for straight strands and disabled from
   // harped strands. We want the odd harped strand to move to the Y axis).
   // Returns the current state.
   bool EnablePointReflection(bool bEnable);

   //------------------------------------------------------------------------
   // Returns true if PointReflection is enabled.
   bool IsPointReflectionEnabled() const;

   //------------------------------------------------------------------------
   // Returns the number of strand points in this pattern.
   StrandIndexType GetStrandPointCount() const;

   //------------------------------------------------------------------------
   // Returns the maximum number of strands that can be in this pattern.
   // Returns same as GetStrandPointCount().
   StrandIndexType GetMaxStrandCount() const;

   //------------------------------------------------------------------------
   // Returns the coordinates of a point in the strand pattern,  make no
   // adjustments for reflection.
   gpPoint2d GetStrandPatternPoint(StrandIndexType idx) const;

   //------------------------------------------------------------------------
   // Returns the coordinates of a particular strand,  make adjustments for
   // reflection.
   gpPoint2d GetStrandPoint(StrandIndexType iStrand) const;

   //------------------------------------------------------------------------
   // Returns the coordinates for a debond strand point
   const StrandPoint* GetDebondStrandPoint(StrandIndexType idxDebond) const;
   StrandPoint* GetDebondStrandPoint(StrandIndexType idxDebond);

   //------------------------------------------------------------------------
   // Add one or more strands in accordance with the strand pattern.  Returns
   // the number of strands added.  Returns zero when no more strands can
   // be added.
   StrandIndexType AddStrand();

   //------------------------------------------------------------------------
   // Removes one or more strands in accordance with the strand pattern. 
   // Returns the number of strands removed.  Returns zero when no more strands
   // can be removed.
   StrandIndexType RemoveStrand();

   //------------------------------------------------------------------------
   // Removes all the strands from the pattern.
   void RemoveAllStrands();

   //------------------------------------------------------------------------
   // Tests is nStrands is a valid strand count.  If nStrands cannot be fit
   // into the strand pattern,  the next highest number of strands is returned,
   // or the max number of strands is returned if nStrands is greater than the
   // max.  Zero is returned if nStrands is a valid strand count.
   StrandIndexType TestStrandCount(StrandIndexType nStrands) const;

   //------------------------------------------------------------------------
   // Tests is nStrands is a valid strand count.  If nStrands cannot be fit
   // into the strand pattern,  the next highest number of strands is returned,
   // or the max number of strands is returned if nStrands is greater than the
   // max.  Zero is returned if nStrands is a valid strand count.
   StrandIndexType TestDebondStrandCount(StrandIndexType nStrands) const;

   //------------------------------------------------------------------------
   // Sets the strand count.  If nStrands cannot be fit into the strand pattern,
   // the next highest number of strands is returned, or the max number of
   // strands is returned if nStrands is greater than the max, and the strand
   // count is not modified.  Zero is returned if the strand count is successfully
   // changed.
   StrandIndexType SetStrandCount(StrandIndexType nStrands);

   //------------------------------------------------------------------------
   // Returns the number of strands in the pattern.
   StrandIndexType GetStrandCount() const;

   //------------------------------------------------------------------------
   // Returns the number of rows that contain strand
   RowIndexType GetNumRowsWithStrand() const;

   //------------------------------------------------------------------------
   // Returns the number of strands currently in a row
   StrandIndexType GetNumStrandsInRow(RowIndexType rowIndex) const;

   //------------------------------------------------------------------------
   // Returns the number of strands currently in a row
   StrandIndexType GetNumDebondStrandsInRow(RowIndexType rowIndex) const;

   //------------------------------------------------------------------------
   // Returns true if an exterior strand in the given row is debonded
   bool IsExteriorStrandDebondedInRow(RowIndexType rowIndex) const;

   //------------------------------------------------------------------------
   // Returns the maximum number of debonded strands for the given total 
   // number of strands
   StrandIndexType GetMaxDebondStrandCount(StrandIndexType nStrands) const;
   StrandIndexType GetMaxDebondStrandCount() const;

   //------------------------------------------------------------------------
   // Add one or more debonded strands in accordance with the strand pattern.  Returns
   // the number of strands added.  Returns zero when no more strands can
   // be added.
   StrandIndexType AddDebondedStrand();

   //------------------------------------------------------------------------
   // Removes one or more debonded strands in accordance with the strand pattern. 
   // Returns the number of strands removed.  Returns zero when no more strands
   // can be removed.
   StrandIndexType RemoveDebondedStrand();

   //------------------------------------------------------------------------
   // Returns the number of debonded strands in the pattern.
   StrandIndexType GetDebondStrandCount() const;

   //------------------------------------------------------------------------
   // Sets the strand count.  If nStrands cannot be fit into the strand pattern,
   // the next highest number of strands is returned, or the max number of
   // strands is returned if nStrands is greater than the max, and the strand
   // count is not modified.  Zero is returned if the strand count is successfully
   // changed.
   StrandIndexType SetDebondStrandCount(StrandIndexType nStrands);

   //------------------------------------------------------------------------
   // Returns the debond length
   Float64 GetDebondLength() const;
   void SetDebondLength(Float64 l);

   //------------------------------------------------------------------------
   // Returns true if the strand is debonded
   bool IsStrandDebonded(StrandIndexType iStrand) const;

   //------------------------------------------------------------------------
   // Returns the center of gravity for the strands currently in the strand
   // pattern.
   gpPoint2d GetCenterOfGravity() const;

   //------------------------------------------------------------------------
   // Returns the center of gravity for nStrands.  The number of strands
   // currently in the strand pattern is ignored.  
   //
   // WARNING: This method will compute the cg for nStrands even if
   //          TestStrandCount() returns non-zero.
   gpPoint2d GetCenterOfGravity(StrandIndexType nStrands) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const bmfStrandPattern& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfStrandPattern& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::vector<PatternPoint> m_PtrnPoints;
   std::vector<StrandPoint> m_StrandPoints;
   std::set<Row> m_Rows;

   bool m_bReflectEnabled;
   Float64 m_DebondLength;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//


// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_STRANDPATTERN_H_

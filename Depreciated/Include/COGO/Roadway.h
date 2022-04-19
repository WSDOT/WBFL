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

#ifndef INCLUDED_COGO_ROADWAY_H_
#define INCLUDED_COGO_ROADWAY_H_
#pragma once

// SYSTEM INCLUDES
//
#include <list>
#include <vector>
#include <Cogo\CogoExp.h>
#include <Cogo\CogoDirection.h>
#include <Cogo\Curve.h>
#include <Cogo\VCurve.h>
#include <System\SubjectT.h>
#include <GeometricPrimitives\Primitives.h>
#include <GeometricPrimitives\LineSegment2d.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class cogoModel;
class cogoRoadway;
class cogoProfile;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   cogoRoadwayObserver

   A pure virtual entry class for observing cogoRoadway objects.


DESCRIPTION
   A pure virtual entry class for observing cogoRoadway objects.
   Presently,  the hint field is not used.

COPYRIGHT
   Copyright © 1999-2022
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 07.20.1998 : Created file
*****************************************************************************/
class COGOCLASS cogoRoadwayObserver
{
public:

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   virtual ~cogoRoadwayObserver() {}

   //------------------------------------------------------------------------
   // Called by our subject to let us now he's changed.
   // The hint parameter isn't used
   virtual void Update(cogoRoadway* pSubject, Uint32 hint) = 0;
};

/*****************************************************************************
CLASS 
   cogoRoadway

   Encapsulates a roadway alignment.

DESCRIPTION
   Because the COGO model is very young, it is highly likely
   that it will be improved to handle things such as chains,
   paths, and alignments.  This class has been named cogoRoadway
   so that the name cogoAlignment can be used later, when it is
   more meaningful

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 05.09.1997 : Created file
*****************************************************************************/
//#pragma warning ( disable : 4231 )
COGOTPL sysSubjectT<cogoRoadwayObserver, cogoRoadway>;
typedef sysSubjectT<cogoRoadwayObserver, cogoRoadway> cogoRoadwayBase;

class COGOCLASS cogoRoadway : public cogoRoadwayBase
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructs an alignment heading due east with station 0+00 at 0,0
   cogoRoadway();

   //------------------------------------------------------------------------
   // Constructs an alignment heading due east with station 0+00 at
   // the point specified by id.
   cogoRoadway(Int32 id,cogoModel* pCogoModel);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~cogoRoadway(); 

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Locates a point at an offset normal to the roadway.
   // Positive offsets are considered to the left, when looking
   // ahead on station.
   // The point is stored in the cogo model.
   Int32 LocatePoint(Float64 station,      // station from which the point is to be located
                     Float64 offset = 0.); // offset from roadway

   //------------------------------------------------------------------------
   // Locates a point at an offset and direction from a station.
   // Negative offsets are considered to be in the opposite
   // direction of the direction arguement.
   // The point is stored in the cogo model.
   Int32 LocatePoint(Float64 station,     // station from which the point is to be located
                     Float64 offset,      // offset from roadway
                     const cogoDirection& direction);  // offset direction (absoulte bearing)

   //------------------------------------------------------------------------
   // Locates a point at a offset normal to the roadway.
   // Positive offsets are considered to the left, when looking
   // ahead on station.
   // The point is stored in the cogo model.
   void LocatePoint(gpPoint2d* pPoint,
                    Float64 station,      // station from which the point is to be located
                    Float64 offset = 0.   // offset from roadway
                    ) const;
 
   //------------------------------------------------------------------------
   // Locates a point at a distance and direction from a station.
   // The point is stored in the cogo model.
   void LocatePoint(gpPoint2d* pPoint,
                    Float64 station,   // station from which the point is to be located
                    Float64 offset,    // offset from the station
                    const cogoDirection& direction  // direction of offset
                    ) const; 


   //------------------------------------------------------------------------
   // Computes the bearing of alignment at the specified station.
   cogoDirection BearingAtStation(Float64 station) const;

   //------------------------------------------------------------------------
   // Computes the bearing of a line that is normal to the alignment at
   // the specified station
   cogoDirection BearingOfNormal(Float64 station) const;

   //------------------------------------------------------------------------
   // Computes the normal offset and station for the specified point
   void GetStationAndOffset(const gpPoint2d& pnt,Float64* pStation,Float64* pOffset) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the reference station from the roadway.
   // This is the station at the reference point.
   // All stationing is referenced to this station.
   // Calls Notify().
   void SetStation(Float64 refStation);

   //------------------------------------------------------------------------
   // Retreives the reference station.
   Float64 GetStation() const;

   //------------------------------------------------------------------------
   // Returns a pointer to the associated CogoModel
   const cogoModel* GetCogoModel() const;

   //------------------------------------------------------------------------
   // Returns a pointer to the associated CogoModel
   cogoModel* GetCogoModel();

   //------------------------------------------------------------------------
   // Adds a point to the alignment.  The point is placed at the end of the
   // alignment.  Returns true if successful.
   bool AddPoint(Int32 id);

   //------------------------------------------------------------------------
   // Adds a curve to the alignment.  The curve is placed at the end of the
   // alignment. Returns true if successful.
   bool AddCurve(Int32 id);

   //------------------------------------------------------------------------
   // Creates a profile for this alignment that begins with a grade
   Int32 CreateProfile(Float64 sta1,Float64 elev1,
                       Float64 sta2,Float64 elev2);

   //------------------------------------------------------------------------
   // Creates a profile for this alignment that begins with a vertical curve
   Int32 CreateProfile(const cogoVCurve& vcurve);

   //------------------------------------------------------------------------
   const cogoProfile* GetProfile(Int32 id) const;

   //------------------------------------------------------------------------
   cogoProfile* GetProfile(Int32 id);

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Returns the index of the curve if station is between the start
   // and end of the curve.  Returns -1 if station is not on a curve.
   Int32 IsStationOnCurve(Float64 station) const;

   //------------------------------------------------------------------------
   // Returns the index of the curve if the point is within the bounds of the
   // pie shaped sector made up of by a circular curve.
   // Returns -1 if point is not on the curve
   Int32 IsPointInSector(Float64 station,Float64 offset,const cogoDirection& dir) const;

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   // elements of the alignment.
   // An alignment is described by point and curve elements
   enum ElementType { etPoint, etCurve };
   struct Element
   {
      ElementType Type;
      Int32 ID;
   };
   std::list<Element> m_Elements;

   // alignment segments
   // the curvilinear path of an alignment is made up of segments
   // segments connect the points of and alignment
   // segments can be curves or lines)
   enum SegmentType { stLine, stCurve };
   struct Segment
   {
      SegmentType Type;
      gpLineSegment2d Line;
      cogoCurve Curve;
      Int32 CurveID;

      Float64 StartStation;
      Float64 EndStation;
      Float64 Length;
   };
   mutable std::list<Segment> m_Segments;

   std::vector<cogoProfile> m_Profiles;


   Int32 m_Id;     // Unique identifier for this chain

   Float64 m_Station; // Station of the reference element.  If it is a point, it
                      // is the station of the point.  If it is a curve, it is 
                      // the station of the PC.

   cogoModel* m_pCogoModel; // cogo model of which this roadway is a member.

   // GROUP: LIFECYCLE
   cogoRoadway(const cogoRoadway& /*rOther*/);               // Remove to enable copy

   // GROUP: OPERATORS
   cogoRoadway& operator = (const cogoRoadway& /*rOther*/);  // Remove to enable assignment

   // GROUP: OPERATIONS
   void UpdateSegmentList() const;  // called from const methods
   const Segment& FindSegment(Float64 station) const;
   gpPoint2d GetPointOnAlignment(Float64 station) const;

   Int16 GetCurveCount() const;
   void StationAndOffset1(Float64 station,Float64 offset, Float64 angle,Float64* pStation,Float64* pOffset) const;
   void StationAndOffset2(Float64 station,Float64 offset, Float64 angle,Float64* pStation,Float64* pOffset) const;
   void StationAndOffset3(Float64 station,Float64 offset, Float64 angle,Float64* pStation,Float64* pOffset) const;
   void StationAndOffset4(Float64 station,Float64 offset, Float64 angle,Float64* pStation,Float64* pOffset) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

#if defined _DEBUG
public:
   bool AssertValid() const;
   void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
public:
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_COGO_ROADWAY_H_

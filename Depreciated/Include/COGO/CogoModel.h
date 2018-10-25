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

#ifndef INCLUDED_COGO_COGOMODEL_H_
#define INCLUDED_COGO_COGOMODEL_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>
#include <boost\shared_ptr.hpp>
#include <Cogo\CogoExp.h>
#include <Cogo\IModel.h>
#include <Cogo\ILocate.h>
#include <Cogo\IProject.h>
#include <Cogo\IIntersect.h>
#include <Cogo\IDivide.h>
#include <Cogo\IMeasure.h>
#include <System\NextAvailableId.h>
#include <Cogo\Curve.h>
#include <Cogo\Roadway.h>
#include <Cogo\CogoDirection.h>
#include <Cogo\CogoAngle.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//
#define COGO_ERROR      -1

/*****************************************************************************
CLASS 
   cogoModel

   Provides basic coordinate geometry modeling features

DESCRIPTION
   Provides basic coordinate geometry modeling features

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class COGOCLASS cogoModel : public cogoIModel,
                            public cogoILocate,
                            public cogoIProject,
                            public cogoIIntersect,
                            public cogoIDivide,
                            public cogoIMeasure
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   cogoModel();

   //------------------------------------------------------------------------
   // Destructor
   ~cogoModel(); 

   // GROUP: OPERATORS

   //////////////////////////////////////////////////////////////////////////
   // cogoIModel
   //////////////////////////////////////////////////////////////////////////

   //------------------------------------------------------------------------
   // Stores a new point in the COGO model. Returns point id or COGO_ERROR
   Int32 StorePoint(Float64 x,   // x coordinate
                    Float64 y);  // y coordinate

   //------------------------------------------------------------------------
   // Stores a new point in the COGO model. Returns point id or COGO_ERROR
   Int32 StorePoint(const gpPoint2d& rPnt);

   //------------------------------------------------------------------------
   // Assigns a copy of point id to pnt.  Returns false
   // if point id is not defined in the model.
   bool GetPoint(gpPoint2d* pPnt,Int32 id) const;

   //------------------------------------------------------------------------
   // Retreives a vector of points.  For each point id in id, the 
   // corrosponding point is stored in points.  Returns true
   // if all poitns in id where found, otherwise false. To
   // determine the number of points found, calls points.size().
   bool GetPoints(std::vector<gpPoint2d>* pPoints,
                  const std::vector<Int32>& id) const;

   //------------------------------------------------------------------------
   // Fills points with all of the points in the model.
   void GetPoints(std::vector<gpPoint2d>* pPoints) const;

   //------------------------------------------------------------------------
   // Removes a point from the cogo model.
   bool RemovePoint(Int32 id);

   //------------------------------------------------------------------------
   // Moves the point to a new position
   bool MovePoint(Int32 id, Float64 newX, Float64 newY);

   //------------------------------------------------------------------------
   // Moves the point to a new position
   bool MovePoint(Int32 id, const gpPoint2d& newPoint);

   //------------------------------------------------------------------------
   // Offsets a point
   bool OffsetPoint(Int32 id, Float64 dx, Float64 dy);

   //------------------------------------------------------------------------
   // Offsets a point
   bool OffsetPoint(Int32 id, const gpSize2d& offset);

   // GROUP: OPERATIONS - Curves

   //------------------------------------------------------------------------
   Int32 StoreCurve(const cogoCurve& curve);
   //------------------------------------------------------------------------
   Int32 StoreCurve(const gpPoint2d& pc,const gpPoint2d& pi,const gpPoint2d& pt,const gpPoint2d& cc);
   //------------------------------------------------------------------------
   Int32 StoreCurve(Int32 pc,Int32 pi,Int32 pt,Int32 cc);

   //------------------------------------------------------------------------
   bool GetCurve(cogoCurve* pCurve,Int32 id);

   //------------------------------------------------------------------------
   bool ReplaceCurve(const cogoCurve& curve,Int32 id);

   //------------------------------------------------------------------------
   bool RemoveCurve(Int32 id);

   // GROUP: OPERATIONS - Alignments

   //------------------------------------------------------------------------
   // Creates an Alignment using two points
   Int32 CreateAlignment(Int32 id1,Int32 id2);

   //------------------------------------------------------------------------
   // Creates an Alignment using a curve
   Int32 CreateAlignment(Int32 id);

   //------------------------------------------------------------------------
   // Returns a pointer to a previously created Alignment chain
   cogoRoadway* GetAlignment(Int32 id);

   //------------------------------------------------------------------------
   const cogoRoadway* GetAlignment(Int32 id) const;

   //------------------------------------------------------------------------
   // Destroy a previously created Alignment chain
   bool RemoveAlignment(Int32 id);

   //------------------------------------------------------------------------
   // Clears the entire cogo model.  All points and alignments are destroyed.
   // Point and Alignment indices are reset.
   void Clear();

   //////////////////////////////////////////////////////////////////////////
   // cogoILocate
   //////////////////////////////////////////////////////////////////////////

   //------------------------------------------------------------------------
   // Locates one point from another, using a distance and
   // direction.  A new point is created and stored in the model.
   Int32 LocateByDistDir(Int32 refPointId,   // id of reference point
                         Float64 distance,   // distance from reference point to new point
                         const cogoDirection& direction); // direction between the two points

   //------------------------------------------------------------------------
   // Locates one point from another, using a distance and direction.  
   bool LocateByDistDir(gpPoint2d* pNewPoint,
                        Int32 refPointId,   // id of reference point
                        Float64 distance,   // distance from reference point to new point
                        const cogoDirection& direction); // direction between the two points

   //------------------------------------------------------------------------
   // Locates one point from another, using a distance and
   // direction.  A new point is created and stored in the model.
   Int32 LocateByDistDir(const gpPoint2d& rRefPoint, // reference point
                         Float64 distance,   // distance from reference point to new point
                         const cogoDirection& direction); // direction between the two points

   //------------------------------------------------------------------------
   // Locates a point on a line defined by two other points.
   // A new point is created and stored in the model.
   // If distance is less than zero,  the new point is located
   // on the opposite size of fromPointId than toPointId.
   // Returns id of new point or COGO_ERROR.
   Int32 LocatePointOnLine(Int32 fromPointId,   // id of first point on the line
                           Int32 toPointId,     // id of second point on the line
                           Float64 distance);   // distance from first point to new point

   //------------------------------------------------------------------------
   // Locates a point on a line defined by two other points.
   // If distance is less than zero,  the new point is located
   // on the opposite size of fromPointId than toPointId.
  bool LocatePointOnLine(gpPoint2d* pNewPoint,
                         Int32 fromPointId,   // id of first point on the line
                         Int32 toPointId,     // id of second point on the line
                         Float64 distance) const; // distance from first point to new point

   //------------------------------------------------------------------------
   // Locates a point on a line defined by two other points.
   // A new point is created and stored in the model.
   // If distance is less than zero,  the new point is located
   // on the opposite size of fromPointId than toPointId.
   // Returns id of new point or COGO_ERROR.
   Int32 LocatePointOnLine(const gpPoint2d& fromPoint,
                           const gpPoint2d& toPoint,
                           Float64 distance);   // distance from first point to new point

   //------------------------------------------------------------------------
   // Locates a point by backsight on fromPoint, turning angle
   // on toPoint at a distance of distance. An angle that is
   // less than zero is considered to be counter-clockwise.
   bool LocateByDistAngle(gpPoint2d* pNewPoint,
                          Int32 fromPointID,
                          Int32 toPointId,
                          Float64 distance,
                          const cogoAngle& angle) const;
   Int32 LocateByDistAngle(const gpPoint2d& fromPoint,
                           const gpPoint2d& toPoint,
                           Float64 distance,
                           const cogoAngle& angle);
   Int32 LocateByDistAngle(Int32 fromPointId,
                           Int32 toPointId,
                           Float64 distance,
                           const cogoAngle& angle);

   //------------------------------------------------------------------------
   // Locates a point by backsight on fromPoint, turning angle
   // on toPoint at a distance of distance. An angle that is
   // less than zero is considered to be counter-clockwise.
   bool LocateByDistDefAngle(gpPoint2d* pNewPoint,
                             Int32 fromPointID,
                             Int32 toPointId,
                             Float64 distance,
                             const cogoAngle& angle) const;
   Int32 LocateByDistDefAngle(const gpPoint2d& fromPoint,
                              const gpPoint2d& toPoint,
                              Float64 distance,
                              const cogoAngle& angle);
   Int32 LocateByDistDefAngle(Int32 fromPointId,
                              Int32 toPointId,
                              Float64 distance,
                              const cogoAngle& angle);

   //------------------------------------------------------------------------
   bool LocateParallelLine(gpPoint2d* pStart,
                           gpPoint2d* pEnd,
                           Int32 fromPointId,
                           Int32 toPointId,
                           Float64 distance) const;
   Int32 LocateParallelLine(Int32* pStartId,
                            Int32* pEndId,
                            Int32 fromPointId,
                            Int32 toPointId,
                            Float64 distance);
   Int32 LocateParallelLine(Int32* pStartId,
                            Int32* pEndId,
                            const gpPoint2d& p1,
                            const gpPoint2d& p2,
                            Float64 distance);

   //////////////////////////////////////////////////////////////////////////
   // cogoIProject
   //////////////////////////////////////////////////////////////////////////

   //------------------------------------------------------------------------
   bool ProjectPointOnLine(gpPoint2d* pNewPoint,
                           Int32 fromPointId,
                           Int32 toPointId,
                           Float64 offset,
                           Int32 projPointId) const;
   Int32 ProjectPointOnLine(Int32 fromPointId,
                            Int32 toPointId,
                            Float64 offset,
                            Int32 projPointId);
   Int32 ProjectPointOnLine(const gpPoint2d& fromPoint,
                            const gpPoint2d& toPoint,
                            Float64 offset,
                            const gpPoint2d& projPoint);

   //////////////////////////////////////////////////////////////////////////
   // cogoIIntersect
   //////////////////////////////////////////////////////////////////////////

   //------------------------------------------------------------------------
   bool LineLineIntersect(gpPoint2d* pPoint,
                          Int32 pnt1,const cogoDirection& d1,Float64 offset1,
                          Int32 pnt2,const cogoDirection& d2,Float64 offset2);

   //------------------------------------------------------------------------
   bool LineLineIntersect(gpPoint2d* pPoint,
                          Int32 p1,
                          Int32 p2,
                          Float64 offset1,
                          Int32 p3,
                          Int32 p4,
                          Float64 offset2);

   //------------------------------------------------------------------------
   // Finds the intersection point of the line passing through points p1 and p2
   // and the line passing through p3 and p4.  The intersection points is stored
   // with id id.
   Int32 LineLineIntersect(Int32 p1,
                           Int32 p2,
                           Float64 offset1,
                           Int32 p3,
                           Int32 p4,
                           Float64 offset2);

   //////////////////////////////////////////////////////////////////////////
   // cogoIDivide
   //////////////////////////////////////////////////////////////////////////

   //------------------------------------------------------------------------
   // Divides the line from fromPointId to toPointId into nParts equal
   // length parts. The intermediate points are stored in vPoints.
   // Returns true if successful, otherwise false.
   bool DivideLine(std::vector<gpPoint2d>* pPoints,
                   Int32 fromPointId, Int32 toPointId,Uint16 nParts) const;

   //------------------------------------------------------------------------
   // Divides the line from fromPointId to toPointId into nParts equal
   // length parts. The intermediate points are stored begining with id
   // and incremented by idInc. Care must be taken not to override
   // previously stored points.
   // Returns true if successful, otherwise false.
   bool DivideLine(std::vector<Int32>* pIds,
                   Int32 fromPointId, Int32 toPointId,Uint16 nParts);

   //------------------------------------------------------------------------
   // Divides the line from p1 to p2 into nParts equal
   // length parts. The intermediate points are stored begining with id
   // and incremented by idInc. Care must be taken not to override
   // previously stored points.
   // Returns true if successful, otherwise false.
   void DivideLine(std::vector<Int32>* pIds,
                   const gpPoint2d& p1, const gpPoint2d& p2,Uint16 nParts);

   //------------------------------------------------------------------------
   // Divides the clockwise arc defined by fromId, vertexId, 
   // toId into nParts equal length parts. The intermediate 
   // points are stored in vPoints.  Returns true if successful,
   // otherwise false.
   bool DivideArc(std::vector<gpPoint2d>* pPoints,
                  Int32 fromId,Int32 vertexId,Int32 toId,Uint16 nParts) const;

   //------------------------------------------------------------------------
   // Divides the clockwise arc defined by fromId, vertexId, 
   // toId into nParts equal length parts.
   // The intermediate points are stored begining with id
   // and incremented by idInc. Care must be taken not to override
   // previously stored points.
   // Returns true if successful, otherwise false.
   bool DivideArc(std::vector<Int32>* pIds,
                  Int32 fromId,Int32 vertexId,Int32 toId,Uint16 nParts);

   //------------------------------------------------------------------------
   // Divides the clockwise arc defined by fromPnt, vertex, 
   // toPnt into nParts equal length parts.
   // The intermediate points are stored begining with id
   // and incremented by idInc. Care must be taken not to override
   // previously stored points.
   // Returns true if successful, otherwise false.
   void DivideArc(std::vector<Int32>* pIds,
                  const gpPoint2d& fromPnt,const gpPoint2d& vertex,const gpPoint2d& toPnt,Uint16 nParts);


   //////////////////////////////////////////////////////////////////////////
   // cogoIMeasure
   //////////////////////////////////////////////////////////////////////////

   //------------------------------------------------------------------------
   bool ComputeArea(Float64* pArea,const std::vector<Int32>& vPointIds) const;

   //------------------------------------------------------------------------
   // Computes the clockwise angle at vertexId from fromId
   // to toId. Returns true if successful.
   bool ComputeAngle(cogoAngle* pAngle,Int32 fromId,Int32 vertexId,Int32 toId) const;

   //------------------------------------------------------------------------
   // Computes the inverse between two points
   bool Inverse(Float64* pDistance,   // Distance between points
                cogoDirection* pDirection,  // Direction from point 1 to point 2
                Int32 fromPointId,     // id of point 1 - from point
                Int32 toPointId) const; // id of point 2 - to point

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   #pragma warning (disable : 4251) // no need to export private data

   typedef std::map<Int32, gpPoint2d> PointContainer;
   typedef PointContainer::iterator PointIterator;
   typedef PointContainer::const_iterator ConstPointIterator;
   PointContainer m_Points;

   typedef std::map<Int32, cogoCurve> CurveContainer;
   typedef CurveContainer::iterator CurveIterator;
   typedef CurveContainer::const_iterator ConstCurveIterator;
   CurveContainer m_Curves;

   typedef std::map<Int32,boost::shared_ptr<cogoRoadway> > AlignmentContainer;
   typedef AlignmentContainer::iterator AlignmentIterator;
   typedef AlignmentContainer::const_iterator ConstAlignmentIterator;
   typedef std::pair<Int32,boost::shared_ptr<cogoRoadway> > AlignmentEntry;
   AlignmentContainer m_Alignments;

   sysNextAvailableId m_PointIdMgr;
   sysNextAvailableId m_CurveIdMgr;
   sysNextAvailableId m_AlignmentIdMgr;

   // GROUP: LIFECYCLE
   cogoModel(const cogoModel& /*rOther*/); // Prevent accidental copying

   // GROUP: OPERATORS
   cogoModel& operator = (const cogoModel& /*rOther*/);  // Prevent accidental assignment

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns a reference to the requested point
   gpPoint2d* GetPoint(Int32 id);
   const gpPoint2d* GetPoint(Int32 id) const;

   //------------------------------------------------------------------------
   // Returns a reference to the requested curve
   cogoCurve* GetCurve(Int32 id);
   const cogoCurve* GetCurve(Int32 id) const;

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

#endif // CogoModel_H_

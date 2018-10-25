///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_GEOMETRY_POLYGON2D_H_
#define INCLUDED_GEOMETRY_POLYGON2D_H_
#pragma once

// SYSTEM INCLUDES
//
#include <vector>

// PROJECT INCLUDES
//
#include <GeometricPrimitives\GeometryExp.h>
#include <GeometricPrimitives\Primitives.h>
#include <GeometricPrimitives\Line2d.h>

// FORWARD DECLARATIONS
//
class gpPolyPointIter2d;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gpPolygon2d

   gpPolygon2d encapsulates the notion of straight-sided polygon. The polygon
   is described by its vertex points.


DESCRIPTION
   gpPolygon2d encapsulates the notion of straight-sided polygon. The polygon
   is described by its vertex points.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.23.1997 : Created file
*****************************************************************************/

class GEOMCLASS gpPolygon2d
{
   friend gpPolyPointIter2d;
public:

   enum ClipRegion { In, Out };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gpPolygon2d();

   //------------------------------------------------------------------------
   // Copy constructor
   gpPolygon2d(const gpPolygon2d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpPolygon2d();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gpPolygon2d& operator = (const gpPolygon2d& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // AddPoint
   // Adds a point to the polygon.  Returns a key that can be used to lookup 
   // the point in later operations.
   Uint32 AddPoint(const gpPoint2d& p);

   //------------------------------------------------------------------------
   // RemovePoint
   // Removes a point from the polygon.  If the point could not be found,  
   // this method does nothing.  Returns true if the point was successfully 
   // removed,  otherwise false.
   bool RemovePoint(Uint32 key);

   //------------------------------------------------------------------------
   // GetPoint
   // Returns a pointer  to the point identified by key.  If the point could not
   // be found,  returns -0.
   const gpPoint2d* GetPoint(Uint32 key) const;

   //------------------------------------------------------------------------
   // ReplacePoint
   // Replaces the point identified by key with point p.  Returns true on 
   // success,  otherwise return false.
   bool ReplacePoint(Uint32 key, const gpPoint2d& p);

   //------------------------------------------------------------------------
   // GetNumPoints
   // Returns the number of vertex points on the polygon.
   CollectionIndexType GetNumPoints() const;

   //------------------------------------------------------------------------
   // Clear
   // Removes all vertex points from the polygon.
   void Clear();

   //------------------------------------------------------------------------
   // Contains
   // Returns true if point is contained within this polygon,  otherwise 
   // returns false. Points on the polygon boundary are considered contained.
   // Postpone implementation until needed.
   bool Contains(const gpPoint2d& point) const;

   //------------------------------------------------------------------------
   // Perimeter
   // Returns the perimeter of the polygon.
   Float64 Perimeter() const;

   //------------------------------------------------------------------------
   // GetProperties
   // Returns the centroidal properties of the polygon. Properties for counter-
   // clockwise defined polygons are positive, for clockwise-defined polygons, 
   // they are negative.
   void GetProperties(Float64* Area,Float64* Ixx,Float64* Iyy,
               Float64* Ixy, gpPoint2d* centroid) const;

   //------------------------------------------------------------------------
   // GetArea
   // Returns the area and location of the centroid of the polygon. Less 
   // computationally expensive than GetProperties if only the area is needed.
   void GetArea(Float64* Area, gpPoint2d* centroid) const;

   //------------------------------------------------------------------------
   // BoundingBox
   // Returns a gpRect2d which defines the bounding box of the polygon.
   gpRect2d GetBoundingBox() const;

   //------------------------------------------------------------------------
   // Offset
   // Offsets this polygon by the given delta arguments. This polygon is 
   // changed by translating its control points by the given distance.  
   // Returns a reference to this polygon.
   gpPolygon2d& Offset(Float64 dx,Float64 dy);
   gpPolygon2d& Offset(const gpSize2d& size);

   //------------------------------------------------------------------------
   // Rotate
   // Rotates this polygon about the given center point by the given angle 
   // (in radians). This is changed. Returns a reference to this polygon.
   gpPolygon2d& Rotate(const gpPoint2d& centerPoint, Float64 angle);

   //------------------------------------------------------------------------
   // CreateClippedPolygon
   // Clips this polygon against line.  Returns the portion of the polygon on
   // the side of the line defined by side.  This is a factory method.  You 
   // are responsible for freeing the memory allocated by this method.  If the
   // polygon lies entirely on the clipping side of the line 0 is returned.
   gpPolygon2d* CreateClippedPolygon(const gpLine2d& line,
                                     gpLine2d::Side side) const;

   //------------------------------------------------------------------------
   // CreateClippedPolygon
   // Clips this polygon against rectangle r.  Returns the portion that is in
   // or out of the rectangle as specified by region.  This is a factory 
   // method.  You are responsible for freeing memory allocated by this method.
   // This method returns 0 if, the polygon lies entirely within the clipping 
   // rectangle and region is set to clip out, or the polygon and the rectangle
   // do not intersect and region is to clip in.
   gpPolygon2d* CreateClippedPolygon(const gpRect2d& r,
                                     gpPolygon2d::ClipRegion region
                                     ) const;

   //------------------------------------------------------------------------
   // GetFurthestDistance
   // Returns the distance to a line that is parallel to line, on specified 
   // side of line,  that passes through the furthest point on the shape from
   // line. Distance can be negative.
   virtual Float64 GetFurthestDistance(const gpLine2d& line,
                               gpLine2d::Side side) const;


   //------------------------------------------------------------------------
   // Reserve
   // For optimization only. Reserves memory for polygon points. Calling this 
   // prior to adding points will reduce the number of calls made to the allocator
   // if you know the number of points in the polygon beforehand.
   void Reserve(CollectionIndexType size);

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const gpPolygon2d& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gpPolygon2d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   typedef std::pair<Uint32,gpPoint2d> PointEntry;
   typedef std::vector<PointEntry>        PointContainer;
   typedef PointContainer::iterator    PointIterator;
   typedef PointContainer::const_iterator ConstPointIterator;

   // GROUP: DATA MEMBERS

   PointContainer m_PointContainer;
   Uint32         m_LastKey;        // the last key issued.

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   void GetPointIter(Uint32 key, ConstPointIterator& rIter) const
   {
      // guess where key is located - this will be the place unless a point has been removed
      if (key>=0 && !m_PointContainer.empty())
      {
         ConstPointIterator the_begin = m_PointContainer.begin();
         if (key<m_PointContainer.size())
         {
            rIter=the_begin;
            rIter+=key;
         }
         else
         {
            rIter=m_PointContainer.end();
            rIter--;
         }

         // 
         bool done = false;
         while(!done)
         {
            // return directly when key has been found
            if (rIter->first==key)
               return;

            if (rIter==the_begin)
            {
               // not found
               done = true;
               rIter=m_PointContainer.end();
            }
            else
            {
               rIter--;
            }
         }
      }
      else
      {
         // key out of range, or container empty
         rIter=m_PointContainer.end();
      }
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

/*****************************************************************************
CLASS 
   gpPolyPointIter2d

   This is a helper class used to iterate through the points in a gmPolygon
   object.  gmPolyPointIter does an insertion order traversal of the points
   in the gmPolygon it is associated with.


DESCRIPTION
   The gmPolyPointIter class will implement the standard iterator methods
   Begin(), End(), Next(),  and operator void *().  The
   standard GetCurrent() iterator method for this class is described below.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.17.1997 : Created file
*****************************************************************************/

class GEOMCLASS gpPolyPointIter2d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gpPolyPointIter2d();

   //------------------------------------------------------------------------
   // gpPolyPointIter2d
   // Explicit constructor.  Creates an iterator that iterates through the 
   // points in pPolygon.
   gpPolyPointIter2d(const gpPolygon2d* const pPolygon);

   //------------------------------------------------------------------------
   // Copy constructor
   gpPolyPointIter2d(const gpPolyPointIter2d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpPolyPointIter2d();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gpPolyPointIter2d& operator = (const gpPolyPointIter2d& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // SetPolygon
   // Sets the polygon for iteration.  Sets the iterator position to Begin().
   void SetPolygon(const gpPolygon2d* const pPolygon);

   //------------------------------------------------------------------------
   // Begin
   // Moves the iterator to the beginning of  the iteration sequence.
   virtual void Begin();

   //------------------------------------------------------------------------
   // End
   // Moves the iterator to the end of the iteration sequence.  The end point 
   // is one past the last element.
   virtual void End();

   //------------------------------------------------------------------------
   // Next
   // Moves the iterator to the next position in the iteration sequence.
   virtual void Next();

   //------------------------------------------------------------------------
   // Prev
   // Moves the iterator to the previous position in the iteration sequence.
   virtual void Prev();

   //------------------------------------------------------------------------
   // Conversion operator to void pointer. This function converts the object
   // in the collection currently pointed to a void pointer. If this function
   // returns zero, no object is currently being pointed to.
   operator void *();
   operator void*() const;

   //------------------------------------------------------------------------
   // CurrentPoint
   // Returns a pointer to the constant current point or a null pointer if 
   // nothing exists.
   const gpPoint2d* CurrentPoint() const;

   //------------------------------------------------------------------------
   // CurrentKey
   // Returns a pointer to the current key.  If there is not a current 
   // element,  returns 0.
   const Uint32* CurrentKey() const;


   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const gpPolyPointIter2d& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gpPolyPointIter2d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   const gpPolygon2d*    m_pPolygon;
   gpPolygon2d::ConstPointIterator  m_Iterator;
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   void Clean();

   // GROUP: ACCESS
   // GROUP: INQUIRY
};


#endif // INCLUDED_GEOMETRY_POLYGON2D_H_

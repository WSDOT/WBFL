///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#ifndef INCLUDED_GEOMMODEL_POLYGON_H_
#define INCLUDED_GEOMMODEL_POLYGON_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>
#include <GeomModel\GeomModelExp.h>
#include <GeomModel\ShapeImp.h>
#include <GeometricPrimitives\Polygon2d.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gmPolyPointIter;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gmPolygon

   Class which defines a straight-sided polygon


DESCRIPTION
   Derived from gmShapeImp,  gmPolygon realizes the gmShapeImp interface with a
   general polygon.  The points of a polygon can be entered in clockwise or
   counter-clockwise order.  The last point need not be the same as the first
   point,  the polygon will automatically be closed when computing
   properties.  It is common to create a polygon in a convenient coordinate
   system, and then use the Translate() and Rotate() methods to position the
   polygon.  The first point stored in the polygon is the hook point.

   In general, it is not a good idea to subclass gmPolygon to represent
   regular polygons or shapes with a fixed number of sides.  Consider a
   rectangle class that is a subclass of gmPolygon.  The rectangle could be
   defined by its center point, its height, and its width.  The user could
   then call AddPoint().  After calling AddPoint(),  the rectangle is no
   longer a rectangle.  It is better to subclass gmShapeImp and use gmPolygon as
   an implementation helper then it is to subclass gmPolygon itself.



COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.13.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmPolygon : public gmShapeImp, public gmIShapeEx
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // My friend, the iterator
   friend gmPolyPointIter;

   //------------------------------------------------------------------------
   // Default constructor
   gmPolygon();

   //------------------------------------------------------------------------
   // Explicit constructor - construct from a gpPolygon2d
   gmPolygon(const gpPolygon2d& rp);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmPolygon();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // AddPoint
   // Adds a point to the polygon.  Returns a key that can be used to lookup 
   // the point in later operations. Key is unique for this polygon only and 
   // is not unique for all polygons in the system.
   Uint32 AddPoint(const gpPoint2d& p);

   //------------------------------------------------------------------------
   // Clear
   // Remove all points from the polygon.
   void Clear();

   //------------------------------------------------------------------------
   // RemovePoint
   // Removes a point from the polygon.  If the point could not be found,  
   // this method does nothing.  Returns true if the point was successfully
   // removed,  otherwise false.
   bool RemovePoint(Uint32 key);

   //------------------------------------------------------------------------
   // GetPoint
   // Returns a pointer  to the point identified by key.  If the point could 
   // not be found,  returns -0.
   const gpPoint2d* GetPoint(Uint32 key) const;

   //------------------------------------------------------------------------
   // GetNumPoints
   // Returns the number of points in the polygon
   CollectionIndexType GetNumPoints() const;

   //------------------------------------------------------------------------
   // ReplacePoint
   // Replaces the point identified by key with point p.  Returns true on 
   // success,  otherwise return false.
   bool ReplacePoint(Uint32 key,const gpPoint2d& p);

   //------------------------------------------------------------------------
   // CreateClone
   // Creates a clone of this broadcaster.  If bRegisterListeners is true the 
   // listeners are registered with the clone.  This is a factory method,  
   // you are responsible for freeing the memory allocated by this method.
   virtual gmIShape* CreateClone(bool bRegisterListeners = false) const;

   //------------------------------------------------------------------------
   // GetProperties
   // Assigns a gmProperties object to the object pointed to by pProperties. 
   // The origin of the shape properties object is the centroid of this shape
   // with a rotation of zero.
   virtual void GetProperties(gmProperties* pProperties) const;

   //------------------------------------------------------------------------
   // GetBoundingBox
   // Returns the smallest rectangle that bounds the entire shape.
   virtual gpRect2d GetBoundingBox() const;

   //------------------------------------------------------------------------
   // CreateClippedShape
   // Clips this shape against line.  Clips away the portion of the shape on the
   // side of the line defined by side.  This is a factory method.  You are 
   // responsible for freeing the memory allocated by this method.  If the shape
   // lies entirely on the clipping side of the line 0 is returned. Any listeners
   // to the original section are not transferred to this new section.
   virtual gmIShape* CreateClippedShape(const gpLine2d& line, 
                                       gpLine2d::Side side) const;

   //------------------------------------------------------------------------
   // CreateClippedShape
   // Clips this shape against rectangle r.  Clips in or out of the rectangle
   // as specified by region.  This is a factory method.  You are responsible 
   // for freeing memory allocated by this method.  This method returns 0 if, 
   // the shape lies entirely within the clipping rectangle and region is set 
   // to clip out, or the shape and the rectangle do not intersect and region 
   // is to clip in. Any listeners to the original section are not transferred
   // to this new section.
   virtual gmIShape* CreateClippedShape(const gpRect2d& r,
                                        gmShapeImp::ClipRegion region
                                        ) const;

   //------------------------------------------------------------------------
   // GetArea
   // Returns area and cg of shape. Typically faster that getting the properties 
   // and then the area.
   virtual void GetArea(Float64* pArea, gpPoint2d* pCG) const;

   //------------------------------------------------------------------------
   // ComputeClippedArea
   // Clips this shape against line and computes area and CG of remaining shape.
   // Clips away the portion of the shape on the side of the line defined by side. 
   virtual void ComputeClippedArea(const gpLine2d& line, gpLine2d::Side side,
                                   Float64* pArea, gpPoint2d* pCG) const;

   //------------------------------------------------------------------------
   // GetFurthestDistance
   // Returns the distance to a line that is parallel to line, on specified 
   // side of line,  that passes through the furthest point on the shape 
   // from line.
   virtual Float64 GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const;

   //------------------------------------------------------------------------
   // Draw
   // Draws the shape on the given device context.  Mapping of the coordinates
   // to the device space should be done using the supplied point mapper.
   // Draw is for static displays only.  The drawing of this analytical 
   // model is not intended for interactive, graphical editing.  Interactive 
   // graphical editing is best left for a package specifically designed for 
   // this purpose, such as jKit/GO.  In a package like jKit/GO,  a GO object
   // would most likely delegate its drawing responsibility to the gmShapeImp 
   // object it represents.
   // Subject to removal if we can ever figure out the MVC stuff
   virtual void Draw(HDC hDC, const grlibPointMapper& mapper) const;


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

   //------------------------------------------------------------------------
   // Copy constructor
   gmPolygon(const gmPolygon& rOther);

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gmPolygon& operator = (const gmPolygon& rOther);
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // DoTranslate
   // Called by the framework went the shape is to be translated.
   virtual void DoTranslate(const gpSize2d& delta);

   //------------------------------------------------------------------------
   // DoRotate
   // Called by the framework went the shape is to be rotated.
   virtual void DoRotate(const gpPoint2d& center, Float64 angle);

   //------------------------------------------------------------------------
   void MakeCopy(const gmPolygon& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gmPolygon& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   gpPolygon2d    m_PolygonImp;     // polygon geometry implementation

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//


/*****************************************************************************
CLASS 
   gmPolyPointIter

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

class GEOMMODELCLASS gmPolyPointIter
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gmPolyPointIter();

   //------------------------------------------------------------------------
   // gmPolyPointIter
   // Explicit constructor.  Creates an iterator that iterates through the 
   // points in pPolygon.
   gmPolyPointIter(const gmPolygon* pPolygon);

   //------------------------------------------------------------------------
   // Copy constructor
   gmPolyPointIter(const gmPolyPointIter& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmPolyPointIter();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gmPolyPointIter& operator = (const gmPolyPointIter& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // SetPolygon
   // Sets the polygon for iteration.  Sets the iterator position to Begin().
   void SetPolygon(const gmPolygon* pPolygon);

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
   void MakeCopy(const gmPolyPointIter& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gmPolyPointIter& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   const gmPolygon*    m_pPolygon;
   gpPolyPointIter2d   m_Iterator;
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   void Clean();

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//




#endif // INCLUDED_GEOMMODEL_POLYGON_H_

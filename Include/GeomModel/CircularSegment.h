///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_GEOMMODEL_CIRCULARSEGMENT_H_
#define INCLUDED_GEOMMODEL_CIRCULARSEGMENT_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeomModel\GeomModelExp.h>
#include <GeomModel\ShapeImp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gmPolygon;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gmCircularSegmentSegment

   Derived from gmShapeImp, this class represents a CircularSegment primitive. 


DESCRIPTION
   The CircularSegment is described by its radius, mid-ordinate, and rotation.
   The hook point for a CircularSegment is the mid-point of the straight edge.

COPYRIGHT
   Copyright (c) 2000
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.19.2000 : Created
*****************************************************************************/

class GEOMMODELCLASS gmCircularSegment : public gmShapeImp
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Creates a Circle with radius equal 
   // to zero,  with its hook point at (0,0).
   gmCircularSegment();

   //------------------------------------------------------------------------
   // gmCircularSegment
   gmCircularSegment(const gpPoint2d& center,Float64 radius,Float64 midOrdinate,Float64 rotation);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmCircularSegment();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // SetHookPoint
   // Sets the location of the hook point to hookPnt.  Returns the previous 
   // hook point location.
   gpPoint2d SetHookPoint(const gpPoint2d& hookPnt);

   //------------------------------------------------------------------------
   // GetHookPoint
   // Returns the location of the hook point.
   gpPoint2d GetHookPoint() const;

   //------------------------------------------------------------------------
   // SetCenter
   // Sets the location of the center.  Returns the previous 
   // center location.
   gpPoint2d SetCenter(const gpPoint2d& center);

   //------------------------------------------------------------------------
   // GetCenter
   // Returns the location of the center point.
   gpPoint2d GetCenter() const;

   //------------------------------------------------------------------------
   // SetRadius
   // Sets the Radius of the Circle.  Returns the previous Radius.
   Float64 SetRadius(Float64 radius);

   //------------------------------------------------------------------------
   // GetRadius
   // Returns the Radius of the Circle.
   Float64 GetRadius() const;

   //------------------------------------------------------------------------
   // SetMidOrdinate
   // Sets the mid-ordinate. Returns the previous value.
   Float64 SetMidOrdinate(Float64 mo);

   //------------------------------------------------------------------------
   // GetMidOrdinate
   // Returns the mid-ordinate
   Float64 GetMidOrdinate() const;

   //------------------------------------------------------------------------
   // SetRotation
   // Sets the rotation. Returns the previous value.
   Float64 SetRotation(Float64 rotation);

   //------------------------------------------------------------------------
   // GetRotation
   // Returns the rotation
   Float64 GetRotation() const;

   //------------------------------------------------------------------------
   // SetInteriorAngle
   // Sets the interior angle. Returns the previous value.
   Float64 SetInteriorAngle(Float64 ia);

   //------------------------------------------------------------------------
   // GetInteriorAngle
   // Returns the interior angle
   Float64 GetInteriorAngle() const;

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
   // CreateClone
   // Creates a clone of this broadcaster.  If bRegisterListeners is true the 
   // listeners are registered with the clone.  This is a factory method,  
   // you are responsible for freeing the memory allocated by this method.
   virtual gmIShape* CreateClone(bool bRegisterListeners = false) const;

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
   // Clips this shape against Circle r.  Clips in or out of the Circle
   // as specified by region.  This is a factory method.  You are responsible 
   // for freeing memory allocated by this method.  This method returns 0 if, 
   // the shape lies entirely within the clipping Circle and region is set 
   // to clip out, or the shape and the Circle do not intersect and region 
   // is to clip in. Any listeners to the original section are not transferred
   // to this new section.
   virtual gmIShape* CreateClippedShape(const gpRect2d& r,
                                        gmShapeImp::ClipRegion region
                                        ) const;

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

   // Prevent accidental copying and assignment
   gmCircularSegment(const gmCircularSegment&);
   gmCircularSegment& operator=(const gmCircularSegment&);

   // GROUP: OPERATORS
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
   void MakeCopy(const gmCircularSegment& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gmCircularSegment& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   Float64   m_Radius;
   gpPoint2d m_HookPoint;
   gpPoint2d m_Center;
   Float64   m_MidOrdinate;
   Float64   m_Rotation;

   // GROUP: LIFECYCLE


   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   gmPolygon* CreatePolygon() const;
   void UpdateHookPoint();
   void EdgePoints(gpPoint2d* p1,gpPoint2d* p2) const;
   gpLine2d BoundaryLine() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GEOMMODEL_CIRCULARSEGMENT_H_

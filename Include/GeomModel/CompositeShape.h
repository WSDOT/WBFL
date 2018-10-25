///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_GEOMMODEL_COMPOSITESHAPE_H_
#define INCLUDED_GEOMMODEL_COMPOSITESHAPE_H_
#pragma once

// SYSTEM INCLUDES
//
#include<map>
#include <GeomModel\GeomModelExp.h>
#include <GeomModel\ShapeImp.h>
#include <boost\shared_ptr.hpp>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gmShapeIter;
class gmConstShapeIter;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gmCompositeShape

   Derived from gmShapeImp,  this unique shape allows very complex shapes to be
   modeled as a collection of primitive shapes.


DESCRIPTION
   In addition to the interface specified below,  this class implements the
   standard broadcaster interface.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.17.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmCompositeShape : public gmShapeImp
{
   friend gmShapeIter;
   friend gmConstShapeIter;
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gmCompositeShape();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmCompositeShape();

   // GROUP: OPERATORS

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // CreateClone
   // Creates a clone of this broadcaster.  If bRegisterListeners is true the 
   // listeners are registered with the clone.  This is a factory method,  
   // you are responsible for freeing the memory allocated by this method.
   virtual gmIShape* CreateClone(bool bRegisterListeners = false) const;

   //------------------------------------------------------------------------
   // CreateClippedShape
   // Clips this composite against line.  Clips away the portion of the 
   // shapes in the composite that are on the side of the line defined by 
   // side.  This is a factory method.  You are responsible for freeing the 
   // memory allocated by this method.  If the section lies entirely on the 
   // clipping side of the line 0 is returned. Any listeners to the original
   // section are not transferred to this new section.
   virtual gmIShape* CreateClippedShape(const gpLine2d& line, gpLine2d::Side side
                                       ) const;

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
   // Clips this composite against rectangle r.  Clips in or out of the 
   // rectangle as specified by region.  This is a factory method.  You 
   // are responsible for freeing memory allocated by this method.  This 
   // method returns 0 if, the composite lies entirely within the clipping
   // rectangle and region is set to clip out, or the composite and the 
   // rectangle do not intersection and region is to clip in. Any listeners
   // to the original section are not transferred to this new section.
   virtual gmIShape* CreateClippedShape(const gpRect2d& r,
                                        gmShapeImp::ClipRegion region
                                       ) const;

   //------------------------------------------------------------------------
   // MakeSolid
   // Calls MakeSolid() for all shapes in the composite.
   virtual void MakeSolid(bool flag);

   //------------------------------------------------------------------------
   // EnableBorderMode
   // Enables or disables the border drawing mode of the composite.  This method enables/disables the border mode of all the shapes currently in the composite.  
   virtual bool EnableBorderMode(bool bEnable);

   //------------------------------------------------------------------------
   // SetBorderColor
   // Sets the border color of all the shapes currently in the composite to 
   // color.  Returns the previous color setting.
   virtual COLORREF SetBorderColor(COLORREF color);

   //------------------------------------------------------------------------
   // EnableFillMode
   // Sets the fill mode of the composite.  This method sets the fill mode 
   // of all the shapes currently in the composite.  All shapes subsequently
   // added to the composite will have their fill mode set as well.  Returns
   // the previous fill mode setting.
   virtual bool EnableFillMode(bool bEnable);

   //------------------------------------------------------------------------
   // SetFillColor
   // Sets the fill color of all the shapes currently in the composite to 
   // color. Returns the previous color setting.
   virtual COLORREF SetFillColor(COLORREF color);

   //------------------------------------------------------------------------
   // Draw
   // Draws the composite by calling Draw() for every shape in the composite.
   virtual void Draw(HDC hDC, const grlibPointMapper& mapper) const;

   //------------------------------------------------------------------------
   // AddShape
   // Adds shape rShape to the composite.  Creates a clone of rShape and 
   // stores it.  If bRegisterListeners is true the rShape’s listeners 
   // are registered with the clone.  Calls SetParent() for the clone.
   // Returns a lookup key for the clone.
   // It is legal,  but not always wise,  to add shapes that overlap 
   // to a composite.  The only time overlapping shapes make sense is
   // when one of the shapes is hollow and the other is solid. 
   Uint32 AddShape(const gmIShape& rShape, bool bRegisterListeners = false);

   //------------------------------------------------------------------------
   // RemoveShape
   // Removes a shape from the composite and frees the memory allocated by 
   // the call CreateClone() in AddShape().  If the composite does not 
   // contain a shape associated with the provided key,  this method does
   // nothing (the debugging version issues a WARNing).  Returns true if 
   // the shape was successfully removed,  otherwise false.
   bool RemoveShape(Uint32 key);

   //------------------------------------------------------------------------
   // Clear
   // Removes all shapes from the composite
   void Clear();

   //------------------------------------------------------------------------
   // GetShape
   // Returns a pointer to a shape identified by key.  If the shape could not
   // be found 0 is returned.
   // This is consistent with iterators
   const gmIShape* GetShape(Uint32 key) const;
   gmIShape* GetShape(Uint32 key);

   //------------------------------------------------------------------------
   // GetNumShapes
   // Returns the number of shapes currently in the composite
   CollectionIndexType GetNumShapes() const;

   //------------------------------------------------------------------------
   // GetFurthestDistance
   // Returns the distance to a line that is parallel to line, on specified 
   // side of line,  that passes through the furthest point on the shape 
   // from line.
   virtual Float64 GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const;

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
   gmCompositeShape(const gmCompositeShape& rOther);

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   gmCompositeShape& operator = (const gmCompositeShape& rOther);

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
   void MakeCopy(const gmCompositeShape& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gmCompositeShape& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   typedef boost::shared_ptr<gmIShape>         ShapePtr;
   typedef std::pair<Uint32, ShapePtr>    ShapeEntry;
   typedef std::map<Uint32,ShapePtr,std::less<Uint32>,std::allocator<ShapePtr> >      ShapeContainer;
   typedef ShapeContainer::iterator       ShapeIterator;
   typedef ShapeContainer::const_iterator ConstShapeIterator;

   ShapeContainer m_ShapeContainer;
   Uint32         m_LastKey;
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

/*****************************************************************************
CLASS 
   gmShapeIter

   This is a helper class used to iterate through the shapes in a 
   gmCompositeShape object.  This iterator can be used to alter the shapes 
   in the composite.

DESCRIPTION
   The gmShapeIter class will implement the standard iterator methods
   Begin(), End(), Next(),  and operator void *().  The
   standard GetCurrent() iterator method for this class is described below.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.17.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmShapeIter
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gmShapeIter();

   //------------------------------------------------------------------------
   // gmShapeIter
   // Explicit constructor.  Creates an iterator that iterates through the 
   // points in pShape
   gmShapeIter(gmCompositeShape* pShape);

   //------------------------------------------------------------------------
   // Copy constructor
   gmShapeIter(const gmShapeIter& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmShapeIter();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gmShapeIter& operator = (const gmShapeIter& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // SetComposite
   // Sets the gmCompositeShape for iteration.  Sets the iterator position 
   // to Begin().
   void SetComposite(gmCompositeShape* pShape);

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
   operator void*() const;

   //------------------------------------------------------------------------
   // CurrentShape
   // Returns a pointer to the constant current point or a null pointer if 
   // nothing exists.
   gmIShape* CurrentShape() const;

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
   void MakeCopy(const gmShapeIter& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gmShapeIter& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   gmCompositeShape*                m_pComposite;
   gmCompositeShape::ShapeIterator  m_Iterator;

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

/*****************************************************************************
CLASS 
   gmConstShapeIter

   This is a helper class used to iterate through the shapes in a 
   gmCompositeShape object.  This iterator can be used to alter the shapes 
   in the composite.

DESCRIPTION
   The gmConstShapeIter class will implement the standard iterator methods
   Begin(), End(), Next(),  and operator void *().  The
   standard GetCurrent() iterator method for this class is described below.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.17.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmConstShapeIter
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gmConstShapeIter();

   //------------------------------------------------------------------------
   // gmConstShapeIter
   // Explicit constructor.  Creates an iterator that iterates through the 
   // points in pShape
   gmConstShapeIter(const gmCompositeShape* pShape);

   //------------------------------------------------------------------------
   // Copy constructor
   gmConstShapeIter(const gmConstShapeIter& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmConstShapeIter();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gmConstShapeIter& operator = (const gmConstShapeIter& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // SetComposite
   // Sets the gmCompositeShape for iteration.  Sets the iterator position 
   // to Begin().
   void SetComposite(const gmCompositeShape* pShape);

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
   operator void*() const;

   //------------------------------------------------------------------------
   // CurrentShape
   // Returns a pointer to the constant current point or a null pointer if 
   // nothing exists.
   const gmIShape* CurrentShape() const;

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
   void MakeCopy(const gmConstShapeIter& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gmConstShapeIter& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   const gmCompositeShape*    m_pComposite;
   gmCompositeShape::ConstShapeIterator  m_Iterator;

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

#endif // INCLUDED_GEOMMODEL_COMPOSITESHAPE_H_

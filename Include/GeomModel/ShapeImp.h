///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#ifndef INCLUDED_GEOMMODEL_SHAPEIMP_H_
#define INCLUDED_GEOMMODEL_SHAPEIMP_H_
#pragma once

// SYSTEM INCLUDES
//
#include <set>
#include <GeomModel\GeomModelExp.h>
#include <GeomModel\IShape.h>
#include <GeometricPrimitives\GeometricPrimitives.h>
#include <GeomModel\ShapeListener.h>

// FORWARD DECLARATIONS
//
class gmCompositeShape;
class gmProperties;
class grlibPointMapper;
class gmShapeListener;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gmShapeImp

   A shape is a representation of the boundary contour of something.  A shape
   could represent the boundary of a section through a structural member or
   the boundary of a parcel of land.  Composite shapes composed of primitive
   geometric shapes, such as circles and polygons, can be created to
   represent complex shapes.  The geometric properties of primitive and
   complex shapes can be computed.


DESCRIPTION
   This abstract base class provides a framework for extending the shape
   modeling package through inheritance.  Subclass authors simply
   override/implement the protected virtual methods to create a specific
   shape type.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.11.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmShapeImp : public gmIShape
{
   friend gmCompositeShape;
public:

   // GROUP: ENUMERATIONS
   // GROUP: LIFECYCLE

   // Default constructor
   gmShapeImp();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmShapeImp();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Translate
   // Translates a shape by a delta amount.
   void Translate(const gpSize2d& delta);

   //------------------------------------------------------------------------
   // Move
   // Move a shape by moving from one point in space to another. 
   virtual void Move(LocatorPoint point,const gpPoint2d& to);
   virtual void Move(const gpPoint2d& from,const gpPoint2d& to);

   //------------------------------------------------------------------------
   // Rotate
   // Rotates a shape.  The rotation is centered about point center.  The 
   // rotation angle is measured in radians counter clockwise.
   void Rotate(const gpPoint2d& center, Float64 angle);

   //------------------------------------------------------------------------
   // GetLocatorPoint
   // Returns a point located at the specified location on the bounding box 
   // around the shape.
   gpPoint2d GetLocatorPoint(LocatorPoint point) const;

   //------------------------------------------------------------------------
   // IsContained
   // Tests if point p is contained within the boundary of the shape.  Returns
   // the containment state of point p.
   // virtual gmShapeImp::Containment IsContained(const gpPoint2d& p) const = 0;

   //------------------------------------------------------------------------
   // MakeSolid
   // Makes this shape represent a solid area if isSolid is true. If not shape
   // is hollow
   virtual void MakeSolid(bool isSolid);

   //------------------------------------------------------------------------
   // IsSolid
   // Returns true if this shape represents a solid,  otherwise returns false.
   bool IsSolid() const;

   //------------------------------------------------------------------------
   //BorderMode
   // Enable/disables the border drawing mode of the shape.  If bEnable is 
   // true,  a border will be drawn around the shape in the border color.  
   // Border mode is enabled by default.  Returns the previous border mode 
   // setting.
   virtual bool EnableBorderMode(bool bEnable);

   //------------------------------------------------------------------------
   // IsBorderModeEnabled
   // Returns true if the border mode is enabled,  otherwise false.
   bool IsBorderModeEnabled() const;

   //------------------------------------------------------------------------
   // SetBorderColor
   // Sets the border color to color.  Returns the previous color setting.  
   // Notifies listeners through the OnDisplayAttributesChanged() method.
   virtual COLORREF SetBorderColor(COLORREF color);

   //------------------------------------------------------------------------
   // GetBorderColor
   // Returns the border color.
   COLORREF GetBorderColor() const;

   //------------------------------------------------------------------------
   // EnableFillMode
   // Enables/disables the fill mode of the shape.  If bEnable is true,  
   // the shape will be filled with the fill color.  Fill mode is enabled by 
   // default.  Returns the previous fill mode setting.
   virtual bool EnableFillMode(bool bEnable);

   //------------------------------------------------------------------------
   // IsFillModeEnabled
   // Returns true if the fill mode is enabled, otherwise false.
   bool IsFillModeEnabled() const;

   //------------------------------------------------------------------------
   // SetFillColor
   // Sets the fill color to color. Returns the previous color setting. 
   // Notifies listeners through the OnDisplayAttributesChanged() method.
   virtual COLORREF SetFillColor(COLORREF color);

   //------------------------------------------------------------------------
   // GetFillColor
   // Returns the fill color.
   COLORREF GetFillColor() const;

   //------------------------------------------------------------------------
   // GetComposite
   // Returns a pointer to the composite interface if this shape supports it,
   // otherwise returns 0.  The default implementation of this method is to 
   // return zero.  If your subclass supports the gmCompositeShape interface,
   // and you wish to expose it,  override this method and return a pointer 
   // to your implementation of the gmCompositeShape interface.
   virtual gmCompositeShape* GetComposite();
   virtual const gmCompositeShape* GetComposite() const;

   //------------------------------------------------------------------------
   // GetParent
   // Returns a pointer to the parent composite if this shape is a member of 
   // a composite,  otherwise returns 0.
   gmCompositeShape* GetParent();
   const gmCompositeShape* GetParent() const;

   //------------------------------------------------------------------------
   // RegisterListener
   // Registers the listener pointed to by pListener with this object.  
   // Calls gmShapeListener::OnRegistered().  Listeners are notified of 
   // changes to this object through the gmShapeListener interface.
   void RegisterListener(gmShapeListener* pListener);

   //------------------------------------------------------------------------
   // UnregisterListener
   // Unregisters the listener pointed to by pListener from this broadcaster.
   // Calls gmShapeListener::OnUnregistered() immediately before the listener
   // is unregistered. This listener will no longer receive notifications 
   // from the broadcaster.  If the listener pointed to by pListener was not 
   // previously registered with this broadcaster, this method does nothing 
   // (DEBUG builds should issue a WARNing).  If pListener is zero, all 
   // listeners are unregistered.
   void UnregisterListener(const gmShapeListener* pListener);

   //------------------------------------------------------------------------
   // ListenerCount
   // Returns the number of listeners registered with this broadcaster.
   CollectionIndexType ListenerCount() const;

   //------------------------------------------------------------------------
   // BeginDamage
   // Clients of a broadcaster should call this method prior to making 
   // wholesale changes to the broadcaster.  This method disables the 
   // listener notification mechanism.  In the damaged state,  a broadcaster 
   // does not broadcast.  This call must be paired with a call to EndDamage().
   // This method increments the damaged count by one. .
   void BeginDamage();

   //------------------------------------------------------------------------
   // EndDamage
   // Clients of a broadcaster should call this method after making wholesale 
   // changes to the broadcaster.  This method enables the listener notification
   // mechanism.  All listeners are notified when this method is called if the 
   // damaged count is zero.  Implementers must decide what listener callback(s)
   // is called.  In the damaged state,  a broadcaster does not broadcast.  
   // This call must be paired with a call to BeginDamage().  This call 
   // decrements the damage count by one.  If the damage count is at zero,
   // this method does nothing.
   void EndDamage();

   //------------------------------------------------------------------------
   // IsDamaged
   // Returns true if the broadcaster is in a damaged state (damaged count is 
   // greater than zero), otherwise returns false.
   bool IsDamaged() const;

   //------------------------------------------------------------------------
   // DamagedCount
   // Returns the number of times EndDamage() must be called to enable the 
   // listener notification mechanism.
   Int32 DamagedCount() const;


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
   gmShapeImp(const gmShapeImp& rOther);

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   gmShapeImp& operator = (const gmShapeImp& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // SetParent
   // Called by gmCompositeShape when inserted into a composite.  pParent 
   // must be returned in any subsequent calls to GetParent().
   void SetParent(gmCompositeShape* pParent);

   //------------------------------------------------------------------------
   // DoTranslate
   // Called by the framework went the shape is to be translated.
   virtual void DoTranslate(const gpSize2d& delta) = 0;

   //------------------------------------------------------------------------
   // DoRotate
   // Called by the framework went the shape is to be rotated.
   virtual void DoRotate(const gpPoint2d& center, Float64 angle) = 0;

   //------------------------------------------------------------------------
   // DoRegisterListeners
   // Helper function that takes the listeners from pOwner and registers them
   // with this shape. This function will be useful in the CreateClone() 
   // member function of derived shapes.
   virtual void DoRegisterListeners(const gmShapeImp& rOwner);

   //------------------------------------------------------------------------
   void MakeCopy(const gmShapeImp& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gmShapeImp& rOther);

   //------------------------------------------------------------------------
   // NotifyAllListeners
   // This method provides subclassed broadcasters a method of notifying 
   // listeners through the base class interface. lHint is a hint as to
   // what type of change was made as described in gmShapeListener.h
   virtual void NotifyAllListeners( Int32 lHint );

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   // general properties
   bool m_IsSolid;                    // hollow or solid
   gmCompositeShape* m_pParent;       // pointer to parent if in a composite
   bool m_BorderMode;                 // if true, draw border
   bool m_FillMode;                   // if true, draw filling
   COLORREF m_BorderColor;            // border color
   COLORREF m_FillColor;              // fill color

   // listeners
   typedef std::set<gmShapeListener*> ListenerList;
   typedef ListenerList::iterator ListenerListIterator;
   typedef ListenerList::const_iterator ConstListenerListIterator;

   ListenerList m_ListenerList;
   Int32        m_DamageCount;     // net # of BeginDamages() - EndDamages
   Int32        m_DamageTypeTally; // running tally that tracks type of damage done 
                                   // while in damage mode

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   void Clean();

   //------------------------------------------------------------------------
   void DoRegisterListener(gmShapeListener* pListener);


   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GEOMMODEL_SHAPE_H_

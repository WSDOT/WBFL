///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_GEOMMODEL_ISHAPE_H_
#define INCLUDED_GEOMMODEL_ISHAPE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeomModel\GeomModelExp.h>
#include <GeometricPrimitives\Line2d.h>

// LOCAL INCLUDES
//


// FORWARD DECLARATIONS
//
class gmCompositeShape;
class gmProperties;
class grlibPointMapper;
class gmShapeListener;
class gpRect2d;

// MISCELLANEOUS
//


/*****************************************************************************
CLASS 
   gmIShape

   This pure abstract base class provides a framework for extending the shape 
   modeling package through interface inheritance. 

DESCRIPTION
   All member functions in this class must be as pure virtual. Subclass authors 
   simply override/implement the protected virtual methods to create a specific 
   shape type. The gmShapeImp class directly implements many of the functions in
   gmIShape and provides a framework that gmShapeImp derived shapes can use to 
   easily implement the entire gmIShape interface. Most new shape classes should
   be derived from gmShapeImp and not directly from gmIshape.

LOG
   rdp : 12.11.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmIShape
{
   friend gmCompositeShape;
public:

   // GROUP: ENUMERATIONS

   //------------------------------------------------------------------------
   // ClipRegion
   // Defines the region of a rectangle that a shape should be clipped against.
   enum ClipRegion{ In, Out };

   //------------------------------------------------------------------------
   // LocatorPoint
   // Defines the major locator points on a bounding rectangle.
   enum LocatorPoint {TopLeft,    TopCenter,    TopRight,
                      LeftCenter, CenterCenter, RightCenter,
                      BottomLeft, BottomCenter, BottomRight};

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // make distructor virtual to promote proper cleanup
   virtual ~gmIShape() {}

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Translate
   // Translates a shape by a delta amount.
   virtual void Translate(const gpSize2d& delta) =0;

   //------------------------------------------------------------------------
   // Move
   // Move a shape by moving from one point in space to another. 
   virtual void Move(LocatorPoint point,const gpPoint2d& to) =0;
   virtual void Move(const gpPoint2d& from,const gpPoint2d& to) =0;

   //------------------------------------------------------------------------
   // Rotate
   // Rotates a shape.  The rotation is centered about point center.  The 
   // rotation angle is measured in radians counter clockwise.
   virtual void Rotate(const gpPoint2d& center, Float64 angle) =0;

   //------------------------------------------------------------------------
   // GetProperties
   // Assigns a gmProperties object to the object pointed to by pProperties. 
   // The origin of the shape properties object is the centroid of this shape
   // with a rotation of zero.
   virtual void GetProperties(gmProperties* pProperties) const =0;

   //------------------------------------------------------------------------
   // GetBoundingBox
   // Returns the smallest rectangle that bounds the entire shape.
   virtual gpRect2d GetBoundingBox() const =0;

   //------------------------------------------------------------------------
   // GetLocatorPoint
   // Returns a point located at the specified location on the bounding box 
   // around the shape.
   virtual gpPoint2d GetLocatorPoint(LocatorPoint point) const =0;

   //------------------------------------------------------------------------
   // IsContained
   // Tests if point p is contained within the boundary of the shape.  Returns
   // the containment state of point p.
   // virtual gmIShape::Containment IsContained(const gpPoint2d& p) const = 0;

   //------------------------------------------------------------------------
   // CreateClone
   // Creates a clone of this broadcaster.  If bRegisterListeners is true the 
   // listeners are registered with the clone.  This is a factory method,  
   // you are responsible for freeing the memory allocated by this method.
   virtual gmIShape* CreateClone(bool bRegisterListeners = false) const =0;

   //------------------------------------------------------------------------
   // CreateClippedShape
   // Clips this shape against line.  Clips away the portion of the shape on the
   // side of the line defined by side.  This is a factory method.  You are 
   // responsible for freeing the memory allocated by this method.  If the shape
   // lies entirely on the clipping side of the line 0 is returned. Any listeners
   // to the original section are not transferred to this new section.
   virtual gmIShape* CreateClippedShape(const gpLine2d& line, 
                                       gpLine2d::Side side) const = 0;

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
                                        gmIShape::ClipRegion region
                                        ) const = 0;

   //------------------------------------------------------------------------
   // GetFurthestDistance
   // Returns the distance to a line that is parallel to line, on specified 
   // side of line,  that passes through the furthest point on the shape 
   // from line.
   virtual Float64 GetFurthestDistance(const gpLine2d& line,
                               gpLine2d::Side side) const = 0;

   //------------------------------------------------------------------------
   // MakeSolid
   // Makes this shape represent a solid area if isSolid is true. If not shape
   // is hollow
   virtual void MakeSolid(bool isSolid) =0;

   //------------------------------------------------------------------------
   // IsSolid
   // Returns true if this shape represents a solid,  otherwise returns false.
   virtual bool IsSolid() const =0;

   //------------------------------------------------------------------------
   // GetPerimeter
   // This method fills the supplied gpPoint2dVector 
   // (typedef for std::vector<gpPoint2d>) with a polygonal representation of
   // the perimeter of this shape.
   // Do not implement until a need is shown
   // virtual void GetPerimeter(gpPoint2dVector& vPoints) const = 0;

   //------------------------------------------------------------------------
   //BorderMode
   // Enable/disables the border drawing mode of the shape.  If bEnable is 
   // true,  a border will be drawn around the shape in the border color.  
   // Border mode is enabled by default.  Returns the previous border mode 
   // setting.
   virtual bool EnableBorderMode(bool bEnable) =0;

   //------------------------------------------------------------------------
   // IsBorderModeEnabled
   // Returns true if the border mode is enabled,  otherwise false.
   virtual bool IsBorderModeEnabled() const =0;

   //------------------------------------------------------------------------
   // SetBorderColor
   // Sets the border color to color.  Returns the previous color setting.  
   // Notifies listeners through the OnDisplayAttributesChanged() method.
   virtual COLORREF SetBorderColor(COLORREF color) =0;

   //------------------------------------------------------------------------
   // GetBorderColor
   // Returns the border color.
   virtual COLORREF GetBorderColor() const =0;

   //------------------------------------------------------------------------
   // EnableFillMode
   // Enables/disables the fill mode of the shape.  If bEnable is true,  
   // the shape will be filled with the fill color.  Fill mode is enabled by 
   // default.  Returns the previous fill mode setting.
   virtual bool EnableFillMode(bool bEnable) =0;

   //------------------------------------------------------------------------
   // IsFillModeEnabled
   // Returns true if the fill mode is enabled, otherwise false.
   virtual bool IsFillModeEnabled() const =0;

   //------------------------------------------------------------------------
   // SetFillColor
   // Sets the fill color to color. Returns the previous color setting. 
   // Notifies listeners through the OnDisplayAttributesChanged() method.
   virtual COLORREF SetFillColor(COLORREF color) =0;

   //------------------------------------------------------------------------
   // GetFillColor
   // Returns the fill color.
   virtual COLORREF GetFillColor() const =0;

   //------------------------------------------------------------------------
   // Draw
   // Draws the shape on the given device context.  Mapping of the coordinates
   // to the device space should be done using the supplied point mapper.
   // Draw is for static displays only.  The drawing of this analytical 
   // model is not intended for interactive, graphical editing.  Interactive 
   // graphical editing is best left for a package specifically designed for 
   // this purpose, such as jKit/GO.  In a package like jKit/GO,  a GO object
   // would most likely delegate its drawing responsibility to the gmIShape 
   // object it represents.
   // Subject to removal if we can ever figure out the MVC stuff
   virtual void Draw(HDC hDC, const grlibPointMapper& mapper) const = 0;

   //------------------------------------------------------------------------
   // GetComposite
   // Returns a pointer to the composite interface if this shape supports it,
   // otherwise returns 0.  The default implementation of this method is to 
   // return zero.  If your subclass supports the gmCompositeShape interface,
   // and you wish to expose it,  override this method and return a pointer 
   // to your implementation of the gmCompositeShape interface.
   virtual gmCompositeShape* GetComposite() =0;
   virtual const gmCompositeShape* GetComposite() const =0;

   //------------------------------------------------------------------------
   // GetParent
   // Returns a pointer to the parent composite if this shape is a member of 
   // a composite,  otherwise returns 0.
   virtual gmCompositeShape* GetParent() =0;
   virtual const gmCompositeShape* GetParent() const =0;

   //------------------------------------------------------------------------
   // RegisterListener
   // Registers the listener pointed to by pListener with this object.  
   // Calls gmShapeListener::OnRegistered().  Listeners are notified of 
   // changes to this object through the gmShapeListener interface.
   virtual void RegisterListener(gmShapeListener* pListener) =0;

   //------------------------------------------------------------------------
   // UnregisterListener
   // Unregisters the listener pointed to by pListener from this broadcaster.
   // Calls gmShapeListener::OnUnregistered() immediately before the listener
   // is unregistered.  This listener will no longer receive notifications 
   // from the broadcaster.  If the listener pointed to by pListener was not 
   // previously registered with this broadcaster, this method does nothing 
   // (DEBUG builds should issue a WARNing).  If pListener is zero, all 
   // listeners are unregistered.
   virtual void UnregisterListener(const gmShapeListener* pListener) =0;

   //------------------------------------------------------------------------
   // ListenerCount
   // Returns the number of listeners registered with this broadcaster.
   virtual CollectionIndexType ListenerCount() const =0;

   //------------------------------------------------------------------------
   // BeginDamage
   // Clients of a broadcaster should call this method prior to making 
   // wholesale changes to the broadcaster.  This method disables the 
   // listener notification mechanism.  In the damaged state,  a broadcaster 
   // does not broadcast.  This call must be paired with a call to EndDamage().
   // This method increments the damaged count by one. .
   virtual void BeginDamage() =0;

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
   virtual void EndDamage() =0;

   //------------------------------------------------------------------------
   // IsDamaged
   // Returns true if the broadcaster is in a damaged state (damaged count is 
   // greater than zero), otherwise returns false.
   virtual bool IsDamaged() const =0;

   //------------------------------------------------------------------------
   // DamagedCount
   // Returns the number of times EndDamage() must be called to enable the 
   // listener notification mechanism.
   virtual Int32 DamagedCount() const =0;

   //------------------------------------------------------------------------
   // NotifyAllListeners
   // This method provides subclassed broadcasters a method of notifying 
   // listeners through the base class interface. lHint is a hint as to
   // what type of change was made as described in gmShapeListener.h
   // NOTE: Derived versions of this function must call NotifyAllListeners()
   //       for their parents if they are in a composite.
   virtual void NotifyAllListeners( Int32 lHint )=0;


   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const =0;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const =0;
#endif // _DEBUG

protected:

   //------------------------------------------------------------------------
   // SetParent
   // Called by gmCompositeShape when inserted into a composite.  pParent 
   // must be returned in any subsequent calls to GetParent().
   // Developers of gmIShape-derived class must also create composite-friendly
   // classes. This means that you should always notify the parent composite
   // by calling the appropriate SetDirty() function when your class has
   // been modified.
   virtual void SetParent(gmCompositeShape* pParent) =0;

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

/*****************************************************************************
CLASS 
   gmIShapeEx

   This pure abstract base class provides a framework for extending the shape 
   modeling package through interface inheritance. 

DESCRIPTION
   Adds limited capability to gmIShape to make working with r/c section capacity 
   computations more efficient.

LOG
   rdp : 11.11.2001 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmIShapeEx
{
public:
   //------------------------------------------------------------------------
   // GetArea
   // Returns area and cg of shape. Typically faster that getting the properties 
   // and then the area.
   virtual void GetArea(Float64* pArea, gpPoint2d* pCG) const = 0;

   //------------------------------------------------------------------------
   // ComputeClippedArea
   // Clips this shape against line and computes area and CG of remaining shape.
   // Clips away the portion of the shape on the side of the line defined by side. 
   virtual void ComputeClippedArea(const gpLine2d& line, gpLine2d::Side side,
                                   Float64* pArea, gpPoint2d* pCG) const = 0;

};


#endif 

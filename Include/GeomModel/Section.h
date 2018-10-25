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

#ifndef INCLUDED_GEOMMODEL_SECTION_H_
#define INCLUDED_GEOMMODEL_SECTION_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>               // components
#include <set>               // listeners
#include <GeomModel\GeomModelExp.h>
#include <GeomModel\SectionListener.h>
#include <GeometricPrimitives\Line2d.h>
#include <boost\shared_ptr.hpp>

// FORWARD DECLARATIONS
//
class gmSection;
class gmIShape;
class gmElasticProperties;
class gmMassProperties;
class grlibPointMapper;
class gpRect2d;
class gmConstSectionComponentIter;
class gmSectionComponentIter;

// MISCELLANEOUS
//

#if !defined INCLUDED_GEOMMODEL_SHAPELISTENER_H_
#include <GeomModel\ShapeListener.h>
#endif

/*****************************************************************************
CLASS 
   gmSectionComponent

   A gmSectionComponent object provides a wrapper around the shape, material 
   properties,  and tructural-ness of a component in a section.


DESCRIPTION
   A gmSectionComponent object provides a wrapper around the shape, material 
   properties,  and tructural-ness of a component in a section.

   This class is both a listener (to its shapes) and a broadcaster (to section)


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.31.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmSectionComponent : public gmShapeListener
{
   friend gmSection;
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // gmSectionComponent
   // Explicit constructor.  Constructs a component wrapper.  The wrapper 
   // assumes ownership of the memory pointed to by pShape.
   gmSectionComponent(gmIShape* pShape,
                 Float64 modE, Float64 density, 
                 bool bIsStructural);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmSectionComponent();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // CreateClone
   // Creates a clone of the current component. All shapes are cloned and 
   // their listners are copied if bRegisterListeners is true. The newly
   // cloned shapes do not become listners of this.
   gmSectionComponent* CreateClone(bool bRegisterListeners = false) const;

   //------------------------------------------------------------------------
   // GetShape
   // Returns a reference to the shape of this component.
   const gmIShape& GetShape() const;
   gmIShape& GetShape();

   //------------------------------------------------------------------------
   // GetModE
   // Returns the modulus of elasticity of the material.
   Float64 GetModE() const;

   //------------------------------------------------------------------------
   // SetModE
   // Sets the modulus of elasticity of the material. Returns the old modulus.
   Float64 SetModE(Float64 modE);

   //------------------------------------------------------------------------
   // GetDensity
   // Returns the density of the material.
   Float64 GetDensity() const;

   //------------------------------------------------------------------------
   // SetDensity
   // Sets the density of the material. Returns the old density.
   Float64 SetDensity(Float64 density);

   //------------------------------------------------------------------------
   // MakeStructural
   // Makes this component structural.  Structural components contribute to 
   // the mass,  elastic,  and transformed properties of the section.
   void MakeStructural();

   //------------------------------------------------------------------------
   // MakeNonstructural
   // Makes this component non-structural.  Non-structural components 
   // contribute only to the mass properties of the section.
   void MakeNonstructural();

   //------------------------------------------------------------------------
   // IsStructural
   // Returns true if this component is structural,  otherwise returns false.
   bool IsStructural()const;

   //------------------------------------------------------------------------
   // OnUpdate
   // Called by the shape whenever it is changed.
   void OnUpdate(const gmIShape* pShape, Int32 lHint);

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
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   gmIShape*  m_pShape;
   Float64    m_ModE;
   Float64    m_Density;
   bool       m_bIsStructural;
   gmSection* m_pParent;  // can be set by gmSection only.

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor
   gmSectionComponent();
   //------------------------------------------------------------------------
   // Copy constructor
   gmSectionComponent(const gmSectionComponent& rOther);
   //------------------------------------------------------------------------
   // Assignment operator
   gmSectionComponent& operator = (const gmSectionComponent& rOther);
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void SetParent(gmSection* ps);
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

/*****************************************************************************
CLASS 
   gmSection

   A section is a collection of internal components of a structural member. 
   Each component consists of a shape and some associated material
   properties.  A component can be designated as structural or
   non-structural.  Non-structural components do not contribute to the
   elastic or transformed properties of a section,  they do however
   contribute to the mass properties.

   In addition to the interface specified below,  this class implements the
   standard broadcaster interface.



DESCRIPTION
   Calculation of transformed properties of a section are not directly
   supported because gmSection is a low-level component and transformed
   property calculations are often domain-specific and
   specification-dependent. However, gmSection can be indirectly used to
   calculate transformed properties by using an n-factor in place of modE as
   the modulus of elasticity for each of the components. The transformed
   properties then become equivalent to the elastic properties. "Equivalent
   density" can then be easily calculated by dividing the mass per unit
   length by the transformed area. 


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.31.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmSection
{
public:
   // friends
   friend gmSectionComponent;
   friend gmConstSectionComponentIter;
   friend gmSectionComponentIter;
   //------------------------------------------------------------------------
   // ClipRegion
   // Defines the region of a rectangle that a shape should be clipped against.
   enum ClipRegion{ In, Out };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   // Creates a section with no components.
   gmSection();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmSection();

   // GROUP: OPERATORS

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // CreateClone
   // Creates a clone of this broadcaster.  If bRegisterListeners is true the 
   // listeners are registered with the clone.  This is a factory method,  
   // you are responsible for freeing the memory allocated by this method.
   virtual gmSection* CreateClone(bool bRegisterListeners = false) const;

   //------------------------------------------------------------------------
   // Translate
   // Translates a section by a delta amount by translating all the pieces 
   // currently in the section.
   void Translate(const gpSize2d& delta);

   //------------------------------------------------------------------------
   // Rotate
   // Rotates the section about a point by rotating all the pieces currently 
   // in the section. The section is rotated by an amount angle,  measured 
   // in radians counter clockwise from the positive X-axis.
   void Rotate(const gpPoint2d& center, Float64 angle);

   //------------------------------------------------------------------------
   // AddComponent
   // Adds a component to the section.  A component consists of a shape (a clone 
   // of rShape) and the material properties modE and density.  This method 
   // creates a clone of rShape.  If bRegisterListeners is true,  listeners 
   // registered with rShape are registered with the clone as well. If a 
   // shape is modified,  section listeners will be notified through the 
   // gmSectionListener interface.  A lookup key is returned.  This key is 
   // used to access the clone of the shape or its associated material 
   // properties.
   Uint32 AddComponent(const gmIShape& rShape,
                       Float64 modE, Float64 density,
                       bool bIsStructural = true,
                       bool bRegisterListeners = false);

   //------------------------------------------------------------------------
   // GetComponent
   // Returns a pointer to a component identified by key.  If the component 
   // could not be found 0 is returned .
   const gmSectionComponent* GetComponent(Uint32 key) const;
   gmSectionComponent* GetComponent(Uint32 key);

   //------------------------------------------------------------------------
   // RemoveComponent
   // Removes a component (shape and material) from the section and frees 
   // the memory allocated by the call to CreateClone() in AddComponent().
   // If the component could not be found,  this method does nothing (the 
   // debugging version issues a WARNing).  Returns true if the component 
   // was successfully removed,  otherwise false.
   bool RemoveComponent(Uint32 key);

   //------------------------------------------------------------------------
   // Removes all of the components from this section.
   void RemoveAllComponents();

   //------------------------------------------------------------------------
   // GetElasticProperties
   // Assigns the elastic properties of the section to the gmElasticProperties 
   // object pointed to by pProperties.
   void GetElasticProperties(gmElasticProperties* pProperties) const;

   //------------------------------------------------------------------------
   // GetMassProperties
   // Assigns the mass properties of the section to the gmMassProperties 
   // object pointed to by pProperties.
   void GetMassProperties(gmMassProperties* pProperties) const;

   //------------------------------------------------------------------------
   // GetBoundingBox
   // Returns the smallest rectangle that bounds the entire section.  If 
   // bExcludeNonstructualComponents is true,  the bounding box is the 
   // smallest rectangle that bounds all of the structural components.
   gpRect2d GetBoundingBox(bool bExcludeNonstructuralComponents) const;

   //------------------------------------------------------------------------
   // CreateClippedSection
   // Clips this section against line.  Clips away the portion of the shape 
   // on the side of the line defined by side.  This is a factory method.  
   // You are responsible for freeing the memory allocated by this method. 
   // If shape s lies entire on the clipping side of the line 0 is returned.
   // Any listeners to the original section are not transferred to this new 
   // section.
   gmSection* CreateClippedSection(const gpLine2d& line,
                                     gpLine2d::Side side) const;

   //------------------------------------------------------------------------
   // CreateClippedSection
   // Clips this section against rectangle r.  Clips in or out of the 
   // rectangle as specified by region.  This is a factory method.  You 
   // are responsible for freeing memory allocated by this method.  This method
   // returns 0 if, the shape lies entirely within the clipping rectangle and 
   // region is set to clip out, or the shape and the rectangle do not 
   // intersection and region is to clip in. Any listeners to the original 
   // section are not transferred to this new section.
   gmSection* CreateClippedSection(const gpRect2d& r,
                                   gmSection::ClipRegion& region) const;

   //------------------------------------------------------------------------
   // EnableBorderMode
   // Enables or disables the border drawing mode of the composite.  This 
   // method enables/disables the border mode of all the shapes currently 
   // in the composite.  
   void EnableBorderMode(bool bEnable);

   //------------------------------------------------------------------------
   // SetBorderColor
   // Sets the border color of all the shapes currently in the composite to 
   // color.  Returns the previous color setting.
   void SetBorderColor(COLORREF color);

   //------------------------------------------------------------------------
   // EnableFillMode
   // Sets the fill mode of the composite.  This method sets the fill mode of
   // all the shapes currently in the composite.  All shapes subsequently 
   // added to the composite will have their fill mode set as well.  Returns
   // the previous fill mode setting.
   void EnableFillMode(bool bEnable);

   //------------------------------------------------------------------------
   // SetFillColor
   // Sets the fill color of all the shapes currently in the composite to 
   // color. Returns the previous color setting.
   void SetFillColor(COLORREF color);

   //------------------------------------------------------------------------
   // Draw
   // Draws the composite by calling Draw() for every shape in the composite.
   void Draw(HDC hDC, const grlibPointMapper& mapper) const;

   //------------------------------------------------------------------------
   // RegisterListener
   // Registers the listener pointed to by pListener with this object.  
   // Calls gmShapeListener::OnRegistered().  Listeners are notified of 
   // changes to this object through the gmShapeListener interface.
   void RegisterListener(gmSectionListener* pListener);

   //------------------------------------------------------------------------
   // UnregisterListener
   // Unregisters the listener pointed to by pListener from this broadcaster.
   // Calls gmShapeListener::OnUnregistered() immediately before the listener
   // is unregistered. This listener will no longer receive notifications 
   // from the broadcaster.  If the listener pointed to by pListener was not 
   // previously registered with this broadcaster, this method does nothing 
   // (DEBUG builds should issue a WARNing).  If pListener is zero, all 
   // listeners are unregistered.
   void UnregisterListener(const gmSectionListener* pListener);

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

   //------------------------------------------------------------------------
   // NotifyAllListeners
   // This method provides subclassed broadcasters a method of notifying 
   // listeners through the base class interface. lHint is a hint as to
   // what type of change was made as described in gmShapeListener.h
   // pComponent is a pointer to the component in question (if applicable).
   void NotifyAllListeners( Int32 lHint, const gmSectionComponent* pComponent=0 );

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
   // DoRegisterListeners
   // Helper function that takes the listeners from pOwner and registers them
   // with this shape. This function will be useful in the CreateClone() 
   // member function.
   virtual void DoRegisterListeners(const gmSection& rOwner);

   //------------------------------------------------------------------------
   void MakeCopy(const gmSection& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gmSection& rOther);
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   typedef boost::shared_ptr<gmSectionComponent>  ComponentPtr;
   typedef std::pair<Uint32, ComponentPtr>    ComponentEntry;
   typedef std::map<Uint32,ComponentPtr,std::less<Uint32>,std::allocator<ComponentPtr> >      ComponentContainer;
   typedef ComponentContainer::iterator       ComponentIterator;
   typedef ComponentContainer::const_iterator ConstComponentIterator;

   ComponentContainer m_ComponentContainer;
   Uint32             m_LastKey;         // last key used

   // listeners
   typedef std::set<gmSectionListener*,std::less<gmSectionListener*>,std::allocator<gmSectionListener*> > ListenerList;
   typedef ListenerList::iterator ListenerListIterator;
   typedef ListenerList::const_iterator ConstListenerListIterator;

   ListenerList m_ListenerList;
   Int32        m_DamageCount;     // net # of BeginDamages() - EndDamages
   Int32        m_DamageTypeTally; // running tally that tracks type of damage done 
                                   // while in damage mode
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Assignment operator
   gmSection& operator = (const gmSection& rOther);

   //------------------------------------------------------------------------
   // Copy constructor
   gmSection(const gmSection& rOther);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void DoRegisterListener(gmSectionListener* pListener);

   void SetShapeDirty(gmSectionComponent* psc, Int32 lHint);

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
   gmSectionComponentIter

   This is a helper class used to iterate through the components in a 
   gmSection object.  This iterator can be used to alter the components 
   in the Section.

DESCRIPTION
   The gmSectionComponentIter class will implement the standard iterator methods
   Begin(), End(), Next(),  and operator void *().  The
   standard GetCurrent() iterator method for this class is described below.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.17.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmSectionComponentIter
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gmSectionComponentIter();

   //------------------------------------------------------------------------
   // gmSectionComponentIter
   // Explicit constructor.  Creates an iterator that iterates through the 
   // components in pSection
   gmSectionComponentIter(gmSection* pSection);

   //------------------------------------------------------------------------
   // Copy constructor
   gmSectionComponentIter(const gmSectionComponentIter& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmSectionComponentIter();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gmSectionComponentIter& operator = (const gmSectionComponentIter& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // SetSection
   // Sets the gmSection for iteration.  Sets the iterator position 
   // to Begin().
   void SetSection(gmSection* pSection);

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
   // CurrentComponent
   // Returns a pointer to the constant current point or a null pointer if 
   // nothing exists.
   gmSectionComponent* CurrentComponent() const;

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
   void MakeCopy(const gmSectionComponentIter& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gmSectionComponentIter& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   gmSection*                m_pSection;
   gmSection::ComponentIterator  m_Iterator;

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
   gmConstSectionComponentIter

   This is a helper class used to iterate through the components in a 
   gmSection object.  This iterator can be used to alter the components 
   in the Section.

DESCRIPTION
   The gmConstSectionComponentIter class will implement the standard iterator methods
   Begin(), End(), Next(),  and operator void *().  The
   standard GetCurrent() iterator method for this class is described below.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.17.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmConstSectionComponentIter
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gmConstSectionComponentIter();

   //------------------------------------------------------------------------
   // gmConstSectionComponentIter
   // Explicit constructor.  Creates an iterator that iterates through the 
   // components in pSection
   gmConstSectionComponentIter(const gmSection* pSection);

   //------------------------------------------------------------------------
   // Copy constructor
   gmConstSectionComponentIter(const gmConstSectionComponentIter& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmConstSectionComponentIter();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gmConstSectionComponentIter& operator = (const gmConstSectionComponentIter& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // SetSection
   // Sets the gmSection for iteration.  Sets the iterator position 
   // to Begin().
   void SetSection(const gmSection* pSection);

   //------------------------------------------------------------------------
   // Begin
   // Moves the iterator to the beginning of the iteration sequence.
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
   // CurrentComponent
   // Returns a pointer to the constant current component or a null pointer if 
   // nothing exists.
   const gmSectionComponent* CurrentComponent() const;

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
   void MakeCopy(const gmConstSectionComponentIter& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gmConstSectionComponentIter& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   const gmSection*    m_pSection;
   gmSection::ConstComponentIterator  m_Iterator;

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




#endif // INCLUDED_GEOMMODEL_SECTION_H_

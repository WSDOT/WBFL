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

#ifndef INCLUDED_GEOMMODEL_PROPERTIES_H_
#define INCLUDED_GEOMMODEL_PROPERTIES_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeomModel\GeomModelExp.h>
#include <GeometricPrimitives\GeometricPrimitives.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gmProperties

   This class encapsulates the geometric properties of a shape and provides
   property transformation services.


DESCRIPTION
   This class encapsulates the geometric properties of a shape and provides
   property transformation services.

   

   Their are four possible coordinate systems that properties can be
   transformed into: Global (Gx, Gy), Centroidal (Cx,Cy), Principal (Px,Py),
   and User-Defined (Ux,Uy). The geometric properties can be transformed to
   any user-defined another coordinate system by changing the origin and
   rotation parameters.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.04.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmProperties
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Enumerations
   // CoordSystemType 
   // Enum which defines the currently set coordinate system.
   enum CoordSystemType{
 	         Centroidal,    // Origin at centroid of shape and
 			                  //   oriented in global coords
 	         Global,        // Origin at global origin
 	         Principal,     // Origin at centroid of shape and
                           //   oriented in principal direction    
 	         UserDefined};  // Origin and orientation set by user

   //------------------------------------------------------------------------
   // Default constructor
   // Initializes all the properties to zero.
   // The origin of the coordinate system is global (0,0) and the 
   // orientation angle is zero.
   gmProperties();

   //------------------------------------------------------------------------
   // gmProperties
   // Explicit constructor.  Initializes the shape properties in the 
   // Centroidal coordinate system to the given values. 
   // If you want to be able to initialize properties in other coord systems, 
   // you need to add more constructors
   gmProperties(Float64 area,
                 const gpPoint2d& centroid,
                 Float64 ixx, Float64 iyy, Float64 ixy,
                 Float64 yTop, Float64 yBottom,
                 Float64 xLeft, Float64 xRight,
                 Float64 perimeter);

   //------------------------------------------------------------------------
   // Copy constructor
   gmProperties(const gmProperties& rOther);

   //------------------------------------------------------------------------
   // Destructor
   // This destructor is not virtual. It is not envisioned that this class 
   // will be extended through inheritance.
   ~gmProperties();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gmProperties& operator = (const gmProperties& rOther);

   //------------------------------------------------------------------------
   // Adds the rhs properties to this (taking parallel axis theorem into
   // consideration). The bounding boxes are unioned together.
   gmProperties operator+ (const gmProperties& rhs) const;


   //------------------------------------------------------------------------
   // Adds the rhs properties to this (taking parallel axis theorem into
   // consideration).  The bounding boxes are unioned together.
   gmProperties& operator+= (const gmProperties& rhs);


   // GROUP: OPERATIONS

   // SetArea
   // Sets the area of the shape. Returns the old area.
   Float64 SetArea(Float64 area);

   // SetCentroid
   // Sets the centroid of the shape, measured in current coordinates. Returns
   // the old centroid.
   gpPoint2d SetCentroid(gpPoint2d cent);

   // SetIxx
   // sets the moment of inertia about the x axis of the 
   // current coordinate system. Returns the old Ixx.
   Float64 SetIxx(Float64 ixx);

   // SetIyy
   // Sets the moment of inertia about the y axis of the current 
   // coordinate system. Returns the old Ixx.
   Float64 SetIyy(Float64 iyy);

   // SetIxy
   // Returns the product of inertia about the current coordinate system.
   // Returns the old Ixx.
   Float64 SetIxy(Float64 ixy);

   // SetYtop
   // Sets the distance from the centroid to the top edge of the bounding 
   // rectangle. This distance is always given using the centroidal orientation.
   // Returns the old value.
   Float64 SetYtop(Float64 ytop);

   // SetYbottom
   // Sets the distance from the centroid to the bottom edge of the 
   // bounding rectangle. This distance is always given using the centroidal orientation.
   // Returns the old value.
   Float64 SetYbottom(Float64 ybot);

   // SetXleft
   // Sets the distance from the centroid to the left edge of the bounding 
   // rectangle. This distance is always given using the centroidal orientation.
   // Returns the old value.
   Float64 SetXleft(Float64 xleft);

   // SetXright
   // Sets the distance from the centroid to the right edge of the bounding 
   // rectangle. This distance is always given using the centroidal orientation.
   // Returns the old value.
   Float64 SetXright(Float64 xright);

   // SetPerimeter
   // Sets the perimeter of the shape
   Float64 SetPerimeter(Float64 p);

   // Area
   // Returns the area of the shape.
   Float64 Area() const;

   // Centroid
   // Returns the centroid of the shape, measured in current coordinates.
   gpPoint2d Centroid() const;

   // Ixx
   // Returns the moment of inertia about the x axis of the 
   // current coordinate system.
   Float64 Ixx() const;

   // Iyy
   // Returns the moment of inertia about the y axis of the current 
   // coordinate system.
   Float64 Iyy() const;

   // Ixy
   // Returns the product of inertia about the current coordinate system.
   Float64 Ixy() const;

   // Ytop
   // Returns the distance from the centroid to the top edge of the bounding 
   // rectangle. This distance is always given using the centroidal orientation.
   Float64 Ytop() const;

   // Ybottom
   // Returns the distance from the centroid to the bottom edge of the 
   // bounding rectangle. This distance is always given using the centroidal orientation.
   Float64 Ybottom() const;

   // Xleft
   // Returns the distance from the centroid to the left edge of the bounding 
   // rectangle. This distance is always given using the centroidal orientation.
   Float64 Xleft() const;

   // Xright
   // Returns the distance from the centroid to the right edge of the bounding 
   // rectangle. This distance is always given using the centroidal orientation.
   Float64 Xright() const;

   // Perimeter
   // Returns the perimeter of the shape
   Float64 Perimeter() const;

   // I11
   // Return the principal moment of inertia about the 1-1 axis.
   Float64 I11() const;

   // I22
   // Returns the principal moment of inertia about the 2-2 axis.
   Float64 I22() const;

   // I12Max
   // Returns the maximum product of inertia for the principal coordinate system.
   Float64 I12Max() const;

   // I12Min
   // Returns the minimum product of inertia for the principal coordinate system.
   Float64 I12Min() const;

   // principalDirection
   // Returns the direction of the principal coordinate system,  measured as an 
   // angle from the global X axis to the 11 axis in radians. The value can range from
   // -PI/2 to PI/2.
   Float64 PrincipalDirection() const;

   // SetCoordinateSystem
   // Sets the type of the coordinate system that properties are to be calculated in.
   // This call will change the location of the coordinate system to the location of 
   // the type specified unless the type is UserDefined. A type of UserDefined 
   // will not move the current coordinate system, but will change the type 
   // returned by GetCoordinateSystem to UserDefined.
   void SetCoordinateSystem(gmProperties::CoordSystemType sys);

   // GetCoordinateSystem
   // Returns the type of the coordinate system that properties are calculated in.
   gmProperties::CoordSystemType GetCoordinateSystem() const;

   // SetOrigin
   // Gets the current origin of the coordinate system for which the properties 
   // are defined with respect to. This also sets the coordinate system type to 
   // UserDefined.
   void SetOrigin(const gpPoint2d& origin);

   // GetOrigin
   // Gets the current origin of the coordinate system for which properties are 
   // calculated with respect to.
   gpPoint2d GetOrigin() const;

   // SetOrientation
   // Sets the current orientation of the coordinate system for which the 
   // properties are defined with respect to.  The orientation angle is measured 
   // in radians,  counter clockwise from the positive global X axis.
   // This also sets the coordinate system type to UserDefined.
   void SetOrientation(Float64 angle);

   // GetOrientation
   // Gets the current orientation of the coordinate system for which the 
   // properties are defined with respect to.  The orientation angle is measured 
   // in radians,  counter clockwise from the positive global X axis.
   Float64 GetOrientation() const;


   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   void Dump(dbgDumpContext& os) const;
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
   void MakeCopy(const gmProperties& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gmProperties& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   // properties about centroidal axis
   Float64   m_Area;
   gpPoint2d m_Centroid;
   Float64   m_Ixx;
   Float64   m_Iyy;
   Float64   m_Ixy;
   gpRect2d  m_Box;
   Float64   m_Perimeter;

   // Current coordinate system
   CoordSystemType m_CoordType;
   gpPoint2d       m_Origin;
   Float64         m_Orientation;

   // properties transformed into current coord sys
   gpPoint2d m_CurrCentroid;
   Float64   m_CurrIxx;
   Float64   m_CurrIyy;
   Float64   m_CurrIxy;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // update current values
   void UpdateOrientation();

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

//------------------------------------------------------------------------
// Returns true if lhs is equalivalent to rhs,  otherwise false.
// Equivalent means the the centroid, area, ixx, iyy, ixy and bounding boxes
// are equal, however, the coordinate system orientation angle and origin
// do not have to be the same.
bool GEOMMODELFUNC operator==(const gmProperties& lhs, const gmProperties& rhs);

//------------------------------------------------------------------------
// Returns true if lhs is not equalivalent to rhs,  otherwise false.
bool GEOMMODELFUNC operator!=(const gmProperties& lhs, const gmProperties& rhs);


#endif // INCLUDED_GEOMMODEL_PROPERTIES_H_

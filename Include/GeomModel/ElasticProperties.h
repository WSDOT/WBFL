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

#ifndef INCLUDED_GEOMMODEL_ELASTICPROPERTIES_H_
#define INCLUDED_GEOMMODEL_ELASTICPROPERTIES_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeomModel\GeomModelExp.h>
#include <GeometricPrimitives\GeometricPrimitives.h>
#include <GeomModel\Properties.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gmElasticProperties

   This class encapsulates the elastic properties of a section and provides 
   property transformation services.


DESCRIPTION
   This class encapsulates the geometric properties of a shape and provides
   property transformation services.

   There are four possible coordinate systems that properties can be
   transformed into: Global (Gx, Gy), Centroidal (Cx,Cy), Principal (Px,Py),
   and User-Defined (Ux,Uy). The geometric properties can be transformed to
   any user-defined another coordinate system by changing the origin and
   rotation parameters.

LOG
   rdp : 12.04.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmElasticProperties
{
   friend bool GEOMMODELFUNC operator==(const gmElasticProperties& lhs, const gmElasticProperties& rhs);

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
   gmElasticProperties();

   //------------------------------------------------------------------------
   // gmElasticProperties
   // Explicit constructor.  Initializes the shape properties in the 
   // Centroidal coordinate system to the given values. 
   // If you want to be able to initialize properties in other coord systems, 
   // you need to add more constructors
   gmElasticProperties(Float64 eArea,
                 const gpPoint2d& centroid,
                 Float64 eIxx, Float64 eIyy, Float64 eIxy,
                 Float64 yTop, Float64 yBottom,
                 Float64 xLeft, Float64 xRight,
                 Float64 perimeter);

   //------------------------------------------------------------------------
   // Copy constructor
   gmElasticProperties(const gmElasticProperties& rOther);

   //------------------------------------------------------------------------
   // Destructor
   // This destructor is not virtual. It is not envisioned that this class 
   // will be extended through inheritance.
   ~gmElasticProperties();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gmElasticProperties& operator = (const gmElasticProperties& rOther);

   //------------------------------------------------------------------------
   // Adds the rhs properties to this (taking parallel axis theorem into
   // consideration). The bounding boxes are unioned together.
   gmElasticProperties operator+ (const gmElasticProperties& rhs) const;


   //------------------------------------------------------------------------
   // Adds the rhs properties to this (taking parallel axis theorem into
   // consideration).  The bounding boxes are unioned together.
   gmElasticProperties& operator+= (const gmElasticProperties& rhs);


   // GROUP: OPERATIONS

   // SetEA
   // Sets the area of the shape. Returns the old area.
   Float64 SetEA(Float64 eA);

   // SetCentroid
   // Sets the centroid of the shape, measured in current coordinates. Returns
   // the old centroid.
   gpPoint2d SetCentroid(gpPoint2d cent);

   // SetEIxx
   // sets the moment of inertia about the x axis of the 
   // current coordinate system. Returns the old Ixx.
   Float64 SetEIxx(Float64 eIxx);

   // SetEIyy
   // Sets the moment of inertia about the y axis of the current 
   // coordinate system. Returns the old Ixx.
   Float64 SetEIyy(Float64 eIyy);

   // SetEIxy
   // Returns the product of inertia about the current coordinate system.
   // Returns the old Ixx.
   Float64 SetEIxy(Float64 eIxy);

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
   // Sets the perimeter. Returns the old value
   Float64 SetPerimeter(Float64 p);

   // EA
   // Returns the area of the shape.
   Float64 EA() const;

   // Centroid
   // Returns the centroid of the shape, measured in current coordinates.
   gpPoint2d Centroid() const;

   // EIxx
   // Returns the moment of inertia about the x axis of the 
   // current coordinate system.
   Float64 EIxx() const;

   // EIyy
   // Returns the moment of inertia about the y axis of the current 
   // coordinate system.
   Float64 EIyy() const;

   // EIxy
   // Returns the product of inertia about the current coordinate system.
   Float64 EIxy() const;

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

   //  Perimeter
   // Returns the perimeter
   Float64 Perimeter() const;

   // EI11
   // Return the principal moment of inertia about the 1-1 axis.
   Float64 EI11() const;

   // EI22
   // Returns the principal moment of inertia about the 2-2 axis.
   Float64 EI22() const;

   // EI12Max
   // Returns the maximum product of inertia for the principal coordinate system.
   Float64 EI12Max() const;

   // EI12Min
   // Returns the minimum product of inertia for the principal coordinate system.
   Float64 EI12Min() const;

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
   void SetCoordinateSystem(gmElasticProperties::CoordSystemType sys);

   // GetCoordinateSystem
   // Returns the type of the coordinate system that properties are calculated in.
   gmElasticProperties::CoordSystemType GetCoordinateSystem() const;

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

   // TransformProperties
   // Transform the properties into an equivalent section by dividing the elastic properties by E
   gmProperties TransformProperties(Float64 E) const;

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
   void MakeCopy(const gmElasticProperties& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gmElasticProperties& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   // properties about centroidal axis
   // implement using a gm properties
   gmProperties m_Properties;

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

//------------------------------------------------------------------------
// Returns true if lhs is equalivalent to rhs,  otherwise false.
// Equivalent means the the centroid, area, ixx, iyy, ixy and bounding boxes
// are equal, however, the coordinate system orientation angle and origin
// do not have to be the same.
bool GEOMMODELFUNC operator==(const gmElasticProperties& lhs, const gmElasticProperties& rhs);

//------------------------------------------------------------------------
// Returns true if lhs is not equalivalent to rhs,  otherwise false.
bool GEOMMODELFUNC operator!=(const gmElasticProperties& lhs, const gmElasticProperties& rhs);


#endif // INCLUDED_GEOMMODEL_ELASTICPROPERTIES_H_

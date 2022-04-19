///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2022  Washington State Department of Transportation
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


#include <GeomModel/GeomModelExp.h>
#include <GeomModel/ShapeProperties.h>

namespace WBFL
{
   namespace Geometry
   {
/// This class encapsulates the geometric properties of a Section and provides
/// property transformation services.
///
/// There are four possible coordinate systems that properties can be
/// transformed into: Global (Gx, Gy), Centroidal (Cx,Cy), Principal (Px,Py),
/// and User-Defined (Ux,Uy). The geometric properties can be transformed to
/// any user-defined another coordinate system by changing the origin and
/// rotation parameters.
class GEOMMODELCLASS ElasticProperties
{
public:
   /// Enum which defines the currently set coordinate system.
   enum class CoordSystemType{
 	         Centroidal,    // Origin at centroid of shape and
 			                  //   oriented in global coords
 	         Global,        // Origin at global origin
 	         Principal,     // Origin at centroid of shape and
                           //   oriented in principal direction    
 	         UserDefined};  // Origin and orientation set by user

   /// Initializes all the properties to zero.
   /// The origin of the coordinate system is global (0,0) and the 
   /// orientation angle is zero.
   ElasticProperties();

   /// Explicit constructor.  Initializes the shape properties in the 
   /// Centroidal coordinate system to the given values. 
   /// If you want to be able to initialize properties in other coord systems, 
   /// you need to add more constructors
   ElasticProperties(Float64 eArea,
                 const Point2d& centroid,
                 Float64 eIxx, Float64 eIyy, Float64 eIxy,
                 Float64 xLeft, Float64 yBottom,
                 Float64 xRight, Float64 yTop);

   /// This destructor is not virtual. It is not envisioned that this class will be extended through inheritance.
   ~ElasticProperties();

   ElasticProperties(const ElasticProperties&) = default;
   ElasticProperties& operator=(const ElasticProperties&) = default;

   /// Returns true if lhs is equalivalent to rhs,  otherwise false.
   /// Equivalent means the the centroid, area, ixx, iyy, ixy and bounding boxes
   /// are equal, however, the coordinate system orientation angle and origin
   /// do not have to be the same.
   bool operator==(const ElasticProperties& rhs) const;

   /// Returns true if lhs is not equalivalent to rhs,  otherwise false.
   bool operator!=(const ElasticProperties& rhs) const;


   /// Adds the rhs properties to this (taking parallel axis theorem into
   /// consideration). The bounding boxes are unioned together.
   ElasticProperties operator+ (const ElasticProperties& rhs) const;

   /// Adds the rhs properties to this (taking parallel axis theorem into
   /// consideration).  The bounding boxes are unioned together.
   ElasticProperties& operator+= (const ElasticProperties& rhs);

   ElasticProperties operator- (const ElasticProperties& rhs) const;
   ElasticProperties& operator-= (const ElasticProperties& rhs);

   /// Sets the EA of the shape..
   void SetEA(Float64 eA);
   Float64 GetEA() const;

   /// Sets the centroid of the shape, measured in current coordinates.
   void SetCentroid(const Point2d& cent);
   const Point2d& GetCentroid() const;

   /// Sets the moment of inertia about the x axis of the current coordinate system.
   void SetEIxx(Float64 eIxx);
   Float64 GetEIxx() const;

   // Sets the moment of inertia about the y axis of the current coordinate system.
   void SetEIyy(Float64 eIyy);
   Float64 GetEIyy() const;

   // Returns the product of inertia about the current coordinate system.
   void SetEIxy(Float64 eIxy);
   Float64 GetEIxy() const;

   /// Sets the distance from the centroid to the top edge of the bounding 
   /// rectangle. This distance is always given using the centroidal orientation.
   void SetYtop(Float64 ytop);
   Float64 GetYtop() const;

   /// Sets the distance from the centroid to the bottom edge of the 
   /// bounding rectangle. This distance is always given using the centroidal orientation.
   void SetYbottom(Float64 ybot);
   Float64 GetYbottom() const;

   /// Sets the distance from the centroid to the left edge of the bounding 
   /// rectangle. This distance is always given using the centroidal orientation.
   void SetXleft(Float64 xleft);
   Float64 GetXleft() const;

   /// Sets the distance from the centroid to the right edge of the bounding 
   /// rectangle. This distance is always given using the centroidal orientation.
   void SetXright(Float64 xright);
   Float64 GetXright() const;

   /// Return the principal moment of inertia about the 1-1 axis.
   Float64 GetEI11() const;

   /// Returns the principal moment of inertia about the 2-2 axis.
   Float64 GetEI22() const;

   /// Returns the maximum product of inertia for the principal coordinate system.
   Float64 GetEI12Max() const;

   /// Returns the minimum product of inertia for the principal coordinate system.
   Float64 GetEI12Min() const;

   /// Returns the direction of the principal coordinate system,  measured as an 
   /// angle from the global X axis to the 11 axis in radians. The value can range from
   /// -PI/2 to PI/2.
   Float64 GetPrincipalDirection() const;

   /// Sets the type of the coordinate system that properties are to be calculated in.
   /// This call will change the location of the coordinate system to the location of 
   /// the type specified unless the type is UserDefined. A type of UserDefined 
   /// will not move the current coordinate system, but will change the type 
   /// returned by GetCoordinateSystem to UserDefined.
   void SetCoordinateSystem(ElasticProperties::CoordSystemType sys);

   /// Returns the type of the coordinate system that properties are calculated in.
   ElasticProperties::CoordSystemType GetCoordinateSystem() const;

   /// Gets the current origin of the coordinate system for which the properties 
   /// are defined with respect to. This also sets the coordinate system type to 
   /// UserDefined.
   void SetOrigin(const Point2d& origin);

   /// Gets the current origin of the coordinate system for which properties are 
   /// calculated with respect to.
   const Point2d& GetOrigin() const;

   /// Sets the current orientation of the coordinate system for which the 
   /// properties are defined with respect to.  The orientation angle is measured 
   /// in radians,  counter clockwise from the positive global X axis.
   /// This also sets the coordinate system type to UserDefined.
   void SetOrientation(Float64 angle);

   /// Gets the current orientation of the coordinate system for which the 
   /// properties are defined with respect to.  The orientation angle is measured 
   /// in radians,  counter clockwise from the positive global X axis.
   Float64 GetOrientation() const;

   /// Transform the properties into an equivalent section by dividing the elastic properties by E
   ShapeProperties TransformProperties(Float64 E) const;

#if defined _DEBUG
   bool AssertValid() const;
   void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

private:
   // properties about centroidal axis
   // implement using a ShapeProperties
   ShapeProperties m_Properties;
};


   }; // Geometry
}; // WBFL

#endif // INCLUDED_GEOMMODEL_ELASTICPROPERTIES_H_

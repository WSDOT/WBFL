///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2023  Washington State Department of Transportation
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
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace Geometry
   {
/// This class encapsulates the geometric properties of a shape and provides
/// property transformation services.
///
/// There are four possible coordinate systems that properties can be
/// transformed into: Global (Gx, Gy), Centroidal (Cx,Cy), Principal (Px,Py),
/// and User-Defined (Ux,Uy). The geometric properties can be transformed to
/// any user-defined another coordinate system by changing the origin and
/// rotation parameters.
class GEOMMODELCLASS ShapeProperties
{
public:
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
   ShapeProperties();

   /// Explicit constructor.  Initializes the shape properties in the 
   /// Centroidal coordinate system to the given values. 
   /// If you want to be able to initialize properties in other coord systems, 
   /// you need to add more constructors
   ShapeProperties(Float64 area,
                 const Point2d& centroid,
                 Float64 ixx, Float64 iyy, Float64 ixy,
                 Float64 xLeft, Float64 yBottom,
                 Float64 xRight, Float64 yTop);

   /// This destructor is not virtual. It is not envisioned that this class 
   /// will be extended through inheritance.
   ~ShapeProperties();

   ShapeProperties(const ShapeProperties&) = default;
   ShapeProperties& operator=(const ShapeProperties&) = default;

   // Returns true if this is equalivalent to rhs,  otherwise false.
   // Equivalent means the the centroid, area, ixx, iyy, ixy and bounding boxes
   // are equal, however, the coordinate system orientation angle and origin
   // do not have to be the same.
   bool operator==(const ShapeProperties& rhs) const;

   /// Returns true if this is not equalivalent to rhs,  otherwise false.
   bool operator!=(const ShapeProperties& rhs) const;

   /// Adds the rhs properties to this (taking parallel axis theorem into
   /// consideration). The bounding boxes are unioned together.
   ShapeProperties operator+ (const ShapeProperties& rhs) const;
   ShapeProperties operator- (const ShapeProperties& rhs) const;

   /// Adds the rhs properties to this (taking parallel axis theorem into
   /// consideration).  The bounding boxes are unioned together.
   ShapeProperties& operator+= (const ShapeProperties& rhs);
   ShapeProperties& operator-= (const ShapeProperties& rhs);

   void SetProperties(Float64 area,const Point2d& centroid,Float64 ixx, Float64 iyy, Float64 ixy, Float64 xLeft,Float64 yBottom, Float64 xRight, Float64 yTop);
   void GetProperties(Float64* area, Point2d* centroid, Float64* ixx, Float64* iyy, Float64* ixy,  Float64* xLeft, Float64* yBottom, Float64* xRight,Float64* yTop) const;

   /// Sets all properties to 0.0
   void Clear();

   /// Sets the area of the shape.
   void SetArea(Float64 area);

   /// Returns the area of the shape.
   Float64 GetArea() const;

   /// Sets the centroid of the shape, measured in current coordinates. Returns the old centroid.
   void SetCentroid(const Point2d& cent);

   /// Returns the centroid of the shape, measured in current coordinates.
   const Point2d& GetCentroid() const;

   /// Sets the moment of inertia about the x axis of the current coordinate system.
   void SetIxx(Float64 ixx);

   /// Returns the moment of inertia about the x axis of the current coordinate system.
   Float64 GetIxx() const;

   /// Sets the moment of inertia about the y axis of the current coordinate system.
   void SetIyy(Float64 iyy);

   /// Returns the moment of inertia about the y axis of the current coordinate system.
   Float64 GetIyy() const;

   /// Returns the product of inertia about the current coordinate system.
   void SetIxy(Float64 ixy);

   /// Returns the product of inertia about the current coordinate system.
   Float64 GetIxy() const;

   /// Sets the distance from the centroid to the top edge of the bounding 
   /// rectangle. This distance is always given using the centroidal orientation.
   void SetYtop(Float64 ytop);

   /// Returns the distance from the centroid to the top edge of the bounding 
   /// rectangle. This distance is always given using the centroidal orientation.
   Float64 GetYtop() const;

   /// Sets the distance from the centroid to the bottom edge of the 
   /// bounding rectangle. This distance is always given using the centroidal orientation.
   void SetYbottom(Float64 ybot);

   /// Returns the distance from the centroid to the bottom edge of the 
   /// bounding rectangle. This distance is always given using the centroidal orientation.
   Float64 GetYbottom() const;

   /// Sets the distance from the centroid to the left edge of the bounding 
   /// rectangle. This distance is always given using the centroidal orientation.
   void SetXleft(Float64 xleft);

   /// Returns the distance from the centroid to the left edge of the bounding 
   /// rectangle. This distance is always given using the centroidal orientation.
   Float64 GetXleft() const;

   /// Sets the distance from the centroid to the right edge of the bounding 
   /// rectangle. This distance is always given using the centroidal orientation.
   void SetXright(Float64 xright);
   
   // Returns the distance from the centroid to the right edge of the bounding 
   // rectangle. This distance is always given using the centroidal orientation.
   Float64 GetXright() const;

   /// Return the principal moment of inertia about the 1-1 axis.
   Float64 GetI11() const;

   /// Returns the principal moment of inertia about the 2-2 axis.
   Float64 GetI22() const;

   /// Returns the maximum product of inertia for the principal coordinate system.
   Float64 GetI12Max() const;

   /// Returns the minimum product of inertia for the principal coordinate system.
   Float64 GetI12Min() const;

   /// Returns the direction of the principal coordinate system,  measured as an 
   /// angle from the global X axis to the 11 axis in radians. The value can range from
   /// -PI/2 to PI/2.
   Float64 GetPrincipalDirection() const;

   // Sets the type of the coordinate system that properties are to be calculated in.
   // This call will change the location of the coordinate system to the location of 
   // the type specified unless the type is UserDefined. A type of UserDefined 
   // will not move the current coordinate system, but will change the type 
   // returned by GetCoordinateSystem to UserDefined.
   void SetCoordinateSystem(ShapeProperties::CoordSystemType sys);

   /// Returns the type of the coordinate system that properties are calculated in.
   ShapeProperties::CoordSystemType GetCoordinateSystem() const;

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

#if defined _DEBUG
   // Returns true if the class is in a valid state, otherwise returns false
   bool AssertValid() const;

   /// Dumps the contents of the class to the given stream.
   void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   /// Self-diagnostic test function.
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

private:
   // properties about centroidal axis
   Float64   m_Area{ 0.0 };
   Point2d m_Centroid;
   Float64   m_Ixx{ 0.0 };
   Float64   m_Iyy{ 0.0 };
   Float64   m_Ixy{ 0.0 };
   Float64 m_Xleft{ 0.0 };
   Float64 m_Xright{ 0.0 };
   Float64 m_Ytop{ 0.0 };
   Float64 m_Ybottom{ 0.0 };

   // Current coordinate system
   CoordSystemType m_CoordType{ CoordSystemType::Centroidal };
   Point2d       m_Origin;
   Float64         m_Orientation{ 0.0 };

   // properties transformed into current coord sys
   Point2d m_CurrCentroid;
   Float64   m_CurrIxx{ 0.0 };
   Float64   m_CurrIyy{ 0.0 };
   Float64   m_CurrIxy{ 0.0 };

   void UpdateOrientation();
   ShapeProperties& Join(const ShapeProperties& other, Float64 scale);
};
   }; // Geometry
}; // WBFL

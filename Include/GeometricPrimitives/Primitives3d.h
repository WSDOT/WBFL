///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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

#ifndef INCLUDED_GEOMETRY_PRIMITIVES3D_H_
#define INCLUDED_GEOMETRY_PRIMITIVES3D_H_
#pragma once

// SYSTEM INCLUDES
//
#include <GeometricPrimitives\GeometryExp.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class GEOMCLASS gpPoint3d;
class GEOMCLASS gpSize3d;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gpSize3d

   Encapsulates the notion of a 3-dimensional quantity that usually 
   represents a displacement or the height, width, and depth of a rectangular
   prisim.


DESCRIPTION
   Encapsulates the notion of a 3-dimensional quantity that usually 
   represents a displacement or the height, width, and depth of a rectangular
   prisim.

LOG
   Richard Brice : 04.21.1999 : Created file
*****************************************************************************/

class GEOMCLASS gpSize3d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor. Set dimensions to zero.
   gpSize3d();

   //------------------------------------------------------------------------
   // Constructor. Sets dimensions to dx, dy, and dz.
   gpSize3d(Float64 dx, Float64 dy,Float64 dz);

   //------------------------------------------------------------------------
   // Constructor. Sets dimensions to point.X(), point.Y(), and point.Z().
   gpSize3d(const gpPoint3d& point);

   //------------------------------------------------------------------------
   // Copy constructor
   gpSize3d(const gpSize3d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpSize3d();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   gpSize3d& operator = (const gpSize3d& rOther);

   //------------------------------------------------------------------------
   // Calculates an offset to this gpSize3d object using the given size argument
   // as the displacement.  Returns (dx+size.Dx(), dy+size.Dy(), dz+size.Dz()).
   // This object is unchanged.
   gpSize3d operator + (const gpSize3d& size) const;

   //------------------------------------------------------------------------
   // Scales the size object by c. Returns (Dx()*c, Dy()*c, Dz*c).
   gpSize3d operator*(Float64 c) const;

   //------------------------------------------------------------------------
   // Scales the size object by c. Returns (Dx()/c, Dy()/c, Dz()/c).
   gpSize3d operator/(Float64 c) const;

   //------------------------------------------------------------------------
   // Calculates an offset to this gpSize3d object using the given size argument
   // as the displacement.  Returns (dx-size.Dx(), dy-size.Dy(), dz-size.Dz()).  
   // This object is unchanged.
   gpSize3d operator - (const gpSize3d& size) const;

   //------------------------------------------------------------------------
   // Returns the gpSize3d object (-dx,-dy, -dz). This object is unchanged.
   gpSize3d operator- () const;

   //------------------------------------------------------------------------
   // Returns true if this gpSize3d object is equal to the rOther gpSize3d 
   // object, otherwise returns false.
   bool operator==(const gpSize3d& rOther) const;

   //------------------------------------------------------------------------
   // Returns false if this gpSize3d object is equal to the rOther gpSize3d 
   // object, otherwise returns true.
   bool operator!=(const gpSize3d& rOther) const;

   //------------------------------------------------------------------------
   // Offset this gpSize3d object by the given size argument.  This gpSize3d
   // object is chaged to (Dx+size.Dx(),Dy+size.Dy(),Dz+size.Dz()).
   // Returns a reference to this object.
   gpSize3d& operator+= (const gpSize3d& rOther);

   //------------------------------------------------------------------------
   // Negatively offset this gpSize3d object by the given size argument.  
   // This gpSize3d object is chaged to (Dx+size.Dx(),Dy+size.Dy(),Dz+size.Dz()).
   // Returns a reference to this object.
   gpSize3d& operator-= (const gpSize3d& rOther);

   //------------------------------------------------------------------------
   // Divides Dx, Dy, and Dz by c.
   gpSize3d& operator/= (Float64 c);

   //------------------------------------------------------------------------
   // Multiplies Dx, Dy, and Dz by c.
   gpSize3d& operator*= (Float64 c);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Returns the length of the diagonal of the rectangle represented by
   // this object.
   Float64 Magnitude() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the size in the x direction.
   Float64 Dx() const;

   //------------------------------------------------------------------------
   // Returns the size in the x direction.
   Float64& Dx();

   //------------------------------------------------------------------------
   // Returns the size in the y direction.
   Float64 Dy() const;

   //------------------------------------------------------------------------
   // Returns the size in the y direction.
   Float64& Dy();

   //------------------------------------------------------------------------
   // Returns the size in the z direction.
   Float64 Dz() const;

   //------------------------------------------------------------------------
   // Returns the size in the z direction.
   Float64& Dz();

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // TestMe
   // Self-Test function. Returns true if successful.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const gpSize3d& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gpSize3d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Dx;
   Float64 m_Dy;
   Float64 m_Dz;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

inline GEOMFUNC gpSize3d operator/(gpSize3d& size, Float64 c)
{   return size.operator/( c ); }
inline GEOMFUNC gpSize3d operator/(Float64 c,gpSize3d& size)
{   return size.operator/( c ); }
inline GEOMFUNC gpSize3d operator*(gpSize3d& size, Float64 c)
{   return size.operator*( c ); }
inline GEOMFUNC gpSize3d operator*(Float64 c,gpSize3d& size)
{   return size.operator*( c ); }
GEOMFUNC std::ostream& operator<<(std::ostream& os,gpSize3d& size);

/*****************************************************************************
CLASS 
   gpPoint3d

   Encapsulates the notion of a 3-dimensional point that represents a
   position in a Cartesian coordinate system.


DESCRIPTION
   Encapsulates the notion of a 3-dimensional point that represents a
   position in a Cartesian coordinate system.

LOG
   Richard Brice : 04.21.1999 : Created file
*****************************************************************************/

class GEOMCLASS gpPoint3d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Sets x, y, and z to zero.
   gpPoint3d();

   //------------------------------------------------------------------------
   // Constructor. Sets coordinate to (x,y,z).
   gpPoint3d(Float64 x,Float64 y,Float64 z);

   //------------------------------------------------------------------------
   // Copy constructor
   gpPoint3d(const gpPoint3d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpPoint3d();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gpPoint3d& operator = (const gpPoint3d& rOther);

   //------------------------------------------------------------------------
   // Calcuates an offset to this point using the given size argument as 
   // the displacement.  Returns (x+size.Dx(),y+size.Dy(),z+size.Dz()).
   // This point is not changed.
   gpPoint3d operator+ (const gpSize3d& size) const;

   //------------------------------------------------------------------------
   // Calcuates an offset to this point using the given size argument as 
   // the displacement.  Returns (x-size.Dx(),y-size.Dy(),z-size.Dz()).
   // This point is not changed.
   gpPoint3d operator- (const gpSize3d& size) const;

   //------------------------------------------------------------------------
   // Calculates the size between two points.  Returns x-p.X(), y-p.Y(), z-p.Z().
   // This point is not changed.
   gpSize3d operator- (const gpPoint3d& p) const;

   //------------------------------------------------------------------------
   // Returns the point (-x,-y,-z). This point is not changed.
   gpPoint3d operator- () const;

   //------------------------------------------------------------------------
   // Offsets this point by the given size argument.  This point is changed to
   // (x+size.Dx(),y+size.Dy(),z+size.Dz()).  Returns a reference to this point.
   gpPoint3d& operator+= (const gpSize3d& size);

   //------------------------------------------------------------------------
   // Offsets this point by the given size argument.  This point is changed to
   // (x-size.Dx(),y-size.Dy(),z-size.Dz()).  Returns a reference to this point.
   gpPoint3d& operator-= (const gpSize3d& size);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Returns the distance between this point and the origin.
   Float64 Magnitude() const;

   //------------------------------------------------------------------------
   // Moves this point to a new position defined by x,y,z.
   void Move(Float64 x,Float64 y,Float64 z);

   //------------------------------------------------------------------------
   // Moves this point to a new position defined by newPosition.
   void Move(const gpPoint3d& newPosition);

   //------------------------------------------------------------------------
   // Returns the distance between this point and point p.
   Float64 Distance(const gpPoint3d& p) const;

   //------------------------------------------------------------------------
   // Offsets this point by the given delta arguments.  This point is changed
   // to (x+dx,y+dy,z+dz).  Returns a reference to this point.
   gpPoint3d& Offset(Float64 dx,Float64 dy,Float64 dz);

   //------------------------------------------------------------------------
   // Offsets this point by the given delta arguments.  This point is changed
   // to (x+size.Dx(),y+size.Dy(),z+size.Dz()).  Returns a reference to this point.
   gpPoint3d& Offset(const gpSize3d& size);

   //------------------------------------------------------------------------
   // Calculates an offset to this point using the given displacement 
   // arguments.  Returns the point (x+dx,y+dy,z+dz).  This point is not
   // changed.
   gpPoint3d OffsetBy(Float64 dx,Float64 dy,Float64 dz) const;

   //------------------------------------------------------------------------
   // Calculates an offset to this point using the given displacement 
   // arguments.  Returns the point (x+size.Dx(),y+size.Dy(),z+size.Dz()).
   // This point is not changed.
   gpPoint3d OffsetBy(const gpSize3d& size) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the x coordinate of the point.
   Float64 X() const;

   //------------------------------------------------------------------------
   // Returns the x coordinate of the point.
   Float64& X();

   //------------------------------------------------------------------------
   // Returns the y coordinate of the point.
   Float64 Y() const;

   //------------------------------------------------------------------------
   // Returns the y coordinate of the point.
   Float64& Y();

   //------------------------------------------------------------------------
   // Returns the z coordinate of the point.
   Float64 Z() const;

   //------------------------------------------------------------------------
   // Returns the z coordinate of the point.
   Float64& Z();
      
   // GROUP: INQUIRY
   // GROUP: DEBUG

#if defined _DEBUG
   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // TestMe
   // Self-Test function. Returns true if successful.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST


protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const gpPoint3d& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gpPoint3d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_X;
   Float64 m_Y;
   Float64 m_Z;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

//------------------------------------------------------------------------
// Returns true if lhs is equal to rhs,  otherwise false.
GEOMFUNC bool operator==(const gpPoint3d& lhs, const gpPoint3d& rhs);

//------------------------------------------------------------------------
// Returns true if lhs is not equal to rhs,  otherwise false.
GEOMFUNC bool operator!=(const gpPoint3d& lhs, const gpPoint3d& rhs);

//------------------------------------------------------------------------
GEOMFUNC std::ostream& operator<<(std::ostream& os,const gpPoint3d& p);

#endif // INCLUDED_GEOMETRY_PRIMITIVES3D_H_

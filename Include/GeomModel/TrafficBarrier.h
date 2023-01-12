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

#ifndef INCLUDED_GEOMMODEL_TRAFFICBARRIER_H_
#define INCLUDED_GEOMMODEL_TRAFFICBARRIER_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeomModel\GeomModelExp.h>
#include <GeomModel\ShapeImp.h>
#include <GeometricPrimitives\Polygon2d.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gmPolygon;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gmTrafficBarrier

   This shape represents the cross section of a typical concrete traffic
   barrier found on bridge structures.


DESCRIPTION
   This shape represents the cross section of a typical concrete traffic
   barrier found on bridge structures.

LOG
   rab : 10.11.1998 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmTrafficBarrier : public gmShapeImp
{
public:
   // GROUP: ENUMERATION
   enum Orientation { Left, Right };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gmTrafficBarrier();

   //------------------------------------------------------------------------
   gmTrafficBarrier(Float64 x1,Float64 x2,Float64 x3,Float64 x4,Float64 x5,
                    Float64 y1,Float64 y2,Float64 y3,
                    Float64 tSlab,
                    Orientation orient,
                    const gpPoint2d& hookPoint);

   //------------------------------------------------------------------------
   // Copy constructor
   gmTrafficBarrier(const gmTrafficBarrier& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmTrafficBarrier();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gmTrafficBarrier& operator = (const gmTrafficBarrier& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void GetProperties(gmProperties* pProperties) const;

   //------------------------------------------------------------------------
   gpRect2d GetBoundingBox() const;

   //------------------------------------------------------------------------
   gmIShape* CreateClone(bool bRegisterListeners = false) const;

   //------------------------------------------------------------------------
   gmIShape* CreateClippedShape(const gpLine2d& line,
                                gpLine2d::Side side) const;

   //------------------------------------------------------------------------
   gmIShape* CreateClippedShape(const gpRect2d& r,
                                gmShapeImp::ClipRegion region ) const;

   //------------------------------------------------------------------------
   Float64 GetFurthestDistance(const gpLine2d& line,
                               gpLine2d::Side side) const;

   //------------------------------------------------------------------------
   void Draw(HDC hdc,const grlibPointMapper& mapper) const;

   //------------------------------------------------------------------------
   Float64 SetX1(Float64 x1);

   //------------------------------------------------------------------------
   Float64 GetX1() const;

   //------------------------------------------------------------------------
   Float64 SetX2(Float64 x2);

   //------------------------------------------------------------------------
   Float64 GetX2() const;

   //------------------------------------------------------------------------
   Float64 SetX3(Float64 x3);

   //------------------------------------------------------------------------
   Float64 GetX3() const;

   //------------------------------------------------------------------------
   Float64 SetX4(Float64 x4);

   //------------------------------------------------------------------------
   Float64 GetX4() const;

   //------------------------------------------------------------------------
   Float64 SetX5(Float64 x5);

   //------------------------------------------------------------------------
   Float64 GetX5() const;

   //------------------------------------------------------------------------
   Float64 SetY1(Float64 y1);

   //------------------------------------------------------------------------
   Float64 GetY1() const;

   //------------------------------------------------------------------------
   Float64 SetY2(Float64 y2);

   //------------------------------------------------------------------------
   Float64 GetY2() const;

   //------------------------------------------------------------------------
   Float64 SetY3(Float64 y3);

   //------------------------------------------------------------------------
   Float64 GetY3() const;

   //------------------------------------------------------------------------
   Float64 SetSlabDepth(Float64 tSlab);

   //------------------------------------------------------------------------
   Float64 GetSlabDepth() const;

   //------------------------------------------------------------------------
   Orientation SetOrientation(Orientation orient);

   //------------------------------------------------------------------------
   Orientation GetOrientation() const;

   //------------------------------------------------------------------------
   gpPoint2d SetHookPoint(const gpPoint2d& hookPnt);

   //------------------------------------------------------------------------
   gpPoint2d GetHookPoint() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   void DoTranslate(const gpSize2d& delta);

   //------------------------------------------------------------------------
   void DoRotate(const gpPoint2d& center,Float64 angle);

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const gmTrafficBarrier& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gmTrafficBarrier& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_X1;
   Float64 m_X2;
   Float64 m_X3;
   Float64 m_X4;
   Float64 m_X5;
   Float64 m_Y1;
   Float64 m_Y2;
   Float64 m_Y3;
   Float64 m_tSlab;
   Orientation m_Orientation;

   gpPoint2d m_HookPoint;
   Float64   m_Rotation;
   gpPolygon2d m_PolyImp; // polygon implementation.

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   void Init();
   gmPolygon* CreatePolygon() const;
   void UpdatePolygon();

   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const override;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const override;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GEOMMODEL_TRAFFICBARRIER_H_

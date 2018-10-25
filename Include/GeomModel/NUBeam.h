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

#ifndef INCLUDED_GEOMMODEL_NUBEAM_H_
#define INCLUDED_GEOMMODEL_NUBEAM_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeomModel\GeomModelExp.h>
#include <GeomModel\IPrecastBeam.h>
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
   gmNUBeam
   Derived from gmIShape,  this class represents the shape of an I-beam.  
   I-beams are typically found in bridge structures.  

DESCRIPTION
   An I-beam is described by its dimensions as shown in the accompanying figure.
   The hook point is located at the center of the top edge of the shape. 

LOG
   rab : 08.13.2002 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmNUBeam :  public gmIPrecastBeam
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Creates a NUBeam with all dimensions equal 
   // to zero,  with its hook point at (0,0).
   gmNUBeam();

   //------------------------------------------------------------------------
   // gmNUBeam
   // Explicit constructor.  Creates an I-beam shape with the given 
   // dimensions.  The hook point is positioned at hookPnt. All beam 
   // dimensions must be nonnegative
   gmNUBeam(Float64 w1, Float64 w2, 
            Float64 d1, Float64 d2, Float64 d3, Float64 d4, Float64 d5,
            Float64 t, 
            Float64 r1, Float64 r2, Float64 r3, Float64 r4,
            const gpPoint2d& hookPnt);

   //------------------------------------------------------------------------
   gmNUBeam(const gmNUBeam&);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmNUBeam();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   gmNUBeam& operator=(const gmNUBeam&);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // SetHookPoint
   // Sets the location of the hook point to hookPnt.  Returns the previous 
   // hook point location.
   gpPoint2d SetHookPoint(const gpPoint2d& hookPnt);

   //------------------------------------------------------------------------
   // GetHookPoint
   // Returns the location of the hook point.
   gpPoint2d GetHookPoint() const;


   //------------------------------------------------------------------------
   // SetW1
   // Sets w1.  Returns the previous value of w1. Must be nonnegative.
   Float64 SetW1(Float64 w1);

   //------------------------------------------------------------------------
   // GetW1
   // Returns the current value of w1.
   Float64 GetW1() const;

   //------------------------------------------------------------------------
   // SetW2
   // Sets w2.  Returns the previous value of w2. Must be nonnegative.
   Float64 SetW2(Float64 w2);

   //------------------------------------------------------------------------
   // GetW2
   // Returns the current value of w2.
   Float64 GetW2() const;

   //------------------------------------------------------------------------
   // SetD1
   // Sets d1.  Returns the previous value of d1. Must be nonnegative.
   Float64 SetD1(Float64 d1);

   //------------------------------------------------------------------------
   // GetD1
   // Returns the current value of d1.
   Float64 GetD1() const;

   //------------------------------------------------------------------------
   // SetD2
   // Sets d2.  Returns the previous value of d2. Must be nonnegative.
   Float64 SetD2(Float64 d2);

   //------------------------------------------------------------------------
   // GetD2
   // Returns the current value of d2.
   Float64 GetD2() const;

   //------------------------------------------------------------------------
   // SetD3
   // Sets d3.  Returns the previous value of d3. Must be nonnegative.
   Float64 SetD3(Float64 d3);

   //------------------------------------------------------------------------
   // GetD3
   // Returns the current value of d3.
   Float64 GetD3() const;

   //------------------------------------------------------------------------
   // SetD4
   // Sets d4.  Returns the previous value of d4. Must be nonnegative.
   Float64 SetD4(Float64 d4);

   //------------------------------------------------------------------------
   // GetD4
   // Returns the current value of d4.
   Float64 GetD4() const;

   //------------------------------------------------------------------------
   // SetD5
   // Sets d5.  Returns the previous value of d5. Must be nonnegative.
   Float64 SetD5(Float64 d5);

   //------------------------------------------------------------------------
   // GetD5
   // Returns the current value of d5.
   Float64 GetD5() const;

   //------------------------------------------------------------------------
   // SetT
   // Sets t.  Returns the previous value of t. Must be nonnegative.
   Float64 SetT(Float64 t);

   //------------------------------------------------------------------------
   // GetT
   // Returns the current value of t.
   Float64 GetT() const;

   //------------------------------------------------------------------------
   // SetR1
   // Sets r1.  Returns the previous value of r1. Must be nonnegative.
   Float64 SetR1(Float64 r1);

   //------------------------------------------------------------------------
   // GetR1
   // Returns the current value of r1.
   Float64 GetR1() const;

   //------------------------------------------------------------------------
   // SetR2
   // Sets r2.  Returns the previous value of r2. Must be nonnegative.
   Float64 SetR2(Float64 r2);

   //------------------------------------------------------------------------
   // GetR2
   // Returns the current value of r2.
   Float64 GetR2() const;

   //------------------------------------------------------------------------
   // SetR3
   // Sets r3.  Returns the previous value of r3. Must be nonnegative.
   Float64 SetR3(Float64 r3);

   //------------------------------------------------------------------------
   // GetR3
   // Returns the current value of r3.
   Float64 GetR3() const;

   //------------------------------------------------------------------------
   // SetR4
   // Sets r4.  Returns the previous value of r4. Must be nonnegative.
   Float64 SetR4(Float64 r4);

   //------------------------------------------------------------------------
   // GetR4
   // Returns the current value of r4.
   Float64 GetR4() const;

   //------------------------------------------------------------------------
   // GetHeight
   // Returns the current height of the section.
   Float64 GetHeight() const;

   //------------------------------------------------------------------------
   // CreateClone
   // Creates a clone of this broadcaster.  If bRegisterListeners is true the 
   // listeners are registered with the clone.  This is a factory method,  
   // you are responsible for freeing the memory allocated by this method.
   virtual gmIShape* CreateClone(bool bRegisterListeners = false) const override;

   //------------------------------------------------------------------------
   // GetProperties
   // Assigns a gmProperties object to the object pointed to by pProperties. 
   // The origin of the shape properties object is the centroid of this shape
   // with a rotation of zero.
   virtual void GetProperties(gmProperties* pProperties) const override;

   //------------------------------------------------------------------------
   // GetBoundingBox
   // Returns the smallest rectangle that bounds the entire shape.
   virtual gpRect2d GetBoundingBox() const override;

   //------------------------------------------------------------------------
   // CreateClippedShape
   // Clips this shape against line.  Clips away the portion of the shape on the
   // side of the line defined by side.  This is a factory method.  You are 
   // responsible for freeing the memory allocated by this method.  If the shape
   // lies entirely on the clipping side of the line 0 is returned. Any listeners
   // to the original section are not transferred to this new section.
   virtual gmIShape* CreateClippedShape(const gpLine2d& line, 
                                       gpLine2d::Side side) const override;

   //------------------------------------------------------------------------
   // CreateClippedShape
   // Clips this shape against NUBeam r.  Clips in or out of the NUBeam
   // as specified by region.  This is a factory method.  You are responsible 
   // for freeing memory allocated by this method.  This method returns 0 if, 
   // the shape lies entirely within the clipping NUBeam and region is set 
   // to clip out, or the shape and the NUBeam do not intersect and region 
   // is to clip in. Any listeners to the original section are not transferred
   // to this new section.
   virtual gmIShape* CreateClippedShape(const gpRect2d& r,
                                        gmShapeImp::ClipRegion region
                                        ) const override;

   //------------------------------------------------------------------------
   // GetFurthestDistance
   // Returns the distance to a line that is parallel to line, on specified 
   // side of line,  that passes through the furthest point on the shape 
   // from line.
   virtual Float64 GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const override;

   //------------------------------------------------------------------------
   // Draw
   // Draws the shape on the given device context.  Mapping of the coordinates
   // to the device space should be done using the supplied point mapper.
   // Draw is for static displays only.  The drawing of this analytical 
   // model is not intended for interactive, graphical editing.  Interactive 
   // graphical editing is best left for a package specifically designed for 
   // this purpose, such as jKit/GO.  In a package like jKit/GO,  a GO object
   // would most likely delegate its drawing responsibility to the gmShapeImp 
   // object it represents.
   // Subject to removal if we can ever figure out the MVC stuff
   virtual void Draw(HDC hDC, const grlibPointMapper& mapper) const override;

   //------------------------------------------------------------------------
   // Contains
   // Returns true if a point is contained within the girder shape or is on
   // its border
   bool Contains(const gpPoint2d& pnt) const;

   //------------------------------------------------------------------------
   // Returns the top flange width of the girder
   virtual Float64 GetTopFlangeWidth() const override;

   //------------------------------------------------------------------------
   // Returns the bottom flange width of the girder
   virtual Float64 GetBottomFlangeWidth() const override;

   //------------------------------------------------------------------------
   // Returns the total top width of the girder
   virtual Float64 GetTopWidth() const override;

   //------------------------------------------------------------------------
   // Returns the web width for shear
   virtual Float64 GetShearWidth() const override;

   //------------------------------------------------------------------------
   // Returns the web width
   virtual Float64 GetMinWebWidth() const override;

   //------------------------------------------------------------------------
   // Returns the minimum bottom flange thickness
   virtual Float64 GetMinBottomFlangeThickness() const override;

   //------------------------------------------------------------------------
   // Returns the minimum top flange thickness
   virtual Float64 GetMinTopFlangeThickness() const override;

   virtual MatingSurfaceIndexType GetNumberOfMatingSurfaces() const override;
   virtual Float64 GetMatingSurfaceWidth(MatingSurfaceIndexType idx) const override;
   virtual Float64 GetMatingSurfaceLocation(MatingSurfaceIndexType idx) const override;
   virtual void GetWebPlane(WebIndexType webIdx,IPlane3d** ppPlane) const override;

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const override;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const override;

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
   // DoTranslate
   // Called by the framework went the shape is to be translated.
   virtual void DoTranslate(const gpSize2d& delta) override;

   //------------------------------------------------------------------------
   // DoRotate
   // Called by the framework went the shape is to be rotated.
   virtual void DoRotate(const gpPoint2d& center, Float64 angle) override;

   //------------------------------------------------------------------------
   void MakeCopy(const gmNUBeam& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gmNUBeam& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   gpPoint2d m_HookPoint;
   Float64   m_Rotation;
   Float64   m_D1;
   Float64   m_D2;
   Float64   m_D3;
   Float64   m_D4;
   Float64   m_D5;
   Float64   m_T;
   Float64   m_W1;
   Float64   m_W2;
   Float64   m_R1;
   Float64   m_R2;
   Float64   m_R3;
   Float64   m_R4;

   gpPolygon2d m_PolyImp; // polygon implementation.

   // GROUP: LIFECYCLE


   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   gmPolygon* CreatePolygon() const;
   void UpdatePolygon();
   void GenerateFillet(gpPolygon2d* pShape,Float64 cx,Float64 cy,Float64 r,Float64 startAngle,Float64 delta,Int32 nSpaces);

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GEOMMODEL_NUBEAM_H_

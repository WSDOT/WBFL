///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_GRAPHICSLIB_DIMENSION_H_
#define INCLUDED_GRAPHICSLIB_DIMENSION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GraphicsLib\GraphicsLibExp.h>
#include <GraphicsLib\Label.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class grlibPointMapper;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   grDimension

   class for drawing dimensions of real things


DESCRIPTION
   dimension lines


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 10.28.1998 : Created file
*****************************************************************************/

class GRCLASS grDimension
{
public:
   //------------------------------------------------------------------------
   // DimensionStyle - style for the dimension - to be added to later
   enum DimensionStyle { Horizontal, Vertical /* Aligned */   };

   //------------------------------------------------------------------------
   // Dimension Locations
   // Note that these locations are not positioned in absolute coordinates. They
   // are always relative to a coordinate system defined by the orientation of
   // the dimension itself.
   //
   //  Horizontal Dimensions:
   //
   //                                              
   //    |<-- Above,Center -->|      Above, Left ->|     |<-
   //    |                    |                    |     |
   //    o                    o                    o     o
   //    |                    |                    |     |
   //    |<-- Below,Center -->|                    |     |<- Below, Right
   //    
   //
   // Vertical Dimensions
   //
   //                                        Above,Left      Below,Left
   //      -------------o----------               |               |
   //         ^                  ^                v               v
   //         |                  |          o-------              -------o
   //   Below, Center      Above,Center
   //         |                  |          o--------             -------o
   //         v                  v                ^               ^
   //     --------------o----------               |               |
   //                                         Above,Right     Below,Right
   //
   //
   // draw dimension above or below hook points.
   enum VerticalDimensionPos
   {  Above, Below };

   //------------------------------------------------------------------------
   // draw dimension left, between, or right of vertical lines
   enum HorizontalDimensionPos
   { Left, Center, Right };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   grDimension();

   //------------------------------------------------------------------------
   // Constructor - sets hook points and label
   // Horizontal dimension Above,Center by default.
   grDimension(const gpPoint2d& pointA, const gpPoint2d& pointB, const std::_tstring& label);

   //------------------------------------------------------------------------
   // Copy constructor
   grDimension(const grDimension& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~grDimension();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   grDimension& operator = (const grDimension& rOther);

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Draw
   virtual void Draw(HDC hDC, const grlibPointMapper& mapper) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // SetStyle - sets the alignment mode
   void SetStyle(DimensionStyle style);

   //------------------------------------------------------------------------
   // GetStyle - get the alignment mode
   DimensionStyle GetStyle() const
   {return m_Style;}

   //------------------------------------------------------------------------
   // Set position of dimension above or below hook points
   void SetVerticalDimensionPos(VerticalDimensionPos pos);

   //------------------------------------------------------------------------
   // Get position of dimension above or below hook points
   VerticalDimensionPos GetVerticalDimensionPos() const;

   //------------------------------------------------------------------------
   // Force horizontal position of dimension. Default is between.
   void SetHorizontalDimensionPos(HorizontalDimensionPos pos);

   //------------------------------------------------------------------------
   // Get horizontal position
   HorizontalDimensionPos GetHorizontalDimensionPos() const;

   //------------------------------------------------------------------------
   // Set hook points for dimensioning. Will assert if points coincide
   void SetHookPoints(const gpPoint2d& pointA, const gpPoint2d& pointB);

   //------------------------------------------------------------------------
   // Get hook points for dimensioning. Will assert if points coincide
   void GetHookPoints(gpPoint2d* pointA, gpPoint2d* pointB) const;

   //------------------------------------------------------------------------
   // Set additional dimension offset. This offset will be added to the
   // default hook point offset and witness line length to move the dimension
   // further away from the hook points. Zero, by default
   // behavior is undefined for negative values.
   void SetAdditionalOffset(Float64 offset){m_AdditionalOffset=offset;}

   //------------------------------------------------------------------------
   // Set additional dimension offset. This offset will be added to the
   // default hook point offset and witness line length to move the dimension
   // further away from the hook points. Zero, by default
   Float64 GetAdditionalOffset() const {return m_AdditionalOffset;}

   //------------------------------------------------------------------------
   //  Set the label to be placed on the dimension. std::endl's in the string
   //  will start a new line and create a multiline label.
   void SetLabel(const std::_tstring& label);

   //------------------------------------------------------------------------
   // Get the label
   std::_tstring GetLabel() const;

   //------------------------------------------------------------------------
   // Sets the point size of the font
   void SetPointSize(Uint32 pt);

   //------------------------------------------------------------------------
   // Returns the point size of the font
   Uint32 GetPointSize() const;

   //------------------------------------------------------------------------
   // Set space factor - a space factor of zero will position the dimension
   // as close as possible to the target. A factor of one will piggyback the
   // next dimension above it, and so on.
   // Zero is the default
   void SetSpaceFactor(Float64 factor);

   //------------------------------------------------------------------------
   // get space factor - a space factor of zero will position the dimension
   // as close as possible to the target. A factor of one will piggyback the
   // next dimension above it, and so on.
   // Zero is the default
   Float64 GetSpaceFactor() const;

   // GROUP: INQUIRY
   //------------------------------------------------------------------------
   // Get bounding box for dimension to be drawn
   gpRect2d GetBoundingBox(HDC hDC, const grlibPointMapper& mapper) const;

   //------------------------------------------------------------------------
   // Get approximate vertical height of dimension in device coordinates. This
   // function will only return the correct value for horizontal dimensions where
   // the hook points are at the same Y value.
   LONG GetApproxVerticalHeight(HDC hDC) const;

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const grDimension& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const grDimension& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   gpPoint2d m_PointA; // hook points
   gpPoint2d m_PointB;

   DimensionStyle           m_Style;
   VerticalDimensionPos     m_VPos;
   HorizontalDimensionPos   m_HPos;
   Float64                  m_AdditionalOffset;
   bool                     m_DoDrawArrows;
   Float64                  m_SpaceFactor;

   // mutable dimension geometry
   mutable bool m_IsUpdated;
   mutable gpPoint2d m_LeftWitness[2];
   mutable gpPoint2d m_RightWitness[2];
   mutable gpPoint2d m_LeftLeader[2];
   mutable gpPoint2d m_RightLeader[2];
   mutable gpPoint2d m_LeftArrowLoc;
   mutable Float64   m_LeftArrowDir;
   mutable gpPoint2d m_RightArrowLoc;
   mutable Float64   m_RightArrowDir;
   mutable grLabel   m_Label;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   bool UpdateGeometry(HDC hDC, const grlibPointMapper& mapper) const;
   bool UpdateHorizontal(HDC hDC, const grlibPointMapper& mapper) const;
   bool UpdateVertical(HDC hDC, const grlibPointMapper& mapper) const;
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
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

#endif // INCLUDED_GRAPHICSLIB_DIMENSION_H_

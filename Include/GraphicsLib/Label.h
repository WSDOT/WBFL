///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright © 1999-2019  Washington State Department of Transportation
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

#ifndef INCLUDED_GRAPHICSLIB_LABEL_H_
#define INCLUDED_GRAPHICSLIB_LABEL_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GraphicsLib\GraphicsLibExp.h>
#include <GeometricPrimitives\Primitives.h>
#include <GraphicsLib\PointMapper.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   grLabel

   A class to represent a label which may be drawn on the screen


DESCRIPTION
   This class allows you to put a mult-line label at a precise location in
   world coordinates on the screen. Multi-line labels are created by putting
   std::endl's (\n's) into the label string.

   The point size of the font can be specified, but the font is always arial.

LOG
   rdp : 05.05.1999 : Created file
*****************************************************************************/

class GRCLASS grLabel
{
public:
   // GROUP: LIFECYCLE
   // 
   enum HorizPosition {Left, Center, Right};
   enum VertPosition {Top, Middle, Bottom};

   //------------------------------------------------------------------------
   // Default constructor
   grLabel();

   //------------------------------------------------------------------------
   // Constructor - sets hook point and label
   // Center-Middle by default.
   grLabel(const gpPoint2d& point, const std::_tstring& label);

   //------------------------------------------------------------------------
   // Copy constructor
   grLabel(const grLabel& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~grLabel();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   grLabel& operator = (const grLabel& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Draw
   // Label is drawn left justified using the settings defined by the 
   // DC
   virtual void Draw(HDC hDC, const grlibPointMapper& mapper) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // SetHorizPosition - sets the Horizontal Position mode as to where the hook
   // point is located on the bounding box of the label.
   void SetHorizPosition(HorizPosition pos);

   //------------------------------------------------------------------------
   // GetHorizPosition - get the horizontal position mode
   HorizPosition GetHorizPosition() const;

   //------------------------------------------------------------------------
   // SetVertPosition - sets the vertical Position mode as to where the hook
   // point is located on the bounding box of the label.
   void SetVertPosition(VertPosition pos);

   //------------------------------------------------------------------------
   // GetVertPosition - get the vertical position mode
   VertPosition GetVertPosition() const;

   //------------------------------------------------------------------------
   // Set hook point
   void SetHookPoint(const gpPoint2d& point);

   //------------------------------------------------------------------------
   // Get hook point.
   gpPoint2d GetHookPoint() const;

   //------------------------------------------------------------------------
   // SetLocation - sets hook point and orientation all at once
   void SetLocation(const gpPoint2d& point, HorizPosition hpos, VertPosition pos);

   //------------------------------------------------------------------------
   //  Set the label to be placed on the dimension. std::endl's (\n's) in the string
   //  will start a new line and create a multiline label.
   void SetLabel(const std::_tstring& label);

   //------------------------------------------------------------------------
   // Get the label
   std::_tstring GetLabel() const;

   //------------------------------------------------------------------------
   // Set point size for label
   void SetPointSize(Uint32 siz);

   //------------------------------------------------------------------------
   // Get point size for label
   Uint32 GetPointSize() const;

   // GROUP: INQUIRY
   //------------------------------------------------------------------------
   // Get bounding box for dimension to be drawn
   virtual gpRect2d GetBoundingBox(HDC hDC, const grlibPointMapper& mapper) const;

   //------------------------------------------------------------------------
   // Get size for dimension to be drawn
   virtual gpSize2d GetSize(HDC hDC, const grlibPointMapper& mapper) const;

   //------------------------------------------------------------------------
   // Get # of lines in label
   IndexType GetNumLines() const;

   //------------------------------------------------------------------------
   // Get Height, in world coordinates of a single line in the label
   Float64 GetLineHeight(HDC hDC, const grlibPointMapper& mapper) const;

   //------------------------------------------------------------------------
   // Get Height, in device coordinates of a single line in the label
   LONG GetLineHeight(HDC hDC) const;


protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const grLabel& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const grLabel& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   gpPoint2d                m_HookPoint;
   std::vector<std::_tstring> m_Labels;
   HorizPosition            m_HorizPos;
   VertPosition             m_VertPos;
   Int32                    m_PointSize;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
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
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GRAPHICSLIB_LABEL_H_

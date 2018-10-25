///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
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

#if !defined INCLUDED_GRAPHICSLIB_GRAPHTOOL_H_
#define INCLUDED_GRAPHICSLIB_GRAPHTOOL_H_
#pragma once

// :COCOON: rdp 09.18.1997 : Cocoon limitations
// :FILE:   GraphTool.h
//
// All preprocessor stuff must go up here because of limitations in
// Cocoon.

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GraphicsLib\GraphicsLibExp.h>
#include <GraphicsLib\PointMapper.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   grGraphTool

   Miscellaneous utilities for making programming in Windows a more pleasant
   experience


DESCRIPTION
   tool


   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

LOG
   rdp : 09.18.1997 : Created file
*****************************************************************************/

class GRCLASS grGraphTool
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Place text at the desired location that is rotated at an arbitrary
   // Rotation in tenth degrees
   static bool TextOutRotated(HDC hDC, LONG x, LONG y, LONG rotation, 
                               LPCTSTR lpszText, LONG textlen, 
                               LONG nPointSize, LPCTSTR lpszFacename=_T("Arial"));

   //------------------------------------------------------------------------
   // Create a ready to go font. Must be deleted with DeleteObject() after use.
   // Rotation in tenth degrees
   static HFONT CreateRotatedFont(HDC hDC, LONG rotation,  
                                  LONG nPointSize, LPCTSTR lpszFaceName=_T("Arial"));

   //------------------------------------------------------------------------
   // A 'nice' range calculation function. You input an original Min and Max
   // and a desired number of segments for the range, and it returns a 
   // nice range, the number of segments it used and a nice increment.
   // Note if numberOfSegments is INVALID_INDEX then this routine will try to select an appropriate
   // nice value
   // It will also try to shrink the bounds of the interval if the original max or
   // min only slightly intrude into the outer bands.
   static void CalculateNiceRange(const Float64 originalMin, const Float64 originalMax, bool bOffsetZero,
                                  CollectionIndexType& numberOfSegments, 
                                  Float64& niceMin, Float64& niceMax, 
                                  Float64& niceIncrement);

   //------------------------------------------------------------------------
   // Draw a rectangle
   static void DrawRect(HDC hDC, const grlibPointMapper& mapper, const gpRect2d& rect, 
                        COLORREF borderColor=RGB(0,0,0), 
                        bool doFill=false, COLORREF fillColor=RGB(255,255,255));
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   //------------------------------------------------------------------------
   // Default constructor
   grGraphTool();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~grGraphTool();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   grGraphTool(const grGraphTool&);
   grGraphTool& operator=(const grGraphTool&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GRAPHICSLIB_GRAPHTOOL_H_


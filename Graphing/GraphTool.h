///////////////////////////////////////////////////////////////////////
// Graphing - Line graph plotting and graph definition management library
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


#include <Graphing/PointMapper.h>

namespace WBFL
{
   namespace Graphing
   { 

/// Helper tools for creating graph fonts, texts, and ranges
class GraphTool
{
public:
   GraphTool() = delete;
   ~GraphTool() = delete;
   GraphTool(const GraphTool&) = delete;
   GraphTool& operator=(const GraphTool&) = delete;

   /// Place text at the desired location that is rotated at an arbitrary.
   /// Rotation in tenth degrees
   static bool TextOutRotated(HDC hDC, LONG x, LONG y, LONG rotation, 
                               LPCTSTR lpszText, LONG textlen, 
                               LONG nPointSize, LPCTSTR lpszFacename=_T("Arial"));

   /// Create a ready to go font. Must be deleted with DeleteObject() after use.
   /// Rotation in tenth degrees
   static HFONT CreateRotatedFont(HDC hDC, LONG rotation,  
                                  LONG nPointSize, LPCTSTR lpszFaceName=_T("Arial"));

   /// A 'nice' range calculation function. You input an original Min and Max
   /// and a desired number of segments for the range, and it returns a 
   /// nice range, the number of segments it used and a nice increment.
   /// Note if numberOfSegments is INVALID_INDEX then this routine will try to select an appropriate
   /// nice value
   /// It will also try to shrink the bounds of the interval if the original max or
   /// min only slightly intrude into the outer bands.
   static void CalculateNiceRange(const Float64 originalMin, const Float64 originalMax, bool bOffsetZero,
                                  CollectionIndexType& numberOfSegments, 
                                  Float64& niceMin, Float64& niceMax, 
                                  Float64& niceIncrement);

   /// Draw a rectangle
   static void DrawRect(HDC hDC, const PointMapper& mapper, const Rect& rect,
                        COLORREF borderColor=RGB(0,0,0), 
                        bool doFill=false, COLORREF fillColor=RGB(255,255,255));
};

   }; // Graphing
}; // WBFL

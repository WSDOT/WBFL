///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifndef INCLUDED_COORDINATEMAP_H_
#define INCLUDED_COORDINATEMAP_H_
#pragma once

class CDisplayView;

interface iCoordinateMap : public IUnknown
{
   // Model Space - the space in which the model is created
   // World Space - space resulting from the model space being rotated, translated, and scaled 
   // Logical Space - space of the drawing window

   // Model point to World Point conversions
   STDMETHOD_(void,MPtoWP)(Float64 mx,Float64 my,Float64* wx,Float64* wy) PURE;
   STDMETHOD_(void,MPtoWP)(IPoint2d* mp,Float64* wx,Float64* wy) PURE;

   STDMETHOD_(void,WPtoMP)(Float64 wx,Float64 wy,Float64* mx,Float64* my) PURE;
   STDMETHOD_(void,WPtoMP)(IPoint2d* wp,Float64* mx,Float64* my) PURE;

   // World point to Logical Point conversions
   STDMETHOD_(void,WPtoLP)(Float64 wx,Float64 wy,LONG* lx,LONG* ly) PURE;
   STDMETHOD_(void,WPtoLP)(IPoint2d* wp,LONG* lx,LONG* ly) PURE;

   STDMETHOD_(void,LPtoWP)(LONG lx,LONG ly,Float64* wx,Float64* wy) PURE;
   STDMETHOD_(void,LPtoWP)(LONG lx,LONG ly,IPoint2d** wp) PURE;

   // conversion to Text space. This space is always isometrically mapped.
   //  -The origin of this space is at the Logical Origin
   //  -Each text unit is a twip, or 1/20 of a point.(Because a point 
   //   is 1/72 inch, a twip is 1/1440 inch.) 
   //  -Positive X is to the right positive Y is up on the device.
   STDMETHOD_(void,WPtoTP)(Float64 wx,Float64 wy,LONG* tx,LONG* ty) PURE;
   STDMETHOD_(void,TPtoWP)(LONG tx,LONG ty,Float64* wx,Float64* wy) PURE;

   STDMETHOD_(void,LPtoTP)(LONG lx,LONG ly,LONG* tx,LONG* ty) PURE;
   STDMETHOD_(void,TPtoLP)(LONG tx,LONG ty,LONG* lx,LONG* ly) PURE;

   // Get size of window in text space coordinates (twips)
   // This window is the size of the logical extents.
   STDMETHOD_(CSize,GetTextWindowExtent)() PURE;

   // get text extent in logical coord's. Font dimensions are expected in
   // 1/10 points (i.e., in form needed by CreatePointFontIndirect).
   // Adjust for DPI scaling
   STDMETHOD_(CSize,GetTextExtent)(CDisplayView* pView,const LOGFONT& font, LPCTSTR lpszText) PURE;
};

#endif // INCLUDED_COORDINATEMAP_H_
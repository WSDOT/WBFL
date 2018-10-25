///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#ifndef INCLUDED_TEXTBLOCK_H_
#define INCLUDED_TEXTBLOCK_H_
#pragma once

#include <DManip\DisplayObject.h>

// This can be generalized to draw texted based on a
// drawing strategy. That way the MFC specific
// stuff can be removed from the interface
interface iTextBlock : public iDisplayObject
{
   STDMETHOD_(void,SetPosition)(IPoint2d* pos) PURE;
   STDMETHOD_(void,GetPosition)(IPoint2d** pos) PURE;

   // Use CDC::SetTextAlign constants
   STDMETHOD_(void,SetTextAlign)(UINT nFlags) PURE;
   STDMETHOD_(UINT,GetTextAlign)() PURE;

   STDMETHOD_(void,SetAngle)(LONG angle) PURE;
   STDMETHOD_(LONG,GetAngle)() PURE;

   STDMETHOD_(void,SetText)(LPCTSTR lpszText) PURE;
   STDMETHOD_(CString,GetText)() PURE;

   // set font. Note that font height is in 10th of points.
   STDMETHOD_(void,SetFont)(const LOGFONT& Font) PURE;
   STDMETHOD_(void,GetFont)(LOGFONT* pFont) PURE;

   STDMETHOD_(void,SetTextColor)(COLORREF color) PURE;
   STDMETHOD_(COLORREF,GetTextColor)() PURE;

   STDMETHOD_(void,SetBkColor)(COLORREF color) PURE;
   STDMETHOD_(COLORREF,GetBkColor)() PURE;

   STDMETHOD_(void,SetBkMode)(int bkMode) PURE;
   STDMETHOD_(int,GetBkMode)() PURE;
};

// Draws text as a title on a view. The title is centered 
// on the top of the display view
interface iViewTitle : public iDisplayObject
{
   STDMETHOD_(void,SetText)(LPCTSTR lpszText) PURE;
   STDMETHOD_(CString,GetText)() PURE;

   // set font. Note that font height is in 10th of points.
   STDMETHOD_(void,SetFont)(const LOGFONT& Font) PURE;
   STDMETHOD_(void,GetFont)(LOGFONT* pFont) PURE;
};

#endif // INCLUDED_TEXTBLOCK_H_
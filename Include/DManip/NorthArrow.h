///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright � 1999-2025  Washington State Department of Transportation
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

#ifndef INCLUDED_NORTHARROW_H_
#define INCLUDED_NORTHARROW_H_
#pragma once

#include <DManip\DisplayObject.h>

interface iNorthArrow : public iDisplayObject
{
   STDMETHOD_(void,SetText)(LPCTSTR lpszText) PURE;
   STDMETHOD_(CString,GetText)() PURE;

   // set font. Note that font height is in 10th of points.
   STDMETHOD_(void,SetFont)(const LOGFONT& Font) PURE;
   STDMETHOD_(void,GetFont)(LOGFONT* pFont) PURE;

   STDMETHOD_(void,SetDirection)(Float64 angle) PURE;
   STDMETHOD_(Float64,GetDirection)() PURE;

   STDMETHOD_(void,SetSize)(LONG size) PURE;
   STDMETHOD_(LONG,GetSize)() PURE;
};

#endif // INCLUDED_NORTHARROW_H_
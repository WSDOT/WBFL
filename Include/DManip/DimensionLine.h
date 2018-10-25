///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_DIMENSIONLINE_H_
#define INCLUDED_DIMENSIONLINE_H_
#pragma once

#include <DManip\DisplayObject.h>
#include <DManip\DManipTypes.h>

struct iTextBlock;

// Note that all distances set below are in twips (1/1440 inches)
interface iDimensionLine : public iDisplayObject
{
   STDMETHOD_(void,SetAngle)(Float64 angle) PURE;
   STDMETHOD_(Float64,GetAngle)() PURE;
   STDMETHOD_(void,SetWitnessLength)(LONG l) PURE;
   STDMETHOD_(LONG,GetWitnessLength)() PURE;
   STDMETHOD_(void,SetWitnessOffset)(LONG wOffset) PURE;
   STDMETHOD_(LONG,GetWitnessOffset)() PURE;
   STDMETHOD_(void,SetArrowHeadSize)(CSize size) PURE;
   STDMETHOD_(CSize,GetArrowHeadSize)() PURE;
   STDMETHOD_(void,SetArrowHeadStyle)(DManip::ArrowHeadStyleType style) PURE;
   STDMETHOD_(DManip::ArrowHeadStyleType,GetArrowHeadStyle)() PURE;
   STDMETHOD_(void,EnableAutoText)(BOOL bEnable) PURE;
   STDMETHOD_(BOOL,IsAutoTextEnabled)() PURE;
   STDMETHOD_(void,SetTextBlock)(iTextBlock* pTextBlock) PURE;
   STDMETHOD_(void,GetTextBlock)(iTextBlock** textBlock) PURE;
};

#endif // INCLUDED_DIMENSIONLINE_H_
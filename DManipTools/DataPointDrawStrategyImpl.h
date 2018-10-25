///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright (C) 2008  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#ifndef INCLUDED_DATAPOINTDRAWSTRATEGYIMPL_H_
#define INCLUDED_DATAPOINTDRAWSTRATEGYIMPL_H_
#pragma once

#include "DataPointDrawStrategy.h"

class CDataPointDrawStrategyImpl : public CCmdTarget
{
public:
   CDataPointDrawStrategyImpl();
   ~CDataPointDrawStrategyImpl();

   DECLARE_INTERFACE_MAP()

   BEGIN_INTERFACE_PART(Strategy,iDataPointDrawStrategy)
      STDMETHOD_(void,get_SymbolFontFace)(char* *pVal);
      STDMETHOD_(void,put_SymbolFontFace)(const char* newVal);
      // character font size in 1/10 points
      STDMETHOD_(long,get_SymbolSize)();
      STDMETHOD_(void,put_SymbolSize)(long code);
      STDMETHOD_(DWORD,get_SymbolCharacterCode)();
      STDMETHOD_(void,put_SymbolCharacterCode)(DWORD code);
      STDMETHOD_(COLORREF,get_Color)();
      STDMETHOD_(void,put_Color)(COLORREF color);
   END_INTERFACE_PART(Strategy)

   BEGIN_INTERFACE_PART(DrawPointStrategy,iDrawPointStrategy)
      STDMETHOD_(void,Draw)(iPointDisplayObject* pDO,CDC* pDC);
      STDMETHOD_(void,DrawDragImage)(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);
      STDMETHOD_(void,DrawHighlite)(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
      STDMETHOD_(void,GetBoundingBox)(iPointDisplayObject* pDO,IRect2d** box);
   END_INTERFACE_PART(DrawPointStrategy)

private:
   virtual void Draw(iPointDisplayObject* pDO,CDC* pDC,COLORREF color,IPoint2d* loc);

   CString  m_FontFace;
   long     m_FontSize;
   DWORD    m_CharCode;
   COLORREF m_Color;
};

#endif // INCLUDED_DATAPOINTDRAWSTRATEGYIMPL_H_
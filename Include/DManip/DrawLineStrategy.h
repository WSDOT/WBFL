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

#ifndef INCLUDED_DRAWLINESTRATEGY_H_
#define INCLUDED_DRAWLINESTRATEGY_H_
#pragma once

interface iLineDisplayObject;

interface iDrawLineStrategy : public IUnknown
{
   // Draws the line in its normal or selected state
   STDMETHOD_(void,Draw)(iLineDisplayObject* pDO,CDC* pDC) PURE;

   // Draws the line while it is being dragged
   STDMETHOD_(void,DrawDragImage)(iLineDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint) PURE;

   // Draws the line in a highlited state. Usually when something is being dragged over it
   STDMETHOD_(void,DrawHighlite)(iLineDisplayObject* pDO,CDC* pDC,BOOL bHighlite) PURE;

   STDMETHOD_(void,GetBoundingBox)(iLineDisplayObject* pDO,IRect2d** box) PURE;
};

#endif // INCLUDED_DRAWLINESTRATEGY_H_
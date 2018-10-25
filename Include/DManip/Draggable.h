///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_DRAGGABLE_H_
#define INCLUDED_DRAGGABLE_H_
#pragma once

interface iDragDataSource;
interface iDragDataSink;
interface iDragData;
interface iCoordinateMap;

interface iDraggable : public IUnknown
{
   STDMETHOD_(void,SetDragData)(iDragData* dd) PURE;
   STDMETHOD_(void,GetDragData)(iDragData** dd) PURE;

   STDMETHOD_(UINT,Format)() PURE;
   STDMETHOD_(void,PrepareDrag)(iDragDataSink* pSink) PURE;
   STDMETHOD_(void,OnDrop)(iDragDataSource* pSource) PURE;
   STDMETHOD_(void,OnDragMoved)(ISize2d* offset) PURE;
   STDMETHOD_(void,OnMoved)() PURE;
   STDMETHOD_(void,OnCopied)() PURE;

   STDMETHOD_(void,DrawDragImage)(CDC* pDC,
                                  iCoordinateMap* map,
                                  const CPoint& dragStart,
                                  const CPoint& dragPoint) PURE;
};

#endif // INCLUDED_DRAGGABLE_H_
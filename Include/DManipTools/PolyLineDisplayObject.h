///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_IPOLYLINEDISPLAYOBJECT_H_
#define INCLUDED_IPOLYLINEDISPLAYOBJECT_H_
#pragma once

#include "DManipToolsTypes.h"

typedef enum PolyLinePointType
{
   plpNone   = 0,
   plpCircle = 1,
   plpDot    = 2
} PolyLinePointType;

// {4B929127-C494-44af-B4A6-1DB9A3143067}
DEFINE_GUID(IID_iPolyLineDisplayObject, 
0x4b929127, 0xc494, 0x44af, 0xb4, 0xa6, 0x1d, 0xb9, 0xa3, 0x14, 0x30, 0x67);
struct __declspec(uuid("{4B929127-C494-44af-B4A6-1DB9A3143067}")) iPolyLineDisplayObject;
interface iPolyLineDisplayObject : public iDisplayObject
{
   STDMETHOD_(void,Commit)() PURE;
   STDMETHOD_(CollectionIndexType,get_NumberOfPoints)() PURE;
   STDMETHOD_(void,AddPoints)(IPoint2dCollection* points) PURE;
   STDMETHOD_(void,AddPoint)(IPoint2d* point) PURE;
   STDMETHOD_(HRESULT,InsertPoint)(CollectionIndexType idx, IPoint2d* point) PURE;
   STDMETHOD_(HRESULT,GetPoint)(CollectionIndexType idx, IPoint2d* *point) PURE;
   STDMETHOD_(HRESULT,RemovePoint)(CollectionIndexType idx) PURE;
   STDMETHOD_(void,ClearPoints)() PURE;
   STDMETHOD_(void,put_Color)(COLORREF color) PURE;
   STDMETHOD_(void,get_Color)(COLORREF* color) PURE;
   STDMETHOD_(void,put_Width)(long width) PURE;
   STDMETHOD_(void,get_Width)(long* width) PURE;
   STDMETHOD_(void,put_PointType)(PolyLinePointType ptType) PURE;
   STDMETHOD_(void,get_PointType)(PolyLinePointType* ptType) PURE;
};

#endif 
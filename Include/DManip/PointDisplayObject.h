///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

#ifndef INCLUDED_POINTDISPLAYOBJECT_H_
#define INCLUDED_POINTDISPLAYOBJECT_H_
#pragma once

#include <DManip\DisplayObject.h>

interface iDrawPointStrategy;

interface iPointDisplayObject : public iDisplayObject
{
   STDMETHOD_(void,SetPosition)(IPoint2d* pos,BOOL bRedraw,BOOL bFireEvent) PURE;
   STDMETHOD_(void,GetPosition)(IPoint2d* *pos) PURE;
   STDMETHOD_(CPoint,GetPosition)() PURE;
   STDMETHOD_(void,Offset)(ISize2d* offset,BOOL bRedraw,BOOL bFireEvent) PURE;
   STDMETHOD_(void,SetDrawingStrategy)(iDrawPointStrategy* pStrategy) PURE;
   STDMETHOD_(void,GetDrawingStrategy)(iDrawPointStrategy** pStrategy) PURE;
   STDMETHOD_(void,EnableAutoUpdate)(BOOL bEnable) PURE;
   STDMETHOD_(BOOL,IsAutoUpdateEnabled)() PURE;
};

#endif // INCLUDED_POINTDISPLAYOBJECT_H_

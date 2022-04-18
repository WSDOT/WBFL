///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifndef INCLUDED_DISPLAYLIST_H_
#define INCLUDED_DISPLAYLIST_H_
#pragma once

#include <DManip\DisplayObjectContainer.h>
#include <DManip\DManipTypes.h>

struct iDisplayObject;
struct iDisplayMgr;
struct iDisplayListEvents;
interface IPoint2d;
interface ISize2d;

interface iDisplayList : public IUnknown
{
   STDMETHOD_(void,SetDisplayMgr)(iDisplayMgr* pDispMgr) PURE;
   STDMETHOD_(void,GetDisplayMgr)(iDisplayMgr** dispMgr) PURE;

   STDMETHOD_(void,SetID)(IDType id) PURE;
   STDMETHOD_(IDType,GetID)() PURE;

   STDMETHOD_(void,AddDisplayObject)(iDisplayObject* pDO) PURE;
   STDMETHOD_(void,GetDisplayObject)(CollectionIndexType index,iDisplayObject** dispObj) PURE;
   STDMETHOD_(void,FindDisplayObject)(IDType id,iDisplayObject** dispObj) PURE;
   STDMETHOD_(void,RemoveDisplayObject)(IDType key,AccessType access) PURE;
   STDMETHOD_(void,Clear)() PURE;
   STDMETHOD_(CollectionIndexType,GetDisplayObjectCount)() PURE;

   STDMETHOD_(void,FindDisplayObjects)(CRect rect,      DisplayObjectContainer* dispObjs) PURE;
   STDMETHOD_(void,FindDisplayObjects)(CPoint point,    DisplayObjectContainer* dispObjs) PURE;
   STDMETHOD_(void,FindDisplayObjects)(IPoint2d* point, DisplayObjectContainer* dispObjs) PURE;

   STDMETHOD_(void,DrawDisplayObjects)(CDC* pDC,bool bSkipSelected) PURE;
   STDMETHOD_(void,HideDisplayObjects)(bool bHide) PURE;

   STDMETHOD_(void,GetWorldExtents)(ISize2d* *ext) PURE;

#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWells)(CDC* pDC) PURE;
#endif

   // Event Sink
   STDMETHOD_(void,RegisterEventSink)(iDisplayListEvents* pEventSink) PURE;
   STDMETHOD_(void,UnregisterEventSink)() PURE;
   STDMETHOD_(void,GetEventSink)(iDisplayListEvents** pEventSink) PURE;
};


#endif // INCLUDED_DISPLAYLIST_H_
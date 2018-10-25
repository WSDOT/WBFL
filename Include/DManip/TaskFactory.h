///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

#ifndef INCLUDED_TASKFACTORY_H_
#define INCLUDED_TASKFACTORY_H_
#pragma once

class CDisplayView;

interface iTask;
interface iDisplayMgr;
interface iInplaceEditable;

interface iTaskFactory : public IUnknown
{
   STDMETHOD_(void,CreateInplaceEditTask)(CDisplayView* pView,iInplaceEditable* pEditable,iTask** task) PURE;
   STDMETHOD_(void,CreateRectSelectTask)(iDisplayMgr* pDispMgr,const CPoint& startPoint,iTask** task) PURE;
   STDMETHOD_(void,CreateLocalDragDropTask)(iDisplayMgr* pDispMgr,const CPoint& startPoint,iTask** task) PURE;
   STDMETHOD_(void,CreateForeignDragDropTask)(iDisplayMgr* pDispMgr,const CPoint& startPoint,iTask** task) PURE;
   STDMETHOD_(void,CreateCenterOnPointTask)(CDisplayView* pView,iTask** task) PURE;
   STDMETHOD_(void,CreateZoomTask)(CDisplayView* pView,HCURSOR hCursor,COLORREF color,iTask** task) PURE;
};

#endif // INCLUDED_TASKFACTORY_H_
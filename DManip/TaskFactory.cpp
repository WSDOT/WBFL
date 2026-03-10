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

#include "pch.h"
#include <DManip/TaskFactory.h>
#include "InplaceEditTaskImpl.h"
#include "RectSelectTaskImpl.h"
#include "LocalDragDropTaskImpl.h"
#include "ForeignDragDropTaskImpl.h"
#include "CenterOnPointTaskImpl.h"
#include "ZoomRectTaskImpl.h"

using namespace WBFL::DManip;

std::shared_ptr<iTask> TaskFactory::CreateInplaceEditTask(CDisplayView* pView,std::shared_ptr<iInplaceEditable> pEditable) const
{
   return std::make_shared<InplaceEditTask>(pView, pEditable);
}

std::shared_ptr<iTask> TaskFactory::CreateRectSelectTask(std::shared_ptr<iDisplayMgr> pDispMgr,const CPoint& startPoint) const
{
   return std::make_shared<RectSelectTask>(pDispMgr, startPoint);
}

std::shared_ptr<iTask> TaskFactory::CreateLocalDragDropTask(std::shared_ptr<iDisplayMgr> pDispMgr,const CPoint& startPoint) const
{
   return std::make_shared<LocalDragDropTask>(pDispMgr, startPoint);
}

std::shared_ptr<iTask> TaskFactory::CreateForeignDragDropTask(std::shared_ptr<iDisplayMgr> pDispMgr,const CPoint& startPoint) const
{
   return std::make_shared<ForeignDragDropTask>(pDispMgr, startPoint);
}

std::shared_ptr<iTask> TaskFactory::CreateCenterOnPointTask(CDisplayView* pView) const
{
   return std::make_shared<CenterOnPointTask>(pView);
}

std::shared_ptr<iTask> TaskFactory::CreateZoomTask(CDisplayView* pView,HCURSOR hCursor,COLORREF color) const
{
   return std::make_shared<ZoomRectTask>(pView, hCursor, color);
}

///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// TaskFactoryImpl.cpp: implementation of the CTaskFactoryImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "TaskFactoryImpl.h"

#include "InplaceEditTaskImpl.h"
#include "RectSelectTaskImpl.h"
#include "LocalDragDropTaskImpl.h"
#include "ForeignDragDropTaskImpl.h"
#include "CenterOnPointTaskImpl.h"
#include "ZoomRectTaskImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskFactoryImpl::CTaskFactoryImpl()
{

}

CTaskFactoryImpl::~CTaskFactoryImpl()
{

}

void CTaskFactoryImpl::CreateInplaceEditTask(CDisplayView* pView,iInplaceEditable* pEditable,iTask** task)
{
   CComObject<CInplaceEditTaskImpl>* pTask;
   CComObject<CInplaceEditTaskImpl>::CreateInstance(&pTask);
   pTask->Init(pView,pEditable);

   (*task) = pTask;
   (*task)->AddRef();
}

void CTaskFactoryImpl::CreateRectSelectTask(iDisplayMgr* pDispMgr,const CPoint& startPoint,iTask** task)
{
   CComObject<CRectSelectTaskImpl>* pTask;
   CComObject<CRectSelectTaskImpl>::CreateInstance(&pTask);
   pTask->Init(pDispMgr,startPoint);

   (*task) = pTask;
   (*task)->AddRef();
}

void CTaskFactoryImpl::CreateLocalDragDropTask(iDisplayMgr* pDispMgr,const CPoint& startPoint,iTask** task)
{
   CComObject<CLocalDragDropTaskImpl>* pTask;
   CComObject<CLocalDragDropTaskImpl>::CreateInstance(&pTask);
   pTask->Init(pDispMgr,startPoint);

   (*task) = pTask;
   (*task)->AddRef();
}

void CTaskFactoryImpl::CreateForeignDragDropTask(iDisplayMgr* pDispMgr,const CPoint& startPoint,iTask** task)
{
   CComObject<CForeignDragDropTaskImpl>* pTask;
   CComObject<CForeignDragDropTaskImpl>::CreateInstance(&pTask);
   pTask->Init(pDispMgr,startPoint);

   (*task) = pTask;
   (*task)->AddRef();
}

void CTaskFactoryImpl::CreateCenterOnPointTask(CDisplayView* pView,iTask** task)
{
   CComObject<CCenterOnPointTaskImpl>* pTask;
   CComObject<CCenterOnPointTaskImpl>::CreateInstance(&pTask);
   pTask->Init(pView);

   (*task) = pTask;
   (*task)->AddRef();
}

void CTaskFactoryImpl::CreateZoomTask(CDisplayView* pView,HCURSOR hCursor,COLORREF color,iTask** task)
{
   CComObject<CZoomRectTaskImpl>* pTask;
   CComObject<CZoomRectTaskImpl>::CreateInstance(&pTask);
   pTask->Init(pView,hCursor,color);

   (*task) = pTask;
   (*task)->AddRef();
}

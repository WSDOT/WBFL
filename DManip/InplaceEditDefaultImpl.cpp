///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// InplaceEditDefaultImpl.cpp: implementation of the CInplaceEditDefaultImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <DManip\DManip.h>
#include "InplaceEditDefaultImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInplaceEditDefaultImpl::CInplaceEditDefaultImpl()
{

}

CInplaceEditDefaultImpl::~CInplaceEditDefaultImpl()
{

}

STDMETHODIMP_(void) CInplaceEditDefaultImpl::DoInplaceEdit()
{
   // Create the task and start it.
   CComPtr<iTask> pTask;
   CreateTask(&pTask);

   CDisplayView* pView = GetDisplayView();
   
   CComPtr<iDisplayMgr> pDispMgr;
   pView->GetDisplayMgr(&pDispMgr);
   pDispMgr->SetTask(pTask);

   CInplaceEdit* pEdit = GetEditObject();
   pEdit->SetTask(pTask);
}

void CInplaceEditDefaultImpl::CreateTask(iTask** task)
{
   // Create the task using the task factory
   CDisplayView* pView = GetDisplayView();
   
   CComPtr<iDisplayMgr> pDispMgr;
   pView->GetDisplayMgr(&pDispMgr);
   
   CComPtr<iTaskFactory> pFactory;
   pDispMgr->GetTaskFactory(&pFactory);

   pFactory->CreateInplaceEditTask(pView,this,task);
}

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
#include <DManip/InplaceEditableDefaultImpl.h>
#include <DManip/DisplayView.h>
#include <DManip/InplaceEditCtrl.h>
#include <DManip/Task.h>
#include <DManip/TaskFactory.h>

using namespace WBFL::DManip;

void InplaceEditableDefaultImpl::DoInplaceEdit()
{
   // Create the task and start it.
   auto task = CreateTask();

   auto* pView = GetDisplayView();

   auto display_mgr = pView->GetDisplayMgr();
   display_mgr->SetTask(task);

   auto* pEdit = GetEditObject();
   pEdit->SetTask(task);
}

void InplaceEditableDefaultImpl::EndInplaceEdit()
{
   auto* pView = GetDisplayView();

   auto display_mgr = pView->GetDisplayMgr();
   display_mgr->SetTask(nullptr);

   auto* pEdit = GetEditObject();
   pEdit->SetTask(nullptr);
}

void InplaceEditableDefaultImpl::SetParent(std::weak_ptr<iDisplayObject> pParent)
{
   m_pCompositeParent = pParent;
}

std::shared_ptr<iDisplayObject> InplaceEditableDefaultImpl::GetParent()
{
   return m_pCompositeParent.lock();
}

std::shared_ptr<iTask> InplaceEditableDefaultImpl::CreateTask()
{
   // Create the task using the task factory
   auto* pView = GetDisplayView();
   auto display_mgr = pView->GetDisplayMgr();
   auto task_factory = display_mgr->GetTaskFactory();
   return task_factory->CreateInplaceEditTask(pView, GetInplaceEditable());
}

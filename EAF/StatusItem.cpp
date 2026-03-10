///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

#include "StdAfx.h"
#include <EAF\StatusItem.h>
#include <EAF\EAFUtilities.h>

using namespace WBFL::EAF;

StatusItem::StatusItem(StatusGroupIDType statusGroupID,StatusCallbackIDType callbackID,LPCTSTR strDescription) :
m_strDescription(strDescription), m_bRemoveAfterEdit(FALSE)
{
   m_StatusGroupID = statusGroupID;
   m_CallbackID    = callbackID;
   m_ID = INVALID_ID;
}

StatusItem::~StatusItem()
{
}

void StatusItem::SetID(StatusItemIDType id)
{
   m_ID = id;
}

StatusItemIDType StatusItem::GetID() const
{
   return m_ID;
}

StatusGroupIDType StatusItem::GetStatusGroupID() const
{
   return m_StatusGroupID;
}

LPCTSTR StatusItem::GetDescription() const
{
   return m_strDescription;
}

StatusCallbackIDType StatusItem::GetCallbackID() const
{
   return m_CallbackID;
}

BOOL StatusItem::RemoveAfterEdit()
{
   return m_bRemoveAfterEdit;
}

void StatusItem::RemoveAfterEdit(BOOL bRemoveAfterEdit)
{
   m_bRemoveAfterEdit = bRemoveAfterEdit;
}

//////////////////////////////////////////////////////////////////////////////
StatusItemCallback::StatusItemCallback(WBFL::EAF::StatusSeverityType severity,LPCTSTR lpszDocSetName,UINT helpID):
m_Severity(severity), m_strDocSetName(lpszDocSetName),m_HelpID(helpID)
{
}

WBFL::EAF::StatusSeverityType StatusItemCallback::GetSeverity() const
{
   return m_Severity;
}

void StatusItemCallback::Execute(std::shared_ptr<StatusItem> pItem)
{
   EAFShowStatusMessage(pItem,m_Severity,FALSE,FALSE,m_strDocSetName,m_HelpID);
}

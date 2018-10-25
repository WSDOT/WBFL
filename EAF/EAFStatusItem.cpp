///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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
#include <EAF\EAFStatusItem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEAFStatusItem::CEAFStatusItem(StatusGroupIDType statusGroupID,StatusCallbackIDType callbackID,LPCTSTR strDescription) :
m_Description(strDescription), m_bRemoveAfterEdit(false)
{
   m_StatusGroupID = statusGroupID;
   m_CallbackID    = callbackID;
   m_ID = INVALID_ID;
}

void CEAFStatusItem::SetID(StatusItemIDType id)
{
   m_ID = id;
}

StatusItemIDType CEAFStatusItem::GetID() const
{
   return m_ID;
}

StatusGroupIDType CEAFStatusItem::GetStatusGroupID() const
{
   return m_StatusGroupID;
}

const std::_tstring& CEAFStatusItem::GetDescription() const
{
   return m_Description;
}

StatusCallbackIDType CEAFStatusItem::GetCallbackID() const
{
   return m_CallbackID;
}

bool CEAFStatusItem::RemoveAfterEdit()
{
   return m_bRemoveAfterEdit;
}

void CEAFStatusItem::RemoveAfterEdit(bool bRemoveAfterEdit)
{
   m_bRemoveAfterEdit = bRemoveAfterEdit;
}


///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFTemplateGroup.h>

IMPLEMENT_DYNAMIC(CEAFTemplateItem,CObject)

CEAFTemplateItem::CEAFTemplateItem()
{
   m_Name = "unnamed";
   m_Path = "";
   m_hIcon = NULL;
}

CEAFTemplateItem::CEAFTemplateItem(LPCTSTR name,LPCTSTR path,HICON hIcon)
{
   m_Name = name;
   m_Path = path;
   m_hIcon = hIcon;
}

CEAFTemplateItem::~CEAFTemplateItem()
{
}

void CEAFTemplateItem::SetName(LPCTSTR name)
{
   m_Name = name;
}

CString CEAFTemplateItem::GetName() const
{
   return m_Name;
}

void CEAFTemplateItem::SetTemplateFilePath(LPCTSTR path)
{
   m_Path = path;
}

CString CEAFTemplateItem::GetTemplateFilePath() const
{
   return m_Path;
}

void CEAFTemplateItem::SetIcon(HICON hIcon)
{
   m_hIcon = hIcon;
}

HICON CEAFTemplateItem::GetIcon() const
{
   return m_hIcon;
}

/////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CEAFTemplateGroup,CObject)

CEAFTemplateGroup::CEAFTemplateGroup(CEAFDocTemplate* pDocTemplate)
{
   m_pDocTemplate = pDocTemplate;
}

CEAFTemplateGroup::~CEAFTemplateGroup()
{
   Clear();
}

void CEAFTemplateGroup::Clear()
{
   std::vector<const CEAFTemplateItem*>::iterator itemIter;
   for ( itemIter = m_Items.begin(); itemIter != m_Items.end(); itemIter++ )
   {
      delete *itemIter;
   }
   m_Items.clear();

   std::vector<const CEAFTemplateGroup*>::iterator groupIter;
   for ( groupIter = m_Groups.begin(); groupIter != m_Groups.end(); groupIter++ )
   {
      delete *groupIter;
   }
   m_Groups.clear();
}

CEAFDocTemplate* CEAFTemplateGroup::GetDocTemplate()
{
   return m_pDocTemplate;
}

void CEAFTemplateGroup::SetGroupName(LPCTSTR name)
{
   m_GroupName = name;
}

CString CEAFTemplateGroup::GetGroupName() const
{
   return m_GroupName;
}

void CEAFTemplateGroup::AddGroup(const CEAFTemplateGroup* group)
{
   m_Groups.push_back(group);
}

CollectionIndexType CEAFTemplateGroup::GetGroupCount() const
{
   return (CollectionIndexType)m_Groups.size();
}

const CEAFTemplateGroup* CEAFTemplateGroup::GetGroup(CollectionIndexType grpIdx) const
{
   return m_Groups[grpIdx];
}

void CEAFTemplateGroup::AddItem(const CEAFTemplateItem* pItem)
{
   m_Items.push_back(pItem);
}

CollectionIndexType CEAFTemplateGroup::GetItemCount() const
{
   return (CollectionIndexType)m_Items.size();
}

const CEAFTemplateItem* CEAFTemplateGroup::GetItem(CollectionIndexType itemIdx) const
{
   return m_Items[itemIdx];
}

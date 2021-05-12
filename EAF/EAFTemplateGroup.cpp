///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CEAFTemplateItem,CObject)

CEAFTemplateItem::CEAFTemplateItem()
{
   m_pDocTemplate = nullptr;
   m_Name = "unnamed";
   m_Path = "";
   m_hIcon = nullptr;
}

CEAFTemplateItem::CEAFTemplateItem(CEAFDocTemplate* pDocTemplate,LPCTSTR name,LPCTSTR path,HICON hIcon)
{
   m_pDocTemplate = pDocTemplate;
   m_Name = name;
   m_Path = path;
   m_hIcon = hIcon;
}

CEAFTemplateItem::~CEAFTemplateItem()
{
}

CEAFTemplateItem* CEAFTemplateItem::Clone() const
{
   return new CEAFTemplateItem(m_pDocTemplate,m_Name,m_Path,m_hIcon);
}

void CEAFTemplateItem::SetDocTemplate(CEAFDocTemplate* pDocTemplate)
{
   m_pDocTemplate = pDocTemplate;
}

CEAFDocTemplate* CEAFTemplateItem::GetDocTemplate() const
{
   return m_pDocTemplate;
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

CEAFTemplateGroup::CEAFTemplateGroup()
{
   m_hIcon = nullptr;
}

CEAFTemplateGroup::~CEAFTemplateGroup()
{
   Clear();
}

CEAFTemplateGroup* CEAFTemplateGroup::Clone() const
{
   CEAFTemplateGroup* pGroup = new CEAFTemplateGroup;
   pGroup->DeepCopy(this);
   return pGroup;
}

CollectionIndexType CEAFTemplateGroup::GetTemplateCount() const
{
   return DeepCount(this);
}

CollectionIndexType CEAFTemplateGroup::DeepCount(const CEAFTemplateGroup* pGroup) const
{
   CollectionIndexType nTemplates = 0;
   for (const auto* pSubgroup : pGroup->m_Groups)
   {
      nTemplates += DeepCount(pSubgroup);
   }

   nTemplates += pGroup->m_Items.size();
   return nTemplates;
}

void CEAFTemplateGroup::DeepCopy(const CEAFTemplateGroup* pGroup)
{
   m_GroupName = pGroup->m_GroupName;
   m_hIcon = pGroup->m_hIcon;

   std::vector<CEAFTemplateItem*>::const_iterator itemIter(pGroup->m_Items.begin());
   std::vector<CEAFTemplateItem*>::const_iterator itemIterEnd(pGroup->m_Items.end());
   for ( ; itemIter != itemIterEnd; itemIter++ )
   {
      CEAFTemplateItem* pItem = *itemIter;
      AddItem(pItem->Clone());
   }

   std::vector<CEAFTemplateGroup*>::const_iterator groupIter(pGroup->m_Groups.begin());
   std::vector<CEAFTemplateGroup*>::const_iterator groupIterEnd(pGroup->m_Groups.end());
   for ( ; groupIter != groupIterEnd; groupIter++ )
   {
      CEAFTemplateGroup* pTemplateGroup = *groupIter;
      AddGroup(pTemplateGroup->Clone());
   }
}

void CEAFTemplateGroup::Clear()
{
   std::vector<CEAFTemplateItem*>::iterator itemIter(m_Items.begin());
   std::vector<CEAFTemplateItem*>::iterator itemIterEnd(m_Items.end());
   for ( ; itemIter != itemIterEnd; itemIter++ )
   {
      delete *itemIter;
   }
   m_Items.clear();

   std::vector<CEAFTemplateGroup*>::iterator groupIter(m_Groups.begin());
   std::vector<CEAFTemplateGroup*>::iterator groupIterEnd(m_Groups.end());
   for ( ; groupIter != groupIterEnd; groupIter++ )
   {
      delete *groupIter;
   }
   m_Groups.clear();
}

void CEAFTemplateGroup::SetGroupName(LPCTSTR name)
{
   m_GroupName = name;
}

CString CEAFTemplateGroup::GetGroupName() const
{
   return m_GroupName;
}

void CEAFTemplateGroup::SetIcon(HICON hIcon)
{
   m_hIcon = hIcon;
}

HICON CEAFTemplateGroup::GetIcon() const
{
   return m_hIcon;
}

void CEAFTemplateGroup::AddGroup(CEAFTemplateGroup* group)
{
   m_Groups.push_back(group);
}

GroupIndexType CEAFTemplateGroup::GetGroupCount() const
{
   return (GroupIndexType)m_Groups.size();
}

const CEAFTemplateGroup* CEAFTemplateGroup::GetGroup(GroupIndexType grpIdx) const
{
   return m_Groups[grpIdx];
}

CEAFTemplateGroup* CEAFTemplateGroup::GetGroup(GroupIndexType grpIdx)
{
   return m_Groups[grpIdx];
}

const CEAFTemplateGroup* CEAFTemplateGroup::FindGroup(LPCTSTR lpszGroupName) const
{
   std::vector<CEAFTemplateGroup*>::const_iterator groupIter(m_Groups.begin());
   std::vector<CEAFTemplateGroup*>::const_iterator groupIterEnd(m_Groups.end());
   for ( ; groupIter != groupIterEnd; groupIter++ )
   {
      CEAFTemplateGroup* pGroup = *groupIter;
      if ( pGroup->GetGroupName() == lpszGroupName )
         return pGroup;

      GroupIndexType nGroups = pGroup->GetGroupCount();
      for ( GroupIndexType grpIdx = 0; grpIdx < nGroups; grpIdx++ )
      {
         CEAFTemplateGroup* pSubGroup = pGroup->GetGroup(grpIdx);
         if ( pSubGroup->FindGroup(lpszGroupName) != nullptr )
            return pSubGroup;
      }
   }

   return nullptr;
}

CEAFTemplateGroup* CEAFTemplateGroup::FindGroup(LPCTSTR lpszGroupName)
{
   std::vector<CEAFTemplateGroup*>::const_iterator groupIter(m_Groups.begin());
   std::vector<CEAFTemplateGroup*>::const_iterator groupIterEnd(m_Groups.end());
   for ( ; groupIter != groupIterEnd; groupIter++ )
   {
      CEAFTemplateGroup* pGroup = *groupIter;
      if ( pGroup->GetGroupName() == lpszGroupName )
         return pGroup;

      GroupIndexType nGroups = pGroup->GetGroupCount();
      for ( GroupIndexType grpIdx = 0; grpIdx < nGroups; grpIdx++ )
      {
         CEAFTemplateGroup* pSubGroup = pGroup->GetGroup(grpIdx);
         if ( pSubGroup->FindGroup(lpszGroupName) != nullptr )
            return pSubGroup;
      }
   }

   return nullptr;
}

void CEAFTemplateGroup::RemoveGroup(GroupIndexType grpIdx)
{
   CEAFTemplateGroup* pGroup = m_Groups[grpIdx];
   delete pGroup;
   m_Groups.erase(m_Groups.begin()+grpIdx);
}

void CEAFTemplateGroup::AddItem(CEAFTemplateItem* pItem)
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

CEAFTemplateItem* CEAFTemplateGroup::GetItem(CollectionIndexType itemIdx)
{
   return m_Items[itemIdx];
}

void CEAFTemplateGroup::RemoveItem(CollectionIndexType itemIdx)
{
   CEAFTemplateItem* pItem = m_Items[itemIdx];
   delete pItem;
   m_Items.erase(m_Items.begin()+itemIdx);
}

bool CEAFTemplateGroup::operator<(const CEAFTemplateGroup& other) const
{
   return m_GroupName < other.m_GroupName;
}

bool CEAFTemplateGroup::operator==(const CEAFTemplateGroup& other) const
{
   return m_GroupName == other.m_GroupName;
}

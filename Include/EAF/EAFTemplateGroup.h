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

#pragma once

#include <EAF\EAFExp.h>
#include <vector>

class CEAFDocTemplate;

// CEAFTemplateItem
//
// Represents a template for a new document. 
// Template items are shown in the right hand side of the New dialog.
class EAFCLASS CEAFTemplateItem : public CObject
{
public:
   CEAFTemplateItem();
   CEAFTemplateItem(LPCTSTR name,LPCTSTR path,HICON hIcon);
   virtual ~CEAFTemplateItem();

   // Set/Get the name (usually the filename)
   virtual void SetName(LPCTSTR name);
   virtual CString GetName() const;

   // Set/Get the icon to display
   virtual void SetIcon(HICON hIcon);
   virtual HICON GetIcon() const;

   // Set/Get the path to the template file that is used to create a new document
   virtual void SetTemplateFilePath(LPCTSTR path);
   virtual CString GetTemplateFilePath() const;

protected:
   CString m_Name;
   CString m_Path;
   HICON m_hIcon;

   DECLARE_DYNAMIC(CEAFTemplateItem)
};

// CEAFTemplateGroup
//
// Represents a group of templates for creating new documents
// Template groups are displayed on the left hand side of the New dialog
// Template groups are in a tree structure and can be any level group.
// Each level contains zero or more template items
class EAFCLASS CEAFTemplateGroup : public CObject
{
public:
   CEAFTemplateGroup(CEAFDocTemplate* pDocTemplate);
   virtual ~CEAFTemplateGroup();

   // Delete all template groups and template items
   void Clear();

   // Returns the document template for this group of documents
   CEAFDocTemplate* GetDocTemplate();

   // Get/Get the group name
   virtual void SetGroupName(LPCTSTR name);
   virtual CString GetGroupName() const;

   // Add a sub-group
   virtual void AddGroup(const CEAFTemplateGroup* pGroup);

   // Returns the group count
   virtual CollectionIndexType GetGroupCount() const;

   // Gets a sub-group by index
   virtual const CEAFTemplateGroup* GetGroup(CollectionIndexType grpIdx) const;

   // Adds an item to this group
   virtual void AddItem(const CEAFTemplateItem* pItem);

   // Returns the number of items in this group
   virtual CollectionIndexType GetItemCount() const;

   // Returns a template item by index
   virtual const CEAFTemplateItem* GetItem(CollectionIndexType itemIdx) const;

private:
   CEAFDocTemplate* m_pDocTemplate;
   CString m_GroupName;

   std::vector<const CEAFTemplateItem*> m_Items;
   std::vector<const CEAFTemplateGroup*> m_Groups;

   DECLARE_DYNAMIC(CEAFTemplateGroup)
};

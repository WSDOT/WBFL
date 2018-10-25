///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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
   CEAFTemplateItem(CEAFDocTemplate* pDocTemplate, // document template for creating the new document
                    LPCTSTR name,                  // name to be displayed in the new dialog
                    LPCTSTR path,                  // path to a template file (nullptr if not using a template file)
                    HICON hIcon);                  // handle to the icon to display in the new dialog

   virtual ~CEAFTemplateItem();

   // Copying must be done through the Clone method
   virtual CEAFTemplateItem* Clone() const;

   // Set/Get the document template
   virtual void SetDocTemplate(CEAFDocTemplate* pDocTemplate);
   virtual CEAFDocTemplate* GetDocTemplate() const;

   // Set/Get the name (usually the filename, this is what get displayed on the right side of the dialog)
   virtual void SetName(LPCTSTR name);
   virtual CString GetName() const;

   // Set/Get the icon to display
   virtual void SetIcon(HICON hIcon);
   virtual HICON GetIcon() const;

   // Set/Get the path to the template file that is used to create a new document
   virtual void SetTemplateFilePath(LPCTSTR path);
   virtual CString GetTemplateFilePath() const;

protected:
   CEAFDocTemplate* m_pDocTemplate;
   CString m_Path;
   CString m_Name;
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
   CEAFTemplateGroup();
   virtual ~CEAFTemplateGroup();

   // copying must be done through the Clone method
   virtual CEAFTemplateGroup* Clone() const;

   // Delete all template groups and template items
   void Clear();

   // Get/Get the group name. This name is displayed in the tree
   // on the left side of the New dialog
   void SetGroupName(LPCTSTR name);
   CString GetGroupName() const;

   void SetIcon(HICON hIcon);
   HICON GetIcon() const;

   // Add a sub-group. This container takes over ownership of the
   // pointer and will delete it.
   void AddGroup(CEAFTemplateGroup* pGroup);

   // Returns the group count
   GroupIndexType GetGroupCount() const;

   // Gets a sub-group by index
   const CEAFTemplateGroup* GetGroup(GroupIndexType grpIdx) const;
   CEAFTemplateGroup* GetGroup(GroupIndexType grpIdx);

   const CEAFTemplateGroup* FindGroup(LPCTSTR lpszGroupName) const;
   CEAFTemplateGroup* FindGroup(LPCTSTR lpszGroupName);

   void RemoveGroup(GroupIndexType grpIdx);

   // Adds an item to this group This container takes over ownership of the
   // pointer and will delete it.
   void AddItem(CEAFTemplateItem* pItem);

   // Returns the number of items in this group
   CollectionIndexType GetItemCount() const;

   // Returns a template item by index
   const CEAFTemplateItem* GetItem(CollectionIndexType itemIdx) const;
   CEAFTemplateItem* GetItem(CollectionIndexType itemIdx);

   void RemoveItem(CollectionIndexType itemIdx);

   // compares based on group name
   bool operator<(const CEAFTemplateGroup& other) const;
   bool operator==(const CEAFTemplateGroup& other) const;

   // returns the total number of templates summed from
   // this group, all sub groups, and all items
   CollectionIndexType GetTemplateCount() const;

protected:
   void DeepCopy(const CEAFTemplateGroup* pGroup);
   CollectionIndexType DeepCount(const CEAFTemplateGroup* pGroup) const;

private:
   CString m_GroupName;
   HICON m_hIcon;

   std::vector<CEAFTemplateItem*> m_Items;
   std::vector<CEAFTemplateGroup*> m_Groups;

   DECLARE_DYNAMIC(CEAFTemplateGroup)
};

///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

class EAFCLASS CEAFTemplateItem : public CObject
{
public:
   CEAFTemplateItem();
   CEAFTemplateItem(LPCTSTR name,LPCTSTR path,HICON hIcon);
   virtual ~CEAFTemplateItem();
   virtual void SetName(LPCTSTR name);
   virtual CString GetName() const;
   virtual void SetIcon(HICON hIcon);
   virtual HICON GetIcon() const;

   virtual void SetTemplateFilePath(LPCTSTR path);
   virtual CString GetTemplateFilePath() const;

protected:
   CString m_Name;
   CString m_Path;
   HICON m_hIcon;

   DECLARE_DYNAMIC(CEAFTemplateItem)
};

class EAFCLASS CEAFTemplateGroup : public CObject
{
public:
   CEAFTemplateGroup(CEAFDocTemplate* pDocTemplate);
   virtual ~CEAFTemplateGroup();

   void Clear();

   CEAFDocTemplate* GetDocTemplate();

   virtual void SetGroupName(LPCSTR name);
   virtual CString GetGroupName() const;

   virtual void AddGroup(const CEAFTemplateGroup* pGroup);
   virtual CollectionIndexType GetGroupCount() const;
   virtual const CEAFTemplateGroup* GetGroup(CollectionIndexType grpIdx) const;

   virtual void AddItem(const CEAFTemplateItem* pItem);
   virtual CollectionIndexType GetItemCount() const;
   virtual const CEAFTemplateItem* GetItem(CollectionIndexType itemIdx) const;

private:
   CEAFDocTemplate* m_pDocTemplate;
   CString m_GroupName;

   std::vector<const CEAFTemplateItem*> m_Items;
   std::vector<const CEAFTemplateGroup*> m_Groups;

   DECLARE_DYNAMIC(CEAFTemplateGroup)
};

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
#include <EAF\EAFTemplateGroup.h>

interface IEAFAppPlugin;
class CEAFDocument;

class EAFCLASS CEAFDocTemplate : public CMultiDocTemplate
{
public:
   CEAFDocTemplate(UINT nIDResource,
                   CRuntimeClass* pDocClass,
                   CRuntimeClass* pFrameClass,
                   CRuntimeClass* pViewClass,
                   HMENU hSharedMenu = NULL,
                   int maxViewCount = -1);
   virtual ~CEAFDocTemplate();

   virtual CDocument* OpenDocumentFile(LPCTSTR lpszPathName,BOOL bMakeVisible);

   virtual const CEAFTemplateGroup* GetTemplateGroup() const;
   virtual CString GetTemplateGroupItemDescription(const CEAFTemplateItem* pItem) const;
   void SetTemplateItem(const CEAFTemplateItem* pItem);

   // returns the maximum number of views that can be created for this template
   int GetMaxViewCount() const;

   // returns the runtime class of the view
   CRuntimeClass* GetViewClass();

   // Sets data that will available to the view class when created
   void SetViewCreationData(LPVOID pCreateData);
   LPVOID GetViewCreationData();

   // Returns the resource ID associated with this tempalte
   UINT GetResourceID() const;

   void SetPlugin(IEAFAppPlugin* pPlugin);
   void GetPlugin(IEAFAppPlugin** ppPlugin);

   DECLARE_DYNAMIC(CEAFDocTemplate)

protected:
   // weak reference to plugin that created this doc template
   IEAFAppPlugin* m_pPlugin;

   CEAFTemplateGroup m_TemplateGroup;

   const CEAFTemplateItem* m_pTemplateItem; // the selected template item from New Project dialog

   // Called by the framework from OpenDocumentFile when the actual document is to be
   // opened. Sub-classes can redefine what it means to open a document
   virtual BOOL DoOpenDocumentFile(LPCTSTR lpszPathName,BOOL bMakeVisible,CEAFDocument* pDocument,CFrameWnd* pFrame);

private:
   int m_MaxViewCount; // maximum number of views that can be displayed at
                       // one time. -1 = unlimited

   BOOL m_bSharedMenu; // if TRUE, a shared menu resource is used

   LPVOID m_pCreateData; // pointer to view creation data
};

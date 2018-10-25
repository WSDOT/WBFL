///////////////////////////////////////////////////////////////////////
// PGSuper - Prestressed Girder SUPERstructure Design and Analysis
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation, 
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but 
// distribution is AS IS, WITHOUT ANY WARRANTY; without even the implied 
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See 
// the Alternate Route Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source 
// License along with this program; if not, write to the Washington 
// State Department of Transportation, Bridge and Structures Office, 
// P.O. Box  47340, Olympia, WA 98503, USA or e-mail 
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#if !defined EAFDocTemplate_H_
#define EAFDocTemplate_H_
#pragma once

#include <EAF\EAFExp.h>

interface IEAFAppPlugin;

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

   int GetMaxViewCount() const;

   CRuntimeClass* GetViewClass();

   // weak reference to plugin that created this doc template
   IEAFAppPlugin* m_pPlugin;

   // After the frame window is created, the menu command handler needs to be initialized
   // and the agents need to be initialized. Since CMIDFrameWnd::InitialUpdateFrame is not
   // a virtual function, this is the only place we can inject our code into the start up
   // procedure after the frame window has been created.
   // This function will call CEAFBrokerDocument::InitAgents() to finish the 
   // inialization process.
   virtual void InitialUpdateFrame(CFrameWnd* pFrame,CDocument* pDoc,BOOL bMakeVisible=TRUE);

   DECLARE_DYNAMIC(CEAFDocTemplate)

private:
   int m_MaxViewCount; // maximum number of views that can be displayed at
                       // one time. -1 = unlimited

   BOOL m_bSharedMenu; // if TRUE, a shared menu resource is used
};

#endif // EAFDocTemplate_H_
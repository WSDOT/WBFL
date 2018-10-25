///////////////////////////////////////////////////////////////////////
// PGSuper - Prestressed Girder SUPERstructure Design and Analysis
// Copyright © 1999-2010  Washington State Department of Transportation
//                        Bridge and Structures Office
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

#include "StdAfx.h"
#include <EAF\EAFDocTemplate.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFDocProxyAgent.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEAFDocTemplate,CMultiDocTemplate)

CEAFDocTemplate::CEAFDocTemplate(UINT nIDResource,
                                 CRuntimeClass* pDocClass,
                                 CRuntimeClass* pFrameClass,
                                 CRuntimeClass* pViewClass,
                                 HMENU hSharedMenu,
                                 int maxViewCount) :
CMultiDocTemplate(nIDResource,pDocClass,pFrameClass,pViewClass)
{
   m_pPlugin = NULL;

   m_bSharedMenu = FALSE;
   if ( hSharedMenu != NULL )
   {
      m_bSharedMenu = TRUE;
      m_hMenuShared = hSharedMenu;
   }
   m_MaxViewCount = maxViewCount;
}

CEAFDocTemplate::~CEAFDocTemplate()
{
   if ( m_bSharedMenu )
   {
      // This prevents the base class virtual destructor from
      // destroying the menu resource (i.e. it checks to make
      // sure the handle isn't NULL)
      //
      // See MSKB Article ID: Q118435, "Sharing Menus Between MDI Child Windows"

      m_hMenuShared = NULL;
   }
}

int CEAFDocTemplate::GetMaxViewCount() const
{
   return m_MaxViewCount;
}

CRuntimeClass* CEAFDocTemplate::GetViewClass()
{
   return m_pViewClass;
}

void CEAFDocTemplate::InitialUpdateFrame(CFrameWnd* pFrame,CDocument* pDoc,BOOL bMakeVisible)
{
   // only do this special initialization for the first view
   int nViews = 0;
   POSITION pos = pDoc->GetFirstViewPosition();
   while(pos != NULL)
   {
      nViews++;
      pDoc->GetNextView(pos);
   }

   if ( 1 < nViews )
      return;

   if ( pDoc->IsKindOf( RUNTIME_CLASS(CEAFBrokerDocument) ) )
   {
      CEAFBrokerDocument* pMyDoc = (CEAFBrokerDocument*)pDoc;


      CEAFMainFrame* pMyFrame = (CEAFMainFrame*)AfxGetMainWnd();
      ASSERT(pMyFrame->IsKindOf(RUNTIME_CLASS(CEAFMainFrame)));
      ASSERT_VALID(pMyFrame);


      // init the doc proxy agent
      pMyDoc->m_pDocProxyAgent->SetDocument(pMyDoc);
      pMyDoc->m_pDocProxyAgent->SetMainFrame(pMyFrame);

      // finish the agent initialization
      pMyDoc->InitAgents();
   }

   CMultiDocTemplate::InitialUpdateFrame(pFrame,pDoc,bMakeVisible);
}

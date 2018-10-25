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

#include "stdafx.h"
#include <EAF\EAFUtilities.h>
#include <EAF\EAFBrokerDocument.h>

#include "ManagePluginsDlg.h"

EAFFUNC CEAFApp* EAFGetApp()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   return (CEAFApp*)AfxGetApp();
}

// Global function for getting the broker from the current document
HRESULT EAFGetBroker(IBroker** ppBroker)
{
   // let's try it the easy way first
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   CEAFDocument* pDoc = pFrame->GetDocument();

   if ( pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CEAFBrokerDocument)) )
   {
      CEAFBrokerDocument* pBrokerDoc = (CEAFBrokerDocument*)pDoc;
      return pBrokerDoc->GetBroker(ppBroker);
   }
   else
   {
      // looks like we have to do it the hard way
      CWinApp* pApp = EAFGetApp();
      CDocument* pDocument = NULL;
      bool bDone = false;
      POSITION doc_template_pos = pApp->GetFirstDocTemplatePosition();

      while ( doc_template_pos != NULL || !bDone )
      {
         CDocTemplate* pTemplate = pApp->GetNextDocTemplate(doc_template_pos);

         POSITION doc_pos = pTemplate->GetFirstDocPosition();
         while ( doc_pos != NULL )
         {
            pDocument = pTemplate->GetNextDoc(doc_pos);
            if ( pDocument )
            {
               bDone = true;
               break;
            }
         }
      }

      if ( pDocument->IsKindOf(RUNTIME_CLASS(CEAFBrokerDocument)) )
      {
         CEAFBrokerDocument* pBrokerDoc = (CEAFBrokerDocument*)pDocument;
         return pBrokerDoc->GetBroker(ppBroker);
      }
   }

   return E_FAIL;
}

std::vector<CEAFPluginState> EAFManagePlugins(LPCSTR lpszTitle,const CATID& catid,CWnd* pParent)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CManagePluginsDlg dlg(lpszTitle,catid,pParent);
   dlg.DoModal(); // this DoModal is correct... dialog takes care of its own data
   return dlg.m_PluginStates;
}

CEAFMainFrame* EAFGetMainFrame()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFMainFrame* pFrame = (CEAFMainFrame*)AfxGetMainWnd();
   ASSERT_KINDOF(CEAFMainFrame,pFrame);
   return pFrame;
}


bool operator<(REFIID a,REFIID b)
{
   /*
   typedef struct _GUID {
      unsigned long  Data1;
      unsigned short Data2;
      unsigned short Data3;
      unsigned char  Data4[8];} GUID;
    */

    if ( a.Data1 > b.Data1 )
       return false;
    if ( a.Data1 < b.Data1 )
       return true;

    if ( a.Data2 > b.Data2 )
       return false;
    if ( a.Data2 < b.Data2 )
       return true;

    if ( a.Data3 > b.Data3 )
       return false;
    if ( a.Data3 < b.Data3 )
       return true;

    for ( int i = 0; i < 8; i++ )
    {
       if ( a.Data4[i] > b.Data4[i] )
          return false;
       if ( a.Data4[i] < b.Data4[i] )
          return true;
    }

    return false;
}

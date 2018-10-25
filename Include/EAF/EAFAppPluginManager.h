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
#include <EAF\EAFPluginManager.h>
#include <EAF\EAFAppPlugin.h>

class EAFCLASS CEAFAppPluginManager : public CEAFPluginManager<IEAFAppPlugin,CEAFApp>
{
public:

   virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
   {
      std::vector<CComPtr<IEAFAppPlugin>>::iterator iter;
      for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
      {
         CComPtr<IEAFAppPlugin> plugin = *iter;
         CCmdTarget* pCmdTarget = plugin->GetCommandTarget();
         if ( pCmdTarget != NULL && pCmdTarget->OnCmdMsg(nID,nCode,pExtra,pHandlerInfo) )
            return TRUE;
      }

      return FALSE;
   }

   virtual BOOL RegisterDocTemplates(CWinApp* pApp)
   {
      std::vector<CComPtr<IEAFAppPlugin>>::iterator iter;
      for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
      {
         CComPtr<IEAFAppPlugin> plugin = *iter;
         CEAFDocTemplate* pDocTemplate = plugin->CreateDocTemplate();
         if ( pDocTemplate )
         {
            CComPtr<IEAFAppPlugin> p;
            pDocTemplate->GetPlugin(&p);
            if ( p == NULL )
               pDocTemplate->SetPlugin(plugin);

            pApp->AddDocTemplate( pDocTemplate );
         }
      }

      return TRUE;
   }
};


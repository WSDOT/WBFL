///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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
#include <EAF\EAFPluginManagerBase.h>
#include <EAF\EAFPlugin.h>

class EAFCLASS CEAFPluginManager : public CEAFPluginManagerBase<IEAFPlugin,CEAFPluginApp>
{
public:
   virtual void IntegrateWithUI(BOOL bIntegrate)
   {
      Plugins::iterator iter;
      for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
      {
         CComPtr<IEAFPlugin> plugin = iter->second;
         plugin->IntegrateWithUI(bIntegrate);
      }
   }

   virtual void LoadDocumentationMaps()
   {
      Plugins::iterator iter;
      for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
      {
         CComPtr<IEAFPlugin> plugin = iter->second;
         plugin->LoadDocumentationMap();
      }
   }

   virtual eafTypes::HelpResult GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID,CString& strURL)
   {
      Plugins::iterator iter;
      for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
      {
         CComPtr<IEAFPlugin> plugin = iter->second;
         if ( plugin->GetDocumentationSetName() == CString(lpszDocSetName) )
         {
            return plugin->GetDocumentLocation(lpszDocSetName,nHID,strURL);
         }
      }

      return eafTypes::hrDocSetNotFound;
   }
};


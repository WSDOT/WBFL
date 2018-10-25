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

// EAFPluginManager.h: interface for the CEAFPluginManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF\EAFExp.h>
#include <EAF\EAFSplashScreen.h>


#include <comcat.h>
#include <vector>

template <typename T,typename P>
class CEAFPluginManager
{
public:
	CEAFPluginManager()
   {
   }

	virtual ~CEAFPluginManager()
   {
   }

   virtual void SetParent(P* parent)
   {
      m_pParent = parent;
   }

   virtual BOOL AddPlugin(T* pPlugin)
   {
      if ( pPlugin == NULL )
         return FALSE;

      m_Plugins.push_back(pPlugin);
      return TRUE;
   }

	virtual BOOL LoadPlugins(const CATID& catid)
   {
      USES_CONVERSION;

      CComPtr<ICatRegister> pICatReg;

      HRESULT hr = pICatReg.CoCreateInstance(CLSID_StdComponentCategoriesMgr);

      if ( FAILED(hr) )
      {
         AfxMessageBox("Failed to create the component category manager");
         return FALSE;
      }

      CComPtr<ICatInformation> pICatInfo;
      pICatReg->QueryInterface(&pICatInfo);

      CComPtr<IEnumCLSID> pIEnumCLSID;

      const int nID = 1;
      CATID ID[nID];
      ID[0] = catid;

      pICatInfo->EnumClassesOfCategories(nID,ID,0,NULL,&pIEnumCLSID);

      // load plug-ins 5 at a time
      CLSID clsid[5]; 
      ULONG nFetched = 0;
      while ( SUCCEEDED(pIEnumCLSID->Next(5,clsid,&nFetched)) && 0 < nFetched)
      {
         for ( ULONG i = 0; i < nFetched; i++ )
         {
            CComPtr<T> plugin;
            plugin.CoCreateInstance(clsid[i]);

            if ( plugin == NULL )
            {
               LPOLESTR pszUserType;
               OleRegGetUserType(clsid[i],USERCLASSTYPE_SHORT,&pszUserType);
               CString strMsg;
               strMsg.Format("Failed to load %s plug in",OLE2A(pszUserType));
               AfxMessageBox(strMsg);
            }
            else
            {
               CString str = plugin->GetName();
               CString strMsg;
               strMsg.Format("Loading %s",str);
               CEAFSplashScreen::SetText(strMsg);

               m_Plugins.push_back(plugin);
            }
         }
      }

      return TRUE;
   }

   virtual BOOL InitPlugins()
   {
      std::vector<CComPtr<T>>::iterator iter;
      for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
      {
         CComPtr<T> plugin = *iter;
         CString str = plugin->GetName();
         CString strMsg;
         strMsg.Format("Initializing %s",str);
         CEAFSplashScreen::SetText(strMsg);

         if ( !plugin->Init(m_pParent) )
            return FALSE;
      }

      CEAFSplashScreen::SetText("");

      return TRUE;
   }

   virtual void UnloadPlugins()
   {
      std::vector<CComPtr<T>>::iterator iter;
      for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
      {
         CComPtr<T> plugin = *iter;
         plugin->Terminate();
      }
      m_Plugins.clear();
   }

   UINT GetPluginCount() const
   {
      return m_Plugins.size();
   }

   HRESULT GetPlugin(UINT idx,T** ppPlugin)
   {
      if ( m_Plugins.size() <= idx )
         return E_INVALIDARG;

      (*ppPlugin) = m_Plugins[idx];
      (*ppPlugin)->AddRef();
      return S_OK;
   }

protected:
   P* m_pParent;
   std::vector<CComPtr<T>> m_Plugins;
};


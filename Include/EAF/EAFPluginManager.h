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

// EAFPluginManager.h: interface for the CEAFPluginManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF\EAFExp.h>
#include <EAF\EAFSplashScreen.h>
#include <EAF\EAFAcceleratorTable.h>
#include <EAF\EAFUtilities.h>

#include <comcat.h>
#include <map>

bool operator<(REFIID a,REFIID b);

// Generic template class for managing plugins

template <typename T,typename P>
class CEAFPluginManager
{
public:
	CEAFPluginManager()
   {
      m_CATID = CLSID_NULL;
   }

	CEAFPluginManager(const CATID& catid)
   {
      m_CATID = catid;
   }

	virtual ~CEAFPluginManager()
   {
   }

   virtual void SetCATID(const CATID& catid)
   {
      m_CATID = catid;
   }

   virtual void SetParent(P* parent)
   {
      m_pParent = parent;
      m_PluginAcceleratorTable.Init(m_pParent->GetPluginCommandManager());
   }

   P* GetParent()
   {
      return m_pParent;
   }

   virtual CEAFAcceleratorTable* GetAcceleratorTable()
   {
      return &m_PluginAcceleratorTable;
   }

   virtual BOOL AddPlugin(const CLSID& clsid,T* pPlugin)
   {
      if ( pPlugin == NULL )
         return FALSE;

      std::pair<Plugins::iterator,bool> result = m_Plugins.insert(std::make_pair(clsid,pPlugin));
      if ( result.second == true )
      {
         // plugin added to container
         if ( !pPlugin->Init(m_pParent) )
         {
            // plugin did not initalize properly
            // remove from container
            m_Plugins.erase(result.first);
            return FALSE; // plug-in not added
         }
         return TRUE; // plug-in added successfullly
      }

      return FALSE; // plugin not added to container
   }

	virtual BOOL LoadPlugins(BOOL bAlwaysAttemptToLoad = FALSE)
   {
      USES_CONVERSION;

      CComPtr<ICatRegister> pICatReg;

      HRESULT hr = pICatReg.CoCreateInstance(CLSID_StdComponentCategoriesMgr);

      if ( FAILED(hr) )
      {
         AfxMessageBox(_T("Failed to create the component category manager"));
         return FALSE;
      }

      CComPtr<ICatInformation> pICatInfo;
      pICatReg->QueryInterface(&pICatInfo);

      CComPtr<IEnumCLSID> pIEnumCLSID;

      const int nID = 1;
      CATID ID[nID];
      ID[0] = m_CATID;

      pICatInfo->EnumClassesOfCategories(nID,ID,0,NULL,&pIEnumCLSID);

      CEAFApp* pApp = EAFGetApp();

      // load plug-ins 5 at a time
      CLSID clsid[5]; 
      ULONG nFetched = 0;
      while ( SUCCEEDED(pIEnumCLSID->Next(5,clsid,&nFetched)) && 0 < nFetched)
      {
         for ( ULONG i = 0; i < nFetched; i++ )
         {
            LPOLESTR pszCLSID;
            ::StringFromCLSID(clsid[i],&pszCLSID);
            CString strState = pApp->GetProfileString(_T("Plugins"),OLE2T(pszCLSID),_T("Enabled"));

            if ( bAlwaysAttemptToLoad || strState.CompareNoCase(_T("Enabled")) == 0 )
            {
               CComPtr<T> plugin;
               HRESULT hr = plugin.CoCreateInstance(clsid[i]);

               if ( plugin == NULL )
               {
                  if ( bAlwaysAttemptToLoad )
                  {
                     // failing is OK if we always attempt
                  }
                  else
                  {
                     LPOLESTR pszUserType;
                     OleRegGetUserType(clsid[i],USERCLASSTYPE_SHORT,&pszUserType);
                     CString strMsg;
                     strMsg.Format(_T("Failed to load %s plug in (%s).\nError code %d\n\nWould you like to disable this plug in?"),OLE2T(pszUserType),OLE2T(pszCLSID),hr);
                     if ( AfxMessageBox(strMsg,MB_YESNO | MB_ICONQUESTION) == IDYES )
                     {
                        pApp->WriteProfileString(_T("Plugins"),OLE2T(pszCLSID),_T("Disabled"));
                     }
                  }
               }
               else
               {
                  CString str = plugin->GetName();
                  CString strMsg;
                  strMsg.Format(_T("Loading %s"),str);
                  CEAFSplashScreen::SetText(strMsg);

                  m_Plugins.insert(std::make_pair(clsid[i],plugin));
               }

               ::CoTaskMemFree((void*)pszCLSID);
            }
         }
      }

      return TRUE;
   }

   virtual BOOL InitPlugins()
   {
      Plugins::iterator iter;
      for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
      {
         CComPtr<T> plugin = iter->second;
         CString str = plugin->GetName();
         CString strMsg;
         strMsg.Format(_T("Initializing %s"),str);
         CEAFSplashScreen::SetText(strMsg);

         if ( !plugin->Init(m_pParent) )
            return FALSE;
      }

      CEAFSplashScreen::SetText(_T(""));

      return TRUE;
   }

   virtual void UnloadPlugins()
   {
      Plugins::iterator iter;
      for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
      {
         CComPtr<T> plugin = iter->second;
         plugin->Terminate();
      }
      m_Plugins.clear();
   }

   virtual void RemovePlugin(const CLSID& clsid)
   {
      Plugins::iterator found = m_Plugins.find(clsid);
      if ( found != m_Plugins.end() )
      {
         // plug-in was found
         CComPtr<T> plugin = found->second; // hang on to it
         m_Plugins.erase(found); // erase if from the container

         plugin->Terminate(); // terminate the plugin
         plugin.Release(); // release it
      }
   }

   CollectionIndexType GetPluginCount() const
   {
      return m_Plugins.size();
   }

   HRESULT GetPlugin(const CLSID& clsid,T** ppPlugin)
   {
      Plugins::iterator found = m_Plugins.find(clsid);
      if ( found != m_Plugins.end() )
      {
         // plug-in was found
         (*ppPlugin) = found->second; // hang on to it
         (*ppPlugin)->AddRef();
         return S_OK;
      }

      return E_FAIL;
   }

   HRESULT GetPlugin(CollectionIndexType idx,T** ppPlugin)
   {
      if ( m_Plugins.size() <= idx )
         return E_INVALIDARG;

      Plugins::iterator iter = m_Plugins.begin();
      for ( CollectionIndexType i = 0; i < idx; i++ )
         iter++;

      (*ppPlugin) = iter->second;
      (*ppPlugin)->AddRef();
      return S_OK;
   }

   void ManagePlugins(LPCTSTR lpszTitle)
   {
      CWnd* pWnd = EAFGetMainFrame();
      EAFManagePlugins(lpszTitle,m_CATID,pWnd);
   }

protected:
   CATID m_CATID;
   P* m_pParent;
   typedef std::map<CLSID,CComPtr<T>> Plugins;
   Plugins m_Plugins;

   CEAFAcceleratorTable m_PluginAcceleratorTable;
};


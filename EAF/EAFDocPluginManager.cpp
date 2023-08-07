///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <EAF\EAFDocPluginManager.h>
#include <EAF\EAFPluginPersist.h>
#include <EAF\EAFDocument.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CEAFDocPluginManager::CEAFDocPluginManager()
{
   m_bSaveMissingPluginData = TRUE;
}

void CEAFDocPluginManager::SetSaveMissingPluginDataFlag(BOOL bSaveDataForMissingPlugins)
{
   m_bSaveMissingPluginData = bSaveDataForMissingPlugins;
}

BOOL CEAFDocPluginManager::GetSaveMissingPluginDataFlag()
{
   return m_bSaveMissingPluginData;
}

HRESULT CEAFDocPluginManager::SavePluginData(IStructuredSave* pStrSave)
{
   if ( m_Plugins.size() == 0 )
      return S_OK;

   pStrSave->BeginUnit(_T("Plugins"),1.0);

   for(auto [clsid,plugin] : m_Plugins)
   {
      CComQIPtr<IEAFPluginPersist> persist(plugin);
      if ( persist )
      {
         pStrSave->BeginUnit(_T("Plugin"),1.0);

         LPOLESTR bstrCLSID = 0;
         HRESULT hr = StringFromCLSID(clsid, &bstrCLSID);
         pStrSave->put_Property(_T("CLSID"),CComVariant(bstrCLSID));
         ::CoTaskMemFree(bstrCLSID);

         hr = persist->Save(pStrSave);
         if ( FAILED(hr) )
            return hr;

         pStrSave->EndUnit();
      }
   }

   if ( m_bSaveMissingPluginData )
   {
      std::ranges::for_each(m_MissingPluginData, [&pStrSave](auto& d) {pStrSave->SaveRawUnit(d.c_str()); });
   }

   pStrSave->EndUnit();

   return S_OK;
}

HRESULT CEAFDocPluginManager::LoadPluginData(IStructuredLoad* pStrLoad)
{
   USES_CONVERSION;

   HRESULT hr = pStrLoad->BeginUnit(_T("Plugins"));
   if ( FAILED(hr) )
      return S_OK; // it is ok if there isn't any plugins data

   // until we run out of "Plugin" units
   while ( SUCCEEDED(pStrLoad->BeginUnit(_T("Plugin"))) )
   {
      // get CLSID of the agent
      CComVariant varCLSID;
      varCLSID.vt = VT_BSTR;
      HRESULT hr = pStrLoad->get_Property(_T("CLSID"), &varCLSID);
      if ( FAILED(hr) )
         return hr;

      CLSID clsid;
      hr = ::CLSIDFromString(CComBSTR(varCLSID.bstrVal), &clsid);
      if ( FAILED(hr) )
         return hr;

      // get the agent
      Plugins::iterator found = m_Plugins.find(clsid);
      if ( found != m_Plugins.end() )
      {
         CComPtr<IEAFDocumentPlugin> plugin = (*found).second;
         CComQIPtr<IEAFPluginPersist> persist(plugin);
         if ( persist )
         {
            hr = persist->Load( pStrLoad );
            if ( FAILED(hr) )
               return hr;
         }
         else
         {
            // plugin previously saved data, but it isn't capable of loading it ???
         }
      }
      else
      {
         // plugin not found... 
         // this could be because it is a 3rd party plugin and it isn't installed
         // skip to the next "Plugin" unit
         CComBSTR bstrRawUnit;
         hr = pStrLoad->LoadRawUnit(&bstrRawUnit);
         if ( FAILED(hr) )
            return hr;

         m_MissingPluginData.push_back(OLE2T(bstrRawUnit));
      }

      pStrLoad->EndUnit(); // end of "Plugin" unit
   };

   pStrLoad->EndUnit(); // Plugins

   return S_OK;
}

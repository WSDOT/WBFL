///////////////////////////////////////////////////////////////////////
// Library - Framework for libraries
// Copyright © 1999-2014  Washington State Department of Transportation
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

// Library.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f Libraryps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "WBFLLibrary.h"

#include "WBFLLibrary_i.c"

#include <WBFLTools_i.c>
#include <WBFLUnitServer_i.c>

#include "LibraryMgr.h"
#include "LibraryViewer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_LibraryMgr, CLibraryMgr)
OBJECT_ENTRY(CLSID_LibraryViewer, CLibraryViewer)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WBFLLibrary);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
   HRESULT hr;
   HRESULT retval = S_OK;
    // registers object, typelib and all interfaces in typelib
    retval = _Module.RegisterServer(TRUE);

    // Create a component category for WBFL Library Managers

   // Create the standard COM Category Manager
   ICatRegister* pICatReg = NULL;
   hr = ::CoCreateInstance( CLSID_StdComponentCategoriesMgr,
                                    NULL,
                                    CLSCTX_ALL,
                                    IID_ICatRegister,
                                    (void**)&pICatReg );
   if ( FAILED(hr) )
      return hr;

   // Fill in CATEGORYINFO struct
   CATEGORYINFO CatInfo;
   CatInfo.catid = CATID_WBFLLibraryMgr;
   CatInfo.lcid = LOCALE_SYSTEM_DEFAULT;
   _tcscpy_s(CatInfo.szDescription,sizeof(CatInfo.szDescription),L"WBFL Library Manager");

   // Array of categories
   const int nID = 1;
   CATID ID[nID];
   ID[0] = CatInfo.catid;

   // Register the category
   hr = pICatReg->RegisterCategories(1,&CatInfo);
   pICatReg->Release();

   return retval;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
   HRESULT retval = S_OK;

   retval = _Module.UnregisterServer(TRUE);


   // Create the standard COM Category Manager
   ICatRegister* pICatReg = NULL;
   HRESULT hr = ::CoCreateInstance( CLSID_StdComponentCategoriesMgr,
                                    NULL,
                                    CLSCTX_ALL,
                                    IID_ICatRegister,
                                    (void**)&pICatReg );
   if ( FAILED(hr) )
      return hr;

   const int nID = 1;
   CATID ID[nID];
   ID[0] = CATID_WBFLLibraryMgr;

   ICatInformation* pICatInfo = NULL;
   hr = pICatReg->QueryInterface( IID_ICatInformation, (void**)&pICatInfo );

   IEnumCLSID* pIEnumCLSID = NULL;
   hr = pICatInfo->EnumClassesOfCategories( nID, ID, 0, NULL, &pIEnumCLSID );

   CLSID clsid;
   hr = pIEnumCLSID->Next(1,&clsid,NULL);
   pICatReg->UnRegisterCategories(nID,ID);

   pIEnumCLSID->Release();
   pICatInfo->Release();
   pICatReg->Release();
   
   return retval;
}



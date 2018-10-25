// BridgeGeometryAgent.cpp : Implementation of DLL Exports.


#include "stdafx.h"
#include "resource.h"
#include "WBFLBridgeGeometryAgent.h"
#include "dllmain.h"

#include <initguid.h>
#include <WBFLCore_i.c>

#include <WBFLTools.h>
#include <WBFLGeometry.h>
#include <WBFLCogo.h>
#include <WBFLCogo_i.c>

// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _AtlModule.GetLockCount()==0) ? S_OK : S_FALSE;
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

// THIS FUNCTION WAS CAUSING SOME PROBLEMS.
//
// Must compile with UNICODE for this function, but this caused MFC problems
// because the other DLL's aren't compiled with UNICODE. If this function is
// put back into the mix, be sure to go to BridgeLinkUltCol.def and put it
// back in the function exports as well

// DllInstall - Adds/Removes entries to the system registry per user
//              per machine.	
//STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
//{
//    HRESULT hr = E_FAIL;
//    static const wchar_t szUserSwitch[] = _T("user");
//
//    if (pszCmdLine != NULL)
//    {
//    	if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
//    	{
//    		AtlSetPerUserRegistration(true);
//    	}
//    }
//
//    if (bInstall)
//    {	
//    	hr = DllRegisterServer();
//    	if (FAILED(hr))
//    	{	
//    		DllUnregisterServer();
//    	}
//    }
//    else
//    {
//    	hr = DllUnregisterServer();
//    }
//
//    return hr;
//}



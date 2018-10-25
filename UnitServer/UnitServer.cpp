///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2010  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// ActiveUnits.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f ActiveUnitsps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "WbflUnitServer.h"

#include "WbflUnitServer_i.c"

#include "UnitServerImp.h"
#include "UnitModeController.h"
#include "DisplayUnitFormatter.h"
#include "AnnotatedDisplayUnitFormatter.h"
#include "UnitSystem.h"
#include "AppUnitSystem.h"
#include "DocUnitSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_UnitSystem, CUnitSystem)
	OBJECT_ENTRY(CLSID_UnitServer, CUnitServerImp)
	OBJECT_ENTRY(CLSID_UnitModeController, CUnitModeController)
	OBJECT_ENTRY(CLSID_DisplayUnitFormatter, CDisplayUnitFormatter)
	OBJECT_ENTRY(CLSID_AnnotatedDisplayUnitFormatter, CAnnotatedDisplayUnitFormatter)
	OBJECT_ENTRY(CLSID_AppUnitSystem, CAppUnitSystem)
	OBJECT_ENTRY(CLSID_DocUnitSystem, CDocUnitSystem)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance);
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
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer(TRUE);
	return S_OK;
}

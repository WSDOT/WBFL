///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

// EAF.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#include "BackDoor.h"
#include <WBFLUnitServer.h>

#include <initguid.h>
#include <EAF\EAFAppPlugin.h>
#include <EAF\EAFUIIntegration.h>
#include <EAF\EAFDisplayUnits.h>
#include <EAF\EAFStatusCenter.h>
#include <EAF\EAFViewController.h>
#include <IReportManager.h>
#include <IGraphManager.h>
#include <WBFLReportManagerAgent_i.c>
#include <WBFLGraphManagerAgent_i.c>

#include "EAFDocProxyAgent.h"

#include <WBFLCore_i.c>
#include <WBFLTools_i.c>
#include <WBFLUnitServer_i.c>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE EAFDLL = { FALSE, 0, 0, nullptr, nullptr };

HINSTANCE GetInstanceHandle()
{
   return EAFDLL.hModule;
}

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("EAF.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(EAFDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(EAFDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("EAF.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(EAFDLL);
	}
	return 1;   // ok
}

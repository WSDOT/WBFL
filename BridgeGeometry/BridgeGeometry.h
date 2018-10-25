// BridgeGeometry.h : main header file for the BridgeGeometry DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CBridgeGeometryApp
// See BridgeGeometry.cpp for the implementation of this class
//

class CBridgeGeometryApp : public CWinApp
{
public:
	CBridgeGeometryApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

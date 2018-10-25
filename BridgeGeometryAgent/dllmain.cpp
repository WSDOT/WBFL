// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include <WBFLBridgeGeometry.h>
#include "WBFLBridgeGeometryAgent.h"
#include "WBFLBridgeGeometryAgent_i.c"
#include "BridgeGeometryInterfaces.h"
#include "dllmain.h"
#include <EAF\EAFUIIntegration.h>

CBridgeGeometryAgentModule _AtlModule;

class CBridgeGeometryAgentApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CBridgeGeometryAgentApp, CWinApp)
END_MESSAGE_MAP()

CBridgeGeometryAgentApp theApp;

BOOL CBridgeGeometryAgentApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CBridgeGeometryAgentApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}

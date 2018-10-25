// BridgeGeometryTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _MIDL_USE_GUIDDEF_
#include <WBFLBridgeGeometry_i.c>
#include <WBFLCogo_i.c>
#include <WBFLGeometry_i.c>
#include <WBFLTools_i.c>

#include "TestBridge.h"

int _tmain(int argc, _TCHAR* argv[])
{
   ::CoInitialize(NULL);

   CTestBridge::Test();

   ::CoUninitialize();

	return 1;
}


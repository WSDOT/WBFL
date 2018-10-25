// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

#include <WBFLAtlExt.h>

using namespace ATL;

#include "BridgeGeometryHelper.h"
#include <MathEx.h>

#if defined _DEBUG
#define ASSERTVALID AssertValid()
#else
#define ASSERTVALID
#endif
///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
// pch.h
//
// This is the MSTest replacement for the legacy COGO\CogoTest console-app
// suite (see F:\ARP\WBFL\COGO\CogoTest). It talks to WBFLCogo.dll ONLY
// through the generated COM headers + CoCreateInstance/CComPtr - never
// through Cogo's own ATL implementation headers - matching how CogoTest
// itself exercised the library.

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h> // IObjectSafety / INTERFACESAFE_FOR_UNTRUSTED_* (see CogoTestUtil.cpp's TestIObjectSafety)

#include "CppUnitTest.h"

#include <WBFLTools.h>
#include <WBFLGeometry.h>
#include <WBFLCogo.h>
#include <WBFLCogo\CogoHelpers.h>
#include <CoordGeom/COGO.h>

#include <MathEx.h>

#include <array>
#include <vector>
#include <tuple>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "CogoTestUtil.h"

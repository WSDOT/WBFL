///////////////////////////////////////////////////////////////////////
// ToolsStorage - Test driver for WBFLTools library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// PCompositeShape.cpp : Implementation of CPCompositeShape
#include "stdafx.h"
#if defined _DEBUG
#if defined VBA_BUILD
#if defined _WIN64
#include "x64\VBA_Debug\StorageTest.h"
#else
#include "Win32\VBA_Debug\StorageTest.h"
#endif
#else
#if defined _WIN64
#include "x64\Debug\StorageTest.h"
#else
#include "Win32\Debug\StorageTest.h"
#endif
#endif
#else
#if defined VBA_BUILD
#if defined _WIN64
#include "x64\VBA_Release\StorageTest.h"
#else
#include "Win32\VBA_Release\StorageTest.h"
#endif
#else
#if defined _WIN64
#include "x64\Release\StorageTest.h"
#else
#include "Win32\Release\StorageTest.h"
#endif
#endif
#endif

#include "PCompositeShape.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCompositeShape

STDMETHODIMP CPCompositeShape::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPCompositeShape
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

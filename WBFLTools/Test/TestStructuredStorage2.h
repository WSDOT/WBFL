///////////////////////////////////////////////////////////////////////
// Tools Test - Test driver for WBFLTools library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// TestStructuredStorage2.h: interface for the CTestStructuredStorage2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSTRUCTUREDSTORAGE2_H__2D3A33C2_5507_11D5_B003_00105A9AF985__INCLUDED_)
#define AFX_TESTSTRUCTUREDSTORAGE2_H__2D3A33C2_5507_11D5_B003_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined _DEBUG
#if defined VBA_BUILD
#if defined _WIN64
#include "StorageTest\x64\VBA_Debug\StorageTest.h"
#else
#include "StorageTest\Win32\VBA_Debug\StorageTest.h"
#endif
#else
#if defined _WIN64
#include "StorageTest\x64\Debug\StorageTest.h"
#else
#include "StorageTest\Win32\Debug\StorageTest.h"
#endif
#endif
#else
#if defined VBA_BUILD
#if defined _WIN64
#include "StorageTest\x64\VBA_Release\StorageTest.h"
#else
#include "StorageTest\Win32\VBA_Release\StorageTest.h"
#endif
#else
#if defined _WIN64
#include "StorageTest\x64\Release\StorageTest.h"
#else
#include "StorageTest\Win32\Release\StorageTest.h"
#endif
#endif
#endif

#include <vector>

class CTestStructuredStorage2  
{
public:
	static void Test();
	CTestStructuredStorage2();
	virtual ~CTestStructuredStorage2();

private:
   // data members
   CComVariant m_BSTR;
   CComVariant m_Float64;
   CComVariant m_Float;
   CComVariant m_BOOL;
   CComVariant m_Short;
   CComVariant m_Long;
   CComVariant m_ULong;
   CComVariant m_UShort;
   using ShapePtr = CComPtr<IPShape>;
   using ShapeContainer = std::vector<ShapePtr>;
   using ShapeIterator = ShapeContainer::iterator;
   ShapeContainer m_TestShapes;

   // methods
	HRESULT LoadMe(IStructuredLoad2* pLoad);
	HRESULT SaveMe(IStructuredSave2* pSave);
	HRESULT LoadPartial(IStructuredLoad2* pLoad);

   void Initialize();

};

#endif // !defined(AFX_TESTSTRUCTUREDSTORAGE2_H__2D3A33C2_5507_11D5_B003_00105A9AF985__INCLUDED_)

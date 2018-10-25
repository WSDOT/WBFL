///////////////////////////////////////////////////////////////////////
// Tools Test - Test driver for WBFLTools library
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

// TestStructuredStorage2.h: interface for the CTestStructuredStorage2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSTRUCTUREDSTORAGE2_H__2D3A33C2_5507_11D5_B003_00105A9AF985__INCLUDED_)
#define AFX_TESTSTRUCTUREDSTORAGE2_H__2D3A33C2_5507_11D5_B003_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined _DEBUG
#include "StorageTest\Debug\StorageTest.h"
#else
#include "StorageTest\Release\StorageTest.h"
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
   typedef CComPtr<IPShape> ShapePtr;
   typedef std::vector<ShapePtr> ShapeContainer;
   typedef ShapeContainer::iterator ShapeIterator;
   ShapeContainer m_TestShapes;

   // methods
	HRESULT LoadMe(IStructuredLoad2* pLoad);
	HRESULT SaveMe(IStructuredSave2* pSave);
	HRESULT LoadPartial(IStructuredLoad2* pLoad);

   void Initialize();

};

#endif // !defined(AFX_TESTSTRUCTUREDSTORAGE2_H__2D3A33C2_5507_11D5_B003_00105A9AF985__INCLUDED_)

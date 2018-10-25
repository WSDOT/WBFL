///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2018  Washington State Department of Transportation
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

// TestPoint3d.h: interface for the CTestPoint3d class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPOINT3D_H__6FECF103_B6A3_11D3_8CDF_C9DF305B3C59__INCLUDED_)
#define AFX_TESTPOINT3D_H__6FECF103_B6A3_11D3_8CDF_C9DF305B3C59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CTestPoint3d  :
   public CComObjectRootEx<CComSingleThreadModel>,
   public IPoint3dEvents
{
public:
	static void Test();
	CTestPoint3d();
	virtual ~CTestPoint3d();

   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestPoint3d)
   COM_INTERFACE_ENTRY(IPoint3dEvents)
END_COM_MAP()

// IPoint3dEvents
public:
	STDMETHOD(OnPointChanged)(IPoint3d* point);

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }

	static void TestISupportErrorInfo();
};

#endif // !defined(AFX_TESTPOINT3D_H__6FECF103_B6A3_11D3_8CDF_C9DF305B3C59__INCLUDED_)

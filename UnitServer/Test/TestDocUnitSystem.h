///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
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

// TestDocUnitSystem.h: interface for the CTestDocUnitSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTDOCUNITSYSTEM_H__16683EE9_558C_11D4_8CE4_0080C7380027__INCLUDED_)
#define AFX_TESTDOCUNITSYSTEM_H__16683EE9_558C_11D4_8CE4_0080C7380027__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ATL_NO_VTABLE CTestDocUnitSystem : 
   public CComObjectRootEx<CComSingleThreadModel>,
   public IDocUnitSystemEvents
{
public:
   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }
	static void Test();
	CTestDocUnitSystem();
	virtual ~CTestDocUnitSystem();


BEGIN_COM_MAP(CTestDocUnitSystem)
   COM_INTERFACE_ENTRY(IDocUnitSystemEvents)
END_COM_MAP()

// IDocUnitSystemEvents
public:
   STDMETHOD(OnUpdateDisplay)();

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }

   static void ConfigureDisplayUnits(IDisplayUnitMgr2* pDUM);
   static void MoreTests();
};

#endif // !defined(AFX_TESTDOCUNITSYSTEM_H__16683EE9_558C_11D4_8CE4_0080C7380027__INCLUDED_)

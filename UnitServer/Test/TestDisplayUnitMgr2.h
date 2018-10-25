///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// TestDisplayUnitMgr2.h: interface for the CTestDisplayUnitMgr2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTDISPLAYUNITMGR2_H__51F0A2CD_CAC1_11D3_8CE1_A85CC0A0E770__INCLUDED_)
#define AFX_TESTDISPLAYUNITMGR2_H__51F0A2CD_CAC1_11D3_8CE1_A85CC0A0E770__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ATL_NO_VTABLE CTestDisplayUnitMgr2 : 
   public CComObjectRootEx<CComSingleThreadModel>,
   public IDisplayUnitMgrEvents
{
public:
   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }
	static void Test();

   CTestDisplayUnitMgr2();
	virtual ~CTestDisplayUnitMgr2();

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }

BEGIN_COM_MAP(CTestDisplayUnitMgr2)
   COM_INTERFACE_ENTRY(IDisplayUnitMgrEvents)
END_COM_MAP()

// IDisplayUnitMgrEvents
public:
   STDMETHOD(OnFormatChanged)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit* displayUnit);
   STDMETHOD(OnDisplayUnitCreated)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit* displayUnit);
   STDMETHOD(OnDisplayUnitRemoved)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/BSTR displayUnit);
   STDMETHOD(OnDisplayUnitGroupCleared)(/*[in]*/ IDisplayUnitGroup* group);
   STDMETHOD(OnDisplayUnitGroupCreated)(/*[in]*/ IDisplayUnitGroup* group);
   STDMETHOD(OnDisplayUnitGroupRemoved)(/*[in]*/ BSTR group);
   STDMETHOD(OnDisplayUnitGroupsCleared)();
};

#endif // !defined(AFX_TESTDISPLAYUNITMGR2_H__51F0A2CD_CAC1_11D3_8CE1_A85CC0A0E770__INCLUDED_)

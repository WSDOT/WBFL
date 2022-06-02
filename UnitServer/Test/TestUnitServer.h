///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// TestUnitServer.h: interface for the CTestUnitServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTUNITSERVER_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)
#define AFX_TESTUNITSERVER_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ATL_NO_VTABLE CTestUnitServer : 
   public CComObjectRootEx<CComSingleThreadModel>,
   public IUnitServerEvents
{
public:
   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }
	static void Test();

   CTestUnitServer();
	virtual ~CTestUnitServer();


BEGIN_COM_MAP(CTestUnitServer)
   COM_INTERFACE_ENTRY(IUnitServerEvents)
END_COM_MAP()

// IUnitServerEvents
public:
   STDMETHOD(OnUnitAdded)(/*[in]*/IUnitType* unitType,/*[in]*/IUnit* unit);
	STDMETHOD(OnUnitRemoved)(/*[in]*/IUnitType* unitType,/*[in]*/BSTR unit);
	STDMETHOD(OnUnitsCleared)(/*[in]*/IUnitType* unitType);
	STDMETHOD(OnUnitTypeAdded)(/*[in]*/IUnitType* unitType);
	STDMETHOD(OnUnitTypeRemoved)(/*[in]*/BSTR unitType);
	STDMETHOD(OnUnitTypesCleared)();

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }
};

#endif // !defined(AFX_TESTUNITSERVER_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)

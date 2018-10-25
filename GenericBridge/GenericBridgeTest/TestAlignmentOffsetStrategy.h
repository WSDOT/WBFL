///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
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

// TestAlignmentOffsetStrategy.h: interface for the CTestAlignmentOffsetStrategy class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_TESTALIGNMENTOFFSETSTRATEGY_H_
#define INCLUDED_TESTALIGNMENTOFFSETSTRATEGY_H_

class ATL_NO_VTABLE CTestAlignmentOffsetStrategy :
   public CComObjectRootEx<CComSingleThreadModel>,
   public IOverhangPathStrategyEvents
{
public:
	static void Test();
	CTestAlignmentOffsetStrategy();
	virtual ~CTestAlignmentOffsetStrategy();

   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestAlignmentOffsetStrategy)
   COM_INTERFACE_ENTRY(IOverhangPathStrategyEvents)
END_COM_MAP()

// IOverhangPathStrategyEvents
public:
   STDMETHOD(OnStrategyChanged)();

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }
};

#endif // INCLUDED_TESTALIGNMENTOFFSETSTRATEGY_H_

///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// TestSpanCollection.h: interface for the CTestSpanCollection class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_TESTSPANCOLLECTION_H_
#define INCLUDED_TESTSPANCOLLECTION_H_

class ATL_NO_VTABLE CTestSpanCollection :
   public CComObjectRootEx<CComSingleThreadModel>,
   public ISpanCollectionEvents
{
public:
	static void Test();
	CTestSpanCollection();
	virtual ~CTestSpanCollection();

   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestSpanCollection)
   COM_INTERFACE_ENTRY(ISpanCollectionEvents)
END_COM_MAP()

// ISpanCollectionEvents
public:
   STDMETHOD(OnSpanChanged)(ISpan* Span);

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }
};

#endif // INCLUDED_TESTSPANCOLLECTION_H_

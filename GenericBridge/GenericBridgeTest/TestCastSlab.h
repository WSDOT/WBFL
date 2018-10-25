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

// TestCastSlab.h: interface for the CTestCastSlab class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_TESTCASTSLAB_H_
#define INCLUDED_TESTCASTSLAB_H_

class ATL_NO_VTABLE CTestCastSlab :
   public CComObjectRootEx<CComSingleThreadModel>,
   public IBridgeDeckEvents
{
public:
	static void Test();
	CTestCastSlab();
	virtual ~CTestCastSlab();

   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestCastSlab)
   COM_INTERFACE_ENTRY(IBridgeDeckEvents)
END_COM_MAP()

// IBridgeDeckEvents
public:
   STDMETHOD(OnBridgeDeckChanged)(IBridgeDeck* deck);

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }
};

#endif // INCLUDED_TESTCASTSLAB_H_

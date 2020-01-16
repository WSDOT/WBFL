///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// TestLineSegment2d.h: interface for the CTestLineSegment2d class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTLINESEGMENT2D_H__5B12E407_AF9C_11D3_8CDF_FF25C5D0C656__INCLUDED_)
#define AFX_TESTLINESEGMENT2D_H__5B12E407_AF9C_11D3_8CDF_FF25C5D0C656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ATL_NO_VTABLE CTestLineSegment2d :
   public CComObjectRootEx<CComSingleThreadModel>,
   public ILineSegment2dEvents
{
public:
   CTestLineSegment2d();

   static void Test();

   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestLineSegment2d)
   COM_INTERFACE_ENTRY(ILineSegment2dEvents)
END_COM_MAP()

// ILineSegment2dEvents
public:
	STDMETHOD(OnLineSegmentChanged)(ILineSegment2d* lineSegment);

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }
	static void TestISupportErrorInfo();
};

#endif // !defined(AFX_TESTLINESEGMENT2D_H__5B12E407_AF9C_11D3_8CDF_FF25C5D0C656__INCLUDED_)

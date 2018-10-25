///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// TestPoint2dCollection.h: interface for the CTestPoint2dCollection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPOINT2DCOLLECTION_H__5B12E405_AF9C_11D3_8CDF_FF25C5D0C656__INCLUDED_)
#define AFX_TESTPOINT2DCOLLECTION_H__5B12E405_AF9C_11D3_8CDF_FF25C5D0C656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestPoint2dCollection  :
   public CComObjectRootEx<CComSingleThreadModel>,
   public IPoint2dCollectionEvents
{
public:
	static void Test();
	CTestPoint2dCollection();
	virtual ~CTestPoint2dCollection();

   void InitEventTest(CollectionIndexType expectedIndex) { m_expectedIndex = expectedIndex; m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestPoint2dCollection)
   COM_INTERFACE_ENTRY(IPoint2dCollectionEvents)
END_COM_MAP()

// IPoint2dCollectionEvents
public:
	STDMETHOD(OnPointChanged)(IPoint2d* point);
	STDMETHOD(OnPointAdded)(CollectionIndexType index,IPoint2d* point);
	STDMETHOD(OnPointRemoved)(CollectionIndexType index);
	STDMETHOD(OnPointsCleared)();

private:
   bool m_bTestState;
   CollectionIndexType m_expectedIndex;
   void Pass() { m_bTestState = true; }

private:
	static void TestISupportErrorInfo();
};

#endif // !defined(AFX_TESTPOINT2DCOLLECTION_H__5B12E405_AF9C_11D3_8CDF_FF25C5D0C656__INCLUDED_)

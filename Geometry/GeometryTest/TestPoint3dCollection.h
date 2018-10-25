///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// TestPoint3dCollection.h: interface for the CTestPoint3dCollection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPOINT3DCOLLECTION_H__19582347_B7D5_11D3_8A0B_006097C68A9C__INCLUDED_)
#define AFX_TESTPOINT3DCOLLECTION_H__19582347_B7D5_11D3_8A0B_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CTestPoint3dCollection  :
   public CComObjectRootEx<CComSingleThreadModel>,
   public IPoint3dCollectionEvents
{
public:
	static void Test();
	CTestPoint3dCollection();
	virtual ~CTestPoint3dCollection();

   void InitEventTest(CollectionIndexType expectedIndex) { m_expectedIndex = expectedIndex; m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestPoint3dCollection)
   COM_INTERFACE_ENTRY(IPoint3dCollectionEvents)
END_COM_MAP()

// IPointCollectionEvents
public:
	STDMETHOD(OnPointChanged)(IPoint3d* point);
	STDMETHOD(OnPointAdded)(CollectionIndexType index,IPoint3d* point);
	STDMETHOD(OnPointRemoved)(CollectionIndexType index);
	STDMETHOD(OnPointsCleared)();

private:
   bool m_bTestState;
   CollectionIndexType m_expectedIndex;
   void Pass() { m_bTestState = true; }

private:
	static void TestISupportErrorInfo();
};

#endif // !defined(AFX_TESTPOINT3DCOLLECTION_H__19582347_B7D5_11D3_8A0B_006097C68A9C__INCLUDED_)

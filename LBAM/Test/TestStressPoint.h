///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
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

// TestStressPoint.h: interface for the CTestStressPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSTRESSPOINT_H__0AD9D36E_69B4_11D5_B01F_00105A9AF985__INCLUDED_)
#define AFX_TESTSTRESSPOINT_H__0AD9D36E_69B4_11D5_B01F_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ATL_NO_VTABLE CTestStressPoint  :
public CComObjectRootEx<CComSingleThreadModel>,
public IStressPointEvents,
public IStressPointsEvents
{
public:
	static void Test();
	CTestStressPoint();
	virtual ~CTestStressPoint();

BEGIN_COM_MAP(CTestStressPoint)
   COM_INTERFACE_ENTRY(IStressPointEvents)
   COM_INTERFACE_ENTRY(IStressPointsEvents)
END_COM_MAP()

public:
// _IStressPointEvents
   STDMETHOD(OnStressPointChanged)(/*[in]*/IStressPoint* StressPoint);

// _IStressPointCollectionEvents
   STDMETHOD(OnStressPointsChanged)(/*[in]*/CollectionIndexType idx);
   STDMETHOD(OnStressPointsAdded)(/*[in]*/CollectionIndexType idx);
   STDMETHOD(OnStressPointsRemoved)(/*[in]*/CollectionIndexType idx);

   bool m_spFired;
   CollectionIndexType m_spCollFired;

   DWORD m_SpCookie;   // cookies for connection points
   DWORD m_CollCookie;
};

#endif // !defined(AFX_TESTSTRESSPOINT_H__0AD9D36E_69B4_11D5_B01F_00105A9AF985__INCLUDED_)

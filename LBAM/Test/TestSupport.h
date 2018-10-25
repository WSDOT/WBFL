///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
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

// TestSupport.h: interface for the CTestSupport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSUPPORT_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTSUPPORT_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestSupport :
public CComObjectRootEx<CComSingleThreadModel>,
public ISupportEvents,
public ISupportsEvents
{
public:
	static void Test();

	CTestSupport();
	virtual ~CTestSupport();

BEGIN_COM_MAP(CTestSupport)
   COM_INTERFACE_ENTRY(ISupportEvents)
   COM_INTERFACE_ENTRY(ISupportsEvents)
END_COM_MAP()


public:
   STDMETHOD(OnSupportChanged)(/*[in]*/ISupport* Support, BSTR stage, ChangeType change);

   STDMETHOD(OnSupportsChanged)(/*[in]*/ISupport* Support, BSTR stage, ChangeType change);
   STDMETHOD(OnSupportsAdded)(ISupport* item, SupportIndexType idx);
   STDMETHOD(OnSupportsBeforeRemove)(ISupport* item, SupportIndexType idx);
	STDMETHOD(OnSupportsMoveTo)(SupportIndexType from, SupportIndexType to);
	STDMETHOD(OnSupportsCopyTo)(SupportIndexType from, SupportIndexType to);
	STDMETHOD(OnSupportsReverse)();

   HRESULT OnCreateSegment(ISupport* pseg)
   {return S_OK;}

   bool m_csStiffnessFired;
   bool m_csStressPointsFired;
   bool m_csDfFired;
   DWORD m_CsCookie;

   void InitEvents()
   {
      m_csStiffnessFired= false;
      m_csStressPointsFired= false;
      m_csDfFired= false;
   }

};

#endif // !defined(AFX_TESTSupport_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

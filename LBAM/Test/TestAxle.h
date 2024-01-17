///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// TestAxle.h: interface for the CTestAxle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTAxle_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTAxle_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestAxle :
public CComObjectRootEx<CComSingleThreadModel>,
public IAxleEvents,
public IAxlesEvents
{
public:
	static void Test();

	CTestAxle();
	virtual ~CTestAxle();

BEGIN_COM_MAP(CTestAxle)
   COM_INTERFACE_ENTRY(IAxleEvents)
   COM_INTERFACE_ENTRY(IAxlesEvents)
END_COM_MAP()

public:
   STDMETHOD(OnAxleChanged)(/*[in]*/IAxle* Axle);

   STDMETHOD(OnAxlesChanged)(/*[in]*/IAxle* Axle);
   STDMETHOD(OnAxlesAdded)(IAxle* item, AxleIndexType idx);
   STDMETHOD(OnAxlesBeforeRemove)(IAxle* item, AxleIndexType idx);
	STDMETHOD(OnAxlesMoveTo)(AxleIndexType from, AxleIndexType to);
	STDMETHOD(OnAxlesCopyTo)(AxleIndexType from, AxleIndexType to);
	STDMETHOD(OnAxlesReverse)();

   HRESULT OnCreateSegment(IAxle* pseg)
   {return S_OK;}


   bool m_csAxlesFired;
   bool m_csAxleFired;
   DWORD m_CsCookie;

};

#endif // !defined(AFX_TESTAxle_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

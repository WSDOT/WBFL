///////////////////////////////////////////////////////////////////////
// Loading Test - Test driver for Loading library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// TestPointLoad.h: interface for the CTestPointLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPointLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTPointLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

static _ATL_FUNC_INFO OnPointLoadChangedInfo     = { CC_STDCALL, VT_EMPTY, 1, {VT_DISPATCH} };

class CTestPointLoad :
public CComObjectRootEx<CComSingleThreadModel>,
public ldIPointLoadEvents,
public ldIPointLoadsEvents
{
public:
	static void Test();

	CTestPointLoad();
	virtual ~CTestPointLoad();

BEGIN_COM_MAP(CTestPointLoad)
  COM_INTERFACE_ENTRY(ldIPointLoadEvents)
  COM_INTERFACE_ENTRY(ldIPointLoadsEvents)
END_COM_MAP()


public:
   STDMETHOD(OnPointLoadChanged)(/*[in]*/ldIPointLoad* PointLoad);
   STDMETHOD(OnPointLoadChanged)(/*[in]*/ldIPointLoadItem* PointLoad);
   STDMETHOD(OnPointLoadAdded)(/*[in]*/ldIPointLoadItem* PointLoad);
   STDMETHOD(OnPointLoadRemoved)();

   bool m_csPointLoadFired;
   bool m_csDFFired;
   unsigned long m_CsCookie;

};

#endif // !defined(AFX_TESTPointLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

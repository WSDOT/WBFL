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

// TestPointLoad.h: interface for the CTestPointLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPointLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTPointLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestPointLoad :
public CComObjectRootEx<CComSingleThreadModel>,
public IPointLoadEvents,
public IPointLoadsEvents
{
public:
	static void Test();

	CTestPointLoad();
	virtual ~CTestPointLoad();

BEGIN_COM_MAP(CTestPointLoad)
  COM_INTERFACE_ENTRY(IPointLoadEvents)
  COM_INTERFACE_ENTRY(IPointLoadsEvents)
END_COM_MAP()

public:
   STDMETHOD(OnPointLoadChanged)(/*[in]*/IPointLoad* PointLoad);
   STDMETHOD(OnPointLoadsChanged)(/*[in]*/IPointLoadItem* PointLoad);
   STDMETHOD(OnPointLoadsAdded)(/*[in]*/IPointLoadItem* PointLoad);
   STDMETHOD(OnPointLoadsBeforeRemove)(/*[in]*/IPointLoadItem* PointLoad);

   bool m_csPointLoadFired;
   bool m_csDFFired;
   unsigned long m_CsCookie;

};

#endif // !defined(AFX_TESTPointLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

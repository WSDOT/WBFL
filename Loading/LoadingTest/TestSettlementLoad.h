///////////////////////////////////////////////////////////////////////
// Loading Test - Test driver for Loading library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// TestSettlementLoad.h: interface for the CTestSettlementLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSettlementLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTSettlementLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestSettlementLoad :
public CComObjectRootEx<CComSingleThreadModel>,
public ldISettlementLoadEvents,
public ldISettlementLoadsEvents
{
public:
	static void Test();

	CTestSettlementLoad();
	virtual ~CTestSettlementLoad();

BEGIN_COM_MAP(CTestSettlementLoad)
  COM_INTERFACE_ENTRY(ldISettlementLoadEvents)
  COM_INTERFACE_ENTRY(ldISettlementLoadsEvents)
END_COM_MAP()

public:
   STDMETHOD(OnSettlementLoadChanged)(/*[in]*/ldISettlementLoad* SettlementLoad);
   STDMETHOD(OnSettlementLoadsChanged)(/*[in]*/ldISettlementLoadItem* SettlementLoad);
   STDMETHOD(OnSettlementLoadsAdded)(/*[in]*/ldISettlementLoadItem* SettlementLoad);
   STDMETHOD(OnSettlementLoadsBeforeRemove)(/*[in]*/ldISettlementLoadItem* SettlementLoad);

   bool m_csSettlementLoadFired;
   bool m_csDFFired;
   unsigned long m_CsCookie;

};

#endif // !defined(AFX_TESTSettlementLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

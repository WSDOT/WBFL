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

// TestDistributedLoad.h: interface for the CTestDistributedLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTDistributedLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTDistributedLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestDistributedLoad :
public CComObjectRootEx<CComSingleThreadModel>,
public IDistributedLoadEvents,
public IDistributedLoadsEvents
{
public:
	static void Test();

	CTestDistributedLoad();
	virtual ~CTestDistributedLoad();

BEGIN_COM_MAP(CTestDistributedLoad)
   COM_INTERFACE_ENTRY(IDistributedLoadEvents)
   COM_INTERFACE_ENTRY(IDistributedLoadsEvents)
END_COM_MAP()

public:
   STDMETHOD(OnDistributedLoadChanged)(/*[in]*/IDistributedLoad* DistributedLoad);
   STDMETHOD(OnDistributedLoadsChanged)(/*[in]*/IDistributedLoadItem* DistributedLoad);
   STDMETHOD(OnDistributedLoadsAdded)(/*[in]*/IDistributedLoadItem* DistributedLoad);
   STDMETHOD(OnDistributedLoadsBeforeRemove)(/*[in]*/IDistributedLoadItem* DistributedLoad);

   bool m_csDistributedLoadFired;
   bool m_csDFFired;
   unsigned long m_CsCookie;

};

#endif // !defined(AFX_TESTDistributedLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

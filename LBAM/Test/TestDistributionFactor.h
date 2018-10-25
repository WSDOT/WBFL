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

// TestDistributionFactor.h: interface for the CTestDistributionFactor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTDISTRIBUTIONFACTOR_H__0AD9D36E_69B4_11D5_B01F_00105A9AF985__INCLUDED_)
#define AFX_TESTDISTRIBUTIONFACTOR_H__0AD9D36E_69B4_11D5_B01F_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ATL_NO_VTABLE CTestDistributionFactor  :
public CComObjectRootEx<CComSingleThreadModel>,
public IDistributionFactorEvents
{
public:
	static void Test();
   static void TestDfOnly();
   static void TestDfCollection();
	CTestDistributionFactor();
	virtual ~CTestDistributionFactor();

BEGIN_COM_MAP(CTestDistributionFactor)
   COM_INTERFACE_ENTRY(IDistributionFactorEvents)
END_COM_MAP()

public:
// _IDistributionFactorEvents
   STDMETHOD(OnDistributionFactorChanged)(/*[in]*/IDistributionFactor* DistributionFactor);

   bool m_Fired;
   unsigned long m_Cookie;   // cookies for connection points
};

#endif // !defined(AFX_TESTDistributionFactor_H__0AD9D36E_69B4_11D5_B01F_00105A9AF985__INCLUDED_)

///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner Test - Test driver for LBAM analysis library
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

// TestLoadCombiner.h: interface for the TestLoadCombiner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTLOADCOMBINER_H__0D3A1E9E_4612_4A70_B90E_98892D621FDA__INCLUDED_)
#define AFX_TESTLOADCOMBINER_H__0D3A1E9E_4612_4A70_B90E_98892D621FDA__INCLUDED_

#include "LcTestUtils.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TestLoadCombiner:
public CComObjectRootEx<CComSingleThreadModel>,
public ILoadCombinationAnalysisContextEvents
{

public:
	TestLoadCombiner();
	virtual ~TestLoadCombiner();

	static void Test();

BEGIN_COM_MAP(TestLoadCombiner)
   COM_INTERFACE_ENTRY(ILoadCombinationAnalysisContextEvents)
END_COM_MAP()

public:
   STDMETHOD(OnResultsChanged)();
   STDMETHOD(OnCombinationChanged)(ComboType scope, BSTR combination);

protected:
   void InitFired();
   bool m_csModelHosedFired;
   bool m_csCombinationChangedFired;
   unsigned long m_Cookie;
};

#endif // !defined(AFX_TestLoadCombiner_H__0D3A1E9E_4612_4A70_B90E_98892D621FDA__INCLUDED_)



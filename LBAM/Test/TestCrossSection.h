///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2018  Washington State Department of Transportation
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

// TestCrossSection.h: interface for the CTestCrossSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCROSSSECTION_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTCROSSSECTION_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestCrossSection :
public CComObjectRootEx<CComSingleThreadModel>,
public ISegmentCrossSectionEvents
{
public:
	static void Test();

	CTestCrossSection();
	virtual ~CTestCrossSection();

BEGIN_COM_MAP(CTestCrossSection)
   COM_INTERFACE_ENTRY(ISegmentCrossSectionEvents)
END_COM_MAP()


public:
   STDMETHOD(OnSegmentCrossSectionChanged)(/*[in]*/ISegmentCrossSection* CrossSection, ChangeType change);

   bool m_csStiffnessFired;
   bool m_csStressPointsFired;
   unsigned long m_CsCookie;

};

#endif // !defined(AFX_TESTCROSSSECTION_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

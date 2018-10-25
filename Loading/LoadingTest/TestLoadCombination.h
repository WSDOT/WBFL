///////////////////////////////////////////////////////////////////////
// Loading Test - Test driver for Loading library
// Copyright © 1999-2012  Washington State Department of Transportation
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

// TestLoadCombination.h: interface for the CTestLoadCombination class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTLoadCombination_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTLoadCombination_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestLoadCombination :
public CComObjectRootEx<CComSingleThreadModel>,
public ldILoadCombinationEvents,
public ldILoadCombinationsEvents
{
public:
	static void Test();

	CTestLoadCombination();
	virtual ~CTestLoadCombination();

BEGIN_COM_MAP(CTestLoadCombination)
   COM_INTERFACE_ENTRY(ldILoadCombinationEvents)
   COM_INTERFACE_ENTRY(ldILoadCombinationsEvents)
END_COM_MAP()


public:
   STDMETHOD(OnLoadCombinationChanged)(/*[in]*/ ldILoadCombination*  LoadCombination, ldLoadingChangeType change);
   STDMETHOD(OnLoadCombinationRenamed)(/*[in]*/ BSTR oldName, BSTR newName);

   STDMETHOD(OnLoadCombinationsChanged)(/*[in]*/ldILoadCombination* LoadCombination, ldLoadingChangeType change);
   STDMETHOD(OnLoadCombinationsRenamed)(/*[in]*/BSTR oldName, /*[in]*/BSTR newName);
   STDMETHOD(OnLoadCombinationsAdded)(/*[in]*/ldILoadCombination* load);
   STDMETHOD(OnLoadCombinationsBeforeRemove)(/*[in]*/ldILoadCombination* load);

   HRESULT OnCreateSegment(ldILoadCombination* pLoadCombination);

   long m_LastID;

   bool m_csLoadCombinationFired;
   bool m_csLoadCombinationsFired;
   unsigned long m_CsCookie;

};

#endif // !defined(AFX_TESTLoadCombination_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

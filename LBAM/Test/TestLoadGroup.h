///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// TestLoadGroup.h: interface for the CTestLoadGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTLoadGroup_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTLoadGroup_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestLoadGroup :
public CComObjectRootEx<CComSingleThreadModel>,
public ILoadGroupEvents,
public ILoadGroupsEvents
{
public:
	static void Test();

	CTestLoadGroup();
	virtual ~CTestLoadGroup();

BEGIN_COM_MAP(CTestLoadGroup)
   COM_INTERFACE_ENTRY(ILoadGroupEvents)
   COM_INTERFACE_ENTRY(ILoadGroupsEvents)
END_COM_MAP()

public:
   STDMETHOD(OnLoadGroupChanged)(/*[in]*/ ILoadGroup*  LoadGroup, ChangeType change);
   STDMETHOD(OnLoadGroupRenamed)(/*[in]*/ BSTR oldName, BSTR newName);

   STDMETHOD(OnLoadGroupsChanged)(/*[in]*/ILoadGroup* LoadGroup, ChangeType change);
   STDMETHOD(OnLoadGroupsRenamed)(/*[in]*/BSTR oldName, /*[in]*/BSTR newName);
   STDMETHOD(OnLoadGroupsAdded)(/*[in]*/ILoadGroup* load);
   STDMETHOD(OnLoadGroupsBeforeRemove)(/*[in]*/ILoadGroup* load);

   HRESULT OnCreateSegment(ILoadGroup* pLoadGroup);

   long m_LastID;

   bool m_csLoadGroupFired;
   bool m_csLoadGroupsFired;
   unsigned long m_CsCookie;

};

#endif // !defined(AFX_TESTLoadGroup_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

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

// TestStage.h: interface for the CTestStage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTStage_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTStage_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestStage :
public CComObjectRootEx<CComSingleThreadModel>,
public IStageEvents,
public IStagesEvents
{
public:
	static void Test();

	CTestStage();
	virtual ~CTestStage();

BEGIN_COM_MAP(CTestStage)
   COM_INTERFACE_ENTRY(IStageEvents)
   COM_INTERFACE_ENTRY(IStagesEvents)
END_COM_MAP()

public:
   STDMETHOD(OnStageChanged)(/*[in]*/ IStage*  Stage, ChangeType change);

   STDMETHOD(OnStagesChanged)(/*[in]*/ IStage*  Stage, ChangeType change);
   STDMETHOD(OnStagesAdded)(IStage* item, StageIndexType idx);
   STDMETHOD(OnStagesBeforeRemove)(IStage* item, StageIndexType idx);
	STDMETHOD(OnStagesMoveTo)(StageIndexType from, StageIndexType to);
	STDMETHOD(OnStagesCopyTo)(StageIndexType from, StageIndexType to);
	STDMETHOD(OnStagesReverse)();


   HRESULT OnCreateSegment(IStage* pstage);

   long m_LastID;

   bool m_csStageFired;
   bool m_csStagesFired;
   DWORD m_CsCookie;

};

#endif // !defined(AFX_TESTStage_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

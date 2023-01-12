///////////////////////////////////////////////////////////////////////
// Loading Test - Test driver for Loading library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// TestVehicularLoad.h: interface for the CTestVehicularLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVehicularLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTVehicularLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestVehicularLoad :
public CComObjectRootEx<CComSingleThreadModel>,
public ldIVehicularLoadEvents,
public ldIVehicularLoadsEvents
{
public:
	static void Test();

	CTestVehicularLoad();
	virtual ~CTestVehicularLoad();

BEGIN_COM_MAP(CTestVehicularLoad)
  COM_INTERFACE_ENTRY(ldIVehicularLoadEvents)
  COM_INTERFACE_ENTRY(ldIVehicularLoadsEvents)
END_COM_MAP()


public:
   STDMETHOD(OnVehicularLoadChanged)(/*[in]*/ldIVehicularLoad* VehicularLoad, ldLoadingChangeType change);

   STDMETHOD(OnVehicularLoadsChanged)(/*[in]*/ldIVehicularLoad* VehicularLoad, ldLoadingChangeType change);
   STDMETHOD(OnVehicularLoadsRenamed)(/*[in]*/BSTR oldName, /*[in]*/BSTR newName);
   STDMETHOD(OnVehicularLoadsAdded)(/*[in]*/ldIVehicularLoad* load);
   STDMETHOD(OnVehicularLoadsBeforeRemove)(/*[in]*/ldIVehicularLoad* load);

   HRESULT OnCreateSegment(ldIVehicularLoad* pVehicularLoad);

   bool m_csAxlesFired;
   bool m_csLiveLoadFired;
   bool m_csVehicularLoadsFired;
   unsigned long m_CsCookie;
   long m_LastID;
};

#endif // !defined(AFX_TESTVehicularLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

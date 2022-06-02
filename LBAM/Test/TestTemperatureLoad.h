///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// TestTemperatureLoad.h: interface for the CTestTemperatureLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTTemperatureLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTTemperatureLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestTemperatureLoad :
public CComObjectRootEx<CComSingleThreadModel>,
public ITemperatureLoadEvents,
public ITemperatureLoadsEvents
{
public:
	static void Test();

	CTestTemperatureLoad();
	virtual ~CTestTemperatureLoad();

BEGIN_COM_MAP(CTestTemperatureLoad)
   COM_INTERFACE_ENTRY(ITemperatureLoadEvents)
   COM_INTERFACE_ENTRY(ITemperatureLoadsEvents)
END_COM_MAP()

public:
   STDMETHOD(OnTemperatureLoadChanged)(/*[in]*/ITemperatureLoad* TemperatureLoad);
   STDMETHOD(OnTemperatureLoadsChanged)(/*[in]*/ITemperatureLoadItem* TemperatureLoad);
   STDMETHOD(OnTemperatureLoadsAdded)(/*[in]*/ITemperatureLoadItem* TemperatureLoad);
   STDMETHOD(OnTemperatureLoadsBeforeRemove)(/*[in]*/ITemperatureLoadItem* TemperatureLoad);

   bool m_csTemperatureLoadFired;
   bool m_csDFFired;
   unsigned long m_CsCookie;

};

#endif // !defined(AFX_TESTTemperatureLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// TestStrainLoad.h: interface for the CTestStrainLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTStrainLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTStrainLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestStrainLoad :
public CComObjectRootEx<CComSingleThreadModel>,
public IStrainLoadEvents,
public IStrainLoadsEvents
{
public:
	static void Test();

	CTestStrainLoad();
	virtual ~CTestStrainLoad();

BEGIN_COM_MAP(CTestStrainLoad)
   COM_INTERFACE_ENTRY(IStrainLoadEvents)
   COM_INTERFACE_ENTRY(IStrainLoadsEvents)
END_COM_MAP()


public:
   STDMETHOD(OnStrainLoadChanged)(/*[in]*/IStrainLoad* StrainLoad);
   STDMETHOD(OnStrainLoadsChanged)(/*[in]*/IStrainLoadItem* StrainLoad);
   STDMETHOD(OnStrainLoadsAdded)(/*[in]*/IStrainLoadItem* StrainLoad);
   STDMETHOD(OnStrainLoadsBeforeRemove)(/*[in]*/IStrainLoadItem* StrainLoad);

   bool m_csStrainLoadFired;
   bool m_csDFFired;
   unsigned long m_CsCookie;

};

#endif // !defined(AFX_TESTStrainLoad_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)

///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
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

// CrackedSectionSlice.h : Declaration of the CCrackedSectionSlice

#ifndef __CrackedSectionSlice_H_
#define __CrackedSectionSlice_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CCrackedSectionSlice
class ATL_NO_VTABLE CCrackedSectionSlice : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCrackedSectionSlice, &CLSID_CrackedSectionSlice>,
	public ISupportErrorInfo,
	public ICrackedSectionSlice
{
public:
	CCrackedSectionSlice()
	{
      m_Area = 0;
      m_cgX = 0;
      m_cgY = 0;
      m_Efg = 0;
      m_Ebg = 0;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_CRACKEDSECTIONSLICE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCrackedSectionSlice)
	COM_INTERFACE_ENTRY(ICrackedSectionSlice)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


private:
   CComPtr<IShape> m_Shape;
   Float64 m_Efg, m_Ebg;
   Float64 m_Area;
   Float64 m_cgX, m_cgY;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICrackedSectionSlice
public:
   STDMETHOD(InitSlice)(/*[in]*/IShape* pShape,/*[in]*/Float64 A,/*[in]*/Float64 cgX,/*[in]*/Float64 cgY,/*[in]*/Float64 Efg,/*[in]*/Float64 Ebg) override;
   STDMETHOD(get_Area)(/*[out,retval]*/Float64* pArea) override;
	STDMETHOD(get_CG)(/*[out,retval]*/IPoint2d** pCG) override;
	STDMETHOD(get_Efg)(/*[out,retval]*/Float64* pEfg) override;
	STDMETHOD(get_Ebg)(/*[out,retval]*/Float64* pEbg) override;
   STDMETHOD(get_Shape)(/*[out,retval]*/IShape** pShape) override;
};

#endif //__CrackedSectionSlice_H_

///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// Size2d.h : Declaration of the CSize2d

#ifndef __SIZE2D_H_
#define __SIZE2D_H_

#include "resource.h"       // main symbols
#include <GeomModel/Primitives.h>

/////////////////////////////////////////////////////////////////////////////
// CSize2d
class ATL_NO_VTABLE CSize2d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSize2d, &CLSID_Size2d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CSize2d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public ISize2d
{
public:
	CSize2d()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SIZE2D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSize2d)
	COM_INTERFACE_ENTRY(ISize2d)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::Size2d m_Size;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISize2d
public:
   STDMETHOD(Clone)(/*[out,retval]*/ISize2d** clone) override;
   STDMETHOD(Dimensions)(/*[out]*/Float64* pDx,/*[out]*/Float64* pDy) override;
	STDMETHOD(Scale)(/*[in]*/ Float64 factor) override;
	STDMETHOD(get_Magnitude)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Dy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Dy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Dx)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Dx)(/*[in]*/ Float64 newVal) override;
};

#endif //__SIZE2D_H_

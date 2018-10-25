///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

/////////////////////////////////////////////////////////////////////////////
// CSize2d
class ATL_NO_VTABLE CSize2d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSize2d, &CLSID_Size2d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CSize2d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IPersist,
   public ISize2d,
   public IStructuredStorage2
{
public:
	CSize2d()
	{
      m_Dx = 0.00;
      m_Dy = 0.00;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SIZE2D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSize2d)
	COM_INTERFACE_ENTRY(ISize2d)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

private:
   Float64 m_Dx;
   Float64 m_Dy;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISize2d
public:
   STDMETHOD(Clone)(/*[out,retval]*/ISize2d** clone);
   STDMETHOD(Dimensions)(/*[out]*/Float64* pDx,/*[out]*/Float64* pDy);
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
	STDMETHOD(Scale)(/*[in]*/ Float64 factor);
	STDMETHOD(get_Magnitude)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Dy)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Dy)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Dx)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Dx)(/*[in]*/ Float64 newVal);

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
};

#endif //__SIZE2D_H_

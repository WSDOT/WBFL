///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// Line2d.h : Declaration of the CLine2d

#ifndef __LINE2D_H_
#define __LINE2D_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLine2d
class ATL_NO_VTABLE CLine2d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLine2d, &CLSID_Line2d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CLine2d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public ILine2d,
   public IStructuredStorage2,
   public IPersist
{
public:
	CLine2d()
	{
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_LINE2D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLine2d)
	COM_INTERFACE_ENTRY(ILine2d)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   // line is stored implicitely (refer to Graphics Gems)
   CComPtr<IVector2d> m_pN; // normal vector *** Must be normalized !!!!
   Float64 m_C; // distance from origin

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILine2d
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(Clone)(/*[out,retval]*/ILine2d** ppLine);
	STDMETHOD(Reverse)();
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pCenter,/*[in]*/ Float64 angle);
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx, /*[in]*/ Float64 cy,/*[in]*/ Float64 angle);
	STDMETHOD(Offset)(/*[in]*/ Float64 offset);
	STDMETHOD(ThroughPoints)(/*[in]*/ IPoint2d* p1, /*[in]*/ IPoint2d* p2);
	STDMETHOD(GetImplicit)(/*[out]*/ Float64* pC,/*[out]*/ IVector2d** pN);
	STDMETHOD(SetImplicit)(/*[in]*/ Float64 c,/*[in]*/ IVector2d* pN);
	STDMETHOD(GetExplicit)(/*[out]*/ IPoint2d** p,/*[out]*/ IVector2d** d);
	STDMETHOD(SetExplicit)(/*[in]*/ IPoint2d *p,/*[in]*/ IVector2d* d);

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
};

#endif //__LINE2D_H_

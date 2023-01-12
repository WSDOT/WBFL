///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// Vector2d.h : Declaration of the CVector2d

#ifndef __VECTOR2D_H_
#define __VECTOR2D_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVector2d
class ATL_NO_VTABLE CVector2d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVector2d, &CLSID_Vector2d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CVector2d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IVector2d,
   public IStructuredStorage2,
   public IPersist
{
public:
	CVector2d()
	{
      m_X = 1.00;
      m_Y = 0.00;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VECTOR2D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVector2d)
	COM_INTERFACE_ENTRY(IVector2d)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

private:
   Float64 m_X;
   Float64 m_Y;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IVector2d
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
   STDMETHOD(Clone)(/*[out,retval]*/ IVector2d** ppClone) override;
	STDMETHOD(IncrementBy)(/*[in]*/ IVector2d* v,/*[out,retval]*/IVector2d** val) override;
	STDMETHOD(Increment)(/*[in]*/ IVector2d* v) override;
	STDMETHOD(DecrementBy)(/*[in]*/ IVector2d* v,/*[out,retval]*/IVector2d** val) override;
	STDMETHOD(Decrement)(/*[in]*/ IVector2d* v) override;
	STDMETHOD(AngleBetween)(/*[in]*/ IVector2d* v,/*[out,retval]*/Float64* val) override;
	STDMETHOD(Dot)(/*[in]*/ IVector2d* v,/*[out,retval]*/Float64* val) override;
	STDMETHOD(Scale)(/*[in]*/ Float64 factor) override;
	STDMETHOD(Rotate)(/*[in]*/ Float64 angle) override;
	STDMETHOD(Reflect)() override;
	STDMETHOD(Projection)(/*[in]*/ IVector2d* pVector,/*[out,retval]*/ Float64* pVal) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize) override;
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy) override;
	STDMETHOD(Normalize)() override;
	STDMETHOD(Normal)(/*[out,retval]*/ IVector2d** ppNormal) override;
	STDMETHOD(IsZero)(/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(get_Size)(/*[out, retval]*/ ISize2d* *pVal) override;
	STDMETHOD(get_Magnitude)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Magnitude)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Direction)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Direction)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Y)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X)(/*[in]*/ Float64 newVal) override;

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;
};

#endif //__VECTOR2D_H_

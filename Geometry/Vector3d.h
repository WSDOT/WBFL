///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// Vector3d.h : Declaration of the CVector3d

#ifndef __VECTOR3D_H_
#define __VECTOR3D_H_

#include "resource.h"       // main symbols
#include <GeomModel/Vector3d.h>


/////////////////////////////////////////////////////////////////////////////
// CVector3d
class ATL_NO_VTABLE CVector3d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVector3d, &CLSID_Vector3d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CVector3d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IVector3d
{
public:
	CVector3d()
	{
	}

	std::shared_ptr<WBFL::Geometry::Vector3d>& GetVector() { return m_pVector; }
	void SetVector(std::shared_ptr<WBFL::Geometry::Vector3d>& Vector) { m_pVector = Vector; }

DECLARE_REGISTRY_RESOURCEID(IDR_VECTOR3D)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVector3d)
	COM_INTERFACE_ENTRY(IVector3d)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
	std::shared_ptr<WBFL::Geometry::Vector3d> m_pVector{ std::make_shared<WBFL::Geometry::Vector3d>(1,0,0) };

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IVector3d
public:
   STDMETHOD(Clone)(/*[out,retval]*/ IVector3d** ppClone) override;
	STDMETHOD(IncrementBy)(/*[in]*/ IVector3d* v,/*[out,retval]*/IVector3d** val) override;
	STDMETHOD(Increment)(/*[in]*/ IVector3d* v) override;
	STDMETHOD(DecrementBy)(/*[in]*/ IVector3d* v,/*[out,retval]*/IVector3d** val) override;
	STDMETHOD(Decrement)(/*[in]*/ IVector3d* v) override;
	STDMETHOD(AngleBetween)(/*[in]*/ IVector3d* v,/*[out,retval]*/ Float64* angle) override;
	STDMETHOD(Dot)(/*[in]*/ IVector3d* v,/*[out,retval]*/Float64* val) override;
	STDMETHOD(Cross)(/*[in]*/ IVector3d* v,/*[out,retval]*/ IVector3d** result) override;
	STDMETHOD(get_Size)(/*[out, retval]*/ ISize3d* *pVal) override;
	STDMETHOD(Scale)(/*[in]*/ Float64 factor) override;
	STDMETHOD(Reflect)() override;
	STDMETHOD(Projection)(/*[in]*/ IVector3d* pVector,/*[out,retval]*/ Float64* pDist) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize3d* pSize) override;
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy,/*[in]*/ Float64 dz) override;
	STDMETHOD(Normalize)() override;
	STDMETHOD(get_Magnitude)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Magnitude)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(IsZero)(/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(get_Z)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Z)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Y)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X)(/*[in]*/ Float64 newVal) override;
};

#endif //__VECTOR3D_H_

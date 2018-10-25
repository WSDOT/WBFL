///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// CoordinateXform3d.h : Declaration of the CCoordinateXform3d

#ifndef __COORDINATEXFORM3D_H_
#define __COORDINATEXFORM3D_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CCoordinateXform3d
class ATL_NO_VTABLE CCoordinateXform3d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCoordinateXform3d, &CLSID_CoordinateXform3d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CCoordinateXform3d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public ICoordinateXform3d,
   public IStructuredStorage2,
   public IPersist
{
public:
	CCoordinateXform3d()
	{
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_COORDINATEXFORM3D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCoordinateXform3d)
	COM_INTERFACE_ENTRY(ICoordinateXform3d)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

private:
	CComPtr<IVector3d> m_pRotationVector;
	Float64 m_Angle; // Angle of rotation about the rotation vector
	CComPtr<IPoint3d> m_pNewOrigin;

   STDMETHOD(OldToNew)(/*[in]*/ IPoint3d* point);
	STDMETHOD(NewToOld)(/*[in]*/ IPoint3d* point);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICoordinateXform3d
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
	STDMETHOD(XformEx)(/*[in]*/ IPoint3d* point,/*[in]*/ XformType type,/*[out,retval]*/ IPoint3d** result);
   STDMETHOD(Xform)(/*[in,out]*/ IPoint3d** point,/*[in]*/ XformType type);
	STDMETHOD(get_RotationVector)(/*[out, retval]*/ IVector3d **pVal);
	STDMETHOD(putref_RotationVector)(/*[in]*/ IVector3d *newVal);
	STDMETHOD(get_RotationAngle)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_RotationAngle)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_NewOrigin)(/*[out, retval]*/ IPoint3d **pVal);
	STDMETHOD(putref_NewOrigin)(/*[in]*/ IPoint3d *newVal);

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
};

#endif //__COORDINATEXFORM3D_H_

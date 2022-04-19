///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// Point3dCollection.h : Declaration of the CPoint3dCollection

#ifndef __POINT3DCOLLECTION_H_
#define __POINT3DCOLLECTION_H_

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"

class CPoint3dCollection;
typedef CComVectorCollection<IPoint3dCollection,IPoint3d,IEnumPoint3d,&IID_IEnumPoint3d,CollectionIndexType> Point3dVectorImpl;

/////////////////////////////////////////////////////////////////////////////
// CPoint3dCollection
class ATL_NO_VTABLE CPoint3dCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPoint3dCollection, &CLSID_Point3dCollection>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPoint3dCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public Point3dVectorImpl
{
public:
	CPoint3dCollection()
	{
	}

   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_POINT3DCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPoint3dCollection)
	COM_INTERFACE_ENTRY(IPoint3dCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPoint3dCollection
public:
   STDMETHOD(Clone)(/*[out,retval]*/IPoint3dCollection** clone) override;
   STDMETHOD(get__Enum)(/*[out,retval]*/ IEnumPoint3d** ppenum) override;
   STDMETHOD(Clear)() override;
// STDMETHOD(Insert)([in]CollectionIndexType index,[in]IPoint3d* pPoint) override;
// STDMETHOD(Reverse)() override;
//	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType Index) override;
//	STDMETHOD(Add)(/*[in]*/ IPoint3d* pPoint) override;
//	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType Index, /*[out, retval]*/ IPoint3d* *pVal) override;
//	STDMETHOD(get__NewEnum)(/*[out, retval]*/ LPUNKNOWN *pVal) override;
//	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
   STDMETHOD(Offset)(Float64 dx,Float64 dy,Float64 dz) override;
   STDMETHOD(OffsetEx)(ISize3d* size) override;
   STDMETHOD(RemoveDuplicatePoints)() override;
};

#endif //__POINT3DCOLLECTION_H_

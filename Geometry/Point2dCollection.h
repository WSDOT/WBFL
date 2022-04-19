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

// Point2dCollection.h : Declaration of the CPoint2dCollection

#ifndef __POINT2DCOLLECTION_H_
#define __POINT2DCOLLECTION_H_

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"

class CPoint2dCollection;
typedef CComVectorCollection<IPoint2dCollection,IPoint2d,IEnumPoint2d,&IID_IEnumPoint2d,CollectionIndexType> Point2dVectorImpl;


/////////////////////////////////////////////////////////////////////////////
// CPoint2dCollection
class ATL_NO_VTABLE CPoint2dCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPoint2dCollection, &CLSID_Point2dCollection>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPoint2dCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public Point2dVectorImpl
{
public:
	CPoint2dCollection()
	{
	}

   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_POINT2DCOLLECTION)

BEGIN_COM_MAP(CPoint2dCollection)
	COM_INTERFACE_ENTRY(IPoint2dCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

public:
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPoint2dCollection
public:
   STDMETHOD(Clone)(/*[out,retval]*/IPoint2dCollection** clone) override;
   STDMETHOD(get__Enum)(/*[out,retval]*/ IEnumPoint2d** ppenum) override;
   STDMETHOD(Clear)() override;
//	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType Index) override;
//	STDMETHOD(Add)(/*[in]*/ IPoint2d* pPoint) override;
//	STDMETHOD(get_Item)(CollectionIndexType Index, IPoint2d** pPoint) override;
//	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
//	STDMETHOD(get__NewEnum)(IUnknown** retval) override;
   STDMETHOD(Offset)(Float64 dx,Float64 dy) override;
   STDMETHOD(OffsetEx)(ISize2d* size) override;
   STDMETHOD(RemoveDuplicatePoints)() override;
};

#endif //__POINT2DCOLLECTION_H_

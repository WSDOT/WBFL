///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2013  Washington State Department of Transportation
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
#include "GeometryCP.h"

class CPoint2dCollection;
typedef CComVectorCollection<IPoint2dCollection,IPoint2d,IEnumPoint2d,&IID_IEnumPoint2d,CollectionIndexType> Point2dVectorImpl;
typedef CPersistentCollection<CPoint2dCollection,Point2dVectorImpl,CollectionIndexType> PersistentPoint2dCollection;

/////////////////////////////////////////////////////////////////////////////
// CPoint2dCollection
class ATL_NO_VTABLE CPoint2dCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPoint2dCollection, &CLSID_Point2dCollection>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPoint2dCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public PersistentPoint2dCollection,
   public IPoint2dEvents,
   public IConnectionPointContainerImpl<CPoint2dCollection>,
   public CProxyDPoint2dCollectionEvents< CPoint2dCollection >
{
public:
	CPoint2dCollection()
	{
      m_bEventsEnabled = true;
	}

   void FinalRelease();

   void EnableEvents(bool bEnable) { m_bEventsEnabled = bEnable; }

DECLARE_REGISTRY_RESOURCEID(IDR_POINT2DCOLLECTION)

BEGIN_COM_MAP(CPoint2dCollection)
	COM_INTERFACE_ENTRY(IPoint2dCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY_CHAIN(PersistentPoint2dCollection)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPoint2dCollection)
	CONNECTION_POINT_ENTRY(IID_IPoint2dCollectionEvents)
END_CONNECTION_POINT_MAP()

protected:
   CComBSTR GetCollectionName()
   {
      return CComBSTR("Point2dCollection"); // This is the "Unit Name" stored in the persistance stream
   }

public:
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPoint2dCollection
public:
   STDMETHOD(Clone)(/*[out,retval]*/IPoint2dCollection** clone);
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(get__Enum)(/*[out,retval]*/ IEnumPoint2d** ppenum);
   STDMETHOD(Clear)();
//	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType Index);
//	STDMETHOD(Add)(/*[in]*/ IPoint2d* pPoint);
//	STDMETHOD(get_Item)(CollectionIndexType Index, IPoint2d** pPoint);
//	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
//	STDMETHOD(get__NewEnum)(IUnknown** retval);

// IPoint2dEvents
public:
	STDMETHOD(OnPointChanged)(IPoint2d* point);

protected :
   // implementation of container's virtual function
   virtual HRESULT OnBeforeAdd ( Point2dVectorImpl::StoredType* pVal);
   virtual HRESULT OnAfterAdd ( Point2dVectorImpl::StoredType* pVal, CollectionIndexType idx);
   virtual HRESULT OnBeforeRemove ( Point2dVectorImpl::StoredType* pVal, CollectionIndexType idx);
   virtual HRESULT OnAfterRemove (CollectionIndexType idx);

   void UnadviseAll();

   bool m_bEventsEnabled;

};

#endif //__POINT2DCOLLECTION_H_

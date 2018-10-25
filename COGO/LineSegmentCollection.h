///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// LineSegmentCollection.h : Declaration of the CLineSegmentCollection

#ifndef __LINESEGMENTCOLLECTION_H_
#define __LINESEGMENTCOLLECTION_H_
#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"
#include "COGOCP.h"


class CLineSegmentCollection;
typedef PersistentKeyedCollection<CLineSegmentCollection,ILineSegmentCollection,&IID_ILineSegmentCollection,CogoElementKey,ILineSegment2d> LineSegmentCollectionImpl;

/////////////////////////////////////////////////////////////////////////////
// CLineSegmentCollection
class ATL_NO_VTABLE CLineSegmentCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CLineSegmentCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CLineSegmentCollection, &CLSID_LineSegmentCollection>,
//	public ISupportErrorInfo,
//   public IObjectSafetyImpl<CLineSegmentCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CLineSegmentCollection>,
	public LineSegmentCollectionImpl,
   public ILineSegment2dEvents,
   public CProxyDLineSegmentCollectionEvents< CLineSegmentCollection >
{
public:
	CLineSegmentCollection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_LINESEGMENTCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLineSegmentCollection)
//	COM_INTERFACE_ENTRY(ILineSegmentCollection)
//	COM_INTERFACE_ENTRY2(IDispatch,ILineSegmentCollection)
//	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(ILineSegment2dEvents)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

//   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY_CHAIN(LineSegmentCollectionImpl)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLineSegmentCollection)
CONNECTION_POINT_ENTRY(IID_ILineSegmentCollectionEvents)
END_CONNECTION_POINT_MAP()


   virtual CComBSTR GetCollectionName() { return CComBSTR("LineSegments"); }
   virtual CComBSTR GetItemName() { return CComBSTR("LineSegment"); }

//// ISupportsErrorInfo
//	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILineSegmentCollection
public:
	STDMETHOD(Key)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoElementKey* key);
	STDMETHOD(get_Factory)(/*[out,retval]*/ ILineSegment2dFactory** factory);
	STDMETHOD(putref_Factory)(/*[in]*/ ILineSegment2dFactory* factory);
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
   STDMETHOD(get_Item)(/*[in]*/ CogoElementKey key, /*[out, retval]*/ ILineSegment2d* *pVal);
   STDMETHOD(putref_Item)(/*[in]*/ CogoElementKey key, /*[in]*/ ILineSegment2d* newVal);
   STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
   STDMETHOD(Add)(/*[in]*/ CogoElementKey key,/*[in]*/ IPoint2d* start,/*[in]*/ IPoint2d* end,/*[out,retval]*/ILineSegment2d* *ls);
   STDMETHOD(AddEx)(/*[in]*/ CogoElementKey key,/*[in]*/ ILineSegment2d* newVal);
   STDMETHOD(Remove)(/*[in]*/ CogoElementKey key);
   STDMETHOD(Clear)();
   STDMETHOD(FindKey)(/*[in]*/ ILineSegment2d* ls,/*[out,retval]*/CogoElementKey* key);
   STDMETHOD(get__EnumKeys)(/*[out,retval]*/ IEnumKeys** ppenum);
   STDMETHOD(get__EnumLineSegments)(/*[out,retval]*/ IEnumLineSegments** ppenum);
   STDMETHOD(Clone)(/*[out,retval]*/ ILineSegmentCollection* *clone);

// ILineSegmentEvents
public:
	STDMETHOD(OnLineSegmentChanged)(ILineSegment2d* lineSeg);

private:
   CComPtr<ILineSegment2dFactory> m_Factory;

   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);

   HRESULT LineSegNotFound(CogoElementKey key);
   HRESULT LineSegAlreadyDefined(CogoElementKey key);
   HRESULT LineSegKeyError(CogoElementKey key,UINT nHelpString,HRESULT hRes);

   void Advise(CogoElementKey key,ILineSegment2d* lineSeg);
   void Unadvise(CogoElementKey key,ILineSegment2d* lineSeg);
   void UnadviseAll();
   std::map<CogoElementKey,DWORD> m_Cookies;
};

#endif //__LINESEGMENTCOLLECTION_H_

///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2018  Washington State Department of Transportation
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
typedef PersistentIDCollection<CLineSegmentCollection,ILineSegmentCollection,&IID_ILineSegmentCollection,CogoObjectID,ILineSegment2d> LineSegmentCollectionImpl;

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


   CComBSTR GetCollectionName() { return CComBSTR("LineSegments"); }
   CComBSTR GetItemName() { return CComBSTR("LineSegment"); }

//// ISupportsErrorInfo
//	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILineSegmentCollection
public:
	STDMETHOD(ID)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoObjectID* ID) override;
	STDMETHOD(get_Factory)(/*[out,retval]*/ ILineSegment2dFactory** factory) override;
	STDMETHOD(putref_Factory)(/*[in]*/ ILineSegment2dFactory* factory) override;
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;  
   STDMETHOD(get_Item)(/*[in]*/ CogoObjectID id, /*[out, retval]*/ ILineSegment2d* *pVal) override;
   STDMETHOD(putref_Item)(/*[in]*/ CogoObjectID id, /*[in]*/ ILineSegment2d* newVal) override;
   STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
   STDMETHOD(Add)(/*[in]*/ CogoObjectID id,/*[in]*/ IPoint2d* start,/*[in]*/ IPoint2d* end,/*[out,retval]*/ILineSegment2d* *ls) override;
   STDMETHOD(AddEx)(/*[in]*/ CogoObjectID id,/*[in]*/ ILineSegment2d* newVal) override;
   STDMETHOD(Remove)(/*[in]*/ CogoObjectID id) override;
   STDMETHOD(Clear)() override;
   STDMETHOD(FindID)(/*[in]*/ ILineSegment2d* ls,/*[out,retval]*/CogoObjectID* ID) override;
   STDMETHOD(get__EnumIDs)(/*[out,retval]*/ IEnumIDs** ppenum) override;
   STDMETHOD(get__EnumLineSegments)(/*[out,retval]*/ IEnumLineSegments** ppenum) override;
   STDMETHOD(Clone)(/*[out,retval]*/ ILineSegmentCollection* *clone) override;

// ILineSegmentEvents
public:
	STDMETHOD(OnLineSegmentChanged)(ILineSegment2d* lineSeg) override;

private:
   CComPtr<ILineSegment2dFactory> m_Factory;

   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);

   HRESULT LineSegNotFound(CogoObjectID id);
   HRESULT LineSegAlreadyDefined(CogoObjectID id);
   HRESULT LineSegIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes);

   void Advise(CogoObjectID id,ILineSegment2d* lineSeg);
   void Unadvise(CogoObjectID id,ILineSegment2d* lineSeg);
   void UnadviseAll();
   std::map<CogoObjectID,DWORD> m_Cookies;
};

#endif //__LINESEGMENTCOLLECTION_H_

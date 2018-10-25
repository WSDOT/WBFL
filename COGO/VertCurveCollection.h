///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2012  Washington State Department of Transportation
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

// VertCurveCollection.h : Declaration of the CVertCurveCollection
#pragma once
 
#ifndef __VERTCURVECOLLECTION_H_
#define __VERTCURVECOLLECTION_H_

#include "resource.h"       // main symbols
#include "COGOCP.h"
#include "Collections.h"

class CVertCurveCollection;
typedef PersistentKeyedCollection<CVertCurveCollection,IVertCurveCollection,&IID_IVertCurveCollection,CogoElementKey,IVertCurve> VertCurveCollectionImpl;

/////////////////////////////////////////////////////////////////////////////
// CVertCurveCollection
class ATL_NO_VTABLE CVertCurveCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CVertCurveCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CVertCurveCollection, &CLSID_VertCurveCollection>,
	public IConnectionPointContainerImpl<CVertCurveCollection>,
	public VertCurveCollectionImpl,
   public IVertCurveEvents,
   public CProxyDVertCurveCollectionEvents< CVertCurveCollection >
{
public:
	CVertCurveCollection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_VERTCURVECOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVertCurveCollection)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IVertCurveEvents)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY_CHAIN(VertCurveCollectionImpl)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CVertCurveCollection)
	CONNECTION_POINT_ENTRY(IID_IVertCurveCollectionEvents)
END_CONNECTION_POINT_MAP()

   virtual CComBSTR GetCollectionName() { return CComBSTR("VertCurves"); }
   virtual CComBSTR GetItemName() { return CComBSTR("VertCurve"); }

// IVertCurveCollection
public:
   STDMETHOD(Clone)(/*[out,retval]*/ IVertCurveCollection* *clone);
	STDMETHOD(putref_Factory)(/*[in]*/IVertCurveFactory* factory);
	STDMETHOD(get_Factory)(/*[out,retval]*/IVertCurveFactory* *factory);
	STDMETHOD(Clear)();
	STDMETHOD(Add)(/*[in]*/ CogoElementKey key,/*[in]*/ IProfilePoint* pbg,/*[in]*/ IProfilePoint* pvi,/*[in]*/ IProfilePoint* pfg,/*[in]*/Float64 l1,/*[in]*/ Float64 l2,/*[out,retval]*/IVertCurve* *vc);
	STDMETHOD(AddEx)(/*[in]*/ CogoElementKey key,/*[in]*/ IVertCurve* newVal);
	STDMETHOD(Remove)(/*[in]*/ CogoElementKey key);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(get_Item)(/*[in]*/ CogoElementKey key, /*[out, retval]*/ IVertCurve* *pVal);
	STDMETHOD(putref_Item)(/*[in]*/ CogoElementKey key, /*[in]*/ IVertCurve* newVal);
// STDMETHOD(get__NewEnum)(IUnknown** retval);
   STDMETHOD(get__EnumKeys)(IEnumKeys** ppenum);
 	STDMETHOD(get__EnumVertCurves)(/*[out,retval]*/ IEnumVertCurves** ppenum);
	STDMETHOD(FindKey)(/*[in]*/ IVertCurve* vc,/*[out,retval]*/CogoElementKey* key);
	STDMETHOD(Key)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoElementKey* key);

// IVertCurveEvents
public:
	STDMETHOD(OnVertCurveChanged)(IVertCurve* vc);

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);
   HRESULT VertCurveNotFound(CogoElementKey key);
   HRESULT VertCurveAlreadyDefined(CogoElementKey key);
   HRESULT VertCurveKeyError(CogoElementKey key,UINT nHelpString,HRESULT hRes);

   void Advise(CogoElementKey key,IVertCurve* vc);
   void Unadvise(CogoElementKey key,IVertCurve* vc);
   void UnadviseAll();
   std::map<CogoElementKey,DWORD> m_Cookies;

   CComPtr<IVertCurveFactory> m_Factory;
};

#endif //__VERTCURVECOLLECTION_H_

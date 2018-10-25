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

// VertCurveCollection.h : Declaration of the CVertCurveCollection
#pragma once
 
#ifndef __VERTCURVECOLLECTION_H_
#define __VERTCURVECOLLECTION_H_

#include "resource.h"       // main symbols
#include "COGOCP.h"
#include "Collections.h"

class CVertCurveCollection;
typedef PersistentIDCollection<CVertCurveCollection,IVertCurveCollection,&IID_IVertCurveCollection,CogoObjectID,IVertCurve> VertCurveCollectionImpl;

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

   CComBSTR GetCollectionName() { return CComBSTR("VertCurves"); }
   CComBSTR GetItemName() { return CComBSTR("VertCurve"); }

// IVertCurveCollection
public:
   STDMETHOD(Clone)(/*[out,retval]*/ IVertCurveCollection* *clone) override;
	STDMETHOD(putref_Factory)(/*[in]*/IVertCurveFactory* factory) override;
	STDMETHOD(get_Factory)(/*[out,retval]*/IVertCurveFactory* *factory) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(Add)(/*[in]*/ CogoObjectID id,/*[in]*/ IProfilePoint* pbg,/*[in]*/ IProfilePoint* pvi,/*[in]*/ IProfilePoint* pfg,/*[in]*/Float64 l1,/*[in]*/ Float64 l2,/*[out,retval]*/IVertCurve* *vc) override;
	STDMETHOD(AddEx)(/*[in]*/ CogoObjectID id,/*[in]*/ IVertCurve* newVal) override;
	STDMETHOD(Remove)(/*[in]*/ CogoObjectID id) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(get_Item)(/*[in]*/ CogoObjectID id, /*[out, retval]*/ IVertCurve* *pVal) override;
	STDMETHOD(putref_Item)(/*[in]*/ CogoObjectID id, /*[in]*/ IVertCurve* newVal) override;
// STDMETHOD(get__NewEnum)(IUnknown** retval) override;
   STDMETHOD(get__EnumIDs)(IEnumIDs** ppenum) override;
 	STDMETHOD(get__EnumVertCurves)(/*[out,retval]*/ IEnumVertCurves** ppenum) override;
	STDMETHOD(FindID)(/*[in]*/ IVertCurve* vc,/*[out,retval]*/CogoObjectID* ID) override;
	STDMETHOD(ID)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoObjectID* ID) override;

// IVertCurveEvents
public:
	STDMETHOD(OnVertCurveChanged)(IVertCurve* vc) override;

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);
   HRESULT VertCurveNotFound(CogoObjectID id);
   HRESULT VertCurveAlreadyDefined(CogoObjectID id);
   HRESULT VertCurveIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes);

   void Advise(CogoObjectID id,IVertCurve* vc);
   void Unadvise(CogoObjectID id,IVertCurve* vc);
   void UnadviseAll();
   std::map<CogoObjectID,DWORD> m_Cookies;

   CComPtr<IVertCurveFactory> m_Factory;
};

#endif //__VERTCURVECOLLECTION_H_

///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// HorzCurveCollection.h : Declaration of the CHorzCurveCollection

#ifndef __HORZCURVECOLLECTION_H_
#define __HORZCURVECOLLECTION_H_
#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"
#include "COGOCP.h"

class CHorzCurveCollection;
typedef PersistentIDCollection<CHorzCurveCollection,IHorzCurveCollection,&IID_IHorzCurveCollection,CogoObjectID,IHorzCurve> HorzCurveCollectionImpl;

/////////////////////////////////////////////////////////////////////////////
// CHorzCurveCollection
class ATL_NO_VTABLE CHorzCurveCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CHorzCurveCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CHorzCurveCollection, &CLSID_HorzCurveCollection>,
	public IConnectionPointContainerImpl<CHorzCurveCollection>,
	public HorzCurveCollectionImpl,
   public IHorzCurveEvents,
   public CProxyDHorzCurveCollectionEvents< CHorzCurveCollection >
{
public:
	CHorzCurveCollection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_HORZCURVECOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHorzCurveCollection)
   COM_INTERFACE_ENTRY(IHorzCurveEvents)

	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY_CHAIN(HorzCurveCollectionImpl)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CHorzCurveCollection)
CONNECTION_POINT_ENTRY(IID_IHorzCurveCollectionEvents)
END_CONNECTION_POINT_MAP()


   virtual CComBSTR GetCollectionName() { return CComBSTR("HorzCurves"); }
   virtual CComBSTR GetItemName() { return CComBSTR("HorzCurve"); }

// IHorzCurveCollection
public:
	STDMETHOD(Clear)();
   STDMETHOD(Add)(/*[in]*/ CogoObjectID id,/*[in]*/ IPoint2d* pbt,/*[in]*/ IPoint2d* pi,/*[in]*/ IPoint2d* pft,/*[in]*/ Float64 radius,/*[in]*/ Float64 Ls1,/*[in]*/ Float64 Ls2,/*[out,retval]*/IHorzCurve** hc);
	STDMETHOD(AddEx)(/*[in]*/ CogoObjectID id,/*[in]*/ IHorzCurve* newVal);
	STDMETHOD(Remove)(/*[in]*/ CogoObjectID id);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(get_Item)(/*[in]*/ CogoObjectID id, /*[out, retval]*/ IHorzCurve* *pVal);
	STDMETHOD(putref_Item)(/*[in]*/ CogoObjectID id, /*[in]*/ IHorzCurve* newVal);
// STDMETHOD(get__NewEnum)(IUnknown** retval);
   STDMETHOD(get__EnumIDs)(IEnumIDs** ppenum);
	STDMETHOD(FindID)(/*[in]*/ IHorzCurve* hc,/*[out,retval]*/CogoObjectID* ID);
	STDMETHOD(get_Factory)(/*[out,retval]*/IHorzCurveFactory** factory);
	STDMETHOD(putref_Factory)(/*[in]*/IHorzCurveFactory* factory);
	STDMETHOD(ID)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoObjectID* ID);
   STDMETHOD(get__EnumHorzCurves)(/*[out,retval]*/ IEnumHorzCurves** ppenum);
   STDMETHOD(Clone)(/*[out,retval]*/ IHorzCurveCollection* *clone);

// IHorzCurveEvents
public:
   STDMETHOD(OnHorzCurveChanged)(/*[in]*/ IHorzCurve* hc);

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);

   HRESULT HorzCurveNotFound(CogoObjectID id);
   HRESULT HorzCurveAlreadyDefined(CogoObjectID id);
   HRESULT HorzCurveIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes);

   void Advise(CogoObjectID id,IHorzCurve* hc);
   void Unadvise(CogoObjectID id,IHorzCurve* hc);
   void UnadviseAll();
   std::map<CogoObjectID,DWORD> m_Cookies;

   CComPtr<IHorzCurveFactory> m_Factory;
};

#endif //__HORZCURVECOLLECTION_H_

///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// CompoundCurveCollection.h : Declaration of the CCompoundCurveCollection

#ifndef __CompoundCurveCOLLECTION_H_
#define __CompoundCurveCOLLECTION_H_
#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"
#include "COGOCP.h"

class CCompoundCurveCollection;
typedef PersistentIDCollection<CCompoundCurveCollection,ICompoundCurveCollection,&IID_ICompoundCurveCollection,CogoObjectID,ICompoundCurve> CompoundCurveCollectionImpl;

/////////////////////////////////////////////////////////////////////////////
// CCompoundCurveCollection
class ATL_NO_VTABLE CCompoundCurveCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CCompoundCurveCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CCompoundCurveCollection, &CLSID_CompoundCurveCollection>,
	public IConnectionPointContainerImpl<CCompoundCurveCollection>,
	public CompoundCurveCollectionImpl,
   public ICompoundCurveEvents,
   public CProxyDCompoundCurveCollectionEvents< CCompoundCurveCollection >
{
public:
	CCompoundCurveCollection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_COMPOUNDCURVECOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCompoundCurveCollection)
   COM_INTERFACE_ENTRY(ICompoundCurveEvents)

	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY_CHAIN(CompoundCurveCollectionImpl)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CCompoundCurveCollection)
CONNECTION_POINT_ENTRY(IID_ICompoundCurveCollectionEvents)
END_CONNECTION_POINT_MAP()


   CComBSTR GetCollectionName() { return CComBSTR("CompoundCurves"); }
   CComBSTR GetItemName() { return CComBSTR("CompoundCurve"); }

// ICompoundCurveCollection
public:
	STDMETHOD(Clear)() override;
   STDMETHOD(Add)(/*[in]*/ CogoObjectID id,/*[in]*/ IPoint2d* pbt,/*[in]*/ IPoint2d* pi,/*[in]*/ IPoint2d* pft,/*[in]*/ Float64 radius,/*[in]*/ Float64 Ls1,/*[in]*/ Float64 Ls2,/*[out,retval]*/ICompoundCurve** hc) override;
	STDMETHOD(AddEx)(/*[in]*/ CogoObjectID id,/*[in]*/ ICompoundCurve* newVal) override;
	STDMETHOD(Remove)(/*[in]*/ CogoObjectID id) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(get_Item)(/*[in]*/ CogoObjectID id, /*[out, retval]*/ ICompoundCurve* *pVal) override;
	STDMETHOD(putref_Item)(/*[in]*/ CogoObjectID id, /*[in]*/ ICompoundCurve* newVal) override;
// STDMETHOD(get__NewEnum)(IUnknown** retval) override;
   STDMETHOD(get__EnumIDs)(IEnumIDs** ppenum) override;
	STDMETHOD(FindID)(/*[in]*/ ICompoundCurve* hc,/*[out,retval]*/CogoObjectID* ID) override;
	STDMETHOD(get_Factory)(/*[out,retval]*/ICompoundCurveFactory** factory) override;
	STDMETHOD(putref_Factory)(/*[in]*/ICompoundCurveFactory* factory) override;
	STDMETHOD(ID)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoObjectID* ID) override;
   STDMETHOD(get__EnumCompoundCurves)(/*[out,retval]*/ IEnumCompoundCurves** ppenum) override;
   STDMETHOD(Clone)(/*[out,retval]*/ ICompoundCurveCollection* *clone) override;

// ICompoundCurveEvents
public:
   STDMETHOD(OnCompoundCurveChanged)(/*[in]*/ ICompoundCurve* hc) override;

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);

   HRESULT CompoundCurveNotFound(CogoObjectID id);
   HRESULT CompoundCurveAlreadyDefined(CogoObjectID id);
   HRESULT CompoundCurveIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes);

   void Advise(CogoObjectID id,ICompoundCurve* hc);
   void Unadvise(CogoObjectID id,ICompoundCurve* hc);
   void UnadviseAll();
   std::map<CogoObjectID,DWORD> m_Cookies;

   CComPtr<ICompoundCurveFactory> m_Factory;
};

#endif //__CompoundCurveCOLLECTION_H_

///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2023  Washington State Department of Transportation
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

// PointCollection.h : Declaration of the CPointCollection

#ifndef __PointCollection_H_
#define __PointCollection_H_
#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"

class CPointCollection;
typedef PersistentIDCollection<CPointCollection,IPointCollection,&IID_IPointCollection,CogoObjectID,IPoint2d> PointCollectionImpl;

/////////////////////////////////////////////////////////////////////////////
// CPointCollection
class ATL_NO_VTABLE CPointCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
// public CComRefCountTracer<CPointCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPointCollection, &CLSID_PointCollection>,
   public PointCollectionImpl
{
public:
	CPointCollection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_POINTCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPointCollection)
   COM_INTERFACE_ENTRY(IPointCollection)
   COM_INTERFACE_ENTRY_CHAIN(PointCollectionImpl)
END_COM_MAP()

   CComBSTR GetCollectionName() { return CComBSTR("Points"); }
   CComBSTR GetItemName() { return CComBSTR("Point"); }

//// ISupportsErrorInfo
//	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPointCollection
public:
//   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
   STDMETHOD(Clone)(/*[out,retval]*/IPointCollection* *clone) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(Add)(/*[in]*/ CogoObjectID id,/*[in]*/ Float64 x,/*[in]*/ Float64 y,/*[out,retval]*/ IPoint2d* *point) override;
	STDMETHOD(AddEx)(/*[in]*/ CogoObjectID id,/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(Remove)(/*[in]*/ CogoObjectID id) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(get_Item)(/*[in]*/ CogoObjectID id, /*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_Item)(/*[in]*/ CogoObjectID id, /*[in]*/ IPoint2d* newVal) override;
// STDMETHOD(get__NewEnum)(IUnknown** retval) override;
   STDMETHOD(get__EnumIDs)(IEnumIDs** ppenum) override;
	STDMETHOD(FindID)(/*[in]*/ IPoint2d* point,/*[out,retval]*/CogoObjectID* ID) override;
	STDMETHOD(ID)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoObjectID* ID) override;
   STDMETHOD(get__EnumPoints)(/*[out,retval]*/ IEnumPoint2d** ppenum) override;

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);

   HRESULT PointNotFound(CogoObjectID id);
   HRESULT PointAlreadyDefined(CogoObjectID id);
   HRESULT PointIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes);
};

#endif //__PointCollection_H_

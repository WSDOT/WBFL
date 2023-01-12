///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// SuperelevationCollection.h : Declaration of the CSuperelevationCollection

#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"

typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT,VARIANT,_Copy<VARIANT>, std::vector<CComVariant> > SuperelevationsEnum;
typedef ICollectionOnSTLImpl<ISuperelevationCollection,std::vector<CComVariant>,VARIANT,_Copy<VARIANT>, SuperelevationsEnum> ISuperelevationColl;

/////////////////////////////////////////////////////////////////////////////
// CSuperelevationCollection
class ATL_NO_VTABLE CSuperelevationCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSuperelevationCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSuperelevationCollection, &CLSID_SuperelevationCollection>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CSuperelevationCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISuperelevationColl,
   public IStructuredStorage2,
   public IPersistImpl<CSuperelevationCollection>
{
public:
	CSuperelevationCollection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SUPERELEVATIONCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSuperelevationCollection)
   COM_INTERFACE_ENTRY(ISuperelevationCollection)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

   CComBSTR GetCollectionName() { return CComBSTR("Superelevations"); }
   CComBSTR GetItemName() { return CComBSTR("Superelevation"); }

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISuperelevationCollection
public:
   STDMETHOD(get_Surface)(/*[out, retval]*/ ISurface* *pVal) override;
   STDMETHOD(putref_Surface)(/*[in]*/ ISurface* newVal) override;
	STDMETHOD(Clear)() override;
   STDMETHOD(Add)(/*[in]*/ VARIANT varBeginStation,/*[in]*/ VARIANT varBeginFullStation, /*[in]*/ VARIANT varEndFullStation,/*[in]*/ VARIANT varEndStation,/*[in]*/ Float64 rate,/*[in]*/IndexType pivotPoint,/*[in]*/SuperTransitionType beginType,/*[in]*/Float64 beginL1,/*[in]*/Float64 beginL2,/*[in]*/SuperTransitionType endType,/*[in]*/Float64 endL1,/*[in]*/Float64 endL2,/*[out,retval]*/ISuperelevation* *pSuperelevation) override;
	STDMETHOD(AddEx)(ISuperelevation* newVal) override;
	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType idx) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx, /*[out, retval]*/ ISuperelevation* *pVal) override;
	STDMETHOD(putref_Item)(/*[in]*/ CollectionIndexType idx, /*[in]*/ ISuperelevation* newVal) override;
   STDMETHOD(GetSuperelevation)(/*[in]*/VARIANT varStation,/*[out,retval]*/ISuperelevation** superelevation) override;
// STDMETHOD(get__NewEnum)(IUnknown** retval) override;
   STDMETHOD(get__EnumSuperelevations)(/*[out,retval]*/ IEnumSuperelevations** ppenum) override;
   STDMETHOD(Clone)(/*[out,retval]*/ ISuperelevationCollection* *clone) override;
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pStg) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);

   //HRESULT ValidateStation(ISuperelevation* pSuperelevation);
   //HRESULT ValidateStation(VARIANT varStation,bool bClone,IStation** station);

   ISurface* m_pSurface; // weak referece to associated profile
};


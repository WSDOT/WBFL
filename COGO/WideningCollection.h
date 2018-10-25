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

// WideningCollection.h : Declaration of the CWideningCollection

#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"
#include "COGOCP.h"

typedef std::pair<DWORD,CComVariant> WideningType;
typedef std::vector<WideningType> Widenings;
typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyFromPair2<WideningType,VARIANT>, Widenings > WideningsEnum;
typedef ICollectionOnSTLImpl<IWideningCollection, Widenings, VARIANT, CopyFromPair2<WideningType,VARIANT>,WideningsEnum> IWideningColl;

/////////////////////////////////////////////////////////////////////////////
// CWideningCollection
class ATL_NO_VTABLE CWideningCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CWideningCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CWideningCollection, &CLSID_WideningCollection>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CWideningCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CWideningCollection>,
	public IWideningColl,
   public IWideningEvents,
   public IStructuredStorage2,
   public CProxyDWideningCollectionEvents< CWideningCollection >,
   public IPersistImpl<CWideningCollection>
{
public:
	CWideningCollection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_WIDENINGCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWideningCollection)
   COM_INTERFACE_ENTRY(IWideningCollection)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)

	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IWideningEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CWideningCollection)
CONNECTION_POINT_ENTRY(IID_IWideningCollectionEvents)
END_CONNECTION_POINT_MAP()


   virtual CComBSTR GetCollectionName() { return CComBSTR("Widenings"); }
   virtual CComBSTR GetItemName() { return CComBSTR("Widening"); }

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IWideningCollection
public:
   STDMETHOD(get_Surface)(/*[out, retval]*/ ISurface* *pVal);
   STDMETHOD(putref_Surface)(/*[in]*/ ISurface* newVal);
	STDMETHOD(Clear)();
   STDMETHOD(Add)(/*[in]*/ VARIANT varBeginStation,/*[in]*/ VARIANT varBeginFullStation, /*[in]*/ VARIANT varEndFullStation,/*[in]*/ VARIANT varEndStation,/*[in]*/ Float64 widening,/*[in]*/IndexType pnt1,/*[in]*/IndexType pnt2,/*[out,retval]*/IWidening* *pWidening);
	STDMETHOD(AddEx)(IWidening* newVal);
	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType idx);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx, /*[out, retval]*/ IWidening* *pVal);
	STDMETHOD(putref_Item)(/*[in]*/ CollectionIndexType idx, /*[in]*/ IWidening* newVal);
   STDMETHOD(GetWidening)(/*[in]*/VARIANT varStation,/*[out,retval]*/IWidening** widening);
// STDMETHOD(get__NewEnum)(IUnknown** retval);
   STDMETHOD(get__EnumWidenings)(/*[out,retval]*/ IEnumWidenings** ppenum);
   STDMETHOD(Clone)(/*[out,retval]*/ IWideningCollection* *clone);
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pStg);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// IWideningEvents
public:
   STDMETHOD(OnWideningChanged)(/*[in]*/ IWidening* widening);

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);

   void AdviseElement(IWidening* pWidening,DWORD* pdwCookie);
   void UnadviseElement(CollectionIndexType idx);
   void UnadviseAll();

   //HRESULT ValidateStation(IWidening* pWidening);
   //HRESULT ValidateStation(VARIANT varStation,bool bClone,IStation** station);

   ISurface* m_pSurface; // weak referece to associated profile
};


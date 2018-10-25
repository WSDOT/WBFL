///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// SurfaceCollection.h : Declaration of the CSurfaceCollection

#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"
#include "COGOCP.h"

typedef std::pair<DWORD,CComVariant> SurfaceType;
typedef std::vector<SurfaceType> Surfaces;
typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyFromPair2<SurfaceType,VARIANT>, Surfaces > SurfacesEnum;
typedef ICollectionOnSTLImpl<ISurfaceCollection, Surfaces, VARIANT, CopyFromPair2<SurfaceType,VARIANT>,SurfacesEnum> ISurfaceColl;

/////////////////////////////////////////////////////////////////////////////
// CSurfaceCollection
class ATL_NO_VTABLE CSurfaceCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSurfaceCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSurfaceCollection, &CLSID_SurfaceCollection>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CSurfaceCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CSurfaceCollection>,
	public ISurfaceColl,
   public ISurfaceEvents,
   public IStructuredStorage2,
   public CProxyDSurfaceCollectionEvents< CSurfaceCollection >,
   public IPersistImpl<CSurfaceCollection>
{
public:
	CSurfaceCollection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SURFACECOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSurfaceCollection)
   COM_INTERFACE_ENTRY(ISurfaceCollection)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)

	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(ISurfaceEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSurfaceCollection)
CONNECTION_POINT_ENTRY(IID_ISurfaceCollectionEvents)
END_CONNECTION_POINT_MAP()


   virtual CComBSTR GetCollectionName() { return CComBSTR("Surfaces"); }
   virtual CComBSTR GetItemName() { return CComBSTR("Surface"); }

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISurfaceCollection
public:
   STDMETHOD(get_Profile)(/*[out, retval]*/ IProfile* *pVal);
   STDMETHOD(putref_Profile)(/*[in]*/ IProfile* newVal);
	STDMETHOD(Clear)();
	STDMETHOD(Add)(ISurface* newVal);
	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType idx);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx, /*[out, retval]*/ ISurface* *pVal);
	STDMETHOD(putref_Item)(/*[in]*/ CollectionIndexType idx, /*[in]*/ ISurface* newVal);
// STDMETHOD(get__NewEnum)(IUnknown** retval);
   STDMETHOD(get__EnumSurfaces)(/*[out,retval]*/ IEnumSurfaces** ppenum);
   STDMETHOD(GetSurface)(/*[in]*/VARIANT varStation,/*[out,retval]*/ISurface** ppSurface);
   STDMETHOD(Clone)(/*[out,retval]*/ ISurfaceCollection* *clone);
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pStg);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// ISurfaceEvents
public:
   STDMETHOD(OnSurfaceChanged)(/*[in]*/ ISurface* widening);

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);

   void AdviseElement(ISurface* pSurface,DWORD* pdwCookie);
   void UnadviseElement(CollectionIndexType idx);
   void UnadviseAll();

   HRESULT ValidateStation(VARIANT varStation,bool bClone,IStation** station);

   IProfile* m_pProfile; // weak referece to associated profile
};


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

// SurfaceTemplateCollection.h : Declaration of the CSurfaceTemplateCollection

#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"

typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, std::vector<CComVariant> > SurfaceTemplatesEnum;
typedef ICollectionOnSTLImpl<ISurfaceTemplateCollection, std::vector<CComVariant>, VARIANT, _Copy<VARIANT>, SurfaceTemplatesEnum> ISurfaceTemplateColl;

/////////////////////////////////////////////////////////////////////////////
// CSurfaceTemplateCollection
class ATL_NO_VTABLE CSurfaceTemplateCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSurfaceTemplateCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSurfaceTemplateCollection, &CLSID_SurfaceTemplateCollection>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CSurfaceTemplateCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISurfaceTemplateColl,
   public IStructuredStorage2,
   public IPersistImpl<CSurfaceTemplateCollection>
{
public:
	CSurfaceTemplateCollection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SURFACETEMPLATECOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSurfaceTemplateCollection)
   COM_INTERFACE_ENTRY(ISurfaceTemplateCollection)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()


   CComBSTR GetCollectionName() { return CComBSTR("SurfaceTemplates"); }
   CComBSTR GetItemName() { return CComBSTR("SurfaceTemplate"); }

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISurfaceTemplateCollection
public:
   STDMETHOD(get_Surface)(/*[out, retval]*/ ISurface* *pVal) override;
   STDMETHOD(putref_Surface)(/*[in]*/ ISurface* newVal) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(Add)(ISurfaceTemplate* newVal) override;
	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType idx) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx, /*[out, retval]*/ ISurfaceTemplate* *pVal) override;
	STDMETHOD(putref_Item)(/*[in]*/ CollectionIndexType idx, /*[in]*/ ISurfaceTemplate* newVal) override;
   STDMETHOD(GetBoundingTemplates)(/*[in]*/VARIANT varStation,/*[out]*/ISurfaceTemplate** ppStart,/*[out]*/ISurfaceTemplate** ppEnd) override;
// STDMETHOD(get__NewEnum)(IUnknown** retval) override;
   STDMETHOD(get__EnumSurfaceTemplates)(/*[out,retval]*/ IEnumSurfaceTemplates** ppenum) override;
   STDMETHOD(Clone)(/*[out,retval]*/ ISurfaceTemplateCollection* *clone) override;
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pStg) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);

   //HRESULT ValidateStation(ISurfaceTemplate* pSurfaceTemplate);
   //HRESULT ValidateStation(VARIANT varStation,bool bClone,IStation** station);

   ISurface* m_pSurface; // weak referece to associated profile
};


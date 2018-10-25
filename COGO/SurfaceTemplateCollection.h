///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2015  Washington State Department of Transportation
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
#include "COGOCP.h"

typedef std::pair<DWORD,CComVariant> SurfaceTemplateType;
typedef std::vector<SurfaceTemplateType> SurfaceTemplates;
typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyFromPair2<SurfaceTemplateType,VARIANT>, SurfaceTemplates > SurfaceTemplatesEnum;
typedef ICollectionOnSTLImpl<ISurfaceTemplateCollection, SurfaceTemplates, VARIANT, CopyFromPair2<SurfaceTemplateType,VARIANT>,SurfaceTemplatesEnum> ISurfaceTemplateColl;

/////////////////////////////////////////////////////////////////////////////
// CSurfaceTemplateCollection
class ATL_NO_VTABLE CSurfaceTemplateCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSurfaceTemplateCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSurfaceTemplateCollection, &CLSID_SurfaceTemplateCollection>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CSurfaceTemplateCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CSurfaceTemplateCollection>,
	public ISurfaceTemplateColl,
   public ISurfaceTemplateEvents,
   public IStructuredStorage2,
   public CProxyDSurfaceTemplateCollectionEvents< CSurfaceTemplateCollection >,
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

	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(ISurfaceTemplateEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSurfaceTemplateCollection)
CONNECTION_POINT_ENTRY(IID_ISurfaceTemplateCollectionEvents)
END_CONNECTION_POINT_MAP()


   virtual CComBSTR GetCollectionName() { return CComBSTR("SurfaceTemplates"); }
   virtual CComBSTR GetItemName() { return CComBSTR("SurfaceTemplate"); }

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISurfaceTemplateCollection
public:
   STDMETHOD(get_Profile)(/*[out, retval]*/ IProfile* *pVal);
   STDMETHOD(putref_Profile)(/*[in]*/ IProfile* newVal);
	STDMETHOD(Clear)();
	STDMETHOD(Add)(ISurfaceTemplate* newVal);
	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType idx);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx, /*[out, retval]*/ ISurfaceTemplate* *pVal);
	STDMETHOD(putref_Item)(/*[in]*/ CollectionIndexType idx, /*[in]*/ ISurfaceTemplate* newVal);
   STDMETHOD(GetBoundingTemplates)(/*[in]*/VARIANT varStation,/*[out]*/ISurfaceTemplate** ppStart,/*[out]*/ISurfaceTemplate** ppEnd);
// STDMETHOD(get__NewEnum)(IUnknown** retval);
   STDMETHOD(get__EnumSurfaceTemplates)(/*[out,retval]*/ IEnumSurfaceTemplates** ppenum);
   STDMETHOD(Clone)(/*[out,retval]*/ ISurfaceTemplateCollection* *clone);
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pStg);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// ISurfaceTemplateEvents
public:
   STDMETHOD(OnSurfaceTemplateChanged)(ISurfaceTemplate* pTemplate);
   STDMETHOD(OnTemplateSegmentAdded)(ISurfaceTemplate* pTemplate,ITemplateSegment* pSegment);
   STDMETHOD(OnTemplateSegmentRemoved)(ISurfaceTemplate* pTemplate);
   STDMETHOD(OnTemplateSegmentsCleared)(ISurfaceTemplate* pTemplate);

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);

   void AdviseElement(ISurfaceTemplate* pSurfaceTemplate,DWORD* pdwCookie);
   void UnadviseElement(CollectionIndexType idx);
   void UnadviseAll();

   //HRESULT ValidateStation(ISurfaceTemplate* pSurfaceTemplate);
   //HRESULT ValidateStation(VARIANT varStation,bool bClone,IStation** station);

   IProfile* m_pProfile; // weak referece to associated profile
};


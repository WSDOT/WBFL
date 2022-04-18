///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// SurfaceTemplate.h : Declaration of the CSurfaceTemplate

#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"


/////////////////////////////////////////////////////////////////////////////
// CSurfaceTemplate
class ATL_NO_VTABLE CSurfaceTemplate : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSurfaceTemplate,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSurfaceTemplate, &CLSID_SurfaceTemplate>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CSurfaceTemplate,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CSurfaceTemplate>,
   public ISurfaceTemplate,
   public IStructuredStorage2,
   public CProxyDSurfaceTemplateEvents< CSurfaceTemplate >,
   public IPersistImpl<CSurfaceTemplate>
{
public:
	CSurfaceTemplate()
	{
	}

	HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SURFACETEMPLATE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSurfaceTemplate)
	COM_INTERFACE_ENTRY(ISurfaceTemplate)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)

   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSurfaceTemplate)
CONNECTION_POINT_ENTRY(IID_ISurfaceTemplateEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISurfaceTemplate
public:
   STDMETHOD(get_Surface)(ISurface* *pVal) override;
   STDMETHOD(putref_Surface)(ISurface* newVal) override;
   STDMETHOD(put_Station)(VARIANT varStation) override;
   STDMETHOD(get_Station)(IStation** station) override;
   STDMETHOD(AddSegment)(Float64 width,Float64 slope,TemplateSlopeType slopeType) override;
   STDMETHOD(AddSegmentEx)(ITemplateSegment* segment) override;
   STDMETHOD(RemoveSegment)(CollectionIndexType idx) override;
   STDMETHOD(get_Item)(CollectionIndexType idx,ITemplateSegment** segment) override;
   STDMETHOD(get_Count)(CollectionIndexType* count) override;
   STDMETHOD(Clear)() override;
   STDMETHOD(GetRidgePointElevationChange)(CollectionIndexType ridgePointIdx1,CollectionIndexType ridgePointIdx2,Float64* deltaElevation) override;
   STDMETHOD(GetElevationChange)(CollectionIndexType ridgePointIdx,Float64 offset,Float64* deltaElevation) override;
   STDMETHOD(GetSlope)(CollectionIndexType ridgePointIdx,Float64 offset,Float64* pSlope) override;
   STDMETHOD(GetSegmentSlope)(CollectionIndexType segmentIdx,Float64* pSlope) override;
   STDMETHOD(GetRidgePointOffset)(IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset) override;
   STDMETHOD(GetRidgePointElevation)(IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset,Float64* pElev) override;
   STDMETHOD(Clone)(ISurfaceTemplate* *clone) override;
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pVal) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

private:
   ISurface* m_pSurface; // weak reference
   CComPtr<IStation> m_Station;
   std::vector<CComPtr<ITemplateSegment>> m_Segments;

   HRESULT ValidateStation(IStation* station);
   HRESULT SurfaceTemplateError(UINT nHelpString,HRESULT hRes);
};

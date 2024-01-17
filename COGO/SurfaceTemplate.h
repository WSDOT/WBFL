///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2024  Washington State Department of Transportation
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


/////////////////////////////////////////////////////////////////////////////
// CSurfaceTemplate
class ATL_NO_VTABLE CSurfaceTemplate : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSurfaceTemplate,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSurfaceTemplate, &CLSID_SurfaceTemplate>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CSurfaceTemplate,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ISurfaceTemplate
{
public:
	CSurfaceTemplate()
	{
      m_pSurface = nullptr;
	}

	HRESULT FinalConstruct();
   void FinalRelease();

   // This object is created by Surface and assigned the inner template
   void SetSurfaceTemplate(std::shared_ptr<WBFL::COGO::SurfaceTemplate> surfaceTemplate) { m_Template = surfaceTemplate; }
   std::shared_ptr<WBFL::COGO::SurfaceTemplate> GetSurfaceTemplate() { return m_Template; }

DECLARE_REGISTRY_RESOURCEID(IDR_SURFACETEMPLATE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSurfaceTemplate)
	COM_INTERFACE_ENTRY(ISurfaceTemplate)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISurfaceTemplate
public:
   STDMETHOD(get_Surface)(ISurface* *pVal) override;
   STDMETHOD(putref_Surface)(ISurface* newVal) override;
   STDMETHOD(get_Station)(IStation** station) override;
   STDMETHOD(GetSegmentParameters)(IndexType segmentIdx, Float64* pWidth, Float64* pSlope, TemplateSlopeType* pSlopeType) override;
   STDMETHOD(UpdateSegmentParameters)(IndexType segmentIdx,Float64 width,Float64 slope,TemplateSlopeType slopeType) override;
   STDMETHOD(get_Item)(IndexType idx,ISurfaceTemplateSegment** segment) override;
   STDMETHOD(get_Count)(IndexType* count) override;
   STDMETHOD(Clear)() override;
   STDMETHOD(GetRidgePointElevationChange)(IndexType ridgePointIdx1,IndexType ridgePointIdx2,Float64* deltaElevation) override;
   STDMETHOD(GetElevationChange)(IndexType ridgePointIdx,Float64 offset,Float64* deltaElevation) override;
   STDMETHOD(GetSlope)(IndexType ridgePointIdx,Float64 offset,Float64* pSlope) override;
   STDMETHOD(GetSegmentSlope)(IndexType segmentIdx,Float64* pSlope) override;
   STDMETHOD(GetRidgePointOffset)(IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset) override;
   STDMETHOD(GetRidgePointElevation)(IndexType ridgePointIdx, Float64* pElev) override;
   STDMETHOD(GetRidgePointOffsetAndElevation)(IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset,Float64* pElev) override;

private:
   std::shared_ptr<WBFL::COGO::SurfaceTemplate> m_Template;
   ISurface* m_pSurface; // weak reference
};

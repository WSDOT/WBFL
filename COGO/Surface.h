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

// Surface.h : Declaration of the CSurface

#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CSurface
class ATL_NO_VTABLE CSurface : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSurface,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSurface, &CLSID_Surface>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CSurface,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ISurface
{
public:
	CSurface()
	{
      m_pProfile = nullptr;
	}

	HRESULT FinalConstruct();
   void FinalRelease();

   void SetSurface(std::shared_ptr<WBFL::COGO::Surface> surface) { m_Surface = surface; }
   std::shared_ptr<WBFL::COGO::Surface> GetSurface() { return m_Surface; }

DECLARE_REGISTRY_RESOURCEID(IDR_SURFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSurface)
	COM_INTERFACE_ENTRY(ISurface)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISurface
public:
   STDMETHOD(get_Profile)(IProfile* *pVal) override;
   STDMETHOD(putref_Profile)(IProfile* newVal) override;
   STDMETHOD(put_AlignmentPoint)(IndexType pntIdx) override;
   STDMETHOD(get_AlignmentPoint)(IndexType* pntIdx) override;
   STDMETHOD(put_ProfileGradePoint)(IndexType pntIdx) override;
   STDMETHOD(get_ProfileGradePoint)(IndexType* pntIdx) override;
   STDMETHOD(put_SurfaceTemplateSegmentCount)(IndexType nSegments) override;
   STDMETHOD(get_SurfaceTemplateSegmentCount)(IndexType* pnSegments) override;
   STDMETHOD(CreateSurfaceTemplate)(VARIANT varStation, ISurfaceTemplate** ppTemplate) override;
   STDMETHOD(GetSurfaceTemplateCount)(IndexType* pCount) override;
   STDMETHOD(GetSurfaceTemplate)(IndexType idx, ISurfaceTemplate** ppTemplate) override;
   STDMETHOD(ClearSurfaceTemplates)() override;
   STDMETHOD(AddSuperelevation)(ISuperelevation* pSuperelevation) override;
   STDMETHOD(FindSuperelevation)(VARIANT varStation, ISuperelevation** ppSuperelevation) override;
   STDMETHOD(ClearSuperelevations)() override;
   STDMETHOD(AddWidening)(IWidening* pWidening) override;
   STDMETHOD(FindWidening)(VARIANT varStation, IWidening** ppWidening) override;
   STDMETHOD(ClearWidenings)() override;
   STDMETHOD(get_StartBoundaryLine)(ILineSegment2d** ppEndLine) override;
   STDMETHOD(get_EndBoundaryLine)(ILineSegment2d** ppEndLine) override;
   STDMETHOD(GetStationRange)(IStation** ppStart,IStation** ppEnd) override;
   STDMETHOD(CreateSurfaceTemplateSectionCut)(VARIANT varStation,VARIANT_BOOL bApplySuperelevations,ISurfaceTemplate** ppSurfaceTemplate) override;
   STDMETHOD(CreateSurfaceProfileSectionCut)(VARIANT varStation,VARIANT varSkewAngle,VARIANT_BOOL bApplySuperelevations,ISurfaceProfile** ppSurfaceProfile) override;
   
private:
   std::shared_ptr<WBFL::COGO::Surface> m_Surface;
   IProfile* m_pProfile; // weak reference
   std::map<Float64, CComPtr<ISurfaceTemplate>> m_SurfaceTemplates;
};

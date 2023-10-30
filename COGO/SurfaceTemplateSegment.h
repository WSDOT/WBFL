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

// TemplateSegment.h : Declaration of the CTemplateSegment

#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CTemplateSegment
class ATL_NO_VTABLE CSurfaceTemplateSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CTemplateSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSurfaceTemplateSegment, &CLSID_SurfaceTemplateSegment>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CSurfaceTemplateSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ISurfaceTemplateSegment
{
public:
	CSurfaceTemplateSegment()
	{
	}

	HRESULT FinalConstruct();
   void FinalRelease();

   void SetSurfaceTemplateSegment(const WBFL::COGO::SurfaceTemplateSegment& segment) { m_Segment = segment; }
   const WBFL::COGO::SurfaceTemplateSegment& GetSurfaceTemplateSegment() { return m_Segment; }

DECLARE_REGISTRY_RESOURCEID(IDR_SURFACETEMPLATESEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSurfaceTemplateSegment)
	COM_INTERFACE_ENTRY(ISurfaceTemplateSegment)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISurfaceTemplateSegment
public:
   STDMETHOD(Init)(Float64 width,Float64 slope,TemplateSlopeType slopeType) override;
   STDMETHOD(put_Width)(Float64 width) override;
   STDMETHOD(get_Width)(Float64* width) override;
   STDMETHOD(put_Slope)(Float64 slope) override;
   STDMETHOD(get_Slope)(Float64* slope) override;
   STDMETHOD(put_SlopeType)(TemplateSlopeType type) override;
   STDMETHOD(get_SlopeType)(TemplateSlopeType* type) override;

private:
   WBFL::COGO::SurfaceTemplateSegment m_Segment;
};

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
   public ISurface,
   public IStructuredStorage2,
   public IPersistImpl<CSurface>
{
public:
	CSurface()
	{
	}

	HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SURFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSurface)
	COM_INTERFACE_ENTRY(ISurface)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

HRESULT Init(IProfile* pProfile,ISurfaceTemplateCollection* pSurfaceTemplates,IndexType alignmentPointIdx,IndexType profilePointIdx,ISuperelevationCollection* pSuperelevations,IWideningCollection* pWidenings);


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISurface
public:
   STDMETHOD(get_Profile)(IProfile* *pVal) override;
   STDMETHOD(putref_Profile)(IProfile* newVal) override;
   STDMETHOD(get_ID)(/*[out,retval]*/CogoObjectID* id) override;
   STDMETHOD(put_ID)(/*[in]*/CogoObjectID id) override;
   STDMETHOD(get_SurfaceTemplates)(ISurfaceTemplateCollection** ppTemplates) override;
   STDMETHOD(get_SegmentCount)(IndexType* pntIdx) override;
   STDMETHOD(put_AlignmentPoint)(IndexType pntIdx) override;
   STDMETHOD(get_AlignmentPoint)(IndexType* pntIdx) override;
   STDMETHOD(put_ProfileGradePoint)(IndexType pntIdx) override;
   STDMETHOD(get_ProfileGradePoint)(IndexType* pntIdx) override;
   STDMETHOD(get_Superelevations)(ISuperelevationCollection** ppSuperelevations) override;
   STDMETHOD(get_Widenings)(IWideningCollection** ppWidenings) override;
   STDMETHOD(get_StartBoundaryLine)(ILineSegment2d** ppEndLine) override;
   STDMETHOD(get_EndBoundaryLine)(ILineSegment2d** ppEndLine) override;
   STDMETHOD(GetStationRange)(IStation** ppStart,IStation** ppEnd) override;
   STDMETHOD(CreateSurfaceTemplate)(VARIANT varStation,VARIANT_BOOL bApplySuperelevations,ISurfaceTemplate** ppSurfaceTemplate) override;
   STDMETHOD(CreateSurfaceProfile)(VARIANT varStation,VARIANT varDirection,VARIANT_BOOL bApplySuperelevations,ISurfaceProfile** ppSurfaceProfile) override;
   STDMETHOD(Clone)(ISurface** ppClone) override;
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pVal) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

private:
   CogoObjectID m_ID;
   IProfile* m_pProfile; // weak reference
   CComPtr<ISurfaceTemplateCollection> m_SurfaceTemplates;
   IndexType m_AlignmentPointIdx;
   IndexType m_ProfilePointIdx;
   CComPtr<ISuperelevationCollection> m_Superelevations;
   CComPtr<IWideningCollection> m_Widenings;

   HRESULT GetWidening(IStation* station,IndexType templateSegmentIdx,Float64* pWidening);
   HRESULT GetSuperelevation(IStation* station,IndexType templateSegmentIdx,Float64 slope,TemplateSlopeType slopeType,Float64* pSlope,TemplateSlopeType* pSlopeType);
   HRESULT CreateTemplateLine(ISurfaceTemplate* pSurfaceTemplate,ILineSegment2d** ppLine);

   HRESULT SurfaceError(UINT nHelpString,HRESULT hRes);

   void InvalidateRidgeLines();
   void ValidateRidgeLines();
   std::map<IndexType,std::vector<CComPtr<IPath>>> m_RidgeLines; // key is the sub-surface index
};

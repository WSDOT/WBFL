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

// Alignment.h : Declaration of the CAlignment

#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAlignment
class ATL_NO_VTABLE CAlignment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CAlignment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CAlignment, &CLSID_Alignment>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CAlignment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IAlignment
{
public:
	CAlignment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetAlignment(std::shared_ptr<WBFL::COGO::Alignment> alignment);
   std::shared_ptr<WBFL::COGO::Alignment> GetAlignment() { return m_Alignment; }

DECLARE_REGISTRY_RESOURCEID(IDR_ALIGNMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAlignment)
	COM_INTERFACE_ENTRY(IAlignment)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IAlignment
public:
   STDMETHOD(get_Item)(/*[in]*/ IndexType idx,/*[out, retval]*/ IPathElement** pVal)  override;
   STDMETHOD(get_Count)(/*[out, retval]*/ IndexType* pVal)  override;
	STDMETHOD(get_RefStation)(/*[out, retval]*/ IStation* *station) override;
	STDMETHOD(put_RefStation)(/*[in]*/ VARIANT varStation) override;
   STDMETHOD(AddPathElement)(/*[in]*/ IPathElement* element) override;
   STDMETHOD(InsertPathElement)(/*[in]*/ IndexType idx,/*[in]*/ IPathElement* element) override;
   STDMETHOD(ClearPathElements)() override;

   STDMETHOD(AddProfile)(IDType id, IProfile* pProfile) override;
   STDMETHOD(GetProfile)(IDType id,/*[out, retval]*/ IProfile** pVal) override;
   STDMETHOD(ClearProfiles)() override;

   STDMETHOD(Move)(/*[in]*/ Float64 dist,/*[in]*/ VARIANT varDirection) override;
   STDMETHOD(StationAndOffset)(/*[in]*/ IPoint2d* point,/*[out]*/ IStation** station,/*[out]*/ Float64* offset) override;
   STDMETHOD(ProjectPoint)(/*[in]*/ IPoint2d* point, /*[out]*/ IPoint2d** newPoint, /*[out]*/ IStation** ppStation, /*[out]*/ VARIANT_BOOL* pvbOnProjection) override;
   STDMETHOD(LocatePoint)(/*[in]*/ VARIANT varStation, /*[in]*/ OffsetMeasureType offsetMeasure, /*[in]*/ Float64 offset, /*[in]*/ VARIANT varDir,/*[out,retval]*/ IPoint2d* *newPoint) override;
   STDMETHOD(Intersect)(/*[in]*/ ILine2d* line,/*[in]*/IPoint2d* pNearest,/*[out,retval]*/IPoint2d** point) override;
   STDMETHOD(IntersectEx)(ILine2d* line, IPoint2d* pNearest, VARIANT_BOOL vbProjectBack, VARIANT_BOOL vbProjectAhead, IPoint2d** point) override;
   STDMETHOD(GetBearing)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ IDirection* *dir) override;
	STDMETHOD(GetNormal)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ IDirection* *dir) override;
   STDMETHOD(GetDirection)(VARIANT varStation, BSTR bstrOrientation, IDirection** direction) override;
   STDMETHOD(get_Length)(/*[out,retval]*/Float64* pLength) override;
   STDMETHOD(CreateOffsetAlignment)(/*[in]*/ Float64 offset,/*[out,retval]*/IAlignment** alignment) override;
   STDMETHOD(CreateSubAlignment)(/*[in]*/VARIANT varStartStation,/*[in]*/VARIANT varEndStation,/*[out,retval]*/IAlignment** alignment) override;
   STDMETHOD(CreateOffsetPath)(Float64 offset,IPath** path) override;
   STDMETHOD(CreateSubPath)(VARIANT varStartStation,VARIANT varEndStation,IPath** path) override;
   
   STDMETHOD(AddStationEquation)(Float64 back, Float64 ahead) override;
   STDMETHOD(GetStationEquationCount)(IndexType* pCount) override;
   STDMETHOD(GetStationEquation)(IndexType i, IStationEquation** ppEquation) override;
   STDMETHOD(ClearStationEquations)() override;
   STDMETHOD(IncrementStation)(VARIANT varStation, Float64 distance, IStation** station) override;
   STDMETHOD(IncrementStationBy)(IStation* station, Float64 distance) override;
   STDMETHOD(ConvertToNormalizedStation)(VARIANT varStation, Float64* station) override;
   STDMETHOD(ConvertToNormalizedStationEx)(VARIANT varStation, IStation** station) override;
   STDMETHOD(ConvertFromNormalizedStation)(Float64 normalizedStation, IStation** station) override;
   STDMETHOD(ConvertFromNormalizedStationEx)(VARIANT varStation, IStation** station) override;
   STDMETHOD(CompareStations)(VARIANT varStation1, VARIANT varStation2, Int8* pResult) override;
   STDMETHOD(DistanceBetweenStations)(VARIANT station1,VARIANT station2,Float64* pDist) override;

   STDMETHOD(Clone)(IAlignment** clone) override;

private:
   std::shared_ptr<WBFL::COGO::Alignment> m_Alignment;
   std::map<IDType, CComPtr<IProfile>> m_Profiles; // alignment owns the COM profile objects
   std::vector<CComPtr<IPathElement>> m_PathElements; // alignment owns the COM path elements

#if defined _DEBUG
   void Validate() const;
#endif
};

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

// Path.h : Declaration of the CPath

#ifndef __PATH_H_
#define __PATH_H_
#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CPath
class ATL_NO_VTABLE CPath : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPath,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPath, &CLSID_Path>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPath,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IPath,
   public IPathElement // see note on ICompoundCurve interface definition in IDL file
{
public:
	CPath()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetPath(std::shared_ptr<WBFL::COGO::Path> path);
   std::shared_ptr<WBFL::COGO::Path> GetPath() { return m_Path; }

DECLARE_REGISTRY_RESOURCEID(IDR_PATH)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPath)
	COM_INTERFACE_ENTRY(IPath)
   COM_INTERFACE_ENTRY(IPathElement)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPath
public:
   STDMETHOD(Clone)(/*[out,retval]*/ IPath* *clone) override;
   STDMETHOD(IntersectEx)(ILine2d* line,IPoint2d* pNearest,VARIANT_BOOL vbProjectBack,VARIANT_BOOL vbProjectAhead,IPoint2d** point) override;
   STDMETHOD(Intersect)(/*[in]*/ ILine2d* line,/*[in]*/IPoint2d* pNearest,/*[out,retval]*/IPoint2d** point) override;
   STDMETHOD(DistanceAndOffset)(/*[in]*/ IPoint2d* point,/*[out]*/ Float64* distance,/*[out]*/ Float64* offset) override;
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx,/*[out, retval]*/ IPathElement* *pVal) override;
	STDMETHOD(put_Item)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IPathElement *pVal) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(Add)(/*[in]*/ IPathElement* element) override;
	STDMETHOD(Insert)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IPathElement* element) override;
	STDMETHOD(Clear)() override;

// IPathElement
public:
   STDMETHOD(Clone)(IPathElement** clone) override;
   STDMETHOD(Move)(Float64 dist, VARIANT varDirection) override;
   STDMETHOD(Offset)(Float64 dx, Float64 dy) override;
   STDMETHOD(PointOnCurve)(Float64 distance, IPoint2d** pVal) override;
   STDMETHOD(GetStartPoint)(IPoint2d** ppPoint) override;
   STDMETHOD(GetEndPoint)(IPoint2d** ppPoint) override;
   STDMETHOD(GetLength)(Float64* pLength) override;
   STDMETHOD(GetKeyPoints)(IPoint2dCollection** ppPoints) override;
   STDMETHOD(LocatePoint)(Float64 distFromStart, OffsetMeasureType offsetType, Float64 offset, VARIANT varDirection, IPoint2d** ppPoint) override;
   STDMETHOD(GetBearing)(Float64 distFromStart, IDirection** ppDirection) override;
   STDMETHOD(GetNormal)(Float64 distFromStart, IDirection** ppNormal) override;
   STDMETHOD(ProjectPoint)(IPoint2d* point, IPoint2d** ppProjPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection) override;
   STDMETHOD(Intersect)(ILine2d* pLine, VARIANT_BOOL vbProjectBack, VARIANT_BOOL vbProjectAhead, IPoint2dCollection** ppPoints) override;
   STDMETHOD(CreateOffsetPath)(Float64 offset, IPath** ppPath) override;
   STDMETHOD(CreateSubpath)(Float64 start, Float64 end, IPath** ppPath) override;

private:
   std::shared_ptr<WBFL::COGO::Path> m_Path;

   std::vector<CComPtr<IPathElement>> m_PathElements;

#if defined _DEBUG
   void Validate() const;
#endif
};

#endif //__PATH_H_

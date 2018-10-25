///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

#include "Collections.h"
#include <vector>
#include "COGOCP.h"

typedef std::pair<DWORD,CComVariant> PathType; // cookie,varient(IUnknown for PathElement)
typedef std::vector<PathType> Paths;
typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyFromPair2<PathType,VARIANT>, Paths > PathEnum;
typedef ICollectionOnSTLImpl<IPath, Paths, VARIANT, CopyFromPair2<PathType,VARIANT>, PathEnum> IPathElementCollection;

struct Element
{
   Float64 start;
   Float64 end;
   CComPtr<IPathElement> pathElement;
};

/////////////////////////////////////////////////////////////////////////////
// CPath
class ATL_NO_VTABLE CPath : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPath,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPath, &CLSID_Path>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPath,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CPath>,
	public IPathElementCollection,
   public IStructuredStorage2,
	public IPathElementEvents,
	public CProxyDPathEvents< CPath >,
   public IPersistImpl<CPath>
{
public:
	CPath()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PATH)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPath)
	COM_INTERFACE_ENTRY(IPath)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IPathElementEvents)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPath)
CONNECTION_POINT_ENTRY(IID_IPathEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPath
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
   STDMETHOD(Clone)(/*[out,retval]*/ IPath* *clone) override;
   STDMETHOD(get__EnumPathElements)(/*[out, retval]*/ IEnumPathElements** pVal) override;  
   STDMETHOD(get_Length)(/*[out,retval]*/Float64* pLength) override;
   STDMETHOD(IntersectEx)(ILine2d* line,IPoint2d* pNearest,VARIANT_BOOL vbProjectBack,VARIANT_BOOL vbProjectAhead,IPoint2d** point) override;
   STDMETHOD(Intersect)(/*[in]*/ ILine2d* line,/*[in]*/IPoint2d* pNearest,/*[out,retval]*/IPoint2d** point) override;
	STDMETHOD(Offset)(/*[in]*/ IPoint2d* point,/*[out]*/ Float64* distance,/*[out]*/ Float64* offset) override; 
	STDMETHOD(ProjectPoint)(/*[in]*/ IPoint2d* point,/*[out,retval]*/ IPoint2d* *newPoint) override;
	STDMETHOD(Normal)(/*[in]*/ Float64 distance,/*[out,retval]*/ IDirection* *dir) override; 
	STDMETHOD(Bearing)(/*[in]*/ Float64 distance,/*[out,retval]*/ IDirection* *dir) override; 
	STDMETHOD(LocatePoint)(/*[in]*/ Float64 distance, /*[in]*/ OffsetMeasureType offsetMeasure, /*[in]*/ Float64 offset, /*[in]*/ VARIANT varDir,/*[out,retval]*/ IPoint2d* *newPoint) override; 
   //STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;  
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx,/*[out, retval]*/ IPathElement* *pVal) override;
	STDMETHOD(putref_Item)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IPathElement *pVal) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(Add)(/*[in]*/ IPathElement* element) override;
	STDMETHOD(AddEx)(/*[in]*/ IUnknown* dispElement) override;
	STDMETHOD(Insert)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IPathElement* element) override;
	STDMETHOD(InsertEx)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IUnknown* dispElement) override;
	STDMETHOD(Remove)(/*[in]*/ VARIANT varID) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(get_PointFactory)(/*[out,retval]*/IPoint2dFactory* *factory) override; 
	STDMETHOD(putref_PointFactory)(/*[in]*/IPoint2dFactory* factory) override; 
   STDMETHOD(Move)(/*[in]*/ Float64 dist,/*[in]*/ IDirection* direction) override;
   STDMETHOD(CreateParallelPath)(/*[in]*/ Float64 offset,/*[out,retval]*/IPath** path) override;
	STDMETHOD(CreateConnectedPath)(/*[out,retval]*/IPath** path) override;
   STDMETHOD(CreateSubPath)(/*[in]*/Float64 start,/*[in]*/Float64 end,/*[out,retval]*/IPath** path) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

// IPathElementEvents
public:
	STDMETHOD(OnPathElementChanged)(IPathElement * element)
	{
      m_PathElements.clear();
      Fire_OnPathChanged(this);
		return S_OK;
	}

private:
   CComPtr<IPoint2dFactory> m_PointFactory;

   CComPtr<IGeomUtil2d> m_GeomUtil;
   CComPtr<ICogoEngine> m_CogoEngine;
   CComPtr<ICoordinateXform2d> m_Xform;

   void AdviseElement(IPathElement* element,DWORD* pdwCookie);
   void UnadviseElement(CollectionIndexType idx);
   void UnadviseAll();

   std::vector<Element> m_PathElements; // not the same as m_coll. This is a fully connected path of elements
   // Returns a vector of Element objects that captures the start and end location
   // along the path of a path element as well as the path element itself.
   // Don't access m_PathElements directly. Use GetPathElements because it
   // initializes m_PathElements on demand.
   std::vector<Element>& GetPathElements();
   bool FindElement(IUnknown* pUnk, Element* pElement);

   Float64 m_PathLength;

   // Finds a PathElement object that contains the specified distance from start of the path.
   // Also determines the distance to teh begining of that Path element
   void FindElement(Float64 distance,Float64* pBeginDist,IPathElement* *pElement);

   // Returns a vector of Element that the given point will project onto
   std::vector<Element> FindElements(IPoint2d* point);

   // Returns the starting point of the given Path element
   void GetStartPoint(IPathElement* pElement,IPoint2d** ppStartPoint);

   // Returns the ending point of the given Path element
   void GetEndPoint(IPathElement* pElement,IPoint2d** ppEndPoint);

   // Creates a dummy line segment path element using a start and end point
   void CreateDummyPathElement(IPoint2d* pStart,IPoint2d* pEnd,IPathElement* *pElement);

   // Creates a dummy line segment path element using the given start point, and the start
   // point of the next path element
   void CreateDummyPathElement(IPoint2d* pStart,IPathElement* nextElement,IPathElement* *pElement);

   // Projects a point onto an Path element
   void ProjectPointOnElement(IPoint2d* point,IPathElement* pElement,IPoint2d** pNewPoint);

   // Intersects a line with a path element, puts the result point(s) in the point collection
   void IntersectElement(ILine2d* line,IPathElement* element,bool bProjectBack,bool bProjectAhead,IPoint2dCollection* points);

   // Returns true if the given point projects onto the Path element
   // If bExtendBack or bExtendAhead are true, the Path element is extended
   bool DoesPointProjectOntoElement(IPoint2d* point,IPathElement* element,bool bExtendBack, bool bExtendAhead);

   void CreateParallelHorzCurve(Float64 offset,IHorzCurve* hc,IUnknown** result);
   void CreateParallelCubicSpline(Float64 offset,ICubicSpline* spline,IUnknown** result);
   void CreateParallelPoint(CollectionIndexType elementIdx,Float64 offset,IPoint2d** pPoint);


   HRESULT CreateSubPathElement(Float64 start,Float64 end,ILineSegment2d* pLS,ILineSegment2d** ppLineSegment);
   HRESULT CreateSubPathElement(Float64 start,Float64 end,IHorzCurve* pHC,IUnknown** ppResult1,IUnknown** ppResult2,IUnknown** ppResult3);
   HRESULT CreateSubPathElement(Float64 start,Float64 end,ICubicSpline* pSpine,IUnknown** ppResult);
   HRESULT CreateSubCurveSpline(Float64 start,Float64 end,CollectionIndexType nPoints,IHorzCurve* pHC,ICubicSpline** ppSpline);
   HRESULT SavePathElement(IPath* pPath,IUnknown* pUnk);

   HRESULT DistanceAndOffset(IPoint2d* point,Float64* pDistance,Float64* pOffset);

   Float64 GetElementLength(IPathElement* pElement);

#if defined _DEBUG
   void DumpPathElements();
   void DumpPathElement(IPoint2d* pPoint);
   void DumpPathElement(ILineSegment2d* pLS);
   void DumpPathElement(IHorzCurve* pHC);
   void DumpPathElement(ICubicSpline* pSpine);
#endif
};

#endif //__PATH_H_

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

// CogoModel.h : Declaration of the CCogoModel

#ifndef __COGOMODEL_H_
#define __COGOMODEL_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCogoModel
class ATL_NO_VTABLE CCogoModel : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CCogoModel,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CCogoModel, &CLSID_CogoModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCogoModel,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ICogoModel,
   public IMeasure,
   public ILocate,
   public IIntersect,
   public IProject,
   public IDivide,
   public ITangent,
   public IStructuredStorage2,
   public IPersistImpl<CCogoModel>
{
public:
	CCogoModel()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   HRESULT put_Alignments(IAlignmentCollection* alignments);
   HRESULT put_Paths(IPathCollection* paths);
   HRESULT put_CompoundCurves(ICompoundCurveCollection* CompoundCurves);
   HRESULT put_Lines(ILineSegmentCollection* lines);
   HRESULT put_Points(IPointCollection* points);
   HRESULT put_ProfilePoints(IProfilePointCollection* profilePoints);
   HRESULT put_VertCurves(IVertCurveCollection* vertCurves);

DECLARE_REGISTRY_RESOURCEID(IDR_COGOMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCogoModel)
	COM_INTERFACE_ENTRY(ICogoModel)
	COM_INTERFACE_ENTRY(IMeasure)
	COM_INTERFACE_ENTRY(ILocate)
	COM_INTERFACE_ENTRY(IIntersect)
	COM_INTERFACE_ENTRY(IProject)
	COM_INTERFACE_ENTRY(IDivide)
	COM_INTERFACE_ENTRY(ITangent)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICogoModel
public:
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pStg) override;
   STDMETHOD(Clone)(/*[out,retval]*/ ICogoModel* *clone) override;
   STDMETHOD(get_Engine)(/*[out,retval]*/ICogoEngine** engine) override;
	STDMETHOD(putref_ProfilePointFactory)(/*[in]*/IProfilePointFactory* factory) override;
	STDMETHOD(get_ProfilePointFactory)(/*[out,retval]*/IProfilePointFactory** factory) override;
	STDMETHOD(putref_VertCurveFactory)(/*[in]*/IVertCurveFactory* factory) override;
	STDMETHOD(get_VertCurveFactory)(/*[out,retval]*/IVertCurveFactory** factory) override;
	STDMETHOD(putref_CompoundCurveFactory)(/*[in]*/ICompoundCurveFactory* factory) override;
	STDMETHOD(get_CompoundCurveFactory)(/*[out,retval]*/ICompoundCurveFactory** factory) override;
	STDMETHOD(putref_AlignmentFactory)(/*[in]*/IAlignmentFactory* factory) override;
	STDMETHOD(get_AlignmentFactory)(/*[out,retval]*/IAlignmentFactory** factory) override;
	STDMETHOD(putref_PathFactory)(/*[in]*/IPathFactory* factory) override;
	STDMETHOD(get_PathFactory)(/*[out,retval]*/IPathFactory** factory) override;
   STDMETHOD(get_Tangent)(/*[out, retval]*/ ITangent* *pVal) override;
   STDMETHOD(get_Divide)(/*[out, retval]*/ IDivide* *pVal) override;
	STDMETHOD(get_Project)(/*[out, retval]*/ IProject* *pVal) override;
	STDMETHOD(get_Measure)(/*[out, retval]*/ IMeasure* *pVal) override;
	STDMETHOD(get_Locate)(/*[out, retval]*/ ILocate* *pVal) override;
	STDMETHOD(get_Intersect)(/*[out, retval]*/ IIntersect* *pVal) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(get_Alignments)(/*[out,retval]*/ IAlignmentCollection* *pVal) override;
   STDMETHOD(get_Paths)(/*[out,retval]*/ IPathCollection* *pVal) override;
   STDMETHOD(get_VertCurves)(/*[out, retval]*/ IVertCurveCollection* *pVal) override;
   STDMETHOD(get_CompoundCurves)(/*[out, retval]*/ ICompoundCurveCollection* *pVal) override;
   STDMETHOD(get_ProfilePoints)(/*[out, retval]*/ IProfilePointCollection* *pVal) override;
   STDMETHOD(get_LineSegments)(/*[out, retval]*/ ILineSegmentCollection* *pVal) override;
	STDMETHOD(get_Points)(/*[out, retval]*/ IPointCollection* *pVal) override;

// IMeasure
public:
  	STDMETHOD(Angle)(/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID vertexID,/*[in]*/ CogoObjectID toID,/*[out,retval]*/ IAngle** angle) override;
	STDMETHOD(Area)(/*[in]*/ VARIANT IDs,/*[out,retval]*/ Float64* area) override;
	STDMETHOD(Distance)(/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID,/*[out,retval]*/ Float64* dist) override;
	STDMETHOD(Direction)(/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID,/*[out,retval]*/ IDirection** dir) override;
   STDMETHOD(Inverse)(/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID,/*[out]*/ Float64* dist,/*[out]*/ IDirection** dir) override;

// ILocate
public:
   STDMETHOD(ParallelLineSegment)(/*[in]*/ CogoObjectID newLineID,/*[in]*/ CogoObjectID newFromID,/*[in]*/ CogoObjectID newToID,/*[in]*/ CogoObjectID lineID, /*[in]*/ Float64 offset) override;
   STDMETHOD(ParallelLineByPoints)(/*[in]*/ CogoObjectID newFromID,/*[in]*/ CogoObjectID newToID,/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID, /*[in]*/ Float64 offset) override;
	STDMETHOD(ByDistAngle)(/*[in]*/ CogoObjectID newID,/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varAngle, /*[in]*/ Float64 offset) override;
	STDMETHOD(ByDistDefAngle)(/*[in]*/ CogoObjectID newID,/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDefAngle, /*[in]*/ Float64 offset) override;
	STDMETHOD(ByDistDir)(/*[in]*/ CogoObjectID newID,/*[in]*/ CogoObjectID fromID, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset) override;
	STDMETHOD(PointOnLine)(/*[in]*/ CogoObjectID newID,/*[in]*/ CogoObjectID fromID, /*[in]*/ CogoObjectID toID, /*[in]*/ Float64 dist, /*[in]*/ Float64 offset) override;
   STDMETHOD(LinesByPoints)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID id11, /*[in]*/ CogoObjectID id12, /*[in]*/ Float64 offset1,/*[in]*/ CogoObjectID id21, /*[in]*/ CogoObjectID id22, /*[in]*/ Float64 offset2, /*[out,retval]*/ VARIANT_BOOL* bFound) override;

// IIntersect
public:
   STDMETHOD(Bearings)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID id1, /*[in]*/ VARIANT varDir1, /*[in]*/ Float64 offset1,/*[in]*/ CogoObjectID id2, /*[in]*/ VARIANT varDir2, /*[in]*/ Float64 offset2,/*[out,retval]*/ VARIANT_BOOL* bFound) override;
   STDMETHOD(BearingCircle)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID id1, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset,/*[in]*/ CogoObjectID idc, /*[in]*/ Float64 radius, /*[in]*/ CogoObjectID idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound) override;
   STDMETHOD(Circles)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID id1, /*[in]*/ Float64 r1, /*[in]*/ CogoObjectID id2, /*[in]*/ Float64 r2, /*[in]*/ CogoObjectID idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound) override;
   STDMETHOD(LineByPointsCircle)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID id1, /*[in]*/ CogoObjectID id2, /*[in]*/ Float64 offset,/*[in]*/ CogoObjectID idc, /*[in]*/ Float64 radius, /*[in]*/ CogoObjectID idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound) override;
   STDMETHOD(Lines)(/*[in]*/CogoObjectID newID,/*[in]*/CogoObjectID id1,/*[in]*/Float64 offset1,/*[in]*/CogoObjectID id2,/*[in]*/Float64 offset2,/*[out,retval]*/VARIANT_BOOL* bFound) override;
   STDMETHOD(LineSegmentCircle)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID lineID, /*[in]*/ Float64 offset,/*[in]*/ CogoObjectID idc, /*[in]*/ Float64 radius, /*[in]*/ CogoObjectID idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound) override;

// IProject
public:
   STDMETHOD(PointOnCurve)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID fromID, /*[in]*/CogoObjectID curveID) override;
   STDMETHOD(PointOnLineByPoints)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID fromID, /*[in]*/ CogoObjectID startID, /*[in]*/ CogoObjectID endID, /*[in]*/ Float64 offset) override;
   STDMETHOD(PointOnLineSegment)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID lineID, /*[in]*/ Float64 offset) override;

// IDivide
public:
   STDMETHOD(Arc)(/*[in]*/CogoObjectID firstID,/*[in]*/ CogoObjectID idInc, /*[in]*/ CogoObjectID fromID, /*[in]*/ CogoObjectID HorzexID, /*[in]*/ CogoObjectID toID,/*[in]*/ CollectionIndexType nParts) override;
   STDMETHOD(BetweenPoints)(/*[in]*/CogoObjectID firstID,/*[in]*/ CogoObjectID idInc, /*[in]*/ CogoObjectID fromID, /*[in]*/ CogoObjectID toID,/*[in]*/ CollectionIndexType nParts) override;
   STDMETHOD(LineSegment)(/*[in]*/CogoObjectID firstID,/*[in]*/ CogoObjectID idInc, /*[in]*/ CogoObjectID lineID,/*[in]*/ CollectionIndexType nParts) override;
	STDMETHOD(CompoundCurve)(/*[in]*/ CogoObjectID firstID, /*[in]*/ CogoObjectID idInc, /*[in]*/ CogoObjectID curveID, /*[in]*/ CollectionIndexType nParts) override;
   STDMETHOD(Path)(/*[in]*/CogoObjectID firstID,/*[in]*/CogoObjectID idInc,/*[in]*/CogoObjectID pathID,/*[in]*/ CollectionIndexType nParts,/*[in]*/ Float64 start,/*[in]*/ Float64 end) override;

// ITangent
public:
   STDMETHOD(External)(/*[in]*/ CogoObjectID newID1, /*[in]*/ CogoObjectID idCenter1, /*[in]*/ Float64 radius1,/*[in]*/ CogoObjectID newID2,/*[in]*/ CogoObjectID idCenter2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign) override;
   STDMETHOD(Cross)(/*[in]*/ CogoObjectID newID1, /*[in]*/ CogoObjectID idCenter1, /*[in]*/ Float64 radius1,/*[in]*/ CogoObjectID newID2,/*[in]*/ CogoObjectID idCenter2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign) override;
   STDMETHOD(Point)(/*[in]*/ CogoObjectID newID, /*[in]*/ CogoObjectID idCenter, /*[in]*/ Float64 radius,/*[in]*/ CogoObjectID pointID,/*[in]*/ TangentSignType sign) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

private:
   CComPtr<ICogoEngine> m_Engine;

   CComPtr<IPointCollection> m_Points;
   CComPtr<ILineSegmentCollection> m_Lines;
   CComPtr<IProfilePointCollection> m_ProfilePoints;
   CComPtr<IVertCurveCollection> m_VertCurves;
   CComPtr<ICompoundCurveCollection> m_CompoundCurves;
   CComPtr<IAlignmentCollection> m_Alignments;
   CComPtr<IPathCollection> m_Paths;
};

#endif //__COGOMODEL_H_

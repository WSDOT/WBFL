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

// Alignment.h : Declaration of the CAlignment

#ifndef __ALIGNMENT_H_
#define __ALIGNMENT_H_
#pragma once

#include "resource.h"       // main symbols

//#include "Collections.h"
//#include <vector>
#include "COGOCP.h"

//typedef std::pair<DWORD,CComVariant> AlignmentType;
//typedef std::vector<AlignmentType> Alignments;
//typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyFromPair2<AlignmentType,VARIANT>, Alignments > AlignmentEnum;
//typedef ICollectionOnSTLImpl<IAlignment, Alignments, VARIANT, CopyFromPair2<AlignmentType,VARIANT>, AlignmentEnum> IAlignmentElementCollection;

/////////////////////////////////////////////////////////////////////////////
// CAlignment
class ATL_NO_VTABLE CAlignment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CAlignment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CAlignment, &CLSID_Alignment>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CAlignment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CAlignment>,
   public IStructuredStorage2,
   public IAlignment,
	public IPathEvents,
	public IProfileEvents,
   public IStationEquationCollectionEvents,
	public CProxyDAlignmentEvents< CAlignment >,
   public IPersistImpl<CAlignment>
{
public:
	CAlignment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void PutPath(IPath* pPath); // used by Clone

   STDMETHOD(putref_Profile)(/*[in]*/ IProfile* pVal);
	STDMETHOD(putref_StationEquations)(IStationEquationCollection* pVal);

DECLARE_REGISTRY_RESOURCEID(IDR_ALIGNMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAlignment)
	COM_INTERFACE_ENTRY(IAlignment)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IPathEvents)
	COM_INTERFACE_ENTRY(IProfileEvents)
	COM_INTERFACE_ENTRY(IStationEquationCollectionEvents)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAlignment)
   CONNECTION_POINT_ENTRY(IID_IAlignmentEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAlignment
public:
   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) { return m_Path->get__NewEnum(retval); }
   STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx,/*[out, retval]*/ IPathElement* *pVal) { return m_Path->get_Item(idx,pVal); }
   STDMETHOD(putref_Item)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IPathElement *pVal) { return m_Path->putref_Item(idx,pVal); }
   STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) { return m_Path->get_Count(pVal); }
	STDMETHOD(get_RefStation)(/*[out, retval]*/ IStation* *station);
	STDMETHOD(put_RefStation)(/*[in]*/ VARIANT varStation);
   STDMETHOD(get_Profile)(/*[out, retval]*/ IProfile* *pVal);
   STDMETHOD(get_StationEquations)(IStationEquationCollection* *pVal);
   STDMETHOD(Add)(/*[in]*/ IPathElement* element) { return m_Path->Add(element); }
   STDMETHOD(AddEx)(/*[in]*/ IUnknown* dispElement) { return m_Path->AddEx(dispElement); }
   STDMETHOD(Insert)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IPathElement* element) { return m_Path->Insert(idx,element); }
   STDMETHOD(InsertEx)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IUnknown* dispElement) { return m_Path->InsertEx(idx,dispElement); }
   STDMETHOD(Remove)(/*[in]*/ VARIANT varID) { return m_Path->Remove(varID); }
   STDMETHOD(Clear)() { return m_Path->Clear(); }
   STDMETHOD(LocatePoint)(/*[in]*/ VARIANT varStation, /*[in]*/ OffsetMeasureType offsetMeasure, /*[in]*/ Float64 offset, /*[in]*/ VARIANT varDir,/*[out,retval]*/ IPoint2d* *newPoint); 
   STDMETHOD(Bearing)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ IDirection* *dir); 
	STDMETHOD(Normal)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ IDirection* *dir); 
	STDMETHOD(Offset)(/*[in]*/ IPoint2d* point,/*[out]*/ IStation* *station,/*[out]*/ Float64* offset); 
	STDMETHOD(ProjectPoint)(/*[in]*/ IPoint2d* point,/*[out,retval]*/ IPoint2d* *newPoint)
   { return m_Path->ProjectPoint(point,newPoint); }
   STDMETHOD(Intersect)(/*[in]*/ ILine2d* line,/*[in]*/IPoint2d* pNearest,/*[out,retval]*/IPoint2d** point)
   { return m_Path->Intersect(line,pNearest,point); }
   STDMETHOD(IntersectEx)(ILine2d* line,IPoint2d* pNearest,VARIANT_BOOL vbProjectBack,VARIANT_BOOL vbProjectAhead,IPoint2d** point)
   { return m_Path->IntersectEx(line,pNearest,vbProjectBack,vbProjectAhead,point); }
	STDMETHOD(Offset)(/*[in]*/ IPoint2d* point,/*[out]*/ Float64* distance,/*[out]*/ Float64* offset)
   { return m_Path->Offset(point,distance,offset); }
   STDMETHOD(get_Length)(/*[out,retval]*/Float64* pLength)
   { return m_Path->get_Length(pLength); }
   STDMETHOD(get_PointFactory)(/*[out,retval]*/IPoint2dFactory* *factory)
   { return m_Path->get_PointFactory(factory); }
	STDMETHOD(putref_PointFactory)(/*[in]*/IPoint2dFactory* factory)
   { return m_Path->putref_PointFactory(factory); }
   STDMETHOD(get__EnumAlignmentElements)(/*[out, retval]*/ IEnumPathElements** pVal) { return m_Path->get__EnumPathElements(pVal); }
   STDMETHOD(Clone)(/*[out,retval]*/ IAlignment* *clone);
   STDMETHOD(CreateParallelAlignment)(/*[in]*/ Float64 offset,/*[out,retval]*/IAlignment** alignment);
   STDMETHOD(CreateSubAlignment)(/*[in]*/VARIANT varStartStation,/*[in]*/VARIANT varEndStation,/*[out,retval]*/IAlignment** alignment);
   STDMETHOD(CreateConnectedAlignment)(/*[out,retval]*/IAlignment** alignment);
   STDMETHOD(CreateParallelPath)(Float64 offset,IPath** path);
   STDMETHOD(CreateSubPath)(VARIANT varStartStation,VARIANT varEndStation,IPath** path);
   STDMETHOD(CreateConnectedPath)(IPath** path);
   STDMETHOD(Move)(/*[in]*/ Float64 dist,/*[in]*/ IDirection* direction)
   { return m_Path->Move(dist,direction); }
   STDMETHOD(GetDirection)(VARIANT varStation, BSTR bstrOrientation,IDirection** direction);
   STDMETHOD(DistanceBetweenStations)(VARIANT station1,VARIANT station2,Float64* pDist);

   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pVal);


// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// IProfileEvents
public:
	STDMETHOD(OnProfileChanged)(IProfile * profile)
	{
      ATLASSERT(m_Profile.IsEqualObject(profile));
      Fire_OnProfileChanged(profile);
      return S_OK;
	}

// IPathEvents
public:
   STDMETHOD(OnPathChanged)(IPath* path)
   {
      ATLASSERT(m_Path.IsEqualObject(path));
      Fire_OnAlignmentChanged(this);
      return S_OK;
   }

// IStationEquationCollectionEvents
public:
   STDMETHOD(OnEquationAdded)(CollectionIndexType idx,IStationEquation* pp)
   {
#if defined _DEBUG
      CComPtr<IStationEquation> equation;
      m_Equations->get_Item(idx,&equation);
      ATLASSERT(equation.IsEqualObject(pp));
#endif
      Fire_OnStationEquationsChanged(m_Equations);
      return S_OK;
   }

   STDMETHOD(OnEquationRemoved)(CollectionIndexType idx)
   {
      Fire_OnStationEquationsChanged(m_Equations);
      return S_OK;
   }

   STDMETHOD(OnEquationsCleared)()
   {
      Fire_OnStationEquationsChanged(m_Equations);
      return S_OK;
   }

private:
   CComPtr<IPath> m_Path;
   DWORD m_dwPathCookie;

   CComPtr<IProfile> m_Profile;
   DWORD m_dwProfileCookie;

   Float64 m_RefStation;

   CComPtr<IStationEquationCollection> m_Equations;
   DWORD m_dwEquationsCookie;

   HRESULT CreateStation(Float64 location,IStation** pStation);
   HRESULT StationToPathDistance(VARIANT varStation,Float64* distance);
};

#endif //__ALIGNMENT_H_

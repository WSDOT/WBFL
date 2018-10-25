///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2010  Washington State Department of Transportation
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
	public CProxyDPathEvents< CAlignment >,
   public IPersistImpl<CAlignment>
{
public:
	CAlignment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void PutPath(IPath* pPath); // used by Clone

DECLARE_REGISTRY_RESOURCEID(IDR_ALIGNMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAlignment)
	COM_INTERFACE_ENTRY(IAlignment)
	COM_INTERFACE_ENTRY(IPath)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IPathEvents)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAlignment)
CONNECTION_POINT_ENTRY(IID_IPathEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPath
public:
   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) { return m_Path->get__NewEnum(retval); }
   STDMETHOD(get_Profile)(/*[out, retval]*/ IProfile* *pVal) { return m_Path->get_Profile(pVal); }
   STDMETHOD(putref_Profile)(/*[in]*/ IProfile* pVal) { return m_Path->putref_Profile(pVal); }
   STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx,/*[out, retval]*/ IPathElement* *pVal) { return m_Path->get_Item(idx,pVal); }
   STDMETHOD(putref_Item)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IPathElement *pVal) { return m_Path->putref_Item(idx,pVal); }
   STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) { return m_Path->get_Count(pVal); }
   STDMETHOD(Add)(/*[in]*/ IPathElement* element) { return m_Path->Add(element); }
   STDMETHOD(AddEx)(/*[in]*/ IUnknown* dispElement) { return m_Path->AddEx(dispElement); }
   STDMETHOD(Insert)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IPathElement* element) { return m_Path->Insert(idx,element); }
   STDMETHOD(InsertEx)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IUnknown* dispElement) { return m_Path->InsertEx(idx,dispElement); }
   STDMETHOD(Remove)(/*[in]*/ VARIANT varKey) { return m_Path->Remove(varKey); }
   STDMETHOD(Clear)() { return m_Path->Clear(); }
	STDMETHOD(LocatePoint)(/*[in]*/ Float64 distance,/*[in]*/ OffsetMeasureType offsetMeasure,  /*[in]*/ Float64 offset, /*[in]*/ VARIANT varDir,/*[out,retval]*/ IPoint2d* *newPoint)
   { return m_Path->LocatePoint(distance,offsetMeasure,offset,varDir,newPoint); }
   STDMETHOD(Bearing)(/*[in]*/ Float64 distance,/*[out,retval]*/ IDirection* *dir)
   { return m_Path->Bearing(distance,dir); }
	STDMETHOD(Normal)(/*[in]*/ Float64 distance,/*[out,retval]*/ IDirection* *dir)
   { return m_Path->Normal(distance,dir); }
	STDMETHOD(ProjectPoint)(/*[in]*/ IPoint2d* point,/*[out,retval]*/ IPoint2d* *newPoint)
   { return m_Path->ProjectPoint(point,newPoint); }
   STDMETHOD(Intersect)(/*[in]*/ ILine2d* line,/*[in]*/IPoint2d* pNearest,/*[out,retval]*/IPoint2d** point)
   { return m_Path->Intersect(line,pNearest,point); }
	STDMETHOD(Offset)(/*[in]*/ IPoint2d* point,/*[out]*/ Float64* distance,/*[out]*/ Float64* offset)
   { return m_Path->Offset(point,distance,offset); }
   STDMETHOD(get_Length)(/*[out,retval]*/Float64* pLength)
   { return m_Path->get_Length(pLength); }
	STDMETHOD(get_PointFactory)(/*[out,retval]*/IPoint2dFactory* *factory)
   { return m_Path->get_PointFactory(factory); }
	STDMETHOD(putref_PointFactory)(/*[in]*/IPoint2dFactory* factory)
   { return m_Path->putref_PointFactory(factory); }
   STDMETHOD(get__EnumPathElements)(/*[out, retval]*/ IEnumPathElements** pVal)
   { return m_Path->get__EnumPathElements(pVal); }
   STDMETHOD(Move)(/*[in]*/ Float64 dist,/*[in]*/ IDirection* direction)
   { return m_Path->Move(dist,direction); }

   // IPath methods that Alignment overrides to provide extended implementations
   STDMETHOD(Clone)(/*[out,retval]*/ IPath* *clone);
   STDMETHOD(CreateParallelPath)(/*[in]*/ Float64 offset,/*[out,retval]*/IPath** path);
   STDMETHOD(CreateSubPath)(/*[in]*/Float64 start,/*[in]*/Float64 end,/*[out,retval]*/IPath** path);
   STDMETHOD(CreateConnectedPath)(/*[out,retval]*/IPath** path);
   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pVal);


// IAlignment
public:
	STDMETHOD(get_RefStation)(/*[out, retval]*/ IStation* *station);
	STDMETHOD(put_RefStation)(/*[in]*/ VARIANT varStation);
	STDMETHOD(LocatePoint)(/*[in]*/ VARIANT varStation, /*[in]*/ OffsetMeasureType offsetMeasure, /*[in]*/ Float64 offset, /*[in]*/ VARIANT varDir,/*[out,retval]*/ IPoint2d* *newPoint); 
   STDMETHOD(LocateCrownPoint2D)(/*[in]*/ VARIANT varStation, /*[in]*/ VARIANT varDir,/*[out,retval]*/ IPoint2d* *newPoint); 
   STDMETHOD(LocateCrownPoint3D)(/*[in]*/ VARIANT varStation, /*[in]*/ VARIANT varDir,/*[out,retval]*/ IPoint3d* *newPoint); 
   STDMETHOD(Bearing)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ IDirection* *dir); 
	STDMETHOD(Normal)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ IDirection* *dir); 
	STDMETHOD(Offset)(/*[in]*/ IPoint2d* point,/*[out]*/ IStation* *station,/*[out]*/ Float64* offset); 
   STDMETHOD(CreateSubPath)(/*[in]*/VARIANT varStartStation,/*[in]*/VARIANT varEndStation,/*[out,retval]*/IPath** path);
   STDMETHOD(GetDirection)(VARIANT varStation, BSTR bstrOrientation,IDirection** direction);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// IPathEvents
public:
   STDMETHOD(OnPathChanged)(IPath* path)
   {
      ATLASSERT(m_Path.IsEqualObject(path));
      Fire_OnPathChanged(this);
      return S_OK;
   }

	STDMETHOD(OnProfileChanged)(IProfile * profile)
	{
      Fire_OnProfileChanged(profile);
      return S_OK;
	}

private:
   CComPtr<IPath> m_Path;
   DWORD m_dwPathCookie;
   Float64 m_RefStation;

   HRESULT CreateStation(Float64 location,IStation** pStation);
   HRESULT StationToPathDistance(VARIANT varStation,Float64* distance);
};

#endif //__ALIGNMENT_H_

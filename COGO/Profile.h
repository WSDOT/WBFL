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

// Profile.h : Declaration of the CProfile

#ifndef __PROFILE_H_
#define __PROFILE_H_
#pragma once

#include "resource.h"       // main symbols

#include "Collections.h"
#include <vector>
#include "COGOCP.h"

typedef std::pair<DWORD,CComVariant> ProfileType;
typedef std::vector<ProfileType> Profiles;
typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyFromPair2<ProfileType,VARIANT>, Profiles > ProfileEnum;
typedef ICollectionOnSTLImpl<IProfile, Profiles, VARIANT, CopyFromPair2<ProfileType,VARIANT>, ProfileEnum> IProfileCollection;

/////////////////////////////////////////////////////////////////////////////
// CProfile
class ATL_NO_VTABLE CProfile : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CProfile,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CProfile, &CLSID_Profile>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CProfile,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CProfile>,
   public IProfileCollection,
   public ISurfaceCollectionEvents,
   public IProfileElementEvents,
   public IStructuredStorage2,
	public CProxyDProfileEvents< CProfile >,
   public IPersistImpl<CProfile>
{
public:
	CProfile()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PROFILE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProfile)
	COM_INTERFACE_ENTRY(IProfile)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISurfaceCollectionEvents)
	COM_INTERFACE_ENTRY(IProfileElementEvents)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CProfile)
CONNECTION_POINT_ENTRY(IID_IProfileEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IProfile
public:
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pStg);
   STDMETHOD(putref_Alignment)(/*[in]*/IAlignment* pAlignment);
   STDMETHOD(get_Alignment)(/*[out,retval]*/IAlignment** ppAlignment);
   STDMETHOD(Clone)(/*[out,retval]*/ IProfile* *clone);
	STDMETHOD(Clear)();
	STDMETHOD(Slope)(/*[in]*/ VARIANT varStation,/*[in]*/ Float64 offset,/*[out,retval]*/ Float64* slope);
   STDMETHOD(TemplateSegmentSlope)(/*[in]*/CogoObjectID id,/*[in]*/VARIANT varStation,/*[in]*/CollectionIndexType templateSegmentIdx,/*[out,retval]*/Float64* pSlope);
	STDMETHOD(Grade)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ Float64* grade);
	STDMETHOD(Elevation)(/*[in]*/ VARIANT varStation,/*[in]*/ Float64 offset,/*[out,retval]*/ Float64* elev);
	STDMETHOD(Remove)(/*[in]*/ VARIANT varID);
	STDMETHOD(Add)(/*[in]*/ IProfileElement* element);
	STDMETHOD(AddEx)(/*[in]*/ IUnknown* dispElement);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx,/*[out, retval]*/ IProfileElement* *pVal);
   STDMETHOD(putref_Item)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IProfileElement* pVal);
   STDMETHOD(get__EnumProfileElements)(/*[out, retval]*/ IEnumProfileElements** retval);  
   STDMETHOD(get_Surfaces)(/*[out,retval]*/ISurfaceCollection** ppSurfaces);
   STDMETHOD(putref_Surfaces)(/*[in]*/ISurfaceCollection* pSurfaces);
   STDMETHOD(GetSurface)(CogoObjectID id,VARIANT varStation,ISurface** ppSurface);
   STDMETHOD(RidgePointOffset)(CogoObjectID id,VARIANT varStation,IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset);
   STDMETHOD(RidgePointElevation)(CogoObjectID id,VARIANT varStation,IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset,Float64* pElev);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// ISurfaceCollectionEvents
   STDMETHOD(OnSurfaceChanged)(ISurface* pSurface)
   {
      Fire_OnProfileChanged(this);
      return S_OK;
   }
   STDMETHOD(OnSurfaceAdded)(ISurface* pSurface)
   {
      Fire_OnProfileChanged(this);
      return S_OK;
   }
   STDMETHOD(OnSurfaceRemoved)()
   {
      Fire_OnProfileChanged(this);
      return S_OK;
   }
   STDMETHOD(OnSurfacesCleared)()
   {
      Fire_OnProfileChanged(this);
      return S_OK;
   }


// IProfileElementEvents
	STDMETHOD(OnProfileElementChanged)(IProfileElement * pe)
	{
      Fire_OnProfileChanged(this);
		return S_OK;
	}

private:
   IAlignment* m_pAlignment; // weak reference
   CComPtr<ISurfaceCollection> m_Surfaces;
   DWORD m_dwSurfaceCollectionCookie;

   // objects used for searching the collection
   CComPtr<IProfileElement> m_TestElement;
   CComPtr<IProfilePoint> m_TestPoint;

   HRESULT GetStation(VARIANT varStation,IStation** station);

   HRESULT GradeAndElevation(IStation* pStation,Float64 offset,Float64* grade,Float64* elev,Float64* pSlope);
   void BeforeProfileGradeAndElevation(IStation* pStation,Float64* grade,Float64* elev);
   void ProfileGradeAndElevation(IStation* pStation,Float64* grade,Float64* elev);
   void AfterProfileGradeAndElevation(IStation* pStation,Float64*grade, Float64* elev);
   HRESULT AdjustForOffset(IStation* pStation,Float64 offset,Float64 profileElev,Float64* pAdjElev,Float64* pSlope);

   void AdviseElement(IProfileElement* element,DWORD* pdwCookie);
   void UnadviseElement(CollectionIndexType idx);
   void UnadviseAll();

   void AssociateWithProfile(IProfileElement* element,bool bAssociate=true);

   void AdviseSurfaces();
   void UnadviseSurfaces();
};

#endif //__PROFILE_H_

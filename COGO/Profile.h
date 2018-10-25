///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

typedef std::pair<CogoElementKey,CComVariant> ProfileType;
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
   public ICrossSectionCollectionEvents,
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
   COM_INTERFACE_ENTRY(ICrossSectionCollectionEvents)
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
   STDMETHOD(get_Path)(/*[out,retval]*/IPath** ppPath);
   STDMETHOD(putref_Path)(/*[in]*/IPath* pPath);
   STDMETHOD(Clone)(/*[out,retval]*/ IProfile* *clone);
	STDMETHOD(Clear)();
	STDMETHOD(CrownPointOffset)(/*[in]*/ VARIANT varStation,/*[out,retval]*/Float64* cpoffset);
	STDMETHOD(CrownSlope)(/*[in]*/ VARIANT varStation,/*[in]*/ Float64 offset,/*[out,retval]*/ Float64* slope);
	STDMETHOD(LeftCrownSlope)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ Float64* slope);
	STDMETHOD(RightCrownSlope)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ Float64* slope);
	STDMETHOD(Grade)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ Float64* grade);
	STDMETHOD(Elevation)(/*[in]*/ VARIANT varStation,/*[in]*/ Float64 offset,/*[out,retval]*/ Float64* elev);
	STDMETHOD(Remove)(/*[in]*/ VARIANT varKey);
	STDMETHOD(Add)(/*[in]*/ IProfileElement* element);
	STDMETHOD(AddEx)(/*[in]*/ IUnknown* dispElement);
   STDMETHOD(get_CrossSections)(/*[out, retval]*/ ICrossSectionCollection* *pVal);
	STDMETHOD(putref_CrossSections)(/*[in]*/ ICrossSectionCollection* pVal);
//	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Item)(/*[in]*/ long idx,/*[out, retval]*/ IProfileElement* *pVal);
   STDMETHOD(putref_Item)(/*[in]*/ long idx,/*[in]*/ IProfileElement* pVal);
   STDMETHOD(get__EnumProfileElements)(/*[out, retval]*/ IEnumProfileElements** retval);  

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// ICrossSectionCollectionEvents
	STDMETHOD(OnCrossSectionChanged)(ICrossSection * csect)
	{
      Fire_OnProfileChanged(this);
      return S_OK;
	}
	STDMETHOD(OnCrossSectionAdded)(ICrossSection * csect)
	{
      Fire_OnProfileChanged(this);
      return S_OK;
	}
	STDMETHOD(OnCrossSectionRemoved)()
	{
      Fire_OnProfileChanged(this);
      return S_OK;
	}
	STDMETHOD(OnCrossSectionsCleared)()
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
   IPath* m_pPath; // weak reference
   CComPtr<ICrossSectionCollection> m_CrossSections;
   DWORD m_dwCookie;

   HRESULT GradeAndElevation(VARIANT varStation,Float64 offset,Float64* grade,Float64* elev);
   void BeforeProfileGradeAndElevation(CComPtr<IStation>& station,Float64* grade,Float64* elev);
   void ProfileGradeAndElevation(CComPtr<IStation>& station,Float64* grade,Float64* elev);
   void AfterProfileGradeAndElevation(CComPtr<IStation>& station,Float64*grade, Float64* elev);
   Float64 AdjustForOffset(CComPtr<IStation>& station,Float64 offset,Float64 elev);

   void Advise(IProfileElement* element,DWORD* pdwCookie);
   void Unadvise(long idx);
   void UnadviseAll();

   void AdviseCrossSections();
   void UnadviseCrossSections();
};

#endif //__PROFILE_H_

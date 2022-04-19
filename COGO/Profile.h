///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

typedef CComVariant ProfileType;
typedef std::vector<ProfileType> Profiles;
typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, std::vector<CComVariant> > ProfileEnum;
typedef ICollectionOnSTLImpl<IProfile, std::vector<CComVariant>, VARIANT, _Copy<VARIANT>, ProfileEnum> IProfileCollection;


/////////////////////////////////////////////////////////////////////////////
// CProfile
class ATL_NO_VTABLE CProfile : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CProfile,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CProfile, &CLSID_Profile>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CProfile,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IProfileCollection,
   public IStructuredStorage2,
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
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

   STDMETHOD(put_Alignment)(IAlignment* pAlignment);


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IProfile
public:
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pStg) override;
   STDMETHOD(get_Alignment)(/*[out,retval]*/IAlignment** ppAlignment) override;
   STDMETHOD(Clone)(/*[out,retval]*/ IProfile* *clone) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(Slope)(/*[in]*/ VARIANT varStation,/*[in]*/ Float64 offset,/*[out,retval]*/ Float64* slope) override;
   STDMETHOD(TemplateSegmentSlope)(/*[in]*/CogoObjectID id,/*[in]*/VARIANT varStation,/*[in]*/CollectionIndexType templateSegmentIdx,/*[out,retval]*/Float64* pSlope) override;
	STDMETHOD(Grade)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ Float64* grade) override;
	STDMETHOD(Elevation)(/*[in]*/ VARIANT varStation,/*[in]*/ Float64 offset,/*[out,retval]*/ Float64* elev) override;
	STDMETHOD(Remove)(/*[in]*/ VARIANT varID) override;
	STDMETHOD(Add)(/*[in]*/ IProfileElement* element) override;
	STDMETHOD(AddEx)(/*[in]*/ IUnknown* dispElement) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx,/*[out, retval]*/ IProfileElement* *pVal) override;
   STDMETHOD(putref_Item)(/*[in]*/ CollectionIndexType idx,/*[in]*/ IProfileElement* pVal) override;
   STDMETHOD(get__EnumProfileElements)(/*[out, retval]*/ IEnumProfileElements** retval) override;  
   STDMETHOD(get_Surfaces)(/*[out,retval]*/ISurfaceCollection** ppSurfaces) override;
   STDMETHOD(putref_Surfaces)(/*[in]*/ISurfaceCollection* pSurfaces) override;
   STDMETHOD(GetSurface)(CogoObjectID id,VARIANT varStation,ISurface** ppSurface) override;
   STDMETHOD(RidgePointOffset)(CogoObjectID id,VARIANT varStation,IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset) override;
   STDMETHOD(RidgePointElevation)(CogoObjectID id,VARIANT varStation,IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset,Float64* pElev) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;


private:
   IAlignment* m_pAlignment; // weak reference
   CComPtr<ISurfaceCollection> m_Surfaces;

   // objects used for searching the collection
   CComPtr<IProfileElement> m_TestElement;
   CComPtr<IProfilePoint> m_TestPoint;

   HRESULT GetStation(VARIANT varStation,IStation** station);

   HRESULT GradeAndElevation(IStation* pStation,Float64 offset,Float64* grade,Float64* elev,Float64* pSlope);
   void BeforeProfileGradeAndElevation(IStation* pStation,Float64* grade,Float64* elev);
   void ProfileGradeAndElevation(IStation* pStation,Float64* grade,Float64* elev);
   void AfterProfileGradeAndElevation(IStation* pStation,Float64*grade, Float64* elev);
   HRESULT AdjustForOffset(IStation* pStation,Float64 offset,Float64 profileElev,Float64* pAdjElev,Float64* pSlope);

   void AssociateWithProfile(IProfileElement* element,bool bAssociate=true);
};

#endif //__PROFILE_H_

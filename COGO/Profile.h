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

// Profile.h : Declaration of the CProfile

#ifndef __PROFILE_H_
#define __PROFILE_H_
#pragma once

#include "resource.h"       // main symbols

#include "Collections.h"
#include <vector>

using ProfileType = CComVariant;
using Profiles = std::vector<ProfileType>;
using ProfileEnum = CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, std::vector<CComVariant> >;
using IProfileCollection = ICollectionOnSTLImpl<IProfile, std::vector<CComVariant>, VARIANT, _Copy<VARIANT>, ProfileEnum>;


/////////////////////////////////////////////////////////////////////////////
// CProfile
class ATL_NO_VTABLE CProfile : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CProfile,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CProfile, &CLSID_Profile>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CProfile,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IProfile
{
public:
	CProfile()
	{
      m_pAlignment = nullptr;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetProfile(std::shared_ptr<WBFL::COGO::Profile> profile);
   std::shared_ptr<WBFL::COGO::Profile> GetProfile() { return m_Profile; }

DECLARE_REGISTRY_RESOURCEID(IDR_PROFILE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProfile)
	COM_INTERFACE_ENTRY(IProfile)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IProfile
public:
   STDMETHOD(put_Alignment)(/*[in]*/IAlignment* ppAlignment) override;
   STDMETHOD(get_Alignment)(/*[out,retval]*/IAlignment** ppAlignment) override;
   STDMETHOD(AddProfileElement)(/*[in]*/ IProfileElement* element) override;
   STDMETHOD(get_ProfileElementCount)(/*[out, retval]*/ IndexType* pVal) override;
   STDMETHOD(get_Item)(/*[in]*/ IndexType idx,/*[out, retval]*/ IProfileElement** pVal) override;
   STDMETHOD(ClearProfileElements)() override;
   STDMETHOD(AddSurface)(IDType id, ISurface* pSurface) override;
   STDMETHOD(GetSurface)(IDType id, ISurface** ppSurface) override;
   STDMETHOD(ClearSurfaces)() override;
   STDMETHOD(Clear)();
   STDMETHOD(CreateSurfaceTemplateSectionCut)(IDType surfaceID, VARIANT varStation, VARIANT_BOOL vbApplySuperelevation, ISurfaceTemplate** ppTemplate) override;
   STDMETHOD(CreateSurfaceTemplateSectionCutEx)(ISurface* pSurface, VARIANT varStation, VARIANT_BOOL vbApplySuperelevation, ISurfaceTemplate** ppTemplate) override;
   STDMETHOD(Elevation)(/*[in]*/IDType surfaceID,/*[in]*/ VARIANT varStation,/*[in]*/ Float64 offset,/*[out,retval]*/ Float64* elev) override;
   STDMETHOD(Grade)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ Float64* grade) override;
   STDMETHOD(CrossSlope)(/*[in]*/IDType surfaceID,/*[in]*/ VARIANT varStation,/*[in]*/ Float64 offset,/*[out,retval]*/ Float64* slope) override;

   //STDMETHOD(Clone)(/*[out,retval]*/ IProfile* *clone) override;
   STDMETHOD(SurfaceTemplateSegmentSlope)(/*[in]*/IDType id,/*[in]*/VARIANT varStation,/*[in]*/IndexType templateSegmentIdx,/*[out,retval]*/Float64* pSlope) override;
   //STDMETHOD(get__EnumProfileElements)(/*[out, retval]*/ IEnumProfileElements** retval) override;
   //STDMETHOD(get_Surfaces)(/*[out,retval]*/ISurfaceCollection** ppSurfaces) override;
   //STDMETHOD(putref_Surfaces)(/*[in]*/ISurfaceCollection* pSurfaces) override;
   STDMETHOD(GetSurfaceContainingStation)(VARIANT varStation,IDType* pID,ISurface** ppSurface) override;
   STDMETHOD(GetRidgePointOffset)(IDType id,VARIANT varStation,IndexType ridgePoint1Idx,IndexType ridgePoint2dIdx,Float64* pOffset) override;
   STDMETHOD(GetRidgePointElevation)(IDType id,VARIANT varStation,IndexType ridgePointIdx,Float64* pElev) override;
   STDMETHOD(GetRidgePointOffsetAndElevation)(IDType id, VARIANT varStation, IndexType ridgePoint1Idx, IndexType ridgePoint2Idx,Float64* pOffset, Float64* pElev) override;

private:
   std::shared_ptr<WBFL::COGO::Profile> m_Profile;
   IAlignment* m_pAlignment; // weak pointer to parent. See notes in get_Alignment

   std::vector<CComPtr<IProfileElement>> m_ProfileElements; // Profile owns the COM profile elements
   std::map<IDType, CComPtr<ISurface>> m_Surfaces; // Profile owns the COM surfaces

#if defined _DEBUG
   void Validate() const;
#endif
};

#endif //__PROFILE_H_

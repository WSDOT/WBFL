///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2025  Washington State Department of Transportation
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

// SurfaceProfile.h : Declaration of the CSurfaceProfile
// A surface profile is similar to a surface template except that it is cut
// at any orientation across the surface (assuming the cut is somewhat transverse to the alignment)

#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CSurfaceProfile
class ATL_NO_VTABLE CSurfaceProfile : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSurfaceProfile,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSurfaceProfile, &CLSID_SurfaceProfile>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CSurfaceProfile,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ISurfaceProfile
{
public:
	CSurfaceProfile()
	{
      m_pSurface = nullptr;
	}

	HRESULT FinalConstruct();
   void FinalRelease();

   void SetSurfaceProfile(std::shared_ptr<WBFL::COGO::SurfaceProfile> profile) { m_SurfaceProfile = profile; }
   std::shared_ptr<WBFL::COGO::SurfaceProfile> GetSurfaceProfile() { return m_SurfaceProfile; }

DECLARE_REGISTRY_RESOURCEID(IDR_SURFACEPROFILE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSurfaceProfile)
	COM_INTERFACE_ENTRY(ISurfaceProfile)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISurfaceProfile
public:
   STDMETHOD(get_Surface)(ISurface* *pVal) override;
   STDMETHOD(putref_Surface)(ISurface* newVal) override;
   STDMETHOD(get_Station)(IStation** station) override;
   STDMETHOD(get_Direction)(IDirection** direction) override;
   STDMETHOD(get_SkewAngle)(IAngle** skewAngle) override;
   STDMETHOD(get_Item)(IndexType idx,ISurfacePoint** point) override;
   STDMETHOD(get_Count)(IndexType* count) override;
   STDMETHOD(GetSurfacePointElevationChange)(IndexType surfacePointIdx1,IndexType surfacePointIdx2,Float64* deltaElevation) override;
   STDMETHOD(GetElevationChange)(IndexType surfacePointIdx,Float64 offset,Float64* deltaElevation) override;
   STDMETHOD(GetSlope)(IndexType surfacePointIdx,Float64 offset,Float64* pSlope) override;
   STDMETHOD(GetSegmentSlope)(IndexType segmentIdx,Float64* pSlope) override;
   STDMETHOD(GetSurfacePointOffset)(IndexType surfacePointIdx,Float64* pOffset) override;
   STDMETHOD(GetSurfacePointElevation)(IndexType surfacePointIdx,Float64* pOffset,Float64* pElev) override;

private:
   std::shared_ptr<WBFL::COGO::SurfaceProfile> m_SurfaceProfile;
   ISurface* m_pSurface; // weak reference
};

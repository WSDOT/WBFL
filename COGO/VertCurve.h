///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// VertCurve.h : Declaration of the CVertCurve

#ifndef __VERTCURVE_H_
#define __VERTCURVE_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"


/////////////////////////////////////////////////////////////////////////////
// CVertCurve
class ATL_NO_VTABLE CVertCurve : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CVertCurve,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CVertCurve, &CLSID_VertCurve>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CVertCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CVertCurve>,
   public IVertCurve,
   public IStructuredStorage2,
   public IProfilePointEvents,
   public CProxyDVertCurveEvents< CVertCurve >,
   public IPersistImpl<CVertCurve>
{
public:
	CVertCurve()
	{
      m_pProfile = nullptr;
	}

	HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_VERTCURVE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVertCurve)
	COM_INTERFACE_ENTRY(IVertCurve)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IProfilePointEvents)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)

   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CVertCurve)
CONNECTION_POINT_ENTRY(IID_IVertCurveEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IVertCurve
public:
   STDMETHOD(get_ComputeFromGradePoints)(/*[out,retval]*/VARIANT_BOOL* pvbCompute) override;
   STDMETHOD(put_ComputeFromGradePoints)(/*[in]*/VARIANT_BOOL vbCompute) override;
   STDMETHOD(get_Profile)(IProfile* *pVal) override;
   STDMETHOD(putref_Profile)(IProfile* newVal) override;
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
   STDMETHOD(Clone)(/*[out,retval]*/ IVertCurve* *clone) override;
	STDMETHOD(get_A)(/*[out,retval]*/Float64* a) override;
   STDMETHOD(get_K1)(/*[out,retval]*/Float64* k) override;
   STDMETHOD(get_K2)(/*[out,retval]*/Float64* k) override;
   STDMETHOD(get_H)(/*[out,retval]*/Float64* h) override;
   STDMETHOD(get_E)(/*[[in]*/Float64 t,/*[out,retval]*/Float64* e) override;
	STDMETHOD(Grade)(/*[in]*/ VARIANT varStation,/*[out,retval]*/Float64* grade) override;
	STDMETHOD(Elevation)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ Float64* elev) override;
	STDMETHOD(get_HighPoint)(/*[out, retval]*/ IProfilePoint* *pVal) override;
	STDMETHOD(get_LowPoint)(/*[out, retval]*/ IProfilePoint* *pVal) override;
	STDMETHOD(put_ExitGrade)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_ExitGrade)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EntryGrade)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EntryGrade)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_PFG)(/*[out, retval]*/ IProfilePoint* *pVal) override;
	STDMETHOD(putref_PFG)(/*[in]*/ IProfilePoint* newVal) override;
	STDMETHOD(get_PVI)(/*[out, retval]*/ IProfilePoint* *pVal) override;
	STDMETHOD(putref_PVI)(/*[in]*/ IProfilePoint* newVal) override;
	STDMETHOD(get_PBG)(/*[out, retval]*/ IProfilePoint* *pVal) override;
	STDMETHOD(putref_PBG)(/*[in]*/ IProfilePoint* newVal) override;
	STDMETHOD(get_L1)(/*[out,retval]*/ Float64* pVal) override;
	STDMETHOD(put_L1)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_L2)(/*[out,retval]*/ Float64* pVal) override;
	STDMETHOD(put_L2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_BVC)(/*[out, retval]*/ IProfilePoint* *pVal) override;
	STDMETHOD(get_EVC)(/*[out, retval]*/ IProfilePoint* *pVal) override;
   STDMETHOD(get_ProfilePointFactory)(/*[out,retval]*/IProfilePointFactory* *factory) override;
   STDMETHOD(putref_ProfilePointFactory)(/*[in]*/IProfilePointFactory* factory) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

// IProfilePointEvents
public:
	STDMETHOD(OnProfilePointChanged)(IProfilePoint* pp) override;

private:
   // if true, L1, L2, BVC, PVI, and EVC are computed from PBG, PFG, g1, and g2
   // assuming BVC=PBG and EVC=PFG
   VARIANT_BOOL m_vbComputeFromGrades;

   IProfile* m_pProfile; // weak reference
   CComPtr<IProfilePointFactory> m_Factory;
   CComPtr<IProfilePoint> m_PBG;
   CComPtr<IProfilePoint> m_BVC;
   CComPtr<IProfilePoint> m_PVI;
   CComPtr<IProfilePoint> m_EVC;
   CComPtr<IProfilePoint> m_PFG;
   DWORD m_dwPBG, m_dwPVI, m_dwPFG; // event cookies
   Float64 m_L1, m_L2; // Half-length of vert curve
   Float64 m_g1, m_g2; // entry and exit grades

   HRESULT IsValid(); // return S_OK if the curve is valid
   void MyAdvise(IProfilePoint* pp,DWORD* pdwCookie);
   void MyUnadvise(IProfilePoint* pp,DWORD dwCookie);

   bool m_bIsDirty;
   void MakeDirty();
   HRESULT Update();

   HRESULT ValidateStation(IProfilePoint* profilePoint);
   HRESULT ValidateStation(VARIANT varStation,IStation** station);
   void TransitionPoint(IStation* *sta,Float64* elev,Float64* grade);
};

#endif //__VERTCURVE_H_

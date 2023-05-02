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

// VerticalCurve.h : Declaration of the CVerticalCurve

#ifndef __VerticalCurve_H_
#define __VerticalCurve_H_
#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CVerticalCurve
class ATL_NO_VTABLE CVerticalCurve : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CVerticalCurve,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CVerticalCurve, &CLSID_VerticalCurve>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CVerticalCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IVerticalCurve,
	public IProfileElement
{
public:
	CVerticalCurve()
	{
	}

	HRESULT FinalConstruct();
   void FinalRelease();

	void SetVerticalCurve(std::shared_ptr<WBFL::COGO::VerticalCurve> vc) { m_Curve = vc; }
	std::shared_ptr<WBFL::COGO::VerticalCurve> GetVerticalCurve() { return m_Curve; }

DECLARE_REGISTRY_RESOURCEID(IDR_VERTICALCURVE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVerticalCurve)
	COM_INTERFACE_ENTRY(IVerticalCurve)
   COM_INTERFACE_ENTRY(IProfileElement)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IVerticalCurve
public:
   STDMETHOD(Init)(IProfilePoint* pPBT, IProfilePoint* pPVI, IProfilePoint* pPFT, Float64 L1, Float64 L2) override;
   STDMETHOD(Init2)(IProfilePoint* pPBT, IProfilePoint* pPFT, Float64 g1, Float64 g2) override;
   //STDMETHOD(Clone)(/*[out,retval]*/ IVerticalCurve* *clone) override;
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
	STDMETHOD(get_PFG)(/*[out, retval]*/ IProfilePoint* *pVal) override;
	STDMETHOD(put_PFG)(/*[in]*/ IProfilePoint* newVal) override;
	STDMETHOD(get_PVI)(/*[out, retval]*/ IProfilePoint* *pVal) override;
	STDMETHOD(put_PVI)(/*[in]*/ IProfilePoint* newVal) override;
	STDMETHOD(get_PBG)(/*[out, retval]*/ IProfilePoint* *pVal) override;
	STDMETHOD(put_PBG)(/*[in]*/ IProfilePoint* newVal) override;
	STDMETHOD(get_L1)(/*[out,retval]*/ Float64* pVal) override;
	STDMETHOD(put_L1)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_L2)(/*[out,retval]*/ Float64* pVal) override;
	STDMETHOD(put_L2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_BVC)(/*[out, retval]*/ IProfilePoint* *pVal) override;
	STDMETHOD(get_EVC)(/*[out, retval]*/ IProfilePoint* *pVal) override;

   // IProfileElement
   //STDMETHOD(Clone)(IProfileElement** clone) override;
	STDMETHOD(get_Profile)(IProfile** pVal) override;
	STDMETHOD(put_Profile)(IProfile* newVal) override;
	STDMETHOD(GetStartPoint)(IProfilePoint** ppPoint) override;
   STDMETHOD(GetEndPoint)(IProfilePoint** ppPoint) override;
   STDMETHOD(GetLength)(Float64* pLength) override;
   STDMETHOD(ComputeGradeAndElevation)(VARIANT varStation, Float64* pGrade, Float64* pElevation) override;

private:
   std::shared_ptr<WBFL::COGO::VerticalCurve> m_Curve; // implementation object
	IProfile* m_pProfile; // weak pointer to actual COM parent
};

#endif //__VerticalCurve_H_

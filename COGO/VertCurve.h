///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVertCurve
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(Clone)(/*[out,retval]*/ IVertCurve* *clone);
	STDMETHOD(get_A)(/*[out,retval]*/Float64* a);
	STDMETHOD(get_K)(/*[out,retval]*/Float64* k);
	STDMETHOD(get_H)(/*[out,retval]*/Float64* h);
   STDMETHOD(get_E)(/*[[in]*/Float64 t,/*[out,retval]*/Float64* e);
	STDMETHOD(Grade)(/*[in]*/ VARIANT varStation,/*[out,retval]*/Float64* grade);
	STDMETHOD(Elevation)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ Float64* elev);
	STDMETHOD(get_HighPoint)(/*[out, retval]*/ IProfilePoint* *pVal);
	STDMETHOD(get_LowPoint)(/*[out, retval]*/ IProfilePoint* *pVal);
	STDMETHOD(get_ExitGrade)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_EntryGrade)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_PFG)(/*[out, retval]*/ IProfilePoint* *pVal);
	STDMETHOD(putref_PFG)(/*[in]*/ IProfilePoint* newVal);
	STDMETHOD(get_PVI)(/*[out, retval]*/ IProfilePoint* *pVal);
	STDMETHOD(putref_PVI)(/*[in]*/ IProfilePoint* newVal);
	STDMETHOD(get_PBG)(/*[out, retval]*/ IProfilePoint* *pVal);
	STDMETHOD(putref_PBG)(/*[in]*/ IProfilePoint* newVal);
	STDMETHOD(get_L1)(/*[out,retval]*/ Float64* pVal);
	STDMETHOD(put_L1)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_L2)(/*[out,retval]*/ Float64* pVal);
	STDMETHOD(put_L2)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_BVC)(/*[out, retval]*/ IProfilePoint* *pVal);
	STDMETHOD(get_EVC)(/*[out, retval]*/ IProfilePoint* *pVal);
   STDMETHOD(get_ProfilePointFactory)(/*[out,retval]*/IProfilePointFactory* *factory);
   STDMETHOD(putref_ProfilePointFactory)(/*[in]*/IProfilePointFactory* factory);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// IProfilePointEvents
public:
	STDMETHOD(OnProfilePointChanged)(IProfilePoint* pp);

private:
   CComPtr<IProfilePointFactory> m_Factory;
   CComPtr<IProfilePoint> m_PBG;
   CComPtr<IProfilePoint> m_PVI;
   CComPtr<IProfilePoint> m_PFG;
   DWORD m_dwPBG, m_dwPVI, m_dwPFG; // event cookies
   Float64 m_L1, m_L2; // Half-length of vert curve

   HRESULT IsValid(); // return S_OK if the curve is valid
   void MyAdvise(IProfilePoint* pp,DWORD* pdwCookie);
   void MyUnadvise(IProfilePoint* pp,DWORD dwCookie);

   void TransitionPoint(IStation* *sta,Float64* elev,Float64* grade);
};

#endif //__VERTCURVE_H_

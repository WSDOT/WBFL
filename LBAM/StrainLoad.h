///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// StrainLoad.h : Declaration of the CStrainLoad

#ifndef __STRAINLOAD_H_
#define __STRAINLOAD_H_

#include "resource.h"       // main symbols
#include "LoadCP.h"

/////////////////////////////////////////////////////////////////////////////
// CStrainLoad
class ATL_NO_VTABLE CStrainLoad : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CStrainLoad,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CStrainLoad, &CLSID_StrainLoad>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CStrainLoad>,
	public IStrainLoad,
   public IPersistImpl<CStrainLoad>,
	public IStructuredStorage2,
   public IObjectSafetyImpl<CStrainLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDStrainLoadEvents< CStrainLoad >
{
public:
   CStrainLoad():
   m_MemberID(-1),
   m_MemberType(mtUndefined),
   m_AxialStrain(0.0),
   m_CurvatureStrain(0.0),
   m_StartLocation(0.0),
   m_EndLocation(0.0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRAINLOAD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrainLoad)
	COM_INTERFACE_ENTRY(IStrainLoad)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CStrainLoad)
CONNECTION_POINT_ENTRY(IID_IStrainLoadEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// IStrainLoad
public:
	STDMETHOD(Clone)(/*[out,retval]*/IStrainLoad** clone) override;
   STDMETHOD(get_StartLocation)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_StartLocation)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EndLocation)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EndLocation)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_CurvatureStrain)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_CurvatureStrain)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_AxialStrain)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_AxialStrain)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_MemberID)(/*[out, retval]*/ MemberIDType *pVal) override;
	STDMETHOD(put_MemberID)(/*[in]*/ MemberIDType newVal) override;
	STDMETHOD(get_MemberType)(/*[out, retval]*/ MemberType *pVal) override;
	STDMETHOD(put_MemberType)(/*[in]*/ MemberType newVal) override;

protected:
   MemberType    m_MemberType;
   MemberIDType  m_MemberID;
   Float64       m_AxialStrain;
   Float64       m_CurvatureStrain;
   Float64       m_StartLocation;
   Float64       m_EndLocation;
};

#endif //__STRAINLOAD_H_

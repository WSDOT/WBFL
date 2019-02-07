///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2019  Washington State Department of Transportation
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

// SegmentCrossSection.h : Declaration of the CCrossSection

#ifndef __CROSSSECTION_H_
#define __CROSSSECTION_H_

#include "resource.h"       // main symbols
#include "CrossSectionCP.h"

/////////////////////////////////////////////////////////////////////////////
// CCrossSection
class ATL_NO_VTABLE CSegmentCrossSection : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegmentCrossSection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSegmentCrossSection, &CLSID_SegmentCrossSection>,
	public ISupportErrorInfo, 
	public IConnectionPointContainerImpl<CSegmentCrossSection>,
	public ISegmentCrossSection,
   public IPersistImpl<CSegmentCrossSection>,
	public IStructuredStorage2,
	public CProxyDSegmentCrossSectionEvents< CSegmentCrossSection >,
   public IObjectSafetyImpl<CSegmentCrossSection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStressPointsEvents
{
public:
   CSegmentCrossSection():
   m_EAForce(1.0),
   m_EIForce(1.0),
   m_EADefl(1.0),
   m_EIDefl(1.0),
   m_Thermal(0.0),
   m_Depth(1.0)
	{
      m_StressPointsCookie = 0;
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_CROSSSECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSegmentCrossSection)
	COM_INTERFACE_ENTRY(ISegmentCrossSection)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IStressPointsEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSegmentCrossSection)
CONNECTION_POINT_ENTRY(IID_ISegmentCrossSectionEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISegmentCrossSection
public:
	STDMETHOD(Clone)(/*[out]*/ISegmentCrossSection** crosssection) override;
	STDMETHOD(GetStiffness)(/*[out]*/Float64* EAForce, /*[out]*/Float64* EIForce, /*[out]*/Float64* EADefl, /*[out]*/Float64* EIDefl) override;
	STDMETHOD(SetStiffness)(/*[in]*/Float64 EAForce, /*[in]*/Float64 EIForce, /*[in]*/Float64 EADefl, /*[in]*/Float64 EIDefl) override;
	STDMETHOD(get_StressPoints)(/*[out, retval]*/ IStressPoints* *pVal) override;
	STDMETHOD(putref_StressPoints)(/*[in]*/ IStressPoints* newVal) override;
	STDMETHOD(get_ThermalCoeff)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_ThermalCoeff)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EIDefl)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EIDefl)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EADefl)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EADefl)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EIForce)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EIForce)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EAForce)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EAForce)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Depth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Depth)(/*[in]*/ Float64 newVal) override;

// IStressPointsEvents
   STDMETHOD(OnStressPointsChanged)(/*[in]*/CollectionIndexType index) override;
   STDMETHOD(OnStressPointsAdded)(/*[in]*/CollectionIndexType index) override;
   STDMETHOD(OnStressPointsRemoved)(/*[in]*/CollectionIndexType index) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

protected:
   Float64 m_EAForce;
   Float64 m_EIForce;
   Float64 m_EADefl;
   Float64 m_EIDefl;
   Float64 m_Thermal;
   Float64 m_Depth;

   CComPtr<IStressPoints> m_StressPoints;
   DWORD m_StressPointsCookie;
};

#endif //__CROSSSECTION_H_

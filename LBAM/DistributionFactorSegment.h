///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
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

// DistributionFactorSegment.h : Declaration of the CDistributionFactorSegment

#ifndef __DISTRIBUTIONFACTORSEGMENT_H_
#define __DISTRIBUTIONFACTORSEGMENT_H_

#include "resource.h"       // main symbols
#include "LBAMCP.h"

/////////////////////////////////////////////////////////////////////////////
// CDistributionFactorSegment
class ATL_NO_VTABLE CDistributionFactorSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDistributionFactorSegment, &CLSID_DistributionFactorSegment>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CDistributionFactorSegment>,
	public IDistributionFactorSegment,
   public IPersistImpl<CDistributionFactorSegment>,
	public IStructuredStorage2,
	public IDistributionFactorEvents,
   public IObjectSafetyImpl<CDistributionFactorSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDDistributionFactorSegmentEvents< CDistributionFactorSegment >
{
public:
   CDistributionFactorSegment():
   m_Length(0)
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_DISTRIBUTIONFACTORSEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDistributionFactorSegment)
	COM_INTERFACE_ENTRY(IDistributionFactorSegment)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IDistributionFactorEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDistributionFactorSegment)
CONNECTION_POINT_ENTRY(IID_IDistributionFactorSegmentEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IDistributionFactorSegment
public:
	STDMETHOD(Clone)(/*[out]*/IDistributionFactorSegment** clone) override;
	STDMETHOD(get_DistributionFactor)(/*[out, retval]*/ IDistributionFactor* *pVal) override;
	STDMETHOD(putref_DistributionFactor)(/*[in]*/ IDistributionFactor* newVal) override;
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Length)(/*[in]*/ Float64 newVal) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

   // IDistributionFactorEvents
	STDMETHOD(OnDistributionFactorChanged)(IDistributionFactor* pdf) override;

protected:
   Float64 m_Length;
   CComPtr<IDistributionFactor> m_pDistributionFactor;
   DWORD m_DistributionFactorCookie;

};

#endif //__DISTRIBUTIONFACTORSEGMENT_H_

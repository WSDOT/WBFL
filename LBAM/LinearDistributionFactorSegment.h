///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2024  Washington State Department of Transportation
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

// LinearDistributionFactorSegment.h : Declaration of the CLinearDistributionFactorSegment

#ifndef __LINEARDISTRIBUTIONFACTORSEGMENT_H_
#define __LINEARDISTRIBUTIONFACTORSEGMENT_H_

#include "resource.h"       // main symbols
#include "LBAMCP.h"

/////////////////////////////////////////////////////////////////////////////
// CLinearDistributionFactorSegment
class ATL_NO_VTABLE CLinearDistributionFactorSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLinearDistributionFactorSegment, &CLSID_LinearDistributionFactorSegment>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLinearDistributionFactorSegment>,
	public ILinearDistributionFactorSegment,
   public IPersistImpl<CLinearDistributionFactorSegment>,
	public IStructuredStorage2,
	public IDistributionFactorEvents,
   public IObjectSafetyImpl<CLinearDistributionFactorSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDDistributionFactorSegmentEvents< CLinearDistributionFactorSegment >
{
public:
   CLinearDistributionFactorSegment():
   m_Length(0)
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_LINEARDISTRIBUTIONFACTORSEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLinearDistributionFactorSegment)
   COM_INTERFACE_ENTRY(ILinearDistributionFactorSegment)
	COM_INTERFACE_ENTRY(IDistributionFactorSegment)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IDistributionFactorEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLinearDistributionFactorSegment)
CONNECTION_POINT_ENTRY(IID_IDistributionFactorSegmentEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILinearDistributionFactorSegment
public:
	STDMETHOD(Clone)(/*[out]*/IDistributionFactorSegment** clone) override;
   STDMETHOD(CreateDistributionFactor)(/*[in]*/ Float64 dist,/*[out,retval]*/IDistributionFactor** pFactor) override;
	STDMETHOD(get_DistributionFactor)(/*[out, retval]*/ IDistributionFactor* *pVal) override;
	STDMETHOD(putref_DistributionFactor)(/*[in]*/ IDistributionFactor* newVal) override;
	STDMETHOD(get_EndDistributionFactor)(/*[out, retval]*/ IDistributionFactor* *pVal) override;
	STDMETHOD(putref_EndDistributionFactor)(/*[in]*/ IDistributionFactor* newVal) override;
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Length)(/*[in]*/ Float64 newVal) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

   // IDistributionFactorEvents
	STDMETHOD(OnDistributionFactorChanged)(IDistributionFactor* pdf) override;

protected:
   Float64 m_Length;
   CComPtr<IDistributionFactor> m_pStartDistributionFactor;
   CComPtr<IDistributionFactor> m_pEndDistributionFactor;
   DWORD m_StartDistributionFactorCookie;
   DWORD m_EndDistributionFactorCookie;

};

#endif //__LINEARDISTRIBUTIONFACTORSEGMENT_H_

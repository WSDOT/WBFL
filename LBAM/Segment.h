///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2020  Washington State Department of Transportation
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

// Segment.h : Declaration of the CSegment

#ifndef __SEGMENT_H_
#define __SEGMENT_H_

#include "resource.h"       // main symbols
#include "CrossSectionCP.h"
#include "LBAMUtils.h"

/////////////////////////////////////////////////////////////////////////////
// CSegment
class ATL_NO_VTABLE CSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSegment, &CLSID_Segment>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CSegment>,
   public IPersistImpl<CSegment>,
	public IStructuredStorage2,
	public ISegment,
	public CProxyDSegmentEvents< CSegment >,
   public IObjectSafetyImpl<CSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISegmentCrossSectionEvents
{
public:
   CSegment():
      m_Length(0)
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSegment)
	COM_INTERFACE_ENTRY(ISegment)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ISegmentCrossSectionEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSegment)
CONNECTION_POINT_ENTRY(IID_ISegmentEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISegment
public:
	STDMETHOD(Clone)(/*[out]*/ISegment** clone) override;
	STDMETHOD(get_SegmentCrossSection)(/*[out, retval]*/ ISegmentCrossSection* *pVal) override;
	STDMETHOD(putref_SegmentCrossSection)(/*[in]*/ ISegmentCrossSection* newVal) override;
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Length)(/*[in]*/ Float64 newVal) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

   // ISegmentCrossSectionEvents
	STDMETHOD(OnSegmentCrossSectionChanged)(ISegmentCrossSection* crossSection, ChangeType change) override;

protected:
   Float64 m_Length;
   CComPtr<ISegmentCrossSection> m_pSegmentCrossSection;
   DWORD m_SegmentCrossSectionCookie;
};

#endif //__SEGMENT_H_

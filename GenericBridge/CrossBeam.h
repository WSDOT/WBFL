///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

// CrossBeam.h : Declaration of the CCrossBeam

#ifndef __CROSSBEAM_H_
#define __CROSSBEAM_H_

#include "resource.h"       // main symbols
#include "Segments.h"
#include "GenericBridgeCP.h"
#include "ColumnSpacing.h"

/////////////////////////////////////////////////////////////////////////////
// CCrossBeam
class ATL_NO_VTABLE CCrossBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCrossBeam, &CLSID_CrossBeam>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CCrossBeam>,
	public ICrossBeam,
   public ISegmentItemEvents,
   public ISegmentMeasure,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CCrossBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public CSegmentsOwner,
	public CProxyDCrossBeamEvents< CCrossBeam >
{
public:
	CCrossBeam()
	{
      m_bIgnoreSegmentEvents = true;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetColumnSpacing(CColumnSpacing* pSpacing)
   {
      m_pColumnSpacing = pSpacing;
   }

   void SetBridge(IGenericBridge* pBridge)
   {
      m_pBridge = pBridge;
      m_pSegments->SetBridge(pBridge);
   }

   STDMETHOD(Clone)(/*[out,retval]*/ICrossBeam* *clone);
   CSegments* GetSegments() { return m_pSegments; }

DECLARE_REGISTRY_RESOURCEID(IDR_CROSSBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCrossBeam)
	COM_INTERFACE_ENTRY(ICrossBeam)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(ISegmentItemEvents)
   COM_INTERFACE_ENTRY(ISegmentMeasure)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CCrossBeam)
CONNECTION_POINT_ENTRY(IID_ICrossBeamEvents)
END_CONNECTION_POINT_MAP()

private:
   VARIANT_BOOL m_bFractional;
   VARIANT_BOOL m_bSymmetrical;
   bool m_bIgnoreSegmentEvents;
   CSegments* m_pSegments;
   CColumnSpacing* m_pColumnSpacing;
   IGenericBridge* m_pBridge; // This is a weak referenece to avoid a circular referece

// virtual methods for CSegmentsOwner
   virtual HRESULT SetUpConnection(ISegmentItem* pCp, unsigned long* pcookie);
   virtual void BreakConnection(ISegmentItem* pCp, unsigned long cookie);
   virtual void OnSegmentsChanged(CSegments* psegments);
   virtual Float64 Length();

   HRESULT AdviseSegmentItem(ISegmentItem* segItem,DWORD* pdwCookie);
   HRESULT UnadviseSegmentItem(ISegmentItem* segItem,DWORD dwCookie);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISegmentMeasure
public:
	STDMETHOD(IsFractional)();

// ICrossBeam
public:
   STDMETHOD(get_Length)(/*[out,retval]*/ Float64* length);
   STDMETHOD(AddSegment)(/*[in]*/ISegment* segment);
   STDMETHOD(InsertSegment)(/*[in]*/ CollectionIndexType idx,/*[in]*/ISegment* segment);
   STDMETHOD(RemoveSegment)(/*[in]*/ CollectionIndexType idx);
   STDMETHOD(RemoveSegments)();
   STDMETHOD(get_Segment)(/*[in]*/ CollectionIndexType idx, /*[out,retval]*/ ISegment* *segment);
   STDMETHOD(get_SegmentCount)(/*[out,retval]*/ CollectionIndexType* count);
   STDMETHOD(get_SegmentLength)(/*[out,retval]*/ Float64* length);
   STDMETHOD(CopySegmentTo)(/*[in]*/ CollectionIndexType fromidx,/*[in]*/ CollectionIndexType toIdx);
   STDMETHOD(MoveSegmentTo)(/*[in]*/ CollectionIndexType fromIdx,/*[in]*/ CollectionIndexType toIdx);
   STDMETHOD(ReverseSegments)();
   STDMETHOD(get_Fractional)(/*[out,retval]*/ VARIANT_BOOL* bFractional);
   STDMETHOD(put_Fractional)(/*[in]*/ VARIANT_BOOL bFractional);
   STDMETHOD(get_Symmetrical)(/*[out,retval]*/ VARIANT_BOOL* bSymmetrical);
   STDMETHOD(put_Symmetrical)(/*[in]*/ VARIANT_BOOL bSymmetrical);
	STDMETHOD(GetMemberSegments)(/*[out,retval]*/ IFilteredSegmentCollection **ppSeg);
	STDMETHOD(GetSegmentForMemberLocation)(/*[in]*/ Float64 location,/*[out]*/Float64* dist,/*[out]*/ ISegmentItem **ppSeg);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

// ISegmentItemEvents
public:
	STDMETHOD(OnSegmentItemChanged)(ISegmentItem* item)
	{
      if ( !m_bIgnoreSegmentEvents )
         Fire_OnCrossBeamChanged(this);

      return S_OK;
	}
};

#endif //__CROSSBEAM_H_

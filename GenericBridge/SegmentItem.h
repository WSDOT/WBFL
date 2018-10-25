///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// SegmentItem.h : Declaration of the CSegmentItem

#ifndef __SEGMENTITEM_H_
#define __SEGMENTITEM_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"

class CSegments;
/////////////////////////////////////////////////////////////////////////////
// CSegmentItem
class ATL_NO_VTABLE CSegmentItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegmentItem,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSegmentItem, &CLSID_SegmentItem>,
	public ISupportErrorInfo,
	public ISegmentItem,
	public CProxyDSegmentItemEvents< CSegmentItem >,
	public IConnectionPointContainerImpl<CSegmentItem>,
	public ISegmentEvents
{
public:
   friend CSegments;

	CSegmentItem()
	{
	}

   void FinalRelease();
	STDMETHOD(PutRefSegment)(/*[in]*/ ISegment* pVal);

DECLARE_REGISTRY_RESOURCEID(IDR_SEGMENTITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSegmentItem)
	COM_INTERFACE_ENTRY(ISegmentItem)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	
   COM_INTERFACE_ENTRY(ISegmentEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSegmentItem)
CONNECTION_POINT_ENTRY(IID_ISegmentItemEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISegmentItem
public:
	STDMETHOD(get_Segment)(/*[out, retval]*/ ISegment* *pVal);
//	STDMETHOD(putref_Segment)(/*[in]*/ ISegment* pVal);
	STDMETHOD(get_RelPosition)(/*[out, retval]*/ CollectionIndexType *pVal);
//   STDMETHOD(Clone)(ISegmentItem** pclone);

// ISegmentEvents
	STDMETHOD(OnSegmentChanged)(ISegment * Segment)
	{
      Fire_OnSegmentItemChanged(this);
      return S_OK;
	}

protected:
   long     m_RelPosition;
   CComPtr<ISegment> m_Segment;
   DWORD m_dwCookie;

   HRESULT AdviseSegment();
   HRESULT UnadviseSegment();
};

#endif //__SEGMENTITEM_H_

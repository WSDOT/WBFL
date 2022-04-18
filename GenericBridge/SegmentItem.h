///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// SegmentItem.h : Declaration of the CSegmentItem

#ifndef __SEGMENTITEM_H_
#define __SEGMENTITEM_H_

#include "resource.h"       // main symbols

class CSegments;
/////////////////////////////////////////////////////////////////////////////
// CSegmentItem
class ATL_NO_VTABLE CSegmentItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegmentItem,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSegmentItem, &CLSID_SegmentItem>,
	public ISupportErrorInfo,
	public ISegmentItem
{
public:
   friend CSegments;

	CSegmentItem()
	{
	}

   void FinalRelease();
	HRESULT PutRefSegment(/*[in]*/ ISegment* pVal);

DECLARE_REGISTRY_RESOURCEID(IDR_SEGMENTITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSegmentItem)
	COM_INTERFACE_ENTRY(ISegmentItem)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISegmentItem
public:
	STDMETHOD(get_Segment)(/*[out, retval]*/ ISegment* *pVal) override;
//	STDMETHOD(putref_Segment)(/*[in]*/ ISegment* pVal) override;
	STDMETHOD(get_RelPosition)(/*[out, retval]*/ CollectionIndexType *pVal) override;
//   STDMETHOD(Clone)(ISegmentItem** pclone) override;

protected:
   CollectionIndexType     m_RelPosition;
   CComPtr<ISegment> m_Segment;
};

#endif //__SEGMENTITEM_H_

///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

// SegmentItem.cpp : Implementation of CSegmentItem
#include "stdafx.h"
#include "SegmentItem.h"
#include "WBFLGenericBridge.h"
#include "Segment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSegmentItem

STDMETHODIMP CSegmentItem::InterfaceSupportsErrorInfo(REFIID riid)
{

	static const IID* arr[] = 
	{
		&IID_ISegmentItem
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CSegmentItem::FinalRelease()
{
}

HRESULT CSegmentItem::PutRefSegment(ISegment *newVal)
{
	CHECK_IN(newVal);
   m_Segment = newVal;
	return S_OK;
}

STDMETHODIMP CSegmentItem::get_RelPosition(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_RelPosition;
	return S_OK;
}

STDMETHODIMP CSegmentItem::get_Segment(ISegment **pVal)
{
   CHECK_RETOBJ(pVal);
	*pVal = m_Segment;
   (*pVal)->AddRef();

	return S_OK;
}

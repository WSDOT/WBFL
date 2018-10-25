///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// CogoInfo.cpp : Implementation of CCogoInfo
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "CogoInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCogoInfo

STDMETHODIMP CCogoInfo::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICogoInfo
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCogoInfo::get_GirderLineID(SpanIndexType spanIdx,GirderIndexType gdrIdx,CogoElementKey *pVal)
{
   CHECK_RETVAL(pVal);
   return ::GB_GetGirderLineId(spanIdx,gdrIdx,pVal);
}

STDMETHODIMP CCogoInfo::get_PierGirderIntersectionPointID(PierIndexType pierIdx,GirderIndexType gdrIdx,PositionType posType,CogoElementKey *pVal)
{
   CHECK_RETVAL(pVal);
   return ::GB_GetPierGirderPointId(pierIdx,gdrIdx,posType,pVal);
}

STDMETHODIMP CCogoInfo::get_BearingGirderIntersectionPointID(PierIndexType pierIdx,GirderIndexType gdrIdx,PositionType posType,CogoElementKey *pVal)
{
   CHECK_RETVAL(pVal);
   return ::GB_GetBearingGirderPointId(pierIdx,gdrIdx,posType,pVal);
}

STDMETHODIMP CCogoInfo::get_GirderEndPointID(SpanIndexType spanIdx,GirderIndexType gdrIdx,EndType endType,CogoElementKey* pVal)
{
   CHECK_RETVAL(pVal);
   return ::GB_GetGirderEndPointId(spanIdx,gdrIdx,endType,pVal);
}

STDMETHODIMP CCogoInfo::get_PierPointID(PierIndexType pierIdx, PierPointType pointType, CogoElementKey *pVal)
{
   CHECK_RETVAL(pVal);

   HRESULT hr;
   CComPtr<IPierCollection> piers;
   m_pBridge->get_Piers(&piers);

   CComPtr<IPier> pier;
   hr = piers->get_Item(pierIdx,&pier);
   if ( FAILED(hr) )
      return hr;

   CComPtr<ISpan> prevSpan,nextSpan;
   pier->get_PrevSpan(&prevSpan);
   pier->get_NextSpan(&nextSpan);

   GirderIndexType nGirdersPrevSpan = 0;
   GirderIndexType nGirdersNextSpan = 0;

   if ( prevSpan )
      prevSpan->get_GirderCount(&nGirdersPrevSpan);

   if ( nextSpan )
      nextSpan->get_GirderCount(&nGirdersNextSpan);

   PositionType posType = (nGirdersPrevSpan < nGirdersNextSpan ? qcbAfter : qcbBefore);

   if ( pointType == pptLeft )
   {
      hr = get_PierGirderIntersectionPointID(pierIdx,0,posType,pVal);
   }
   else if ( pointType == pptRight )
   {
      hr = get_PierGirderIntersectionPointID(pierIdx,max(nGirdersPrevSpan,nGirdersNextSpan)-1,posType,pVal);
   }
   else if ( pointType == pptAlignment )
   {
      hr = ::GB_GetPierAlignmentPointId(pierIdx,pVal);
   }
   else if ( pointType == pptBridge )
   {
      hr = ::GB_GetPierCLBridgePointId(pierIdx,pVal);
   }

   return hr;
}

STDMETHODIMP CCogoInfo::get_AlignmentKey(CogoElementKey* alignmentKey)
{
   CHECK_RETVAL(alignmentKey);
   *alignmentKey = g_AlignmentKey;
   return S_OK;
}

STDMETHODIMP CCogoInfo::get_CLBridgeKey(CogoElementKey* clBridgeKey)
{
   CHECK_RETVAL(clBridgeKey);
   *clBridgeKey = g_CLBridgeKey;
   return S_OK;
}

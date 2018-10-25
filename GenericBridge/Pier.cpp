///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

// Pier.cpp : Implementation of CPier
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "Pier.h"
#include "ColumnLayout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPier
HRESULT CPier::FinalConstruct()
{
   HRESULT hr = m_PierImpl.FinalConstruct(this);
   if ( FAILED(hr) )
   {
      return hr;
   }

   m_CurbLineOffset[qcbLeft] = 0;
   m_CurbLineOffset[qcbRight] = 0;

   return S_OK;
}

void CPier::FinalRelease()
{
}

STDMETHODIMP CPier::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPier,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IPier
STDMETHODIMP CPier::get_DeckProfile(IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   return m_DeckProfile.CopyTo(ppPoints);
}

STDMETHODIMP CPier::get_DeckThickness(/*[out,retval]*/Float64* pTDeck)
{
   CHECK_RETVAL(pTDeck);
   *pTDeck = m_tDeck;
   return S_OK;
}

STDMETHODIMP CPier::get_CurbLineOffset(/*[in]*/DirectionType side,/*[in]*/CurbLineMeasurementType clMeasure,/*[out,retval]*/Float64* pCLO)
{
   CHECK_RETVAL(pCLO);
   *pCLO = m_CurbLineOffset[side];
   if ( clMeasure == clmPlaneOfPier )
   {
      CComPtr<IAngle> objSkew;
      get_SkewAngle(&objSkew);
      Float64 skew;
      objSkew->get_Value(&skew);
      *pCLO /= cos(skew);
   }
   return S_OK;
}

STDMETHODIMP CPier::get_CurbToCurbWidth(/*[in]*/CurbLineMeasurementType clMeasure,/*[out,retval]*/Float64* pWcc)
{
   CHECK_RETVAL(pWcc);
   Float64 LCO, RCO;
   get_CurbLineOffset(qcbLeft,clMeasure,&LCO);
   get_CurbLineOffset(qcbRight,clMeasure,&RCO);
   *pWcc = fabs(LCO) + fabs(RCO); // curb-curb width is unsigned, but offsets are signed... uses absolute value
   return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPierEx
STDMETHODIMP CPier::putref_DeckProfile(IPoint2dCollection* pPoints)
{
   CHECK_IN(pPoints);
   m_DeckProfile = pPoints;
   return S_OK;
}

STDMETHODIMP CPier::put_DeckThickness(/*[in]*/Float64 tDeck)
{
   m_tDeck = tDeck;
   return S_OK;
}

STDMETHODIMP CPier::put_CurbLineOffset(/*[in]*/DirectionType side,/*[in]*/Float64 clo)
{
   m_CurbLineOffset[side] = clo;
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CPier::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);
   load->BeginUnit(CComBSTR("Pier"));


   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CPier::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("Pier"),1.0);


   save->EndUnit();

   return S_OK;
}


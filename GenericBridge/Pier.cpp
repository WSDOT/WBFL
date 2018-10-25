///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

   m_DeckElevation = 0;
   m_CrownPointOffset = 0;
   m_Slope[qcbLeft] = 0;
   m_Slope[qcbRight] = 0;
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
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IPier
STDMETHODIMP CPier::get_DeckElevation(/*[out,retval]*/Float64* pElev)
{
   CHECK_RETVAL(pElev);
   *pElev = m_DeckElevation;
   return S_OK;
}

STDMETHODIMP CPier::get_DeckThickness(/*[out,retval]*/Float64* pTDeck)
{
   CHECK_RETVAL(pTDeck);
   *pTDeck = m_tDeck;
   return S_OK;
}

STDMETHODIMP CPier::get_CrownPointOffset(/*[out,retval]*/Float64* pCPO)
{
   CHECK_RETVAL(pCPO);
   *pCPO = m_CrownPointOffset;
   return S_OK;
}

STDMETHODIMP CPier::get_CrownSlope(/*[in]*/DirectionType side,/*[out,retval]*/Float64* pSlope)
{
   CHECK_RETVAL(pSlope);
   *pSlope = m_Slope[side];
   return S_OK;
}

STDMETHODIMP CPier::get_CurbLineOffset(/*[in]*/DirectionType side,/*[out,retval]*/Float64* pCLO)
{
   CHECK_RETVAL(pCLO);
   *pCLO = m_CurbLineOffset[side];
   return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPierEx
STDMETHODIMP CPier::put_DeckElevation(/*[in]*/Float64 elev)
{
   m_DeckElevation = elev;
   return S_OK;
}

STDMETHODIMP CPier::put_DeckThickness(/*[in]*/Float64 tDeck)
{
   m_tDeck = tDeck;
   return S_OK;
}

STDMETHODIMP CPier::put_CrownPointOffset(/*[in]*/Float64 cpo)
{
   m_CrownPointOffset = cpo;
   return S_OK;
}

STDMETHODIMP CPier::put_CrownSlope(/*[in]*/DirectionType side,/*[in]*/Float64 slope)
{
   m_Slope[side] = slope;
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


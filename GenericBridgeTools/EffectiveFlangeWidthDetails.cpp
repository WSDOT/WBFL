///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2023  Washington State Department of Transportation
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

// EffectiveFlangeWidthDetails.cpp : Implementation of CEffectiveFlangeWidthDetails
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "EffectiveFlangeWidthDetails.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEffectiveFlangeWidthDetails
HRESULT CEffectiveFlangeWidthDetails::FinalConstruct()
{
   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthDetails::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IEffectiveFlangeWidthDetails
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CEffectiveFlangeWidthDetails::put_EffectiveSpanLength(Float64 length)
{
   m_EffSpanLength = length;
   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthDetails::get_EffectiveSpanLength(Float64* length)
{
   CHECK_RETVAL(length);
   *length = m_EffSpanLength;
   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthDetails::put_SlabThickness(Float64 tSlab)
{
   m_SlabThickness = tSlab;
   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthDetails::get_SlabThickness(Float64* tSlab)
{
   CHECK_RETVAL(tSlab);
   *tSlab = m_SlabThickness;
   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthDetails::AddFlangeParameters(Float64 tWeb,Float64 wFlange,Float64 lSpacing,Float64 rSpacing)
{
   PARAMS params;
   params.WebThickness    = tWeb;
   params.TopFlangeThickness = wFlange;
   params.LeftSpacing        = lSpacing;
   params.RightSpacing       = rSpacing;

   m_FlangeParameters.push_back(params);

   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthDetails::get_FlangeCount(FlangeIndexType* nFlanges)
{
   CHECK_RETVAL(nFlanges);
   *nFlanges = m_FlangeParameters.size();
   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthDetails::GetFlangeParameters(FlangeIndexType flangeIdx,Float64* tWeb,Float64* wFlange,Float64* lSpacing,Float64* rSpacing)
{
   if ( flangeIdx < 0 || (FlangeIndexType)m_FlangeParameters.size() <= flangeIdx )
      return E_INVALIDARG;

   CHECK_RETVAL(tWeb);
   CHECK_RETVAL(wFlange);
   CHECK_RETVAL(lSpacing);
   CHECK_RETVAL(rSpacing);

   PARAMS& params = m_FlangeParameters[flangeIdx];

   *tWeb     = params.WebThickness;
   *wFlange  = params.TopFlangeThickness;
   *lSpacing = params.LeftSpacing;
   *rSpacing = params.RightSpacing;

   return S_OK;
}

STDMETHODIMP CEffectiveFlangeWidthDetails::EffectiveFlangeWidth(Float64* effFlangeWidth)
{
   CHECK_RETVAL(effFlangeWidth);

   Float64 w1 = 0.25*m_EffSpanLength;

   Float64 w2 = 0;
   Float64 w3 = 0;
   std::vector<PARAMS>::iterator iter;
   for ( iter = m_FlangeParameters.begin(); iter != m_FlangeParameters.end(); iter ++ )
   {
      PARAMS& params = *iter;
      w2 += 12*m_SlabThickness + Max(params.WebThickness, params.TopFlangeThickness /2);

      Float64 left,right;
      left = params.LeftSpacing;
      right = params.RightSpacing;
      w3 += left+right;
   }

   (*effFlangeWidth) = Min(w1,w2,w3);

   return S_OK;
}


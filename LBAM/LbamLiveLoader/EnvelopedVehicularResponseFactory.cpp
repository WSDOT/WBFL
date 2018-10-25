///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2018  Washington State Department of Transportation
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

// EnvelopedVehicularResponseFactory.cpp : Implementation of CEnvelopedVehicularResponseFactory
#include "stdafx.h"
#include "WBFLLBAMLiveLoader.h"
#include "EnvelopedVehicularResponseFactory.h"

#include "BruteForceVehicularResponse2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnvelopedVehicularResponseFactory

STDMETHODIMP CEnvelopedVehicularResponseFactory::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IEnvelopedVehicularResponseFactory
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CEnvelopedVehicularResponseFactory::CreateEnvelopedVehicularResponse(IEnvelopedVehicularResponse** pEVR)
{
	CHECK_RETOBJ(pEVR);

    CComObject<CBruteForceVehicularResponse2>* p_vehicular_response;
    HRESULT hr = CComObject<CBruteForceVehicularResponse2>::CreateInstance(&p_vehicular_response);
    (*pEVR) = p_vehicular_response;
	(*pEVR)->AddRef();

	return S_OK;
}

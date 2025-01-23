///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2025  Washington State Department of Transportation
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

// StressPoints.cpp : Implementation of CStressPoints
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "StressPoints.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStressPoints

STDMETHODIMP CStressPoints::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStressPoints
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStressPoints::OnStressPointChanged(/*[in]*/IStressPoint* pStressPoint)
{
   // find stress point in our collection - will only fire on first found
   IndexType i = 0;
   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      // could use COM identity (IUnknown), but seems like a waste.
      if (it->second.m_T == pStressPoint)
      {
         Fire_OnStressPointsChanged(i);
         return S_OK;
      }
      i++;
   }

   ATLASSERT(false); // all stress points that we watch should be in our container?
   return S_OK;
}

STDMETHODIMP CStressPoints::Clone(/*[out]*/IStressPoints* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new stress point collection and fill it up
   CComObject<CStressPoints>* pnew;
   HRESULT hr = CComObject<CStressPoints>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IStressPoints> spisps(pnew); // holder for reference count

   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      CComPtr<IStressPoint> isp;
      
      // deep clone
      hr = it->second.m_T->Clone(&isp);
      if (FAILED(hr))
         return hr;

      // this call sets up connection points
      hr = spisps->Add(isp);
      if (FAILED(hr))
         return hr;
   }

   return spisps.CopyTo(pColl);
}



///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
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

// GraphXyDataProvider.cpp : Implementation of CGraphXyDataProvider
#include "stdafx.h"
#include <WBFLDManipTools.h>
#include "DManipTools\DManipTools.h"
#include "GraphXyDataProvider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphXyDataProvider

CGraphXyDataProvider::CGraphXyDataProvider()
{
}


STDMETHODIMP CGraphXyDataProvider::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_iGraphXyDataProvider
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CGraphXyDataProvider::FinalConstruct()
{
   HRESULT hr;
   hr = m_DataSet.CoCreateInstance(CLSID_DataSet2d);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   hr = m_Factory.CoCreateInstance(CLSID_LegendEntry);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   return S_OK;
}

STDMETHODIMP_(void) CGraphXyDataProvider::get_DataSet(iDataSet2d* *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_DataSet.CopyTo(pVal);
}

STDMETHODIMP_(void) CGraphXyDataProvider::put_DataSet(iDataSet2d* newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_DataSet = newVal;
}

STDMETHODIMP_(void) CGraphXyDataProvider::get_DataPointFactory(iDataPointFactory* *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Factory.CopyTo(pVal);
}

STDMETHODIMP_(void) CGraphXyDataProvider::put_DataPointFactory(iDataPointFactory* newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Factory = newVal;
}


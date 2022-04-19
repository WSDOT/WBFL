///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// MassProperties.cpp : Implementation of CMassProperties
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "MassProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMassProperties

STDMETHODIMP CMassProperties::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IMassProperties
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CMassProperties::get_MassPerLength(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetMassPerLength();
	return S_OK;
}

STDMETHODIMP CMassProperties::put_MassPerLength(Float64 newVal)
{
   m_Props.SetMassPerLength(newVal);
	return S_OK;
}

STDMETHODIMP CMassProperties::AddProperties(IMassProperties *props)
{
   CHECK_IN(props);
   Float64 mpl;
   props->get_MassPerLength(&mpl);
   m_Props += mpl;
	return S_OK;
}

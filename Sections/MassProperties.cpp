///////////////////////////////////////////////////////////////////////
// Sections - Model bridge member cross sections
// Copyright © 1999-2019  Washington State Department of Transportation
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
#include "WBFLSections.h"
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
      &IID_IMassProperties,
      &IID_IStructuredStorage2,
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
   *pVal = m_MPL;
	return S_OK;
}

STDMETHODIMP CMassProperties::put_MassPerLength(Float64 newVal)
{
   m_MPL = newVal;
	return S_OK;
}

STDMETHODIMP CMassProperties::AddProperties(IMassProperties *props)
{
   CHECK_IN(props);
   Float64 mpl;
   props->get_MassPerLength(&mpl);
   m_MPL += mpl;
	return S_OK;
}

STDMETHODIMP CMassProperties::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CMassProperties::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("MassProperties"),1.0);
   pSave->put_Property(CComBSTR("MPL"),CComVariant(m_MPL));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CMassProperties::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("MassProperties"));

   pLoad->get_Property(CComBSTR("MPL"),&var);
   m_MPL = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

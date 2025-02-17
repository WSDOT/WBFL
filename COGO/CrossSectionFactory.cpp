///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright � 1999-2022  Washington State Department of Transportation
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

// CrossSectionFactory.cpp : Implementation of CCrossSectionFactory
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CrossSectionFactory.h"
#include "CrossSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCrossSectionFactory
STDMETHODIMP CCrossSectionFactory::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICrossSectionFactory,
		&IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCrossSectionFactory::get_Profile(IProfile* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pProfile )
   {
      (*pVal) = m_pProfile;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CCrossSectionFactory::putref_Profile(IProfile* newVal)
{
   m_pProfile = newVal;
   return S_OK;
}

STDMETHODIMP CCrossSectionFactory::CreateCrossSection(ICrossSection **pVal)
{
   CHECK_RETOBJ(pVal);
   CComObject<CCrossSection>* pCS;
   CComObject<CCrossSection>::CreateInstance(&pCS);

   (*pVal) = pCS;
   (*pVal)->AddRef();

   (*pVal)->putref_Profile(m_pProfile);

	return S_OK;
}

STDMETHODIMP CCrossSectionFactory::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CCrossSectionFactory::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("CrossSectionFactory"),1.0);
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCrossSectionFactory::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("CrossSectionFactory"));

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

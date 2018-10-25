///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// ProfilePointFactory.cpp : Implementation of CProfilePointFactory
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "ProfilePointFactory.h"
#include "ProfilePoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfilePointFactory

STDMETHODIMP CProfilePointFactory::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProfilePointFactory,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CProfilePointFactory::get_Profile(IProfile* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pProfile )
   {
      (*pVal) = m_pProfile;
      (*pVal)->AddRef();
   }
   return S_OK;
}

STDMETHODIMP CProfilePointFactory::putref_Profile(IProfile* newVal)
{
   CHECK_IN(newVal);
   m_pProfile = newVal;
   return S_OK;
}

STDMETHODIMP CProfilePointFactory::CreateProfilePoint(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);

   CComObject<CProfilePoint>* pPP;
   CComObject<CProfilePoint>::CreateInstance(&pPP);

   (*pVal) = pPP;
   (*pVal)->AddRef();

   (*pVal)->putref_Profile(m_pProfile);

	return S_OK;
}

STDMETHODIMP CProfilePointFactory::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CProfilePointFactory::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("ProfilePointFactory"),1.0);
   pSave->EndUnit();
   return S_OK;
}

STDMETHODIMP CProfilePointFactory::Load(IStructuredLoad2* pLoad)
{
   pLoad->BeginUnit(CComBSTR("ProfilePointFactory"));

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

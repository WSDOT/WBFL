///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// Size2d.cpp : Implementation of CSize2d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Size2d.h"
#include <Math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSize2d

STDMETHODIMP CSize2d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISize2d,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSize2d::get_Dx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Dx;

	return S_OK;
}

STDMETHODIMP CSize2d::put_Dx(Float64 newVal)
{
   m_Dx = newVal;

	return S_OK;
}

STDMETHODIMP CSize2d::get_Dy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Dy;

	return S_OK;
}

STDMETHODIMP CSize2d::put_Dy(Float64 newVal)
{
   m_Dy = newVal;

	return S_OK;
}

STDMETHODIMP CSize2d::get_Magnitude(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = sqrt(m_Dx*m_Dx + m_Dy*m_Dy);

	return S_OK;
}

STDMETHODIMP CSize2d::Scale(Float64 factor)
{
   m_Dx *= factor;
   m_Dy *= factor;

	return S_OK;
}

STDMETHODIMP CSize2d::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

STDMETHODIMP CSize2d::Dimensions(Float64* pDx,Float64* pDy)
{
   CHECK_RETVAL(pDx);
   CHECK_RETVAL(pDy);

   *pDx = m_Dx;
   *pDy = m_Dy;
   return S_OK;
}

// IPersist
STDMETHODIMP CSize2d::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CSize2d::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Size2d"),1.0);
   pSave->put_Property(CComBSTR("Dx"),CComVariant(m_Dx));
   pSave->put_Property(CComBSTR("Dy"),CComVariant(m_Dy));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CSize2d::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Size2d"));
   
   pLoad->get_Property(CComBSTR("Dx"),&var);
   m_Dx = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Dy"),&var);
   m_Dy = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2024  Washington State Department of Transportation
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
		&IID_ISize2d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSize2d::get_Dx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Size.Dx();

	return S_OK;
}

STDMETHODIMP CSize2d::put_Dx(Float64 newVal)
{
   m_Size.Dx() = newVal;

	return S_OK;
}

STDMETHODIMP CSize2d::get_Dy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Size.Dy();

	return S_OK;
}

STDMETHODIMP CSize2d::put_Dy(Float64 newVal)
{
   m_Size.Dy() = newVal;

	return S_OK;
}

STDMETHODIMP CSize2d::get_Magnitude(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Size.Magnitude();
	return S_OK;
}

STDMETHODIMP CSize2d::Scale(Float64 factor)
{
   m_Size *= factor;
	return S_OK;
}

STDMETHODIMP CSize2d::Clone(ISize2d** clone)
{
   CHECK_RETOBJ(clone);
   CComObject<CSize2d>* pClone;
   CComObject<CSize2d>::CreateInstance(&pClone);
   pClone->m_Size = m_Size;

   (*clone) = pClone;
   (*clone)->AddRef();
   return S_OK;
}

STDMETHODIMP CSize2d::Dimensions(Float64* pDx,Float64* pDy)
{
   CHECK_RETVAL(pDx);
   CHECK_RETVAL(pDy);

   std::tie(*pDx,*pDy) = m_Size.GetDimensions();
   return S_OK;
}

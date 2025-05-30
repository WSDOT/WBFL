///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2025  Washington State Department of Transportation
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

// Angle.cpp : Implementation of CAngle
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Angle.h"

#include <WBFLCogo\CogoHelpers.h>


/////////////////////////////////////////////////////////////////////////////
// CAngle

STDMETHODIMP CAngle::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAngle,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAngle::get_Value(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Angle->GetValue();
	return S_OK;
}

STDMETHODIMP CAngle::put_Value(Float64 newVal)
{
   m_Angle->SetValue(newVal);
	return S_OK;
}

STDMETHODIMP CAngle::get_Degree(long *pVal)
{
   CHECK_RETVAL(pVal);

   auto [d, m, s] = m_Angle->GetDMS();
   *pVal = d;

	return S_OK;
}

STDMETHODIMP CAngle::get_Minute(long *pVal)
{
   CHECK_RETVAL(pVal);

   auto [d, m, s] = m_Angle->GetDMS();
   *pVal = m;

	return S_OK;
}

STDMETHODIMP CAngle::get_Second(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   auto [d, m, s] = m_Angle->GetDMS();
   *pVal = s;

	return S_OK;
}

STDMETHODIMP CAngle::Normalize()
{
   m_Angle->Normalize();
	return S_OK;
}

STDMETHODIMP CAngle::FromDMS(long deg, long min, Float64 sec)
{
   try
   {
      m_Angle->SetDMS((unsigned)deg, (unsigned short)min, sec);
   }
   catch(...)
   {
      return E_INVALIDARG;
   }

	return S_OK;
}

STDMETHODIMP CAngle::FromString(BSTR bstrAngle)
{
   USES_CONVERSION;

   CHECK_IN(bstrAngle);

   std::_tstring str( OLE2T(bstrAngle) );
   try
   {
      m_Angle->FromString(str);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }
	return S_OK;
}

STDMETHODIMP CAngle::FromVariant(VARIANT varAngle)
{
   auto [hr,angle] = cogoUtil::AngleFromVariant(varAngle);
   if (FAILED(hr)) return hr;
   *m_Angle = angle;
   return S_OK;
}

STDMETHODIMP CAngle::Increment( VARIANT varAngle, IAngle* *pVal)
{
   CHECK_RETOBJ(pVal);

   auto [hr, inc_angle] = cogoUtil::AngleFromVariant(varAngle);
   if (FAILED(hr)) return hr;

   WBFL::COGO::Angle new_angle = *m_Angle;
   new_angle.Increment(inc_angle);

   return cogoUtil::CreateAngle(new_angle, pVal);
}

STDMETHODIMP CAngle::IncrementBy(VARIANT varAngle)
{
   auto [hr, inc_angle] = cogoUtil::AngleFromVariant(varAngle);
   if (FAILED(hr)) return hr;

   m_Angle->Increment(inc_angle);
	return S_OK;
}

STDMETHODIMP CAngle::Clone(IAngle* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CAngle>* pClone;
   CComObject<CAngle>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->SetAngle(m_Angle);

   return S_OK;
}

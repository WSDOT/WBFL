///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// Direction.cpp : Implementation of CDirection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Direction.h"

#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirection

STDMETHODIMP CDirection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDirection,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDirection::get_Azimuth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Direction.GetAzimuth();
   return S_OK;
}

STDMETHODIMP CDirection::get_Value(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Direction.GetValue();
	return S_OK;
}

STDMETHODIMP CDirection::put_Value(Float64 newVal)
{
   m_Direction.SetValue(newVal);
	return S_OK;
}

STDMETHODIMP CDirection::get_NSDirection(NSDirectionType *pVal)
{
   CHECK_RETVAL(pVal);
    
   auto [ns,d,m,s,ew] = m_Direction.GetDMS();

   *pVal = (ns == WBFL::COGO::Direction::NSDirection::North ? nsNorth : nsSouth);

	return S_OK;
}

STDMETHODIMP CDirection::put_NSDirection(NSDirectionType newVal)
{
   if (newVal != nsNorth && newVal != nsSouth) return E_INVALIDARG;

   auto [ns, d, m, s, ew] = m_Direction.GetDMS();

   ns = (newVal == nsNorth ? WBFL::COGO::Direction::NSDirection::North : WBFL::COGO::Direction::NSDirection::South);
   try { m_Direction.SetDMS(ns, d, m, s, ew); }
   catch (...) { return E_FAIL; }
   return S_OK;
}

STDMETHODIMP CDirection::get_EWDirection(EWDirectionType *pVal)
{
   CHECK_RETVAL(pVal);
   auto [ns, d, m, s, ew] = m_Direction.GetDMS();

   *pVal = (ew == WBFL::COGO::Direction::EWDirection::East ? ewEast : ewWest);

	return S_OK;
}

STDMETHODIMP CDirection::put_EWDirection(EWDirectionType newVal)
{
   if (newVal != ewEast && newVal != ewWest) return E_INVALIDARG;

   auto [ns, d, m, s, ew] = m_Direction.GetDMS();

   ew = (newVal == ewEast ? WBFL::COGO::Direction::EWDirection::East: WBFL::COGO::Direction::EWDirection::West);
   try { m_Direction.SetDMS(ns, d, m, s, ew); }
   catch (...) { return E_INVALIDARG; }
   return S_OK;
}

STDMETHODIMP CDirection::get_Degree(long *pVal)
{
   CHECK_RETVAL(pVal);
   
   auto [ns, d, m, s, ew] = m_Direction.GetDMS();

   *pVal = d;
   return S_OK;
}

STDMETHODIMP CDirection::put_Degree(long newVal)
{
   auto [ns, d, m, s, ew] = m_Direction.GetDMS();
   d = (unsigned short)newVal;
   try { m_Direction.SetDMS(ns, d, m, s, ew); }
   catch (...) { return E_INVALIDARG; }
   return S_OK;
}

STDMETHODIMP CDirection::get_Minute(long *pVal)
{
   CHECK_RETVAL(pVal);
   auto [ns, d, m, s, ew] = m_Direction.GetDMS();
   *pVal = m;

	return S_OK;
}

STDMETHODIMP CDirection::put_Minute(long newVal)
{
   auto [ns, d, m, s, ew] = m_Direction.GetDMS();
   m = (unsigned short)newVal;
   try { m_Direction.SetDMS(ns, d, m, s, ew); }
   catch (...) { return E_INVALIDARG; }
   return S_OK;
}

STDMETHODIMP CDirection::get_Second(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   auto [ns, d, m, s, ew] = m_Direction.GetDMS();
   *pVal = s;

	return S_OK;
}

STDMETHODIMP CDirection::put_Second(Float64 newVal)
{
   auto [ns, d, m, s, ew] = m_Direction.GetDMS();
   s = (unsigned short)newVal;
   try { m_Direction.SetDMS(ns, d, m, s, ew); }
   catch (...) { return E_INVALIDARG; }
   return S_OK;
}

STDMETHODIMP CDirection::IncrementBy(VARIANT varAngle)
{
   auto [hr, inc_angle] = cogoUtil::AngleFromVariant(varAngle);
   if (FAILED(hr)) return hr;

   m_Direction.Increment(inc_angle);

	return S_OK;
}

STDMETHODIMP CDirection::Increment(VARIANT varAngle, IDirection* *pVal)
{
   CHECK_RETOBJ(pVal);
   
   auto [hr, inc_angle] = cogoUtil::AngleFromVariant(varAngle);
   if (FAILED(hr)) return hr;

   auto new_direction = m_Direction.IncrementBy(inc_angle);

   CComObject<CDirection>* pDir;
   CComObject<CDirection>::CreateInstance(&pDir);
   pDir->SetDirection(new_direction);
   (*pVal) = pDir;
   (*pVal)->AddRef();

   return hr;
}

STDMETHODIMP CDirection::FromString(BSTR bstrDir)
{
   USES_CONVERSION;

   CHECK_IN(bstrDir);
   std::_tstring str(OLE2T(bstrDir));
   try
   {
      m_Direction.FromString(str);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }

	return S_OK;
}

STDMETHODIMP CDirection::FromDMS(NSDirectionType ns, long Degree, long Minute, Float64 Second, EWDirectionType ew)
{
   if (ns != nsNorth && ns != nsSouth) return E_INVALIDARG;
   if (ew != ewEast && ew != ewWest) return E_INVALIDARG;

   try
   {
      WBFL::COGO::Direction::NSDirection nsDir = (ns == nsNorth ? WBFL::COGO::Direction::NSDirection::North : WBFL::COGO::Direction::NSDirection::South);
      WBFL::COGO::Direction::EWDirection ewDir = (ew == ewEast ? WBFL::COGO::Direction::EWDirection::East: WBFL::COGO::Direction::EWDirection::West);
      m_Direction.SetDMS(nsDir,(unsigned short)Degree, (unsigned short)Minute, Second, ewDir);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }

   return S_OK;
}

STDMETHODIMP CDirection::FromAzimuth(Float64 azimuth)
{
   try
   {
      m_Direction.SetAzimuth(azimuth);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }

   return S_OK;
}

STDMETHODIMP CDirection::FromAzimuthEx(long Degree, long Minute, Float64 Second)
{
   try { m_Direction.SetAzimuth((short)Degree, (unsigned short)Minute, Second); }
   catch (...) { return E_INVALIDARG; }
   return S_OK;
}

STDMETHODIMP CDirection::FromVariant(VARIANT varDirection)
{
   auto [hr, direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;
   m_Direction = direction;
   return S_OK;
}

STDMETHODIMP CDirection::AngleBetween(IDirection* dir,IAngle** pVal)
{
   CHECK_IN(dir);
   CHECK_RETOBJ(pVal);

   auto direction = cogoUtil::GetInnerDirection(dir);

   auto angle = m_Direction.AngleBetween(direction);

   return cogoUtil::CreateAngle(angle, pVal);
}

STDMETHODIMP CDirection::Clone(IDirection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CDirection>* pClone;
   CComObject<CDirection>::CreateInstance(&pClone);
   pClone->SetDirection(m_Direction);
   (*clone) = pClone;
   (*clone)->AddRef();

   return S_OK;
}

STDMETHODIMP CDirection::IsEqual(IDirection* pDirection)
{
   CHECK_IN(pDirection);
   auto direction = cogoUtil::GetInnerDirection(pDirection);
   return m_Direction == direction ? S_OK : S_FALSE;
}

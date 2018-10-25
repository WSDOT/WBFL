///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
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

// AppUnitSystem.cpp : Implementation of CAppUnitSystem
#include "stdafx.h"
#include "WbflUnitServer.h"
#include "AppUnitSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAppUnitSystem
HRESULT CAppUnitSystem::FinalConstruct()
{
   HRESULT hr = S_OK;
   CComObject<CUnitServerImp>* pUnitServer;
   hr = CComObject<CUnitServerImp>::CreateInstance(&pUnitServer);
   if ( FAILED(hr) )
      return E_FAIL;

   m_pUnitServer = pUnitServer;

   CComObject<CDisplayUnitMgr2>* pDUM;
   hr = CComObject<CDisplayUnitMgr2>::CreateInstance(&pDUM);
   if ( FAILED(hr) )
      return E_FAIL;

   pDUM->Init(m_pUnitServer);
   m_pDispUnitMgr = pDUM;

   m_dwUnitServerCookie = AdviseSink(m_pUnitServer,IID_IUnitServerEventSink);
   m_dwDispUnitMgrCookie = AdviseSink(m_pDispUnitMgr,IID_IDisplayUnitMgrEvents);

   return S_OK;
}

void CAppUnitSystem::FinalRelease()
{
   UnadviseSink(m_pUnitServer,IID_IUnitServerEventSink,m_dwUnitServerCookie);
   UnadviseSink(m_pDispUnitMgr,IID_IDisplayUnitMgrEvents,m_dwDispUnitMgrCookie);
}

DWORD CAppUnitSystem::AdviseSink(IUnknown* pUnk,REFIID riid)
{
   DWORD dwCookie;
   CComPtr<IUnknown> p(pUnk);
   p.Advise(GetUnknown(),riid,&dwCookie);
   InternalRelease(); // Break circular reference
   return dwCookie;
}

void CAppUnitSystem::UnadviseSink(IUnknown* pUnk,REFIID riid,DWORD dwCookie)
{
   CComQIPtr<IConnectionPointContainer> pCPC(pUnk);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( riid, &pCP );
   InternalAddRef(); // Counteract call to InternalRelease() in AdviseSink
   pCP->Unadvise( dwCookie );
}

STDMETHODIMP CAppUnitSystem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAppUnitSystem
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAppUnitSystem::get_UnitServer(IUnitServer **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_pUnitServer;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CAppUnitSystem::get_DisplayUnitMgr(IDisplayUnitMgr2 **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_pDispUnitMgr;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CAppUnitSystem::ConvertToBaseUnits(Float64 value,VARIANT fromUnit,Float64* retval)
{
   CComPtr<IUnit> pUnit;
   CComQIPtr<IUnitConvert> convert(m_pUnitServer);
   CComQIPtr<IUnitConvert2> convert2(m_pUnitServer);
   HRESULT hr = S_OK;

   switch (fromUnit.vt)
   {
   case VT_BSTR:
      hr = convert->ConvertToBaseUnits(value,fromUnit.bstrVal,retval);
      break;

   case VT_UNKNOWN:
      fromUnit.punkVal->QueryInterface(&pUnit);
      hr = convert2->ConvertToBaseUnits(value,pUnit,retval);
      break;

   case VT_DISPATCH:
      fromUnit.pdispVal->QueryInterface(&pUnit);
      hr = convert2->ConvertToBaseUnits(value,pUnit,retval);
      break;

   default:
      hr = E_INVALIDARG;
   }

   return hr;
}

STDMETHODIMP CAppUnitSystem::ConvertFromBaseUnits(Float64 value,VARIANT toUnit,Float64* retval)
{
   CComPtr<IUnit> pUnit;
   CComQIPtr<IUnitConvert> convert(m_pUnitServer);
   CComQIPtr<IUnitConvert2> convert2(m_pUnitServer);
   HRESULT hr = S_OK;

   switch (toUnit.vt)
   {
   case VT_BSTR:
      hr = convert->ConvertFromBaseUnits(value,toUnit.bstrVal,retval);
      break;

   case VT_UNKNOWN:
      toUnit.punkVal->QueryInterface(&pUnit);
      hr = convert2->ConvertFromBaseUnits(value,pUnit,retval);
      break;

   case VT_DISPATCH:
      toUnit.pdispVal->QueryInterface(&pUnit);
      hr = convert2->ConvertFromBaseUnits(value,pUnit,retval);
      break;

   default:
      hr = E_INVALIDARG;
   }

   return hr;
}

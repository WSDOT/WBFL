///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// UnconfinedConcrete.cpp : Implementation of CUnconfinedConcrete
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "UnconfinedConcrete.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnconfinedConcrete

HRESULT CUnconfinedConcrete::FinalConstruct()
{
   HRESULT hr = m_UnitServer.CoCreateInstance(CLSID_UnitServer);
   if ( FAILED(hr) )
      return hr;

   m_Fc = 4.00; // ksi
   m_MinStrain = -0.0035;
   m_MaxStrain = 10.0;

   return S_OK;
}

void CUnconfinedConcrete::FinalRelease()
{
   m_UnitServer.Release();
}

STDMETHODIMP CUnconfinedConcrete::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUnconfinedConcrete,
      &IID_IStressStrain,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CUnconfinedConcrete::get_fc(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertToBaseUnits(m_Fc,CComBSTR("ksi"),pVal);

   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::put_fc(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) ) 
      return E_INVALIDARG;

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertFromBaseUnits(newVal,CComBSTR("ksi"),&newVal);

   if ( newVal < 3.0 || 16.0 < newVal )
      return E_INVALIDARG;

   m_Fc = newVal;

	return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::put_Name(BSTR name)
{
   m_bstrName = name;
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::get_Name(BSTR *name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::ComputeStress(Float64 strain,Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = 0;

   if ( 0 < strain )
      return S_OK;

   strain *= -1.0;

   Float64 n = 0.80 + m_Fc/2.500;
   Float64 k = 0.67 + m_Fc/9.000;
   Float64 Ec = GetEc();
   Float64 ec = m_Fc*n/(Ec*(n-1));

   Float64 e = strain/ec;
   if ( e < 1.0 )
      k = 1.00;

   if ( k < 1.00 )
      k = 1.00;

   Float64 f = m_Fc*(n*(e)/((n-1) + pow(e,n*k)));

   // The stress is in KSI, convert it to base units because that is what the caller expects
   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);
   convert->ConvertToBaseUnits(f,CComBSTR("ksi"),&f);

   *pVal = -f;

   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   *minStrain = m_MinStrain;
   *maxStrain = m_MaxStrain;
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);

   Float64 Ec = GetEc();
   Float64 n = 0.8 + m_Fc/2.5;

   (*strain) = -(m_Fc/Ec)*(n/(n-1));
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   Float64 Ec = GetEc();
   *pey = m_Fc/Ec;
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   Float64 Ec = GetEc();

   // The stress is in KSI, convert it to base units because that is what the caller expects
   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);
   convert->ConvertFromBaseUnits(Ec,CComBSTR("ksi"),&Ec);

   *pE = Ec;
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::get_UnitServer(IUnitServer** ppVal )
{
   CHECK_RETOBJ(ppVal);

   (*ppVal) = m_UnitServer;
   (*ppVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::putref_UnitServer(IUnitServer* pNewVal )
{
   CHECK_IN(pNewVal);

   m_UnitServer = pNewVal;
   return S_OK;
}

Float64 CUnconfinedConcrete::GetEc()
{
   return (40.000*sqrt(m_Fc*1000) + 1000.000);
}

///////////////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CUnconfinedConcrete::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("UnconfinedConcrete"),1.0);

   pSave->put_Property(CComBSTR("Fc"),CComVariant(m_Fc));
   pSave->put_Property(CComBSTR("MaxStrain"),CComVariant(m_MaxStrain));
   pSave->put_Property(CComBSTR("MinStrain"),CComVariant(m_MinStrain));

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("UnconfinedConcrete"));

   if ( FAILED(pLoad->get_Property(CComBSTR("Fc"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Fc = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("MaxStrain"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_MaxStrain = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("MinStrain"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_MinStrain = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

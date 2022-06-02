///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// UHPConcrete.cpp : Implementation of CUHPConcrete
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "UHPConcrete.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUHPConcrete

HRESULT CUHPConcrete::FinalConstruct()
{
   HRESULT hr = m_UnitServer.CoCreateInstance(CLSID_UnitServer);
   if ( FAILED(hr) )
      return hr;

   m_fc = 18.00; // ksi
   m_ecu = -0.0035; // negative for compression
   m_K1 = 1.0;
   m_alpha = 0.85;
   m_ftcr = 0.75; // ksi
   m_ftloc = 1.0; // ksi
   m_etloc = 0.0025;
   m_gamma = 0.85;

   return S_OK;
}

void CUHPConcrete::FinalRelease()
{
   m_UnitServer.Release();
}

STDMETHODIMP CUHPConcrete::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUHPConcrete,
      &IID_IStressStrain,
      &IID_IStructuredStorage2
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CUHPConcrete::get_fc(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertToBaseUnits(m_fc,CComBSTR("ksi"),pVal);

   return S_OK;
}

STDMETHODIMP CUHPConcrete::put_fc(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) ) 
      return E_INVALIDARG;

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertFromBaseUnits(newVal,CComBSTR("ksi"),&newVal);

   m_fc = newVal;

   ATLASSERT(18.0 <= m_fc); // 18 ksi is the minimum value for f'c, UHPC GS 1.1

	return S_OK;
}

STDMETHODIMP CUHPConcrete::get_ecu(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_ecu;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::put_ecu(Float64 newVal)
{
   if (0 <= newVal)
      return E_INVALIDARG; // compression is negative

   m_ecu = newVal;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::get_K1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_K1;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::put_K1(Float64 newVal)
{
   if (newVal <= 0)
      return E_INVALIDARG;

   m_K1 = newVal;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::get_alpha(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_alpha;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::put_alpha(Float64 newVal)
{
   if (newVal <= 0)
      return E_INVALIDARG;

   m_alpha = newVal;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::get_ftcr(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertToBaseUnits(m_ftcr, CComBSTR("ksi"), pVal);

   return S_OK;
}

STDMETHODIMP CUHPConcrete::put_ftcr(Float64 newVal)
{
   if (newVal < 0 || IsZero(newVal))
      return E_INVALIDARG;

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertFromBaseUnits(newVal, CComBSTR("ksi"), &newVal);

   m_ftcr = newVal;

   ATLASSERT(0.75 <= m_ftcr); // minimum value is 0.75 ksi, UHPC GS 1.1

   return S_OK;
}

STDMETHODIMP CUHPConcrete::get_ftloc(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertToBaseUnits(m_ftloc, CComBSTR("ksi"), pVal);

   return S_OK;
}

STDMETHODIMP CUHPConcrete::put_ftloc(Float64 newVal)
{
   if (newVal < 0 || IsZero(newVal))
      return E_INVALIDARG;

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertFromBaseUnits(newVal, CComBSTR("ksi"), &newVal);

   m_ftloc = newVal;

   return S_OK;
}

STDMETHODIMP CUHPConcrete::get_etloc(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_etloc;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::put_etloc(Float64 newVal)
{
   if (newVal <= 0)
      return E_INVALIDARG; // tension is positive

   m_etloc = newVal;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::get_gamma(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_gamma;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::put_gamma(Float64 newVal)
{
   if (newVal <= 0)
      return E_INVALIDARG;

   m_gamma = newVal;
   return S_OK;
}


STDMETHODIMP CUHPConcrete::put_Name(BSTR name)
{
   m_bstrName = name;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::get_Name(BSTR *name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}

STDMETHODIMP CUHPConcrete::ComputeStress(Float64 strain,Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   ATLASSERT(m_ftcr <= m_ftloc); // ft,loc must be greater or equal to f,trc, UHPC GS 1.1

   *pVal = 0;

   Float64 Ec = GetEc();

   HRESULT hr = S_OK;

   if (0 < strain)
   {
      // tension
      Float64 e_tcr = m_gamma*m_ftcr / Ec;
      if (strain < e_tcr)
      {
         // strain is less than cracking
         *pVal = strain*Ec;
      }
      else if (::IsLE(strain,m_etloc))
      {
         *pVal = (m_ftloc < 1.2*m_ftcr) ? m_gamma*m_ftcr : ::LinInterp(strain - e_tcr,m_gamma*m_ftcr,m_gamma*m_ftloc,m_etloc - e_tcr);
      }
      else
      {
         // beyond localization so can't carry any tension
         *pVal = (m_ftloc < 1.2 * m_ftcr) ? m_gamma * m_ftcr : ::LinInterp(strain - e_tcr, m_gamma * m_ftcr, m_gamma * m_ftloc, m_etloc - e_tcr);
         hr = S_FALSE;
      }
   }
   else
   {
      // compression
      strain = fabs(strain);
      Float64 e_cp = 1.0*m_alpha*m_fc / Ec;
      if (strain < e_cp)
      {
         *pVal = -strain * Ec;
      }
      else if (::IsLE(strain, -m_ecu))
      {
         *pVal = -1.0 * m_alpha * m_fc; // negative for compression
      }
      else
      {
         *pVal = -1.0 * m_alpha * m_fc;// 0.0; // beyond maximum strain
         hr = S_FALSE;
      }
   }

   // The stress is in KSI, convert it to base units because that is what the caller expects
   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);
   convert->ConvertToBaseUnits(*pVal,CComBSTR("ksi"),pVal);

   return hr;
}

STDMETHODIMP CUHPConcrete::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   *maxStrain = m_etloc;

   Float64 Ec = GetEc();
   Float64 e_cp = -1.0*m_alpha*m_fc / Ec;
   *minStrain = Min(e_cp, m_ecu); // using Min because compression strain is negative. we want value that is furthest from zero on a numberline. smaller negative values are further from zero.

   return S_OK;
}

STDMETHODIMP CUHPConcrete::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);

   Float64 Ec = GetEc();
   Float64 e_cp = -1.0*m_alpha*m_fc / Ec;
   (*strain) = e_cp;

   return S_OK;
}

STDMETHODIMP CUHPConcrete::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   Float64 Ec = GetEc();
   Float64 e_cp = -1.0*m_alpha*m_fc / Ec;
   *pey = e_cp;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   Float64 Ec = GetEc();

   // The stress is in KSI, convert it to base units because that is what the caller expects
   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);
   convert->ConvertToBaseUnits(Ec,CComBSTR("ksi"),&Ec);

   *pE = Ec;
   return S_OK;
}

STDMETHODIMP CUHPConcrete::get_UnitServer(IUnitServer** ppVal )
{
   CHECK_RETOBJ(ppVal);

   (*ppVal) = m_UnitServer;
   (*ppVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CUHPConcrete::putref_UnitServer(IUnitServer* pNewVal )
{
   CHECK_IN(pNewVal);

   m_UnitServer = pNewVal;
   return S_OK;
}

Float64 CUHPConcrete::GetEc()
{
   return 2500*m_K1*pow(m_fc,0.33);
}

///////////////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CUHPConcrete::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("UHPConcrete"),1.0);

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CUHPConcrete::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("UHPConcrete"));

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

// IPersist
STDMETHODIMP CUHPConcrete::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

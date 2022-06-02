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

// PCIUHPConcrete.cpp : Implementation of CPCIUHPConcrete
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "PCIUHPConcrete.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCIUHPConcrete

HRESULT CPCIUHPConcrete::FinalConstruct()
{
   HRESULT hr = m_UnitServer.CoCreateInstance(CLSID_UnitServer);
   if ( FAILED(hr) )
      return hr;

   m_fc = 17.4; // ksi

   return S_OK;
}

void CPCIUHPConcrete::FinalRelease()
{
   m_UnitServer.Release();
}

STDMETHODIMP CPCIUHPConcrete::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPCIUHPConcrete,
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

STDMETHODIMP CPCIUHPConcrete::get_fc(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertToBaseUnits(m_fc,CComBSTR("ksi"),pVal);

   return S_OK;
}

STDMETHODIMP CPCIUHPConcrete::put_fc(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) ) 
      return E_INVALIDARG;

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertFromBaseUnits(newVal,CComBSTR("ksi"),&newVal);

   m_fc = newVal;

   ATLASSERT(17.4 <= m_fc); // 17.4 ksi is the minimum value for f'c, PCI-UHPC GS

	return S_OK;
}


STDMETHODIMP CPCIUHPConcrete::put_Name(BSTR name)
{
   m_bstrName = name;
   return S_OK;
}

STDMETHODIMP CPCIUHPConcrete::get_Name(BSTR *name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}

STDMETHODIMP CPCIUHPConcrete::ComputeStress(Float64 strain,Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = 0;

   Float64 Ec = GetEc();

   if (0 < strain)
   {
      // tension
      Float64 e_tcr = 0.00012;
      if (strain < e_tcr)
      {
         // strain is less than cracking
         *pVal = strain*0.75/ e_tcr;
      }
      else if (::IsLE(strain,0.005))
      {
         *pVal = 0.75; // ksi
      }
      else
      {
         // beyond localization so can't carry any tension
         *pVal = 0.0; // ksi
      }
   }
   else
   {
      // compression
      strain = fabs(strain);
      *pVal = InRange(0.001, strain, 0.003) ? -0.85 * m_fc : -0.85*m_fc*strain/0.001;
   }

   // The stress is in KSI, convert it to base units because that is what the caller expects
   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);
   convert->ConvertToBaseUnits(*pVal, CComBSTR("ksi"), pVal);

   // NOTE: This stress-strain accomodates strains that are beyond the strain limit. For this reason,
   // we don't return S_FALSE for strains exceeding the limits. If we did, the moment capacity solver would
   // not converge.

   return S_OK;
}

STDMETHODIMP CPCIUHPConcrete::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   *maxStrain = 0.005;
   *minStrain = -0.003;

   return S_OK;
}

STDMETHODIMP CPCIUHPConcrete::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);

   (*strain) = -0.003;

   return S_OK;
}

STDMETHODIMP CPCIUHPConcrete::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = 0.00012;
   return S_OK;
}

STDMETHODIMP CPCIUHPConcrete::get_ModulusOfElasticity(Float64* pE)
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

STDMETHODIMP CPCIUHPConcrete::get_UnitServer(IUnitServer** ppVal )
{
   CHECK_RETOBJ(ppVal);

   (*ppVal) = m_UnitServer;
   (*ppVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CPCIUHPConcrete::putref_UnitServer(IUnitServer* pNewVal )
{
   CHECK_IN(pNewVal);

   m_UnitServer = pNewVal;
   return S_OK;
}

Float64 CPCIUHPConcrete::GetEc()
{
   return 2500*pow(m_fc,0.33);
}

///////////////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CPCIUHPConcrete::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("PCIUHPConcrete"),1.0);

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CPCIUHPConcrete::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("PCIUHPConcrete"));

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

// IPersist
STDMETHODIMP CPCIUHPConcrete::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

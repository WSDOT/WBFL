///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// UnconfinedConcrete.cpp : Implementation of CUnconfinedConcrete
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "UnconfinedConcrete.h"

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
   if (FAILED(hr))
      return hr;

   SetupUnits();

   return S_OK;
}

void CUnconfinedConcrete::FinalRelease()
{
}

void CUnconfinedConcrete::SetupUnits()
{
   CComPtr<IUnitTypes> unitTypes;
   m_UnitServer->get_UnitTypes(&unitTypes);

   CComPtr<IUnitType> unitType;
   unitTypes->get_Item(CComVariant("Pressure"), &unitType);

   CComPtr<IUnits> units;
   unitType->get_Units(&units);

   units->get_Item(CComVariant("ksi"), &m_ksiUnit);

   m_UnitServer.QueryInterface(&m_Convert);
}

void CUnconfinedConcrete::ClearUnits()
{
   m_ksiUnit.Release();
   m_Convert.Release();
   m_UnitServer.Release();
}

STDMETHODIMP CUnconfinedConcrete::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUnconfinedConcrete,
      &IID_IStressStrain,
      &IID_ISupportUnitServer
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CUnconfinedConcrete::get_fc(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Model.GetFc();
   *pVal = WBFL::Units::ConvertFromSysUnits(*pVal, WBFL::Units::Measure::KSI);
   m_Convert->ConvertToBaseUnits(*pVal,m_ksiUnit, pVal);
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::put_fc(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) ) 
      return E_INVALIDARG;

   // convert inbound value to KSI
   m_Convert->ConvertFromBaseUnits(newVal, m_ksiUnit, &newVal);
   // convert from KSI to the system units
   newVal = WBFL::Units::ConvertToSysUnits(newVal, WBFL::Units::Measure::KSI);
   m_Model.SetFc(newVal);

	return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::put_Name(BSTR name)
{
   USES_CONVERSION;
   m_Model.SetName(OLE2T(name));
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::get_Name(BSTR *name)
{
   USES_CONVERSION;
   CHECK_RETSTRING(name);
   *name = T2BSTR(m_Model.GetName().c_str());
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::ComputeStress(Float64 strain,Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   auto result = m_Model.ComputeStress(strain);
   *pVal = result.first;
   *pVal = WBFL::Units::ConvertFromSysUnits(*pVal, WBFL::Units::Measure::KSI);
   m_Convert->ConvertToBaseUnits(*pVal, m_ksiUnit, pVal);
   return (result.second == true ? S_OK : S_FALSE);
}

STDMETHODIMP CUnconfinedConcrete::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   m_Model.GetStrainLimits(minStrain, maxStrain);

   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   *strain = m_Model.GetStrainAtPeakStress();
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = m_Model.GetYieldStrain();
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   *pE = m_Model.GetModulusOfElasticity();
   *pE = WBFL::Units::ConvertFromSysUnits(*pE, WBFL::Units::Measure::KSI);
   m_Convert->ConvertToBaseUnits(*pE, m_ksiUnit, pE);
   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::get_UnitServer(IUnitServer** ppVal)
{
   CHECK_RETOBJ(ppVal);

   (*ppVal) = m_UnitServer;
   (*ppVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CUnconfinedConcrete::putref_UnitServer(IUnitServer* pNewVal)
{
   CHECK_IN(pNewVal);

   ClearUnits();
   m_UnitServer = pNewVal;
   SetupUnits();

   return S_OK;
}

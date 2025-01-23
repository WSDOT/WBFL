///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
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

// PSPowerFormula.cpp : Implementation of CPSPowerFormula
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "PSPowerFormula.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSPowerFormula

STDMETHODIMP CPSPowerFormula::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IPowerFormula,
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

HRESULT CPSPowerFormula::FinalConstruct()
{
   HRESULT hr = m_UnitServer.CoCreateInstance(CLSID_UnitServer);
   if (FAILED(hr))
      return hr;

   SetupUnits();
   return S_OK;
}

void CPSPowerFormula::FinalRelease()
{
}

void CPSPowerFormula::ClearUnits()
{
   m_ksiUnit.Release();
   m_Convert.Release();
   m_UnitServer.Release();
}

void CPSPowerFormula::SetupUnits()
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

STDMETHODIMP CPSPowerFormula::get_Grade(StrandGradeType* grade)
{
   CHECK_RETVAL(grade);
   *grade = (StrandGradeType)(m_Model.GetStrandGrade());
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::put_Grade(StrandGradeType grade)
{
   m_Model.SetStrandGrade((WBFL::Materials::StrandGrade)grade);
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_ProductionMethod(ProductionMethodType* type)
{
   CHECK_RETVAL(type);
   *type = (ProductionMethodType)m_Model.GetStrandType();
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::put_ProductionMethod(ProductionMethodType type)
{
   m_Model.SetStrandType((WBFL::Materials::StrandType)type);
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::put_ReductionFactor(Float64 factor)
{
   m_Model.SetScalingFactor(factor);
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_ReductionFactor(Float64* factor)
{
   CHECK_RETVAL(factor);
   *factor = m_Model.GetScalingFactor();
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::SetStrainLimits(Float64 eMin, Float64 eMax)
{
   m_Model.SetStrainLimits(eMin, eMax);
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::put_Name(BSTR name)
{
   USES_CONVERSION;
   m_Model.SetName(OLE2T(name));
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_Name(BSTR *name)
{
   USES_CONVERSION;
   CHECK_RETSTRING(name);
   *name = T2BSTR(m_Model.GetName().c_str());
   return S_OK;
}


STDMETHODIMP CPSPowerFormula::ComputeStress(Float64 strain,Float64* pVal)
{
   CHECK_RETVAL(pVal);

   auto [stress, bStrainWithinLimits] = m_Model.ComputeStress(strain);
   *pVal = stress;

   *pVal = WBFL::Units::ConvertFromSysUnits(*pVal, WBFL::Units::Measure::KSI);
   m_Convert->ConvertToBaseUnits(*pVal, m_ksiUnit, pVal);

   return (bStrainWithinLimits ? S_OK : S_FALSE);
}

STDMETHODIMP CPSPowerFormula::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   m_Model.GetStrainLimits(minStrain, maxStrain);

   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   *strain = m_Model.GetStrainAtPeakStress();
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = m_Model.GetYieldStrain();
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   *pE = m_Model.GetModulusOfElasticity();
   *pE = WBFL::Units::ConvertFromSysUnits(*pE, WBFL::Units::Measure::KSI);
   m_Convert->ConvertToBaseUnits(*pE, m_ksiUnit, pE);
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_UnitServer(IUnitServer** ppVal)
{
   CHECK_RETOBJ(ppVal);

   (*ppVal) = m_UnitServer;
   (*ppVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CPSPowerFormula::putref_UnitServer(IUnitServer* pNewVal)
{
   CHECK_IN(pNewVal);

   ClearUnits();
   m_UnitServer = pNewVal;
   SetupUnits();

   return S_OK;
}

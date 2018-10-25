///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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

// ManderModel.cpp : Implementation of CManderModel
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "ManderModel.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManderModel

HRESULT CManderModel::FinalConstruct()
{
   HRESULT hr = m_UnitServer.CoCreateInstance(CLSID_UnitServer);
   if ( FAILED(hr) )
      return hr;

   m_Fco = 4000.; // psi
   m_eco = 0.002;
   m_R = 5;

   m_MinStrain = -0.003;
   m_MaxStrain = 10.0;

   return S_OK;
}

void CManderModel::FinalRelease()
{
   m_UnitServer.Release();
}

STDMETHODIMP CManderModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IManderModel,
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

// IManderModel
STDMETHODIMP CManderModel::putref_Section(IManderModelSection* section)
{
   CHECK_IN(section);
   m_Section = section;
   return S_OK;
}

STDMETHODIMP CManderModel::get_Section(IManderModelSection** section)
{
   CHECK_RETOBJ(section);
   (*section) = m_Section;
   if ( *section )
      (*section)->AddRef();

   return S_OK;
}

STDMETHODIMP CManderModel::put_fco(Float64 fco)
{
   m_Fco = fco;
   return S_OK;
}

STDMETHODIMP CManderModel::get_fco(Float64* fco)
{
   CHECK_RETVAL(fco);
   *fco = m_Fco;
   return S_OK;
}

STDMETHODIMP CManderModel::put_eco(Float64 eco)
{
   m_eco = eco;
   return S_OK;
}

STDMETHODIMP CManderModel::get_eco(Float64* eco)
{
   CHECK_RETVAL(eco);
   *eco = m_eco;
   return S_OK;
}

STDMETHODIMP CManderModel::put_R(Float64 r)
{
   m_R = r;
   return S_OK;
}

STDMETHODIMP CManderModel::get_R(Float64* r)
{
   CHECK_RETVAL(r);
   *r = m_R;
   return S_OK;
}

// IStressStrain
STDMETHODIMP CManderModel::put_Name(BSTR name)
{
   m_bstrName = name;
   return S_OK;
}

STDMETHODIMP CManderModel::get_Name(BSTR *name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}

STDMETHODIMP CManderModel::ComputeStress(Float64 strain,Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = 0;

   if ( 0 < strain )
      return S_OK;

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   strain *= -1.0; // swap signs so we are working with positive strains

   Float64 Ec = GetEc();
   Float64 fr,fcc,ecc;
   GetConcreteParameters(fr,fcc,ecc);

   Float64 Esec = fcc/ecc;

   Float64 r = Ec/(Ec-Esec);
   Float64 x = strain/ecc;
   Float64 fc = fcc*x*r/(r-1+pow(x,r));

   // The stress is in PSI, convert it to base units because that is what the caller expects
   convert->ConvertToBaseUnits(fc,CComBSTR("psi"),&fc);

   *pVal = -fc;

   return S_OK;
}

STDMETHODIMP CManderModel::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   *minStrain = m_MinStrain;
   *maxStrain = m_MaxStrain;
   return S_OK;
}

STDMETHODIMP CManderModel::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   Float64 fr,fcc,ecc;
   GetConcreteParameters(fr,fcc,ecc);
   (*strain) = ecc;
   return S_OK;
}

STDMETHODIMP CManderModel::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   Float64 Ec = GetEc();
   *pey = m_Fco/Ec;
   return S_OK;
}

STDMETHODIMP CManderModel::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   Float64 Ec = GetEc();

   // The stress is in PSI, convert it to base units because that is what the caller expects
   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);
   convert->ConvertToBaseUnits(Ec,CComBSTR("psi"),&Ec);

   *pE = Ec;
   return S_OK;
}

STDMETHODIMP CManderModel::get_UnitServer(IUnitServer** ppVal )
{
   CHECK_RETOBJ(ppVal);

   (*ppVal) = m_UnitServer;
   (*ppVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CManderModel::putref_UnitServer(IUnitServer* pNewVal )
{
   CHECK_IN(pNewVal);

   m_UnitServer = pNewVal;
   return S_OK;
}

Float64 CManderModel::GetEc()
{
   return 60000.0*sqrt(m_Fco);
}

void CManderModel::GetConcreteParameters(Float64& fr,Float64& fcc,Float64& ecc)
{
   Float64 ke, ps, fyh;
   m_Section->get_ConfinementEffectivenessCoefficient(&ke);
   m_Section->get_TransvReinforcementRatio(&ps);
   m_Section->get_TransvYieldStrength(&fyh);

   // fyh is in base units, we need it in PSI, convert it
   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);
   convert->ConvertFromBaseUnits(fyh,CComBSTR("psi"),&fyh);

   fr = 0.5*ke*ps*fyh;
   fcc = m_Fco*(-1.254 + 2.254*sqrt(1+7.94*(fr/m_Fco)) - 2*(fr/m_Fco));
   ecc = m_eco*(1+m_R*(fcc/m_Fco - 1));
}

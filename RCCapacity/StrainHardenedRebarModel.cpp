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

// StrainHardenedRebarModel.cpp : Implementation of CStrainHardenedRebarModel
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "StrainHardenedRebarModel.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrainHardenedRebarModel

STDMETHODIMP CStrainHardenedRebarModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStrainHardenedRebarModel,
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

STDMETHODIMP CStrainHardenedRebarModel::Init(Float64 fy,Float64 fu,Float64 Es,Float64 esh,Float64 efr)
{
   if ( Es < 0 || IsZero(Es) )
      return E_INVALIDARG;

   if ( fy < 0 || IsZero(fy) )
      return E_INVALIDARG;

   if ( fu < 0 || IsZero(fu) )
      return E_INVALIDARG;

   if ( esh < 0 || IsZero(esh) )
      return E_INVALIDARG;

   if ( efr < 0 || IsZero(efr) )
      return E_INVALIDARG;

   m_Fy = fy;
   m_Fu = fu;
   m_Es = Es;
   m_esh = esh;
   m_efr = efr;

	return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_Name(BSTR name)
{
   m_bstrName = name;
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_Name(BSTR *name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::ComputeStress(Float64 strain,Float64* pVal)
{
   CHECK_RETVAL(pVal);

//   if ( strain < -m_efr || m_efr < strain )
//   {
//      *pVal = 0;
//      return E_FAIL;
//   }

   Float64 ey = m_Fy/m_Es;
   Float64 sign = BinarySign(strain);
   strain = fabs(strain);

   if (InRange(0.0, strain, ey))
   {
      *pVal = m_Es*strain;
   }
   else if (InRange(ey, strain, m_esh))
   {
      *pVal = m_Fy; // plateau
   }
   else if (InRange(m_esh, strain, m_efr))
   {
      *pVal = m_Fu - (m_Fu - m_Fy)*pow((m_efr - strain), 2) / pow((m_esh - m_efr), 2); // strain hardening
   }
   else if (m_efr < strain)
   {
      *pVal = m_Fu; // fractured, but just flatten out the line so that the solver doesn't have problems
   }

   (*pVal) *= sign;

   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   *minStrain = -m_efr;
   *maxStrain =  m_efr;
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   *strain = m_efr;
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = m_Fy/m_Es;
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_ModulusOfElasticity(Float64* pE)
{
   return get_Es(pE);
}

STDMETHODIMP CStrainHardenedRebarModel::get_fy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Fy;
	return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_fy(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_Fy = newVal;
	return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_fu(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Fu;
	return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_fu(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_Fu = newVal;
	return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_Es(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Es;
	return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_Es(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_Es = newVal;
	return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_esh(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_esh;
	return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_esh(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_esh = newVal;
	return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_efr(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_efr;
	return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_efr(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_efr = newVal;
	return S_OK;
}

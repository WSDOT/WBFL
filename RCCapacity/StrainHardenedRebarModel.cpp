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

   m_Model.SetProperties(fy, fu, Es, esh, efr);

	return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_Name(BSTR name)
{
   USES_CONVERSION;
   m_Model.SetName(OLE2T(name));
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_Name(BSTR *name)
{
   USES_CONVERSION;
   CHECK_RETSTRING(name);
   *name = T2BSTR(m_Model.GetName().c_str());
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::ComputeStress(Float64 strain,Float64* pVal)
{
   CHECK_RETVAL(pVal);

   auto result = m_Model.ComputeStress(strain);
   *pVal = result.first;
   return (result.second == true ? S_OK : S_FALSE);
}

STDMETHODIMP CStrainHardenedRebarModel::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   m_Model.GetStrainLimits(minStrain, maxStrain);

   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   *strain = m_Model.GetStrainAtPeakStress();
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = m_Model.GetYieldStrain();
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   *pE = m_Model.GetModulusOfElasticity();
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_fy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 fy, fu, Es, esh, er;
   bool bIsStrainHardening;
   m_Model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
   ATLASSERT(bIsStrainHardening == true);

   *pVal = fy;
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_fy(Float64 newVal)
{
   if (newVal < 0 || IsZero(newVal))
      return E_INVALIDARG;

   Float64 fy, fu, Es, esh, er;
   bool bIsStrainHardening;
   m_Model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
   ATLASSERT(bIsStrainHardening == true);

   m_Model.SetProperties(newVal, fu, Es, esh, er);

   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_fu(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 fy, fu, Es, esh, er;
   bool bIsStrainHardening;
   m_Model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
   ATLASSERT(bIsStrainHardening == true);

   *pVal = fu;
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_fu(Float64 newVal)
{
   if (newVal < 0 || IsZero(newVal))
      return E_INVALIDARG;

   Float64 fy, fu, Es, esh, er;
   bool bIsStrainHardening;
   m_Model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
   ATLASSERT(bIsStrainHardening == true);

   m_Model.SetProperties(fy, newVal, Es, esh, er);

   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_Es(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 fy, fu, Es, esh, er;
   bool bIsStrainHardening;
   m_Model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
   ATLASSERT(bIsStrainHardening == true);

   *pVal = Es;
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_Es(Float64 newVal)
{
   if (newVal < 0 || IsZero(newVal))
      return E_INVALIDARG;

   Float64 fy, fu, Es, esh, er;
   bool bIsStrainHardening;
   m_Model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
   ATLASSERT(bIsStrainHardening == true);

   m_Model.SetProperties(fy, fu, newVal, esh, er);

   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_esh(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 fy, fu, Es, esh, er;
   bool bIsStrainHardening;
   m_Model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
   ATLASSERT(bIsStrainHardening == true);

   *pVal = esh;
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_esh(Float64 newVal)
{
   if (newVal < 0 || IsZero(newVal))
      return E_INVALIDARG;

   Float64 fy, fu, Es, esh, er;
   bool bIsStrainHardening;
   m_Model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
   ATLASSERT(bIsStrainHardening == true);

   m_Model.SetProperties(fy, fu, Es, newVal, er);

   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::get_efr(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 fy, fu, Es, esh, er;
   bool bIsStrainHardening;
   m_Model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
   ATLASSERT(bIsStrainHardening == true);

   *pVal = er;
   return S_OK;
}

STDMETHODIMP CStrainHardenedRebarModel::put_efr(Float64 newVal)
{
   if (newVal < 0 || IsZero(newVal))
      return E_INVALIDARG;

   Float64 fy, fu, Es, esh, er;
   bool bIsStrainHardening;
   m_Model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
   ATLASSERT(bIsStrainHardening == true);

   m_Model.SetProperties(fy, fu, Es, esh, newVal);

   return S_OK;

}

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

// RambergOsgoodModel.cpp : Implementation of CRambergOsgoodModel
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "RambergOsgoodModel.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRambergOsgoodModel

STDMETHODIMP CRambergOsgoodModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IPowerFormula,
		&IID_IStressStrain
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CRambergOsgoodModel::FinalConstruct()
{
   return S_OK;
}

void CRambergOsgoodModel::FinalRelease()
{
}

STDMETHODIMP CRambergOsgoodModel::Init(Float64 A, Float64 B, Float64 C, Float64 Eps, Float64 fpu, Float64 minStrain, Float64 maxStrain)
{
   m_Model.SetModelParameters(A, B, C, Eps, fpu, minStrain, maxStrain);
   return S_OK;
}

STDMETHODIMP CRambergOsgoodModel::put_Name(BSTR name)
{
   USES_CONVERSION;
   m_Model.SetName(OLE2T(name));
   return S_OK;
}

STDMETHODIMP CRambergOsgoodModel::get_Name(BSTR *name)
{
   USES_CONVERSION;
   CHECK_RETSTRING(name);
   *name = T2BSTR(m_Model.GetName().c_str());
   return S_OK;
}


STDMETHODIMP CRambergOsgoodModel::ComputeStress(Float64 strain,Float64* pVal)
{
   CHECK_RETVAL(pVal);

   auto [stress, bStrainWithinLimits] = m_Model.ComputeStress(strain);
   *pVal = stress;
   return (bStrainWithinLimits ? S_OK : S_FALSE);
}

STDMETHODIMP CRambergOsgoodModel::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   m_Model.GetStrainLimits(minStrain, maxStrain);

   return S_OK;
}

STDMETHODIMP CRambergOsgoodModel::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   *strain = m_Model.GetStrainAtPeakStress();
   return S_OK;
}

STDMETHODIMP CRambergOsgoodModel::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = m_Model.GetYieldStrain();
   return S_OK;
}

STDMETHODIMP CRambergOsgoodModel::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   *pE = m_Model.GetModulusOfElasticity();
   return S_OK;
}

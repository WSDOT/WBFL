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

HRESULT CRambergOsgoodModel::FinalConstruct()
{
   return S_OK;
}

void CRambergOsgoodModel::FinalRelease()
{
}

STDMETHODIMP CRambergOsgoodModel::Init(Float64 A, Float64 B, Float64 C, Float64 Eps, Float64 fpu, Float64 minStrain, Float64 maxStrain)
{
   m_A = A;
   m_B = B;
   m_C = C;
   m_Eps = Eps;
   m_fpu = fpu;
   m_MinStrain = minStrain;
   m_MaxStrain = maxStrain;
   return S_OK;
}

STDMETHODIMP CRambergOsgoodModel::put_Name(BSTR name)
{
   m_bstrName = name;
   return S_OK;
}

STDMETHODIMP CRambergOsgoodModel::get_Name(BSTR *name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}


STDMETHODIMP CRambergOsgoodModel::ComputeStress(Float64 strain,Float64* pVal)
{
   CHECK_RETVAL(pVal);

   Float64 sign = BinarySign(strain);
   strain = fabs(strain);

   Float64 D = 1 + pow(m_B * strain, m_C);
   Float64 fps = Min(m_Eps * strain * (m_A + (1 - m_A) /pow(D, 1.0 / m_C)), m_fpu);

   *pVal = sign*fps;

   return ::IsLT(m_MaxStrain,sign* strain) ? S_FALSE : S_OK;
}

STDMETHODIMP CRambergOsgoodModel::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   *minStrain = m_MinStrain;
   *maxStrain = m_MaxStrain;
   return S_OK;
}

STDMETHODIMP CRambergOsgoodModel::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   (*strain) = m_MaxStrain;
   return S_OK;
}

STDMETHODIMP CRambergOsgoodModel::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = 0.9*m_fpu/m_Eps;
   return S_OK;
}

STDMETHODIMP CRambergOsgoodModel::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   *pE = m_Eps;
   return S_OK;
}

///////////////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CRambergOsgoodModel::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("RambergOsgoodModel"),1.0);


   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CRambergOsgoodModel::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("RambergOsgoodModel"));


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

// IPersist
STDMETHODIMP CRambergOsgoodModel::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

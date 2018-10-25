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

// LRFDPrestressFormula.cpp : Implementation of CLRFDPrestressFormula
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "LRFDPrestressFormula.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLRFDPrestressFormula

STDMETHODIMP CLRFDPrestressFormula::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_ILRFDPrestressFormula,
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

HRESULT CLRFDPrestressFormula::FinalConstruct()
{
   m_MinStrain = -0.035;
   m_MaxStrain =  0.035;

   return S_OK;
}

void CLRFDPrestressFormula::FinalRelease()
{
}

STDMETHODIMP CLRFDPrestressFormula::put_Fpu(Float64 fpu)
{
   m_Fpu = fpu;
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_Fpu(Float64* pFpu)
{
   CHECK_RETVAL(pFpu);
   *pFpu = m_Fpu;
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::put_Eps(Float64 Eps)
{
   m_Eps = Eps;
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_ProductionMethod(ProductionMethodType* type)
{
   CHECK_RETVAL(type);
   *type = m_ProductionMethod;
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::put_ProductionMethod(ProductionMethodType type)
{
   m_ProductionMethod = type;
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::put_Name(BSTR name)
{
   m_bstrName = name;
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_Name(BSTR *name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}


STDMETHODIMP CLRFDPrestressFormula::ComputeStress(Float64 strain,Float64* pVal)
{
   CHECK_RETVAL(pVal);

   Float64 sign = BinarySign(strain);
   strain = fabs(strain);

   Float64 k = (m_ProductionMethod == pmtLowRelaxation ? 0.28 : 0.38); // LRFD Table C5.7.3.1.1-1

   Float64 c_over_d = 0.003/(0.003 + strain);

   Float64 fps = m_Fpu*(1 - k*c_over_d);

   *pVal = sign*fps;

   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   *minStrain = m_MinStrain;
   *maxStrain = m_MaxStrain;
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   (*strain) = m_MaxStrain;
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = (m_ProductionMethod == pmtLowRelaxation ? 0.90 : 0.85)*m_Fpu/m_Eps;
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   *pE = m_Eps;
   return S_OK;
}

///////////////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CLRFDPrestressFormula::Save(IStructuredSave2* pSave)
{
   return E_FAIL;
}

STDMETHODIMP CLRFDPrestressFormula::Load(IStructuredLoad2* pLoad)
{
   return E_FAIL;
}

// IPersist
STDMETHODIMP CLRFDPrestressFormula::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

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
		&IID_IStressStrain
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
   return S_OK;
}

void CLRFDPrestressFormula::FinalRelease()
{
}

STDMETHODIMP CLRFDPrestressFormula::put_Fpu(Float64 fpu)
{
   m_Model.SetFpu(fpu);
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_Fpu(Float64* pFpu)
{
   CHECK_RETVAL(pFpu);
   *pFpu = m_Model.GetFpu();
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::put_Eps(Float64 Eps)
{
   m_Model.SetEps(Eps);
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_ProductionMethod(ProductionMethodType* type)
{
   CHECK_RETVAL(type);
   *type = (ProductionMethodType)m_Model.GetStrandType();
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::put_ProductionMethod(ProductionMethodType type)
{
   m_Model.SetStrandType((WBFL::Materials::StrandType)type);
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::put_Name(BSTR name)
{
   USES_CONVERSION;
   m_Model.SetName(OLE2T(name));
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_Name(BSTR *name)
{
   USES_CONVERSION;
   CHECK_RETSTRING(name);
   *name = T2BSTR(m_Model.GetName().c_str());
   return S_OK;
}


STDMETHODIMP CLRFDPrestressFormula::ComputeStress(Float64 strain,Float64* pVal)
{
   CHECK_RETVAL(pVal);

   auto [stress,bExceedsStrainLimit] = m_Model.ComputeStress(strain);
   *pVal = stress;
   return (bExceedsStrainLimit ? S_OK : S_FALSE);
}

STDMETHODIMP CLRFDPrestressFormula::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   m_Model.GetStrainLimits(minStrain, maxStrain);

   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   *strain = m_Model.GetStrainAtPeakStress();
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = m_Model.GetYieldStrain();
   return S_OK;
}

STDMETHODIMP CLRFDPrestressFormula::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   *pE = m_Model.GetModulusOfElasticity();
   return S_OK;
}

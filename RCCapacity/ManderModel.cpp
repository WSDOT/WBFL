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

// ManderModel.cpp : Implementation of CManderModel
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "ManderModel.h"
#include "CircularManderSection.h"
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
   return S_OK;
}

void CManderModel::FinalRelease()
{
}

STDMETHODIMP CManderModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IManderModel,
      &IID_IStressStrain
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

   // get the internal section object and provide it to the model
   CManderSection* p = dynamic_cast<CManderSection*>(section);
   ATLASSERT(p);
   m_Model.SetSection(p->GetSection());

   // keep a copy of the incoming section so it can be returned in get_Section
   // this is a putref_ so this method must return the same object as  received
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
   m_Model.Set_fco(fco);
   return S_OK;
}

STDMETHODIMP CManderModel::get_fco(Float64* fco)
{
   CHECK_RETVAL(fco);
   *fco = m_Model.Get_fco();
   return S_OK;
}

STDMETHODIMP CManderModel::put_eco(Float64 eco)
{
   m_Model.Set_eco(eco);
   return S_OK;
}

STDMETHODIMP CManderModel::get_eco(Float64* eco)
{
   CHECK_RETVAL(eco);
   *eco = m_Model.Get_eco();
   return S_OK;
}

STDMETHODIMP CManderModel::put_R(Float64 r)
{
   m_Model.SetR(r);
   return S_OK;
}

STDMETHODIMP CManderModel::get_R(Float64* r)
{
   CHECK_RETVAL(r);
   *r = m_Model.GetR();
   return S_OK;
}

STDMETHODIMP CManderModel::GetConcreteParameters(Float64* pfr, Float64* pfcc, Float64* pecc)
{
   CHECK_RETVAL(pfr);
   CHECK_RETVAL(pfcc);
   CHECK_RETVAL(pecc);

   m_Model.ComputeConcreteProperties(pfr, pfcc, pecc);

   return S_OK;
}

// IStressStrain
STDMETHODIMP CManderModel::put_Name(BSTR name)
{
   USES_CONVERSION;
   m_Model.SetName(OLE2T(name));
   return S_OK;
}

STDMETHODIMP CManderModel::get_Name(BSTR *name)
{
   USES_CONVERSION;
   CHECK_RETSTRING(name);
   *name = T2BSTR(m_Model.GetName().c_str());
   return S_OK;
}

STDMETHODIMP CManderModel::ComputeStress(Float64 strain,Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   auto result = m_Model.ComputeStress(strain);
   *pVal = result.first;
   return (result.second == true ? S_OK : S_FALSE);
}

STDMETHODIMP CManderModel::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   m_Model.GetStrainLimits(minStrain, maxStrain);

   return S_OK;
}

STDMETHODIMP CManderModel::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   *strain = m_Model.GetStrainAtPeakStress();
   return S_OK;
}

STDMETHODIMP CManderModel::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = m_Model.GetYieldStrain();
   return S_OK;
}

STDMETHODIMP CManderModel::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   *pE = m_Model.GetModulusOfElasticity();
   return S_OK;
}

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

// RebarModel.cpp : Implementation of CRebarModel
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "RebarModel.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRebarModel

STDMETHODIMP CRebarModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRebarModel,
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

STDMETHODIMP CRebarModel::Init(Float64 fy, Float64 Es,Float64 maxStrain)
{
   if ( Es < 0 || IsZero(Es) )
      return E_INVALIDARG;

   if ( fy < 0 || IsZero(fy) )
      return E_INVALIDARG;

   if ( maxStrain < 0 || IsZero(maxStrain) )
      return E_INVALIDARG;

   m_Fy = fy;
   m_Es = Es;
   m_MaxStrain = maxStrain;
   m_MinStrain = -maxStrain;
	return S_OK;
}

STDMETHODIMP CRebarModel::put_Name(BSTR name)
{
   m_bstrName = name;
   return S_OK;
}

STDMETHODIMP CRebarModel::get_Name(BSTR *name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}

STDMETHODIMP CRebarModel::ComputeStress(Float64 strain,Float64* pVal)
{
   CHECK_RETVAL(pVal);

   Float64 ey = m_Fy/m_Es;

   if ( InRange(-ey,strain,ey) )
      *pVal = m_Es*strain;
   else
      *pVal = (BinarySign(strain)*m_Fy);

   return IsLT(m_MaxStrain,strain) ? S_FALSE : S_OK;
}

STDMETHODIMP CRebarModel::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   *minStrain = m_MinStrain;
   *maxStrain = m_MaxStrain;
   return S_OK;
}

STDMETHODIMP CRebarModel::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   *strain = m_MaxStrain;
   return S_OK;
}

STDMETHODIMP CRebarModel::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = m_Fy/m_Es;
   return S_OK;
}

STDMETHODIMP CRebarModel::get_ModulusOfElasticity(Float64* pE)
{
   return get_Es(pE);
}

STDMETHODIMP CRebarModel::get_fy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Fy;
	return S_OK;
}

STDMETHODIMP CRebarModel::put_fy(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_Fy = newVal;
	return S_OK;
}

STDMETHODIMP CRebarModel::get_Es(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Es;
	return S_OK;
}

STDMETHODIMP CRebarModel::put_Es(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_Es = newVal;
	return S_OK;
}

STDMETHODIMP CRebarModel::get_MaxStrain(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_MaxStrain;
   return S_OK;
}

STDMETHODIMP CRebarModel::put_MaxStrain(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_MaxStrain = newVal;
   m_MinStrain = -m_MaxStrain;

   return S_OK;
}

///////////////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CRebarModel::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("RebarModel"),1.0);

   pSave->put_Property(CComBSTR("Fy"),CComVariant(m_Fy));
   pSave->put_Property(CComBSTR("Es"),CComVariant(m_Es));
   pSave->put_Property(CComBSTR("MaxStrain"),CComVariant(m_MaxStrain));
   pSave->put_Property(CComBSTR("MinStrain"),CComVariant(m_MinStrain));

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CRebarModel::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("RebarModel"));

   if ( FAILED(pLoad->get_Property(CComBSTR("Fy"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Fy = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("Es"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Es = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("MaxStrain"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_MaxStrain = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("MinStrain"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_MinStrain = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

// IPersist
STDMETHODIMP CRebarModel::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

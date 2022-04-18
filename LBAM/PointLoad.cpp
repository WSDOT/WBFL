///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// PointLoad.cpp : Implementation of CPointLoad
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "PointLoad.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointLoad

STDMETHODIMP CPointLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPointLoad
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPointLoad::get_MemberType(MemberType *pVal)
{
   CHECK_RETVAL(pVal);

	*pVal = m_MemberType;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_MemberType(MemberType newVal)
{
   if (newVal != m_MemberType)
   {
      CHECK_MEMBERTYPE(newVal);

      m_MemberType = newVal;
      Fire_OnPointLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CPointLoad::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_MemberID;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_MemberID(MemberIDType newVal)
{
	if (newVal<0)
      return E_INVALIDARG;

   if (newVal!=m_MemberID)
   {
      m_MemberID = newVal;
      Fire_OnPointLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CPointLoad::get_Location(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Location;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Location(Float64 newVal)
{
	if (newVal<-1.0)
      return E_INVALIDARG;

   if (newVal!=m_Location)
   {
      m_Location = newVal;
      Fire_OnPointLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CPointLoad::get_Fx(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Fx;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Fx(Float64 newVal)
{
   if (newVal!=m_Fx)
   {
      m_Fx = newVal;
      Fire_OnPointLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CPointLoad::get_Fy(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Fy;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Fy(Float64 newVal)
{
   if (newVal!=m_Fy)
   {
      m_Fy = newVal;
      Fire_OnPointLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CPointLoad::get_Mz(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Mz;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Mz(Float64 newVal)
{
   if (newVal!=m_Mz)
   {
      m_Mz = newVal;
      Fire_OnPointLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CPointLoad::SetForce(Float64 Fx, Float64 Fy, Float64 Mz)
{
   if (Fx!=m_Fx || Fy!=m_Fy || Mz!=m_Mz)
   {
      m_Fx = Fx;
      m_Fy = Fy;
      m_Mz = Mz;
      Fire_OnPointLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CPointLoad::GetForce(Float64 *Fx, Float64 *Fy, Float64 *Mz)
{
	CHECK_RETVAL(Fx);
	CHECK_RETVAL(Fy);
	CHECK_RETVAL(Mz);

   *Fx = m_Fx;
   *Fy = m_Fy;
   *Mz = m_Mz;

	return S_OK;
}

STDMETHODIMP CPointLoad::Clone(IPointLoad **clone)
{
   CHECK_RETOBJ(clone);

   // create a new and fill it up
   CComObject<CPointLoad>* pnew;
   HRESULT hr = CComObject<CPointLoad>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IPointLoad> pscs(pnew); // for reference count

   pnew->m_MemberType  = m_MemberType;
   pnew->m_MemberID    = m_MemberID;
   pnew->m_Location    = m_Location;

   pnew->m_Fx = m_Fx;
   pnew->m_Fy = m_Fy;
   pnew->m_Mz = m_Mz;

   return pscs.CopyTo(clone);
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CPointLoad::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("PointLoad"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      _variant_t var;

      hr = pload->get_Property(_bstr_t("Location"),&var);
      if (FAILED(hr))
         return hr;

      m_Location = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("MemberType"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t type(var);
      hr = StringToMemberType(type, &m_MemberType);
      if (FAILED(hr))
         return hr;
      
      var.Clear();

      hr = pload->get_Property(_bstr_t("MemberID"),&var);
      if (FAILED(hr))
         return hr;

      m_MemberID = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("Fx"),&var);
      if (FAILED(hr))
         return hr;

      m_Fx = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("Fy"),&var);
      if (FAILED(hr))
         return hr;

      m_Fy = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("Mz"),&var);
      if (FAILED(hr))
         return hr;

      m_Mz = var;
      var.Clear();

   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CPointLoad::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("PointLoad"), MY_VER);

      {
         hr = psave->put_Property(CComBSTR("Location"),_variant_t(m_Location));

         _bstr_t type = MemberTypeToString(m_MemberType);

         hr = psave->put_Property(CComBSTR("MemberType"),_variant_t(type));
         hr = psave->put_Property(CComBSTR("MemberID"),_variant_t(m_MemberID));
         hr = psave->put_Property(CComBSTR("Fx"),_variant_t(m_Fx));
         hr = psave->put_Property(CComBSTR("Fy"),_variant_t(m_Fy));
         hr = psave->put_Property(CComBSTR("Mz"),_variant_t(m_Mz));
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IPointLoad);
   }

   return S_OK;
}

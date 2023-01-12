///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2023  Washington State Department of Transportation
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

// DistributedLoad.cpp : Implementation of CDistributedLoad
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "DistributedLoad.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDistributedLoad

STDMETHODIMP CDistributedLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDistributedLoad
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDistributedLoad::Clone(IDistributedLoad** clone)
{
   CHECK_RETOBJ(clone);

   // create a new and fill it up
   CComObject<CDistributedLoad>* pnew;
   HRESULT hr = CComObject<CDistributedLoad>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IDistributedLoad> pscs(pnew); // for reference count

   pnew->m_MemberType       = m_MemberType;
   pnew->m_MemberID         = m_MemberID;
   pnew->m_Direction        = m_Direction;
   pnew->m_Orientation      = m_Orientation;
   pnew->m_StartLocation    = m_StartLocation;
   pnew->m_EndLocation      = m_EndLocation;
   pnew->m_WStart           = m_WStart;
   pnew->m_WEnd             = m_WEnd;

   return pscs.CopyTo(clone);
}

STDMETHODIMP CDistributedLoad::get_MemberType(MemberType *pVal)
{
   CHECK_RETVAL(pVal);

	*pVal = m_MemberType;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_MemberType(MemberType newVal)
{
   if (newVal != m_MemberType)
   {
      if (newVal<mtUndefined || newVal> mtSuperstructureMember)
         return E_INVALIDARG;

      m_MemberType = newVal;
      Fire_OnDistributedLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_MemberID;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_MemberID(MemberIDType newVal)
{
	if (newVal<0)
      return E_INVALIDARG;

   if (newVal!=m_MemberID)
   {
      m_MemberID = newVal;
      Fire_OnDistributedLoadChanged(this);
   }

	return S_OK;
}



STDMETHODIMP CDistributedLoad::get_StartLocation(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_StartLocation;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_StartLocation(Float64 newVal)
{
	if (newVal<-1.0)
      return E_INVALIDARG;

   if (newVal!=m_StartLocation)
   {
      m_StartLocation = newVal;
      Fire_OnDistributedLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_EndLocation(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_EndLocation;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_EndLocation(Float64 newVal)
{
	if (newVal<-1.0)
      return E_INVALIDARG;

   if (newVal!=m_EndLocation)
   {
      m_EndLocation = newVal;
      Fire_OnDistributedLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_Orientation(LoadOrientation *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Orientation;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_Orientation(LoadOrientation newVal)
{
   if (newVal!=m_Orientation)
   {
      if (newVal<loGlobal  || newVal> loGlobalProjected)
         return E_INVALIDARG;

      m_Orientation = newVal;
      Fire_OnDistributedLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_Direction(LoadDirection *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Direction;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_Direction(LoadDirection newVal)
{
   if (newVal!=m_Direction)
   {
      if (newVal!=ldFx && newVal!=ldFy)
         return E_INVALIDARG;

      m_Direction = newVal;
      Fire_OnDistributedLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_WStart(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_WStart;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_WStart(Float64 newVal)
{
   if (newVal!=m_WStart)
   {
      m_WStart = newVal;
      Fire_OnDistributedLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_WEnd(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_WEnd;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_WEnd(Float64 newVal)
{
   if (newVal!=m_WEnd)
   {
      m_WEnd = newVal;
      Fire_OnDistributedLoadChanged(this);
   }

	return S_OK;
}


// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CDistributedLoad::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("DistributedLoad"));
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
      hr = pload->get_Property(_bstr_t("Direction"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t dir(var);
      hr = StringToLoadDirection(dir, &m_Direction);
      if (FAILED(hr))
         return hr;

      var.Clear();
      hr = pload->get_Property(_bstr_t("Orientation"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t or(var);
      hr = StringToLoadOrientation(or, &m_Orientation);
      if (FAILED(hr))
         return hr;

      var.Clear();
      hr = pload->get_Property(_bstr_t("StartLocation"),&var);
      if (FAILED(hr))
         return hr;

      m_StartLocation = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("EndLocation"),&var);
      if (FAILED(hr))
         return hr;

      m_EndLocation = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("WStart"),&var);
      if (FAILED(hr))
         return hr;

      m_WStart = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("WEnd"),&var);
      if (FAILED(hr))
         return hr;

      m_WEnd = var;

   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CDistributedLoad::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("DistributedLoad"), MY_VER);
      if (FAILED(hr))
         return hr;

      {
         _bstr_t type = MemberTypeToString(m_MemberType);

         hr = psave->put_Property(CComBSTR("MemberType"),_variant_t(type));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("MemberID"),_variant_t(m_MemberID));
         if (FAILED(hr))
            return hr;

         _bstr_t dir = LoadDirectionToString(m_Direction);

         hr = psave->put_Property(CComBSTR("Direction"),_variant_t(dir));
         if (FAILED(hr))
            return hr;

         _bstr_t or = LoadOrientationToString(m_Orientation);

         hr = psave->put_Property(CComBSTR("Orientation"),_variant_t(or));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("StartLocation"),_variant_t(m_StartLocation));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("EndLocation"),_variant_t(m_EndLocation));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("WStart"),_variant_t(m_WStart));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("WEnd"),_variant_t(m_WEnd));
         if (FAILED(hr))
            return hr;
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IDistributedLoad);
   }

   return hr;
}

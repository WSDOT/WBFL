///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2021  Washington State Department of Transportation
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
#include "WBFLLoading.h"
#include "PointLoad.h"
#include "LoadingUtils.h"

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
		&IID_ldIPointLoad
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//STDMETHODIMP CPointLoad::get_MemberType(MemberType *pVal)
//{
//   CHECK_RETVAL(pVal);
//
//	*pVal = m_MemberType;
//
//	return S_OK;
//}
//
//STDMETHODIMP CPointLoad::put_MemberType(MemberType newVal)
//{
//   if (newVal != m_MemberType)
//   {
//      CHECK_MEMBERTYPE(newVal);
//
//      m_MemberType = newVal;
//      Fire_OnPointLoadChanged(this);
//   }
//
//	return S_OK;
//}

STDMETHODIMP CPointLoad::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_MemberID;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_MemberID(MemberIDType id)
{
   HRESULT hr = PutMemberID(this,id);
	return hr;
}

STDMETHODIMP CPointLoad::get_Location(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Location;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Location(Float64 location)
{
   HRESULT hr = PutLocation(this,location);
	return hr;
}

STDMETHODIMP CPointLoad::get_Fx(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Fx;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Fx(Float64 fx)
{
   HRESULT hr = PutFx(this,fx);
	return hr;
}

STDMETHODIMP CPointLoad::get_Fy(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Fy;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Fy(Float64 fy)
{
   HRESULT hr = PutFy(this,fy);
	return hr;
}

STDMETHODIMP CPointLoad::get_Mz(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Mz;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Mz(Float64 mz)
{
   HRESULT hr = PutMz(this,mz);
	return hr;
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

STDMETHODIMP CPointLoad::Clone(ldIPointLoad **clone)
{
   CHECK_RETOBJ(clone);

   // create a new and fill it up
   CComObject<CPointLoad>* pnew;
   HRESULT hr = CComObject<CPointLoad>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ldIPointLoad> pscs(pnew); // for reference count

//   pnew->m_MemberType  = m_MemberType;
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
      CComVariant var;

      hr = pload->get_Property(CComBSTR("Location"),&var);
      if (FAILED(hr))
         return hr;

      m_Location = var.dblVal;
      var.Clear();
//
//      hr = pload->get_Property(CComBSTR("MemberType"),&var);
//      if (FAILED(hr))
//         return hr;
//
//      CComBSTR type(var.bstrVal);
//      hr = StringToMemberType(type, &m_MemberType);
//      if (FAILED(hr))
//         return hr;
      
      var.Clear();

      hr = pload->get_Property(CComBSTR("MemberID"),&var);
      if (FAILED(hr))
         return hr;

      m_MemberID = var.iVal;
      var.Clear();

      hr = pload->get_Property(CComBSTR("Fx"),&var);
      if (FAILED(hr))
         return hr;

      m_Fx = var.dblVal;
      var.Clear();

      hr = pload->get_Property(CComBSTR("Fy"),&var);
      if (FAILED(hr))
         return hr;

      m_Fy = var.dblVal;
      var.Clear();

      hr = pload->get_Property(CComBSTR("Mz"),&var);
      if (FAILED(hr))
         return hr;

      m_Mz = var.dblVal;
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
         hr = psave->put_Property(CComBSTR("Location"),CComVariant(m_Location));

//         CComBSTR type(MemberTypeToString(m_MemberType));

//         hr = psave->put_Property(CComBSTR("MemberType"), CComVariant(type));
         hr = psave->put_Property(CComBSTR("MemberID"),   CComVariant(m_MemberID));
         hr = psave->put_Property(CComBSTR("Fx"),         CComVariant(m_Fx));
         hr = psave->put_Property(CComBSTR("Fy"),         CComVariant(m_Fy));
         hr = psave->put_Property(CComBSTR("Mz"),         CComVariant(m_Mz));
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ldIPointLoad);
   }

   return S_OK;
}


HRESULT CPointLoad::PutLocation(CPointLoad* pThis,Float64 location)
{
	if (location < -1.0)
      return E_INVALIDARG;

   if ( IsEqual(pThis->m_Location,location ) )
      return S_OK;

   pThis->m_Location = location;
   pThis->Fire_OnPointLoadChanged(pThis);
   return S_OK;
}

HRESULT CPointLoad::PutFx(CPointLoad* pThis,Float64 fx)
{
   if ( IsEqual(pThis->m_Fx,fx ) )
      return S_OK;

   pThis->m_Fx = fx;
   pThis->Fire_OnPointLoadChanged(pThis);
   return S_OK;
}

HRESULT CPointLoad::PutFy(CPointLoad* pThis,Float64 fy)
{
   if ( IsEqual(pThis->m_Fy,fy ) )
      return S_OK;

   pThis->m_Fy = fy;
   pThis->Fire_OnPointLoadChanged(pThis);
   return S_OK;
}

HRESULT CPointLoad::PutMz(CPointLoad* pThis,Float64 mz)
{
   if ( IsEqual(pThis->m_Mz,mz ) )
      return S_OK;

   pThis->m_Mz = mz;
   pThis->Fire_OnPointLoadChanged(pThis);
   return S_OK;
}

HRESULT CPointLoad::PutMemberID(CPointLoad* pThis,MemberIDType id)
{
	if (id < 0)
      return E_INVALIDARG;

   if ( pThis->m_MemberID == id )
      return S_OK;

   pThis->m_MemberID = id;
   pThis->Fire_OnPointLoadChanged(pThis);
   return S_OK;
}

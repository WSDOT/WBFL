///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2010  Washington State Department of Transportation
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
#include "WBFLLoading.h"
#include "DistributedLoad.h"
#include "LoadingUtils.h"

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
		&IID_ldIDistributedLoad
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDistributedLoad::Clone(ldIDistributedLoad** clone)
{
   CHECK_RETOBJ(clone);

   // create a new and fill it up
   CComObject<CDistributedLoad>* pnew;
   HRESULT hr = CComObject<CDistributedLoad>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ldIDistributedLoad> pscs(pnew); // for reference count

//   pnew->m_MemberType       = m_MemberType;
   pnew->m_MemberID         = m_MemberID;
   pnew->m_Direction        = m_Direction;
   pnew->m_Orientation      = m_Orientation;
   pnew->m_StartLocation    = m_StartLocation;
   pnew->m_EndLocation      = m_EndLocation;
   pnew->m_WStart           = m_WStart;
   pnew->m_WEnd             = m_WEnd;

   return pscs.CopyTo(clone);
}

//STDMETHODIMP CDistributedLoad::get_MemberType(MemberType *pVal)
//{
//   CHECK_RETVAL(pVal);
//
//	*pVal = m_MemberType;
//
//	return S_OK;
//}
//
//STDMETHODIMP CDistributedLoad::put_MemberType(MemberType newVal)
//{
//   if (newVal != m_MemberType)
//   {
//      if (newVal<mtUndefined || newVal> mtSuperstructureMember)
//         return E_INVALIDARG;
//
//      m_MemberType = newVal;
//      Fire_OnDistributedLoadChanged(this);
//   }
//
//	return S_OK;
//}

STDMETHODIMP CDistributedLoad::get_MemberID(long *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_MemberID;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_MemberID(long id)
{
   HRESULT hr;
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CDistributedLoad,long,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading> CEditTxn;
      CComObject<CEditTxn>* pTxn;
      CComObject<CEditTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Distributed Load Member ID"),&PutMemberID,m_MemberID, id);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      hr = PutMemberID(this,id);
   }

	return hr;
}

STDMETHODIMP CDistributedLoad::get_StartLocation(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_StartLocation;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_StartLocation(Float64 start)
{
   HRESULT hr;
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CDistributedLoad,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading> CEditTxn;
      CComObject<CEditTxn>* pTxn;
      CComObject<CEditTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Distributed Load Start Location"),&PutStartLocation,m_StartLocation, start);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      hr = PutStartLocation(this,start);
   }

	return hr;
}

STDMETHODIMP CDistributedLoad::get_EndLocation(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_EndLocation;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_EndLocation(Float64 end)
{
   HRESULT hr;
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CDistributedLoad,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading> CEditTxn;
      CComObject<CEditTxn>* pTxn;
      CComObject<CEditTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Distributed Load End Location"),&PutEndLocation,m_EndLocation, end);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      hr = PutEndLocation(this,end);
   }

	return hr;
}

STDMETHODIMP CDistributedLoad::get_Orientation(ldLoadOrientation *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Orientation;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_Orientation(ldLoadOrientation orientation)
{
   HRESULT hr;
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CDistributedLoad,ldLoadOrientation,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading> CEditTxn;
      CComObject<CEditTxn>* pTxn;
      CComObject<CEditTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Distributed Load Orientation"),&PutOrientation,m_Orientation, orientation);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      hr = PutOrientation(this,orientation);
   }

	return hr;
}

STDMETHODIMP CDistributedLoad::get_Direction(ldLoadDirection *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Direction;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_Direction(ldLoadDirection direction)
{
   HRESULT hr;
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CDistributedLoad,ldLoadDirection,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading> CEditTxn;
      CComObject<CEditTxn>* pTxn;
      CComObject<CEditTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Distributed Load Direction"),&PutDirection,m_Direction, direction);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      hr = PutDirection(this,direction);
   }

	return hr;
}

STDMETHODIMP CDistributedLoad::get_WStart(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_WStart;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_WStart(Float64 wStart)
{
   HRESULT hr;
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CDistributedLoad,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading> CEditTxn;
      CComObject<CEditTxn>* pTxn;
      CComObject<CEditTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Distributed Load Start Load"),&PutWStart,m_WStart, wStart);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      hr = PutWStart(this,wStart);
   }

	return hr;
}

STDMETHODIMP CDistributedLoad::get_WEnd(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_WEnd;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_WEnd(Float64 wEnd)
{
   HRESULT hr;
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CDistributedLoad,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading> CEditTxn;
      CComObject<CEditTxn>* pTxn;
      CComObject<CEditTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Distributed Load End Load"),&PutWEnd,m_WEnd, wEnd);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      hr = PutWEnd(this,wEnd);
   }

	return hr;
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
      CComVariant var;
//      hr = pload->get_Property(CComBSTR("MemberType"),&var);
//      if (FAILED(hr))
//         return hr;
//
//      hr = StringToMemberType(var.bstrVal, &m_MemberType);
//      if (FAILED(hr))
//         return hr;
      
      var.Clear();
      hr = pload->get_Property(CComBSTR("MemberID"),&var);
      if (FAILED(hr))
         return hr;

      m_MemberID = var.lVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("Direction"),&var);
      if (FAILED(hr))
         return hr;

      hr = StringToLoadDirection(var.bstrVal, &m_Direction);
      if (FAILED(hr))
         return hr;

      var.Clear();
      hr = pload->get_Property(CComBSTR("Orientation"),&var);
      if (FAILED(hr))
         return hr;

      hr = StringToLoadOrientation(var.bstrVal, &m_Orientation);
      if (FAILED(hr))
         return hr;

      var.Clear();
      hr = pload->get_Property(CComBSTR("StartLocation"),&var);
      if (FAILED(hr))
         return hr;

      m_StartLocation = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("EndLocation"),&var);
      if (FAILED(hr))
         return hr;

      m_EndLocation = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("WStart"),&var);
      if (FAILED(hr))
         return hr;

      m_WStart = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("WEnd"),&var);
      if (FAILED(hr))
         return hr;

      m_WEnd = var.dblVal;
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
//         CComBSTR type = MemberTypeToString(m_MemberType);
//
//         hr = psave->put_Property(CComBSTR("MemberType"),CComVariant(type));
//         if (FAILED(hr))
//            return hr;

         hr = psave->put_Property(CComBSTR("MemberID"),CComVariant(m_MemberID));
         if (FAILED(hr))
            return hr;

         CComBSTR dir = LoadDirectionToString(m_Direction);

         hr = psave->put_Property(CComBSTR("Direction"),CComVariant(dir));
         if (FAILED(hr))
            return hr;

         CComBSTR or = LoadOrientationToString(m_Orientation);

         hr = psave->put_Property(CComBSTR("Orientation"),CComVariant(or));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("StartLocation"),CComVariant(m_StartLocation));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("EndLocation"),CComVariant(m_EndLocation));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("WStart"),CComVariant(m_WStart));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("WEnd"),CComVariant(m_WEnd));
         if (FAILED(hr))
            return hr;
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ldIDistributedLoad);
   }

   return hr;
}

HRESULT CDistributedLoad::PutStartLocation(CDistributedLoad* pThis,Float64 start)
{
   if (start < -1.0)
      return E_INVALIDARG;

   if ( !IsEqual(start,pThis->m_StartLocation) )
   {
      pThis->m_StartLocation = start;
      pThis->Fire_OnDistributedLoadChanged(pThis);
   }

	return S_OK;
}

HRESULT CDistributedLoad::PutEndLocation(CDistributedLoad* pThis,Float64 end)
{
   if (end < -1.0)
      return E_INVALIDARG;

   if ( !IsEqual(end,pThis->m_EndLocation) )
   {
      pThis->m_EndLocation = end;
      pThis->Fire_OnDistributedLoadChanged(pThis);
   }

	return S_OK;
}

HRESULT CDistributedLoad::PutWStart(CDistributedLoad* pThis,Float64 wStart)
{
   if ( !IsEqual(wStart,pThis->m_WStart) )
   {
      pThis->m_WStart = wStart;
      pThis->Fire_OnDistributedLoadChanged(pThis);
   }

	return S_OK;
}

HRESULT CDistributedLoad::PutWEnd(CDistributedLoad* pThis,Float64 wEnd)
{
   if ( !IsEqual(wEnd,pThis->m_WEnd) )
   {
      pThis->m_WEnd = wEnd;
      pThis->Fire_OnDistributedLoadChanged(pThis);
   }

	return S_OK;
}

HRESULT CDistributedLoad::PutDirection(CDistributedLoad* pThis,ldLoadDirection direction)
{
   if (direction != ldldFx && direction != ldldFy)
      return E_INVALIDARG;

   if (direction != pThis->m_Direction)
   {
      pThis->m_Direction = direction;
      pThis->Fire_OnDistributedLoadChanged(pThis);
   }

	return S_OK;
}

HRESULT CDistributedLoad::PutOrientation(CDistributedLoad* pThis,ldLoadOrientation orientation)
{
   if (orientation != pThis->m_Orientation)
   {
      if (orientation < ldloGlobal  || ldloGlobalProjected < orientation)
         return E_INVALIDARG;

      pThis->m_Orientation = orientation;
      pThis->Fire_OnDistributedLoadChanged(pThis);
   }

	return S_OK;
}

HRESULT CDistributedLoad::PutMemberID(CDistributedLoad* pThis,long id)
{
	if (id < 0)
      return E_INVALIDARG;

   if (id != pThis->m_MemberID)
   {
      pThis->m_MemberID = id;
      pThis->Fire_OnDistributedLoadChanged(pThis);
   }

	return S_OK;
}

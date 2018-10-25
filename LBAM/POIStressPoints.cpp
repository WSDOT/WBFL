///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2011  Washington State Department of Transportation
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

// POIStressPoints.cpp : Implementation of CPOIStressPoints
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "LBAM.hh"
#include "LBAMUtils.h"
#include "POIStressPoints.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPOIStressPoints

STDMETHODIMP CPOIStressPoints::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPOIStressPoints
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CPOIStressPoints::FinalRelease()
{
   try
   {
      IteratorType it(m_Container.begin());
      IteratorType itend(m_Container.end());
      while( it!=itend)
      {
         DoErase(it, false);

         it=m_Container.begin();
      }
   }
   catch(...)
   {
      ATLASSERT(0);
   }
}

STDMETHODIMP CPOIStressPoints::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Container.size();

	return S_OK;
}

STDMETHODIMP CPOIStressPoints::get_Item(VARIANT invar, IPOIStressPointsItem **pVal)
{
   CHECK_RETOBJ(pVal);

   try
   {
      IteratorType itend( m_Container.end() );

      CComPtr<IPOIStressPointsItem> item;
      if (invar.vt==VT_I4)
      {
         long idx = invar.lVal;
         IteratorType it( m_Container.begin() );
         for (long i=0; i<idx; i++)
         {
            it++;
            if (it==itend)
               return E_INVALIDARG;
         }

         item = it->second.m_T;
      }
      else if (invar.vt==VT_BSTR)
      {
         CComBSTR stage(invar.bstrVal);
         IteratorType it( m_Container.find(stage) );
         if (it!=itend)
         {
            item = it->second.m_T;
         }
         else
         {
            CComBSTR msg =CreateErrorMsg1S(IDS_E_POI_NO_STAGE, stage);
            THROW_LBAM_MSG(POI_NO_STAGE,msg);
         }
      }
      else
      {
         return E_INVALIDARG;
      }

	   return item.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMModel);
   }
}

STDMETHODIMP CPOIStressPoints::Clear()
{
   try
   {
      IteratorType it( m_Container.begin() );
      IteratorType itend( m_Container.end() );
      while( it!=itend)
      {
         Fire_OnPOIStressPointsBeforeRemove(it->second.m_T);

         DoErase(it);

         it=m_Container.begin();
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMModel);
   }

	return S_OK;
}

STDMETHODIMP CPOIStressPoints::Insert(BSTR Stage, IStressPoints *leftSps, IStressPoints *rightSps)
{
   CHECK_IN(Stage);
   CHECK_IN(leftSps);
   CHECK_IN(rightSps);

   HRESULT hr;
	IteratorType it( m_Container.find( Stage) );
   if (it!=m_Container.end())
   {
      // must remove old items before inserting new
      hr = Remove(Stage);
      if (FAILED(hr))
      {
         ATLASSERT(0);
         return hr;
      }
   }

   CComObject<CPOIStressPointsItem>* pcitem;
   hr = CComObject<CPOIStressPointsItem>::CreateInstance(&pcitem);
   if (FAILED(hr))
      return hr;

   CComPtr<IPOIStressPointsItem> pitem(pcitem);

   pcitem->m_Stage = Stage;
   pcitem->m_LeftStressPoints = leftSps;
   pcitem->m_RightStressPoints = rightSps;

   hr =  CrAdvise(leftSps, this, IID_IStressPointsEvents, &(pcitem->m_LeftCookie));
   if (FAILED(hr))
      return hr;

   hr =  CrAdvise(rightSps, this, IID_IStressPointsEvents, &(pcitem->m_RightCookie));
   if (FAILED(hr))
      return hr;

   m_Container.insert( StoredType(Stage, pitem));

   Fire_OnPOIStressPointsAdded(pitem);

	return S_OK;
}

STDMETHODIMP CPOIStressPoints::Remove(BSTR Stage)
{
   CHECK_IN(Stage);
   try
   {
	   IteratorType it( m_Container.find( Stage) );
      if (it!=m_Container.end())
      {
         DoErase(it);
      }
      else
      {
         CComBSTR msg =CreateErrorMsg1S(IDS_E_POI_NO_STAGE, Stage);
         THROW_LBAM_MSG(POI_NO_STAGE,msg);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMModel);
   }

	return S_OK;
}

void CPOIStressPoints::DoErase(IteratorType& it, bool doFire)
{
   IPOIStressPointsItem* item = it->second.m_T;
   CPOIStressPointsItem* citem = dynamic_cast<CPOIStressPointsItem*>(item);
   if (citem)
   {
      if (doFire)
      {
         Fire_OnPOIStressPointsBeforeRemove(item);
      }

      // disconnect and erase
      CHRException hr;
      hr =  CrUnadvise(citem->m_LeftStressPoints, this, IID_IStressPointsEvents,   citem->m_LeftCookie);
      hr =  CrUnadvise(citem->m_RightStressPoints , this, IID_IStressPointsEvents, citem->m_RightCookie);

      m_Container.erase(it);
   }
   else
   {
      ATLASSERT(0);
      THROW_HR(E_FAIL);
   }
}

STDMETHODIMP CPOIStressPoints::Clone(IPOIStressPoints **Clone)
{
   CHECK_RETVAL(Clone);

   CHRException hr;
   try
   {
      CComObject<CPOIStressPoints>* cclone;
      hr = CComObject<CPOIStressPoints>::CreateInstance(&cclone);
      CComPtr<IPOIStressPoints> pclone(cclone);

      // deep clone
      IteratorType it(m_Container.begin());
      IteratorType itend(m_Container.end());
      for (; it!=itend; it++)
      {
         IPOIStressPointsItem* item = it->second.m_T;
         CPOIStressPointsItem* citem = dynamic_cast<CPOIStressPointsItem*>(item);

         CComPtr<IStressPoints> lftcln, rghtcln;
         hr = citem->m_LeftStressPoints->Clone(&lftcln);
         hr = citem->m_RightStressPoints->Clone(&rghtcln);

         pclone->Insert(citem->m_Stage, lftcln, rghtcln);
      }

	   return pclone.CopyTo(Clone);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMModel);
   }
}


STDMETHODIMP CPOIStressPoints::get__EnumElements(/*[out, retval]*/ IEnumPOIStressPoints* *ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumPOIStressPoints, &IID_IEnumPOIStressPoints, IPOIStressPointsItem*, CustomCopyType, ContainerType> MyEnumType;
   CComObject<MyEnumType>* pEnum;
   HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IEnumPOIStressPoints> pHolder(pEnum); // memory leak avoidance

   hr = pEnum->Init( NULL, m_Container );
   if ( FAILED(hr) )
      return hr;

   *ppenum = pEnum;
   (*ppenum)->AddRef(); // for client

   return S_OK;
}


STDMETHODIMP CPOIStressPoints::get__NewEnum(IUnknown** ppUnk)
{
   CHECK_RETOBJ(ppUnk);

	*ppUnk = NULL;
	HRESULT hRes = S_OK;

   typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyType, ContainerType > VecEnumType;
	CComObject<VecEnumType>* p;
	hRes = CComObject<VecEnumType>::CreateInstance(&p);
	if (SUCCEEDED(hRes))
	{
		hRes = p->Init(this->GetControllingUnknown(), m_Container);
		if (hRes == S_OK)
			hRes = p->QueryInterface(IID_IUnknown, (void**)ppUnk);
	}
	if (hRes != S_OK)
		delete p;
	return hRes;
}

// _IStressPointsEvents
HRESULT CPOIStressPoints::OnStressPointsChanged(CollectionIndexType index)
{
   Fire_OnPOIStressPointsChanged(this);
   return S_OK;
}

HRESULT CPOIStressPoints::OnStressPointsAdded(CollectionIndexType index)
{
   Fire_OnPOIStressPointsChanged(this);
   return S_OK;
}

HRESULT CPOIStressPoints::OnStressPointsRemoved(CollectionIndexType index)
{
   Fire_OnPOIStressPointsChanged(this);
   return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CPOIStressPoints::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   this->Clear();

   hr = pload->BeginUnit(CComBSTR("POIStressPoints"));
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
      hr = pload->get_Property(_bstr_t("Count"),&var);
      if (FAILED(hr))
         return hr;

      long cnt = var;
      var.Clear();

      for (long i=0; i<cnt; i++)
      {
         CComPtr<IPOIStressPointsItem> item;

         hr = pload->get_Property(_bstr_t("POIStressPointsItem"),&var);
         if (FAILED(hr))
            return hr;

         hr = _CopyVariantToInterface<IPOIStressPointsItem>::copy(&item, &var);
         if (FAILED(hr))
            return STRLOAD_E_INVALIDFORMAT;

         CComBSTR stage;
         hr = item->get_Stage(&stage);
         if (FAILED(hr))
            return hr;

         CComPtr<IStressPoints> left, right;
         hr = item->get_LeftStressPoints(&left);
         if (FAILED(hr))
            return hr;

         hr = item->get_RightStressPoints(&right);
         if (FAILED(hr))
            return hr;

         hr = Insert(stage, left, right);
         if (FAILED(hr))
            return hr;
      }
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CPOIStressPoints::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("POIStressPoints"), MY_VER);

      CollectionIndexType cnt = m_Container.size();
      hr = psave->put_Property(CComBSTR("Count"),_variant_t(cnt));

      IteratorType it( m_Container.begin() );
      IteratorType itend( m_Container.end() );
      for (; it!=itend; it++)
      {
         IPOIStressPointsItem* item = it->second.m_T;

         hr = psave->put_Property(CComBSTR("POIStressPointsItem"),_variant_t(item));
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IPOI);
   }

   return S_OK;
}


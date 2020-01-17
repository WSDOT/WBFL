///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2020  Washington State Department of Transportation
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

// UnkArray.cpp : Implementation of CUnkArray
#include "stdafx.h"
#include "WBFLTools.h"
#include "UnkArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnkArray

STDMETHODIMP CUnkArray::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUnkArray
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CUnkArray::get_Item(CollectionIndexType relPosition, IUnknown* *pVal)
{
   if ( !IsValidIndex(relPosition,m_Values) )
      return E_INVALIDARG;


   try
   {
      return m_Values[relPosition].m_T.CopyTo(pVal);
   }
   catch(...)
   {
      return E_INVALIDARG;
   }

	return S_OK;
}

STDMETHODIMP CUnkArray::put_Item(CollectionIndexType relPosition, IUnknown* newVal)
{
   if ( !IsValidIndex(relPosition,m_Values) )
      return E_INVALIDARG;


   try
   {
      m_Values[relPosition] = newVal;
   }
   catch(...)
   {
      return E_INVALIDARG;
   }

	return S_OK;
}

STDMETHODIMP CUnkArray::Add(IUnknown* item)
{

   try
   {
      m_Values.push_back(CComPtr<IUnknown>(item));
   }
   catch(...)
   {
      return E_FAIL;
   }

	return S_OK;
}

STDMETHODIMP CUnkArray::Remove(CollectionIndexType relPosition)
{
   if ( !IsValidIndex(relPosition,m_Values) )
      return E_INVALIDARG;

   try
   {
      ContainerIterator iter = m_Values.begin();
      iter+= relPosition;

      m_Values.erase(iter);

   }
   catch(...)
   {
      return E_FAIL;
   }

	return S_OK;
}

STDMETHODIMP CUnkArray::Insert(CollectionIndexType relPosition, IUnknown* item)
{
   if ( !IsValidIndex(relPosition,m_Values) )
      return E_INVALIDARG;

   try
   {
      ContainerIterator iter = m_Values.begin();
      iter+= relPosition;

      m_Values.insert(iter, CComPtr<IUnknown>(item));

   }
   catch(...)
   {
      return E_FAIL;
   }

	return S_OK;
}

STDMETHODIMP CUnkArray::Reserve(CollectionIndexType count)
{
   if (count<0)
      return E_INVALIDARG;

   try
   {
   	m_Values.reserve(count);
   }
   catch(...)
   {
      return E_FAIL;
   }

	return S_OK;
}

STDMETHODIMP CUnkArray::Clear()
{
   try
   {
   	m_Values.clear();
   }
   catch(...)
   {
      return E_FAIL;
   }

	return S_OK;
}

class _CopyIUnknown
{
public:
	static HRESULT copy(VARIANT* p1, const CUnkArray::MemberType* p2)
	{
      CComVariant var(p2->m_T);
      HRESULT hr=var.Detach(p1);
      ATLASSERT(SUCCEEDED(hr));
		return S_OK;
	}
	static void init(VARIANT* ) {}
	static void destroy(VARIANT* p) {}
};

class _CopyIUnknownC
{
public:
   static HRESULT copy(IUnknown** p1, const CUnkArray::MemberType* p2)
	{
      CComPtr<IUnknown> bs(p2->m_T);
		*p1 = bs.Detach();
		return S_OK;
	}
	static void init(VARIANT* ) {}
	static void destroy(IUnknown** p) {}
};


STDMETHODIMP CUnkArray::get__NewEnum(IUnknown** ppUnk)
{
   CHECK_RETOBJ(ppUnk);

	*ppUnk = nullptr;
	HRESULT hRes = S_OK;

   typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, _CopyIUnknown, ContainerType > VecEnumType;
	CComObject<VecEnumType>* p;
	hRes = CComObject<VecEnumType>::CreateInstance(&p);
	if (SUCCEEDED(hRes))
	{
		hRes = p->Init(this->GetUnknown(), m_Values);
		if (hRes == S_OK)
			hRes = p->QueryInterface(IID_IUnknown, (void**)ppUnk);
	}
	if (hRes != S_OK)
		delete p;
	return hRes;
}

STDMETHODIMP CUnkArray::get__EnumElements(/*[out, retval]*/ IEnumUnkArray* *ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumUnkArray, &IID_IEnumUnkArray, IUnknown*, _CopyIUnknownC, ContainerType> MyEnumType;
   CComObject<MyEnumType>* pEnum;
   HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IEnumUnkArray> pHolder(pEnum); // memory leak avoidance

   hr = pEnum->Init( nullptr, m_Values );
   if ( FAILED(hr) )
      return hr;

   *ppenum = pEnum;
   (*ppenum)->AddRef(); // for client

   return S_OK;
}

STDMETHODIMP CUnkArray::get_Count(CollectionIndexType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Values.size();

	return S_OK;
}


STDMETHODIMP CUnkArray::Clone(IUnkArray **clone)
{
   HRESULT hr;

	CComObject<CUnkArray>* paro;
   hr = CComObject<CUnkArray>::CreateInstance(&paro);
   if (FAILED(hr))
      return hr;

   CComPtr<IUnkArray> par(paro);

   for (ContainerIterator it=m_Values.begin(); it!=m_Values.end(); it++)
   {
      paro->m_Values.push_back(*it);
   }

   *clone = par.Detach();

	return S_OK;
}

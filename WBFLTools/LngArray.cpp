///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
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

// LongArray.cpp : Implementation of CLongArray
#include "stdafx.h"
#include "WBFLTools.h"
#include "LngArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLongArray

STDMETHODIMP CLongArray::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILongArray
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLongArray::get_Item(CollectionIndexType relPosition, LONG *pVal)
{
   if ( !IsValidIndex(relPosition,m_Values) )
      return E_INVALIDARG;

   try
   {
      *pVal = m_Values[relPosition];
   }
   catch(...)
   {
      return E_INVALIDARG;
   }

	return S_OK;
}

STDMETHODIMP CLongArray::put_Item(CollectionIndexType relPosition, LONG newVal)
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

STDMETHODIMP CLongArray::Add(LONG item)
{
   try
   {
      m_Values.push_back(item);
   }
   catch(...)
   {
      return E_FAIL;
   }

	return S_OK;
}

STDMETHODIMP CLongArray::Remove(CollectionIndexType relPosition)
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

STDMETHODIMP CLongArray::Insert(CollectionIndexType relPosition, LONG item)
{
   if ( !IsValidIndex(relPosition,m_Values) )
      return E_INVALIDARG;

   try
   {
      ContainerIterator iter = m_Values.begin();
      iter+= relPosition;

      m_Values.insert(iter, item);

   }
   catch(...)
   {
      return E_FAIL;
   }

	return S_OK;
}

STDMETHODIMP CLongArray::Reserve(CollectionIndexType count)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

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

STDMETHODIMP CLongArray::Clear()
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

class _CopyLong
{
public:
	static HRESULT copy(VARIANT* p1, const LONG* p2)
	{
#if defined _WIN64
      p1->vt = VT_I8;
      p1->llVal = *p2;
#else
      p1->vt = VT_I4;
		p1->lVal = *p2;
#endif
		return S_OK;
	}
	static void init(VARIANT* ) {}
	static void destroy(VARIANT* p) {}
};

class _CopyLongC
{
public:
	static HRESULT copy(LONG* p1, const LONG* p2)
	{
		*p1 = *p2;
		return S_OK;
	}
	static void init(VARIANT* ) {}
	static void destroy(LONG* p) {}
};



STDMETHODIMP CLongArray::get__NewEnum(IUnknown** ppUnk)
{
   CHECK_RETOBJ(ppUnk);

	*ppUnk = nullptr;
	HRESULT hRes = S_OK;

   using VecEnumType = CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, _CopyLong, ContainerType >;
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

STDMETHODIMP CLongArray::get__EnumElements(/*[out, retval]*/ IEnumLongArray* *ppenum)
{
   CHECK_RETOBJ(ppenum);

   using MyEnumType = CComEnumOnSTL<IEnumLongArray, &IID_IEnumLongArray, LONG, _CopyLongC, ContainerType>;
   CComObject<MyEnumType>* pEnum;
   HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IEnumLongArray> pHolder(pEnum); // memory leak avoidance

   hr = pEnum->Init( nullptr, m_Values );
   if ( FAILED(hr) )
      return hr;

   *ppenum = pEnum;
   (*ppenum)->AddRef(); // for client

   return S_OK;
}

STDMETHODIMP CLongArray::get_Count(CollectionIndexType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Values.size();

	return S_OK;
}

STDMETHODIMP CLongArray::Clone(ILongArray **clone)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   HRESULT hr;

	CComObject<CLongArray>* paro;
   hr = CComObject<CLongArray>::CreateInstance(&paro);
   if (FAILED(hr))
      return hr;

   CComPtr<ILongArray> par(paro);

   for (ContainerIterator it=m_Values.begin(); it!=m_Values.end(); it++)
   {
      paro->m_Values.push_back(*it);
   }

   *clone = par.Detach();

	return S_OK;
}

STDMETHODIMP CLongArray::ReDim(CollectionIndexType size)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (size<0)
      return E_INVALIDARG;
   else if (size==0)
      m_Values.clear();
   else
 	   m_Values.assign(size, 0);

	return S_OK;
}

STDMETHODIMP CLongArray::Find(LONG value, CollectionIndexType *fndIndex)
{
   HRESULT hr = E_FAIL;

   CollectionIndexType idx = 0;
   for(ContainerIterator it=m_Values.begin(); it!=m_Values.end(); it++)
   {
      if(value == *it)
      {
         *fndIndex = idx;
         hr = S_OK;
         break;
      }
      idx++;
   }

	return hr;
}

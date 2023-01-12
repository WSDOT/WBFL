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

// IDArray.cpp : Implementation of CIDArray
#include "stdafx.h"
#include "WBFLTools.h"
#include "IDArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIDArray

STDMETHODIMP CIDArray::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IIDArray
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CIDArray::get_Item(CollectionIndexType relPosition, IDType *pVal)
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

STDMETHODIMP CIDArray::put_Item(CollectionIndexType relPosition, IDType newVal)
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

STDMETHODIMP CIDArray::Add(IDType item)
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

STDMETHODIMP CIDArray::Remove(CollectionIndexType relPosition)
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

STDMETHODIMP CIDArray::Insert(CollectionIndexType relPosition, IDType item)
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

STDMETHODIMP CIDArray::Reserve(CollectionIndexType count)
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

STDMETHODIMP CIDArray::Clear()
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

class _CopyID
{
public:
	static HRESULT copy(VARIANT* p1, const IDType* p2)
	{
      p1->vt = VT_I4;
		p1->llVal = *p2;
		return S_OK;
	}
	static void init(VARIANT* ) {}
	static void destroy(VARIANT* p) {}
};

class _CopyIDC
{
public:
	static HRESULT copy(IDType* p1, const IDType* p2)
	{
		*p1 = *p2;
		return S_OK;
	}
	static void init(VARIANT* ) {}
	static void destroy(IDType* p) {}
};



STDMETHODIMP CIDArray::get__NewEnum(IUnknown** ppUnk)
{
   CHECK_RETOBJ(ppUnk);

	*ppUnk = nullptr;
	HRESULT hRes = S_OK;

   typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, _CopyID, ContainerType > VecEnumType;
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

STDMETHODIMP CIDArray::get__EnumElements(/*[out, retval]*/ IEnumIDArray* *ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumIDArray, &IID_IEnumIDArray, IDType, _CopyIDC, ContainerType> MyEnumType;
   CComObject<MyEnumType>* pEnum;
   HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IEnumIDArray> pHolder(pEnum); // memory leak avoidance

   hr = pEnum->Init( nullptr, m_Values );
   if ( FAILED(hr) )
      return hr;

   *ppenum = pEnum;
   (*ppenum)->AddRef(); // for client

   return S_OK;
}

STDMETHODIMP CIDArray::get_Count(CollectionIndexType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Values.size();

	return S_OK;
}

STDMETHODIMP CIDArray::Clone(IIDArray **clone)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   HRESULT hr;

	CComObject<CIDArray>* paro;
   hr = CComObject<CIDArray>::CreateInstance(&paro);
   if (FAILED(hr))
      return hr;

   CComPtr<IIDArray> par(paro);

   for (ContainerIterator it=m_Values.begin(); it!=m_Values.end(); it++)
   {
      paro->m_Values.push_back(*it);
   }

   *clone = par.Detach();

	return S_OK;
}

STDMETHODIMP CIDArray::ReDim(CollectionIndexType size)
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

STDMETHODIMP CIDArray::Find(IDType value, CollectionIndexType *fndIndex)
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

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

// BstrArray.cpp : Implementation of CBstrArray
#include "stdafx.h"
#include "WBFLTools.h"
#include "BstrArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBstrArray

STDMETHODIMP CBstrArray::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBstrArray
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CBstrArray::get_Item(IndexType relPosition, BSTR *pVal)
{
   if ( !IsValidIndex(relPosition,m_Values) )
      return E_INVALIDARG;


   try
   {
       *pVal = m_Values[relPosition].m_T.Copy();
   }
   catch(...)
   {
      return E_INVALIDARG;
   }

	return S_OK;
}

STDMETHODIMP CBstrArray::put_Item(IndexType relPosition, BSTR newVal)
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

STDMETHODIMP CBstrArray::Add(BSTR item)
{
   try
   {
      m_Values.push_back(CComBSTR(item));
   }
   catch(...)
   {
      return E_FAIL;
   }

	return S_OK;
}

STDMETHODIMP CBstrArray::Remove(IndexType relPosition)
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

STDMETHODIMP CBstrArray::Insert(IndexType relPosition, BSTR item)
{
   if ( !IsValidIndex(relPosition,m_Values) )
      return E_INVALIDARG;

   try
   {
      ContainerIterator iter = m_Values.begin();
      iter+= relPosition;

      m_Values.insert(iter, CComBSTR(item));

   }
   catch(...)
   {
      return E_FAIL;
   }

	return S_OK;
}

STDMETHODIMP CBstrArray::Reserve(IndexType count)
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

STDMETHODIMP CBstrArray::Clear()
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

class _CopyBSTR
{
public:
	static HRESULT copy(VARIANT* p1, const CAdapt<CComBSTR>* p2)
	{
      CComVariant var(p2->m_T);
      HRESULT hr=var.Detach(p1);
      ATLASSERT(SUCCEEDED(hr));
		return S_OK;
	}
	static void init(VARIANT* ) {}
	static void destroy(VARIANT* p) {}
};

class _CopyBSTRC
{
public:
	static HRESULT copy(BSTR* p1, const CAdapt<CComBSTR>* p2)
	{
      *p1 = p2->m_T.Copy();
		return S_OK;
	}
   static void init(VARIANT* p) {::VariantInit(p);}
   static void destroy(BSTR* p) {::SysFreeString(*p);}
};


STDMETHODIMP CBstrArray::get__NewEnum(IUnknown** ppUnk)
{
   CHECK_RETOBJ(ppUnk);

	*ppUnk = nullptr;
	HRESULT hRes = S_OK;

   using VecEnumType = CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, _CopyBSTR, ContainerType >;
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

STDMETHODIMP CBstrArray::get__EnumElements(/*[out, retval]*/ IEnumBstrArray* *ppenum)
{
   CHECK_RETOBJ(ppenum);

   using MyEnumType = CComEnumOnSTL<IEnumBstrArray, &IID_IEnumBstrArray, BSTR, _CopyBSTRC, ContainerType>;
   CComObject<MyEnumType>* pEnum;
   HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IEnumBstrArray> pHolder(pEnum); // memory leak avoidance

   hr = pEnum->Init( nullptr, m_Values );
   if ( FAILED(hr) )
      return hr;

   *ppenum = pEnum;
   (*ppenum)->AddRef(); // for client

   return S_OK;
}

STDMETHODIMP CBstrArray::get_Count(IndexType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Values.size();

	return S_OK;
}

STDMETHODIMP CBstrArray::Clone(IBstrArray **clone)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   HRESULT hr;

	CComObject<CBstrArray>* paro;
   hr = CComObject<CBstrArray>::CreateInstance(&paro);
   if (FAILED(hr))
      return hr;

   CComPtr<IBstrArray> par(paro);

   for (ContainerIterator it=m_Values.begin(); it!=m_Values.end(); it++)
   {
      paro->m_Values.push_back(*it);
   }

   *clone = par.Detach();

	return S_OK;
}

STDMETHODIMP CBstrArray::ReDim(IndexType size)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (size<0)
      return E_INVALIDARG;
   else if (size==0)
      m_Values.clear();
   else
      // fill with blank strings
 	   m_Values.assign(size, CComBSTR() );


	return S_OK;
}

STDMETHODIMP CBstrArray::Find(BSTR value, IndexType *fndIndex)
{
   HRESULT hr = E_FAIL;

   IndexType idx = 0;
   for(ContainerIterator it=m_Values.begin(); it!=m_Values.end(); it++)
   {
      if(*it == value)
      {
         *fndIndex = idx;
         hr = S_OK;
         break;
      }
      idx++;
   }

	return hr;
}

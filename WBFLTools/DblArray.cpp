///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2021  Washington State Department of Transportation
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

// DblArray.cpp : Implementation of CDblArray
#include "stdafx.h"
#include "WBFLTools.h"
#include "DblArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDblArray

STDMETHODIMP CDblArray::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDblArray
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CDblArray::get_Item(CollectionIndexType relPosition, Float64 *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

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

STDMETHODIMP CDblArray::put_Item(CollectionIndexType relPosition, Float64 newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

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

STDMETHODIMP CDblArray::Add(Float64 item)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

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

STDMETHODIMP CDblArray::Remove(CollectionIndexType relPosition)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

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

STDMETHODIMP CDblArray::Insert(CollectionIndexType relPosition, Float64 item)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

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

STDMETHODIMP CDblArray::Reserve(CollectionIndexType count)
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

STDMETHODIMP CDblArray::Clear()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

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

class _CopyFloat64
{
public:
	static HRESULT copy(VARIANT* p1, const Float64* p2)
	{
      p1->vt = VT_R8;
		p1->dblVal = *p2;
		return S_OK;
	}
	static void init(VARIANT* ) {}
	static void destroy(VARIANT* p) {}
};

class _CopyFloat64C
{
public:
	static HRESULT copy(Float64* p1, const Float64* p2)
	{
		*p1 = *p2;
		return S_OK;
	}
	static void init(VARIANT* ) {}
	static void destroy(Float64* p) {}
};


STDMETHODIMP CDblArray::get__NewEnum(IUnknown** ppUnk)
{
   CHECK_RETOBJ(ppUnk);

	*ppUnk = nullptr;
	HRESULT hRes = S_OK;

   typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, _CopyFloat64, ContainerType > VecEnumType;
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

STDMETHODIMP CDblArray::get__EnumElements(/*[out, retval]*/ IEnumDblArray* *ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumDblArray, &IID_IEnumDblArray, Float64, _CopyFloat64C, ContainerType> MyEnumType;
   CComObject<MyEnumType>* pEnum;
   HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IEnumDblArray> pHolder(pEnum); // memory leak avoidance

   hr = pEnum->Init( nullptr, m_Values );
   if ( FAILED(hr) )
      return hr;

   *ppenum = pEnum;
   (*ppenum)->AddRef(); // for client

   return S_OK;
}

STDMETHODIMP CDblArray::get_Count(CollectionIndexType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Values.size();

	return S_OK;
}

STDMETHODIMP CDblArray::Clone(IDblArray **clone)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   HRESULT hr;

	CComObject<CDblArray>* paro;
   hr = CComObject<CDblArray>::CreateInstance(&paro);
   if (FAILED(hr))
      return hr;

   CComPtr<IDblArray> par(paro);

   for (ContainerIterator it=m_Values.begin(); it!=m_Values.end(); it++)
   {
      paro->m_Values.push_back(*it);
   }

   *clone = par.Detach();

	return S_OK;
}

STDMETHODIMP CDblArray::ReDim(CollectionIndexType size)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (size<0)
      return E_INVALIDARG;
   else if (size==0)
      m_Values.clear();
   else
 	   m_Values.assign(size, 0.0);

	return S_OK;
}

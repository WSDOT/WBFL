///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2020  Washington State Department of Transportation
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

// DataSet2d.cpp : Implementation of CDataSet2dImpl
#include "stdafx.h"
#include <WBFLDManipTools.h>
#include "DManipTools\DManipTools.h"
#include "DataSet2dImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataSet2dImpl

STDMETHODIMP CDataSet2dImpl::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_iDataSet2d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDataSet2dImpl::get_Item(CollectionIndexType index, IPoint2d** pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   (*pVal) = 0;
   if ( index < 0 || m_Container.size() <= index )
      return E_FAIL;

   ContainerItem ppt = m_Container[index];
   return ppt.m_T.CopyTo(pVal);

}

STDMETHODIMP_(void) CDataSet2dImpl::get_Count(CollectionIndexType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   *pVal = m_Container.size();
}

STDMETHODIMP_(void) CDataSet2dImpl::Add(IPoint2d *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   m_Container.emplace_back(pVal);
}

STDMETHODIMP CDataSet2dImpl::Insert(CollectionIndexType index, IPoint2d *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (index < 0 || index > m_Container.size()+1)
      return E_INVALIDARG;

   if (index==m_Container.size())

      Add(pVal);
   else
   {
      ContainerIterator it = m_Container.begin();
      it += index;
      m_Container.insert(it, ContainerItem(pVal));
   }

   return S_OK;
}

STDMETHODIMP CDataSet2dImpl::Remove(CollectionIndexType index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if ( index < 0 || index > m_Container.size()-1)
      return E_INVALIDARG;

      ContainerIterator it = m_Container.begin();
      it += index;
      m_Container.erase(it);

      return S_OK;
}

STDMETHODIMP_(void) CDataSet2dImpl::Clear()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   m_Container.clear();
}



HRESULT CDataSet2dImpl::Clone(/*[out]*/iDataSet2d* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new stress point collection and fill it up
   CComObject<CDataSet2dImpl>* pnew;
   HRESULT hr = CComObject<CDataSet2dImpl>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<CDataSet2dImpl> spisps(pnew); // holder for reference count

   for (ContainerIterator it= m_Container.begin(); it != m_Container.end(); it++)
   {
      // deep clone
      Float64 x, y;
      hr = it->m_T->get_X(&x);
      if (FAILED(hr))
         return hr;
      hr = it->m_T->get_Y(&y);
      if (FAILED(hr))
         return hr;

      CComPtr<IPoint2d> pp2d;
      pp2d.CoCreateInstance(CLSID_Point2d);
      
      hr = pp2d->put_X(x);
      if (FAILED(hr))
         return hr;
      hr = pp2d->put_Y(y);
      if (FAILED(hr))
         return hr;

      // add to collection
      spisps->Add(pp2d);
   }

   *pColl = spisps;
   (*pColl)->AddRef();

   return S_OK;
}


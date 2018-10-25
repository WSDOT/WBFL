///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// SegmentItem.cpp : Implementation of CSegmentItem
#include "stdafx.h"
#include "LoadCombinationsAgg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSegmentItem

STDMETHODIMP CLoadCombinationsAgg::InterfaceSupportsErrorInfo(REFIID riid)
{

	static const IID* arr[] = 
	{
		&IID_ISegmentItem
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CLoadCombinationsAgg::get_Item(/*[in]*/CollectionIndexType index, /*[out,retval]*/ ILoadCombination* *pVal)
{
   ATLASSERT(m_LoadCombinations!=NULL);
   return m_LoadCombinations->get_Item( index, pVal);
}

STDMETHODIMP CLoadCombinationsAgg::get__NewEnum(/*[out,retval]*/ IUnknown** retval)  
{
   ATLASSERT(m_LoadCombinations!=NULL);
   return m_LoadCombinations->get__NewEnum(retval);
}

STDMETHODIMP CLoadCombinationsAgg::get_Count(/*[out,retval]*/ CollectionIndexType *pVal)
{
   ATLASSERT(m_LoadCombinations!=NULL);
   return m_LoadCombinations->get_Count(pVal);
}

STDMETHODIMP CLoadCombinationsAgg::get__EnumElements(/*[out,retval]*/ IEnumLoadCombination* *pVal)
{
   ATLASSERT(m_LoadCombinations!=NULL);
   return m_LoadCombinations->get__EnumElements(pVal);
}

STDMETHODIMP CLoadCombinationsAgg::Find(/*[in]*/BSTR name, /*[out,retval]*/ILoadCombination** loadCombination)
{
   ATLASSERT(m_LoadCombinations!=NULL);
   return m_LoadCombinations->Find(name, loadCombination);
}

STDMETHODIMP CLoadCombinationsAgg::Add(/*[in]*/ILoadCombination* loadCombination)
{
   ATLASSERT(m_LoadCombinations!=NULL);
   return m_LoadCombinations->Add(loadCombination);
}

STDMETHODIMP CLoadCombinationsAgg::RemoveByName(/*[in]*/BSTR name)
{
   ATLASSERT(m_LoadCombinations!=NULL);
   return m_LoadCombinations->RemoveByName(name);
}

STDMETHODIMP CLoadCombinationsAgg::RemoveByIndex(/*[in]*/CollectionIndexType index, /*[out,retval]*/BSTR* name)
{
   ATLASSERT(m_LoadCombinations!=NULL);
   return m_LoadCombinations->RemoveByIndex(index, name);
}

STDMETHODIMP CLoadCombinationsAgg::Clone(/*[out,retval]*/ILoadCombinations** loadCombinations)
{
   ATLASSERT(m_LoadCombinations!=NULL);
   return m_LoadCombinations->Clone(loadCombinations);
}

STDMETHODIMP CLoadCombinationsAgg::Clear()
{
   ATLASSERT(m_LoadCombinations!=NULL);
   return m_LoadCombinations->Clear();
}


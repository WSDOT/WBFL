///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include "LoadCasesAgg.h"


/////////////////////////////////////////////////////////////////////////////
// CSegmentItem

STDMETHODIMP CLoadCasesAgg::InterfaceSupportsErrorInfo(REFIID riid)
{

	static const IID* arr[] = 
	{
		&IID_ISegmentItem
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CLoadCasesAgg::get_Item(/*[in]*/IndexType index, /*[out,retval]*/ ILoadCase* *pVal)
{
   ATLASSERT(m_LoadCases!=nullptr);
   return m_LoadCases->get_Item( index, pVal);
}

STDMETHODIMP CLoadCasesAgg::get__NewEnum(/*[out,retval]*/ IUnknown** retval)  
{
   ATLASSERT(m_LoadCases!=nullptr);
   return m_LoadCases->get__NewEnum(retval);
}

STDMETHODIMP CLoadCasesAgg::get_Count(/*[out,retval]*/ IndexType *pVal)
{
   ATLASSERT(m_LoadCases!=nullptr);
   return m_LoadCases->get_Count(pVal);
}

STDMETHODIMP CLoadCasesAgg::get__EnumElements(/*[out,retval]*/ IEnumLoadCase* *pVal)
{
   ATLASSERT(m_LoadCases!=nullptr);
   return m_LoadCases->get__EnumElements(pVal);
}

STDMETHODIMP CLoadCasesAgg::Find(/*[in]*/BSTR name, /*[out,retval]*/ILoadCase** loadCase)
{
   ATLASSERT(m_LoadCases!=nullptr);
   return m_LoadCases->Find(name, loadCase);
}

STDMETHODIMP CLoadCasesAgg::Add(/*[in]*/ILoadCase* loadCase)
{
   ATLASSERT(m_LoadCases!=nullptr);
   return m_LoadCases->Add(loadCase);
}

STDMETHODIMP CLoadCasesAgg::RemoveByName(/*[in]*/BSTR name)
{
   ATLASSERT(m_LoadCases!=nullptr);
   return m_LoadCases->RemoveByName(name);
}

STDMETHODIMP CLoadCasesAgg::RemoveByIndex(/*[in]*/IndexType index, /*[out,retval]*/BSTR* name)
{
   ATLASSERT(m_LoadCases!=nullptr);
   return m_LoadCases->RemoveByIndex(index, name);
}

STDMETHODIMP CLoadCasesAgg::Clone(/*[out,retval]*/ILoadCases** loadCases)
{
   ATLASSERT(m_LoadCases!=nullptr);
   return m_LoadCases->Clone(loadCases);
}

STDMETHODIMP CLoadCasesAgg::Clear()
{
   ATLASSERT(m_LoadCases!=nullptr);
   return m_LoadCases->Clear();
}


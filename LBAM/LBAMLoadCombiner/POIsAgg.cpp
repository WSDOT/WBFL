// SegmentItem.cpp : Implementation of CSegmentItem
#include "stdafx.h"
#include "POIsAgg.h"

/////////////////////////////////////////////////////////////////////////////
// CSegmentItem

STDMETHODIMP CPOIsAgg::InterfaceSupportsErrorInfo(REFIID riid)
{

	static const IID* arr[] = 
	{
		&IID_ISegmentItem
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CPOIsAgg::get_Item(/*[in]*/long index, /*[out,retval]*/ IPOI* *pVal)
{
   ATLASSERT(m_POIs!=NULL);
   return m_POIs->get_Item( index, pVal);
}

STDMETHODIMP CPOIsAgg::get__NewEnum(/*[out,retval]*/ IUnknown** retval)  
{
   ATLASSERT(m_POIs!=NULL);
   return m_POIs->get__NewEnum(retval);
}

STDMETHODIMP CPOIsAgg::get_Count(/*[out,retval]*/ long *pVal)
{
   ATLASSERT(m_POIs!=NULL);
   return m_POIs->get_Count(pVal);
}

STDMETHODIMP CPOIsAgg::get__EnumElements(/*[out,retval]*/ IEnumPOI* *pVal)
{
   ATLASSERT(m_POIs!=NULL);
   return m_POIs->get__EnumElements(pVal);
}

STDMETHODIMP CPOIsAgg::Find(/*[in]*/long id, /*[out,retval]*/IPOI** POI)
{
   ATLASSERT(m_POIs!=NULL);
   return m_POIs->Find(id, POI);
}

STDMETHODIMP CPOIsAgg::Add(/*[in]*/IPOI* POI)
{
   ATLASSERT(m_POIs!=NULL);
   return m_POIs->Add(POI);
}

STDMETHODIMP CPOIsAgg::RemoveByID(/*[in]*/long id)
{
   ATLASSERT(m_POIs!=NULL);
   return m_POIs->RemoveByID(id);
}

STDMETHODIMP CPOIsAgg::RemoveByIndex(/*[in]*/long index, /*[out,retval]*/long* id)
{
   ATLASSERT(m_POIs!=NULL);
   return m_POIs->RemoveByIndex(index, id);
}

STDMETHODIMP CPOIsAgg::Clone(/*[out,retval]*/IPOIs** POIs)
{
   ATLASSERT(m_POIs!=NULL);
   return m_POIs->Clone(POIs);
}

STDMETHODIMP CPOIsAgg::Clear()
{
   ATLASSERT(m_POIs!=NULL);
   return m_POIs->Clear();
}


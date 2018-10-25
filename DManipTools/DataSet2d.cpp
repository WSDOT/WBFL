// DataSet2d.cpp : Implementation of CDataSet2d
#include "stdafx.h"
#include "DManipTools.h"
#include "DataSet2d.h"
#include "Geometry_i.c"

/////////////////////////////////////////////////////////////////////////////
// CDataSet2d

STDMETHODIMP CDataSet2d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDataSet2d
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CDataSet2d::get_Name(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Name.Copy();

	return S_OK;
}

STDMETHODIMP CDataSet2d::put_Name(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Name = newVal;

	return S_OK;
}

STDMETHODIMP CDataSet2d::get_Color(COLORREF *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Color;

	return S_OK;
}

STDMETHODIMP CDataSet2d::put_Color(COLORREF newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Color = newVal;

	return S_OK;
}

STDMETHODIMP CDataSet2d::get_DataPointSymbolType(DataPointSymbolType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_SymbolType;

	return S_OK;
}

STDMETHODIMP CDataSet2d::put_DataPointSymbolType(DataPointSymbolType newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_SymbolType = newVal;

	return S_OK;
}


STDMETHODIMP CDataSet2d::Clone(/*[out]*/IDataSet2d* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new stress point collection and fill it up
   CComObject<CDataSet2d>* pnew;
   HRESULT hr = CComObject<CDataSet2d>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<CDataSet2d> spisps(pnew); // holder for reference count

   for (iterator it= begin(); it != end(); it++)
   {
      // deep clone
      double x, y;
      hr = it->second->get_X(&x);
      if (FAILED(hr))
         return hr;
      hr = it->second->get_Y(&y);
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
      hr = spisps->Add(pp2d);
      if (FAILED(hr))
         return hr;
   }

   // properties
   spisps->m_Color = m_Color;
   spisps->m_Name = m_Name;

   *pColl = spisps;
   (*pColl)->AddRef();

   return S_OK;
}

HRESULT CDataSet2d::SaveAdditionalProperties(IStructuredSave2 *save)
{
   HRESULT hr;
   hr = save->put_Property(CComBSTR("Name"), CComVariant(m_Name));
   if (FAILED(hr))
      return hr;

   hr = save->put_Property(CComBSTR("Color"),CComVariant((long)m_Color));
   if (FAILED(hr))
      return hr;

   return S_OK;
}

HRESULT CDataSet2d::LoadAdditionalProperties(IStructuredLoad2 *pload)
{
   HRESULT hr;
   CComVariant varname;
   hr = pload->get_Property(CComBSTR("Name"),&varname);
   if (FAILED(hr))
      return hr;

   m_Name = varname.bstrVal;

   CComVariant varlong;
   hr = pload->get_Property(CComBSTR("Color"),&varlong);
   if (FAILED(hr))
      return hr;

   m_Color = varlong.lVal;

   return S_OK;
}


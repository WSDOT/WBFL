///////////////////////////////////////////////////////////////////////
// Sections - Model bridge member cross sections
// Copyright © 1999-2018  Washington State Department of Transportation
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

// CompositeSectionItemEx.cpp : Implementation of CCompositeSectionItemEx
#include "stdafx.h"
#include "WBFLSections.h"
#include "CompositeSectionItemEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompositeSectionItemEx


STDMETHODIMP CCompositeSectionItemEx::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICompositeSectionItemEx,
		&IID_IStructuredStorage2
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCompositeSectionItemEx::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_Shape;
   if ( *pVal )
      (*pVal)->AddRef();


	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::putref_Shape(IShape *newVal)
{
   CHECK_IN(newVal);

   m_Shape = newVal;

	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::get_Efg(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Efg;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::put_Efg(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Efg = newVal;

	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::get_Ebg(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Ebg;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::put_Ebg(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Ebg = newVal;

	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::get_Dfg(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Dfg;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::put_Dfg(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Dfg = newVal;

	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::get_Dbg(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Dbg;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::put_Dbg(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Dbg = newVal;

	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::get_Structural(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_bStructural;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::put_Structural(VARIANT_BOOL newVal)
{
   m_bStructural = newVal;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CCompositeSectionItemEx::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("CompositeSectionItemEx"),1.0);
   pSave->put_Property(CComBSTR("Structural"),CComVariant(m_bStructural));
   pSave->put_Property(CComBSTR("Dfg"),CComVariant(m_Dfg));
   pSave->put_Property(CComBSTR("Dbg"),CComVariant(m_Dbg));
   pSave->put_Property(CComBSTR("Efg"),CComVariant(m_Efg));
   pSave->put_Property(CComBSTR("Ebg"),CComVariant(m_Ebg));
   pSave->put_Property(CComBSTR("Shape"),CComVariant(m_Shape));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCompositeSectionItemEx::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("CompositeSectionItem"));

   pLoad->get_Property(CComBSTR("Structural"),&var);
   m_bStructural = var.boolVal;

   pLoad->get_Property(CComBSTR("Dfg"),&var);
   m_Dfg = var.dblVal;

   pLoad->get_Property(CComBSTR("Dbg"),&var);
   m_Dbg = var.dblVal;

   pLoad->get_Property(CComBSTR("Efg"),&var);
   m_Efg = var.dblVal;

   pLoad->get_Property(CComBSTR("Ebg"),&var);
   m_Ebg = var.dblVal;

   pLoad->get_Property(CComBSTR("Shape"),&var);
   if ( FAILED( _CopyVariantToInterface<IShape>::copy(&m_Shape,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

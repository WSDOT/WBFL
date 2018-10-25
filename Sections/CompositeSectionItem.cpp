///////////////////////////////////////////////////////////////////////
// Sections - Model bridge member cross sections
// Copyright © 1999-2012  Washington State Department of Transportation
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

// CompositeSectionItem.cpp : Implementation of CCompositeSectionItem
#include "stdafx.h"
#include "WBFLSections.h"
#include "CompositeSectionItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompositeSectionItem


STDMETHODIMP CCompositeSectionItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICompositeSectionItemEx,
		&IID_ICompositeSectionItem,
		&IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCompositeSectionItem::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_Shape;
   if ( *pVal )
      (*pVal)->AddRef();


	return S_OK;
}

STDMETHODIMP CCompositeSectionItem::putref_Shape(IShape *newVal)
{
   CHECK_IN(newVal);

   m_Shape = newVal;

	return S_OK;
}

STDMETHODIMP CCompositeSectionItem::get_E(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_E;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItem::put_E(Float64 newVal)
{
   if ( newVal <= 0 )
      return E_INVALIDARG;

   m_E = newVal;

	return S_OK;
}

STDMETHODIMP CCompositeSectionItem::get_Density(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Density;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItem::put_Density(Float64 newVal)
{
   if ( newVal <= 0 )
      return E_INVALIDARG;

   m_Density = newVal;

	return S_OK;
}

STDMETHODIMP CCompositeSectionItem::get_Void(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_bVoid;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItem::put_Void(VARIANT_BOOL newVal)
{
   m_bVoid = newVal;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItem::get_Structural(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_bStructural;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItem::put_Structural(VARIANT_BOOL newVal)
{
   m_bStructural = newVal;
	return S_OK;
}

STDMETHODIMP CCompositeSectionItem::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CCompositeSectionItem::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("CompositeSectionItem"),1.0);
   pSave->put_Property(CComBSTR("Structural"),CComVariant(m_bStructural));
   pSave->put_Property(CComBSTR("Void"),CComVariant(m_bVoid));
   pSave->put_Property(CComBSTR("Density"),CComVariant(m_Density));
   pSave->put_Property(CComBSTR("E"),CComVariant(m_E));
   pSave->put_Property(CComBSTR("Shape"),CComVariant(m_Shape));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCompositeSectionItem::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("CompositeSectionItem"));

   pLoad->get_Property(CComBSTR("Structural"),&var);
   m_bStructural = var.boolVal;

   pLoad->get_Property(CComBSTR("Void"),&var);
   m_bVoid = var.boolVal;

   pLoad->get_Property(CComBSTR("Density"),&var);
   m_Density = var.dblVal;

   pLoad->get_Property(CComBSTR("E"),&var);
   m_E = var.dblVal;

   pLoad->get_Property(CComBSTR("Shape"),&var);
   if ( FAILED( _CopyVariantToInterface<IShape>::copy(&m_Shape,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

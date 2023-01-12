///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// CompositeShapeItem.cpp : Implementation of CCompositeShapeItem
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "CompositeShapeItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompositeShapeItem


STDMETHODIMP CCompositeShapeItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICompositeShapeItem,
		&IID_IStructuredStorage2
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCompositeShapeItem::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_Shape;
   if ( *pVal )
      (*pVal)->AddRef();


	return S_OK;
}

STDMETHODIMP CCompositeShapeItem::putref_Shape(IShape *newVal)
{
   CHECK_IN(newVal);

   m_Shape = newVal;

	return S_OK;
}

STDMETHODIMP CCompositeShapeItem::get_Void(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_bVoid;
	return S_OK;
}

STDMETHODIMP CCompositeShapeItem::put_Void(VARIANT_BOOL newVal)
{
   m_bVoid = newVal;
	return S_OK;
}

STDMETHODIMP CCompositeShapeItem::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CCompositeShapeItem::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("CompositeShapeItem"),1.0);
   pSave->put_Property(CComBSTR("Void"),CComVariant(m_bVoid));
   pSave->put_Property(CComBSTR("Shape"),CComVariant(m_Shape));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCompositeShapeItem::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("CompositeShapeItem"));

   pLoad->get_Property(CComBSTR("Void"),&var);
   m_bVoid = var.boolVal;

   pLoad->get_Property(CComBSTR("Shape"),&var);
   if ( FAILED( _CopyVariantToInterface<IShape>::copy(&m_Shape,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

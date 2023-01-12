///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// ProfileElement.cpp : Implementation of CProfileElement
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "ProfileElement.h"
#include "ProfilePoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CProfileElement
HRESULT CProfileElement::FinalConstruct()
{
   CComObject<CProfilePoint>* pp;
   CComObject<CProfilePoint>::CreateInstance(&pp);

   pp->QueryInterface(&m_Value);

   m_Type = pePoint;

   return S_OK;
}

void CProfileElement::FinalRelease()
{
}

STDMETHODIMP CProfileElement::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProfileElement,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CProfileElement::get_Type(ProfileElementType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Type;

	return S_OK;
}

STDMETHODIMP CProfileElement::get_Value(IUnknown** dispVal)
{
   CHECK_RETOBJ(dispVal);
   (*dispVal) = m_Value;
   (*dispVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CProfileElement::putref_Value(IUnknown* dispVal)
{
   CHECK_IN(dispVal);
   
   CComQIPtr<IProfilePoint> point(dispVal);
   CComQIPtr<IVertCurve> vc(dispVal);

   if( point == nullptr && vc == nullptr )
      return E_INVALIDARG;


   m_Type = (point != nullptr ? pePoint : peVertCurve);
   m_Value = dispVal;

	return S_OK;
}

STDMETHODIMP CProfileElement::Clone(IProfileElement* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CProfileElement>* pClone;
   CComObject<CProfileElement>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   switch( m_Type )
   {
   case pePoint:
      {
         CComQIPtr<IProfilePoint> pp(m_Value);
         CComPtr<IProfilePoint> clonePP;
         pp->Clone(&clonePP);

         CComQIPtr<IUnknown, &IID_IUnknown> dispClone(clonePP);
         (*clone)->putref_Value(dispClone);
      }
      break;

   case peVertCurve:
      {
         CComQIPtr<IVertCurve> vc(m_Value);
         CComPtr<IVertCurve> cloneVC;
         vc->Clone(&cloneVC);

         CComQIPtr<IUnknown, &IID_IUnknown> dispClone(cloneVC);
         (*clone)->putref_Value(dispClone);
      }
      break;
   }

   return S_OK;
}

STDMETHODIMP CProfileElement::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CProfileElement::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("ProfileElement"),1.0);
   pSave->put_Property(CComBSTR("Value"),CComVariant(m_Value));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CProfileElement::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("ProfileElement"));

   pLoad->get_Property(CComBSTR("Value"),&var);
   CComPtr<IUnknown> dispVal;
   _CopyVariantToInterface<IUnknown>::copy(&dispVal,&var);
   putref_Value(dispVal);

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// Material.cpp : Implementation of CMaterial
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "Material.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaterial
HRESULT CMaterial::FinalConstruct()
{
   return S_OK;
}

void CMaterial::FinalRelease()
{
}

STDMETHODIMP CMaterial::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMaterial,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CMaterial::Clone(IMaterial** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CMaterial>* pClone;
   CComObject<CMaterial>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->put_E(m_E);
   (*clone)->put_Density(m_Density);

   return S_OK;
}

STDMETHODIMP CMaterial::get_E(Float64* E)
{
   CHECK_RETVAL(E);
   (*E) = m_E;
   return S_OK;
}

STDMETHODIMP CMaterial::put_E(Float64 E)
{
   if ( E <= 0.0 )
      return E_INVALIDARG;

   if ( IsEqual(m_E,E) )
      return S_OK;

   m_E = E;
   Fire_OnMaterialChanged(this);
   return S_OK;
}

STDMETHODIMP CMaterial::get_Density(Float64* w)
{
   CHECK_RETVAL(w);
   (*w) = m_Density;
   return S_OK;
}

STDMETHODIMP CMaterial::put_Density(Float64 w)
{
   if ( IsEqual(m_Density,w) )
      return S_OK;

   m_Density = w;
   Fire_OnMaterialChanged(this);
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CMaterial::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("Material"));

   load->get_Property(CComBSTR("E"),&var);
   m_E = var.dblVal;

   load->get_Property(CComBSTR("Density"),&var);
   m_Density = var.dblVal;

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CMaterial::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("Material"),1.0);

   save->put_Property(CComBSTR("E"),CComVariant(m_E));
   save->put_Property(CComBSTR("Density"),CComVariant(m_Density));

   save->EndUnit();

   return S_OK;
}

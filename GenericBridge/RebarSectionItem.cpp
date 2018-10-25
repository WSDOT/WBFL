///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2018  Washington State Department of Transportation
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

// RebarSectionItem.cpp : Implementation of CRebarSectionItem
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "RebarSectionItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRebarSectionItem

STDMETHODIMP CRebarSectionItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRebarSectionItem,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////
// IRebarSectionItem implementation

HRESULT CRebarSectionItem::Init(IPoint2d* pLocation,Float64 start,Float64 end,HookType hkLeft,HookType hkRight,IRebar* pRebar)
{
   m_Location = pLocation;
   m_LeftExtension = start;
   m_RightExtension = end;
   m_LeftHookType = hkLeft;
   m_RightHookType = hkRight;
   m_Rebar = pRebar;

   return S_OK;
}

STDMETHODIMP CRebarSectionItem::get_Location(IPoint2d** location)
{
   CHECK_RETOBJ(location);
   (*location) = m_Location;
   (*location)->AddRef();
   return S_OK;
}

STDMETHODIMP CRebarSectionItem::get_LeftExtension(Float64* dist)
{
   CHECK_RETVAL(dist);
   *dist = m_LeftExtension;
   return S_OK;
}

STDMETHODIMP CRebarSectionItem::get_RightExtension(Float64* dist)
{
   CHECK_RETVAL(dist);
   *dist = m_RightExtension;
   return S_OK;
}

STDMETHODIMP CRebarSectionItem::get_LeftHook(/*[out,retval]*/HookType* hook)
{
   CHECK_RETVAL(hook);
   *hook = m_LeftHookType;
   return S_OK;
}

STDMETHODIMP CRebarSectionItem::get_RightHook(/*[out,retval]*/HookType* hook)
{
   CHECK_RETVAL(hook);
   *hook = m_RightHookType;
   return S_OK;
}

STDMETHODIMP CRebarSectionItem::get_Rebar(IRebar** rebar)
{
   CHECK_RETOBJ(rebar);
   (*rebar) = m_Rebar;
   (*rebar)->AddRef();
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CRebarSectionItem::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("RebarSectionItem"));

   load->get_Property(CComBSTR("Location"),&var);
    _CopyVariantToInterface<IPoint2d>::copy(&m_Location,&var);

    load->get_Property(CComBSTR("LeftExtension"),&var);
    m_LeftExtension = var.dblVal;

    load->get_Property(CComBSTR("RightExtension"),&var);
    m_RightExtension = var.dblVal;

   load->get_Property(CComBSTR("Rebar"),&var);
    _CopyVariantToInterface<IRebar>::copy(&m_Rebar,&var);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CRebarSectionItem::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("RebarSectionItem"),1.0);
   save->put_Property(CComBSTR("Location"),CComVariant(m_Location));
   save->put_Property(CComBSTR("LeftExtension"),CComVariant(m_LeftExtension));
   save->put_Property(CComBSTR("RightExtension"),CComVariant(m_RightExtension));
   save->put_Property(CComBSTR("Rebar"),CComVariant(m_Rebar));
   save->EndUnit();

   return S_OK;
}

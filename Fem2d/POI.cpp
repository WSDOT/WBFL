///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2025  Washington State Department of Transportation
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
// POI.cpp : Implementation of CPOI
#include "stdafx.h"
#include "POI.h"
#include "ModelEvents.h"


#define ON_CHANGED() ATLASSERT(m_pModel!=0); \
                               m_pModel->OnPOIChanged(this);

/////////////////////////////////////////////////////////////////////////////
// CPOI
HRESULT CPOI::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, PoiIDType ID, MemberIDType memberID, Float64 loc)
{
   if (loc < -1.0)
      return CComCoClass<CPOI,&CLSID_Fem2dPOI>::Error(IDS_E_INVALID_POI_LOCATION, IDH_E_INVALID_POI_LOCATION, GetHelpFile(), IID_IFem2dPOI, FEM2D_E_INVALID_POI_LOCATION);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  // have to save as CModel to get at C++ event handlers
   m_ID = ID;
   m_MemberID = memberID;
   m_Location = loc;

   return S_OK;
}

static const Float64 MY_VER=1.0;

STDMETHODIMP CPOI::Load(/*[in]*/ IStructuredLoad2 *pload)
{
   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("POI"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      CComVariant varlong;
      varlong.vt = VT_I4;
      hr = pload->get_Property(CComBSTR("ID"),&varlong);
      if (FAILED(hr))
         return hr;

      m_ID = varlong.lVal;

      hr = pload->get_Property(CComBSTR("MemberID"),&varlong);
      if (FAILED(hr))
         return hr;

      m_MemberID = varlong.lVal;

      CComVariant vardbl;
      vardbl.vt = VT_R8;
      hr = pload->get_Property(CComBSTR("Location"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Location = vardbl.dblVal;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CPOI::Save(/*[in]*/ IStructuredSave2 *psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("POI"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      hr = psave->put_Property(CComBSTR("ID"),CComVariant(m_ID));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("MemberID"),CComVariant(m_MemberID));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Location"),CComVariant(m_Location));
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   if (FAILED(hr))
      return hr;

   return S_OK;
}

STDMETHODIMP CPOI::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dPOI
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPOI::get_ID(PoiIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_ID;

	return S_OK;
}

STDMETHODIMP CPOI::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_MemberID;

	return S_OK;
}

STDMETHODIMP CPOI::put_MemberID(MemberIDType newVal)
{
   if (m_MemberID != newVal)
   {
	   m_MemberID = newVal;
      ON_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CPOI::get_Location(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Location;

	return S_OK;
}

STDMETHODIMP CPOI::put_Location(Float64 newVal)
{
   if (newVal < -1.0)
      return CComCoClass<CPOI,&CLSID_Fem2dPOI>::Error(IDS_E_INVALID_POI_LOCATION, IDH_E_INVALID_POI_LOCATION, GetHelpFile(), IID_IFem2dPOI, FEM2D_E_INVALID_POI_LOCATION);

   if (m_Location != newVal)
   {
	   m_Location = newVal;
      ON_CHANGED()
   }
	return S_OK;
}

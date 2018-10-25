///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2010  Washington State Department of Transportation
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
// JointDisplacement.cpp : Implementation of CJointDisplacement
#include "stdafx.h"
#include "JointDisplacement.h"
#include "ModelEvents.h"
#include "Loading.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ON_LOAD_CHANGED() ATLASSERT(m_pModel!=0); \
                          ATLASSERT(m_pLoading!=0);\
                          LoadCaseIDType Loadingid; \
                          m_pLoading->get_ID(&Loadingid); \
                          m_pModel->OnJointDisplacementChanged(this, Loadingid);

/////////////////////////////////////////////////////////////////////////////
// CJointDisplacement
void CJointDisplacement::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, LoadIDType ID, JointIDType jointID, Float64 Dx, Float64 Dy, Float64 Rz)
{
   ATLASSERT(pLoading!=0);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  // C++ model event handlers
   m_pLoading = pLoading;
   m_ID = ID;
   m_JointID = jointID;
   m_Dx = Dx;
   m_Dy = Dy;
   m_Rz = Rz;
}

STDMETHODIMP CJointDisplacement::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dJointDisplacement
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

static const Float64 MY_VER=1.0;

STDMETHODIMP CJointDisplacement::Load(/*[in]*/ IStructuredLoad2 *pload)
{
   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("JointDisplacement"));
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

      hr = pload->get_Property(CComBSTR("JointID"),&varlong);
      if (FAILED(hr))
         return hr;

      m_JointID = varlong.lVal;

      CComVariant vardbl;
      vardbl.vt = VT_R8;
      hr = pload->get_Property(CComBSTR("Dx"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Dx = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("Dy"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Dy = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("Rz"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Rz = vardbl.dblVal;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CJointDisplacement::Save(/*[in]*/ IStructuredSave2 *psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("JointDisplacement"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      hr = psave->put_Property(CComBSTR("ID"),CComVariant(m_ID));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("JointID"),CComVariant(m_JointID));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Dx"),CComVariant(m_Dx));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Dy"),CComVariant(m_Dy));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Rz"),CComVariant(m_Rz));
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   if (FAILED(hr))
      return hr;

   return S_OK;
}


STDMETHODIMP CJointDisplacement::get_ID(LoadIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_ID;

	return S_OK;
}

STDMETHODIMP CJointDisplacement::get_JointID(JointIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_JointID;

	return S_OK;
}

STDMETHODIMP CJointDisplacement::put_JointID(JointIDType newVal)
{
   if (m_JointID != newVal)
   {
	   m_JointID = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointDisplacement::get_Dx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Dx;

	return S_OK;
}

STDMETHODIMP CJointDisplacement::put_Dx(Float64 newVal)
{
   if (m_Dx != newVal)
   {
	   m_Dx = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointDisplacement::get_Dy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Dy;

	return S_OK;
}

STDMETHODIMP CJointDisplacement::put_Dy(Float64 newVal)
{
   if (m_Dy != newVal)
   {
	   m_Dy = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointDisplacement::get_Rz(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Rz;

	return S_OK;
}

STDMETHODIMP CJointDisplacement::put_Rz(Float64 newVal)
{
   if (m_Rz != newVal)
   {
	   m_Rz = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointDisplacement::SetDisplacement(Float64 Dx, Float64 Dy, Float64 Rz)
{
	m_Dx = Dx;
   m_Dy = Dy;
   m_Rz = Rz;

   ON_LOAD_CHANGED()
	return S_OK;
}

STDMETHODIMP CJointDisplacement::GetDisplacement(Float64 *Dx, Float64 *Dy, Float64 *Rz)
{
   CHECK_RETVAL(Dx);
   CHECK_RETVAL(Dy);
   CHECK_RETVAL(Rz);
	*Dx = m_Dx;
   *Dy = m_Dy;
   *Rz = m_Rz;

	return S_OK;
}

STDMETHODIMP CJointDisplacement::get_Loading(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
	ATLASSERT(m_pLoading!=0);

   LoadCaseIDType id;
   m_pLoading->get_ID(&id);
   *pVal = id;

	return S_OK;
}

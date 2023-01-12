///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
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
// JointLoad.cpp : Implementation of CJointLoad
#include "stdafx.h"
#include "JointLoad.h"
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
                          m_pModel->OnJointLoadChanged(this, Loadingid);

/////////////////////////////////////////////////////////////////////////////
// CJointLoad
void CJointLoad::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, LoadIDType ID, JointIDType jointID, Float64 Fx, Float64 Fy, Float64 Mz)
{
   ATLASSERT(pLoading!=0);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  // C++ event handlers
   m_pLoading = pLoading;
   m_ID = ID;
   m_JointID = jointID;
   m_Fx = Fx;
   m_Fy = Fy;
   m_Mz = Mz;
}

STDMETHODIMP CJointLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dJointLoad
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

static const Float64 MY_VER=1.0;

STDMETHODIMP CJointLoad::Load(/*[in]*/ IStructuredLoad2 *pload)
{
   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("JointLoad"));
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
      hr = pload->get_Property(CComBSTR("Fx"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Fx = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("Fy"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Fy = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("Mz"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Mz = vardbl.dblVal;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CJointLoad::Save(/*[in]*/ IStructuredSave2 *psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("JointLoad"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      hr = psave->put_Property(CComBSTR("ID"),CComVariant(m_ID));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("JointID"),CComVariant(m_JointID));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Fx"),CComVariant(m_Fx));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Fy"),CComVariant(m_Fy));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Mz"),CComVariant(m_Mz));
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   if (FAILED(hr))
      return hr;

   return S_OK;
}



STDMETHODIMP CJointLoad::get_ID(LoadIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_ID;

	return S_OK;
}

STDMETHODIMP CJointLoad::get_JointID(JointIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_JointID;

	return S_OK;
}

STDMETHODIMP CJointLoad::put_JointID(JointIDType newVal)
{
   if (m_JointID != newVal)
   {
	   m_JointID = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointLoad::get_Fx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Fx;

	return S_OK;
}

STDMETHODIMP CJointLoad::put_Fx(Float64 newVal)
{
   if (m_Fx != newVal)
   {
	   m_Fx = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointLoad::get_Fy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Fy;

	return S_OK;
}

STDMETHODIMP CJointLoad::put_Fy(Float64 newVal)
{
   if (m_Fy != newVal)
   {
	   m_Fy = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointLoad::get_Mz(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Mz;

	return S_OK;
}

STDMETHODIMP CJointLoad::put_Mz(Float64 newVal)
{
   if (m_Mz != newVal)
   {
	   m_Mz = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointLoad::SetForce(Float64 Fx, Float64 Fy, Float64 Mz)
{
	m_Fx = Fx;
   m_Fy = Fy;
   m_Mz = Mz;

   ON_LOAD_CHANGED()
	return S_OK;
}

STDMETHODIMP CJointLoad::GetForce(Float64 *Fx, Float64 *Fy, Float64 *Mz)
{
   CHECK_RETVAL(Fx);
   CHECK_RETVAL(Fy);
   CHECK_RETVAL(Mz);
	*Fx = m_Fx;
   *Fy = m_Fy;
   *Mz = m_Mz;

	return S_OK;
}

STDMETHODIMP CJointLoad::get_Loading(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
	ATLASSERT(m_pLoading!=0);

   LoadCaseIDType id;
   m_pLoading->get_ID(&id);
   *pVal = id;

	return S_OK;
}

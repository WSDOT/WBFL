///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// LRFDSolutionEx.cpp : Implementation of CLRFDSolutionEx
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "LRFDSolutionEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLRFDSolutionEx
HRESULT CLRFDSolutionEx::FinalConstruct()
{
   m_fs.CoCreateInstance(CLSID_DblArray);
   m_fps.CoCreateInstance(CLSID_DblArray);
   return S_OK;
}

void CLRFDSolutionEx::FinalRelease()
{
   m_fs.Release();
   m_fps.Release();
}

STDMETHODIMP CLRFDSolutionEx::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRCSolutionEx,
      &IID_ILRFDSolutionEx
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////////
// IRCSolutionEx
STDMETHODIMP CLRFDSolutionEx::InitSolution(Float64 Mn,Float64 c,IDblArray* fs,IDblArray* fps,Float64 Cflange,Float64 Cweb,Float64 T,Float64 Yflange,Float64 Yweb)
{
   ATLASSERT(false); // don't call this method, use InitLRFDSolution
   m_Alpha1  = 99999;
   m_Beta1   = 99999;
   m_Mn      = Mn;
   m_c       = c;
   m_Cflange = Cflange;
   m_Cweb    = Cweb;
   m_T       = T;
   m_Yflange = Yflange;
   m_Yweb    = Yweb;

   m_fs.Release();
   fs->Clone(&m_fs);

   m_fps.Release();
   fps->Clone(&m_fps);

	return S_OK;
}

STDMETHODIMP CLRFDSolutionEx::get_Mn(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Mn;
	return S_OK;
}

STDMETHODIMP CLRFDSolutionEx::get_NeutralAxisDepth(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_c;
   return S_OK;
}

STDMETHODIMP CLRFDSolutionEx::get_fs(IDblArray** pVal)
{
   return m_fs->Clone(pVal);
}

STDMETHODIMP CLRFDSolutionEx::get_fps(IDblArray** pVal)
{
   return m_fps->Clone(pVal);
}

STDMETHODIMP CLRFDSolutionEx::get_Cflange(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Cflange;
	return S_OK;
}

STDMETHODIMP CLRFDSolutionEx::get_Cweb(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Cweb;
	return S_OK;
}

STDMETHODIMP CLRFDSolutionEx::get_T(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_T;
	return S_OK;
}

STDMETHODIMP CLRFDSolutionEx::get_Yflange(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Yflange;
	return S_OK;
}

STDMETHODIMP CLRFDSolutionEx::get_Yweb(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Yweb;
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////
// ILRFDSolutionEx
STDMETHODIMP CLRFDSolutionEx::InitLRFDSolution(Float64 alpha1,Float64 beta1,Float64 Mn,Float64 c,IDblArray* fs,IDblArray* fps,Float64 Cflange,Float64 Cweb,Float64 T,Float64 Yflange,Float64 Yweb)
{
   m_Alpha1  = alpha1;
   m_Beta1   = beta1;
   m_Mn      = Mn;
   m_c       = c;
   m_Cflange = Cflange;
   m_Cweb    = Cweb;
   m_T       = T;
   m_Yflange = Yflange;
   m_Yweb    = Yweb;

   m_fs.Release();
   fs->Clone(&m_fs);

   m_fps.Release();
   fps->Clone(&m_fps);

	return S_OK;
}

STDMETHODIMP CLRFDSolutionEx::get_Alpha1(Float64* pAlpha1)
{
   CHECK_RETVAL(pAlpha1);
   *pAlpha1 = m_Alpha1;
   return S_OK;
}

STDMETHODIMP CLRFDSolutionEx::get_Beta1(Float64* pBeta1)
{
   CHECK_RETVAL(pBeta1);
   *pBeta1 = m_Beta1;
   return S_OK;
}

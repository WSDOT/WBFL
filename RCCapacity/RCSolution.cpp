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

// RCSolution.cpp : Implementation of CRCSolution
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "RCSolution.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRCSolution
STDMETHODIMP CRCSolution::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRCSolution
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CRCSolution::InitSolution(Float64 Mn,Float64 c,Float64 fps,Float64 Cflange,Float64 Cweb,Float64 T,Float64 Yflange,Float64 Yweb,VARIANT_BOOL bIsOverReinforced)
{
   m_Mn      = Mn;
   m_c       = c;
   m_fps     = fps;
   m_Cflange = Cflange;
   m_Cweb    = Cweb;
   m_T       = T;
   m_Yflange = Yflange;
   m_Yweb    = Yweb;
   m_bIsOverReinforced = bIsOverReinforced;

	return S_OK;
}

STDMETHODIMP CRCSolution::get_Mn(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Mn;
	return S_OK;
}

STDMETHODIMP CRCSolution::get_IsOverReinforced(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_bIsOverReinforced;
	return S_OK;
}

STDMETHODIMP CRCSolution::get_NeutralAxisDepth(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_c;
   return S_OK;
}

STDMETHODIMP CRCSolution::get_fps(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_fps;
   return S_OK;
}

STDMETHODIMP CRCSolution::get_Cflange(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Cflange;
	return S_OK;
}

STDMETHODIMP CRCSolution::get_Cweb(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Cweb;
	return S_OK;
}

STDMETHODIMP CRCSolution::get_T(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_T;
	return S_OK;
}

STDMETHODIMP CRCSolution::get_Yflange(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Yflange;
	return S_OK;
}

STDMETHODIMP CRCSolution::get_Yweb(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Yweb;
	return S_OK;
}

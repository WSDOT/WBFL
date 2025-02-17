///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright � 1999-2025  Washington State Department of Transportation
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

// StationEquation.cpp : Implementation of CStationEquation
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "StationEquation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStationEquation

STDMETHODIMP CStationEquation::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStationEquation,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IStation Equation
STDMETHODIMP CStationEquation::GetEquation(Float64* pBackStation,Float64* pAheadStation)
{
   CHECK_RETVAL(pBackStation);
   CHECK_RETVAL(pAheadStation);

   auto [back, ahead, normal] = m_Equation.GetEquationParameters();
   *pBackStation  = back;
   *pAheadStation = ahead;

   return S_OK;
}

STDMETHODIMP CStationEquation::get_Back(Float64* pBack)
{
   CHECK_RETVAL(pBack);

   *pBack = m_Equation.GetBack();

   return S_OK;
}

STDMETHODIMP CStationEquation::get_Ahead(Float64* pAhead)
{
   CHECK_RETVAL(pAhead);

   *pAhead = m_Equation.GetAhead();

   return S_OK;
}

STDMETHODIMP CStationEquation::get_NormalizedValue(Float64* pNormalizedValue)
{
   CHECK_RETVAL(pNormalizedValue);

   *pNormalizedValue = m_Equation.GetNormalizedStation();;

   return S_OK;
}

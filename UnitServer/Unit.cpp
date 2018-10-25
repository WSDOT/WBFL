///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
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

// Unit.cpp : Implementation of CUnit
#include "stdafx.h"
#include "WbflUnitServer.h"
#include "Unit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CUnit
void CUnit::Init( IUnitServer* pUnitServer,IUnitType* pUnitType,Float64 pre,Float64 cf,Float64 post,BSTR tag,UnitSystemType unitSystem)
{
   ATLASSERT( pUnitServer != 0 );
   ATLASSERT( pUnitType   != 0 );

   m_pUnitServer = pUnitServer;
   m_pUnitType   = pUnitType;

   m_Tag = tag;

   m_PreTerm    = pre;
   m_ConvFactor = cf;
   m_PostTerm   = post;

   _ASSERTE( unitSystem == unitsSI || unitSystem == unitsUS || unitSystem == (unitsSI+unitsUS) );
   m_UnitSystem = unitSystem;
}

STDMETHODIMP CUnit::get_Tag(BSTR * pVal)
{
   CHECK_RETSTRING(pVal);

   *pVal = m_Tag.Copy();
	return S_OK;
}

STDMETHODIMP CUnit::get_PreTerm(Float64 * pVal)
{
   CHECK_RETVAL( pVal );

   *pVal = m_PreTerm;
	return S_OK;
}

STDMETHODIMP CUnit::get_ConvFactor(Float64 * pVal)
{
   CHECK_RETVAL( pVal );

   *pVal = m_ConvFactor;
	return S_OK;
}

STDMETHODIMP CUnit::get_PostTerm(Float64 * pVal)
{
   CHECK_RETVAL( pVal );

   *pVal = m_PostTerm;
	return S_OK;
}

STDMETHODIMP CUnit::get_UnitSystem(UnitSystemType * pVal)
{
   CHECK_RETVAL( pVal );

   *pVal = m_UnitSystem;
	return S_OK;
}

STDMETHODIMP CUnit::get_UnitType(IUnitType** ppUnitType)
{
   CHECK_RETOBJ( ppUnitType );

   *ppUnitType = m_pUnitType;
   (*ppUnitType)->AddRef();
   return S_OK;
}

STDMETHODIMP CUnit::get_UnitServer(IUnitServer** unitServer)
{
   CHECK_RETOBJ( unitServer );

   *unitServer = m_pUnitServer;
   (*unitServer)->AddRef();

   return S_OK;
}

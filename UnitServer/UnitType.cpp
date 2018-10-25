///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// UnitType.cpp : Implementation of CUnitType
#include "stdafx.h"
#include "WbflUnitServer.h"
#include "UnitType.h"
#include "Units.h"
#include "Unit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CUnitType
void CUnitType::Init( IUnitServer* pUnitServer, BSTR bstrLabel, Float64 m,Float64 l,Float64 t,Float64 k,Float64 a)
{
   ATLASSERT( pUnitServer != 0 );
   ATLASSERT( bstrLabel != 0 );

   m_pUnitServer = pUnitServer;

   m_Mass   = m;
   m_Length = l;
   m_Time   = t;
   m_Temp   = k;
   m_Angle  = a;

   m_bstrLabel = bstrLabel;

   CComObject<CUnits>* pUnits;
   CComObject<CUnits>::CreateInstance( &pUnits );
   pUnits->Init( m_pUnitServer, this );
   pUnits->QueryInterface( IID_IUnits, (void**)&m_pUnits );

   // Hookup to the connection point
   m_pUnits.Advise( GetUnknown(), IID_IUnitsEventSink, &m_Cookie );
   InternalRelease(); // Break circular reference
}

HRESULT CUnitType::FinalConstruct()
{
   return S_OK;
}

void CUnitType::FinalRelease()
{
   InternalAddRef(); // Counteract Release in Init()

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( m_pUnits );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IUnitsEventSink, &pCP );
   pCP->Unadvise( m_Cookie );

}

STDMETHODIMP CUnitType::AddUnit(BSTR bstrTag,Float64 preTerm,Float64 cf,Float64 postTerm,UnitSystemType unitSystem)
{
   CHECK_IN(bstrTag);

   CComPtr<IUnit> pUnit;
   return m_pUnits->Add(bstrTag,preTerm,cf,postTerm,unitSystem,&pUnit);
}

STDMETHODIMP CUnitType::get_Mass(Float64 * pMass)
{
   CHECK_RETVAL(pMass);

   *pMass   = m_Mass;
	return S_OK;
}

STDMETHODIMP CUnitType::get_Length(Float64 * pLength)
{
   CHECK_RETVAL(pLength);
   *pLength   = m_Length;
	return S_OK;
}

STDMETHODIMP CUnitType::get_Time(Float64 * pTime)
{
   CHECK_RETVAL(pTime);

   *pTime   = m_Time;
	return S_OK;
}

STDMETHODIMP CUnitType::get_Temperature(Float64 * pTemp)
{
   CHECK_RETVAL(pTemp);
   *pTemp   = m_Temp;
	return S_OK;
}

STDMETHODIMP CUnitType::get_Angle(Float64 * pAngle)
{
   CHECK_RETVAL( pAngle );
   *pAngle   = m_Angle;
	return S_OK;
}

STDMETHODIMP CUnitType::get_Label(BSTR * pLabel)
{
   CHECK_RETSTRING(pLabel);
   *pLabel = m_bstrLabel.Copy();
	return S_OK;
}

STDMETHODIMP CUnitType::get_Units(IUnits** ppUnits)
{
   CHECK_RETOBJ(ppUnits);

   *ppUnits = m_pUnits;
   (*ppUnits)->AddRef();
   return S_OK;
}

STDMETHODIMP CUnitType::get_UnitServer(IUnitServer** unitServer)
{
   CHECK_RETOBJ(unitServer);

   (*unitServer) = m_pUnitServer;
   (*unitServer)->AddRef();

   return S_OK;
}

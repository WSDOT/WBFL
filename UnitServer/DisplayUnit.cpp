///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// DisplayUnit.cpp : Implementation of CDisplayUnit
#include "stdafx.h"
#include "WBFLUnitServer.h"
#include "DisplayUnit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDisplayUnit
void CDisplayUnit::AdviseFormatter()
{
   m_pFormatter.Advise( GetUnknown(), IID_IDisplayUnitFormatterEvents,&m_Cookie);
   InternalRelease(); // Break circular reference
}

void CDisplayUnit::UnadviseFormatter()
{
   if ( m_pFormatter == 0 )
      return;

   InternalAddRef(); // Counteract Release() in AdviseUnitFormatter()

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( m_pFormatter );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IDisplayUnitFormatterEvents, &pCP );
   pCP->Unadvise( m_Cookie );
}

void CDisplayUnit::FinalRelease()
{
   UnadviseFormatter();
}

STDMETHODIMP CDisplayUnit::get_Formatter(IDisplayUnitFormatter** formatter)
{
   CHECK_RETOBJ(formatter);
   m_pFormatter.QueryInterface(formatter);
   return S_OK;
}

STDMETHODIMP CDisplayUnit::putref_Formatter(IDisplayUnitFormatter* formatter)
{
   CHECK_IN(formatter);

   if ( !m_pFormatter.IsEqualObject(formatter) )
   {
      UnadviseFormatter();
      m_pFormatter = formatter;
      AdviseFormatter();

      Fire_OnFormatChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CDisplayUnit::get_Unit(IUnit** unit)
{
   CHECK_RETOBJ(unit);
   return m_pUnit.QueryInterface(unit);
}

STDMETHODIMP CDisplayUnit::get_UnitTag(BSTR* unitTag)
{
   CHECK_RETSTRING(unitTag);
   return m_pUnit->get_Tag(unitTag);
}

STDMETHODIMP CDisplayUnit::get_UnitSystem(UnitSystemType* unitSystem)
{
   CHECK_RETVAL(unitSystem);
   *unitSystem = m_UnitSystem;
   return S_OK;
}

STDMETHODIMP CDisplayUnit::IsDefault(VARIANT_BOOL* bIsDefault)
{
   CHECK_RETVAL(bIsDefault);
   *bIsDefault = m_bIsDefault;
   return S_OK;
}

STDMETHODIMP CDisplayUnit::Format(Float64 val, VARIANT_BOOL bShowUnitTag, BSTR* fmtString)
{
   CHECK_RETSTRING(fmtString);

   Float64 cv;
   m_pConverter->ConvertFromBaseUnits(val,m_pUnit,&cv);

   CComBSTR bstrTag;
   if ( bShowUnitTag )
      m_pUnit->get_Tag(&bstrTag);

   m_pFormatter->Format(cv,bstrTag,fmtString);

   return S_OK;
}

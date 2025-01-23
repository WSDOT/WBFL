///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
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

// DisplayUnitGroup.cpp : Implementation of CDisplayUnitGroup
#include "stdafx.h"
#include "WBFLUnitServer.h"
#include "DisplayUnitGroup.h"
#include "DisplayUnit.h"
#include "Helper.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


class FindDisplayUnit
{
public:
   FindDisplayUnit(const BSTR& bstr) : m_bstrTarget(bstr) {}
   bool operator()(const CComVariant& var)
   {
      _ASSERT( var.vt == VT_UNKNOWN );
      CComQIPtr<IDisplayUnit> pDU( var.punkVal );
      CComBSTR bstrUnitTag;
      pDU->get_UnitTag( &bstrUnitTag );
      return (_tcscmp( m_bstrTarget, bstrUnitTag ) == 0);
   }

private:
   CComBSTR m_bstrTarget;
};

class FindDefaultDisplayUnit
{
public:
   FindDefaultDisplayUnit(UnitModeType unitMode)
   {
      m_Target = unitMode == umSI ? unitsSI : unitsUS;
   }

   bool operator()(const CComVariant& var)
   {
      _ASSERT( var.vt == VT_UNKNOWN );
      CComQIPtr<IDisplayUnit> pDU( var.punkVal );

      UnitSystemType unitSystem;
      pDU->get_UnitSystem(&unitSystem);
      if ( unitSystem == unitsAll || unitSystem == m_Target )
      {
         VARIANT_BOOL bIsDefault;
         pDU->IsDefault(&bIsDefault);
         if ( bIsDefault == VARIANT_TRUE )
            return true;
      }
      return false;
   }

private:
   UnitSystemType m_Target;
};

/////////////////////////////////////////////////////////////////////////////
// CDisplayUnitGroup

void CDisplayUnitGroup::UnadviseDisplayUnit(IDisplayUnit* pDisplayUnit)
{
   ATLASSERT(pDisplayUnit != 0);
   USES_CONVERSION;

   InternalAddRef(); // Counteract Release() in Create()

   //
   // Disconnection from connection point
   //

   // Get the lookup key
   CComBSTR bstrKey;
   pDisplayUnit->get_UnitTag(&bstrKey);
   std::_tstring strKey( OLE2T(bstrKey) );

   // Lookup the cookie
   std::map<std::_tstring,DWORD>::iterator found;
   found = m_DisplayUnitCookies.find( strKey );
   ATLASSERT( found != m_DisplayUnitCookies.end() );

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( pDisplayUnit );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IDisplayUnitEvents, &pCP );
   pCP->Unadvise( (*found).second );

   // Remove cookie from map
   m_DisplayUnitCookies.erase( found );
}

void CDisplayUnitGroup::UnadviseAll()
{
   std::vector<CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CComVariant& var = *iter;
      CComQIPtr<IDisplayUnit> pDisplayUnit(var.punkVal);
      UnadviseDisplayUnit(pDisplayUnit);
   }
}


void CDisplayUnitGroup::FinalRelease()
{
   // First do the unit server
   if ( m_Cookie )
   {
	  CComQIPtr<IConnectionPointContainer> pCPC( m_pUnitType );
	  CComPtr<IConnectionPoint> pCP;
	  pCPC->FindConnectionPoint( IID_IUnitTypeEvents, &pCP );
	  pCP->Unadvise( m_Cookie );
   }

   // Disconnect DisplayUnit connection points
   UnadviseAll();
}

HRESULT CDisplayUnitGroup::BadUnitTagError(BSTR bstrTag)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), IDS_E_BADUNITTAG, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, str, W2T(bstrTag) );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return CComCoClass<CDisplayUnitGroup>::Error(oleMsg, IDH_E_BADUNITTAG, GetHelpFile(), IID_IDisplayUnitGroup, UNITS_E_BADUNITTAG);
}

STDMETHODIMP CDisplayUnitGroup::get_Name(BSTR* name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}

STDMETHODIMP CDisplayUnitGroup::get_UnitType(BSTR* unitType)
{
   CHECK_RETSTRING(unitType);
   m_pUnitType->get_Label(unitType);
   return S_OK;
}

STDMETHODIMP CDisplayUnitGroup::get_Item(BSTR bstrUnitTag,IDisplayUnit** retval)
{
   CHECK_IN(bstrUnitTag);
   CHECK_RETOBJ(retval);

   std::vector<CComVariant>::iterator found;
   found = std::find_if(m_coll.begin(),m_coll.end(),FindDisplayUnit(bstrUnitTag));
   if ( found == m_coll.end() )
      return BadUnitTagError(bstrUnitTag);

   CComVariant& var = *found;
   var.pdispVal->QueryInterface( retval );
   return S_OK;
}

STDMETHODIMP CDisplayUnitGroup::get_Count(IndexType* retval)
{
   CHECK_RETVAL(retval);
   long count;
   IDisplayUnitCollection::get_Count(&count);
   *retval = count;
   return S_OK;
}

//STDMETHODIMP CDisplayUnitGroup::get__NewEnum(IUnknown** retval)
//{
//}

//STDMETHODIMP CDisplayUnitGroup::get_Count(long* retval)
//{
//}

STDMETHODIMP CDisplayUnitGroup::Add(BSTR bstrUnitTag,UnitSystemType unitSystem,IDisplayUnitFormatter* formatter, VARIANT_BOOL bDefault,IDisplayUnit** dispUnit)
{
   USES_CONVERSION;
   HRESULT hr = S_OK;

   CHECK_IN(bstrUnitTag);
   CHECK_IN(formatter);
   CHECK_RETOBJ(dispUnit);

   CComPtr<IUnit> pUnit;
   CComVariant index(bstrUnitTag);
   CComPtr<IUnits> pUnits;
   m_pUnitType->get_Units(&pUnits);
   hr = pUnits->get_Item(index,&pUnit);
   if ( FAILED(hr) )
      return BadUnitTagError(bstrUnitTag);

   CComObject<CDisplayUnit>* newDispUnit;
   hr = CComObject<CDisplayUnit>::CreateInstance(&newDispUnit);
   if ( FAILED(hr) )
      return hr;

   newDispUnit->Init(m_pUnitServer,pUnit,formatter,unitSystem,bDefault);

   newDispUnit->QueryInterface(dispUnit);

   // Hookup to the connection point
   DWORD dwCookie;
   std::_tstring strKey( OLE2T(bstrUnitTag) );
   CComPtr<IDisplayUnit> pCP(newDispUnit);
   pCP.Advise( GetUnknown(), IID_IDisplayUnitEvents, &dwCookie );
   m_DisplayUnitCookies.insert( std::make_pair(strKey,dwCookie) );

   InternalRelease(); // Break circular reference

   CComPtr<IDisplayUnit> pNewDispUnit;
   newDispUnit->QueryInterface(&pNewDispUnit);

   CComVariant var(pNewDispUnit);
   m_coll.push_back(var);

   Fire_OnDisplayUnitCreated(this,pNewDispUnit);

   return S_OK;
}

STDMETHODIMP CDisplayUnitGroup::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnDisplayUnitGroupCleared(this);
   return S_OK;
}

STDMETHODIMP CDisplayUnitGroup::Remove(BSTR bstrUnitTag)
{
   CHECK_IN(bstrUnitTag);

   std::vector<CComVariant>::iterator found;
   found = std::find_if(m_coll.begin(),m_coll.end(),FindDisplayUnit(bstrUnitTag));
   if ( found == m_coll.end() )
      return BadUnitTagError(bstrUnitTag);

   CComVariant& var = *found;
   CComQIPtr<IDisplayUnit> pDisplayUnit(var.pdispVal);
   UnadviseDisplayUnit(pDisplayUnit);
   pDisplayUnit.Release();

   m_coll.erase(found);

   Fire_OnDisplayUnitRemoved(this,bstrUnitTag);

   return S_OK;
}


STDMETHODIMP CDisplayUnitGroup::get_Default(UnitModeType unitMode, IDisplayUnit **pVal)
{
   // Find the default display unit for the specified unit system
   CHECK_RETOBJ(pVal);
   std::vector<CComVariant>::iterator found;
   found = std::find_if(m_coll.begin(),m_coll.end(),FindDefaultDisplayUnit(unitMode));

   if ( found == m_coll.end() )
      return CComCoClass<CDisplayUnitGroup>::Error(IDS_E_DEFAULTNOTFOUND, IDH_E_DEFAULTNOTFOUND, GetHelpFile(),IID_IDisplayUnitGroup,UNITS_E_DEFAULTNOTFOUND);

   CComVariant& var = *found;
   var.pdispVal->QueryInterface( pVal );

	return S_OK;
}

STDMETHODIMP CDisplayUnitGroup::get__EnumDisplayUnits(IEnumDisplayUnits** enumDisplayUnits)
{
   CHECK_RETOBJ(enumDisplayUnits);

   using Enum = CComEnumOnSTL<IEnumDisplayUnits,&IID_IEnumDisplayUnits, IDisplayUnit*, _CopyVariantToInterface<IDisplayUnit>, std::vector<CComVariant> >;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( nullptr, m_coll );
   if ( FAILED(hr) )
      return hr;

   pEnum->QueryInterface( enumDisplayUnits );

   return S_OK;
}

///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2018  Washington State Department of Transportation
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

// Units.cpp : Implementation of CUnits
#include "stdafx.h"
#include "WbflUnitServer.h"
#include "UnitServerImp.h"
#include "Units.h"
#include "Unit.h"
#include "Helper.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


class FindUnit
{
public:
   FindUnit(const BSTR& bstr) : m_bstrTarget(bstr) {}
   bool operator()(const CComVariant& var)
   {
      _ASSERT( var.vt == VT_UNKNOWN );
      CComQIPtr<IUnit> pUnit( var.punkVal );
      CComBSTR bstrTag;
      pUnit->get_Tag( &bstrTag );
      return (_tcscmp( m_bstrTarget, bstrTag ) == 0);
   }

private:
   CComBSTR m_bstrTarget;
};

/////////////////////////////////////////////////////////////////////////////
// CUnits

//STDMETHODIMP CUnits::get_Count(long* retval)
//{
//}

STDMETHODIMP CUnits::get_Item(VARIANT Index, IUnit** retval)
{
   CHECK_RETOBJ(retval);

   std::vector<CComVariant>::iterator iter;
   iter = GetUnit( Index );

   if ( iter == m_coll.end() )
       return E_INVALIDARG;

   CComVariant& var = *iter;
   ATLASSERT(var.vt = VT_UNKNOWN);
   var.punkVal->QueryInterface( retval );

   return S_OK;
}

//STDMETHODIMP CUnits::get__NewEnum(IUnknown** retval)
//{
//}

STDMETHODIMP CUnits::get__EnumUnits(IEnumUnits** enumUnits)
{
   CHECK_RETOBJ(enumUnits);

   typedef CComEnumOnSTL<IEnumUnits,&IID_IEnumUnits, IUnit*, _CopyVariantToInterface<IUnit>, std::vector<CComVariant> > Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( nullptr, m_coll );
   if ( FAILED(hr) )
      return hr;

   pEnum->QueryInterface( enumUnits );

   return S_OK;
}

STDMETHODIMP CUnits::Add(BSTR bstrTag,Float64 preTerm,Float64 cf,Float64 postTerm,UnitSystemType unitSystem,IUnit** ppUnit)
{
   CHECK_IN(bstrTag);

   if ( ppUnit != nullptr )
   {
      CHECK_RETOBJ(ppUnit);
   }

   // Check if this unit already exists
   std::vector<CComVariant>::iterator found;
   found = std::find_if(m_coll.begin(),m_coll.end(),FindUnit(bstrTag));
   if ( found != m_coll.end() )
   {
      return CComCoClass<CUnits>::Error(IDS_E_UNITALREADYDEFINED,IDH_E_UNITALREADYDEFINED, GetHelpFile(),IID_IUnits, UNITS_E_UNITALREADYDEFINED );
   }

   CComObject<CUnit>* pUnit;
   CComObject<CUnit>::CreateInstance(&pUnit);
   pUnit->Init(m_pUnitServer,m_pUnitType,preTerm,cf,postTerm,bstrTag,unitSystem);
   CComPtr<IUnit> unit(pUnit);

   if ( ppUnit != nullptr )
   {
      *ppUnit = unit;
      (*ppUnit)->AddRef();
   }

   CComVariant var(unit);
   m_coll.push_back(var);

   Fire_OnUnitAdded(unit);

   return S_OK;
}

STDMETHODIMP CUnits::Clear()
{
   m_coll.clear();
   Fire_OnUnitsCleared();
   return S_OK;
}

STDMETHODIMP CUnits::get_Count(CollectionIndexType* retval)
{
   CHECK_RETVAL(retval);
   long count;
   IUnitCollection::get_Count(&count);
   *retval = count;
   return S_OK;
}

STDMETHODIMP CUnits::Remove(VARIANT Index)
{
   std::vector<CComVariant>::iterator iter;
   iter = GetUnit( Index );

   if ( iter == m_coll.end() )
      return E_INVALIDARG;

   CComBSTR bstrTag;
   CComQIPtr<IUnit> pUnit((*iter).pdispVal);
   pUnit->get_Tag(&bstrTag);
   pUnit.Release();

   m_coll.erase(iter);

   Fire_OnUnitRemoved(bstrTag);

   return S_OK;
}

std::vector<CComVariant>::iterator CUnits::GetUnit(VARIANT Index)
{
   std::vector<CComVariant>::iterator iter;

   switch( Index.vt )
   {
   case VT_I2:
        iter = GetUnitByIndex( Index.iVal );
        break;

   case VT_I4:
        iter = GetUnitByIndex( Index.lVal );
        break;

   case VT_BSTR:
        iter = GetUnitByTag( Index.bstrVal );
        break;

   default:
        iter = m_coll.end();
   }

   return iter;
}

std::vector<CComVariant>::iterator CUnits::GetUnitByIndex(long idx)
{
   if ( idx < 0 || (long)m_coll.size() <= idx )
      return m_coll.end();

   std::vector<CComVariant>::iterator iter;
   iter = m_coll.begin() + idx;

   return iter;
}

std::vector<CComVariant>::iterator CUnits::GetUnitByTag(BSTR bstrName)
{
   std::vector<CComVariant>::iterator found;
   found = std::find_if(m_coll.begin(),m_coll.end(),FindUnit(bstrName));
   return found;
}

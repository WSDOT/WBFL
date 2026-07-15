///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright � 1999-2026  Washington State Department of Transportation
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

// UnitTypes.cpp : Implementation of CUnitTypes
#include "stdafx.h"
#include "WbflUnitServer.h"
#include "UnitTypes.h"
#include "UnitType.h"
#include "Helper.h"
#include <algorithm>
#include <Units\Measure.h>
#include <Units\XUnit.h>


void CUnitTypes::UnadviseUnitType(IUnitType* pUnitType)
{
   ATLASSERT(pUnitType != 0);
   USES_CONVERSION;

   InternalAddRef(); // Counteract Release used to break circular reference

   //
   // Disconnection from connection point
   //

   // Get the lookup key
   CComBSTR bstrLabel;
   pUnitType->get_Label(&bstrLabel);
   std::_tstring strLabel( OLE2T(bstrLabel) );

   // Lookup the cookie
   std::map<std::_tstring,DWORD>::iterator found;
   found = m_Cookies.find( strLabel );
   ATLASSERT( found != m_Cookies.end() );

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( pUnitType );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IUnitTypeEvents, &pCP );
   pCP->Unadvise( (*found).second );

   // Remove cookie from map
   m_Cookies.erase( found );
}

void CUnitTypes::UnadviseAll()
{
   std::vector<CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CComVariant& var = *iter;
      CComQIPtr<IUnitType> pUnitType(var.pdispVal);
      UnadviseUnitType(pUnitType);
   }
}

/////////////////////////////////////////////////////////////////////////////
// CUnitTypes

// Wraps IUnitTypes::Add/IUnitType::AddUnit in a block scope so BEGIN_NEWUNITTYPE/NEWUNIT/END_NEWUNITTYPE read
// like the classic macro table, while every number is sourced from WBFL::Units::Measure:: (the single
// native source of truth) rather than being hand-transcribed here a second time. Both the unit-type and
// each of its units flow through the same public Add()/AddUnit() methods used by dynamically-created unit
// types at run time, so the shared unit catalog (see CUnitServerImp::GetUnitCatalog()) ends up with an
// identical, single entry for every built-in and dynamically-added unit type/unit alike.
#define BEGIN_NEWUNITTYPE(name,m,l,t,k,a) \
   { \
      CComPtr<IUnitType> pUnitType; \
      HRESULT hr = Add( CComBSTR(name), (m),(l),(t),(k),(a), &pUnitType ); \
      if ( FAILED(hr) ) return hr; \
      CComPtr<IUnits> pUnits; \
      pUnitType->get_Units(&pUnits);

#define NEWUNIT(tag,pre,cf,post,us) \
      pUnits->Add( CComBSTR(tag), (pre),(cf),(post), (us), nullptr );

#define END_NEWUNITTYPE() \
   }

HRESULT CUnitTypes::FinalConstruct()
{
   return S_OK;
}

void CUnitTypes::FinalRelease()
{
   UnadviseAll();
}

HRESULT CUnitTypes::InitDefaultUnits()
{
   using namespace WBFL::Units;

   // Every built-in unit added below intentionally has the same dimensionality as one of WBFLUnits'
   // compile-time PhysicalT aliases (that's the whole point - built-in and dynamically-added unit types
   // share one catalog). Suppress DynamicPhysical's "this duplicates a compile-time dimension" diagnostic
   // for the duration of this seeding; it stays fully active for any other, non-built-in caller.
#if defined _DEBUG
   DynamicPhysical::SuppressDuplicateDimensionWarningScope suppressWarnings;
#endif

   try
   {
      // Mass
      BEGIN_NEWUNITTYPE( CComBSTR("Mass"), 1,0,0,0,0 );
         NEWUNIT( CComBSTR("kg"),     0.0, Measure::Kilogram.GetConvFactor(), 0.0, unitsSI );
         NEWUNIT( CComBSTR("Mg"),     0.0, Measure::Megagram.GetConvFactor(), 0.0, unitsSI );
         NEWUNIT( CComBSTR("g"),      0.0, Measure::Gram.GetConvFactor(),     0.0, unitsSI );
         NEWUNIT( CComBSTR("MT"),     0.0, Measure::MetricTon.GetConvFactor(),0.0, unitsSI );
         NEWUNIT( CComBSTR("slug"),   0.0, Measure::Slug.GetConvFactor(),     0.0, unitsUS );
         NEWUNIT( CComBSTR("lb"),     0.0, Measure::PoundMass.GetConvFactor(),0.0, unitsUS );
         NEWUNIT( CComBSTR("kslug"),  0.0, Measure::KSlug.GetConvFactor(),    0.0, unitsUS );
         NEWUNIT( CComBSTR("12slug"), 0.0, Measure::_12Slug.GetConvFactor(),  0.0, unitsUS );
         NEWUNIT( CComBSTR("12kslug"),0.0, Measure::_12KSlug.GetConvFactor(), 0.0, unitsUS );
      END_NEWUNITTYPE();

      // Length
      BEGIN_NEWUNITTYPE( CComBSTR("Length"), 0,1,0,0,0 );
         NEWUNIT( CComBSTR("m"),    0.0, Measure::Meter.GetConvFactor(),        0.0, unitsSI );
         NEWUNIT( CComBSTR("mm"),   0.0, Measure::Millimeter.GetConvFactor(),   0.0, unitsSI );
         NEWUNIT( CComBSTR("cm"),   0.0, Measure::Centimeter.GetConvFactor(),   0.0, unitsSI );
         NEWUNIT( CComBSTR("km"),   0.0, Measure::Kilometer.GetConvFactor(),    0.0, unitsSI );
         NEWUNIT( CComBSTR("ft"),   0.0, Measure::Feet.GetConvFactor(),         0.0, unitsUS );
         NEWUNIT( CComBSTR("in"),   0.0, Measure::Inch.GetConvFactor(),         0.0, unitsUS );
         NEWUNIT( CComBSTR("mile"), 0.0, Measure::Mile.GetConvFactor(),         0.0, unitsUS );
         NEWUNIT( CComBSTR("yd"),   0.0, Measure::Yard.GetConvFactor(),         0.0, unitsUS );
         NEWUNIT( CComBSTR("ft(US survey)"), 0.0, Measure::USSurveyFoot.GetConvFactor(), 0.0, unitsUS );
         NEWUNIT( CComBSTR("yd(US survey)"), 0.0, Measure::USSurveyYard.GetConvFactor(), 0.0, unitsUS );
      END_NEWUNITTYPE();

      // Time
      BEGIN_NEWUNITTYPE( CComBSTR("Time"), 0,0,1,0,0 );
         NEWUNIT( CComBSTR("sec"), 0.0, Measure::Second.GetConvFactor(), 0.0, UnitSystemType(unitsSI + unitsUS) );
         NEWUNIT( CComBSTR("min"), 0.0, Measure::Minute.GetConvFactor(), 0.0, UnitSystemType(unitsSI + unitsUS) );
         NEWUNIT( CComBSTR("hr"),  0.0, Measure::Hour.GetConvFactor(),   0.0, UnitSystemType(unitsSI + unitsUS) );
         NEWUNIT( CComBSTR("day"), 0.0, Measure::Day.GetConvFactor(),   0.0, UnitSystemType(unitsSI + unitsUS) );
      END_NEWUNITTYPE();

      // Temperature
      BEGIN_NEWUNITTYPE( CComBSTR("Temperature"), 0,0,0,1,0 );
         NEWUNIT( CComBSTR("C"), Measure::Celsius.GetPreTerm(),    Measure::Celsius.GetConvFactor(),    Measure::Celsius.GetPostTerm(),    unitsAll );
         NEWUNIT( CComBSTR("F"), Measure::Fahrenheit.GetPreTerm(), Measure::Fahrenheit.GetConvFactor(), Measure::Fahrenheit.GetPostTerm(), unitsAll );
      END_NEWUNITTYPE();

      // Angle
      BEGIN_NEWUNITTYPE( CComBSTR("Angle"), 0,0,0,0,1 );
         NEWUNIT( CComBSTR("rad"), 0.0, Measure::Radian.GetConvFactor(), 0.0, unitsAll );
         NEWUNIT( CComBSTR("deg"), 0.0, Measure::Degree.GetConvFactor(), 0.0, unitsAll );
      END_NEWUNITTYPE();

      // Mass Per Length
      BEGIN_NEWUNITTYPE( CComBSTR("MassPerLength"), 1,-1,0,0,0 );
         NEWUNIT( CComBSTR("kg/m"),    0.0, Measure::KgPerMeter.GetConvFactor(),  0.0, unitsSI );
         NEWUNIT( CComBSTR("slug/ft"), 0.0, Measure::SlugPerFeet.GetConvFactor(), 0.0, unitsUS );
         NEWUNIT( CComBSTR("lb/ft"),   0.0, Measure::LbfPerFeet.GetConvFactor(),  0.0, unitsUS );
      END_NEWUNITTYPE();

      // Area
      BEGIN_NEWUNITTYPE( CComBSTR("Length2"), 0,2,0,0,0 );
         NEWUNIT( CComBSTR("m^2"),    0.0, Measure::Meter2.GetConvFactor(),    0.0, unitsSI );
         NEWUNIT( CComBSTR("mm^2"),   0.0, Measure::Millimeter2.GetConvFactor(),0.0, unitsSI );
         NEWUNIT( CComBSTR("cm^2"),   0.0, Measure::Centimeter2.GetConvFactor(),0.0, unitsSI );
         NEWUNIT( CComBSTR("km^2"),   0.0, Measure::Kilometer2.GetConvFactor(), 0.0, unitsSI );
         NEWUNIT( CComBSTR("ft^2"),   0.0, Measure::Feet2.GetConvFactor(),      0.0, unitsUS );
         NEWUNIT( CComBSTR("in^2"),   0.0, Measure::Inch2.GetConvFactor(),      0.0, unitsUS );
         NEWUNIT( CComBSTR("mile^2"), 0.0, Measure::Mile2.GetConvFactor(),      0.0, unitsUS );
         NEWUNIT( CComBSTR("yd^2"),   0.0, Measure::Yard2.GetConvFactor(),      0.0, unitsUS );
      END_NEWUNITTYPE();

      // Volume
      BEGIN_NEWUNITTYPE( CComBSTR("Length3"), 0,3,0,0,0 );
         NEWUNIT( CComBSTR("m^3"),    0.0, Measure::Meter3.GetConvFactor(),     0.0, unitsSI );
         NEWUNIT( CComBSTR("mm^3"),   0.0, Measure::Millimeter3.GetConvFactor(),0.0, unitsSI );
         NEWUNIT( CComBSTR("cm^3"),   0.0, Measure::Centimeter3.GetConvFactor(),0.0, unitsSI );
         NEWUNIT( CComBSTR("km^3"),   0.0, Measure::Kilometer3.GetConvFactor(), 0.0, unitsSI );
         NEWUNIT( CComBSTR("ft^3"),   0.0, Measure::Feet3.GetConvFactor(),      0.0, unitsUS );
         NEWUNIT( CComBSTR("in^3"),   0.0, Measure::Inch3.GetConvFactor(),      0.0, unitsUS );
         NEWUNIT( CComBSTR("mile^3"), 0.0, Measure::Mile3.GetConvFactor(),      0.0, unitsUS );
         NEWUNIT( CComBSTR("yd^3"),   0.0, Measure::Yard3.GetConvFactor(),      0.0, unitsUS );
      END_NEWUNITTYPE();

      // Length4 (Moment of Inertia). NOTE: the temperature exponent here was previously 1 (a bug - moment
      // of inertia has no temperature dependence, confirmed against WBFL::Units::Length4's dimension); it
      // is corrected to 0 here.
      BEGIN_NEWUNITTYPE( CComBSTR("Length4"), 0,4,0,0,0 );
         NEWUNIT( CComBSTR("m^4"),    0.0, Measure::Meter4.GetConvFactor(),     0.0, unitsSI );
         NEWUNIT( CComBSTR("mm^4"),   0.0, Measure::Millimeter4.GetConvFactor(),0.0, unitsSI );
         NEWUNIT( CComBSTR("cm^4"),   0.0, Measure::Centimeter4.GetConvFactor(),0.0, unitsSI );
         NEWUNIT( CComBSTR("km^4"),   0.0, Measure::Kilometer4.GetConvFactor(), 0.0, unitsSI );
         NEWUNIT( CComBSTR("ft^4"),   0.0, Measure::Feet4.GetConvFactor(),      0.0, unitsUS );
         NEWUNIT( CComBSTR("in^4"),   0.0, Measure::Inch4.GetConvFactor(),      0.0, unitsUS );
         NEWUNIT( CComBSTR("mile^4"), 0.0, Measure::Mile4.GetConvFactor(),      0.0, unitsUS );
         NEWUNIT( CComBSTR("yd^4"),   0.0, Measure::Yard4.GetConvFactor(),      0.0, unitsUS );
      END_NEWUNITTYPE();

      // Pressure
      BEGIN_NEWUNITTYPE( CComBSTR("Pressure"), 1,-1,-2,0,0 );
         NEWUNIT( CComBSTR("Pa"),  0.0, Measure::Pa.GetConvFactor(),  0.0, unitsSI );
         NEWUNIT( CComBSTR("kPa"), 0.0, Measure::kPa.GetConvFactor(), 0.0, unitsSI );
         NEWUNIT( CComBSTR("MPa"), 0.0, Measure::MPa.GetConvFactor(), 0.0, unitsSI );
         NEWUNIT( CComBSTR("psi"), 0.0, Measure::PSI.GetConvFactor(), 0.0, unitsUS );
         NEWUNIT( CComBSTR("psf"), 0.0, Measure::PSF.GetConvFactor(), 0.0, unitsUS );
         NEWUNIT( CComBSTR("ksi"), 0.0, Measure::KSI.GetConvFactor(), 0.0, unitsUS );
         NEWUNIT( CComBSTR("ksf"), 0.0, Measure::KSF.GetConvFactor(), 0.0, unitsUS );
      END_NEWUNITTYPE();

      // Unit Weight
      BEGIN_NEWUNITTYPE( CComBSTR("UnitWeight"), 1,-3,-3,0,0 );
         NEWUNIT( CComBSTR("N/m^3"), 0.0, Measure::NewtonPerMeter3.GetConvFactor(), 0.0, unitsSI );
         NEWUNIT( CComBSTR("pci"),   0.0, Measure::PCI.GetConvFactor(),             0.0, unitsUS );
         NEWUNIT( CComBSTR("pcf"),   0.0, Measure::PCF.GetConvFactor(),             0.0, unitsUS );
      END_NEWUNITTYPE();

      // Density
      BEGIN_NEWUNITTYPE( CComBSTR("Density"), 1,-3,0,0,0 );
         NEWUNIT( CComBSTR("kg/m^3"),    0.0, Measure::KgPerMeter3.GetConvFactor(),  0.0, unitsSI );
         NEWUNIT( CComBSTR("slug/ft^3"), 0.0, Measure::SlugPerFeet3.GetConvFactor(), 0.0, unitsUS );
         NEWUNIT( CComBSTR("lb/ft^3"),   0.0, Measure::LbmPerFeet3.GetConvFactor(),  0.0, unitsUS );
      END_NEWUNITTYPE();

      // Force
      BEGIN_NEWUNITTYPE( CComBSTR("Force"), 1,1,-2,0,0 );
         NEWUNIT( CComBSTR("N"),   0.0, Measure::Newton.GetConvFactor(),     0.0, unitsSI );
         NEWUNIT( CComBSTR("kN"),  0.0, Measure::Kilonewton.GetConvFactor(), 0.0, unitsSI );
         NEWUNIT( CComBSTR("lbf"), 0.0, Measure::Pound.GetConvFactor(),      0.0, unitsUS );
         NEWUNIT( CComBSTR("kip"), 0.0, Measure::Kip.GetConvFactor(),        0.0, unitsUS );
         NEWUNIT( CComBSTR("ton"), 0.0, Measure::Ton.GetConvFactor(),        0.0, unitsUS );
      END_NEWUNITTYPE();

      // Force Per Length
      BEGIN_NEWUNITTYPE( CComBSTR("ForcePerLength"), 1,0,-2,0,0 );
         NEWUNIT( CComBSTR("N/m"),    0.0, Measure::NewtonPerMeter.GetConvFactor(),     0.0, unitsSI );
         NEWUNIT( CComBSTR("N/mm"),   0.0, Measure::NewtonPerMillimeter.GetConvFactor(),0.0, unitsSI );
         NEWUNIT( CComBSTR("lbf/ft"), 0.0, Measure::LbfPerFoot.GetConvFactor(),         0.0, unitsUS );
         NEWUNIT( CComBSTR("lbf/in"), 0.0, Measure::LbfPerInch.GetConvFactor(),         0.0, unitsUS );
         NEWUNIT( CComBSTR("kip/ft"), 0.0, Measure::KipPerFoot.GetConvFactor(),         0.0, unitsUS );
         NEWUNIT( CComBSTR("kip/in"), 0.0, Measure::KipPerInch.GetConvFactor(),         0.0, unitsUS );
      END_NEWUNITTYPE();

      // Moment
      BEGIN_NEWUNITTYPE( CComBSTR("Moment"), 1,2,-2,0,0 );
         NEWUNIT( CComBSTR("N-m"),    0.0, Measure::NewtonMeter.GetConvFactor(),     0.0, unitsSI );
         NEWUNIT( CComBSTR("N-mm"),   0.0, Measure::NewtonMillimeter.GetConvFactor(),0.0, unitsSI );
         NEWUNIT( CComBSTR("kN-m"),   0.0, Measure::KilonewtonMeter.GetConvFactor(), 0.0, unitsSI );
         NEWUNIT( CComBSTR("lbf-in"), 0.0, Measure::InchLbf.GetConvFactor(),         0.0, unitsUS );
         NEWUNIT( CComBSTR("lbf-ft"), 0.0, Measure::PoundFeet.GetConvFactor(),       0.0, unitsUS );
         NEWUNIT( CComBSTR("kip-ft"), 0.0, Measure::KipFeet.GetConvFactor(),         0.0, unitsUS );
         NEWUNIT( CComBSTR("kip-in"), 0.0, Measure::KipInch.GetConvFactor(),         0.0, unitsUS );
      END_NEWUNITTYPE();

      // Thermal expansion
      BEGIN_NEWUNITTYPE( CComBSTR("ThermalExpansion"), 0,0,0,-1,0 );
         NEWUNIT( CComBSTR("1/C"), 0.0, Measure::PerCelsius.GetConvFactor(),    0.0, unitsAll );
         NEWUNIT( CComBSTR("1/F"), 0.0, Measure::PerFahrenheit.GetConvFactor(), 0.0, unitsAll );
      END_NEWUNITTYPE();
   }
   catch (WBFL::Units::XUnit&)
   {
      return E_FAIL;
   }

   return S_OK;
}

//STDMETHODIMP CUnitTypes::get_Count(long* retval)
//{
//      // Implemented by ICollectionOnSTLImpl
//}

STDMETHODIMP::CUnitTypes::get_Count(IndexType* retval)
{
   CHECK_RETVAL(retval);
   long count;
   IUnitTypeCollection::get_Count(&count);
   (*retval) = count;
   return S_OK;
}

STDMETHODIMP CUnitTypes::get_Item(VARIANT Index, IUnitType** retval)
{
   CHECK_RETOBJ(retval);

   HRESULT hr = S_OK;

   if ( Index.vt == VT_I2 || Index.vt == VT_I4 || Index.vt == VT_I8 || Index.vt == VT_UI2 || Index.vt == VT_UI4 || Index.vt == VT_UI8 )
   {
      IndexType idx;
      switch(Index.vt )
      {
      case VT_I2:    idx = (IndexType)Index.iVal;   break;
      case VT_I4:    idx = (IndexType)Index.lVal;   break;
      case VT_I8:    idx = (IndexType)Index.llVal;  break;
      case VT_UI2:   idx = (IndexType)Index.uiVal;  break;
      case VT_UI4:   idx = (IndexType)Index.ulVal;  break;
      case VT_UI8:   idx = (IndexType)Index.ullVal; break;
      }

      if ( idx == INVALID_INDEX || m_coll.size() <= idx )
         return E_INVALIDARG;

      CComVariant& var = m_coll[idx];
      ATLASSERT(var.vt == VT_UNKNOWN);
      var.punkVal->QueryInterface( retval );
   }
   else if ( Index.vt == VT_BSTR )
   {
      std::vector<CComVariant>::iterator found;
      found = std::find_if(m_coll.begin(), m_coll.end(),FindUnitType(Index.bstrVal));
      if ( found == m_coll.end() )
         return E_INVALIDARG;

      CComVariant& var = *found;
      ATLASSERT(var.vt == VT_UNKNOWN);
      var.punkVal->QueryInterface( retval );
   }
   else
   {
      return E_INVALIDARG;
   }

   return S_OK;
}

//STDMETHODIMP CUnitTypes::get__NewEnum(IUnknown** retval)
//{
//      // Implemented by ICollectionOnSTLImpl
//}

STDMETHODIMP CUnitTypes::get__EnumUnitTypes(IEnumUnitTypes** enumUnitTypes)
{
   CHECK_RETOBJ(enumUnitTypes);

   using Enum = CComEnumOnSTL<IEnumUnitTypes,&IID_IEnumUnitTypes, IUnitType*, _CopyVariantToInterface<IUnitType>, std::vector<CComVariant> >;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( nullptr, m_coll );
   if ( FAILED(hr) )
      return hr;

   pEnum->QueryInterface( enumUnitTypes );

   return S_OK;
}

STDMETHODIMP CUnitTypes::Add(BSTR label,Float64 m,Float64 l,Float64 t,Float64 k,Float64 a,IUnitType** ppUnitType)
{
   USES_CONVERSION;

   CHECK_IN(label);

   if ( ppUnitType != nullptr )
   {
      CHECK_RETOBJ(ppUnitType);
   }

   // First check to see if we already have a unit type with this name
   std::vector<CComVariant>::iterator found;
   found = std::find_if(m_coll.begin(), m_coll.end(),FindUnitType(label));
   if ( found != m_coll.end() )
      return CComCoClass<CUnitTypes>::Error(IDS_E_UNITTYPEALREADYDEFINED,IDH_E_UNITTYPEALREADYDEFINED, GetHelpFile(),IID_IUnitTypes, UNITS_E_UNITTYPEALREADYDEFINED );

   // Register in the shared catalog before creating the COM object, so nothing needs to be unwound if this
   // fails (it shouldn't, given the uniqueness check above, but the catalog is the authoritative check).
   std::_tstring strLabel( OLE2T(label) );
   try
   {
      m_pUnitCatalog->AddUnitType(strLabel, m, l, t, k, a);
   }
   catch (WBFL::Units::XUnit&)
   {
      return CComCoClass<CUnitTypes>::Error(IDS_E_UNITTYPEALREADYDEFINED,IDH_E_UNITTYPEALREADYDEFINED, GetHelpFile(),IID_IUnitTypes, UNITS_E_UNITTYPEALREADYDEFINED );
   }

   // OK, this is a new unit type for this server
   CComObject<CUnitType>* pUnitType;
   HRESULT hr = CComObject<CUnitType>::CreateInstance( &pUnitType );
   if ( FAILED(hr) )
      return E_FAIL;

   pUnitType->Init(m_pUnitServer,m_pUnitCatalog,label,m,l,t,k,a);
   
   CComPtr<IUnitType> unitType;
   pUnitType->QueryInterface(&unitType);

   CComVariant var( unitType );
   m_coll.push_back( var );

   if ( ppUnitType != nullptr )
   {
      *ppUnitType = pUnitType;
      pUnitType->AddRef();
   }

   // Hookup to the connection point
   DWORD dwCookie;
   hr = unitType.Advise( GetUnknown(), IID_IUnitTypeEvents, &dwCookie );
   ATLASSERT(SUCCEEDED(hr));
   m_Cookies.insert( std::make_pair(strLabel,dwCookie) );

   InternalRelease(); // Break circular reference

   
   Fire_OnUnitTypeAdded(unitType);

   return S_OK;
}

STDMETHODIMP CUnitTypes::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnUnitTypesCleared();
   return S_OK;
}

STDMETHODIMP CUnitTypes::Remove(VARIANT Index)
{
   HRESULT hr = S_OK;

   CComPtr<IUnitType> ut;
   switch( Index.vt )
   {
   case VT_DISPATCH:
      Index.pdispVal->QueryInterface( &ut );
      hr = Remove( ut );
      break;

   case VT_UNKNOWN:
      Index.punkVal->QueryInterface( &ut );
      hr = Remove( ut );
      break;

   case VT_I2:
      hr = Remove( Index.iVal );
      break;

   case VT_I4:
      hr = Remove( Index.lVal );
      break;

   case VT_BSTR:
      hr = Remove( Index.bstrVal );
      break;

   default:
      hr = E_INVALIDARG;
   }

   return hr;
}

HRESULT CUnitTypes::Remove(IUnitType* pUnitType)
{
   CHECK_IN(pUnitType);

   std::vector<CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter < m_coll.end(); iter++ )
   {
      // We must compare IUnknown pointers. The specification for
      // QueryInterfaces says IUnknown must always return the exact
      // same pointer value. This is not true on any other interface.
      CComVariant& var = *iter;
   
      CComPtr<IUnknown> p1;
      CComPtr<IUnknown> p2;
      
      pUnitType->QueryInterface(&p1);
      var.pdispVal->QueryInterface(&p2);

      if ( p1 == p2 )
      {
         CComBSTR bstrLabel;
         pUnitType->get_Label(&bstrLabel);

         UnadviseUnitType(pUnitType);

         m_coll.erase( iter );

         Fire_OnUnitTypeRemoved(bstrLabel);

         return S_OK;
      }
   }

   return E_FAIL;
}

HRESULT CUnitTypes::Remove(long idx)
{
   if ( idx < 0 || (long)m_coll.size() <= idx )
      return E_INVALIDARG;

   CComVariant& var = m_coll[idx];
   CComQIPtr<IUnitType> pUnitType(var.pdispVal);
   CComBSTR bstrLabel;
   pUnitType->get_Label(&bstrLabel);

   UnadviseUnitType(pUnitType);
   
   pUnitType.Release();

   m_coll.erase( m_coll.begin() + idx );

   Fire_OnUnitTypeRemoved(bstrLabel);

   return S_OK;
}

HRESULT CUnitTypes::Remove(BSTR bstrName)
{
   std::vector<CComVariant>::iterator found;
   found = std::find_if(m_coll.begin(), m_coll.end(),FindUnitType(bstrName));
   if ( found == m_coll.end() )
      return CComCoClass<CUnitTypes>::Error(IDS_E_BADUNITTYPE,IDH_E_BADUNITTYPE, GetHelpFile(),IID_IUnitTypes,UNITS_E_BADUNITTYPE);

   CComVariant& var = *found;
   _ASSERT( var.vt == VT_UNKNOWN );

   CComQIPtr<IUnitType> pUnitType(var.punkVal);
   UnadviseUnitType(pUnitType);
   pUnitType.Release();

   m_coll.erase( found );

   Fire_OnUnitTypeRemoved(bstrName);

   return S_OK;
}


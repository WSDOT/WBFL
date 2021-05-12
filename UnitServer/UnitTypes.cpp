///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
   pCPC->FindConnectionPoint( IID_IUnitTypeEventSink, &pCP );
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

#define INIT_NEWUNIT()  \
   CUnitType* pUnitType;

#define BEGIN_NEWUNIT(name,m,l,t,k,a) \
   pUnitType = create_unit_type(m_pUnitServer,(name),(m),(l),(t),(k),(a)); \
   SaveUnitType( pUnitType ); \

#define NEWUNIT(tag,pre,cf,post,us) \
   pUnitType->AddUnit((tag),(pre),(cf),(post),(us));

#define END_NEWUNIT() \
   pUnitType->Release()

CUnitType* create_unit_type(IUnitServer* pUnitServer,const CComBSTR& bstrLabel,Float64 m,Float64 l,Float64 t,Float64 k,Float64 a)
{
   CComObject<CUnitType>* pUnitType;
   CComObject<CUnitType>::CreateInstance( &pUnitType );
   pUnitType->AddRef();
   pUnitType->Init( pUnitServer,bstrLabel, m, l, t, k ,a );
   return pUnitType;   
}

void CUnitTypes::SaveUnitType(IUnitType* pUnitType)
{
   USES_CONVERSION;

   CComVariant var( pUnitType );

   // Hookup to the connection point
   DWORD dwCookie;
   CComBSTR bstrLabel;
   pUnitType->get_Label(&bstrLabel);
   std::_tstring strLabel( OLE2T(bstrLabel) );
   CComPtr<IUnitType> pCPUnitType(pUnitType);
   pCPUnitType.Advise( GetUnknown(), IID_IUnitTypeEventSink, &dwCookie );
   m_Cookies.insert( std::make_pair(strLabel,dwCookie) );

   InternalRelease(); // Break Circular Reference

   m_coll.push_back( var );
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
   INIT_NEWUNIT();

   // Mass
   BEGIN_NEWUNIT( CComBSTR("Mass"), 1,0,0,0,0 );
      NEWUNIT( CComBSTR("kg"),    0.0, 1.000,         0.0, unitsSI );
      NEWUNIT( CComBSTR("Mg"),    0.0, 1.0e3,         0.0, unitsSI );
      NEWUNIT( CComBSTR("g"),     0.0, 1.0e-3,        0.0, unitsSI );
      NEWUNIT( CComBSTR("MT"),    0.0, 1.0e3,         0.0, unitsSI );
      NEWUNIT( CComBSTR("slug"),  0.0, 14.5939029372, 0.0, unitsUS );
      NEWUNIT( CComBSTR("lb"),    0.0, 0.45359237,    0.0, unitsUS );
      NEWUNIT( CComBSTR("kslug"), 0.0, 14593.9029372, 0.0, unitsUS );
      NEWUNIT( CComBSTR("12slug"),0.0, 175.126835246, 0.0, unitsUS );
      NEWUNIT( CComBSTR("12kslug"), 0.0, 175126.835246, 0.0, unitsUS );
   END_NEWUNIT();

   // Length
   BEGIN_NEWUNIT( CComBSTR("Length"), 0,1,0,0,0 );
      NEWUNIT( CComBSTR("m"),    0.0, 1.0000,   0.0, unitsSI );
      NEWUNIT( CComBSTR("mm"),   0.0, 1.0e-3,   0.0, unitsSI );
      NEWUNIT( CComBSTR("cm"),   0.0, 1.0e-2,   0.0, unitsSI );
      NEWUNIT( CComBSTR("km"),   0.0, 1.0e03,   0.0, unitsSI );
      NEWUNIT( CComBSTR("ft"),   0.0, 0.3048,   0.0, unitsUS );
      NEWUNIT( CComBSTR("in"),   0.0, 0.0254,   0.0, unitsUS );
      NEWUNIT( CComBSTR("mile"), 0.0, 1609.344, 0.0, unitsUS );
      NEWUNIT( CComBSTR("yd"),   0.0, 0.9144,   0.0, unitsUS );
      NEWUNIT( CComBSTR("ft(US survey)"),   0.0, 1200./3937.,   0.0, unitsUS );
      NEWUNIT( CComBSTR("yd(US survey)"),   0.0, 3600./3937.,   0.0, unitsUS );
   END_NEWUNIT();

   // Time
   BEGIN_NEWUNIT( CComBSTR("Time"), 0,0,1,0,0 );
      NEWUNIT( CComBSTR("sec"), 0.0,     1.0, 0.0, UnitSystemType(unitsSI + unitsUS) );
      NEWUNIT( CComBSTR("min"), 0.0,    60.0, 0.0, UnitSystemType(unitsSI + unitsUS) );
      NEWUNIT( CComBSTR("hr"),  0.0,  3600.0, 0.0, UnitSystemType(unitsSI + unitsUS) );
      NEWUNIT( CComBSTR("day"), 0.0, 86400.0, 0.0, UnitSystemType(unitsSI + unitsUS) );
   END_NEWUNIT();

   // Temperature
   BEGIN_NEWUNIT( CComBSTR("Temperature"), 0,0,0,1,0 );
      NEWUNIT( CComBSTR("C"),   0.0, 1.0,   0.0, unitsAll );
      NEWUNIT( CComBSTR("F"), -32.0, 5./9., 0.0, unitsAll );
   END_NEWUNIT();

   // Angle
   BEGIN_NEWUNIT( CComBSTR("Angle"), 0,0,0,0,1 );
      NEWUNIT( CComBSTR("rad"), 0.0, 1.0,               0.0, unitsAll  );
      NEWUNIT( CComBSTR("deg"), 0.0, 1.74532925199e-02, 0.0, unitsAll  );
   END_NEWUNIT();

   // Mass Per Length
   BEGIN_NEWUNIT( CComBSTR("MassPerLength"), 1,-1,0,0,0 );
      NEWUNIT( CComBSTR("kg/m"),    0.0, 1.0,             0.0, unitsSI );
      NEWUNIT( CComBSTR("slug/ft"), 0.0, 0.0208854342115, 0.0, unitsUS );
      NEWUNIT( CComBSTR("lb/ft"),   0.0, 1.48816394357,   0.0, unitsUS );
   END_NEWUNIT();

   // Area
   BEGIN_NEWUNIT( CComBSTR("Length2"), 0,2,0,0,0 );
      NEWUNIT( CComBSTR("m^2"),    0.0, 1.0,           0.0, unitsSI );
      NEWUNIT( CComBSTR("mm^2"),   0.0, 1.0e-06,       0.0, unitsSI );
      NEWUNIT( CComBSTR("cm^2"),   0.0, 1.0e-04,       0.0, unitsSI );
      NEWUNIT( CComBSTR("km^2"),   0.0, 1.0e+06,       0.0, unitsSI );
      NEWUNIT( CComBSTR("ft^2"),   0.0, 0.09290304,    0.0, unitsUS );
      NEWUNIT( CComBSTR("in^2"),   0.0, 0.00064516,    0.0, unitsUS );
      NEWUNIT( CComBSTR("mile^2"), 0.0, 2589988.11034, 0.0, unitsUS );
      NEWUNIT( CComBSTR("yd^2"),   0.0, 0.83612736,    0.0, unitsUS );
   END_NEWUNIT();

   // Volume
   BEGIN_NEWUNIT( CComBSTR("Length3"), 0,3,0,0,0 );
      NEWUNIT( CComBSTR("m^3"),    0.0, 1.0,            0.0, unitsSI );
      NEWUNIT( CComBSTR("mm^3"),   0.0, 1.0e-09,        0.0, unitsSI );
      NEWUNIT( CComBSTR("cm^3"),   0.0, 1.0e-06,        0.0, unitsSI );
      NEWUNIT( CComBSTR("km^3"),   0.0, 1.0e+09,        0.0, unitsSI );
      NEWUNIT( CComBSTR("ft^3"),   0.0, 0.028316846592, 0.0, unitsUS );
      NEWUNIT( CComBSTR("in^3"),   0.0, 0.000016387064, 0.0, unitsUS );
      NEWUNIT( CComBSTR("mile^3"), 0.0, 4168181825.44,  0.0, unitsUS );
      NEWUNIT( CComBSTR("yd^3"),   0.0, 0.764554857984, 0.0, unitsUS );
   END_NEWUNIT();

   // Length4 (Moment of Interita)
   BEGIN_NEWUNIT( CComBSTR("Length4"), 0,4,0,1,0 );
      NEWUNIT( CComBSTR("m^4"),    0.0, 1.0,               0.0, unitsSI );
      NEWUNIT( CComBSTR("mm^4"),   0.0, 1.0e-12,           0.0, unitsSI );
      NEWUNIT( CComBSTR("cm^4"),   0.0, 1.0e-08,           0.0, unitsSI );
      NEWUNIT( CComBSTR("km^4"),   0.0, 1.0e+12,           0.0, unitsSI );
      NEWUNIT( CComBSTR("ft^4"),   0.0, 8.63097484124e-03, 0.0, unitsUS );
      NEWUNIT( CComBSTR("in^4"),   0.0, 4.162314256e-07,   0.0, unitsUS );
      NEWUNIT( CComBSTR("mile^4"), 0.0, 6.70803841168e12,  0.0, unitsUS );
      NEWUNIT( CComBSTR("yd^4"),   0.0, 0.699108962141,    0.0, unitsUS );
   END_NEWUNIT();

   // Pressure
   BEGIN_NEWUNIT( CComBSTR("Pressure"), 1,-1,-2,0,0 );
      NEWUNIT( CComBSTR("Pa"),  0.0, 1.0,               0.0, unitsSI );
      NEWUNIT( CComBSTR("kPa"), 0.0, 1.0e+03,           0.0, unitsSI );
      NEWUNIT( CComBSTR("MPa"), 0.0, 1.0e+06,           0.0, unitsSI );
      NEWUNIT( CComBSTR("psi"), 0.0, 6.89475729317e+03, 0.0, unitsUS );
      NEWUNIT( CComBSTR("psf"), 0.0, 4.78802589803e+01, 0.0, unitsUS );
      NEWUNIT( CComBSTR("ksi"), 0.0, 6.89475729317e+06, 0.0, unitsUS );
      NEWUNIT( CComBSTR("ksf"), 0.0, 4.78802589803e+04, 0.0, unitsUS );
   END_NEWUNIT();

   // Unit Weight
   BEGIN_NEWUNIT( CComBSTR("UnitWeight"), 1,-3,-3,0,0 );
      NEWUNIT( CComBSTR("N/m^3"), 0.0, 1.0,           0.0, unitsSI );
      NEWUNIT( CComBSTR("pci"),   0.0, 271447.137526, 0.0, unitsUS );
      NEWUNIT( CComBSTR("pcf"),   0.0, 157.087463846, 0.0, unitsUS );
   END_NEWUNIT();

   // Density
   BEGIN_NEWUNIT( CComBSTR("Density"), 1,-3,0,0,0 );
      NEWUNIT( CComBSTR("kg/m^3"),    0.0, 1.0,           0.0, unitsSI );
      NEWUNIT( CComBSTR("slug/ft^3"), 0.0, 515.378818393, 0.0, unitsUS );
      NEWUNIT( CComBSTR("lb/ft^3"),   0.0, 16.018463374,  0.0, unitsUS );
   END_NEWUNIT();

   // Force
   BEGIN_NEWUNIT( CComBSTR("Force"), 1,1,-2,0,0 );
      NEWUNIT( CComBSTR("N"),   0.0, 1.0,           0.0, unitsSI );
      NEWUNIT( CComBSTR("kN"),  0.0, 1.0e+03,       0.0, unitsSI );
      NEWUNIT( CComBSTR("lbf"), 0.0, 4.44822161525, 0.0, unitsUS );
      NEWUNIT( CComBSTR("kip"), 0.0, 4448.22161525, 0.0, unitsUS );
      NEWUNIT( CComBSTR("ton"), 0.0, 8896.44323052, 0.0, unitsUS );
   END_NEWUNIT();

   // Force Per Length
   BEGIN_NEWUNIT( CComBSTR("ForcePerLength"), 1,0,-2,0,0 );
      NEWUNIT( CComBSTR("N/m"),    0.0, 1.0,           0.0, unitsSI );
      NEWUNIT( CComBSTR("N/mm"),   0.0, 1.0e+03,       0.0, unitsSI );
      NEWUNIT( CComBSTR("lbf/ft"), 0.0, 14.5939029372, 0.0, unitsUS );
      NEWUNIT( CComBSTR("lbf/in"), 0.0, 175.126835246, 0.0, unitsUS );
      NEWUNIT( CComBSTR("kip/ft"), 0.0, 14593.9029372, 0.0, unitsUS );
      NEWUNIT( CComBSTR("kip/in"), 0.0, 175126.835246, 0.0, unitsUS );
   END_NEWUNIT();

   // Moment
   BEGIN_NEWUNIT( CComBSTR("Moment"), 1,2,-2,0,0 );
      NEWUNIT( CComBSTR("N-m"),    0.0, 1.0,            0.0, unitsSI );
      NEWUNIT( CComBSTR("N-mm"),   0.0, 1.0e+03,        0.0, unitsSI );
      NEWUNIT( CComBSTR("kN-m"),   0.0, 1.0e+03,        0.0, unitsSI );
      NEWUNIT( CComBSTR("lbf-in"), 0.0, 0.112984829028, 0.0, unitsUS );
      NEWUNIT( CComBSTR("lbf-ft"), 0.0, 1.35581794833,  0.0, unitsUS );
      NEWUNIT( CComBSTR("kip-ft"), 0.0, 1355.81794833,  0.0, unitsUS );
      NEWUNIT( CComBSTR("kip-in"), 0.0, 112.984829028,  0.0, unitsUS );
   END_NEWUNIT();

   // Thermal expansion
   BEGIN_NEWUNIT( CComBSTR("ThermalExpansion"), 0,0,0,-1,0 );
      NEWUNIT( CComBSTR("1/C"),   0.0, 1.0,   0.0, unitsAll );
      NEWUNIT( CComBSTR("1/F"),   0.0, 5./9., 0.0, unitsAll );
   END_NEWUNIT();

   return S_OK;
}

//STDMETHODIMP CUnitTypes::get_Count(long* retval)
//{
//      // Implemented by ICollectionOnSTLImpl
//}

STDMETHODIMP::CUnitTypes::get_Count(CollectionIndexType* retval)
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

   typedef CComEnumOnSTL<IEnumUnitTypes,&IID_IEnumUnitTypes, IUnitType*, _CopyVariantToInterface<IUnitType>, std::vector<CComVariant> > Enum;
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

   // OK, this is a new unit type for this server
   CComObject<CUnitType>* pUnitType;
   HRESULT hr = CComObject<CUnitType>::CreateInstance( &pUnitType );
   if ( FAILED(hr) )
      return E_FAIL;

   pUnitType->Init(m_pUnitServer,label,m,l,t,k,a);
   
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
   std::_tstring strLabel( OLE2T(label) );
   hr = unitType.Advise( GetUnknown(), IID_IUnitTypeEventSink, &dwCookie );
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


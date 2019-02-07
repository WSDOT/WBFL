///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2019  Washington State Department of Transportation
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

// DisplayUnitMgr2.cpp : Implementation of CDisplayUnitMgr2
#include "stdafx.h"
#include "WBFLUnitServer.h"
#include "DisplayUnitMgr2.h"
#include "DisplayUnitGroup.h"
#include "Helper.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


class FindDisplayUnitGroup
{
public:
   FindDisplayUnitGroup(const BSTR& bstr) : m_bstrTarget(bstr) {}
   bool operator()(const CComVariant& var)
   {
      _ASSERT( var.vt == VT_DISPATCH );
      CComQIPtr<IDisplayUnitGroup> pDUG( var.pdispVal );
      CComBSTR bstrGroup;
      pDUG->get_Name( &bstrGroup );
      return (_tcscmp( m_bstrTarget, bstrGroup ) == 0);
   }

private:
   CComBSTR m_bstrTarget;
};

/////////////////////////////////////////////////////////////////////////////
// CDisplayUnitMgr
void CDisplayUnitMgr2::Init(IUnitServer* pUnitServer)
{
   ATLASSERT( pUnitServer != 0 );
   m_pUnitServer = pUnitServer;
}

void CDisplayUnitMgr2::UnadviseDisplayUnitGroup(IDisplayUnitGroup* pGroup)
{
   ATLASSERT(pGroup != 0);
   USES_CONVERSION;

   InternalAddRef(); // Counteract Release() in Create()

   //
   // Disconnection from connection point
   //

   // Get the lookup key
   CComBSTR bstrKey;
   pGroup->get_Name(&bstrKey);
   std::_tstring strKey( OLE2T(bstrKey) );

   // Lookup the cookie
   std::map<std::_tstring,DWORD>::iterator found;
   found = m_GroupCookies.find( strKey );
   ATLASSERT( found != m_GroupCookies.end() );

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( pGroup );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IDisplayUnitGroupEvents, &pCP );
   pCP->Unadvise( (*found).second );

   // Remove cookie from map
   m_GroupCookies.erase( found );
}

void CDisplayUnitMgr2::UnadviseAll()
{
   std::vector<CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CComVariant& var = *iter;
      CComQIPtr<IDisplayUnitGroup> pGroup(var.pdispVal);
      UnadviseDisplayUnitGroup(pGroup);
   }
}

void CDisplayUnitMgr2::FinalRelease()
{
   UnadviseAll();
}

HRESULT CDisplayUnitMgr2::BadDisplayUnitGroupError(BSTR name)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), IDS_E_BADDISPLAYUNITGROUP, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, str, W2T(name) );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return CComCoClass<CDisplayUnitMgr2>::Error(oleMsg,IDH_E_BADDISPLAYUNITGROUP, GetHelpFile(), IID_IDisplayUnitMgr2, UNITS_E_BADDISPLAYUNITGROUP);
}

STDMETHODIMP CDisplayUnitMgr2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IDisplayUnitMgr2,
	};
	for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDisplayUnitMgr2::get_Item(BSTR bstrGroup,IDisplayUnitGroup** retval)
{
   CHECK_IN(bstrGroup);
   CHECK_RETOBJ(retval);

   std::vector<CComVariant>::iterator found;
   found = std::find_if( m_coll.begin(), m_coll.end(), FindDisplayUnitGroup(bstrGroup) );

   if ( found == m_coll.end() )
      return BadDisplayUnitGroupError(bstrGroup);

   CComVariant& var = *found;
   var.pdispVal->QueryInterface(retval);
   return S_OK;
}

STDMETHODIMP CDisplayUnitMgr2::get_Count(CollectionIndexType* retval)
{
   CHECK_RETVAL(retval);
   long count;
   IDisplayUnitGroup2Collection::get_Count(&count);
   *retval = count;
   return S_OK;
}

//STDMETHODIMP CDisplayUnitMgr2::get__NewEnum(IUnknown** retval) override;
//{
//   // Implemented by ATL
//   return S_OK;
//}

//STDMETHODIMP CDisplayUnitMgr2::get_Count(long* retval)
//{
//   // Implemented by ATL
//   return S_OK;
//}

STDMETHODIMP CDisplayUnitMgr2::Add(BSTR bstrGroup,BSTR bstrUnitType,IDisplayUnitGroup** newGroup)
{
   USES_CONVERSION;
   HRESULT hr = S_OK;
   CHECK_RETOBJ(newGroup);

   CComPtr<IDisplayUnitGroup> pExistingGroup;
   hr = get_Item(bstrGroup,&pExistingGroup);
   if ( SUCCEEDED(hr) )
   {
      // A group with this name already exists.
      return CComCoClass<CDisplayUnitMgr2>::Error(IDS_E_GROUPALREADYDEFINED,IDH_E_GROUPALREADYDEFINED, GetHelpFile(),IID_IDisplayUnitMgr2,UNITS_E_GROUPALREADYDEFINED);
   }

   // OK, a group named bstrGroup doesn't exist. But before we
   // create it, get the unit type object
   CComPtr<IUnitTypes> pUnitTypes;
   m_pUnitServer->get_UnitTypes(&pUnitTypes);
   CComPtr<IUnitType> pUnitType;
   hr = pUnitTypes->get_Item(CComVariant(bstrUnitType),&pUnitType);
   if ( FAILED(hr) )
   {
      TCHAR str[256];
      ::LoadString( _Module.GetModuleInstance(), IDS_E_BADUNITTYPE, str, 256);
      TCHAR msg[256];
      int cOut = _stprintf_s( msg, 256, str, W2T(bstrUnitType) );
      _ASSERTE( cOut < 256 );
      CComBSTR oleMsg(msg);
      return CComCoClass<CDisplayUnitMgr2>::Error(oleMsg,IDH_E_BADUNITTYPE, GetHelpFile(),IID_IDisplayUnitMgr2,UNITS_E_BADUNITTYPE);
   }

   // Got the unit type object. Create the group
   CComObject<CDisplayUnitGroup>* pNewGroup;
   hr = CComObject<CDisplayUnitGroup>::CreateInstance(&pNewGroup);
   if ( FAILED(hr) )
      return hr;

   pNewGroup->Init( bstrGroup,  pUnitType );

   pNewGroup->QueryInterface(newGroup);

   // Hookup to the connection point
   DWORD dwCookie;
   std::_tstring strKey( OLE2T(bstrGroup) );
   CComPtr<IDisplayUnitGroup> pCP(pNewGroup);
   pCP.Advise( GetUnknown(), IID_IDisplayUnitGroupEvents, &dwCookie );
   m_GroupCookies.insert( std::make_pair(strKey,dwCookie) );

   InternalRelease(); // Break the circular ref with the connected object

   CComVariant var(*newGroup);
   m_coll.push_back(var);

   Fire_OnDisplayUnitGroupCreated(*newGroup);

   return S_OK;
}

STDMETHODIMP CDisplayUnitMgr2::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnDisplayUnitGroupsCleared();
   return S_OK;
}

STDMETHODIMP CDisplayUnitMgr2::Remove(BSTR bstrGroup)
{
   CHECK_IN(bstrGroup);

   std::vector<CComVariant>::iterator found;
   found = std::find_if( m_coll.begin(), m_coll.end(), FindDisplayUnitGroup(bstrGroup) );

   if ( found == m_coll.end() )
      return BadDisplayUnitGroupError(bstrGroup);

   CComQIPtr<IDisplayUnitGroup> pGroup((*found).pdispVal);
   UnadviseDisplayUnitGroup(pGroup);
   pGroup.Release();

   m_coll.erase(found);

   Fire_OnDisplayUnitGroupRemoved(bstrGroup);

   return S_OK;
}

STDMETHODIMP CDisplayUnitMgr2::get__EnumDisplayUnitGroups(IEnumDisplayUnitGroups** enumDisplayUnitGroups)
{
   CHECK_RETOBJ(enumDisplayUnitGroups);

   typedef CComEnumOnSTL<IEnumDisplayUnitGroups,&IID_IEnumDisplayUnitGroups, IDisplayUnitGroup*, _CopyVariantToInterface<IDisplayUnitGroup>, std::vector<CComVariant> > Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( nullptr, m_coll );
   if ( FAILED(hr) )
      return hr;

   pEnum->QueryInterface( enumDisplayUnitGroups );

   return S_OK;
}

///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2013  Washington State Department of Transportation
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

// VertCurveCollection.cpp : Implementation of CVertCurveCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "VertCurveCollection.h"
#include "VertCurveFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVertCurveCollection
HRESULT CVertCurveCollection::FinalConstruct()
{
   CComObject<CVertCurveFactory>* pFactory;
   CComObject<CVertCurveFactory>::CreateInstance(&pFactory);

   m_Factory = pFactory;
   return S_OK;
}

void CVertCurveCollection::FinalRelease()
{
   UnadviseAll();
}

STDMETHODIMP CVertCurveCollection::get_Item(CogoElementKey key, IVertCurve **pVal)
{
   CHECK_RETVAL(pVal);
   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found == m_coll.end() )
   {
      return VertCurveNotFound(key);
   }

   std::pair<CogoElementKey,CComVariant> p = *found;
   p.second.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CVertCurveCollection::putref_Item(CogoElementKey key, IVertCurve *newVal)
{
   CHECK_IN(newVal);

   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found == m_coll.end() )
   {
      return VertCurveNotFound(key);
   }

   CComVariant& var = (*found).second;

   CComQIPtr<IVertCurve> old_VertCurve(var.pdispVal);
   Unadvise(key,old_VertCurve);

   var = newVal;
   Advise(key,newVal);

   Fire_OnVertCurveChanged(key,newVal);

	return S_OK;
}

STDMETHODIMP CVertCurveCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
	return S_OK;
}

STDMETHODIMP CVertCurveCollection::Remove(CogoElementKey key)
{
   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found == m_coll.end() )
   {
      return VertCurveNotFound(key);
   }

   CComVariant& var = (*found).second;
   CComQIPtr<IVertCurve> VertCurve(var.pdispVal);
   Unadvise(key,VertCurve);

   m_coll.erase(found);

   Fire_OnVertCurveRemoved(key);

	return S_OK;
}

STDMETHODIMP CVertCurveCollection::Add(CogoElementKey key, IProfilePoint* pbg, IProfilePoint* pvi, IProfilePoint* pfg,Float64 l1,Float64 l2,IVertCurve* *vc)
{
   CHECK_IN(pbg);
   CHECK_IN(pvi);
   CHECK_IN(pfg);
   if ( l1 <= 0.0 || l2 <= 0.0 )
      return E_INVALIDARG;

   if ( vc != NULL )
   {
      CHECK_RETOBJ(vc);
   }

   CComPtr<IVertCurve> newVC;
   m_Factory->CreateVertCurve(&newVC);
   newVC->putref_PBG(pbg);
   newVC->putref_PVI(pvi);
   newVC->putref_PFG(pfg);
   newVC->put_L1(l1);
   newVC->put_L2(l2);

   if ( vc != NULL )
   {
      (*vc) = newVC;
      (*vc)->AddRef();
   }

   return AddEx(key,newVC);
}

STDMETHODIMP CVertCurveCollection::AddEx(CogoElementKey key, IVertCurve* newVal)
{
   CHECK_IN(newVal);
   
   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found != m_coll.end() )
   {
      return VertCurveAlreadyDefined(key);
   }

   CComQIPtr<IUnknown,&IID_IUnknown> pDisp(newVal);
   CComVariant var(pDisp);
   std::pair<std::map<CogoElementKey,CComVariant>::iterator,bool> result;
   result = m_coll.insert(std::make_pair(key,var));
   if ( result.second == false )
   {
      return E_FAIL;
   }

   // Hookup to the connection VertCurve
   Advise(key,newVal);

   Fire_OnVertCurveAdded(key,newVal);

	return S_OK;
}

STDMETHODIMP CVertCurveCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnVertCurvesCleared();
	return S_OK;
}

STDMETHODIMP CVertCurveCollection::FindKey(IVertCurve* vc,CogoElementKey* key)
{
   CHECK_IN(vc);
   CHECK_RETVAL(key);

   std::map<CogoElementKey,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      std::pair<CogoElementKey,CComVariant> item = *iter;
      CComQIPtr<IVertCurve> value( item.second.pdispVal );
      ATLASSERT( value != NULL );
      if ( value.IsEqualObject(vc) )
      {
         *key = item.first;
         return S_OK;
      }
   }

   return E_FAIL;
}

STDMETHODIMP CVertCurveCollection::get__EnumKeys(IEnumKeys** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumKeys,&IID_IEnumKeys, CogoElementKey, MapCopyKey<std::map<CogoElementKey,CComVariant>>, std::map<CogoElementKey,CComVariant> > Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( NULL, m_coll );
   if ( FAILED(hr) )
      return hr;

   pEnum->QueryInterface( ppenum );

   return S_OK;
}

STDMETHODIMP CVertCurveCollection::get__EnumVertCurves(IEnumVertCurves** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumVertCurves,&IID_IEnumVertCurves, IVertCurve*, MapCopyValueToInterface<std::map<CogoElementKey,CComVariant>,IVertCurve*>, std::map<CogoElementKey,CComVariant> > Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( NULL, m_coll );
   if ( FAILED(hr) )
      return hr;

   pEnum->QueryInterface( ppenum );

   return S_OK;
}

STDMETHODIMP CVertCurveCollection::Key(CollectionIndexType index,CogoElementKey* key)
{
   CHECK_RETVAL(key);

   if ( !IsValidIndex(index,m_coll) )
      return E_INVALIDARG;

   std::map<CogoElementKey,CComVariant>::iterator iter = m_coll.begin();
   for ( CollectionIndexType i = 0; i < index; i++ )
      iter++;

   std::pair<CogoElementKey,CComVariant> p = *iter;
   *key = p.first;

   return S_OK;
}

STDMETHODIMP CVertCurveCollection::putref_Factory(IVertCurveFactory* factory)
{
   CHECK_IN(factory);
   m_Factory = factory;
   return S_OK;
}

STDMETHODIMP CVertCurveCollection::get_Factory(IVertCurveFactory* *factory)
{
   CHECK_RETOBJ(factory);
   (*factory) = m_Factory;
   (*factory)->AddRef();
   return S_OK;
}

STDMETHODIMP CVertCurveCollection::OnVertCurveChanged(IVertCurve* vc)
{
   CogoElementKey key;
   HRESULT hr = FindKey(vc,&key);

   // This container only listens to events from VertCurve objects in this 
   // container. If the key isn't found an error has been made somewhere
   ATLASSERT( SUCCEEDED(hr) );

   Fire_OnVertCurveChanged(key,vc);

   return S_OK;
}

STDMETHODIMP CVertCurveCollection::Clone(IVertCurveCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CVertCurveCollection>* pClone;
   CComObject<CVertCurveCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<IEnumVertCurves> enumVC;
   get__EnumVertCurves(&enumVC);

   CollectionIndexType count = 0;
   CComPtr<IVertCurve> vc;
   while ( enumVC->Next(1,&vc,NULL) != S_FALSE )
   {
      CComPtr<IVertCurve> cloneVC;
      vc->Clone(&cloneVC);

      CogoElementKey key;
      Key(count++,&key);

      (*clone)->AddEx(key,cloneVC);
   }

   (*clone)->putref_Factory(m_Factory);

   return S_OK;
}

void CVertCurveCollection::Advise(CogoElementKey key,IVertCurve* vc)
{
   DWORD dwCookie;
   CComPtr<IVertCurve> pCP(vc);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_IVertCurveEvents, &dwCookie );
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection VertCurve with VertCurve object\n");
      return;
   }

   m_Cookies.insert( std::make_pair(key,dwCookie) );

   InternalRelease(); // Break circular reference
}

void CVertCurveCollection::Unadvise(CogoElementKey key,IVertCurve* vc)
{
   ATLASSERT(vc != 0);

   //
   // Disconnection from connection VertCurve
   //

   // Lookup the cookie
   std::map<CogoElementKey,DWORD>::iterator found;
   found = m_Cookies.find( key );
   if ( found == m_Cookies.end() )
   {
      ATLTRACE("Failed to disconnect connection VertCurve with VertCurve object\n");
      return;
   }

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection VertCurve and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( vc );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IVertCurveEvents, &pCP );
   DWORD dwCookie = (*found).second;
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));

   // Remove cookie from map
   m_Cookies.erase( key );
}

void CVertCurveCollection::UnadviseAll()
{
   std::map<CogoElementKey,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CogoElementKey key = (*iter).first;
      CComQIPtr<IVertCurve> vc( (*iter).second.pdispVal );
      Unadvise(key,vc);
   }
}

HRESULT CVertCurveCollection::VertCurveNotFound(CogoElementKey key)
{
   return VertCurveKeyError(key,IDS_E_VERTCURVENOTFOUND,COGO_E_VERTCURVENOTFOUND);
}

HRESULT CVertCurveCollection::VertCurveAlreadyDefined(CogoElementKey key)
{
   return VertCurveKeyError(key,IDS_E_VERTCURVEALREADYDEFINED,COGO_E_VERTCURVEALREADYDEFINED);
}

HRESULT CVertCurveCollection::VertCurveKeyError(CogoElementKey key,UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, key );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return CComCoClass<CVertCurveCollection,&CLSID_VertCurveCollection>::Error(oleMsg, IID_IVertCurveCollection, hRes);
}

HRESULT CVertCurveCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   pSave->put_Property(CComBSTR("VertCurveFactory"),CComVariant(m_Factory));
   return S_OK;
}

HRESULT CVertCurveCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->get_Property(CComBSTR("VertCurveFactory"),&var);
   m_Factory.Release();
   _CopyVariantToInterface<IVertCurveFactory>::copy(&m_Factory,&var);
   return S_OK;
}

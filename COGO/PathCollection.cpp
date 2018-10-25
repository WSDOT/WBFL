///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// PathCollection.cpp : Implementation of CPathCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "PathCollection.h"
#include "PathFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathCollection
HRESULT CPathCollection::FinalConstruct()
{
   CComObject<CPathFactory>* pFactory;
   CComObject<CPathFactory>::CreateInstance(&pFactory);

   m_Factory = pFactory;
   return S_OK;
}

void CPathCollection::FinalRelease()
{
   UnadviseAll();
   m_coll.clear();
}

STDMETHODIMP CPathCollection::get_Item(CogoElementKey key, IPath **pVal)
{
   CHECK_RETVAL(pVal);
   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found == m_coll.end() )
   {
      return PathNotFound(key);
   }

   std::pair<CogoElementKey,CComVariant> p = *found;
   p.second.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CPathCollection::putref_Item(CogoElementKey key, IPath *newVal)
{
   CHECK_IN(newVal);

   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found == m_coll.end() )
   {
      return PathNotFound(key);
   }

   CComVariant& var = (*found).second;

   CComQIPtr<IPath> old_Path(var.pdispVal);
   Unadvise(key,old_Path);

   var = newVal;
   Advise(key,newVal);

   Fire_OnPathChanged(this,key,newVal);

	return S_OK;
}

STDMETHODIMP CPathCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
	return S_OK;
}

STDMETHODIMP CPathCollection::Remove(CogoElementKey key)
{
   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found == m_coll.end() )
   {
      return PathNotFound(key);
   }

   CComVariant& var = (*found).second;
   CComQIPtr<IPath> pp(var.pdispVal);
   Unadvise(key,pp);

   m_coll.erase(found);

   Fire_OnPathRemoved(this,key);

	return S_OK;
}

STDMETHODIMP CPathCollection::Add(CogoElementKey key, IPath* *path)
{
   if ( path != NULL )
   {
      CHECK_RETOBJ(path);
   }

   CComPtr<IPath> newPath;
   m_Factory->CreatePath(&newPath);

   if ( path != NULL )
   {
      (*path) = newPath;
      (*path)->AddRef();
   }

   return AddEx(key,newPath);
}

STDMETHODIMP CPathCollection::AddEx(CogoElementKey key, IPath* newVal)
{
   CHECK_IN(newVal);

   VARIANT_BOOL bIsValid;
   m_Factory->IsValidType(newVal,&bIsValid);
   if ( bIsValid != VARIANT_TRUE )
      return E_INVALIDARG;
   
   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found != m_coll.end() )
   {
      return PathAlreadyDefined(key);
   }

   CComQIPtr<IUnknown,&IID_IUnknown> pDisp(newVal);
   CComVariant var(pDisp);
   m_coll.insert(std::make_pair(key,var));

   // Hookup to the connection Path
   Advise(key,newVal);

   Fire_OnPathAdded(this,key,newVal);

	return S_OK;
}

STDMETHODIMP CPathCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnPathsCleared(this);
	return S_OK;
}

STDMETHODIMP CPathCollection::FindKey(IPath* pp,CogoElementKey* key)
{
   CHECK_IN(pp);
   CHECK_RETVAL(key);

   std::map<CogoElementKey,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      std::pair<CogoElementKey,CComVariant> item = *iter;
      CComQIPtr<IPath> value( item.second.pdispVal );
      ATLASSERT( value != NULL );
      if ( value.IsEqualObject(pp) )
      {
         *key = item.first;
         return S_OK;
      }
   }

   return E_FAIL;
}

STDMETHODIMP CPathCollection::get__EnumKeys(IEnumKeys** ppenum)
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

STDMETHODIMP CPathCollection::Key(CollectionIndexType index,CogoElementKey* key)
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

STDMETHODIMP CPathCollection::get_Factory(IPathFactory** factory)
{
   CHECK_RETOBJ(factory);

   (*factory) = m_Factory;
   (*factory)->AddRef();

   return S_OK;
}

STDMETHODIMP CPathCollection::putref_Factory(IPathFactory* factory)
{
   CHECK_IN(factory);
   m_Factory = factory;
   return S_OK;
}

STDMETHODIMP CPathCollection::get__EnumPaths(IEnumPaths** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumPaths,&IID_IEnumPaths, IPath*, MapCopyValueToInterface<std::map<CogoElementKey,CComVariant>,IPath*>, std::map<CogoElementKey,CComVariant> > Enum;
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

STDMETHODIMP CPathCollection::Clone(IPathCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CPathCollection>* pClone;
   CComObject<CPathCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CollectionIndexType count = 0;
   CComPtr<IEnumPaths> enumPaths;
   get__EnumPaths(&enumPaths);
   CComPtr<IPath> Path;
   while ( enumPaths->Next(1,&Path,NULL) != S_FALSE )
   {
      CComPtr<IPath> clonePath;
      Path->Clone(&clonePath);

      CogoElementKey key;
      Key(count++,&key);

      (*clone)->AddEx(key,clonePath);

      Path.Release();
   };

   (*clone)->putref_Factory(m_Factory);

   return S_OK;
}

void CPathCollection::Advise(CogoElementKey key,IPath* Path)
{
   DWORD dwCookie;
   HRESULT hr = AtlAdvise(Path,GetUnknown(),IID_IPathEvents,&dwCookie);
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point with Path object\n");
      return;
   }

   m_Cookies.insert( std::make_pair(key,dwCookie) );

   InternalRelease(); // Break circular reference
}

void CPathCollection::Unadvise(CogoElementKey key,IPath* Path)
{
   ATLASSERT(Path != 0);

   //
   // Disconnection from connection Path
   //

   // Lookup the cookie
   std::map<CogoElementKey,DWORD>::iterator found;
   found = m_Cookies.find( key );
   if ( found == m_Cookies.end() )
   {
      ATLTRACE("Failed to disconnect connection point with Path object\n");
      return;
   }

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection Path and disconnection
   DWORD dwCookie = (*found).second;
   HRESULT hr = AtlUnadvise(Path,IID_IPathEvents,dwCookie);
   ATLASSERT(SUCCEEDED(hr));

   // Remove cookie from map
   m_Cookies.erase( key );
}

void CPathCollection::UnadviseAll()
{
   std::map<CogoElementKey,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CogoElementKey key = (*iter).first;
      CComQIPtr<IPath> Path( (*iter).second.pdispVal );
      Unadvise(key,Path);
   }
}

HRESULT CPathCollection::PathNotFound(CogoElementKey key)
{
   return PathKeyError(key,IDS_E_PATHNOTFOUND,COGO_E_PATHNOTFOUND);
}

HRESULT CPathCollection::PathAlreadyDefined(CogoElementKey key)
{
   return PathKeyError(key,IDS_E_PATHALREADYDEFINED,COGO_E_PATHALREADYDEFINED);
}

HRESULT CPathCollection::PathKeyError(CogoElementKey key,UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, key );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return CComCoClass<CPathCollection,&CLSID_PathCollection>::Error(oleMsg, IID_IPathCollection, hRes);
}

HRESULT CPathCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   pSave->put_Property(CComBSTR("PathFactory"),CComVariant(m_Factory));
   return S_OK;
}

HRESULT CPathCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->get_Property(CComBSTR("PathFactory"),&var);
   m_Factory.Release();
   _CopyVariantToInterface<IPathFactory>::copy(&m_Factory,&var);
   return S_OK;
}

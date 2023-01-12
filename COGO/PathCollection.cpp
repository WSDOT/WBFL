///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

STDMETHODIMP CPathCollection::get_Item(CogoObjectID id, IPath **pVal)
{
   CHECK_RETVAL(pVal);
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return PathNotFound(id);
   }

   std::pair<CogoObjectID,CComVariant> p = *found;
   p.second.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CPathCollection::putref_Item(CogoObjectID id, IPath *newVal)
{
   CHECK_IN(newVal);

   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return PathNotFound(id);
   }

   CComVariant& var = (*found).second;

   CComQIPtr<IPath> old_Path(var.pdispVal);
   Unadvise(id,old_Path);

   var = newVal;
   Advise(id,newVal);

   Fire_OnPathChanged(this,id,newVal);

	return S_OK;
}

STDMETHODIMP CPathCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
	return S_OK;
}

STDMETHODIMP CPathCollection::Remove(CogoObjectID id)
{
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return PathNotFound(id);
   }

   CComVariant& var = (*found).second;
   CComQIPtr<IPath> pp(var.pdispVal);
   Unadvise(id,pp);

   m_coll.erase(found);

   Fire_OnPathRemoved(this,id);

	return S_OK;
}

STDMETHODIMP CPathCollection::Add(CogoObjectID id, IPath* *path)
{
   if ( path != nullptr )
   {
      CHECK_RETOBJ(path);
   }

   CComPtr<IPath> newPath;
   m_Factory->CreatePath(&newPath);

   if ( path != nullptr )
   {
      (*path) = newPath;
      (*path)->AddRef();
   }

   return AddEx(id,newPath);
}

STDMETHODIMP CPathCollection::AddEx(CogoObjectID id, IPath* newVal)
{
   CHECK_IN(newVal);

   VARIANT_BOOL bIsValid;
   m_Factory->IsValidType(newVal,&bIsValid);
   if ( bIsValid != VARIANT_TRUE )
      return E_INVALIDARG;
   
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found != m_coll.end() )
   {
      return PathAlreadyDefined(id);
   }

   CComQIPtr<IUnknown,&IID_IUnknown> pDisp(newVal);
   CComVariant var(pDisp);
   m_coll.insert(std::make_pair(id,var));

   // Hookup to the connection Path
   Advise(id,newVal);

   Fire_OnPathAdded(this,id,newVal);

	return S_OK;
}

STDMETHODIMP CPathCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnPathsCleared(this);
	return S_OK;
}

STDMETHODIMP CPathCollection::FindID(IPath* pp,CogoObjectID* id)
{
   CHECK_IN(pp);
   CHECK_RETVAL(id);

   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      std::pair<CogoObjectID,CComVariant> item = *iter;
      CComQIPtr<IPath> value( item.second.pdispVal );
      ATLASSERT( value != nullptr );
      if ( value.IsEqualObject(pp) )
      {
         *id = item.first;
         return S_OK;
      }
   }

   return E_FAIL;
}

STDMETHODIMP CPathCollection::get__EnumIDs(IEnumIDs** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumIDs,&IID_IEnumIDs, CogoObjectID, MapCopyID<std::map<CogoObjectID,CComVariant>>, std::map<CogoObjectID,CComVariant> > Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( nullptr, m_coll );
   if ( FAILED(hr) )
      return hr;

   pEnum->QueryInterface( ppenum );

   return S_OK;
}

STDMETHODIMP CPathCollection::ID(CollectionIndexType index,CogoObjectID* id)
{
   CHECK_RETVAL(id);

   if ( !IsValidIndex(index,m_coll) )
      return E_INVALIDARG;

   std::map<CogoObjectID,CComVariant>::iterator iter = m_coll.begin();
   for ( CollectionIndexType i = 0; i < index; i++ )
      iter++;

   std::pair<CogoObjectID,CComVariant> p = *iter;
   *id = p.first;

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

   typedef CComEnumOnSTL<IEnumPaths,&IID_IEnumPaths, IPath*, MapCopyValueToInterface<std::map<CogoObjectID,CComVariant>,IPath*>, std::map<CogoObjectID,CComVariant> > Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( nullptr, m_coll );
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
   while ( enumPaths->Next(1,&Path,nullptr) != S_FALSE )
   {
      CComPtr<IPath> clonePath;
      Path->Clone(&clonePath);

      CogoObjectID id;
      ID(count++,&id);

      (*clone)->AddEx(id,clonePath);

      Path.Release();
   };

   (*clone)->putref_Factory(m_Factory);

   return S_OK;
}

void CPathCollection::Advise(CogoObjectID id,IPath* Path)
{
   DWORD dwCookie;
   HRESULT hr = AtlAdvise(Path,GetUnknown(),IID_IPathEvents,&dwCookie);
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point with Path object\n");
      return;
   }

   m_Cookies.insert( std::make_pair(id,dwCookie) );

   InternalRelease(); // Break circular reference
}

void CPathCollection::Unadvise(CogoObjectID id,IPath* Path)
{
   ATLASSERT(Path != 0);

   //
   // Disconnection from connection Path
   //

   // Lookup the cookie
   std::map<CogoObjectID,DWORD>::iterator found;
   found = m_Cookies.find( id );
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
   m_Cookies.erase( id );
}

void CPathCollection::UnadviseAll()
{
   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CogoObjectID id = (*iter).first;
      CComQIPtr<IPath> Path( (*iter).second.pdispVal );
      Unadvise(id,Path);
   }
}

HRESULT CPathCollection::PathNotFound(CogoObjectID id)
{
   return PathIDError(id,IDS_E_PATHNOTFOUND,COGO_E_PATHNOTFOUND);
}

HRESULT CPathCollection::PathAlreadyDefined(CogoObjectID id)
{
   return PathIDError(id,IDS_E_PATHALREADYDEFINED,COGO_E_PATHALREADYDEFINED);
}

HRESULT CPathCollection::PathIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, id );
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

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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathCollection
HRESULT CPathCollection::FinalConstruct()
{
   return S_OK;
}

void CPathCollection::FinalRelease()
{
   m_coll.clear();
}

STDMETHODIMP CPathCollection::get_Item(CogoObjectID id, IPath **pVal)
{
   CHECK_RETVAL(pVal);
   auto found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return PathNotFound(id);
   }

   auto p = *found;
   p.second.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CPathCollection::putref_Item(CogoObjectID id, IPath *newVal)
{
   CHECK_IN(newVal);

   auto found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return PathNotFound(id);
   }

   CComVariant& var = (*found).second;

   CComQIPtr<IPath> old_Path(var.pdispVal);

   var = newVal;

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
   auto found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return PathNotFound(id);
   }

   CComVariant& var = (*found).second;
   CComQIPtr<IPath> pp(var.pdispVal);

   m_coll.erase(found);

	return S_OK;
}

STDMETHODIMP CPathCollection::Add(CogoObjectID id, IPath* newVal)
{
   CHECK_IN(newVal);
   
   auto found = m_coll.find(id);
   if ( found != m_coll.end() )
   {
      return PathAlreadyDefined(id);
   }

   CComQIPtr<IUnknown,&IID_IUnknown> pDisp(newVal);
   CComVariant var(pDisp);
   m_coll.insert(std::make_pair(id,var));

   return S_OK;
}

STDMETHODIMP CPathCollection::Clear()
{
   m_coll.clear();
	return S_OK;
}

STDMETHODIMP CPathCollection::FindID(IPath* pp,CogoObjectID* id)
{
   CHECK_IN(pp);
   CHECK_RETVAL(id);

   for( auto& item : m_coll)
   {
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

//STDMETHODIMP CPathCollection::get__EnumIDs(IEnumIDs** ppenum)
//{
//   CHECK_RETOBJ(ppenum);
//
//   using Enum = CComEnumOnSTL<IEnumIDs,&IID_IEnumIDs, CogoObjectID, MapCopyID<std::map<CogoObjectID,CComVariant>>, std::map<CogoObjectID,CComVariant> >;
//   CComObject<Enum>* pEnum;
//   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
//   if ( FAILED(hr) )
//      return hr;
//
//   hr = pEnum->Init( nullptr, m_coll );
//   if ( FAILED(hr) )
//      return hr;
//
//   pEnum->QueryInterface( ppenum );
//
//   return S_OK;
//}

STDMETHODIMP CPathCollection::ID(CollectionIndexType index,CogoObjectID* id)
{
   CHECK_RETVAL(id);

   if(m_coll.size() <= index)
      return E_INVALIDARG;

   auto iter = m_coll.begin();
   std::advance(iter, index);

   std::pair<CogoObjectID,CComVariant> p = *iter;
   *id = p.first;

   return S_OK;
}

STDMETHODIMP CPathCollection::get__EnumPaths(IEnumPaths** ppenum)
{
   CHECK_RETOBJ(ppenum);

   using Enum = CComEnumOnSTL<IEnumPaths,&IID_IEnumPaths, IPath*, MapCopyValueToInterface<std::map<CogoObjectID,CComVariant>,IPath*>, std::map<CogoObjectID,CComVariant> >;
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
   CComPtr<IPath> path;
   while ( enumPaths->Next(1,&path,nullptr) != S_FALSE )
   {
      CComPtr<IPath> clonePath;
      path->Clone(&clonePath);

      CogoObjectID id;
      ID(count++,&id);

      (*clone)->Add(id,clonePath);

      path.Release();
   };

   return S_OK;
}


HRESULT CPathCollection::PathNotFound(CogoObjectID id)
{
   return E_INVALIDARG;
}

HRESULT CPathCollection::PathAlreadyDefined(CogoObjectID id)
{
   return E_INVALIDARG;
}

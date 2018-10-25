///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2014  Washington State Department of Transportation
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

// ProfilePointCollection.cpp : Implementation of CProfilePointCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "ProfilePointCollection.h"
#include "ProfilePointFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfilePointCollection

HRESULT CProfilePointCollection::FinalConstruct()
{
   CComObject<CProfilePointFactory>* pFactory;
   CComObject<CProfilePointFactory>::CreateInstance(&pFactory);

   m_Factory = pFactory;
   return S_OK;
}

void CProfilePointCollection::FinalRelease()
{
   UnadviseAll();
}

STDMETHODIMP CProfilePointCollection::get_Item(CogoObjectID id, IProfilePoint **pVal)
{
   CHECK_RETVAL(pVal);
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return ProfilePointNotFound(id);
   }

   std::pair<CogoObjectID,CComVariant> p = *found;
   p.second.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CProfilePointCollection::putref_Item(CogoObjectID id, IProfilePoint *newVal)
{
   CHECK_IN(newVal);

   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return ProfilePointNotFound(id);
   }

   CComVariant& var = (*found).second;

   CComQIPtr<IProfilePoint> old_ProfilePoint(var.pdispVal);
   Unadvise(id,old_ProfilePoint);

   var = newVal;
   Advise(id,newVal);

   Fire_OnProfilePointChanged(id,newVal);

	return S_OK;
}

STDMETHODIMP CProfilePointCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
	return S_OK;
}

STDMETHODIMP CProfilePointCollection::Remove(CogoObjectID id)
{
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return ProfilePointNotFound(id);
   }

   CComVariant& var = (*found).second;
   CComQIPtr<IProfilePoint> pp(var.pdispVal);
   Unadvise(id,pp);

   m_coll.erase(found);

   Fire_OnProfilePointRemoved(id);

	return S_OK;
}

STDMETHODIMP CProfilePointCollection::Add(CogoObjectID id, VARIANT varStation, Float64 elevation,IProfilePoint* *pp)
{
   if ( pp != NULL )
   {
      CHECK_RETOBJ(pp);
   }

   CComPtr<IProfilePoint> point;
   m_Factory->CreateProfilePoint(&point);
   
   HRESULT hr = point->put_Station(varStation);
   if ( FAILED(hr) )
      return hr;

   point->put_Elevation(elevation);

   if ( pp != NULL )
   {
      (*pp) = point;
      (*pp)->AddRef();
   }

   return AddEx(id,point);
}

STDMETHODIMP CProfilePointCollection::AddEx(CogoObjectID id, IProfilePoint* newVal)
{
   CHECK_IN(newVal);
   
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found != m_coll.end() )
   {
      return ProfilePointAlreadyDefined(id);
   }

   CComQIPtr<IUnknown,&IID_IUnknown> pDisp(newVal);
   CComVariant var(pDisp);
   m_coll.insert(std::make_pair(id,var));

   // Hookup to the connection ProfilePoint
   Advise(id,newVal);

   Fire_OnProfilePointAdded(id,newVal);

	return S_OK;
}

STDMETHODIMP CProfilePointCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnProfilePointsCleared();
	return S_OK;
}

STDMETHODIMP CProfilePointCollection::FindID(IProfilePoint* pp,CogoObjectID* id)
{
   CHECK_IN(pp);
   CHECK_RETVAL(id);

   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      std::pair<CogoObjectID,CComVariant> item = *iter;
      CComQIPtr<IProfilePoint> value( item.second.pdispVal );
      ATLASSERT( value != NULL );
      if ( value.IsEqualObject(pp) )
      {
         *id = item.first;
         return S_OK;
      }
   }

   return E_FAIL;
}

STDMETHODIMP CProfilePointCollection::get__EnumIDs(IEnumIDs** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumIDs,&IID_IEnumIDs, CogoObjectID, MapCopyID<std::map<CogoObjectID,CComVariant>>, std::map<CogoObjectID,CComVariant> > Enum;
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

STDMETHODIMP CProfilePointCollection::ID(CollectionIndexType index,CogoObjectID* id)
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

STDMETHODIMP CProfilePointCollection::get_Factory(IProfilePointFactory* *factory)
{
   CHECK_RETOBJ(factory);
   (*factory) = m_Factory;
   (*factory)->AddRef();
   return S_OK;
}

STDMETHODIMP CProfilePointCollection::putref_Factory(IProfilePointFactory* factory)
{
   CHECK_IN(factory);
   m_Factory = factory;
   return S_OK;
}

STDMETHODIMP CProfilePointCollection::get__EnumProfilePoints(IEnumProfilePoints** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumProfilePoints,&IID_IEnumProfilePoints, IProfilePoint*, MapCopyValueToInterface<std::map<CogoObjectID,CComVariant>,IProfilePoint*>, std::map<CogoObjectID,CComVariant> > Enum;
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

STDMETHODIMP CProfilePointCollection::Clone(IProfilePointCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CProfilePointCollection>* pClone;
   CComObject<CProfilePointCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<IEnumProfilePoints> enumPP;
   get__EnumProfilePoints(&enumPP);

   CollectionIndexType count = 0;
   CComPtr<IProfilePoint> pp;
   while ( enumPP->Next(1,&pp,NULL) != S_FALSE )
   {
      CComPtr<IProfilePoint> clonePP;
      pp->Clone(&clonePP);

      CogoObjectID id;
      ID(count++,&id);

      (*clone)->AddEx(id,clonePP);

      pp.Release();
   }

   (*clone)->putref_Factory(m_Factory);

   return S_OK;
}

STDMETHODIMP CProfilePointCollection::OnProfilePointChanged(IProfilePoint* pp)
{
   CogoObjectID id;
   HRESULT hr = FindID(pp,&id);

   // This container only listens to events from ProfilePoint objects in this 
   // container. If the id isn't found an error has been made somewhere
   ATLASSERT( SUCCEEDED(hr) );

   Fire_OnProfilePointChanged(id,pp);

   return S_OK;
}

void CProfilePointCollection::Advise(CogoObjectID id,IProfilePoint* pp)
{
   DWORD dwCookie;
   CComPtr<IProfilePoint> pCP(pp);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_IProfilePointEvents, &dwCookie );
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection ProfilePoint with ProfilePoint object\n");
      return;
   }

   m_Cookies.insert( std::make_pair(id,dwCookie) );

   InternalRelease(); // Break circular reference
}

void CProfilePointCollection::Unadvise(CogoObjectID id,IProfilePoint* pp)
{
   ATLASSERT(pp != 0);

   //
   // Disconnection from connection ProfilePoint
   //

   // Lookup the cookie
   std::map<CogoObjectID,DWORD>::iterator found;
   found = m_Cookies.find( id );
   if ( found == m_Cookies.end() )
   {
      ATLTRACE("Failed to disconnect connection ProfilePoint with ProfilePoint object\n");
      return;
   }

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection ProfilePoint and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( pp );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IProfilePointEvents, &pCP );
   DWORD dwCookie = (*found).second;
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));

   // Remove cookie from map
   m_Cookies.erase( id );
}

void CProfilePointCollection::UnadviseAll()
{
   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CogoObjectID id = (*iter).first;
      CComQIPtr<IProfilePoint> pp( (*iter).second.pdispVal );
      Unadvise(id,pp);
   }
}

HRESULT CProfilePointCollection::ProfilePointNotFound(CogoObjectID id)
{
   return ProfilePointIDError(id,IDS_E_PROFILEPOINTNOTFOUND,COGO_E_PROFILEPOINTNOTFOUND);
}

HRESULT CProfilePointCollection::ProfilePointAlreadyDefined(CogoObjectID id)
{
   return ProfilePointIDError(id,IDS_E_PROFILEPOINTALREADYDEFINED,COGO_E_PROFILEPOINTALREADYDEFINED);
}

HRESULT CProfilePointCollection::ProfilePointIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, id );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return CComCoClass<CProfilePointCollection,&CLSID_ProfilePointCollection>::Error(oleMsg, IID_IProfilePointCollection, hRes);
}

HRESULT CProfilePointCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   pSave->put_Property(CComBSTR("ProfilePointFactory"),CComVariant(m_Factory));
   return S_OK;
}

HRESULT CProfilePointCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->get_Property(CComBSTR("ProfilePointFactory"),&var);
   m_Factory.Release();
   _CopyVariantToInterface<IProfilePointFactory>::copy(&m_Factory,&var);
   return S_OK;
}


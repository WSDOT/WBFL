///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// PointCollection.cpp : Implementation of CPointCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "PointCollection.h"
#include "PointFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointCollection
HRESULT CPointCollection::FinalConstruct()
{
   CComObject<CPointFactory>* pFactory;
   CComObject<CPointFactory>::CreateInstance(&pFactory);
   m_Factory = pFactory;
   return S_OK;
}

void CPointCollection::FinalRelease()
{
   UnadviseAll();
}


STDMETHODIMP CPointCollection::get_Item(CogoObjectID id, IPoint2d **pVal)
{
   CHECK_RETVAL(pVal);
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return PointNotFound(id);
   }

   std::pair<CogoObjectID,CComVariant> p = *found;
   p.second.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CPointCollection::putref_Item(CogoObjectID id, IPoint2d *newVal)
{
   CHECK_IN(newVal);

   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return PointNotFound(id);
   }

   CComVariant& var = (*found).second;

   CComQIPtr<IPoint2d> old_point(var.pdispVal);
   Unadvise(id,old_point);

   var = newVal;
   Advise(id,newVal);

   Fire_OnPointChanged(id,newVal);

	return S_OK;
}

STDMETHODIMP CPointCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
	return S_OK;
}

STDMETHODIMP CPointCollection::Remove(CogoObjectID id)
{
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return PointNotFound(id);
   }

   CComVariant& var = (*found).second;
   CComQIPtr<IPoint2d> point(var.pdispVal);
   Unadvise(id,point);

   m_coll.erase(found);

   Fire_OnPointRemoved(id);

	return S_OK;
}

STDMETHODIMP CPointCollection::Add(CogoObjectID id, Float64 x, Float64 y,IPoint2d* *point)
{
   if ( point != nullptr )
   {
      CHECK_RETOBJ(point);
   }

   CComPtr<IPoint2d> newPoint;
   m_Factory->CreatePoint(&newPoint);

   newPoint->Move(x,y);

   if ( point != nullptr )
   {
      (*point) = newPoint;
      (*point)->AddRef();
   }

   return AddEx(id,newPoint);
}

STDMETHODIMP CPointCollection::AddEx(CogoObjectID id, IPoint2d* newVal)
{
   CHECK_IN(newVal);
   
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found != m_coll.end() )
   {
      return PointAlreadyDefined(id);
   }

   CComQIPtr<IUnknown,&IID_IUnknown> pDisp(newVal);
   CComVariant var(pDisp);
   std::pair<std::map<CogoObjectID,CComVariant>::iterator,bool> result;
   result = m_coll.insert(std::make_pair(id,var));
   if ( result.second == false )
   {
      return E_FAIL;
   }

   // Hookup to the connection point
   Advise(id,newVal);

   Fire_OnPointAdded(id,newVal);

	return S_OK;
}

STDMETHODIMP CPointCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnPointsCleared();
	return S_OK;
}

STDMETHODIMP CPointCollection::FindID(IPoint2d* point,CogoObjectID* id)
{
   CHECK_IN(point);
   CHECK_RETVAL(id);

   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      std::pair<CogoObjectID,CComVariant> item = *iter;
      CComQIPtr<IPoint2d> value( item.second.pdispVal );
      ATLASSERT( value != nullptr );
      if ( value.IsEqualObject(point) )
      {
         *id = item.first;
         return S_OK;
      }
   }

   return E_FAIL;
}

STDMETHODIMP CPointCollection::get__EnumIDs(IEnumIDs** ppenum)
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

STDMETHODIMP CPointCollection::get_Factory(IPoint2dFactory** factory)
{
   CHECK_RETOBJ(factory);
   (*factory) = m_Factory;
   (*factory)->AddRef();
   return S_OK;
}

STDMETHODIMP CPointCollection::putref_Factory(IPoint2dFactory* factory)
{
   CHECK_IN(factory);
   m_Factory = factory;
   return S_OK;
}

STDMETHODIMP CPointCollection::ID(CollectionIndexType index,CogoObjectID* id)
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

STDMETHODIMP CPointCollection::get__EnumPoints(IEnumPoint2d** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumPoint2d,&IID_IEnumPoint2d, IPoint2d*, MapCopyValueToInterface<std::map<CogoObjectID,CComVariant>,IPoint2d*>, std::map<CogoObjectID,CComVariant> > Enum;
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

STDMETHODIMP CPointCollection::Clone(IPointCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CPointCollection>* pClone;
   CComObject<CPointCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->putref_Factory(m_Factory);

   CollectionIndexType count = 0;
   CComPtr<IEnumPoint2d> enumPoints;
   get__EnumPoints(&enumPoints);
   CComPtr<IPoint2d> point;
   while ( enumPoints->Next(1,&point,nullptr) != S_FALSE )
   {
      CComPtr<IPoint2d> clonePoint;
      m_Factory->CreatePoint(&clonePoint);

      clonePoint->MoveEx(point);

      CogoObjectID id;
      ID(count++,&id);

      (*clone)->AddEx(id,clonePoint);

      point.Release();
   };

   return S_OK;
}

//STDMETHODIMP CPointCollection::get_StructuredStorage(IStructuredStorage2* *pStg)
//{
//   CHECK_RETOBJ(pStg);
//   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
//}


////////////////////////////////////////////////
// IStructuredStorage2
//STDMETHODIMP CPointCollection::Save(IStructuredSave2* pSave)
//{
//   CHECK_IN(pSave);
//
//   pSave->BeginUnit(CComBSTR("Points"),1.0);
//
//   pSave->put_Property(CComBSTR("PointFactory"),CComVariant(m_Factory));
//   
//   pSave->put_Property(CComBSTR("Count"),CComVariant((long)m_coll.size()));
//   
//   MyMap::iterator iter;
//   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
//   {
//      pSave->BeginUnit(CComBSTR("Point"),1.0);
//
//      std::pair<const long,CComVariant>& pair = *iter;
//      pSave->put_Property(CComBSTR("ID"),CComVariant(pair.first));
//      pSave->put_Property(CComBSTR("Value"),CComVariant(pair.second));
//
//      pSave->EndUnit();
//   }
//
//   pSave->EndUnit();
//
//   return S_OK;
//}
//
//STDMETHODIMP CPointCollection::Load(IStructuredLoad2* pLoad)
//{
//   CHECK_IN(pLoad);
//
//   CComVariant var;
//   VARIANT_BOOL bEnd;
//
//   pLoad->BeginUnit(CComBSTR("Points"));
//
//   pLoad->get_Property(CComBSTR("PointFactory"),&var);
//   m_Factory.Release();
//   _CopyVariantToInterface<IPoint2dFactory>::copy(&m_Factory,&var);
//
//   long count;
//   pLoad->get_Property(CComBSTR("Count"),&var);
//   count = var;
//
//   for ( long i = 0; i < count; i++ )
//   {
//      long ID;
//      pLoad->BeginUnit(CComBSTR("Point"));
//
//      pLoad->get_Property(CComBSTR("ID"),&var);
//      ID = var;
//
//      pLoad->get_Property(CComBSTR("Value"),&var);
//      CComPtr<IPoint2d> point;
//      _CopyVariantToInterface<IPoint2d>::copy(&point,&var);
//
//      AddEx(ID,point);
//
//      pLoad->EndUnit(&bEnd);
//   }
//
//   pLoad->EndUnit(&bEnd);
//
//   return S_OK;
//}

HRESULT CPointCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   pSave->put_Property(CComBSTR("PointFactory"),CComVariant(m_Factory));
   return S_OK;
}

HRESULT CPointCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->get_Property(CComBSTR("PointFactory"),&var);
   m_Factory.Release();
   _CopyVariantToInterface<IPoint2dFactory>::copy(&m_Factory,&var);
   return S_OK;
}

////////////////////////////////////////////////

STDMETHODIMP CPointCollection::OnPointChanged(IPoint2d* point)
{
   CComQIPtr<IPoint2d> pointEx(point);
   // Better be listening only to IPoint2d objects
   ATLASSERT( pointEx != nullptr );

   CogoObjectID id;
   HRESULT hr = FindID(pointEx,&id);

   // This container only listens to events from point objects in this 
   // container. If the id isn't found an error has been made somewhere
   Fire_OnPointChanged(id,pointEx);

   return S_OK;
}

void CPointCollection::Advise(CogoObjectID id,IPoint2d* point)
{
   ATLASSERT(point != 0);

   DWORD dwCookie;
   CComPtr<IPoint2d> pCP(point);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_IPoint2dEvents, &dwCookie );
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point with Point object\n");
      return;
   }

   m_Cookies.insert( std::make_pair(id,dwCookie) );

   InternalRelease(); // Break circular reference
}

void CPointCollection::Unadvise(CogoObjectID id,IPoint2d* point)
{
   ATLASSERT(point != 0);

   //
   // Disconnection from connection point
   //

   // Lookup the cookie
   std::map<CogoObjectID,DWORD>::iterator found;
   found = m_Cookies.find( id );
   if ( found == m_Cookies.end() )
   {
      ATLTRACE("Failed to disconnect connection point with Point object\n");
      return;
   }

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( point );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IPoint2dEvents, &pCP );
   DWORD dwCookie = (*found).second;
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));

   // Remove cookie from map
   m_Cookies.erase( id );
}

void CPointCollection::UnadviseAll()
{
   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CogoObjectID id = (*iter).first;
      CComQIPtr<IPoint2d> point( (*iter).second.pdispVal );
      Unadvise(id,point);
   }
}

HRESULT CPointCollection::PointNotFound(CogoObjectID id)
{
   return PointIDError(id,IDS_E_POINTNOTFOUND,COGO_E_POINTNOTFOUND);
}

HRESULT CPointCollection::PointAlreadyDefined(CogoObjectID id)
{
   return PointIDError(id,IDS_E_POINTALREADYDEFINED,COGO_E_POINTALREADYDEFINED);
}

HRESULT CPointCollection::PointIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, id );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return Error(oleMsg, IID_IPointCollection, hRes);
}


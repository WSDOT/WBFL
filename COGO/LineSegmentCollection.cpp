///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 2001  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// LineSegmentCollection.cpp : Implementation of CLineSegmentCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "LineSegmentCollection.h"
#include "LineSegmentFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineSegmentCollection
HRESULT CLineSegmentCollection::FinalConstruct()
{
   CComObject<CLineSegmentFactory>* pFactory;
   CComObject<CLineSegmentFactory>::CreateInstance(&pFactory);
   m_Factory = pFactory;
   return S_OK;
}

void CLineSegmentCollection::FinalRelease()
{
   UnadviseAll();
   m_coll.clear();
}

//STDMETHODIMP CLineSegmentCollection::InterfaceSupportsErrorInfo(REFIID riid)
//{
//	static const IID* arr[] = 
//	{
//		&IID_ILineSegmentCollection
//	};
//	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
//	{
//		if (InlineIsEqualGUID(*arr[i],riid))
//			return S_OK;
//	}
//	return S_FALSE;
//}

//STDMETHODIMP CLineSegmentCollection::get__NewEnum(IUnknown** retval)
//{
//   return S_OK;
//}

STDMETHODIMP CLineSegmentCollection::get_Item(CogoElementKey key, ILineSegment2d* *pVal)
{
   CHECK_RETVAL(pVal);
   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found == m_coll.end() )
   {
      return LineSegNotFound(key);
   }

   std::pair<CogoElementKey,CComVariant> p = *found;
   p.second.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CLineSegmentCollection::putref_Item(CogoElementKey key, ILineSegment2d* newVal)
{
   CHECK_IN(newVal);

   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found == m_coll.end() )
   {
      return LineSegNotFound(key);
   }

   CComVariant& var = (*found).second;

   CComQIPtr<ILineSegment2d> old_ls(var.pdispVal);
   Unadvise(key,old_ls);

   var = newVal;
   Advise(key,newVal);

   Fire_OnLineSegmentChanged(key,newVal);

	return S_OK;
}

STDMETHODIMP CLineSegmentCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
   return S_OK;
}

STDMETHODIMP CLineSegmentCollection::Add(CogoElementKey key, IPoint2d* start, IPoint2d* end,ILineSegment2d* *ls)
{
   CHECK_IN(start);
   CHECK_IN(end);

   if ( ls != NULL )
   {
      CHECK_RETOBJ(ls);
   }

   CComPtr<ILineSegment2d> newLS;
   m_Factory->CreateLineSegment(&newLS);

   newLS->putref_StartPoint(start);
   newLS->putref_EndPoint(end);

   if ( ls != NULL )
   {
      (*ls) = newLS;
      (*ls)->AddRef();
   }

   return AddEx(key,newLS);
}

STDMETHODIMP CLineSegmentCollection::AddEx(CogoElementKey key, ILineSegment2d* newVal)
{
   CHECK_IN(newVal);
   
   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found != m_coll.end() )
   {
      return LineSegAlreadyDefined(key);
   }

   CComQIPtr<IUnknown,&IID_IUnknown> pDisp(newVal);
   CComVariant var(pDisp);
   m_coll.insert(std::make_pair(key,var));

   // Hookup to the connection point
   Advise(key,newVal);

   Fire_OnLineSegmentAdded(key,newVal);

	return S_OK;
}

STDMETHODIMP CLineSegmentCollection::Remove(CogoElementKey key)
{
   std::map<CogoElementKey,CComVariant>::iterator found;
   found = m_coll.find(key);
   if ( found == m_coll.end() )
   {
      return LineSegNotFound(key);
   }

   CComVariant& var = (*found).second;
   CComQIPtr<ILineSegment2d> ls(var.pdispVal);
   Unadvise(key,ls);

   m_coll.erase(found);

   Fire_OnLineSegmentRemoved(key);

	return S_OK;
}

STDMETHODIMP CLineSegmentCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnLineSegmentsCleared();
	return S_OK;
}

STDMETHODIMP CLineSegmentCollection::FindKey(ILineSegment2d* ls, CogoElementKey* key)
{
   CHECK_IN(ls);
   CHECK_RETVAL(key);

   std::map<CogoElementKey,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      std::pair<CogoElementKey,CComVariant> item = *iter;
      CComQIPtr<ILineSegment2d> value( item.second.pdispVal );
      ATLASSERT( value != NULL );
      if ( value.IsEqualObject(ls) )
      {
         *key = item.first;
         return S_OK;
      }
   }

   return E_FAIL;
}

STDMETHODIMP CLineSegmentCollection::get__EnumKeys(IEnumKeys** ppenum)
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

STDMETHODIMP CLineSegmentCollection::get__EnumLineSegments(IEnumLineSegments** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumLineSegments,&IID_IEnumLineSegments, ILineSegment2d*, MapCopyValueToInterface<std::map<CogoElementKey,CComVariant>,ILineSegment2d*>, std::map<CogoElementKey,CComVariant> > Enum;
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

STDMETHODIMP CLineSegmentCollection::get_Factory(ILineSegment2dFactory** factory)
{
   CHECK_RETOBJ(factory);
   (*factory) = m_Factory;
   (*factory)->AddRef();
   return S_OK;
}

STDMETHODIMP CLineSegmentCollection::putref_Factory(ILineSegment2dFactory* factory)
{
   CHECK_IN(factory);
   m_Factory = factory;
   return S_OK;
}

STDMETHODIMP CLineSegmentCollection::Key(CollectionIndexType index,CogoElementKey* key)
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

STDMETHODIMP CLineSegmentCollection::Clone(ILineSegmentCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CLineSegmentCollection>* pClone;
   CComObject<CLineSegmentCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->putref_Factory(m_Factory);

   CogoElementKey count = 0;
   CComPtr<IEnumLineSegments> enumLS;
   get__EnumLineSegments(&enumLS);
   CComPtr<ILineSegment2d> ls;
   while ( enumLS->Next(1,&ls,NULL) != S_FALSE )
   {
      CComPtr<ILineSegment2d> cloneLS;
      m_Factory->CreateLineSegment(&cloneLS);

      CComPtr<IPoint2d> start;
      CComPtr<IPoint2d> end;
      ls->get_StartPoint(&start);
      ls->get_EndPoint(&end);

      CComPtr<IPoint2d> cloneStart;
      CComPtr<IPoint2d> cloneEnd;
      cloneLS->get_StartPoint(&cloneStart);
      cloneLS->get_EndPoint(&cloneEnd);

      cloneStart->MoveEx(start);
      cloneEnd->MoveEx(end);

      CogoElementKey key;
      Key(count++,&key);

      (*clone)->AddEx(key,cloneLS);

      ls.Release();
   };

   return S_OK;
}

STDMETHODIMP CLineSegmentCollection::OnLineSegmentChanged(ILineSegment2d* lineSeg)
{
   CComQIPtr<ILineSegment2d> lineSegEx(lineSeg);
   ATLASSERT( lineSegEx != NULL ); // better be listening only to LineSegment2dEx objects

   CogoElementKey key;
   HRESULT hr = FindKey(lineSegEx,&key);

   // This container only listens to events from linesegment objects in this 
   // container. If the key isn't found an error has been made somewhere
   ATLASSERT( SUCCEEDED(hr) );


   Fire_OnLineSegmentChanged(key,lineSegEx);

   return S_OK;
}


void CLineSegmentCollection::Advise(CogoElementKey key,ILineSegment2d* lineSeg)
{
   DWORD dwCookie;
   CComPtr<ILineSegment2d> pCP(lineSeg);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_ILineSegment2dEvents, &dwCookie );
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point with LineSegment object\n");
      return;
   }

   m_Cookies.insert( std::make_pair(key,dwCookie) );

   InternalRelease(); // Break circular reference
}

void CLineSegmentCollection::Unadvise(CogoElementKey key,ILineSegment2d* lineSeg)
{
   ATLASSERT(lineSeg != 0);

   //
   // Disconnection from connection point
   //

   // Lookup the cookie
   std::map<CogoElementKey,DWORD>::iterator found;
   found = m_Cookies.find( key );
   if ( found == m_Cookies.end() )
   {
      ATLTRACE("Failed to disconnect connection point with LineSegment object\n");
      return;
   }

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( lineSeg );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_ILineSegment2dEvents, &pCP );
   DWORD dwCookie = (*found).second;
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));

   // Remove cookie from map
   m_Cookies.erase( key );
}

void CLineSegmentCollection::UnadviseAll()
{
   std::map<CogoElementKey,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CogoElementKey key = (*iter).first;
      CComQIPtr<ILineSegment2d> lineSeg( (*iter).second.pdispVal );
      Unadvise(key,lineSeg);
   }
}

HRESULT CLineSegmentCollection::LineSegNotFound(CogoElementKey key)
{
   return LineSegKeyError(key,IDS_E_LINESEGMENTNOTFOUND,COGO_E_LINESEGMENTNOTFOUND);
}

HRESULT CLineSegmentCollection::LineSegAlreadyDefined(CogoElementKey key)
{
   return LineSegKeyError(key,IDS_E_LINESEGMENTALREADYDEFINED,COGO_E_LINESEGMENTALREADYDEFINED);
}

HRESULT CLineSegmentCollection::LineSegKeyError(CogoElementKey key,UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   TCHAR msg[256];
   int cOut = sprintf_s( msg, 256, str, key );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return CComCoClass<CLineSegmentCollection,&CLSID_LineSegmentCollection>::Error(oleMsg, IID_ILineSegmentCollection, hRes);
}

HRESULT CLineSegmentCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   pSave->put_Property(CComBSTR("LineSegmentFactory"),CComVariant(m_Factory));
   return S_OK;
}

HRESULT CLineSegmentCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->get_Property(CComBSTR("LineSegmentFactory"),&var);
   m_Factory.Release();
   _CopyVariantToInterface<ILineSegment2dFactory>::copy(&m_Factory,&var);
   return S_OK;
}

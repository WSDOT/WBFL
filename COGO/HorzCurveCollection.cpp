///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// HorzCurveCollection.cpp : Implementation of CHorzCurveCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "HorzCurveCollection.h"
#include "HorzCurveFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHorzCurveCollection
HRESULT CHorzCurveCollection::FinalConstruct()
{
   CComObject<CHorzCurveFactory>* pFactory;
   CComObject<CHorzCurveFactory>::CreateInstance(&pFactory);

   m_Factory = pFactory;

   return S_OK;
}

void CHorzCurveCollection::FinalRelease()
{
   UnadviseAll();
   m_coll.clear();
}

STDMETHODIMP CHorzCurveCollection::get_Item(CogoObjectID id, IHorzCurve **pVal)
{
   CHECK_RETVAL(pVal);
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return HorzCurveNotFound(id);
   }

   std::pair<CogoObjectID,CComVariant> p = *found;
   p.second.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CHorzCurveCollection::putref_Item(CogoObjectID id, IHorzCurve *newVal)
{
   CHECK_IN(newVal);

   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return HorzCurveNotFound(id);
   }

   CComVariant& var = (*found).second;

   CComQIPtr<IHorzCurve> old_curve(var.pdispVal);
   Unadvise(id,old_curve);

   var = newVal;
   Advise(id,newVal);

   Fire_OnHorzCurveChanged(id,newVal);

	return S_OK;
}

STDMETHODIMP CHorzCurveCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
	return S_OK;
}

STDMETHODIMP CHorzCurveCollection::Remove(CogoObjectID id)
{
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return HorzCurveNotFound(id);
   }

   CComVariant& var = (*found).second;
   CComQIPtr<IHorzCurve> hc(var.pdispVal);
   Unadvise(id,hc);

   m_coll.erase(found);

   Fire_OnHorzCurveRemoved(id);

	return S_OK;
}

STDMETHODIMP CHorzCurveCollection::Add(CogoObjectID id, IPoint2d* pbt, IPoint2d* pi, IPoint2d* pft, Float64 radius, Float64 Ls1, Float64 Ls2,IHorzCurve** hc)
{
   CHECK_IN(pbt);
   CHECK_IN(pi);
   CHECK_IN(pft);
   if ( radius <= 0 )
      return E_INVALIDARG;

   if ( Ls1 < 0 )
      return E_INVALIDARG;

   if ( Ls2 < 0 )
      return E_INVALIDARG;

   if ( hc != NULL )
   {
      CHECK_RETOBJ(hc);
   }

   CComPtr<IHorzCurve> newHC;
   m_Factory->CreateHorzCurve(&newHC);

   newHC->putref_PBT(pbt);
   newHC->putref_PI(pi);
   newHC->putref_PFT(pft);
   newHC->put_Radius(radius);
   newHC->put_SpiralLength(spEntry,Ls1);
   newHC->put_SpiralLength(spExit,Ls2);

   if ( hc != NULL )
   {
      (*hc) = newHC;
      (*hc)->AddRef();
   }

   return AddEx(id,newHC);
}

   
STDMETHODIMP CHorzCurveCollection::AddEx(CogoObjectID id, IHorzCurve* newVal)
{
   CHECK_IN(newVal);

   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found != m_coll.end() )
   {
      return HorzCurveAlreadyDefined(id);
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

   Fire_OnHorzCurveAdded(id,newVal);

	return S_OK;
}

STDMETHODIMP CHorzCurveCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnHorzCurvesCleared();
	return S_OK;
}

STDMETHODIMP CHorzCurveCollection::FindID(IHorzCurve* hc,CogoObjectID* id)
{
   CHECK_IN(hc);
   CHECK_RETVAL(id);

   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      std::pair<CogoObjectID,CComVariant> item = *iter;
      CComQIPtr<IHorzCurve> value( item.second.pdispVal );
      ATLASSERT( value != NULL );
      if ( value.IsEqualObject(hc) )
      {
         *id = item.first;
         return S_OK;
      }
   }

   return E_FAIL;
}

STDMETHODIMP CHorzCurveCollection::get__EnumIDs(IEnumIDs** ppenum)
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

STDMETHODIMP CHorzCurveCollection::get__EnumHorzCurves(IEnumHorzCurves** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumHorzCurves,&IID_IEnumHorzCurves, IHorzCurve*, MapCopyValueToInterface<std::map<CogoObjectID,CComVariant>,IHorzCurve*>, std::map<CogoObjectID,CComVariant> > Enum;
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

STDMETHODIMP CHorzCurveCollection::Clone(IHorzCurveCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CHorzCurveCollection>* pClone;
   CComObject<CHorzCurveCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<IEnumHorzCurves> enumHC;
   get__EnumHorzCurves(&enumHC);

   CollectionIndexType count = 0;
   CComPtr<IHorzCurve> hc;
   while ( enumHC->Next(1,&hc,NULL) != S_FALSE )
   {
      CComPtr<IHorzCurve> cloneHC;
      hc->Clone(&cloneHC);

      CogoObjectID id;
      ID(count++,&id);

      (*clone)->AddEx(id,cloneHC);
   }

   (*clone)->putref_Factory(m_Factory);

   return S_OK;
}

STDMETHODIMP CHorzCurveCollection::get_Factory(IHorzCurveFactory** factory)
{
   CHECK_RETOBJ(factory);
   (*factory) = m_Factory;
   (*factory)->AddRef();
   return S_OK;
}

STDMETHODIMP CHorzCurveCollection::putref_Factory(IHorzCurveFactory* factory)
{
   CHECK_IN(factory);
   m_Factory = factory;
   return S_OK;
}

STDMETHODIMP CHorzCurveCollection::ID(CollectionIndexType index,CogoObjectID* id)
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

////////////////////////////////////////////////

STDMETHODIMP CHorzCurveCollection::OnHorzCurveChanged(IHorzCurve* hc)
{
   CogoObjectID id;
   HRESULT hr = FindID(hc,&id);

   // This container only listens to events from point objects in this 
   // container. If the id isn't found an error has been made somewhere
   ATLASSERT( SUCCEEDED(hr) );

   Fire_OnHorzCurveChanged(id,hc);

   return S_OK;
}

void CHorzCurveCollection::Advise(CogoObjectID id,IHorzCurve* hc)
{
   DWORD dwCookie;
   CComPtr<IHorzCurve> pCP(hc);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_IHorzCurveEvents, &dwCookie );
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point with HorzCurve object\n");
      return;
   }

   m_Cookies.insert( std::make_pair(id,dwCookie) );

   InternalRelease(); // Break circular reference
}

void CHorzCurveCollection::Unadvise(CogoObjectID id,IHorzCurve* hc)
{
   ATLASSERT(hc != 0);

   //
   // Disconnection from connection point
   //

   // Lookup the cookie
   std::map<CogoObjectID,DWORD>::iterator found;
   found = m_Cookies.find( id );
   if ( found == m_Cookies.end() )
   {
      ATLTRACE("Failed to disconnect connection point with HorzCurve object\n");
      return;
   }

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( hc );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IHorzCurveEvents, &pCP );
   DWORD dwCookie = (*found).second;
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));

   // Remove cookie from map
   m_Cookies.erase( id );
}

void CHorzCurveCollection::UnadviseAll()
{
   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CogoObjectID id = (*iter).first;
      CComQIPtr<IHorzCurve> hc( (*iter).second.pdispVal );
      Unadvise(id,hc);
   }
}

HRESULT CHorzCurveCollection::HorzCurveNotFound(CogoObjectID id)
{
   return HorzCurveIDError(id,IDS_E_HORZCURVENOTFOUND,COGO_E_HORZCURVENOTFOUND);
}

HRESULT CHorzCurveCollection::HorzCurveAlreadyDefined(CogoObjectID id)
{
   return HorzCurveIDError(id,IDS_E_HORZCURVEALREADYDEFINED,COGO_E_HORZCURVEALREADYDEFINED);
}

HRESULT CHorzCurveCollection::HorzCurveIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, id );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return Error(oleMsg, IID_IHorzCurveCollection, hRes);
}

HRESULT CHorzCurveCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   pSave->put_Property(CComBSTR("HorzCurveFactory"),CComVariant(m_Factory));
   return S_OK;
}

HRESULT CHorzCurveCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->get_Property(CComBSTR("HorzCurveFactory"),&var);
   m_Factory.Release();
   _CopyVariantToInterface<IHorzCurveFactory>::copy(&m_Factory,&var);
   return S_OK;
}

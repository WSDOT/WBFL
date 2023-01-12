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

// CompoundCurveCollection.cpp : Implementation of CCompoundCurveCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CompoundCurveCollection.h"
#include "CompoundCurveFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompoundCurveCollection
HRESULT CCompoundCurveCollection::FinalConstruct()
{
   CComObject<CCompoundCurveFactory>* pFactory;
   CComObject<CCompoundCurveFactory>::CreateInstance(&pFactory);

   m_Factory = pFactory;

   return S_OK;
}

void CCompoundCurveCollection::FinalRelease()
{
   UnadviseAll();
   m_coll.clear();
}

STDMETHODIMP CCompoundCurveCollection::get_Item(CogoObjectID id, ICompoundCurve **pVal)
{
   CHECK_RETVAL(pVal);
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return CompoundCurveNotFound(id);
   }

   std::pair<CogoObjectID,CComVariant> p = *found;
   p.second.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CCompoundCurveCollection::putref_Item(CogoObjectID id, ICompoundCurve *newVal)
{
   CHECK_IN(newVal);

   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return CompoundCurveNotFound(id);
   }

   CComVariant& var = (*found).second;

   CComQIPtr<ICompoundCurve> old_curve(var.pdispVal);
   Unadvise(id,old_curve);

   var = newVal;
   Advise(id,newVal);

   Fire_OnCompoundCurveChanged(id,newVal);

	return S_OK;
}

STDMETHODIMP CCompoundCurveCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
	return S_OK;
}

STDMETHODIMP CCompoundCurveCollection::Remove(CogoObjectID id)
{
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return CompoundCurveNotFound(id);
   }

   CComVariant& var = (*found).second;
   CComQIPtr<ICompoundCurve> hc(var.pdispVal);
   Unadvise(id,hc);

   m_coll.erase(found);

   Fire_OnCompoundCurveRemoved(id);

	return S_OK;
}

STDMETHODIMP CCompoundCurveCollection::Add(CogoObjectID id, IPoint2d* pbt, IPoint2d* pi, IPoint2d* pft, Float64 radius, Float64 Ls1, Float64 Ls2,ICompoundCurve** hc)
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

   if ( hc != nullptr )
   {
      CHECK_RETOBJ(hc);
   }

   CComPtr<ICompoundCurve> newHC;
   m_Factory->CreateCompoundCurve(&newHC);

   newHC->putref_PBT(pbt);
   newHC->putref_PI(pi);
   newHC->putref_PFT(pft);
   newHC->put_Radius(radius);
   newHC->put_SpiralLength(spEntry,Ls1);
   newHC->put_SpiralLength(spExit,Ls2);

   if ( hc != nullptr )
   {
      (*hc) = newHC;
      (*hc)->AddRef();
   }

   return AddEx(id,newHC);
}

   
STDMETHODIMP CCompoundCurveCollection::AddEx(CogoObjectID id, ICompoundCurve* newVal)
{
   CHECK_IN(newVal);

   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found != m_coll.end() )
   {
      return CompoundCurveAlreadyDefined(id);
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

   Fire_OnCompoundCurveAdded(id,newVal);

	return S_OK;
}

STDMETHODIMP CCompoundCurveCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnCompoundCurvesCleared();
	return S_OK;
}

STDMETHODIMP CCompoundCurveCollection::FindID(ICompoundCurve* hc,CogoObjectID* id)
{
   CHECK_IN(hc);
   CHECK_RETVAL(id);

   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      std::pair<CogoObjectID,CComVariant> item = *iter;
      CComQIPtr<ICompoundCurve> value( item.second.pdispVal );
      ATLASSERT( value != nullptr );
      if ( value.IsEqualObject(hc) )
      {
         *id = item.first;
         return S_OK;
      }
   }

   return E_FAIL;
}

STDMETHODIMP CCompoundCurveCollection::get__EnumIDs(IEnumIDs** ppenum)
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

STDMETHODIMP CCompoundCurveCollection::get__EnumCompoundCurves(IEnumCompoundCurves** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumCompoundCurves,&IID_IEnumCompoundCurves, ICompoundCurve*, MapCopyValueToInterface<std::map<CogoObjectID,CComVariant>,ICompoundCurve*>, std::map<CogoObjectID,CComVariant> > Enum;
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

STDMETHODIMP CCompoundCurveCollection::Clone(ICompoundCurveCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CCompoundCurveCollection>* pClone;
   CComObject<CCompoundCurveCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<IEnumCompoundCurves> enumHC;
   get__EnumCompoundCurves(&enumHC);

   CollectionIndexType count = 0;
   CComPtr<ICompoundCurve> hc;
   while ( enumHC->Next(1,&hc,nullptr) != S_FALSE )
   {
      CComPtr<ICompoundCurve> cloneHC;
      hc->Clone(&cloneHC);

      CogoObjectID id;
      ID(count++,&id);

      (*clone)->AddEx(id,cloneHC);
   }

   (*clone)->putref_Factory(m_Factory);

   return S_OK;
}

STDMETHODIMP CCompoundCurveCollection::get_Factory(ICompoundCurveFactory** factory)
{
   CHECK_RETOBJ(factory);
   (*factory) = m_Factory;
   (*factory)->AddRef();
   return S_OK;
}

STDMETHODIMP CCompoundCurveCollection::putref_Factory(ICompoundCurveFactory* factory)
{
   CHECK_IN(factory);
   m_Factory = factory;
   return S_OK;
}

STDMETHODIMP CCompoundCurveCollection::ID(CollectionIndexType index,CogoObjectID* id)
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

STDMETHODIMP CCompoundCurveCollection::OnCompoundCurveChanged(ICompoundCurve* hc)
{
   CogoObjectID id;
   HRESULT hr = FindID(hc,&id);

   // This container only listens to events from point objects in this 
   // container. If the id isn't found an error has been made somewhere
   ATLASSERT( SUCCEEDED(hr) );

   Fire_OnCompoundCurveChanged(id,hc);

   return S_OK;
}

void CCompoundCurveCollection::Advise(CogoObjectID id,ICompoundCurve* hc)
{
   DWORD dwCookie;
   CComPtr<ICompoundCurve> pCP(hc);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_ICompoundCurveEvents, &dwCookie );
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point with CompoundCurve object\n");
      return;
   }

   m_Cookies.insert( std::make_pair(id,dwCookie) );

   InternalRelease(); // Break circular reference
}

void CCompoundCurveCollection::Unadvise(CogoObjectID id,ICompoundCurve* hc)
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
      ATLTRACE("Failed to disconnect connection point with CompoundCurve object\n");
      return;
   }

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( hc );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_ICompoundCurveEvents, &pCP );
   DWORD dwCookie = (*found).second;
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));

   // Remove cookie from map
   m_Cookies.erase( id );
}

void CCompoundCurveCollection::UnadviseAll()
{
   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CogoObjectID id = (*iter).first;
      CComQIPtr<ICompoundCurve> hc( (*iter).second.pdispVal );
      Unadvise(id,hc);
   }
}

HRESULT CCompoundCurveCollection::CompoundCurveNotFound(CogoObjectID id)
{
   return CompoundCurveIDError(id,IDS_E_COMPOUNDCURVENOTFOUND,COGO_E_COMPOUNDCURVENOTFOUND);
}

HRESULT CCompoundCurveCollection::CompoundCurveAlreadyDefined(CogoObjectID id)
{
   return CompoundCurveIDError(id,IDS_E_COMPOUNDCURVEALREADYDEFINED,COGO_E_COMPOUNDCURVEALREADYDEFINED);
}

HRESULT CCompoundCurveCollection::CompoundCurveIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, id );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return Error(oleMsg, IID_ICompoundCurveCollection, hRes);
}

HRESULT CCompoundCurveCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   pSave->put_Property(CComBSTR("CompoundCurveFactory"),CComVariant(m_Factory));
   return S_OK;
}

HRESULT CCompoundCurveCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->get_Property(CComBSTR("CompoundCurveFactory"),&var);
   m_Factory.Release();
   _CopyVariantToInterface<ICompoundCurveFactory>::copy(&m_Factory,&var);
   return S_OK;
}

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

// SuperelevationCollection.cpp : Implementation of CSuperelevationCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "SuperelevationCollection.h"
#include "Superelevation.h"
#include "CogoHelpers.h"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class SortSuperelevations
{
public:
   SortSuperelevations(IProfile* pProfile) { m_pProfile = pProfile; }
   bool operator()(SuperelevationType& pX,SuperelevationType& pY)
   {
      CComVariant& varX = pX.second;
      CComVariant& varY = pY.second;
      CComPtr<IStation> staX, staY;
      
      CComQIPtr<ISuperelevation> csX(varX.pdispVal);
      CComQIPtr<ISuperelevation> csY(varY.pdispVal);

      csX->get_BeginTransition(&staX);
      csY->get_BeginTransition(&staY);
      return 0 < cogoUtil::Compare(m_pProfile,staX,staY);
   }
private:
   IProfile* m_pProfile; // weak reference
};

/////////////////////////////////////////////////////////////////////////////
// CSuperelevationCollection
HRESULT CSuperelevationCollection::FinalConstruct()
{
   m_pProfile = NULL;
   return S_OK;
}

void CSuperelevationCollection::FinalRelease()
{
   UnadviseAll();
}

STDMETHODIMP CSuperelevationCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISuperelevationCollection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSuperelevationCollection::get_Profile(IProfile* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pProfile )
   {
      (*pVal) = m_pProfile;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::putref_Profile(IProfile* pProfile)
{
   m_pProfile = pProfile;

   CComPtr<IEnumSuperelevations> enumSuperelevations;
   get__EnumSuperelevations(&enumSuperelevations);

   CComPtr<ISuperelevation> widening;
   while ( enumSuperelevations->Next(1,&widening,NULL) != S_FALSE )
   {
      widening->putref_Profile(m_pProfile);
      widening.Release();
   };

   return S_OK;
}

//STDMETHODIMP CSuperelevationCollection::get__NewEnum(IUnknown** retval)
//{
//}

STDMETHODIMP CSuperelevationCollection::get_Item(CollectionIndexType idx, ISuperelevation* *pVal)
{
   CHECK_RETOBJ(pVal);

   if ( !IsValidIndex(idx,m_coll) )
      return E_INVALIDARG;

   SuperelevationType& p = m_coll[idx];
   CComVariant& varItem = p.second;
   varItem.pdispVal->QueryInterface(pVal);
   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::putref_Item(CollectionIndexType idx,ISuperelevation* pVal)
{
   CHECK_IN(pVal);

   HRESULT hr = S_OK;

   if ( !IsValidIndex(idx,m_coll) )
      return E_INVALIDARG;

   //hr = ValidateStation(pVal);
   //if ( FAILED(hr) )
   //   return hr;

   // Get the item
   SuperelevationType& cst = m_coll[idx];
   CComVariant& var = cst.second; // Variant holding IDispatch to Superelevation
   pVal->putref_Profile(m_pProfile);

   UnadviseElement(idx); // Unadvise from the current element

   var = pVal; // Associate new Superelevation with this variant

   // Advise
   DWORD dwCookie;
   AdviseElement(pVal,&dwCookie);

   // Update the cookie
   cst.first = dwCookie;

   Fire_OnSuperelevationChanged(pVal);

   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::GetSuperelevation(VARIANT varStation,ISuperelevation** superelevation)
{
   // searches for the Superelevation that contains the specified station
   CHECK_RETOBJ(superelevation);
   *superelevation = NULL;

   CComPtr<IStation> station;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&station);
   if ( FAILED(hr) )
      return hr;

   Superelevations::iterator iter(m_coll.begin());
   Superelevations::iterator end(m_coll.end());
   for ( ; iter != end; iter++ )
   {
      CComQIPtr<ISuperelevation> thisSuperelevation(iter->second.pdispVal);

      CComPtr<IStation> startStation,endStation;
      thisSuperelevation->get_BeginTransition(&startStation);
      thisSuperelevation->get_EndTransition(&endStation);

      if ( 0 <= cogoUtil::Compare(m_pProfile,startStation,station) &&
           0 <= cogoUtil::Compare(m_pProfile,station,endStation) )
      {
         return thisSuperelevation.CopyTo(superelevation);
      }
   }

   return S_FALSE;
}

STDMETHODIMP CSuperelevationCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::AddEx(ISuperelevation* widening)
{
   CHECK_IN(widening);

   HRESULT hr = S_OK;
   //hr = ValidateStation(widening);
   //if ( FAILED(hr) )
   //   return hr;

   widening->putref_Profile(m_pProfile);

   DWORD dwCookie;
   AdviseElement(widening,&dwCookie);
   m_coll.push_back( std::make_pair(dwCookie,CComVariant(widening)));

   std::sort(m_coll.begin(),m_coll.end(),SortSuperelevations(m_pProfile));

   Fire_OnSuperelevationAdded(widening);
   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::Add(VARIANT varBeginStation,VARIANT varBeginFullStation,VARIANT varEndFullStation,VARIANT varEndStation,Float64 rate,IndexType pivotPoint,SuperTransitionType beginType,Float64 beginL1,Float64 beginL2,SuperTransitionType endType,Float64 endL1,Float64 endL2,ISuperelevation* *pSuperelevation)
{
   if ( pSuperelevation != NULL )
   {
      CHECK_RETOBJ(pSuperelevation);
   }

   CComObject<CSuperelevation>* pNewSuperelevation;
   CComObject<CSuperelevation>::CreateInstance(&pNewSuperelevation);
   CComPtr<ISuperelevation> newSuperelevation;
   newSuperelevation = pNewSuperelevation;

   HRESULT hr = newSuperelevation->Init(m_pProfile,varBeginStation,varBeginFullStation,varEndFullStation,varEndStation,rate,pivotPoint,beginType,beginL1,beginL2,endType,endL1,endL2);
   if ( FAILED(hr) )
      return hr;

   if ( pSuperelevation != NULL )
   {
      (*pSuperelevation) = newSuperelevation;
      (*pSuperelevation)->AddRef();
   }

   return AddEx(newSuperelevation);
}

STDMETHODIMP CSuperelevationCollection::Remove(CollectionIndexType idx)
{
   if ( idx < 0 || m_coll.size() <= idx )
      return E_INVALIDARG;

   UnadviseElement(idx);
   m_coll.erase(m_coll.begin() + idx );
   Fire_OnSuperelevationRemoved();
   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnSuperelevationsCleared();
   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::Clone(ISuperelevationCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSuperelevationCollection>* pClone;
   CComObject<CSuperelevationCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->putref_Profile(m_pProfile);

   CComPtr<IEnumSuperelevations> enumSuperelevations;
   get__EnumSuperelevations(&enumSuperelevations);

   CComPtr<ISuperelevation> widening;
   while ( enumSuperelevations->Next(1,&widening,NULL) != S_FALSE )
   {
      CComPtr<ISuperelevation> wideningClone;
      widening->Clone(&wideningClone);

      (*clone)->AddEx(wideningClone);

      widening.Release();
   };


   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

/////////////////////////////////////////////////////////////////////////////
// ISuperelevationEvents
STDMETHODIMP CSuperelevationCollection::OnSuperelevationChanged(ISuperelevation * pSuperelevation)
{
   Fire_OnSuperelevationChanged(pSuperelevation);
   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::get__EnumSuperelevations(IEnumSuperelevations** retval)
{
   CHECK_RETOBJ(retval);

   typedef CComEnumOnSTL<IEnumSuperelevations,
                         &IID_IEnumSuperelevations, 
                         ISuperelevation*,
                         CopyFromPair2Interface<SuperelevationType,ISuperelevation*>, 
                         std::vector<SuperelevationType>> Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( NULL, m_coll );
   if ( FAILED(hr) )
      return hr;

   pEnum->QueryInterface( retval );

   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CSuperelevationCollection::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Superelevations"),1.0);
   CollectionIndexType count = m_coll.size();
   pSave->put_Property(CComBSTR("Count"),CComVariant(count));
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      pSave->put_Property(CComBSTR("Superelevation"),m_coll[i].second);
   }

   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Superelevations"));

   pLoad->get_Property(CComBSTR("Count"),&var);
   long count = var.lVal;

   for ( long i = 0; i < count; i++ )
   {
      pLoad->get_Property(CComBSTR("Superelevation"),&var);
      CComPtr<ISuperelevation> widening;
      _CopyVariantToInterface<ISuperelevation>::copy(&widening,&var);
      AddEx(widening);
   }

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

//////////////////////////////////////////
// Helper methods

void CSuperelevationCollection::AdviseElement(ISuperelevation* widening,DWORD* pdwCookie)
{
   CComPtr<ISuperelevation> pCP(widening);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_ISuperelevationEvents, pdwCookie );
   if ( FAILED(hr) )
   {
      *pdwCookie = 0;
      ATLTRACE("Failed to establish connection point with Superelevation object\n");
      return;
   }

   InternalRelease(); // Break circular reference
}

void CSuperelevationCollection::UnadviseElement(CollectionIndexType idx)
{
   //
   // Disconnection from connection Superelevation
   //
   SuperelevationType& p = m_coll[idx];
   if ( p.first == 0 )
      return;

   DWORD dwCookie = p.first;
   CComVariant& var = p.second;

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( var.pdispVal );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_ISuperelevationEvents, &pCP );
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));

   p.first = 0;
}

void CSuperelevationCollection::UnadviseAll()
{
   for ( CollectionIndexType i = 0; i < m_coll.size(); i++ )
   {
      UnadviseElement(i);
   }
}

HRESULT CSuperelevationCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   return S_OK;
}

HRESULT CSuperelevationCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   return S_OK;
}
//
//HRESULT CSuperelevationCollection::ValidateStation(ISuperelevation* csect)
//{
//   CComPtr<IStation> station;
//   csect->get_Station(&station);
//   CComPtr<IStation> sta;
//   return ValidateStation(CComVariant(station),false,&sta);
//}
//
//HRESULT CSuperelevationCollection::ValidateStation(VARIANT varStation,bool bClone,IStation** station)
//{
//   HRESULT hr = cogoUtil::StationFromVariant(varStation,bClone,station);
//   if ( FAILED(hr) )
//      return hr;
//
//   if ( m_pProfile == NULL )
//   {
//      ZoneIndexType staEqnZoneIdx;
//      (*station)->get_StationZoneIndex(&staEqnZoneIdx);
//      if ( staEqnZoneIdx != INVALID_INDEX )
//         return E_INVALIDARG; // station must be normalized
//   }
//
//   return S_OK;
//}
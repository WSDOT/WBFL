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

// SuperelevationCollection.cpp : Implementation of CSuperelevationCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "SuperelevationCollection.h"
#include "Superelevation.h"
#include <WBFLCogo\CogoHelpers.h>

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
   bool operator()(CComVariant& pX,CComVariant& pY)
   {
      CComVariant& varX = pX;
      CComVariant& varY = pY;
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
   m_pSurface = nullptr;
   return S_OK;
}

void CSuperelevationCollection::FinalRelease()
{
}

STDMETHODIMP CSuperelevationCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISuperelevationCollection,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSuperelevationCollection::get_Surface(ISurface* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pSurface )
   {
      (*pVal) = m_pSurface;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::putref_Surface(ISurface* pSurface)
{
   CHECK_IN(pSurface);
   m_pSurface = pSurface;

   CComPtr<IEnumSuperelevations> enumSuperelevations;
   get__EnumSuperelevations(&enumSuperelevations);

   CComPtr<ISuperelevation> superelevation;
   while ( enumSuperelevations->Next(1,&superelevation,nullptr) != S_FALSE )
   {
      superelevation->putref_Surface(m_pSurface);
      superelevation.Release();
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

   CComVariant& p = m_coll[idx];
   CComVariant& varItem = p;
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
   CComVariant& cst = m_coll[idx];
   CComVariant& var = cst; // Variant holding IDispatch to Superelevation
   pVal->putref_Surface(m_pSurface);

   var = pVal; // Associate new Superelevation with this variant

   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::GetSuperelevation(VARIANT varStation,ISuperelevation** superelevation)
{
   // searches for the Superelevation that contains the specified station
   CHECK_RETOBJ(superelevation);
   *superelevation = nullptr;

   CComPtr<IStation> station;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&station);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }

   auto iter(m_coll.begin());
   auto end(m_coll.end());
   for ( ; iter != end; iter++ )
   {
      CComQIPtr<ISuperelevation> thisSuperelevation(iter->pdispVal);

      CComPtr<IStation> startStation,endStation;
      thisSuperelevation->get_BeginTransition(&startStation);
      thisSuperelevation->get_EndTransition(&endStation);

      if ( 0 <= cogoUtil::Compare(profile,startStation,station) &&
           0 <= cogoUtil::Compare(profile,station,endStation) )
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

STDMETHODIMP CSuperelevationCollection::AddEx(ISuperelevation* superelevation)
{
   CHECK_IN(superelevation);

   HRESULT hr = S_OK;
   superelevation->putref_Surface(m_pSurface);

   m_coll.emplace_back(CComVariant(superelevation));

   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }
   std::sort(std::begin(m_coll),std::end(m_coll),SortSuperelevations(profile));

   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::Add(VARIANT varBeginStation,VARIANT varBeginFullStation,VARIANT varEndFullStation,VARIANT varEndStation,Float64 rate,IndexType pivotPoint,SuperTransitionType beginType,Float64 beginL1,Float64 beginL2,SuperTransitionType endType,Float64 endL1,Float64 endL2,ISuperelevation* *pSuperelevation)
{
   if ( pSuperelevation != nullptr )
   {
      CHECK_RETOBJ(pSuperelevation);
   }

   CComObject<CSuperelevation>* pNewSuperelevation;
   CComObject<CSuperelevation>::CreateInstance(&pNewSuperelevation);
   CComPtr<ISuperelevation> newSuperelevation;
   newSuperelevation = pNewSuperelevation;

   HRESULT hr = newSuperelevation->Init(m_pSurface,varBeginStation,varBeginFullStation,varEndFullStation,varEndStation,rate,pivotPoint,beginType,beginL1,beginL2,endType,endL1,endL2);
   if ( FAILED(hr) )
      return hr;

   if ( pSuperelevation != nullptr )
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

   m_coll.erase(m_coll.begin() + idx );
   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::Clear()
{
   m_coll.clear();
   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::Clone(ISuperelevationCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSuperelevationCollection>* pClone;
   CComObject<CSuperelevationCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->putref_Surface(m_pSurface);

   CComPtr<IEnumSuperelevations> enumSuperelevations;
   get__EnumSuperelevations(&enumSuperelevations);

   CComPtr<ISuperelevation> superelevation;
   while ( enumSuperelevations->Next(1,&superelevation,nullptr) != S_FALSE )
   {
      CComPtr<ISuperelevation> superelevationClone;
      superelevation->Clone(&superelevationClone);

      (*clone)->AddEx(superelevationClone);

      superelevation.Release();
   };


   return S_OK;
}

STDMETHODIMP CSuperelevationCollection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

STDMETHODIMP CSuperelevationCollection::get__EnumSuperelevations(IEnumSuperelevations** retval)
{
   CHECK_RETOBJ(retval);

   typedef CComEnumOnSTL<IEnumSuperelevations,
                         &IID_IEnumSuperelevations, 
                         ISuperelevation*,
                         _CopyVariantToInterface<ISuperelevation>, 
                         std::vector<CComVariant>> Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( nullptr, m_coll );
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
      pSave->put_Property(CComBSTR("Superelevation"),m_coll[i]);
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
      CComPtr<ISuperelevation> superelevation;
      _CopyVariantToInterface<ISuperelevation>::copy(&superelevation,&var);
      AddEx(superelevation);
   }

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
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
//   if ( m_pProfile == nullptr )
//   {
//      ZoneIndexType staEqnZoneIdx;
//      (*station)->get_StationZoneIndex(&staEqnZoneIdx);
//      if ( staEqnZoneIdx != INVALID_INDEX )
//         return E_INVALIDARG; // station must be normalized
//   }
//
//   return S_OK;
//}
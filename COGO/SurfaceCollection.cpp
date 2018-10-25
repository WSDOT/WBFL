///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// SurfaceCollection.cpp : Implementation of CSurfaceCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "SurfaceCollection.h"
#include "Surface.h"
#include <WBFLCogo\CogoHelpers.h>

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class SortSurfaces
{
public:
   SortSurfaces(IProfile* pProfile) { m_pProfile = pProfile; }
   bool operator()(SurfaceType& pX,SurfaceType& pY)
   {
      CComVariant& varX = pX.second;
      CComVariant& varY = pY.second;
      CComPtr<IStation> staX, staY;
      
      CComQIPtr<ISurface> csX(varX.pdispVal);
      CComQIPtr<ISurface> csY(varY.pdispVal);

      CComPtr<ISurfaceTemplateCollection> templatesX, templatesY;
      csX->get_SurfaceTemplates(&templatesX);
      csY->get_SurfaceTemplates(&templatesY);

      CComPtr<ISurfaceTemplate> templateX, templateY;
      templatesX->get_Item(0,&templateX);
      templatesY->get_Item(0,&templateY);

      templateX->get_Station(&staX);
      templateY->get_Station(&staY);

      return 0 < cogoUtil::Compare(m_pProfile,staX,staY);
   }
private:
   IProfile* m_pProfile; // weak reference
};

/////////////////////////////////////////////////////////////////////////////
// CSurfaceCollection
HRESULT CSurfaceCollection::FinalConstruct()
{
   m_pProfile = NULL;
   return S_OK;
}

void CSurfaceCollection::FinalRelease()
{
   UnadviseAll();
}

STDMETHODIMP CSurfaceCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISurfaceCollection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSurfaceCollection::get_Profile(IProfile* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pProfile )
   {
      (*pVal) = m_pProfile;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CSurfaceCollection::putref_Profile(IProfile* pProfile)
{
   m_pProfile = pProfile;

   CComPtr<IEnumSurfaces> enumSurfaces;
   get__EnumSurfaces(&enumSurfaces);

   CComPtr<ISurface> surface;
   while ( enumSurfaces->Next(1,&surface,NULL) != S_FALSE )
   {
      surface->putref_Profile(m_pProfile);
      surface.Release();
   };

   return S_OK;
}

//STDMETHODIMP CSurfaceCollection::get__NewEnum(IUnknown** retval)
//{
//}

STDMETHODIMP CSurfaceCollection::get_Item(CollectionIndexType idx, ISurface* *pVal)
{
   CHECK_RETOBJ(pVal);

   if ( !IsValidIndex(idx,m_coll) )
      return E_INVALIDARG;

   SurfaceType& p = m_coll[idx];
   CComVariant& varItem = p.second;
   varItem.pdispVal->QueryInterface(pVal);
   return S_OK;
}

STDMETHODIMP CSurfaceCollection::putref_Item(CollectionIndexType idx,ISurface* pVal)
{
   CHECK_IN(pVal);

   HRESULT hr = S_OK;

   if ( !IsValidIndex(idx,m_coll) )
      return E_INVALIDARG;

   // Get the item
   SurfaceType& cst = m_coll[idx];
   CComVariant& var = cst.second; // Variant holding IDispatch to Surface
   pVal->putref_Profile(m_pProfile);

   UnadviseElement(idx); // Unadvise from the current element

   var = pVal; // Associate new Surface with this variant

   // Advise
   DWORD dwCookie;
   AdviseElement(pVal,&dwCookie);

   // Update the cookie
   cst.first = dwCookie;

   Fire_OnSurfaceChanged(pVal);

   return S_OK;
}

STDMETHODIMP CSurfaceCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
   return S_OK;
}

STDMETHODIMP CSurfaceCollection::Add(ISurface* surface)
{
   CHECK_IN(surface);

   HRESULT hr = S_OK;

   surface->putref_Profile(m_pProfile);

   DWORD dwCookie;
   AdviseElement(surface,&dwCookie);
   m_coll.push_back( std::make_pair(dwCookie,CComVariant(surface)));

   std::sort(m_coll.begin(),m_coll.end(),SortSurfaces(m_pProfile));

   Fire_OnSurfaceAdded(surface);
   return S_OK;
}

STDMETHODIMP CSurfaceCollection::Remove(CollectionIndexType idx)
{
   if ( idx < 0 || m_coll.size() <= idx )
      return E_INVALIDARG;

   UnadviseElement(idx);
   m_coll.erase(m_coll.begin() + idx );
   Fire_OnSurfaceRemoved();
   return S_OK;
}

STDMETHODIMP CSurfaceCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnSurfacesCleared();
   return S_OK;
}

STDMETHODIMP CSurfaceCollection::Clone(ISurfaceCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSurfaceCollection>* pClone;
   CComObject<CSurfaceCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->putref_Profile(m_pProfile);

   CComPtr<IEnumSurfaces> enumSurfaces;
   get__EnumSurfaces(&enumSurfaces);

   CComPtr<ISurface> surface;
   while ( enumSurfaces->Next(1,&surface,NULL) != S_FALSE )
   {
      CComPtr<ISurface> surfaceClone;
      surface->Clone(&surfaceClone);

      (*clone)->Add(surfaceClone);

      surface.Release();
   };


   return S_OK;
}

STDMETHODIMP CSurfaceCollection::FindSurface(CogoObjectID id,ISurface** ppSurface)
{
   CHECK_RETOBJ(ppSurface);

   CComPtr<IEnumSurfaces> enumSurfaces;
   get__EnumSurfaces(&enumSurfaces);
   CComPtr<ISurface> surface;
   while ( enumSurfaces->Next(1,&surface,NULL) != S_FALSE )
   {
      CogoObjectID surfaceID;
      surface->get_ID(&surfaceID);
      if ( surfaceID == id )
      {
         // this is the surface
         (*ppSurface) = surface;
         (*ppSurface)->AddRef();
         return S_OK;
      }

      surface.Release();
   }

   return E_FAIL; // surface not found
}

STDMETHODIMP CSurfaceCollection::GetSurface(CogoObjectID id,VARIANT varStation,ISurface** ppSurface)
{
   CHECK_RETOBJ(ppSurface);
   (*ppSurface) = NULL;

   CComPtr<IStation> objStation;
   HRESULT hr = ValidateStation(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IEnumSurfaces> enumSurfaces;
   get__EnumSurfaces(&enumSurfaces);
   CComPtr<ISurface> surface;
   while ( enumSurfaces->Next(1,&surface,NULL) != S_FALSE )
   {
      CogoObjectID surfaceID;
      surface->get_ID(&surfaceID);
      if ( surfaceID == id )
      {
         CComPtr<IStation> objStartStation,objEndStation;
         surface->GetStationRange(&objStartStation,&objEndStation);

         if ( 0 <= cogoUtil::Compare(m_pProfile,objStartStation,objStation) && // station is after start
              0 <= cogoUtil::Compare(m_pProfile,objStation,objEndStation) )  // and station is before end
         {
            // this is the surface
            (*ppSurface) = surface;
            (*ppSurface)->AddRef();
            return S_OK;
         }
      }

      surface.Release();
   }

   return E_FAIL; // surface not found
}

STDMETHODIMP CSurfaceCollection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

/////////////////////////////////////////////////////////////////////////////
// ISurfaceEvents
STDMETHODIMP CSurfaceCollection::OnSurfaceChanged(ISurface * pSurface)
{
   Fire_OnSurfaceChanged(pSurface);
   return S_OK;
}

STDMETHODIMP CSurfaceCollection::get__EnumSurfaces(IEnumSurfaces** retval)
{
   CHECK_RETOBJ(retval);

   typedef CComEnumOnSTL<IEnumSurfaces,
                         &IID_IEnumSurfaces, 
                         ISurface*,
                         CopyFromPair2Interface<SurfaceType,ISurface*>, 
                         std::vector<SurfaceType>> Enum;
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
STDMETHODIMP CSurfaceCollection::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Surfaces"),1.0);
   CollectionIndexType count = m_coll.size();
   pSave->put_Property(CComBSTR("Count"),CComVariant(count));
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      pSave->put_Property(CComBSTR("Surface"),m_coll[i].second);
   }

   return S_OK;
}

STDMETHODIMP CSurfaceCollection::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Surfaces"));

   pLoad->get_Property(CComBSTR("Count"),&var);
   long count = var.lVal;

   for ( long i = 0; i < count; i++ )
   {
      pLoad->get_Property(CComBSTR("Surface"),&var);
      CComPtr<ISurface> surface;
      _CopyVariantToInterface<ISurface>::copy(&surface,&var);
      Add(surface);
   }

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

//////////////////////////////////////////
// Helper methods

void CSurfaceCollection::AdviseElement(ISurface* surface,DWORD* pdwCookie)
{
   CComPtr<ISurface> pCP(surface);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_ISurfaceEvents, pdwCookie );
   if ( FAILED(hr) )
   {
      *pdwCookie = 0;
      ATLTRACE("Failed to establish connection point with Surface object\n");
      return;
   }

   InternalRelease(); // Break circular reference
}

void CSurfaceCollection::UnadviseElement(CollectionIndexType idx)
{
   //
   // Disconnection from connection Surface
   //
   SurfaceType& p = m_coll[idx];
   if ( p.first == 0 )
      return;

   DWORD dwCookie = p.first;
   CComVariant& var = p.second;

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( var.pdispVal );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_ISurfaceEvents, &pCP );
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));

   p.first = 0;
}

void CSurfaceCollection::UnadviseAll()
{
   for ( CollectionIndexType i = 0; i < m_coll.size(); i++ )
   {
      UnadviseElement(i);
   }
}

HRESULT CSurfaceCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   return S_OK;
}

HRESULT CSurfaceCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   return S_OK;
}

HRESULT CSurfaceCollection::ValidateStation(VARIANT varStation,bool bClone,IStation** station)
{
   HRESULT hr = cogoUtil::StationFromVariant(varStation,bClone,station);
   if ( FAILED(hr) )
      return hr;

   if ( m_pProfile == NULL )
   {
      ZoneIndexType staEqnZoneIdx;
      (*station)->get_StationZoneIndex(&staEqnZoneIdx);
      if ( staEqnZoneIdx != INVALID_INDEX )
         return E_INVALIDARG; // station must be normalized
   }

   return S_OK;
}
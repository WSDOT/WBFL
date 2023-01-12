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

// SurfaceTemplateCollection.cpp : Implementation of CSurfaceTemplateCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "SurfaceTemplateCollection.h"
#include "SurfaceTemplate.h"
#include <WBFLCogo\CogoHelpers.h>

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class SortSurfaceTemplates
{
public:
   SortSurfaceTemplates(IProfile* pProfile) { m_pProfile = pProfile; }
   bool operator()(CComVariant& pX, CComVariant& pY)
   {
      CComVariant& varX = pX;
      CComVariant& varY = pY;
      CComPtr<IStation> staX, staY;
      
      CComQIPtr<ISurfaceTemplate> csX(varX.pdispVal);
      CComQIPtr<ISurfaceTemplate> csY(varY.pdispVal);

      csX->get_Station(&staX);
      csY->get_Station(&staY);
      return 0 < cogoUtil::Compare(m_pProfile,staX,staY);
   }
private:
   IProfile* m_pProfile; // weak reference
};

/////////////////////////////////////////////////////////////////////////////
// CSurfaceTemplateCollection
HRESULT CSurfaceTemplateCollection::FinalConstruct()
{
   m_pSurface = nullptr;
   return S_OK;
}

void CSurfaceTemplateCollection::FinalRelease()
{
}

STDMETHODIMP CSurfaceTemplateCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISurfaceTemplateCollection,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSurfaceTemplateCollection::get_Surface(ISurface* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pSurface )
   {
      (*pVal) = m_pSurface;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CSurfaceTemplateCollection::putref_Surface(ISurface* pSurface)
{
   m_pSurface = pSurface;

   CComPtr<IEnumSurfaceTemplates> enumSurfaceTemplates;
   get__EnumSurfaceTemplates(&enumSurfaceTemplates);

   CComPtr<ISurfaceTemplate> surfaceTemplate;
   while ( enumSurfaceTemplates->Next(1,&surfaceTemplate,nullptr) != S_FALSE )
   {
      surfaceTemplate->putref_Surface(m_pSurface);
      surfaceTemplate.Release();
   };

   return S_OK;
}

//STDMETHODIMP CSurfaceTemplateCollection::get__NewEnum(IUnknown** retval)
//{
//}

STDMETHODIMP CSurfaceTemplateCollection::get_Item(CollectionIndexType idx, ISurfaceTemplate* *pVal)
{
   CHECK_RETOBJ(pVal);

   if ( !IsValidIndex(idx,m_coll) )
      return E_INVALIDARG;

   CComVariant& p = m_coll[idx];
   CComVariant& varItem = p;
   varItem.pdispVal->QueryInterface(pVal);
   return S_OK;
}

STDMETHODIMP CSurfaceTemplateCollection::putref_Item(CollectionIndexType idx,ISurfaceTemplate* pVal)
{
   CHECK_IN(pVal);

   HRESULT hr = S_OK;

   if ( !IsValidIndex(idx,m_coll) )
      return E_INVALIDARG;

   // Get the item
   CComVariant& cst = m_coll[idx];
   CComVariant& var = cst; // Variant holding IDispatch to SurfaceTemplate
   pVal->putref_Surface(m_pSurface);

   var = pVal; // Associate new SurfaceTemplate with this variant

   return S_OK;
}

STDMETHODIMP CSurfaceTemplateCollection::GetBoundingTemplates(VARIANT varStation,ISurfaceTemplate** ppStart,ISurfaceTemplate** ppEnd)
{
   CHECK_RETOBJ(ppStart);
   CHECK_RETOBJ(ppEnd);

   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }

   // Templates at ends extend infinitely up/down station
   // Deal with special cases first
   if (m_coll.empty())
   {
      ATLASSERT(0); // bad form
      return E_FAIL;
   }
   else if (m_coll.size() == 1)
   {
      // only one template. It bounds all
      CComVariant& stType1 = m_coll.front();
      CComVariant var1(stType1);
      CComQIPtr<ISurfaceTemplate> template1(var1.pdispVal);
      template1.CopyTo(ppStart);
      template1.CopyTo(ppEnd);
      return S_OK;
   }
   else
   {
      // Check if station is before or after all templates
      CComVariant& stType_front = m_coll.front();
      CComVariant var_front(stType_front);
      CComQIPtr<ISurfaceTemplate> template_front(var_front.pdispVal);
      CComPtr<IStation> station_front;
      template_front->get_Station(&station_front);

      if (0 >= cogoUtil::Compare(profile, station_front, objStation))
      {
         // station is before start of templates. use front template for bracket
         template_front.CopyTo(ppStart);
         template_front.CopyTo(ppEnd);
         return S_OK;
      }
      else
      {
         CComVariant& stType_back = m_coll.back();
         CComVariant var_back(stType_back);
         CComQIPtr<ISurfaceTemplate> template_back(var_back.pdispVal);
         CComPtr<IStation> station_back;
         template_back->get_Station(&station_back);

         if (0 <= cogoUtil::Compare(profile, station_back, objStation))
         {
            // station is after end of templates. use back template for bracket
            template_back.CopyTo(ppStart);
            template_back.CopyTo(ppEnd);
            return S_OK;
         }
         else
         {
            // station is in between two templates - find bracketing templates
            auto iter1(m_coll.begin());
            auto iter2(iter1 + 1);
            auto end(m_coll.end());
            for (; iter2 != end; iter1++, iter2++)
            {
               CComVariant& stType1 = *iter1;
               CComVariant& stType2 = *iter2;

               CComVariant var1(stType1);
               CComVariant var2(stType2);

               CComQIPtr<ISurfaceTemplate> template1(var1.pdispVal);
               CComQIPtr<ISurfaceTemplate> template2(var2.pdispVal);

               CComPtr<IStation> station1, station2;
               template1->get_Station(&station1);
               template2->get_Station(&station2);

               if (0 <= cogoUtil::Compare(profile, station1, objStation) && // station is at or after station1
                  0 <= cogoUtil::Compare(profile, objStation, station2))  // station is at or before station2
               {
                  // station is between station1 and station2... these are the templates that we want
                  template1.CopyTo(ppStart);
                  template2.CopyTo(ppEnd);

                  return S_OK;
               }
            }
         }
      }
   }

   return E_FAIL;
}

STDMETHODIMP CSurfaceTemplateCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
   return S_OK;
}

STDMETHODIMP CSurfaceTemplateCollection::Add(ISurfaceTemplate* pSurfaceTemplate)
{
   CHECK_IN(pSurfaceTemplate);

   pSurfaceTemplate->putref_Surface(m_pSurface);

   m_coll.emplace_back( CComVariant(pSurfaceTemplate));

   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }
   std::sort(std::begin(m_coll),std::end(m_coll),SortSurfaceTemplates(profile));

   return S_OK;
}

STDMETHODIMP CSurfaceTemplateCollection::Remove(CollectionIndexType idx)
{
   if ( idx < 0 || m_coll.size() <= idx )
      return E_INVALIDARG;

   m_coll.erase(m_coll.begin() + idx );
   return S_OK;
}

STDMETHODIMP CSurfaceTemplateCollection::Clear()
{
   m_coll.clear();
   return S_OK;
}

STDMETHODIMP CSurfaceTemplateCollection::Clone(ISurfaceTemplateCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSurfaceTemplateCollection>* pClone;
   CComObject<CSurfaceTemplateCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->putref_Surface(m_pSurface);

   CComPtr<IEnumSurfaceTemplates> enumSurfaceTemplates;
   get__EnumSurfaceTemplates(&enumSurfaceTemplates);

   CComPtr<ISurfaceTemplate> surfaceTemplate;
   while ( enumSurfaceTemplates->Next(1,&surfaceTemplate,nullptr) != S_FALSE )
   {
      CComPtr<ISurfaceTemplate> surfaceTemplateClone;
      surfaceTemplate->Clone(&surfaceTemplateClone);

      (*clone)->Add(surfaceTemplateClone);

      surfaceTemplate.Release();
   };


   return S_OK;
}

STDMETHODIMP CSurfaceTemplateCollection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

STDMETHODIMP CSurfaceTemplateCollection::get__EnumSurfaceTemplates(IEnumSurfaceTemplates** retval)
{
   CHECK_RETOBJ(retval);

   typedef CComEnumOnSTL<IEnumSurfaceTemplates,
                         &IID_IEnumSurfaceTemplates, 
                         ISurfaceTemplate*,
                         _CopyVariantToInterface<ISurfaceTemplate>, 
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
STDMETHODIMP CSurfaceTemplateCollection::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("SurfaceTemplates"),1.0);
   CollectionIndexType count = m_coll.size();
   pSave->put_Property(CComBSTR("Count"),CComVariant(count));
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      pSave->put_Property(CComBSTR("SurfaceTemplate"),m_coll[i]);
   }

   return S_OK;
}

STDMETHODIMP CSurfaceTemplateCollection::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("SurfaceTemplates"));

   pLoad->get_Property(CComBSTR("Count"),&var);
   long count = var.lVal;

   for ( long i = 0; i < count; i++ )
   {
      pLoad->get_Property(CComBSTR("SurfaceTemplate"),&var);
      CComPtr<ISurfaceTemplate> surfaceTemplate;
      _CopyVariantToInterface<ISurfaceTemplate>::copy(&surfaceTemplate,&var);
      Add(surfaceTemplate);
   }

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}


HRESULT CSurfaceTemplateCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   return S_OK;
}

HRESULT CSurfaceTemplateCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   return S_OK;
}
//
//HRESULT CSurfaceTemplateCollection::ValidateStation(ISurfaceTemplate* csect)
//{
//   CComPtr<IStation> station;
//   csect->get_Station(&station);
//   CComPtr<IStation> sta;
//   return ValidateStation(CComVariant(station),false,&sta);
//}
//
//HRESULT CSurfaceTemplateCollection::ValidateStation(VARIANT varStation,bool bClone,IStation** station)
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
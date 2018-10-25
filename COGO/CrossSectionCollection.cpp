///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// CrossSectionCollection.cpp : Implementation of CCrossSectionCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CrossSectionCollection.h"
#include "CrossSectionFactory.h"
#include "CogoHelpers.h"
#include <MathEx.h>

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class SortCrossSections
{
public:
   bool operator()(CSType& pX,CSType& pY)
   {
      CComVariant& varX = pX.second;
      CComVariant& varY = pY.second;
      CComPtr<IStation> staX, staY;
      
      CComQIPtr<ICrossSection> csX(varX.pdispVal);
      CComQIPtr<ICrossSection> csY(varY.pdispVal);

      csX->get_Station(&staX);
      csY->get_Station(&staY);

      return staX < staY;
   }
};

/////////////////////////////////////////////////////////////////////////////
// CCrossSectionCollection
HRESULT CCrossSectionCollection::FinalConstruct()
{
   CComObject<CCrossSectionFactory>* pFactory;
   CComObject<CCrossSectionFactory>::CreateInstance(&pFactory);

   m_Factory = pFactory;

   return S_OK;
}

void CCrossSectionCollection::FinalRelease()
{
   UnadviseAll();
}

STDMETHODIMP CCrossSectionCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICrossSectionCollection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//STDMETHODIMP CCrossSectionCollection::get__NewEnum(IUnknown** retval)
//{
//}

STDMETHODIMP CCrossSectionCollection::get_Item(CollectionIndexType idx, ICrossSection* *pVal)
{
   CHECK_RETOBJ(pVal);

   if ( !IsValidIndex(idx,m_coll) )
      return E_INVALIDARG;

   CSType& p = m_coll[idx];
   CComVariant& varItem = p.second;
   varItem.pdispVal->QueryInterface(pVal);
   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::putref_Item(CollectionIndexType idx,ICrossSection* pVal)
{
   CHECK_IN(pVal);

   if ( !IsValidIndex(idx,m_coll) )
      return E_INVALIDARG;

   // Get the item
   CSType& cst = m_coll[idx];
   CComVariant& var = cst.second; // Variant holding IDispatch to CrossSection

   UnadviseElement(idx); // Unadvise from the current element

   var = pVal; // Associate new CrossSection with this variant

   // Advise
   DWORD dwCookie;
   AdviseElement(pVal,&dwCookie);

   // Update the cookie
   cst.first = dwCookie;

   Fire_OnCrossSectionChanged(pVal);

   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::AddEx(ICrossSection* csect)
{
   CHECK_IN(csect);

   DWORD dwCookie;
   AdviseElement(csect,&dwCookie);
   m_coll.push_back( std::make_pair(dwCookie,CComVariant(csect)));
   std::sort(m_coll.begin(),m_coll.end(),SortCrossSections());

   Fire_OnCrossSectionAdded(csect);
   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::Add(VARIANT varStation, Float64 cpo, Float64 left, Float64 right,ICrossSection* *cs)
{
   if ( cs != NULL )
   {
      CHECK_RETOBJ(cs);
   }

   CComPtr<ICrossSection> newCS;
   m_Factory->CreateCrossSection(&newCS);
   HRESULT hr = newCS->put_Station(varStation);
   if ( FAILED(hr) )
      return hr;

   newCS->put_CrownPointOffset(cpo);
   newCS->put_LeftCrownSlope(left);
   newCS->put_RightCrownSlope(right);

   if ( cs != NULL )
   {
      (*cs) = newCS;
      (*cs)->AddRef();
   }

   return AddEx(newCS);
}

STDMETHODIMP CCrossSectionCollection::Remove(CollectionIndexType idx)
{
   if ( idx < 0 || m_coll.size() <= idx )
      return E_INVALIDARG;

   UnadviseElement(idx);
   m_coll.erase(m_coll.begin() + idx );
   Fire_OnCrossSectionRemoved();
   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::CrownPointOffset(VARIANT varStation,Float64* cpoffset)
{
   CHECK_RETVAL(cpoffset);

   Float64 left, right, cpo;
   HRESULT hr = GetCrossSectionData(varStation,&cpo,&left,&right);
   if ( FAILED(hr) )
      return hr;

   *cpoffset = cpo;

   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::CrownSlope(VARIANT varStation, Float64 offset, Float64* slope)
{
   CHECK_RETVAL(slope);

   Float64 left, right, cpo;
   HRESULT hr = GetCrossSectionData(varStation,&cpo,&left,&right);
   if ( FAILED(hr) )
      return hr;

   *slope = (offset < cpo ? left : right );

   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::LeftCrownSlope(VARIANT varStation, Float64* slope)
{
   CHECK_RETVAL(slope);

   Float64 left, right, cpo;
   HRESULT hr = GetCrossSectionData(varStation,&cpo,&left,&right);
   if ( FAILED(hr) )
      return hr;

   *slope = left;

   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::RightCrownSlope(VARIANT varStation, Float64* slope)
{
   CHECK_RETVAL(slope);

   Float64 left, right, cpo;
   HRESULT hr = GetCrossSectionData(varStation,&cpo,&left,&right);
   if ( FAILED(hr) )
      return hr;

   *slope = right;

   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::CreateCrossSection(VARIANT varStation, ICrossSection* *objCS)
{
   CHECK_RETOBJ(objCS);

   Float64 left, right, cpo;
   HRESULT hr = GetCrossSectionData(varStation,&cpo,&left,&right);
   if ( FAILED(hr) )
      return hr;

   CComPtr<ICrossSection> cs;
   m_Factory->CreateCrossSection(&cs);
   cs->put_Station(varStation);
   cs->put_CrownPointOffset(cpo);
   cs->put_LeftCrownSlope(left);
   cs->put_RightCrownSlope(right);

   (*objCS) = cs;
   (*objCS)->AddRef();

   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnCrossSectionsCleared();
   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::Clone(ICrossSectionCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CCrossSectionCollection>* pClone;
   CComObject<CCrossSectionCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->PutProfile(m_pProfile);

   CComPtr<IEnumCrossSections> enumSections;
   get__EnumCrossSections(&enumSections);

   CComPtr<ICrossSection> cs;
   while ( enumSections->Next(1,&cs,NULL) != S_FALSE )
   {
      CComPtr<ICrossSection> csClone;
      cs->Clone(&csClone);

      (*clone)->AddEx(csClone);

      cs.Release();
   };

   (*clone)->putref_Factory(m_Factory);

   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

/////////////////////////////////////////////////////////////////////////////
// ICrossSectionEvents
STDMETHODIMP CCrossSectionCollection::OnCrossSectionChanged(ICrossSection * csect)
{
   m_CrownPointPath.Release();
   Fire_OnCrossSectionChanged(csect);
   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::OnCrossSectionMoved(ICrossSection * csect)
{
   // Re-sort the collection
   m_CrownPointPath.Release();
   std::sort(m_coll.begin(),m_coll.end(),SortCrossSections());
   Fire_OnCrossSectionChanged(csect);
   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::get__EnumCrossSections(IEnumCrossSections** retval)
{
   CHECK_RETOBJ(retval);

   typedef CComEnumOnSTL<IEnumCrossSections,
                         &IID_IEnumCrossSections, 
                         ICrossSection*,
                         CopyFromPair2Interface<CSType,ICrossSection*>, 
                         std::vector<CSType>> Enum;
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

STDMETHODIMP CCrossSectionCollection::get_Profile(IProfile** ppProfile)
{
   CHECK_RETOBJ(ppProfile);
   (*ppProfile) = m_pProfile;
   (*ppProfile)->AddRef();
   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::get_CrownPointPath(IPath** ppPath)
{
   if (m_CrownPointPath == NULL )
   {
      HRESULT hr = UpdateCrownPointPath();
      if ( FAILED(hr) )
         return hr;
   }

   (*ppPath) = m_CrownPointPath;
   (*ppPath)->AddRef();

   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::get_Factory(ICrossSectionFactory* *factory)
{
   CHECK_RETOBJ(factory);
   (*factory) = m_Factory;
   (*factory)->AddRef();
   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::putref_Factory(ICrossSectionFactory* factory)
{
   CHECK_IN(factory);
   m_Factory = factory;
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CCrossSectionCollection::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("CrossSections"),1.0);
   CollectionIndexType count = m_coll.size();
   pSave->put_Property(CComBSTR("Count"),CComVariant(count));
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      pSave->put_Property(CComBSTR("CrossSection"),m_coll[i].second);
   }

   pSave->put_Property(CComBSTR("Factory"),CComVariant(m_Factory));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCrossSectionCollection::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("CrossSections"));

   pLoad->get_Property(CComBSTR("Count"),&var);
   long count = var.lVal;

   for ( long i = 0; i < count; i++ )
   {
      pLoad->get_Property(CComBSTR("CrossSection"),&var);
      CComPtr<ICrossSection> cs;
      _CopyVariantToInterface<ICrossSection>::copy(&cs,&var);
      AddEx(cs);
   }

   pLoad->get_Property(CComBSTR("Factory"),&var);
   CComPtr<ICrossSectionFactory> factory;
   _CopyVariantToInterface<ICrossSectionFactory>::copy(&factory,&var);
   putref_Factory(factory);

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

//////////////////////////////////////////
// Helper methods
HRESULT CCrossSectionCollection::GetCrossSectionData(VARIANT varStation,Float64* pCPO,Float64* pLeft,Float64* pRight)
{
   if ( m_coll.size() == 0 )
   {
      *pCPO   = 0.0;
      *pLeft  = 0.0;
      *pRight = 0.0;
      return S_OK;
   }

   CComPtr<IStation> station;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,&station);

   // See out first cross section after "station"
   CComPtr<IStation> nextStation;
   CComPtr<ICrossSection> csNext;
   CrossSections::iterator iter = m_coll.begin();
   do
   {
      CSType& type = *iter++;
      CComVariant& var = type.second;
      csNext.Release();
      var.pdispVal->QueryInterface(&csNext);

      nextStation.Release();
      csNext->get_Station(&nextStation);
   } while ( nextStation < station && iter < m_coll.end() );

   if ( iter == m_coll.begin()+1 || iter == m_coll.end() && nextStation < station )
   {
      // Station occurs before first or after the last defined cross section
      // Simply grab the data from that cross section
      csNext->get_CrownPointOffset(pCPO);
      csNext->get_LeftCrownSlope(pLeft);
      csNext->get_RightCrownSlope(pRight);
      return S_OK;
   }

   // If we get this far, there must be at least 2 cross sections defined
   ATLASSERT(m_coll.size() >= 2);

   // Get the previous cross section
   iter--;
   iter--;
   CSType& typePrev = *iter;
   CComVariant& varPrev = typePrev.second;
   CComQIPtr<ICrossSection> csPrev(varPrev.pdispVal);
   CComPtr<IStation> prevStation;
   csPrev->get_Station(&prevStation);

   Float64 prevLeft, prevRight, prevCPO;
   Float64 nextLeft, nextRight, nextCPO;

   csNext->get_LeftCrownSlope(&nextLeft);
   csNext->get_RightCrownSlope(&nextRight);
   csNext->get_CrownPointOffset(&nextCPO);

   csPrev->get_LeftCrownSlope(&prevLeft);
   csPrev->get_RightCrownSlope(&prevRight);
   csPrev->get_CrownPointOffset(&prevCPO);

   // Lineraly interpolate the cross section parameters
   Float64 a = station - prevStation;
   Float64 range = nextStation - prevStation;

   *pLeft  = LinInterp(a, prevLeft,  nextLeft,  range);
   *pRight = LinInterp(a, prevRight, nextRight, range);
   *pCPO   = LinInterp(a, prevCPO,   nextCPO,   range);

   return S_OK;
}

void CCrossSectionCollection::AdviseElement(ICrossSection* cs,DWORD* pdwCookie)
{
   CComPtr<ICrossSection> pCP(cs);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_ICrossSectionEvents, pdwCookie );
   if ( FAILED(hr) )
   {
      *pdwCookie = 0;
      ATLTRACE("Failed to establish connection point with CrossSection object\n");
      return;
   }

   InternalRelease(); // Break circular reference
}

void CCrossSectionCollection::UnadviseElement(CollectionIndexType idx)
{
   //
   // Disconnection from connection CrossSection
   //
   CSType& p = m_coll[idx];
   if ( p.first == 0 )
      return;

   DWORD dwCookie = p.first;
   CComVariant& var = p.second;

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( var.pdispVal );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_ICrossSectionEvents, &pCP );
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));

   p.first = 0;
}

void CCrossSectionCollection::UnadviseAll()
{
   for ( CollectionIndexType i = 0; i < m_coll.size(); i++ )
   {
      UnadviseElement(i);
   }
}

HRESULT CCrossSectionCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   pSave->put_Property(CComBSTR("CrossSectionFactory"),CComVariant(m_Factory));
   return S_OK;
}

HRESULT CCrossSectionCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->get_Property(CComBSTR("CrossSectionFactory"),&var);
   m_Factory.Release();
   _CopyVariantToInterface<ICrossSectionFactory>::copy(&m_Factory,&var);
   return S_OK;
}

HRESULT CCrossSectionCollection::UpdateCrownPointPath()
{
   ATLASSERT(m_CrownPointPath == NULL);

   CComPtr<IPath> alignment_path;
   m_pProfile->get_Path(&alignment_path);
   CComQIPtr<IAlignment> alignment(alignment_path);
   if ( alignment == NULL )
      return E_FAIL; // need to be conncted to an alignment

   CComPtr<IStation> objRefStation;
   alignment->get_RefStation(&objRefStation);

   Float64 ref_station;
   objRefStation->get_Value(&ref_station);

   m_CrownPointPath.CoCreateInstance(CLSID_Path);

   CrossSections::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      CComPtr<IStation> station;
      CComPtr<ICrossSection> cross_section;

      CSType& type = *iter++;
      CComVariant& var = type.second;
      var.pdispVal->QueryInterface(&cross_section);

      Float64 cpo;
      cross_section->get_CrownPointOffset(&cpo);
      cross_section->get_Station(&station);

      CComPtr<IDirection> normal;
      alignment->Normal(CComVariant(station),&normal);

      CComPtr<IPoint2d> point;
      alignment->LocatePoint(CComVariant(station),omtAlongDirection,cpo,CComVariant(normal),&point);
      m_CrownPointPath->AddEx(point);
   }

   return S_OK;
}

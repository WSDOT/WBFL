///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// Profile.cpp : Implementation of CProfile
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Profile.h"
#include "ProfileElement.h"
#include "ProfilePoint.h"
#include "SurfaceCollection.h"
#include <WBFLCogo\CogoHelpers.h>

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class SortProfileElements
{
public:
   SortProfileElements(IAlignment* pAlignment){ m_pAlignment = pAlignment; }
   bool operator()(ProfileType& pX,ProfileType& pY)
   {
      CComVariant& varX = pX.second;
      CComVariant& varY = pY.second;
      CComPtr<IStation> staX, staY;
      
      CComQIPtr<IProfileElement> peX(varX.pdispVal);
      CComQIPtr<IProfileElement> peY(varY.pdispVal);

      CComPtr<IUnknown> disp;
      ProfileElementType type;

      peX->get_Type(&type);
      peX->get_Value(&disp);
      if ( type == pePoint )
      {
         CComQIPtr<IProfilePoint> point(disp);
         point->get_Station(&staX);
      }
      else
      {
         CComQIPtr<IVertCurve> curve(disp);
         CComPtr<IProfilePoint> bvc;
         curve->get_BVC(&bvc);
         bvc->get_Station(&staX);
      }

      disp.Release();

      peY->get_Type(&type);
      peY->get_Value(&disp);
      if ( type == pePoint )
      {
         CComQIPtr<IProfilePoint> point(disp);
         point->get_Station(&staY);
      }
      else
      {
         CComQIPtr<IVertCurve> curve(disp);
         CComPtr<IProfilePoint> bvc;
         curve->get_BVC(&bvc);
         bvc->get_Station(&staY);
      }

      return 0 < cogoUtil::Compare(m_pAlignment,staX,staY);
   }

private:
   IAlignment* m_pAlignment; // weak reference
};


/////////////////////////////////////////////////////////////////////////////
// CProfile
HRESULT CProfile::FinalConstruct()
{
   CComObject<CSurfaceCollection>* pSurfaces;
   CComObject<CSurfaceCollection>::CreateInstance(&pSurfaces);
   m_Surfaces = pSurfaces;
   m_Surfaces->putref_Profile(this);
   AdviseSurfaces();

   m_pAlignment = nullptr;

   CComObject<CProfileElement>* pTestElement;
   CComObject<CProfileElement>::CreateInstance(&pTestElement);
   m_TestElement = pTestElement;

   CComObject<CProfilePoint>* pTestPoint;
   CComObject<CProfilePoint>::CreateInstance(&pTestPoint);
   m_TestPoint = pTestPoint;
   m_TestPoint->putref_Profile(this);

   m_TestElement->putref_Value(m_TestPoint);

   return S_OK;
}

void CProfile::FinalRelease()
{
   UnadviseAll();
   UnadviseSurfaces();
}

STDMETHODIMP CProfile::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProfile,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}


STDMETHODIMP CProfile::get_Item(CollectionIndexType idx,IProfileElement **pVal)
{
   CHECK_RETOBJ(pVal);

   if ( idx < 0 || m_coll.size() <= idx )
      return E_INVALIDARG;

   ProfileType& type = m_coll[idx];
   CComVariant& var = type.second;
   var.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CProfile::putref_Item( CollectionIndexType idx, IProfileElement* pVal)
{
   CHECK_IN(pVal);

   if ( m_coll.size() <= idx )
   {
      return E_INVALIDARG;
   }

   // Get the item
   ProfileType& pt = m_coll[idx];
   CComVariant& var = pt.second; // Variant holding IUnknown to ProfileElement

   UnadviseElement(idx); // Unadvise from the current element

   var = pVal; // Associate new ProfileElement with this variant

   // Advise
   DWORD dwCookie;
   AdviseElement(pVal,&dwCookie);

   // Update the cookie
   pt.first = dwCookie;

   Fire_OnProfileChanged(this);

   return S_OK;
}

STDMETHODIMP CProfile::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
   return S_OK;
}

STDMETHODIMP CProfile::GetSurface(CogoObjectID id,VARIANT varStation,ISurface** ppSurface)
{
   if ( m_Surfaces )
   {
      return m_Surfaces->GetSurface(id,varStation,ppSurface);
   }
   else
   {
      CHECK_RETOBJ(ppSurface);
      *ppSurface = nullptr;
      return S_FALSE;
   }
}

STDMETHODIMP CProfile::get_Surfaces(ISurfaceCollection** ppSurfaces)
{
   CHECK_RETOBJ(ppSurfaces);
   (*ppSurfaces) = m_Surfaces;
   (*ppSurfaces)->AddRef();
   return S_OK;
}

STDMETHODIMP CProfile::putref_Surfaces(ISurfaceCollection* pSurfaces)
{
   CHECK_IN(pSurfaces);

   InternalAddRef();
   AtlUnadvise(m_Surfaces,IID_ISurfaceCollectionEvents,m_dwSurfaceCollectionCookie);

   m_Surfaces = pSurfaces;

   m_Surfaces.Advise(GetUnknown(),IID_ISurfaceCollectionEvents,&m_dwSurfaceCollectionCookie);
   InternalRelease();

   Fire_OnProfileChanged(this);

   return S_OK;
}

STDMETHODIMP CProfile::Add(IProfileElement *element)
{
   CHECK_IN(element);
   DWORD dwCookie;
   AdviseElement(element,&dwCookie);
   AssociateWithProfile(element);
   m_coll.emplace_back(dwCookie,CComVariant(element) );
   std::sort(std::begin(m_coll),std::end(m_coll),SortProfileElements(m_pAlignment));

   Fire_OnProfileChanged(this);

	return S_OK;
}

STDMETHODIMP CProfile::AddEx(IUnknown* dispElement)
{
   CHECK_IN(dispElement);
   CComQIPtr<IProfilePoint> point(dispElement);
   CComQIPtr<IVertCurve> curve(dispElement);

   if ( point == nullptr && curve == nullptr )
   {
      return Error(IDS_E_PROFILEELEMENTTYPE,IID_IProfile,COGO_E_PROFILEELEMENTTYPE);
   }

   CComObject<CProfileElement>* pElement;
   CComObject<CProfileElement>::CreateInstance(&pElement);
   CComPtr<IProfileElement> element = pElement;
   element->putref_Value(dispElement);

   return Add(element);
}

STDMETHODIMP CProfile::Remove(VARIANT varID)
{
   if ( varID.vt == VT_I2 || varID.vt == VT_I4 )
   {
      // Element identified by zero-based index
      long index = (varID.vt == VT_I2 ? varID.iVal : varID.lVal);
      if ( index < 0 || (long)m_coll.size() <= index )
         return E_INVALIDARG;

      UnadviseElement(index);
      m_coll.erase(m_coll.begin() + index);
   }
   else if ( varID.vt == VT_UNKNOWN || varID.vt == VT_DISPATCH )
   {
      // Element identified by a profile element object or by profile point or vert curve
      CComQIPtr<IProfileElement> element(varID.punkVal);
      CComQIPtr<IProfilePoint> point(varID.punkVal);
      CComQIPtr<IVertCurve> vc(varID.punkVal);

      // The input object is not of the correct type
      if ( element == nullptr && 
           point   == nullptr &&
           vc      == nullptr )
      {
         return E_INVALIDARG;
      }

      Profiles::iterator iter;
      bool bRemoved = false;
      for ( iter = m_coll.begin(); iter < m_coll.end(); iter++ )
      {
         ProfileType& pt = *iter;
         CComVariant& varElement = pt.second;
         CComQIPtr<IProfileElement> pe(varElement.punkVal);
         CComPtr<IUnknown> dispVal;
         pe->get_Value(&dispVal);
         if ( element != nullptr && element.IsEqualObject(varElement.punkVal) ||
              point   != nullptr && point.IsEqualObject(dispVal)              ||
              vc      != nullptr && vc.IsEqualObject(dispVal) )
         {
            UnadviseElement(iter - m_coll.begin());
            AssociateWithProfile(pe,false);
            m_coll.erase(iter);
            bRemoved = true;
            break; // exit the loop
         }
      }

      if ( !bRemoved )
      {
         return E_INVALIDARG;
      }
   }
   else
   {
      return E_INVALIDARG;
   }

   Fire_OnProfileChanged(this);
	return S_OK;
}

STDMETHODIMP CProfile::Elevation(VARIANT varStation, Float64 offset, Float64 *elev)
{
   CComPtr<IStation> station;
   HRESULT hr = GetStation(varStation,&station);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 grade;
   Float64 slope;
   return GradeAndElevation(station,offset,&grade,elev,&slope);
}

STDMETHODIMP CProfile::Grade(VARIANT varStation, Float64 *grade)
{
   CComPtr<IStation> station;
   HRESULT hr = GetStation(varStation,&station);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 elev;
   Float64 slope;
   Float64 offset = 0;
   return GradeAndElevation(station,offset,grade,&elev,&slope);
}

STDMETHODIMP CProfile::Slope(VARIANT varStation, Float64 offset, Float64* slope)
{
   CComPtr<IStation> station;
   HRESULT hr = GetStation(varStation,&station);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 elev;
   Float64 grade;
   return GradeAndElevation(station,offset,&grade,&elev,slope);
}

STDMETHODIMP CProfile::TemplateSegmentSlope(CogoObjectID id,VARIANT varStation,CollectionIndexType templateSegmentIdx,Float64* pSlope)
{
   CHECK_RETVAL(pSlope);

   HRESULT hr = S_OK;
   CComPtr<ISurface> surface;
   hr = m_Surfaces->GetSurface(id,varStation,&surface);
   if ( FAILED(hr) )
   {
      return hr;
   }

   if ( surface == nullptr )
   {
      *pSlope = 0;
      return S_OK;
   }

   CComPtr<ISurfaceTemplate> surfaceTemplate;
   hr = surface->CreateSurfaceTemplate(varStation,VARIANT_TRUE,&surfaceTemplate);
   if ( FAILED(hr) )
   {
      return hr;
   }

   CComPtr<ITemplateSegment> segment;
   hr = surfaceTemplate->get_Item(templateSegmentIdx,&segment);
   if ( FAILED(hr) )
   {
      return hr;
   }

   TemplateSlopeType slopeType;
   segment->get_SlopeType(&slopeType);

   Float64 slope;
   segment->get_Slope(&slope);

   if ( slopeType == tsFixedVertical )
   {
      // vertical slopes <= +/-0.001% are considered vertical
      // if < 0, slope goes down, else slope goes up
      if ( IsZero(slope,0.00001) )
      {
         slope = ::BinarySign(slope)*DBL_MAX;
      }
      else
      {
         slope = 1/slope;
      }
   }

   *pSlope = slope;
   return S_OK;
}

STDMETHODIMP CProfile::RidgePointOffset(CogoObjectID id,VARIANT varStation,IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset)
{
   // Gets the offset of ridgePointIdx measured from refPointIdx
   CComPtr<ISurface> surface;
   HRESULT hr = GetSurface(id,varStation,&surface);
   if ( FAILED(hr) )
   {
      return hr;
   }

   if ( surface == nullptr )
   {
      *pOffset = 0.0;
      return S_OK;
   }

   CComPtr<ISurfaceTemplate> surfaceTemplate;
   hr = surface->CreateSurfaceTemplate(varStation,VARIANT_TRUE,&surfaceTemplate);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return surfaceTemplate->GetRidgePointOffset(ridgePointIdx,refPointIdx,pOffset);
}

STDMETHODIMP CProfile::RidgePointElevation(CogoObjectID id,VARIANT varStation,IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset,Float64* pElev)
{
   // Gets the offset and elevation of the specified ridge point at the station provided. Offset is measured from the ridge point identified by refPointIdx
   HRESULT hr = RidgePointOffset(id,varStation,ridgePointIdx,refPointIdx,pOffset);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = Elevation(varStation,*pOffset,pElev);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return S_OK;
}

STDMETHODIMP CProfile::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnProfileChanged(this);
   return S_OK;
}

STDMETHODIMP CProfile::get__EnumProfileElements(IEnumProfileElements** retval)
{
   CHECK_RETOBJ(retval);

   typedef CComEnumOnSTL<IEnumProfileElements,
                         &IID_IEnumProfileElements, 
                         IProfileElement*,
                         CopyFromPair2Interface<ProfileType,IProfileElement*>, 
                         std::vector<ProfileType> > Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = pEnum->Init( nullptr, m_coll );
   if ( FAILED(hr) )
   {
      return hr;
   }

   pEnum->QueryInterface( retval );

   return S_OK;
}

STDMETHODIMP CProfile::get_Alignment(IAlignment** ppAlignment)
{
   CHECK_RETVAL(ppAlignment);
   if ( m_pAlignment )
   {
      (*ppAlignment) = m_pAlignment;
      (*ppAlignment)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CProfile::putref_Alignment(IAlignment* pAlignment)
{
   m_pAlignment = pAlignment;
   return S_OK;
}

STDMETHODIMP CProfile::Clone(IProfile* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CProfile>* pClone;
   CComObject<CProfile>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<ISurfaceCollection> cloneSurfaces;
   m_Surfaces->Clone(&cloneSurfaces);
   (*clone)->putref_Surfaces(cloneSurfaces);

   CComPtr<IEnumProfileElements> enumPE;
   get__EnumProfileElements(&enumPE);

   CComPtr<IProfileElement> pe;
   while ( enumPE->Next(1,&pe,nullptr) != S_FALSE )
   {
      CComPtr<IProfileElement> clonePE;
      pe->Clone(&clonePE);

      (*clone)->Add(clonePE);
      pe.Release();
   };

   return S_OK;
}

STDMETHODIMP CProfile::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CProfile::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Profile"),1.0);

   pSave->BeginUnit(CComBSTR("ProfileElements"),1.0);
   CollectionIndexType count = m_coll.size();
   pSave->put_Property(CComBSTR("Count"),CComVariant(count));
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      pSave->put_Property(CComBSTR("ProfileElement"),m_coll[i].second);
   }
   pSave->EndUnit(); // ProfileElements

   pSave->put_Property(CComBSTR("Surfaces"),CComVariant(m_Surfaces));

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CProfile::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Profile"));

   pLoad->BeginUnit(CComBSTR("ProfileElements"));
   pLoad->get_Property(CComBSTR("Count"),&var);
   long count = var.lVal;
   for ( long i = 0; i < count; i++ )
   {
      pLoad->get_Property(CComBSTR("ProfileElement"),&var);
      CComPtr<IProfileElement> pe;
      _CopyVariantToInterface<IProfileElement>::copy(&pe,&var);
      Add(pe);
   }
   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd); // ProfileElements

   pLoad->get_Property(CComBSTR("Surfaces"),&var);
   UnadviseSurfaces();
   m_Surfaces.Release();
   _CopyVariantToInterface<ISurfaceCollection>::copy(&m_Surfaces,&var);
   AdviseSurfaces();

   pLoad->EndUnit(&bEnd);

   return S_OK;
}

/////////////////////////////////////
// Helper methods
HRESULT CProfile::GradeAndElevation(IStation* pStation,Float64 offset,Float64* grade,Float64* elev,Float64* pSlope)
{
   CHECK_RETVAL(grade);
   CHECK_RETVAL(elev);


   if ( m_coll.size() == 0 )
   {
      *elev = 0.0;
      HRESULT hr = AdjustForOffset(pStation,offset,*elev,elev,pSlope);
      if ( FAILED(hr) )
      {
         return hr;
      }

      *grade = 0.0;
      return S_OK;
   }

   ProfileType pt = m_coll[0];
   CComVariant varElement = pt.second;
   CComQIPtr<IProfileElement> element(varElement.pdispVal);
   CComPtr<IUnknown> disp;
   ProfileElementType type;
   CComPtr<IStation> startSta;

   element->get_Type(&type);
   element->get_Value(&disp);

   if ( type == pePoint )
   {
      CComQIPtr<IProfilePoint> point(disp);
      point->get_Station(&startSta);
   }
   else
   {
      CComQIPtr<IVertCurve> vc(disp);
      CComPtr<IProfilePoint> bvc;
      vc->get_BVC(&bvc);
      bvc->get_Station(&startSta);
   }

   // Station is before the first station defined for the alignment
   if ( 0 < cogoUtil::Compare(m_pAlignment,pStation,startSta) )
   {
      BeforeProfileGradeAndElevation(pStation,grade,elev);
      return AdjustForOffset(pStation,offset,*elev,elev,pSlope);
   }

   pt = *(m_coll.end()-1);
   varElement = pt.second;
   element.Release();
   disp.Release();
   CComPtr<IStation> endSta;
   varElement.pdispVal->QueryInterface(&element);
   element->get_Type(&type);
   element->get_Value(&disp);

   if ( type == pePoint )
   {
      CComQIPtr<IProfilePoint> point(disp);
      point->get_Station(&endSta);
   }
   else
   {
      CComQIPtr<IVertCurve> vc(disp);
      CComPtr<IProfilePoint> evc;
      vc->get_EVC(&evc);
      evc->get_Station(&endSta);
   }

   // Station is after the last station defined for the alignment
   if ( 0 < cogoUtil::Compare(m_pAlignment,endSta,pStation) )
   {
      AfterProfileGradeAndElevation(pStation,grade,elev);
      return AdjustForOffset(pStation,offset,*elev,elev,pSlope);
   }

   // Station is somewhere in the middle of the alignment
   ProfileGradeAndElevation(pStation,grade,elev);
   return AdjustForOffset(pStation,offset,*elev,elev,pSlope);
}

void CProfile::BeforeProfileGradeAndElevation(IStation* pStation,Float64* pGrade, Float64* pElev)
{
   // Get the first element. If it is a vertical curve
   // the curve can compute the elevation
   ProfileType pt = m_coll[0];
   CComVariant varElement = pt.second;
   CComQIPtr<IProfileElement> element(varElement.pdispVal);
   CComPtr<IUnknown> disp;
   ProfileElementType type;

   element->get_Type(&type);
   element->get_Value(&disp);

   if ( type == peVertCurve )
   {
      CComQIPtr<IVertCurve> vc(disp);
      vc->Grade(CComVariant(pStation),pGrade);
      vc->Elevation(CComVariant(pStation),pElev);
      return;
   }
   else
   {
      // First point is a profile point... Need to get the next item in the profile
      CComQIPtr<IProfilePoint> p1(disp);

      if ( m_coll.size() == 1 )
      {
         p1->get_Elevation(pElev);
         *pGrade = 0;
         return;
      }

      ATLASSERT(m_coll.size() > 1); // size == 1 should be handled elsewhere
      pt = m_coll[1];
      varElement = pt.second;
      element.Release();
      varElement.pdispVal->QueryInterface(&element);

      disp.Release();
      element->get_Type(&type);
      element->get_Value(&disp);

      CComPtr<IProfilePoint> p2;
      if ( type == pePoint )
      {
         // second element is a point
         disp->QueryInterface(&p2);
      }
      else
      {
         // second element is a vertical curve
         // get the bvc point
         CComQIPtr<IVertCurve> vc(disp);
         vc->get_BVC(&p2);
      }

      CComPtr<IStation> sta1,sta2;
      Float64 elev1,elev2;

      p1->get_Station(&sta1);
      p1->get_Elevation(&elev1);

      p2->get_Station(&sta2);
      p2->get_Elevation(&elev2);

      Float64 staVal1 = cogoUtil::GetNormalizedStationValue(this,sta1);
      Float64 staVal2 = cogoUtil::GetNormalizedStationValue(this,sta2);
      Float64 stationVal = cogoUtil::GetNormalizedStationValue(this,pStation);

      if ( !IsEqual(staVal1,staVal2) ) 
      {
         *pElev = LinInterp(stationVal - staVal1,elev1,elev2,staVal2-staVal1);
         *pGrade = (elev2 - elev1)/(staVal2 - staVal1);
      }
      else
      {
          // first and second point are at same location

         // If the next element is a vertical curve, it can compute the elevation and grade
         if ( type == peVertCurve )
         {
            CComQIPtr<IVertCurve> vc(disp);
            vc->Grade(CComVariant(pStation),pGrade);
            vc->Elevation(CComVariant(pStation),pElev);
            return;
         }
         else
         {
            // we have two profile points at exactly the same location
            // use the elevation of the first point and set the grade = 0
            *pElev  = elev1;
            *pGrade = 0;
         }
      }

      return;
   }
}

bool CompareProfileElements(const ProfileType& pt,const ProfileType& testPt)
{
   CComPtr<IProfile> profile;

   CComPtr<IStation> station;
   const CComVariant& varElement = pt.second;
   CComQIPtr<IProfileElement> element(varElement.pdispVal);
   CComPtr<IUnknown> disp;
   element->get_Value(&disp);

   ProfileElementType type;
   element->get_Type(&type);
   if ( type == pePoint )
   {
      CComQIPtr<IProfilePoint> point(disp);
      point->get_Station(&station);

      point->get_Profile(&profile);
   }
   else
   {
      CComQIPtr<IVertCurve> vc(disp);
      CComPtr<IProfilePoint> bvc;
      vc->get_BVC(&bvc);
      bvc->get_Station(&station);

      vc->get_Profile(&profile);
   }

   CComPtr<IStation> testStation;
   const CComVariant& varTestElement = testPt.second;
   CComQIPtr<IProfileElement> test_element(varTestElement.pdispVal);
   CComPtr<IUnknown> test_disp;
   test_element->get_Value(&test_disp);

   test_element->get_Type(&type);
   if ( type == pePoint )
   {
      CComQIPtr<IProfilePoint> point(test_disp);
      point->get_Station(&testStation);
   }
   else
   {
      CComQIPtr<IVertCurve> vc(test_disp);
      CComPtr<IProfilePoint> bvc;
      vc->get_BVC(&bvc);
      bvc->get_Station(&testStation);
   }

   return (0 < cogoUtil::Compare(profile,station,testStation));
}

void CProfile::ProfileGradeAndElevation(IStation* pStation,Float64* pGrade, Float64* pElev)
{
   if ( m_coll.size() == 1 )
   {
      ProfileType& pt = m_coll[0];
      CComVariant& varElement = pt.second;
      CComQIPtr<IProfileElement> element(varElement.pdispVal);
      CComPtr<IUnknown> disp;
      ProfileElementType type;

      element->get_Type(&type);
      element->get_Value(&disp);

      if ( type == pePoint )
      {
         CComQIPtr<IProfilePoint> point(disp);
         point->get_Elevation(pElev);
         *pGrade = 0.0;
         return;
      }
      else
      {
         CComQIPtr<IVertCurve> vc(disp);
         vc->Elevation(CComVariant(pStation),pElev);
         vc->Grade(CComVariant(pStation),pGrade);
         return;
      }
   }

   m_TestPoint->put_Station(CComVariant(pStation));
   ProfileType findMe(-1,CComVariant(m_TestElement));
   Profiles::iterator iter = std::upper_bound(m_coll.begin(),m_coll.end(),findMe,CompareProfileElements);
   if ( iter == m_coll.end() )
   {
      iter--;
   }

//   // Alternative (and original) implementation... linear search
//   // Iterate over the profile until we are one element past the desired station
//   CComPtr<IStation> lastStation;
//   Profiles::iterator iter = m_coll.begin();
//   do
//   {
//      ProfileType& pt = *iter++;
//      CComVariant& varElement = pt.second;
//      CComQIPtr<IProfileElement> element(varElement.pdispVal);
//      CComPtr<IUnknown> disp;
//      element->get_Value(&disp);
//
//      ProfileElementType type;
//      element->get_Type(&type);
//      if ( type == pePoint )
//      {
//         CComQIPtr<IProfilePoint> point(disp);
//         lastStation.Release();
//         point->get_Station(&lastStation);
//      }
//      else
//      {
//         CComQIPtr<IVertCurve> vc(disp);
//         CComPtr<IProfilePoint> bvc;
//         vc->get_BVC(&bvc);
//         lastStation.Release();
//         bvc->get_Station(&lastStation);
//      }
//   } while ( 0 <= cogoUtil::Compare(m_pAlignment,lastStation,pStation) && iter != m_coll.end() );

   // These elements are on either side the the desired station
   //iter--; // went one past... back up one


   ProfileType& ptNext = *iter--;
   ProfileType& ptPrev = *iter;
   CComVariant& varnextElement = ptNext.second;
   CComVariant& varprevElement = ptPrev.second;
   CComQIPtr<IProfileElement> nextElement(varnextElement.pdispVal);
   CComQIPtr<IProfileElement> prevElement(varprevElement.pdispVal);

   CComPtr<IUnknown> prevDisp;
   CComPtr<IUnknown> nextDisp;

   prevElement->get_Value(&prevDisp);
   nextElement->get_Value(&nextDisp);

   ProfileElementType prevType, nextType;
   prevElement->get_Type(&prevType);
   nextElement->get_Type(&nextType);

   CComPtr<IStation> prevSta, nextSta;
   Float64 prevElev, nextElev;

   // Check to see if previous element is a vertical curve and if station is within
   // the limits of the curve. If it is, use the vertical curve to compute the elevation
   CComPtr<IStation> bvcSta, evcSta;
   bool bBetweenElements = true;
   if ( prevType == peVertCurve )
   {
      CComQIPtr<IVertCurve> vc(prevDisp);
      CComPtr<IProfilePoint> bvc, evc;
      vc->get_BVC(&bvc);
      vc->get_EVC(&evc);
      bvc->get_Station(&bvcSta);
      evc->get_Station(&evcSta);

      if ( 0 <= cogoUtil::Compare(m_pAlignment,bvcSta,pStation) && 0 <= cogoUtil::Compare(m_pAlignment,pStation,evcSta) )
      {
         vc->Elevation(CComVariant(pStation),pElev);
         vc->Grade(CComVariant(pStation),pGrade);
         bBetweenElements = false;
      }
      else
      {
         prevSta = evcSta;
         evc->get_Elevation(&prevElev);
      }
   }
   else
   {
      CComQIPtr<IProfilePoint> p(prevDisp);
      p->get_Station(&prevSta);
      p->get_Elevation(&prevElev);
   }

   // Check to see if the next element is a vertical curve and if the station is within
   // the limits of the curve. If it is, use the vertical curve to compute the elevation
   if ( nextType == peVertCurve )
   {
      CComQIPtr<IVertCurve> vc(nextDisp);
      CComPtr<IProfilePoint> bvc, evc;
      vc->get_BVC(&bvc);
      vc->get_EVC(&evc);
      
      bvcSta.Release();
      bvc->get_Station(&bvcSta);

      evcSta.Release();
      evc->get_Station(&evcSta);

      if ( 0 <= cogoUtil::Compare(m_pAlignment,bvcSta,pStation) && 0 <= cogoUtil::Compare(m_pAlignment,pStation,evcSta) )
      {
         vc->Elevation(CComVariant(pStation),pElev);
         vc->Grade(CComVariant(pStation),pGrade);
         bBetweenElements = false;
      }
      else
      {
         nextSta = bvcSta;
         bvc->get_Elevation(&nextElev);
      }
   }
   else
   {
      CComQIPtr<IProfilePoint> p(nextDisp);
      p->get_Station(&nextSta);
      p->get_Elevation(&nextElev);
   }

   // Station is on a grade between points.
   if ( bBetweenElements )
   {
      //ATLASSERT( prevSta <= station && station <= nextSta );
      Float64 dx = cogoUtil::Distance(m_pAlignment,prevSta,nextSta);
      Float64 dy = nextElev - prevElev;
      Float64 grade = dy/dx;
      *pGrade = grade;
      Float64 distance = cogoUtil::Distance(m_pAlignment,prevSta,pStation);
      *pElev = prevElev + grade*distance;
   }
}

void CProfile::AfterProfileGradeAndElevation(IStation* pStation,Float64* pGrade,Float64* pElev)
{
   // Get the last element. If it is a vertical curve
   // the curve can compute the elevation
   ProfileType pt = *(m_coll.end()-1);
   CComVariant varElement = pt.second;
   CComQIPtr<IProfileElement> element(varElement.pdispVal);
   CComPtr<IUnknown> disp;
   ProfileElementType type;

   element->get_Type(&type);
   element->get_Value(&disp);

   if ( type == peVertCurve )
   {
      CComQIPtr<IVertCurve> vc(disp);
      vc->Elevation(CComVariant(pStation),pElev);
      vc->Grade(CComVariant(pStation),pGrade);
      return;
   }
   else
   {
      // Last point is a profile point... Need to get the previous item in the profile
      CComQIPtr<IProfilePoint> p1(disp);

      if ( m_coll.size() == 1 )
      {
         p1->get_Elevation(pElev);
         *pGrade = 0;
         return;
      }

      ATLASSERT(m_coll.size() > 1); // size == 1 should be handled elsewhere
      pt = *(m_coll.end()-2);
      varElement = pt.second;
      element.Release();
      varElement.pdispVal->QueryInterface(&element);

      disp.Release();
      element->get_Type(&type);
      element->get_Value(&disp);

      CComPtr<IProfilePoint> p2;
      if ( type == pePoint )
      {
         // second element is a point
         disp->QueryInterface(&p2);
      }
      else
      {
         // element is a vertical curve
         // get the evc point
         CComQIPtr<IVertCurve> vc(disp);
         vc->get_EVC(&p2);
      }

      CComPtr<IStation> sta1,sta2;
      Float64 elev1,elev2;

      p1->get_Station(&sta1);
      p1->get_Elevation(&elev1);

      p2->get_Station(&sta2);
      p2->get_Elevation(&elev2);

      Float64 staVal1 = cogoUtil::GetNormalizedStationValue(m_pAlignment,sta1);
      Float64 staVal2 = cogoUtil::GetNormalizedStationValue(m_pAlignment,sta2);
      Float64 stationVal = cogoUtil::GetNormalizedStationValue(m_pAlignment,pStation);

      if ( !IsEqual(staVal1,staVal2) )
      {
         *pElev = LinInterp(stationVal - staVal1,elev1,elev2,staVal2-staVal1);
         *pGrade = (elev2 - elev1)/(staVal2 - staVal1);
      }
      else
      {
          // last and second to last points are at same location

         // If the second to last element is a vertical curve, it can compute the elevation and grade
         if ( type == peVertCurve )
         {
            CComQIPtr<IVertCurve> vc(disp);
            vc->Grade(CComVariant(pStation),pGrade);
            vc->Elevation(CComVariant(pStation),pElev);
            return;
         }
         else
         {
            // we have two profile points at exactly the same location
            // use the elevation of the last point and set the grade = 0
            *pElev  = elev2;
            *pGrade = 0;
         }
      }

      return;
   }
}

HRESULT CProfile::AdjustForOffset(IStation* pStation,Float64 offset,Float64 profileElev,Float64* pAdjElev,Float64* pSlope)
{
   CComPtr<ISurface> surface;
   m_Surfaces->GetSurface(COGO_FINISHED_SURFACE_ID,CComVariant(pStation),&surface);
   if ( surface == nullptr )
   {
      *pAdjElev = profileElev;
      return S_OK;
   }

   CComPtr<ISurfaceTemplate> surfaceTemplate;
   HRESULT hr = surface->CreateSurfaceTemplate(CComVariant(pStation),VARIANT_FALSE,&surfaceTemplate); // don't apply super
   if ( FAILED(hr) )
   {
      return hr;
   }

   IndexType alignmentPointIdx, profileGradePointIdx;
   surface->get_AlignmentPoint(&alignmentPointIdx);
   surface->get_ProfileGradePoint(&profileGradePointIdx);

   Float64 elevation = 0.0;

   CComPtr<ISuperelevationCollection> superelevations;
   surface->get_Superelevations(&superelevations);
   CComPtr<ISuperelevation> superelevation;
   superelevations->GetSuperelevation(CComVariant(pStation),&superelevation);
   if ( superelevation )
   {
      // this station is in a superelevation transition!!!
      IndexType pivotPoint;
      superelevation->get_PivotPoint(&pivotPoint);

      // determine elevation at pivot point based on normal section
      Float64 delta;
      hr = surfaceTemplate->GetRidgePointElevationChange(profileGradePointIdx,pivotPoint,&delta);
      if ( FAILED(hr) )
      {
         return hr;
      }

      Float64 pivotElevation = profileElev + delta;

      // Create the superelevated section
      CComPtr<ISurfaceTemplate> superSurfaceTemplate;
      hr = surface->CreateSurfaceTemplate(CComVariant(pStation),VARIANT_TRUE,&superSurfaceTemplate);
      if ( FAILED(hr) )
      {
         return hr;
      }

      // determine elevation at alignment based on superelevation section
      hr = superSurfaceTemplate->GetRidgePointElevationChange(pivotPoint,alignmentPointIdx,&delta);
      if ( FAILED(hr) )
      {
         return hr;
      }

      Float64 alignmentElev = pivotElevation + delta;

      // adjust elevation for offset from alignment
      hr = superSurfaceTemplate->GetElevationChange(alignmentPointIdx,offset,&delta);
      if ( FAILED(hr) )
      {
         return hr;
      }

      elevation = alignmentElev + delta;

      // get the cross slope
      hr = superSurfaceTemplate->GetSlope(alignmentPointIdx,offset,pSlope);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }
   else
   {
      // Determine elevation at Alignment = Profile Elevation + Change in elevation from profile point to alignment point
      Float64 delta;
      hr = surfaceTemplate->GetRidgePointElevationChange(profileGradePointIdx,alignmentPointIdx,&delta);
      if ( FAILED(hr) )
      {
         return hr;
      }

      Float64 alignmentElev = profileElev + delta;

      // Adjust elevation for offset from alignment
      hr = surfaceTemplate->GetElevationChange(alignmentPointIdx,offset,&delta);
      if ( FAILED(hr) )
      {
         return hr;
      }

      elevation = alignmentElev + delta;

      // get the cross slope
      hr = surfaceTemplate->GetSlope(alignmentPointIdx,offset,pSlope);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }

   *pAdjElev = elevation;
   return S_OK;
}

void CProfile::AssociateWithProfile(IProfileElement* element,bool bAssociate)
{
   CComPtr<IUnknown> disp;
   ProfileElementType type;

   element->get_Type(&type);
   element->get_Value(&disp);

   if ( type == peVertCurve )
   {
      CComQIPtr<IVertCurve> vc(disp);
      vc->putref_Profile(bAssociate ? this : nullptr);
   }
   else if ( type == pePoint )
   {
      CComQIPtr<IProfilePoint> pp(disp);
      pp->putref_Profile(bAssociate ? this : nullptr);
   }
   else
   {
      ATLASSERT(false);
      // is there a new type?
   }
}

void CProfile::AdviseElement(IProfileElement* element,DWORD* pdwCookie)
{
   HRESULT hr = AtlAdvise(element,GetUnknown(),IID_IProfileElementEvents,pdwCookie);
   if ( FAILED(hr) )
   {
      *pdwCookie = 0;
      ATLTRACE("Failed to establish connection point with CrossSection object\n");
      return;
   }

   InternalRelease(); // Break circular reference
}

void CProfile::UnadviseElement(CollectionIndexType idx)
{
   //
   // Disconnection from connection CrossSection
   //
   ProfileType& p = m_coll[idx];
   if ( p.first == 0 )
   {
      return;
   }

   DWORD dwCookie = (DWORD)p.first;
   CComVariant& var = p.second;

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   HRESULT hr = AtlUnadvise( var.pdispVal, IID_IProfileElementEvents, dwCookie );
   ATLASSERT(SUCCEEDED(hr));

   p.first = 0;
}

void CProfile::UnadviseAll()
{
   for ( CollectionIndexType i = 0; i < m_coll.size(); i++ )
   {
      UnadviseElement(i);
   }
}

void CProfile::AdviseSurfaces()
{
   m_Surfaces.Advise(GetUnknown(),IID_ISurfaceCollectionEvents,&m_dwSurfaceCollectionCookie);
   InternalRelease();
}

void CProfile::UnadviseSurfaces()
{
   InternalAddRef();
   AtlUnadvise(m_Surfaces,IID_ISurfaceCollectionEvents,m_dwSurfaceCollectionCookie);
}

HRESULT CProfile::GetStation(VARIANT varStation,IStation** station)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
   {
      return hr;
   }

   ZoneIndexType zoneIdx;
   objStation->get_StationZoneIndex(&zoneIdx);

   if ( m_pAlignment && zoneIdx != INVALID_INDEX )
   {
      CComPtr<IStationEquationCollection> equations;
      m_pAlignment->get_StationEquations(&equations);
      hr = equations->ConvertToNormalizedStationEx(CComVariant(objStation),station);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }
   else
   {
      if ( zoneIdx != INVALID_INDEX )
      {
         return E_INVALIDARG; // if this profile is not associated with an alignment, station must be normalized
      }

      (*station) = objStation;
      (*station)->AddRef();
   }

   return S_OK;
}

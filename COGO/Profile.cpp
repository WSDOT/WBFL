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

// Profile.cpp : Implementation of CProfile
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Profile.h"
#include "ProfileElement.h"
#include "CrossSectionCollection.h"
#include "CogoHelpers.h"
#include <MathEx.h>

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class SortProfileElements
{
public:
   bool operator()(std::pair<CogoElementKey,CComVariant>& pX,std::pair<CogoElementKey,CComVariant>& pY)
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

      Float64 staXValue;
      staX->get_Value(&staXValue);

      Float64 staYValue;
      staY->get_Value(&staYValue);

      return staXValue < staYValue;
   }
};


/////////////////////////////////////////////////////////////////////////////
// CProfile
HRESULT CProfile::FinalConstruct()
{
   CComObject<CCrossSectionCollection>* pColl;
   CComObject<CCrossSectionCollection>::CreateInstance(&pColl);

   pColl->PutProfile(this);

   m_CrossSections = pColl;
   AdviseCrossSections();

   m_pPath = NULL;

   return S_OK;
}

void CProfile::FinalRelease()
{
   UnadviseAll();
   UnadviseCrossSections();
}

STDMETHODIMP CProfile::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProfile,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CProfile::get_Count(CollectionIndexType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
   return S_OK;
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

   if ( idx < 0 || m_coll.size() <= idx )
      return E_INVALIDARG;

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

//STDMETHODIMP CProfile::get_Count(long *pVal)
//{
//	// TODO: Add your implementation code here
//
//	return S_OK;
//}

STDMETHODIMP CProfile::get_CrossSections(ICrossSectionCollection **pVal)
{
   CHECK_RETVAL(pVal);

   (*pVal) = m_CrossSections;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CProfile::putref_CrossSections(ICrossSectionCollection* pVal)
{
   CHECK_IN(pVal);

   InternalAddRef();
   AtlUnadvise(m_CrossSections,IID_ICrossSectionCollectionEvents,m_dwCookie);

   m_CrossSections = pVal;

   m_CrossSections.Advise(GetUnknown(),IID_ICrossSectionCollectionEvents,&m_dwCookie);
   InternalRelease();

   Fire_OnProfileChanged(this);

   return S_OK;
}
STDMETHODIMP CProfile::Add(IProfileElement *element)
{
   CHECK_IN(element);
   DWORD dwCookie;
   AdviseElement(element,&dwCookie);
   m_coll.push_back( std::make_pair(dwCookie,CComVariant(element)) );
   std::sort(m_coll.begin(),m_coll.end(),SortProfileElements());

   Fire_OnProfileChanged(this);

	return S_OK;
}

STDMETHODIMP CProfile::AddEx(IUnknown* dispElement)
{
   CHECK_IN(dispElement);
   CComQIPtr<IProfilePoint> point(dispElement);
   CComQIPtr<IVertCurve> curve(dispElement);

   if ( point == NULL && curve == NULL )
      return Error(IDS_E_PROFILEELEMENTTYPE,IID_IProfile,COGO_E_PROFILEELEMENTTYPE);

   CComObject<CProfileElement>* pElement;
   CComObject<CProfileElement>::CreateInstance(&pElement);
   CComPtr<IProfileElement> element = pElement;

   if ( point )
   {
      element->putref_Value(dispElement);
   }
   else
   {
      element->putref_Value(dispElement);
   }

   return Add(pElement);
}

STDMETHODIMP CProfile::Remove(VARIANT varKey)
{
   if ( varKey.vt == VT_I2 || varKey.vt == VT_I4 )
   {
      // Element identified by zero-based index
      long index = (varKey.vt == VT_I2 ? varKey.iVal : varKey.lVal);
      if ( index < 0 || (long)m_coll.size() <= index )
         return E_INVALIDARG;

      UnadviseElement(index);
      m_coll.erase(m_coll.begin() + index);
   }
   else if ( varKey.vt == VT_UNKNOWN || varKey.vt == VT_DISPATCH )
   {
      // Element identified by a profile element object or by profile point or vert curve
      CComQIPtr<IProfileElement> element(varKey.punkVal);
      CComQIPtr<IProfilePoint> point(varKey.punkVal);
      CComQIPtr<IVertCurve> vc(varKey.punkVal);

      // The input object is not of the correct type
      if ( element == NULL && 
           point   == NULL &&
           vc      == NULL )
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
         if ( element != NULL && element.IsEqualObject(varElement.punkVal) ||
              point   != NULL && point.IsEqualObject(dispVal)              ||
              vc      != NULL && vc.IsEqualObject(dispVal) )
         {
            UnadviseElement(iter - m_coll.begin());
            m_coll.erase(iter);
            bRemoved = true;
            break; // exit the loop
         }
      }

      if ( !bRemoved )
         return E_INVALIDARG;
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
   Float64 grade;
   return GradeAndElevation(varStation,offset,&grade,elev);
}

STDMETHODIMP CProfile::Grade(VARIANT varStation, Float64 *grade)
{
   Float64 elev;
   Float64 offset = 0;
   return GradeAndElevation(varStation,offset,grade,&elev);
}

STDMETHODIMP CProfile::CrownPointOffset(VARIANT varStation,Float64* cpoffset)
{
   CHECK_RETVAL(cpoffset);
   return m_CrossSections->CrownPointOffset(varStation,cpoffset);
}

STDMETHODIMP  CProfile::LeftCrownSlope(VARIANT varStation,Float64* slope)
{
   CHECK_RETVAL(slope);
   return m_CrossSections->LeftCrownSlope(varStation,slope);
}

STDMETHODIMP CProfile::RightCrownSlope(VARIANT varStation,Float64* slope)
{
   CHECK_RETVAL(slope);
   return m_CrossSections->RightCrownSlope(varStation,slope);
}

STDMETHODIMP CProfile::CrownSlope(VARIANT varStation, Float64 offset, Float64* slope)
{
   CHECK_RETVAL(slope);
   return m_CrossSections->CrownSlope(varStation,offset,slope);
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
                         CopyFromPair2Interface<std::pair<CogoElementKey,CComVariant>,
                                                IProfileElement*>, 
                         std::vector<std::pair<CogoElementKey,CComVariant> > > Enum;
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

STDMETHODIMP CProfile::get_Path(IPath** ppPath)
{
   CHECK_RETVAL(ppPath);
   (*ppPath) = m_pPath;
   if ( m_pPath )
      (*ppPath)->AddRef();

   return S_OK;
}

STDMETHODIMP CProfile::putref_Path(IPath* pPath)
{
   m_pPath = pPath;
   return S_OK;
}

STDMETHODIMP CProfile::Clone(IProfile* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CProfile>* pClone;
   CComObject<CProfile>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();


   CComPtr<ICrossSectionCollection> cloneCrossSections;
   m_CrossSections->Clone(&cloneCrossSections);
   (*clone)->putref_CrossSections(cloneCrossSections);

   CComPtr<IEnumProfileElements> enumPE;
   get__EnumProfileElements(&enumPE);

   CComPtr<IProfileElement> pe;
   while ( enumPE->Next(1,&pe,NULL) != S_FALSE )
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

   pSave->put_Property(CComBSTR("CrossSections"),CComVariant(m_CrossSections));

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

   pLoad->get_Property(CComBSTR("CrossSections"),&var);
   UnadviseCrossSections();
   m_CrossSections.Release();
   _CopyVariantToInterface<ICrossSectionCollection>::copy(&m_CrossSections,&var);
   AdviseCrossSections();

   pLoad->EndUnit(&bEnd);

   return S_OK;
}

/////////////////////////////////////
// Helper methods
HRESULT CProfile::GradeAndElevation(VARIANT varStation,Float64 offset,Float64* grade,Float64* elev)
{
   CHECK_RETVAL(grade);
   CHECK_RETVAL(elev);

   CComPtr<IStation> station;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,&station);
   if ( FAILED(hr) )
      return hr;


   if ( m_coll.size() == 0 )
   {
      *elev = 0.0;
      *elev = AdjustForOffset(station,offset,*elev);
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
   if ( station < startSta )
   {
      BeforeProfileGradeAndElevation(station,grade,elev);
      *elev = AdjustForOffset(station,offset,*elev);
      return S_OK;
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

   if ( endSta < station )
   {
      AfterProfileGradeAndElevation(station,grade,elev);
      *elev = AdjustForOffset(station,offset,*elev);
      return S_OK;
   }

   ProfileGradeAndElevation(station,grade,elev);
   *elev = AdjustForOffset(station,offset,*elev);
   return S_OK;
}

void CProfile::BeforeProfileGradeAndElevation(CComPtr<IStation>& station,Float64* pGrade, Float64* pElev)
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
      vc->Grade(CComVariant(station),pGrade);
      vc->Elevation(CComVariant(station),pElev);
      return;
   }
   else
   {
      // First point is a profile point... Need to get the next item in the profile
      CComQIPtr<IProfilePoint> p1(disp);

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

      Float64 staVal1,staVal2,stationVal;
      sta1->get_Value(&staVal1);
      sta2->get_Value(&staVal2);
      station->get_Value(&stationVal);

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
            vc->Grade(CComVariant(station),pGrade);
            vc->Elevation(CComVariant(station),pElev);
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

void CProfile::ProfileGradeAndElevation(CComPtr<IStation>& station,Float64* pGrade, Float64* pElev)
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
         vc->Elevation(CComVariant(station),pElev);
         vc->Grade(CComVariant(station),pGrade);
         return;
      }
   }

   // Iterate over the profile until we are one element past the desired station
   CComPtr<IStation> lastStation;
   Profiles::iterator iter = m_coll.begin();
   do
   {
      ProfileType& pt = *iter++;
      CComVariant& varElement = pt.second;
      CComQIPtr<IProfileElement> element(varElement.pdispVal);
      CComPtr<IUnknown> disp;
      element->get_Value(&disp);

      ProfileElementType type;
      element->get_Type(&type);
      if ( type == pePoint )
      {
         CComQIPtr<IProfilePoint> point(disp);
         lastStation.Release();
         point->get_Station(&lastStation);
      }
      else
      {
         CComQIPtr<IVertCurve> vc(disp);
         CComPtr<IProfilePoint> bvc;
         vc->get_BVC(&bvc);
         lastStation.Release();
         bvc->get_Station(&lastStation);
      }
   } while ( lastStation <= station && iter != m_coll.end() );

   // These elements are on either side the the desired station
   iter--; // went one past... back up one
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

      if ( bvcSta <= station && station <= evcSta )
      {
         vc->Elevation(CComVariant(station),pElev);
         vc->Grade(CComVariant(station),pGrade);
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

      if ( bvcSta <= station && station <= evcSta )
      {
         vc->Elevation(CComVariant(station),pElev);
         vc->Grade(CComVariant(station),pGrade);
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
      Float64 grade = ( nextElev - prevElev) / (nextSta - prevSta );
      *pGrade = grade;
      *pElev = prevElev + grade*(station - prevSta);
   }
}

void CProfile::AfterProfileGradeAndElevation(CComPtr<IStation>& station,Float64* pGrade,Float64* pElev)
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
      vc->Elevation(CComVariant(station),pElev);
      vc->Grade(CComVariant(station),pGrade);
      return;
   }
   else
   {
      // Last point is a profile point... Need to get the previous item in the profile
      CComQIPtr<IProfilePoint> p1(disp);

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

      Float64 staVal1,staVal2,stationVal;
      sta1->get_Value(&staVal1);
      sta2->get_Value(&staVal2);
      station->get_Value(&stationVal);

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
            vc->Grade(CComVariant(station),pGrade);
            vc->Elevation(CComVariant(station),pElev);
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

Float64 CProfile::AdjustForOffset(CComPtr<IStation>& station,Float64 offset,Float64 profileElev)
{
   Float64 elev;
   CComPtr<ICrossSection> cs;
   m_CrossSections->CreateCrossSection(CComVariant(station),&cs);

   Float64 cpo, left, right;
   cs->get_CrownPointOffset(&cpo);
   cs->get_LeftCrownSlope(&left);
   cs->get_RightCrownSlope(&right);

   if ( cpo * offset <= 0 )
   {
      // offset is in the opposite direction of the crown point offset
      Float64 slope = (offset < 0 ? left : right);
      elev = profileElev + fabs(offset) * slope;
   }
   else if ( fabs(offset) < fabs(cpo) )
   {
      // offset is in the same direction as the crown point offset
      // however, the offset does not go past the crown point offset
      Float64 slope = (cpo < 0 ? right : left);
      elev = profileElev - fabs(offset)*slope;
   }
   else
   {
      // offset is in the same direction as the crown point offset
      // however, the offset goes past the crown point offset
      Float64 slope1 = (cpo < 0 ? right : left);
      Float64 slope2 = (cpo < 0 ? left : right);
      elev = profileElev - fabs(cpo) * slope1 + fabs(offset-cpo)*slope2;
   }

   return elev;
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
   std::pair<CogoElementKey,CComVariant>& p = m_coll[idx];
   if ( p.first == 0 )
      return;

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

void CProfile::AdviseCrossSections()
{
   m_CrossSections.Advise(GetUnknown(),IID_ICrossSectionCollectionEvents,&m_dwCookie);
   InternalRelease();
}

void CProfile::UnadviseCrossSections()
{
   InternalAddRef();
   AtlUnadvise(m_CrossSections,IID_ICrossSectionCollectionEvents,m_dwCookie);
}

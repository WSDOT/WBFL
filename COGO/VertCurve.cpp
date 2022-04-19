///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2022  Washington State Department of Transportation
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

// VertCurve.cpp : Implementation of CVertCurve
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "VertCurve.h"
#include "ProfilePointFactory.h"
#include <WBFLCogo\CogoHelpers.h>
#include <xutility> // for Min and Max
#include <limits>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// NOTE: When L1 and L2 are both zero, treat the vertical curve as a profile point at the PVI

#define UPDATE_CURVE   HRESULT _hr = Update(); if ( FAILED(_hr) ) {return _hr;}

/////////////////////////////////////////////////////////////////////////////
// CVertCurve

HRESULT CVertCurve::FinalConstruct()
{
   CComObject<CProfilePointFactory>* pFactory;
   CComObject<CProfilePointFactory>::CreateInstance(&pFactory);
   m_Factory = pFactory;
   m_Factory->putref_Profile(m_pProfile);

   m_Factory->CreateProfilePoint(&m_PBG);
   m_Factory->CreateProfilePoint(&m_PVI);
   m_Factory->CreateProfilePoint(&m_PFG);

   m_Factory->CreateProfilePoint(&m_BVC);
   m_Factory->CreateProfilePoint(&m_EVC);

   m_vbComputeFromGrades = VARIANT_FALSE;
   m_bIsDirty = true;

   m_L1 = 0.0;
   m_L2 = 0.0;
   m_g1 = 0.0;
   m_g2 = 0.0;

   m_PBG->put_Station(CComVariant(0.00));
   m_PBG->put_Elevation(0.00);

   m_BVC->put_Station(CComVariant(0.00));
   m_BVC->put_Elevation(0.00);

   m_PVI->put_Station(CComVariant(m_L1));
   m_PVI->put_Elevation(0.00);

   m_EVC->put_Station(CComVariant(m_L1 + m_L2));
   m_EVC->put_Elevation(0.00);
   
   m_PFG->put_Station(CComVariant(m_L1 + m_L2));
   m_PFG->put_Elevation(0.00);

   return S_OK;
}

void CVertCurve::FinalRelease()
{
}

STDMETHODIMP CVertCurve::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IVertCurve,
      &IID_IStructuredStorage2
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

STDMETHODIMP CVertCurve::get_ComputeFromGradePoints(VARIANT_BOOL* pvbCompute)
{
   CHECK_RETVAL(pvbCompute);
   *pvbCompute = m_vbComputeFromGrades;
   return S_OK;
}

STDMETHODIMP CVertCurve::put_ComputeFromGradePoints(VARIANT_BOOL vbCompute)
{
   m_vbComputeFromGrades = vbCompute;
   MakeDirty();
   return S_OK;
}

STDMETHODIMP CVertCurve::get_Profile(IProfile* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pProfile )
   {
      (*pVal) = m_pProfile;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CVertCurve::put_Profile(IProfile* newVal)
{
   m_pProfile = newVal;
   m_Factory->putref_Profile(m_pProfile);
   m_PBG->putref_Profile(m_pProfile);
   m_BVC->putref_Profile(m_pProfile);
   m_PVI->putref_Profile(m_pProfile);
   m_EVC->putref_Profile(m_pProfile);
   m_PFG->putref_Profile(m_pProfile);
   MakeDirty();

   return S_OK;
}

STDMETHODIMP CVertCurve::get_PBG(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   return m_PBG.CopyTo(pVal);
}

STDMETHODIMP CVertCurve::putref_PBG(IProfilePoint *newVal)
{
   CHECK_IN(newVal);

   HRESULT hr = ValidateStation(newVal);
   if ( FAILED(hr) )
   {
      return hr;
   }

   m_PBG->putref_Profile(nullptr);
   m_PBG = newVal;
   m_PBG->putref_Profile(m_pProfile);

   MakeDirty();

   return S_OK;
}

STDMETHODIMP CVertCurve::get_PVI(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_vbComputeFromGrades == VARIANT_TRUE )
   {
      UPDATE_CURVE;
   }
   return m_PVI.CopyTo(pVal);
}

STDMETHODIMP CVertCurve::putref_PVI(IProfilePoint *newVal)
{
   CHECK_IN(newVal);

   HRESULT hr = ValidateStation(newVal);
   if ( FAILED(hr) )
   {
      return hr;
   }

   m_PVI->putref_Profile(nullptr);
   m_PVI = newVal;
   m_PVI->putref_Profile(m_pProfile);
   
   MakeDirty();

   return S_OK;
}

STDMETHODIMP CVertCurve::get_PFG(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   return m_PFG.CopyTo(pVal);
}

STDMETHODIMP CVertCurve::putref_PFG(IProfilePoint *newVal)
{
   CHECK_IN(newVal);

   HRESULT hr = ValidateStation(newVal);
   if ( FAILED(hr) )
   {
      return hr;
   }

   m_PFG->putref_Profile(nullptr);
   m_PFG = newVal;
   m_PFG->putref_Profile(m_pProfile);

   MakeDirty();

   return S_OK;
}

STDMETHODIMP CVertCurve::get_L1(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   UPDATE_CURVE;
   (*pVal) = m_L1;
   return S_OK;
}

STDMETHODIMP CVertCurve::put_L1(Float64 newVal)
{
   if ( newVal < 0.0 )
   {
      return E_INVALIDARG;
   }

   m_L1 = newVal;
   MakeDirty();

   return S_OK;
}


STDMETHODIMP CVertCurve::get_L2(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   UPDATE_CURVE;
   (*pVal) = m_L2;
   return S_OK;
}

STDMETHODIMP CVertCurve::put_L2(Float64 newVal)
{
   if ( newVal < 0.0 )
   {
      return E_INVALIDARG;
   }

   m_L2 = newVal;
   MakeDirty();

   return S_OK;
}

STDMETHODIMP CVertCurve::get_BVC(IProfilePoint* *pVal)
{
   CHECK_RETOBJ(pVal);
   UPDATE_CURVE;
   return m_BVC.CopyTo(pVal);
}

STDMETHODIMP CVertCurve::get_EVC(IProfilePoint* *pVal)
{
   CHECK_RETOBJ(pVal);
   UPDATE_CURVE;
   return m_EVC.CopyTo(pVal);
}

STDMETHODIMP CVertCurve::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   UPDATE_CURVE;
   (*pVal) = m_L1 + m_L2;
   return S_OK;
}

STDMETHODIMP CVertCurve::put_EntryGrade(Float64 newVal)
{
   m_g1 = newVal;
   MakeDirty();

   return S_OK;
}

STDMETHODIMP CVertCurve::get_EntryGrade(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   UPDATE_CURVE;
   *pVal = m_g1;
   return S_OK;
}

STDMETHODIMP CVertCurve::put_ExitGrade(Float64 newVal)
{
   m_g2 = newVal;
   MakeDirty();

   return S_OK;
}

STDMETHODIMP CVertCurve::get_ExitGrade(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   UPDATE_CURVE;
   *pVal = m_g2;
   return S_OK;
}

STDMETHODIMP CVertCurve::get_LowPoint(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   UPDATE_CURVE;

   if ( IsZero(m_L1) && IsZero(m_L2) )
   {
      // this curve is has no length so it is just a profile point
      CComPtr<IStation> staPVI;
      Float64 elevPVI;
      m_PVI->get_Station(&staPVI);
      m_PVI->get_Elevation(&elevPVI);

      m_Factory->CreateProfilePoint(pVal);
      (*pVal)->put_Station(CComVariant(staPVI));
      (*pVal)->put_Elevation(elevPVI);
      return S_OK;
   }

   CComPtr<IProfilePoint> bvc;
   get_BVC(&bvc);

   CComPtr<IStation> staBVC;
   Float64 elevBVC;
   bvc->get_Station(&staBVC);
   bvc->get_Elevation(&elevBVC);

   CComPtr<IStation> staPVI;
   Float64 elevPVI;
   m_PVI->get_Station(&staPVI);
   m_PVI->get_Elevation(&elevPVI);

   CComPtr<IProfilePoint> evc;
   get_EVC(&evc);
   CComPtr<IStation> staEVC;
   Float64 elevEVC;
   evc->get_Station(&staEVC);
   evc->get_Elevation(&elevEVC);

   Float64 g1, g2;
   get_EntryGrade(&g1);
   get_ExitGrade(&g2);

   CComPtr<IStation> staTrans;
   Float64 elevTrans, gTrans; // transition point
   TransitionPoint(&staTrans,&elevTrans,&gTrans);

   // Low point on left curve
   Float64 bvcValue = cogoUtil::GetNormalizedStationValue(m_pProfile,staBVC);
   Float64 transValue = cogoUtil::GetNormalizedStationValue(m_pProfile,staTrans);
   Float64 xLeft = -g1*m_L1/(gTrans - g1) + bvcValue;
   Float64 yLeft;
   if ( bvcValue < xLeft && xLeft < transValue )
   {
      // low point is on the curve
      Elevation(CComVariant(xLeft),&yLeft);
   }
   else
   {
      // low point is off the curve, check the ends
      if ( elevTrans < elevBVC )
      {
         xLeft = transValue;
         yLeft = elevTrans;
      }
      else
      {
         xLeft = bvcValue;
         yLeft = elevBVC;
      }
   }

   // Low point on right curve
   Float64 evcValue = cogoUtil::GetNormalizedStationValue(m_pProfile,staEVC);
   Float64 xRight = -gTrans*m_L2/(g2 - gTrans) + transValue;
   Float64 yRight;
   if ( transValue < xRight && xRight < evcValue )
   {
      // low point is on the curve
      Elevation(CComVariant(xRight),&yRight);
   }
   else
   {
      // low point is off the curve, check the ends
      if ( elevTrans < elevEVC )
      {
         xRight = transValue;;
         yRight = elevTrans;
      }
      else
      {
         xRight = evcValue;
         yRight = elevEVC;
      }
   }

   m_Factory->CreateProfilePoint(pVal);
   if ( yLeft < yRight )
   {
      CComPtr<IStation> station;
      cogoUtil::CreateStation(m_pProfile,xLeft,&station);
      (*pVal)->put_Station(CComVariant(station));
      (*pVal)->put_Elevation(yLeft);
   }
   else
   {
      CComPtr<IStation> station;
      cogoUtil::CreateStation(m_pProfile,xRight,&station);
      (*pVal)->put_Station(CComVariant(station));
      (*pVal)->put_Elevation(yRight);
   }

   return S_OK;
}

STDMETHODIMP CVertCurve::get_HighPoint(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   UPDATE_CURVE;

   if ( IsZero(m_L1) && IsZero(m_L2) )
   {
      // this curve is has no length so it is just a profile point
      CComPtr<IStation> staPVI;
      Float64 elevPVI;
      m_PVI->get_Station(&staPVI);
      m_PVI->get_Elevation(&elevPVI);

      m_Factory->CreateProfilePoint(pVal);
      (*pVal)->put_Station(CComVariant(staPVI));
      (*pVal)->put_Elevation(elevPVI);
      return S_OK;
   }

   CComPtr<IProfilePoint> bvc;
   get_BVC(&bvc);

   CComPtr<IStation> staBVC;
   Float64 elevBVC;
   bvc->get_Station(&staBVC);
   bvc->get_Elevation(&elevBVC);

   CComPtr<IStation> staPVI;
   Float64 elevPVI;
   m_PVI->get_Station(&staPVI);
   m_PVI->get_Elevation(&elevPVI);

   CComPtr<IProfilePoint> evc;
   get_EVC(&evc);

   CComPtr<IStation> staEVC;
   Float64 elevEVC;
   evc->get_Station(&staEVC);
   evc->get_Elevation(&elevEVC);

   Float64 g1, g2;
   get_EntryGrade(&g1);
   get_ExitGrade(&g2);

   CComPtr<IStation> staTrans;
   Float64 elevTrans, gTrans; // transition point
   TransitionPoint(&staTrans,&elevTrans,&gTrans);

   // High point on left curve
   Float64 bvcValue = cogoUtil::GetNormalizedStationValue(m_pProfile,staBVC);
   Float64 transValue = cogoUtil::GetNormalizedStationValue(m_pProfile,staTrans);
   Float64 xLeft = -g1*m_L1/(gTrans - g1) + bvcValue;
   Float64 yLeft;
   if ( bvcValue < xLeft && xLeft < transValue )
   {
      // high point is on the curve
      Elevation(CComVariant(xLeft),&yLeft);
   }
   else
   {
      // high point is off the curve, check the extreme ends
      if ( elevTrans > elevBVC )
      {
         xLeft = transValue;
         yLeft = elevTrans;
      }
      else
      {
         xLeft = bvcValue;
         yLeft = elevBVC;
      }
   }

   // High point on right curve
   Float64 evcValue = cogoUtil::GetNormalizedStationValue(m_pProfile,staEVC);
   Float64 xRight = -gTrans*m_L2/(g2 - gTrans) + transValue;
   Float64 yRight;
   if ( transValue < xRight && xRight < evcValue )
   {
      // high point is on the curve
      Elevation(CComVariant(xRight),&yRight);
   }
   else
   {
      // high point is off the curve, check the extreme ends
      if ( elevEVC < elevTrans )
      {
         xRight = transValue;
         yRight = elevTrans;
      }
      else
      {
         xRight = evcValue;
         yRight = elevEVC;
      }
   }

   m_Factory->CreateProfilePoint(pVal);
   if ( yRight <= yLeft )
   {
      CComPtr<IStation> station;
      cogoUtil::CreateStation(m_pProfile,xLeft,&station);
      (*pVal)->put_Station(CComVariant(station));
      (*pVal)->put_Elevation(yLeft);
   }
   else
   {
      CComPtr<IStation> station;
      cogoUtil::CreateStation(m_pProfile,xRight,&station);
      (*pVal)->put_Station(CComVariant(station));
      (*pVal)->put_Elevation(yRight);
   }

   return S_OK;
}

STDMETHODIMP CVertCurve::Elevation(VARIANT varStation, Float64 *elev)
{
   CHECK_RETVAL(elev);
   UPDATE_CURVE;

   CComPtr<IStation> sta;
   HRESULT hr = ValidateStation(varStation,&sta);
   if ( FAILED(hr) )
   {
      return hr;
   }
   Float64 staValue = cogoUtil::GetNormalizedStationValue(m_pProfile,sta);

   Float64 g1, g2;
   get_EntryGrade(&g1);
   get_ExitGrade(&g2);


   if ( IsZero(m_L1) && IsZero(m_L2) )
   {
      // this curve is has no length so it is just a profile point
      CComPtr<IStation> staPVI;
      Float64 elevPVI;
      m_PVI->get_Station(&staPVI);
      m_PVI->get_Elevation(&elevPVI);
      Float64 pviValue = cogoUtil::GetNormalizedStationValue(m_pProfile,staPVI);

      if ( IsEqual(pviValue,staValue) )
      {
         *elev = elevPVI;
      }
      else if ( staValue < pviValue )
      {
         // Before curve
         *elev = elevPVI - g1*(pviValue - staValue);
      }
      else if ( pviValue < staValue )
      {
         // After curve
         *elev = elevPVI + g2*(staValue - pviValue);
      }
      else
      {
         ATLASSERT(false); // should not get here
      }

      return S_OK;
   }

   CComPtr<IProfilePoint> bvc;
   get_BVC(&bvc);

   CComPtr<IStation> staBVC;
   Float64 elevBVC;
   bvc->get_Station(&staBVC);
   bvc->get_Elevation(&elevBVC);
   Float64 bvcValue = cogoUtil::GetNormalizedStationValue(m_pProfile,staBVC);

   CComPtr<IProfilePoint> evc;
   get_EVC(&evc);

   CComPtr<IStation> staEVC;
   Float64 elevEVC;
   evc->get_Station(&staEVC);
   evc->get_Elevation(&elevEVC);
   Float64 evcValue = cogoUtil::GetNormalizedStationValue(m_pProfile,staEVC);

   if ( staValue < bvcValue )
   {
      // Before curve
      *elev = elevBVC - g1*(bvcValue - staValue);
   }
   else if ( evcValue < staValue )
   {
      // After curve
      *elev = elevEVC + g2*(staValue - evcValue);
   }
   else
   {
      // On curve
      CComPtr<IStation> staTrans;
      Float64 elevTrans, gradeTrans; // transition point
      TransitionPoint(&staTrans,&elevTrans,&gradeTrans);
      Float64 transValue = cogoUtil::GetNormalizedStationValue(m_pProfile,staTrans);

      if ( staValue < transValue )
      {
         // station is left of PVI
         Float64 x = staValue - bvcValue;
         Float64 L = transValue - bvcValue;
         Float64 y;
         if ( IsZero(L) )
         {
            y = elevBVC;
         }
         else
         {
            y = (gradeTrans-g1)*pow(x,2)/(2*L) + g1*x + elevBVC;
         }
         *elev = y;
      }
      else
      {
         // station is right of PVI
         Float64 x = staValue - transValue;
         Float64 L = evcValue - transValue;
         Float64 y;
         if ( IsZero(L) )
         {
            y = elevTrans;
         }
         else
         {
            y = (g2-gradeTrans)*pow(x,2)/(2*L) + gradeTrans*x + elevTrans;
         }

         *elev = y;
      }
   }

   return S_OK;
}

STDMETHODIMP CVertCurve::Grade(VARIANT varStation, Float64 *grade)
{
   CHECK_RETVAL(grade);
   UPDATE_CURVE;

   CComPtr<IStation> sta;
   HRESULT hr = ValidateStation(varStation,&sta);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 g1, g2;
   get_EntryGrade(&g1);
   get_ExitGrade(&g2);

   if ( IsZero(m_L1) && IsZero(m_L2) )
   {
      // this curve is has no length so it is just a profile point
      CComPtr<IStation> staPVI;
      m_PVI->get_Station(&staPVI);

      if ( 0 < cogoUtil::Compare(m_pProfile,sta,staPVI) )
      {
         // Before curve
         *grade = g1;
      }
      else if ( 0 < cogoUtil::Compare(m_pProfile,staPVI,sta) )
      {
         // After curve
         *grade = g2;
      }
      else
      {
         // exactly at PVI
         *grade = g1;
      }

      return S_OK;
   }


   CComPtr<IProfilePoint> bvc;
   get_BVC(&bvc);

   CComPtr<IStation> staBVC;
   Float64 elevBVC;
   bvc->get_Station(&staBVC);
   bvc->get_Elevation(&elevBVC);

   CComPtr<IProfilePoint> evc;
   get_EVC(&evc);

   CComPtr<IStation> staEVC;
   Float64 elevEVC;
   evc->get_Station(&staEVC);
   evc->get_Elevation(&elevEVC);

   if ( 0 < cogoUtil::Compare(m_pProfile,sta,staBVC) )
   {
      // Before curve
      *grade = g1;
   }
   else if ( 0 < cogoUtil::Compare(m_pProfile,staEVC,sta) )
   {
      // After curve
      *grade = g2;
   }
   else
   {
      // On curve
      CComPtr<IStation> staTrans;
      Float64 elevTrans, gradeTrans; // transition point
      TransitionPoint(&staTrans,&elevTrans,&gradeTrans);

      if ( 0 < cogoUtil::Compare(m_pProfile,sta,staTrans) )
      {
         // station is left of PVI
         Float64 x = cogoUtil::Distance(m_pProfile,staBVC,sta);
         Float64 L = cogoUtil::Distance(m_pProfile,staBVC,staTrans);
         Float64 g = (gradeTrans-g1)*x/L + g1;
         *grade = g;
      }
      else
      {
         // station is right of PVI
         Float64 x = cogoUtil::Distance(m_pProfile,staTrans,sta);
         Float64 L = cogoUtil::Distance(m_pProfile,staTrans,staEVC);
         Float64 g = (g2-gradeTrans)*x/L + gradeTrans;
         *grade = g;
      }
   }

   return S_OK;
}

STDMETHODIMP CVertCurve::get_ProfilePointFactory(IProfilePointFactory* *factory)
{
   CHECK_RETOBJ(factory);
   (*factory) = m_Factory;
   (*factory)->AddRef();
   return S_OK;
}

STDMETHODIMP CVertCurve::putref_ProfilePointFactory(IProfilePointFactory* factory)
{
   CHECK_IN(factory);
   m_Factory = factory;
   return S_OK;
}

STDMETHODIMP CVertCurve::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

STDMETHODIMP CVertCurve::get_A(Float64* a)
{
   CHECK_RETVAL(a);
   Float64 g1, g2;
   get_EntryGrade(&g1);
   get_ExitGrade(&g2);
   *a = g2 - g1;
   return S_OK;
}

STDMETHODIMP CVertCurve::get_K1(Float64* k)
{
   CHECK_RETVAL(k);
   Float64 L1, L2;
   get_L1(&L1);
   get_L2(&L2);

   if (IsZero(L2) || IsEqual(L1, L2))
   {
      // curve is symmetric
      Float64 a;
      get_A(&a);

      Float64 L = L1 + L2;
      *k = IsZero(L) ? DBL_MAX : a / L;
   }
   else
   {
      // curve is unsymmetric
      CComPtr<IStation> station;
      Float64 elev;
      Float64 grade;
      TransitionPoint(&station, &elev, &grade);

      Float64 entry_grade;
      get_EntryGrade(&entry_grade);

      Float64 a = grade - entry_grade;
      *k = a / L1;
   }

   return S_OK;
}

STDMETHODIMP CVertCurve::get_K2(Float64* k)
{
   CHECK_RETVAL(k);
   Float64 L1, L2;
   get_L1(&L1);
   get_L2(&L2);

   if (IsZero(L2) || IsEqual(L1, L2))
   {
      // curve is symmetric
      return get_K1(k);
   }
   else
   {
      CComPtr<IStation> station;
      Float64 elev;
      Float64 grade;
      TransitionPoint(&station, &elev, &grade);

      Float64 exit_grade;
      get_ExitGrade(&exit_grade);

      Float64 a = exit_grade - grade;
      *k = a / L1;
   }

   return S_OK;
}

STDMETHODIMP CVertCurve::get_H(Float64* h)
{
   CHECK_RETVAL(h);

   Float64 L1, L2;
   get_L1(&L1);
   get_L2(&L2);

   if ( L1 + L2 == 0 )
   {
      *h = 0;
      return S_OK;
   }

   Float64 a;
   get_A(&a);

   *h = (L1*L2*a)/(2*(L1+L2));
   return S_OK;
}

STDMETHODIMP CVertCurve::get_E(Float64 t,Float64* e)
{
   CHECK_RETVAL(e);

   Float64 L1, L2;
   get_L1(&L1);
   get_L2(&L2);

   Float64 h;
   get_H(&h);

   if ( IsZero(h) )
   {
      *e = 0;
      return S_OK;
   }

   if (t < L1)
   {
      *e = h*pow(t/L1,2);
   }
   else
   {
      // get t from end of curve
      t = (L1 + L2 - t);
      *e = h*pow(t/L2,2);
   }

   return S_OK;
}

STDMETHODIMP CVertCurve::Clone(IVertCurve* *clone)
{
   CHECK_RETOBJ(clone);
   UPDATE_CURVE;

   CComObject<CVertCurve>* pClone;
   CComObject<CVertCurve>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->put_ComputeFromGradePoints(m_vbComputeFromGrades);
   if ( m_vbComputeFromGrades == VARIANT_TRUE )
   {
      CComPtr<IProfilePoint> pfgClone;
      m_PFG->Clone(&pfgClone);
      (*clone)->putref_PFG(pfgClone);

      CComPtr<IProfilePoint> pbgClone;
      m_PBG->Clone(&pbgClone);
      (*clone)->putref_PBG(pbgClone);

      (*clone)->put_EntryGrade(m_g1);
      (*clone)->put_ExitGrade(m_g2);
   }
   else
   {
      CComPtr<IProfilePoint> pfgClone;
      m_PFG->Clone(&pfgClone);
      (*clone)->putref_PFG(pfgClone);

      CComPtr<IProfilePoint> pviClone;
      m_PVI->Clone(&pviClone);
      (*clone)->putref_PVI(pviClone);

      CComPtr<IProfilePoint> pbgClone;
      m_PBG->Clone(&pbgClone);
      (*clone)->putref_PBG(pbgClone);

      (*clone)->put_L1(m_L1);
      (*clone)->put_L2(m_L2);
   }

   // These items aren't cloned
   (*clone)->putref_ProfilePointFactory(m_Factory);
   (*clone)->put_Profile(m_pProfile);

   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CVertCurve::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("VertCurve"),2.0);
   pSave->put_Property(CComBSTR("ComputeFromGrades"),CComVariant(m_vbComputeFromGrades));
   if ( m_vbComputeFromGrades == VARIANT_TRUE )
   {
      pSave->put_Property(CComBSTR("PBG"),CComVariant(m_PBG));
      pSave->put_Property(CComBSTR("PFG"),CComVariant(m_PFG));
      pSave->put_Property(CComBSTR("G1"),CComVariant(m_g1));
      pSave->put_Property(CComBSTR("G2"),CComVariant(m_g2));
   }
   else
   {
      pSave->put_Property(CComBSTR("PBG"),CComVariant(m_PBG));
      pSave->put_Property(CComBSTR("PVI"),CComVariant(m_PVI));
      pSave->put_Property(CComBSTR("PFG"),CComVariant(m_PFG));
      pSave->put_Property(CComBSTR("L1"),CComVariant(m_L1));
      pSave->put_Property(CComBSTR("L2"),CComVariant(m_L2));
   }

   pSave->put_Property(CComBSTR("ProfilePointFactory"),CComVariant(m_Factory));

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CVertCurve::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("VertCurve"));

   Float64 version;
   pLoad->get_Version(&version);

   if ( version < 2 )
   {
      m_vbComputeFromGrades = VARIANT_FALSE;
   }
   else
   {
      pLoad->get_Property(CComBSTR("ComputeFromGrades"),&var);
      m_vbComputeFromGrades = var.boolVal;
   }

   if ( m_vbComputeFromGrades == VARIANT_TRUE )
   {
      pLoad->get_Property(CComBSTR("PBG"),&var);
      CComPtr<IProfilePoint> pbg;
      _CopyVariantToInterface<IProfilePoint>::copy(&pbg,&var);
      putref_PBG(pbg);

      pLoad->get_Property(CComBSTR("PFG"),&var);
      CComPtr<IProfilePoint> pfg;
      _CopyVariantToInterface<IProfilePoint>::copy(&pfg,&var);
      putref_PFG(pfg);

      pLoad->get_Property(CComBSTR("G1"),&var);
      m_g1 = var.dblVal;

      pLoad->get_Property(CComBSTR("G2"),&var);
      m_g2 = var.dblVal;
   }
   else
   {
      pLoad->get_Property(CComBSTR("PBG"),&var);
      CComPtr<IProfilePoint> pbg;
      _CopyVariantToInterface<IProfilePoint>::copy(&pbg,&var);
      putref_PBG(pbg);

      pLoad->get_Property(CComBSTR("PVI"),&var);
      CComPtr<IProfilePoint> pvi;
      _CopyVariantToInterface<IProfilePoint>::copy(&pvi,&var);
      putref_PVI(pvi);

      pLoad->get_Property(CComBSTR("PFG"),&var);
      CComPtr<IProfilePoint> pfg;
      _CopyVariantToInterface<IProfilePoint>::copy(&pfg,&var);
      putref_PFG(pfg);

      pLoad->get_Property(CComBSTR("L1"),&var);
      m_L1 = var.dblVal;

      pLoad->get_Property(CComBSTR("L2"),&var);
      m_L2 = var.dblVal;
   }

   pLoad->get_Property(CComBSTR("ProfilePointFactory"),&var);
   CComPtr<IProfilePointFactory> factory;
   _CopyVariantToInterface<IProfilePointFactory>::copy(&factory,&var);
   putref_ProfilePointFactory(factory);

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

void CVertCurve::MakeDirty()
{
   m_bIsDirty = true;
}

HRESULT CVertCurve::Update()
{
   if ( !m_bIsDirty )
   {
      return S_OK;
   }

   HRESULT hr = IsValid();
   if ( FAILED(hr) )
   {
      return hr;
   }

   if ( m_vbComputeFromGrades == VARIANT_TRUE )
   {
      // Need to compute L1, L2, and PVI

      // BVC = PBG and EVC = PFG
      CComPtr<IStation> staPBG, staPFG;
      m_PBG->get_Station(&staPBG);
      m_PFG->get_Station(&staPFG);

      Float64 elevPBG, elevPFG;
      m_PBG->get_Elevation(&elevPBG);
      m_PFG->get_Elevation(&elevPFG);

      CComPtr<IStation> bvcStation, evcStation;
      staPBG->Clone(&bvcStation);
      staPFG->Clone(&evcStation);

      Float64 elevBVC = elevPBG;
      Float64 elevEVC = elevPFG;

      m_BVC->put_Station(CComVariant(bvcStation));
      m_BVC->put_Elevation(elevBVC);

      m_EVC->put_Station(CComVariant(evcStation));
      m_EVC->put_Elevation(elevEVC);


      Float64 staBVC = cogoUtil::GetNormalizedStationValue(m_pProfile,bvcStation);
      Float64 staEVC = cogoUtil::GetNormalizedStationValue(m_pProfile,evcStation);

      Float64 staPVI;
      if ( IsZero(m_g2-m_g1) )
      {
         // entry and exit grades are the same
         staPVI = (staBVC + staEVC)/2;
      }
      else
      {
         staPVI = ((elevBVC - elevEVC) + m_g2*(staEVC - staBVC))/(m_g2-m_g1) + staBVC;
      }
      m_L1 = staPVI - staBVC;
      m_L2 = staEVC - staPVI;
      
      // we need to be concerned with station equations so we just can't add m_L1 to
      // the BVC station... make PVI be a copy of BVC and then use the IncrementStationBy
      // method to compute the station of the PVI taking into account station equations
      CComPtr<IStation> station;
      staPBG->Clone(&station); // staPBG is at BVC
      cogoUtil::IncrementStationBy(m_pProfile,station,m_L1);
      m_PVI->put_Station(CComVariant(station));

      // compute the PVI elevation
      Float64 elevPVI = elevBVC + m_L1*m_g1;
      m_PVI->put_Elevation(elevPVI);

      if ( IsEqual(m_L1,m_L2) )
      {
         // symmetric curve
         m_L1 = m_L1 + m_L2;
         m_L2 = 0;
      }
   }
   else
   {
      // need to compute BVC, EVC, g1, and g2

      // Compute g1 and g2
      CComPtr<IStation> staPBG, staPVI, staPFG;
      m_PBG->get_Station(&staPBG);
      m_PVI->get_Station(&staPVI);
      m_PFG->get_Station(&staPFG);

      Float64 elevPBG, elevPVI, elevPFG;
      m_PBG->get_Elevation(&elevPBG);
      m_PVI->get_Elevation(&elevPVI);
      m_PFG->get_Elevation(&elevPFG);

      Float64 dx = cogoUtil::Distance(m_pProfile,staPBG,staPVI);
      Float64 dy = elevPVI - elevPBG;

      m_g1 = IsZero(dx) ? 0 : dy/dx;

      dx = cogoUtil::Distance(m_pProfile,staPVI,staPFG);
      dy = elevPFG - elevPVI;

      m_g2 = IsZero(dx) ? 0 : dy/dx;

      // Compute BVC and EVC
      Float64 staPVIValue = cogoUtil::GetNormalizedStationValue(m_pProfile,staPVI);

      Float64 l1 = m_L1;
      Float64 l2 = m_L2;
      if ( IsZero(m_L2) )
      {
         // curve is symmetric with m_L1 being the total length
         l1 /= 2;
         l2 = l1;
      }

      Float64 staBVC  = staPVIValue - l1;
      Float64 elevBVC = elevPVI - m_g1*l1;

      CComPtr<IStation> objBVC;
      cogoUtil::CreateStation(m_pProfile,staBVC,&objBVC);
      m_BVC->put_Station(CComVariant(objBVC));
      m_BVC->put_Elevation(elevBVC);

      Float64 staEVC = staPVIValue + l2;
      Float64 elevEVC = elevPVI + m_g2*l2;

      CComPtr<IStation> objEVC;
      cogoUtil::CreateStation(m_pProfile,staEVC,&objEVC);
      m_EVC->put_Station(CComVariant(objEVC));
      m_EVC->put_Elevation(elevEVC);
   }

   m_bIsDirty = false;

   return S_OK;
}

HRESULT CVertCurve::IsValid()
{
   if ( m_vbComputeFromGrades == VARIANT_TRUE )
   {
      if ( IsEqual(m_g1,m_g2) )
      {
         CComPtr<IStation> staPBG, staPFG;
         m_PBG->get_Station(&staPBG);
         m_PFG->get_Station(&staPFG);

         Float64 pbg = cogoUtil::GetNormalizedStationValue(m_pProfile,staPBG);
         Float64 pfg = cogoUtil::GetNormalizedStationValue(m_pProfile,staPFG);

         Float64 elevPBG, elevPFG;
         m_PBG->get_Elevation(&elevPBG);
         m_PFG->get_Elevation(&elevPFG);

         Float64 elev = elevPBG + m_g1*(pfg-pbg);
         if ( !IsEqual(elevPFG,elev) )
         {
            // Grade lines never intersect... g1 and g2 are the same so the
            // grades are parallel lines. The line going from PBG must
            // pass through PFG otherwise the profile is discontinuous and invalid
            return Error(IDS_E_VERTCURVEPOINTS,IID_IVertCurve,COGO_E_VERTCURVEPOINTS);
         }
      }
   }
   else
   {
      if ( IsZero(m_L1) && !IsZero(m_L2) )
      {
         // L2 must be zero if L1 is zero
         return Error(IDS_E_VERTCURVEPOINTS,IID_IVertCurve,COGO_E_VERTCURVEPOINTS);
      }

      CComPtr<IStation> staPBG, staPVI, staPFG;
      m_PBG->get_Station(&staPBG);
      m_PVI->get_Station(&staPVI);
      m_PFG->get_Station(&staPFG);

      Float64 pbg = cogoUtil::GetNormalizedStationValue(m_pProfile,staPBG);
      Float64 pvi = cogoUtil::GetNormalizedStationValue(m_pProfile,staPVI);
      Float64 pfg = cogoUtil::GetNormalizedStationValue(m_pProfile,staPFG);

      if ( pvi < pbg || pfg < pvi )
      {
         return Error(IDS_E_VERTCURVEPOINTS,IID_IVertCurve,COGO_E_VERTCURVEPOINTS);
      }
   }

   return S_OK;
}

void CVertCurve::TransitionPoint(IStation** sta,Float64* elev,Float64* grade)
{
   // Computes the station, elevation, and grade at the transition point
   // between the two vertical curves

   CComPtr<IStation> staBVC, staPVI, staEVC;
   Float64 elevBVC, elevPVI, elevEVC;

   CComPtr<IProfilePoint> bvc, evc;
   get_BVC(&bvc);
   get_EVC(&evc);

   bvc->get_Station(&staBVC);
   bvc->get_Elevation(&elevBVC);

   m_PVI->get_Station(&staPVI);
   m_PVI->get_Elevation(&elevPVI);

   evc->get_Station(&staEVC);
   evc->get_Elevation(&elevEVC);

   Float64 g1,g2;
   get_EntryGrade(&g1);
   get_ExitGrade(&g2);

   Float64 elevPVI1; // Elevation at intersection of g1 and grade at PVI
   elevPVI1 = elevBVC + g1*m_L1/2;

   Float64 h; // distance from PVI to curve
   if ( IsZero(m_L1+m_L2) )
   {
      h = 0;
   }
   else
   {
      h = m_L1*m_L2*(g2 - g1)/(2*(m_L1+m_L2)); // positive if sag curve
   }

   *elev = elevPVI + h;
   *sta  = staPVI;
   (*sta)->AddRef();

   if ( IsZero(m_L1) )
   {
      *grade = g1;
   }
   else
   {
      *grade = (*elev - elevPVI1)*2/m_L1;
   }
}

HRESULT CVertCurve::ValidateStation(IProfilePoint* profilePoint)
{
   CComPtr<IStation> station;
   profilePoint->get_Station(&station);
   CComPtr<IStation> sta;
   return ValidateStation(CComVariant(station),&sta);
}

HRESULT CVertCurve::ValidateStation(VARIANT varStation,IStation** station)
{
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,station);
   if ( FAILED(hr) )
   {
      return hr;
   }

   if ( m_pProfile == nullptr )
   {
      ZoneIndexType staEqnZoneIdx;
      (*station)->get_StationZoneIndex(&staEqnZoneIdx);
      if ( staEqnZoneIdx != INVALID_INDEX )
      {
         return E_INVALIDARG; // station must be normalized
      }
   }

   return S_OK;
}
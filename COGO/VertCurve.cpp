///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2011  Washington State Department of Transportation
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
#include "CogoHelpers.h"
#include <xutility> // for _cpp_min and _cpp_max
#include <limits>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CHECK_CURVE   HRESULT _hr = IsValid(); if ( FAILED(_hr) ) {return _hr;}

/////////////////////////////////////////////////////////////////////////////
// CVertCurve

HRESULT CVertCurve::FinalConstruct()
{
   CComObject<CProfilePointFactory>* pFactory;
   CComObject<CProfilePointFactory>::CreateInstance(&pFactory);
   m_Factory = pFactory;

   m_Factory->CreateProfilePoint(&m_PBG);
   m_Factory->CreateProfilePoint(&m_PVI);
   m_Factory->CreateProfilePoint(&m_PFG);

   MyAdvise(m_PBG,&m_dwPBG);
   MyAdvise(m_PVI,&m_dwPVI);
   MyAdvise(m_PFG,&m_dwPFG);

   m_L1 = 0.5;
   m_L2 = 0.5;

   m_PBG->put_Station(CComVariant(0.00));
   m_PBG->put_Elevation(0.00);

   m_PVI->put_Station(CComVariant(m_L1));
   m_PVI->put_Elevation(0.00);
   
   m_PFG->put_Station(CComVariant(m_L1 + m_L2));
   m_PFG->put_Elevation(0.00);

   return S_OK;
}

void CVertCurve::FinalRelease()
{
   MyUnadvise(m_PBG,m_dwPBG);
   MyUnadvise(m_PVI,m_dwPVI);
   MyUnadvise(m_PFG,m_dwPFG);
}

STDMETHODIMP CVertCurve::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IVertCurve,
      &IID_IStructuredStorage2
   };
   for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

STDMETHODIMP CVertCurve::get_PBG(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);

   (*pVal) = m_PBG;
   (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CVertCurve::putref_PBG(IProfilePoint *newVal)
{
   CHECK_IN(newVal);

   MyUnadvise(m_PBG,m_dwPBG);
   m_PBG = newVal;
   MyAdvise(m_PBG,&m_dwPBG);

   Fire_OnVertCurveChanged(this);

   return S_OK;
}

STDMETHODIMP CVertCurve::get_PVI(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);

   (*pVal) = m_PVI;
   (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CVertCurve::putref_PVI(IProfilePoint *newVal)
{
   CHECK_IN(newVal);

   MyUnadvise(m_PVI,m_dwPVI);
   m_PVI = newVal;
   MyAdvise(m_PVI,&m_dwPVI);

   Fire_OnVertCurveChanged(this);

   return S_OK;
}

STDMETHODIMP CVertCurve::get_PFG(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);

   (*pVal) = m_PFG;
   (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CVertCurve::putref_PFG(IProfilePoint *newVal)
{
   CHECK_IN(newVal);

   MyUnadvise(m_PFG,m_dwPFG);
   m_PFG = newVal;
   MyAdvise(m_PFG,&m_dwPFG);

   Fire_OnVertCurveChanged(this);

   return S_OK;
}

STDMETHODIMP CVertCurve::get_L1(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   (*pVal) = m_L1;
   return S_OK;
}

STDMETHODIMP CVertCurve::put_L1(Float64 newVal)
{
   if ( newVal <= 0.0 )
      return E_INVALIDARG;

   m_L1 = newVal;
   Fire_OnVertCurveChanged(this);
   return S_OK;
}


STDMETHODIMP CVertCurve::get_L2(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   (*pVal) = m_L2;
   return S_OK;
}

STDMETHODIMP CVertCurve::put_L2(Float64 newVal)
{
   if ( newVal <= 0.0 )
      return E_INVALIDARG;

   m_L2 = newVal;
   Fire_OnVertCurveChanged(this);
   return S_OK;
}

STDMETHODIMP CVertCurve::get_BVC(IProfilePoint* *pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 g1;
   get_EntryGrade(&g1);

   CComPtr<IStation> objPVI;
   Float64 elevPVI;
   m_PVI->get_Station(&objPVI);
   m_PVI->get_Elevation(&elevPVI);

   Float64 staPVI;
   objPVI->get_Value(&staPVI);

   Float64 staBVC;
   Float64 elevBVC;

   staBVC = staPVI - m_L1;
   elevBVC = elevPVI - g1*m_L1;

   m_Factory->CreateProfilePoint(pVal);
   (*pVal)->put_Station(CComVariant(staBVC));
   (*pVal)->put_Elevation(elevBVC);

   return S_OK;
}

STDMETHODIMP CVertCurve::get_EVC(IProfilePoint* *pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 g2;
   get_ExitGrade(&g2);

   CComPtr<IStation> objPVI;
   Float64 elevPVI;
   m_PVI->get_Station(&objPVI);
   m_PVI->get_Elevation(&elevPVI);

   Float64 staPVI;
   objPVI->get_Value(&staPVI);

   Float64 staEVC, elevEVC;

   staEVC = staPVI + m_L2;
   elevEVC = elevPVI + g2*m_L2;

   m_Factory->CreateProfilePoint(pVal);
   (*pVal)->put_Station(CComVariant(staEVC));
   (*pVal)->put_Elevation(elevEVC);

   return S_OK;
}

STDMETHODIMP CVertCurve::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   CHECK_CURVE;

   (*pVal) = m_L1 + m_L2;

   return S_OK;
}

STDMETHODIMP CVertCurve::get_EntryGrade(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   CHECK_CURVE;

   CComPtr<IStation> staPBG, staPVI;
   m_PBG->get_Station(&staPBG);
   m_PVI->get_Station(&staPVI);

   Float64 elePBG, elePVI;
   m_PBG->get_Elevation(&elePBG);
   m_PVI->get_Elevation(&elePVI);

   Float64 dx = staPVI - staPBG;
   Float64 dy = elePVI - elePBG;

   *pVal = dy/dx;

   return S_OK;
}

STDMETHODIMP CVertCurve::get_ExitGrade(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   CHECK_CURVE;

   CComPtr<IStation> staPVI, staPFG;
   m_PVI->get_Station(&staPVI);
   m_PFG->get_Station(&staPFG);

   Float64 elePVI, elePFG;
   m_PVI->get_Elevation(&elePVI);
   m_PFG->get_Elevation(&elePFG);

   Float64 dx = staPFG - staPVI;
   Float64 dy = elePFG - elePVI;

   *pVal = dy/dx;

   return S_OK;
}

STDMETHODIMP CVertCurve::get_LowPoint(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   CHECK_CURVE;

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
   Float64 bvcValue;
   staBVC->get_Value(&bvcValue);
   Float64 transValue;
   staTrans->get_Value(&transValue);
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
         staTrans->get_Value(&xLeft);
         yLeft = elevTrans;
      }
      else
      {
         staBVC->get_Value(&xLeft);
         yLeft = elevBVC;
      }
   }

   // Low point on right curve
   Float64 evcValue;
   staEVC->get_Value(&evcValue);
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
         staTrans->get_Value(&xRight);
         yRight = elevTrans;
      }
      else
      {
         staEVC->get_Value(&xRight);
         yRight = elevEVC;
      }
   }

   m_Factory->CreateProfilePoint(pVal);
   if ( yLeft < yRight )
   {
      (*pVal)->put_Station(CComVariant(xLeft));
      (*pVal)->put_Elevation(yLeft);
   }
   else
   {
      (*pVal)->put_Station(CComVariant(xRight));
      (*pVal)->put_Elevation(yRight);
   }

   return S_OK;
}

STDMETHODIMP CVertCurve::get_HighPoint(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   CHECK_CURVE;

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
   Float64 bvcValue;
   staBVC->get_Value(&bvcValue);
   Float64 transValue;
   staTrans->get_Value(&transValue);
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
   Float64 evcValue;
   staEVC->get_Value(&evcValue);
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
      if ( elevTrans > elevEVC )
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
      (*pVal)->put_Station(CComVariant(xLeft));
      (*pVal)->put_Elevation(yLeft);
   }
   else
   {
      (*pVal)->put_Station(CComVariant(xRight));
      (*pVal)->put_Elevation(yRight);
   }

   return S_OK;
}

STDMETHODIMP CVertCurve::Elevation(VARIANT varStation, Float64 *elev)
{
   CHECK_RETVAL(elev);
   CHECK_CURVE;

   CComPtr<IStation> sta;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,&sta);
   if ( FAILED(hr) )
      return hr;

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

   Float64 g1, g2;
   get_EntryGrade(&g1);
   get_ExitGrade(&g2);


   if ( sta < staBVC )
   {
      // Before curve
      *elev = elevBVC - g1*(staBVC - sta);
   }
   else if ( staEVC < sta )
   {
      // After curve
      *elev = elevEVC + g2*(sta - staEVC);
   }
   else
   {
      // On curve
      CComPtr<IStation> staTrans;
      Float64 elevTrans, gradeTrans; // transition point
      TransitionPoint(&staTrans,&elevTrans,&gradeTrans);

      if ( sta < staTrans )
      {
         // station is left of PVI
         Float64 x = sta - staBVC;
         Float64 L = staTrans - staBVC;
         Float64 y = (gradeTrans-g1)*pow(x,2)/(2*L) + g1*x + elevBVC;
         *elev = y;
      }
      else
      {
         // station is right of PVI
         Float64 x = sta - staTrans;
         Float64 L = staEVC - staTrans;
         Float64 y = (g2-gradeTrans)*pow(x,2)/(2*L) + gradeTrans*x + elevTrans;
         *elev = y;
      }
   }

   return S_OK;
}

STDMETHODIMP CVertCurve::Grade(VARIANT varStation, Float64 *grade)
{
   CHECK_RETVAL(grade);
   CHECK_CURVE;

   CComPtr<IStation> sta;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,&sta);
   if ( FAILED(hr) )
      return hr;

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

   Float64 g1, g2;
   get_EntryGrade(&g1);
   get_ExitGrade(&g2);


   if ( sta < staBVC )
   {
      // Before curve
      *grade = g1;
   }
   else if ( staEVC < sta )
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

      if ( sta < staTrans )
      {
         // station is left of PVI
         Float64 x = sta - staBVC;
         Float64 L = staTrans - staBVC;
         Float64 g = (gradeTrans-g1)*x/L + g1;
         *grade = g;
      }
      else
      {
         // station is right of PVI
         Float64 x = sta - staTrans;
         Float64 L = staEVC - staTrans;
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

STDMETHODIMP CVertCurve::get_K(Float64* k)
{
   CHECK_RETVAL(k);
   Float64 L;
   get_Length(&L);

   if ( L == 0 )
   {
      *k = DBL_MAX;
      return S_OK;
   }

   Float64 a;
   get_A(&a);


   *k = a/(2*L);
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

   CComObject<CVertCurve>* pClone;
   CComObject<CVertCurve>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

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

   // Factory isn't cloned
   (*clone)->putref_ProfilePointFactory(m_Factory);

   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CVertCurve::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("VertCurve"),1.0);
   pSave->put_Property(CComBSTR("PBG"),CComVariant(m_PBG));
   pSave->put_Property(CComBSTR("PVI"),CComVariant(m_PVI));
   pSave->put_Property(CComBSTR("PFG"),CComVariant(m_PFG));
   pSave->put_Property(CComBSTR("L1"),CComVariant(m_L1));
   pSave->put_Property(CComBSTR("L2"),CComVariant(m_L2));
   pSave->put_Property(CComBSTR("ProfilePointFactory"),CComVariant(m_Factory));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CVertCurve::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("VertCurve"));

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

   pLoad->get_Property(CComBSTR("ProfilePointFactory"),&var);
   CComPtr<IProfilePointFactory> factory;
   _CopyVariantToInterface<IProfilePointFactory>::copy(&factory,&var);
   putref_ProfilePointFactory(factory);
   


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

/////////////////////////////////////////////
// IProfilePointEvents
STDMETHODIMP CVertCurve::OnProfilePointChanged(IProfilePoint* pp)
{
//   ::MessageBox(NULL,"CVertCurve::OnProfilePointChanged","Event",MB_OK);
   Fire_OnVertCurveChanged(this);
   return S_OK;
}

//////////////////////////////////////////////
// Helper Methods
void CVertCurve::MyAdvise(IProfilePoint* pp,DWORD* pdwCookie)
{
   HRESULT hr = AtlAdvise(pp,GetUnknown(),IID_IProfilePointEvents,pdwCookie);
   if ( SUCCEEDED(hr) )
      InternalRelease();
   else
      *pdwCookie = 0;
}

void CVertCurve::MyUnadvise(IProfilePoint* pp,DWORD dwCookie)
{
   if ( dwCookie != 0 )
      InternalAddRef();

   AtlUnadvise(pp,IID_IProfilePointEvents,dwCookie);
}

HRESULT CVertCurve::IsValid()
{
   CComPtr<IStation> staPBG, staPVI, staPFG;
   m_PBG->get_Station(&staPBG);
   m_PVI->get_Station(&staPVI);
   m_PFG->get_Station(&staPFG);

   if ( staPBG < staPVI && staPVI < staPFG )
      return S_OK;

   return Error(IDS_E_VERTCURVEPOINTS,IID_IVertCurve,COGO_E_VERTCURVEPOINTS);
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
   h = m_L1*m_L2*(g2 - g1)/(2*(m_L1+m_L2)); // positive if sag curve

   *elev = elevPVI + h;
   *sta  = staPVI;
   (*sta)->AddRef();

   *grade = (*elev - elevPVI1)*2/m_L1;
}

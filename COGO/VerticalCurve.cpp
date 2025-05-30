///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2025  Washington State Department of Transportation
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

// VerticalCurve.cpp : Implementation of CVerticalCurve
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "VerticalCurve.h"
#include <WBFLCogo\CogoHelpers.h>


/////////////////////////////////////////////////////////////////////////////
// CVerticalCurve

HRESULT CVerticalCurve::FinalConstruct()
{
   m_Curve = WBFL::COGO::VerticalCurve::Create();
   m_pProfile = nullptr;
   return S_OK;
}

void CVerticalCurve::FinalRelease()
{
}

STDMETHODIMP CVerticalCurve::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IVerticalCurve,
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

STDMETHODIMP CVerticalCurve::Init(IProfilePoint* pPBT, IProfilePoint* pPVI, IProfilePoint* pPFT, Float64 L1, Float64 L2)
{
   CHECK_IN(pPBT);
   CHECK_IN(pPVI);
   CHECK_IN(pPFT);
   m_Curve->Init(*cogoUtil::GetInnerProfilePoint(pPBT), *cogoUtil::GetInnerProfilePoint(pPVI), *cogoUtil::GetInnerProfilePoint(pPFT), L1, L2);
   return S_OK;
}

STDMETHODIMP CVerticalCurve::Init2(IProfilePoint* pPBT, IProfilePoint* pPFT, Float64 g1, Float64 g2)
{
   CHECK_IN(pPBT);
   CHECK_IN(pPFT);
   m_Curve->Init(*cogoUtil::GetInnerProfilePoint(pPBT), *cogoUtil::GetInnerProfilePoint(pPFT), g1, g2);
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_Profile(IProfile* *pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_pProfile;
   (*pVal)->AddRef();
   return S_OK;
}

STDMETHODIMP CVerticalCurve::put_Profile(IProfile* newVal)
{
   m_pProfile = newVal;
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_PBG(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateProfilePoint(m_Curve->GetPBG(), pVal);
}

STDMETHODIMP CVerticalCurve::put_PBG(IProfilePoint *newVal)
{
   CHECK_IN(newVal);
   m_Curve->SetPBG(*cogoUtil::GetInnerProfilePoint(newVal));
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_PVI(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateProfilePoint(m_Curve->GetPVI(), pVal);
}

STDMETHODIMP CVerticalCurve::put_PVI(IProfilePoint *newVal)
{
   CHECK_IN(newVal);
   m_Curve->SetPVI(*cogoUtil::GetInnerProfilePoint(newVal));
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_PFG(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateProfilePoint(m_Curve->GetPFG(), pVal);
}

STDMETHODIMP CVerticalCurve::put_PFG(IProfilePoint *newVal)
{
   CHECK_IN(newVal);
   m_Curve->SetPFG(*cogoUtil::GetInnerProfilePoint(newVal));
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_L1(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Curve->GetL1();
   return S_OK;
}

STDMETHODIMP CVerticalCurve::put_L1(Float64 newVal)
{
   if ( newVal < 0.0 )
   {
      return E_INVALIDARG;
   }

   m_Curve->SetL1(newVal);
   return S_OK;
}


STDMETHODIMP CVerticalCurve::get_L2(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Curve->GetL2();
   return S_OK;
}

STDMETHODIMP CVerticalCurve::put_L2(Float64 newVal)
{
   if ( newVal < 0.0 )
   {
      return E_INVALIDARG;
   }

   m_Curve->SetL2(newVal);

   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_BVC(IProfilePoint* *pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateProfilePoint(m_Curve->GetBVC(), pVal);
}

STDMETHODIMP CVerticalCurve::get_EVC(IProfilePoint* *pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateProfilePoint(m_Curve->GetEVC(), pVal);
}


STDMETHODIMP CVerticalCurve::put_EntryGrade(Float64 newVal)
{
   m_Curve->SetEntryGrade(newVal);
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_EntryGrade(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Curve->GetEntryGrade();
   return S_OK;
}

STDMETHODIMP CVerticalCurve::put_ExitGrade(Float64 newVal)
{
   m_Curve->SetExitGrade(newVal);

   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_ExitGrade(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Curve->GetExitGrade();
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_LowPoint(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateProfilePoint(m_Curve->GetLowPoint(), pVal);
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_HighPoint(IProfilePoint **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateProfilePoint(m_Curve->GetHighPoint(), pVal);
}

STDMETHODIMP CVerticalCurve::Elevation(VARIANT varStation, Float64 *elev)
{
   CHECK_RETVAL(elev);

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   *elev = m_Curve->GetElevation(station);

   return S_OK;
}

STDMETHODIMP CVerticalCurve::Grade(VARIANT varStation, Float64 *grade)
{
   CHECK_RETVAL(grade);

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   *grade = m_Curve->GetGrade(station);
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_A(Float64* a)
{
   CHECK_RETVAL(a);
   *a = m_Curve->GetA();
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_K1(Float64* k)
{
   CHECK_RETVAL(k);
   *k = m_Curve->GetK1();
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_K2(Float64* k)
{
   CHECK_RETVAL(k);
   *k = m_Curve->GetK2();
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_H(Float64* h)
{
   CHECK_RETVAL(h);
   *h = m_Curve->GetH();
   return S_OK;
}

STDMETHODIMP CVerticalCurve::get_E(Float64 t, Float64* e)
{
   CHECK_RETVAL(e);
   *e = m_Curve->GetE(t);
   return S_OK;
}

// IProfileElement
// 
//STDMETHOD(Clone)(IProfileElement** clone) override;
STDMETHODIMP CVerticalCurve::GetStartPoint(IProfilePoint** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreateProfilePoint(m_Curve->GetBVC(),ppPoint);
}

STDMETHODIMP CVerticalCurve::GetEndPoint(IProfilePoint** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreateProfilePoint(m_Curve->GetEVC(), ppPoint);
}

STDMETHODIMP CVerticalCurve::GetLength(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   try
   {
      *pVal = m_Curve->GetLength();
   }
   catch (...)
   {
      return E_FAIL;
   }

   return S_OK;
}

STDMETHODIMP CVerticalCurve::ComputeGradeAndElevation(VARIANT varStation, Float64* pGrade, Float64* pElevation)
{
   CHECK_RETVAL(pGrade);
   CHECK_RETVAL(pElevation);

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   std::tie(*pGrade, *pElevation) = m_Curve->ComputeGradeAndElevation(station);
   return S_OK;
}

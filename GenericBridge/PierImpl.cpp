///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// PierImpl.cpp : Implementation of CPierImpl
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "PierImpl.h"
#include "ColumnLayout.h"
#include <Math\Math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPierImpl
HRESULT CPierImpl::FinalConstruct(IPier* pPier)
{
   m_bIsDirty = true;

   m_pPier = pPier;

   m_Type = ptIntegral;

   CComObject<CColumnLayout>* pColumnLayout;
   CComObject<CColumnLayout>::CreateInstance(&pColumnLayout);
   m_ColumnLayout = pColumnLayout;

   m_Skew.CoCreateInstance(CLSID_Angle);

   return S_OK;
}

void CPierImpl::SetItems(ICrossBeam* pCrossBeam,IBearingLayout* pBearingLayout,IColumnLayout* pLayout)
{
   m_CrossBeam.Release();
   m_BearingLayout.Release();
   m_ColumnLayout.Release();

   m_CrossBeam     = pCrossBeam;
   m_BearingLayout = pBearingLayout;
   m_ColumnLayout  = pLayout;

   m_bIsDirty = true;
}

Float64 CPierImpl::GetSkewAngle()
{
   Float64 value;
   m_Skew->get_Value(&value);
   return value;
}

Float64 CPierImpl::GetDelta()
{
   if ( m_bIsDirty )
   {
      // Delta is the difference in location between the left curb line and 
      // the left edge of cross beam. If delta is greater than zero the
      // curb line is left of the left edge of the cross beam.
      //
      // This delta value is used in coordinate transformations

      // Location of the alignment measured from the left edge of the cross beam
      ColumnIndexType refColIdx;
      Float64 refColOffset;
      m_ColumnLayout->GetReferenceColumn(&refColIdx,&refColOffset);
      Float64 Xcol;
      m_ColumnLayout->get_ColumnLocation(refColIdx,&Xcol);
      Float64 Xxb = Xcol - refColOffset;

      // Location of the alignment measured from the left curb line
      Float64 CLO;
      m_pPier->get_CurbLineOffset(qcbLeft,clmPlaneOfPier,&CLO); // in pier coordinates
      Float64 Xcl = -CLO; // in curb line coordinates

      m_Delta = Xcl - Xxb; // Xxb + delta = Xcl
      m_Delta = IsZero(m_Delta) ? 0 : m_Delta;

      CComQIPtr<ILinearCrossBeam> cb(m_CrossBeam);
      Float64 X2;
      cb->get_X2(&X2);
      m_Delta += X2;

      m_bIsDirty = false;
   }

   return m_Delta;
}

/////////////////////////////////////////////////////////////////////////////
// IPier - delegate
HRESULT  CPierImpl::put_Type(PierType type)
{
   m_Type = type;
   return S_OK;
}

HRESULT  CPierImpl::get_Type(PierType* type)
{
   CHECK_RETVAL(type);
   *type = m_Type;
   return S_OK;
}

HRESULT  CPierImpl::get_CurbToCurbWidth(CurbLineMeasurementType clMeasure,Float64* pWcc)
{
   CHECK_RETVAL(pWcc);
   Float64 LCO, RCO;
   m_pPier->get_CurbLineOffset(qcbLeft,clMeasure,&LCO);
   m_pPier->get_CurbLineOffset(qcbRight,clMeasure,&RCO);
   *pWcc = fabs(LCO) + fabs(RCO); // curb-curb width is unsigned, but offsets are signed... uses absolute value
   return S_OK;
}

HRESULT  CPierImpl::putref_SkewAngle(/*[in]*/IAngle* pSkew)
{
   CHECK_IN(pSkew);
   m_Skew = pSkew;
   return S_OK;
}

HRESULT  CPierImpl::get_SkewAngle(/*[out,retval]*/IAngle** ppSkew)
{
   CHECK_RETOBJ(ppSkew);
   return m_Skew.CopyTo(ppSkew);
}

HRESULT  CPierImpl::putref_CrossBeam(ICrossBeam* pCrossBeam)
{
   CHECK_IN(pCrossBeam);
   m_CrossBeam = pCrossBeam;
   m_CrossBeam->putref_Pier(m_pPier);
   return S_OK;
}

HRESULT  CPierImpl::get_CrossBeam(ICrossBeam** ppCrossBeam)
{
   CHECK_RETOBJ(ppCrossBeam);
   return m_CrossBeam.CopyTo(ppCrossBeam);
}

HRESULT  CPierImpl::putref_BearingLayout(IBearingLayout* pBearingLayout)
{
   CHECK_IN(pBearingLayout);
   m_BearingLayout = pBearingLayout;
   m_BearingLayout->putref_Pier(m_pPier);
   return S_OK;
}

HRESULT  CPierImpl::get_BearingLayout(IBearingLayout** ppBearingLayout)
{
   CHECK_RETOBJ(ppBearingLayout);
   return m_BearingLayout.CopyTo(ppBearingLayout);
}

HRESULT  CPierImpl::putref_ColumnLayout(IColumnLayout* pColumnLayout)
{
   CHECK_IN(pColumnLayout);
   m_ColumnLayout = pColumnLayout;
   m_ColumnLayout->putref_Pier(m_pPier);
   return S_OK;
}

HRESULT  CPierImpl::get_ColumnLayout(IColumnLayout** ppColumnLayout)
{
   CHECK_RETOBJ(ppColumnLayout);
   return m_ColumnLayout.CopyTo(ppColumnLayout);
}

HRESULT  CPierImpl::get_Column(ColumnIndexType columnIdx,IColumn* *column)
{
   return m_ColumnLayout->get_Column(columnIdx,column);
}

HRESULT  CPierImpl::ConvertCrossBeamToCurbLineCoordinate(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pXcl)
{
   CHECK_RETVAL(pXcl);
   Float64 delta = GetDelta();
   *pXcl = Xxb + delta;
   return S_OK;
}

HRESULT  CPierImpl::ConvertCurbLineToCrossBeamCoordinate(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pXxb)
{
   CHECK_RETVAL(pXxb);
   Float64 delta = GetDelta();
   *pXxb = Xcl - delta;
   return S_OK;
}

HRESULT  CPierImpl::ConvertPierToCrossBeamCoordinate(/*[in]*/Float64 Xp,/*[out,retval]*/Float64* pXxb)
{
   CHECK_RETVAL(pXxb);

   Float64 Xcl;
   HRESULT hr = ConvertPierToCurbLineCoordinate(Xp,&Xcl);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return ConvertCurbLineToCrossBeamCoordinate(Xcl,pXxb);
}

HRESULT  CPierImpl::ConvertCrossBeamToPierCoordinate(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pXp)
{
   CHECK_RETVAL(pXp);

   Float64 Xcl;
   HRESULT hr = ConvertCrossBeamToCurbLineCoordinate(Xxb,&Xcl);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return ConvertCurbLineToPierCoordinate(Xcl,pXp);
}

HRESULT  CPierImpl::ConvertPierToCurbLineCoordinate(/*[in]*/Float64 Xp,/*[out,retval]*/Float64* pXcl)
{
   CHECK_RETVAL(pXcl);
   Float64 leftCLO;
   HRESULT hr = m_pPier->get_CurbLineOffset(qcbLeft,clmPlaneOfPier,&leftCLO);
   if ( FAILED(hr) )
   {
      return hr;
   }
   *pXcl = Xp - leftCLO;
   return S_OK;
}

HRESULT  CPierImpl::ConvertCurbLineToPierCoordinate(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pXp)
{
   CHECK_RETVAL(pXp);
   Float64 leftCLO;
   HRESULT hr = m_pPier->get_CurbLineOffset(qcbLeft,clmPlaneOfPier,&leftCLO);
   if ( FAILED(hr) )
   {
      return hr;
   }
   *pXp = Xcl + leftCLO;
   return S_OK;
}

HRESULT  CPierImpl::get_CurbLineElevation(/*[in]*/DirectionType side,/*[out,retval]*/Float64* pElev)
{
   CHECK_RETVAL(pElev);

   WBFL::Math::PiecewiseFunction fn;
   CreateDeckProfileFunction(&fn);

   Float64 clo;
   HRESULT hr = m_pPier->get_CurbLineOffset(side,clmPlaneOfPier,&clo); // curb line offsets are in Pier coordinates
   if ( FAILED(hr) )
   {
      return hr;
   }

   *pElev = fn.Evaluate(clo);
   return S_OK;
}

HRESULT  CPierImpl::get_Elevation(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pElev)
{
   CHECK_RETVAL(pElev);

   WBFL::Math::PiecewiseFunction fn;
   CreateDeckProfileFunction(&fn);

   Float64 Xp;
   ConvertCurbLineToPierCoordinate(Xcl,&Xp); // the deck profile function is in pier coordinates
   *pElev = fn.Evaluate(Xp);
   return S_OK;
}

void CPierImpl::CreateDeckProfileFunction(WBFL::Math::PiecewiseFunction* pFN)
{
   CComPtr<IPoint2dCollection> deckProfile;
   m_pPier->get_DeckProfile(&deckProfile);

   CComPtr<IEnumPoint2d> enumPoints;
   deckProfile->get__Enum(&enumPoints);
   WBFL::Math::PiecewiseFunction fn;
   CComPtr<IPoint2d> pnt;
   while ( enumPoints->Next(1,&pnt,nullptr) != S_FALSE )
   {
      Float64 x,y;
      pnt->Location(&x,&y);
      pFN->AddPoint(x,y);
      pnt.Release();
   }
}

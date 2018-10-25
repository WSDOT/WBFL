///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPierImpl
HRESULT CPierImpl::FinalConstruct(IPier* pPier)
{
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
}

Float64 CPierImpl::GetSkewAngle()
{
   Float64 value;
   m_Skew->get_Value(&value);
   return value;
}

Float64 CPierImpl::GetDelta()
{
   // Location of the alignment measured from the left edge of the cross beam
   ColumnIndexType refColIdx;
   Float64 refColOffset;
   m_ColumnLayout->GetReferenceColumn(&refColIdx,&refColOffset);
   Float64 Xcol;
   m_ColumnLayout->get_ColumnLocation(refColIdx,&Xcol);
   Float64 Xxb = Xcol - refColOffset;

   // Location of the alignment measured from the left curb line
   Float64 CLO;
   m_pPier->get_CurbLineOffset(qcbLeft,&CLO); // in pier coordinates
   Float64 Xcl = -CLO; // in curb line coordinates

   Float64 delta = Xcl - Xxb; // Xxb + delta = Xcl
   return delta;
}

/////////////////////////////////////////////////////////////////////////////
// IPier
STDMETHODIMP CPierImpl::put_Type(PierType type)
{
   m_Type = type;
   return S_OK;
}

STDMETHODIMP CPierImpl::get_Type(PierType* type)
{
   CHECK_RETVAL(type);
   *type = m_Type;
   return S_OK;
}

STDMETHODIMP CPierImpl::putref_SkewAngle(/*[in]*/IAngle* pSkew)
{
   CHECK_IN(pSkew);
   m_Skew = pSkew;
   return S_OK;
}

STDMETHODIMP CPierImpl::get_SkewAngle(/*[out,retval]*/IAngle** ppSkew)
{
   CHECK_RETOBJ(ppSkew);
   return m_Skew.CopyTo(ppSkew);
}

STDMETHODIMP CPierImpl::putref_CrossBeam(ICrossBeam* pCrossBeam)
{
   CHECK_IN(pCrossBeam);
   m_CrossBeam = pCrossBeam;
   m_CrossBeam->putref_Pier(m_pPier);
   return S_OK;
}

STDMETHODIMP CPierImpl::get_CrossBeam(ICrossBeam** ppCrossBeam)
{
   CHECK_RETOBJ(ppCrossBeam);
   return m_CrossBeam.CopyTo(ppCrossBeam);
}

STDMETHODIMP CPierImpl::putref_BearingLayout(IBearingLayout* pBearingLayout)
{
   CHECK_IN(pBearingLayout);
   m_BearingLayout = pBearingLayout;
   m_BearingLayout->putref_Pier(m_pPier);
   return S_OK;
}

STDMETHODIMP CPierImpl::get_BearingLayout(IBearingLayout** ppBearingLayout)
{
   CHECK_RETOBJ(ppBearingLayout);
   return m_BearingLayout.CopyTo(ppBearingLayout);
}

STDMETHODIMP CPierImpl::putref_ColumnLayout(IColumnLayout* pColumnLayout)
{
   CHECK_IN(pColumnLayout);
   m_ColumnLayout = pColumnLayout;
   m_ColumnLayout->putref_Pier(m_pPier);
   return S_OK;
}

STDMETHODIMP CPierImpl::get_ColumnLayout(IColumnLayout** ppColumnLayout)
{
   CHECK_RETOBJ(ppColumnLayout);
   return m_ColumnLayout.CopyTo(ppColumnLayout);
}

STDMETHODIMP CPierImpl::get_Column(ColumnIndexType columnIdx,IColumn* *column)
{
   return m_ColumnLayout->get_Column(columnIdx,column);
}

STDMETHODIMP CPierImpl::ConvertCrossBeamToCurbLineCoordinate(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pXcl)
{
   CHECK_RETVAL(pXcl);
   Float64 delta = GetDelta();
   *pXcl = Xxb + delta;
   return S_OK;
}

STDMETHODIMP CPierImpl::ConvertCurbLineToCrossBeamCoordinate(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pXxb)
{
   CHECK_RETVAL(pXxb);
   Float64 delta = GetDelta();
   *pXxb = Xcl - delta;
   return S_OK;
}

STDMETHODIMP CPierImpl::ConvertPierToCrossBeamCoordinate(/*[in]*/Float64 Xp,/*[out,retval]*/Float64* pXxb)
{
   CHECK_RETVAL(pXxb);

   Float64 CPO; // distance from Alignment to Crown Point
   m_pPier->get_CrownPointOffset(&CPO);

   Float64 XclCrown;
   m_pPier->get_CrownPointLocation(&XclCrown); // location of the crown point in curb line coordinates

   Float64 XxbCrown;
   m_pPier->ConvertCurbLineToCrossBeamCoordinate(XclCrown,&XxbCrown); // location of crown point in XBeam coordinates

   Float64 delta = (XxbCrown - CPO); // CPO is in Pier Coordiantes.

   *pXxb = Xp + delta;
   return S_OK;
}

STDMETHODIMP CPierImpl::ConvertCrossBeamToPierCoordinate(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pXp)
{
   CHECK_RETVAL(pXp);

   Float64 CPO; // distance from Alignment to Crown Point
   m_pPier->get_CrownPointOffset(&CPO);

   Float64 XclCrown;
   m_pPier->get_CrownPointLocation(&XclCrown); // location of the crown point in curb line coordinates

   Float64 XxbCrown;
   m_pPier->ConvertCurbLineToCrossBeamCoordinate(XclCrown,&XxbCrown); // location of crown point in XBeam coordinates

   Float64 delta = (XxbCrown - CPO); // CPO is in Pier Coordiantes.

   *pXp = Xxb - delta;
   return S_OK;
}

STDMETHODIMP CPierImpl::get_CurbLineElevation(/*[in]*/DirectionType side,/*[out,retval]*/Float64* pElev)
{
   CHECK_RETVAL(*pElev);
   Float64 Xcp;
   m_pPier->get_CrownPointLocation(&Xcp);
   
   Float64 Ycp;
   m_pPier->get_CrownPointElevation(&Ycp);

   Float64 cpo;
   m_pPier->get_CrownPointOffset(&cpo);

   Float64 Ydeck;
   m_pPier->get_DeckElevation(&Ydeck);

   if ( side == qcbLeft )
   {
      Float64 sl;
      m_pPier->get_CrownSlope(qcbLeft,&sl);

      if ( 0 <= cpo )
      {
         Float64 leftCLO;
         m_pPier->get_CurbLineOffset(qcbLeft,&leftCLO);
         *pElev = Ydeck + leftCLO*sl;
      }
      else
      {
         *pElev = Ycp - sl*Xcp;
      }
   }
   else
   {
      Float64 sr;
      m_pPier->get_CrownSlope(qcbRight,&sr);
      Float64 leftCLO;
      m_pPier->get_CurbLineOffset(qcbLeft,&leftCLO);
      Float64 rightCLO;
      m_pPier->get_CurbLineOffset(qcbRight,&rightCLO);
      if ( 0 < cpo )
      {
         *pElev = Ycp + (rightCLO - leftCLO - Xcp)*sr;
      }
      else
      {
         *pElev = Ydeck + rightCLO*sr;
      }
   }

   return S_OK;
}

STDMETHODIMP CPierImpl::get_Elevation(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pElev)
{
   Float64 Xcp;
   m_pPier->get_CrownPointLocation(&Xcp);
   if ( Xcl < Xcp )
   {
      Float64 clElev;
      m_pPier->get_CurbLineElevation(qcbLeft,&clElev);

      Float64 sl;
      m_pPier->get_CrownSlope(qcbLeft,&sl);

      *pElev = clElev + Xcl*sl;
   }
   else
   {
      Float64 cpElev;
      m_pPier->get_CrownPointElevation(&cpElev);

      Float64 sr;
      m_pPier->get_CrownSlope(qcbRight,&sr);

      *pElev = cpElev + (Xcl - Xcp)*sr;
   }
   return S_OK;
}

STDMETHODIMP CPierImpl::get_CrownPointLocation(/*[out,retval]*/Float64* pXcl)
{
   // location of the crown point in Curb Line Coordinates
   CHECK_RETVAL(pXcl);
   Float64 skew = GetSkewAngle();
   Float64 cpo;
   m_pPier->get_CrownPointOffset(&cpo);
   Float64 clo;
   m_pPier->get_CurbLineOffset(qcbLeft,&clo);
   Float64 Xcp = cpo/cos(skew) - clo;
   *pXcl = Xcp;
   return S_OK;
}

STDMETHODIMP CPierImpl::get_CrownPointElevation(/*[out,retval]*/Float64* pElev)
{
   CHECK_RETVAL(pElev);

   Float64 Ydeck;
   m_pPier->get_DeckElevation(&Ydeck);

   Float64 cpo;
   m_pPier->get_CrownPointOffset(&cpo);

   *pElev = Ydeck;
   if ( 0 < cpo )
   {
      // crown point is to the right of the alignment
      Float64 sl;
      m_pPier->get_CrownSlope(qcbLeft,&sl);
      *pElev += cpo*sl;
   }
   else if ( cpo < 0 )
   {
      // crown point is to the left of the alignment
      Float64 sr;
      m_pPier->get_CrownSlope(qcbRight,&sr);
      *pElev += cpo*sr;
   }

   return S_OK;
}

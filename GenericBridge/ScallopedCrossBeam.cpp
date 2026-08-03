///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2026  Washington State Department of Transportation
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

// ScallopedCrossBeam.cpp : Implementation of CScallopedCrossBeam
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "ScallopedCrossBeam.h"
#include <ComException.h>
#include <Math\Math.h>


/////////////////////////////////////////////////////////////////////////////
// CScallopedCrossBeam
HRESULT CScallopedCrossBeam::FinalConstruct()
{
   m_H1L = 0;
   m_H1R = 0;
   m_HU = 0;
   m_X1L = 0;
   m_X1R = 0;
   m_W1 = 0;
   m_W2 = 0;
   m_R = 0;
   m_D = 0;

   HRESULT hr = m_RebarLayout.CoCreateInstance(CLSID_RebarLayout);
   if ( FAILED(hr) )
   {
      return hr;
   }

   m_UXBProfile.CoCreateInstance(CLSID_Point2dCollection);

   m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);

   return S_OK;
}

void CScallopedCrossBeam::FinalRelease()
{
}

void CScallopedCrossBeam::Invalidate()
{
   m_UXBProfile->Clear();
   m_LXBProfile.Release();
   m_BXBProfile.Release();

   m_bIsLXBDirty = true;
   m_bIsUXBDirty = true;
   m_bIsBXBDirty = true;
}

STDMETHODIMP CScallopedCrossBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICrossBeam,
      &IID_IScallopedCrossBeam,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//////////////////////////////////////////////////////
// ICrossBeam
STDMETHODIMP CScallopedCrossBeam::putref_Pier(IPier* pPier)
{
   CHECK_IN(pPier);
   m_pPier = pPier;
   Invalidate();
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_Pier(IPier** ppPier)
{
   CHECK_RETVAL(ppPier);
   if ( m_pPier )
   {
      *ppPier = m_pPier;
      (*ppPier)->AddRef();
   }
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_Length(XBeamLocation location, Float64* length)
{
   CHECK_RETVAL(length);

   Float64 loh, w, roh;
   CComPtr<IColumnLayout> columnLayout;
   m_pPier->get_ColumnLayout(&columnLayout);
   columnLayout->get_ColumnLayoutWidth(&w);
   columnLayout->get_Overhang(qcbLeft,&loh);
   columnLayout->get_Overhang(qcbRight,&roh);

   (*length) = loh + w + roh; // this is the length at the top of the lower cross beam

   if (location == xblTopLowerXBeam)
   {
      Float64 deltaXl, deltaXr;
      GetUpperXBeamDeltas(&deltaXl, &deltaXr);
      (*length) += deltaXl;
      (*length) -= deltaXr;
   }
   else if (location == xblBottomXBeam)
   {
      (*length) -= m_X1L + m_X1R;
   }

   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_Depth(/*[in]*/StageIndexType stageIdx,/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pDepth)
{
   CHECK_RETVAL(pDepth);

   // Create a function that represents the top of the lower cross beam
   Float64 Xoffset;
   Float64 x,y;

   // Adjust X-values so they are in XBeam coordinates (X=0 at bottom left of lower cross beam)
   CComPtr<IPoint2dCollection> bxbProfile;
   GetBottomXBeamProfile(&bxbProfile);
   CComPtr<IPoint2d> pnt;
   bxbProfile->get_Item(0,&pnt);
   pnt->get_X(&Xoffset);
   pnt.Release();

   CComPtr<IEnumPoint2d> enumPoints;
   bxbProfile->get__Enum(&enumPoints);
   WBFL::Math::PiecewiseFunction fnBottom;
   while ( enumPoints->Next(1,&pnt,nullptr) != S_FALSE )
   {
      pnt->Location(&x,&y);
      fnBottom.AddPoint(x-Xoffset,y);
      pnt.Release();
   }

   CComPtr<IPoint2dCollection> lxbProfile;
   GetLowerXBeamProfile(&lxbProfile);
   enumPoints.Release();
   lxbProfile->get__Enum(&enumPoints);
   WBFL::Math::PiecewiseFunction fnTop;
   while ( enumPoints->Next(1,&pnt,nullptr) != S_FALSE )
   {
      pnt->Location(&x,&y);
      fnTop.AddPoint(x-Xoffset,y);
      pnt.Release();
   }


   Float64 Y1 = fnTop.Evaluate(Xxb);
   Float64 Y2 = fnBottom.Evaluate(Xxb);

   Float64 H = Y1 - Y2; // depth of the lower cross beam
   *pDepth = H;

   PierType pierType;
   m_pPier->get_Type(&pierType);

   if ( 0 < stageIdx && pierType == ptIntegral )
   {
      *pDepth += m_HU;
   }

   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_FullDepth(Float64 Xxb,Float64* pDepth)
{
   HRESULT hr = get_Depth(0,Xxb,pDepth);
   if ( FAILED(hr) )
   {
      return hr;
   }

   (*pDepth) += m_HU;
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_Profile(/*[in]*/StageIndexType stageIdx,/*[out,retval]*/IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   CComPtr<IPoint2dCollection> txbProfile;
   if ( stageIdx == 0 )
   {
      // top profile is the top of the lower cross beam
      GetLowerXBeamProfile(&txbProfile);
   }
   else
   {
      // top profile is the top of the upper cross beam
      GetUpperXBeamProfile(&txbProfile);
   }

   CComPtr<IPoint2dCollection> bxbProfile;
   GetBottomXBeamProfile(&bxbProfile);
   bxbProfile->Reverse(); // points are left to right... reverse them so they are right to left

   CComPtr<IPolyShape> shape;
   shape.CoCreateInstance(CLSID_PolyShape);
   shape->AddPoints(txbProfile); // left to right across top of lower cross beam
   shape->AddPoints(bxbProfile); // right to left across bottom of lower cross beam

   shape.QueryInterface(ppShape);

   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_TopSurface(StageIndexType stageIdx,IPoint2dCollection** ppPoints)
{
   if ( stageIdx == 0 )
   {
      return GetLowerXBeamProfile(ppPoints);
   }
   else
   {
      return GetUpperXBeamProfile(ppPoints);
   }

   ATLASSERT(false); // should never get here
   return E_FAIL;
}

STDMETHODIMP CScallopedCrossBeam::get_BottomSurface(StageIndexType stageIdx,IPoint2dCollection** ppPoints)
{
   return GetBottomXBeamProfile(ppPoints);
}

STDMETHODIMP CScallopedCrossBeam::get_Surface(CrossBeamRebarDatum datum, Float64 offset, IPoint2dCollection** ppPoints)
{
   CComPtr<IPoint2dCollection> uxbProfile; // top of upper xbeam profile
   CComPtr<IPoint2dCollection> lxbProfile; // top of lower xbeam profile
   CComPtr<IPoint2dCollection> bxbProfile; // bottom of lower xbeam profile
   GetUpperXBeamProfile(&uxbProfile);
   GetLowerXBeamProfile(&lxbProfile);
   GetBottomXBeamProfile(&bxbProfile);

   switch (datum)
   {
   case xbTop:
      uxbProfile->Clone(ppPoints);
      break;

   case xbTopLowerXBeam:
      lxbProfile->Clone(ppPoints);
      break;

   case xbBottom:
      bxbProfile->Clone(ppPoints);
      ATLASSERT(0 <= offset); // there is no xbeam below the bottom
      break;

   default:
      ATLASSERT(false); // should never get here
   }

   (*ppPoints)->Offset(0, offset);

   // create clipping lines along the ends of the cross beam
   IndexType nPoints;
   CComPtr<IPoint2d> pntLeft1, pntLeft2;
   CComPtr<IPoint2d> pntRight1, pntRight2;

   uxbProfile->get_Item(0, &pntLeft1);
   bxbProfile->get_Item(0, &pntLeft2);

   uxbProfile->get_Count(&nPoints);
   uxbProfile->get_Item(nPoints - 1, &pntRight1);
   bxbProfile->get_Count(&nPoints);
   bxbProfile->get_Item(nPoints - 1, &pntRight2);

   CComPtr<ILineSegment2d> lsLeft;
   lsLeft.CoCreateInstance(CLSID_LineSegment2d);
   lsLeft->ThroughPoints(pntLeft1, pntLeft2);

   CComPtr<ILineSegment2d> lsRight;
   lsRight.CoCreateInstance(CLSID_LineSegment2d);
   lsRight->ThroughPoints(pntRight1, pntRight2);

   // create line segments from the first 2 and last 2 points of the offset profile line
   // and clip with end clipping lines

   // left side
   CComPtr<IPoint2d> pnt1, pnt2;
   (*ppPoints)->get_Item(0, &pnt1);
   (*ppPoints)->get_Item(1, &pnt2);

   CComPtr<IPoint2d> pnt1Clone, pnt2Clone;
   pnt1->Clone(&pnt1Clone);
   pnt2->Clone(&pnt2Clone);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);
   ls->ThroughPoints(pnt1Clone, pnt2Clone);

   CComPtr<IPoint2d> pntIntersect;
   if (m_GeomUtil->SegSegIntersect(lsLeft, ls, &pntIntersect) == S_OK)
   {
      // there was an intersection... replace the left point with
      // the intersection point
      (*ppPoints)->Remove(0);
      (*ppPoints)->Insert(0, pntIntersect);
   }

   // right side
   (*ppPoints)->get_Count(&nPoints);
   CComPtr<IPoint2d> pnt3, pnt4;
   (*ppPoints)->get_Item(nPoints - 2, &pnt3);
   (*ppPoints)->get_Item(nPoints - 1, &pnt4);

   CComPtr<IPoint2d> pnt3Clone, pnt4Clone;
   pnt3->Clone(&pnt3Clone);
   pnt4->Clone(&pnt4Clone);

   ls.Release();
   ls.CoCreateInstance(CLSID_LineSegment2d);
   ls->ThroughPoints(pnt3Clone, pnt4Clone);

   pntIntersect.Release();
   if (m_GeomUtil->SegSegIntersect(lsRight, ls, &pntIntersect) == S_OK)
   {
      // there was an intersection... replace the right point with
      // the intersection point
      (*ppPoints)->Remove(nPoints-1);
      (*ppPoints)->Insert(nPoints-1, pntIntersect);
   }

   (*ppPoints)->RemoveDuplicatePoints();

   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_BasicShape(Float64 Xxb,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   CComPtr<IShape> lowerXBeamShape;
   GetLowerXBeamShape(Xxb,&lowerXBeamShape);

   CComPtr<IShape> upperXBeamShape;
   GetUpperXBeamShape(Xxb,&upperXBeamShape);

   CComPtr<ICompositeShape> compositeShape;
   compositeShape.CoCreateInstance(CLSID_CompositeShape);
   compositeShape->AddShape(lowerXBeamShape,VARIANT_FALSE);
   compositeShape->AddShape(upperXBeamShape,VARIANT_FALSE);

   compositeShape->get_Shape(ppShape);

   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_Shape(StageIndexType stageIdx,Float64 Xxb,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   // Lower cross beam
   CComPtr<IShape> lowerXBeamShape;
   GetLowerXBeamShape(Xxb,&lowerXBeamShape);

   PierType pierType;
   m_pPier->get_Type(&pierType);

   if ( stageIdx == 0 || pierType != ptIntegral )
   {
      lowerXBeamShape.CopyTo(ppShape);
      return S_OK;
   }

   CComPtr<IShape> upperXBeamShape;
   GetUpperXBeamShape(Xxb,&upperXBeamShape);

   CComPtr<ICompositeShape> compositeShape;
   compositeShape.CoCreateInstance(CLSID_CompositeShape);
   compositeShape->AddShape(lowerXBeamShape,VARIANT_FALSE);
   compositeShape->AddShape(upperXBeamShape,VARIANT_FALSE);

   compositeShape->get_Shape(ppShape);

   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_RebarLayout(IRebarLayout** ppRebarLayout)
{
   CHECK_RETVAL(ppRebarLayout);
   return m_RebarLayout.CopyTo(ppRebarLayout);
}

STDMETHODIMP CScallopedCrossBeam::putref_RebarLayout(IRebarLayout* pRebarLayout)
{
   m_RebarLayout.Release();
   if ( pRebarLayout )
   {
      m_RebarLayout = pRebarLayout;
   }
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IScallopedCrossBeam implementation
STDMETHODIMP CScallopedCrossBeam::put_H1L(/*[in]*/Float64 H1L)
{
   if ( !IsEqual(m_H1L,H1L) )
   {
      m_H1L = H1L;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_H1L(/*[out,retval]*/Float64* pH1L)
{
   CHECK_RETVAL(pH1L);
   *pH1L = m_H1L;
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::put_H1R(/*[in]*/Float64 H1R)
{
   if ( !IsEqual(m_H1R,H1R) )
   {
      m_H1R = H1R;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_H1R(/*[out,retval]*/Float64* pH1R)
{
   CHECK_RETVAL(pH1R);
   *pH1R = m_H1R;
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::put_HU(/*[in]*/Float64 HU)
{
   if ( !IsEqual(m_HU,HU) )
   {
      m_HU = HU;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_HU(/*[out,retval]*/Float64* pHU)
{
   CHECK_RETVAL(pHU);
   *pHU = m_HU;
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::put_X1L(/*[in]*/Float64 X1L)
{
   if ( !IsEqual(m_X1L,X1L) )
   {
      m_X1L = X1L;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_X1L(/*[out,retval]*/Float64* pX1L)
{
   CHECK_RETVAL(pX1L);
   *pX1L = m_X1L;
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::put_X1R(/*[in]*/Float64 X1R)
{
   if ( !IsEqual(m_X1R,X1R) )
   {
      m_X1R = X1R;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_X1R(/*[out,retval]*/Float64* pX1R)
{
   CHECK_RETVAL(pX1R);
   *pX1R = m_X1R;
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::put_W1(/*[in]*/Float64 W1)
{
   if ( !IsEqual(m_W1,W1) )
   {
      m_W1 = W1;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_W1(/*[out,retval]*/Float64* pW1)
{
   CHECK_RETVAL(pW1);
   *pW1 = m_W1;
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::put_W2(/*[in]*/Float64 W2)
{
   if ( !IsEqual(m_W2,W2) )
   {
      m_W2 = W2;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_W2(/*[out,retval]*/Float64* pW2)
{
   CHECK_RETVAL(pW2);
   *pW2 = m_W2;
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::put_D(/*[in]*/Float64 D)
{
   if ( !IsEqual(m_D,D) )
   {
      m_D = D;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_D(/*[out,retval]*/Float64* pD)
{
   CHECK_RETVAL(pD);
   *pD = m_D;
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::put_R(/*[in]*/Float64 R)
{
   if ( !IsEqual(m_R,R) )
   {
      m_R = R;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::get_R(/*[out,retval]*/Float64* pR)
{
   CHECK_RETVAL(pR);
   *pR = m_R;
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CScallopedCrossBeam::Load(IStructuredLoad2* load)
{
   CComVariant var;

   load->BeginUnit(CComBSTR("ScallopedCrossBeam"));

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CScallopedCrossBeam::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("ScallopedCrossBeam"),1.0);

   save->EndUnit();
   return S_OK;
}

////////////////////////////////////////////////////////////////
HRESULT CScallopedCrossBeam::GetUpperXBeamProfile(IPoint2dCollection** ppPoints,bool bClone)
{
   CHECK_RETOBJ(ppPoints);

   if (m_bIsUXBDirty)
   {
#if defined _DEBUG
      IndexType nPoints;
      m_UXBProfile->get_Count(&nPoints);
      ATLASSERT(nPoints == 0);
#endif
      Float64 tDeck;
      m_pPier->get_DeckThickness(&tDeck);

      CComPtr<IPoint2dCollection> deckProfile;
      m_pPier->get_DeckProfile(&deckProfile);

      // Get cross beam start and end in Pier Coordinates
      Float64 XxbStart = 0;
      Float64 XxbEnd;
      get_Length(xblBottomXBeam, &XxbEnd);

      // Adjust for the end slopes
      // this is the start/end of the XBeam measured at the top of the upper xbeam
      Float64 deltaXl, deltaXr;
      GetUpperXBeamDeltas(&deltaXl, &deltaXr);

      XxbStart += deltaXl - m_X1L;
      XxbEnd   += deltaXr + m_X1R;

      // Start and end in pier coordinates (this is the coordinate system we need)
      Float64 XpStart, XpEnd;
      m_pPier->ConvertCrossBeamToPierCoordinate(XxbStart, &XpStart);
      m_pPier->ConvertCrossBeamToPierCoordinate(XxbEnd, &XpEnd);

      // Start and end in curb line coordinates so we can get deck elevations
      Float64 XclStart, XclEnd;
      m_pPier->ConvertCrossBeamToCurbLineCoordinate(XxbStart, &XclStart);
      m_pPier->ConvertCrossBeamToCurbLineCoordinate(XxbEnd, &XclEnd);

      Float64 YxbStart, YxbEnd;
      m_pPier->get_Elevation(XclStart, &YxbStart);
      m_pPier->get_Elevation(XclEnd, &YxbEnd);
      YxbStart -= tDeck;
      YxbEnd -= tDeck;

      CComPtr<IPoint2d> pntStart;
      pntStart.CoCreateInstance(CLSID_Point2d);
      pntStart->Move(XpStart, YxbStart);
      m_UXBProfile->Add(pntStart);

      // Work left to right across the deck profile, offsetting by tDeck to get the top of Xbeam profile
      CComPtr<IEnumPoint2d> enumPoints;
      deckProfile->get__Enum(&enumPoints);
      CComPtr<IPoint2d> pnt;
      while (enumPoints->Next(1, &pnt, nullptr) != S_FALSE)
      {
         Float64 x, y;
         pnt->Location(&x, &y);
         if (XpStart < x && x < XpEnd && !IsEqual(XpStart, x) && !IsEqual(XpEnd, x))
         {
            // point is within the extents of the cross beam
            y -= tDeck;
            CComPtr<IPoint2d> xbPoint;
            xbPoint.CoCreateInstance(CLSID_Point2d);
            xbPoint->Move(x, y);
            m_UXBProfile->Add(xbPoint);
         }
         pnt.Release();
      }

      CComPtr<IPoint2d> pntEnd;
      pntEnd.CoCreateInstance(CLSID_Point2d);
      pntEnd->Move(XpEnd, YxbEnd);
      m_UXBProfile->Add(pntEnd);

      m_UXBProfile->RemoveDuplicatePoints();

      m_bIsUXBDirty = false;
   }

   if (bClone)
   {
      return m_UXBProfile->Clone(ppPoints);
   }
   else
   {
      return m_UXBProfile.CopyTo(ppPoints);
   }
}

HRESULT CScallopedCrossBeam::GetLowerXBeamProfile(IPoint2dCollection** ppPoints,bool bClone)
{
   CHECK_RETOBJ(ppPoints);

   if ( m_bIsLXBDirty )
   {
      CComPtr<IPoint2dCollection> uxbProfile;
      GetUpperXBeamProfile(&uxbProfile);

      // Determine the horizontal limits of the lower xbeam top profile
      Float64 deltaXl, deltaXr;
      GetUpperXBeamDeltas(&deltaXl, &deltaXr);

      CComPtr<IPoint2d> uxbTL;
      uxbProfile->get_Item(0, &uxbTL);

      IndexType nPoints;
      uxbProfile->get_Count(&nPoints);
      CComPtr<IPoint2d> uxbTR;
      uxbProfile->get_Item(nPoints - 1, &uxbTR);

      Float64 Xl, Xr;
      uxbTL->get_X(&Xl);
      Xl -= deltaXl;

      uxbTR->get_X(&Xr);
      Xr -= deltaXr;

      m_LXBProfile.Release();
      m_LXBProfile.CoCreateInstance(CLSID_Point2dCollection);

      // copy all points from the upper xbeam profile within the limits Xl and Xr
      // to the lower xbeam profile, offsetting by HU
      for (IndexType idx = nPoints - 1; 0 <= idx && idx != INVALID_INDEX; idx--)
      {
         CComPtr<IPoint2d> pnt;
         uxbProfile->get_Item(idx, &pnt);
         Float64 X;
         pnt->get_X(&X);
         if (InRange(Xl, X, Xr))
         {
            CComPtr<IPoint2d> pntLXB;
            pnt->Clone(&pntLXB);
            pntLXB->Offset(0, -m_HU);
            m_LXBProfile->Insert(0,pntLXB);
         }
      }

      // now locate and add the left and right points of the lower xbeam profile
      // the horizonal position is Xl and Xr, which are in Pier Coordinates

      // convert Xl and Xr to curb line coordinates
      Float64 Xlcl, Xrcl;
      m_pPier->ConvertPierToCurbLineCoordinate(Xl, &Xlcl);
      m_pPier->ConvertPierToCurbLineCoordinate(Xr, &Xrcl);

      // get deck elevations
      Float64 Yl, Yr;
      m_pPier->get_Elevation(Xlcl, &Yl);
      m_pPier->get_Elevation(Xrcl, &Yr);

      Float64 tDeck;
      m_pPier->get_DeckThickness(&tDeck);

      // adjust for deck thickness
      Yl -= tDeck;
      Yr -= tDeck;

      CComPtr<IPoint2d> lxbTL;
      lxbTL.CoCreateInstance(CLSID_Point2d);
      lxbTL->Move(Xl, Yl - m_HU);
      m_LXBProfile->Insert(0, lxbTL);

      CComPtr<IPoint2d> lxbTR;
      lxbTR.CoCreateInstance(CLSID_Point2d);
      lxbTR->Move(Xr, Yr - m_HU);
      m_LXBProfile->Add(lxbTR);

      m_LXBProfile->RemoveDuplicatePoints();

      m_bIsLXBDirty = false;
   }

   if (bClone)
   {
      return m_LXBProfile->Clone(ppPoints);
   }
   else
   {
      return m_LXBProfile.CopyTo(ppPoints);
   }
}

Float64 LowerDepth(Float64 x, Float64 Xs, Float64 dX, Float64 dyL, Float64 dyR)
{
    if (IsZero(dX))
        return dyL;

    return ::LinInterp(
        x - Xs,
        dyL,
        dyR,
        dX);
};

Float64 LowerTopY(Float64 x, Float64 Xs, Float64 Yl, Float64 Yr, IPoint2dCollection* lxbProfile)
{
    IndexType nPoints;
    lxbProfile->get_Count(&nPoints);

    for (IndexType idx = 1;
        idx < nPoints;
        ++idx)
    {
        CComPtr<IPoint2d> p0;
        CComPtr<IPoint2d> p1;

        lxbProfile->get_Item(idx - 1, &p0);
        lxbProfile->get_Item(idx, &p1);

        Float64 x0, y0;
        Float64 x1, y1;

        p0->Location(&x0, &y0);
        p1->Location(&x1, &y1);

        const Float64 xMin = min(x0, x1);
        const Float64 xMax = max(x0, x1);

        if (InRange(xMin, x, xMax))
        {
            const Float64 segmentDX = x1 - x0;

            if (IsZero(segmentDX))
                return y0;

            return ::LinInterp(
                x - x0,
                y0,
                y1,
                segmentDX);
        }
    }

    if (x <= Xs)
        return Yl;

    return Yr;
};

void AddScallop(
    Float64 R, Float64 D, Float64 Xs, Float64 Yl, Float64 Yr, Float64 dX, Float64 dyL, Float64 dyR,
    Float64 x0Full,
    Float64 x1Full,
    Float64 xClip0,
    Float64 xClip1,
    bool skipFirst,
    IPoint2dCollection* BXBProfile, IPoint2dCollection* lxbProfile)
{
    if (x1Full <= x0Full ||
        xClip1 <= xClip0 ||
        R <= 0.0 ||
        D < 0.0)
    {
        return;
    }

    const Float64 xMid =
        0.5 * (x0Full + x1Full);

    /*
     * The crown of the circular scallop is D below the
     * top of the lower cross beam.
     */
    const Float64 crownY =
        LowerTopY(xMid, Xs, Yl, Yr, lxbProfile) - D;

    const Float64 circleCenterY =
        crownY - R;

    IndexType nSegs = 24;

    for (IndexType i = 0;
        i <= nSegs;
        ++i)
    {
        if (skipFirst && i == 0)
            continue;

        const Float64 u =
            static_cast<Float64>(i) /
            static_cast<Float64>(nSegs);

        const Float64 x =
            xClip0 +
            u * (xClip1 - xClip0);

        // Ordinary bottom profile at this location
        const Float64 bottomY =
            LowerTopY(x, Xs, Yl, Yr, lxbProfile) -
            LowerDepth(x, Xs, dX, dyL, dyR);

        Float64 y = bottomY;

        const Float64 dx =
            x - xMid;

        if (std::fabs(dx) <= R)
        {
            const Float64 circleY =
                circleCenterY +
                std::sqrt(
                    max(
                        0.0,
                        R * R - dx * dx));

            /*
             * Use the circle only where it is above the
             * ordinary lower-beam bottom.
             */
            y = max(bottomY, circleY);
        }

        CComPtr<IPoint2d> p;
        p.CoCreateInstance(CLSID_Point2d);

        p->Move(x, y);
        BXBProfile->Add(p);
    }
};

HRESULT CScallopedCrossBeam::GetBottomXBeamProfile(IPoint2dCollection** ppPoints,bool bClone)
{
   CHECK_RETOBJ(ppPoints);

   if ( m_bIsBXBDirty )
   {
      // get top profile of lower cross beam
      CComPtr<IPoint2dCollection> lxbProfile;
      GetLowerXBeamProfile(&lxbProfile);

      // get the top left point
      CComPtr<IPoint2d> lxbTL;
      lxbProfile->get_Item(0, &lxbTL);

      IndexType nPoints;
      lxbProfile->get_Count(&nPoints);
      CComPtr<IPoint2d> lxbTR;
      lxbProfile->get_Item(nPoints - 1, &lxbTR);

      Float64 Xl, Yl;
      lxbTL->Location(&Xl, &Yl);

      Float64 Xr, Yr;
      lxbTR->Location(&Xr, &Yr);

      // interpolation parameters for depth of lower xbeam between tapers
      Float64 Xs = Xl;
      Float64 dX = Xr - Xl;
      Float64 dyL = m_H1L;
      Float64 dyR = m_H1R;

      // horizontal location of left/right tapers
      Float64 Xlt = Xl;
      Float64 Xrt = Xr;

      Xlt = IsZero(Xlt) ? 0 : Xlt;
      Xrt = IsZero(Xrt) ? 0 : Xrt;

      // horizontal location of left/right end points of bottom of xbeam
      Xl += m_X1L;
      Xr -= m_X1R;

      m_BXBProfile.Release();
      m_BXBProfile.CoCreateInstance(CLSID_Point2dCollection);

      CComPtr<IColumnLayout> columnLayout;
      m_pPier->get_ColumnLayout(&columnLayout);
      IndexType nCols;
	  columnLayout->get_ColumnCount(&nCols);

      std::vector<Float64> colStations;

      for (IndexType colIdx = 0;
          colIdx < nCols;
          ++colIdx)
      {
          Float64 xCol;
          columnLayout->get_ColumnLocation(colIdx, &xCol);

          Float64 xPierCol;
          m_pPier->ConvertCrossBeamToPierCoordinate(xCol, &xPierCol);

          colStations.push_back(xPierCol);
      }

      std::sort(
          colStations.begin(),
          colStations.end());

      colStations.erase(
          std::unique(
              colStations.begin(),
              colStations.end(),
              [](Float64 a, Float64 b)
              {
                  return
                      std::fabs(a - b) <
                      1.0e-8;
              }),
          colStations.end());

      const Float64 XscallopLeft = Xl + m_X1L;

      const Float64 XscallopRight = Xr + m_X1R;

      if (colStations.size() >= 2)
      {
          const Float64 leftSpacing =
              colStations[1] -
              colStations[0];

          const Float64 rightSpacing =
              colStations[colStations.size() - 1] -
              colStations[colStations.size() - 2];

          std::vector<Float64> fullStations;

          fullStations.push_back(
              colStations.front() -
              leftSpacing);

          for (Float64 xCol : colStations)
              fullStations.push_back(xCol);

          fullStations.push_back(
              colStations.back() +
              rightSpacing);

          bool firstPoint = true;

          for (size_t i = 1;
              i < fullStations.size();
              ++i)
          {
              const Float64 x0Full =
                  fullStations[i - 1];

              const Float64 x1Full =
                  fullStations[i];

              const Float64 xClip0 =
                  max(
                      x0Full,
                      XscallopLeft);

              const Float64 xClip1 =
                  min(
                      x1Full,
                      XscallopRight);

              if (xClip1 > xClip0)
              {
                  AddScallop(m_R, m_D, Xs, Yl, Yr, dX, dyL, dyR,
                      x0Full,
                      x1Full,
                      xClip0,
                      xClip1,
                      !firstPoint, m_BXBProfile, lxbProfile);

                  firstPoint = false;
              }
          }
      }
      else
      {
          AddScallop(m_R, m_D, Xs, Yl, Yr, dX, dyL, dyR,
              XscallopLeft,
              XscallopRight,
              XscallopLeft,
              XscallopRight,
              false, m_BXBProfile, lxbProfile);
      }

      ///////////////////////////////////////////////////////////////////////

      Float64 Xltcl, Xrtcl;
      m_pPier->ConvertPierToCurbLineCoordinate(Xlt, &Xltcl);
      m_pPier->ConvertPierToCurbLineCoordinate(Xrt, &Xrtcl);

      Float64 Ylt, Yrt;
      m_pPier->get_Elevation(Xltcl, &Ylt);
      m_pPier->get_Elevation(Xrtcl, &Yrt);

      Float64 tDeck;
      m_pPier->get_DeckThickness(&tDeck);

      Ylt -= tDeck;
      Yrt -= tDeck;

      CComPtr<IPoint2d> bxbL;
      bxbL.CoCreateInstance(CLSID_Point2d);
      bxbL->Move(Xl, Yl - m_H1L);
      m_BXBProfile->Insert(0, bxbL);

      CComPtr<IPoint2d> bxbR;
      bxbR.CoCreateInstance(CLSID_Point2d);
      bxbR->Move(Xr, Yr - m_H1R);
      m_BXBProfile->Add(bxbR);

      m_BXBProfile->RemoveDuplicatePoints();

      m_bIsBXBDirty = false;
   }

   if (bClone)
   {
      return m_BXBProfile->Clone(ppPoints);
   }
   else
   {
      return m_BXBProfile.CopyTo(ppPoints);
   }
}

HRESULT CScallopedCrossBeam::GetLowerXBeamShape(Float64 Xxb,IShape** ppShape)
{
   Float64 Xcl;
   m_pPier->ConvertCrossBeamToCurbLineCoordinate(Xxb,&Xcl);

   Float64 Y;
   m_pPier->get_Elevation(Xcl,&Y);

   Float64 tDeck;
   m_pPier->get_DeckThickness(&tDeck);

   Y -= tDeck;
   
   Float64 D;
   get_Depth(0,Xxb,&D);

   CComPtr<IRectangle> lowerXBeamShape;
   lowerXBeamShape.CoCreateInstance(CLSID_Rect);
   lowerXBeamShape->put_Height(D);
   lowerXBeamShape->put_Width(m_W1);

   CComQIPtr<IXYPosition> position(lowerXBeamShape);
   CComPtr<IPoint2d> pnt;
   position->get_LocatorPoint(lpTopCenter,&pnt);
   pnt->Move(0,Y-m_HU);
   position->put_LocatorPoint(lpTopCenter,pnt);

   CComQIPtr<IShape> shape(lowerXBeamShape);
   shape.CopyTo(ppShape);

   return S_OK;
}

HRESULT CScallopedCrossBeam::GetUpperXBeamShape(Float64 Xxb,IShape** ppShape)
{
   Float64 Xcl;
   m_pPier->ConvertCrossBeamToCurbLineCoordinate(Xxb,&Xcl);

   Float64 Y;
   m_pPier->get_Elevation(Xcl,&Y);

   Float64 tDeck;
   m_pPier->get_DeckThickness(&tDeck);

   Y -= tDeck;

   PierType pierType;
   m_pPier->get_Type(&pierType);
   if ( pierType == ptExpansion )
   {
      // model expansion pier with two rectangles... one for the diaphragm on each side of the pier
      CComPtr<ICompositeShape> compositeShape;
      compositeShape.CoCreateInstance(CLSID_CompositeShape);

      CComPtr<IBearingLayout> bearingLayout;
      m_pPier->get_BearingLayout(&bearingLayout);
      IndexType nBearingLines;
      bearingLayout->get_BearingLineCount(&nBearingLines);
      Float64 backBrgOffset = 0;
      Float64 aheadBrgOffset = 0;
      if ( nBearingLines == 1 )
      {
         CComQIPtr<IBridgePier> bridgePier(m_pPier);
         if ( bridgePier )
         {
            CComPtr<IGenericBridge> bridge;
            bridgePier->get_Bridge(&bridge);

            PierIndexType pierIdx;
            bridgePier->get_Index(&pierIdx);
            if ( pierIdx == 0 )
            {
               bearingLayout->get_BearingLineOffset(0,&aheadBrgOffset);
            }
            else
            {
               bearingLayout->get_BearingLineOffset(0,&backBrgOffset);
            }
         }
         else
         {
            bearingLayout->get_BearingLineOffset(0,&backBrgOffset);
         }
      }
      else
      {
         bearingLayout->get_BearingLineOffset(0,&backBrgOffset);
         bearingLayout->get_BearingLineOffset(1,&aheadBrgOffset);
      }

      CComPtr<IRectangle> leftUpperXBeamShape;
      leftUpperXBeamShape.CoCreateInstance(CLSID_Rect);
      leftUpperXBeamShape->put_Height(m_HU);
      leftUpperXBeamShape->put_Width(m_W2/2);

      CComQIPtr<IXYPosition> position(leftUpperXBeamShape);
      CComPtr<IPoint2d> pnt;
      position->get_LocatorPoint(lpTopCenter,&pnt);
      pnt->Move(backBrgOffset,Y);
      position->put_LocatorPoint(lpTopCenter,pnt);
      CComQIPtr<IShape> leftShape(leftUpperXBeamShape);
      compositeShape->AddShape(leftShape,VARIANT_FALSE);

      if ( 1 < nBearingLines )
      {
         CComPtr<IRectangle> rightUpperXBeamShape;
         rightUpperXBeamShape.CoCreateInstance(CLSID_Rect);
         rightUpperXBeamShape->put_Height(m_HU);
         rightUpperXBeamShape->put_Width(m_W2/2);

         position.Release();
         rightUpperXBeamShape.QueryInterface(&position);
         pnt.Release();
         position->get_LocatorPoint(lpTopCenter,&pnt);
         pnt->Move(aheadBrgOffset,Y);
         position->put_LocatorPoint(lpTopCenter,pnt);
         CComQIPtr<IShape> rightShape(rightUpperXBeamShape);
         compositeShape->AddShape(rightShape,VARIANT_FALSE);
      }



      compositeShape->get_Shape(ppShape);
   }
   else
   {
      CComPtr<IRectangle> upperXBeamShape;
      upperXBeamShape.CoCreateInstance(CLSID_Rect);
      upperXBeamShape->put_Height(m_HU);
      upperXBeamShape->put_Width(m_W2);

      CComQIPtr<IXYPosition> position(upperXBeamShape);
      CComPtr<IPoint2d> pnt;
      position->get_LocatorPoint(lpTopCenter,&pnt);
      pnt->Move(0,Y);
      position->put_LocatorPoint(lpTopCenter,pnt);

      CComQIPtr<IShape> shape(upperXBeamShape);
      shape.CopyTo(ppShape);
   }

   return S_OK;
}

void CScallopedCrossBeam::GetUpperXBeamDeltas(Float64* pUXBleft,Float64* pUXBright)
{
   *pUXBleft = 0.0;
   *pUXBright = 0.0;
   PierType pierType;
   m_pPier->get_Type(&pierType);
   if (pierType == ptIntegral)
   {
      *pUXBleft = -m_X1L*(m_HU) / m_H1L;
      *pUXBright = m_X1R*(m_HU) / m_H1R;
   }
}


///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

// LinearCrossBeam.cpp : Implementation of CLinearCrossBeam
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "LinearCrossBeam.h"
#include <ComException.h>
#include <Math\Math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinearCrossBeam
HRESULT CLinearCrossBeam::FinalConstruct()
{
   m_H1 = 0;
   m_H2 = 0;
   m_H3 = 0;
   m_H4 = 0;
   m_H5 = 0;
   m_X1 = 0;
   m_X2 = 0;
   m_X3 = 0;
   m_X4 = 0;
   m_W1 = 0;
   m_W2 = 0;

   HRESULT hr = m_RebarLayout.CoCreateInstance(CLSID_RebarLayout);
   if ( FAILED(hr) )
   {
      return hr;
   }

   m_UXBProfile.CoCreateInstance(CLSID_Point2dCollection);

   m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);

   return S_OK;
}

void CLinearCrossBeam::FinalRelease()
{
}

void CLinearCrossBeam::Invalidate()
{
   m_UXBProfile->Clear();
   m_LXBProfile.Release();
   m_BXBProfile.Release();

   m_bIsLXBDirty = true;
   m_bIsUXBDirty = true;
   m_bIsBXBDirty = true;
}

STDMETHODIMP CLinearCrossBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICrossBeam,
      &IID_ILinearCrossBeam,
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
STDMETHODIMP CLinearCrossBeam::putref_Pier(IPier* pPier)
{
   CHECK_IN(pPier);
   m_pPier = pPier;
   Invalidate();
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_Pier(IPier** ppPier)
{
   CHECK_RETVAL(ppPier);
   if ( m_pPier )
   {
      *ppPier = m_pPier;
      (*ppPier)->AddRef();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_Length(XBeamLocation location, Float64* length)
{
   CHECK_RETVAL(length);

   Float64 loh, w, roh;
   CComPtr<IColumnLayout> columnLayout;
   m_pPier->get_ColumnLayout(&columnLayout);
   columnLayout->get_ColumnLayoutWidth(&w);
   columnLayout->get_Overhang(qcbLeft,&loh);
   columnLayout->get_Overhang(qcbRight,&roh);

   (*length) = loh + w + roh; // this is the basic length at the top of the lower cross beam

   if (location == xblTopLowerXBeam)
   {
      Float64 deltaXl, deltaXr;
      GetUpperXBeamDeltas(&deltaXl, &deltaXr);
      (*length) += deltaXl;
      (*length) -= deltaXr;
   }
   else if (location == xblBottomXBeam)
   {
      (*length) -= m_X2 + m_X4;
   }

   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_Depth(/*[in]*/StageIndexType stageIdx,/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pDepth)
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
      *pDepth += m_H5;
   }

   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_FullDepth(Float64 Xxb,Float64* pDepth)
{
   HRESULT hr = get_Depth(0,Xxb,pDepth);
   if ( FAILED(hr) )
   {
      return hr;
   }

   (*pDepth) += m_H5;
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_Profile(/*[in]*/StageIndexType stageIdx,/*[out,retval]*/IShape** ppShape)
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

STDMETHODIMP CLinearCrossBeam::get_TopSurface(StageIndexType stageIdx,IPoint2dCollection** ppPoints)
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

STDMETHODIMP CLinearCrossBeam::get_BottomSurface(StageIndexType stageIdx,IPoint2dCollection** ppPoints)
{
   return GetBottomXBeamProfile(ppPoints);
}

STDMETHODIMP CLinearCrossBeam::get_Surface(CrossBeamRebarDatum datum, Float64 offset, IPoint2dCollection** ppPoints)
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

   if (!IsZero(m_X1))
   {
      // there is a taper along the bottom of the xbeam
      CComPtr<IPoint2d> pntLeft3;
      bxbProfile->get_Item(1, &pntLeft3);

      lsLeft->ThroughPoints(pntLeft2, pntLeft3);

      CComPtr<IPoint2d> pnt1, pnt2;
      (*ppPoints)->get_Item(0, &pnt1);
      (*ppPoints)->get_Item(1, &pnt2);

      CComPtr<IPoint2d> pnt1Clone, pnt2Clone;
      pnt1->Clone(&pnt1Clone);
      pnt2->Clone(&pnt2Clone);

      CComPtr<ILineSegment2d> ls;
      ls.CoCreateInstance(CLSID_LineSegment2d);
      ls->ThroughPoints(pnt1Clone, pnt2Clone);

      pntIntersect.Release();
      if (m_GeomUtil->SegSegIntersect(lsLeft, ls, &pntIntersect) == S_OK)
      {
         // there was an intersection... replace the left point with
         // the intersection point
         (*ppPoints)->Remove(0);
         (*ppPoints)->Insert(0, pntIntersect);
      }
   }

   if (!IsZero(m_X3))
   {
      CComPtr<IPoint2d> pntRight3;
      bxbProfile->get_Count(&nPoints);
      bxbProfile->get_Item(nPoints - 2, &pntRight3);

      lsRight->ThroughPoints(pntRight2, pntRight3);

      CComPtr<IPoint2d> pnt1, pnt2;
      (*ppPoints)->get_Count(&nPoints);
      (*ppPoints)->get_Item(nPoints-2, &pnt1);
      (*ppPoints)->get_Item(nPoints-1, &pnt2);

      CComPtr<IPoint2d> pnt1Clone, pnt2Clone;
      pnt1->Clone(&pnt1Clone);
      pnt2->Clone(&pnt2Clone);

      CComPtr<ILineSegment2d> ls;
      ls.CoCreateInstance(CLSID_LineSegment2d);
      ls->ThroughPoints(pnt1Clone, pnt2Clone);

      pntIntersect.Release();
      if (m_GeomUtil->SegSegIntersect(lsRight, ls, &pntIntersect) == S_OK)
      {
         // there was an intersection... replace the left point with
         // the intersection point
         (*ppPoints)->Remove(nPoints-1);
         (*ppPoints)->Insert(nPoints-1, pntIntersect);
      }
   }

   (*ppPoints)->RemoveDuplicatePoints();

   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_BasicShape(Float64 Xxb,IShape** ppShape)
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

STDMETHODIMP CLinearCrossBeam::get_Shape(StageIndexType stageIdx,Float64 Xxb,IShape** ppShape)
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

STDMETHODIMP CLinearCrossBeam::get_RebarLayout(IRebarLayout** ppRebarLayout)
{
   CHECK_RETVAL(ppRebarLayout);
   return m_RebarLayout.CopyTo(ppRebarLayout);
}

STDMETHODIMP CLinearCrossBeam::putref_RebarLayout(IRebarLayout* pRebarLayout)
{
   m_RebarLayout.Release();
   if ( pRebarLayout )
   {
      m_RebarLayout = pRebarLayout;
   }
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// ILinearCrossBeam implementation
STDMETHODIMP CLinearCrossBeam::put_H1(/*[in]*/Float64 H1)
{
   if ( !IsEqual(m_H1,H1) )
   {
      m_H1 = H1;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_H1(/*[out,retval]*/Float64* pH1)
{
   CHECK_RETVAL(pH1);
   *pH1 = m_H1;
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::put_H2(/*[in]*/Float64 H2)
{
   if ( !IsEqual(m_H2,H2) )
   {
      m_H2 = H2;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_H2(/*[out,retval]*/Float64* pH2)
{
   CHECK_RETVAL(pH2);
   *pH2 = m_H2;
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::put_H3(/*[in]*/Float64 H3)
{
   if ( !IsEqual(m_H3,H3) )
   {
      m_H3 = H3;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_H3(/*[out,retval]*/Float64* pH3)
{
   CHECK_RETVAL(pH3);
   *pH3 = m_H3;
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::put_H4(/*[in]*/Float64 H4)
{
   if ( !IsEqual(m_H4,H4) )
   {
      m_H4 = H4;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_H4(/*[out,retval]*/Float64* pH4)
{
   CHECK_RETVAL(pH4);
   *pH4 = m_H4;
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::put_H5(/*[in]*/Float64 H5)
{
   if ( !IsEqual(m_H5,H5) )
   {
      m_H5 = H5;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_H5(/*[out,retval]*/Float64* pH5)
{
   CHECK_RETVAL(pH5);
   *pH5 = m_H5;
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::put_X1(/*[in]*/Float64 X1)
{
   if ( !IsEqual(m_X1,X1) )
   {
      m_X1 = X1;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_X1(/*[out,retval]*/Float64* pX1)
{
   CHECK_RETVAL(pX1);
   *pX1 = m_X1;
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::put_X2(/*[in]*/Float64 X2)
{
   if ( !IsEqual(m_X2,X2) )
   {
      m_X2 = X2;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_X2(/*[out,retval]*/Float64* pX2)
{
   CHECK_RETVAL(pX2);
   *pX2 = m_X2;
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::put_X3(/*[in]*/Float64 X3)
{
   if ( !IsEqual(m_X3,X3) )
   {
      m_X3 = X3;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_X3(/*[out,retval]*/Float64* pX3)
{
   CHECK_RETVAL(pX3);
   *pX3 = m_X3;
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::put_X4(/*[in]*/Float64 X4)
{
   if ( !IsEqual(m_X4,X4) )
   {
      m_X4 = X4;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_X4(/*[out,retval]*/Float64* pX4)
{
   CHECK_RETVAL(pX4);
   *pX4 = m_X4;
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::put_W1(/*[in]*/Float64 W1)
{
   if ( !IsEqual(m_W1,W1) )
   {
      m_W1 = W1;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_W1(/*[out,retval]*/Float64* pW1)
{
   CHECK_RETVAL(pW1);
   *pW1 = m_W1;
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::put_W2(/*[in]*/Float64 W2)
{
   if ( !IsEqual(m_W2,W2) )
   {
      m_W2 = W2;
      Invalidate();
   }
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_W2(/*[out,retval]*/Float64* pW2)
{
   CHECK_RETVAL(pW2);
   *pW2 = m_W2;
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CLinearCrossBeam::Load(IStructuredLoad2* load)
{
   CComVariant var;

   load->BeginUnit(CComBSTR("LinearCrossBeam"));

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("LinearCrossBeam"),1.0);

   save->EndUnit();
   return S_OK;
}

////////////////////////////////////////////////////////////////
HRESULT CLinearCrossBeam::GetUpperXBeamProfile(IPoint2dCollection** ppPoints,bool bClone)
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

      XxbStart += deltaXl - m_X2;
      XxbEnd   += deltaXr + m_X4;

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

HRESULT CLinearCrossBeam::GetLowerXBeamProfile(IPoint2dCollection** ppPoints,bool bClone)
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
      // to the lower xbeam profile, offsetting by H5
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
            pntLXB->Offset(0, -m_H5);
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
      lxbTL->Move(Xl, Yl - m_H5);
      m_LXBProfile->Insert(0, lxbTL);

      CComPtr<IPoint2d> lxbTR;
      lxbTR.CoCreateInstance(CLSID_Point2d);
      lxbTR->Move(Xr, Yr - m_H5);
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

HRESULT CLinearCrossBeam::GetBottomXBeamProfile(IPoint2dCollection** ppPoints,bool bClone)
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
      Float64 dyL = m_H1 + m_H2;
      Float64 dyR = m_H3 + m_H4;

      // horizontal location of left/right tapers
      Float64 Xlt = Xl + m_X1;
      Float64 Xrt = Xr - m_X3;

      Xlt = IsZero(Xlt) ? 0 : Xlt;
      Xrt = IsZero(Xrt) ? 0 : Xrt;

      // horizontal location of left/right end points of bottom of xbeam
      Xl += m_X2;
      Xr -= m_X4;

      m_BXBProfile.Release();
      m_BXBProfile.CoCreateInstance(CLSID_Point2dCollection);
      for (IndexType idx = nPoints - 1; 0 <= idx && idx != INVALID_INDEX; idx--)
      {
         CComPtr<IPoint2d> pnt;
         lxbProfile->get_Item(idx, &pnt);
         Float64 X;
         pnt->get_X(&X);
         if (InRange(Xlt, X, Xrt))
         {
            // X is between tapers
            CComPtr<IPoint2d> pntBXB;
            pnt->Clone(&pntBXB);

            Float64 dy = ::LinInterp(X - Xs, dyL, dyR, dX);

            pntBXB->Offset(0, -dy);
            m_BXBProfile->Insert(0, pntBXB);
         }
      }

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
      bxbL->Move(Xl, Yl - m_H1);
      m_BXBProfile->Insert(0, bxbL);

      if (!IsZero(m_H2) && !IsZero(m_X1))
      {
         // there is a taper on the left side
         CComPtr<IPoint2d> bxbLT;
         bxbLT.CoCreateInstance(CLSID_Point2d);

         Float64 y;
         bxbL->get_Y(&y);

         bxbLT->Move(Xlt, y - m_H2);
         m_BXBProfile->Insert(1, bxbLT);
      }

      if (!IsZero(m_H4) && !IsZero(m_X3))
      {
         // there is a taper on the right side
         CComPtr<IPoint2d> bxbRT;
         bxbRT.CoCreateInstance(CLSID_Point2d);

         Float64 y = Yr - m_H3 - m_H4; // this is bxbR->Y - m_H4

         bxbRT->Move(Xrt, y);
         m_BXBProfile->Add(bxbRT);
      }

      CComPtr<IPoint2d> bxbR;
      bxbR.CoCreateInstance(CLSID_Point2d);
      bxbR->Move(Xr, Yr - m_H3);
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

HRESULT CLinearCrossBeam::GetLowerXBeamShape(Float64 Xxb,IShape** ppShape)
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
   pnt->Move(0,Y-m_H5);
   position->put_LocatorPoint(lpTopCenter,pnt);

   CComQIPtr<IShape> shape(lowerXBeamShape);
   shape.CopyTo(ppShape);

   return S_OK;
}

HRESULT CLinearCrossBeam::GetUpperXBeamShape(Float64 Xxb,IShape** ppShape)
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
      leftUpperXBeamShape->put_Height(m_H5);
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
         rightUpperXBeamShape->put_Height(m_H5);
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
      upperXBeamShape->put_Height(m_H5);
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

void CLinearCrossBeam::GetUpperXBeamDeltas(Float64* pUXBleft,Float64* pUXBright)
{
   *pUXBleft = 0.0;
   *pUXBright = 0.0;
   PierType pierType;
   m_pPier->get_Type(&pierType);
   if (pierType == ptIntegral)
   {
      *pUXBleft = -m_X2*(m_H5) / m_H1;
      *pUXBright = m_X4*(m_H5) / m_H3;
   }
}


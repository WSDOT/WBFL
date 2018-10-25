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

   return S_OK;
}

void CLinearCrossBeam::FinalRelease()
{
}

STDMETHODIMP CLinearCrossBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICrossBeam,
      &IID_ILinearCrossBeam,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
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

STDMETHODIMP CLinearCrossBeam::get_Length(Float64* length)
{
   CHECK_RETVAL(length);

   Float64 loh, w, roh;
   CComPtr<IColumnLayout> columnLayout;
   m_pPier->get_ColumnLayout(&columnLayout);
   columnLayout->get_ColumnLayoutWidth(&w);
   columnLayout->get_Overhang(qcbLeft,&loh);
   columnLayout->get_Overhang(qcbRight,&roh);

   (*length) = loh + w + roh;

   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_Depth(/*[in]*/StageIndexType stageIdx,/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pDepth)
{
   CHECK_RETVAL(pDepth);

   // Create a function that represents the top of the lower cross beam

   CComPtr<IPoint2d> pntTL,pntTC,pntTR,pntBL,pntBL2,pntBC,pntBR2,pntBR;
   GetLowerXBeamPoints(&pntTL,&pntTC,&pntTR,&pntBL,&pntBL2,&pntBC,&pntBR2,&pntBR);

   Float64 Xoffset;
   Float64 x,y;

   // Adjust X-values so they are in XBeam coordinates (X=0 at bottom left of lower cross beam)

   mathPwLinearFunction2dUsingPoints fnBottom;
   pntBL->Location(&x,&y);
   Xoffset = x;
   fnBottom.AddPoint(x-Xoffset,y);

   pntBL2->Location(&x,&y);
   fnBottom.AddPoint(x-Xoffset,y);

   pntBC->Location(&x,&y);
   fnBottom.AddPoint(x-Xoffset,y);

   pntBR2->Location(&x,&y);
   fnBottom.AddPoint(x-Xoffset,y);

   pntBR->Location(&x,&y);
   fnBottom.AddPoint(x-Xoffset,y);

   mathPwLinearFunction2dUsingPoints fnTop;
   pntTL->Location(&x,&y);
   fnTop.AddPoint(x-Xoffset,y);

   pntTC->Location(&x,&y);
   fnTop.AddPoint(x-Xoffset,y);

   pntTR->Location(&x,&y);
   fnTop.AddPoint(x-Xoffset,y);


   Float64 Y1 = fnTop.Evaluate(Xxb);
   Float64 Y2 = fnBottom.Evaluate(Xxb);

   Float64 H = Y1 - Y2;
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

   if ( stageIdx == 0 )
   {
      CComPtr<IPoint2d> pntTL,pntTC,pntTR,pntBL,pntBL2,pntBC,pntBR2,pntBR;
      GetLowerXBeamPoints(&pntTL,&pntTC,&pntTR,&pntBL,&pntBL2,&pntBC,&pntBR2,&pntBR);

      CComPtr<IPolyShape> shape;
      shape.CoCreateInstance(CLSID_PolyShape);
      shape->AddPointEx(pntTL);
      shape->AddPointEx(pntTC);
      shape->AddPointEx(pntTR);
      shape->AddPointEx(pntBR);
      shape->AddPointEx(pntBR2);
      shape->AddPointEx(pntBC);
      shape->AddPointEx(pntBL2);
      shape->AddPointEx(pntBL);

      shape.QueryInterface(ppShape);
   }
   else
   {
      CComPtr<IPoint2d> pntTL, pntTC, pntTR;
      CComPtr<IPoint2d> pntBL, pntBC, pntBR;
      GetUpperXBeamPoints(&pntTL,&pntTC,&pntTR,&pntBL,&pntBC,&pntBR);

      CComPtr<IPolyShape> shape;
      shape.CoCreateInstance(CLSID_PolyShape);
      shape->AddPointEx(pntTL);
      shape->AddPointEx(pntTC);
      shape->AddPointEx(pntTR);
      shape->AddPointEx(pntBR);
      shape->AddPointEx(pntBC);
      shape->AddPointEx(pntBL);

      shape.QueryInterface(ppShape);
   }

   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_TopSurface(StageIndexType stageIdx,IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);

   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   if ( stageIdx == 0 )
   {
      CComPtr<IPoint2d> pntTL,pntTC,pntTR,pntBL,pntBL2,pntBC,pntBR2,pntBR;
      GetLowerXBeamPoints(&pntTL,&pntTC,&pntTR,&pntBL,&pntBL2,&pntBC,&pntBR2,&pntBR);

      points->Add(pntTL);
      points->Add(pntTC);
      points->Add(pntTR);
   }
   else
   {
      CComPtr<IPoint2d> pntTL, pntTC, pntTR;
      CComPtr<IPoint2d> pntBL, pntBC, pntBR;
      GetUpperXBeamPoints(&pntTL,&pntTC,&pntTR,&pntBL,&pntBC,&pntBR);

      points->Add(pntTL);
      points->Add(pntTC);
      points->Add(pntTR);
   }

   points.CopyTo(ppPoints);
   return S_OK;
}

STDMETHODIMP CLinearCrossBeam::get_BottomSurface(StageIndexType stageIdx,IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);

   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   CComPtr<IPoint2d> pntTL,pntTC,pntTR,pntBL,pntBL2,pntBC,pntBR2,pntBR;
   GetLowerXBeamPoints(&pntTL,&pntTC,&pntTR,&pntBL,&pntBL2,&pntBC,&pntBR2,&pntBR);

   points->Add(pntBL);
   if ( pntBL->SameLocation(pntBL2) == S_FALSE )
   {
      points->Add(pntBL2);
   }

   points->Add(pntBC);

   if ( pntBR->SameLocation(pntBR2) == S_FALSE )
   {
      points->Add(pntBR2);
   }
   points->Add(pntBR);

   points.CopyTo(ppPoints);
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
   m_H1 = H1;
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
   m_H2 = H2;
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
   m_H3 = H3;
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
   m_H4 = H4;
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
   m_H5 = H5;
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
   m_X1 = X1;
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
   m_X2 = X2;
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
   m_X3 = X3;
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
   m_X4 = X4;
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
   m_W1 = W1;
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
   m_W2 = W2;
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

void CLinearCrossBeam::GetUpperXBeamPoints(IPoint2d** ppTL,IPoint2d** ppTC,IPoint2d** ppTR,IPoint2d** ppBL,IPoint2d** ppBC,IPoint2d** ppBR)
{
   Float64 tDeck;
   m_pPier->get_DeckThickness(&tDeck);

   // Get crown point in Pier Coordinates
   Float64 XclCrownPoint;
   m_pPier->get_CrownPointLocation(&XclCrownPoint);
   Float64 XxbCrownPoint;
   m_pPier->ConvertCurbLineToCrossBeamCoordinate(XclCrownPoint,&XxbCrownPoint);
   Float64 XpCrownPoint;
   m_pPier->ConvertCrossBeamToPierCoordinate(XxbCrownPoint,&XpCrownPoint);
   Float64 Ycp;
   m_pPier->get_CrownPointElevation(&Ycp);
   Ycp -= tDeck;

   // Get cross beam start and end in Pier Coordinates
   Float64 XxbStart = 0;
   Float64 XxbEnd;
   get_Length(&XxbEnd);

   // Adjust for the end slopes
   // this is the start/end of the XBeam measured at the top of the upper xbeam
   XxbStart -= m_X2*(m_H1+m_H5)/m_H1;
   XxbEnd   += m_X4*(m_H3+m_H5)/m_H3;

   Float64 XpStart, XpEnd;
   m_pPier->ConvertCrossBeamToPierCoordinate(XxbStart,&XpStart);
   m_pPier->ConvertCrossBeamToPierCoordinate(XxbEnd,  &XpEnd);

   Float64 XclStart, XclEnd;
   m_pPier->ConvertCrossBeamToCurbLineCoordinate(XxbStart,&XclStart);
   m_pPier->ConvertCrossBeamToCurbLineCoordinate(XxbEnd,  &XclEnd);

   Float64 YxbStart, YxbEnd;
   m_pPier->get_Elevation(XclStart,&YxbStart);
   m_pPier->get_Elevation(XclEnd,  &YxbEnd);
   YxbStart -= tDeck;
   YxbEnd   -= tDeck;

   // Create the points
   ::CoCreateInstance(CLSID_Point2d,NULL,CLSCTX_ALL,IID_IPoint2d,(LPVOID*)ppTL);
   ::CoCreateInstance(CLSID_Point2d,NULL,CLSCTX_ALL,IID_IPoint2d,(LPVOID*)ppTC);
   ::CoCreateInstance(CLSID_Point2d,NULL,CLSCTX_ALL,IID_IPoint2d,(LPVOID*)ppTR);
   ::CoCreateInstance(CLSID_Point2d,NULL,CLSCTX_ALL,IID_IPoint2d,(LPVOID*)ppBL);
   ::CoCreateInstance(CLSID_Point2d,NULL,CLSCTX_ALL,IID_IPoint2d,(LPVOID*)ppBC);
   ::CoCreateInstance(CLSID_Point2d,NULL,CLSCTX_ALL,IID_IPoint2d,(LPVOID*)ppBR);

   // work CCW around the upper cross beam
   (*ppTL)->Move(XpStart,YxbStart);
   (*ppTC)->Move(XpCrownPoint,Ycp);
   (*ppTR)->Move(XpEnd,YxbEnd);
   (*ppBR)->Move(XpEnd - m_X4*m_H5/m_H3,YxbEnd-m_H5);
   (*ppBC)->Move(XpCrownPoint,Ycp-m_H5);
   (*ppBL)->Move(XpStart + m_X2*m_H5/m_H1,YxbStart-m_H5);


   // make sure crown point is on the XBeam (it could actually be off the beam.. if it is, just put it at the edge)
   Float64 XL, XC, XR;
   (*ppTL)->get_X(&XL);
   (*ppTC)->get_X(&XC);
   (*ppTR)->get_X(&XR);

   if ( XC < XL )
   {
      Float64 Y;
      (*ppTL)->get_Y(&Y);
      (*ppTC)->Move(XL,Y);

      Float64 X;
      (*ppBL)->Location(&X,&Y);
      (*ppBC)->Move(X,Y);
   }
   else if ( XR < XC )
   {
      Float64 Y;
      (*ppTR)->get_Y(&Y);
      (*ppTC)->Move(XR,Y);

      Float64 X;
      (*ppBR)->Location(&X,&Y);
      (*ppBC)->Move(X,Y);
   }
}

void CLinearCrossBeam::GetLowerXBeamPoints(IPoint2d** ppTL,IPoint2d** ppTC,IPoint2d** ppTR,IPoint2d** ppBL,IPoint2d** ppBL2,IPoint2d** ppBC,IPoint2d** ppBR2,IPoint2d** ppBR)
{
   CComPtr<IPoint2d> uxbTL,uxbTC,uxbTR,uxbBL,uxbBC,uxbBR;
   GetUpperXBeamPoints(&uxbTL,&uxbTC,&uxbTR,&uxbBL,&uxbBC,&uxbBR);

   uxbBL.CopyTo(ppTL);
   uxbBC.CopyTo(ppTC);
   uxbBR.CopyTo(ppTR);

   uxbBL->Clone(ppBL);
   uxbBL->Clone(ppBL2);
   uxbBC->Clone(ppBC);
   uxbBR->Clone(ppBR);
   uxbBR->Clone(ppBR2);

   (*ppBL)->Offset(m_X2,-m_H1);
   (*ppBL2)->Offset(m_X1,-(m_H1+m_H2));
   (*ppBR2)->Offset(-m_X3,-(m_H3+m_H4));
   (*ppBR)->Offset(-m_X4,-m_H3);

   Float64 x,y;
   uxbBC->Location(&x,&y);

   Float64 h1 = m_H1 + m_H2;
   Float64 h2 = m_H3 + m_H4;
   Float64 L;
   get_Length(&L);
   Float64 dy = ::LinInterp(x,h1,h2,L);
   y -= dy;
   (*ppBC)->Move(x,y);
}

void CLinearCrossBeam::GetLowerXBeamShape(Float64 Xxb,IShape** ppShape)
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
}

void CLinearCrossBeam::GetUpperXBeamShape(Float64 Xxb,IShape** ppShape)
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
      CComPtr<IBearingLayout> bearingLayout;
      m_pPier->get_BearingLayout(&bearingLayout);
      IndexType nBearingLines;
      bearingLayout->get_BearingLineCount(&nBearingLines);
      Float64 backBrgOffset = 0;
      Float64 aheadBrgOffset = 0;
      if ( nBearingLines == 1 )
      {
         bearingLayout->get_BearingLineOffset(0,&backBrgOffset);
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

      CComQIPtr<IShape> leftShape(leftUpperXBeamShape);
      CComQIPtr<IShape> rightShape(rightUpperXBeamShape);

      CComPtr<ICompositeShape> compositeShape;
      compositeShape.CoCreateInstance(CLSID_CompositeShape);
      compositeShape->AddShape(leftShape,VARIANT_FALSE);
      compositeShape->AddShape(rightShape,VARIANT_FALSE);

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
}

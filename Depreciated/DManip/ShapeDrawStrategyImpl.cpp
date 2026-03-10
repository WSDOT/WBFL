///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// ShapeDrawStrategyImpl.cpp: implementation of the CShapeDrawStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "ShapeDrawStrategyImpl.h"
#include <MathEx.h>
#include <limits>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShapeDrawStrategyImpl::CShapeDrawStrategyImpl()
{
   m_SolidLineStyle = lsSolid;
   m_SolidLineColor = RGB(0,0,0); // black
   m_SolidFillColor = RGB(0,0,0); // black
   m_SolidLineWidth = 1;

   m_VoidLineStyle = lsSolid;
   m_VoidLineColor  = RGB(255,255,255); // white
   m_VoidFillColor  = RGB(255,255,255); // white
   m_VoidLineWidth = 1;

   m_bFill = false;
   m_bHasBoundingShape = true;
}

CShapeDrawStrategyImpl::~CShapeDrawStrategyImpl()
{
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::SetShape(IShape* pShape)
{
   m_Shape = pShape;

   m_CompositeShape.Release();
   m_Shape.QueryInterface(&m_CompositeShape);

   m_BoundingBox.Release(); 
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::GetShape(IShape** ppShape)
{
   (*ppShape) = m_Shape;
   if ( m_Shape )
      (*ppShape)->AddRef();
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::SetSolidLineStyle(LineStyleType lineStyle)
{
   m_SolidLineStyle = lineStyle;
}

STDMETHODIMP_(LineStyleType) CShapeDrawStrategyImpl::GetSolidLineStyle()
{
   return m_SolidLineStyle;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::SetSolidLineColor(COLORREF crColor)
{
   m_SolidLineColor = crColor;
}

STDMETHODIMP_(COLORREF) CShapeDrawStrategyImpl::GetSolidLineColor()
{
   return m_SolidLineColor;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::SetSolidFillColor(COLORREF crColor)
{
   m_SolidFillColor = crColor;
}

STDMETHODIMP_(COLORREF) CShapeDrawStrategyImpl::GetSolidFillColor()
{
   return m_SolidFillColor;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::SetSolidLineWidth(UINT nPixels)
{
   m_SolidLineWidth = nPixels;
}

STDMETHODIMP_(UINT) CShapeDrawStrategyImpl::GetSolidLineWidth()
{
   return m_SolidLineWidth;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::SetVoidLineStyle(LineStyleType lineStyle)
{
   m_VoidLineStyle = lineStyle;
}

STDMETHODIMP_(LineStyleType) CShapeDrawStrategyImpl::GetVoidLineStyle()
{
   return m_VoidLineStyle;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::SetVoidLineColor(COLORREF crColor)
{
   m_VoidLineColor = crColor;
}

STDMETHODIMP_(COLORREF) CShapeDrawStrategyImpl::GetVoidLineColor()
{
   return m_VoidLineColor;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::SetVoidFillColor(COLORREF crColor)
{
   m_VoidFillColor = crColor;
}

STDMETHODIMP_(COLORREF) CShapeDrawStrategyImpl::GetVoidFillColor()
{
   return m_VoidFillColor;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::SetVoidLineWidth(UINT nPixels)
{
   m_VoidLineWidth = nPixels;
}

STDMETHODIMP_(UINT) CShapeDrawStrategyImpl::GetVoidLineWidth()
{
   return m_VoidLineWidth;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::DoFill(bool doFill)
{
   m_bFill = doFill;
}

STDMETHODIMP_(bool) CShapeDrawStrategyImpl::DoFill()
{
   return m_bFill;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::HasBoundingShape(bool bHasBoundingShape)
{
   m_bHasBoundingShape = bHasBoundingShape;
}

STDMETHODIMP_(bool) CShapeDrawStrategyImpl::HasBoundingShape()
{
   return m_bHasBoundingShape;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::Draw(iPointDisplayObject* pDO,CDC* pDC)
{
   DrawMe(pDO,pDC,false);
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::DrawHighlite(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   DrawMe(pDO,pDC,bHighlite);
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::DrawDragImage(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
   ATLASSERT(false); // not implemented
//   map->LPtoWP(dragPoint.x, dragPoint.y, &m_CachePoint);
//
//   CRect r = pDO->GetBoundingBox();
//
//   COLORREF color;
//   color = RGB(0,0,255);
//
//   CPen pen(PS_SOLID,1,color);
//   CPen* pOldPen = pDC->SelectObject(&pen);
//   DrawMe(r,pDC);
//   pDC->SelectObject(pOldPen);
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl::GetBoundingBox(iPointDisplayObject* pDO, IRect2d** rect)
{
   if ( m_BoundingBox )
   {
      (*rect) = m_BoundingBox;
      (*rect)->AddRef();
      return;
   }
   
   if ( m_Shape == nullptr )
   {
      CComPtr<IPoint2d> point;
      pDO->GetPosition(&point);

      CComPtr<iDisplayList> pDL;
      pDO->GetDisplayList(&pDL);
      CComPtr<iDisplayMgr> pDispMgr;
      pDL->GetDisplayMgr(&pDispMgr);

      CComPtr<iCoordinateMap> map;
      pDispMgr->GetCoordinateMap(&map);

      // map the point to world space
      Float64 px, py;
      map->MPtoWP(point,&px,&py);

      m_BoundingBox.CoCreateInstance(CLSID_Rect2d);

      m_BoundingBox->put_Left(px);
      m_BoundingBox->put_Right(px);
      m_BoundingBox->put_Top(py);
      m_BoundingBox->put_Bottom(py);

      (*rect) = m_BoundingBox;
      (*rect)->AddRef();

      return;
   }


   if ( m_bHasBoundingShape )
   {
      CComPtr<IPoint2dCollection> points;
      GetPointsInWorldSpace(pDO,m_Shape,&points);

      IndexType nPoints;
      points->get_Count(&nPoints);
      Float64 left = DBL_MAX;
      Float64 right = -DBL_MAX;
      Float64 top = -DBL_MAX;
      Float64 bottom = DBL_MAX;

      for ( IndexType i = 0; i < nPoints; i++ )
      {
         CComPtr<IPoint2d> point;
         points->get_Item(i,&point);

         Float64 x,y;
         point->Location(&x, &y);

         left  = Min(left, x);
         right = Max(right,x);

         top    = Max(top,   y);
         bottom = Min(bottom,y);
      }

      m_BoundingBox.CoCreateInstance(CLSID_Rect2d);

      m_BoundingBox->put_Left(left);
      m_BoundingBox->put_Right(right);
      m_BoundingBox->put_Top(top);
      m_BoundingBox->put_Bottom(bottom);
   }
   else
   {
      m_Shape->get_BoundingBox(&m_BoundingBox);
   }

   (*rect) = m_BoundingBox;
   (*rect)->AddRef();
}

/////////////////////////////////////////////////////////
// iGravityWellStrategy Implementation
STDMETHODIMP_(void) CShapeDrawStrategyImpl::GetGravityWell(iDisplayObject* pDO, CRgn* pRgn)
{
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> map;
   pDispMgr->GetCoordinateMap(&map);

   CComPtr<IShape> pShape;
   if (m_CompositeShape)
   {
      CComPtr<ICompositeShapeItem> compShapeItem;
      m_CompositeShape->get_Item(0, &compShapeItem);
      compShapeItem->get_Shape(&pShape);
   }
   else
   {
      m_Shape.CopyTo(&pShape);
   }

   CComPtr<IPoint2dCollection> polypoints;
   GetPointsInWorldSpace(pDO, pShape, &polypoints);

   IndexType nPoints;
   polypoints->get_Count(&nPoints);

   CPoint* points = new CPoint[nPoints];
   for (IndexType i = 0; i < nPoints; i++)
   {
      CComPtr<IPoint2d> point;
      polypoints->get_Item(i, &point);

      map->WPtoLP(point, &points[i].x, &points[i].y);
   }

   VERIFY(pRgn->CreatePolygonRgn(points, (int)nPoints, ALTERNATE));

   delete[] points;
}

void CShapeDrawStrategyImpl::DrawMe(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   COLORREF line_color;
   COLORREF fill_color;

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   BOOL bIsSelected = pDO->IsSelected();

   if ( bIsSelected || bHighlite )
   {
      line_color = pDispMgr->GetSelectionLineColor();
      fill_color = pDispMgr->GetSelectionFillColor();
   }
   else
   {
      line_color = m_SolidLineColor;
      fill_color = m_SolidFillColor;
   }

   CPen solid_pen;
   CreatePen(m_SolidLineStyle,m_SolidLineWidth,line_color,solid_pen);

   CBrush solid_brush;
   if ( bIsSelected )
   {
      solid_brush.CreateHatchBrush(HS_DIAGCROSS,fill_color);
   }
   else
   {
      solid_brush.CreateSolidBrush(fill_color);
   }

   CPen void_pen;
   CreatePen(m_VoidLineStyle,m_VoidLineWidth,m_VoidLineColor,void_pen);

   CBrush void_brush(m_VoidFillColor);

   CPen* pOldPen = pDC->SelectObject(&solid_pen);
   CBrush* pOldBrush;
   
   if ( bHighlite )
   {
      // highlited always uses nullptr brush (not filled)
      pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
   }
   else
   {
      if ( m_bFill )
      {
         pOldBrush = pDC->SelectObject(&solid_brush);
      }
      else
      {
         pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
      }
   }


   if ( m_CompositeShape )
   {
      DrawShape(pDO,pDC,m_CompositeShape,solid_pen,solid_brush,void_pen,void_brush);
   }
   else
   {
      DrawShape(pDO,pDC,m_Shape);
   }


   pDC->SelectObject(pOldPen);
   pDC->SelectObject(pOldBrush);
}

void CShapeDrawStrategyImpl::DrawShape(iDisplayObject* pDO,CDC* pDC,ICompositeShape* pCompositeShape,CPen& solidPen,CBrush& solidBrush,CPen& voidPen,CBrush& voidBrush)
{
   IndexType nShapes;
   pCompositeShape->get_Count(&nShapes);
   for ( IndexType idx = 0; idx < nShapes; idx++ )
   {
      CComPtr<ICompositeShapeItem> item;
      pCompositeShape->get_Item(idx,&item);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      VARIANT_BOOL bVoid;
      item->get_Void(&bVoid);

      if ( bVoid == VARIANT_TRUE )
      {
         pDC->SelectObject(&voidPen);

         if ( m_bFill )
            pDC->SelectObject(&voidBrush);
         else
            pDC->SelectStockObject(NULL_BRUSH);
      }
      else
      {
         pDC->SelectObject(&solidPen);

         if ( m_bFill )
            pDC->SelectObject(&solidBrush);
         else
            pDC->SelectStockObject(NULL_BRUSH);
      }

      CComQIPtr<ICompositeShape> composite(shape);
      if ( composite )
      {
         DrawShape(pDO,pDC,composite,solidPen,solidBrush,voidPen,voidBrush);
      }
      else
      {
         DrawShape(pDO,pDC,shape);
      }
   }
}

void CShapeDrawStrategyImpl::DrawShape(iDisplayObject* pDO,CDC* pDC,IShape* pShape)
{
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> map;
   pDispMgr->GetCoordinateMap(&map);

   CComPtr<IPoint2dCollection> polypoints;
   GetPointsInWorldSpace(pDO,pShape,&polypoints);

   IndexType nPoints;
   polypoints->get_Count(&nPoints);

   CPoint* points = new CPoint[nPoints];
   for ( IndexType i = 0; i < nPoints; i++ )
   {
      CComPtr<IPoint2d> point;
      polypoints->get_Item(i,&point);

      map->WPtoLP(point,&points[i].x,&points[i].y);
   }

   pDC->Polygon(points,(int)nPoints);

   delete[] points;
}

void CShapeDrawStrategyImpl::GetPointsInWorldSpace(iDisplayObject* pDO,IShape* pShape,IPoint2dCollection** pPoints)
{
   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> map;
   pDispMgr->GetCoordinateMap(&map);

   CComPtr<IPoint2dCollection> polypoints;
   pShape->get_PolyPoints(&polypoints);

   IndexType nPoints;
   polypoints->get_Count(&nPoints);

   for ( IndexType i = 0; i < nPoints; i++ )
   {
      CComPtr<IPoint2d> point;
      polypoints->get_Item(i,&point);

      Float64 wx,wy;
      map->MPtoWP(point,&wx,&wy);
      CComPtr<IPoint2d> p;
      p.CoCreateInstance(CLSID_Point2d);
      p->Move(wx,wy);
      points->Add(p);
   }

   (*pPoints) = points;
   (*pPoints)->AddRef();
}

void CShapeDrawStrategyImpl::CreatePen(LineStyleType lineStyle,UINT width,COLORREF color,CPen& pen)
{
   DWORD centerStyle[] = { 20, 2, 3, 2 };
   LOGBRUSH lb;
   lb.lbStyle = BS_SOLID;
   lb.lbColor = color;
   lb.lbHatch = 0;
   switch(lineStyle)
   {
   case lsNull:
      pen.CreatePen(PS_NULL, width, color);
      break;

   case lsSolid:
      pen.CreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_JOIN_BEVEL, width, &lb);
      break;
      
   case lsDot:
      pen.CreatePen(PS_DOT,width,color);
      break;

   case lsDash:
      pen.CreatePen(PS_DASH,width,color);
      break;

   case lsCenterline:
      pen.CreatePen(PS_USERSTYLE | PS_GEOMETRIC,width,&lb,sizeof(centerStyle)/sizeof(DWORD),centerStyle);
      break;
   }
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <GeomModel/GeomModel.h>
CShapeDrawStrategyImpl2::CShapeDrawStrategyImpl2()
{
   m_SolidLineStyle = lsSolid;
   m_SolidLineColor = RGB(0, 0, 0); // black
   m_SolidFillColor = RGB(0, 0, 0); // black
   m_SolidLineWidth = 1;

   m_VoidLineStyle = lsSolid;
   m_VoidLineColor = RGB(255, 255, 255); // white
   m_VoidFillColor = RGB(255, 255, 255); // white
   m_VoidLineWidth = 1;

   m_bFill = false;
   m_bHasBoundingShape = true;
}

CShapeDrawStrategyImpl2::~CShapeDrawStrategyImpl2()
{
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::SetShape(const std::shared_ptr<const WBFL::Geometry::Shape>& shape)
{
   m_Shape = shape;
   m_CompositeShape = std::dynamic_pointer_cast<const WBFL::Geometry::CompositeShape>(m_Shape);

   m_BoundingBox.Release();
}

STDMETHODIMP_(const std::shared_ptr<const WBFL::Geometry::Shape>&) CShapeDrawStrategyImpl2::GetShape()
{
   return m_Shape;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::SetSolidLineStyle(LineStyleType lineStyle)
{
   m_SolidLineStyle = lineStyle;
}

STDMETHODIMP_(LineStyleType) CShapeDrawStrategyImpl2::GetSolidLineStyle()
{
   return m_SolidLineStyle;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::SetSolidLineColor(COLORREF crColor)
{
   m_SolidLineColor = crColor;
}

STDMETHODIMP_(COLORREF) CShapeDrawStrategyImpl2::GetSolidLineColor()
{
   return m_SolidLineColor;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::SetSolidFillColor(COLORREF crColor)
{
   m_SolidFillColor = crColor;
}

STDMETHODIMP_(COLORREF) CShapeDrawStrategyImpl2::GetSolidFillColor()
{
   return m_SolidFillColor;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::SetSolidLineWidth(UINT nPixels)
{
   m_SolidLineWidth = nPixels;
}

STDMETHODIMP_(UINT) CShapeDrawStrategyImpl2::GetSolidLineWidth()
{
   return m_SolidLineWidth;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::SetVoidLineStyle(LineStyleType lineStyle)
{
   m_VoidLineStyle = lineStyle;
}

STDMETHODIMP_(LineStyleType) CShapeDrawStrategyImpl2::GetVoidLineStyle()
{
   return m_VoidLineStyle;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::SetVoidLineColor(COLORREF crColor)
{
   m_VoidLineColor = crColor;
}

STDMETHODIMP_(COLORREF) CShapeDrawStrategyImpl2::GetVoidLineColor()
{
   return m_VoidLineColor;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::SetVoidFillColor(COLORREF crColor)
{
   m_VoidFillColor = crColor;
}

STDMETHODIMP_(COLORREF) CShapeDrawStrategyImpl2::GetVoidFillColor()
{
   return m_VoidFillColor;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::SetVoidLineWidth(UINT nPixels)
{
   m_VoidLineWidth = nPixels;
}

STDMETHODIMP_(UINT) CShapeDrawStrategyImpl2::GetVoidLineWidth()
{
   return m_VoidLineWidth;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::DoFill(bool doFill)
{
   m_bFill = doFill;
}

STDMETHODIMP_(bool) CShapeDrawStrategyImpl2::DoFill()
{
   return m_bFill;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::HasBoundingShape(bool bHasBoundingShape)
{
   m_bHasBoundingShape = bHasBoundingShape;
}

STDMETHODIMP_(bool) CShapeDrawStrategyImpl2::HasBoundingShape()
{
   return m_bHasBoundingShape;
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::Draw(iPointDisplayObject* pDO, CDC* pDC)
{
   DrawMe(pDO, pDC, false);
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::DrawHighlite(iPointDisplayObject* pDO, CDC* pDC, BOOL bHighlite)
{
   DrawMe(pDO, pDC, bHighlite);
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::DrawDragImage(iPointDisplayObject* pDO, CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
   ATLASSERT(false); // not implemented
//   map->LPtoWP(dragPoint.x, dragPoint.y, &m_CachePoint);
//
//   CRect r = pDO->GetBoundingBox();
//
//   COLORREF color;
//   color = RGB(0,0,255);
//
//   CPen pen(PS_SOLID,1,color);
//   CPen* pOldPen = pDC->SelectObject(&pen);
//   DrawMe(r,pDC);
//   pDC->SelectObject(pOldPen);
}

STDMETHODIMP_(void) CShapeDrawStrategyImpl2::GetBoundingBox(iPointDisplayObject* pDO, IRect2d** rect)
{
   if (m_BoundingBox)
   {
      (*rect) = m_BoundingBox;
      (*rect)->AddRef();
      return;
   }

   if (m_Shape == nullptr)
   {
      CComPtr<IPoint2d> point;
      pDO->GetPosition(&point);

      CComPtr<iDisplayList> pDL;
      pDO->GetDisplayList(&pDL);
      CComPtr<iDisplayMgr> pDispMgr;
      pDL->GetDisplayMgr(&pDispMgr);

      CComPtr<iCoordinateMap> map;
      pDispMgr->GetCoordinateMap(&map);

      // map the point to world space
      Float64 px, py;
      map->MPtoWP(point, &px, &py);

      m_BoundingBox.CoCreateInstance(CLSID_Rect2d);

      m_BoundingBox->put_Left(px);
      m_BoundingBox->put_Right(px);
      m_BoundingBox->put_Top(py);
      m_BoundingBox->put_Bottom(py);

      (*rect) = m_BoundingBox;
      (*rect)->AddRef();

      return;
   }


   if (m_bHasBoundingShape)
   {
      CComPtr<IPoint2dCollection> points;
      GetPointsInWorldSpace(pDO, m_Shape, &points);

      IndexType nPoints;
      points->get_Count(&nPoints);
      Float64 left = DBL_MAX;
      Float64 right = -DBL_MAX;
      Float64 top = -DBL_MAX;
      Float64 bottom = DBL_MAX;

      for (IndexType i = 0; i < nPoints; i++)
      {
         CComPtr<IPoint2d> point;
         points->get_Item(i, &point);

         Float64 x, y;
         point->Location(&x, &y);

         left = Min(left, x);
         right = Max(right, x);

         top = Max(top, y);
         bottom = Min(bottom, y);
      }

      m_BoundingBox.CoCreateInstance(CLSID_Rect2d);

      m_BoundingBox->put_Left(left);
      m_BoundingBox->put_Right(right);
      m_BoundingBox->put_Top(top);
      m_BoundingBox->put_Bottom(bottom);
   }
   else
   {
      m_BoundingBox.CoCreateInstance(CLSID_Rect2d);
      auto bbox = m_Shape->GetBoundingBox();
      m_BoundingBox->put_Left(bbox.Left());
      m_BoundingBox->put_Right(bbox.Right());
      m_BoundingBox->put_Top(bbox.Top());
      m_BoundingBox->put_Bottom(bbox.Bottom());
   }

   (*rect) = m_BoundingBox;
   (*rect)->AddRef();
}

/////////////////////////////////////////////////////////
// iGravityWellStrategy Implementation
STDMETHODIMP_(void) CShapeDrawStrategyImpl2::GetGravityWell(iDisplayObject* pDO, CRgn* pRgn)
{
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> map;
   pDispMgr->GetCoordinateMap(&map);

   std::shared_ptr<const WBFL::Geometry::Shape> shape;
   if (m_CompositeShape)
   {
      shape = m_CompositeShape->GetShape(0);
   }
   else
   {
      shape = m_Shape;
   }

   CComPtr<IPoint2dCollection> polypoints;
   GetPointsInWorldSpace(pDO, shape, &polypoints);

   IndexType nPoints;
   polypoints->get_Count(&nPoints);

   CPoint* points = new CPoint[nPoints];
   for (IndexType i = 0; i < nPoints; i++)
   {
      CComPtr<IPoint2d> point;
      polypoints->get_Item(i, &point);

      map->WPtoLP(point, &points[i].x, &points[i].y);
   }

   VERIFY(pRgn->CreatePolygonRgn(points, (int)nPoints, ALTERNATE));

   delete[] points;
}

void CShapeDrawStrategyImpl2::DrawMe(iPointDisplayObject* pDO, CDC* pDC, BOOL bHighlite)
{
   COLORREF line_color;
   COLORREF fill_color;

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   BOOL bIsSelected = pDO->IsSelected();

   if (bIsSelected || bHighlite)
   {
      line_color = pDispMgr->GetSelectionLineColor();
      fill_color = pDispMgr->GetSelectionFillColor();
   }
   else
   {
      line_color = m_SolidLineColor;
      fill_color = m_SolidFillColor;
   }

   CPen solid_pen;
   CreatePen(m_SolidLineStyle, m_SolidLineWidth, line_color, solid_pen);

   CBrush solid_brush;
   if (bIsSelected)
   {
      solid_brush.CreateHatchBrush(HS_DIAGCROSS, fill_color);
   }
   else
   {
      solid_brush.CreateSolidBrush(fill_color);
   }

   CPen void_pen;
   CreatePen(m_VoidLineStyle, m_VoidLineWidth, m_VoidLineColor, void_pen);

   CBrush void_brush(m_VoidFillColor);

   CPen* pOldPen = pDC->SelectObject(&solid_pen);
   CBrush* pOldBrush;

   if (bHighlite)
   {
      // highlited always uses nullptr brush (not filled)
      pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
   }
   else
   {
      if (m_bFill)
      {
         pOldBrush = pDC->SelectObject(&solid_brush);
      }
      else
      {
         pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
      }
   }


   if (m_CompositeShape)
   {
      DrawShape(pDO, pDC, m_CompositeShape, solid_pen, solid_brush, void_pen, void_brush);
   }
   else
   {
      DrawShape(pDO, pDC, m_Shape);
   }


   pDC->SelectObject(pOldPen);
   pDC->SelectObject(pOldBrush);
}

void CShapeDrawStrategyImpl2::DrawShape(iDisplayObject* pDO, CDC* pDC, const std::shared_ptr<const WBFL::Geometry::CompositeShape>& compositeShape, CPen& solidPen, CBrush& solidBrush, CPen& voidPen, CBrush& voidBrush)
{
   IndexType nShapes = compositeShape->GetShapeCount();
   for (IndexType idx = 0; idx < nShapes; idx++)
   {
      const auto& shape = compositeShape->GetShape(idx);

      if (compositeShape->IsVoid(idx))
      {
         pDC->SelectObject(&voidPen);

         if (m_bFill)
            pDC->SelectObject(&voidBrush);
         else
            pDC->SelectStockObject(NULL_BRUSH);
      }
      else
      {
         pDC->SelectObject(&solidPen);

         if (m_bFill)
            pDC->SelectObject(&solidBrush);
         else
            pDC->SelectStockObject(NULL_BRUSH);
      }

      std::shared_ptr<const WBFL::Geometry::CompositeShape> composite = std::dynamic_pointer_cast<const WBFL::Geometry::CompositeShape>(shape);
      if (composite)
      {
         DrawShape(pDO, pDC, composite, solidPen, solidBrush, voidPen, voidBrush);
      }
      else
      {
         DrawShape(pDO, pDC, shape);
      }
   }
}

void CShapeDrawStrategyImpl2::DrawShape(iDisplayObject* pDO, CDC* pDC, const std::shared_ptr<const WBFL::Geometry::Shape>& shape)
{
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> map;
   pDispMgr->GetCoordinateMap(&map);

   CComPtr<IPoint2dCollection> polypoints;
   GetPointsInWorldSpace(pDO, shape, &polypoints);

   IndexType nPoints;
   polypoints->get_Count(&nPoints);

   CPoint* points = new CPoint[nPoints];
   for (IndexType i = 0; i < nPoints; i++)
   {
      CComPtr<IPoint2d> point;
      polypoints->get_Item(i, &point);

      map->WPtoLP(point, &points[i].x, &points[i].y);
   }

   pDC->Polygon(points, (int)nPoints);

   delete[] points;
}

void CShapeDrawStrategyImpl2::GetPointsInWorldSpace(iDisplayObject* pDO, const std::shared_ptr<const WBFL::Geometry::Shape>& shape, IPoint2dCollection** pPoints)
{
   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> map;
   pDispMgr->GetCoordinateMap(&map);

   auto poly_points = shape->GetPolyPoints();
   for(const auto& point : poly_points)
   {
      Float64 wx, wy;
      map->MPtoWP(point.X(),point.Y(), &wx, &wy);
      CComPtr<IPoint2d> p;
      p.CoCreateInstance(CLSID_Point2d);
      p->Move(wx, wy);
      points->Add(p);
   }

   (*pPoints) = points;
   (*pPoints)->AddRef();
}

void CShapeDrawStrategyImpl2::CreatePen(LineStyleType lineStyle, UINT width, COLORREF color, CPen& pen)
{
   DWORD centerStyle[] = { 20, 2, 3, 2 };
   LOGBRUSH lb;
   lb.lbStyle = BS_SOLID;
   lb.lbColor = color;
   lb.lbHatch = 0;
   switch (lineStyle)
   {
   case lsNull:
      pen.CreatePen(PS_NULL, width, color);
      break;

   case lsSolid:
      pen.CreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_JOIN_BEVEL, width, &lb);
      break;

   case lsDot:
      pen.CreatePen(PS_DOT, width, color);
      break;

   case lsDash:
      pen.CreatePen(PS_DASH, width, color);
      break;

   case lsCenterline:
      pen.CreatePen(PS_USERSTYLE | PS_GEOMETRIC, width, &lb, sizeof(centerStyle) / sizeof(DWORD), centerStyle);
      break;
   }
}


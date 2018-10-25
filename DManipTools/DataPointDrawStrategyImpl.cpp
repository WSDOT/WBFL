///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright (C) 2008  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#include "stdafx.h"
#include "DataPointDrawStrategyImpl.h"
#include "mfcdual.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// default symbol size in twips
static const long SSIZE = 1440 * 3/32;

CDataPointDrawStrategyImpl::CDataPointDrawStrategyImpl():
m_Color( RGB(200,0,0) ),
m_FontFace("Symbol"),
m_FontSize(80),
m_CharCode(0)
{
}

CDataPointDrawStrategyImpl::~CDataPointDrawStrategyImpl()
{
}


BEGIN_INTERFACE_MAP(CDataPointDrawStrategyImpl,CCmdTarget)
   INTERFACE_PART(CDataPointDrawStrategyImpl,IID_iDrawPointStrategy,DrawPointStrategy)
   INTERFACE_PART(CDataPointDrawStrategyImpl,IID_iDataPointDrawStrategy,Strategy)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CDataPointDrawStrategyImpl,DrawPointStrategy);
DELEGATE_CUSTOM_INTERFACE(CDataPointDrawStrategyImpl,Strategy);

STDMETHODIMP_(void) CDataPointDrawStrategyImpl::XStrategy::get_SymbolFontFace(char* *pVal)
{
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,Strategy);

   int nChar = pThis->m_FontFace.GetLength()+1;
   *pVal = new char[nChar];
   strcpy_s(*pVal, nChar, pThis->m_FontFace);
}

STDMETHODIMP_(void) CDataPointDrawStrategyImpl::XStrategy::put_SymbolFontFace(const char* newVal)
{
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,Strategy);

   pThis->m_FontFace = newVal;
}

STDMETHODIMP_(long) CDataPointDrawStrategyImpl::XStrategy::get_SymbolSize()
{
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,Strategy);

   return pThis->m_FontSize;
}

STDMETHODIMP_(void) CDataPointDrawStrategyImpl::XStrategy::put_SymbolSize(long size)
{
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,Strategy);

   if (size>20)
      pThis->m_FontSize = size;
   else
      ATLASSERT(0); // are you sure you want smaller than a two point font?
}

STDMETHODIMP_(DWORD) CDataPointDrawStrategyImpl::XStrategy::get_SymbolCharacterCode()
{
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,Strategy);

   return pThis->m_CharCode;
}

STDMETHODIMP_(void) CDataPointDrawStrategyImpl::XStrategy::put_SymbolCharacterCode(DWORD code)
{
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,Strategy);

   pThis->m_CharCode = code;
}

STDMETHODIMP_(COLORREF) CDataPointDrawStrategyImpl::XStrategy::get_Color()
{
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,Strategy);

   return pThis->m_Color;
}

STDMETHODIMP_(void) CDataPointDrawStrategyImpl::XStrategy::put_Color(COLORREF color)
{
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,Strategy);

   pThis->m_Color = color;
}

STDMETHODIMP_(void) CDataPointDrawStrategyImpl::XDrawPointStrategy::Draw(iPointDisplayObject* pDO,CDC* pDC)
{
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,DrawPointStrategy);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   COLORREF color;

   if ( pDO->IsSelected() )
      color = pDispMgr->GetSelectionLineColor();
   else
      color = pThis->m_Color;

   CComPtr<IPoint2d> pos;
   pDO->GetPosition(&pos);

   pThis->Draw(pDO,pDC,color,pos);
}

STDMETHODIMP_(void) CDataPointDrawStrategyImpl::XDrawPointStrategy::DrawHighlite(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,DrawPointStrategy);
   Draw(pDO,pDC);
}

STDMETHODIMP_(void) CDataPointDrawStrategyImpl::XDrawPointStrategy::DrawDragImage(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& cpdragPoint)
{
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,DrawPointStrategy);

   CComPtr<IPoint2d> dragPoint;
   map->LPtoWP(cpdragPoint.x, cpdragPoint.y, &dragPoint);

   pThis->Draw(pDO,pDC,RGB(255,0,0),dragPoint);
}

STDMETHODIMP_(void) CDataPointDrawStrategyImpl::XDrawPointStrategy::GetBoundingBox(iPointDisplayObject* pDO,IRect2d** box)
{ 
   METHOD_PROLOGUE(CDataPointDrawStrategyImpl,DrawPointStrategy);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   // height of cut above/below girder
   Float64 xo,yo;
   pMap->TPtoWP(0,0,&xo,&yo);
   Float64 x2,y2;
   pMap->TPtoWP(SSIZE,SSIZE,&x2,&y2);

   Float64 width = (x2-xo)/2.0;
   Float64 height = (y2-yo)/2.0;

   CComPtr<IPoint2d> point;
   pDO->GetPosition(&point);
   Float64 xp, yp;
   point->get_X(&xp);
   point->get_Y(&yp);

   CComPtr<IRect2d> bounding_box;
   bounding_box.CoCreateInstance(CLSID_Rect2d);

   bounding_box->put_Top(yp + height);
   bounding_box->put_Left(xp - width);
   bounding_box->put_Bottom(yp - height);
   bounding_box->put_Right(xp + width);

   (*box) = bounding_box;
   (*box)->AddRef();
}

void CDataPointDrawStrategyImpl::Draw(iPointDisplayObject* pDO,CDC* pDC,COLORREF color,IPoint2d* loc)
{
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   long cx,cy;
   pMap->WPtoLP(loc,&cx,&cy);

	if (m_CharCode==0)
   {
      // draw nothing
   }
   else
   {
      COLORREF old_col = pDC->SetTextColor(m_Color);

      CFont font;
      font.CreatePointFont(m_FontSize, m_FontFace, pDC);
      CFont* old_font = pDC->SelectObject(&font);

      CRect rect(0,0,0,0);
      pDC->DrawText( (LPCTSTR)&m_CharCode, 1, &rect, DT_CALCRECT);
      long wid2 = rect.Width()/2;
      long hgt2 = rect.Height()/2;

      CRect newrect(cx-wid2, cy-hgt2, cx+wid2, cy+hgt2);
      pDC->DrawText( (LPCTSTR)&m_CharCode, 1, &newrect, DT_CENTER|DT_VCENTER|DT_NOCLIP);

      pDC->SelectObject(old_font);
      pDC->SetTextColor(old_col);
   }
}

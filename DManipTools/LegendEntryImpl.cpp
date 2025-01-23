///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2025  Washington State Department of Transportation
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

// LegendEntryImpl.cpp : Implementation of CLegendEntryImpl
#include "stdafx.h"
#include <WBFLDManipTools.h>
#include "DManipTools\DManipTools.h"
#include "LegendEntryImpl.h"

#include "DataPointDrawStrategyImpl.h"
#include "DataPointEventsImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLegendEntryImpl

CLegendEntryImpl::CLegendEntryImpl():
m_FontFace("Symbol"),
m_FontSize(120),
m_CharCode(0),
m_Color(RGB(200,0,0)),
m_DoDrawLine(FALSE)
{
}


STDMETHODIMP CLegendEntryImpl::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_iLegendEntry
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP_(void) CLegendEntryImpl::get_Name(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Name.CopyTo(pVal);
}

STDMETHODIMP_(void) CLegendEntryImpl::put_Name(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Name = newVal;

}

STDMETHODIMP_(void) CLegendEntryImpl::get_SymbolFontFace(TCHAR* *pVal)
{
   int nChar = m_FontFace.GetLength()+1;
   *pVal = new TCHAR[nChar];
   _tcscpy_s(*pVal,nChar,m_FontFace);
}

STDMETHODIMP_(void) CLegendEntryImpl::put_SymbolFontFace(LPCTSTR newVal)
{
   m_FontFace = CString(newVal);
}

STDMETHODIMP_(long) CLegendEntryImpl::get_SymbolSize()
{
   return m_FontSize;
}

STDMETHODIMP_(void) CLegendEntryImpl::put_SymbolSize(long size)
{
   if (size>20)
      m_FontSize = size;
   else
      ATLASSERT(false); // are you sure you want smaller than a two point font?
}

STDMETHODIMP_(DWORD) CLegendEntryImpl::get_SymbolCharacterCode()
{
   return m_CharCode;
}

STDMETHODIMP_(void) CLegendEntryImpl::put_SymbolCharacterCode(DWORD code)
{
   m_CharCode = code;
}

STDMETHODIMP_(COLORREF) CLegendEntryImpl::get_Color()
{
   return m_Color;
}

STDMETHODIMP_(void) CLegendEntryImpl::put_Color(COLORREF color)
{
   m_Color = color;
}

STDMETHODIMP_(void) CLegendEntryImpl::get_DoDrawLine(BOOL* doDraw)
{
   *doDraw = m_DoDrawLine;
}

STDMETHODIMP_(void) CLegendEntryImpl::put_DoDrawLine(BOOL doDraw)
{
   m_DoDrawLine = doDraw;
}


STDMETHODIMP_(void) CLegendEntryImpl::Draw(CDC *pDC, CRect& drawRect, BOOL beingDragged)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (m_CharCode==0 && !m_DoDrawLine)
   {
      // fill rect solid
      CBrush brush(m_Color);
      CPen back_pen(PS_SOLID, 1, m_Color);
      CBrush* pold_brush = pDC->SelectObject(&brush);
      CPen* pold_pen = pDC->SelectObject(&back_pen);

      pDC->Rectangle(drawRect);

      pDC->SelectObject(&pold_brush);
      pDC->SelectObject(&pold_pen);
   }
   else
   {
      long midy =(drawRect.top + drawRect.bottom)/2;

      if (m_DoDrawLine)
      {
         CPen pen(PS_SOLID, 3, m_Color);
         CPen* old_pen = pDC->SelectObject(&pen);

         pDC->MoveTo(drawRect.left, midy);
         pDC->LineTo(drawRect.right, midy);

         pDC->SelectObject(old_pen);
      }

      if (!beingDragged && m_CharCode!=0)
      {
         COLORREF old_col = pDC->SetTextColor(m_Color);
         CFont font;
         font.CreatePointFont(m_FontSize, m_FontFace, pDC);
         CFont* old_font = pDC->SelectObject(&font);

         CRect rect(0,0,0,0);
         pDC->DrawText( (LPCTSTR)&m_CharCode, 1, &rect, DT_CALCRECT);
         long hgt2 = 1 + rect.Height()/2;

         long midx = (drawRect.left+drawRect.right)/2;

         UINT old_align = pDC->SetTextAlign(TA_CENTER|TA_TOP);
         pDC->TextOut(midx, midy-hgt2, (LPCTSTR)&m_CharCode, 1);

         pDC->SetTextAlign(old_align);
         pDC->SelectObject(old_font);
         pDC->SetTextColor(old_col);
      }
   }
}

STDMETHODIMP_(HRESULT) CLegendEntryImpl::CreateDataPoint(Float64 dataX, Float64 dataY, 
                                                         Float64 graphX, Float64 graphY, 
                                                         iDisplayObject** dataPoint)
{
   CComPtr<IPoint2d> mpnt;
   HRESULT hr = mpnt.CoCreateInstance(CLSID_Point2d);
   if (FAILED(hr))
      return hr;
   mpnt->put_X(graphX);
   mpnt->put_Y(graphY);

   // data point
   CComPtr<iPointDisplayObject> dp_rep;
   ::CoCreateInstance(CLSID_PointDisplayObject,nullptr,CLSCTX_ALL,IID_iPointDisplayObject,(void**)&dp_rep);

   CDataPointDrawStrategyImpl* pDisplayImpl = new CDataPointDrawStrategyImpl();
   iDrawPointStrategy* pidp = (iDrawPointStrategy*)pDisplayImpl->GetInterface(&IID_iDrawPointStrategy);
   dp_rep->SetDrawingStrategy(pidp);
   pidp->Release();

   dp_rep->SetPosition(mpnt,FALSE,FALSE);

   CDataPointEventsImpl* pEvents = new CDataPointEventsImpl();
   IUnknown* iunk = pEvents->GetInterface(&IID_IUnknown);
   CComQIPtr<iDisplayObjectEvents,&IID_iDisplayObjectEvents> events(iunk);
   dp_rep->RegisterEventSink(events);
   iunk->Release();

   CComQIPtr<iDataPointDrawStrategy,&IID_iDataPointDrawStrategy> dp_draw(pDisplayImpl->GetInterface(&IID_IUnknown));
   ATLASSERT(dp_draw!=nullptr);
   dp_draw->put_Color(m_Color);
   dp_draw->put_SymbolCharacterCode(m_CharCode);
   dp_draw->put_SymbolSize(m_FontSize);
   dp_draw->put_SymbolFontFace(m_FontFace);
/*
   CComQIPtr<iDragData,&IID_iDragData> dd(pEvents->GetInterface(&IID_IUnknown));
   CComQIPtr<iDraggable,&IID_iDraggable> draggable(dp_rep);
   draggable->SetDragData(dd); 
*/
   CComQIPtr<iConnectable,&IID_iConnectable> dp_connectable(dp_rep);
   CComPtr<iSocket> socket;
   dp_connectable->AddSocket(0,mpnt,&socket);

   // tool tips
   CString strToolTipText;
   strToolTipText.Format(_T("(%f, %f)"), dataX, dataY);
   dp_rep->SetToolTipText(strToolTipText);

   return dp_rep.QueryInterface(dataPoint);
}

STDMETHODIMP_(HRESULT) CLegendEntryImpl::GetClassID(CLSID *pClassID)
{
   *pClassID = CLSID_LegendEntry;
   return S_OK;
}

STDMETHODIMP_(void) CLegendEntryImpl::WriteDragData(iDragDataSink* pSink, UINT cfFormat)
{
   // name
   long len = m_Name.Length();
   pSink->Write(cfFormat,&len,sizeof(long));
   if (len>0)
   {
      BSTR tstr = m_Name.m_str;
      pSink->Write(cfFormat,tstr,len*sizeof(wchar_t)); // string data
   }

   // font face
   len = m_FontFace.GetLength();
   pSink->Write(cfFormat,&len,sizeof(long));
   pSink->Write(cfFormat,(void*)LPCTSTR(m_FontFace),len*sizeof(TCHAR));
  
   pSink->Write(cfFormat,&m_FontSize,sizeof(long));
   pSink->Write(cfFormat,&m_CharCode,sizeof(DWORD));
   pSink->Write(cfFormat,&m_Color,sizeof(COLORREF));
   pSink->Write(cfFormat,&m_DoDrawLine,sizeof(BOOL));
}

STDMETHODIMP_(void) CLegendEntryImpl::ReadDragData(iDragDataSource* pSource, UINT cfFormat)
{
   long len;
   // name
   pSource->Read(cfFormat,&len,sizeof(long));
   wchar_t* wstr = new wchar_t[len+1];

   if (len>0)
      pSource->Read(cfFormat,wstr,len*sizeof(wchar_t)); 

   wstr[len] = _T('\0');
   m_Name = wstr;

   delete[] wstr;

   // font face
   pSource->Read(cfFormat,&len,sizeof(long));
   TCHAR* tstr = new TCHAR[len+1];

   if (len>0)
      pSource->Read(cfFormat,tstr,len*sizeof(TCHAR)); 

   tstr[len] = _T('\0');
   m_FontFace = tstr;

   delete[] tstr;
  
   pSource->Read(cfFormat,&m_FontSize,sizeof(long));
   pSource->Read(cfFormat,&m_CharCode,sizeof(DWORD));
   pSource->Read(cfFormat,&m_Color,sizeof(COLORREF));
   pSource->Read(cfFormat,&m_DoDrawLine,sizeof(BOOL));
}

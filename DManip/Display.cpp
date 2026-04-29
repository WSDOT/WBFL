///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2026  Washington State Department of Transportation
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

#include "pch.h"
#include <DManip/Display.h>
#include <DManip/DisplayMgrImpl.h>
#include <DManip/MappingImpl.h>

#include <ShellScalingApi.h> // needed for Per Monitor DPI information



/////////////////////////////////////////////////////////////////////////////
// CDisplay

CDisplay::CDisplay(CWnd* pWnd)
{
	m_pWnd = pWnd;
}

const CWnd* CDisplay::GetWnd() const
{
	return m_pWnd;
}

CWnd* CDisplay::GetWnd()
{
	return m_pWnd;
}

std::shared_ptr<WBFL::DManip::iDisplayMgr> CDisplay::GetDisplayMgr()
{
	return m_pDispMgr;
}

std::shared_ptr<const WBFL::DManip::iDisplayMgr> CDisplay::GetDisplayMgr() const
{
	return m_pDispMgr;
}

void CDisplay::CenterOnPoint(const WBFL::Geometry::Point2d& wPoint, bool reDraw)
{
	// get center of adjusted world extents
	const auto& origin = m_pMapping->GetWorldOrg();
	auto ext = m_pMapping->GetAdjustedWorldExt();

	auto center = origin + ext / 2.0;

	// compute distance between centers and offset world view rect this much
	auto offset = wPoint - center;

	auto new_origin = origin + offset;
	m_pMapping->SetWorldOrg(new_origin);

	if (reDraw)
		m_pWnd->Invalidate();
}

void CDisplay::CenterOnPoint(CPoint center, bool reDraw)
{
	// move world rect required distance
	auto wPoint = m_pCoordinateMap->LPtoWP(center.x, center.y);

	CenterOnPoint(wPoint, reDraw);
}

void CDisplay::SetWorldViewRect(const WBFL::Geometry::Rect2d& rect)
{
	m_pMapping->SetWorldOrg(rect.Left(), rect.Bottom());
	m_pMapping->SetWorldExt(rect.Width(), rect.Height());
}

void CDisplay::Zoom(CRect rect, bool reDraw)
{
	rect.NormalizeRect();

	Float64 wbot, wleft, wtop, wright;
	m_pCoordinateMap->LPtoWP(rect.left, rect.bottom, &wleft, &wbot);
	m_pCoordinateMap->LPtoWP(rect.right, rect.top, &wright, &wtop);

	WBFL::Geometry::Rect2d wrect(wleft, wbot, wright, wtop);
	wrect.Normalize();

	Zoom(wrect, reDraw);
}

void CDisplay::Zoom(const WBFL::Geometry::Rect2d& rect, bool reDraw)
{
	SetWorldViewRect(rect);
	CenterOnPoint(rect.Center(), reDraw);
}

void CDisplay::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT_VALID(pDC);
	UNUSED(pDC); // unused in release builds

	// Default to one page printing if doc length not known
	if (pInfo != NULL)
		pInfo->m_bContinuePrinting =
		(pInfo->GetMaxPage() != 0xffff || (pInfo->m_nCurPage == 1));


	pDC->SetMapMode(m_nMapMode);
	m_pMapping->PrepareDC(pDC);
}

void CDisplay::OnCleanUpDC(CDC* pDC, CPrintInfo* pInfo)
{
	m_pMapping->CleanUpDC(pDC);
}


void CDisplay::SetMapMode(int mapMode)
{
	m_nMapMode = mapMode;
}

int CDisplay::GetMapMode() const
{
	return m_nMapMode;
}

std::shared_ptr<const WBFL::DManip::iCoordinateMap> CDisplay::GetCoordinateMap() const
{
	return m_pCoordinateMap;
}

CRect CDisplay::GetViewRect() const
{
	CRect rDisp;
	if (m_IsPrinting)
		rDisp = m_PrintingRect;
	else
		GetWnd()->GetClientRect(&rDisp);

	return rDisp;
}

void CDisplay::ScaleFont(LOGFONT& lfFont) const
{
	HMONITOR hMonitor = MonitorFromWindow(m_pWnd->GetSafeHwnd(), MONITOR_DEFAULTTONEAREST);
	UINT Xdpi, Ydpi;
	HRESULT hr = GetDpiForMonitor(hMonitor, MDT_DEFAULT, &Xdpi, &Ydpi);
	ATLASSERT(Xdpi == Ydpi);

	lfFont.lfHeight = MulDiv(lfFont.lfHeight, Xdpi, USER_DEFAULT_SCREEN_DPI);
}

DROPEFFECT CDisplay::CanDrop(COleDataObject* pDataObject, DWORD dwKeyState, const WBFL::Geometry::Point2d& point)
{
	return DROPEFFECT_NONE;
}

void CDisplay::OnDropped(COleDataObject* pDataObject, DROPEFFECT dropEffect, const WBFL::Geometry::Point2d& point)
{
	// Do nothing
}
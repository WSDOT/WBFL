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


#pragma once

#include <DManip/DManipExp.h>
#include <DManip/CoordinateMap.h>
#include <DManip/Mapping.h>
#include <DManip/DisplayMgr.h>
#include <afxwin.h>

class DMANIPCLASS CDisplay
{

public:
    CDisplay(CWnd* pWnd);

    const CWnd* GetWnd() const;

	CWnd* GetWnd();

    std::shared_ptr<WBFL::DManip::iDisplayMgr> GetDisplayMgr();
    std::shared_ptr<const WBFL::DManip::iDisplayMgr> GetDisplayMgr() const;

    /// @brief Zooms the view to a rectangle
    void Zoom(CRect rect, bool reDraw = true);
    void Zoom(const WBFL::Geometry::Rect2d& rect, bool reDraw = true);

    void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = nullptr);

    /// @brief Pan such that the specified point is in the center of the client area.
    void CenterOnPoint(CPoint center, bool reDraw = true);
    void CenterOnPoint(const WBFL::Geometry::Point2d& wOrg, bool reDraw = true);

    void SetMapMode(int mapMode);

    int GetMapMode() const;

    std::shared_ptr<const WBFL::DManip::iCoordinateMap> GetCoordinateMap() const;

    CRect GetViewRect() const;

    /// @brief Scales font size (point size) for high DPI devices
    void ScaleFont(LOGFONT& lfFont) const;


    virtual DROPEFFECT CanDrop(COleDataObject* pDataObject, DWORD dwKeyState, const WBFL::Geometry::Point2d& point);
    virtual void OnDropped(COleDataObject* pDataObject, DROPEFFECT dropEffect, const WBFL::Geometry::Point2d& point);

protected:

    void SetWorldViewRect(const WBFL::Geometry::Rect2d& rect);

    // current mapping
    std::shared_ptr<WBFL::DManip::iMapping>        m_pMapping;
    std::shared_ptr<WBFL::DManip::iCoordinateMap>  m_pCoordinateMap;

    CWnd* m_pWnd;

    std::shared_ptr<WBFL::DManip::iDisplayMgr> m_pDispMgr;

    int m_nMapMode = MM_TEXT;

    bool m_IsPrinting;
    CRect m_PrintingRect;


public:
    // Virtual required to clean up DC for mapping functionality. This is called from OnPaint.
    // If you need to override OnPaint, you MUST call this function after OnDraw.
    // If you need a client DC, use the CDManipClientDC class defined below - it will take 
    // care of the initialization and clean up for you.
    virtual void OnCleanUpDC(CDC* pDC, CPrintInfo* pInfo = nullptr);
};


/////////////////////////////////////////////////////////////////////////////

// Utility class for creating local client DC's. Use this class along with 
// CDisplayView if you need a local DC and it will properly initialize mapping
// and clean up after itself
class CDManipClientDC : public CClientDC
{
public:

    CDManipClientDC(CDisplay* disp) :
        m_pDisp(disp),
        CClientDC(disp->GetWnd())
    {
        disp->OnPrepareDC(this);
    }

    virtual ~CDManipClientDC()
    {
        m_pDisp->OnCleanUpDC(this);
    }

private:
    CDisplay* m_pDisp;
};

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


#pragma once

#include <DManip/DManipExp.h>
#include <DManip/DisplayMgr.h>
#include <DManip/CoordinateMap.h>
#include <DManip/Mapping.h>

class WBFL::DManip::iTask;
class WBFL::DManip::TaskFactory;



/// @brief The display view canvas.
class DMANIPCLASS CDisplayView : public CScrollView
{
protected:
	CDisplayView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDisplayView)

// Attributes
public:
   std::shared_ptr<WBFL::DManip::iDisplayMgr> GetDisplayMgr();
   std::shared_ptr<const WBFL::DManip::iDisplayMgr> GetDisplayMgr() const;
   CRect GetViewRect() const;

// Operations
public:
   virtual DROPEFFECT CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,const WBFL::Geometry::Point2d& point);
   virtual void OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect, const WBFL::Geometry::Point2d& point);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayView)
public:
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) override;
	virtual void OnDragLeave() override;
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) override;
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) override;
   virtual DROPEFFECT OnDragScroll( DWORD dwKeyState, CPoint point ) override;
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = nullptr) override;
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const override;
protected:
	virtual void OnDraw(CDC* pDC) override;      // overridden to draw this view
	virtual void OnInitialUpdate() override;     // first time after construct
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) override;
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) override;
	//}}AFX_VIRTUAL

   void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo,CRect rcDraw);

public:
   // Virtual required to clean up DC for mapping functionality. This is called from OnPaint.
   // If you need to override OnPaint, you MUST call this function after OnDraw.
   // If you need a client DC, use the CDManipClientDC class defined below - it will take 
   // care of the initialization and clean up for you.
	virtual void OnCleanUpDC(CDC* pDC, CPrintInfo* pInfo = nullptr);

public:
   std::shared_ptr<const WBFL::DManip::iCoordinateMap> GetCoordinateMap() const;

   /// @brief Sets the mapping mode
   void SetMappingMode(WBFL::DManip::MapMode mm, bool reDraw=true);
   WBFL::DManip::MapMode GetMappingMode();

   /// @brief Scales the world space to fit within the window
   void ScaleToFit(bool reDraw=true);

   /// @brief Pan such that the specified point is in the center of the client area.
   void CenterOnPoint(CPoint center, bool reDraw=true);
   void CenterOnPoint(const WBFL::Geometry::Point2d& wOrg, bool reDraw=true);

   /// @brief Activates a task whereby the user centers the canvas on a point by left button mouse click
   void ActivateCenterOnPointTask();

   /// @brief Zooms the view to a rectangle
   void Zoom(CRect rect, bool reDraw=true);
   void Zoom(const WBFL::Geometry::Rect2d& rect, bool reDraw=true);
   /// @brief Zoomes the view by apply a scaling factor
   void Zoom(Float64 factor, bool reDraw=true);

   /// @brief Actives a task whereby the user zooms in on the canvas by drawing a rectangle with the mouse
   void ActivateZoomTask();

   /// @brief Scales font size (point size) for high DPI devices
   void ScaleFont(LOGFONT& lfFont) const;

// Implementation
protected:
	virtual ~CDisplayView();
#ifdef _DEBUG
	virtual void AssertValid() const override;
	virtual void Dump(CDumpContext& dc) const override;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDisplayView)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnContextMenu(CWnd* pWnd,CPoint point);
   afx_msg void OnDestroy();
	afx_msg void OnPaint();
	//}}AFX_MSG
   afx_msg BOOL OnNeedToolTipText(UINT id,NMHDR* pNMHDR,LRESULT* pResult);
	DECLARE_MESSAGE_MAP()


protected:
   // set up world to logical mapping via rectangles. This is used by 
   // the panning and zooming functionality. You can override this 
   // by using the iMapping interface directly in your subclass
   void SetLogicalViewRect(int mapMode, CRect rect);
   RECT GetLogicalViewRect();
   void SetWorldViewRect(const WBFL::Geometry::Rect2d& rect);

   CRect GetAdjustedLogicalViewRect();
   WBFL::Geometry::Rect2d GetAdjustedWorldViewRect();

   std::shared_ptr<WBFL::DManip::iDisplayMgr>       m_pDispMgr;

   // current mapping
   std::shared_ptr<WBFL::DManip::iMapping>          m_pMapping;
   std::shared_ptr<WBFL::DManip::iCoordinateMap>    m_pCoordinateMap;

   // different mappings for screen and printer. to be switched back
   // and forth at print time
   std::shared_ptr<WBFL::DManip::iMapping>          m_pPrinterMapping;
   std::shared_ptr<WBFL::DManip::iCoordinateMap>    m_pPrinterCoordinateMap;
   std::shared_ptr<WBFL::DManip::iMapping>          m_pScreenMapping;
   std::shared_ptr<WBFL::DManip::iCoordinateMap>    m_pScreenCoordinateMap;

   bool m_IsPrinting;
   CRect m_PrintingRect;

   // Last resort event handler if display objects event sinks and display list event sinks
   // don't handle the event... default implementations do nothing. Override these methods
   // in subclasses
   virtual void HandleLButtonDown(UINT nFlags, CPoint logPoint);
	virtual void HandleLButtonUp(UINT nFlags, CPoint logPoint);
	virtual void HandleLButtonDblClk(UINT nFlags, CPoint logPoint);
	virtual void HandleRButtonDown(UINT nFlags, CPoint logPoint);
	virtual void HandleRButtonUp(UINT nFlags, CPoint logPoint);
	virtual void HandleRButtonDblClk(UINT nFlags, CPoint logPoint);
	virtual void HandleMouseMove(UINT nFlags, CPoint logPoint);
	virtual void HandleMouseWheel(UINT nFlags, short zDelta, CPoint logPoint);
	virtual void HandleKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void HandleContextMenu(CWnd* pWnd,CPoint logPoint);
public:
   afx_msg void OnSize(UINT nType, int cx, int cy);
};

/////////////////////////////////////////////////////////////////////////////

// Utility class for creating local client DC's. Use this class along with 
// CDisplayView if you need a local DC and it will properly initialize mapping
// and clean up after itself
class CDManipClientDC : public CClientDC
{
public:

   CDManipClientDC(CDisplayView* view):
   m_pView(view),
   CClientDC(view)
   {
      view->OnPrepareDC(this);
   }

   virtual ~CDManipClientDC()
   {
      m_pView->OnCleanUpDC(this);
   }

private:
   CDisplayView* m_pView;
};

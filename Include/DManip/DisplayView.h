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
#include <DManip/Display.h>

class WBFL::DManip::iTask;
class WBFL::DManip::TaskFactory;



/// @brief The display view canvas.
class DMANIPCLASS CDisplayView : public CScrollView, public CDisplay
{
protected:
	CDisplayView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDisplayView)

// Attributes
public:

// Operations
public:



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

   /// @brief Sets the mapping mode
   void SetMappingMode(WBFL::DManip::MapMode mm, bool reDraw=true);
   WBFL::DManip::MapMode GetMappingMode();

   /// @brief Scales the world space to fit within the window
   void ScaleToFit(bool reDraw=true);

   /// @brief Activates a task whereby the user centers the canvas on a point by left button mouse click
   void ActivateCenterOnPointTask();

   /// @brief Zoomes the view by apply a scaling factor
   void Zoom(Float64 factor, bool reDraw=true);

   /// @brief Actives a task whereby the user zooms in on the canvas by drawing a rectangle with the mouse
   void ActivateZoomTask();

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

   CRect GetAdjustedLogicalViewRect();
   WBFL::Geometry::Rect2d GetAdjustedWorldViewRect();

   // different mappings for screen and printer. to be switched back
   // and forth at print time
   std::shared_ptr<WBFL::DManip::iMapping>          m_pPrinterMapping;
   std::shared_ptr<WBFL::DManip::iCoordinateMap>    m_pPrinterCoordinateMap;
   std::shared_ptr<WBFL::DManip::iMapping>          m_pScreenMapping;
   std::shared_ptr<WBFL::DManip::iCoordinateMap>    m_pScreenCoordinateMap;

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

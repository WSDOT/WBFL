///////////////////////////////////////////////////////////////////////
// PGSuper - Prestressed Girder SUPERstructure Design and Analysis
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation, 
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but 
// distribution is AS IS, WITHOUT ANY WARRANTY; without even the implied 
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See 
// the Alternate Route Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source 
// License along with this program; if not, write to the Washington 
// State Department of Transportation, Bridge and Structures Office, 
// 4500 3rd AVE SE - P.O. Box  47340, Olympia, WA 98503, USA or e-mail 
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#pragma once

// Dummy file to allow BridgeLink applications to compile without the ObjectiveGrid class

// To supress usage of ObjectiveGrid, uncomment #define _NOGRID in WbflGrid.h

#include <afxwin.h>

#undef IDC_HELP

#define ROWCOL long

#define DECLARE_REGISTER()
#define IMPLEMENT_REGISTER(a,b,c,d,e)

#define GRID_DECLARE_REGISTER()
#define GRID_IMPLEMENT_REGISTER(a,b,c,d,e)

#define GX_SCROLLINVIEW          0
#define GX_DISPLAYEDITWND        0
#define GX_IDS_CTRL_TEXTFIT      0
#define GX_IDS_UA_VALID_MIN      0
#define GX_IDS_UA_VALID_MAX      0
#define GX_IDS_UA_VALID_MSG      0
#define GX_IDS_CTRL_EDIT         0
#define GX_IDS_CTRL_HEADER       0
#define GX_IDS_CTRL_STATIC       0
#define GX_IDS_CTRL_CHECKBOX3D   0
#define GX_IDS_CTRL_CBS_DROPDOWN 0
#define GX_IDS_CTRL_CBS_DROPDOWNLIST 0
#define GX_IDS_CTRL_ZEROBASED_EX 0
#define GX_IDS_CTRL_PUSHBTN 0
#define GX_IDS_CTRL_SPINEDIT 0
#define GX_SELFULL               0 
#define GX_SELCOL                0
#define GX_SELTABLE              0
#define GX_SELNONE               0
#define GX_FMT_GEN               0
#define GX_FMT_HIDDEN            0

#define GX_IDS_UA_TOOLTIPTEXT 0

#define GX_IDS_UA_SPINBOUND_MIN 0
#define GX_IDS_UA_SPINBOUND_MAX 0
#define GX_IDS_UA_SPINBOUND_WRAP 0

#define GX_SELMULTIPLE 0
#define GX_SELSHIFT 0
#define GX_SELKEYBOARD 0
#define GX_SELROW 0

#define GX_MERGE_HORIZONTAL 0
#define GX_MERGE_VERTICAL 0
#define GX_MERGE_COMPVALUE 0

#define GX_INVALIDATE 0
#define GX_HITEND 0
#define GX_HITSTART 0

#define GXSYSCOLOR(_c_) 0

#define GX_UPDATENOW 0

#define WM_GX_NEEDCHANGETAB 0

#define GX_DNDSTYLES 0
#define GX_DNDDISABLED 0
#define GX_DNDNOAPPENDCOLS 0
#define GX_DNDNOAPPENDROWS 0
#define GX_DNDDIFFRANGEDLG 0
#define GX_DNDMULTI 0


const WORD gxnMergeEvalOnDisplay = 0x0;
const WORD gxnMergeDelayEval = 0x0;
const WORD gxnDisabled = 0x0;
const WORD gxnAutomatic = 0x0;
const WORD gxnEnhanced = 0x0;
const WORD gxnEnabled = 0x0;

// Forward declarations
class CGXGridParam;
class CGXGridWnd;
class CGXRangeList;
class CGXRange;
class CGXStyle;
class CGXControl;
class CGXCheckBox;
class CRowColArray;
class CGXBrush;

class CRowColArray
{
public:
   ROWCOL operator[](INT_PTR) { return 0; }
   INT_PTR GetSize() { return 0; }
   INT_PTR GetAt(INT_PTR) { return 0; }
   INT_PTR Add(DWORD newElement) { return 0; }
   INT_PTR GetCount() const { return 0; }
};

class CGXFont
{
public:
   void SetOrientation(UINT) {}
};

class CGXBrush
{
public:
   bool operator==(const CGXBrush&) { return true; }
};

class CGXAbstractUserAttribute
{
public:
   virtual double GetDoubleValue() const { return 0.0; }
};

class CGXControl
{
public:
   virtual ~CGXControl() {}
   void GetValue(CString& s) { s="-999999"; }
	void GetCurrentText(CString& s) { s="-999999"; }
   BOOL IsInit() const { return TRUE; }
   BOOL GetModify() { return FALSE; }
};

class CGXCheckBox : public CGXControl
{
public:
};

class CGXStyle
{
public:
   CGXStyle& SetControl(UINT) { return *this; }
   CGXStyle& SetChoiceList(const TCHAR*) { return *this; }
   CGXStyle& SetValue(const TCHAR*) { return *this; }
   CGXStyle& SetValue(const CString& str) { return *this; }
   CGXStyle& SetValue(UINT) { return *this; }
   CGXStyle& SetValue(long) { return *this; }
   CGXStyle& SetValue(double) { return *this; }
   CGXStyle& SetHorizontalAlignment(UINT) { return *this; }
   CGXStyle& SetVerticalAlignment(UINT) { return *this; }
   CGXStyle& SetUserAttribute(UINT, const TCHAR*) { return *this; }
   CGXStyle& SetUserAttribute(UINT, CGXAbstractUserAttribute&) { return *this; }
   CGXStyle& SetUserAttribute(UINT, double) { return *this; }
   CGXStyle& SetUserAttribute(UINT, long) { return *this; }
   CGXStyle& SetEnabled(BOOL) { return *this; }
   CGXStyle& SetWrapText(BOOL) { return *this; }
   CGXStyle& SetTextColor(COLORREF) { return *this; }
   CGXStyle& SetReadOnly(BOOL) { return *this; }
   CGXStyle& SetTriState(BOOL) { return *this; }
   CGXStyle& SetInterior(COLORREF) { return *this; }
   CGXStyle& SetMergeCell(UINT) { return *this; }
   CGXStyle& SetFont(const CGXFont&) { return *this; }
   CGXStyle& SetItemDataPtr(void*) { return *this; }
   CGXStyle& SetAutoSize(BOOL) { return *this; }

   BOOL GetIncludeChoiceList() const { return FALSE; }
   BOOL GetEnabled() { return FALSE; }

   const CGXAbstractUserAttribute& GetUserAttribute(WORD nID) const { return m_abstract_user_attribute; }

   WORD GetControl() { return 0; }
   CString GetChoiceList() {return CString(""); }

   CGXStyle& SetFormat(UINT) { return *this; }

   CGXBrush GetInterior() { return CGXBrush(); }

   void* GetItemDataPtr() const { return nullptr; }

   const CString& CGXStyle::GetValue() const { return m_svalue; }

   BOOL GetIncludeUserAttribute(WORD nID) const { return FALSE; }
   BOOL GetIncludeReadOnly() const { return FALSE; }
   BOOL GetReadOnly() const { return FALSE; }

protected:
   CGXAbstractUserAttribute m_abstract_user_attribute;
   CString m_svalue{ _T("0") };
};

class CGXRange
{
public:
   CGXRange(const CGXRange *r)   { top=0; bottom=0; }
   CGXRange(ROWCOL=0,ROWCOL=0,ROWCOL=0,ROWCOL=0)  { top=0; bottom=0; }
   void ExpandRange(ROWCOL,ROWCOL,ROWCOL,ROWCOL) {}
   BOOL IsCells() { return FALSE; }
   BOOL IsRows() { return FALSE; }
   BOOL IsCols() { return FALSE; }
   BOOL IsTable() { return FALSE; }
   CGXRange& SetTable() { return *this; }
   CGXRange& SetRows(ROWCOL,ROWCOL nRows=0) { return *this; }
   CGXRange& SetCols(ROWCOL,ROWCOL nCols=0) { return *this; }

   ROWCOL top;
   ROWCOL bottom;
   ROWCOL left;
   ROWCOL right;
};

class CGXRangeList
{
public:
   CGXRangeList() { m_pRange = &m_Range; }

   CGXRange*& GetHead() { return m_pRange; }
   CGXRange* GetHead() const { return m_pRange; }
   CGXRange* GetTail() const { return m_pRange; }
   CGXRange* GetNext(POSITION) const { return m_pRange; }

   BOOL IsAnyCellFromCol(ROWCOL) { return TRUE; }
   BOOL IsAnyCellFromRow(ROWCOL) { return TRUE; }
   BOOL IsCellInList(ROWCOL, ROWCOL) { return TRUE; }
   ROWCOL GetCount() { return 0; }

   void DeleteAll() {}

   POSITION GetHeadPosition() { return nullptr; }

private:
   CGXRange m_Range;
   CGXRange* m_pRange;
};

class CGXGridParam
{
public:
   CGXRangeList* GetRangeList() { return &m_RangeList; }
   void EnableSelection(WORD) {}
   void EnableTrackColWidth(ROWCOL) {}
   void EnableTrackRowHeight(ROWCOL) {}
   void SetLockReadOnly(BOOL) {}

   void EnableMoveRows(BOOL) {}
   void EnableMoveCols(BOOL) {}

   void SetExcelLikeSelectionFrame(BOOL) {}

   BOOL IsEnableUndo() { return FALSE; }
   void EnableUndo(BOOL bEnable = TRUE) {}

private:
   CGXRangeList m_RangeList;
};

class CGXGridCore
{
public:
   virtual int GetColWidth(ROWCOL) {return 0;}
   virtual BOOL OnLButtonClickedRowCol(ROWCOL,ROWCOL,UINT,CPoint) {return TRUE;}
   virtual BOOL OnRButtonHitRowCol(ROWCOL nHitRow, ROWCOL nHitCol, ROWCOL nDragRow, ROWCOL nDragCol, CPoint point, UINT nFlags, WORD nHitState) { return TRUE; }

   virtual BOOL OnValidateCell(ROWCOL nRow, ROWCOL nCol) { return TRUE; }

   virtual BOOL InsertCols(ROWCOL nCol, ROWCOL nCount, int* anWidthArray = NULL, CObArray* pCellsArray = NULL, CObArray* pColsArray = NULL, ROWCOL nRowCount = 0, UINT flags = GX_UPDATENOW) { return TRUE; }

   virtual ROWCOL GetColCount() { return 0; }

   virtual BOOL InsertRows(ROWCOL, ROWCOL) { return FALSE; }
   virtual BOOL RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags = GX_UPDATENOW) { return TRUE; }
   virtual BOOL HideRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bHide = TRUE) { return TRUE; }

   virtual void SetSelection(POSITION SelRectId, ROWCOL nTop = 0, ROWCOL nLeft = 0, ROWCOL nBottom = 0, ROWCOL nRight = 0) {}
   virtual BOOL GetCurrentCell(ROWCOL& nRow, ROWCOL& nCol) { return TRUE; }
   virtual void OnDrawItem(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CRect& rectItem, const CGXStyle& style) {}

   virtual BOOL SetFrozenRows(ROWCOL nFrozenRows, ROWCOL nHeaderRows = 0) { return TRUE; }
   virtual BOOL SetFrozenCols(ROWCOL nFrozenCols, ROWCOL nHeaderCols = 0) { return TRUE; }
   virtual BOOL SetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags = GX_UPDATENOW) { return TRUE; }

   virtual void UpdateStyleRange(const CGXRange& range) {}
   
   int CalcSumOfRowHeights(ROWCOL nFromRow, ROWCOL nToRow, int nAbortAt = 0) { return 0; }
   void EnableGridToolTips() {}

   CGXControl* GetControl(ROWCOL, ROWCOL) { return &m_Control; }
   CGXControl* GetCurrentCellControl() { return &m_Control; }

   virtual void SetScrollBarMode(int nBar, int nSetting, BOOL bRedraw = TRUE) {}

   virtual BOOL ResizeColWidthsToFit(CGXRange range, BOOL bResizeCoveredCells = TRUE, UINT nFlags = GX_UPDATENOW) { return TRUE; }

   virtual BOOL TransferCurrentCell(BOOL bSaveAndValidate = TRUE, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE) { return TRUE; }

   void ImplementCutPaste() {}
   virtual BOOL CanPaste() { return FALSE; }
   virtual BOOL CanCopy() { return FALSE; }
   void Copy() {}
   BOOL Paste() { return FALSE; }
   BOOL PasteTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle) { return FALSE; }
   BOOL Undo() { return FALSE; }

   virtual void DisplayWarningText() {}

   CString m_sWarningText;
   DWORD m_nClipboardFlags;

   CWnd* m_pGridWnd{ nullptr };

private:
   CGXControl m_Control;
};

class CGXGridWnd : public CGXGridCore, public CWnd
{
public:
   CGXGridWnd()
   {}

   void RegisterClass() {}
   virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID) { return FALSE; }

   virtual BOOL CanActivateGrid(BOOL bActivate) { return TRUE; }

   CRect GetGridRect() { return CRect(); }
   ROWCOL GetRowCount() { return 0; }
   BOOL SetCurrentCell(ROWCOL,ROWCOL,UINT) { return TRUE; }
   ROWCOL GetLeftCol() { return 0; }
   CGXGridParam* GetParam() { return &m_Param; }
   void Initialize() {}
   void EnableIntelliMouse() {}
   BOOL SetStyleRange(CGXRange&, CGXStyle&) { return TRUE; }

   BOOL IsCurrentCell(ROWCOL,ROWCOL) { return FALSE; }
   BOOL IsActiveCurrentCell() { return FALSE; }

   CString GetValueRowCol(ROWCOL,ROWCOL) { return CString("-9999999"); }

   void SetWarningText(const TCHAR*) {}
   BOOL OnValidateCell(ROWCOL,ROWCOL) { return TRUE; }

   void SetRowCount(ROWCOL) {};
   void SetColCount(ROWCOL) {};
   ROWCOL GetColCount() { return 0; }

   void ResizeRowHeightsToFit(CGXRange&) {}

   BOOL SetValueRange(CGXRange&,unsigned short) {return TRUE;}
   BOOL SetValueRange(CGXRange&,double) {return TRUE;}
   BOOL SetValueRange(CGXRange&, short) { return TRUE; }
   BOOL SetValueRange(CGXRange&, long) { return TRUE; }
   BOOL SetValueRange(CGXRange&,const TCHAR*) {return TRUE;}
   BOOL SetValueRange(CGXRange&, const CString&) { return TRUE; }

   void ClearCells(CGXRange&) {}

   void ScrollCellInView(ROWCOL,ROWCOL) {}

   void LockUpdate(BOOL) {}

   void Redraw() {}

   CWnd* GridWnd() { return this; }

   void SelectRange(CGXRange&,BOOL bSelect = TRUE) {}
   void SetCurrentCell(ROWCOL,ROWCOL) {}

   virtual BOOL ResizeColWidthsToFit(CGXRange range, BOOL bResizeCoveredCells = TRUE, UINT nFlags = GX_UPDATENOW) { return TRUE; }

   BOOL GetStyleRowCol(ROWCOL,ROWCOL,CGXStyle&) {return TRUE;}

   BOOL HideCols(ROWCOL, ROWCOL, BOOL bHide = TRUE) { return TRUE; }
   BOOL IsColHidden(ROWCOL) { return TRUE; }
   virtual void OnModifyCell(ROWCOL,ROWCOL) {}
   virtual void OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol) {}

   virtual void OnDrawItem(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CRect& rectDraw, const CGXStyle& style) {}
   virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt) { return TRUE; };
   virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags) { return TRUE; };
   virtual void OnChangedSelection(const CGXRange* pRange, BOOL, BOOL) {};

   virtual BOOL OnLButtonHitRowCol(ROWCOL nHitRow, ROWCOL nHitCol, ROWCOL nDragRow, ROWCOL nDragCol, CPoint point, UINT flags, WORD nHitState) { return TRUE; }

   virtual void OnClickedButtonRowCol(ROWCOL nRow, ROWCOL nCol) {};
   virtual BOOL OnEndEditing(ROWCOL nRow, ROWCOL nCol) { return TRUE; }

   ROWCOL GetSelectedRows(CRowColArray& awRows, BOOL bRangeRowsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE) { return 0; }
   ROWCOL GetSelectedRows(CDWordArray& awRows, BOOL bRangeRowsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE) { return 0; }
   ROWCOL GetSelectedCols(CRowColArray& awCols, BOOL bRangeColsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE) { return 0; }

   BOOL GetSelectedCols(CRowColArray& awLeft, CRowColArray& awRight, BOOL bRangeColsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE) { return TRUE; }

   void EnableOleDropTarget(UINT) {}

   void SetMergeCellsMode(WORD nMode, BOOL bRedraw = TRUE) {}

   virtual BOOL OnStartEditing(ROWCOL nRow, ROWCOL nCol) { return TRUE; }

private:
   CGXGridParam m_Param;
};

class CGXTabInfo
{
public:
   BOOL bSel{ FALSE };
   CObject* pExtra{ nullptr };
};

class CGXTabBeam
{
public:
   BOOL EnableWindow(BOOL bEnable) { return TRUE; }
   int GetCount() { return 0; }
   CGXTabInfo& GetTab(int nTab) { return m_TabInfo; }

private:
   CGXTabInfo m_TabInfo;
};

class CGXTabWnd : public CWnd
{
public:
   static void RegisterClass(HINSTANCE) {}
   UINT GetNextID() { return 0; }
   void GetInsideRect(CRect& r) { r = CRect(0, 0, 0, 0); }
   virtual CWnd* AttachWnd(CWnd* pWnd, LPCTSTR szLabel) { return nullptr; }
   virtual void SwitchTab(int nTab) {}
   CWnd* SetActivePane() { return nullptr; }
   CWnd* GetActivePane() { return nullptr; }
   CGXTabBeam& GetBeam() { return m_Beam; }
private:
   CGXTabBeam m_Beam;
};

inline void GXInit(){}
inline void GXSetNewGridLineMode(BOOL) {}
inline void GXTerminate(){}
inline void GXForceTerminate(){}
inline BOOL CopyRangeList(CGXRangeList&,BOOL){return TRUE;}
inline void DDV_GXGridWnd(CDataExchange*,CGXGridWnd*){}
inline void DDV_GXTabWnd(CDataExchange* pDX, CGXTabWnd* pTabWnd) {}
inline BOOL GXDiscardNcActivate() { return TRUE; }


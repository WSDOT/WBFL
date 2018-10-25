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

#ifndef INCLUDED_NOGRID_H_
#define INCLUDED_NOGRID_H_

// Dummy file to allow PGSuper to compile without the ObjectiveGrid class

#include <afxwin.h>

#define ROWCOL long

#define DECLARE_REGISTER()
#define IMPLEMENT_REGISTER(a,b,c,d,e)

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
#define GX_IDS_CTRL_ZEROBASED_EX 0
#define GX_SELFULL               0 
#define GX_SELCOL                0
#define GX_SELTABLE              0

// Forward declarations
class CGXGridParam;
class CGXGridWnd;
class CGXRangeList;
class CGXRange;
class CGXStyle;
class CGXControl;

class CGXControl
{
public:
   void GetValue(CString& s) { s="-999999"; }
	void GetCurrentText(CString& s) { s="-999999"; }
};

class CGXStyle
{
public:
   CGXStyle& SetControl(UINT) {return *this;}
   CGXStyle& SetChoiceList(const char*){return *this;}
   CGXStyle& SetValue(const char*){return *this;}
   CGXStyle& SetHorizontalAlignment(UINT) {return *this;}
   CGXStyle& SetVerticalAlignment(UINT){return *this;}
   CGXStyle& SetUserAttribute(UINT,const char*){return *this;}
   CGXStyle& SetEnabled(BOOL) {return *this;}
   CGXStyle& SetWrapText(BOOL) {return *this;}
   CGXStyle& SetTextColor(COLORREF) {return *this;}
   CGXStyle& SetReadOnly(BOOL) {return *this;}
   CGXStyle& SetTriState(BOOL) {return *this;}

   WORD GetControl() { return 0; }
   CString GetChoiceList() {return CString(""); }
};

class CGXRange
{
public:
   CGXRange(const CGXRange *r)   { top=0; bottom=0; }
   CGXRange(ROWCOL=0,ROWCOL=0,ROWCOL=0,ROWCOL=0)  { top=0; bottom=0; }
   void ExpandRange(ROWCOL,ROWCOL,ROWCOL,ROWCOL) {}
   ROWCOL top;
   ROWCOL bottom;
};

class CGXRangeList
{
public:
   CGXRangeList() { m_pRange = &m_Range; }

   CGXRange*& GetHead() { return m_pRange; }
   CGXRange* GetHead() const { return m_pRange; }

   BOOL IsAnyCellFromCol(ROWCOL) { return TRUE; }
   BOOL IsAnyCellFromRow(ROWCOL) { return TRUE; }

   ROWCOL GetCount() { return 0; }

private:
   CGXRange m_Range;
   CGXRange* m_pRange;
};

class CGXGridParam
{
public:
   CGXRangeList* GetRangeList() { return &m_RangeList; }
   void EnableUndo(BOOL) {}
   void EnableSelection(WORD) {}
   void EnableTrackColWidth(ROWCOL) {}
   void EnableTrackRowHeight(ROWCOL) {}
   void SetLockReadOnly(BOOL) {}

   void EnableMoveRows(BOOL) {}

private:
   CGXRangeList m_RangeList;
};

class CGXGridCore
{
public:
   int GetColWidth(ROWCOL) {return 0;}
   BOOL OnLButtonClickedRowCol(ROWCOL,ROWCOL,UINT,CPoint) {return TRUE;}
};

class CGXGridWnd : public CGXGridCore, public CWnd
{
public:
   CGXGridWnd()
   {}

   CRect GetGridRect() { return CRect(); }
   ROWCOL GetRowCount() { return 0; }
   void InsertRows(ROWCOL,ROWCOL) {}
   void RemoveRows(ROWCOL,ROWCOL) {}
   BOOL SetCurrentCell(ROWCOL,ROWCOL,UINT) { return TRUE; }
   ROWCOL GetLeftCol() { return 0; }
   CGXGridParam* GetParam() { return &m_Param; }
   void Initialize() {}
   void EnableIntelliMouse() {}
   void SetStyleRange(CGXRange& , CGXStyle&) {}

   BOOL IsCurrentCell(ROWCOL,ROWCOL) { return FALSE; }
   BOOL IsActiveCurrentCell() { return FALSE; }

   CGXControl* GetControl(ROWCOL,ROWCOL) { return &m_Control; }
   CString GetValueRowCol(ROWCOL,ROWCOL) { return CString("-9999999"); }

   void SetWarningText(const char*) {}
   BOOL OnValidateCell(ROWCOL,ROWCOL) { return TRUE; }

   void SetRowCount(ROWCOL) {};
   void SetColCount(ROWCOL) {};
   ROWCOL GetColCount() { return 0; }

   void ResizeRowHeightsToFit(CGXRange&) {}

   BOOL SetValueRange(CGXRange&,unsigned short) {return TRUE;}
   BOOL SetValueRange(CGXRange&,double) {return TRUE;}
   BOOL SetValueRange(CGXRange&,long) {return TRUE;}
   BOOL SetValueRange(CGXRange&,const char*) {return TRUE;}

   void ScrollCellInView(ROWCOL,ROWCOL) {}

   void LockUpdate(BOOL) {}

   void Redraw() {}

   CWnd* GridWnd() { return this; }

   void SelectRange(CGXRange&) {}
   void SetCurrentCell(ROWCOL,ROWCOL) {}

   void ResizeColWidthsToFit(CGXRange&) {}

   BOOL GetStyleRowCol(ROWCOL,ROWCOL,CGXStyle&) {return TRUE;}

   void HideCols(ROWCOL,ROWCOL) {}
   void OnModifyCell(ROWCOL,ROWCOL) {}


private:
   CGXGridParam m_Param;
   CGXControl m_Control;
};

inline void GXInit(){}
inline void GXTerminate(){}
inline BOOL CopyRangeList(CGXRangeList&,BOOL){return TRUE;}
inline void DDV_GXGridWnd(CDataExchange*,CGXGridWnd*){}
inline BOOL GXDiscardNcActivate() { return TRUE; }

#endif //  INCLUDED_NOGRID_H_
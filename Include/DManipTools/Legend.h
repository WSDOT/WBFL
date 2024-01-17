///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
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

#ifndef INCLUDED_LEGEND_H_
#define INCLUDED_LEGEND_H_
#pragma once

class CRect;
class CDC;
interface iDragDataSink;
interface iDragDataSource;
interface iDisplayObject;


// {55504B51-10F4-4c2e-9E61-974B2E38396C}
DEFINE_GUID(IID_iLegendEntry, 
0x55504b51, 0x10f4, 0x4c2e, 0x9e, 0x61, 0x97, 0x4b, 0x2e, 0x38, 0x39, 0x6c);
struct __declspec(uuid("{55504B51-10F4-4c2e-9E61-974B2E38396C}")) iLegendEntry;
interface iLegendEntry : public IUnknown
{
   STDMETHOD_(void,get_Name)(BSTR *pVal) PURE;
   // draw symbol in drawRect. Size is in logical units
   STDMETHOD_(void,Draw)(CDC* pDC, CRect& drawRect, BOOL beingDragged) PURE;

   // write and read to a data source for drag/drop operations
   STDMETHOD_(HRESULT,GetClassID)(CLSID *pClassID) PURE; // same as IPersist
   STDMETHOD_(void,WriteDragData)(iDragDataSink* pSink, UINT cfFormat) PURE;
   STDMETHOD_(void,ReadDragData)(iDragDataSource* pSource, UINT cfFormat) PURE;
};

// configurable legend entry to use symbols based on the Windows'
// "Symbol" font
// {E3BD88F7-D54B-4058-A350-900E97D13176}
DEFINE_GUID(IID_iSymbolLegendEntry, 
0xe3bd88f7, 0xd54b, 0x4058, 0xa3, 0x50, 0x90, 0xe, 0x97, 0xd1, 0x31, 0x76);
struct __declspec(uuid("{E3BD88F7-D54B-4058-A350-900E97D13176}")) iSymbolLegendEntry;
interface iSymbolLegendEntry : public iLegendEntry
{
   STDMETHOD_(void,put_Name)(BSTR newVal) PURE;

   // name of font face for symbol
   // "Symbol" is the default
   STDMETHOD_(void,get_SymbolFontFace)(TCHAR* *pVal) PURE;
   STDMETHOD_(void,put_SymbolFontFace)(LPCTSTR newVal) PURE;

   // character font size in 1/10 points
   STDMETHOD_(long,get_SymbolSize)() PURE;
   STDMETHOD_(void,put_SymbolSize)(long code) PURE;

   // Unicode constant defining symbol to be used for legend item
   // Refer to Word's Insert Symbol command for a list of these codes
   // NOTE that a value of zero will fill the entire legend box with the 
   // current color.
   STDMETHOD_(DWORD,get_SymbolCharacterCode)() PURE;
   STDMETHOD_(void,put_SymbolCharacterCode)(DWORD code) PURE;

   STDMETHOD_(COLORREF,get_Color)() PURE;
   STDMETHOD_(void,put_Color)(COLORREF color) PURE;

   // draw a horizontal colored line across the legend box
   STDMETHOD_(void,get_DoDrawLine)(BOOL* doDraw) PURE;
   STDMETHOD_(void,put_DoDrawLine)(BOOL doDraw) PURE;
};



// {FD4134B6-D588-4e3a-9158-FCAA773E82E5}
DEFINE_GUID(IID_iLegendDisplayObject, 
0xfd4134b6, 0xd588, 0x4e3a, 0x91, 0x58, 0xfc, 0xaa, 0x77, 0x3e, 0x82, 0xe5);
struct __declspec(uuid("{FD4134B6-D588-4e3a-9158-FCAA773E82E5}")) iLegendDisplayObject;
interface iLegendDisplayObject : public iDisplayObject
{
   // location of top left corner of border
   STDMETHOD_(void,put_Position)(IPoint2d* pos,BOOL bRedraw,BOOL bFireEvent) PURE;
   STDMETHOD_(void,get_Position)(IPoint2d* *pos) PURE;

   STDMETHOD_(void,get_Title)(BSTR *pVal) PURE;
   STDMETHOD_(void,put_Title)(BSTR newVal) PURE;

   // Font for legend entry names. Note that font height is in 10th of points.
   // Note that Title is drawn in bold version of same font
   STDMETHOD_(void,put_Font)(const LOGFONT& Font) PURE;
   STDMETHOD_(void,get_Font)(LOGFONT* pFont) PURE;

   STDMETHOD_(void,get_NumEntries)(IndexType* count) PURE;
   STDMETHOD_(void,AddEntry)(iLegendEntry* entry) PURE;
   STDMETHOD_(HRESULT,InsertEntry)(IndexType index, iLegendEntry* entry) PURE;
   STDMETHOD_(HRESULT,get_Entry)(IndexType index, iLegendEntry* *entry) PURE;
   STDMETHOD_(HRESULT,RemoveEntry)(IndexType index) PURE;
   STDMETHOD_(void,ClearEntries)() PURE;

   // Number of rows displayed in legend "grid". Number of columns is
   // determined by the number of entries to be displayed. Grid is filled
   // column-wise
   STDMETHOD_(void,get_NumRows)(IndexType* count) PURE;
   STDMETHOD_(void,put_NumRows)(IndexType count) PURE;

   // size of each legend grid in twips. The minimum allowable size is
   // 10x wide and 4x high of the Font size.
   STDMETHOD_(void,get_CellSize)(CSize* size) PURE;
   STDMETHOD_(void,put_CellSize)(CSize size) PURE;

   // call this after filling legend entries to compute minimum cell
   // size in twips based on text size.
   STDMETHOD_(void,GetMinCellSize)(CSize* size) PURE;

   // draw border or not?
   STDMETHOD_(void,get_DoDrawBorder)(BOOL* doDraw) PURE;
   STDMETHOD_(void,put_DoDrawBorder)(BOOL doDraw) PURE;

   // fill interior or not?
   STDMETHOD_(void,get_DoFill)(BOOL* doDraw) PURE;
   STDMETHOD_(void,put_DoFill)(BOOL doDraw) PURE;

   // if DoFill, use this color
   STDMETHOD_(COLORREF,get_FillColor)() PURE;
   STDMETHOD_(void,put_FillColor)(COLORREF color) PURE;

   // allow user to drag around screen?
   STDMETHOD_(void,get_IsDraggable)(BOOL* canDrag) PURE;
   STDMETHOD_(void,put_IsDraggable)(BOOL canDrag) PURE;

};

#endif
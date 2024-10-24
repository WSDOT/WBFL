#pragma once

class CRect;
class CDC;
interface iDragDataSink;
interface iDragDataSource;
interface iDisplayObject;


// configurable legend entry to use symbols based on the Windows'
// "Symbol" font
interface iSymbolLegendEntry : public WBFL::DManip::LegendEntry
{
   virtual void SetName(std::_tstring name) = 0;

   // name of font face for symbol
   // "Symbol" is the default
   virtual std::_tstring GetSymbolFontFace() = 0;
   virtual void SetSymbolFontFace(LPCTSTR newVal) = 0;

   // character font size in 1/10 points
   virtual long GetSymbolSize() = 0;
   virtual void SetSymbolSize(long code) = 0;

   // Unicode constant defining symbol to be used for legend item
   // Refer to Word's Insert Symbol command for a list of these codes
   // NOTE that a value of zero will fill the entire legend box with the 
   // current color.
   virtual DWORD GetSymbolCharacterCode() = 0;
   virtual void SetSymbolCharacterCode(DWORD code) = 0;

   virtual COLORREF GetColor() = 0;
   virtual void SetColor(COLORREF color) = 0;

   // draw a horizontal colored line across the legend box
   virtual BOOL DoDrawLine() = 0;
   virtual void DoDrawLine(BOOL doDraw) = 0;
};

interface iLegendDisplayObject : WBFL::DManip::LegendDisplayObject
{
   // location of top left corner of border
   virtual void SetPosition(const WBFL::Geometry::Point2d& pos, BOOL bRedraw, BOOL bFireEvent) = 0;
   virtual WBFL::Geometry::Point2d GetPosition() = 0;

   virtual std::_tstring GetTitle() = 0;
   virtual void SetTitle(std::_tstring newVal) = 0;

   // Font for legend entry names. Note that font height is in 10th of points.
   // Note that Title is drawn in bold version of same font
   virtual void SetFont(const LOGFONT& Font) = 0;
   virtual LOGFONT GetFont() = 0;

   virtual IndexType GetNumEntries() = 0;
   virtual void AddEntry(std::shared_ptr<::iLegendEntry> entry) = 0;
   virtual void InsertEntry(IndexType index, std::shared_ptr<::iLegendEntry> entry) = 0;
   virtual std::shared_ptr<::iLegendEntry> GetEntry(IndexType index) = 0;
   virtual void RemoveEntry(IndexType index) = 0;
   virtual void ClearEntries() = 0;

   // Number of rows displayed in legend "grid". Number of columns is
   // determined by the number of entries to be displayed. Grid is filled
   // column-wise
   virtual IndexType GetNumRows() = 0;
   virtual void SetNumRows(IndexType count) = 0;

   // size of each legend grid in twips. The minimum allowable size is
   // 10x wide and 4x high of the Font size.
   virtual CSize GetCellSize() = 0;
   virtual void SetCellSize(CSize size) = 0;

   // call this after filling legend entries to compute minimum cell
   // size in twips based on text size.
   virtual CSize GetMinCellSize() = 0;

   // draw border or not?
   virtual BOOL DoDrawBorder() = 0;
   virtual void DoDrawBorder(BOOL doDraw) = 0;

   // fill interior or not?
   virtual BOOL DoFill() = 0;
   virtual void DoFill(BOOL doDraw) = 0;

   // if DoFill, use this color
   virtual COLORREF GetFillColor() = 0;
   virtual void SetFillColor(COLORREF color) = 0;

   // allow user to drag around screen?
   virtual BOOL GetIsDraggable() = 0;
   virtual void IsDraggable(BOOL canDrag) = 0;
};

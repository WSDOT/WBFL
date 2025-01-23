///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2025  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// BearingLayout.cpp : Implementation of CBearingLayout
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "BearingLayout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBearingLayout
HRESULT CBearingLayout::FinalConstruct()
{
   m_pPier = nullptr;

   // Start with one bearing line
   BearingLineData brgLineData;
   m_BearingLines.push_back(brgLineData);

   return S_OK;
}

void CBearingLayout::FinalRelease()
{
}

STDMETHODIMP CBearingLayout::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBearingLayout,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IBearingLayout

STDMETHODIMP CBearingLayout::putref_Pier(/*[in]*/IPier* pPier)
{
   CHECK_IN(pPier);
   m_pPier = pPier;
   return S_OK;
}

STDMETHODIMP CBearingLayout::get_Pier(/*[out,retval]*/IPier** ppPier)
{
   CHECK_RETOBJ(ppPier);
   if ( m_pPier )
   {
      *ppPier = m_pPier;
      (*ppPier)->AddRef();
   }
   return S_OK;
}

STDMETHODIMP CBearingLayout::get_Spacing(IndexType brgLineIdx,SpacingIndexType spaceIdx, Float64* space)
{
   CHECK_RETVAL(space);

   if ( spaceIdx < 0 || (SpacingIndexType)m_BearingLines[brgLineIdx].m_Spacing.size() <= spaceIdx)
   {
      return Error(IDS_E_SPACEINDEX,IID_IBearingLayout,GB_E_SPACEINDEX);
   }

   
   if ( m_BearingLines[brgLineIdx].m_Spacing.size() == 0 )
   {
      *space = 0;
   }
   else
   {
      *space = m_BearingLines[brgLineIdx].m_Spacing[spaceIdx];
   }

   return S_OK;
}

STDMETHODIMP CBearingLayout::put_Spacing(IndexType brgLineIdx,SpacingIndexType spaceIdx,Float64 space)
{
   IndexType nBearings;
   get_BearingCount(brgLineIdx,&nBearings);
   SpacingIndexType nSpaces = SpacingIndexType(nBearings - 1);
   if ( spaceIdx < 0 || nSpaces <= spaceIdx )
   {
      return Error(IDS_E_SPACEINDEX,IID_IBearingLayout,GB_E_SPACEINDEX);
   }

   if ( space <= 0 )
   {
      return Error(IDS_E_SPACING,IID_IBearingLayout,GB_E_SPACING);
   }

   if ( IsEqual(m_BearingLines[brgLineIdx].m_Spacing[spaceIdx],space) )
   {
      return S_OK; // Do nothing if same
   }

   m_BearingLines[brgLineIdx].m_Spacing[spaceIdx] = space;

   return S_OK;
}

STDMETHODIMP CBearingLayout::get_BearingLineCount(IndexType* pnBearingLines)
{
   CHECK_RETVAL(pnBearingLines);
   *pnBearingLines = m_BearingLines.size();
   return S_OK;
}

STDMETHODIMP CBearingLayout::put_BearingLineCount(IndexType nBearingLines)
{
   m_BearingLines.resize(nBearingLines);
   return S_OK;
}

STDMETHODIMP CBearingLayout::get_BearingLineOffset(IndexType brgLineIdx,Float64* pOffset)
{
   CHECK_RETVAL(pOffset);
   *pOffset = m_BearingLines[brgLineIdx].m_BrgLineOffset;
   return S_OK;
}

STDMETHODIMP CBearingLayout::put_BearingLineOffset(IndexType brgLineIdx,Float64 offset)
{
   m_BearingLines[brgLineIdx].m_BrgLineOffset = offset;
   return S_OK;
}

STDMETHODIMP CBearingLayout::get_BearingCount(IndexType brgLineIdx,IndexType* nBearings)
{
   CHECK_RETVAL(nBearings);

   if ( m_BearingLines[brgLineIdx].m_Spacing.size() == 0 )
   {
      (*nBearings) = 1; // if no bearings, simply report 1 bearing
   }
   else
   {
      *nBearings = GetNumBearings(brgLineIdx);
   }

   return S_OK;
}

STDMETHODIMP CBearingLayout::put_BearingCount(IndexType brgLineIdx,IndexType nBearings)
{
   IndexType currNumBearings;
   get_BearingCount(brgLineIdx,&currNumBearings);
   if ( currNumBearings < nBearings )
   {
      Add(brgLineIdx,nBearings-currNumBearings);
   }
   else if ( nBearings < currNumBearings )
   {
      Remove(brgLineIdx,currNumBearings-1,currNumBearings-nBearings);
   }

   RenumberBearings();

   return S_OK;
}

STDMETHODIMP CBearingLayout::Add(IndexType brgLineIdx,IndexType nBearings)
{
   if ( nBearings == INVALID_INDEX )
   {
      return E_INVALIDARG;
   }

   // Get the current number of bearings
   IndexType currNumBearings;
   get_BearingCount(brgLineIdx,&currNumBearings);

   nBearings += currNumBearings;

   SpacingIndexType nSpaces = SpacingIndexType(nBearings - 1);

   // Increasing number of bearings
   Float64 lastSpace;
   if ( currNumBearings == 1 )
   {
      lastSpace = 1; // There isn't a spacing defined, use a reasonable default
   }
   else
   {
      lastSpace = m_BearingLines[brgLineIdx].m_Spacing.back();
   }

   m_BearingLines[brgLineIdx].m_Spacing.resize(nSpaces,lastSpace); // fills new values with lastSpace

   RenumberBearings();

   return S_OK;
}

STDMETHODIMP CBearingLayout::Insert(IndexType brgLineIdx,SpacingIndexType spaceIdx,SpacingIndexType nInsert)
{
   if ( nInsert < 0 )
   {
      return E_INVALIDARG;
   }

   IndexType nBearings;
   get_BearingCount(brgLineIdx,&nBearings);

   if ( nBearings <= spaceIdx )
   {
      return Error(IDS_E_SPACEINDEX,IID_IBearingLayout,GB_E_SPACEINDEX);
   }

   if ( nInsert <= 0 ) // Must be adding at least 1 girder line
   {
      return E_INVALIDARG;
   }

   // interate over all the piers and insert girder lines
   // Get the spacing at the specified index. This is the spacing that will be used. 
   // If there is only one girder line, use a default spacing of 1
   Float64 spacing;
   if ( m_BearingLines[brgLineIdx].m_Spacing.size() == 0 )
   {
      spacing = 1.0;
   }
   else
   {
      if (spaceIdx == INVALID_INDEX) // inserting before first
      {
         spacing = m_BearingLines[brgLineIdx].m_Spacing[0];
      }
      else if ( (SpacingIndexType)m_BearingLines[brgLineIdx].m_Spacing.size() <= spaceIdx ) // inserting after last
      {
         spacing = m_BearingLines[brgLineIdx].m_Spacing[m_BearingLines[brgLineIdx].m_Spacing.size()-1];
      }
      else
      {
         spacing = m_BearingLines[brgLineIdx].m_Spacing[spaceIdx];
      }
   }

   SpacingIndexType offset = spaceIdx;
   if ( spaceIdx == INVALID_INDEX )
   {
      offset = 0;
   }
   else if ( (SpacingIndexType)m_BearingLines[brgLineIdx].m_Spacing.size() <= spaceIdx )
   {
      offset = m_BearingLines[brgLineIdx].m_Spacing.size() - 1;
   }

   m_BearingLines[brgLineIdx].m_Spacing.insert(m_BearingLines[brgLineIdx].m_Spacing.begin()+offset,nInsert,spacing);

   RenumberBearings();

   return S_OK;
}

STDMETHODIMP CBearingLayout::Remove(IndexType brgLineIdx,IndexType brgIdx,IndexType nRemove)
{
   SpacingIndexType nSpaceIdx = SpacingIndexType(brgIdx == 0 ? 0 : brgIdx-1);

   if ( brgIdx < 0 || GetNumBearings(brgLineIdx) <= brgIdx)
   {
      return Error(IDS_E_SPACEINDEX,IID_IBearingLayout,GB_E_SPACEINDEX);
   }

   if ( nRemove <= 0 )
   {
      return E_INVALIDARG; // Nothing to remove
   }

   // Get current number of bearings
   IndexType nCurrBearings;
   get_BearingCount(brgLineIdx,&nCurrBearings);

   // make sure there will be at least one bearing left
   if ( nCurrBearings <= nRemove )
   {
      return Error(IDS_E_LESS_THAN_MIN_COLUMNS,IID_IBearingLayout,GB_E_LESS_THAN_MIN_COLUMNS);
   }
   ColumnIndexType nRemainingBearings = nCurrBearings - nRemove;

   // Determine the index of the last spacing to be removed
   SpacingIndexType nLastSpaceIdx = nSpaceIdx + nRemove;

   // remove bearings
   m_BearingLines[brgLineIdx].m_Spacing.erase(m_BearingLines[brgLineIdx].m_Spacing.begin()+nSpaceIdx,m_BearingLines[brgLineIdx].m_Spacing.begin()+nLastSpaceIdx);

   ATLASSERT(GetNumBearings(brgLineIdx) == nRemainingBearings);

   RenumberBearings();

   return S_OK;
}

STDMETHODIMP CBearingLayout::SetReferenceBearing(IndexType brgLineIdx,IndexType brgIdx,Float64 alignmentOffset)
{
   m_BearingLines[brgLineIdx].m_RefBrgIdx = brgIdx;
   m_BearingLines[brgLineIdx].m_RefBrgOffset = alignmentOffset;
   return S_OK;
}

STDMETHODIMP CBearingLayout::GetReferenceBearing(IndexType brgLineIdx,IndexType* pBrgIdx,Float64* pAlignmentOffset)
{
   CHECK_RETVAL(pBrgIdx);
   CHECK_RETVAL(pAlignmentOffset);
   *pBrgIdx = m_BearingLines[brgLineIdx].m_RefBrgIdx;
   *pAlignmentOffset = m_BearingLines[brgLineIdx].m_RefBrgOffset;
   return S_OK;
}

STDMETHODIMP CBearingLayout::get_BearingLayoutWidth(IndexType brgLineIdx,Float64* pCLW)
{
   CHECK_RETVAL(pCLW);
   Float64 width = 0;
   for(const auto& space : m_BearingLines[brgLineIdx].m_Spacing)
   {
      width += space;
   }

   *pCLW = width;
   return S_OK;
}

STDMETHODIMP CBearingLayout::get_BearingLocation(IndexType brgLineIdx,IndexType brgIdx,Float64* pXxb)
{
   // Gets the location of a bearing in XBeam Coordinates
   if ( m_BearingLines[brgLineIdx].m_Spacing.size() < brgIdx )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(pXxb);

   Float64 leftBrgOffset = GetLeftBearingOffset(brgLineIdx); // offset of left-most bearing from alignment
   
   Float64 leftColumnOffset;
   CComPtr<IColumnLayout> columnLayout;
   m_pPier->get_ColumnLayout(&columnLayout);
   columnLayout->get_ColumnOffset(0,&leftColumnOffset); // offset of left-most column from alignment

   Float64 leftColumnOverhang;
   columnLayout->get_Overhang(qcbLeft,&leftColumnOverhang); // overhang from left-most column to left edge of cross beam
   
   Float64 brgLocation = leftColumnOverhang - leftColumnOffset + leftBrgOffset; // dist from left edge of cross beam to left most bearing

   for ( IndexType idx = 0; idx < brgIdx && 0 < brgIdx; idx++ )
   {
      Float64 spacing;
      get_Spacing(brgLineIdx,idx,&spacing);
      brgLocation += spacing;
   }

   *pXxb = brgLocation;

   return S_OK;
}

STDMETHODIMP CBearingLayout::get_BearingOffset(IndexType brgLineIdx,IndexType brgIdx,Float64* pOffset)
{
   // returns the offset of the specified bearing from the alignment
   CHECK_RETVAL(pOffset);
   if ( m_BearingLines[brgLineIdx].m_Spacing.size() <= brgIdx )
   {
      return E_INVALIDARG;
   }

   *pOffset = m_BearingLines[brgLineIdx].m_RefBrgOffset;
   if ( brgIdx < m_BearingLines[brgLineIdx].m_RefBrgIdx )
   {
      IndexType nSpaces = m_BearingLines[brgLineIdx].m_RefBrgIdx - brgIdx;
      for ( IndexType idx = 0; idx < nSpaces; idx++ )
      {
         Float64 s = m_BearingLines[brgLineIdx].m_Spacing[idx];
         *pOffset -= s;
      }
   }
   else if ( m_BearingLines[brgLineIdx].m_RefBrgIdx < brgIdx )
   {
      IndexType nSpaces = m_BearingLines[brgLineIdx].m_Spacing.size();
      for ( IndexType idx = m_BearingLines[brgLineIdx].m_RefBrgIdx; idx < nSpaces; idx++ )
      {
         Float64 s = m_BearingLines[brgLineIdx].m_Spacing[idx];
         *pOffset += s;
      }
   }

   return S_OK;
}

STDMETHODIMP CBearingLayout::get_BearingElevation(IndexType brgLineIdx,IndexType brgIdx,Float64* pElev)
{
   CHECK_RETVAL(pElev);

   Float64 Xxb;
   get_BearingLocation(brgLineIdx,brgIdx,&Xxb);

   Float64 Xcl;
   m_pPier->ConvertCrossBeamToCurbLineCoordinate(Xxb,&Xcl);

   Float64 deckElev;
   m_pPier->get_Elevation(Xcl,&deckElev);

   Float64 tDeck;
   m_pPier->get_DeckThickness(&tDeck);

   CComPtr<ICrossBeam> xbeam;
   m_pPier->get_CrossBeam(&xbeam);

   Float64 xbeam_full_depth;
   xbeam->get_FullDepth(Xxb,&xbeam_full_depth);

   Float64 lower_xbeam_depth;
   xbeam->get_Depth(0,Xxb,&lower_xbeam_depth);

   Float64 depth = xbeam_full_depth - lower_xbeam_depth;

   *pElev = deckElev - tDeck - depth;

   return S_OK;
}

//////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CBearingLayout::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("BearingLayout"),1.0);

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CBearingLayout::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   VARIANT_BOOL bEnd;

   pLoad->BeginUnit(CComBSTR("BearingLayout"));


   pLoad->EndUnit(&bEnd);

   return S_OK;
}

/////////////////////////////////////////////////

IndexType CBearingLayout::GetNumBearings(IndexType brgLineIdx) const
{
   return m_BearingLines[brgLineIdx].m_Spacing.size() + 1;
}

void CBearingLayout::RenumberBearings()
{
   // Does nothing right now, but if we add an IBearing object
   // we'll need to update the individual bearing indicies.

   // The implementation for this class is taken from IColumnLayout
   // so we just kept the same basic implementation

   //IndexType colIdx = 0;
   //BOOST_FOREACH(CComPtr<IColumn>& column,m_Columns)
   //{
   //   column->put_Index(colIdx++);
   //}
}

Float64 CBearingLayout::GetLeftBearingOffset(IndexType brgLineIdx)
{
   // returns the offset from the alignment to the left-most bearing
   // values less than zero indicate the left-most bearing is to the
   // left of the alignment

   Float64 leftBrgOffset = m_BearingLines[brgLineIdx].m_RefBrgOffset;

   if ( 0 < m_BearingLines[brgLineIdx].m_RefBrgIdx )
   {
      // make the reference bearing the first bearing
      for ( IndexType brgIdx = m_BearingLines[brgLineIdx].m_RefBrgIdx-1; 0 <= brgIdx && brgIdx != INVALID_INDEX; brgIdx-- )
      {
         Float64 space;
         get_Spacing(brgLineIdx,brgIdx,&space);
         leftBrgOffset -= space;
      }
   }

   return leftBrgOffset;
}
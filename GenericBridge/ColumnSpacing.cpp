///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// ColumnSpacing.cpp : Implementation of CColumnSpacing
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "ColumnSpacing.h"
#include "Column.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColumnSpacing
HRESULT CColumnSpacing::FinalConstruct()
{
   m_bUniform = VARIANT_TRUE;
   m_UniformSpacing = 1.0;

   CComObject<CColumn>* pColumn;
   CComObject<CColumn>::CreateInstance(&pColumn);
   m_Columns.push_back(pColumn);

   return S_OK;
}

void CColumnSpacing::FinalRelease()
{
   m_Columns.clear();
}

STDMETHODIMP CColumnSpacing::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IColumnSpacing,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CColumnSpacing::Clone(IColumnSpacing* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CColumnSpacing> *pClone;
   CComObject<CColumnSpacing>::CreateInstance(&pClone);
   (*clone) = pClone;
   (*clone)->AddRef();

   CColumnSpacing* pSpacingClone = dynamic_cast<CColumnSpacing*>(pClone);

   pSpacingClone->m_bUniform = m_bUniform;
   pSpacingClone->m_UniformSpacing = m_UniformSpacing;

   pSpacingClone->m_SpacingData = m_SpacingData;

   // Clone all of the columns
   pClone->ClearColumns();
   std::vector<CComPtr<IColumn> >::iterator iter;
   for ( iter = m_Columns.begin(); iter != m_Columns.end(); iter++ )
   {
      CComPtr<IColumn> column = *iter;
      CColumn* pColumn = dynamic_cast<CColumn*>(column.p);

      CComPtr<IColumn> columnClone;
      pColumn->Clone(&columnClone);

      pClone->AddColumn(columnClone);
   }

   return S_OK;
}

void CColumnSpacing::ClearColumns()
{
   m_Columns.clear();
}

void CColumnSpacing::AddColumn(IColumn* column)
{
   m_Columns.push_back(CComPtr<IColumn>(column));
}

void CColumnSpacing::SetBridge(IGenericBridge* pBridge)
{
   m_pBridge = pBridge; 

   std::vector<CComPtr<IColumn> >::iterator iter;
   for ( iter = m_Columns.begin(); iter != m_Columns.end(); iter++ )
   {
      CColumn* pColumn = dynamic_cast<CColumn*>((*iter).p);
      pColumn->SetBridge(pBridge);
   }
}

Float64 CColumnSpacing::GetCrossBeamWidth()
{
   Float64 width = 0;
   if ( m_bUniform == VARIANT_TRUE )
   {
      width = m_UniformSpacing * (GetNumColumns()-1);
   }
   else
   {
      for ( std::vector<Float64>::iterator iter = m_SpacingData.m_Spacing.begin(); iter != m_SpacingData.m_Spacing.end(); iter++ )
      {
         width += *iter;
      }
   }

   width += m_SpacingData.m_Overhang[0] + m_SpacingData.m_Overhang[1];

   return width;
}

/////////////////////////////////////////////////////////////////////////////
// IColumnSpacing
STDMETHODIMP CColumnSpacing::get_Uniform(VARIANT_BOOL* bUniform)
{
   CHECK_RETVAL(bUniform);

   *bUniform = m_bUniform;

   return S_OK;
}

STDMETHODIMP CColumnSpacing::put_Uniform(VARIANT_BOOL bUniform)
{
   if ( m_bUniform == bUniform )
      return S_OK; // nothing actually changed

   m_bUniform = bUniform;

   Fire_OnColumnSpacingChanged();
   return S_OK;
}

STDMETHODIMP CColumnSpacing::get_Spacing(SpacingIndexType spaceIdx, Float64* space)
{
   CHECK_RETVAL(space);

   if ( spaceIdx < 0 || (SpacingIndexType)m_SpacingData.m_Spacing.size() <= spaceIdx && m_bUniform == VARIANT_FALSE)
      return Error(IDS_E_SPACEINDEX,IID_IColumnSpacing,GB_E_SPACEINDEX);

   if ( m_bUniform == VARIANT_TRUE )
   {
      *space = m_UniformSpacing;
      return S_OK;
   }
   
   if ( m_SpacingData.m_Spacing.size() == 0 )
      *space = 0;
   else
      *space = m_SpacingData.m_Spacing[spaceIdx];

   return S_OK;
}

STDMETHODIMP CColumnSpacing::put_Spacing(SpacingIndexType spaceIdx,Float64 space)
{
   ColumnIndexType nColumns;
   get_ColumnCount(&nColumns);
   SpacingIndexType nSpaces = SpacingIndexType(nColumns - 1);
   if ( spaceIdx < 0 || nSpaces <= spaceIdx && m_bUniform == VARIANT_FALSE )
      return Error(IDS_E_SPACEINDEX,IID_IColumnSpacing,GB_E_SPACEINDEX);

   if ( space <= 0 )
      return Error(IDS_E_SPACING,IID_IColumnSpacing,GB_E_SPACING);

   if ( m_bUniform == VARIANT_TRUE )
   {
      if ( IsEqual(m_UniformSpacing,space) )
         return S_OK; // Do nothing if same

      m_UniformSpacing = space;
   }
   else
   {
      if ( IsEqual(m_SpacingData.m_Spacing[spaceIdx],space) )
         return S_OK; // Do nothing if same

      m_SpacingData.m_Spacing[spaceIdx] = space;
   }

   Fire_OnColumnSpacingChanged();
   return S_OK;
}

STDMETHODIMP CColumnSpacing::get_Overhang(DirectionType side,Float64* overhang)
{
   CHECK_RETVAL(overhang);

   (*overhang) = m_SpacingData.m_Overhang[side == qcbLeft ? 0 : 1];

   return S_OK;
}

STDMETHODIMP CColumnSpacing::put_Overhang(DirectionType side, Float64 overhang)
{
   if ( overhang < 0 )
      return Error(IDS_E_OVERHANG,IID_IColumnSpacing,GB_E_OVERHANG);

   if ( IsEqual(m_SpacingData.m_Overhang[side == qcbLeft ? 0 : 1],overhang) )
      return S_OK; // Do nothing if same

   m_SpacingData.m_Overhang[side == qcbLeft ? 0 : 1] = overhang;

   Fire_OnColumnSpacingChanged();
   return S_OK;
}

STDMETHODIMP CColumnSpacing::get_ColumnCount(ColumnIndexType* nColumns)
{
   CHECK_RETVAL(nColumns);

   if ( m_SpacingData.m_Spacing.size() == 0 )
      (*nColumns) = 1; // if no columns, simply report 1 column
   else
      *nColumns = GetNumColumns();

   return S_OK;
}

STDMETHODIMP CColumnSpacing::Add(ColumnIndexType nColumns)
{
   if ( nColumns < 0 )
      return E_INVALIDARG;

   // Get the current number of columns
   ColumnIndexType currNumColumns;
   get_ColumnCount(&currNumColumns);

   nColumns += currNumColumns;

   SpacingIndexType nSpaces = SpacingIndexType(nColumns - 1);

   if ( nColumns < currNumColumns )
   {
      if ( currNumColumns - nColumns <= 0 )
         return E_INVALIDARG;

      // Reducing number of columns
      m_SpacingData.m_Spacing.resize(nSpaces);
      m_Columns.resize(nColumns);
   }
   else if ( currNumColumns < nColumns )
   {
      // Increasing number of columns
      Float64 lastSpace;
      if ( currNumColumns == 1 )
         lastSpace = 1; // There isn't a spacing defined, use a reasonable default
      else
         lastSpace = m_SpacingData.m_Spacing[m_SpacingData.m_Spacing.size()-1];

      m_SpacingData.m_Spacing.resize(nSpaces,lastSpace); // fills new values with lastSpace

      CComPtr<IColumn> lastColumn = m_Columns.back();
      CColumn* pLastColumn = dynamic_cast<CColumn*>(lastColumn.p);

      for ( ColumnIndexType i = 0; i < nColumns - currNumColumns; i++ )
      {
         CComPtr<IColumn> clone;
         pLastColumn->Clone(&clone);
         PutColumn(m_Columns.size(),clone);
      }
   }

   Fire_OnColumnCountChanged(nColumns);
   return S_OK;
}

STDMETHODIMP CColumnSpacing::Insert(SpacingIndexType spaceIdx,SpacingIndexType nInsert)
{
   if ( nInsert < 0 )
      return E_INVALIDARG;

   ColumnIndexType nColumns;
   get_ColumnCount(&nColumns);

   if ( nColumns <= spaceIdx )
      return Error(IDS_E_SPACEINDEX,IID_IColumnSpacing,GB_E_SPACEINDEX);

   if ( nInsert <= 0 ) // Must be adding at least 1 girder line
      return E_INVALIDARG;

   // interate over all the piers and insert girder lines
   // Get the spacing at the specified index. This is the spacing that will be used. 
   // If there is only one girder line, use a default spacing of 1
   Float64 spacing;
   if ( m_SpacingData.m_Spacing.size() == 0 )
   {
      spacing = 1.0;
   }
   else
   {
      if (spaceIdx == INVALID_INDEX) // inserting before first
         spacing = m_SpacingData.m_Spacing[0];
      else if ( (SpacingIndexType)m_SpacingData.m_Spacing.size() <= spaceIdx ) // inserting after last
         spacing = m_SpacingData.m_Spacing[m_SpacingData.m_Spacing.size()-1];
      else
         spacing = m_SpacingData.m_Spacing[spaceIdx];
   }

   SpacingIndexType offset = spaceIdx;
   if ( spaceIdx == INVALID_INDEX )
      offset = 0;
   else if ( (SpacingIndexType)m_SpacingData.m_Spacing.size() <= spaceIdx )
      offset = m_SpacingData.m_Spacing.size() - 1;

   m_SpacingData.m_Spacing.insert(m_SpacingData.m_Spacing.begin()+offset,nInsert,spacing);

   CComPtr<IColumn> lastColumn;
   if ( spaceIdx == INVALID_INDEX )
      lastColumn = m_Columns[0];
   else if ( nColumns-1 <= spaceIdx )
      lastColumn = m_Columns[nColumns-1];
   else
      lastColumn = m_Columns[spaceIdx+1];

   CColumn* pLastColumn = dynamic_cast<CColumn*>(lastColumn.p);

   for ( SpacingIndexType i = 0; i < nInsert; i++ )
   {
      CComPtr<IColumn> clone;
      pLastColumn->Clone(&clone);
      PutColumn(spaceIdx+1,clone);
   }

   get_ColumnCount(&nColumns);
   Fire_OnColumnCountChanged(nColumns);

   return S_OK;
}

STDMETHODIMP CColumnSpacing::Remove(ColumnIndexType columnIdx,ColumnIndexType nRemove)
{
   SpacingIndexType nSpaceIdx = SpacingIndexType(columnIdx == 0 ? 0 : columnIdx-1);

   if ( columnIdx < 0 || GetNumColumns() <= columnIdx )
      return Error(IDS_E_SPACEINDEX,IID_IColumnSpacing,GB_E_SPACEINDEX);

   if ( nRemove <= 0 )
      return E_INVALIDARG; // Nothing to remove

   // Get current number of columns
   ColumnIndexType nCurrColumns;
   get_ColumnCount(&nCurrColumns);

   // make sure there will be at least one column left
   if ( nCurrColumns <= nRemove )
   {
      return Error(IDS_E_LESS_THAN_MIN_COLUMNS,IID_IColumnSpacing,GB_E_LESS_THAN_MIN_COLUMNS);
   }
   ColumnIndexType nRemainingColumns = nCurrColumns - nRemove;

   // Determine the index of the last spacing to be removed
   long nLastSpaceIdx = nSpaceIdx + nRemove;

   // remove columns
   m_SpacingData.m_Spacing.erase(m_SpacingData.m_Spacing.begin()+nSpaceIdx,m_SpacingData.m_Spacing.begin()+nLastSpaceIdx);
   m_Columns.erase(m_Columns.begin()+nSpaceIdx,m_Columns.begin()+nSpaceIdx+nRemove);

   ATLASSERT(GetNumColumns() == nRemainingColumns);

   Fire_OnColumnCountChanged(nRemainingColumns);
   return S_OK;
}

STDMETHODIMP CColumnSpacing::get_Column(ColumnIndexType colIdx,IColumn* *column)
{
   CHECK_RETOBJ(column);

   if ( colIdx < 0 || (ColumnIndexType)m_Columns.size() <= colIdx )
      return E_INVALIDARG;
   
   (*column) = m_Columns[colIdx];
   (*column)->AddRef();

   return S_OK;
}

//////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CColumnSpacing::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("ColumnSpacing"),1.0);

   pSave->put_Property(CComBSTR("Uniform"),CComVariant(m_bUniform));
   pSave->put_Property(CComBSTR("UniformSpacing"),CComVariant(m_UniformSpacing));

   pSave->BeginUnit(CComBSTR("Columns"),1.0);
   long nColumns = m_Columns.size();
   pSave->put_Property(CComBSTR("NumColumns"),CComVariant(nColumns));
   std::vector<CComPtr<IColumn> >::iterator iter;
   for ( iter = m_Columns.begin(); iter != m_Columns.end(); iter++ )
   {
      CComPtr<IColumn> column = *iter;
      CComQIPtr<IStructuredStorage2> ssColumn(column);
      ssColumn->Save(pSave);
   }
   pSave->EndUnit();

   pSave->BeginUnit(CComBSTR("SpacingData"),1.0);
   pSave->put_Property(CComBSTR("LeftOverhang"), CComVariant(m_SpacingData.m_Overhang[0]));
   pSave->put_Property(CComBSTR("RightOverhang"),CComVariant(m_SpacingData.m_Overhang[1]));
   long nSpaces = m_SpacingData.m_Spacing.size();
   pSave->put_Property(CComBSTR("NumSpaces"),CComVariant(nSpaces));

   std::vector<Float64>::iterator it;
   for ( it = m_SpacingData.m_Spacing.begin(); it != m_SpacingData.m_Spacing.end(); it++ )
   {
      Float64 space = *it;
      pSave->put_Property(CComBSTR("Space"),CComVariant(space));
   }
   pSave->EndUnit();


   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CColumnSpacing::Load(IStructuredLoad2* pLoad)
{
   m_Columns.clear();

   CComVariant var;
   VARIANT_BOOL bEnd;

   pLoad->BeginUnit(CComBSTR("ColumnSpacing"));

   pLoad->get_Property(CComBSTR("Uniform"),&var);
   m_bUniform = var.boolVal;

   pLoad->get_Property(CComBSTR("UniformSpacing"),&var);
   m_UniformSpacing = var.dblVal;

   pLoad->BeginUnit(CComBSTR("Columns"));
   long nColumns;
   pLoad->get_Property(CComBSTR("NumColumns"),&var);
   nColumns = var.lVal;
   for ( long i = 0; i < nColumns; i++ )
   {
      CComObject<CColumn>* pColumn;
      CComObject<CColumn>::CreateInstance(&pColumn);
      CComPtr<IColumn> column = pColumn;

      pColumn->SetBridge(m_pBridge);

      CComQIPtr<IStructuredStorage2> ssColumn(column);
      ssColumn->Load(pLoad);

      AddColumn(column);
   }
   pLoad->EndUnit(&bEnd);

   pLoad->BeginUnit(CComBSTR("SpacingData"));
   pLoad->get_Property(CComBSTR("LeftOverhang"),&var);
   m_SpacingData.m_Overhang[0] = var.dblVal;

   pLoad->get_Property(CComBSTR("RightOverhang"),&var);
   m_SpacingData.m_Overhang[1] = var.dblVal;

   long nSpaces;
   pLoad->get_Property(CComBSTR("NumSpaces"),&var);
   nSpaces = var.lVal;
   for ( long j = 0; j < nSpaces; j++ )
   {
      pLoad->get_Property(CComBSTR("Space"),&var);
      Float64 space = var.dblVal;
      m_SpacingData.m_Spacing.push_back(space);
   }
   pLoad->EndUnit(&bEnd);

   pLoad->EndUnit(&bEnd);

   return S_OK;
}

/////////////////////////////////////////////////

ColumnIndexType CColumnSpacing::GetNumColumns() const
{
   return m_SpacingData.m_Spacing.size() + 1;
}

void CColumnSpacing::PutColumn(ColumnIndexType columnIdx,IColumn* column)
{
   m_Columns.insert(m_Columns.begin() + columnIdx,column);

   CColumn* pColumn = dynamic_cast<CColumn*>(m_Columns[columnIdx].p);
   pColumn->SetBridge(m_pBridge);
}

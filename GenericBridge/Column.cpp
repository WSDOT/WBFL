///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

// Column.cpp : Implementation of CColumn
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "Column.h"
#include "Segment.h"
#include <ComException.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColumn
HRESULT CColumn::FinalConstruct()
{
   m_Height     = 0.0;
   m_BaseElevation = 0.0;
   m_BaseOffset = 0.0;

   m_bComputeBaseElevation = false;
   m_bComputeHeight = false;

   m_Index = INVALID_INDEX;

   m_pColumnLayout = nullptr;

   return S_OK;
}

void CColumn::FinalRelease()
{
}

STDMETHODIMP CColumn::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IColumn,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//////////////////////////////////////////////////////
// IColumn
STDMETHODIMP CColumn::putref_ColumnLayout(/*[in]*/IColumnLayout* pColumnLayout)
{
   CHECK_IN(pColumnLayout);
   m_pColumnLayout = pColumnLayout;
   return S_OK;
}

STDMETHODIMP CColumn::get_ColumnLayout(/*[out,retval]*/IColumnLayout** ppColumnLayout)
{
   CHECK_RETOBJ(ppColumnLayout);
   if ( m_pColumnLayout )
   {
      (*ppColumnLayout) = m_pColumnLayout;
      (*ppColumnLayout)->AddRef();
   }
   return S_OK;
}

STDMETHODIMP CColumn::put_Index(IndexType index)
{
   m_Index = index;
   return S_OK;
}

STDMETHODIMP CColumn::get_Index(IndexType* pIndex)
{
   CHECK_RETVAL(pIndex);
   *pIndex = m_Index;
   return S_OK;
}

STDMETHODIMP CColumn::get_Height(Float64* height)
{
   CHECK_RETVAL(height);
   ComputeHeight();
   (*height) = m_Height;
   return S_OK;
}

STDMETHODIMP CColumn::put_Height(Float64 height)
{
   if ( height < 0 )
   {
      return E_INVALIDARG;
   }

   m_Height = height;
   m_bComputeHeight = false;
   m_bComputeBaseElevation = true;
   //Fire_OnColumnChanged(this);
   return S_OK;
}

STDMETHODIMP CColumn::get_BaseElevation(Float64* baseElevation)
{
   CHECK_RETVAL(baseElevation);
   ComputeBaseElevation();
   *baseElevation = m_BaseElevation;
   return S_OK;
}

STDMETHODIMP CColumn::put_BaseElevation(Float64 baseElevation)
{
   m_BaseElevation = baseElevation;
   m_bComputeHeight = true;
   m_bComputeBaseElevation = false;
   //Fire_OnColumnChanged(this);
   return S_OK;
}

STDMETHODIMP CColumn::get_BaseOffset(Float64* offset)
{
   CHECK_RETVAL(offset);
   (*offset) = m_BaseOffset;;
   return S_OK;
}

STDMETHODIMP CColumn::put_BaseOffset(Float64 offset)
{
   if ( IsEqual(m_BaseOffset,offset) )
   {
      return S_OK;
   }

   m_BaseOffset = offset;
   //Fire_OnColumnChanged(this);
   return S_OK;
}

STDMETHODIMP CColumn::get_Length(Float64* length)
{
   CHECK_RETVAL(length);
   (*length) = sqrt(m_Height*m_Height + m_BaseOffset*m_BaseOffset);
   return S_OK;
}

STDMETHODIMP CColumn::get_TopElevation(Float64* pTopElev)
{
   return m_pColumnLayout->get_TopColumnElevation(m_Index,pTopElev);
}

STDMETHODIMP CColumn::Clone(IColumn** ppClone)
{
   CComObject<CColumn>* pClone;
   CComObject<CColumn>::CreateInstance(&pClone);

   get_Height(&pClone->m_Height);
   pClone->m_bComputeBaseElevation = true;
   pClone->m_bComputeHeight = false;

   pClone->m_BaseOffset = m_BaseOffset;

   (*ppClone) = pClone;
   (*ppClone)->AddRef();
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CColumn::Load(IStructuredLoad2* load)
{
   load->BeginUnit(CComBSTR("Column"));

   CComVariant var;
   load->get_Property(CComBSTR("Height"),&var);
   m_Height = var.dblVal;

   load->get_Property(CComBSTR("BaseOffset"),&var);
   m_BaseOffset = var.dblVal;


   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CColumn::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("Column"),1.0);

   save->put_Property(CComBSTR("Height"),CComVariant(m_Height));
   save->put_Property(CComBSTR("BaseOffset"),CComVariant(m_BaseOffset));

   save->EndUnit();
   return S_OK;
}

void CColumn::ComputeHeight()
{
   if ( !m_bComputeHeight )
   {
      return;
   }

   Float64 topElev;
   get_TopElevation(&topElev);
   m_Height = topElev - m_BaseElevation;
   m_bComputeHeight = false;
}

void CColumn::ComputeBaseElevation()
{
   if ( !m_bComputeBaseElevation )
   {
      return;
   }

   Float64 topElev;
   get_TopElevation(&topElev);
   m_BaseElevation = topElev - m_Height;
   m_bComputeBaseElevation = false;
}

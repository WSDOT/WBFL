///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2016  Washington State Department of Transportation
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

// TemplateSegment.cpp : Implementation of CTemplateSegment
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "TemplateSegment.h"
#include "Station.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemplateSegment

HRESULT CTemplateSegment::FinalConstruct()
{
   m_Width = 1;
   m_Slope = 0.02;
   m_SlopeType = tsHorizontal;

   return S_OK;
}

void CTemplateSegment::FinalRelease()
{
}

STDMETHODIMP CTemplateSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_ITemplateSegment,
      &IID_IStructuredStorage2
   };
   for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

// ITemplateSegment
STDMETHODIMP CTemplateSegment::Init(Float64 width,Float64 slope,TemplateSlopeType slopeType)
{
   if ( width < 0 )
      return E_INVALIDARG;

   m_Width = width;
   m_Slope = slope;
   m_SlopeType = slopeType;

   return S_OK;
}

STDMETHODIMP CTemplateSegment::put_Width(Float64 width)
{
   if ( width < 0 )
      return E_INVALIDARG;

   if ( !IsEqual(m_Width,width) )
   {
      m_Width = width;
      Fire_OnTemplateSegmentChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CTemplateSegment::get_Width(Float64* width)
{
   CHECK_RETVAL(width);
   *width = m_Width;
   return S_OK;
}

STDMETHODIMP CTemplateSegment::put_Slope(Float64 slope)
{
   if ( !IsEqual(m_Slope,slope) )
   {
      m_Slope = slope;
      Fire_OnTemplateSegmentChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CTemplateSegment::get_Slope(Float64* slope)
{
   CHECK_RETVAL(slope);
   *slope = m_Slope;
   return S_OK;
}

STDMETHODIMP CTemplateSegment::put_SlopeType(TemplateSlopeType type)
{
   if ( m_SlopeType != type )
   {
      m_SlopeType = type;
      Fire_OnTemplateSegmentChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CTemplateSegment::get_SlopeType(TemplateSlopeType* type)
{
   CHECK_RETVAL(type);
   *type = m_SlopeType;
   return S_OK;
}

STDMETHODIMP CTemplateSegment::Clone(ITemplateSegment** ppClone)
{
   CHECK_RETOBJ(ppClone);

   CComObject<CTemplateSegment>* pClone;
   CComObject<CTemplateSegment>::CreateInstance(&pClone);

   pClone->Init(m_Width,m_Slope,m_SlopeType);

   (*ppClone) = pClone;
   (*ppClone)->AddRef();
   
   return S_OK;
}

STDMETHODIMP CTemplateSegment::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CTemplateSegment::Save(IStructuredSave2* pSave)
{
#pragma Reminder("IMPLEMENT CTemplateSegment:Save")
   pSave->BeginUnit(CComBSTR("TemplateSegment"),1.0);
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CTemplateSegment::Load(IStructuredLoad2* pLoad)
{
#pragma Reminder("IMPLEMENT CTemplateSegment::Load")

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("TemplateSegment"));


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

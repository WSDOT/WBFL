///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include "SurfaceTemplateSegment.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSurfaceTemplateSegment

HRESULT CSurfaceTemplateSegment::FinalConstruct()
{
   return S_OK;
}

void CSurfaceTemplateSegment::FinalRelease()
{
}

STDMETHODIMP CSurfaceTemplateSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_ISurfaceTemplateSegment,
   };
   for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

// ITemplateSegment
STDMETHODIMP CSurfaceTemplateSegment::Init(Float64 width,Float64 slope,TemplateSlopeType slopeType)
{
   if ( width < 0 )
      return E_INVALIDARG;

   m_Segment.SetParameters(width, slope, WBFL::COGO::SurfaceTemplateSegment::SlopeType(slopeType));
   return S_OK;
}

STDMETHODIMP CSurfaceTemplateSegment::put_Width(Float64 width)
{
   if ( width < 0 )
      return E_INVALIDARG;

   m_Segment.SetWidth(width);

   return S_OK;
}

STDMETHODIMP CSurfaceTemplateSegment::get_Width(Float64* width)
{
   CHECK_RETVAL(width);
   *width = m_Segment.GetWidth();
   return S_OK;
}

STDMETHODIMP CSurfaceTemplateSegment::put_Slope(Float64 slope)
{
   m_Segment.SetSlope(slope);

   return S_OK;
}

STDMETHODIMP CSurfaceTemplateSegment::get_Slope(Float64* slope)
{
   CHECK_RETVAL(slope);
   *slope = m_Segment.GetSlope();
   return S_OK;
}

STDMETHODIMP CSurfaceTemplateSegment::put_SlopeType(TemplateSlopeType type)
{
   m_Segment.SetSlopeType(WBFL::COGO::SurfaceTemplateSegment::SlopeType(type));

   return S_OK;
}

STDMETHODIMP CSurfaceTemplateSegment::get_SlopeType(TemplateSlopeType* type)
{
   CHECK_RETVAL(type);
   *type = TemplateSlopeType(m_Segment.GetSlopeType());
   return S_OK;
}

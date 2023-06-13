///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// SinglePierLineFactory.cpp : Implementation of CSinglePierLineFactory

#include "stdafx.h"
#include "WBFLCogo.h"
#include "UniformSpacingLayoutLineFactory.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_AlignmentID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetAlignmentID();
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_AlignmentID(IDType ID)
{
   m_Factory->SetAlignmentID(ID);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_StartPierID(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetStartPierLineID();
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_StartPierID(IDType newVal)
{
   m_Factory->SetStartPierLineID(newVal);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_EndPierID(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetEndPierLineID();
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_EndPierID(IDType newVal)
{
   m_Factory->SetEndPierLineID(newVal);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_PierIDInc(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetPierLineIDIncrement();
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_PierIDInc(IDType newVal)
{
   m_Factory->SetPierLineIDIncrement(newVal);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_StartSpacingOffset(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetStartSpacingOffset();
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_StartSpacingOffset(Float64 newVal)
{
   m_Factory->SetStartSpacingOffset(newVal);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_EndSpacingOffset(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetEndSpacingOffset();
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_EndSpacingOffset(Float64 newVal)
{
   m_Factory->SetEndSpacingOffset(newVal);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_StartSpacing(IDblArray** pVal)
{
   CHECK_RETOBJ(pVal);
   const auto& spacing = m_Factory->GetStartSpacing();
   return cogoUtil::CreateArray(spacing, pVal);
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_StartSpacing(IDblArray* newVal)
{
   CHECK_IN(newVal);
   auto spacing = cogoUtil::GetArray(newVal);
   m_Factory->SetStartSpacing(spacing);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_EndSpacing(IDblArray** pVal)
{
   CHECK_RETOBJ(pVal);
   const auto& spacing = m_Factory->GetEndSpacing();
   return cogoUtil::CreateArray(spacing,pVal);
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_EndSpacing(IDblArray* newVal)
{
   CHECK_IN(newVal);
   auto spacing = cogoUtil::GetArray(newVal);
   m_Factory->SetEndSpacing(spacing);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_LayoutLineID(IDType ID)
{
   m_Factory->SetLayoutLineID(ID);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_LayoutLineID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetLayoutLineID();
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_LayoutLineIDInc(IDType inc)
{
   m_Factory->SetLayoutLineIDIncrement(inc);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_LayoutLineIDInc(IDType* inc)
{
   CHECK_RETVAL(inc);
   *inc = m_Factory->GetLayoutLineIDIncrement();
   return S_OK;
}



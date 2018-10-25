///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2015  Washington State Department of Transportation
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

// EqualSpaceDiaphragmLineFactory.cpp : Implementation of CEqualSpaceDiaphragmLineFactory

#include "stdafx.h"
#include "EqualSpaceDiaphragmLineFactory.h"
#include "DiaphragmLine.h"

// CEqualSpaceDiaphragmLineFactory
STDMETHODIMP CEqualSpaceDiaphragmLineFactory::put_AlignmentID(CogoObjectID ID)
{
   m_AlignmentID = ID;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::get_AlignmentID(CogoObjectID* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_AlignmentID;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::put_StartStation(Float64 station)
{
   m_StartStation = station;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::get_StartStation(Float64* pStation)
{
   CHECK_RETVAL(pStation);
   *pStation = m_StartStation;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::put_EndStation(Float64 station)
{
   m_EndStation = station;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::get_EndStation(Float64* pStation)
{
   CHECK_RETVAL(pStation);
   *pStation = m_EndStation;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::put_DiaphragmLineID(LineIDType newVal)
{
   m_StartID = newVal;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::get_DiaphragmLineID(LineIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_StartID;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::put_DiaphragmLineIDInc(LineIDType newVal)
{
   m_IDInc = newVal;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::get_DiaphragmLineIDInc(LineIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_IDInc;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::put_Divisor(Int16 divisor)
{
   if ( divisor < 2 )
      return E_INVALIDARG;

   m_Divisor = divisor;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::get_Divisor(Int16* divisor)
{
   CHECK_RETVAL(divisor);
   *divisor = m_Divisor;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::put_Staggered(VARIANT_BOOL bStaggered)
{
   m_bStaggered = bStaggered;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::get_Staggered(VARIANT_BOOL* bStaggered)
{
   CHECK_RETVAL(bStaggered);
   *bStaggered = m_bStaggered;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::put_LeftGirderLineID(GirderIDType ID)
{
   m_LeftGirderID = ID;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::get_LeftGirderLineID(GirderIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_LeftGirderID;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::put_RightGirderLineID(GirderIDType ID)
{
   m_RightGirderID = ID;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::get_RightGirderLineID(GirderIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_RightGirderID;
   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::Create(IBridgeGeometry* pBridge,IUnkArray** ppArrayDiaphagmLines)
{
   CHECK_IN(pBridge);
   CHECK_RETOBJ(ppArrayDiaphagmLines);

   CComPtr<IUnkArray> arrUnks;
   arrUnks.CoCreateInstance(CLSID_UnkArray);

   CComPtr<IAlignment> alignment;
   HRESULT hr = pBridge->get_Alignment(m_AlignmentID,&alignment);
   if ( FAILED(hr) )
   {
      ATLASSERT(false); // bad alignmentID
      return hr;
   }

   LineIDType ID = m_StartID;
   for ( Int16 i = 1; i < m_Divisor; i++, ID += m_IDInc )
   {
      CComObject<CDiaphragmLine>* pDiaphragmLine;
      CComObject<CDiaphragmLine>::CreateInstance(&pDiaphragmLine);
      CComPtr<IDiaphragmLine> diaphragmLine = pDiaphragmLine;

      pDiaphragmLine->m_ID = ID;


      Float64 station = m_StartStation + (m_EndStation - m_StartStation)*i/m_Divisor;

      CComPtr<IDirection> normal;
      alignment->Normal(CComVariant(station),&normal);
      Float64 dir;
      normal->get_Value(&dir);

      CComPtr<IPoint2d> pntAlignment;
      alignment->LocatePoint(CComVariant(station),omtNormal,0.0,CComVariant(0.0),&pntAlignment);

      CComPtr<IPoint2d> p;
      CComPtr<IVector2d> v;
      pDiaphragmLine->m_Line->GetExplicit(&p,&v);
      v->put_Direction(dir);
      pDiaphragmLine->m_Line->SetExplicit(pntAlignment,v);

      pDiaphragmLine->m_pBridge = pBridge;

      pDiaphragmLine->m_LeftGirderID  = m_LeftGirderID;
      pDiaphragmLine->m_RightGirderID = m_RightGirderID;
      pDiaphragmLine->m_bStaggered    = (m_bStaggered == VARIANT_TRUE ? true : false);

      CComPtr<IUnknown> pUnk(diaphragmLine);
      arrUnks->Add(pUnk);
   }

   arrUnks.CopyTo(ppArrayDiaphagmLines);

   return S_OK;
}

STDMETHODIMP CEqualSpaceDiaphragmLineFactory::Reset()
{
   m_StartID       = INVALID_INDEX;
   m_IDInc         = 1;
   m_Divisor       = 2;
   m_bStaggered    = VARIANT_FALSE;
   m_LeftGirderID  = INVALID_INDEX;
   m_RightGirderID = INVALID_INDEX;
	return S_OK;
}

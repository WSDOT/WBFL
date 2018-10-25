///////////////////////////////////////////////////////////////////////
// BridgeGeometry
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

// ThroughPointDiaphragmLineFactory.cpp : Implementation of CThroughPointDiaphragmLineFactory

#include "stdafx.h"
#include "ThroughPointDiaphragmLineFactory.h"
#include "DiaphragmLine.h"

// CThroughPointDiaphragmLineFactory
STDMETHODIMP CThroughPointDiaphragmLineFactory::put_Point(IPoint2d* point)
{
   CHECK_IN(point);
   m_Point = point;
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_Point(IPoint2d** point)
{
   CHECK_RETOBJ(point);
   return m_Point.CopyTo(point);
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::put_Direction(IDirection* direction)
{
   CHECK_IN(direction);
   m_Direction = direction;
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_Direction(IDirection** direction)
{
   CHECK_RETOBJ(direction);
   return m_Direction.CopyTo(direction);
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::put_DiaphragmLineID(LineIDType newVal)
{
   m_ID = newVal;
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_DiaphragmLineID(LineIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_ID;
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::put_Staggered(VARIANT_BOOL bStaggered)
{
   m_bStaggered = bStaggered;
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_Staggered(VARIANT_BOOL* bStaggered)
{
   CHECK_RETVAL(bStaggered);
   *bStaggered = m_bStaggered;
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::put_LeftGirderLineID(GirderIDType ID)
{
   m_LeftGirderID = ID;
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_LeftGirderLineID(GirderIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_LeftGirderID;
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::put_RightGirderLineID(GirderIDType ID)
{
   m_RightGirderID = ID;
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_RightGirderLineID(GirderIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_RightGirderID;
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::Create(IBridgeGeometry* pBridge,IUnkArray** ppArrayDiaphagmLines)
{
   CHECK_IN(pBridge);
   CHECK_RETOBJ(ppArrayDiaphagmLines);

   CComPtr<IUnkArray> arrUnks;
   arrUnks.CoCreateInstance(CLSID_UnkArray);

   CComObject<CDiaphragmLine>* pDiaphragmLine;
   CComObject<CDiaphragmLine>::CreateInstance(&pDiaphragmLine);
   CComPtr<IDiaphragmLine> diaphragmLine = pDiaphragmLine;

   pDiaphragmLine->m_ID = m_ID;
   
   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> v;
   pDiaphragmLine->m_Line->GetExplicit(&p,&v);

   Float64 dir;
   m_Direction->get_Value(&dir);
   v->put_Direction(dir);

   pDiaphragmLine->m_Line->SetExplicit(m_Point,v);

   pDiaphragmLine->m_pBridge = pBridge;
   pDiaphragmLine->m_LeftGirderID  = m_LeftGirderID;
   pDiaphragmLine->m_RightGirderID = m_RightGirderID;
   pDiaphragmLine->m_bStaggered    = (m_bStaggered == VARIANT_TRUE ? true : false);
   
   CComPtr<IUnknown> pUnk(diaphragmLine);
   arrUnks->Add(pUnk);

   arrUnks.CopyTo(ppArrayDiaphagmLines);

   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::Reset()
{
   m_bStaggered    = VARIANT_FALSE;
   m_LeftGirderID  = INVALID_INDEX;
   m_RightGirderID = INVALID_INDEX;
	return S_OK;
}

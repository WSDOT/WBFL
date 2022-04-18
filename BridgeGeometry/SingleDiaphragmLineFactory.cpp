///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2022  Washington State Department of Transportation
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

// SingleDiaphragmLineFactory.cpp : Implementation of CSingleDiaphragmLineFactory

#include "stdafx.h"
#include "SingleDiaphragmLineFactory.h"
#include "DiaphragmLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CSingleDiaphragmLineFactory
STDMETHODIMP CSingleDiaphragmLineFactory::put_AlignmentID(CogoObjectID ID)
{
   m_AlignmentID = ID;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_AlignmentID(CogoObjectID* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_AlignmentID;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_Station(Float64 station)
{
   m_Station = station;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_Station(Float64* pStation)
{
   CHECK_RETVAL(pStation);
   *pStation = m_Station;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_Orientation(BSTR orientation)
{
   m_bstrOrientation = orientation;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_Orientation(BSTR* orientation)
{
   CHECK_RETSTRING(orientation);
   *orientation = m_bstrOrientation.Copy();
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_DiaphragmLineID(LineIDType newVal)
{
   m_ID = newVal;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_DiaphragmLineID(LineIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_ID;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_Staggered(VARIANT_BOOL bStaggered)
{
   m_bStaggered = bStaggered;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_Staggered(VARIANT_BOOL* bStaggered)
{
   CHECK_RETVAL(bStaggered);
   *bStaggered = m_bStaggered;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_LeftGirderLineID(GirderIDType ID)
{
   m_LeftGirderID = ID;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_LeftGirderLineID(GirderIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_LeftGirderID;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_RightGirderLineID(GirderIDType ID)
{
   m_RightGirderID = ID;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_RightGirderLineID(GirderIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_RightGirderID;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::Create(IBridgeGeometry* pBridge,IUnkArray** ppArrayDiaphagmLines)
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

   LineIDType ID = m_ID;

   CComObject<CDiaphragmLine>* pDiaphragmLine;
   CComObject<CDiaphragmLine>::CreateInstance(&pDiaphragmLine);
   CComPtr<IDiaphragmLine> diaphragmLine = pDiaphragmLine;

   pDiaphragmLine->m_ID = ID;

   pDiaphragmLine->m_pBridge = pBridge;
   pDiaphragmLine->m_LeftGirderID  = m_LeftGirderID;
   pDiaphragmLine->m_RightGirderID = m_RightGirderID;
   pDiaphragmLine->m_bStaggered    = (m_bStaggered == VARIANT_TRUE ? true : false);
   
   CComPtr<IPoint2d> pntAlignment;
   alignment->LocatePoint(CComVariant(m_Station),omtNormal,0.0,CComVariant(0.0),&pntAlignment);

   CComPtr<IDirection> objDirection;
   alignment->GetDirection(CComVariant(m_Station),m_bstrOrientation,&objDirection);
   Float64 dir;
   objDirection->get_Value(&dir);

   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> v;
   pDiaphragmLine->m_Line->GetExplicit(&p,&v);
   v->put_Direction(dir);
   pDiaphragmLine->m_Line->SetExplicit(pntAlignment,v);


   CComPtr<IUnknown> pUnk(diaphragmLine);
   arrUnks->Add(pUnk);

   arrUnks.CopyTo(ppArrayDiaphagmLines);

   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::Reset()
{
   m_AlignmentID   = INVALID_INDEX;
   m_Divisor       = 2;
   m_bStaggered    = VARIANT_FALSE;
   m_LeftGirderID  = INVALID_INDEX;
   m_RightGirderID = INVALID_INDEX;
	return S_OK;
}

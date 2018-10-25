///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2017  Washington State Department of Transportation
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

// SingleGirderLineFactory.cpp : Implementation of CSingleGirderLineFactory

#include "stdafx.h"
#include "SingleGirderLineFactory.h"
#include "GirderLine.h"

// CSingleGirderLineFactory


STDMETHODIMP CSingleGirderLineFactory::get_GirderLineID(GirderIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_GirderLineID;

   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_GirderLineID(GirderIDType newVal)
{
   m_GirderLineID = newVal;

   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_LayoutLineID(LineIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_LayoutLineID;

   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_LayoutLineID(LineIDType newVal)
{
   m_LayoutLineID = newVal;

   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_Type(GirderLineType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_GirderLineType;
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_Type(GirderLineType newVal)
{
   m_GirderLineType = newVal;
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_StartPierID(PierIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_StartPierID;

   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_StartPierID(PierIDType newVal)
{
   m_StartPierID = newVal;
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_EndPierID(PierIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_EndPierID;

   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_EndPierID(PierIDType newVal)
{
   m_EndPierID = newVal;
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_StartMeasurementType(MeasurementType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_MeasureType[etStart];
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_StartMeasurementType(MeasurementType newVal)
{
   m_MeasureType[etStart] = newVal;
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_StartMeasurementLocation(MeasurementLocation* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_MeasureLocation[etStart];
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_StartMeasurementLocation(MeasurementLocation newVal)
{
   m_MeasureLocation[etStart] = newVal;
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_EndMeasurementType(MeasurementType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_MeasureType[etEnd];
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_EndMeasurementType(MeasurementType newVal)
{
   m_MeasureType[etEnd] = newVal;
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_EndMeasurementLocation(MeasurementLocation* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_MeasureLocation[etEnd];
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_EndMeasurementLocation(MeasurementLocation newVal)
{
   m_MeasureLocation[etEnd] = newVal;
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::Create(IBridgeGeometry* pBridge,IUnkArray** ppArrayGirderLines)
{
   CHECK_IN(pBridge);
   CHECK_RETOBJ(ppArrayGirderLines);

   CComPtr<IUnkArray> arrUnks;
   arrUnks.CoCreateInstance(CLSID_UnkArray);

   CComObject<CGirderLine>* pGirderLine;
   CComObject<CGirderLine>::CreateInstance(&pGirderLine);
   CComPtr<IGirderLine> girderLine = pGirderLine;

   pGirderLine->m_pBridge         = pBridge;
   pGirderLine->m_ID              = m_GirderLineID;
   pGirderLine->m_LayoutLineID    = m_LayoutLineID;
   pGirderLine->m_Type            = m_GirderLineType;
   pGirderLine->m_StartPierID     = m_StartPierID;
   pGirderLine->m_EndPierID       = m_EndPierID;
   pGirderLine->m_MeasureType[etStart] = m_MeasureType[etStart];
   pGirderLine->m_MeasureLocation[etStart] = m_MeasureLocation[etStart];
   pGirderLine->m_MeasureType[etEnd] = m_MeasureType[etEnd];
   pGirderLine->m_MeasureLocation[etEnd] = m_MeasureLocation[etEnd];

   CComPtr<IUnknown> pUnk(girderLine);

   arrUnks->Add(pUnk);
   arrUnks.CopyTo(ppArrayGirderLines);
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::Reset()
{
   m_GirderLineID = INVALID_INDEX;
   m_LayoutLineID = INVALID_INDEX;
   m_StartPierID  = INVALID_INDEX;
   m_EndPierID    = INVALID_INDEX;
   m_GirderLineType = glChord;
   m_MeasureType[etStart] = mtAlongItem;
   m_MeasureLocation[etStart] = mlPierLine;
   m_MeasureType[etEnd] = mtAlongItem;
   m_MeasureLocation[etEnd] = mlPierLine;

	return S_OK;
}

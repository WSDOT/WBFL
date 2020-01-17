///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2020  Washington State Department of Transportation
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

// SimpleGirderLineFactory.cpp : Implementation of CSimpleGirderLineFactory

#include "stdafx.h"
#include "SimpleGirderLineFactory.h"
#include "GirderLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



// CSimpleGirderLineFactory

STDMETHODIMP CSimpleGirderLineFactory::get_GirderLineID(GirderIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_StartGirderLineID;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_GirderLineID(GirderIDType newVal)
{
   m_StartGirderLineID = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_GirderLineIDInc(GirderIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_GirderLineIDInc;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_GirderLineIDInc(GirderIDType newVal)
{
   m_GirderLineIDInc = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_LeftLayoutLineID(LineIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_LeftLayoutLineID;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_LeftLayoutLineID(LineIDType newVal)
{
   m_LeftLayoutLineID = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_RightLayoutLineID(LineIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_RightLayoutLineID;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_RightLayoutLineID(LineIDType newVal)
{
   m_RightLayoutLineID = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_LayoutLineIDInc(LineIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_LayoutLineIDInc;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_LayoutLineIDInc(LineIDType newVal)
{
   m_LayoutLineIDInc = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_Type(GirderLineType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_GirderLineType;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_Type(GirderLineType newVal)
{
   m_GirderLineType = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_StartPierID(PierIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_StartPierID;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_StartPierID(PierIDType newVal)
{
   m_StartPierID = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_EndPierID(PierIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_EndPierID;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_EndPierID(PierIDType newVal)
{
   m_EndPierID = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_PierIDInc(PierIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_PierIDInc;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_PierIDInc(PierIDType newVal)
{
   m_PierIDInc = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_Continuous(VARIANT_BOOL* pbContinuous)
{
   CHECK_RETVAL(pbContinuous);
   *pbContinuous = m_bContinuous;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_Continuous(VARIANT_BOOL bContinuous)
{
   m_bContinuous = bContinuous;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_StartMeasurementType(MeasurementType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_MeasureType[etStart];
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_StartMeasurementType(MeasurementType newVal)
{
   m_MeasureType[etStart] = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_StartMeasurementLocation(MeasurementLocation* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_MeasureLocation[etStart];
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_StartMeasurementLocation(MeasurementLocation newVal)
{
   m_MeasureLocation[etStart] = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_EndMeasurementType(MeasurementType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_MeasureType[etEnd];
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_EndMeasurementType(MeasurementType newVal)
{
   m_MeasureType[etEnd] = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::get_EndMeasurementLocation(MeasurementLocation* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_MeasureLocation[etEnd];
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::put_EndMeasurementLocation(MeasurementLocation newVal)
{
   m_MeasureLocation[etEnd] = newVal;
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::Create(IBridgeGeometry* pBridge,IUnkArray** ppArrayGirderLines)
{
   CHECK_IN(pBridge);
   CHECK_RETOBJ(ppArrayGirderLines);

   CComPtr<IUnkArray> arrUnks;
   arrUnks.CoCreateInstance(CLSID_UnkArray);

   if ( m_bContinuous == VARIANT_TRUE )
   {
      GirderIDType girderLineID = m_StartGirderLineID;
      LineIDType layoutLineID = m_LeftLayoutLineID;
      for ( ; layoutLineID <= m_RightLayoutLineID; girderLineID += m_GirderLineIDInc, layoutLineID += m_LayoutLineIDInc )
      {
         CComObject<CGirderLine>* pGirderLine;
         CComObject<CGirderLine>::CreateInstance(&pGirderLine);
         CComPtr<IGirderLine> girderLine = pGirderLine;

         pGirderLine->m_pBridge      = pBridge;
         pGirderLine->m_ID           = girderLineID;
         pGirderLine->m_LayoutLineID = layoutLineID;
         pGirderLine->m_Type         = m_GirderLineType;

         pGirderLine->m_StartPierID  = m_StartPierID;
         pGirderLine->m_EndPierID    = m_EndPierID;

         pGirderLine->m_MeasureType[etStart]     = m_MeasureType[etStart];
         pGirderLine->m_MeasureLocation[etStart] = m_MeasureLocation[etStart];

         pGirderLine->m_MeasureType[etEnd]     = m_MeasureType[etEnd];
         pGirderLine->m_MeasureLocation[etEnd] = m_MeasureLocation[etEnd];

         CComPtr<IUnknown> pUnk(girderLine);

         arrUnks->Add(pUnk);
      }
   }
   else
   {
      // simple span layout
      GirderIDType girderLineID = m_StartGirderLineID;
      for ( PierIDType pierID = m_StartPierID; pierID < m_EndPierID; pierID += m_PierIDInc )
      {
         LineIDType layoutLineID = m_LeftLayoutLineID;
         for ( ; layoutLineID <= m_RightLayoutLineID; girderLineID += m_GirderLineIDInc, layoutLineID += m_LayoutLineIDInc )
         {
            CComObject<CGirderLine>* pGirderLine;
            CComObject<CGirderLine>::CreateInstance(&pGirderLine);
            CComPtr<IGirderLine> girderLine = pGirderLine;

            pGirderLine->m_pBridge      = pBridge;
            pGirderLine->m_ID           = girderLineID;
            pGirderLine->m_LayoutLineID = layoutLineID;
            pGirderLine->m_Type         = m_GirderLineType;

            pGirderLine->m_StartPierID  = pierID;
            pGirderLine->m_EndPierID    = pierID+m_PierIDInc;

            pGirderLine->m_MeasureType[etStart]     = m_MeasureType[etStart];
            pGirderLine->m_MeasureLocation[etStart] = m_MeasureLocation[etStart];

            pGirderLine->m_MeasureType[etEnd]     = m_MeasureType[etEnd];
            pGirderLine->m_MeasureLocation[etEnd] = m_MeasureLocation[etEnd];

            CComPtr<IUnknown> pUnk(girderLine);

            arrUnks->Add(pUnk);
         }
      }
   }
   arrUnks.CopyTo(ppArrayGirderLines);
   return S_OK;
}

STDMETHODIMP CSimpleGirderLineFactory::Reset()
{
   m_StartGirderLineID     = INVALID_INDEX;
   m_GirderLineIDInc       = 1;
   m_LeftLayoutLineID      = INVALID_INDEX;
   m_RightLayoutLineID     = INVALID_INDEX;
   m_LayoutLineIDInc       = 1;
   m_StartPierID           = INVALID_INDEX;
   m_EndPierID             = INVALID_INDEX;
   m_PierIDInc             = 1;
   m_GirderLineType        = glChord;
   m_bContinuous           = VARIANT_TRUE;
   m_MeasureType[etStart]     = mtAlongItem;
   m_MeasureLocation[etStart] = mlPierLine;
   m_MeasureType[etEnd]     = mtAlongItem;
   m_MeasureLocation[etEnd] = mlPierLine;

   return S_OK;
}

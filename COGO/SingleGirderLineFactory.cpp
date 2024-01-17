///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// SinglePierLineFactory.cpp : Implementation of CSinglePierLineFactory

#include "stdafx.h"
#include "WBFLCogo.h"
#include "SingleGirderLineFactory.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

STDMETHODIMP CSingleGirderLineFactory::get_GirderLineID(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetGirderLineID();
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_GirderLineID(IDType newVal)
{
   m_Factory->SetGirderLineID(newVal);
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_LayoutLineID(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetLayoutLineID();
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_LayoutLineID(IDType newVal)
{
   m_Factory->SetLayoutLineID(newVal);
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_Type(GirderLineType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = GirderLineType(m_Factory->GetGirderLineType());
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_Type(GirderLineType newVal)
{
   m_Factory->SetGirderLineType(WBFL::COGO::GirderLineType(newVal));
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_StartPierID(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetPierID(WBFL::COGO::EndType::Start);
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_StartPierID(IDType newVal)
{
   m_Factory->SetPierID(WBFL::COGO::EndType::Start, newVal);
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_EndPierID(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetPierID(WBFL::COGO::EndType::End);
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_EndPierID(IDType newVal)
{
   m_Factory->SetPierID(WBFL::COGO::EndType::End, newVal);
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_StartMeasurementType(MeasurementType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = MeasurementType(m_Factory->GetMeasurementType(WBFL::COGO::EndType::Start));
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_StartMeasurementType(MeasurementType newVal)
{
   m_Factory->SetMeasurementType(WBFL::COGO::EndType::Start, (WBFL::COGO::MeasurementType(newVal)));
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_StartMeasurementLocation(MeasurementLocation* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = MeasurementLocation(m_Factory->GetMeasurementLocation(WBFL::COGO::EndType::Start));
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_StartMeasurementLocation(MeasurementLocation newVal)
{
   m_Factory->SetMeasurementLocation(WBFL::COGO::EndType::Start, WBFL::COGO::MeasurementLocation(newVal));
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_EndMeasurementType(MeasurementType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = MeasurementType(m_Factory->GetMeasurementType(WBFL::COGO::EndType::End));
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_EndMeasurementType(MeasurementType newVal)
{
   m_Factory->SetMeasurementType(WBFL::COGO::EndType::End, (WBFL::COGO::MeasurementType(newVal)));
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::get_EndMeasurementLocation(MeasurementLocation* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = MeasurementLocation(m_Factory->GetMeasurementLocation(WBFL::COGO::EndType::End));
   return S_OK;
}

STDMETHODIMP CSingleGirderLineFactory::put_EndMeasurementLocation(MeasurementLocation newVal)
{
   m_Factory->SetMeasurementLocation(WBFL::COGO::EndType::End, WBFL::COGO::MeasurementLocation(newVal));
   return S_OK;
}

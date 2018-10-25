///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// PCISolution.cpp : Implementation of CPCISolution
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "PCISolution.h"
#include "RCSolution.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCISolution

HRESULT CPCISolution::FinalConstruct()
{
   CComObject<CRCSolution>* pSolution;
   CComObject<CRCSolution>::CreateInstance(&pSolution);
   m_Solution = pSolution;

   return S_OK;
}

void CPCISolution::FinalRelease()
{
   m_Solution.Release();
}


STDMETHODIMP CPCISolution::InitSolution(Float64 Mn,Float64 c,Float64 fps,Float64 Cflange,Float64 Cweb,Float64 T,Float64 Yflange,Float64 Yweb,VARIANT_BOOL bIsOverReinforced)
{
   return m_Solution->InitSolution(Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bIsOverReinforced);
}

STDMETHODIMP CPCISolution::get_Mn(Float64 *pVal)
{
   return m_Solution->get_Mn(pVal);
}

STDMETHODIMP CPCISolution::get_IsOverReinforced(VARIANT_BOOL *pVal)
{
   return m_Solution->get_IsOverReinforced(pVal);
}

STDMETHODIMP CPCISolution::get_NeutralAxisDepth(Float64* pVal)
{
   return m_Solution->get_NeutralAxisDepth(pVal);
}

STDMETHODIMP CPCISolution::get_fps(Float64* pVal)
{
   return m_Solution->get_fps(pVal);
}

STDMETHODIMP CPCISolution::get_Cflange(Float64 *pVal)
{
   return m_Solution->get_Cflange(pVal);
}

STDMETHODIMP CPCISolution::get_Cweb(Float64 *pVal)
{
   return m_Solution->get_Cweb(pVal);
}

STDMETHODIMP CPCISolution::get_T(Float64 *pVal)
{
   return m_Solution->get_T(pVal);
}

STDMETHODIMP CPCISolution::get_Yflange(Float64 *pVal)
{
   return m_Solution->get_Yflange(pVal);
}

STDMETHODIMP CPCISolution::get_Yweb(Float64 *pVal)
{
   return m_Solution->get_Yweb(pVal);
}

STDMETHODIMP CPCISolution::InitSolution(Float64 Mn,Float64 c,Float64 fps,Float64 Cflange,Float64 Cweb,Float64 T,Float64 Yflange,Float64 Yweb,VARIANT_BOOL bOverReinforced,Float64 avgBeta1)
{
   InitSolution(Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bOverReinforced);
   m_AvgBeta1 = avgBeta1;
   return S_OK;
}

STDMETHODIMP CPCISolution::get_AvgBeta1(Float64 *pVal)
{
   *pVal = m_AvgBeta1;
   return S_OK;
}

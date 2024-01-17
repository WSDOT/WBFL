///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
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

// PCISolutionEx.cpp : Implementation of CPCISolutionEx
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "RCSolutionEx.h"
#include "PCISolutionEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCISolutionEx


HRESULT CPCISolutionEx::FinalConstruct()
{
   CComObject<CRCSolutionEx>* pSolution;
   CComObject<CRCSolutionEx>::CreateInstance(&pSolution);
   m_Solution = pSolution;

   return S_OK;
}

void CPCISolutionEx::FinalRelease()
{
   m_Solution.Release();
}


STDMETHODIMP CPCISolutionEx::InitSolution(Float64 Mn,Float64 c,IDblArray* fs,IDblArray* fps,Float64 Cflange,Float64 Cweb,Float64 T,Float64 Yflange,Float64 Yweb)
{
   return m_Solution->InitSolution(Mn,c,fs,fps,Cflange,Cweb,T,Yflange,Yweb);
}

STDMETHODIMP CPCISolutionEx::get_Mn(Float64 *pVal)
{
   return m_Solution->get_Mn(pVal);
}

STDMETHODIMP CPCISolutionEx::get_NeutralAxisDepth(Float64* pVal)
{
   return m_Solution->get_NeutralAxisDepth(pVal);
}

STDMETHODIMP CPCISolutionEx::get_fs(IDblArray** pVal)
{
   return m_Solution->get_fs(pVal);
}

STDMETHODIMP CPCISolutionEx::get_fps(IDblArray** pVal)
{
   return m_Solution->get_fps(pVal);
}

STDMETHODIMP CPCISolutionEx::get_Cflange(Float64 *pVal)
{
   return m_Solution->get_Cflange(pVal);
}

STDMETHODIMP CPCISolutionEx::get_Cweb(Float64 *pVal)
{
   return m_Solution->get_Cweb(pVal);
}

STDMETHODIMP CPCISolutionEx::get_T(Float64 *pVal)
{
   return m_Solution->get_T(pVal);
}

STDMETHODIMP CPCISolutionEx::get_Yflange(Float64 *pVal)
{
   return m_Solution->get_Yflange(pVal);
}

STDMETHODIMP CPCISolutionEx::get_Yweb(Float64 *pVal)
{
   return m_Solution->get_Yweb(pVal);
}

STDMETHODIMP CPCISolutionEx::InitSolution(Float64 Mn,Float64 c,IDblArray* fs,IDblArray* fps,Float64 Cflange,Float64 Cweb,Float64 T,Float64 Yflange,Float64 Yweb,Float64 avgBeta1)
{
   InitSolution(Mn,c,fs,fps,Cflange,Cweb,T,Yflange,Yweb);
   m_AvgBeta1 = avgBeta1;
   return S_OK;
}

STDMETHODIMP CPCISolutionEx::get_AvgBeta1(Float64 *pVal)
{
   *pVal = m_AvgBeta1;
   return S_OK;
}

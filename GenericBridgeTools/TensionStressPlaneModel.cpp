///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2021  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TensionStressPlaneModel.cpp : Implementation of CTensionStressPlaneModel
#include "stdafx.h"
#include "TensionStressPlaneModel.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTensionStressPlaneModel

STDMETHODIMP CTensionStressPlaneModel::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] =
   {
      &IID_IStressStrain,
      &IID_IStructuredStorage2
   };
   for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i], riid))
         return S_OK;
   }
   return S_FALSE;
}

STDMETHODIMP CTensionStressPlaneModel::put_Name(BSTR name)
{
   m_bstrName = name;
   return S_OK;
}

STDMETHODIMP CTensionStressPlaneModel::get_Name(BSTR *name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}

STDMETHODIMP CTensionStressPlaneModel::ComputeStress(Float64 strain, Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = (strain < 0 ? 0 : strain);

   return S_OK;
}

STDMETHODIMP CTensionStressPlaneModel::StrainLimits(Float64* minStrain, Float64* maxStrain)
{
   // we aren't using real strains so there is no strain limit
   // use extreme values so strains are always valid
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   *minStrain = -Float64_Max;
   *maxStrain = Float64_Max;
   return S_OK;
}

STDMETHODIMP CTensionStressPlaneModel::get_StrainAtPeakStress(Float64* strain)
{
   ATLASSERT(false); // this shouldn't get called in the context that it is being used
   CHECK_RETVAL(strain);
   *strain = 0;
   return S_OK;
}

STDMETHODIMP CTensionStressPlaneModel::get_YieldStrain(Float64* pey)
{
   ATLASSERT(false); // this shouldn't get called in the context that it is being used
   CHECK_RETVAL(pey);
   *pey = 0;
   return S_OK;
}

STDMETHODIMP CTensionStressPlaneModel::get_ModulusOfElasticity(Float64* pE)
{
   ATLASSERT(false); // this shouldn't get called in the context that it is being used
   *pE = 0;
   return S_OK;
}

///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// PrestressingStrand.cpp : Implementation of CPrestressingStrand
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "PrestressingStrand.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Float64 gs_Grade[2] = { 250.0, 270.0 };  // KSI
Float64 gs_Size[6][2] = { {0.25,   0.036} ,   // Inch, Inch^2
                         {0.3125, 0.058},
                         {0.375,  0.080},
                         {0.4375, 0.108},
                         {0.50,   0.1440},
                         {0.60,   0.2160} 
                       };

////////////////////////////////////////////////////////////////////////////
// CPrestressingStrand
HRESULT CPrestressingStrand::FinalConstruct()
{
   return S_OK;
}

void CPrestressingStrand::FinalRelease()
{
}

STDMETHODIMP CPrestressingStrand::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPrestressingStrand,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////
// IPrestressingStrand
STDMETHODIMP CPrestressingStrand::get_Name(BSTR* name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::put_Name(BSTR name)
{
   CHECK_IN(name);
   m_bstrName = name;
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_Grade(StrandGrade* grade)
{
   CHECK_RETVAL(grade);
   *grade = m_Grade;
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::put_Grade(StrandGrade grade)
{
   m_Grade = grade;
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_Type(StrandType* type)
{
   CHECK_RETVAL(type);
   *type = m_Type;
   return m_Type;
}

STDMETHODIMP CPrestressingStrand::put_Type(StrandType type)
{
   m_Type = type;
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_Size(StrandSize* size)
{
   CHECK_RETVAL(size);
   *size = m_Size;
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::put_Size(StrandSize size)
{
   m_Size = size;
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_NominalDiameter(Float64* dps)
{
   CHECK_RETVAL(dps);
   *dps = gs_Size[m_Size][0];
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_NominalArea(Float64* aps)
{
   CHECK_RETVAL(aps);
   *aps = gs_Size[m_Size][1];
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_UltimateStrength(Float64* fpu)
{
   CHECK_RETVAL(fpu);
   *fpu = gs_Grade[m_Grade];
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_YieldStrength(Float64* fpy)
{
   HRESULT hr = get_UltimateStrength(fpy);
   if ( FAILED(hr) )
      return hr;

   (*fpy) *= (m_Type == LowRelaxation ? 0.85 : 0.90);
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_ModulusE(Float64* e)
{
   CHECK_RETVAL(e);
   (*e) = 28500.0;
   return S_OK;
}


/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CPrestressingStrand::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("PrestressingStrand"));



   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CPrestressingStrand::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("PrestressingStrand"),1.0);



   save->EndUnit();

   return S_OK;
}

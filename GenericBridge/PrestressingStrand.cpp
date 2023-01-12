///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <Units\Units.h>

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

const WBFL::Materials::PsStrand* CPrestressingStrand::GetStrand()
{
   lrfdStrandPool* pStrandPool = lrfdStrandPool::GetInstance();
   const WBFL::Materials::PsStrand* pStrand = pStrandPool->GetStrand((WBFL::Materials::PsStrand::Grade)m_Grade,
                                                       (WBFL::Materials::PsStrand::Type)m_Type,
                                                       (WBFL::Materials::PsStrand::Coating)m_Coating,
                                                       (WBFL::Materials::PsStrand::Size)m_Size);

   return pStrand;
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

STDMETHODIMP CPrestressingStrand::get_Type(StrandMaterialType* type)
{
   CHECK_RETVAL(type);
   *type = m_Type;
   return m_Type;
}

STDMETHODIMP CPrestressingStrand::put_Type(StrandMaterialType type)
{
   m_Type = type;
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_Coating(StrandCoating* coating)
{
   CHECK_RETVAL(coating);
   *coating = m_Coating;
   return m_Coating;
}

STDMETHODIMP CPrestressingStrand::put_Coating(StrandCoating coating)
{
   m_Coating = coating;
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

STDMETHODIMP CPrestressingStrand::put_InstallationStage(StageIndexType stageIdx)
{
   m_InstallationStageIdx = stageIdx;
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_InstallationStage(StageIndexType* pStageIdx)
{
   CHECK_RETVAL(pStageIdx);
   *pStageIdx = m_InstallationStageIdx;
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::put_RemovalStage(StageIndexType stageIdx)
{
   m_RemovalStageIdx = stageIdx;
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_RemovalStage(StageIndexType* pStageIdx)
{
   CHECK_RETVAL(pStageIdx);
   *pStageIdx = m_RemovalStageIdx;
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_NominalDiameter(Float64* dps)
{
   CHECK_RETVAL(dps);

   const WBFL::Materials::PsStrand* pStrand = GetStrand();
   *dps = pStrand->GetNominalDiameter();
   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_NominalArea(Float64* aps)
{
   CHECK_RETVAL(aps);

   const WBFL::Materials::PsStrand* pStrand = GetStrand();
   *aps = pStrand->GetNominalArea();

   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_UltimateStrength(Float64* fpu)
{
   CHECK_RETVAL(fpu);

    const WBFL::Materials::PsStrand* pStrand = GetStrand();
   *fpu = pStrand->GetUltimateStrength();

   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_YieldStrength(Float64* fpy)
{
   CHECK_RETVAL(fpy);

   const WBFL::Materials::PsStrand* pStrand = GetStrand();
   *fpy = pStrand->GetYieldStrength();

   return S_OK;
}

STDMETHODIMP CPrestressingStrand::get_ModulusE(Float64* e)
{
   CHECK_RETVAL(e);

   const WBFL::Materials::PsStrand* pStrand = GetStrand();
   *e = pStrand->GetE();

   return S_OK;
}

/////////////////////////////////////////////////////
// IMaterial
STDMETHODIMP CPrestressingStrand::get_E(StageIndexType stageIdx,Float64* E)
{
   CHECK_RETVAL(E);
   ATLASSERT(m_InstallationStageIdx <= m_RemovalStageIdx); // installation must be before removal (equal case is when they are bot INVALID_INDEX)
   if (
         (stageIdx < m_InstallationStageIdx || m_InstallationStageIdx == INVALID_INDEX) // stage is before installation or there isn't an installation stage
      || // -OR-
         (m_RemovalStageIdx < stageIdx && m_RemovalStageIdx != INVALID_INDEX) // stage is after removal and there is a removal stage
      )
   {
      *E = 0;
   }
   else
   {
      get_ModulusE(E);
   }

   return S_OK;
}

STDMETHODIMP CPrestressingStrand::put_E(StageIndexType stageIdx,Float64 E)
{
   ATLASSERT(false); // this method shouldn't be called
   return E_NOTIMPL;
}

STDMETHODIMP CPrestressingStrand::get_Density(StageIndexType stageIdx,Float64* w)
{
   CHECK_RETVAL(w);
   ATLASSERT(m_InstallationStageIdx <= m_RemovalStageIdx); // installation must be before removal (equal case is when they are bot INVALID_INDEX)
   if (
      (stageIdx < m_InstallationStageIdx || m_InstallationStageIdx == INVALID_INDEX) // stage is before installation or there isn't an installation stage
      || // -OR-
      (m_RemovalStageIdx < stageIdx && m_RemovalStageIdx != INVALID_INDEX) // stage is after removal and there is a removal stage
      )
   {
      *w = 0;
   }
   else
   {
      *w = WBFL::Units::ConvertToSysUnits(490.0, WBFL::Units::Measure::LbfPerFeet3);
   }

   return S_OK;
}

STDMETHODIMP CPrestressingStrand::put_Density(StageIndexType stageIdx,Float64 w)
{
   ATLASSERT(false); // this method shouldn't be called
   return E_NOTIMPL;
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

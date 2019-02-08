///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2019  Washington State Department of Transportation
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

// Rebar.cpp : Implementation of CRebar
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "Rebar.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRebar
HRESULT CRebar::FinalConstruct()
{
   return S_OK;
}

void CRebar::FinalRelease()
{
}

STDMETHODIMP CRebar::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRebar,
      &IID_IMaterial,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CRebar::Clone(IRebar** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CRebar>* pClone;
   CComObject<CRebar>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->Init(m_Name,m_E,m_Density,m_fpu,m_fpy,m_db,m_Ab,m_InstallationStageIdx);

   return S_OK;
}

STDMETHODIMP CRebar::Init(BSTR name,Float64 Es,Float64 density,Float64 fpu,Float64 fpy,Float64 db,Float64 Ab,StageIndexType stageIdx)
{
   m_Name    = CComBSTR(name);
   m_E       = Es;
   m_Density = density;
   m_fpu     = fpu;
   m_fpy     = fpy;
   m_db      = db;
   m_Ab      = Ab;
   m_InstallationStageIdx = stageIdx;
   return S_OK;
}

STDMETHODIMP CRebar::get_Name(BSTR* name)
{
   CHECK_RETSTRING(name);
   (*name) = m_Name.Copy();
   return S_OK;
}

STDMETHODIMP CRebar::put_Name(BSTR name)
{
   m_Name = name;
   return S_OK;
}

STDMETHODIMP CRebar::get_UltimateStrength(Float64* fpu)
{
   CHECK_RETVAL(fpu);
   *fpu = m_fpu;
   return S_OK;
}

STDMETHODIMP CRebar::put_UltimateStrength(Float64 fpu)
{
   m_fpu = fpu;
   return S_OK;
}

STDMETHODIMP CRebar::get_YieldStrength(Float64* fpy)
{
   CHECK_RETVAL(fpy);
   *fpy = m_fpy;
   return S_OK;
}

STDMETHODIMP CRebar::put_YieldStrength(Float64 fpy)
{
   m_fpy = fpy;
   return S_OK;
}

STDMETHODIMP CRebar::get_NominalDiameter(Float64* db)
{
   CHECK_RETVAL(db);
   *db = m_db;
   return S_OK;
}

STDMETHODIMP CRebar::put_NominalDiameter(Float64 db)
{
   m_db = db;
   return S_OK;
}

STDMETHODIMP CRebar::get_NominalArea(Float64* Ab)
{
   CHECK_RETVAL(Ab);
   *Ab = m_Ab;
   return S_OK;
}

STDMETHODIMP CRebar::put_NominalArea(Float64 Ab)
{
   m_Ab = Ab;
   return S_OK;
}

STDMETHODIMP CRebar::get_InstallationStage(StageIndexType* pStageIdx)
{
   CHECK_RETVAL(pStageIdx);
   *pStageIdx = m_InstallationStageIdx;
   return S_OK;
}

STDMETHODIMP CRebar::put_InstallationStage(StageIndexType stageIdx)
{
   m_InstallationStageIdx = stageIdx;
   return S_OK;
}

/////////////////////////////////////////////////////
// IMaterial implementation
STDMETHODIMP CRebar::get_E(StageIndexType stageIdx,Float64* E)
{
   CHECK_RETVAL(E);
   if ( stageIdx < m_InstallationStageIdx || m_InstallationStageIdx == INVALID_INDEX )
      (*E) = 0;
   else
      (*E) = m_E;

   return S_OK;
}

STDMETHODIMP CRebar::put_E(StageIndexType stageIdx,Float64 E)
{
   ATLASSERT(false); // don't call this method
   return E_NOTIMPL;
}

STDMETHODIMP CRebar::get_Density(StageIndexType stageIdx,Float64* w)
{
   CHECK_RETVAL(w);
   if ( stageIdx < m_InstallationStageIdx )
      (*w) = 0;
   else
      (*w) = m_Density;

   return S_OK;
}

STDMETHODIMP CRebar::put_Density(StageIndexType stageIdx,Float64 w)
{
   ATLASSERT(false); // don't call this method
   return E_NOTIMPL;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CRebar::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("Rebar"));

   load->get_Property(CComBSTR("Name"),&var);
   m_Name = var.bstrVal;

   load->get_Property(CComBSTR("E"),&var);
   m_E = var.dblVal;

   load->get_Property(CComBSTR("Density"),&var);
   m_Density = var.dblVal;

   load->get_Property(CComBSTR("UltimateStrength"),&var);
   m_fpu = var.dblVal;

   load->get_Property(CComBSTR("YieldStrength"),&var);
   m_fpy = var.dblVal;

   load->get_Property(CComBSTR("NominalDiameter"),&var);
   m_db = var.dblVal;

   load->get_Property(CComBSTR("NominalArea"),&var);
   m_Ab = var.dblVal;

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CRebar::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("Rebar"),1.0);

   save->put_Property(CComBSTR("Name"),CComVariant(m_Name));
   save->put_Property(CComBSTR("E"),CComVariant(m_E));
   save->put_Property(CComBSTR("Density"),CComVariant(m_Density));
   save->put_Property(CComBSTR("UltimateStrength"),CComVariant(m_fpu));
   save->put_Property(CComBSTR("YieldStrength"),CComVariant(m_fpy));
   save->put_Property(CComBSTR("NominalDiameter"),CComVariant(m_db));
   save->put_Property(CComBSTR("NominalArea"),CComVariant(m_Ab));

   save->EndUnit();

   return S_OK;
}

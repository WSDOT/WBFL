///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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

// RCBeam.cpp : Implementation of CRCBeam
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "RCBeam.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRCBeam
HRESULT CRCBeam::FinalConstruct()
{
   HRESULT hr = m_UnitServer.CoCreateInstance(CLSID_UnitServer);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
   {
      return E_FAIL;
   }

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertToBaseUnits(7.0,CComBSTR("ksi"),&m_FcBeam);
   convert->ConvertToBaseUnits(4.0,CComBSTR("ksi"),&m_FcSlab);
   convert->ConvertToBaseUnits(270.0,CComBSTR("ksi"),&m_Fpu);
   convert->ConvertToBaseUnits(149.0,CComBSTR("ksi"),&m_Fpe);
   convert->ConvertToBaseUnits(60.0,CComBSTR("ksi"),&m_Fy);
   convert->ConvertToBaseUnits(29000.0,CComBSTR("ksi"),&m_Es);
   convert->ConvertToBaseUnits(28600.0,CComBSTR("ksi"),&m_Eps);

   convert->ConvertToBaseUnits(6.0,CComBSTR("in"),&m_hf);
   convert->ConvertToBaseUnits(72.0,CComBSTR("in"),&m_b);
   convert->ConvertToBaseUnits(6.0,CComBSTR("in"),&m_bw);
   convert->ConvertToBaseUnits(65.0,CComBSTR("in"),&m_ds);
   convert->ConvertToBaseUnits(65.0,CComBSTR("in"),&m_dps);
   convert->ConvertToBaseUnits(68.0,CComBSTR("in"),&m_h);

   m_Aps    = 0; // if the default changes from zero, then a unit conversion is required
   m_As     = 0;

   m_Fpy    = 0.9*m_Fpu;

   return S_OK;
}

void CRCBeam::FinalRelease()
{
   m_UnitServer.Release();
}

STDMETHODIMP CRCBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRCBeam,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CRCBeam::get_b(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_b;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_b(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_b = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_bw(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_bw;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_bw(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_bw = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_hf(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_hf;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_hf(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_hf = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_As(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_As;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_As(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_As = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_fy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Fy;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_fy(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Fy = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_Aps(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Aps;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_Aps(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Aps = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_fpu(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Fpu;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_fpu(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Fpu = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_fpy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Fpy;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_fpy(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Fpy = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_FcSlab(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_FcSlab;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_FcSlab(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_FcSlab = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_FcBeam(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_FcBeam;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_FcBeam(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_FcBeam = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_ds(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_ds;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_ds(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_ds = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_dps(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_dps;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_dps(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_dps = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_fpe(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Fpe;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_fpe(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Fpe = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_h(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_h;
	return S_OK;
}

STDMETHODIMP CRCBeam::put_h(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_h = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam::get_Es(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Es;
   return S_OK;
}

STDMETHODIMP CRCBeam::put_Es(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_Es = newVal;
   return S_OK;
}

STDMETHODIMP CRCBeam::get_Eps(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Eps;
   return S_OK;
}

STDMETHODIMP CRCBeam::put_Eps(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_Eps = newVal;
   return S_OK;
}

STDMETHODIMP CRCBeam::get_UnitServer(IUnitServer** ppVal )
{
   CHECK_RETOBJ(ppVal);

   (*ppVal) = m_UnitServer;
   (*ppVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CRCBeam::putref_UnitServer(IUnitServer* pNewVal )
{
   CHECK_IN(pNewVal);

   m_UnitServer = pNewVal;
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CRCBeam::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("RCBeam"),1.0);

   pSave->put_Property(CComBSTR("b"),  CComVariant(m_b));
   pSave->put_Property(CComBSTR("hf"), CComVariant(m_hf));
   pSave->put_Property(CComBSTR("h"),  CComVariant(m_h));
   pSave->put_Property(CComBSTR("bw"), CComVariant(m_bw));

   pSave->put_Property(CComBSTR("ds"), CComVariant(m_ds));
   pSave->put_Property(CComBSTR("As"), CComVariant(m_As));

   pSave->put_Property(CComBSTR("dps"),CComVariant(m_dps));
   pSave->put_Property(CComBSTR("Aps"),CComVariant(m_Aps));

   pSave->put_Property(CComBSTR("Es"), CComVariant(m_Es));
   pSave->put_Property(CComBSTR("Eps"),CComVariant(m_Eps));

   pSave->put_Property(CComBSTR("FcBeam"),CComVariant(m_FcBeam));
   pSave->put_Property(CComBSTR("FcSlab"),CComVariant(m_FcSlab));

   pSave->put_Property(CComBSTR("fpu"),CComVariant(m_Fpu));
   pSave->put_Property(CComBSTR("fpe"),CComVariant(m_Fpe));
   pSave->put_Property(CComBSTR("fpy"),CComVariant(m_Fpy));
   pSave->put_Property(CComBSTR("fy"), CComVariant(m_Fy));

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CRCBeam::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("RCBeam"));


   if ( FAILED(pLoad->get_Property(CComBSTR("b"),  &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_b = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("hf"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_hf = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("h"),  &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_h = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("bw"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_bw = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("ds"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_ds = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("As"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_As = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("dps"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_dps = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("Aps"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Aps = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("Es"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Es = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("Eps"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Eps = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("FcBeam"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_FcBeam = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("FcSlab"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_FcSlab = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("fpu"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Fpu = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("fpe"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Fpe = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("fpy"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Fpy = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("fy"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Fy = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
